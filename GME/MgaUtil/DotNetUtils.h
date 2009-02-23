#pragma once


class CDotNetUtils
{
public:
	static int CallManagedFunction(BSTR assemblyPath, BSTR typeName, BSTR methodName, int mode);
	static int CallManagedFunction(BSTR assemblyPath, BSTR typeName, BSTR methodName, CComPtr<IMgaProject> param);

private:
	static int CallManagedFunction(BSTR assemblyPath, BSTR typeName, BSTR methodName, CComPtr<IMgaProject> param, int mode);
};
