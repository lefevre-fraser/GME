// AggregateTreeCtrl.cpp: implementation of the CAggregateTreeCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gmeactivebrowser.h"
#include "AggregateTreeCtrl.h"
#include "ActiveBrowserPropertyPage.h"
#include "..\gme\GMEOLEData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAggregateTreeCtrl::CAggregateTreeCtrl()
{

	m_bIsStateStored=FALSE;

}

CAggregateTreeCtrl::~CAggregateTreeCtrl()
{

}

HTREEITEM CAggregateTreeCtrl::InsertItem(HTREEITEM hParent, CString strObjectName, LPUNKNOWN pUnknown, objtype_enum otObjectType)
{
	MGATREECTRL_LOGEVENT("CAggregateTreeCtrl::InsertItem "+strObjectName+"\r\n");

	if(m_MgaMap.bIsInMap(pUnknown)) // Should not happen
	{
		TRACE(" Duplicate element found inserting a new element into the aggregation tree map.\n");
#ifdef _DEBUG
		m_MgaMap.Dump(afxDump);
#endif
		ASSERT(FALSE);
		

		return NULL;
	}


	TVINSERTSTRUCT tvInsert;
	tvInsert.hParent = hParent;
	tvInsert.hInsertAfter = NULL;
	tvInsert.item.pszText = strObjectName.GetBuffer(0);

	tvInsert.item.state=0;
	tvInsert.item.stateMask=0;
	tvInsert.item.lParam=NULL;

	CAggregatePropertyPage* pParent=(CAggregatePropertyPage*)GetParent();

	int sourceControlImageOffset = 0;
	int sourceControlLatentState = 0;

	if(pParent->m_Options.m_bIsDynamicLoading)
	{
		tvInsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE|TVIF_CHILDREN;
		if(otObjectType==OBJTYPE_FOLDER || otObjectType==OBJTYPE_MODEL)
		{
			CComQIPtr<IMgaObject> ccpMgaObject(pUnknown);
			tvInsert.item.cChildren=pParent->reqHasDisplayedChild(ccpMgaObject);
			//sourceControlImageOffset = pParent->GetSourceControlStateOffset(ccpMgaObject, &sourceControlLatentState);
		}
		else
		{
			tvInsert.item.cChildren=0;
		}
		sourceControlImageOffset = pParent->GetSourceControlStateOffset(CComQIPtr<IMgaObject>( pUnknown), &sourceControlLatentState);
	}
	else
	{
		tvInsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	}

	if(hParent==NULL)	// Root folder
	{

		tvInsert.item.iImage=0+sourceControlImageOffset;
		tvInsert.item.iSelectedImage=0+sourceControlImageOffset;
	}
	else
	{
		tvInsert.item.iImage=(int)otObjectType+sourceControlImageOffset;
		tvInsert.item.iSelectedImage=(int)otObjectType+sourceControlImageOffset;
	}

	if(otObjectType==OBJTYPE_FOLDER)
	{
		bool has_dep;
		if(IsLibrary(pUnknown, &has_dep))
		{
			tvInsert.item.iImage=10;
			tvInsert.item.iSelectedImage=10;
			if( has_dep)
			{
				tvInsert.item.iImage=54;
				tvInsert.item.iSelectedImage=54;
			}
		}
	}

	// Inserting item into the tree control
	HTREEITEM hItem=CTreeCtrl::InsertItem(&tvInsert);
	strObjectName.ReleaseBuffer();

	SetItemData(hItem,(DWORD)hItem);
	
	CMgaObjectProxy ObjectProxy(pUnknown,otObjectType);
	m_MgaMap.AddEntry(hItem,ObjectProxy);

	SetItemProperties(hItem, sourceControlLatentState);
	
	return hItem;

}


HTREEITEM CAggregateTreeCtrl::InsertItemUpdate(HTREEITEM hParent, CString strObjectName, LPUNKNOWN pUnknown, objtype_enum otObjectType)
{
	MGATREECTRL_LOGEVENT("CAggregateTreeCtrl::InsertItemUpdate "+strObjectName+"\r\n");

	HTREEITEM hTreeItem;
	if(m_MgaMap.LookupTreeItem(pUnknown,hTreeItem))
	{
		return hTreeItem;
	}


	TVINSERTSTRUCT tvInsert;
	tvInsert.hParent = hParent;
	tvInsert.hInsertAfter = NULL;
	tvInsert.item.pszText = strObjectName.GetBuffer(0);

	tvInsert.item.state=0;
	tvInsert.item.stateMask=0;
	tvInsert.item.lParam=NULL;

	CAggregatePropertyPage* pParent=(CAggregatePropertyPage*)GetParent();

	int sourceControlImageOffset = 0;
	int sourceControlLatentState = 0;

	if(pParent->m_Options.m_bIsDynamicLoading)
	{
		tvInsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE|TVIF_CHILDREN;
		if(otObjectType==OBJTYPE_FOLDER || otObjectType==OBJTYPE_MODEL)
		{
			CComQIPtr<IMgaObject> ccpMgaObject(pUnknown);
			tvInsert.item.cChildren=pParent->reqHasDisplayedChild(ccpMgaObject);
			//sourceControlImageOffset = pParent->GetSourceControlStateOffset(ccpMgaObject, &sourceControlLatentState);
		}
		else
		{
			tvInsert.item.cChildren=0;
		}
		sourceControlImageOffset = pParent->GetSourceControlStateOffset(CComQIPtr<IMgaObject>( pUnknown), &sourceControlLatentState);
	}
	else
	{
		tvInsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	}

	if(hParent==NULL)	// Root folder
	{

		tvInsert.item.iImage=0+sourceControlImageOffset;
		tvInsert.item.iSelectedImage=0+sourceControlImageOffset;
	}
	else
	{
		tvInsert.item.iImage=(int)otObjectType+sourceControlImageOffset;
		tvInsert.item.iSelectedImage=(int)otObjectType+sourceControlImageOffset;
	}

	if(otObjectType==OBJTYPE_FOLDER)
	{
		bool has_dep;
		if(IsLibrary(pUnknown, &has_dep))
		{
			tvInsert.item.iImage=10 + sourceControlImageOffset;
			tvInsert.item.iSelectedImage=10 + sourceControlImageOffset;
			if( has_dep)
			{
				tvInsert.item.iImage=54;
				tvInsert.item.iSelectedImage=54;
			}
		}
			

	}

	// Inserting item into the tree control
	HTREEITEM hItem=CTreeCtrl::InsertItem(&tvInsert);
	strObjectName.ReleaseBuffer();

	SetItemData(hItem,(DWORD)hItem);
	
	CMgaObjectProxy ObjectProxy(pUnknown,otObjectType);
	m_MgaMap.AddEntry(hItem,ObjectProxy);

	SetItemProperties(hItem, sourceControlLatentState);
	
	return hItem;

}


void CAggregateTreeCtrl::MaintainRegistry()
{
	BYTE nMaxStored=4;

	HKEY hKey;                  // handle to key to enumerate
	DWORD dwIndex=0;            // subkey index
	char szName[255];           // subkey name
	DWORD lName=254;				// size of subkey buffer
	char szClass[255];          // class string buffer
	DWORD lClass;				// size of class string buffer
	FILETIME ftLastWriteTime;	// last write time
	
	FILETIME ftOldestWriteTime;	// oldest write time
	CString strOldestName;		// Name of the oldest key


	// Initializing filetime with the current system time    
    SYSTEMTIME stSystemTime;    
    GetSystemTime(&stSystemTime);              // gets current time
	 // converts to file time format
    SystemTimeToFileTime(&stSystemTime, &ftOldestWriteTime); 

   	// Getting the key of Tree Data
	hKey=AfxGetApp()->GetSectionKey("TreeData");

	for(dwIndex=0;
		ERROR_NO_MORE_ITEMS!=
		RegEnumKeyEx(hKey,dwIndex,szName,&lName,NULL,szClass,&lClass,&ftLastWriteTime);
		dwIndex++,lName=254
		)
	{
			// If the current is earlier
			if(::CompareFileTime(&ftLastWriteTime,&ftOldestWriteTime)==-1)
			{
				ftOldestWriteTime=ftLastWriteTime;
				strOldestName=szName;
			}
	}

	if(dwIndex>nMaxStored)
	{
		// Deleting the oldest key			
		::RegDeleteKey(HKEY_CURRENT_USER,CString("Software\\")+
													AfxGetApp()->m_pszRegistryKey+
													AfxGetApp()->m_pszProfileName+
													"\\TreeData\\"+strOldestName);
	}
	
	::RegCloseKey(hKey);
}


void CAggregateTreeCtrl::LoadItemStateFromRegistry(CString& strProjectName, HTREEITEM hItem)
{		

		// Searching hte map for the Mga pointer
		LPUNKNOWN pUnknown;
		if(m_MgaMap.LookupObjectUnknown(hItem,pUnknown))
		{
			CComQIPtr<IMgaObject>ccpMgaObject(pUnknown);
			if(ccpMgaObject) // succesful conversion
			{
				CComBSTR IDObj;
				ccpMgaObject->get_ID(&IDObj);

				// Get Object id and item state in the registry
				CString strID(IDObj);				
				UINT nItemState=AfxGetApp()->GetProfileInt(CString("TreeData\\")+strProjectName,strID,0xffffffff);

		
				if(nItemState!=0xffffffff)
				{
					CMgaMappedTreeCtrl::SetItemState(hItem,nItemState);
				}

			}
		}
}


void CAggregateTreeCtrl::LoadTreeStateFromRegistry(CString& strProjectName)
{

	// If the key does not exist return
	HKEY hKey;
	if(ERROR_SUCCESS!=::RegOpenKeyEx(HKEY_CURRENT_USER,
		CString("Software\\")+
		AfxGetApp()->m_pszRegistryKey+
		"\\" +
		AfxGetApp()->m_pszProfileName+
		"\\TreeData\\"+
		strProjectName,
		0,KEY_ALL_ACCESS,&hKey))
	{
		return;
	}
	else
	{
		::RegCloseKey(hKey);
	}
	
	
	
	// Traverse all items in tree control
	HTREEITEM hItem= GetRootItem();

	while ( hItem )
	{
		/* Getting the items to the registry		*/
		LoadItemStateFromRegistry(strProjectName,hItem);
		
		// Get first child node
		HTREEITEM hNextItem = GetChildItem( hItem );

		if ( !hNextItem )
		{
			// Get next sibling child
			hNextItem = GetNextSiblingItem( hItem );

			if ( !hNextItem )
			{
				HTREEITEM hParentItem=hItem;
				while ( !hNextItem && hParentItem )
				{
					// No more children: Get next sibling to parent
					hParentItem = GetParentItem( hParentItem );
					hNextItem = GetNextSiblingItem( hParentItem );
				}
			}
		}

		hItem = hNextItem;
	}

	// Deleting the key			
	::RegDeleteKey(HKEY_CURRENT_USER,CString("Software\\")+AfxGetApp()->m_pszRegistryKey+AfxGetApp()->m_pszProfileName+
													"\\TreeData\\"+strProjectName);

	return;

}



void CAggregateTreeCtrl::SaveTreeStateToRegistry(CString& strProjectName)
{
	// Traverse all items in tree control
	HTREEITEM hItem= GetRootItem();

	while ( hItem )
	{
		/* Saving the items to the registry		*/
		// Getting item state
		UINT nItemState=CTreeCtrlEx::GetItemState(hItem,0xffffffff);

		// Searching the map for the Mga pointer
		LPUNKNOWN pUnknown;
		if(m_MgaMap.LookupObjectUnknown(hItem,pUnknown))
		{
			CComQIPtr<IMgaObject>ccpMgaObject(pUnknown);
			if(ccpMgaObject) // succesful conversion
			{
				CComBSTR IDObj;
				ccpMgaObject->get_ID(&IDObj);

				// Put Object id and item state in the registry
				CString strID(IDObj);
				
				AfxGetApp()->WriteProfileInt(CString("TreeData\\")+strProjectName,strID,nItemState);
			}
		}

		// Get first child node
		HTREEITEM hNextItem = GetChildItem( hItem );

		if ( !hNextItem )
		{
			// Get next sibling child
			hNextItem = GetNextSiblingItem( hItem );

			if ( !hNextItem )
			{
				HTREEITEM hParentItem=hItem;
				while ( !hNextItem && hParentItem )
				{
					// No more children: Get next sibling to parent
					hParentItem = GetParentItem( hParentItem );
					hNextItem = GetNextSiblingItem( hParentItem );
				}
			}
		}

		hItem = hNextItem;
	}

	// If there is too many project trees stored in the registry 
	// we delete the oldest one
	MaintainRegistry();
	return;

}


void CAggregateTreeCtrl::StoreState()
{

	m_StateBuffer.RemoveAll();

	// Traverse all items in tree control
	HTREEITEM hItem= GetRootItem();

	while ( hItem )
	{
		/* Saving the items to the state buffer		*/
		// Getting item state
		UINT nItemState=CTreeCtrlEx::GetItemState(hItem,0x000000ff);
		CString strItemState;
		strItemState.Format("%ul",nItemState);

		// Searching the map for the Mga pointer
		LPUNKNOWN pUnknown;
		if(m_MgaMap.LookupObjectUnknown(hItem,pUnknown))
		{
			CComQIPtr<IMgaObject>ccpMgaObject(pUnknown);
			if(ccpMgaObject) // succesful conversion
			{
				CComBSTR IDObj;
				ccpMgaObject->get_ID(&IDObj);

				// Put Object id and item state in the buffer
				CString strID(IDObj);
				m_StateBuffer.SetAt(strID,strItemState);
				
			}
		}

		// Get first child node
		HTREEITEM hNextItem = GetChildItem( hItem );

		if ( !hNextItem )
		{
			// Get next sibling child
			hNextItem = GetNextSiblingItem( hItem );

			if ( !hNextItem )
			{
				HTREEITEM hParentItem=hItem;
				while ( !hNextItem && hParentItem )
				{
					// No more children: Get next sibling to parent
					hParentItem = GetParentItem( hParentItem );
					hNextItem = GetNextSiblingItem( hParentItem );
				}
			}
		}

		hItem = hNextItem;
	}

	m_bIsStateStored=TRUE;
	return;

}



void CAggregateTreeCtrl::RestoreState()
{
	if(!m_bIsStateStored)return;

	// Traverse all items in tree control
	HTREEITEM hItem= GetRootItem();

	while ( hItem )
	{
		/* Getting the item from the map		*/
		
		// Searching the map for the Mga pointer
		LPUNKNOWN pUnknown;
		if(m_MgaMap.LookupObjectUnknown(hItem,pUnknown))
		{
			CComQIPtr<IMgaObject>ccpMgaObject(pUnknown);
			if(ccpMgaObject) // succesful conversion
			{
				CComBSTR IDObj;
				ccpMgaObject->get_ID(&IDObj);

				// Get Object id and item state from the map
				CString strID(IDObj);
				CString strItemState;
				if(m_StateBuffer.Lookup(strID,strItemState))
				{
					char* pszEndPtr=NULL;
					UINT nItemState=strtoul(strItemState,&pszEndPtr,10);														
					CMgaMappedTreeCtrl::SetItemState(hItem,nItemState);
				}
			}
		}
		
		// Get first child node
		HTREEITEM hNextItem = GetChildItem( hItem );

		if ( !hNextItem )
		{
			// Get next sibling child
			hNextItem = GetNextSiblingItem( hItem );

			if ( !hNextItem )
			{
				HTREEITEM hParentItem=hItem;
				while ( !hNextItem && hParentItem )
				{
					// No more children: Get next sibling to parent
					hParentItem = GetParentItem( hParentItem );
					hNextItem = GetNextSiblingItem( hParentItem );
				}
			}
		}

		hItem = hNextItem;
	}

	m_StateBuffer.RemoveAll();
	m_bIsStateStored=FALSE;
	return;
}





int CAggregateTreeCtrl::ItemCompareProc(LPARAM lParamItem1, LPARAM lParamItem2, LPARAM lParamSort)
{


	CAggregateTreeCtrl* pTreeCtrl = (CAggregateTreeCtrl*) lParamSort;

	HTREEITEM hItem1=(HTREEITEM) lParamItem1;
	HTREEITEM hItem2=(HTREEITEM) lParamItem2;

	
	CAggregatePropertyPage* pParent=(CAggregatePropertyPage*)pTreeCtrl->GetParent();

	switch(pParent->m_Options.m_soSortOptions)
	{		
		case SORT_BYNAME:
			{
				CString strItem1 = pTreeCtrl->GetItemText(hItem1);
				CString strItem2 = pTreeCtrl->GetItemText(hItem2);
				return -strcmp(strItem2, strItem1);
			}break;
		case SORT_BYTYPE:
			{
				CMgaObjectProxy MgaObjectProxyItem1;
				CMgaObjectProxy MgaObjectProxyItem2;
				if(
					pTreeCtrl->m_MgaMap.LookupObjectProxy(hItem1,MgaObjectProxyItem1) &&
					pTreeCtrl->m_MgaMap.LookupObjectProxy(hItem2,MgaObjectProxyItem2))
				{
					// Same Type - Sort By Name
					if(MgaObjectProxyItem1.m_TypeInfo==MgaObjectProxyItem2.m_TypeInfo)
					{
						CString strItem1 = pTreeCtrl->GetItemText(hItem1);
						CString strItem2 = pTreeCtrl->GetItemText(hItem2);
						return -strcmp(strItem2, strItem1);

					}

					// Folder has a high priority
					if(MgaObjectProxyItem1.m_TypeInfo==OBJTYPE_FOLDER)
					{
						return -1;
					}

					if(MgaObjectProxyItem2.m_TypeInfo==OBJTYPE_FOLDER)
					{
						return 1;
					}

					return MgaObjectProxyItem1.m_TypeInfo-MgaObjectProxyItem2.m_TypeInfo;
				}
				else
				{
					// For dummy elements that are not in the map it does not matter
					return 0;
				}

			}break;
		case SORT_BYCREATION:
			{
				
				CMgaObjectProxy MgaObjectProxyItem1;
				CMgaObjectProxy MgaObjectProxyItem2;

				if(
					pTreeCtrl->m_MgaMap.LookupObjectProxy(hItem1,MgaObjectProxyItem1) &&
					pTreeCtrl->m_MgaMap.LookupObjectProxy(hItem2,MgaObjectProxyItem2))
				{
					CComQIPtr<IMgaObject>ccpItem1(MgaObjectProxyItem1.m_pMgaObject);
					CComQIPtr<IMgaObject>ccpItem2(MgaObjectProxyItem2.m_pMgaObject);

					if(ccpItem1 &&ccpItem2)
					{						
						// Query the RelativeID
						long lRelID1,lRelID2;
						COMTHROW(ccpItem1->get_RelID(&lRelID1));
						COMTHROW(ccpItem2->get_RelID(&lRelID2));																	
						
						return lRelID1-lRelID2;
					}
					else // Unsuccessful query of the objects
					{
						return 0;
					}

				}
				else
				{
					// For dummy elements that are not in the map it does not matter
					return 0;
				}

			}break;
	}
	return 0;
}

void CAggregateTreeCtrl::SortItems(HTREEITEM hItem)
{
	// Sort the tree control's items using 
	// custom callback procedure.

		// Traverse all items in tree control

	if(hItem==NULL)
	{
		hItem= GetRootItem();
	}

	while ( hItem )
	{
			TVSORTCB tvs;
			tvs.hParent = hItem;
			tvs.lpfnCompare = (PFNTVCOMPARE)ItemCompareProc;
			tvs.lParam = (LPARAM) this;

			CTreeCtrl::SortChildrenCB(&tvs);
		

		// Get first child node
		HTREEITEM hNextItem = GetChildItem( hItem );

		if ( !hNextItem )
		{
			// Get next sibling child
			hNextItem = GetNextSiblingItem( hItem );

			if ( !hNextItem )
			{
				HTREEITEM hParentItem=hItem;
				while ( !hNextItem && hParentItem )
				{
					// No more children: Get next sibling to parent
					hParentItem = GetParentItem( hParentItem );
					hNextItem = GetNextSiblingItem( hParentItem );
				}
			}
		}

		hItem = hNextItem;
	}

}


void CAggregateTreeCtrl::MakeSureGUIDIsUniqueForSmartCopy( CComPtr<IMgaFCO>& fco)
{
	// this method prevents cloned objects having the same guid
	// as their original ones
	CComBSTR bstr;
	COMTHROW( fco->get_RegistryValue( CComBSTR( "guid"), &bstr));
	if( bstr == 0 || bstr == "") return; // no guid present, no need to replace it

	GUID t_guid = GUID_NULL;
	::CoCreateGuid(&t_guid);
		
	if (t_guid != GUID_NULL)
	{
		CString str_guid;
		str_guid.Format("{%08lX-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X}",
			t_guid.Data1, t_guid.Data2, t_guid.Data3,
			t_guid.Data4[0], t_guid.Data4[1], t_guid.Data4[2], t_guid.Data4[3],
			t_guid.Data4[4], t_guid.Data4[5], t_guid.Data4[6], t_guid.Data4[7]);
		
		// thus replace the old guid with a new one
		COMTHROW( fco->put_RegistryValue( CComBSTR( "guid"), CComBSTR(str_guid)));
	}

	// store the previous guid in prev subnode
	COMTHROW( fco->put_RegistryValue( CComBSTR( "guid/prev"), bstr));
}



BOOL CAggregateTreeCtrl::IsRelevantDropTarget(CPoint point,CImageList* pDragImageList)
{
	UINT uFlags;	
	HTREEITEM hItem=HitTest(point, &uFlags);
	
	// Setting previously selected item to avoid blinking
	// To avoid the the messed up window we have to turn off the drag image list

	HTREEITEM hSelItem=GetSelectedItem();
	if(GetSelectedCount()>1)hSelItem=NULL;

	if ((hItem != NULL) && (TVHT_ONITEM & uFlags))
	{
		// Selecting
		if(hItem!=hSelItem)
		{
			if(pDragImageList!=NULL)
			{
				pDragImageList->DragShowNolock(FALSE);
				ClearSelection();
				SelectItem(hItem);
				pDragImageList->DragShowNolock(TRUE);
			}
			else
			{
				ClearSelection();
				SelectItem(hItem);
			}
			
		}
		CMgaObjectProxy ObjectProxy;
		if(m_MgaMap.LookupObjectProxy(hItem,ObjectProxy)) // If it is in the map
		{
			if(ObjectProxy.m_TypeInfo==OBJTYPE_FOLDER || ObjectProxy.m_TypeInfo==OBJTYPE_MODEL)
			{
				return TRUE;
			}
		}		
	}
	else
	{
		if(GetSelectedCount()>1)
		{
			if(pDragImageList!=NULL)
			{
					pDragImageList->DragShowNolock(FALSE);
					ClearSelection();				
					pDragImageList->DragShowNolock(TRUE);
			}
			else
			{
				ClearSelection();		
			}
		}
	}
	return FALSE;
}

BOOL CAggregateTreeCtrl::DoDrop(eDragOperation doDragOp, COleDataObject *pDataObject, CPoint point)
{
	MGATREECTRL_LOGEVENT("CAggregateTreeCtrl::DoDrop\r\n");
	CString _t = "";
	if( doDragOp == DRAGOP_REFERENCE)
		_t = " REFERENCE\r\n";
	if( doDragOp == DRAGOP_SUBTYPE)
		_t = " DERIVE\r\n";
	if( doDragOp == DRAGOP_INSTANCE)
		_t = " INSTANCE\r\n";
	if( doDragOp == DRAGOP_COPY)
		_t = " COPY\r\n";
	if( doDragOp == DRAGOP_MOVE)
		_t = " MOVE\r\n";
	if( doDragOp == DRAGOP_CLOSURE)
		_t = " CLOSURE COPY\r\n";
	if( doDragOp == DRAGOP_CLOSURE_MERGE)
		_t = " COPY MERGE\r\n";
	MGATREECTRL_LOGEVENT( _t);

	HTREEITEM hItem= GetSelectedItem();
	CMgaObjectProxy MgaObjectProxy;

	if(hItem==NULL || !m_MgaMap.LookupObjectProxy(hItem,MgaObjectProxy))
	{
		ASSERT(FALSE);
		return FALSE;
	}

	
	CGMEActiveBrowserApp* pApp=(CGMEActiveBrowserApp*)AfxGetApp();
	CMgaContext* pMgaContext=&pApp->m_CurrentProject.m_MgaContext;
	
	// Setting up the drop target 
	CComQIPtr<IMgaObject> ccpTargetObject(MgaObjectProxy.m_pMgaObject);
	if(!ccpTargetObject) 
	{
		MessageBox("Invalid target type.","Error",MB_OK|MB_ICONERROR);
		return FALSE;
	}

	// PETER: Checking clipboard, paste XML clipboard.
	if (!CGMEDataSource::IsGmeNativeDataAvailable(pDataObject,pMgaContext->m_ccpProject)) 
	{
		if (!CGMEDataSource::IsXMLDataAvailable(pDataObject))  {
			MessageBox("Unknown clipboard format.","Error",MB_OK|MB_ICONERROR);
			return FALSE;
		}
		if (doDragOp != DRAGOP_COPY && doDragOp != DRAGOP_CLOSURE && doDragOp != DRAGOP_CLOSURE_MERGE) {
			MessageBox("Only copy operation is supported on GME XML clipboard format.","Error",MB_OK|MB_ICONERROR);
			return FALSE;
		}
			
		bool res = CGMEDataSource::ParseXMLData(pDataObject, ccpTargetObject, doDragOp == DRAGOP_CLOSURE_MERGE);
		
		return res?TRUE:FALSE;
	}
	// PETER: end
	

	CComPtr<IDataObject> ccpDataObject = pDataObject->GetIDataObject(FALSE);
	CComPtr<IMgaDataSource> ccpMgaDataSource;
	COMTHROW(ccpDataObject.QueryInterface(&ccpMgaDataSource));

	CComPtr<IUnknown> ccpData;
	COMTHROW(ccpMgaDataSource->get_Data( &ccpData));
	
	CComPtr<IUnknown> ccpFolders;
	COMTHROW(ccpMgaDataSource->get_Folders( &ccpFolders));
	
	CComPtr<IMgaResolver> ccpMgaResolver;
	COMTHROW( ccpMgaResolver.CoCreateInstance(L"Mga.MgaResolver") );

	CComQIPtr<IMgaFCOs> ccpDroppedFCOs( ccpData);
	CComQIPtr<IMgaFolders> ccpDroppedFolders( ccpFolders);

	if (!ccpDroppedFCOs && !ccpDroppedFolders) {
		BOOL bRetVal = FALSE;

		MSGTRY {
			CComQIPtr<IMgaMetaRole> metaRole(ccpData);
			if (metaRole) {
				CComPtr<IMgaFCO> child;
				pMgaContext->BeginTransaction(FALSE); // Read/Write Transaction
				if (MgaObjectProxy.m_TypeInfo == OBJTYPE_MODEL) {	// If the drop target is a model
					CComQIPtr<IMgaModel> ccpTargetModel(MgaObjectProxy.m_pMgaObject);
					switch (doDragOp) {
						case DRAGOP_MOVE:
						case DRAGOP_COPY:
						{
							COMTHROW(ccpTargetModel->CreateChildObject(metaRole, &child));
						} break;				
					}	// switch
				} else if (MgaObjectProxy.m_TypeInfo == OBJTYPE_FOLDER) { // If the drop target is a folder
					CComQIPtr<IMgaFolder> ccpTargetFolder(MgaObjectProxy.m_pMgaObject);
					switch (doDragOp) {
						case DRAGOP_MOVE:
						case DRAGOP_COPY:
						{
							CComPtr<IMgaMetaFCO> metaFCO;
							COMTHROW(metaRole->get_Kind(&metaFCO));
							if (metaFCO)
								COMTHROW(ccpTargetFolder->CreateRootObject(metaFCO, &child));
						} break;				
					}	// switch
				}
				if (child) {
					CComBSTR nm;
					COMTHROW(metaRole->get_DisplayedName(&nm));
					COMTHROW(child->put_Name(nm));
				}
				pMgaContext->CommitTransaction ();
			}
		} MSGCATCH ("Error completing PartBrowser drop operation", pMgaContext->AbortTransaction ();)	

		return bRetVal;
	}

	// ccpDroppedFCOs can't be null since every copier creates the Mga.MgaFCOs collection even if no element is added
	// ccpDroppedFolders might be null i.e. GMEDoc does not create the Mga.MgaFolders collection
	// when an fco is dragged from the GMEView to the ActiveBrowser

	BOOL bRetVal=FALSE;

	MSGTRY{
		pMgaContext->BeginTransaction(false); // Read/Write Transaction
		if(MgaObjectProxy.m_TypeInfo==OBJTYPE_FOLDER) // If the drop target is a folder
		{
			CComQIPtr<IMgaFolder> ccpTargetFolder(MgaObjectProxy.m_pMgaObject);

			switch(doDragOp)
			{
				case DRAGOP_MOVE:
				{
					CComPtr<IMgaFolders> ccpNewFolders;
					CComPtr<IMgaFCOs> ccpNewFCOs;

					// first move the selected folders. The order matters 
					// since the NEWCHILD event must be the last one.
					if( ccpDroppedFolders) COMTHROW( ccpTargetFolder->MoveFolders( ccpDroppedFolders, &ccpNewFolders));

					// then move the selected fcos
					COMTHROW( ccpTargetFolder->MoveFCOs( ccpDroppedFCOs, &ccpNewFCOs));

					// this ensures that the new parent is notified in the right time and place
					// a NEWCHILD event is sent to the target folder
					COMTHROW( ccpTargetFolder->RefreshParent( ccpTargetFolder));

					bRetVal=TRUE;
				}break;
				case DRAGOP_COPY:
				{
					CComPtr<IMgaFolders> ccpNewFolders;
					if( ccpDroppedFolders) COMTHROW(ccpTargetFolder->CopyFolders(ccpDroppedFolders,&ccpNewFolders));

					CComPtr<IMgaFCOs> ccpNewFCOs;
					COMTHROW(ccpTargetFolder->CopyFCOs(ccpDroppedFCOs,&ccpNewFCOs));
					
					MGACOLL_ITERATE(IMgaFCO, ccpNewFCOs) { // for smart copy related entries
						MakeSureGUIDIsUniqueForSmartCopy( CComPtr<IMgaFCO>( MGACOLL_ITER) );
					} MGACOLL_ITERATE_END;

					bRetVal=TRUE;
				}break;
				case DRAGOP_REFERENCE:
				{
					///////////////////// NOT IMPLEMENTED !!!! ///////////////
					bRetVal=FALSE;
				}break;
				case DRAGOP_INSTANCE:
				{
					MGACOLL_ITERATE(IMgaFCO,ccpDroppedFCOs) 
					{					
						CComPtr<IMgaFCO> ccpNewFco;
						HRESULT hr;
						if( ( hr = ccpTargetFolder->DeriveRootObject(MGACOLL_ITER,VARIANT_TRUE,&ccpNewFco)) != S_OK) {
							if( hr == E_MGA_NOT_DERIVABLE) // typical failure code when subtyping/instantiating
							{
								CComBSTR msg( L"Object '"), nm;
								COMTHROW( MGACOLL_ITER->get_Name( &nm));
								msg.Append( nm);
								msg.Append( "' could not be derived. Some of its ancestors or descendants may be already derived! [Error code E_MGA_NOT_DERIVABLE]");
								Utils::put2Console( Utils::get_GME( pMgaContext->m_ccpProject), msg, MSG_ERROR);
									pMgaContext->AbortTransaction();//COMTHROW( hr);
								return FALSE;//break; // although it was inside a MGACOLL_ITERATE, we aborted the trans
							}
							COMTHROW( hr); // otherwise
							break;
						}
					}
					MGACOLL_ITERATE_END;
					bRetVal=TRUE;			
				}break;
				case DRAGOP_SUBTYPE:
				{
					MGACOLL_ITERATE(IMgaFCO,ccpDroppedFCOs) 
					{					
						CComPtr<IMgaFCO> ccpNewFco;
						HRESULT hr;
						if( ( hr = ccpTargetFolder->DeriveRootObject(MGACOLL_ITER,VARIANT_FALSE,&ccpNewFco)) != S_OK) {
							//MGATREECTRL_LOGEVENT("    "+fcoName+" cannot be derived.\r\n");
							if( hr == E_MGA_NOT_DERIVABLE) // typical failure code when subtyping/instantiating
							{
								CComBSTR msg( L"Object '"), nm;
								COMTHROW( MGACOLL_ITER->get_Name( &nm));
								msg.Append( nm);
								msg.Append( "' could not be derived. Some of its ancestors or descendants may be already derived! [Error code E_MGA_NOT_DERIVABLE]");
								Utils::put2Console( Utils::get_GME( pMgaContext->m_ccpProject), msg, MSG_ERROR);
									pMgaContext->AbortTransaction();//COMTHROW( hr);
								return FALSE;//break; // although it was inside a MGACOLL_ITERATE, we aborted the trans
							}
							COMTHROW( hr); // otherwise
							break;
						}
					}
					MGACOLL_ITERATE_END;

					bRetVal=TRUE;
				}break;

				
			}
		}
		else if(MgaObjectProxy.m_TypeInfo==OBJTYPE_MODEL) // If the drop target is a model
		{
			long fol_cnt = 0;
			if( ccpDroppedFolders)
			{
				COMTHROW( ccpDroppedFolders->get_Count( &fol_cnt));
				if ( fol_cnt > 0)
					AfxMessageBox("Cannot insert folders into a model");
			}

			CComQIPtr<IMgaModel> ccpTargetModel(MgaObjectProxy.m_pMgaObject);
			switch(doDragOp)
			{
				case DRAGOP_MOVE:
				{
#if(0)		// plain old version
					CComPtr<IMgaFCOs> ccpNewFCOs;

					CComPtr<IMgaMetaRoles> ccpMetaRoles;
					COMTHROW(ccpMetaRoles.CoCreateInstance(OLESTR("Mga.MgaMetaRoles")));

					MGACOLL_ITERATE(IMgaFCO, ccpDroppedFCOs) 
					{
						CComPtr<IMgaFCO> ccpFCO;
						COMTHROW(pMgaContext->m_ccpTerritory->OpenFCO(MGACOLL_ITER, &ccpFCO));
						CComPtr<IMgaMetaRole> ccpMetaRole;
						COMTHROW(ccpFCO->get_MetaRole(&ccpMetaRole));
						CComPtr<IMgaMetaFCO> ccpKind;
						COMTHROW(ccpFCO->get_Meta(&ccpKind));
						CComPtr<IMgaMetaRole> ccpNewRole;

						COMTHROW(ccpMgaResolver->get_RoleByMeta(ccpTargetModel,ccpKind,OBJTYPE_NULL,ccpMetaRole,NULL,&ccpNewRole));
						COMTHROW(ccpMetaRoles->Append(ccpNewRole));
					}
					MGACOLL_ITERATE_END;
					COMTHROW( ccpTargetModel->MoveFCOs(ccpDroppedFCOs,ccpMetaRoles,&ccpNewFCOs) );

					bRetVal = TRUE;
#else		// check if the target = source
					CComPtr<IMgaFCOs> ccpNewFCOs;

					CComPtr<IMgaMetaRoles> ccpMetaRoles;
					COMTHROW(ccpMetaRoles.CoCreateInstance(OLESTR("Mga.MgaMetaRoles")));

					long fco_cnt = 0;
					COMTHROW( ccpDroppedFCOs->get_Count( &fco_cnt));
					if ( fco_cnt > 0)
					{
						bool valid = true;
						if ( fco_cnt == 1)
						{
							valid = false;
							CComPtr<IMgaFCO> one_fco;
							MGACOLL_ITERATE(IMgaFCO, ccpDroppedFCOs) {
								one_fco = MGACOLL_ITER;
							} MGACOLL_ITERATE_END;
							VARIANT_BOOL is_equal;
							COMTHROW( one_fco->get_IsEqual( ccpTargetModel, &is_equal));

							if (is_equal == VARIANT_FALSE) // not equal
								valid = true;
						}

						if ( valid)
						{
							MGACOLL_ITERATE(IMgaFCO, ccpDroppedFCOs) 
							{
								CComPtr<IMgaFCO> ccpFCO;
								COMTHROW(pMgaContext->m_ccpTerritory->OpenFCO(MGACOLL_ITER, &ccpFCO));
								CComPtr<IMgaMetaRole> ccpMetaRole;
								COMTHROW(ccpFCO->get_MetaRole(&ccpMetaRole));
								CComPtr<IMgaMetaFCO> ccpKind;
								COMTHROW(ccpFCO->get_Meta(&ccpKind));
								CComPtr<IMgaMetaRole> ccpNewRole;

								COMTHROW(ccpMgaResolver->get_RoleByMeta(ccpTargetModel,ccpKind,OBJTYPE_NULL,ccpMetaRole,NULL,&ccpNewRole));
								COMTHROW(ccpMetaRoles->Append(ccpNewRole));
							}
							MGACOLL_ITERATE_END;

							COMTHROW( ccpTargetModel->MoveFCOs(ccpDroppedFCOs,ccpMetaRoles,&ccpNewFCOs) );
							bRetVal = TRUE;
						}
						else bRetVal = FALSE;
					}
					else bRetVal=FALSE; //?
#endif

				}break;
				case DRAGOP_COPY:
				{
					CComPtr<IMgaFCOs> ccpNewFCOs;

					CComPtr<IMgaMetaRoles> ccpMetaRoles;
					COMTHROW(ccpMetaRoles.CoCreateInstance(OLESTR("Mga.MgaMetaRoles")));

					MGACOLL_ITERATE(IMgaFCO, ccpDroppedFCOs) 
					{
						CComPtr<IMgaFCO> ccpFCO;
						COMTHROW(pMgaContext->m_ccpTerritory->OpenFCO(MGACOLL_ITER, &ccpFCO));
						CComPtr<IMgaMetaRole> ccpMetaRole;
						COMTHROW(ccpFCO->get_MetaRole(&ccpMetaRole));
						CComPtr<IMgaMetaFCO> ccpKind;
						COMTHROW(ccpFCO->get_Meta(&ccpKind));
						CComPtr<IMgaMetaRole> ccpNewRole;

						COMTHROW(ccpMgaResolver->get_RoleByMeta(ccpTargetModel,ccpKind,OBJTYPE_NULL,ccpMetaRole,NULL,&ccpNewRole));
						COMTHROW(ccpMetaRoles->Append(ccpNewRole));
					}
					MGACOLL_ITERATE_END;
					COMTHROW( ccpTargetModel->CopyFCOs(ccpDroppedFCOs,ccpMetaRoles,&ccpNewFCOs) );

					MGACOLL_ITERATE(IMgaFCO, ccpNewFCOs) { // for smart copy related entries
						MakeSureGUIDIsUniqueForSmartCopy( CComPtr<IMgaFCO>( MGACOLL_ITER) );
					} MGACOLL_ITERATE_END;
					
					bRetVal=TRUE;

				}break;
				case DRAGOP_REFERENCE:
				{						

							CComBSTR bszSourceName;

							MGACOLL_ITERATE(IMgaFCO,ccpDroppedFCOs)
							{
								//-acquiring a pointer in the active territory for MGACOLL_ITER
								CComPtr<IMgaFCO> ccpFCO;
								COMTHROW(pMgaContext->m_ccpTerritory->OpenFCO(MGACOLL_ITER, &ccpFCO));

								CComPtr<IMgaConnection> conn;
								if(ccpFCO.QueryInterface(&conn) != S_OK) { // skip connections, they cannot be referenced
									CComPtr<IMgaMetaRole> ccpNewMetaRole;
									COMTHROW( ccpMgaResolver->get_RefRoleByMeta(ccpTargetModel, NULL, ccpFCO, &ccpNewMetaRole) );

									if(ccpNewMetaRole == 0)
									{
										MGATREECTRL_LOGEVENT("    Cannot create reference.\r\n");
									}
									else {
										CComPtr<IMgaFCO> ccpNewFCO;
										COMTHROW( ccpTargetModel->CreateReference(ccpNewMetaRole,ccpFCO,&ccpNewFCO) );
										ASSERT(ccpNewFCO != NULL);

										// Creating name for the new reference:
										bszSourceName.Empty();
										COMTHROW( ccpFCO->get_Name(&bszSourceName) );
										/*
										// ReferencedName+"Ref"
										CString strSourceName(bszSourceName);
										strSourceName += "Ref";
										bszSourceName = strSourceName;*/ // commented by zolmol according to DoPasteNative() logic in GMEView.cpp 

										//Rename
										COMTHROW( ccpNewFCO->put_Name(bszSourceName));
									}
								}
							}MGACOLL_ITERATE_END;
							
							bRetVal=TRUE;
				}break;
				case DRAGOP_INSTANCE:
				case DRAGOP_SUBTYPE:
				{
					HRESULT hr = S_OK;
					bool excep_handled = false;
					MGACOLL_ITERATE(IMgaFCO,ccpDroppedFCOs) {
						
						//-acquiring a pointer in the active territory for MGACOLL_ITER
						CComPtr<IMgaFCO> ccpFCO;
						COMTHROW(pMgaContext->m_ccpTerritory->OpenFCO(MGACOLL_ITER, &ccpFCO));

						CComBSTR bstr;
						COMTHROW(ccpFCO->get_Name(&bstr));
						CString fcoName;
						CopyTo(bstr,fcoName);

						CComPtr<IMgaMetaFCO> ccpMetaFCO;
						COMTHROW( ccpFCO->get_Meta(&ccpMetaFCO) );
						ASSERT( ccpMetaFCO != NULL);

						// Old role can be NULL
						CComPtr<IMgaMetaRole> ccpOldMetaRole;
						COMTHROW( ccpFCO->get_MetaRole(&ccpOldMetaRole) );
						
						CComPtr<IMgaMetaRole> ccpNewMetaRole;
						COMTHROW( ccpMgaResolver->get_RoleByMeta(ccpTargetModel, ccpMetaFCO, OBJTYPE_NULL, ccpOldMetaRole, NULL, &ccpNewMetaRole) );
						if(ccpNewMetaRole == 0)
						{
							MGATREECTRL_LOGEVENT("    Cannot insert object derived from "+fcoName+"\r\n");
						}
						else {
							CComPtr<IMgaFCO> ccpNewFCO;
							VARIANT_BOOL inst = doDragOp == DRAGOP_INSTANCE? VARIANT_TRUE : VARIANT_FALSE;
							if((hr = ccpTargetModel->DeriveChildObject(ccpFCO,ccpNewMetaRole, inst ,&ccpNewFCO)) != S_OK) {
								MGATREECTRL_LOGEVENT("    "+fcoName+" cannot be derived.\r\n");
								if( hr == E_MGA_NOT_DERIVABLE) // typical failure code when subtyping/instantiating
								{
									CComBSTR msg( L"Object '"), nm;
									COMTHROW( ccpFCO->get_Name( &nm));
									msg.Append( nm);
									msg.Append( "' could not be derived. Some of its ancestors or descendants may be already derived! [Error code E_MGA_NOT_DERIVABLE]");
									Utils::put2Console( Utils::get_GME( pMgaContext->m_ccpProject), msg, MSG_ERROR);

									pMgaContext->AbortTransaction();//COMTHROW( hr);
									return FALSE;//break; // although it was inside a MGACOLL_ITERATE, we aborted the trans
								}
								COMTHROW( hr); // otherwise
								break;
							}
						}

					}
					MGACOLL_ITERATE_END;
					bRetVal=TRUE;
				}break;
				
			}
		}
		pMgaContext->CommitTransaction();

	}MSGCATCH("Error completing drop operation",pMgaContext->AbortTransaction();)	



	return bRetVal;
}

BOOL CAggregateTreeCtrl::DoDropWithoutChecking(eDragOperation doDragOp, COleDataObject *pDataObject, CPoint point)
{
	MGATREECTRL_LOGEVENT("CAggregateTreeCtrl::DoDropWithoutChecking\r\n");

	CGMEActiveBrowserApp* pApp = (CGMEActiveBrowserApp*)AfxGetApp();
	CMgaContext* pMgaContext = &pApp->m_CurrentProject.m_MgaContext;

	CComPtr<IMgaComponentEx> constrMgr;
	if (pMgaContext)
		constrMgr = pMgaContext->FindConstraintManager();
	if (constrMgr)
		COMTHROW(constrMgr->Enable(false));
	BOOL res = DoDrop( doDragOp, pDataObject, point);
	if (constrMgr) {
		COMTHROW(constrMgr->Enable(true));
//		constrMgr.Release();
	}

	return res;
}

void CAggregateTreeCtrl::SetItemProperties(HTREEITEM hItem, int p_fileLatentState)
{


	CMgaObjectProxy ObjectProxy;

	if(!m_MgaMap.LookupObjectProxy(hItem, ObjectProxy))return;

	CComQIPtr<IMgaObject> ccpObject(ObjectProxy.m_pMgaObject);

	if(!ccpObject)return; // Not an MgaObject
	

	BYTE cState=0;

	CGMEActiveBrowserApp* pApp=(CGMEActiveBrowserApp*)AfxGetApp();
	CMgaContext* pMgaContext=&pApp->m_CurrentProject.m_MgaContext;

	pMgaContext->BeginTransaction();


	// Checking access rights
	VARIANT_BOOL vtbIsWritable=VARIANT_FALSE;
	VARIANT_BOOL vtbIsReadOnly=VARIANT_FALSE;
	COMTHROW( ccpObject->get_IsWritable(&vtbIsWritable));
	COMTHROW( ccpObject->HasReadOnlyAccess( &vtbIsReadOnly));

	if (vtbIsWritable != VARIANT_TRUE || vtbIsReadOnly == VARIANT_TRUE || p_fileLatentState != 0)
	{
		// Read only object
		cState|=0x0001;
	}
	else
	{
		// If the object is writable

		
	}


	VARIANT_BOOL vtbIsLibObject=VARIANT_FALSE;;
	COMTHROW(ccpObject->get_IsLibObject(&vtbIsLibObject));
	
	if(vtbIsLibObject!=VARIANT_TRUE)
	{
		// Not a LibObject
	}
	else
	{
		// LibObject
		cState|=0x0002;

	}

	pMgaContext->CommitTransaction();

	/////////////// If it is an FCO cast it //////////////
	// If not an Folder deal with Subtype/instance flags
	if(ObjectProxy.m_TypeInfo!=OBJTYPE_FOLDER) 
	{
		CComQIPtr<IMgaFCO> ccpMgaFCO(ObjectProxy.m_pMgaObject);
		if(!ccpMgaFCO)return; // Not an FCO

		
		pMgaContext->BeginTransaction();
		// Is it instance?
		VARIANT_BOOL vtbIsInstance=VARIANT_FALSE;
		COMTHROW(ccpMgaFCO->get_IsInstance(&vtbIsInstance));

		if(vtbIsInstance!=VARIANT_TRUE)
		{
			CComPtr<IMgaFCO> ccpBaseType;
			COMTHROW(ccpMgaFCO->get_BaseType(&ccpBaseType));

			if(!ccpBaseType)
			{
				// Not derived
			}
			else
			{
				// Derived
				cState|=0x0008;
			}

		}
		else
		{
			// Instance
			cState|=0x0004;

		}

		pMgaContext->CommitTransaction();
	} // if not folder
	

	if(cState)
	{
		CTreeCtrl::SetItemState( hItem,INDEXTOSTATEIMAGEMASK(cState), TVIS_STATEIMAGEMASK );
	}
	else
	{		
		CTreeCtrl::SetItemState( hItem,0, TVIS_STATEIMAGEMASK );
	}
}



BOOL CAggregateTreeCtrl::IsLibrary(LPUNKNOWN pUnknown, bool *p_ptrHasAnyDependency /*= 0*/)
{

	CComQIPtr<IMgaFolder> ccpFolder(pUnknown);
	
	if(!ccpFolder)return FALSE;

		
	CGMEActiveBrowserApp* pApp=(CGMEActiveBrowserApp*)AfxGetApp();
	CMgaContext* pMgaContext=&pApp->m_CurrentProject.m_MgaContext;

	pMgaContext->BeginTransaction();

	CComBSTR bszLibName;						
	COMTHROW(ccpFolder->get_LibraryName(&bszLibName));

	if( bszLibName && p_ptrHasAnyDependency)  // user interested in the dependency status
	{
		*p_ptrHasAnyDependency = IsUngroupedLibrary( ccpFolder);
	}

	pMgaContext->CommitTransaction();

	if(!bszLibName)
	{	
		return FALSE;
	}

	return TRUE;

}

//static
bool CAggregateTreeCtrl::IsUngroupedLibrary(CComPtr<IMgaFolder> pLibPtr)
{
	ASSERT( pLibPtr);
	if( !pLibPtr) return false;

	bool retv = true;
	CComPtr<IMgaFolders> c1, c2;
	COMTHROW( pLibPtr->GetVirtuallyIncludedBy( &c1));
	COMTHROW( pLibPtr->GetVirtuallyIncludes( &c2));
	long l1( 0), l2( 0);
	if( c1) COMTHROW( c1->get_Count( &l1));
	if( c2) COMTHROW( c2->get_Count( &l2));
	if( l1 == 0 && l2 == 0)
	{
		retv = false;
	}

	return retv;
}