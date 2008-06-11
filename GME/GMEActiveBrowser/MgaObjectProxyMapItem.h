// MgaObjectProxyMapItem.h: interface for the CMgaObjectProxyMapItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MGAOBJECTPROXYMAPITEM_H__0A26F08F_7295_4AEC_81F6_C1DFE5FD7944__INCLUDED_)
#define AFX_MGAOBJECTPROXYMAPITEM_H__0A26F08F_7295_4AEC_81F6_C1DFE5FD7944__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MgaObjectProxy.h"

class CMgaObjectProxyMapItem : public CMgaObjectProxy  
{
	friend class CMgaMap;
	HTREEITEM m_hTreeItem;
public:
	CMgaObjectProxyMapItem(LPUNKNOWN pMgaObject, objtype_enum type, HTREEITEM hTreeItem);
	CMgaObjectProxyMapItem(CMgaObjectProxy& rSourceMgaObjectProxy, HTREEITEM hTreeItem);
	virtual ~CMgaObjectProxyMapItem();

};

#endif // !defined(AFX_MGAOBJECTPROXYMAPITEM_H__0A26F08F_7295_4AEC_81F6_C1DFE5FD7944__INCLUDED_)
