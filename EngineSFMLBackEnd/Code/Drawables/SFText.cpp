#include "SFText.h"

#include "../Resources/SFFont.h"
#include "../Resources/SFShader.h"
#include <Engine/Core/GameManager.h>
#include <Utilities/Guards.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Text.hpp>

SFText::SFText(const TextConfig& config)
	: IText(config)
{
	ThrowIfFalse(
		m_config.m_animType == TextAnimType::Static,
		"SFText requires TextAnimType::Static."
	);

	ThrowIfFalse(Init(), "SFText initialization failed");
}

void SFText::Update(float deltaTime)
{
	SFDrawables<sf::Text>::Update(deltaTime);
}

void SFText::Render(IRenderer* renderer)
{
	SFDrawables<sf::Text>::Render(renderer);
}

void SFText::SetText(const std::string& text)
{
	auto txtObj = this->GetPrimaryDrawableAs<sf::Text>();

	txtObj->setString(text);

	if (m_config.m_alignment == TextAlignment::None)
		return;

	const sf::FloatRect b = txtObj->getLocalBounds();

	float xFactor = 0.5f;
	switch (m_config.m_alignment)
	{
	case TextAlignment::LeftHand:  xFactor = 0.f;   break;
	case TextAlignment::Center:    xFactor = 0.5f;  break;
	case TextAlignment::RightHand: xFactor = 1.f;   break;
	}

	const float yFactor = 0.5f;

	const sf::Vector2f origin
	{
		b.position.x + (b.size.x * xFactor),
		b.position.y + (b.size.y * yFactor)
	};

	txtObj->setOrigin(origin);
}


Vector2f SFText::GetSize()
{
	if (auto* txt = this->GetPrimaryDrawable())
	{
		auto bounds = txt->getLocalBounds();
		return Vector2f(bounds.size);
	}

	return {};
}

unsigned int SFText::GetCharSize()
{
	if (auto* txt = this->GetPrimaryDrawable())
		return txt->getCharacterSize();

	return {};
}

void SFText::SetCharSize(unsigned int charSize)
{
	if (auto* txt = this->GetPrimaryDrawable())
		txt->setCharacterSize(charSize);
}

Colour SFText::GetOutlineColour()
{
	if (auto* txt = this->GetPrimaryDrawable())
		return txt->getOutlineColor();

	return {};
}

void SFText::SetOutlineColour(const Colour& colour)
{
	if (auto* txt = this->GetPrimaryDrawable())
		return txt->setOutlineColor(colour);
}

Colour SFText::GetFillColour()
{
	if (auto* txt = this->GetPrimaryDrawable())
		return txt->getFillColor();

	return {};
}

void SFText::SetFillColour(const Colour& colour)
{
	if (auto* txt = this->GetPrimaryDrawable())
		return txt->setFillColor(colour);
}

float SFText::GetOutlineThickness()
{
	if (auto* txt = this->GetPrimaryDrawable())
		return txt->getOutlineThickness();

	return {};
}

void SFText::SetOutlineThickness(float thickness)
{
	if (auto* txt = this->GetPrimaryDrawable())
		return txt->setOutlineThickness(thickness);
}

SFText::SFText(const TextConfig& config, bool initialise)
	: IText(config)
{
	if (initialise)
		ThrowIfFalse(Init(), "SFText initialization failed");
}


bool SFText::Init()
{
	auto* gameMgr = GameManager::Get();
	if (!CheckNotNull(gameMgr, "Invalid Pointer 'gameMgr' from GameManager::Get()"))
		return false;

	auto* baseFont = gameMgr->GetFontMgr().GetFont(m_config.m_fontName);
	if (!CheckNotNull(baseFont, "Invalid Pointer 'baseFont' from GetFontMgr().GetFont"))
		return false;

	auto* sfFont = static_cast<SFFont*>(baseFont);

	SetDrawable(std::make_shared<sf::Text>(sfFont->GetNativeFont()));

	SetCharSize(m_config.m_charSize);
	SetOutlineThickness(m_config.m_charSize / 10.f);
	SetOutlineColour(m_config.m_colour);
	SetPosition(m_config.m_position);

	return true;
}

SFAnimatedText::SFAnimatedText(const TextConfig& config)
	: SFText(config, false), m_timer(1.f), m_textShader(nullptr), m_updateFunc(nullptr), m_renderFunc(nullptr)
{
	ThrowIfFalse(m_config.m_animType != TextAnimType::Custom, "TextConfig can't initialize TextAnimType::Custom");
	ThrowIfFalse(Init(), "SFAnimatedText initialization failed");
}

SFAnimatedText::SFAnimatedText(const CustomTextConfig& ctc)
	: SFText(ctc.m_config, false), m_timer(1.f), m_textShader(nullptr), m_updateFunc(ctc.m_updateFunc), m_renderFunc(ctc.m_renderFunc)
{
	ThrowIfFalse(m_config.m_animType == TextAnimType::Custom, "CustomTextConfig can't initialize TextAnimType types other than TextAnimType::Custom");
	ThrowIfFalse(Init(), "SFAnimatedText initialization failed");

	if (!ctc.m_shaderName.empty())
		ThrowIfFalse(LoadShader(ctc.m_shaderName), std::format("LoadShader failed: id-{}", ctc.m_shaderName));
}

void SFAnimatedText::Update(float deltaTime)
{
	switch (m_config.m_animType)
	{
	case TextAnimType::Flashing:
	case TextAnimType::Countdown:
		FadeInAndOutUpdate(deltaTime);
		break;
	case TextAnimType::Custom:
		if (m_updateFunc)
			m_updateFunc(deltaTime);
		break;
	}
}

void SFAnimatedText::Render(IRenderer* renderer)
{
	if (!CheckNotNull(renderer, "Invalid Pointer 'renderer'"))
		return;

	switch (m_config.m_animType)
	{
	case TextAnimType::Flashing:
	case TextAnimType::Countdown:
		FadeInFadeOutRender(renderer);
		break;
	case TextAnimType::Custom:
		if (m_renderFunc)
			m_renderFunc(renderer);
		break;
	}
}

void SFAnimatedText::InitFlashingText(const std::string& text, bool loop)
{
	SetIsLooping(loop);
	SetText(text);
}

void SFAnimatedText::InitCountdownText(int startFrom, const std::string& countDownMessage)
{
	SetMaxCount(startFrom);
	SetIsLooping(false);
	SetCountDown(countDownMessage);
	SetText(std::to_string(startFrom));
	m_timer.SetMaxTime(1.f);
	m_timer.RestartTimer(); // start ticking immediately
}

void SFAnimatedText::SetMaxCount(int startFrom)
{
	ThrowIfFalse(
		startFrom > 0,
		"Countdown start value must be greater than zero."
	);

	m_count = m_maxCount = startFrom;
	m_countEnded = false;
}

void SFAnimatedText::SetUpdateFunc(UpdateFunc func)
{
	m_updateFunc = func;
}

void SFAnimatedText::SetRenderFunc(RenderFunc func)
{
	m_renderFunc = func;
}

bool SFAnimatedText::LoadShader(const std::string& shaderID)
{
	auto* gameMgr = GameManager::Get();
	if (!CheckNotNull(gameMgr, "Invalid Pointer 'gameMgr' from GameManager::Get()"))
		return false;

	auto* shader = gameMgr->GetShaderMgr().GetShader(shaderID);
	if (!CheckNotNull(shader, std::format("Invalid Pointer 'shader' from GetShaderMgr().GetShader({})", shaderID)))
		return false;

	m_textShader = shader;

	return true;
}

void SFAnimatedText::FadeInAndOutUpdate(float deltaTime)
{
	if (m_paused)
	{
		m_timer.SetCurrTime(m_looping ? 1.f : 0.f);
		return;
	}

	if (m_reduceAlpha)
	{
		m_timer.Update(deltaTime);

		if (m_timer.CheckEnd())
		{
			m_reduceAlpha = false;

			if (m_timer.GetCurrTime() < 0.f)
				m_timer.SetCurrTime(0.f);
		}

		return;
	}

	if (m_looping)
	{
		m_timer.Update(-deltaTime);

		if (m_timer.GetCurrTime() >= m_timer.GetMaxTime())
		{
			m_reduceAlpha = true;
			m_timer.RestartTimer();
		}

		return;
	}

	if (m_countEnded)
	{
		m_paused = true;
		return;
	}

	m_timer.Update(deltaTime);

	if (!m_timer.CheckEnd())
		return;

	if (m_count > 0)
	{
		--m_count;
		SetText(std::to_string(m_count));
		m_timer.RestartTimer();
	}
	else
	{
		SetText(m_countdownMsg);
		m_countEnded = true;
	}
}

void SFAnimatedText::FadeInFadeOutRender(IRenderer* renderer)
{
	if (!CheckNotNull(renderer, "Invalid Pointer 'renderer'"))
		return;

	if (!CheckNotNull(m_textShader, "Invalid Pointer 'm_textShader'"))
		return;

	auto* drawable = this->GetPrimaryDrawable();
	if (!CheckNotNull(drawable, "Invalid Pointer 'drawable'"))
		return;

	auto* shader = dynamic_cast<SFShader*>(m_textShader);
	if (!CheckNotNull(shader, "Invalid Pointer 'shader'"))
		return;

	shader->GetNativeShader().setUniform("time", m_timer.GetCurrTime());

	renderer->Draw(this, m_textShader);
}

bool SFAnimatedText::Init()
{
	ThrowIfFalse(SFText::Init(), "SFText parent initialization failed");

	switch (m_config.m_animType)
	{
	case TextAnimType::Flashing:
	{
		ThrowIfFalse(LoadShader("FadeInOutShader"),
			std::format("LoadShader failed: id-{}",
			"FadeInOutShader"));
	}
		break;
	case TextAnimType::Countdown:
	{
		ThrowIfFalse(LoadShader("FadeInOutShader"),
			std::format("LoadShader failed: id-{}",
			"FadeInOutShader"));
	}
		break;
	default:
		// no special resources needed; keep going
		break;
	}

	return true;
}