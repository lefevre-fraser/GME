#include "stdAfx.h"
#include "MgaTerritory.h"
// ----------------------------------------
// Implementation for the MgaTerritory and MgaAddOn  classes
// ----------------------------------------



STDMETHODIMP CMgaTerritory::Associate( IMgaObject *obj,  VARIANT userdata) { 
	COMTRY {
			CHECK_MYINPTRPAR(obj);
			if(!coreterr) COMTHROW( E_MGA_TARGET_DESTROYED);
			ObjFor(obj)->objsetuserdata(this, userdata);
	} COMCATCH(;);
			
};

STDMETHODIMP CMgaTerritory::OpenObj(IMgaObject *oldptr, IMgaObject **newptr) { 
	COMTRY {
		CHECK_MYINPTRPAR(oldptr); 
		CHECK_OUTPAR(newptr); 
		CComPtr<IMgaObject> np;
		if(!coreterr) COMTHROW(E_MGA_TARGET_DESTROYED);
		ObjFor(oldptr)->getinterface(&np,this);
		if(*newptr) (*newptr)->Release();
		*newptr = np.Detach();
	} COMCATCH(;) 
}

STDMETHODIMP CMgaTerritory::OpenFCO(IMgaFCO *oldptr, IMgaFCO **newptr) { 
	COMTRY {
		CHECK_MYINPTRPAR(oldptr); 
		CHECK_OUTPAR(newptr); 
		CComPtr<IMgaFCO> np;
		if(!coreterr) COMTHROW(E_MGA_TARGET_DESTROYED);
		ObjFor(oldptr)->getinterface(&np,this);
		if(*newptr) (*newptr)->Release();
		*newptr = np.Detach();
	} COMCATCH(;) 
}

STDMETHODIMP CMgaTerritory::OpenFCOs(IMgaFCOs *oldptr, IMgaFCOs **newptr) { 
	COMTRY {
		CHECK_MYINPTRSPAR(oldptr); 
		CHECK_OUTPAR(newptr); 
		CREATEEXCOLLECTION_FOR(MgaFCO, q);
		if(!coreterr) COMTHROW(E_MGA_TARGET_DESTROYED);
		MGACOLL_ITERATE(IMgaFCO, oldptr) {
			CComPtr<IMgaFCO> bb;
		    ObjFor(MGACOLL_ITER)->getinterface(&bb);
			q->Add(bb);
		}
		MGACOLL_ITERATE_END;
		if(*newptr) (*newptr)->Release();
		*newptr = q.Detach();
	} COMCATCH(;) 
}


STDMETHODIMP CMgaTerritory::CloseObj(IMgaObject *obj) {
	COMTRY {
		CHECK_MYINPTRPAR(obj); 
		if(!coreterr) COMTHROW(E_MGA_TARGET_DESTROYED);
		COMTHROW(obj->Close());
	} COMCATCH(;) 
}

STDMETHODIMP CMgaTerritory::Flush() {
/*
	bool trwas = false;
	bool pushwas = false;
*/
/*
	COMTRY {
		if(!coreterr) COMTHROW(E_MGA_TARGET_DESTROYED);

		MGA_TRACE("Terr flush. Lock count: %d\n", refcnt);
#ifdef OLD_FLUSH
		CComPtr<ICoreAttributes> atts;
		COMTHROW(coreterr->get_Attributes(&atts));
		long count = 0;
		COMTHROW( atts->get_Count(&count) );
		ASSERT( count >= 0 );
		if(count > 0) {
			MGACOLL_ITERATE(ICoreAttribute, atts) {
				CoreObj ob;
				CComPtr<IMgaObject> mob;
				COMTHROW(MGACOLL_ITER->get_Object(&ob));
				ob->QueryInterface(&mob);
				if(mob) mgaproject->ObjFor(mob)->removeterrfromlist(this);
			} MGACOLL_ITERATE_END;

		}
#else	
		objsetcoll::iterator f;
		while((f =inobjs.begin()) != inobjs.end()) (*f)->removeterrfromlist(this);
#endif
		ASSERT(("Territory is still locked by some objects", refcnt == 0));
		COMTHROW(coreterr->Clear());
	} COMCATCH(
		if(coreterr) coreterr->Clear();
		);
*/

	COMTRY {
	   if(coreterr) COMTHROW(coreterr->Clear());
	} COMCATCH(;);
	
};


STDMETHODIMP CMgaTerritory::CheckProject(IMgaProject *project) {
	return(project == mgaproject? S_OK : E_MGA_FOREIGN_PROJECT);
}


STDMETHODIMP CMgaTerritory::Destroy() {
	COMTRY {
		if(!coreterr) COMTHROW(E_MGA_TARGET_DESTROYED);
		COMTHROW(Flush());
		CMgaProject::tercoll::iterator i = mgaproject->allterrs.begin(), end = mgaproject->allterrs.end();
		for(;i != end; i++) {
			if(*i == this) {
				mgaproject->allterrs.erase(i);
				coreterr = NULL;   // release CoreTerritory object
				handler = NULL;	// release sink
				rwhandler = NULL;	// release sink
				return S_OK;
			}
			
		}
		ASSERT(false);	// not found among project territories
	} COMCATCH(;)
}


STDMETHODIMP CMgaTerritory::SetNamespace( BSTR pNmsp)
{
	COMTRY {
		m_bstrCurrNamespace = pNmsp;
		mgaproject->SetNmspaceInMeta(); // set into the metaproject if open
	} COMCATCH(;)
}

STDMETHODIMP CMgaTerritory::GetNamespace( BSTR * pNmsp)
{
	COMTRY {
		if( m_bstrCurrNamespace.Length() > 0) // namespace set
		{
			CComBSTR res;
			res.AppendBSTR( m_bstrCurrNamespace);
			*pNmsp = res.Detach();
		}
	} COMCATCH(;)
}

STDMETHODIMP CMgaAddOn::CheckProject(IMgaProject *project) {
	return(project == mgaproject? S_OK : E_MGA_FOREIGN_PROJECT);
}


STDMETHODIMP CMgaAddOn::Destroy() {
	COMTRY {
		MARKSIG('8'); 
		if(!handler) COMTHROW(E_MGA_TARGET_DESTROYED);
		CMgaProject::addoncoll::iterator i = mgaproject->alladdons.begin(), end = mgaproject->alladdons.end();
		for(;i != end; i++) {
			if(*i == this) {
				mgaproject->alladdons.erase(i);
				if(mgaproject->alladdons.empty()) mgaproject->reserveterr = NULL;   // release 
				handler = NULL;	// release sink
				return S_OK;
			}
			
		}
		ASSERT(("addon not found among project addons",false));	
		active = false;
	} COMCATCH(;)
}


STDMETHODIMP CMgaAddOn::get_Priority( long *pVal) { return E_MGA_NOT_IMPLEMENTED; }
STDMETHODIMP CMgaAddOn::put_Priority( long newVal) { return E_MGA_NOT_IMPLEMENTED; }


