#include "SFPaginatedMenu.h"

SFMenu* SFPaginatedMenu::AddMenu(SFMenu* menu)
{
	return dynamic_cast<SFMenu*>(IPaginatedMenu::AddMenu(menu));
}

SFMenu* SFPaginatedMenu::GetMenuByNumber(int menuNumber)
{
	return dynamic_cast<SFMenu*>(IPaginatedMenu::GetMenuByNumber(menuNumber));
}