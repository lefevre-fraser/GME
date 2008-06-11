// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__9E9AAAD2_28B8_11D3_B36C_0060082DF884__INCLUDED_)
#define AFX_STDAFX_H__9E9AAAD2_28B8_11D3_B36C_0060082DF884__INCLUDED_

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


#define _NOTHREADS

#include <stl_user_config.h>

#define ASSERT ATLASSERT

#include "resource.h"
#include "CoreLib.h"
#include "CommonSmart.h"
#include "CommonStl.h"
#include "CoreUtilities.h"



extern HRESULT check_location_compatibility(ICoreMetaObject *newobj, ICoreMetaObject *oldobj);
extern HRESULT check_location_compatibility(ICoreMetaAttribute *newobj, ICoreMetaAttribute *oldobj);

extern HRESULT check_location_compatibility(ICoreObject *newobj, ICoreObject *oldobj);
extern HRESULT check_location_compatibility(ICoreAttribute *newobj, ICoreAttribute *oldobj);



#ifdef _DEBUG
//#define DEBUG_REPOSITORY
//#define DEBUG_OBJECTLOOKUP
//#define DEBUG_CONTAINERS		// this is really slow
//#define TRACE_REPOSITORY
//#define TRACE_CORE
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__9E9AAAD2_28B8_11D3_B36C_0060082DF884__INCLUDED)
