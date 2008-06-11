// PanningView.cpp : Implementation of CPanningViewApp and DLL registration.

#include "stdafx.h"
#include "PanningView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CPanningViewApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0xB6ED16CA, 0x512F, 0x48B7, { 0xB5, 0xDB, 0x1C, 0x6, 0x48, 0x21, 0xF7, 0xDB } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CPanningViewApp::InitInstance - DLL initialization

BOOL CPanningViewApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// CPanningViewApp::ExitInstance - DLL termination

int CPanningViewApp::ExitInstance()
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
