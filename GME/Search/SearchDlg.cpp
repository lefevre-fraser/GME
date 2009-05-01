// SearchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Search.h"
#include "SearchDlg.h"
#include "SearchCtl.h"
#include "Validate.h"
#include "Input.h"
#include "SearchAlg.h"
#include <string>
#include <sstream>
#include <stack>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchDlg dialog


CSearchDlg::CSearchDlg()
: m_scopedCtrlEnabled( FALSE)
, m_edtName2(_T(""))
, m_edtRoleName2(_T(""))
, m_edtKindName2(_T(""))
, m_edtAttribute2(_T(""))
, m_cmbType2(_T(""))
, m_scope(0)
, m_searchResults(FALSE)
, m_radioLogical(0)
,vScrollWidth (::GetSystemMetrics (SM_CXVSCROLL)),	// WinXP default style: 17
lineSize (20),
pageSize (50),
v_scrollPos(0),
h_scrollPos(0)

{
    //{{AFX_DATA_INIT(CSearchDlg)
    m_edtName = _T("");
    m_edtKindName = _T("");
    m_edtRoleName = _T("");
    //m_cmbType = _T("");
    m_edtAttrName = _T("");
    m_edtAttrValue = _T("");
    m_chkAtom = TRUE;
    m_chkFullWord = FALSE;
    m_chkMod = TRUE;
    m_chkRef = TRUE;
    m_chkSet = TRUE;
    //m_chkSplSearch = FALSE;
    m_chkLocate = FALSE;
    m_chkMatchCase = TRUE;
    //m_chkScopedSearch = FALSE;
    //m_stcRef = _T("");
    //}}AFX_DATA_INIT


    //create an empty IMgaFCOs list. it gets filled by the searchbutton
    //and emptied by RemoveAll(), cleaned up by RemoveZombies()
    COMTHROW(results.CoCreateInstance(L"Mga.MgaFCOs"));
}


void CSearchDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CSearchDlg)
    //DDX_Control(pDX, IDC_CHECK_LOCATE, m_chkLocateCtrl);
    DDX_Control(pDX, IDC_CHECK_CASESENS, m_chkMatchCaseCtrl);
    // DDX_Control(pDX, IDC_CHECK_SCOPED, m_chkScopedSearchCtrl);
    DDX_Control(pDX, IDC_CHECKFULLWORD, m_chkFullWordCtrl);
    DDX_Control(pDX, IDC_EDITNAME, m_edtNameCtrl);
    DDX_Control(pDX, IDC_EDITKIND, m_edtKindNameCtrl);
    DDX_Control(pDX, IDC_EDITROLE, m_edtRoleNameCtrl);
    DDX_Control(pDX, IDC_EDITATTRNAME, m_edtAttrNameCtrl);
    //DDX_Control(pDX, IDC_EDITATTRVALU, m_edtAttrValueCtrl);
    //DDX_Control(pDX, IDC_CHECKSPLSEARCH, m_chkSplSearchCtrl);
    //    DDX_Control(pDX, IDC_STATICREF, m_stcRefCtrl);
    DDX_Control(pDX, IDC_CHECKREF, m_chkRefCtrl);
    DDX_Control(pDX, IDC_PROGRESSSEARCH, m_pgsSearch);
    DDX_Control(pDX, IDC_CHECKATM, m_chkAtomCtrl);
    DDX_Control(pDX, IDC_CHECKSET, m_chkSetCtrl);
    DDX_Control(pDX, IDC_CHECKMOD, m_chkModCtrl);
    //    DDX_Control(pDX, IDC_COMBOTYPE, m_cmbCtrl);
    DDX_Control(pDX, IDC_BUTTON_GO, m_btnGO);
    DDX_Control(pDX, IDC_LISTRESULTS, m_lstResults);
    DDX_Text(pDX, IDC_EDITNAME, m_edtName);
    DDX_Text(pDX, IDC_EDITKIND, m_edtKindName);
    DDX_Text(pDX, IDC_EDITROLE, m_edtRoleName);
    //DDX_CBString(pDX, IDC_COMBOTYPE, m_cmbType);
    DDX_Text(pDX, IDC_EDITATTRNAME, m_edtAttrName);
    //DDX_Text(pDX, IDC_EDITATTRVALU, m_edtAttrValue);
    DDX_Check(pDX, IDC_CHECKATM, m_chkAtom);
    DDX_Check(pDX, IDC_CHECKFULLWORD, m_chkFullWord);
    DDX_Check(pDX, IDC_CHECKMOD, m_chkMod);
    DDX_Check(pDX, IDC_CHECKREF, m_chkRef);
    DDX_Check(pDX, IDC_CHECKSET, m_chkSet);
    //   DDX_Check(pDX, IDC_CHECKSPLSEARCH, m_chkSplSearch);
    //DDX_Check(pDX, IDC_CHECK_LOCATE, m_chkLocate);
    DDX_Check(pDX, IDC_CHECK_CASESENS, m_chkMatchCase);
    //DDX_Check(pDX, IDC_CHECK_SCOPED, m_chkScopedSearch);
    //DDX_Text(pDX, IDC_STATICREF, m_stcRef);
    //}}AFX_DATA_MAP
    DDX_ValidateInp(pDX, IDC_EDITNAME, m_edtName);
    DDX_ValidateInp(pDX, IDC_EDITKIND, m_edtKindName);
    DDX_ValidateInp(pDX, IDC_EDITROLE, m_edtRoleName);
    DDX_ValidateInp(pDX, IDC_EDITATTRNAME, m_edtAttrName);
    //DDX_ValidateInp(pDX, IDC_EDITATTRVALU, m_edtAttrValue);

    DDX_Text(pDX, IDC_EDITNAME2, m_edtName2);
    DDX_Text(pDX, IDC_EDITROLE2, m_edtRoleName2);
    DDX_Text(pDX, IDC_EDITKIND2, m_edtKindName2);
    DDX_Text(pDX, IDC_EDITATTRVALU2, m_edtAttribute2);
    //DDX_Radio(pDX, IDC_RADIOAND, m_radioAnd);
    DDX_Control(pDX, IDC_RADIOAND, m_logicalGrp);
    //DDX_Control(pDX, IDC_COMBOTYPE2, m_cmbCtrl2);
    DDX_Control(pDX, IDC_PREV_SRCH, m_prevSearches);
    //DDX_CBString(pDX, IDC_COMBOTYPE2, m_cmbType2);
    DDX_Radio(pDX, IDC_ENTIRESCOPE2, m_scope);
    DDX_Check(pDX, IDC_CHECK_RESULTS, m_searchResults);
    DDX_Radio(pDX, IDC_RADIOAND, m_radioLogical);
    DDX_Control(pDX, IDC_EDITNAME2, m_edtNameCtrl2);
    DDX_Control(pDX, IDC_EDITROLE2, m_edtRoleNameCtrl2);
    DDX_Control(pDX, IDC_EDITKIND2, m_edtKindNameCtrl2);
    DDX_Control(pDX, IDC_EDITATTRVALU2, m_edtAttributeCtrl2);
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
    ON_WM_VSCROLL()
    ON_WM_HSCROLL()
    //ON_CBN_SELCHANGE(IDC_COMBOTYPE, &CSearchDlg::OnCbnSelchangeCombotype)
    ON_NOTIFY(NM_DBLCLK, IDC_PREV_SRCH, OnDblclkPrevSearches)
    /*ON_EN_CHANGE(IDC_EDITNAME2, &CSearchDlg::OnEnChangeEditname2)
    ON_CBN_SELCHANGE(IDC_EDITNAME2, &CSearchDlg::OnCbnSelchangeEditname2)
    ON_CBN_SELCHANGE(IDC_EDITKIND, &CSearchDlg::OnCbnSelchangeEditkind)
    ON_CBN_SELCHANGE(IDC_EDITNAME, &CSearchDlg::OnCbnSelchangeEditname)*/
END_MESSAGE_MAP()

/*void CSearchDlg::EnableScoped( BOOL enabled)
{
m_scopedCtrlEnabled = enabled;
if( m_chkScopedSearchCtrl.GetSafeHwnd())
{
m_chkScopedSearchCtrl.SetCheck( BST_UNCHECKED);
m_chkScopedSearchCtrl.EnableWindow( m_scopedCtrlEnabled);
}
}*/

BOOL CSearchDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    //EnableSplSearch();
    //m_chkScopedSearchCtrl.EnableWindow( m_scopedCtrlEnabled);

    m_lstResults.InsertColumn(1, "Object", LVCFMT_LEFT, 100, 1);
    m_lstResults.InsertColumn(2, "Path", LVCFMT_LEFT, 210, 2);
    m_lstResults.InsertColumn(3, "Type", LVCFMT_LEFT, 95, 3);
    m_lstResults.InsertColumn(4, "Value", LVCFMT_LEFT, 210, 4);
	m_lstResults.SetExtendedStyle(m_lstResults.GetExtendedStyle()|LVS_EX_FULLROWSELECT);

    specialSearchFCO = NULL;
    //m_stcRefCtrl.SetWindowText("NULL References");
    //m_stcRefCtrl.ShowWindow(TRUE);

    m_pgsSearch.SetRange(1,16000);
    m_pgsSearch.SetStep(1);

    //added
    m_prevSearches.InsertColumn(1,"Search String",LVCFMT_LEFT,100,1);
    LoadPrevSearch();
    //m_edtNameCtrl.SetFocus();

    //compute logical width and height
    //ComputeWidthHeight();

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
            //m_stcRefCtrl.SetWindowText("NULL References");
            //m_stcRefCtrl.ShowWindow(TRUE);
        }
    }


    TheCtrl->CommitTransaction();

}

/* compute logical width and height of the components using
the child controls
This is not working needs a fix.
*/

void CSearchDlg::ComputeWidthHeight()
{
    HWND hwnd = ::GetWindow( GetSafeHwnd(),
        GW_CHILD);
    RECT r;
    int minx, maxx,miny,maxy;
    ::GetClientRect(hwnd,&r);
    minx=r.left;miny=r.top;maxx=r.right;maxy=r.bottom;
    hwnd = ::GetWindow( hwnd, GW_HWNDNEXT |GW_HWNDFIRST);
    while( hwnd )
    {
        //::EnableWindow(hwnd,true);
        // Get the next window. Use it.
        ::GetClientRect(hwnd,&r);
        if(minx>r.left) minx=r.left;
        if(maxx<r.right) maxx=r.right;
        if(miny>r.top) miny=r.top;
        if(maxy<r.bottom) maxy=r.bottom;
        hwnd = ::GetWindow( hwnd, GW_HWNDNEXT |GW_HWNDFIRST);


    }
    GetClientRect(&r);ScreenToClient(&r);
    pageHeight=maxy-miny+r.top*2;
    pageWidth=maxx-minx+r.left*2;
}

// Enable search 
void CSearchDlg::EnableSearch()
{
    //Iterate through all the child controls and enable it
    HWND hwnd = ::GetWindow( GetSafeHwnd(),
        GW_CHILD);

    while( hwnd )
    {
        ::EnableWindow(hwnd,true);
        // Get the next window. Use it.
        hwnd = ::GetWindow( hwnd, GW_HWNDNEXT |GW_HWNDFIRST);


    }
}

// Must disable search functions
void CSearchDlg::DisableSearch()
{

    //Iterate through all the child controls and disable it
    HWND hwnd = ::GetWindow( GetSafeHwnd(),
        GW_CHILD |GW_HWNDFIRST);
    while( hwnd )
    {
        ::EnableWindow(hwnd,false);
        // Get the next window. Use it.
        hwnd = ::GetWindow( hwnd, GW_HWNDNEXT );
    }
}


void CSearchDlg::OnButtonGo() 
{

    if(CWnd::UpdateData(TRUE))
    {

        /*if(!m_edtAttrValue.IsEmpty() && m_edtAttrName.IsEmpty())
        {
        AfxMessageBox("Please Specify an Attribute Name along with the Value");
        return;
        }*/

        if(m_searchResults)
        {
            SearchResults();
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
        inp.GetInput(m_edtName,m_edtRoleName,m_edtKindName,m_edtAttrName,m_edtName2,m_edtRoleName2,m_edtKindName2,m_edtAttribute2,m_edtAttrValue,
            m_chkMod,m_chkAtom,m_chkRef,m_chkSet,m_chkFullWord,NULL,0,m_chkMatchCase,m_scope,m_radioLogical);


        CSearch searchGME(inp);

        searchGME.Search(rootInput, ccpObjectsInTerr, specialSearchFCO,results,&m_pgsSearch);
        //		AfxMessageBox("Finished Searching");

        DisplayResults();
        m_pgsSearch.ShowWindow(SW_HIDE);
        m_pgsSearch.SetPos(1);



        TheCtrl->CommitTransaction();

    }
    CreateSearchHistory();
    SaveSearch();

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

    /*if(!m_chkSplSearch) //only want to wipe this out on a regular search
    {
    specialSearchFCO = NULL;
    m_stcRefCtrl.SetWindowText("NULL References");
    m_stcRefCtrl.ShowWindow(TRUE);
    }*/


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

/*TODO:  Remove this*/
void CSearchDlg::OnCheckSplSearch() 
{

    /*CWnd::UpdateData(TRUE);

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
    }*/



}
//TODO: Refactor this, its a bit long
//Separate horizontal and vertical scroll bar code
void CSearchDlg::OnSize(UINT nType, int cx, int cy)
{

    CDialog::OnSize(nType, cx, cy);

	return;
    int width_x=cx;
    int width_y=cy;
    int right_margin=0;

    if( nType == SIZE_MINIMIZED) return; 

    //resize results list
    if( cx >= 0 && cy >= 0 && m_lstResults.GetSafeHwnd())
    {
        CRect rectResults;
        m_lstResults.GetWindowRect( &rectResults); ScreenToClient( &rectResults);
		m_lstResults.SetWindowPos( NULL, 0, 0, cx, rectResults.Height(), SWP_NOMOVE|SWP_NOZORDER|SWP_SHOWWINDOW);
    }
	return;
    // resize previous searches
    if( width_x >= 0 && width_y >= 0 && m_prevSearches.GetSafeHwnd())
    {
        CRect r0;
        m_prevSearches.GetWindowRect( &r0); ScreenToClient( &r0);

        //presumption: r0.left is the horiz_margin on both sides
        width_y = r0.bottom - r0.top; // we use the horiz_margin when determining height
        width_x = width_x-r0.left-right_margin;


        width_x=width_x>100?width_x:100;
        width_y=width_y>100?width_y:100;

        m_prevSearches.SetWindowPos( 0, r0.left, r0.top, width_x, width_y, SWP_NOMOVE|SWP_NOZORDER|SWP_SHOWWINDOW);

    }

    RECT r;
    GetClientRect(&r);ScreenToClient(&r);

    //check if height and width has changed
    int changeWidth=r.right-r.left-pageWidth;
    int changeHeight=r.bottom-r.top-pageWidth;
    bool widthChanged=(r.right-r.left)!=pageWidth;
    bool heightChanged=(r.bottom-r.top)!=pageHeight;


    //calculate page height and page width
    pageHeight=r.bottom-r.top;
    pageWidth=r.right-r.left;
    //hard coded need to change it
    //TODO: need to programmatically determine logical width so that it can be used.
    logicalHeight=390;
    logicalWidth=585;

    int oldPos= v_scrollPos; 



    //if height changed scroll window
    if(logicalHeight>pageHeight)
    {
        //v_scrollPos= v_scrollPos*((double)pageHeight/logicalHeight);
        if (v_scrollPos < 0)
            v_scrollPos = 0;
        if (v_scrollPos > (logicalHeight - pageHeight + 1))
            v_scrollPos = (logicalHeight - pageHeight + 1);
        ScrollWindow(0,oldPos - v_scrollPos,  NULL, NULL);
    }
    //set vertical scroll bar

    if(logicalHeight>pageHeight)
    {
        SCROLLINFO si;
        si.fMask=SIF_ALL;
        si.nMax=logicalHeight;
        si.nMin=0;
        si.nPos=v_scrollPos;
        si.nPage=pageHeight;
        si.nTrackPos=2;
        SetScrollInfo(SB_VERT,&si);
    }


    oldPos=h_scrollPos;
    
    //if width changed scroll window appropriately
    if(logicalWidth>pageWidth)
    {
        // h_scrollPos = h_scrollPos*(((double)pageWidth)/logicalWidth);
        if (h_scrollPos < 0)
            h_scrollPos = 0;
        if (h_scrollPos > (logicalWidth - pageWidth + 1))
            h_scrollPos = (logicalWidth - pageWidth + 1);
        ScrollWindow(oldPos - h_scrollPos,0,  NULL, NULL);
        // SetScrollPos(SB_HORZ,h_scrollPos,true);
    }
    //set horizontal scroll bar
    if(logicalWidth>pageWidth)
    {
        SCROLLINFO hsi;
        hsi.fMask=SIF_ALL;
        hsi.nMax=logicalWidth;
        hsi.nMin=0;
        hsi.nPos=h_scrollPos;
        hsi.nPage=pageWidth;
        hsi.nTrackPos=2;
        SetScrollInfo(SB_HORZ,&hsi);
    }

    ShowScrollBar(SB_VERT,logicalHeight>pageHeight);
    ShowScrollBar(SB_HORZ,logicalWidth>pageWidth);
    //Invalidate();
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
                //m_stcRefCtrl.SetWindowText(name);
                //m_stcRefCtrl.ShowWindow(TRUE);
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

                /*CComPtr<IMgaFolder> parent;
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
                specialSearchFCO = selectedFCO;*/
            }

            //CComPtr<IMgaObject> selectedObject = (IMgaObject *)(selectedFCO.p); // WAS this the scapegoat?
            CComQIPtr<IMgaObject> selectedObject( selectedFCO);
            TheCtrl->CommitTransaction();
            if( selectedObject)
            {
                TheCtrl->LocateMgaObject(selectedObject);
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


void CSearchDlg::ParseAttribute()
{
    std::stack<CString> expr;
    int index= m_edtAttrName.FindOneOf("&|");
    CString temp;
    int i=0;
    while(index!=-1)
    {
        AfxExtractSubString(temp,m_edtAttrName,i,m_edtAttrName[index]);
        expr.push(temp);
        expr.push(CString(m_edtAttrName[index]));
        i++;
        index= m_edtAttrName.FindOneOf("&|");
    }
    //m_edtAttrValue.Find(
}

void CSearchDlg::SaveSearch()
{
    CRegKey key;
    std::stringstream stream;

    if(key.Open(HKEY_CURRENT_USER,_TEXT("Software\\GME"),KEY_ALL_ACCESS)==ERROR_SUCCESS)
    {
        key.DeleteSubKey("Search");
        //key.Create(HKEY_CURRENT_USER,_TEXT("Software\\GME\\Search"));
    }
    key.Create(HKEY_CURRENT_USER,_TEXT("Software\\GME\\Search"));
    for(int i=0;i<m_prevSearches.GetItemCount();i++)
    {
        stream<<"search"<<i;
        key.SetStringValue(stream.str().c_str(), m_prevSearches.GetItemText(i,0));
        stream.str("");
    }
    key.Close();

}

void CSearchDlg::LoadPrevSearch()
{
    CRegKey key;
    std::string temp;
    std::stringstream stream(temp);
    ULONG length=1000;
    CHAR name[1000];

    int i=0;
    if(key.Open(HKEY_CURRENT_USER,_TEXT("Software\\GME\\Search"),KEY_ALL_ACCESS)==ERROR_SUCCESS)
    {
        while(i<10)
        {
            temp="search";
            stream<<int(i);
            temp+=stream.str();
            if(key.QueryStringValue(temp.c_str(),name,&length)!=ERROR_SUCCESS)
                break;
            //CString temp(name);
            //m_prevSearches.SetItemText(1,i,name);
            m_prevSearches.InsertItem(i,name);
            InsertHistory(name);
            stream.str("");
            i++;
        }

    }

}

// Create search history and insert it into history box
//and the respective combo boxes
void CSearchDlg::CreateSearchHistory()
{

    //insert at the top of combobox
    if (m_edtName!="")m_edtNameCtrl.InsertString(0,m_edtName);
    if (m_edtRoleName!="")m_edtRoleNameCtrl.InsertString(0,m_edtRoleName);
    if(m_edtKindName!="") m_edtKindNameCtrl.InsertString(0,m_edtKindName);
    if(m_edtAttrName!="") m_edtAttrNameCtrl.InsertString(0,m_edtAttrName);
    if (m_edtName2!="")m_edtNameCtrl2.InsertString(0,m_edtName2);
    if (m_edtRoleName2!="")m_edtRoleNameCtrl2.InsertString(0,m_edtRoleName2);
    if(m_edtKindName!="") m_edtKindNameCtrl2.InsertString(0,m_edtKindName);
    if(m_edtAttribute2!="") m_edtAttributeCtrl2.InsertString(0,m_edtAttribute2);
    //std::stringstream stream;
    CString srchString;
    srchString.Append(m_edtName);
    srchString.Append(" ,");
    srchString.Append(m_edtRoleName);
    srchString.Append(" ,");
    srchString.Append(m_edtKindName);
    srchString.Append(" ,");
    srchString.Append(m_edtAttrName);
    srchString.Append(" ,");
    //stream<<m_cmbCtrl.GetCurSel();
    //srchString.Append(stream.str().c_str());
    //srchString.Append(" ,");
    //stream.clear();

    srchString.Append(m_edtName2);
    srchString.Append(" ,");
    srchString.Append(m_edtRoleName2);
    srchString.Append(" ,");
    srchString.Append(m_edtKindName2);
    srchString.Append(" ,");
    srchString.Append(m_edtAttribute2);
    //srchString.Append(" ,");
    //stream<<m_cmbCtrl2.GetCurSel();
    //srchString.Append(stream.str().c_str());
    //srchString.Append(" ,");
    //stream.clear();

    CString first=m_prevSearches.GetItemText(0,0);
    if(first==srchString || srchString==" , , , , , , ,")
        return;

    if(m_prevSearches.GetItemCount()==10)
        m_prevSearches.DeleteItem(9);
    m_prevSearches.InsertItem(0,srchString);


}

void CSearchDlg::OnDblclkPrevSearches(NMHDR* pNMHDR, LRESULT* pResult) 
{
    int index=m_prevSearches.GetSelectionMark();
    CString srch=m_prevSearches.GetItemText(index,0);
    int curPos=0;
    m_edtName= srch.Tokenize(",",curPos).Trim();

    m_edtRoleName=srch.Tokenize(",",curPos).Trim();
    m_edtKindName=srch.Tokenize(",",curPos).Trim();
    m_edtAttrName=srch.Tokenize(",",curPos).Trim();
    //m_cmbType=srch.Tokenize(",",curPos);
    m_edtName2=srch.Tokenize(",",curPos).Trim();
    m_edtRoleName2=srch.Tokenize(",",curPos).Trim();
    m_edtKindName2=srch.Tokenize(",",curPos).Trim();
    m_edtAttribute2=srch.Tokenize(",",curPos).Trim();
    //m_cmbType2=srch.Tokenize(",",curPos);
    UpdateData(FALSE);    
}

/*
Inserts history in the combo box
*/

void CSearchDlg::InsertHistory(CString string)
{
    int curPos=0;
    int n;
    CString lbText;

    // For each combobox control check if the current text is not empty
    //and is current text equals previous search text.
    //if above consitions are true don't insert into combo history
    //otherwise insert. This doesn't stop from combo box containing same texts and multiple places
    //becaseu it doesn't check whole list of texts
    //if more than 10 elments exists in the combo box delete it as well
    CString token=string.Tokenize(",",curPos).Trim();
    n=m_edtNameCtrl.GetLBTextLen(0);
    n=n==-1?1:n;
    m_edtNameCtrl.GetLBText(0,lbText.GetBuffer(n));
    if( token!="" && lbText!=token) m_edtNameCtrl.AddString(token);
    //if (m_edtNameCtrl.GetLBTextLen(10)!=CB_ERR) m_edtNameCtrl.DeleteString(10);


    token=string.Tokenize(",",curPos).Trim();
    n=m_edtRoleNameCtrl.GetLBTextLen(0);
    n=n==-1?1:n;
    m_edtRoleNameCtrl.GetLBText(0,lbText.GetBuffer(n));
    if( token!="" && lbText!=token) m_edtRoleNameCtrl.AddString(token);
    //if (m_edtRoleNameCtrl.GetLBTextLen(10)!=CB_ERR) m_edtRoleNameCtrl.DeleteString(10);

    token=string.Tokenize(",",curPos).Trim();
    n=m_edtKindNameCtrl.GetLBTextLen(0);
    n=n==-1?1:n;
    m_edtKindNameCtrl.GetLBText(0,lbText.GetBuffer(n));
    if( token!="" && lbText!=token) m_edtKindNameCtrl.AddString(token);
    //if (m_edtKindNameCtrl.GetLBTextLen(10)!=CB_ERR) m_edtKindNameCtrl.DeleteString(10);

    token=string.Tokenize(",",curPos).Trim();
    n=m_edtAttrNameCtrl.GetLBTextLen(0);
    n=n==-1?1:n;
    m_edtAttrNameCtrl.GetLBText(0,lbText.GetBuffer(n));
    if( token!="" && lbText!=token) m_edtAttrNameCtrl.AddString(token);
    //if (m_edtAttrNameCtrl.GetLBTextLen(10)!=CB_ERR) m_edtAttrNameCtrl.DeleteString(10);

    token=string.Tokenize(",",curPos).Trim();
    n=m_edtNameCtrl2.GetLBTextLen(0);
    n=n==-1?1:n;
    m_edtNameCtrl2.GetLBText(0,lbText.GetBuffer(n));
    if( token!="" && lbText!=token) m_edtNameCtrl2.AddString(token);
    //if (m_edtNameCtrl2.GetLBTextLen(10)!=CB_ERR) m_edtNameCtrl2.DeleteString(10);

    token=string.Tokenize(",",curPos).Trim();
    n=m_edtRoleNameCtrl2.GetLBTextLen(0);
    n=n==-1?1:n;
    m_edtRoleNameCtrl2.GetLBText(0,lbText.GetBuffer(n));
    if( token!="" && lbText!=token) m_edtRoleNameCtrl2.AddString(token);
    //if (m_edtRoleNameCtrl2.GetLBTextLen(10)!=CB_ERR) m_edtRoleNameCtrl2.DeleteString(10);

    token=string.Tokenize(",",curPos).Trim();
    n=m_edtKindNameCtrl2.GetLBTextLen(0);
    n=n==-1?1:n;
    m_edtKindNameCtrl2.GetLBText(0,lbText.GetBuffer(n));
    if( token!="" && lbText!=token) m_edtKindNameCtrl2.AddString(token);
    //if (m_edtKindNameCtrl2.GetLBTextLen(10)!=CB_ERR) m_edtKindNameCtrl2.DeleteString(10);

    token=string.Tokenize(",",curPos).Trim();
    n=m_edtAttributeCtrl2.GetLBTextLen(0);
    n=n==-1?1:n;
    m_edtAttributeCtrl2.GetLBText(0,lbText.GetBuffer(n));
    if( token!="" && lbText!=token) m_edtAttributeCtrl2.AddString(token);
    //if (m_edtAttributeCtrl2.GetLBTextLen(10)!=CB_ERR) m_edtAttributeCtrl2.DeleteString(10);

    //Once added make sure that the combo box doesn' exceed more than 10 items


    UpdateData(FALSE);    

}

void CSearchDlg::SearchResults()
{
    CSearchCtrl *TheCtrl = GetCtrl();
    CComPtr<IMgaProject> ccpProject = TheCtrl->GetProject();
    m_pgsSearch.ShowWindow(SW_RESTORE);
    TheCtrl->BeginTransaction();

    CComPtr<IMgaObjects> ccpObjectsInTerr = TheCtrl->PutInMyTerritory( TheCtrl->GetScopedL());
    CComPtr<IMgaFCOs> new_results;
    COMTHROW(new_results.CoCreateInstance(L"Mga.MgaFCOs"));;
    CInput inp;
    inp.GetInput(m_edtName,m_edtRoleName,m_edtKindName,m_edtAttrName,m_edtName2,m_edtRoleName2,m_edtKindName2,m_edtAttribute2,m_edtAttrValue,
        m_chkMod,m_chkAtom,m_chkRef,m_chkSet,m_chkFullWord,NULL,0,m_chkMatchCase,m_scope,m_radioLogical
        );

    CSearch searchGME(inp);
    searchGME.SearchResults(results,new_results,&m_pgsSearch);
    results=new_results;
    m_pgsSearch.ShowWindow(SW_HIDE);
    m_pgsSearch.SetPos(1);
    DisplayResults();
    TheCtrl->CommitTransaction();


}

//Called when vertical scroll occurs

void CSearchDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* /*pScrollBar*/)
{
    int oldPos = v_scrollPos;

    switch(nSBCode)
    {
    case SB_TOP:
        v_scrollPos = 0;
        break;
    case SB_BOTTOM:
        v_scrollPos = logicalHeight - pageHeight;
        break;
    case SB_ENDSCROLL:
        break;
    case SB_LINEDOWN:
        v_scrollPos += lineSize;
        break;
    case SB_LINEUP:
        v_scrollPos -= lineSize; 
        break;
    case SB_PAGEDOWN:
        v_scrollPos += pageSize;
        break;
    case SB_PAGEUP:
        v_scrollPos -= pageSize;
        break;
    case SB_THUMBPOSITION:
    case SB_THUMBTRACK:
        v_scrollPos = nPos;
        break;
    }

    if (v_scrollPos > (logicalHeight - pageHeight + 1))
        v_scrollPos = (logicalHeight - pageHeight + 1);
    if (v_scrollPos < 0)
        v_scrollPos = 0;

    ScrollWindow(0, oldPos - v_scrollPos, NULL, NULL);
    SetScrollPos(SB_VERT, v_scrollPos,true);

    //CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

//called when horizontal scroll occurs

void CSearchDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* /*pScrollBar*/)
{
    int oldPos = h_scrollPos;

    switch(nSBCode)
    {
    case SB_TOP:
        h_scrollPos = 0;
        break;
    case SB_BOTTOM:
        h_scrollPos = logicalWidth - pageWidth;
        break;
    case SB_ENDSCROLL:
        break;
    case SB_LINEDOWN:
        h_scrollPos += lineSize;
        break;
    case SB_LINEUP:
        h_scrollPos -= lineSize; 
        break;
    case SB_PAGEDOWN:
        h_scrollPos += pageSize;
        break;
    case SB_PAGEUP:
        h_scrollPos -= pageSize;
        break;
    case SB_THUMBPOSITION:
    case SB_THUMBTRACK:
        h_scrollPos = nPos;
        break;
    }

    if (h_scrollPos > (logicalWidth - pageWidth + 1))
        h_scrollPos = (logicalWidth - pageWidth + 1);
    if (h_scrollPos < 0)
        h_scrollPos = 0;

    ScrollWindow(oldPos - h_scrollPos,0,  NULL, NULL);
    SetScrollPos(SB_HORZ, h_scrollPos,true);

    //CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}



CSearchDlg::~CSearchDlg()
{
}

