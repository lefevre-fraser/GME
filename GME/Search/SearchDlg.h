#if !defined(AFX_SEARCHDLG_H__E59A9A8F_05E1_48EB_BB09_897251FD3943__INCLUDED_)
#define AFX_SEARCHDLG_H__E59A9A8F_05E1_48EB_BB09_897251FD3943__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSearchCtrl;

#include "ComHelp.h"
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
   
    //added -kiran
    void SaveSearchHistory();
    void LoadSearchHistory();
    void CreateSearchHistory();

    //virtual LRESULT WindowProc(UINT message,  WPARAM wParam, LPARAM lParam);
    //virtual BOOL PreTranslateMessage(MSG *pMsg);

// Dialog Data
	//{{AFX_DATA(CSearchDlg)
	enum { IDD = IDD_SEARCH_DIALOG };
	//CStatic	m_stcRefCtrl;
	CProgressCtrl	m_pgsSearch;

	CString	m_edtNameFirst;
	CString	m_edtKindNameFirst;
	CString	m_edtRoleNameFirst;
    CString	m_edtAttributeFirst;
	
    //remove
    CString	m_edtAttrValue;

    CString m_edtNameSecond;
    CString m_edtRoleNameSecond;
    CString m_edtKindNameSecond;
    CString m_edtAttributeSecond;

	BOOL	m_chkAtom;
	BOOL	m_chkFullWord;
	BOOL	m_chkMod;
	BOOL	m_chkRef;
	BOOL	m_chkSet;
	BOOL	m_chkLocate;
	BOOL	m_chkMatchCase;
	
	CButton	m_chkMatchCaseCtrl;
	CButton	m_chkFullWordCtrl;
	CButton	m_chkRefCtrl;
	CButton	m_chkAtomCtrl;
	CButton	m_chkSetCtrl;
	CButton	m_chkModCtrl;
	CComboBox	m_cmbCtrl;
	CButton	m_btnGO;
	CListCtrl	m_lstResults;
    CTreeCtrl m_treeSearchHistory;

    //first search criteria controls
	CComboBox	m_edtNameCtrlFirst;
	CComboBox	m_edtKindNameCtrlFirst;
	CComboBox	m_edtRoleNameCtrlFirst;
	CComboBox	m_edtAttributeCtrlFirst;
	
    //second search criteria controls
    CComboBox m_edtNameCtrlSecond;
    CComboBox m_edtRoleNameCtrlSecond;
    CComboBox m_edtKindNameCtrlSecond;
    CComboBox m_edtAttributeCtrlSecond;
     
    CButton m_logicalGrp;
    CComboBox m_cmbCtrl2;
    int m_radioScope;
    BOOL m_searchResults;
    int m_radioLogical;

private:
    //insert history to combobox
    void InsertHistory(CString string);

    //prepare history string by appending search term name and value pairs. value is enclose by quotes
    void PrepareHistoryString(const CString &strCriteriaName,CString & strSearchValue,HTREEITEM hParent,CString &strSearch);
    void PrepareHistoryString(const CString &strCriteriaName,int & strSearchValue,HTREEITEM hParent,CString &strSearch);
    
    //reverse of prepare extract search value from the saved string
    //string and int version with string extracting string value and int version extracting
    //integer values
    void ReadHistoryValue(const CString &strCriteriaName, CString &strHistory, CString &strValue);
    void ReadHistoryValue(const CString &strCriteriaName,CString &strHistory, int &value);
   
    //called to enter history text to combobox
    //checks first if it exists at the first index of items
    //if it does it is not inserted, else inserted
    void InsertTextToControl(CString& strSearchTerm,CComboBox& control);

    
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
   
   	CComPtr<IMgaFCOs> results;
	CComPtr<IMgaFCO> specialSearchFCO;

	BOOL m_scopedCtrlEnabled; // whether to enable scoped search at all


	// Generated message map functions
	//{{AFX_MSG(CSearchDlg)
	afx_msg void OnButtonGo();
	afx_msg void OnClickListResults(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListResults(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
    afx_msg void OnCbnSelchangeCombotype();
    afx_msg void OnNMDblclkTreeSearchHistory(NMHDR *pNMHDR, LRESULT *pResult);
    // if the connections are to be searched for
    BOOL m_chkConnection;
    BOOL m_chkSplSearch;
    afx_msg void OnCheckSplSearch();
    // reference static text ctrl
    CStatic m_stcRefCtrl;
    CButton m_chkConnCtrl;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHDLG_H__E59A9A8F_05E1_48EB_BB09_897251FD3943__INCLUDED_)
