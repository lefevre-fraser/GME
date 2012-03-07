#include "stdafx.h"
#include "GMEStd.h"
#include "DynMenu.h"

////////////////////////////// CDynMenu /////////////////////////////

CDynMenu::CDynMenu(int iden, char* nm) : id(iden), name(nm)
{
	menu.CreatePopupMenu();
	minID = maxID = -1;
}

CDynMenu::~CDynMenu()
{
}

void CDynMenu::AddItem(int id, const CString& roleName, const CString& displayName, const CString& helpMsg)
{
	if(minID < 0)
		minID = id;
	maxID = id;
	std::unique_ptr<CDynMenuItem> item(new CDynMenuItem(id, roleName, helpMsg));
	items.push_back(std::move(item));
}

void CDynMenu::Sort()
{
	std::sort(items.begin(), items.end(),
		[](const std::unique_ptr<CDynMenuItem>& a, const std::unique_ptr<CDynMenuItem>& b)
	{ return a->GetLabel() < b->GetLabel(); }
	);
	for (auto it = items.begin(); it != items.end(); it++)
	{
		menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, (**it).id, (**it).label);
	}
}

CDynMenuItem* CDynMenu::FindItem(int id)
{
	for (auto it = items.begin(); it != items.end(); it++) {
		CDynMenuItem* item = it->get();
		if(item->id == id)
			return item;
	}
	return 0;
}
