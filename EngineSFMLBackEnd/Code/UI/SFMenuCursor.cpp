#include "SFMenuCursor.h"

SFMenuCursor::SFMenuCursor(SFSprite* sprite, const MenuNav& menuNav)
	: IMenuCursor(std::move(static_cast<ISprite*>(sprite)), menuNav)
{}

void SFMenuCursor::SetPosition(const Vector2f& pos)
{
	ENSURE_VALID(m_cursor);
	static_cast<SFSprite*>(m_cursor.get())->SetPosition(pos);
}

void SFMenuCursor::SetScale(const Vector2f& cellSize)
{
    ENSURE_VALID(m_cursor);
    auto spr = static_cast<SFSprite*>(m_cursor.get());

    spr->SetScale({ 1.f, 1.f });

    auto texSize = spr->GetTextureSize();

    // compare against local (texture) size, not global GetSize()
    Vector2f tex = Vector2f(static_cast<int>(texSize.x), static_cast<int>(texSize.y));
    Vector2f scaleXY = { cellSize.x / tex.x, cellSize.y / tex.y };

    float scale = std::min(scaleXY.x, scaleXY.y);
    spr->SetScale({ scale, scale });
}
