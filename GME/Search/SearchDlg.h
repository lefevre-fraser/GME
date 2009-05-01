#if !defined(AFX_SEARCHDLG_H__E59A9A8F_05E1_48EB_BB09_897251FD3943__INCLUDED_)
#define AFX_SEARCHDLG_H__E59A9A8F_05E1_48EB_BB09_897251FD3943__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSearchCtrl;

#include "ComHelp.h"
#include "MEdit.h"
#include "MButton.h"
#include "MComboBox.h"
#include "MListCtrl.h"
#include "afxwin.h"
#include "afxcmn.h"
// SearchDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSearchDlg dialog

class CSearchDlg : public CDialog
{
// Construction
public:
	CSearchDlg();   // standard constructor
    ~CSearchDlg();
	BOOL OnInitDialog();

//  These functions should be implemented to work with CSearchCtl
	void RemoveAll();						// must remove all search result
	void RemoveZombies();					// must remove results belong to zombie objects
	void EnableSearch();					// enable search functions
	void DisableSearch();					// must disable search functions
	void EnableScoped( BOOL enable);

	inline CSearchCtrl* getMyParent() { return GetCtrl(); }
	void clickGo();
	void itemDblClicked();
	void itemClicked();
	void tabPressed( CWnd* pOriginator, bool bShift = false);
    
    //added
    void SaveSearch();
    void LoadPrevSearch();
    void CreateSearchHistory();

// Dialog Data
	//{{AFX_DATA(CSearchDlg)
	enum { IDD = IDD_SEARCH_DIALOG };
	//CStatic	m_stcRefCtrl;
	CProgressCtrl	m_pgsSearch;

	CString	m_edtName;
	CString	m_edtKindName;
	CString	m_edtRoleName;
	CString	m_cmbType;
	CString	m_edtAttrName;
	CString	m_edtAttrValue;
	BOOL	m_chkAtom;
	BOOL	m_chkFullWord;
	BOOL	m_chkMod;
	BOOL	m_chkRef;
	BOOL	m_chkSet;
	//BOOL	m_chkSplSearch;
	BOOL	m_chkLocate;
	BOOL	m_chkMatchCase;
	//BOOL    m_chkScopedSearch;
	//CString	m_stcRef;

	//CMButton	m_chkSplSearchCtrl;
	//CMButton	m_chkLocateCtrl;
	CMButton	m_chkMatchCaseCtrl;
	//CMButton	m_chkScopedSearchCtrl;
	CMButton	m_chkFullWordCtrl;
	CMButton	m_chkRefCtrl;
	CMButton	m_chkAtomCtrl;
	CMButton	m_chkSetCtrl;
	CMButton	m_chkModCtrl;
	CMComboBox	m_cmbCtrl;
	CMButton	m_btnGO;
	CMListCtrl	m_lstResults;
	CMEdit	m_edtNameCtrl;
	CMEdit	m_edtKindNameCtrl;
	CMEdit	m_edtRoleNameCtrl;
	CMEdit	m_edtAttrNameCtrl;
	//CMEdit	m_edtAttrValueCtrl;

private:
    //insert history to combobox
    void InsertHistory(CString string);
    void ComputeWidthHeight();

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	CSearchCtrl *GetCtrl() { return (CSearchCtrl*)GetParent(); }

	
	void BuildExtendedName(IMgaFCO *named, CString &extName);
	void BuildExtendedName(IMgaFolder *named, CString &extName);
	void DisplayResults();
    void SearchResults();

    //*Added*
    void ParseAttribute();

	CComPtr<IMgaFCOs> results;
	CComPtr<IMgaFCO> specialSearchFCO;

	BOOL m_scopedCtrlEnabled; // whether to enable scoped search at all


	// Generated message map functions
	//{{AFX_MSG(CSearchDlg)
	afx_msg void OnButtonGo();
	afx_msg void OnClickListResults(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListResults(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckSplSearch();
    afx_msg void OnDblclkPrevSearches(NMHDR* pNMHDR, LRESULT* pResult);

    //scroll bar
     afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
     afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
    afx_msg void OnCbnSelchangeCombotype();

   
    //scroll bar
    int v_scrollPos;
    int h_scrollPos;
	const int vScrollWidth;
    const int lineSize;
	const int pageSize;
    int logicalHeight;
    int pageHeight;
    int logicalWidth;
    int pageWidth;
     
    //
    CString m_edtName2;
    CString m_edtRoleName2;
    CString m_edtKindName2;
    CString m_edtAttribute2;
    //BOOL m_radioAnd;
    CButton m_logicalGrp;
    CComboBox m_cmbCtrl2;
    CListCtrl m_prevSearches;
    CString m_cmbType2;
    int m_scope;
    BOOL m_searchResults;
    int m_radioLogical;
   
    CMEdit m_edtNameCtrl2;
    CMEdit m_edtRoleNameCtrl2;
    CMEdit m_edtKindNameCtrl2;
    CMEdit m_edtAttributeCtrl2;
    
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHDLG_H__E59A9A8F_05E1_48EB_BB09_897251FD3943__INCLUDED_)
