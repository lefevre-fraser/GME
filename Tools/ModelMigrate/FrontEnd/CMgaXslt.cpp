#include "stdafx.h"
#include "CMgaXslt.h"             

#define DISPATCH_XSLT 0
#if(DISPATCH_XSLT)
// it seems Mga.MgaXSLT is not really Dispatch compatible yet
#else
// in this case we use MIDL produced h file from an idl file which includes only the gme idls
#include "..\IDLComp\GMEIDLs_h.h" 
#endif


void CXslt::doNativeXslt( LPCTSTR pScrF, LPCTSTR pInF, LPCTSTR pOutF, CString& resError)
{/*
	// native vtable based
	CComPtr<IMgaXslt> xslt;
	HRESULT hr = xslt.CoCreateInstance(L"Mga.MgaXslt");
	ASSERT( xslt != NULL );
	if( FAILED( hr) || xslt == NULL) { resError = "COM Error at CreateInstance!"; return; }
	
	CComBSTR x_scr( pScrF);
	CComBSTR f_iin( pInF);
	CComBSTR f_out( pOutF);
	CComBSTR error;

	try 
	{
		hr = xslt->ApplyXslt( x_scr, f_iin, f_out, &error);
		if( FAILED( hr)) throw hr;
	} catch( HRESULT&)
	{
		if( error && error.Length() > 0)
			resError = COLE2T( error);
		else 
			resError = "COM Error!";
	}
	*/
}

void CXslt::doDispatchXslt( LPCTSTR pScrF, LPCTSTR pInF, LPCTSTR pOutF, CString& resError)
{
	// dispatch based, if it worked
	CComPtr<IUnknown> unknwn;
	HRESULT hr;
	hr = unknwn.CoCreateInstance( L"Mga.MgaXslt");
	if( FAILED( hr)) { resError = "COM Error at CreateInstance!"; return; }
	CComPtr<IDispatch> disp;
	hr = unknwn.QueryInterface( &disp);
	if( FAILED( hr)) { resError = "COM Error at QueryInterface!"; return; }
	CMgaXsltDriver xslt( disp);
	CComBSTR error;
	try 
	{
		hr = xslt.ApplyXslt( pScrF, pInF, pOutF, &error);

		if( FAILED( hr)) throw hr;
	} catch( HRESULT&)
	{
		if( error && error.Length() > 0)
			resError = COLE2T( error);
		else // error is empty
			resError = "COM Error";
	}
}