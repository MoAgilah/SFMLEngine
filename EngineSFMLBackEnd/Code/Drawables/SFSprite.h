#pragma once

#include "SFDrawables.h"
#include <Engine/Interface/Drawables/ISprite.h>
#include <string>

namespace sf { class Sprite; }

class SFSprite : public SFDrawables<sf::Sprite>, public ISprite
{
public:
	SFSprite() = default;
	SFSprite(const std::string& texId);

	std::string_view GetTexID() const { return m_texID; }

	bool SetTexture(const std::string& texId) override;

	void Update(float dt) override;
	void Render(IRenderer* renderer) override;

	sf::Sprite* GetSprite();

	Vector2u GetTextureSize() const override;
	void SetTextureRect(const IntRect& rect) override;

private:

	std::string m_texID;
};

struct Range
{
	int m_current = 0;
	int m_max = 0;
};

SFSprite* GetSprite(IDrawable* drawable);

class SFAnimatedSprite : public SFSprite
{
public:
	SFAnimatedSprite(const std::string& texId, int rows, int columns, float framesPerSec, bool symmetrical, float animationSpeed);
	SFAnimatedSprite(const std::string& texId, float framesPerSec, bool symmetrical, float animationSpeed);

	void Update(float dt) override;

	Vector2f GetSize() override;

	Vector2u GetFrameSize() const { return m_frameSize; }
	void SetFrameSize(const Vector2u& size, int currentFrame = 1, int currentAnim = 1);

	void ChangeAnim(int animNum);
	int GetCurrentAnim() const { return m_animation.m_current; }

	void EnsureAnim(int anim);

	void SetFrames(const std::vector<int>& numFrames);
	void SetFrameData(int rows, int columns, const std::vector<int>& numFrames);

	bool PlayedNumTimes(int val) const { return m_animCycles == val; }
	bool PlayedOnce() const { return m_animCycles > 0; }

	void SetShouldLoop(bool loop) { m_loop = loop; }

	float GetCurrAnimSpeed() const { return m_animSpeed; }
	void UpdateAnimSpeed(float animSpd);

private:

	Range m_frame;
	Range m_animation;
	bool m_symmetrical;
	bool m_loop = true;
	int m_frameTime = 0;
	int m_animCycles = 0;
	float m_animSpeed = 0;
	float m_currentTime = 0;
	float m_framesPerSecond = 0;
	Vector2u m_frameSize;
	std::vector<int> m_numFrames;
};

SFAnimatedSprite* GetAnimatedSprite(IDrawable* drawable);