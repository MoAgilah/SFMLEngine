#include "SFGrid.h"

#include "../Drawables/SFText.h"
#include "../Resources/SFFont.h"

SFGrid::SFGrid(int rows, int columns, const std::string& fontName, const std::string& tileFilePaths)
	: IGrid(rows, columns)
{
	Init(fontName, tileFilePaths);
}

void SFGrid::Init(const std::string& fontName, const std::string& tileFilePaths)
{

	auto font = dynamic_cast<SFFont*>(GameManager::Get()->GetFontMgr().GetFont(fontName));
	m_grid.reserve(m_rows * m_columns);

	for (int y = 0; y < m_rows; ++y)
	{
		for (int x = 0; x < m_columns; ++x)
			m_grid.emplace_back(std::make_shared<SFTile>(x, y, &font->GetNativeFont()));
	}

	if (!m_grid.empty())
	{
		LoadTileTypes(tileFilePaths);
		ArrangeTilePositions();
	}
}
