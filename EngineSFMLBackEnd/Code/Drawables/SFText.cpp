#include "SFText.h"

#include "../Resources/SFFont.h"
#include "../Resources/SFShader.h"
#include <Engine/Core/GameManager.h>
#include <Utilities/Utils.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Text.hpp>

SFText::SFText(const TextConfig& config)
	: IText(config)
{
	THROW_IF_FALSE_MSG(Init(), "SFText initialization failed");
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
	if (txtObj)
	{
		txtObj->setString(text);
		auto bounds = txtObj->getLocalBounds();
		SetPosition(SetTextPosition(m_config.m_alignment, GetPosition(), bounds.size, bounds.position));
	}
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

bool SFText::Init()
{
	GameManager* gameMgr = nullptr;
	// Safely get the singleton (catch exceptions → set outError, log, return false)
	ERR_TRY_ASSIGN_OR_RET(gameMgr, GameManager::Get(), false);
	ENSURE_VALID_RET(gameMgr, false);

	IFont* baseFont = nullptr;
	// Safely fetch the texture (catch exceptions → set outError, log, return false)
	ERR_TRY_ASSIGN_OR_RET(baseFont, gameMgr->GetFontMgr().GetFont(m_config.m_fontName), false);
	ENSURE_VALID_RET(baseFont, false);

	// Back end type check
	auto* sfFont = dynamic_cast<SFFont*>(baseFont);
	ENSURE_VALID_RET(sfFont, false);

	SetDrawable(std::make_shared<sf::Text>(sfFont->GetNativeFont()));

	SetCharSize(m_config.m_charSize);
	SetOutlineThickness(m_config.m_charSize / 10.f);
	SetOutlineColour(m_config.m_colour);
	SetPosition(m_config.m_position);

	return true;
}

SFAnimatedText::SFAnimatedText(const TextConfig& config)
	: SFText(config), m_timer(1.f), m_textShader(nullptr), m_updateFunc(nullptr), m_renderFunc(nullptr)
{
	THROW_IF_FALSE_MSG(m_config.m_animType != TextAnimType::Custom, "TextConfig can't initialize TextAnimType::Custom");
	THROW_IF_FALSE_MSG(Init(), "SFAnimatedText initialization failed");
}

SFAnimatedText::SFAnimatedText(const CustomTextConfig& ctc)
	: SFText(ctc.m_config), m_timer(1.f), m_textShader(nullptr), m_updateFunc(ctc.m_updateFunc), m_renderFunc(ctc.m_renderFunc)
{
	THROW_IF_FALSE_MSG(m_config.m_animType == TextAnimType::Custom, "CustomTextConfig can't initialize TextAnimType types other than TextAnimType::Custom");
	THROW_IF_FALSE_MSG(Init(), "SFAnimatedText initialization failed");

	if (!ctc.m_shaderName.empty())
		THROW_IF_FALSE_MSG(LoadShader(ctc.m_shaderName), "LoadShader failed: id-{}", ctc.m_shaderName);
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
	ENSURE_VALID(renderer);

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
}

void SFAnimatedText::SetMaxCount(int startFrom)
{
	m_count = m_maxCount = startFrom;
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
	GameManager* gameMgr = nullptr;
	ERR_TRY_ASSIGN_OR_RET(gameMgr, GameManager::Get(), false);
	ENSURE_VALID_RET(gameMgr, false);

	IShader* shader = nullptr;
	ERR_TRY_ASSIGN_OR_RET(shader, gameMgr->GetShaderMgr().GetShader(shaderID), false);
	ENSURE_VALID_RET(shader, false);

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

	float time;

	if (m_reduceAlpha)
	{
		m_timer.Update(deltaTime);
		time = m_timer.GetCurrTime() / m_timer.GetMaxTime();

		if (m_timer.CheckEnd())
		{
			m_reduceAlpha = false;
			if (time < 0.f)
				m_timer.SetCurrTime(0.f);
		}
	}
	else
	{
		if (m_looping)
		{
			m_timer.Update(-deltaTime);
			time = m_timer.GetCurrTime() / m_timer.GetMaxTime();

			if (m_timer.GetCurrTime() >= m_timer.GetMaxTime())
			{
				m_reduceAlpha = true;
				m_timer.RestartTimer();
			}
		}
		else
		{
			if (!CountHasEnded())
			{
				--m_count;
				if (m_count != 0)
				{
					SetText(std::to_string(m_count));
				}
				else
				{
					SetText(m_countdownMsg);
				}
			}
			else
			{
				m_paused = true;
			}
		}
	}
}

void SFAnimatedText::FadeInFadeOutRender(IRenderer* renderer)
{
	ENSURE_VALID(renderer);
	ENSURE_VALID(m_textShader);
	DECL_GET_OR_RETURN(drawable, this->GetPrimaryDrawable());

	auto shader = dynamic_cast<SFShader*>(m_textShader);
	ENSURE_VALID(shader);

	shader->GetNativeShader().setUniform("time", m_timer.GetCurrTime());

	renderer->Draw(this, m_textShader);
}

bool SFAnimatedText::Init()
{
	THROW_IF_FALSE_MSG(SFText::Init(), "SFText parent initialization failed");

	switch (m_config.m_animType)
	{
	case TextAnimType::Flashing:
	{
		THROW_IF_FALSE_MSG(LoadShader("FadeInOutShader"),
			"LoadShader failed: id-{}",
			"FadeInOutShader");
	}
		break;
	case TextAnimType::Countdown:
	{
		THROW_IF_FALSE_MSG(LoadShader("FadeInOutShader"),
			"LoadShader failed: id-{}",
			"FadeInOutShader");
	}
		break;
	default:
		// no special resources needed; keep going
		break;
	}

	return true;
}