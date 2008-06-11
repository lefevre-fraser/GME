// MgaSet.h : Declaration of the CMgaSet

#ifndef __MGASET_H_
#define __MGASET_H_

#include "resource.h"       // main symbols
#include "MgaFCO.h"

/////////////////////////////////////////////////////////////////////////////
// CMgaSet
class ATL_NO_VTABLE CMgaSet : 
	public CComCoClass<CMgaSet, &CLSID_MgaSet>,
	public IMgaFCOImpl< 
		CComObjectRootEx<CComSingleThreadModel>,
	     IDispatchImpl<IMgaSet, &IID_IMgaSet, &LIBID_MGALib> >,
	public ISupportErrorInfoImpl<&IID_IMgaSet>
{
public:
	CMgaSet()
	{
	}


DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMgaSet)
	COM_INTERFACE_ENTRY(IMgaSet)
	COM_INTERFACE_ENTRY_IID(IID_IMgaFCO,IMgaSet)		
	COM_INTERFACE_ENTRY_IID(IID_IMgaObject,IMgaSet)
	COM_INTERFACE_ENTRY_IID(IID_ISupportErrorInfo, IMyErrorInfoBase)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IMgaSet
public:
	STDMETHOD(RemoveMember)(IMgaFCO *member) { return inFCO->RemoveMember(member); };
	STDMETHOD(RemoveAll)()                   { return inFCO->SetRemoveAll(); };
	STDMETHOD(AddMember)(IMgaFCO *member) { return inFCO->AddMember(member); };
	STDMETHOD(get_Members)(IMgaFCOs * *pVal) { return inFCO->get_Members(pVal); };
	STDMETHOD(get_IsMember)(IMgaFCO *obj, VARIANT_BOOL *pVal) { return inFCO->get_IsMember(obj, pVal); };
	STDMETHOD(GetIsMemberDisp)(IMgaFCO *obj, VARIANT_BOOL *pVal) { return inFCO->get_IsMember(obj, pVal); };
	STDMETHOD(CompareToBase)(short *status)		{ return inFCO->SetCompareToBase(NULL,status); }
    STDMETHOD(RevertToBase)()						{ return inFCO->SetRevertToBase(NULL); }
};



class addmember : public DeriveTreeTask {
	bool Do(CoreObj self, std::vector<CoreObj> *peers = NULL);
public:
	addmember(bool isext) { endreserve = isext ? 2:1; };
};

class removemember : public DeriveTreeTask {
	bool Do(CoreObj self, std::vector<CoreObj> *peers = NULL);
};

#endif //__MGASET_H_
