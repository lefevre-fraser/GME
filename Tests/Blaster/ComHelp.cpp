
#include "stdafx.h"
#include "ComHelp.h"

void CIUnknownPtrList::Load(SAFEARRAY** ppsa)
{
	ASSERT(ppsa && *ppsa);
	ASSERT(IsEmpty());

	INTERFACE* *p;
	COMVERIFY(SafeArrayAccessData(*ppsa, (void**)&p));
	ASSERT(p);

	long bound;

	ASSERT( (*ppsa)->fFeatures | FADF_UNKNOWN );
	ASSERT( (*ppsa)->cbElements == sizeof(IUnknown*) );
	ASSERT( SafeArrayGetDim(*ppsa) == 1 );
	COMASSERT(SafeArrayGetLBound(*ppsa, 1, &bound));
	ASSERT( bound == 0 );

	COMVERIFY(SafeArrayGetUBound(*ppsa, 1, &bound));
	ASSERT( bound >= -1 );

	while( bound-- >= 0 )
		AddTail(*(p++));

	COMVERIFY(SafeArrayUnaccessData(*ppsa));
	COMVERIFY(SafeArrayDestroyNoRelease(*ppsa));
	*ppsa = NULL;
}

void CIUnknownPtrList::Copy(SAFEARRAY* psa)
{
	ASSERT(psa);
	ASSERT(IsEmpty());

	INTERFACE* *p;
	COMVERIFY(SafeArrayAccessData(psa, (void**)&p));
	ASSERT(p);

	long bound;

	ASSERT( SafeArrayGetDim(psa) == 1 );
	COMASSERT(SafeArrayGetLBound(psa, 1, &bound));
	ASSERT( bound == 0 );

	COMVERIFY(SafeArrayGetUBound(psa, 1, &bound));
	ASSERT( bound >= -1 );

	while( bound-- >= 0 )
		AddTail(*(p++));

	COMVERIFY(SafeArrayUnaccessData(psa));
}

SAFEARRAY* CIUnknownPtrList::Store()
{
	SAFEARRAY *psa;

	psa = SafeArrayCreateVector(VT_UNKNOWN, 0, GetCount());
	ASSERT(psa);

	IUnknown* *p;
	COMVERIFY(SafeArrayAccessData(psa,(void**)&p));

	POSITION pos = GetHeadPosition();
	while(pos)
		*(p++) = GetNext(pos);

	COMVERIFY(SafeArrayUnaccessData(psa));

	RemoveAll();
	return psa;
}

void CIUnknownPtrList::AddRefAll()
{
	POSITION pos = GetHeadPosition();
	while(pos)
		GetNext(pos)->AddRef();
}

void CIUnknownPtrList::ReleaseAll()
{
	POSITION pos = GetHeadPosition();
	while(pos)
		GetNext(pos)->Release();
}

// --------------------------- SafeArray

HRESULT SafeArrayDestroyNoRelease(SAFEARRAY* psa)
{
	ASSERT(psa);

	ASSERT( psa->fFeatures | FADF_UNKNOWN );
	ASSERT( psa->cbElements == sizeof(IUnknown*) );

	psa->fFeatures &= ~FADF_UNKNOWN;

	return SafeArrayDestroy(psa);
}

void LoadBstrSafeArray(CStringList& dest, SAFEARRAY** ppsa)
{
	ASSERT(ppsa && *ppsa);
	ASSERT(dest.IsEmpty());

	BSTR *p;
	COMVERIFY(SafeArrayAccessData(*ppsa,(void**)&p));
	ASSERT(p);

	long bound;

	ASSERT( SafeArrayGetDim(*ppsa) == 1 );
	COMASSERT(SafeArrayGetLBound(*ppsa, 1, &bound));
	ASSERT( bound == 0 );

	COMVERIFY(SafeArrayGetUBound(*ppsa, 1, &bound));
	ASSERT( bound >= -1 );

	while( bound-- >= 0 )
		dest.AddTail(CString(*(p++)));

	COMVERIFY(SafeArrayUnaccessData(*ppsa));
	COMVERIFY(SafeArrayDestroy(*ppsa));
	*ppsa = NULL;
}

SAFEARRAY* StoreBstrSafeArray(CStringList& source)
{
	SAFEARRAY *psa;

	psa = SafeArrayCreateVector(VT_BSTR, 0, source.GetCount());
	ASSERT(psa);

	BSTR *p;
	COMVERIFY(SafeArrayAccessData(psa,(void**)&p));

	POSITION pos = source.GetHeadPosition();
	while(pos)
	{
		BSTR s = source.GetNext(pos).AllocSysString();
		ASSERT(s);
		*(p++) = s;
	}

	COMVERIFY(SafeArrayUnaccessData(psa));

	source.RemoveAll();
	return psa;
}

// --------------------------- hresult_exception

hresult_exception::hresult_exception()
{
	hr = 0;
}

hresult_exception::hresult_exception(const hresult_exception &e)
{
	hr = e.hr;
}

hresult_exception::hresult_exception(HRESULT a)
{
	hr = a;
}

hresult_exception &hresult_exception::operator=(const hresult_exception &e)
{
	hr = e.hr;
	return *this;
}

hresult_exception &hresult_exception::operator=(HRESULT a)
{
	hr = a;
	return *this;
}

hresult_exception::~hresult_exception()
{
}

const char *hresult_exception::what() const
{
	static char message[80];
	sprintf(message, "HRESULT (0x%08lx) exception", hr);
	return message;
}
