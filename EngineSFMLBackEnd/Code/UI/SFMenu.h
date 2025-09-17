#pragma once

#include "../Drawables/SFSprite.h"
#include <Engine/Interface/UI/IMenu.h>
#include <Utilities/Vector.h>

class SFMenu : public IMenu
{
public:
	SFMenu(const Vector2f& menuSize, float outlineThickness, const Vector2f& dimensions, const MenuPositionData& menuPositionData);
	~SFMenu() = default;

	void AddCursor(ISprite* spr, const MenuNav& menuNav);

protected:

	void BuildMenuSpace() override;
	void BuildColumns() override;
	void BuildRows() override;

	void SetActiveTextElement() override;
};