// SearchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Search.h"
#include "SearchDlg.h"
#include "SearchCtl.h"
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
, m_edtNameSecond(_T(""))
, m_edtRoleNameSecond(_T(""))
, m_edtKindNameSecond(_T(""))
, m_edtAttributeSecond(_T(""))
, m_radioScope(0)
, m_searchResults(FALSE)
, m_radioLogical(0)
, m_edtNameFirst( _T(""))
, m_edtKindNameFirst( _T(""))
, m_edtRoleNameFirst( _T(""))
, m_edtAttributeFirst( _T(""))
, m_edtAttrValue ( _T(""))
, m_chkAtom(TRUE)
, m_chkFullWord(FALSE)
, m_chkMod(TRUE)
, m_chkRef (TRUE)
, m_chkSet(TRUE)
, m_chkLocate(FALSE)
, m_chkMatchCase(TRUE)

{
    //create an empty IMgaFCOs list. it gets filled by the searchbutton
    //and emptied by RemoveAll(), cleaned up by RemoveZombies()
    COMTHROW(results.CoCreateInstance(L"Mga.MgaFCOs"));
}

void CSearchDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CSearchDlg)
    DDX_Control(pDX, IDC_CHECK_CASESENS, m_chkMatchCaseCtrl);
    DDX_Control(pDX, IDC_CHECKFULLWORD, m_chkFullWordCtrl);
    DDX_Control(pDX, IDC_EDITNAME, m_edtNameCtrlFirst);
    DDX_Control(pDX, IDC_EDITKIND, m_edtKindNameCtrlFirst);
    DDX_Control(pDX, IDC_EDITROLE, m_edtRoleNameCtrlFirst);
    DDX_Control(pDX, IDC_EDITATTRNAME, m_edtAttributeCtrlFirst);
    DDX_Control(pDX, IDC_CHECKREF, m_chkRefCtrl);
    DDX_Control(pDX, IDC_PROGRESSSEARCH, m_pgsSearch);
    DDX_Control(pDX, IDC_CHECKATM, m_chkAtomCtrl);
    DDX_Control(pDX, IDC_CHECKSET, m_chkSetCtrl);
    DDX_Control(pDX, IDC_CHECKMOD, m_chkModCtrl);
    DDX_Control(pDX, IDC_BUTTON_GO, m_btnGO);
    DDX_Control(pDX, IDC_LISTRESULTS, m_lstResults);
    DDX_Text(pDX, IDC_EDITNAME, m_edtNameFirst);
    DDX_Text(pDX, IDC_EDITKIND, m_edtKindNameFirst);
    DDX_Text(pDX, IDC_EDITROLE, m_edtRoleNameFirst);
    DDX_Text(pDX, IDC_EDITATTRNAME, m_edtAttributeFirst);
    DDX_Check(pDX, IDC_CHECKATM, m_chkAtom);
    DDX_Check(pDX, IDC_CHECKFULLWORD, m_chkFullWord);
    DDX_Check(pDX, IDC_CHECKMOD, m_chkMod);
    DDX_Check(pDX, IDC_CHECKREF, m_chkRef);
    DDX_Check(pDX, IDC_CHECKSET, m_chkSet);
    DDX_Check(pDX, IDC_CHECK_CASESENS, m_chkMatchCase);
    //DDX_ValidateInp(pDX, IDC_EDITNAME, m_edtNameFirst);
    //DDX_ValidateInp(pDX, IDC_EDITKIND, m_edtKindNameFirst);
    //DDX_ValidateInp(pDX, IDC_EDITROLE, m_edtRoleNameFirst);
    //DDX_ValidateInp(pDX, IDC_EDITATTRNAME, m_edtAttributeFirst);
    DDX_Text(pDX, IDC_EDITNAME2, m_edtNameSecond);
    DDX_Text(pDX, IDC_EDITROLE2, m_edtRoleNameSecond);
    DDX_Text(pDX, IDC_EDITKIND2, m_edtKindNameSecond);
    DDX_Text(pDX, IDC_EDITATTRVALU2, m_edtAttributeSecond);
    DDX_Control(pDX, IDC_RADIOAND, m_logicalGrp);
    //DDX_Control(pDX, IDC_PREV_SRCH, m_prevSearches);
    DDX_Radio(pDX, IDC_ENTIRESCOPE2, m_radioScope);
    DDX_Check(pDX, IDC_CHECK_RESULTS, m_searchResults);
    DDX_Radio(pDX, IDC_RADIOAND, m_radioLogical);
    DDX_Control(pDX, IDC_EDITNAME2, m_edtNameCtrlSecond);
    DDX_Control(pDX, IDC_EDITROLE2, m_edtRoleNameCtrlSecond);
    DDX_Control(pDX, IDC_EDITKIND2, m_edtKindNameCtrlSecond);
    DDX_Control(pDX, IDC_EDITATTRVALU2, m_edtAttributeCtrlSecond);
    DDX_Control(pDX, IDC_TREE_SEARCH_HISTORY, m_treeSearchHistory);
}

BEGIN_MESSAGE_MAP(CSearchDlg, CDialog)
    //{{AFX_MSG_MAP(CSearchDlg)
    ON_BN_CLICKED(IDC_BUTTON_GO, OnButtonGo)
    ON_NOTIFY(NM_CLICK, IDC_LISTRESULTS, OnClickListResults)
    ON_NOTIFY(NM_DBLCLK, IDC_LISTRESULTS, OnDblclkListResults)
    //}}AFX_MSG_MAP
    ON_WM_SIZE()
    ON_WM_SIZING()
    ON_WM_VSCROLL()
    ON_WM_HSCROLL()
    ON_WM_KEYDOWN()
    ON_NOTIFY(NM_DBLCLK, IDC_TREE_SEARCH_HISTORY, &CSearchDlg::OnNMDblclkTreeSearchHistory)
END_MESSAGE_MAP()

BOOL CSearchDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_lstResults.InsertColumn(1, "Object", LVCFMT_LEFT, 100, 1);
    m_lstResults.InsertColumn(2, "Path", LVCFMT_LEFT, 210, 2);
    m_lstResults.InsertColumn(3, "Type", LVCFMT_LEFT, 95, 3);
    m_lstResults.InsertColumn(4, "Value", LVCFMT_LEFT, 210, 4);
    m_lstResults.SetExtendedStyle(m_lstResults.GetExtendedStyle()|LVS_EX_FULLROWSELECT);

    specialSearchFCO = NULL;

    m_pgsSearch.SetRange(1,16000);
    m_pgsSearch.SetStep(1);

    //load search history from registry
    LoadSearchHistory();

    return true;
}

/////////////////////////////////////////////////////////////////////////////
// CSearchDlg message handlers


/////////////////////////////////////////////////////////////////////////////
//  These functions should be implemented to work with CSearchCtl

// Must remove all search result
void CSearchDlg::RemoveAll()
{
    results = NULL;
    COMTHROW(results.CoCreateInstance(L"Mga.MgaFCOs"));
    DisplayResults();
}

// Must remove results belong to zombie objects
void CSearchDlg::RemoveZombies()
{
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
        }
    }

    TheCtrl->CommitTransaction();
}

// Enable search 
//enables all the  controls in the search dialog
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

//disables all the  controls in the search dialog
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
        if(m_searchResults)
        {
            SearchResults();
            CreateSearchHistory();
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
        inp.GetInput(m_edtNameFirst,m_edtRoleNameFirst,m_edtKindNameFirst,m_edtAttributeFirst,m_edtNameSecond,m_edtRoleNameSecond,m_edtKindNameSecond,m_edtAttributeSecond,m_edtAttrValue,
            m_chkMod,m_chkAtom,m_chkRef,m_chkSet,m_chkFullWord,NULL,0,m_chkMatchCase,m_radioScope,m_radioLogical);


        CSearch searchGME(inp);
        searchGME.Search(rootInput, ccpObjectsInTerr, specialSearchFCO,results,&m_pgsSearch);
        //		AfxMessageBox("Finished Searching");

        DisplayResults();
        m_pgsSearch.ShowWindow(SW_HIDE);
        m_pgsSearch.SetPos(1);

        TheCtrl->CommitTransaction();
    }
    CreateSearchHistory();
    SaveSearchHistory();

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
    bool attr_value_to_be_shown = !m_edtAttrValue.IsEmpty() && !m_edtAttributeFirst.IsEmpty();

    //Hide the window so it doesn't waste time redrawing each time we add an item
    m_lstResults.ShowWindow(SW_HIDE);
    m_lstResults.DeleteAllItems();

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
                COMTHROW( MGACOLL_ITER->get_StrAttrByName( CComBSTR( m_edtAttributeFirst), &bstr));
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
    this->itemClicked(); *pResult = 0;
}

void CSearchDlg::OnDblclkListResults(NMHDR* pNMHDR, LRESULT* pResult) 
{
    this->itemDblClicked(); *pResult = 0;
}

void CSearchDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);
    const int bottomMargin = 10;
    if( cx >= 0 && cy >= 0 && m_lstResults.GetSafeHwnd()&& m_treeSearchHistory.GetSafeHwnd())
    {
        int bottomPos = (cy-bottomMargin)>0 ? (cy-bottomMargin):0;
        CRect rectResultsList; m_lstResults.GetWindowRect( &rectResultsList); ScreenToClient( &rectResultsList);
        rectResultsList.bottom= bottomPos;
        m_lstResults.SetWindowPos( NULL, rectResultsList.left, rectResultsList.top, rectResultsList.Width(), rectResultsList.Height(), SWP_NOMOVE|SWP_NOZORDER|SWP_SHOWWINDOW);

        CRect rectPrevSearches;
        m_treeSearchHistory.GetWindowRect(rectPrevSearches); ScreenToClient(rectPrevSearches);
        rectPrevSearches.bottom = bottomPos;
        m_treeSearchHistory.SetWindowPos(NULL, rectPrevSearches.left, rectPrevSearches.top, rectPrevSearches.Width(), 
            rectPrevSearches.Height(), SWP_NOMOVE|SWP_NOZORDER|SWP_SHOWWINDOW);
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

//save search history in registry
void CSearchDlg::SaveSearchHistory()
{
    CRegKey key;
    std::stringstream stream;

    //delete the key first and save new one
    if(key.Open(HKEY_CURRENT_USER,_TEXT("Software\\GME"),KEY_ALL_ACCESS)==ERROR_SUCCESS)
    {
        key.DeleteSubKey("Search");
    }
    key.Create(HKEY_CURRENT_USER,_TEXT("Software\\GME\\Search"));
    HTREEITEM hItem=m_treeSearchHistory.GetRootItem();
    int i=0;
    while(hItem && i<10)
    {
        //the search history are stored as search0, search1 etc 
        //form key string
        stream<<"search"<<i;

        //set the key and the value
        key.SetStringValue(stream.str().c_str(), m_treeSearchHistory.GetItemText(hItem));

        //clear the string stream
        stream.str("");

        //get next item to be saved
        hItem=m_treeSearchHistory.GetNextSiblingItem(hItem);
        i++;

    }
    key.Close();
}

void CSearchDlg::LoadSearchHistory()
{
    CRegKey key;
    std::string strKeyName;
    std::stringstream stream(strKeyName);
    ULONG length;
    CHAR strValue[1000];
    //CString strValue;

    int i=0;
    if(key.Open(HKEY_CURRENT_USER,_TEXT("Software\\GME\\Search"),KEY_ALL_ACCESS)==ERROR_SUCCESS)
    {
        while(i<10)
        {
            //form the key
            strKeyName="search";
            stream<<int(i);

            //buffer size
            length=sizeof(strValue);

            strKeyName+=stream.str();

            //query the key
            if(key.QueryStringValue(strKeyName.c_str(),strValue,&length)!=ERROR_SUCCESS)
                break;

            //insert it in the tree control and combo boxes
            InsertHistory(strValue);
            stream.str("");
            i++;
        }
    }
}


//create search history text and insert it intt the tree control
//called after the user clicks the search button and results are available

void CSearchDlg::CreateSearchHistory()
{
    //variable to store if criteria is empty
    bool firstCriteriaEmpty=false,secondCriteriaEmpty=false;

    InsertTextToControl(m_edtNameFirst,m_edtNameCtrlFirst);
    InsertTextToControl(m_edtRoleNameFirst,m_edtKindNameCtrlFirst);
    InsertTextToControl(m_edtKindNameFirst,m_edtKindNameCtrlFirst);
    InsertTextToControl(m_edtAttributeFirst,m_edtAttributeCtrlFirst);

    InsertTextToControl(m_edtNameSecond,m_edtNameCtrlSecond);
    InsertTextToControl(m_edtRoleNameSecond,m_edtRoleNameCtrlSecond);
    InsertTextToControl(m_edtKindNameFirst,m_edtKindNameCtrlSecond);
    InsertTextToControl(m_edtAttributeSecond,m_edtAttributeCtrlSecond);

    //read the root item
    CString strFirstElement=m_treeSearchHistory.GetItemText(m_treeSearchHistory.GetRootItem());
    //insert an dummy item to the tree once the processing of search text is complete
    //it will be renamed to appropriate one
    HTREEITEM hItem=m_treeSearchHistory.InsertItem("Dummy",NULL,TVI_FIRST);

    CString strSearch;

    if(m_edtNameFirst!="" || m_edtKindNameFirst!="" || m_edtRoleNameFirst!="" || m_edtAttributeFirst!="")
    {
        HTREEITEM hFirstCriteria=m_treeSearchHistory.InsertItem("First Search Criteria",hItem,TVI_FIRST);
        //First criteria
        PrepareHistoryString("Name",m_edtNameFirst,hFirstCriteria,strSearch);
        PrepareHistoryString("Role",m_edtRoleNameFirst,hFirstCriteria,strSearch);
        PrepareHistoryString("Kind",m_edtKindNameFirst,hFirstCriteria,strSearch);
        PrepareHistoryString("Attribute",m_edtAttributeFirst,hFirstCriteria,strSearch);
    }
    else
    {
        firstCriteriaEmpty=true;
    }


    //search criteria separator

    //strSearch.Append(":");
    if(m_edtNameSecond!="" || m_edtKindNameSecond!="" || m_edtRoleNameSecond!="" || m_edtAttributeSecond!="")
    {
        HTREEITEM hSecondCriteria=m_treeSearchHistory.InsertItem("Second Search Criteria",hItem,TVI_LAST);

        //second criteria
        PrepareHistoryString("Second Name",m_edtNameSecond,hSecondCriteria,strSearch);
        PrepareHistoryString("Second Role",m_edtRoleNameSecond,hSecondCriteria,strSearch);
        PrepareHistoryString("Second Kind",m_edtKindNameSecond,hSecondCriteria,strSearch);
        PrepareHistoryString("Second Attribute",m_edtAttributeSecond,hSecondCriteria,strSearch);
    }
    else
    {
        secondCriteriaEmpty=true;
    }

    //others
    HTREEITEM hOtherCriteria=m_treeSearchHistory.InsertItem("Others",hItem,TVI_LAST);
    PrepareHistoryString("Logical",m_radioLogical,hOtherCriteria,strSearch);
    PrepareHistoryString("Model",m_chkMod,hOtherCriteria,strSearch);
    PrepareHistoryString("Atom",m_chkAtom,hOtherCriteria,strSearch);
    PrepareHistoryString("Set",m_chkSet,hOtherCriteria,strSearch);
    PrepareHistoryString("Reference",m_chkRef,hOtherCriteria,strSearch);
    PrepareHistoryString("Case",m_chkMatchCase,hOtherCriteria,strSearch);
    PrepareHistoryString("WholeWord",m_chkFullWord,hOtherCriteria,strSearch);
    PrepareHistoryString("Scope",m_radioScope,hOtherCriteria,strSearch);
    PrepareHistoryString("Results",m_searchResults,hOtherCriteria,strSearch);

    m_treeSearchHistory.SetItemText(hItem,strSearch);

    //Get first element from the previous history or check if both the criteria
    //are empty, if they are same the history is not added
    if(strFirstElement==strSearch || (firstCriteriaEmpty && secondCriteriaEmpty))
    {
        m_treeSearchHistory.DeleteItem(hItem);
        return;
    }

    //for now it allows keeping unlimited history while the program is running
    //once the program is reloaded only 10 history items are allowed
}

//this is used for inserting history text to combo boxes
//it first checks if the first element in the combobox is same
//as the element to be inserted, if not it adds to the combo comtrol

void CSearchDlg::InsertTextToControl(CString& strNewTerm,CComboBox& control)
{
    CString strTerm;
    int n=control.GetLBTextLen(0);
    n=n==-1?1:n;
    control.GetLBText(0,strTerm.GetBuffer(n));
    if (strNewTerm!="" && strNewTerm!=strTerm) control.InsertString(0,strNewTerm);
}

//prepares history string it is of the form
//<name>=<search term/text>
//combined with ',' for a seacrh criteria, search criterias are separated by ':'
//it also adds child to the tree control
void CSearchDlg::PrepareHistoryString(const CString &strCriteriaName,CString & strSearchValue,HTREEITEM hParent,CString &strSearch)
{
    CString strNameValue;
    if(strSearchValue.Trim()=="")
        return;
    if(strSearch.GetLength()>0)
        strSearch.Append(", ");

    strNameValue.Append(strCriteriaName);
    strNameValue.Append("=");
    strNameValue.Append("\"");
    strNameValue.Append(strSearchValue);
    strNameValue.Append("\"");

    strSearch.Append(strNameValue);

    m_treeSearchHistory.InsertItem(strNameValue,hParent,NULL);
}

void CSearchDlg::PrepareHistoryString(const CString &strCriteriaName,int & strSearchValue,HTREEITEM hParent,CString &strSearch)
{
    char buffer[10];
    _itoa(strSearchValue,buffer,10);
    PrepareHistoryString(strCriteriaName,CString(buffer),hParent,strSearch);

}


void CSearchDlg::InsertHistory(CString strHistory)
{
    //insert at the top of combobox

    // For each combobox control check if the current text is not empty
    //and is current text equals previous search text.
    //if above consitions are true don't insert into combo history
    //otherwise insert. This doesn't stop from combo box containing same texts and multiple places
    //becaseu it doesn't check whole list of texts
    //if more than 10 elments exists in the combo box delete it as well

    CString readValue;

    HTREEITEM hItem=m_treeSearchHistory.InsertItem("Dummy",NULL,TVI_LAST);
    HTREEITEM hFirstCriteria=m_treeSearchHistory.InsertItem("First Search Criteria",hItem,TVI_FIRST);
    HTREEITEM hSecondCriteria=m_treeSearchHistory.InsertItem("Second Search Criteria",hItem,TVI_LAST);
    HTREEITEM hOtherCriteria=m_treeSearchHistory.InsertItem("Other",hItem,TVI_LAST);

    CString strSearch;

    ReadHistoryValue("Name",strHistory,readValue);
    InsertTextToControl(readValue,m_edtNameCtrlFirst);
    PrepareHistoryString(CString("Name"),readValue,hFirstCriteria,strSearch);

    ReadHistoryValue("Role",strHistory,readValue);
    InsertTextToControl(readValue,m_edtRoleNameCtrlFirst);
    PrepareHistoryString(CString("Role"),readValue,hFirstCriteria,strSearch);

    ReadHistoryValue("Kind",strHistory,readValue);
    InsertTextToControl(readValue,m_edtKindNameCtrlFirst);
    PrepareHistoryString(CString("Kind"),readValue,hFirstCriteria,strSearch);

    ReadHistoryValue("Attribute",strHistory,readValue);
    InsertTextToControl(readValue,m_edtAttributeCtrlFirst);
    PrepareHistoryString(CString("Attribute"),readValue,hFirstCriteria,strSearch);

    //if no first search criteria items are there delete it
    int length=strSearch.GetLength();
    if(length==0)
        m_treeSearchHistory.DeleteItem(hFirstCriteria);

    //search criteria separator
    //strSearch.Append(":");

    ReadHistoryValue("Second Name",strHistory,readValue);
    InsertTextToControl(readValue,m_edtNameCtrlSecond);
    PrepareHistoryString(CString("Second Name"),readValue,hSecondCriteria,strSearch);

    ReadHistoryValue("Second Role",strHistory,readValue);
    InsertTextToControl(readValue,m_edtRoleNameCtrlSecond);
    PrepareHistoryString(CString("Second Role"),readValue,hSecondCriteria,strSearch);

    ReadHistoryValue("Second Kind",strHistory,readValue);
    InsertTextToControl(readValue,m_edtKindNameCtrlSecond);
    PrepareHistoryString(CString("Second Kind"),readValue,hSecondCriteria,strSearch);

    ReadHistoryValue("Second Attribute",strHistory,readValue);
    InsertTextToControl(readValue,m_edtAttributeCtrlSecond);
    PrepareHistoryString(CString("Second Attribute"),readValue,hSecondCriteria,strSearch);

    //check if second search criteria has been added
    length=strSearch.GetLength()-length;
    if(length==0)
         m_treeSearchHistory.DeleteItem(hSecondCriteria);


    ReadHistoryValue("Logical",strHistory,m_radioLogical);
    PrepareHistoryString("Logical",m_radioLogical,hOtherCriteria,strSearch);

    ReadHistoryValue("Model",strHistory,m_chkMod);
    PrepareHistoryString("Model",m_chkMod,hOtherCriteria,strSearch);

    ReadHistoryValue("Atom",strHistory,m_chkAtom);
    PrepareHistoryString("Atom",m_chkAtom,hOtherCriteria,strSearch);

    ReadHistoryValue("Set",strHistory,m_chkSet);
    PrepareHistoryString("Set",m_chkSet,hOtherCriteria,strSearch);

    ReadHistoryValue("Reference",strHistory,m_chkRef);
    PrepareHistoryString("Reference",m_chkRef,hOtherCriteria,strSearch);

    ReadHistoryValue("Case",strHistory,m_chkMatchCase);
    PrepareHistoryString("Case",m_chkMatchCase,hOtherCriteria,strSearch);

    ReadHistoryValue("WholeWord",strHistory,m_chkFullWord);
    PrepareHistoryString("WholeWord",m_chkFullWord,hOtherCriteria,strSearch);

    ReadHistoryValue("Scope",strHistory,m_radioScope);
    PrepareHistoryString("Scope",m_radioScope,hOtherCriteria,strSearch);

    ReadHistoryValue("Results",strHistory,m_searchResults);
    PrepareHistoryString("Results",m_searchResults,hOtherCriteria,strSearch);

    m_treeSearchHistory.SetItemText(hItem,strSearch);

    UpdateData(FALSE); 
}

//parse the search string to read a particular value
//first it looks for the criteria name
//when found takes the string after that as the value
//the quotes and commas are removed, 2 search criterias are differentiated by ':'
void CSearchDlg::ReadHistoryValue(const CString &strCriteriaName, CString &strHistory, CString &strValue)
{
    //clear the output string
    strValue="";
    CString strTemp(strCriteriaName);
    strTemp.Append("=");
    int indexText,indexComma;
    indexText=strHistory.Find(strTemp);
    if(indexText==-1) return;
    indexComma=strHistory.Find(",",indexText);
    indexComma=indexComma==-1?strHistory.GetLength():indexComma;
    int start=indexText + strTemp.GetLength()+1;
    strValue=strHistory.Mid(start,indexComma-start-1);

}

void CSearchDlg::ReadHistoryValue(const CString &strCriteriaName,CString &strHistory, int &value)
{
    CString strValue;
    ReadHistoryValue(strCriteriaName,strHistory,strValue);
    value=atoi(strValue.GetBuffer());
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
    inp.GetInput(m_edtNameFirst,m_edtRoleNameFirst,m_edtKindNameFirst,m_edtAttributeFirst,m_edtNameSecond,m_edtRoleNameSecond,m_edtKindNameSecond,m_edtAttributeSecond,m_edtAttrValue,
        m_chkMod,m_chkAtom,m_chkRef,m_chkSet,m_chkFullWord,NULL,0,m_chkMatchCase,m_radioScope,m_radioLogical
        );

    CSearch searchGME(inp);
    searchGME.SearchResults(results,new_results,&m_pgsSearch);
    results=new_results;
    m_pgsSearch.ShowWindow(SW_HIDE);
    m_pgsSearch.SetPos(1);
    DisplayResults();
    TheCtrl->CommitTransaction();
}

CSearchDlg::~CSearchDlg()
{
}

void CSearchDlg::OnNMDblclkTreeSearchHistory(NMHDR *pNMHDR, LRESULT *pResult)
{
    CString strSearchText;
    HTREEITEM hItem=m_treeSearchHistory.GetSelectedItem();
    HTREEITEM hParent=m_treeSearchHistory.GetParentItem(hItem);
    HTREEITEM hGrandParent=m_treeSearchHistory.GetParentItem(hParent);

    if(hGrandParent)
        strSearchText=m_treeSearchHistory.GetItemText(hGrandParent);
    else if(hParent)
        strSearchText=m_treeSearchHistory.GetItemText(hParent);
    else
        strSearchText=m_treeSearchHistory.GetItemText(hItem);

    //first search criteria
    ReadHistoryValue("Name",strSearchText,m_edtNameFirst);
    ReadHistoryValue("Role",strSearchText,m_edtRoleNameFirst);
    ReadHistoryValue("Kind",strSearchText,m_edtKindNameFirst);
    ReadHistoryValue("Attribute",strSearchText,m_edtAttributeFirst);

    //second search criteria
    ReadHistoryValue("Second Name",strSearchText,m_edtNameSecond);
    ReadHistoryValue("Second Role",strSearchText,m_edtRoleNameSecond);
    ReadHistoryValue("Second Kind",strSearchText,m_edtKindNameSecond);
    ReadHistoryValue("Second Attribute",strSearchText,m_edtAttributeSecond);

    //others ReadHistoryValue("Logical",strHistory,m_radioLogical);
    ReadHistoryValue("Model",strSearchText,m_chkMod);
    ReadHistoryValue("Atom",strSearchText,m_chkAtom);
    ReadHistoryValue("Set",strSearchText,m_chkSet);
    ReadHistoryValue("Reference",strSearchText,m_chkRef);
    ReadHistoryValue("Case",strSearchText,m_chkMatchCase);
    ReadHistoryValue("WholeWord",strSearchText,m_chkFullWord);
    ReadHistoryValue("Scope",strSearchText,m_radioScope);
    ReadHistoryValue("Results",strSearchText,m_searchResults);

    UpdateData(FALSE);    
    *pResult = 0;
}
