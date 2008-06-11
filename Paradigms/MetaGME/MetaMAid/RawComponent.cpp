///////////////////////////////////////////////////////////////////////////
// RawComponent.cpp, the main RAW COM component implementation file
// This is the file (along with its header RawComponent.h)
// that the component implementor is expected to modify in the first place
//
///////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "ComHelp.h"
#include "GMECOM.h"
#include <ComponentConfig.h>
#include "RawComponent.h"
#include <string>

#define HR_THROW(x) throw x;

void CopyTo(const OLECHAR *p, int olelen, char *s, int charlen)
{
	ASSERT( olelen >= -1 && charlen >= 0 );
	ASSERT( charlen == 0 || p != NULL );

	if( charlen <= 0 )
		return;

	UINT acp = GetACP();

	int len = WideCharToMultiByte(acp, 0, p, olelen, 
		s, charlen, NULL, NULL);

	// zero if failed
	ASSERT( len > 0 );

	ASSERT( len == charlen );
}		

void CopyTo(const char *p, int len, BSTR *b)
{
	ASSERT( len >= 0 );
	ASSERT( b != NULL );

	if(*b)
	{
		SysFreeString(*b);
		*b = NULL;
	}

	if( len <= 0 )
		return;

	UINT acp = GetACP();
	int blen = MultiByteToWideChar(acp, 0, p, len, NULL, 0);

	if( blen <= 0 )
		HR_THROW(-1);

	*b = SysAllocStringLen(NULL, blen);
	if( *b == NULL )
		HR_THROW(-1);

	int tlen = MultiByteToWideChar(acp, 0, p, len, *b, blen);

	if( tlen <= 0 )
		HR_THROW(-1);
	
	ASSERT( tlen == blen );

	(*b)[blen] = '\0';
}

CComBSTR getMyKind( CComPtr<IMgaFCO> fco)
{
	CComBSTR rv;

	if( fco)
	{
		CComPtr<IMgaMetaFCO> mmfco;
		COMTHROW( fco->get_Meta( &mmfco));
		
		COMTHROW( mmfco->get_Name( &rv));
	}
	return rv;
}

bool found( CComBSTR oldpref, char toRemove, CComBSTR& newpref)
{
	unsigned int len = oldpref.Length();
	if( !len) return false;

	char *buff = new char[ len + 1];

	CopyTo( oldpref, len, buff, len);
	buff[ len] = '\0';

	std::string prf( buff);
	ASSERT( prf.length() == len);

	delete [] buff;

	unsigned int pos = prf.find( toRemove);
	if( pos != std::string::npos) // found
	{
		prf.erase( pos, 1);
		ASSERT( prf.find( toRemove) == std::string::npos);

		CopyTo( prf.c_str(), prf.length(), &newpref);

		return true;
	}

	return false;
}


// this method is called after all the generic initialization is done
// this should be empty, unless application-specific initialization is needed
STDMETHODIMP RawComponent::Initialize(struct IMgaProject *) {
	return S_OK;
}

// this is the obsolete component interface
// this present implementation either tries to call InvokeEx, or returns an error;
STDMETHODIMP RawComponent::Invoke(IMgaProject* gme, IMgaFCOs *models, long param) {
#ifdef SUPPORT_OLD_INVOKE
	CComPtr<IMgaFCO> focus;
	CComVariant parval = param;
	return InvokeEx(gme, focus, selected, parvar);
#else
	if(interactive) {
		AfxMessageBox("This component does not support the obsolete invoke mechanism");
	}
	return E_MGA_NOT_SUPPORTED;
#endif
}


// This is the main component method for interpereters and plugins. 
// May als be used in case of invokeable addons
STDMETHODIMP RawComponent::InvokeEx( IMgaProject *project,  IMgaFCO *currentobj,  
									IMgaFCOs *selectedobjs,  long param) {
	return S_OK;
}

// GME currently does not use this function
// you only need to implement it if other invokation mechanisms are used
STDMETHODIMP RawComponent::ObjectsInvokeEx( IMgaProject *project,  IMgaObject *currentobj,  IMgaObjects *selectedobjs,  long param) {
	if(interactive) {
		//AfxMessageBox("Tho ObjectsInvoke method is not implemented");
	}
	return E_MGA_NOT_SUPPORTED;
}


// implement application specific parameter-mechanism in these functions:
STDMETHODIMP RawComponent::get_ComponentParameter(BSTR name, VARIANT *pVal) {
	return S_OK;
}

STDMETHODIMP RawComponent::put_ComponentParameter(BSTR name, VARIANT newVal) {
	return S_OK;
}


#ifdef GME_ADDON

// these two functions are the main 
STDMETHODIMP RawComponent::GlobalEvent(globalevent_enum event) { 
	return S_OK; 
}

STDMETHODIMP RawComponent::ObjectEvent(IMgaObject * obj, unsigned long eventmask, VARIANT v) {
	if( eventmask & OBJEVENT_CREATED) 
	{
		CComQIPtr<IMgaFCO> fco( obj);
		if( fco)
		{
			// library contained objects can't be modified !
			// ( during library attach they may seem as newly created
			// that's why they end up here, in the EVENT_CREATED branch )
			VARIANT_BOOL libobj;
			COMTHROW( fco->get_IsLibObject( &libobj));
			if( libobj == VARIANT_TRUE) return S_OK;

			CComPtr<IMgaMetaFCO> mmfco;
			COMTHROW( fco->get_Meta( &mmfco));
			
			CComBSTR kind;
			COMTHROW( mmfco->get_Name( &kind));

			if( kind == L"FCO")
			{
				VARIANT_BOOL var;
				COMTHROW( fco->get_BoolAttrByName( CComBSTR( L"IsAbstract"), &var));
				if( var != VARIANT_TRUE) // not abstract yet
					COMTHROW( fco->put_BoolAttrByName( CComBSTR( L"IsAbstract"), VARIANT_TRUE));
			}
			else if( kind == L"BaseInheritance"
			      || kind == L"BaseIntInheritance"
			      || kind == L"BaseImpInheritance")
			{
				CComBSTR oldpref, newpref;
				COMTHROW( fco->get_RegistryValue( CComBSTR( L"autorouterPref"), &oldpref));

				// A baseinh connection should be drawn from the BaseObject as source, Triangle as destination.
				// We don't know what kind of FCO has been used as BaseObject, but we can present
				// the connection (by clearing the misleading autorouterpreference) as its kind
				// implies: a baseinh connection must go to the top of the triangle!

				// If autorouterpref has 's' (case sensitive!) the user is mislead by seeing
				// a baseinh connection attached to the bottom of the triangle symbol.
				// It is a visual aid for GME novices, who make the connection by benefitting 
				// from the hotspots.
				if( found( oldpref, 's', newpref))
					COMTHROW( fco->put_RegistryValue( CComBSTR( L"autorouterPref"), newpref));
			}
			else if( kind == L"DerivedInheritance"
			      || kind == L"DerivedIntInheritance"
			      || kind == L"DerivedImpInheritance")
			{
				CComBSTR oldpref, newpref;
				COMTHROW( fco->get_RegistryValue( CComBSTR( L"autorouterPref"), &oldpref));

				// If autorouterpref has 'N' (case sensitive!) the user is mislead by seeing
				// a derivinh connection attached to the top of the triangle symbol.
				if( found( oldpref, 'N', newpref))
					COMTHROW( fco->put_RegistryValue( CComBSTR( L"autorouterPref"), newpref));
			}
		}
	}
	return S_OK;
}

#endif
