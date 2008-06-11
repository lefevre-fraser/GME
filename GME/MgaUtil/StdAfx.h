// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__461F30A9_3BF0_11D4_B3F0_005004D38590__INCLUDED_)
#define AFX_STDAFX_H__461F30A9_3BF0_11D4_B3F0_005004D38590__INCLUDED_

# if _MSC_VER > 1000
#  pragma once
# endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers //zolmol7
 
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT

 
#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

# undef  _ATL_APARTMENT_THREADED
# undef  _ATL_SINGLE_THREADED
# define _ATL_FREE_THREADED

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

///////////////////////////////////////////////////////////////////

#define chSTR(x) #x
#define chSTR2(x) chSTR(x)
#define bookmark(desc) message(__FILE__"("\
 chSTR2(__LINE__) ") : PRAGMA-- " #desc )

///////////////////////////////////////////////////////////////////

#include <stl_user_config.h>

#include <vector>
#include <list>

#include "MgaUtilLib.h"
#include "CommonSmart.h"
#include "CommonStl.h"
#include "CommonError.h"
#include "CommonMfc.h"
#include "CommonMgaTrukk.h"
///////////////////////////////////////////////////////////////////

#ifndef __AFXTEMPL_H__
#include <afxtempl.h>
#endif

#include "Resource.h"
#include "PropertiesDlg.h"
#include "ConnPropertiesDlg.h"
#include "FolderPropertiesDlg.h"

regaccessmode_enum regacc_translate(int x);
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__461F30A9_3BF0_11D4_B3F0_005004D38590__INCLUDED_)
