#include "stdafx.h"
#include "DotNetUtils.h"
#include <MSCOREE.H>
#include <corerror.h>
#include "resource.h"

#include "atlsafe.h"

#import "C:\\windows\\Microsoft.NET\\Framework\\v2.0.50727\\mscorlib.tlb" auto_rename
using namespace mscorlib;

// http://blogs.msdn.com/oldnewthing/archive/2004/10/25/247180.aspx
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)



typedef HRESULT (WINAPI * tCorBindToRuntimeEx)(LPWSTR,LPWSTR,DWORD,REFCLSID,REFIID,LPVOID*);


int CDotNetUtils::CallManagedFunction(BSTR assemblyPath, BSTR typeName, BSTR methodName, int mode)
{
	//
	// Query 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\NET Framework Setup\NDP\v2.0.50727\Install' DWORD value
	// See http://support.microsoft.com/kb/318785/ (http://support.microsoft.com/kb/318785/) for more information on .NET runtime versioning information
	// For some code, see: http://astebner.sts.winisp.net/Tools/detectFX.cpp.txt, http://blogs.msdn.com/astebner/archive/2004/09/18/231253.aspx
	//
	HKEY key = NULL;
	DWORD lastError = 0;
	lastError = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\NET Framework Setup\\NDP\\v2.0.50727"), 0, KEY_QUERY_VALUE, &key);
	if (lastError != ERROR_SUCCESS) {
		AfxMessageBox("CallManagedFunction .NET version discovery: Error opening HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\NET Framework Setup\\NDP\\v2.0.50727");
		return 1;
	}

	DWORD type;
	BYTE data[4];
	DWORD len = sizeof(data);
	lastError = RegQueryValueEx(key, TEXT("Install"), NULL, &type, data, &len);

	if (lastError != ERROR_SUCCESS) {
		RegCloseKey(key);
		AfxMessageBox("CallManagedFunction .NET version discovery: Error querying HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\NET Framework Setup\\NDP\\v2.0.50727\\Install");
		return 2;
	}

	RegCloseKey(key);

	// Was Install DWORD key value == 1 ??
	if(data[0] == 1) {
		TRACE(".NET Framework v2.0.50727 is installed");
	} else {
		AfxMessageBox("CallManagedFunction: .NET Framework v2.0.50727 is NOT installed");
		return 3;
	}

	HMODULE cor = LoadLibrary("mscoree.dll");
	if (!cor) {
		AfxMessageBox("CallManagedFunction: couldn't load mscoree.dll (.NET Framework provider dll)");
		return 3;
	}
	tCorBindToRuntimeEx pCorBindToRuntimeEx = (tCorBindToRuntimeEx) GetProcAddress(cor, "CorBindToRuntimeEx");
	if (!pCorBindToRuntimeEx) {
		AfxMessageBox("CallManagedFunction: couldn't load CorBindToRuntimeEx function entry from mscoree.dll (.NET Framework provider dll)");
		FreeLibrary(cor);
		return 3;
	}
	LPWSTR pszVer = L"v2.0.50727";
	LPWSTR pszFlavor = L"wks";
	ICorRuntimeHost *pHost = NULL;

	HRESULT hr = pCorBindToRuntimeEx(pszVer,
									 pszFlavor,
									 STARTUP_LOADER_OPTIMIZATION_SINGLE_DOMAIN | STARTUP_CONCURRENT_GC,
									 CLSID_CorRuntimeHost,
									 IID_ICorRuntimeHost,
									 (void **)&pHost);

	if (!SUCCEEDED(hr)) {
		CString csTemp;
		if (hr == CLR_E_SHIM_RUNTIMELOAD)
			csTemp.Format("CallManagedFunction: CorBindToRuntimeEx failed because of mismatching .NET Framework version (CLR_E_SHIM_RUNTIMELOAD).");
		else
			csTemp.Format("CallManagedFunction: CorBindToRuntimeEx failed: %ld", hr);
		AfxMessageBox(csTemp);
		FreeLibrary(cor);
		return 1;
	}

	TRACE("Loaded version 2.0.50727 of the CLR\n");

	pHost->Start(); // Start the CLR

	//
	// Get a pointer to the default domain in the CLR
	//
	_AppDomainPtr pDefaultDomain = NULL;
	IUnknownPtr   pAppDomainPunk = NULL;

	hr = pHost->GetDefaultDomain(&pAppDomainPunk);
	ASSERT(pAppDomainPunk);

	hr = pAppDomainPunk->QueryInterface(__uuidof(_AppDomain), (void**) &pDefaultDomain);
	ASSERT(pDefaultDomain);

	BSTR uncaughtException = 0;
	int retval = 0;

	try
	{
		// Load MgaClrUtil.dll from resource
		HRSRC hResInfo = FindResource(HINST_THISCOMPONENT, MAKEINTRESOURCE(IDR_CLR_ASSEMBLY1),  RT_RCDATA);
		HGLOBAL hGlobal = LoadResource(HINST_THISCOMPONENT, hResInfo);
		LPVOID data = LockResource(hGlobal);
		DWORD size = SizeofResource(HINST_THISCOMPONENT, hResInfo);
		ATL::CComSafeArray<BYTE> ByteArray;
		ByteArray.Add(size, reinterpret_cast<BYTE const*>(data), TRUE);

		_AssemblyPtr util = pDefaultDomain->Load_3(*ByteArray.GetSafeArrayPtr());

		// Pass in location for ManagedExceptionCallback
		_variant_t exceptionStringLocation;
		exceptionStringLocation = (int)&uncaughtException;
#ifdef _WIN64
#error int isn't big enough for a pointer on _WIN64
#endif
		ATL::CComSafeArray<VARIANT> arguments;
		arguments.Add(exceptionStringLocation.Detach(), 0);
		arguments.Add(_variant_t(assemblyPath).Detach(), 0);
		arguments.Add(_variant_t(typeName).Detach(), 0);
		arguments.Add(_variant_t(methodName).Detach(), 0);
		arguments.Add(_variant_t(mode).Detach(), 0);
		_variant_t helper = util->CreateInstance_3(_bstr_t("GME.MgaUtil.RegistrationHelper"),
			0, BindingFlags_Default, 0, arguments, 0, 0);
		// KMS: for some reason, CreateInstance_3 doesn't throw an exception if the Type isn't found.
		// Check if the return value is VT_EMPTY
		if (helper == _variant_t())
		{
			retval = 1;
		}
	}
	catch(_com_error& error)
	{
		CString csTemp;
		csTemp.Format("CallManagedFunction exception, ERROR: %s", (_TCHAR*)error.Description());
		if (uncaughtException != 0)
		{
			csTemp += _T("\n\nAdditional information:\n");
			csTemp += uncaughtException;
			SysFreeString(uncaughtException);
		}
		AfxMessageBox(csTemp);
		retval = 1;
	}

	pHost->Stop();
	pHost->Release();

	FreeLibrary(cor);

	return retval;
}

extern "C" void __declspec(dllexport) __stdcall ManagedExceptionCallback(void * pBSTR, BSTR exception)
{
	BSTR* target = (BSTR*)pBSTR;
	*target = SysAllocString(exception);
}
