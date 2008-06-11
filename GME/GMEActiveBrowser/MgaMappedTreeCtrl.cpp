// MgaMappedTreeCtrl.cpp: implementation of the CMgaMappedTreeCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gmeactivebrowser.h"
#include "MgaMappedTreeCtrl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMgaMappedTreeCtrl::CMgaMappedTreeCtrl():m_DropTarget(this)
{

	try
	{
		COMTHROW( m_EventLogger.CoCreateInstance(L"Mga.MgaEventLogger"));
	}
	catch(...)
	{
		m_EventLogger = NULL;
	}
	
}

CMgaMappedTreeCtrl::~CMgaMappedTreeCtrl()
{

}

void CMgaMappedTreeCtrl::CleanUp()
{
	CTreeCtrlEx::DeleteAllItems();
	m_MgaMap.DestroyMap();


}

BOOL CMgaMappedTreeCtrl::GetSelectedItemProxy(CMgaObjectProxy &rMgaObjectProxy)
{
	HTREEITEM hTreeItem=CTreeCtrlEx::GetSelectedItem();

	if(hTreeItem== NULL) return FALSE; // No selected item

	return m_MgaMap.LookupObjectProxy(hTreeItem,rMgaObjectProxy);
}



BOOL CMgaMappedTreeCtrl::SetItemState(HTREEITEM hItem, UINT nState)
{

	if(nState&TVIS_BOLD)CTreeCtrl::SetItemState(hItem,TVIS_BOLD,TVIS_BOLD);	
	if(nState&TVIS_SELECTED)CTreeCtrlEx::SelectItemEx(hItem);
	if(nState&TVIS_EXPANDED)Expand(hItem,TVE_EXPAND );

	return TRUE;
}

BOOL CMgaMappedTreeCtrl::DeleteItem(HTREEITEM hItem)
{

	m_MgaMap.RemoveTreeItem(hItem);
	return CTreeCtrl::DeleteItem(hItem);
}

// Recursively deletes every child
void CMgaMappedTreeCtrl::DeleteAllChildren(HTREEITEM hParent)
{
	if (ItemHasChildren(hParent)) // this may indicate true and the GetChildItem may give at the same time back 0x00000000 since that children may not have htreeitem inserted for it
	{
	   HTREEITEM hItem = GetChildItem(hParent);

	   while (hItem != NULL)
	   {
			DeleteAllChildren(hItem);

		   	HTREEITEM hNextItem = GetNextSiblingItem(hItem);		
			// Consistently removes item from map and the tree ctrl
			CMgaMappedTreeCtrl::DeleteItem(hItem);
			hItem=hNextItem;

	   }
	}

}

void CMgaMappedTreeCtrl::ExpandAllChildren(HTREEITEM hParent,UINT nCode)
{

	if (ItemHasChildren(hParent))
	{
	   HTREEITEM hItem = GetChildItem(hParent);

	   while (hItem != NULL)
	   {		   
		   Expand(hItem,nCode);
		   hItem = GetNextSiblingItem(hItem);						
	   }
	}

}


BOOL CMgaMappedTreeCtrl::IsRelevantDropTarget(CPoint point, CImageList*)
{
	return FALSE;
}

void CMgaMappedTreeCtrl::RegisterDropTarget()
{

	m_DropTarget.Register(this);
}

BOOL CMgaMappedTreeCtrl::DoDrop(eDragOperation, COleDataObject*, CPoint)
{
	return FALSE;
}
