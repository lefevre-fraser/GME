// MgaObjectProxyMapItem.cpp: implementation of the CMgaObjectProxyMapItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gmeactivebrowser.h"
#include "MgaObjectProxyMapItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMgaObjectProxyMapItem::CMgaObjectProxyMapItem(LPUNKNOWN pMgaObject, objtype_enum type, HTREEITEM hTreeItem)
:CMgaObjectProxy(pMgaObject,type),m_hTreeItem(hTreeItem)
{

}

CMgaObjectProxyMapItem::CMgaObjectProxyMapItem(CMgaObjectProxy& rSourceMgaObjectProxy, HTREEITEM hTreeItem)
:CMgaObjectProxy(rSourceMgaObjectProxy),m_hTreeItem(hTreeItem)
{
	

}

CMgaObjectProxyMapItem::~CMgaObjectProxyMapItem()
{

}
