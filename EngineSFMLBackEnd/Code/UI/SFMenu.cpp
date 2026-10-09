#include "SFMenu.h"

#include "SFMenuCursor.h"
#include "../Drawables/SFShape.h"
#include "../Drawables/SFSprite.h"
#include "../Drawables/SFText.h"
#include <Utilities/Guards.h>

SFMenu::SFMenu(const Vector2f& menuSize, float outlineThickness, const Vector2u& dimensions, const MenuPositionData& menuPositionData)
	: IMenu(outlineThickness, dimensions, menuPositionData)
{
	m_menuSpace = std::make_shared<SFRect>(menuSize, Vector2f());

	BuildMenuSpace();

	BuildCells([](const Vector2f& cellSize, float outlineThickness)
		{
			auto rect = std::make_shared<SFRect>(
				cellSize,
				Vector2f{}
			);

			rect->SetScale({ 1.f, 1.f });
			rect->SetOrigin(cellSize / 2.f);
			rect->SetOutlineThickness(outlineThickness);
			rect->SetOutlineColour(Colour::Green);

			return std::make_shared<MenuItem>(std::move(rect));
		});
}

void SFMenu::AddCursor(std::shared_ptr<ISprite> spr,const MenuNav& menuNav)
{
	if (!CheckNotNull(spr.get(), "Invalid Pointer 'spr'"))
		return;

	auto sfSprite = std::dynamic_pointer_cast<SFSprite>(spr);

	if (!CheckNotNull(sfSprite.get(), "Invalid Pointer 'sfSprite'"))
		return;

	auto cursor = std::make_shared<SFMenuCursor>(
		std::move(sfSprite),
		menuNav
	);

	m_cursors.emplace_back(std::move(cursor));
}