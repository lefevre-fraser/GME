#if !defined(AFX_CONSOLE_H__AEAA39FE_41DB_43E1_BC64_1C05D697E3F4__INCLUDED_)
#define AFX_CONSOLE_H__AEAA39FE_41DB_43E1_BC64_1C05D697E3F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CConsole wrapper class

class CConsole : public CWnd
{
protected:
	DECLARE_DYNCREATE(CConsole)
public:
	~CConsole();
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xe4eb8324, 0x13f0, 0x46cb, { 0x96, 0xa3, 0xf5, 0x39, 0xdf, 0x7f, 0x79, 0xd4 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR /*lpszClassName*/,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* /*pContext = NULL*/)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// Attributes
public:
	CString GetContents();
	void SetContents(LPCTSTR);
	CString Get_Contents();
	void Set_Contents(LPCTSTR);

// Operations
public:
	void Message(LPCTSTR str, short type);
	void Clear();
	void AboutBox();
	void SetGMEApp(IDispatch *idp);
	void SetGMEProj(IDispatch *idp);
	void NavigateTo(LPCTSTR url);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONSOLE_H__AEAA39FE_41DB_43E1_BC64_1C05D697E3F4__INCLUDED_)
