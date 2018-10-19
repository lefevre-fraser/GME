// HtmlCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "console.h"
#include "HtmlCtrl.h"
#include "ConsoleCtl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHtmlCtrl

IMPLEMENT_DYNAMIC(CHtmlCtrl, CHtmlView)


CHtmlCtrl::CHtmlCtrl()
{
	//{{AFX_DATA_INIT(CHtmlCtrl)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CHtmlCtrl::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHtmlCtrl)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHtmlCtrl, CHtmlView)
	//{{AFX_MSG_MAP(CHtmlCtrl)
	ON_WM_DESTROY()
	ON_WM_MOUSEACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHtmlCtrl diagnostics

#ifdef _DEBUG
//
// MFC manages/stores states in statically linked (small) stubs
// Also, it updates the current module state for window message dispatch
// In this case, message is sent to the hosted IE window (so the module state won't be changed to our DLL), 
// which calls CHtmlView through COM. For some reason CHtmlView does not update module state when called trhough COM, 
// and eventually it calls MFC functions (only this one in our case) which will not find the (correct) module state
//
void CHtmlCtrl::AssertValid() const
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
	CHtmlView::AssertValid();
}

void CHtmlCtrl::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHtmlCtrl message handlers

//////////////////
// Create control in same position as an existing static control with
// the same ID (could be any kind of control, really)
//
BOOL CHtmlCtrl::CreateFromStatic(UINT nID, CWnd* pParent)
{
	CStatic wndStatic;
	if (!wndStatic.SubclassDlgItem(nID, pParent))
		return FALSE;

	// Get static control rect, convert to parent's client coords.
	CRect rc;
	wndStatic.GetWindowRect(&rc);
	pParent->ScreenToClient(&rc);
	wndStatic.DestroyWindow();

	// create HTML control (CHtmlView)
	return Create(NULL,                  // class name
		NULL,                             // title
		(WS_CHILD | WS_VISIBLE ),         // style
		rc,                               // rectangle
		pParent,                          // parent
		nID,                              // control ID
		NULL);                            // frame/doc context not used
}

////////////////
// Override to avoid CView stuff that assumes a frame.
//
void CHtmlCtrl::OnDestroy()
{
	// This is probably unecessary since ~CHtmlView does it, but
	// safer to mimic CHtmlView::OnDestroy.
	/*if (m_pBrowserApp) {
		m_pBrowserApp->Release();
		m_pBrowserApp = NULL;
	}*/ //commented for vc7, Release its not a public member of IWebBrowser2
	// CWnd::OnDestroy(); // bypass CView doc/frame stuff
	__super::OnDestroy();
}

////////////////
// Override to avoid CView stuff that assumes a frame.
//
int CHtmlCtrl::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT msg)
{
	// bypass CView doc/frame stuff
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, msg);
}

//////////////////
// Override navigation handler to pass to "app:" links to virtual handler.
// Cancels the navigation in the browser, since app: is a pseudo-protocol.
//
void CHtmlCtrl::OnBeforeNavigate2( LPCTSTR lpszURL,
	DWORD nFlags,
	LPCTSTR lpszTargetFrameName,
	CByteArray& baPostedData,
	LPCTSTR lpszHeaders,
	BOOL* pbCancel )
{
	const TCHAR MGA_PROTOCOL[] = _T("mga:");
	int len = _tcslen(MGA_PROTOCOL);
	if (_tcsnicmp(lpszURL, MGA_PROTOCOL, len)==0) {
		OnMgaURL(lpszURL + len);
		*pbCancel = TRUE;
	}
}

void CHtmlCtrl::OnMgaURL(LPCTSTR lpszWhere)
{
	CWnd *wnd = GetParent();
	if (wnd->IsKindOf(RUNTIME_CLASS(CConsoleCtrl))) {
		CConsoleCtrl *ctrl = STATIC_DOWNCAST(CConsoleCtrl, wnd);
		ctrl->FireClickMGAID(lpszWhere);
	}
}

void CHtmlCtrl::OnDocumentComplete(LPCTSTR lpszURL)
{
	CWnd *wnd = GetParent();
	if (wnd->IsKindOf(RUNTIME_CLASS(CConsoleCtrl))) {
		CConsoleCtrl *ctrl = STATIC_DOWNCAST(CConsoleCtrl, wnd);
		ctrl->AddGMEToScript();
	}
}



HRESULT CExtendedHtmlControlSite::XInternetSecurityManager::ProcessUrlAction(
	/* [in] */ __RPC__in LPCWSTR pwszUrl,
	/* [in] */ DWORD dwAction,
	/* [size_is][out] */ __RPC__out_ecount_full(cbPolicy) BYTE *pPolicy,
	/* [in] */ DWORD cbPolicy,
	/* [unique][in] */ __RPC__in_opt BYTE *pContext,
	/* [in] */ DWORD cbContext,
	/* [in] */ DWORD dwFlags,
	/* [in] */ DWORD dwReserved)
{
	METHOD_PROLOGUE(CExtendedHtmlControlSite, InternetSecurityManager);
	CString url = pThis->m_pView->GetLocationURL();
	// allow e.g. <a href=\"javascript:(new ActiveXObject('shell.application')).... from trusted locations
	if (wcsncmp(url, L"file:", 5) == 0 ||
		wcsncmp(url, L"res:", 4) == 0 ||
		wcsncmp(url, L"about:", 6) == 0)
	{
		*(PDWORD)pPolicy = URLPOLICY_ALLOW;
		return S_OK;
	}
	return INET_E_DEFAULT_ACTION;
}





// the rest of this file is boilerplate

CExtendedHtmlControlSite::CExtendedHtmlControlSite(COleControlContainer* pContainer, CHtmlCtrl* pView)
	:COleControlSite(pContainer), m_pView(pView)
{
}

CExtendedHtmlControlSite::~CExtendedHtmlControlSite(void)
{
}

BEGIN_INTERFACE_MAP(CExtendedHtmlControlSite, COleControlSite)
	INTERFACE_PART(CExtendedHtmlControlSite, IID_IServiceProvider, ServiceProvider)
	INTERFACE_PART(CExtendedHtmlControlSite, IID_IInternetSecurityManager, InternetSecurityManager)
END_INTERFACE_MAP()


ULONG FAR EXPORT CExtendedHtmlControlSite::XServiceProvider::AddRef()
{
	METHOD_PROLOGUE(CExtendedHtmlControlSite, ServiceProvider)
		return pThis->ExternalAddRef();
}

ULONG FAR EXPORT CExtendedHtmlControlSite::XServiceProvider::Release()
{
	METHOD_PROLOGUE(CExtendedHtmlControlSite, ServiceProvider)
		return pThis->ExternalRelease();
}

HRESULT FAR EXPORT CExtendedHtmlControlSite::XServiceProvider::QueryInterface(REFIID riid,
	void** ppvObj)
{
	METHOD_PROLOGUE(CExtendedHtmlControlSite, ServiceProvider)
		HRESULT hr = (HRESULT)pThis->ExternalQueryInterface(&riid, ppvObj);
	return hr;
}

STDMETHODIMP CExtendedHtmlControlSite::XServiceProvider::QueryService(REFGUID guidService,
	REFIID riid,
	void** ppvObject)
{
	if (riid == IID_IInternetSecurityManager)
	{
		METHOD_PROLOGUE(CExtendedHtmlControlSite, ServiceProvider);
		HRESULT hr = (HRESULT)pThis->ExternalQueryInterface(&riid, ppvObject);
		return hr;
	}
	else
	{
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}
}


ULONG FAR EXPORT CExtendedHtmlControlSite::XInternetSecurityManager::AddRef()
{
	METHOD_PROLOGUE(CExtendedHtmlControlSite, InternetSecurityManager)
	return pThis->ExternalAddRef();
}

ULONG FAR EXPORT CExtendedHtmlControlSite::XInternetSecurityManager::Release()
{
	METHOD_PROLOGUE(CExtendedHtmlControlSite, InternetSecurityManager)
	return pThis->ExternalRelease();
}

HRESULT FAR EXPORT CExtendedHtmlControlSite::XInternetSecurityManager::QueryInterface(REFIID riid,
	void** ppvObj)
{
	METHOD_PROLOGUE(CExtendedHtmlControlSite, InternetSecurityManager)
	HRESULT hr = (HRESULT)pThis->ExternalQueryInterface(&riid, ppvObj);
	return hr;
}

HRESULT CExtendedHtmlControlSite::XInternetSecurityManager::SetSecuritySite(
	/* [unique][in] */ __RPC__in_opt IInternetSecurityMgrSite *pSite)
{
	return INET_E_DEFAULT_ACTION;
}

HRESULT CExtendedHtmlControlSite::XInternetSecurityManager::GetSecuritySite(
	/* [out] */ __RPC__deref_out_opt IInternetSecurityMgrSite **ppSite) {
	return INET_E_DEFAULT_ACTION;
}

HRESULT CExtendedHtmlControlSite::XInternetSecurityManager::MapUrlToZone(
	/* [in] */ __RPC__in LPCWSTR pwszUrl,
	/* [out] */ __RPC__out DWORD *pdwZone,
	/* [in] */ DWORD dwFlags) {
	return INET_E_DEFAULT_ACTION;
	// *pdwZone = 0;
	// return S_OK;
}

HRESULT CExtendedHtmlControlSite::XInternetSecurityManager::GetSecurityId(
	/* [in] */ __RPC__in LPCWSTR pwszUrl,
	/* [size_is][out] */ __RPC__out_ecount_full(*pcbSecurityId) BYTE *pbSecurityId,
	/* [out][in] */ __RPC__inout DWORD *pcbSecurityId,
	/* [in] */ DWORD_PTR dwReserved) {
	return INET_E_DEFAULT_ACTION;
}

HRESULT CExtendedHtmlControlSite::XInternetSecurityManager::QueryCustomPolicy(
	/* [in] */ __RPC__in LPCWSTR pwszUrl,
	/* [in] */ __RPC__in REFGUID guidKey,
	/* [size_is][size_is][out] */ __RPC__deref_out_ecount_full_opt(*pcbPolicy) BYTE **ppPolicy,
	/* [out] */ __RPC__out DWORD *pcbPolicy,
	/* [in] */ __RPC__in BYTE *pContext,
	/* [in] */ DWORD cbContext,
	/* [in] */ DWORD dwReserved) {
	return INET_E_DEFAULT_ACTION;
}

HRESULT CExtendedHtmlControlSite::XInternetSecurityManager::SetZoneMapping(
	/* [in] */ DWORD dwZone,
	/* [in] */ __RPC__in LPCWSTR lpszPattern,
	/* [in] */ DWORD dwFlags) {
	return INET_E_DEFAULT_ACTION;
}

HRESULT CExtendedHtmlControlSite::XInternetSecurityManager::GetZoneMappings(
	/* [in] */ DWORD dwZone,
	/* [out] */ __RPC__deref_out_opt IEnumString **ppenumString,
	/* [in] */ DWORD dwFlags) {
	return INET_E_DEFAULT_ACTION;
}

