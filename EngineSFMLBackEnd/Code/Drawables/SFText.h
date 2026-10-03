#pragma once

#include "SFDrawables.h"
#include <Engine/Interface/Drawables/IText.h>
#include <Engine/Core/CountdownTimer.h>
#include <Utilities/Vector2.h>
#include <optional>
#include <string>

namespace sf { class Text; }

class SFText : public SFDrawables<sf::Text>, public IText
{
public:
	SFText(const TextConfig& config);

	void Update(float deltaTime) override;
	void Render(IRenderer* renderer) override;

	void SetText(const std::string& text) override;

	Vector2f GetSize() override;

	unsigned int GetCharSize() override;
	void SetCharSize(unsigned int charSize) override;

	Colour GetOutlineColour() override;
	void SetOutlineColour(const Colour& colour) override;

	Colour GetFillColour() override;
	void SetFillColour(const Colour& colour) override;

	float GetOutlineThickness() override;
	void SetOutlineThickness(float thickness) override;

	void ResetOutlineColour() { SetOutlineColour(m_config.m_colour); }

protected:

	bool Init() override;
};

class SFCountDownText : public SFText, public ICountdownText
{
public:
	SFCountDownText(const TextConfig& config, float countdownInterval, int startFrom, const std::string& countDownMessage);

	void Update(float deltaTime) override;
};