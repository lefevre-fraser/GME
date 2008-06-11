// ComponentDll.h : main header file for the Component DLL
//

#if !defined(AFX_COMPONENTAPP_H__DC43D02A_061D_11D2_BBB3_0040051F7117__INCLUDED_)
#define AFX_COMPONENTAPP_H__DC43D02A_061D_11D2_BBB3_0040051F7117__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include <vector>

typedef jint (JNICALL *P_JNI_CreateJavaVM)        (JavaVM **pvm, void** penv, void *args);
typedef jint (JNICALL *P_JNI_GetCreatedJavaVMs)   (JavaVM **vmBuf,jsize bufLen, jsize *nVMs);

/////////////////////////////////////////////////////////////////////////////
// CComponentApp
// See Component.cpp for the implementation of this class
//

class CComponentApp : public CWinApp
{
public:
	CComponentApp();
    
    void addComponents( HKEY folder );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComponentApp)
	public:
	virtual BOOL InitInstance();    
	//}}AFX_VIRTUAL

    virtual int ExitInstance();

	//{{AFX_MSG(CComponentApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

//protected:

public:
    std::vector<COleObjectFactory*> m_factories;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMONENTAPP_H__DC43D02A_061D_11D2_BBB3_0040051F7117__INCLUDED_)
