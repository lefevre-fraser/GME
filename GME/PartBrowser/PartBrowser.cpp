// PartBrowser.cpp : Implementation of CPartBrowserApp and DLL registration.

#include "stdafx.h"
#include "PartBrowser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CPartBrowserApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0xEA3F7431, 0x913A, 0x421F, { 0x9B, 0x9C, 0xBE, 0xB6, 0xA7, 0x35, 0x28, 0x5A } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CPartBrowserApp::InitInstance - DLL initialization

BOOL CPartBrowserApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// CPartBrowserApp::ExitInstance - DLL termination

int CPartBrowserApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
