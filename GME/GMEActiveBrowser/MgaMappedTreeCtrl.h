// MgaMappedTreeCtrl.h: interface for the CMgaMappedTreeCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MGAMAPPEDTREECTRL_H__01ABA150_667F_4191_95BC_DA45058B98C9__INCLUDED_)
#define AFX_MGAMAPPEDTREECTRL_H__01ABA150_667F_4191_95BC_DA45058B98C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TreeCtrlEx.h"
#include "MgaMap.h"	// Added by ClassView
#include "GMEActiveBrowserDropTarget.h"	// Added by ClassView

#define MGATREECTRL_LOGEVENT(eventstring) \
{ \
	if(m_EventLogger != NULL) \
	{ \
		CComBSTR eventBSTR = eventstring; \
		m_EventLogger->LogEvent(eventBSTR); \
	} \
} \

class CMgaMappedTreeCtrl : public CTreeCtrlEx  
{
public:
	virtual BOOL DoDrop(eDragOperation, COleDataObject*,CPoint);
	void RegisterDropTarget();
	virtual BOOL IsRelevantDropTarget(CPoint point,CImageList*);
	void ExpandAllChildren(HTREEITEM hParent,UINT nCode);
	void DeleteAllChildren(HTREEITEM hParent);
	BOOL DeleteItem(HTREEITEM hItem);
	BOOL SetItemState(HTREEITEM hItem, UINT nState);
	BOOL GetSelectedItemProxy(CMgaObjectProxy& rMgaObjectProxy);
	void CleanUp();
	CMgaMappedTreeCtrl();
	virtual ~CMgaMappedTreeCtrl();

	CMgaMap m_MgaMap;

protected:
	CGMEActiveBrowserDropTarget m_DropTarget;

	CComPtr<IMgaEventLogger> m_EventLogger;
};

#endif // !defined(AFX_MGAMAPPEDTREECTRL_H__01ABA150_667F_4191_95BC_DA45058B98C9__INCLUDED_)
