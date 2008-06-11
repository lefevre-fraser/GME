// StringArrayEx.cpp: implementation of the CStringArrayEx class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gmeactivebrowser.h"
#include "StringArrayEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStringArrayEx::CStringArrayEx()
{

}

CStringArrayEx::~CStringArrayEx()
{

}


///////////////////////////////////////////////////////////////////////
// Returns the index where the element was inserted
///////////////////////////////////////////////////////////////////////
int CStringArrayEx::InsertAtOrder(CString &strElement)
{
	bool bIsGreater=true; // Detecting the change in search
	
	TRACE("\nStrArEx Dump:\n");
	TRACE(strElement);
	TRACE(" ");

	int nMaxElement=CStringArray::GetUpperBound();

	for(int i=0;i<=nMaxElement;i++)
	{
		bIsGreater=((strElement > CStringArray::ElementAt(i))?true:false);
		if(false==bIsGreater) // Change
		{
			CStringArray::InsertAt(i,strElement);
			return i;
		}

	}
	return CStringArray::Add(strElement); // The last element,which was greater than each
}
