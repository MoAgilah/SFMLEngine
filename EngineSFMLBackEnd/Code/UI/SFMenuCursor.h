#pragma once

#include "../Drawables/SFSprite.h"
#include <Engine/Interface/UI/IMenuCursor.h>
#include <Engine/UI/MenuNavigation.h>
#include <Utilities/Vector.h>


class SFMenuCursor : public IMenuCursor
{
public:
	SFMenuCursor(SFSprite* sprite, const MenuNav& menuNav);
	~SFMenuCursor() = default;

	void SetPosition(const Vector2f& pos);
	void SetScale(const Vector2f& cellSize);
};