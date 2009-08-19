// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define WINVER 0x0501

#include <iostream>
#include <tchar.h>
#include <Afx.h>
//#include <afxdisp.h>
#include <Atlbase.h>
#include <Objbase.h>


#if !defined(ASSERT) && defined(ATLASSERT)
#define ASSERT ATLASSERT
#endif

// --------------------------- hresult_exception

class hresult_exception : public std::exception
{
public:
	hresult_exception() throw();
	hresult_exception(const hresult_exception &e) throw();
	hresult_exception(HRESULT hr) throw();
	hresult_exception &operator=(const hresult_exception &e) throw();
	hresult_exception &operator=(HRESULT hr) throw();
	~hresult_exception() throw();
	virtual const char *what() const throw();

public:
	HRESULT hr;
};



#define HR_THROW(_hr) \
do { \
	ASSERT(("HR_THROW: Throwing HRESULT exception. Press IGNORE", false)); \
	throw hresult_exception(_hr); \
} while(false)


#define COMTHROW(FUNC) \
do { \
	HRESULT _hr = (FUNC); \
	if( FAILED(_hr) ) { \
		ASSERT(("COMTHROW: Throwing HRESULT exception. Press IGNORE", false)); \
		throw hresult_exception(_hr); \
	} \
} while(false)

#define COMTRY try

#define COMCATCH(CLEANUP) \
	catch(hresult_exception &e) \
	{ \
		ASSERT( FAILED(e.hr) ); \
		{ CLEANUP; } \
		return e.hr; \
	} \
	return S_OK;


void CopyTo(const CComBSTR b, char* *p_ptrResult); // caller's job to free
void CopyTo(const OLECHAR *p, int olelen, char *s, int charlen);
void CopyTo(const char *p, int len, BSTR *b);
