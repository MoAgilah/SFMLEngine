#pragma once

#include "SFDrawables.h"
#include <Engine/Interface/UI/IText.h>
#include <Engine/Core/Timer.h>
#include <Utilities/Vector.h>
#include <string>
#include <optional>
#include <functional>

namespace sf { class Text; class Shader; }

class SFText : public SFDrawables<sf::Text>, public IText
{
public:
	SFText() {}
	SFText(const TextConfig& config);

	void Update(float deltaTime) override;
	void Render(IRenderer* renderer) override;

	virtual void SetText(const std::string& text);
	virtual void Reset(const std::string& text, std::optional<TextConfig> config = std::nullopt);

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

private:

	void Init() override;
};

using UpdateFunc = std::function<void(float)>;
using RenderFunc = std::function<void(IRenderer* renderer)>;

class SFAnimatedText : public SFText
{
public:
	SFAnimatedText(const TextConfig& config);

	void Update(float deltaTime) override;
	void Render(IRenderer* renderer) override;

	void Reset(const std::string& text, std::optional<TextConfig> config = std::nullopt) override;

	bool GetIsLooping() { return m_looping; }
	void SetIsLooping(bool loop) { m_looping = loop; }

	bool GetIsPaused() { return m_paused; }
	void SetIsPaused(bool pause) { m_paused = pause; }

	void SetMaxCount(int startFrom);
	bool CountHasEnded() const { return m_count == 0; }

	void SetCountDown(const std::string& msg) { m_countdownMsg = msg; }

	void SetUpdateFunc(UpdateFunc func);
	void SetRenderFunc(RenderFunc func);

	Timer& GetTimer() { return m_timer; }

private:

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
	sf::Shader* m_textShader;
};

void InitFlashingText(SFAnimatedText* txtObj, const std::string& text, bool loop = true, std::optional<TextConfig> config = std::nullopt);
void InitCountdownText(SFAnimatedText* txtObj, int startFrom, const std::string& countDownMessage, std::optional<TextConfig> config = std::nullopt);
void InitCustomTextAnim(SFAnimatedText* txtObj, const std::string& text, UpdateFunc updator, RenderFunc rendaror, const std::string& shaderName = "", std::optional<TextConfig> config = std::nullopt);