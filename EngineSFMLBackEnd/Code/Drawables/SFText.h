#pragma once

#include "SFDrawables.h"
#include <Engine/Interface/UI/IText.h>
#include <Engine/Core/Timer.h>
#include <Utilities/Vector.h>
#include <optional>
#include <string>

namespace sf { class Text; }

class SFText : public SFDrawables<sf::Text>, public IText
{
public:
	SFText() {}
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

class SFAnimatedText : public SFText
{
public:
	SFAnimatedText(const TextConfig& config);
	SFAnimatedText(const CustomTextConfig& config);

	void Update(float deltaTime) override;
	void Render(IRenderer* renderer) override;

	void InitFlashingText(const std::string& text, bool loop = true);
	void InitCountdownText(int startFrom, const std::string& countDownMessage);

	bool GetIsLooping() const { return m_looping; }
	void SetIsLooping(bool loop) { m_looping = loop; }

	bool GetIsPaused() const { return m_paused; }
	void SetIsPaused(bool pause) { m_paused = pause; }

	void SetMaxCount(int startFrom);
	bool CountHasEnded() const { return m_count == -1; }

	void SetCountDown(const std::string& msg) { m_countdownMsg = msg; }

	void SetUpdateFunc(UpdateFunc func);
	void SetRenderFunc(RenderFunc func);

	Timer& GetTimer() { return m_timer; }

protected:

	bool Init() override;

private:

	bool LoadShader(const std::string& shader);

	void FadeInAndOutUpdate(float deltaTime);
	void FadeInFadeOutRender(IRenderer* renderer);

private:

	Timer m_timer;
	bool m_paused = false;
	bool m_looping = true;
	bool m_reduceAlpha = true;
	int m_count = 0;
	int m_maxCount = 0;
	UpdateFunc m_updateFunc;
	RenderFunc m_renderFunc;
	std::string m_countdownMsg;
	IShader* m_textShader;
};