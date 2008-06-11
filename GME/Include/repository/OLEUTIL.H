//*****************************************************************************
// oleutil.h
//
// This file defines helper routines/classes to simplify repository
// programming in C++.
// !NOTE!: Do not add anything that is strictly RepODBC project dependent to 
//         this file.
//
// Copyright (c) 1996, Microsoft Corp.  All rights reserved.
//*****************************************************************************

#ifndef __OLEUTIL_H__
#define __OLEUTIL_H__

#include <math.h>
#include <time.h>
#include "repapi.h"

#define MIN_DATE		(-657434L)		// About year 100
#define MAX_DATE		2958466L		// About year 9999

// Half a second, expressed in days
#define HALF_SECOND  (1.0/172800.0)

// One-based array of days in year at month start
static int rgMonthDays[13] =
	{0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

// Macros for interface reference counts.
#ifdef _DEBUG
#define DefineIRef() DWORD m_cRef
#define InitIRef() m_cRef(0),
#define IncIRef() UInterlockedIncrement(&m_cRef)
#define DecIRef() UInterlockedDecrement(&m_cRef)
#else
#define DefineIRef()
#define InitIRef()
#define IncIRef()
#define DecIRef()
#endif

//*****************************************************************************
// Smart Pointers for use with COM Objects.  
//
// Based on the CSmartInterface class in Dale Rogerson's technical
// article "Calling COM Objects with Smart Interface Pointers" on MSDN.
//*****************************************************************************
template <class I>
class CIfacePtr
{
public:
//*****************************************************************************
// Construction - Note that it does not AddRef the pointer.  The caller must
// hand this class a reference.
//*****************************************************************************
	CIfacePtr(
		I			*pI = NULL)			// Interface ptr to store.
	:	m_pI(pI)
	{
	}

//*****************************************************************************
// Copy Constructor
//*****************************************************************************
	CIfacePtr(
		const CIfacePtr<I>& rSI)		// Interface ptr to copy.
	:	m_pI(rSI.m_pI)
	{
		if (m_pI != NULL)
			m_pI->AddRef();
	}
   
//*****************************************************************************
// Destruction
//*****************************************************************************
	~CIfacePtr()
	{
		if (m_pI != NULL)
			m_pI->Release();
	}

//*****************************************************************************
// Assignment Operator for a plain interface pointer.  Note that it does not
// AddRef the pointer.  Making this assignment hands a reference count to this
// class.
//*****************************************************************************
	CIfacePtr<I>& operator=(			// Reference to this class.
		I			*pI)				// Interface pointer.
	{
		if (m_pI != NULL)
			m_pI->Release();
		m_pI = pI;
		return (*this);
	}

//*****************************************************************************
// Assignment Operator for a CIfacePtr class.  Note this releases the reference
// on the current ptr and AddRefs the new one.
//*****************************************************************************
	CIfacePtr<I>& operator=(			// Reference to this class.
		const CIfacePtr<I>& rSI)
	{
		// Only need to AddRef/Release if difference
		if (m_pI != rSI.m_pI)
		{
			if (m_pI != NULL)
				m_pI->Release();

			if ((m_pI = rSI.m_pI) != NULL)
				m_pI->AddRef();
		}
		return (*this);
	}

//*****************************************************************************
// Conversion to a normal interface pointer.
//*****************************************************************************
	operator I*()						// The contained interface ptr.
	{
		return (m_pI);
	}

//*****************************************************************************
// Deref
//*****************************************************************************
	I* operator->()						// The contained interface ptr.
	{
		_ASSERTE(m_pI != NULL);
		return (m_pI);
	}

//*****************************************************************************
// Address of
//*****************************************************************************
	I** operator&()						// Address of the contained iface ptr.
	{
		return (&m_pI);
	}

//*****************************************************************************
// Equality
//*****************************************************************************
	BOOL operator==(					// TRUE or FALSE.
		I			*pI) const			// An interface ptr to cmp against.
	{
		return (m_pI == pI);
	}

//*****************************************************************************
// In-equality
//*****************************************************************************
	BOOL operator!=(					// TRUE or FALSE.
		I			*pI) const			// An interface ptr to cmp against.
	{
		return (m_pI != pI);
	}

//*****************************************************************************
// Negation
//*****************************************************************************
	BOOL operator!() const				// TRUE if NULL, FALSE otherwise.
	{
		return (!m_pI);
	}

protected:
	I			*m_pI;					// The actual interface Ptr.
};


//*****************************************************************************
// Return the length of the specified BSTR.
//*****************************************************************************
inline ULONG BSTRLen(					// Length of the BSTR.
	BSTR		bstr)					// BSTR to get the length of.
{
	return (*(((ULONG *) bstr)-1));
}

//*****************************************************************************
// Compare two BSTRs, but don't pass NULL to _wcsicmp.
//*****************************************************************************
inline int BSTRiCmp(					// <0, 1, >0
	BSTR		p1,						// one BSTR
	BSTR		p2)						// other BSTR
{
	// if pointers equal, same string or both empty.
	if (p1 == p2)
		return 0;
	// if first string is empty, it is shorter, so less.
	if (p1 == 0)
		return -1;
	// if second string is empty, it is shorter, so first is greater.
	if (p2 == 0)
		return 1;
	// pass to library function.
	return _wcsicmp(p1, p2);
}

//*****************************************************************************
// This is a utility function to allocate a SafeArray.
//*****************************************************************************
inline SAFEARRAY *AllocSafeArrayLen(	// Return status.
	BYTE		*pData,					// Data to be placed in the array.
	size_t		iSize)					// Size of data.
{
	SAFEARRAYBOUND sBound;				// Used to fill out the bounds.
	SAFEARRAY	*pArray;				// Ptr to the new array.

	sBound.cElements = iSize;
	sBound.lLbound = 0;
	if ((pArray = SafeArrayCreate(VT_UI1, 1, &sBound)) != NULL)
		memcpy(pArray->pvData, (void *) pData, iSize);
	return (pArray);
}

//*****************************************************************************
// Get the # of bytes in the safe array.
//*****************************************************************************
inline int SafeArrayGetDatasize(		// Size of the SafeArray data.
	SAFEARRAY	*psArray)				// Pointer to the SafeArray.
{
	int			iElems = 0;				// # of elements in the array.
	int			i;						// Loop control.

	// Compute the # of elements in the array.
	for (i=0; i < psArray->cDims; ++i)
		iElems += psArray->rgsabound[i].cElements;

	// Return the size.
	return (iElems * psArray->cbElements);
}

//*****************************************************************************
// If your application is using exception handling, then define both of the
// macros here to do whatever you need.  Any components of CVariant that can
// fail (which will always be out of memory) will throw using this macro.
//*****************************************************************************
#ifndef __REPOS_EXCEPTIONS__
#define THROW_REPOS_EXCEPTION() {}
#endif

//*****************************************************************************
// Helper class for working with variant values.  This class is broken up
// into:
// * ctor's of every type which automatically set the variant with the right values.
// * assignment operators which will fill out a variant.
// * access operators to easily return certain types.
//*****************************************************************************
class CVariant : public VARIANT
{
public:

//*****************************************************************************
// Default ctor simply marks the variant as empty.
//*****************************************************************************
	CVariant()
	{
		::VariantInit(this);
	}

//*****************************************************************************
// Dtor will free the variant releasing memory and pointers.
//*****************************************************************************
	~CVariant()
	{
		::VariantClear(this);
	}

//*****************************************************************************
// Copy ctor
//*****************************************************************************

	CVariant(const CVariant& varSrc)
	{
		::VariantInit(this);
		::VariantCopy(this, const_cast<VARIANT*>(static_cast<const VARIANT*>(&varSrc)));
	}

//*****************************************************************************
// Equal operator
//*****************************************************************************
	CVariant& operator=(const CVariant& varSrc)
	{
		::VariantCopy(this, const_cast<VARIANT*>(static_cast<const VARIANT*>(&varSrc)));
	}

//*****************************************************************************
// Integer family.
//*****************************************************************************
	CVariant(BYTE byte)
	{
		::VariantInit(this);
		this->vt = VT_I1;
		this->bVal = byte;
	}

	CVariant(short val)
	{
		::VariantInit(this);
		this->vt = VT_I2;
		this->iVal = val;
	}

	CVariant(long lValNew)
	{
		::VariantInit(this);
		this->vt = VT_I4;
		this->lVal = lValNew;
	}

	CVariant(const int lValNew)
	{
		::VariantInit(this);
		this->vt = VT_I4;
		this->lVal = lValNew;
	}

	CVariant(unsigned short val)
	{
		::VariantInit(this);
		this->vt = VT_UI2;
		this->iVal = val;
	}

	CVariant(unsigned long lValNew)
	{
		::VariantInit(this);
		this->vt = VT_UI4;
		this->lVal = lValNew;
	}


//*****************************************************************************
// Float family.
//*****************************************************************************
	CVariant(float fltVal)
	{
		::VariantInit(this);
		this->vt = VT_R4;
		this->fltVal = fltVal;
	}

	CVariant(double dblVal)
	{
		::VariantInit(this);
		this->vt = VT_R8;
		this->dblVal = dblVal;
	}

	CVariant(SYSTEMTIME stDate)
	{
		::VariantInit(this);
		this->vt = VT_DATE;
		if (FAILED(SystemTimeToDate(stDate, &this->date)))
			this->vt = VT_EMPTY;
	}

	CVariant(FILETIME ftDate)
	{
		SYSTEMTIME	stDate;

		::VariantInit(this);
		this->vt = VT_DATE;
		if (FAILED(FileTimeToSystemTime(&ftDate, &stDate)) ||
			FAILED(SystemTimeToDate(stDate, &this->date)))
			this->vt = VT_EMPTY;
	}

	CVariant(TIMESTAMP_STRUCT tstmpDate)
	{
		::VariantInit(this);
		this->vt = VT_DATE;
		if (FAILED(TimeStampToDate(tstmpDate, &this->date)))
			this->vt = VT_EMPTY;
	}


//*****************************************************************************
// String family.  These will allocate a BSTR internally.  To be safe, you
// need to check for vt != VT_EMPTY to make sure a string was allocated.
//*****************************************************************************
#ifdef UNICODE
	CVariant(LPCTSTR szString)
	{
		::VariantInit(this);
		if (!szString)
		{
			this->vt = VT_NULL;
			this->bstrVal = NULL;
		}
		else if ((this->bstrVal = ::SysAllocString(szString)) != NULL)
			this->vt = VT_BSTR;
		else
		{
			this->vt = VT_EMPTY;
			THROW_REPOS_EXCEPTION();
		}
	}
#else
	CVariant(LPCTSTR szString)
	{
		::VariantInit(this);
		if (!szString)
		{
			this->vt = VT_NULL;
			this->bstrVal = NULL;
		}
		else
		{
			LPWSTR		szUStr;
			int iSize = _tcslen(szString);
	
			if ((szUStr = new WCHAR[iSize + 1]) == NULL ||
				::MultiByteToWideChar(CP_ACP, 0, szString, iSize + 1, szUStr, iSize + 1) == FALSE ||
				(this->bstrVal = ::SysAllocString(szUStr)) == NULL)
			{
				this->vt = VT_EMPTY;
				THROW_REPOS_EXCEPTION();
			}
			else
				this->vt = VT_BSTR;
			delete [] szUStr;
		}
	}
#endif

	CVariant(BSTR bstr)
	{
		::VariantInit(this);
		if (!bstr)
		{
			this->vt = VT_NULL;
			this->bstrVal = NULL;
		}
		else if ((this->bstrVal = ::SysAllocString(bstr)) != NULL)
			this->vt = VT_BSTR;
		else
		{
			this->vt = VT_EMPTY;
			THROW_REPOS_EXCEPTION();
		}
	}

	CVariant(BYTE *pbBuff, size_t iSize)
	{
		::VariantInit(this);
		if (!pbBuff)
		{
			this->vt = VT_NULL;
			this->bstrVal = NULL;
		}
		else 
			InitSafeArrayLen(pbBuff, iSize);
	}


//*****************************************************************************
// Assignment operators.
//*****************************************************************************

	const CVariant &operator=(BYTE byte)
	{
		::VariantClear(this);
		this->vt = VT_I1;
		this->bVal = byte;
		return (*this);
	}

	const CVariant &operator=(short val)
	{
		::VariantClear(this);
		this->vt = VT_I2;
		this->iVal = val;
		return (*this);
	}

	const CVariant &operator=(long lValNew)
	{
		::VariantClear(this);
		this->vt = VT_I4;
		this->lVal = lValNew;
		return (*this);
	}

	const CVariant &operator=(int lValNew)
	{
		::VariantClear(this);
		this->vt = VT_I4;
		this->lVal = lValNew;
		return (*this);
	}

	const CVariant &operator=(unsigned short val)
	{
		::VariantClear(this);
		this->vt = VT_UI2;
		this->iVal = val;
		return (*this);
	}

	const CVariant &operator=(unsigned long lValNew)
	{
		::VariantClear(this);
		this->vt = VT_UI4;
		this->lVal = lValNew;
		return (*this);
	}

	const CVariant &operator=(float fltVal)
	{
		::VariantClear(this);
		this->vt = VT_R4;
		this->fltVal = fltVal;
		return (*this);
	}

	const CVariant &operator=(double dblVal)
	{
		::VariantClear(this);
		this->vt = VT_R8;
		this->dblVal = dblVal;
		return (*this);
	}

	const CVariant &operator=(SYSTEMTIME stDate)
	{
		::VariantClear(this);
		this->vt = VT_DATE;
		if (FAILED(SystemTimeToDate(stDate, &this->date)))
			this->vt = VT_EMPTY;
		return (*this);
	}

	const CVariant &operator=(FILETIME ftDate)
	{
		SYSTEMTIME	stDate;

		::VariantClear(this);
		this->vt = VT_DATE;
		if (FAILED(FileTimeToSystemTime(&ftDate, &stDate)) ||
			FAILED(SystemTimeToDate(stDate, &this->date)))
			this->vt = VT_EMPTY;
		return (*this);
	}

	const CVariant &operator=(TIMESTAMP_STRUCT tstmpDate)
	{
		::VariantClear(this);
		this->vt = VT_DATE;
		if (FAILED(TimeStampToDate(tstmpDate, &this->date)))
			this->vt = VT_EMPTY;
		return (*this);
	}

#ifdef UNICODE
	const CVariant &operator=(LPCTSTR szString)
	{
		::VariantClear(this);
		if (!szString)
		{
			this->vt = VT_NULL;
			this->bstrVal = NULL;
		}
		else if ((this->bstrVal = SysAllocString(szString)) != NULL)
			this->vt = VT_BSTR;
		else
		{
			this->vt = VT_EMPTY;
			THROW_REPOS_EXCEPTION();
		}
		return (*this);
	}
#else
	const CVariant &operator=(LPCTSTR szString)
	{
		::VariantClear(this);
		if (!szString)
		{
			this->vt = VT_NULL;
			this->bstrVal = NULL;
		}
		else
		{
			LPWSTR		szUStr;
			int iSize = _tcslen(szString);
	
			if ((szUStr = new WCHAR[iSize + 1]) == NULL ||
				MultiByteToWideChar(CP_ACP, 0, szString, iSize + 1, szUStr, iSize + 1) == FALSE ||
				(this->bstrVal = SysAllocString(szUStr)) == NULL)
			{
				this->vt = VT_EMPTY;
				THROW_REPOS_EXCEPTION();
			}
			else
				this->vt = VT_BSTR;
			delete [] szUStr;
		}
		return (*this);
	}
#endif

	const CVariant &operator=(BSTR bstr)
	{
		::VariantClear(this);
		if (!bstr)
		{
			this->vt = VT_NULL;
			this->bstrVal = NULL;
		}
		else if ((this->bstrVal = ::SysAllocString(bstr)) != NULL)
			this->vt = VT_BSTR;
		else
		{
			this->vt = VT_EMPTY;
			THROW_REPOS_EXCEPTION();
		}
		return (*this);
	}


//*****************************************************************************
// Conversion functions.
// @future: These should handle things like fraction, millisecond, and DayOfWeek.
//*****************************************************************************

	static BOOL OleDateFromTm(WORD wYear, WORD wMonth, WORD wDay,
		WORD wHour, WORD wMinute, WORD wSecond, DATE& dtDest)
	{
		// Validate year and month (ignore day of week and milliseconds)
		if (wYear > 9999 || wMonth < 1 || wMonth > 12)
			return FALSE;

		//  Check for leap year and set the number of days in the month
		BOOL bLeapYear = ((wYear & 3) == 0) &&
			((wYear % 100) != 0 || (wYear % 400) == 0);

		int nDaysInMonth =
			rgMonthDays[wMonth] - rgMonthDays[wMonth-1] +
			((bLeapYear && wDay == 29 && wMonth == 2) ? 1 : 0);

		// Finish validating the date
		if (wDay < 1 || wDay > nDaysInMonth ||
			wHour > 23 || wMinute > 59 ||
			wSecond > 59)
		{
			return FALSE;
		}

		// Cache the date in days and time in fractional days
		long nDate;
		double dblTime;

		//It is a valid date; make Jan 1, 1AD be 1
		nDate = wYear*365L + wYear/4 - wYear/100 + wYear/400 +
			rgMonthDays[wMonth-1] + wDay;

		//  If leap year and it's before March, subtract 1:
		if (wMonth <= 2 && bLeapYear)
			--nDate;

		//  Offset so that 12/30/1899 is 0
		nDate -= 693959L;

		dblTime = (((long)wHour * 3600L) +  // hrs in seconds
			((long)wMinute * 60L) +  // mins in seconds
			((long)wSecond)) / 86400.;

		dtDest = (double) nDate + ((nDate >= 0) ? dblTime : -dblTime);

		return TRUE;
	}

	static BOOL TmFromOleDate(DATE dtSrc, struct tm& tmDest)
	{
		// The legal range does not actually span year 0 to 9999.
		if (dtSrc > MAX_DATE || dtSrc < MIN_DATE) // about year 100 to about 9999
			return FALSE;

		long nDays;             // Number of days since Dec. 30, 1899
		long nDaysAbsolute;     // Number of days since 1/1/0
		long nSecsInDay;        // Time in seconds since midnight
		long nMinutesInDay;     // Minutes in day

		long n400Years;         // Number of 400 year increments since 1/1/0
		long n400Century;       // Century within 400 year block (0,1,2 or 3)
		long n4Years;           // Number of 4 year increments since 1/1/0
		long n4Day;             // Day within 4 year block
								//  (0 is 1/1/yr1, 1460 is 12/31/yr4)
		long n4Yr;              // Year within 4 year block (0,1,2 or 3)
		BOOL bLeap4 = TRUE;     // TRUE if 4 year block includes leap year

		double dblDate = dtSrc; // tempory serial date

		// If a valid date, then this conversion should not overflow
		nDays = (long)dblDate;

		// Round to the second
		dblDate += ((dtSrc > 0.0) ? HALF_SECOND : -HALF_SECOND);

		nDaysAbsolute = (long)dblDate + 693959L; // Add days from 1/1/0 to 12/30/1899

		dblDate = fabs(dblDate);
		nSecsInDay = (long)((dblDate - floor(dblDate)) * 86400.);

		// Calculate the day of week (sun=1, mon=2...)
		//   -1 because 1/1/0 is Sat.  +1 because we want 1-based
		tmDest.tm_wday = (int)((nDaysAbsolute - 1) % 7L) + 1;

		// Leap years every 4 yrs except centuries not multiples of 400.
		n400Years = (long)(nDaysAbsolute / 146097L);

		// Set nDaysAbsolute to day within 400-year block
		nDaysAbsolute %= 146097L;

		// -1 because first century has extra day
		n400Century = (long)((nDaysAbsolute - 1) / 36524L);

		// Non-leap century
		if (n400Century != 0)
		{
			// Set nDaysAbsolute to day within century
			nDaysAbsolute = (nDaysAbsolute - 1) % 36524L;

			// +1 because 1st 4 year increment has 1460 days
			n4Years = (long)((nDaysAbsolute + 1) / 1461L);

			if (n4Years != 0)
				n4Day = (long)((nDaysAbsolute + 1) % 1461L);
			else
			{
				bLeap4 = FALSE;
				n4Day = (long)nDaysAbsolute;
			}
		}
		else
		{
			// Leap century - not special case!
			n4Years = (long)(nDaysAbsolute / 1461L);
			n4Day = (long)(nDaysAbsolute % 1461L);
		}

		if (bLeap4)
		{
			// -1 because first year has 366 days
			n4Yr = (n4Day - 1) / 365;

			if (n4Yr != 0)
				n4Day = (n4Day - 1) % 365;
		}
		else
		{
			n4Yr = n4Day / 365;
			n4Day %= 365;
		}

		// n4Day is now 0-based day of year. Save 1-based day of year, year number
		tmDest.tm_yday = (int)n4Day + 1;
		tmDest.tm_year = n400Years * 400 + n400Century * 100 + n4Years * 4 + n4Yr;

		// Handle leap year: before, on, and after Feb. 29.
		if (n4Yr == 0 && bLeap4)
		{
			// Leap Year
			if (n4Day == 59)
			{
				/* Feb. 29 */
				tmDest.tm_mon = 2;
				tmDest.tm_mday = 29;
				goto DoTime;
			}

			// Pretend it's not a leap year for month/day comp.
			if (n4Day >= 60)
				--n4Day;
		}

		// Make n4DaY a 1-based day of non-leap year and compute
		//  month/day for everything but Feb. 29.
		++n4Day;

		// Month number always >= n/32, so save some loop time */
		for (tmDest.tm_mon = (n4Day >> 5) + 1;
			n4Day > rgMonthDays[tmDest.tm_mon]; tmDest.tm_mon++);

		tmDest.tm_mday = (int)(n4Day - rgMonthDays[tmDest.tm_mon-1]);

	DoTime:
		if (nSecsInDay == 0)
			tmDest.tm_hour = tmDest.tm_min = tmDest.tm_sec = 0;
		else
		{
			tmDest.tm_sec = (int)nSecsInDay % 60L;
			nMinutesInDay = nSecsInDay / 60L;
			tmDest.tm_min = (int)nMinutesInDay % 60;
			tmDest.tm_hour = (int)nMinutesInDay / 60;
		}

		return TRUE;
	}

	static HRESULT SystemTimeToDate(		
		SYSTEMTIME	&stDate,				
		DATE		*pdtDate)			
	{
		if (OleDateFromTm(stDate.wYear, stDate.wMonth, stDate.wDay, stDate.wHour, 
				stDate.wMinute, stDate.wSecond, *pdtDate))
			return (S_OK);

		return (E_FAIL);
	}

	static HRESULT TimeStampToDate(		
		TIMESTAMP_STRUCT &tstmpDate,				
		DATE		*pdtDate)			
	{
		if (OleDateFromTm(tstmpDate.year, tstmpDate.month, tstmpDate.day, tstmpDate.hour, 
				tstmpDate.minute, tstmpDate.second, *pdtDate))
			return (S_OK);

		return (E_FAIL);
	}

	static HRESULT DateToSystemTime(
		DATE		date,		
		SYSTEMTIME	*pstDate)			
	{
		tm	tmDate;

		if (!TmFromOleDate(date, tmDate))
			return (E_FAIL);

		pstDate->wYear = tmDate.tm_year;
		pstDate->wMonth = tmDate.tm_mon;
		pstDate->wDayOfWeek = 0; 
		pstDate->wDay = tmDate.tm_mday; 
		pstDate->wHour = tmDate.tm_hour;
		pstDate->wMinute = tmDate.tm_min;
		pstDate->wSecond = tmDate.tm_sec;
		pstDate->wMilliseconds = 0;
		
		return (S_OK);
	}

	static HRESULT DateToTimeStamp(
		DATE		date,		
		TIMESTAMP_STRUCT *ptstmpDate)			
	{
		tm	tmDate;

		if (!TmFromOleDate(date, tmDate))
			return (E_FAIL);

		ptstmpDate->year = tmDate.tm_year;
		ptstmpDate->month = tmDate.tm_mon;
		ptstmpDate->day = tmDate.tm_mday; 
		ptstmpDate->hour = tmDate.tm_hour;
		ptstmpDate->minute = tmDate.tm_min;
		ptstmpDate->second = tmDate.tm_sec;
		ptstmpDate->fraction = 0;
		
		return (S_OK);
	}

//*****************************************************************************
// This one is a little misleading, for example it won't compare the contents
// of two BSTR's to see if they match, you'd have to have the same BSTR used
// into two values.  This is consistent with MFC, however.
//*****************************************************************************
	BOOL operator==(const VARIANT& varSrc) const
	{
		return (vt == varSrc.vt &&
				memcmp(((BYTE *) this) + 8, ((BYTE *) &varSrc) + 8,
							sizeof(VARIANT) - 8) == 0);
	}

	BOOL operator!=(const VARIANT&varSrc) const
	{
		return (!(*this == varSrc));
	}


//*****************************************************************************
// Access operators.
//*****************************************************************************

	BOOL IsEmpty()
	{ return (this->vt == VT_EMPTY); }

	operator int()
	{
		_ASSERTE(this->vt == VT_I2 || this->vt == VT_I4 || this->vt == VT_BOOL);
		if (this->vt == VT_I2) 
			return (this->iVal);
		else if (this->vt == VT_BOOL)
			return (this->boolVal);
		return (this->lVal);
	}

	operator unsigned int()
	{
		_ASSERTE(this->vt == VT_UI1 || this->vt == VT_UI2 || this->vt == VT_UI4 || this->vt == VT_BOOL);
		if (this->vt == VT_UI4)
			return (this->lVal);
		else if (this->vt == VT_UI1)
			return (this->bVal);
		else if (this->vt == VT_UI2) 
			return (this->iVal);
		return ((unsigned int) this->boolVal);
	}

	operator float()
	{
		_ASSERTE(this->vt == VT_R4);
		return (this->fltVal);
	}

	operator double()
	{
		_ASSERTE(this->vt == VT_R4 || this->vt == VT_R8);
		if (this->vt == VT_R4) 
			return (this->fltVal);
		return (this->dblVal);
	}

	operator BSTR()
	{
		_ASSERTE(this->vt == VT_BSTR || this->vt == VT_NULL);
		return (this->bstrVal);
	}

//*****************************************************************************
// Conversion functions for wide/multi-byte.
//*****************************************************************************
	HRESULT GetString(LPSTR szOut, int iMax)
	{
		if (this->vt == VT_NULL)
			*szOut = '\0';
		else if (WideCharToMultiByte(CP_ACP, 0, this->bstrVal , -1, szOut, iMax,
									NULL, NULL) == FALSE)
			return (E_FAIL);
		return (S_OK);
	}

	HRESULT GetString(LPWSTR szOut, int iMax)
	{
		int			iLen = min(iMax, *(long *)(this->bstrVal - sizeof(DWORD)));
		wcsncpy(szOut, this->bstrVal, iLen);
		szOut[iLen] = '\0';
		return (S_OK);
	}

//*****************************************************************************
// Conversion functions for SYSTEMTIME and TIMESTAMP_STRUCT.
//*****************************************************************************
	HRESULT	GetDate(SYSTEMTIME *pstDate)
	{
		if ((vt != VT_DATE) ||
				FAILED(DateToSystemTime(date, pstDate)))
			return (E_FAIL);
		return (S_OK);
	}

	HRESULT	GetDate(TIMESTAMP_STRUCT *ptstmpDate)
	{
		if ((vt != VT_DATE) ||
				FAILED(DateToTimeStamp(date, ptstmpDate)))
			return (E_FAIL);
		return (S_OK);
	}


//*****************************************************************************
// Clear the variant.
//*****************************************************************************
	void Clear()
	{
		::VariantClear(this);
	}

//*****************************************************************************
// Helper function to init a safe array.  This will leave the vt value
// as VT_EMPTY if the function fails.
//*****************************************************************************
	SAFEARRAY * InitSafeArrayLen(BYTE *pData, size_t iSize)
	{
		if ((this->parray = AllocSafeArrayLen(pData, iSize)) != NULL)
			this->vt = VT_UI1 | VT_ARRAY;
		else
		{
			this->vt = VT_EMPTY;
			THROW_REPOS_EXCEPTION();
		}
		return (this->parray);
	}
};

//*****************************************************************************
// This code adds more helpers on top of CVariant that are Repository specific.
//*****************************************************************************
class CRepVariant : public CVariant
{
public:
	CRepVariant() :
		CVariant()
	{
	}

	CRepVariant(REFOBJID objid)
	{
		::VariantInit(this);
		InitSafeArrayLen((BYTE *)&objid, sizeof(OBJID));
	}

	CRepVariant(REFGUID guid)
	{
		::VariantInit(this);
		InitSafeArrayLen((BYTE *)&guid, sizeof(GUID));
	}

	CRepVariant(INTID intid)
	{
		::VariantInit(this);
		InitSafeArrayLen((BYTE *)&intid, sizeof(INTID));
	}

	CRepVariant(VERSIONID versionid)
	{
		SAFEARRAYBOUND	rgsabound[3];
		
		::VariantInit(this);

		// Construct the bounds array.
		rgsabound[0].lLbound = 0;
		rgsabound[0].cElements = sizeof(INTID);
		rgsabound[1].lLbound = 0;
		rgsabound[1].cElements = sizeof(BRANCHID);
		rgsabound[2].lLbound = 0;
		rgsabound[2].cElements = sizeof(VERSIONNUM);

		// Create SafeArray.
		if ((this->parray = SafeArrayCreate(VT_UI1, 3, rgsabound)) == NULL)
#pragma warning(disable : 4390)
			THROW_REPOS_EXCEPTION();
		this->vt = VT_ARRAY|VT_UI1;		// Array of bytes.
#pragma warning(default : 4390)

		// Copy the data and return.
		*((VERSIONID *) this->parray->pvData) = versionid;
	}

	CRepVariant &operator=(REFOBJID objid)
	{
		::VariantClear(this);
		InitSafeArrayLen((BYTE *)&objid, sizeof(OBJID));
		return (*this);
	}

	CRepVariant &operator=(REFGUID guid)
	{
		::VariantClear(this);
		InitSafeArrayLen((BYTE *)&guid, sizeof(GUID));
		return (*this);
	}

	CRepVariant &operator=(INTID intid)
	{
		::VariantClear(this);
		InitSafeArrayLen((BYTE *)&intid, sizeof(INTID));
		return (*this);
	}

	CRepVariant &operator=(VERSIONID versionid)
	{
		SAFEARRAYBOUND	rgsabound[3];
		
		::VariantClear(this);

		// Construct the bounds array.
		rgsabound[0].lLbound = 0;
		rgsabound[0].cElements = sizeof(INTID);
		rgsabound[1].lLbound = 0;
		rgsabound[1].cElements = sizeof(BRANCHID);
		rgsabound[2].lLbound = 0;
		rgsabound[2].cElements = sizeof(VERSIONNUM);

		// Create SafeArray.
		if ((this->parray = SafeArrayCreate(VT_UI1, 3, rgsabound)) == NULL)
#pragma warning(disable : 4390)
			THROW_REPOS_EXCEPTION();
		this->vt = VT_ARRAY|VT_UI1;		// Array of bytes.
#pragma warning(default : 4390)

		// Copy the data and return.
		*((VERSIONID *) this->parray->pvData) = versionid;

		return (*this);
	}

	operator OBJID()
	{
		OBJID	objid;
		_ASSERTE(((this->vt & VT_UI1) || (this->vt & VT_UI4)) && (this->vt & VT_ARRAY) && 
					SafeArrayGetDatasize(this->parray) == sizeof(OBJID));
		memcpy(&objid, parray->pvData, sizeof(OBJID));
		return (objid);
	}

	operator GUID()
	{
		GUID	guid;
		_ASSERTE(((this->vt & VT_UI1) || (this->vt & VT_UI4)) && (this->vt & VT_ARRAY) && 
					SafeArrayGetDatasize(this->parray) == sizeof(GUID));
		memcpy(&guid, parray->pvData, sizeof(GUID));
		return (guid);
	}

	operator INTID()
	{
		INTID	intid;
		_ASSERTE((this->vt == (VT_UI1 | VT_ARRAY) || this->vt == (VT_UI4 | VT_ARRAY)) && 
					SafeArrayGetDatasize(this->parray) == sizeof(INTID));
		memcpy(&intid, parray->pvData, sizeof(INTID));
		return (intid);
	}

	operator VERSIONID()
	{
		VERSIONID	versionid;
		_ASSERTE((this->vt == (VT_UI1 | VT_ARRAY) || this->vt == (VT_UI4 | VT_ARRAY)) &&
					(SafeArrayGetDatasize(this->parray) == sizeof(VERSIONID)) &&
					(SafeArrayGetDim(this->parray) == 3));
		memcpy(&versionid, parray->pvData, sizeof(VERSIONID));
		return (versionid);
	}

	operator struct tagVARIANT*()
	{
		return ((VARIANT *)this);
	}

//*****************************************************************************
// Returns safe array formatted in "0x1234" format, mostly for debugging.
//*****************************************************************************
	LPCTSTR GetHexString(LPTSTR szStr, int iMax)
	{
		int			i, iSize;
		char		*p;
		char		ch;
		LPCTSTR		szSave = szStr;
		
		_ASSERTE((this->vt == (VT_UI1 | VT_ARRAY) || this->vt == (VT_UI4 | VT_ARRAY)));
		_ASSERTE(this->IsEmpty() == FALSE);

		// Make sure the output string has enough room.
		if ((iSize = SafeArrayGetDatasize(this->parray)) * 2 + 3 > iMax)
		{
			_ASSERTE(0);
			return (NULL);
		}

		// Setup string with prefix.
		_tcscpy(szStr, "0x");
		szStr += 2;

		// Convert each byte to the character equivalent.
		for (i=0, p=(char *)this->parray->pvData;  i<iSize;  i++, p++)
		{
			ch = (*p & 0xf0) >> 4;
			if (ch <= 9)
				*szStr = ch + '0';
			else
				*szStr = ch - 10 + 'A';
			++szStr;
			ch = *p & 0x0f;
			if (ch <= 9)
				*szStr = ch + '0';
			else
				*szStr = ch - 10 + 'A';
			++szStr;
		}
		*szStr = 0;
		return (szSave);
	}
};

//*****************************************************************************
// Helper class for transaction management.
//*****************************************************************************
class CTimAutoTransaction
{
public:
	CTimAutoTransaction(IRepository *pRepos) : m_State(tNone) 
		{ pRepos->QueryInterface(IID_IRepositoryTransaction, (void**)&m_pTrans); }
	
	~CTimAutoTransaction()
	{ if (m_State == tTrans)
		Abort();
	  m_pTrans->Release();
	  m_pTrans = NULL;
	}

	HRESULT Begin() {HRESULT hr=m_pTrans->Begin(); m_State = tTrans; return hr;}
	HRESULT Commit() {HRESULT hr=m_pTrans->Commit(); m_State = tNone; return hr;}
	HRESULT Abort() {HRESULT hr=m_pTrans->Abort(); m_State = tNone; return hr;}

	IRepositoryTransaction	*m_pTrans;
	enum {tNone, tTrans}	m_State;
};

#endif // __OLEUTIL_H__
