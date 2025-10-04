#include "SFText.h"

#include "../Resources/SFFont.h"
#include "../Resources/SFShader.h"
#include <Engine/Core/GameManager.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Text.hpp>

SFText::SFText(const TextConfig& config)
	: IText(config)
{
	auto font = dynamic_cast<SFFont*>(GameManager::Get()->GetFontMgr().GetFont(m_config.m_fontName));

	if (font)
		SetDrawable(std::make_shared<sf::Text>(font->GetNativeFont()));
	else
		std::cerr << "Font Error: Could not find font '" << m_config.m_fontName << "'\n";

	Init();
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

void SFText::Reset(const std::string& text, std::optional<TextConfig> config)
{
	if (config)
	{
		m_config = *config;
		Init();
	}

	SetText(text);
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

void SFText::Init()
{
	SetCharSize(m_config.m_charSize);
	SetOutlineThickness(m_config.m_charSize / 10.f);
	SetOutlineColour(m_config.m_colour);
	SetPosition(m_config.m_position);
}

SFAnimatedText::SFAnimatedText(const TextConfig& config)
	: SFText(config), m_timer(1.f), m_textShader(nullptr)
{
	switch (m_config.m_animType)
	{
	case TextAnimType::Flashing:
	case TextAnimType::Countdown:
	{
		auto shader = dynamic_cast<SFShader*>(GameManager::Get()->GetShaderMgr().GetShader("FadeInOutShader"));
		if (shader)
			m_textShader = &shader->GetNativeShader();
		else
			std::cerr << "Shader Error: 'FadeInOutShader' not found\n";
	}
		break;
	}
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

void SFAnimatedText::Reset(const std::string& text, std::optional<TextConfig> config)
{
	if (config)
		m_config = *config;

	SetText(text);
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
					Reset(std::to_string(m_count));
				}
				else
				{
					Reset(m_countdownMsg);
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
	if (!renderer || !this->GetPrimaryDrawableAs<sf::Text>() || !m_textShader)
		return;

	m_textShader->setUniform("time", m_timer.GetCurrTime());

	if (auto* windowHandle = renderer->GetWindow())
	{
		auto* sfWindow = static_cast<sf::RenderWindow*>(windowHandle->GetNativeHandle());
		if (sfWindow)
		{
			sf::RenderStates states;
			states.shader = m_textShader;
			sfWindow->draw(*this->GetPrimaryDrawable(), states);
		}
	}
}

void InitFlashingText(SFAnimatedText* txtObj, const std::string& text, bool loop, std::optional<TextConfig> config)
{
	if (txtObj)
	{
		txtObj->SetIsLooping(loop);
		txtObj->Reset(text, config);
	}
}

void InitCountdownText(SFAnimatedText* txtObj, int startFrom, const std::string& countDownMessage, std::optional<TextConfig> config)
{
	if (txtObj)
	{
		txtObj->SetMaxCount(startFrom);
		txtObj->SetIsLooping(false);
		txtObj->SetCountDown(countDownMessage);
		txtObj->Reset(std::to_string(startFrom), config);
	}
}

void InitCustomTextAnim(SFAnimatedText* txtObj, const std::string& text, UpdateFunc updator, RenderFunc rendaror, const std::string& shaderName, std::optional<TextConfig> config)
{
	if (txtObj)
	{
		txtObj->SetUpdateFunc(updator);
		txtObj->SetRenderFunc(rendaror);
		txtObj->Reset(text, config);
	}
}