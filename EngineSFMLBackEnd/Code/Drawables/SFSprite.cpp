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
	if (!CheckNotNull(gameMgr, std::format("Invalid Pointer 'baseTex' GetTextureMgr().GetTexture({})", texId)))
		return false;

	// Backend type check
	auto* sfTex = dynamic_cast<SFTexture*>(baseTex);
	if (!CheckNotNull(sfTex, "Invalid Pointer 'sfTex'"))
		return false;

	auto sfSpr = std::make_shared<sf::Sprite>(sfTex->GetNativeTexture());
	if (!CheckNotNull(sfSpr.get(), "Invalid Pointer 'sfSpr'"))
		return false;

	// Apply to drawable
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

SFAnimatedSprite::SFAnimatedSprite(const std::string& texId, int rows, int columns, float framesPerSec, bool symmetrical, float animSpeed)
	: SFSprite(texId), m_animSpeed(animSpeed), m_framesPerSecond(framesPerSec / 1000.0f), m_symmetrical(symmetrical)
{
	auto texSize = GetTextureSize();
	SetFrameSize({ texSize.x / static_cast<unsigned>(columns), texSize.y / static_cast<unsigned>(rows) });
}

SFAnimatedSprite::SFAnimatedSprite(const std::string& texId, float framesPerSec, bool symmetrical, float animSpeed)
	: SFSprite(texId), m_animSpeed(animSpeed), m_framesPerSecond(framesPerSec / 1000.0f), m_symmetrical(symmetrical)
{
}

void SFAnimatedSprite::Update(float dt)
{
	if (!m_loop)
	{
		if (m_frame.m_current == m_numFrames[m_animation.m_current])
			return;
	}

	m_currentTime += m_animSpeed * dt;

	if (m_currentTime >= m_framesPerSecond)
	{
		m_currentTime = 0.0f;

		++m_frame.m_current;

		if (m_symmetrical)
		{
			if (m_frame.m_current >= m_frame.m_max)
				m_frame.m_current = 0;
		}
		else
		{
			if (m_frame.m_current >= m_numFrames[m_animation.m_current])
			{
				if (m_loop)
					m_frame.m_current = 0;
				else
					--m_frame.m_current;
				++m_animCycles;
			}
		}

		int left = m_frame.m_current * GetFrameSize().x;
		int top = m_animation.m_current * GetFrameSize().y;
		SetTextureRect({ left, top, static_cast<int>(GetFrameSize().x), static_cast<int>(GetFrameSize().y) });
	}
}

Vector2f SFAnimatedSprite::GetSize()
{
	auto size = GetFrameSize();
	return Vector2f(static_cast<float>(size.x), static_cast<float>(size.y));
}

void SFAnimatedSprite::SetFrameSize(const Vector2u& size, int currentFrame, int currentAnim)
{
	m_frameSize = size;

	int left = currentFrame * size.x;
	int top = currentAnim * size.y;

	SetTextureRect({left, top, static_cast<int>(size.x), static_cast<int>(size.y)});
	SetOrigin(Vector2f(static_cast<float>(size.x), static_cast<float>(size.y)) * 0.5f);
}

void SFAnimatedSprite::ChangeAnim(int animNum)
{
	m_animCycles = 0;
	m_animation.m_current = animNum;
}

void SFAnimatedSprite::EnsureAnim(int anim)
{
	if (GetCurrentAnim() != anim)
		ChangeAnim(anim);
}

void SFAnimatedSprite::SetFrames(const std::vector<int>& numFrames)
{
	m_numFrames.assign(numFrames.begin(), numFrames.end());
	m_animation.m_max = m_numFrames[m_animation.m_current];
}

void SFAnimatedSprite::SetFrameData(int rows, int columns, const std::vector<int>& numFrames)
{
	auto texSize = GetTextureSize();
	SetFrameSize({ texSize.x / static_cast<unsigned>(columns), texSize.y / static_cast<unsigned>(rows) });
	SetFrames(numFrames);
}

void SFAnimatedSprite::UpdateAnimSpeed(float animSpd)
{
	if (m_animSpeed != animSpd)
		m_animSpeed = animSpd;
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
