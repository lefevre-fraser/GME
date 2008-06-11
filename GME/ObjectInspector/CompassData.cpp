// CompassData.cpp: implementation of the CCompassData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "objectinspector.h"
#include "CompassData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


bool CCompassData::ParseCompassValue(CString strValue, UINT &uValue)
{
	char szDelimiters[]=",;\t ";
	char* token=NULL;
						
	char *str=new char[strValue.GetLength()+1];
	strcpy(str,strValue);

	token=strtok(str,szDelimiters);

	bool bIsProcessed=false;
	UINT uCompassTemp=0;

	while(token!=NULL)
	{		
		bIsProcessed=false;
		
		CString strTemp;
		strTemp="North";
		if(!strTemp.CompareNoCase(token))
		{
			uCompassTemp|=CMPS_NORTH;
			bIsProcessed=true;
		}

		strTemp="South";
		if(!strTemp.CompareNoCase(token))
		{
			uCompassTemp|=CMPS_SOUTH;
			bIsProcessed=true;
		}
		strTemp="East";
		if(!strTemp.CompareNoCase(token))
		{
			uCompassTemp|=CMPS_EAST;
			bIsProcessed=true;
		}

		strTemp="West";
		if(!strTemp.CompareNoCase(token))
		{
			uCompassTemp|=CMPS_WEST;
			bIsProcessed=true;
		}

		strTemp="Northeast";
		if(!strTemp.CompareNoCase(token))
		{
			uCompassTemp|=CMPS_NORTHEAST;
			bIsProcessed=true;
		}

		strTemp="Southeast";
		if(!strTemp.CompareNoCase(token))
		{
			uCompassTemp|=CMPS_SOUTHEAST;
			bIsProcessed=true;
		}

		strTemp="SouthWest";
		if(!strTemp.CompareNoCase(token))
		{
			uCompassTemp|=CMPS_SOUTHWEST;
			bIsProcessed=true;
		}

		strTemp="NorthWest";
		if(!strTemp.CompareNoCase(token))
		{
			uCompassTemp|=CMPS_NORTHWEST;
			bIsProcessed=true;
		}
		strTemp="Center";
		if(!strTemp.CompareNoCase(token))
		{
			uCompassTemp|=CMPS_CENTER;
			bIsProcessed=true;
		}

		if(!bIsProcessed)break;
		// Next token
		token=strtok(NULL,szDelimiters);
	}
	delete[] str;

	if(bIsProcessed) uValue=uCompassTemp;

	return bIsProcessed;
}

CString CCompassData::toString(UINT uData)
{

	CString strRetVal;

	if(uData&CMPS_NORTH)
	{
		strRetVal+="North;";
	}

	if(uData&CMPS_EAST)
	{
		strRetVal+="East;";
	}
	
	if(uData&CMPS_SOUTH)
	{
		strRetVal+="South;";
	}

	if(uData&CMPS_WEST)
	{
		strRetVal+="West;";
	}

	if(uData&CMPS_NORTHEAST)
	{
		strRetVal+="Northeast;";
	}

	if(uData&CMPS_SOUTHEAST)
	{
		strRetVal+="Southeast;";
	}

	if(uData&CMPS_SOUTHWEST)
	{
		strRetVal+="Southwest;";
	}

	if(uData&CMPS_NORTHWEST)
	{
		strRetVal+="Northwest;";
	}

	if(uData&CMPS_CENTER)
	{
		strRetVal+="Center;";
	}

	// Trimming the last semicolon
	if(!strRetVal.IsEmpty())
	{
		strRetVal=strRetVal.Left(strRetVal.GetLength()-1);
	}

	return strRetVal;

}

bool CCompassData::bIsSingle(UINT uData)
{
	int count=0;
	if(uData&CMPS_NORTH)
	{
		count++;
	}

	if(uData&CMPS_EAST)
	{
		count++;
	}
	
	if(uData&CMPS_SOUTH)
	{
		count++;
	}

	if(uData&CMPS_WEST)
	{
		count++;
	}

	if(uData&CMPS_NORTHEAST)
	{
		count++;
	}

	if(uData&CMPS_SOUTHEAST)
	{
		count++;
	}

	if(uData&CMPS_SOUTHWEST)
	{
		count++;
	}

	if(uData&CMPS_NORTHWEST)
	{
		count++;
	}

	if(uData&CMPS_CENTER)
	{
		count++;
	}
	return (count<=1);
}


// Convarts MGA format to compass value. 
// The MGA format is a number from 0 (NORTH) to 8 (CENTER) clockwise.
UINT CCompassData::ParseMgaCompassValueOption(const CString &strValue)
{
		UINT uCompassTemp=0;
		
		CString strTemp;
		strTemp="0";
		if(!strTemp.CompareNoCase(strValue))
		{
			uCompassTemp|=CMPS_NORTH;
		}

		strTemp="4";
		if(!strTemp.CompareNoCase(strValue))
		{
			uCompassTemp|=CMPS_SOUTH;
		}
		strTemp="2";
		if(!strTemp.CompareNoCase(strValue))
		{
			uCompassTemp|=CMPS_EAST;
		}

		strTemp="6";
		if(!strTemp.CompareNoCase(strValue))
		{
			uCompassTemp|=CMPS_WEST;
		}

		strTemp="1";
		if(!strTemp.CompareNoCase(strValue))
		{
			uCompassTemp|=CMPS_NORTHEAST;
		}

		strTemp="3";
		if(!strTemp.CompareNoCase(strValue))
		{
			uCompassTemp|=CMPS_SOUTHEAST;
		}

		strTemp="5";
		if(!strTemp.CompareNoCase(strValue))
		{
			uCompassTemp|=CMPS_SOUTHWEST;
		}

		strTemp="7";
		if(!strTemp.CompareNoCase(strValue))
		{
			uCompassTemp|=CMPS_NORTHWEST;
		}
		strTemp="8";
		if(!strTemp.CompareNoCase(strValue))
		{
			uCompassTemp|=CMPS_CENTER;
		}

		ASSERT(uCompassTemp); // Invalid strValue. Value must be in {0..8}.

		return uCompassTemp;
}


// Converts MGA format to compass value. 
// MGA format here (Yes, another invention for the same thing !!!): "neswNESW"
void CCompassData::ParseMgaCompassValueCheck(const CString &strValue, UINT &uSmallCaseValue, UINT &uCapitalValue)
{
	uSmallCaseValue=0;
	uCapitalValue=0;

// Small case value
	if(strValue.Find('n')!=-1)
	{
		uSmallCaseValue|=CMPS_NORTH;
	}

	if(strValue.Find('e')!=-1)
	{
		uSmallCaseValue|=CMPS_EAST;
	}

	if(strValue.Find('s')!=-1)
	{
		uSmallCaseValue|=CMPS_SOUTH;
	}

	if(strValue.Find('w')!=-1)
	{
		uSmallCaseValue|=CMPS_WEST;
	}

// Capital value
	if(strValue.Find('N')!=-1)
	{
		uCapitalValue|=CMPS_NORTH;
	}

	if(strValue.Find('E')!=-1)
	{
		uCapitalValue|=CMPS_EAST;
	}

	if(strValue.Find('S')!=-1)
	{
		uCapitalValue|=CMPS_SOUTH;
	}

	if(strValue.Find('W')!=-1)
	{
		uCapitalValue|=CMPS_WEST;
	}
}


void CCompassData::toMgaStringCheck(CString& strValue, UINT uData, bool bIsCapital)
{
	strValue.Empty();

	if(uData&CMPS_NORTH)
	{
		strValue+=bIsCapital?"N":"n";	
	}
	if(uData&CMPS_EAST)
	{
		strValue+=bIsCapital?"E":"e";
	}
	if(uData&CMPS_SOUTH)
	{
		strValue+=bIsCapital?"S":"s";
	}

	if(uData&CMPS_WEST)
	{
		strValue+=bIsCapital?"W":"w";
	}

}

void CCompassData::toMgaStringOption(CString& strValue, UINT uData)
{
	ASSERT(bIsSingle(uData));

	UINT uMgaValue;

	if(uData&CMPS_NORTH)
	{
		uMgaValue=0;
	}
	else if(uData&CMPS_EAST)
	{
		uMgaValue=2;
	}
	else if(uData&CMPS_SOUTH)
	{
		uMgaValue=4;
	}

	else if(uData&CMPS_WEST)
	{
		uMgaValue=6;
	}

	else if(uData&CMPS_NORTHEAST)
	{
		uMgaValue=1;
	}

	else if(uData&CMPS_SOUTHEAST)
	{
		uMgaValue=3;
	}

	else if(uData&CMPS_SOUTHWEST)
	{
		uMgaValue=5;
	}

	else if(uData&CMPS_NORTHWEST)
	{
		uMgaValue=7;
	}

	else if(uData&CMPS_CENTER)
	{
		uMgaValue=8;
	}
	else
	{
		ASSERT(0); // Invalid compass value
	}

	strValue.Format("%u",uMgaValue);
}