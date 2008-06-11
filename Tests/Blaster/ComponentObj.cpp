// ComponentObj.cpp : implementation file
//

#include "stdafx.h"

#include "GMECOM.h"

#ifdef BUILDER_OBJECT_NETWORK
#include "Component.h"
//#include "Builder2000.h"
#else 
#ifdef OLD_BUILDER_OBJECT_NETWORK
#include "Interpreter.h"
#include "Builder.h"
#endif
#endif
#include "ComHelp.h"

#include "ComponentLib.h"
#include "ComponentObj.h"

#include "ComponentConfig.h"


#include "ComponentLib_i.c"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// --------------------------------------- GmeDllDesc

// Syntax:
//   interpreter,<paradigm>,<description>,<progid>
//   plug-in,*,<description>,<progid>
//   add-on,<paradigm>,<progid>
//
// Examples:
//   L"<GMEDLLDESC> interpreter,SF,SF Code Generator,MGA.Component.SF <END>"
//   L"<GMEDLLDESC> add-on,*,My first general add-on,MGA.GenAddon.MyAddon <END>"

#define WCHAR_L() L
#define WCHAR(PAR) WCHAR_L()PAR

#ifdef GME_PLUGIN
wchar_t GmeDllDesc[] = L"<GMEDLLDESC> plug-in," L"," WCHAR(Component_NAME) L"," WCHAR(COCLASS_PROGID) L"<END>";
#define CETYPE	COMPONENTTYPE_PLUGIN
#else
#ifdef GME_ADDON
wchar_t GmeDllDesc[] = L"<GMEDLLDESC> add-on,*," WCHAR(Component_NAME) L"," WCHAR(COCLASS_PROGID) L"<END>";
#define CETYPE	COMPONENTTYPE_ADDON
#else
#ifdef GME_INTERPRETER
wchar_t GmeDllDesc[] = L"<GMEDLLDESC> interpreter," WCHAR(PARADIGMS) L"," WCHAR(COMPONENT_NAME) L"," WCHAR(COCLASS_PROGID) L"<END>";
#define CETYPE	COMPONENTTYPE_INTERPRETER
#else
#error No GME Componenttype (one of GME_PLUGIN, GME_ADDON, GME_INTERPRETER) is defined
#endif
#endif
#endif

#undef WCHAR_L
#undef WCHAR



/////////////////////////////////////////////////////////////////////////////
// CComponentObj

IMPLEMENT_DYNCREATE(CComponentObj, CCmdTarget)

CComponentObj::CComponentObj()
{
	EnableAutomation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	
	AfxOleLockApp();

	registeractiveobjectret = 0;
}

void CComponentObj::RegisterActiveObject()
{
	ASSERT( registeractiveobjectret == 0 );

	COMVERIFY( ::RegisterActiveObject(GetInterface(), CLSID_MgaComponent,
		ACTIVEOBJECT_STRONG, &registeractiveobjectret) );

	ASSERT( registeractiveobjectret );
}

CComponentObj::~CComponentObj()
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.

	ASSERT( registeractiveobjectret == 0 );

	AfxOleUnlockApp();
}

void CComponentObj::UnregisterActiveObject()
{
	ASSERT( registeractiveobjectret );
	COMVERIFY( ::RevokeActiveObject(registeractiveobjectret, NULL) );
	registeractiveobjectret = 0;
}

void CComponentObj::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CComponentObj, CCmdTarget)
	//{{AFX_MSG_MAP(CComponentObj)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CComponentObj, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CComponentObj)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: We get the type and name of the embedded class 
// "XComponent" and "m_xComponent" from the "Component" parameter

BEGIN_INTERFACE_MAP(CComponentObj, CCmdTarget)
	INTERFACE_PART(CComponentObj, IID_IMgaComponent, Component)
	INTERFACE_PART(CComponentObj, IID_IMgaVersionInfo, VersionInfo)
END_INTERFACE_MAP()

// We register the ComponentClass
// CLSID_MGAComponentClass

IMPLEMENT_OLECREATE(CComponentObj, COCLASS_PROGID, 
COCLASS_UUID_EXPLODED1,
COCLASS_UUID_EXPLODED2,
COCLASS_UUID_EXPLODED3,
COCLASS_UUID_EXPLODED4,
COCLASS_UUID_EXPLODED5,
COCLASS_UUID_EXPLODED6,
COCLASS_UUID_EXPLODED7,
COCLASS_UUID_EXPLODED8,
COCLASS_UUID_EXPLODED9,
COCLASS_UUID_EXPLODED10,
COCLASS_UUID_EXPLODED11
)

/////////////////////////////////////////////////////////////////////////////
// CComponentObj::XInterface


STDMETHODIMP_(ULONG) COMCLASS::AddRef()
{
	COMPROLOGUE;
	return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) COMCLASS::Release()
{
	COMPROLOGUE;
	return pThis->ExternalRelease();
}

STDMETHODIMP COMCLASS::QueryInterface(REFIID riid, void** ppv)
{
	COMPROLOGUE;
	return pThis->ExternalQueryInterface(&riid, ppv);
}


#if defined(BUILDER_OBJECT_NETWORK) || defined(OLD_BUILDER_OBJECT_NETWORK)
// If BUILDER OBJECT NETWORK IS NOT USED, THESE METHODS ARE IMPLEMENTED BY THE USER
// (generally in ComComponent.cpp)


STDMETHODIMP COMCLASS::Invoke(IMgaProject *gme, IMgaFCOs *psa, long param)
{

	COMPROLOGUE;
	CPushRoutingFrame temp(NULL);		// hack!!

	ASSERT( gme != NULL );

	long prefs;
	COMTHROW(gme->get_Preferences(&prefs));

	COMTHROW(gme->put_Preferences(prefs | MGAPREF_RELAXED_RDATTRTYPES | MGAPREF_RELAXED_WRATTRTYPES));
/*
	CBuilder builder(gme);

	CBuilderObjectList objects;
	if(psa) {
	  MGACOLL_ITERATE(IMgaFCO, psa) {
		CBuilderObject* o = CBuilder::theInstance->FindObject(MGACOLL_ITER);
		ASSERT( o != NULL );
		objects.AddTail(o);
	  } MGACOLL_ITERATE_END;
	}
*/

#ifdef BUILDER_OBJECT_NETWORK
	CComponent comp;
//	comp.Invoke(builder, objects, param);
	comp.Invoke(gme, psa, param);
#else 
	CInterpreter intp;
	intp.Interpret(builder, objects, param);
#endif

	COMTHROW(gme->put_Preferences(prefs));
	return S_OK;
}


// You may also want to modify the implementations for the following methods

STDMETHODIMP COMCLASS::Initialize(struct IMgaProject *) { 
	return S_OK; 
};

STDMETHODIMP COMCLASS::Enable(VARIANT_BOOL newVal) { 
	return S_OK; 
};
STDMETHODIMP COMCLASS::get_InteractiveMode(VARIANT_BOOL *enabled) { 
	if(enabled) *enabled = VARIANT_TRUE;
	return S_OK; 
};
        
STDMETHODIMP COMCLASS::put_InteractiveMode(VARIANT_BOOL enabled) { 
	return S_OK; 
};


#endif


STDMETHODIMP COMCLASS::get_ComponentType( componenttype_enum *t)
{
	COMPROLOGUE;
	*t = CETYPE;
	return S_OK;
}

#undef COMCLASS
#undef COMPROLOGUE

/////////////////////////////////////////////////////////////////////////////
// CComponentObj::XVersionInfo

#define COMCLASS		CComponentObj::XVersionInfo
#define COMPROLOGUE		METHOD_PROLOGUE(CComponentObj,VersionInfo)

STDMETHODIMP_(ULONG) COMCLASS::AddRef()
{
	COMPROLOGUE;
	return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) COMCLASS::Release()
{
	COMPROLOGUE;
	return pThis->ExternalRelease();
}

STDMETHODIMP COMCLASS::QueryInterface(REFIID riid, void** ppv)
{
	COMPROLOGUE;
	return pThis->ExternalQueryInterface(&riid, ppv);
}

STDMETHODIMP COMCLASS::get_version(enum MgaInterfaceVersion *pVal)
{
	COMPROLOGUE;

	if( pVal == NULL )
		return E_POINTER;

	*pVal = MgaInterfaceVersion_Current;
	return S_OK;
}

#undef COMCLASS
#undef COMPROLOGUE

// --------------------------- CComponentReg

CComponentReg::CComponentReg()
{

	CString pars = PARADIGMS;
	while( !pars.IsEmpty() )
	{
		CString trash = pars.SpanIncluding(" ,;");
		pars = pars.Mid(trash.GetLength());
		if( pars.IsEmpty() )
			break;
		CString par = pars.SpanExcluding(" ,;");
		pars = pars.Mid(par.GetLength());
		ASSERT(!par.IsEmpty());
		paradigms.AddTail(par);
	}
}


#define COMRETURN(hr) { HRESULT res; if((res = (hr)) != S_OK) return res; }
 
HRESULT CComponentReg::UnregisterParadigms() {
	CComPtr<IMgaRegistrar> registrar;
	COMRETURN(registrar.CoCreateInstance(OLESTR("Mga.MgaRegistrar")));
	COMRETURN(registrar->UnregisterComponent(CComBSTR(COCLASS_PROGID), REGACCESS_USER));
	return S_OK;
}

HRESULT CComponentReg::RegisterParadigms() {
	CComPtr<IMgaRegistrar> registrar;
	COMRETURN(registrar.CoCreateInstance(OLESTR("Mga.MgaRegistrar")));
	COMRETURN(registrar->RegisterComponent(CComBSTR(COCLASS_PROGID),CETYPE, CComBSTR(COMPONENT_NAME), REGACCESS_USER));
	POSITION pos = paradigms.GetHeadPosition();
	while(pos)
	{
		CString paradigm = paradigms.GetNext(pos);
		COMRETURN(registrar->Associate(CComBSTR(COCLASS_PROGID), CComBSTR(paradigm), REGACCESS_USER));
	}
	return S_OK;
}

