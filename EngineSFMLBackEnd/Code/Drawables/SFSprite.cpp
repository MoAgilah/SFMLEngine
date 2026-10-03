#include "SFSprite.h"

#include "Resources/SFTexture.h"
#include <Engine/Core/Constants.h>
#include <Engine/Core/GameManager.h>
#include <Utilities/Guards.h>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>


SFSprite::SFSprite(const std::string& texId)
{
	ThrowIfFalse(SetTexture(texId), "SFSprite initialization failed");
}

bool SFSprite::SetTexture(const std::string& texId)
{
	auto* gameMgr = GameManager::Get();
	if (!CheckNotNull(gameMgr, "Invalid Pointer 'gameMgr' from GameManager::Get()"))
		return false;

	auto* baseTex = gameMgr->GetTextureMgr().GetTexture(texId);
	if (!CheckNotNull(baseTex, std::format("Invalid Pointer 'baseTex' GetTextureMgr().GetTexture({})", texId)))
		return false;

	auto* sfTex = static_cast<SFTexture*>(baseTex);

	auto sfSpr = std::make_shared<sf::Sprite>(sfTex->GetNativeTexture());

	SetDrawable(std::move(sfSpr));

	m_texID = texId;
	SetScale(GameConstants::Scale);
	const auto texSize = GetTextureSize();
	SetOrigin(Vector2f(static_cast<float>(texSize.x), static_cast<float>(texSize.y)) * 0.5f);

	return true;
}

void SFSprite::SetDirection(bool dir)
{
	auto* sfSpr = this->GetPrimaryDrawableAs<sf::Sprite>();
	if (!CheckNotNull(sfSpr, "Invalid Pointer 'sfSpr'"))
		return;

	if (dir)
	{
		// flip X
		sfSpr->setScale(GameConstants::Scale);
	}
	else
	{
		//unflip x
		sfSpr->setScale({ -GameConstants::Scale.x, GameConstants::Scale.y });
	}
}


void SFSprite::Update(float dt)
{
	// does nothing
}

void SFSprite::Render(IRenderer* renderer)
{
	SFDrawables<sf::Sprite>::Render(renderer);
}

sf::Sprite* SFSprite::GetSprite()
{
	auto* sfSpr = this->GetPrimaryDrawableAs<sf::Sprite>();
	if (!CheckNotNull(sfSpr, "Invalid Pointer 'sfSpr'"))
		return nullptr;

	return sfSpr;
}

Vector2u SFSprite::GetTextureSize() const
{
	auto* sfSpr = this->GetPrimaryDrawableAs<sf::Sprite>();
	if (!CheckNotNull(sfSpr, "Invalid Pointer 'sfSpr'"))
		return Vector2u();

	return sfSpr->getTexture().getSize();
}

void SFSprite::SetTextureRect(const IntRect& rect)
{
	auto* sfSpr = this->GetPrimaryDrawableAs<sf::Sprite>();
	if (!CheckNotNull(sfSpr, "Invalid Pointer 'sfSpr'"))
		return;

	sfSpr->setTextureRect(rect);
}

SFAnimatedSprite::SFAnimatedSprite(const std::string& texId, int rows, int columns, float frameDurationMs, float animSpeed)
	: SFSprite(texId), IAnimatedSprite(animSpeed, frameDurationMs)
{
	ThrowIfFalse(
		rows > 0,
		"Animation rows must be greater than zero."
	);

	ThrowIfFalse(
		columns > 0,
		"Animation columns must be greater than zero."
	);

	auto texSize = GetTextureSize();
	SetFrameSize({ texSize.x / static_cast<unsigned>(columns), texSize.y / static_cast<unsigned>(rows) });
}

void SFAnimatedSprite::Update(float dt)
{
	IAnimatedSprite::Update(dt);

	int left = m_frame.m_current * GetFrameSize().x;
	int top = m_animation.m_current * GetFrameSize().y;
	SetTextureRect({ left, top, static_cast<int>(GetFrameSize().x), static_cast<int>(GetFrameSize().y) });
}

Vector2f SFAnimatedSprite::GetSize()
{
	auto size = GetFrameSize();
	return Vector2f(static_cast<float>(size.x), static_cast<float>(size.y));
}

void SFAnimatedSprite::SetFrameSize(const Vector2u& size)
{
	ThrowIfFalse(
		size.x > 0,
		"Animation frame width must be greater than zero."
	);

	ThrowIfFalse(
		size.y > 0,
		"Animation frame height must be greater than zero."
	);

	m_frameSize = size;

	SetTextureRect({0, 0, static_cast<int>(size.x), static_cast<int>(size.y)});
	SetOrigin(Vector2f(static_cast<float>(size.x), static_cast<float>(size.y)) * 0.5f);
}

void SFAnimatedSprite::SetFrameData(int rows, int columns, const std::vector<int>& numFrames)
{
	ThrowIfFalse(
		rows > 0,
		"Animation rows must be greater than zero."
	);

	ThrowIfFalse(
		columns > 0,
		"Animation columns must be greater than zero."
	);

	auto texSize = GetTextureSize();
	SetFrameSize({ texSize.x / static_cast<unsigned>(columns), texSize.y / static_cast<unsigned>(rows) });
	SetFrames(numFrames);
}

SFSprite* GetSprite(IDrawable* drawable)
{
	auto* spr = dynamic_cast<SFSprite*>(drawable);
	if (!CheckNotNull(spr, "Invalid Pointer 'spr'"))
		return nullptr;

	return spr;
}

SFAnimatedSprite* GetAnimatedSprite(IDrawable* drawable)
{
	auto* spr = dynamic_cast<SFAnimatedSprite*>(drawable);
	if (!CheckNotNull(spr, "Invalid Pointer 'spr'"))
		return nullptr;

	return spr;
}
