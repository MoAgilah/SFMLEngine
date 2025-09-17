#include "SFMenuCursor.h"

SFMenuCursor::SFMenuCursor(SFSprite* sprite, const MenuNav& menuNav)
	: IMenuCursor(std::move(static_cast<ISprite*>(sprite)), menuNav)
{}

void SFMenuCursor::SetPosition(const Vector2f& pos)
{
	static_cast<SFSprite*>(m_cursor.get())->SetPosition(pos);
}

void SFMenuCursor::SetScale(const Vector2f& cellSize)
{
	auto spr = static_cast<SFSprite*>(m_cursor.get());

	Vector2f scaleXY = cellSize / spr->GetSize();

	float scale = std::min(scaleXY.x, scaleXY.y);

	spr->SetScale({ scale, scale });
}
