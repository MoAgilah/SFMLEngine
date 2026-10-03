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
	ThrowIfFalse(Init(), "SFText initialization failed");
}

void SFText::Update(float deltaTime)
{
	UpdateEffect(deltaTime);

	SFDrawables<sf::Text>::Update(deltaTime);
}

void SFText::Render(IRenderer* renderer)
{
	if (auto* effect = GetEffect())
	{
		SFDrawables<sf::Text>::Render(renderer, effect->GetShader());
		return;
	}

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

SFCountDownText::SFCountDownText(const TextConfig& config, float countdownInterval, int startFrom, const std::string& countDownMessage)
	: SFText(config), ICountdownText(countdownInterval, startFrom, countDownMessage)
{
	SetText(std::to_string(GetCount()));
}

void SFCountDownText::Update(float deltaTime)
{
	ICountdownText::Update(deltaTime);

	if (CountHasEnded())
	{
		SetText(m_countdownMsg);
	}
	else
	{
		SetText(std::to_string(GetCount()));
	}

	SFText::Update(deltaTime);
}
