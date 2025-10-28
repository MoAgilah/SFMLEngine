#include "SFMenu.h"

#include "SFMenuCursor.h"
#include "SFMenuItem.h"
#include "../Drawables/SFShape.h"
#include "../Drawables/SFSprite.h"
#include "../Drawables/SFText.h"
#include <Utilities/Utils.h>

SFMenu::SFMenu(const Vector2f& menuSize, float outlineThickness, const Vector2f& dimensions, const MenuPositionData& menuPositionData)
	: IMenu(outlineThickness, dimensions, menuPositionData)
{
	m_menuSpace = std::make_shared<SFRect>(menuSize, Vector2f());

	ENSURE_VALID(m_menuSpace);

	// UI in screen space: ignore world scale
	if (auto rect = static_cast<SFRect*>(m_menuSpace.get()))
		rect->SetScale({ 1.f, 1.f });

	BuildMenuSpace();
}

void SFMenu::AddCursor(ISprite* spr, const MenuNav& menuNav)
{
	ENSURE_VALID(spr);

	auto cursor = std::make_shared<SFMenuCursor>(
		dynamic_cast<SFSprite*>(spr), menuNav);
	m_cursors.push_back(std::move(cursor));
}

void SFMenu::BuildMenuSpace()
{
	auto rect = dynamic_cast<SFRect*>(m_menuSpace.get());

	if (rect)
	{
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
	}

	BuildColumns();
	BuildRows();
}

void SFMenu::BuildColumns()
{
	auto rect = static_cast<SFRect*>(m_menuSpace.get());

	if (rect)
	{
		float columnWidth = rect->GetSize().x / m_dimensions.x;
		m_columnsSize = Vector2f(columnWidth, rect->GetSize().y);

		m_menuSpaceTopLeft = rect->GetPosition() - rect->GetOrigin();
	}

	for (size_t i = 0; i < m_dimensions.x; i++)
	{
		auto column = std::make_shared<SFRect>(m_columnsSize, Vector2f());
		if (auto r = static_cast<SFRect*>(column.get()))
			r->SetScale({ 1.f, 1.f });
		m_columns.push_back(std::move(column));
	}

	for (auto& column : m_columns)
	{
		auto rect = static_cast<SFRect*>(column.get());

		if (rect)
		{
			rect->SetOrigin(m_columnsSize / 2.f);
			rect->SetOutlineColour(Colour::Yellow);
			rect->SetOutlineThickness(m_outlineThickness);
		}
	}

	rect = static_cast<SFRect*>(m_columns[0].get());

	if (rect)
		rect->SetPosition(m_menuSpaceTopLeft + rect->GetOrigin());

	for (size_t i = 1; i < m_dimensions.x; i++)
	{
		auto rect = static_cast<SFRect*>(m_columns[i].get());

		if (rect)
		{
			auto prevRect = static_cast<SFRect*>(m_columns[i - 1].get());
			rect->SetPosition(prevRect->GetPosition() + Vector2f(prevRect->GetSize().x, 0));
		}
	}
}

void SFMenu::BuildRows()
{
	auto rect = static_cast<SFRect*>(m_menuSpace.get());

	if (rect)
	{
		float rowHeight = rect->GetSize().y / m_dimensions.y;
		m_cellsSize = Vector2f(m_columnsSize.x, rowHeight);
	}

	for (size_t i = 0; i < m_dimensions.y; i++)
	{
		std::vector<std::shared_ptr<IMenuItem>> row;
		for (size_t j = 0; j < m_dimensions.x; j++)
		{
			auto cell = std::make_shared<SFMenuItem>(m_cellsSize, m_outlineThickness);
			row.emplace_back(std::move(cell));  // constructs in-place
		}

		m_rows.push_back(std::move(row));
	}

	auto& row = m_rows[0];

	if (row.empty())
		return;

	row[0]->SetPosition(m_menuSpaceTopLeft + row[0]->GetOrigin());

	for (size_t i = 1; i < row.size(); i++)
		row[i]->SetPosition(row[i - 1]->GetPosition() + Vector2f(row[i - 1]->GetSize().x, 0));

	// remaining rows
	for (size_t i = 1; i < m_rows.size(); i++)
	{
		for (size_t j = 0; j < m_rows[i].size(); j++)
			m_rows[i][j]->SetPosition(m_rows[i - 1][j]->GetPosition() + Vector2f(0, m_rows[i - 1][j]->GetSize().y));
	}
}

void SFMenu::SetActiveTextElement()
{
	for (const auto& cellID : m_activeCells)
	{
		auto cell = GetCell(cellID);
		if (cell)
		{
			auto text = cell->GetTextElement();
			if (text)
			{
				if (cell->GetMenuSlotNumber() == m_menuNavigation.GetCurrCursorPos())
				{
					if (text->IsAnimated())
						dynamic_cast<SFAnimatedText*>(text)->SetIsPaused(false);

					if (m_passiveColour)
						text->SetOutlineColour(text->GetDefaultColour());
				}
				else
				{
					if (text->IsAnimated())
						dynamic_cast<SFAnimatedText*>(text)->SetIsPaused(true);

					if (m_passiveColour)
						text->SetOutlineColour(*m_passiveColour);
				}
			}
		}
	}
}