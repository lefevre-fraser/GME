// MgaMap.cpp: implementation of the CMgaMap class.
//
// Maintains double map to enforce the easy mapping between a 
// tree element and the corresponding mga object and vice versa
// providing fast search based on the CMap hash tables and ensures the consistency
// between the two inner maps.
//
// The first map (m_MapItem2Object) maintans the correspondence between a tree item
// handle as a key and an LPUNKNOWN type pointer as a value.
// The second map (m_MapObject2Item) has an LPUNKNOWN pointer as a 
// key and a CMgaObjectProxyMapItem class containing the CMgaObjectProxy
// object and the tree item handle value.
// So the mapping can be summarized as follows:
//	m_MapItem2Object: HTREEITEM -> LPUNKNOWN
//	m_MapObject2Item: LPUNKNOWN -> (CMgaObjectProxy+HTREEITEM)
//
// 
//
// Tihamer Levendovszky 11/26/2001
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gmeactivebrowser.h"
#include "MgaMap.h"
#include <comdef.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMgaMap::CMgaMap()
{

}

CMgaMap::~CMgaMap()
{
	DestroyMap();
}

void CMgaMap::DestroyMap()
{
	// Remove elements from object map and delete the object
	POSITION pos=m_MapObject2Item.GetStartPosition();
	CMgaObjectProxyMapItem* pObject;
	LPUNKNOWN pUnknown;

	// Remove the TreeItem handles and LPUNKNOWNs from the item map
	m_MapItem2Object.RemoveAll();


	while(pos!=NULL)
	{
		m_MapObject2Item.GetNextAssoc(pos,pUnknown,pObject);
		m_MapObject2Item.RemoveKey(pUnknown);
		delete pObject;
		pUnknown->Release();
	}

}

// Retreives the corresponding TreeItem handle from an Object Proxy
BOOL CMgaMap::LookupTreeItem(CMgaObjectProxy MgaObjectProxy, HTREEITEM &hTreeItem)
{
	CMgaObjectProxyMapItem* pMgaObjectProxyMapItem;

	BOOL bResult=m_MapObject2Item.Lookup(MgaObjectProxy.m_pMgaObject,pMgaObjectProxyMapItem);

	if(bResult) hTreeItem=pMgaObjectProxyMapItem->m_hTreeItem;

	return bResult;
}


// Retreives the Object Proxy from the corresponding TreeItem handle
BOOL CMgaMap::LookupObjectProxy(HTREEITEM hTreeItem,CMgaObjectProxy& rObjectProxy)
{
	CMgaObjectProxyMapItem* pMgaObjectProxyMapItem;
	LPUNKNOWN pUnknown;
	
	BOOL bResult=m_MapItem2Object.Lookup(hTreeItem,pUnknown);
	
	if(bResult)
	{
		if( (bResult=m_MapObject2Item.Lookup(pUnknown,pMgaObjectProxyMapItem)) )
		{
			rObjectProxy=*pMgaObjectProxyMapItem;
		}
	}
	return  bResult;
}


// Removes a tree item maintaining the consistency between the two maps
BOOL CMgaMap::RemoveTreeItem(HTREEITEM hTreeItem)
{
	LPUNKNOWN pUnknown;

	if(!m_MapItem2Object.Lookup(hTreeItem,pUnknown))
	{
		return FALSE;
	}
	else
	{
		m_MapItem2Object.RemoveKey(hTreeItem);

		CMgaObjectProxyMapItem* pObjectProxyMapItem;
		if(m_MapObject2Item.Lookup(pUnknown,pObjectProxyMapItem))
		{
			m_MapObject2Item.RemoveKey(pUnknown);			
			// Free COM object
			pUnknown->Release();
			delete pObjectProxyMapItem;
		}
		return TRUE;
	}

}


// Removes an Object Proxy maintaining the consistency between the two maps
BOOL CMgaMap::RemoveObjectProxy(CMgaObjectProxy MgaObjectProxy)
{	
	CMgaObjectProxyMapItem* pObjectProxyMapItem;

	if(!m_MapObject2Item.Lookup(MgaObjectProxy.m_pMgaObject,pObjectProxyMapItem))
	{
		return FALSE;
	}
	else
	{
		m_MapObject2Item.RemoveKey(pObjectProxyMapItem->m_pMgaObject);
		m_MapItem2Object.RemoveKey(pObjectProxyMapItem->m_hTreeItem);
		
		// Free COM object
		pObjectProxyMapItem->m_pMgaObject->Release();
		delete pObjectProxyMapItem;
		return TRUE;
	}
}


// Adds a new TreeItem Handle - ObjectProxy pair to the map
void CMgaMap::AddEntry(HTREEITEM hTreeItem, CMgaObjectProxy MgaObjectProxy)
{

// Removing the elements from the maps with the keys, because CMap::SetAt would overwrite
// the value belonging to the already existing key 
// resulting an inconsistency with the other map. 
	RemoveTreeItem(hTreeItem);
	RemoveObjectProxy(MgaObjectProxy);	
	
	// Increase reference counter for this map
	MgaObjectProxy.m_pMgaObject->AddRef();

	m_MapItem2Object.SetAt(hTreeItem,MgaObjectProxy.m_pMgaObject);

	CMgaObjectProxyMapItem* pMgaObjectProxyMapItem= new CMgaObjectProxyMapItem(MgaObjectProxy,hTreeItem);
	m_MapObject2Item.SetAt(MgaObjectProxy.m_pMgaObject,pMgaObjectProxyMapItem);

}


// Low level function for efficiency: if one wants IUnknown pointer
// he can get it with one lookup call
BOOL CMgaMap::LookupObjectUnknown(HTREEITEM hTreeItem, LPUNKNOWN &pUnknown)
{

	return m_MapItem2Object.Lookup(hTreeItem,pUnknown);
}


_COM_SMARTPTR_TYPEDEF(IMgaObject, __uuidof(IMgaObject));

BOOL CMgaMap::SearchTreeItem(BSTR Id, HTREEITEM &hTreeItem, IUnknown* &punk)
{
	// read all looking for the ID

   LPUNKNOWN	nKey;
   CMgaObjectProxyMapItem *	pt;
   POSITION pos = m_MapObject2Item.GetStartPosition();
   bool found = false;
   while (pos != NULL)
   {
      m_MapObject2Item.GetNextAssoc( pos, nKey, pt);
	  IMgaObjectPtr mgao(nKey);
	  IUnknownPtr punkptr(nKey);

	  punk = punkptr;
	  BSTR oid = NULL;
	  mgao->get_ID(&oid);
	  _bstr_t boid(oid, false);
	  _bstr_t bid = (char*)Id;
	  if (bid == boid)
	  {
		  found = true;
		  break;
	  }
   }

	if(found) 
		hTreeItem = pt->m_hTreeItem;

	return (found);
}


BOOL CMgaMap::LookupTreeItem(LPUNKNOWN pUnknown, HTREEITEM &hTreeItem)
{
	CMgaObjectProxyMapItem* pMgaObjectProxyMapItem;

	BOOL bResult=m_MapObject2Item.Lookup(pUnknown,pMgaObjectProxyMapItem);

	if(bResult) hTreeItem=pMgaObjectProxyMapItem->m_hTreeItem;

	return bResult;
}



BOOL CMgaMap::bIsInMap(LPUNKNOWN pUnknown)
{
	CMgaObjectProxyMapItem* pMgaObjectProxyMapItem;
	return m_MapObject2Item.Lookup(pUnknown,pMgaObjectProxyMapItem);
}

BOOL CMgaMap::bIsInMap(HTREEITEM hTreeItem)
{
	LPUNKNOWN pUnknown;
	return m_MapItem2Object.Lookup(hTreeItem,pUnknown);
}



// Dump function
#ifdef _DEBUG
void CMgaMap::Dump(CDumpContext& dc ) const
{
	dc<<"______________________ MgaMap Dump begin _______________________";
	// Dumping the Item2Object Map
	dc<<"\n\nMapItem2Object:\n";
	
	HTREEITEM hItem;
	LPUNKNOWN pUnknown;

	POSITION pos = m_MapItem2Object.GetStartPosition();
	while(pos!=NULL)
	{
		m_MapItem2Object.GetNextAssoc(pos,hItem,pUnknown);
		CString strOut;
		strOut.Format(" %x  |  %x\n",hItem, pUnknown);
		dc<<strOut;
	}
	dc<<"\n";

	// Dumping Object2Item Map
	dc<<"\n\nMapObject2Item:\n";
	

	CMgaObjectProxyMapItem* pMgaObjectProxyMapItem;


	pos = m_MapObject2Item.GetStartPosition();
	while(pos!=NULL)
	{
		m_MapObject2Item.GetNextAssoc(pos,pUnknown,pMgaObjectProxyMapItem);
		CString strOut;
		strOut.Format(" %x  |  %x  |  %d\n", pUnknown, pMgaObjectProxyMapItem->m_hTreeItem,pMgaObjectProxyMapItem->m_TypeInfo);
		dc<<strOut;
	}
	dc<<"\n";

	dc<<"______________________ MgaMap Dump end _______________________\n\n";
}
#endif