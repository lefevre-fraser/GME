#pragma once
// HtmlCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHtmlCtrl html view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <afxhtml.h>

#include <mshtmcid.h>
#include <mshtmhst.h>
#include <mshtmdid.h>
#include <mshtml.h>

class CConsoleCtl;
class CHtmlCtrl;


class CExtendedHtmlControlSite : public COleControlSite
{
public:
	CExtendedHtmlControlSite(COleControlContainer* pContainer, CHtmlCtrl* pView);
	virtual ~CExtendedHtmlControlSite(void);
protected:
	CHtmlCtrl* m_pView;

	DECLARE_INTERFACE_MAP()

	BEGIN_INTERFACE_PART(ServiceProvider, IServiceProvider)
		STDMETHOD(QueryService)(REFGUID, REFIID, void**);
	END_INTERFACE_PART(ServiceProvider)

	BEGIN_INTERFACE_PART(InternetSecurityManager, IInternetSecurityManager)
		virtual HRESULT STDMETHODCALLTYPE SetSecuritySite(
			/* [unique][in] */ __RPC__in_opt IInternetSecurityMgrSite *pSite);

		virtual HRESULT STDMETHODCALLTYPE GetSecuritySite(
			/* [out] */ __RPC__deref_out_opt IInternetSecurityMgrSite **ppSite);

		virtual HRESULT STDMETHODCALLTYPE MapUrlToZone(
			/* [in] */ __RPC__in LPCWSTR pwszUrl,
			/* [out] */ __RPC__out DWORD *pdwZone,
			/* [in] */ DWORD dwFlags);

		virtual HRESULT STDMETHODCALLTYPE GetSecurityId(
			/* [in] */ __RPC__in LPCWSTR pwszUrl,
			/* [size_is][out] */ __RPC__out_ecount_full(*pcbSecurityId) BYTE *pbSecurityId,
			/* [out][in] */ __RPC__inout DWORD *pcbSecurityId,
			/* [in] */ DWORD_PTR dwReserved);

		virtual HRESULT STDMETHODCALLTYPE ProcessUrlAction(
			/* [in] */ __RPC__in LPCWSTR pwszUrl,
			/* [in] */ DWORD dwAction,
			/* [size_is][out] */ __RPC__out_ecount_full(cbPolicy) BYTE *pPolicy,
			/* [in] */ DWORD cbPolicy,
			/* [unique][in] */ __RPC__in_opt BYTE *pContext,
			/* [in] */ DWORD cbContext,
			/* [in] */ DWORD dwFlags,
			/* [in] */ DWORD dwReserved);

		virtual HRESULT STDMETHODCALLTYPE QueryCustomPolicy(
			/* [in] */ __RPC__in LPCWSTR pwszUrl,
			/* [in] */ __RPC__in REFGUID guidKey,
			/* [size_is][size_is][out] */ __RPC__deref_out_ecount_full_opt(*pcbPolicy) BYTE **ppPolicy,
			/* [out] */ __RPC__out DWORD *pcbPolicy,
			/* [in] */ __RPC__in BYTE *pContext,
			/* [in] */ DWORD cbContext,
			/* [in] */ DWORD dwReserved);

		virtual HRESULT STDMETHODCALLTYPE SetZoneMapping(
			/* [in] */ DWORD dwZone,
			/* [in] */ __RPC__in LPCWSTR lpszPattern,
			/* [in] */ DWORD dwFlags);

		virtual HRESULT STDMETHODCALLTYPE GetZoneMappings(
			/* [in] */ DWORD dwZone,
			/* [out] */ __RPC__deref_out_opt IEnumString **ppenumString,
			/* [in] */ DWORD dwFlags);
	END_INTERFACE_PART(InternetSecurityManager)
};


class CHtmlCtrl : public CHtmlView
{		
public:
	CHtmlCtrl();
	~CHtmlCtrl() { }

// html Data
public:
	//{{AFX_DATA(CHtmlCtrl)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	BOOL CreateFromStatic(UINT nID, CWnd* pParent);
 
	// Normally, CHtmlView destroys itself in PostNcDestroy,
    // but we don't want to do that for a control since a control
    // is usually implemented as a stack object in a dialog.
    //
    virtual void PostNcDestroy() {  }

	BOOL CreateControlSite(COleControlContainer* pContainer,
		COleControlSite** ppSite, UINT /* nID */, REFCLSID /* clsid */)
	{
		ASSERT(ppSite != NULL);
		*ppSite = new CExtendedHtmlControlSite(pContainer, this);
		return TRUE;
	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHtmlCtrl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

    // override to trap "app:" pseudo protocol
    virtual void OnBeforeNavigate2( LPCTSTR lpszURL,
       DWORD nFlags,
       LPCTSTR lpszTargetFrameName,
       CByteArray& baPostedData,
       LPCTSTR lpszHeaders,
       BOOL* pbCancel );

	// override to handle links to "app:mumble...". lpszWhere will be "mumble"
    virtual void OnMgaURL(LPCTSTR lpszWhere);
	virtual void OnDocumentComplete(LPCTSTR lpszURL);

// Implementation
protected:

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CHtmlCtrl)
	afx_msg void OnDestroy();
	afx_msg int  OnMouseActivate(CWnd* pDesktopWnd,UINT nHitTest,UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CHtmlCtrl)
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

