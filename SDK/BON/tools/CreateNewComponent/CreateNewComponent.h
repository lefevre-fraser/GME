// CreateNewComponent.h : main header file for the CREATENEWCOMPONENT application
//

#if !defined(AFX_CREATENEWCOMPONENT_H__6D70640F_3C5E_4415_AB7F_1BF0F537BD8F__INCLUDED_)
#define AFX_CREATENEWCOMPONENT_H__6D70640F_3C5E_4415_AB7F_1BF0F537BD8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCreateNewComponentApp:
// See CreateNewComponent.cpp for the implementation of this class
//

class CCreateNewComponentApp : public CWinApp
{
public:
	CCreateNewComponentApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreateNewComponentApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCreateNewComponentApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREATENEWCOMPONENT_H__6D70640F_3C5E_4415_AB7F_1BF0F537BD8F__INCLUDED_)
