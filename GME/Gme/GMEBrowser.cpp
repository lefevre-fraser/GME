// GMEBrowser.cpp : implementation file
//

#include "stdafx.h"
#include "GMEApp.h"
#include "GMEstd.h"
#include "mainfrm.h"
#include "GMEDoc.h"
#include "GMEView.h"
#include "sizecbar.h"
#include "GMEBrowser.h"
#include "guimeta.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



#define MULTIPLE_OPEN_VIEW

/////////////////////////////////////////////////////////////////////////////
// CGMEBrowser dialog


CGMEBrowser *CGMEBrowser::theInstance = 0;

CGMEBrowser::CGMEBrowser(CWnd* /*pParent =NULL*/)
{
	//{{AFX_DATA_INIT(CGMEBrowser)
	//}}AFX_DATA_INIT
	VERIFY(theInstance == 0);
	theInstance = this;
}


void CGMEBrowser::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CGMEBrowser)
	DDX_Control(pDX, IDC_GME_ACTIVE_BROWSER_CTRL, m_GMEActiveBrowser);
	//}}AFX_DATA_MAP
}

void CGMEBrowser::CloseProject()
{
	m_GMEActiveBrowser.CloseCurrentProject();
}

bool CGMEBrowser::GetSelectedItems(CComPtr<IMgaObjects> &items)
{
	LPUNKNOWN lpSelObjs = m_GMEActiveBrowser.GetSelectedMgaObjects();
	CComQIPtr<IMgaObjects> objs( lpSelObjs);
	long cnt = 0;
	if( objs) COMTHROW( objs->get_Count( &cnt));
	if( cnt > 0)
		items = objs;

	return cnt > 0;
}

//#pragma warning ( disable : 4100 ) // Unreferenced formal param
bool CGMEBrowser::GetSelectedItem(CComPtr<IMgaObject>&)
{
	HRESULT hr = S_OK;

	return hr == S_OK;
}
//#pragma warning ( default : 4100 ) // Unreferenced formal param

void CGMEBrowser::SetProject(CComPtr<IMgaProject> mgaProject)
{
	m_GMEActiveBrowser.SetCurrentProject(mgaProject);
}

void CGMEBrowser::RefreshAll()
{
	m_GMEActiveBrowser.RefreshAll();
}

void CGMEBrowser::ShowObject(LPUNKNOWN selected) 
{
	if (CGMEDoc::theInstance) {
		CGMEDoc::theInstance->ShowObject(selected);
	}
}

void CGMEBrowser::ShowObjectInParent( LPUNKNOWN selected)
{
	if (CGMEDoc::theInstance) {
		CGMEDoc::theInstance->ShowObject(selected, true);
	}
}

void CGMEBrowser::ShowFindDlg()
{
	if( CGMEDoc::theInstance && CMainFrame::theInstance)
		CMainFrame::theInstance->ShowFindDlg();
}

void CGMEBrowser::ShowObjInsp()
{
	if( CGMEDoc::theInstance && CMainFrame::theInstance && CGMEObjectInspector::theInstance)
	{
		HWND hwnd = CGMEObjectInspector::theInstance->GetSafeHwnd();
		if( hwnd) ::SetFocus( hwnd);
	}
}

void CGMEBrowser::CycleObjInsp( VARIANT_BOOL frwd)
{
	if( CGMEObjectInspector::theInstance)
	{
		CGMEObjectInspector::theInstance->CyclePanel( frwd);
	}
}

void CGMEBrowser::FocusItem(BSTR Id)
{
	m_GMEActiveBrowser.FocusItem(Id);
}

BEGIN_MESSAGE_MAP(CGMEBrowser, CSizingControlBar)
	//{{AFX_MSG_MAP(CGMEBrowser)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGMEBrowser message handlers

int CGMEBrowser::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CSizingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	if(!m_GMEActiveBrowser.Create("ttt",WS_CHILD | WS_VISIBLE,CRect(0,0,100,100),this,IDC_GME_ACTIVE_BROWSER_CTRL))
		return -1;

	m_szMin = CSize(200,200);
    m_szFloat = CSize(350,600); 
	m_szHorz = CSize(300,200);
    m_szVert = CSize(250,300);
	
	return 0;
}

void CGMEBrowser::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	CSizingControlBar::OnUpdateCmdUI(pTarget, bDisableIfNoHndler);

	UpdateDialogControls(pTarget, bDisableIfNoHndler);
}


void CGMEBrowser::OnSize(UINT nType, int cx, int cy) 
{
	CSizingControlBar::OnSize(nType, cx, cy);
	
	CRect rc;
	GetClientRect(rc);	
	m_GMEActiveBrowser.MoveWindow(rc);
}

BEGIN_EVENTSINK_MAP(CGMEBrowser, CSizingControlBar)
    //{{AFX_EVENTSINK_MAP(CGMEBrowser)
	ON_EVENT(CGMEBrowser, IDC_GME_ACTIVE_BROWSER_CTRL, 1 /* DblClickMgaObject */, OnDblClickMgaObjectGmeActiveBrowserCtrl, VTS_UNKNOWN)
	ON_EVENT(CGMEBrowser, IDC_GME_ACTIVE_BROWSER_CTRL, 2 /* ShowAttributes */, OnShowAttributesGmeActiveBrowserCtrl, VTS_UNKNOWN)
	ON_EVENT(CGMEBrowser, IDC_GME_ACTIVE_BROWSER_CTRL, 3 /* ShowPreferences */, OnShowPreferencesGmeActiveBrowserCtrl, VTS_UNKNOWN)
	ON_EVENT(CGMEBrowser, IDC_GME_ACTIVE_BROWSER_CTRL, 4 /* ShowProperties */, OnShowPropertiesGmeActiveBrowserCtrl, VTS_NONE)
	ON_EVENT(CGMEBrowser, IDC_GME_ACTIVE_BROWSER_CTRL, 5 /* ClickMgaObject */, OnClickMgaObjectGmeActiveBrowserCtrl, VTS_UNKNOWN)
	ON_EVENT(CGMEBrowser, IDC_GME_ACTIVE_BROWSER_CTRL, 6 /* ShowInParentMgaObject */, OnShowInParentMgaObjectGmeActiveBrowserCtrl, VTS_UNKNOWN)
	ON_EVENT(CGMEBrowser, IDC_GME_ACTIVE_BROWSER_CTRL, 7 /* RootFolderNameChanged */, OnRootFolderNameChangedGmeActiveBrowserCtrl, VTS_NONE)
	ON_EVENT(CGMEBrowser, IDC_GME_ACTIVE_BROWSER_CTRL, 8 /* ShowFindDlg */, OnShowFindDlgGmeActiveBrowserCtrl, VTS_NONE)
	ON_EVENT(CGMEBrowser, IDC_GME_ACTIVE_BROWSER_CTRL, 9 /* ShowObjInspDlg */, OnShowObjInspDlgGmeActiveBrowserCtrl, VTS_NONE)
	ON_EVENT(CGMEBrowser, IDC_GME_ACTIVE_BROWSER_CTRL, 10 /*CycleObjInsp*/ , OnCycleObjsInspGmeActiveBrowserCtrl, VTS_BOOL)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CGMEBrowser::OnDblClickMgaObjectActivebrowserCtlr1(LPUNKNOWN selected) 
{
	ShowObject(selected);
}

void CGMEBrowser::OnCRonObjectActivebrowserCtlr1(LPUNKNOWN selected) 
{
	ShowObject(selected);
}

BOOL CGMEBrowser::PreTranslateMessage(MSG* pMsg) 
{
	// New browser is not a dialog, it's a property sheet, baby...
	::TranslateMessage(pMsg);
	::DispatchMessage(pMsg);
	return TRUE;
}

void CGMEBrowser::ShowAttrPref(bool isAttr, LPUNKNOWN selected) {

	CComPtr<IUnknown> sunk = selected;

#ifdef GME_OLD_ATTRIBUTE_PANEL

	CGuiMetaFco *guiMeta = NULL;
	if(sunk == 0)
		return;

	CComPtr<IMgaFCO> fco;
	
	if (!theApp.mgaProject) 
		return;
	
	
	if (SUCCEEDED(sunk.QueryInterface(&fco))) {
		long status;
		COMTHROW(theApp.mgaProject->get_ProjectStatus(&status));
		bool inTrans = (status & 0x08L) != 0;
		CComPtr<IMgaTerritory> terr;
		if (!inTrans) {
			try {
				COMTHROW(theApp.mgaProject->CreateTerritory(NULL, &terr));
				COMTHROW(theApp.mgaProject->BeginTransaction(terr));
			}
			catch (hresult_exception e) {
				return;
			}
		}

		try {
			CComPtr<IMgaMetaFCO> metaFco;
			COMTHROW(fco->get_Meta(&metaFco));
			VERIFY(metaFco);
			metaref_type metaref;
			COMTHROW(metaFco->get_MetaRef(&metaref));
			guiMeta = CGuiMetaProject::theInstance->GetGuiMetaFco(metaref);


		}
		catch (hresult_exception e) {
			if (!inTrans) {
				theApp.mgaProject->AbortTransaction();
			}
		}
		if (!inTrans) {
			theApp.mgaProject->CommitTransaction();
		}

	}
	if (guiMeta) {
		CMainFrame::theInstance->GetPreferencePanel().SetFco(fco,&(guiMeta->attrs));	
		if (isAttr) {
			CMainFrame::theInstance->GetAttributePanel().ShowAttrDlg();
		}
		else {
			CMainFrame::theInstance->GetPreferencePanel().ShowPrefDlg();
		}
	}

#else
// Tih@mer Object Inspector /////////////////////////////////////////////////////////		
	/* Converting single selection to multiple 
	CComPtr<IMgaObjects> ccpSelectedObjects;
	COMTHROW(ccpSelectedObjects.CoCreateInstance(L"Mga.MgaObjects"));
	CComPtr<IMgaObject>ccpMgaObject(fco);
	ccpSelectedObjects->Append(ccpMgaObject);
	CGMEObjectInspector::theInstance->SetFCOs(ccpSelectedObjects);
	*/

	
	SetCurrObject(selected);
	CGMEObjectInspector::theInstance->ShowPanel(!isAttr);

#endif


/////////////////////////////////////////////////////////////////////////////////////


}

void CGMEBrowser::SetCurrObject(LPUNKNOWN pMgaObject)
{
	CComPtr<IUnknown> sunk = pMgaObject;
	LPUNKNOWN pUnknown=m_GMEActiveBrowser.GetSelectedMgaObjects();
	CComQIPtr<IMgaObjects> ccpSelectedObjects(pUnknown);
	pUnknown->Release();
	ASSERT(ccpSelectedObjects!=NULL);
//	CComQIPtr<IMgaObjects> ccpSelectedObjects(pMgaObject);
	CGMEObjectInspector::theInstance->SetObjects(ccpSelectedObjects);
}

void CGMEBrowser::OnShowAttributesActivebrowserctrl1(LPUNKNOWN object) 
{
	ShowAttrPref(true, object);
}

void CGMEBrowser::OnShowPreferencesActivebrowserctrl1(LPUNKNOWN object) 
{
	ShowAttrPref(false, object);
}

void CGMEBrowser::OnDblClickMgaObjectGmeActiveBrowserCtrl(LPUNKNOWN pMgaObject) 
{
	ShowObject(pMgaObject);
//	ShowAttrPref(true, pMgaObject);
	
}

void CGMEBrowser::OnShowAttributesGmeActiveBrowserCtrl(LPUNKNOWN pMgaObject) 
{
	ShowAttrPref(true, pMgaObject);
	
}

void CGMEBrowser::OnShowPreferencesGmeActiveBrowserCtrl(LPUNKNOWN pMgaObject) 
{
	ShowAttrPref(false, pMgaObject);
	
}

void CGMEBrowser::OnShowPropertiesGmeActiveBrowserCtrl() 
{
	
	LPUNKNOWN pUnknown=m_GMEActiveBrowser.GetSelectedMgaObjects();
	CComQIPtr<IMgaObjects> ccpSelectedObjects(pUnknown);
	pUnknown->Release();
	ASSERT(ccpSelectedObjects!=NULL);
	CGMEObjectInspector::theInstance->SetObjects(ccpSelectedObjects);

	CGMEObjectInspector::theInstance->ShowPanel(2);
	
}

void CGMEBrowser::OnClickMgaObjectGmeActiveBrowserCtrl(LPUNKNOWN pMgaObject) 
{
	SetCurrObject(pMgaObject);
}

void CGMEBrowser::OnShowInParentMgaObjectGmeActiveBrowserCtrl(LPUNKNOWN pMgaObject) 
{
	ShowObjectInParent(pMgaObject);
}

void CGMEBrowser::OnShowFindDlgGmeActiveBrowserCtrl()
{
	ShowFindDlg();
}

void CGMEBrowser::OnShowObjInspDlgGmeActiveBrowserCtrl()
{
	ShowObjInsp();
}

void CGMEBrowser::OnCycleObjsInspGmeActiveBrowserCtrl(VARIANT_BOOL frwd)
{
	CycleObjInsp( frwd);
}

void CGMEBrowser::OnRootFolderNameChangedGmeActiveBrowserCtrl()
{
	theApp.UpdateProjectName();
}
