#pragma once

#include "SFTile.h"
#include <Engine/Core/Constants.h>
#include <Engine/Interface/Collisions/IGrid.h>

class SFGrid : public IGrid
{
public:
	SFGrid(int rows, int columns, const std::string& fontName = "Arial", const std::string& tileFilePaths = GameConstants::TileFilePaths);
	virtual ~SFGrid() = default;

	void Init(const std::string& fontName, const std::string& tileFilePath) override;
};