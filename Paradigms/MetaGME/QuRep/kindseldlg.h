#pragma once
#include "afxwin.h"
#include "resource.h"


// KindSelDlg dialog

class KindSelDlg : public CDialog
{
	DECLARE_DYNAMIC(KindSelDlg)

public:
	KindSelDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~KindSelDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	bool         m_ranOnceAlready;	
	bool         m_applyAllSelected;
	bool         m_breakOnCancelSelected;
	int          m_selection;
	CString      m_resKindName;
	CString      m_currElemName;
	CString      m_oldKindName;

	CButton      m_quitOnCancel;
	CButton      m_applyForAll;
	CEdit        m_curElem;
	CEdit        m_oldKind;
	CListBox     m_knds;

public:
	bool shouldApplyForAll();
	bool shouldFinish();
	bool init( CString p_name, CString p_oldKind);
	bool setup();
	CString  selection();
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnLbnDblclkList1();
};
