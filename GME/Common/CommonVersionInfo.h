#ifndef COMMONVERSIONINFO_H
#define COMMONVERSIONINFO_H

#include "CommonError.h"

class ATL_NO_VTABLE IMgaVersionInfoImpl : public IMgaVersionInfo {
public:
	    BEGIN_INTERFACE
		STDMETHOD(get_version(MgaInterfaceVersion *pVal)) {
			//AFX_MANAGE_STATE( AfxGetStaticModuleState());//z
			if(!pVal) return E_POINTER;
			*pVal = MgaInterfaceVersion_Current;
			return S_OK;
		}
};


#endif // COMMONVERSIONINFO_H
