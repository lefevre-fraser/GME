// AggregateTreeCtrl.h: interface for the CAggregateTreeCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AGGREGATETREECTRL_H__BAA3D537_E504_4801_B793_6F96B703380C__INCLUDED_)
#define AFX_AGGREGATETREECTRL_H__BAA3D537_E504_4801_B793_6F96B703380C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MgaMappedTreeCtrl.h"

class CAggregateTreeCtrl : public CMgaMappedTreeCtrl  
{
	friend class CAggregatePropertyPage;
	friend class CAggregateContextMenu;

	
	CMapStringToString m_StateBuffer;

	BOOL m_bIsStateStored;
public:
	BOOL IsLibrary(LPUNKNOWN pUnknown, bool *p_ptrIsDependent = 0);
	static bool IsUngroupedLibrary(CComPtr<IMgaFolder> ptr);

    
	void SetItemProperties(HTREEITEM hItem, int p_fileLatentState = 0);
	BOOL DoDrop(eDragOperation doDragOp, COleDataObject *pDataObject, CPoint point);
	BOOL DoDropWithoutChecking(eDragOperation doDragOp, COleDataObject *pDataObject, CPoint point);
	void MakeSureGUIDIsUniqueForSmartCopy( CComPtr<IMgaFCO>& fco);
	BOOL IsRelevantDropTarget(CPoint point,CImageList*);
	void RestoreState();
	void StoreState();
	void MaintainRegistry();
	void SortItems(HTREEITEM hItem=NULL);
	static int CALLBACK ItemCompareProc(LPARAM lParamItem1, LPARAM lParamItem2, LPARAM lParamSort);
	void SaveTreeStateToRegistry(CString&);
	void LoadTreeStateFromRegistry(CString&);
	void LoadItemStateFromRegistry(CString& strProjectName, HTREEITEM hItem);
	HTREEITEM InsertItem(HTREEITEM hParent, CString strObjectName, LPUNKNOWN pUnknown, objtype_enum otObjectType);
	HTREEITEM InsertItemUpdate(HTREEITEM hParent, CString strObjectName, LPUNKNOWN pUnknown, objtype_enum otObjectType);

	CAggregateTreeCtrl();
	virtual ~CAggregateTreeCtrl();

};

#endif // !defined(AFX_AGGREGATETREECTRL_H__BAA3D537_E504_4801_B793_6F96B703380C__INCLUDED_)
