#include "stdafx.h"
#include "Formatter.h"

namespace GMEConsole
{
	CString Formatter::MakeObjectHyperlink(const CString & text, const CString& objectId)
	{
		CString result("<a href=\"mga:id-");		
		result+= objectId;
		result+=  "</a>";
		
		return result;
	}

	CString Formatter::MakeColored(const CString & text, COLORREF color)
	{
		CString result;
		result.Format("<font color=\"#%02X%02X%02X\"> %s </font>", (int)GetRValue(color), (int)GetGValue(color),(int)GetBValue(color), text);
		return result;
	}
}

/*
<font color="#ffffff">
My very first html page RGB
</font>
*/