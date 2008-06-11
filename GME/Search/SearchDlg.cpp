// SearchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Search.h"
#include "SearchDlg.h"
#include "SearchCtl.h"
#include "Validate.h"
#include "Input.h"
#include "SearchAlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchDlg dialog


CSearchDlg::CSearchDlg()
: m_scopedCtrlEnabled( FALSE)
{
	//{{AFX_DATA_INIT(CSearchDlg)
	m_edtName = _T("");
	m_edtKindName = _T("");
	m_edtRoleName = _T("");
	m_cmbType = _T("");
	m_edtAttrName = _T("");
	m_edtAttrValue = _T("");
	m_chkAtom = TRUE;
	m_chkFullWord = FALSE;
	m_chkMod = TRUE;
	m_chkRef = TRUE;
	m_chkSet = TRUE;
	m_chkSplSearch = FALSE;
	m_chkLocate = FALSE;
	m_chkMatchCase = TRUE;
	m_chkScopedSearch = FALSE;
	m_stcRef = _T("");
	//}}AFX_DATA_INIT

	//create an empty IMgaFCOs list. it gets filled by the searchbutton
	//and emptied by RemoveAll(), cleaned up by RemoveZombies()
	COMTHROW(results.CoCreateInstance(L"Mga.MgaFCOs"));
}


void CSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchDlg)
	DDX_Control(pDX, IDC_CHECK_LOCATE, m_chkLocateCtrl);
	DDX_Control(pDX, IDC_CHECK_CASESENS, m_chkMatchCaseCtrl);
	DDX_Control(pDX, IDC_CHECK_SCOPED, m_chkScopedSearchCtrl);
	DDX_Control(pDX, IDC_CHECKFULLWORD, m_chkFullWordCtrl);
	DDX_Control(pDX, IDC_EDITNAME, m_edtNameCtrl);
	DDX_Control(pDX, IDC_EDITKIND, m_edtKindNameCtrl);
	DDX_Control(pDX, IDC_EDITROLE, m_edtRoleNameCtrl);
	DDX_Control(pDX, IDC_EDITATTRNAME, m_edtAttrNameCtrl);
	DDX_Control(pDX, IDC_EDITATTRVALU, m_edtAttrValueCtrl);
	DDX_Control(pDX, IDC_CHECKSPLSEARCH, m_chkSplSearchCtrl);
	DDX_Control(pDX, IDC_STATICREF, m_stcRefCtrl);
	DDX_Control(pDX, IDC_CHECKREF, m_chkRefCtrl);
	DDX_Control(pDX, IDC_PROGRESSSEARCH, m_pgsSearch);
	DDX_Control(pDX, IDC_CHECKATM, m_chkAtomCtrl);
	DDX_Control(pDX, IDC_CHECKSET, m_chkSetCtrl);
	DDX_Control(pDX, IDC_CHECKMOD, m_chkModCtrl);
	DDX_Control(pDX, IDC_COMBOTYPE, m_cmbCtrl);
	DDX_Control(pDX, IDC_BUTTON_GO, m_btnGO);
	DDX_Control(pDX, IDC_LISTRESULTS, m_lstResults);
	DDX_Text(pDX, IDC_EDITNAME, m_edtName);
	DDX_Text(pDX, IDC_EDITKIND, m_edtKindName);
	DDX_Text(pDX, IDC_EDITROLE, m_edtRoleName);
	DDX_CBString(pDX, IDC_COMBOTYPE, m_cmbType);
	DDX_Text(pDX, IDC_EDITATTRNAME, m_edtAttrName);
	DDX_Text(pDX, IDC_EDITATTRVALU, m_edtAttrValue);
	DDX_Check(pDX, IDC_CHECKATM, m_chkAtom);
	DDX_Check(pDX, IDC_CHECKFULLWORD, m_chkFullWord);
	DDX_Check(pDX, IDC_CHECKMOD, m_chkMod);
	DDX_Check(pDX, IDC_CHECKREF, m_chkRef);
	DDX_Check(pDX, IDC_CHECKSET, m_chkSet);
	DDX_Check(pDX, IDC_CHECKSPLSEARCH, m_chkSplSearch);
	DDX_Check(pDX, IDC_CHECK_LOCATE, m_chkLocate);
	DDX_Check(pDX, IDC_CHECK_CASESENS, m_chkMatchCase);
	DDX_Check(pDX, IDC_CHECK_SCOPED, m_chkScopedSearch);
	DDX_Text(pDX, IDC_STATICREF, m_stcRef);
	//}}AFX_DATA_MAP
	DDX_ValidateInp(pDX, IDC_EDITNAME, m_edtName);
	DDX_ValidateInp(pDX, IDC_EDITKIND, m_edtKindName);
	DDX_ValidateInp(pDX, IDC_EDITROLE, m_edtRoleName);
	DDX_ValidateInp(pDX, IDC_EDITATTRNAME, m_edtAttrName);
	DDX_ValidateInp(pDX, IDC_EDITATTRVALU, m_edtAttrValue);
}


BEGIN_MESSAGE_MAP(CSearchDlg, CDialog)
	//{{AFX_MSG_MAP(CSearchDlg)
	ON_BN_CLICKED(IDC_BUTTON_GO, OnButtonGo)
	ON_NOTIFY(NM_CLICK, IDC_LISTRESULTS, OnClickListResults)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTRESULTS, OnDblclkListResults)
	ON_BN_CLICKED(IDC_CHECKSPLSEARCH, OnCheckSplSearch)
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
	ON_WM_SIZING()
END_MESSAGE_MAP()

void CSearchDlg::EnableScoped( BOOL enabled)
{
	m_scopedCtrlEnabled = enabled;
	if( m_chkScopedSearchCtrl.GetSafeHwnd())
	{
		m_chkScopedSearchCtrl.SetCheck( BST_UNCHECKED);
		m_chkScopedSearchCtrl.EnableWindow( m_scopedCtrlEnabled);
	}
}

BOOL CSearchDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	//EnableSplSearch();
	m_chkScopedSearchCtrl.EnableWindow( m_scopedCtrlEnabled);

	m_lstResults.InsertColumn(1, "Object", LVCFMT_LEFT, 100, 1);
	m_lstResults.InsertColumn(2, "Path", LVCFMT_LEFT, 210, 2);
	m_lstResults.InsertColumn(3, "Type", LVCFMT_LEFT, 95, 3);
	m_lstResults.InsertColumn(4, "Value", LVCFMT_LEFT, 210, 4);

	specialSearchFCO = NULL;
	m_stcRefCtrl.SetWindowText("NULL References");
	m_stcRefCtrl.ShowWindow(TRUE);

	m_pgsSearch.SetRange(1,16000);
	m_pgsSearch.SetStep(1);

	//m_edtNameCtrl.SetFocus();

	return true;

}

/////////////////////////////////////////////////////////////////////////////
// CSearchDlg message handlers


/////////////////////////////////////////////////////////////////////////////
//  These functions should be implemented to work with CSearchCtl

// Must remove all search result
void CSearchDlg::RemoveAll()
{
//	AfxMessageBox("Begin RemoveAll()");
	results = NULL;
	COMTHROW(results.CoCreateInstance(L"Mga.MgaFCOs"));
	DisplayResults();


//removing the tail turned out to perform better than removing the head, but all in all, 
//just setting to null and making a new list (above) is the fastest
/*	long count;
	COMTHROW(results->get_Count(&count));
	for(long i=count; i>0; i--)
	{
		COMTHROW(results->Remove(i)); //keep removing the tail till there's nothing left (1-based)
	}
*/
//	AfxMessageBox("End RemoveAll()");

}

// Must remove results belong to zombie objects
void CSearchDlg::RemoveZombies()
{

//	AfxMessageBox("ZOMBIES");
	bool zombieFound = false;

	CSearchCtrl *TheCtrl = GetCtrl();
	TheCtrl->BeginTransaction();
	
	long position = 1; //IMgaFCOs is 1-based
	MGACOLL_ITERATE(IMgaFCO,results)
	{
		long oStatus;
		COMTHROW(MGACOLL_ITER->get_Status(&oStatus));
		if(oStatus != OBJECT_EXISTS)
		{
			COMTHROW(results->Remove(position));
			//removing the zombie causes the next item to have the same position
			//that the zombie just had, so don't advance the position counter
			zombieFound = true;
		}
		else
		{
			position++;
		}

	}MGACOLL_ITERATE_END;

	if(zombieFound) //only redraw if we had to remove a zombie
	{
		DisplayResults();
	}

	if(specialSearchFCO != NULL)
	{	//test if specialSearchFCO became a zombie
		long oStatus;
		COMTHROW(specialSearchFCO->get_Status(&oStatus));
		if(oStatus != OBJECT_EXISTS)
		{
			specialSearchFCO = NULL;
			m_stcRefCtrl.SetWindowText("NULL References");
			m_stcRefCtrl.ShowWindow(TRUE);
		}
	}


	TheCtrl->CommitTransaction();

}

// Enable search functions
void CSearchDlg::EnableSearch()
{

	m_btnGO.EnableWindow(TRUE);
	m_lstResults.EnableWindow(TRUE);

	
}

// Must disable search functions
void CSearchDlg::DisableSearch()
{
	m_btnGO.EnableWindow(FALSE);
	m_lstResults.EnableWindow(FALSE);
}
void CSearchDlg::OnButtonGo() 
{

	if(CWnd::UpdateData(TRUE))
	{

		if(!m_edtAttrValue.IsEmpty() && m_edtAttrName.IsEmpty())
		{
			AfxMessageBox("Please Specify an Attribute Name along with the Value");
			return;
		}


		CSearchCtrl *TheCtrl = GetCtrl();
		CComPtr<IMgaProject> ccpProject = TheCtrl->GetProject();

		//show progress on especially long searches
		m_pgsSearch.ShowWindow(SW_RESTORE);
		RemoveAll();
//		AfxMessageBox("Searching");
		m_lstResults.ShowWindow(SW_HIDE);

		TheCtrl->BeginTransaction();
		CComPtr<IMgaObjects> ccpObjectsInTerr = TheCtrl->PutInMyTerritory( TheCtrl->GetScopedL());

		//the CInput class is a legacy from the Search Add-on
		//it has functionality for local searching, 
		//which is not used here. (hence the NULL's and 0's below)
		CComPtr<IMgaFolder> rootInput;
		COMTHROW(ccpProject->get_RootFolder(&rootInput));
		CInput inp;
		inp.GetInput(m_edtName,m_edtRoleName,m_edtKindName,m_edtAttrName,m_cmbCtrl.GetCurSel(),m_edtAttrValue,
						m_chkSplSearch,m_chkMod,m_chkAtom,m_chkRef,m_chkSet,m_chkFullWord,NULL,0,m_chkMatchCase,m_chkScopedSearch);

		
		CSearch searchGME(inp);

		searchGME.Search(rootInput, ccpObjectsInTerr, specialSearchFCO,results,&m_pgsSearch);
//		AfxMessageBox("Finished Searching");
		
		DisplayResults();
		m_pgsSearch.ShowWindow(SW_HIDE);
		m_pgsSearch.SetPos(1);


		TheCtrl->CommitTransaction();
	}
	
}

// recursively build a path of names from the rootFCO to "named" used in the original call
void CSearchDlg::BuildExtendedName(IMgaFCO *named, CString &extName)
{
	
	if (named != NULL)
	{
		CComPtr<IMgaModel> parent;
		COMTHROW( named->get_ParentModel(&parent));
		if (parent != NULL)
		{
			BuildExtendedName(parent, extName);
			extName += " : ";
		}
		else //parent is a Folder
		{
			CComPtr<IMgaFolder> parentFolder = NULL;
			COMTHROW( named->get_ParentFolder(&parentFolder));
			BuildExtendedName(parentFolder, extName);
			extName += " : ";
		}
		CBstr bstr;
		COMTHROW( named->get_Name(bstr));
		extName += bstr;
	}

}

// Get the parent folders' names, too
void CSearchDlg::BuildExtendedName(IMgaFolder *named, CString &extName)
{
	if (named != NULL)
	{
		CComPtr<IMgaFolder> parent;
		COMTHROW( named->get_ParentFolder(&parent));
		if (parent != NULL)
		{
			BuildExtendedName(parent, extName);
			extName += " : ";
		}
		CBstr bstr;
		COMTHROW( named->get_Name(bstr));
		extName += bstr;
	}
}

//display all found items at once
void CSearchDlg::DisplayResults()
{
//	AfxMessageBox("Displaying Results");
	int count = 0;
	CString name;
	CString path, type, valu;
	bool attr_value_to_be_shown = !m_edtAttrValue.IsEmpty() && !m_edtAttrName.IsEmpty();

	if(!m_chkSplSearch) //only want to wipe this out on a regular search
	{
		specialSearchFCO = NULL;
		m_stcRefCtrl.SetWindowText("NULL References");
		m_stcRefCtrl.ShowWindow(TRUE);
	}


	//Hide the window so it doesn't waste time redrawing each time we add an item
	m_lstResults.ShowWindow(SW_HIDE);
	m_lstResults.DeleteAllItems();
	
    //CWnd::UpdateData(false);	
	

	MGACOLL_ITERATE(IMgaFCO, results)
	{

		path = "";
		name = "";
		type = "";
		valu = "";
		CBstr bstr;
		COMTHROW( MGACOLL_ITER->get_Name(bstr) );
		name += bstr;

		BuildExtendedName(MGACOLL_ITER.p, path);


		objtype_enum rret;
		COMTHROW( MGACOLL_ITER->get_ObjType( &rret) );
		if (rret == OBJTYPE_ATOM)
			type = "ATOM";
		else if (rret == OBJTYPE_MODEL)
			type = "MODEL";
		else if (rret == OBJTYPE_REFERENCE)
			type = "REFERENCE";
		else if (rret == OBJTYPE_SET)
			type = "SET";

		m_lstResults.InsertItem(count, name);
		m_lstResults.SetItemText(count, 1, path);
		m_lstResults.SetItemText(count, 2, type);
		if( attr_value_to_be_shown)
		{
			try {
				CComBSTR bstr;
				COMTHROW( MGACOLL_ITER->get_StrAttrByName( CComBSTR( m_edtAttrName), &bstr));
				valu += bstr;
				m_lstResults.SetItemText(count, 3, valu);
			}
			catch(hresult_exception&) { // prepare for the unexpected
				m_lstResults.SetItemText(count, 3, "<<Not found>>");
			}
		}
		
		count++;

		//let the user know the searcher is still alive for especially long result lists
		//(before, when this function didn't hide the m_lstResults control while adding stuff, 
		//it would take much more time than the actual searching for long result lists)
		m_pgsSearch.StepIt();

		
	} MGACOLL_ITERATE_END;

	if (count==0)
	{
		m_lstResults.InsertItem(count, "");
		m_lstResults.SetItemText(count, 1, "No Matching Results");
	}

	//Now that everything is added, allow the display to redraw
	m_lstResults.ShowWindow(SW_RESTORE);

}

void CSearchDlg::OnClickListResults(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	this->itemClicked(); *pResult = 0;/*long count = 0;
	if( results) COMTHROW(results->get_Count(&count));

	if(count > 0 ) //don't want to grab stuff out of an empty list
	{

		CWnd::UpdateData(TRUE);

		CSearchCtrl *TheCtrl = GetCtrl();
		try
		{
			TheCtrl->BeginTransaction();

			long selected = m_lstResults.GetSelectionMark() + 1; //IMgaFCOs 1 based, GetSelectionMark 0 based
			CComPtr<IMgaFCO> selectedFCO;
			// selected might be 0 because GeSelectionMark might have returned -1
			if( selected >= 1 && selected <= count)
			{
				COMTHROW(results->get_Item(selected,&selectedFCO)); // crashed probably when called with 0
				
				//want to be able to search for references to this object in the special search
				CBstr bstr;
				CString name;
				COMTHROW( selectedFCO->get_Name(bstr));
				name = CString( bstr) + " References";
				m_stcRefCtrl.SetWindowText(name);
				m_stcRefCtrl.ShowWindow(TRUE);
				specialSearchFCO = selectedFCO;
			}
			
			//CComPtr<IMgaObject> selectedObject = (IMgaObject *)(selectedFCO.p); // WAS this the scapegoat?
			CComQIPtr<IMgaObject> selectedObject( selectedFCO);
			TheCtrl->CommitTransaction();
			if( selectedObject) TheCtrl->ClickOnObject(selectedObject);
		}
		catch( ...)
		{
			TheCtrl->AbortTransaction();
		}

		*pResult = 0;
	}*/

}

void CSearchDlg::OnDblclkListResults(NMHDR* pNMHDR, LRESULT* pResult) 
{

	this->itemDblClicked(); *pResult = 0;/*long count = 0;
	if( results) COMTHROW(results->get_Count(&count));


	if(count > 0 ) //don't want to grab stuff out of an empty list
	{
		CWnd::UpdateData(TRUE);

		CSearchCtrl *TheCtrl = GetCtrl();
		try
		{
			// non-model children of Folders can't be shown, only located
			bool must_do_locate = false;

			TheCtrl->BeginTransaction();

			long selected = m_lstResults.GetSelectionMark() + 1; //IMgaFCOs 1 based, GetSelectionMark 0 based
			CComPtr<IMgaFCO> selectedFCO;
			// selected might be 0 because GeSelectionMark might have returned -1
			if( selected >= 1 && selected <= count)
			{
				COMTHROW(results->get_Item(selected,&selectedFCO)); // crashed probably when called with 0

				CComPtr<IMgaFolder> parent;
				COMTHROW( selectedFCO->get_ParentFolder( &parent));
				if( parent)
				{
					objtype_enum objtp;
					COMTHROW( selectedFCO->get_ObjType( &objtp));
					if( objtp != OBJTYPE_MODEL)
						must_do_locate = true; // can't show it otherwise 
				}

				

				//want to be able to search for references to this object in the special search
				CBstr bstr;
				CString name;
				COMTHROW( selectedFCO->get_Name(bstr));
				name = CString( bstr) + " References";
				m_stcRefCtrl.SetWindowText(name);
				m_stcRefCtrl.ShowWindow(TRUE);
				specialSearchFCO = selectedFCO;
			}
			
			//CComPtr<IMgaObject> selectedObject = (IMgaObject *)(selectedFCO.p); // WAS this the scapegoat?
			CComQIPtr<IMgaObject> selectedObject( selectedFCO);
			TheCtrl->CommitTransaction();
			if( selectedObject)
			{
				if( m_chkLocate || must_do_locate) TheCtrl->LocateMgaObject(selectedObject);
				else             TheCtrl->DblClickOnObject(selectedObject);
			}

		}
		catch(...)
		{
			TheCtrl->AbortTransaction();
		}

		*pResult = 0;
	}*/

}

void CSearchDlg::OnCheckSplSearch() 
{

	CWnd::UpdateData(TRUE);

	if(m_chkSplSearch)
	{
		m_chkMod = FALSE;
		m_chkAtom = FALSE;
		m_chkSet = FALSE;
		m_chkRef = TRUE;

		m_chkModCtrl.EnableWindow(FALSE);
		m_chkAtomCtrl.EnableWindow(FALSE);
		m_chkSetCtrl.EnableWindow(FALSE);
		m_chkRefCtrl.EnableWindow(FALSE);
		CWnd::UpdateData(FALSE);
	}
	else
	{
		m_chkMod = TRUE;
		m_chkAtom = TRUE;
		m_chkSet = TRUE;
		m_chkRef = TRUE;

		m_chkModCtrl.EnableWindow(TRUE);
		m_chkAtomCtrl.EnableWindow(TRUE);
		m_chkSetCtrl.EnableWindow(TRUE);
		m_chkRefCtrl.EnableWindow(TRUE);
		CWnd::UpdateData(FALSE);

		//reset special reference search to NULL
		specialSearchFCO = NULL;
		m_stcRefCtrl.SetWindowText("NULL References");
		m_stcRefCtrl.ShowWindow(TRUE);
		CWnd::UpdateData(TRUE);
	}
	
	
	
}

void CSearchDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if( nType == SIZE_MINIMIZED) return; 

	if( cx >= 0 && cy >= 0 && m_lstResults.GetSafeHwnd())
	{
		CRect r0;
		m_lstResults.GetWindowRect( &r0); ScreenToClient( &r0);

		//presumption: r0.left is the horiz_margin on both sides
		cy -= r0.top + r0.left; // we use the horiz_margin when determining height
		cx -= 2 * r0.left;
		m_lstResults.SetWindowPos( 0, 0, 0, cx, cy, SWP_NOMOVE|SWP_NOZORDER|SWP_SHOWWINDOW);
	}
}

void CSearchDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialog::OnSizing(fwSide, pRect);
	// GMESearch::OnSizing() responsible for preventing shrinking the window too much
}

void CSearchDlg::clickGo()
{
	this->OnButtonGo();
}

void CSearchDlg::itemClicked()
{
	long count = 0;
	if( results) COMTHROW(results->get_Count(&count));

	if(count > 0 ) //don't want to grab stuff out of an empty list
	{

		CWnd::UpdateData(TRUE);

		CSearchCtrl *TheCtrl = GetCtrl();
		try
		{
			TheCtrl->BeginTransaction();

			long selected = m_lstResults.GetSelectionMark() + 1; //IMgaFCOs 1 based, GetSelectionMark 0 based
			CComPtr<IMgaFCO> selectedFCO;
			// selected might be 0 because GeSelectionMark might have returned -1
			if( selected >= 1 && selected <= count)
			{
				COMTHROW(results->get_Item(selected,&selectedFCO)); // crashed probably when called with 0
				
				//want to be able to search for references to this object in the special search
				CBstr bstr;
				CString name;
				COMTHROW( selectedFCO->get_Name(bstr));
				name = CString( bstr) + " References";
				m_stcRefCtrl.SetWindowText(name);
				m_stcRefCtrl.ShowWindow(TRUE);
				specialSearchFCO = selectedFCO;
			}
			
			//CComPtr<IMgaObject> selectedObject = (IMgaObject *)(selectedFCO.p); // WAS this the scapegoat?
			CComQIPtr<IMgaObject> selectedObject( selectedFCO);
			TheCtrl->CommitTransaction();
			if( selectedObject) TheCtrl->ClickOnObject(selectedObject);
		}
		catch( ...)
		{
			TheCtrl->AbortTransaction();
		}
	}
}

void CSearchDlg::itemDblClicked()
{
	long count = 0;
	if( results) COMTHROW(results->get_Count(&count));


	if(count > 0 ) //don't want to grab stuff out of an empty list
	{
		CWnd::UpdateData(TRUE);

		CSearchCtrl *TheCtrl = GetCtrl();
		try
		{
			// non-model children of Folders can't be shown, only located
			bool must_do_locate = false;

			TheCtrl->BeginTransaction();

			long selected = m_lstResults.GetSelectionMark() + 1; //IMgaFCOs 1 based, GetSelectionMark 0 based
			CComPtr<IMgaFCO> selectedFCO;
			// selected might be 0 because GeSelectionMark might have returned -1
			if( selected >= 1 && selected <= count)
			{
				COMTHROW(results->get_Item(selected,&selectedFCO)); // crashed probably when called with 0

				CComPtr<IMgaFolder> parent;
				COMTHROW( selectedFCO->get_ParentFolder( &parent));
				if( parent)
				{
					objtype_enum objtp;
					COMTHROW( selectedFCO->get_ObjType( &objtp));
					if( objtp != OBJTYPE_MODEL)
						must_do_locate = true; // can't show it otherwise 
				}

				

				//want to be able to search for references to this object in the special search
				CBstr bstr;
				CString name;
				COMTHROW( selectedFCO->get_Name(bstr));
				name = CString( bstr) + " References";
				m_stcRefCtrl.SetWindowText(name);
				m_stcRefCtrl.ShowWindow(TRUE);
				specialSearchFCO = selectedFCO;
			}
			
			//CComPtr<IMgaObject> selectedObject = (IMgaObject *)(selectedFCO.p); // WAS this the scapegoat?
			CComQIPtr<IMgaObject> selectedObject( selectedFCO);
			TheCtrl->CommitTransaction();
			if( selectedObject)
			{
				if( m_chkLocate || must_do_locate) TheCtrl->LocateMgaObject(selectedObject);
				else             TheCtrl->DblClickOnObject(selectedObject);
			}

		}
		catch(...)
		{
			TheCtrl->AbortTransaction();
		}

	}
}

void CSearchDlg::tabPressed( CWnd * pOriginator, bool bShift /*= false*/)
{
	CWnd *nxt = 0;
	nxt = GetNextDlgTabItem( pOriginator, bShift);
	if( nxt) {
		nxt->SetFocus();
	}
}
