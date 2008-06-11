// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__70C41B18_E3CE_11D3_B37A_005004D38590__INCLUDED_)
#define AFX_STDAFX_H__70C41B18_E3CE_11D3_B37A_005004D38590__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

#include <stl_user_config.h>

#define ASSERT ATLASSERT

#include "ParserLib.h"
#include "CommonSmart.h"
#include "CommonStl.h"
#define GLOBAL_ID_STR   "guid"
#define GLOBAL_ID_LEN   38
#define PREV_GLOBAL_ID_STR   "guid/prev"
#define PREV_ID_STR     "prev"
typedef IMgaConstraint IMgaMetaConstraint;
typedef IMgaConstraints IMgaMetaConstraints;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__70C41B18_E3CE_11D3_B37A_005004D38590__INCLUDED)
