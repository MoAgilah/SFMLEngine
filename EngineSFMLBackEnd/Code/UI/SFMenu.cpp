#include "SFMenu.h"

#include "SFMenuCursor.h"
#include "SFMenuItem.h"
#include "../Drawables/SFShape.h"
#include "../Drawables/SFSprite.h"
#include "../Drawables/SFText.h"
#include <Utilities/Guards.h>

SFMenu::SFMenu(const Vector2f& menuSize, float outlineThickness, const Vector2f& dimensions, const MenuPositionData& menuPositionData)
	: IMenu(outlineThickness, dimensions, menuPositionData)
{
	m_menuSpace = std::make_shared<SFRect>(menuSize, Vector2f());
	if (!CheckNotNull(m_menuSpace.get(), "Invalid Pointer 'm_menuSpace'"))
		throw std::invalid_argument("SFMenu requires a valid SFRect for m_menuSpace");

	// UI in screen space: ignore world scale
	auto rect = static_cast<SFRect*>(m_menuSpace.get());
	if (!CheckNotNull(rect, "Invalid Pointer 'rect'"))
		throw std::invalid_argument("SFMenu requires a valid SFRect");

	rect->SetScale({ 1.f, 1.f });

	BuildMenuSpace();
}

void SFMenu::AddCursor(ISprite* spr, const MenuNav& menuNav)
{
	if (!CheckNotNull(spr, "Invalid Pointer 'spr'"))
		return;

	auto cursor = std::make_shared<SFMenuCursor>(
		dynamic_cast<SFSprite*>(spr), menuNav);
	if (!CheckNotNull(cursor.get(), "Invalid Pointer 'cursor'"))
		return;

	m_cursors.push_back(std::move(cursor));
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
		// Compute border area from anchor bounds (like screen size)
		Vector2f border = (*(m_menuPositionData.m_anchorBounds) - rect->GetSize()) / 2.f;
		border.x += rect->GetOrigin().x;  // Shift to align left
		rect->SetPosition(border);
		break;
	}
	}

	rect->SetOutlineThickness(m_outlineThickness);
	rect->SetOutlineColour(Colour::Red);

	BuildColumns();
	BuildRows();
}

void SFMenu::BuildColumns()
{
	auto rect = static_cast<SFRect*>(m_menuSpace.get());
	if (!CheckNotNull(rect, "Invalid Pointer 'rect' from m_menuSpace"))
		return;

	float columnWidth = rect->GetSize().x / m_dimensions.x;
	m_columnsSize = Vector2f(columnWidth, rect->GetSize().y);

	m_menuSpaceTopLeft = rect->GetPosition() - rect->GetOrigin();

	for (size_t i = 0; i < m_dimensions.x; i++)
	{
		auto column = std::make_shared<SFRect>(m_columnsSize, Vector2f());
		if (!CheckNotNull(column.get(), std::format("Invalid Pointer 'rect' for column {}", i)))
			throw std::invalid_argument(std::format("SFMenu requires a valid SFRect for column {}",i));

		rect = static_cast<SFRect*>(column.get());
		if (!CheckNotNull(rect, "Invalid Pointer 'rect' from column"))
			return;

		rect->SetScale({ 1.f, 1.f });
		rect->SetOrigin(m_columnsSize / 2.f);
		rect->SetOutlineColour(Colour::Yellow);
		rect->SetOutlineThickness(m_outlineThickness);

		m_columns.push_back(std::move(column));
	}

	rect = static_cast<SFRect*>(m_columns[0].get());
	if (!CheckNotNull(rect, std::format("Invalid Pointer 'rect' from m_columns[{}]", 0)))
		return;

	rect->SetPosition(m_menuSpaceTopLeft + rect->GetOrigin());

	for (size_t i = 1; i < m_dimensions.x; i++)
	{
		rect = static_cast<SFRect*>(m_columns[i].get());
		if (!CheckNotNull(rect, std::format("Invalid Pointer 'rect' from m_columns[{}]", i)))
			return;

		auto prevRect = static_cast<SFRect*>(m_columns[i - 1].get());
		if (!CheckNotNull(rect, std::format("Invalid Pointer 'rect' from m_columns[{}]", i - 1)))
			return;

		rect->SetPosition(prevRect->GetPosition() + Vector2f(prevRect->GetSize().x, 0));
	}
}

void SFMenu::BuildRows()
{
	auto rect = static_cast<SFRect*>(m_menuSpace.get());
	if (!CheckNotNull(rect, "Invalid Pointer 'rect' from m_menuSpace"))
		return;

	float rowHeight = rect->GetSize().y / m_dimensions.y;
	m_cellsSize = Vector2f(m_columnsSize.x, rowHeight);

	for (size_t i = 0; i < m_dimensions.y; i++)
	{
		std::vector<std::shared_ptr<IMenuItem>> row;
		for (size_t j = 0; j < m_dimensions.x; j++)
		{
			auto cell = std::make_shared<SFMenuItem>(m_cellsSize, m_outlineThickness);
			if (!CheckNotNull(cell.get(), std::format("Invalid Pointer 'cell' for col {}, row {}", i, j)))
				throw std::invalid_argument(std::format("SFMenu requires a valid SFRect for col {}, row {}", i, j));

			row.emplace_back(std::move(cell));  // constructs in-place
		}

		m_rows.push_back(std::move(row));
	}

	auto& row = m_rows[0];

	if (row.empty())
		return;

	auto menuItem = row[0];
	if (!CheckNotNull(menuItem.get(), std::format("Invalid Pointer 'menuItem' from m_rows[{}, {}]", 0, 0)))
		return;

	row[0]->SetPosition(m_menuSpaceTopLeft + row[0]->GetOrigin());

	for (size_t i = 1; i < row.size(); i++)
	{
		menuItem = row[i];
		if (!CheckNotNull(menuItem.get(), std::format("Invalid Pointer 'menuItem' from m_rows[{}, {}]", 0, i)))
			throw std::invalid_argument(std::format("SFMenu requires a valid SFMenuItem for m_rows[{}, {}]", 0, i));

		auto prevMenuItem = row[i - 1];
		if (!CheckNotNull(prevMenuItem.get(), std::format("Invalid Pointer 'prevMenuItem' from m_rows[{}, {}]", 0, i - 1)))
			throw std::invalid_argument(std::format("SFMenu requires a valid SFMenuItem for m_rows[{}, {}]", 0, i - 1));

		menuItem->SetPosition(prevMenuItem->GetPosition() + Vector2f(prevMenuItem->GetSize().x, 0));
	}

	// remaining rows
	for (size_t i = 1; i < m_rows.size(); i++)
	{
		for (size_t j = 0; j < m_rows[i].size(); j++)
		{
			menuItem = m_rows[i][j];
			if (!CheckNotNull(menuItem.get(), std::format("Invalid Pointer 'menuItem' from m_rows[{}, {}]", i, j)))
				throw std::invalid_argument(std::format("SFMenu requires a valid SFMenuItem for m_rows[{}, {}]", i, j));

			auto prevMenuItem = m_rows[i - 1][j];
			if (!CheckNotNull(prevMenuItem.get(), std::format("Invalid Pointer 'prevMenuItem' from m_rows[{}, {}]", i - 1, j)))
				throw std::invalid_argument(std::format("SFMenu requires a valid SFMenuItem for m_rows[{}, {}]", i - 1, j));

			menuItem->SetPosition(prevMenuItem->GetPosition() + Vector2f(0, prevMenuItem->GetSize().y));
		}
	}
}

void SFMenu::SetActiveTextElement()
{
	for (const auto& cellID : m_activeCells)
	{
		auto cell = GetCell(cellID);
		if (!CheckNotNull(m_menuSpace.get(), std::format("Invalid Pointer 'cell' with cellID:({},{})", cellID.first, cellID.second)))
			return;

		auto text = cell->GetTextElement();
		if (!CheckNotNull(text, "Invalid Pointer 'text'"))
			return;

		if (cell->GetMenuSlotNumber() == m_menuNavigation.GetCurrCursorPos())
		{
			if (text->IsAnimated())
			{
				auto sfText = dynamic_cast<SFAnimatedText*>(text);
				if (!CheckNotNull(sfText, "Invalid Pointer 'sfText'"))
					return;

				sfText->SetIsPaused(false);
			}

			if (m_passiveColour)
				text->SetOutlineColour(text->GetDefaultColour());
		}
		else
		{
			if (text->IsAnimated())
			{
				auto sfText = dynamic_cast<SFAnimatedText*>(text);
				if (!CheckNotNull(sfText, "Invalid Pointer 'sfText'"))
					return;

				sfText->SetIsPaused(true);
			}

			if (m_passiveColour)
				text->SetOutlineColour(*m_passiveColour);
		}
	}
}