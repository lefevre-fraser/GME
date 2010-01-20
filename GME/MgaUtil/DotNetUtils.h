#pragma once


class CDotNetUtils
{
public:
	static int CallManagedFunction(BSTR assemblyPath, BSTR typeName, BSTR methodName, int mode);
};
