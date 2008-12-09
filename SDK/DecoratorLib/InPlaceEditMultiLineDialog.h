#if !defined(AFX_INPLACEEDITMULTILINEDIALOG_H__54CB7BF5_A177_4Af4_83EF_A3127CAD55B4__INCLUDED_)
#define AFX_INPLACEEDITMULTILINEDIALOG_H__54CB7BF5_A177_4Af4_83EF_A3127CAD55B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InPlaceEditMultiLineDialog.h : header file
//

#include "stdafx.h"
#include "InPlaceEditDialog.h"

// CInPlaceEditMultiLineDialog dialog

class CInPlaceEditMultiLineDialog : public CInPlaceEditDialog
{
	DECLARE_DYNAMIC(CInPlaceEditMultiLineDialog)

public:
	CInPlaceEditMultiLineDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CInPlaceEditMultiLineDialog();

// Dialog Data
	//{{AFX_DATA(CInPlaceEditMultiLineDialog)
	enum { IDD = IDD_INPLACEEDITMLDIALOG };
	//}}AFX_DATA
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPLACEEDITMULTILINEDIALOG_H__54CB7BF5_A177_4Af4_83EF_A3127CAD55B4__INCLUDED_)
