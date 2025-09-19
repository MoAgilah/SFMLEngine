#include "SFSprite.h"

#include "Resources/SFTexture.h"
#include <Engine/Core/Constants.h>
#include <Engine/Core/GameManager.h>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

SFSprite::SFSprite(const std::string& texId)
{
	SetTexture(texId);
}

void SFSprite::SetTexture(const std::string& texId)
{
	m_texID = texId;

	try
	{
		SetDrawable(std::make_shared<sf::Sprite>(dynamic_cast<SFTexture*>(GameManager::Get()->GetTextureMgr().GetTexture(m_texID))->GetNativeTexture()));
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << "Texture Error: " << e.what() << std::endl;
	}

	SetScale(GameConstants::Scale);
	auto texSize = GetTextureSize();
	SetOrigin(Vector2f(static_cast<float>(texSize.x), static_cast<float>(texSize.y)) * 0.5f);
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
	return this->GetPrimaryDrawableAs<sf::Sprite>();
}

void SFSprite::Move(float x, float y)
{
	Move(Vector2f(x, y));
}

void SFSprite::Move(const Vector2f& mov)
{
	for (auto spr : this->GetDrawables())
		spr->move(mov);
}

Vector2u SFSprite::GetTextureSize() const
{
	return this->GetPrimaryDrawableAs<sf::Sprite>()->getTexture().getSize();
}

void SFSprite::SetTextureRect(const IntRect& rect)
{
	this->GetPrimaryDrawableAs<sf::Sprite>()->setTextureRect(rect);
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