#include "StdAfx.h"

#include "Comdef.h"
#include "ComponentConfig.h"

void SetErrorInfo(HRESULT hr, const wchar_t* err)
{
	ICreateErrorInfoPtr errCreate;
	if (SUCCEEDED(CreateErrorInfo(&errCreate))
		&& SUCCEEDED(errCreate->SetDescription(const_cast<wchar_t*>(err)))
#define __OLESTR(x) L ## x
#define _OLESTR(x) __OLESTR(x)
		&& SUCCEEDED(errCreate->SetSource(_OLESTR(COCLASS_PROGID)))
		)
	{

		IErrorInfoPtr errorInfo = errCreate;
		SetErrorInfo(0, errorInfo);
	}
}
