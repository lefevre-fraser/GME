#include "stdafx.h"
#include "DotNetUtils.h"
#include <MSCOREE.H>
#include <corerror.h>

#import "C:\\windows\\Microsoft.NET\\Framework\\v2.0.50727\\mscorlib.tlb" auto_rename
using namespace mscorlib;


typedef HRESULT (WINAPI * tCorBindToRuntimeEx)(LPWSTR,LPWSTR,DWORD,REFCLSID,REFIID,LPVOID*);


int CDotNetUtils::CallManagedFunction(BSTR assemblyPath, BSTR typeName, BSTR methodName, int mode)
{
	return CallManagedFunction(assemblyPath, typeName, methodName, NULL, mode);
}

int CDotNetUtils::CallManagedFunction(BSTR assemblyPath, BSTR typeName, BSTR methodName, CComPtr<IMgaProject> param)
{
	return CallManagedFunction(assemblyPath, typeName, methodName, param, 0);
}

int CDotNetUtils::CallManagedFunction(BSTR assemblyPath, BSTR typeName, BSTR methodName, CComPtr<IMgaProject> param, int mode)
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
	} else {
		tCorBindToRuntimeEx pCorBindToRuntimeEx = (tCorBindToRuntimeEx) GetProcAddress(cor, "CorBindToRuntimeEx");
		if (!pCorBindToRuntimeEx) {
			AfxMessageBox("CallManagedFunction: couldn't load CorBindToRuntimeEx function entry from mscoree.dll (.NET Framework provider dll)");
			return 3;
		} else {
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

			try
			{
				_ObjectHandlePtr pObjectHandle;
				_ObjectPtr pObject; 
				_TypePtr pType;
				SAFEARRAY* psa;

				// Create an instance of a type from an assembly
				pObjectHandle = pDefaultDomain->CreateInstanceFrom(assemblyPath, typeName);

				variant_t vtobj = pObjectHandle->Unwrap();								// Get an _Object (as variant) from the _ObjectHandle
				vtobj.pdispVal->QueryInterface(__uuidof(_Object), (void**)&pObject);	// QI the variant for the Object iface
				pType = pObject->GetType();												// Get the _Type iface
				psa = SafeArrayCreateVector(VT_VARIANT, 0, 1);							// Create a safearray (0 length)
				
				{
					VARIANT typeNameParam;
					VariantInit(&typeNameParam);
					CComPtr<IDispatch> p;
					if (!param) {
						typeNameParam.vt = VT_I4;
						typeNameParam.intVal = mode;
					} else {
						typeNameParam.vt = VT_DISPATCH;
						p = param;
						typeNameParam.pdispVal = p;
					}
					LONG index = 0;

					SafeArrayPutElement(psa, &index, &typeNameParam);
				}

				//_variant_t retVal = 
				pType->InvokeMember_3(methodName,										// Invoke "Test" method on pType
									  BindingFlags_InvokeMethod,
									  NULL,
									  vtobj,
									  psa);

				//if (retVal.vt == VT_I4)
				//{
				//	int ret = retVal.intVal;
				//}

				SafeArrayDestroy(psa);													// Destroy safearray
			}
			catch(_com_error& error)
			{
				CString csTemp;
				csTemp.Format("CallManagedFunction exception, ERROR: %s", (_TCHAR*)error.Description());
				AfxMessageBox(csTemp);
			}

			pHost->Stop();
			pHost->Release();
		}

		FreeLibrary(cor);
	}

	return 0;
}

