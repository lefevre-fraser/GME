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
	POSITION pos = items.GetHeadPosition();
	while(pos)
		delete items.GetNext(pos);
}

void CDynMenu::AddItem(int id, const CString& roleName, const CString& displayName, const CString& helpMsg)
{
	if(minID < 0)
		minID = id;
	maxID = id;
	CDynMenuItem* item = new CDynMenuItem(id, roleName, helpMsg);
	items.AddTail(item);
	menu.AppendMenu(MF_ENABLED | MF_UNCHECKED | MF_STRING, id, displayName);
}

CDynMenuItem* CDynMenu::FindItem(int id)
{
	POSITION pos = items.GetHeadPosition();
	while(pos) {
		CDynMenuItem* item = items.GetNext(pos);
		if(item->id == id)
			return item;
	}
	return 0;
}
