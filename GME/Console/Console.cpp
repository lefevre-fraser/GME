// Console.cpp : Implementation of CConsoleApp and DLL registration.

#include "stdafx.h"
#include "Console.h"
#include <initguid.h>
#include "Console_i.c"
#include "ScriptHost.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CConsoleApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x339fd307, 0x717b, 0x4698, { 0xac, 0x13, 0x4a, 0xcc, 0xcf, 0x5d, 0x4c, 0x91 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


////////////////////////////////////////////////////////////////////////////
// CConsoleApp::InitInstance - DLL initialization

BOOL CConsoleApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();
	if (!InitATL())
		return FALSE;


	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}


////////////////////////////////////////////////////////////////////////////
// CConsoleApp::ExitInstance - DLL termination

int CConsoleApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	_Module.Term();


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

	return _Module.RegisterServer(TRUE);

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

	_Module.UnregisterServer(TRUE); //TRUE indicates that typelib is unreg'd

	return NOERROR;
}


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_ScriptHost, CScriptHost)
END_OBJECT_MAP()

STDAPI DllCanUnloadNow(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return (AfxDllCanUnloadNow()==S_OK && _Module.GetLockCount()==0) ? S_OK : S_FALSE; 
} 
/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(AfxDllGetClassObject(rclsid, riid, ppv) == S_OK)
		return S_OK;
	return _Module.GetClassObject(rclsid, riid, ppv);
}

BOOL CConsoleApp::InitATL()
{
	_Module.Init(ObjectMap, AfxGetInstanceHandle());
	return TRUE;

}
