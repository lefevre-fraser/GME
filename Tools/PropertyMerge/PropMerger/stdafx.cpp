// stdafx.cpp : source file that includes just the standard includes
// PropMerger.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

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

void CopyTo( CComBSTR p_src, char **p_ptrResult)
{
	if( !p_ptrResult) return;

	*p_ptrResult = 0;

	unsigned int len = p_src.Length();
	if( !len) return;

	char *buff = new char[ len + 1]; 

	CopyTo( p_src, len, buff, len);
	buff[ len] = '\0';

	*p_ptrResult = buff;
}

void CopyTo(const OLECHAR *p, int olelen, char *s, int charlen)
{
	ASSERT( olelen >= -1 && charlen >= 0 );
	ASSERT( charlen == 0 || p != NULL );

	if( charlen <= 0 )
		return;

	UINT acp = GetACP();

	int len = WideCharToMultiByte(acp, 0, p, olelen, 
		s, charlen, NULL, NULL);

	// zero if failed
	ASSERT( len > 0 );

	ASSERT( len == charlen );
}		

void CopyTo(const char *p, int len, BSTR *b)
{
	ASSERT( len >= 0 );
	ASSERT( b != NULL );

	if(*b)
	{
		SysFreeString(*b);
		*b = NULL;
	}

	if( len <= 0 )
		return;

	UINT acp = GetACP();
	int blen = MultiByteToWideChar(acp, 0, p, len, NULL, 0);

	if( blen <= 0 )
		HR_THROW(-1);

	*b = SysAllocStringLen(NULL, blen);
	if( *b == NULL )
		HR_THROW(-1);

	int tlen = MultiByteToWideChar(acp, 0, p, len, *b, blen);

	if( tlen <= 0 )
		HR_THROW(-1);
	
	ASSERT( tlen == blen );

	(*b)[blen] = '\0';
}

