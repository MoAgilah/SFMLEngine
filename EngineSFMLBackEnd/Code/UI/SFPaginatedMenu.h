#pragma once

#include "SFMenu.h"
#include <Engine/Interface/UI/IPaginatedMenu.h>

class SFPaginatedMenu : public IPaginatedMenu
{
public:
	SFPaginatedMenu() = default;
	~SFPaginatedMenu() = default;

	SFMenu* AddMenu(SFMenu* menu);
	SFMenu* GetMenuByNumber(int menuNumer);
	SFMenu* GetCurrentMenu() { return GetMenuByNumber(m_currentMenuNum); }
};