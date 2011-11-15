// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently


#if !defined(AFX_STDAFX_H__270B4F89_B17C_11D3_9AD1_00AA00B6FE26__INCLUDED_)
#define AFX_STDAFX_H__270B4F89_B17C_11D3_9AD1_00AA00B6FE26__INCLUDED_

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _CRT_SECURE_NO_WARNINGS

#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#pragma warning(push,3)


#include <list>//slist
#include <string>
#include <set>
#include <queue>
#include <vector>
#include <hash_set>
#include <hash_map>
#pragma warning(pop)

#ifdef _DEBUG
#define MGA_TRACE AtlTrace
#else
inline void NOOP_TRACE2(LPCSTR, ...) { }
#define MGA_TRACE 1 ? void(0) : NOOP_TRACE2
#endif

#undef VARIANT_TRUE
#define VARIANT_TRUE ((VARIANT_BOOL)-1)
#include "CoreLib.h"
#include "MgaLib.h"	

#define ASSERT ATLASSERT
#include "CommonSmart.h"
#include "CommonStl.h"
#include "CommonError.h"
#include "CommonCollection.h"
#include "MgaGeneric.h"
#include "MgaCoreObj.h"
#include "MgaTrukk.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__270B4F89_B17C_11D3_9AD1_00AA00B6FE26__INCLUDED)
