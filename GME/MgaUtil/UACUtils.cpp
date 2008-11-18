#include "stdafx.h"
#include "UACUtils.h"

bool CUACUtils::isVistaOrLater()
{ 
	OSVERSIONINFO osvi;

	::ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    GetVersionEx(&osvi);

	return (osvi.dwMajorVersion >= 6);
}

