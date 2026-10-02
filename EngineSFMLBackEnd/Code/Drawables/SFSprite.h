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

	void SetDirection(bool dir) override;

	void Update(float dt) override;
	void Render(IRenderer* renderer) override;

	sf::Sprite* GetSprite();

	Vector2u GetTextureSize() const override;
	void SetTextureRect(const IntRect& rect) override;

private:

	std::string m_texID;
};

SFSprite* GetSprite(IDrawable* drawable);

class SFAnimatedSprite : public SFSprite, public IAnimatedSprite
{
public:
	SFAnimatedSprite(const std::string& texId, int rows, int columns, float frameDurationMs, float animationSpeed);

	void Update(float dt) override;

	Vector2f GetSize() override;

	Vector2u GetFrameSize() const { return m_frameSize; }
	void SetFrameSize(const Vector2u& size) override;

	void SetFrameData(int rows, int columns, const std::vector<int>& numFrames) override;
};

SFAnimatedSprite* GetAnimatedSprite(IDrawable* drawable);