// ObjectInspector.cpp : Implementation of CObjectInspectorApp and DLL registration.

#include "stdafx.h"
#include "ObjectInspector.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CObjectInspectorApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x92b54998, 0x8e88, 0x41a2, { 0x92, 0x4f, 0x73, 0x54, 0xca, 0xd1, 0x45, 0x65 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


////////////////////////////////////////////////////////////////////////////
// CObjectInspectorApp::InitInstance - DLL initialization

BOOL CObjectInspectorApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		SetRegistryKey(_T("GME\\GUI\\ObjectInspector"));
	}

	return bInit;
}


////////////////////////////////////////////////////////////////////////////
// CObjectInspectorApp::ExitInstance - DLL termination

int CObjectInspectorApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}


/////////////////////////////////////////////////////////////////////////////
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


/////////////////////////////////////////////////////////////////////////////
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
