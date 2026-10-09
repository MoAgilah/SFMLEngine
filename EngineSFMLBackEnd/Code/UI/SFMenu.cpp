#include "SFMenu.h"

#include "SFMenuCursor.h"
#include "SFMenuItem.h"
#include "../Drawables/SFShape.h"
#include "../Drawables/SFSprite.h"
#include "../Drawables/SFText.h"
#include <Utilities/Guards.h>

SFMenu::SFMenu(const Vector2f& menuSize, float outlineThickness, const Vector2u& dimensions, const MenuPositionData& menuPositionData)
	: IMenu(outlineThickness, dimensions, menuPositionData)
{
	m_menuSpace = std::make_shared<SFRect>(menuSize, Vector2f());

	// UI in screen space: ignore world scale
	auto rect = static_cast<SFRect*>(m_menuSpace.get());

	rect->SetScale({ 1.f, 1.f });

	BuildMenuSpace();
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

void SFMenu::BuildMenuSpace()
{
	auto rect = static_cast<SFRect*>(m_menuSpace.get());
	if (!CheckNotNull(rect, "Invalid Pointer 'rect'"))
		return;

	rect->SetOrigin(rect->GetSize() / 2.f);

	switch (m_menuPositionData.m_positionMode)
	{
	case MenuPositionMode::Centered:
	{
		// Center menu at m_centerPoint
		rect->SetPosition(*(m_menuPositionData.m_centerPoint));
		break;
	}
	case MenuPositionMode::Anchored:
	{
		rect->SetPosition(
			(*m_menuPositionData.m_anchorBounds - rect->GetSize()) / 2.f
			+ rect->GetOrigin()
		);
		break;
	}
	}

	rect->SetOutlineThickness(m_outlineThickness);
	rect->SetOutlineColour(Colour::Red);

	BuildCells();
}

void SFMenu::BuildCells()
{
	if (!CheckNotNull(m_menuSpace.get(), "Invalid Pointer 'm_menuSpace'"))
		return;

	CalculateCellSize(m_menuSpace->GetSize());

	auto rect = static_cast<SFRect*>(m_menuSpace.get());
	if (!CheckNotNull(rect, "Invalid Pointer 'rect' from m_menuSpace"))
		return;

	CalculateMenuTopLeft(
		rect->GetPosition(),
		rect->GetOrigin()
	);

	m_cells.clear();
	m_cells.reserve(
		static_cast<size_t>(m_dimensions.x) * m_dimensions.y
	);

	for (size_t row = 0; row < m_dimensions.y; ++row)
	{
		for (size_t col = 0; col < m_dimensions.x; ++col)
		{
			auto cell = std::make_shared<SFMenuItem>(
				m_cellsSize,
				m_outlineThickness
			);

			cell->SetPosition(CalculateCellPosition(row, col));

			m_cells.emplace_back(std::move(cell));
		}
	}
}