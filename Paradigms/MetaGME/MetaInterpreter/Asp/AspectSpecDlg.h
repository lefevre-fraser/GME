#if !defined(AFX_ASPECTSPECDLG_H__A771B477_7ECF_41F9_8FCD_1557C770B87C__INCLUDED_)
#define AFX_ASPECTSPECDLG_H__A771B477_7ECF_41F9_8FCD_1557C770B87C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include <AFXDLGS.H>

#include "AspectPage.h"

class CAspectPage;
class CAspectSpecDlg;
extern CAspectSpecDlg	*theAspectDlg;

typedef CTypedPtrList<CPtrList, CAspectPage*> CAspectPageList;

// AspectSpecDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAspectSpecDlg

class CAspectSpecDlg : public CPropertySheet
{
	//DECLARE_DYNAMIC(CAspectSpecDlg)

// Construction
public:
	CAspectSpecDlg(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CAspectSpecDlg(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

	CAspectPageList	aspectPages;
	CStringList	aspectNames;
	int	lastID;
	int countPages;
	

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAspectSpecDlg)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	void GetEntry(int entryNum, CString &roleName, CString &kindAspect, CString &isPrimary, const void * &ptr);
	int AddEntry(CString aspectName, CString roleName, CString  kindAspect, CString primaryAspect, const void * ptr);
	void GetAspects(CStringList& aspects);
	void GetAspects( int rowID, CStringList& aspects);
	virtual ~CAspectSpecDlg();

	// Generated message map functions
protected:
	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	//{{AFX_MSG(CAspectSpecDlg)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASPECTSPECDLG_H__A771B477_7ECF_41F9_8FCD_1557C770B87C__INCLUDED_)
