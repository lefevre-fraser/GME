#include <windows.h>
#include <atlbase.h>
#include "CommonSmart.h"


#define HR_THROW throw 

long GetArrayLength(SAFEARRAY *p)
{
	ASSERT( p != NULL );

	if( !(p->cDims == 1 || p->cDims == 2) )
		HR_THROW(E_INVALIDARG);

	ASSERT( p->rgsabound[0].cElements >= 0 );
	return p->rgsabound[0].cElements;
}

long GetArrayLength(const VARIANT &v)
{
	if( (v.vt & VT_ARRAY) == VT_ARRAY )
		return GetArrayLength(v.parray);
	else if( v.vt == VT_EMPTY )
		return 0;

	HR_THROW(E_INVALIDARG);
}

void CopyTo(SAFEARRAY *p, CComBSTR *start, CComBSTR *end)
{
	ASSERT( p != NULL );
	ASSERT( start <= end );

	ASSERT( (p->fFeatures & FADF_BSTR) == FADF_BSTR );

	BSTR *q = NULL;

	HRESULT hr = SafeArrayAccessData(p, (void**)&q);
	if(hr != S_OK) HR_THROW(hr);
	ASSERT( q != NULL );

	try
	{
		ASSERT( GetArrayLength(p) == (end - start) );

		while( start < end )
		{
			*start = *q;

			++q;
			++start;
		}
	}
	catch(hresult_exception &)
	{
		SafeArrayUnaccessData(p);
		throw;
	}

	hr = SafeArrayUnaccessData(p);
	if(hr != S_OK) HR_THROW(hr);
}

void CopyTo(const VARIANT &v, CComBSTR *start, CComBSTR *end)
{
	ASSERT( start <= end );

	if( v.vt == VT_EMPTY && start == end )
		return;

	if( v.vt != (VT_BSTR | VT_ARRAY) )
		HR_THROW(E_INVALIDARG);

	CopyTo(v.parray, start, end);
}

