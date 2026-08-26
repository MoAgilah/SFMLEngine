#include "SFMenuCursor.h"

#include <Utilities/Guards.h>

SFMenuCursor::SFMenuCursor(SFSprite* sprite, const MenuNav& menuNav)
	: IMenuCursor(std::move(static_cast<ISprite*>(sprite)), menuNav)
{}

void SFMenuCursor::SetPosition(const Vector2f& pos)
{
    if (!CheckNotNull(m_cursor.get(), "Invalid Pointer 'm_cursor'"))
        return;

	static_cast<SFSprite*>(m_cursor.get())->SetPosition(pos);
}

void SFMenuCursor::SetScale(const Vector2f& cellSize)
{
    if (!CheckNotNull(m_cursor.get(), "Invalid Pointer 'm_cursor'"))
        return;

    auto spr = static_cast<SFSprite*>(m_cursor.get());
    if (!CheckNotNull(spr, "Invalid Pointer 'spr'"))
        return;

    spr->SetScale({ 1.f, 1.f });

    auto texSize = spr->GetTextureSize();

    // compare against local (texture) size, not global GetSize()
    Vector2f tex = Vector2f(static_cast<int>(texSize.x), static_cast<int>(texSize.y));
    Vector2f scaleXY = { cellSize.x / tex.x, cellSize.y / tex.y };

    float scale = std::min(scaleXY.x, scaleXY.y);
    spr->SetScale({ scale, scale });
}
