// GMEView.cpp : Implementation of CGMEViewApp and DLL registration.

#include "stdafx.h"
#include "GMEView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGMEViewApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0xE8F51618, 0x624F, 0x41D6, { 0xB3, 0x8F, 0x1, 0xC8, 0x1, 0x82, 0xAE, 0xDC } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CGMEViewApp::InitInstance - DLL initialization

BOOL CGMEViewApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// CGMEViewApp::ExitInstance - DLL termination

int CGMEViewApp::ExitInstance()
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
