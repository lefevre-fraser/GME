// Meta.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f Metaps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>

#include "Meta_i.c"
#include "MetaLib_i.c"
#include "Core_i.c"
#include "Gme_i.c"

#include "CommonError.h"
#include "CommonSmart.h"

#include "MgaMetaProject.h"
#include "MgaMetaFolder.h"
#include "MgaMetaModel.h"
#include "MgaMetaAspect.h"
#include "MgaMetaRole.h"
#include "MgaMetaAtom.h"
#include "MgaMetaReference.h"
#include "MgaMetaSet.h"
#include "MgaMetaConnection.h"
#include "MgaMetaConnJoint.h"
#include "MgaMetaAttribute.h"
#include "MgaMetaPointerSpec.h"
#include "MgaMetaPointerItem.h"
#include "MgaMetaPart.h"
#include "MgaMetaRegNode.h"
#include "MgaMetaEnumItem.h"
#include "MgaMetaConstraint.h"

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_MgaMetaProject, CMgaMetaProject)
OBJECT_ENTRY(CLSID_MgaMetaFolder, CMgaMetaFolder)
OBJECT_ENTRY(CLSID_MgaMetaModel, CMgaMetaModel)
OBJECT_ENTRY(CLSID_MgaMetaAspect, CMgaMetaAspect)
OBJECT_ENTRY(CLSID_MgaMetaRole, CMgaMetaRole)
OBJECT_ENTRY(CLSID_MgaMetaAtom, CMgaMetaAtom)
OBJECT_ENTRY(CLSID_MgaMetaReference, CMgaMetaReference)
OBJECT_ENTRY(CLSID_MgaMetaSet, CMgaMetaSet)
OBJECT_ENTRY(CLSID_MgaMetaConnection, CMgaMetaConnection)
OBJECT_ENTRY(CLSID_MgaMetaConnJoint, CMgaMetaConnJoint)
OBJECT_ENTRY(CLSID_MgaMetaAttribute, CMgaMetaAttribute)
OBJECT_ENTRY(CLSID_MgaMetaPointerSpec, CMgaMetaPointerSpec)
OBJECT_ENTRY(CLSID_MgaMetaPointerItem, CMgaMetaPointerItem)
OBJECT_ENTRY(CLSID_MgaMetaPart, CMgaMetaPart)
OBJECT_ENTRY(CLSID_MgaMetaRegNode, CMgaMetaRegNode)
OBJECT_ENTRY(CLSID_MgaMetaEnumItem, CMgaMetaEnumItem)
OBJECT_ENTRY(CLSID_MgaMetaConstraint, CMgaMetaConstraint)

OBJECT_ENTRY(CLSID_MgaMetaFCOs, FCOsExCOMType)
OBJECT_ENTRY(CLSID_MgaMetaRoles, RolesExCOMType)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_METALib);
        DisableThreadLibraryCalls(hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
        _Module.Term();
    return TRUE;    // ok
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib
    return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    return _Module.UnregisterServer(TRUE);
}

// --------------------------- Traverse

void TraverseObject(CMgaMetaProject *metaproject, CCoreObjectPtr &me)
{
	ASSERT( metaproject != NULL );
	ASSERT( me != NULL );

	me.Load();

	CComObjPtr<IMgaMetaBase> base;
	if( SUCCEEDED(QueryInterface(me, base)) )
	{
		ASSERT( base != NULL );

		objtype_enum objtype;
		COMTHROW( base->get_ObjType(&objtype) );

		switch(objtype)
		{
		case OBJTYPE_MODEL:
			CMgaMetaModel::Traverse(metaproject, me);
			break;

		case OBJTYPE_ATOM:
			CMgaMetaAtom::Traverse(metaproject, me);
			break;

		case OBJTYPE_REFERENCE:
			CMgaMetaReference::Traverse(metaproject, me);
			break;

		case OBJTYPE_CONNECTION:
			CMgaMetaConnection::Traverse(metaproject, me);
			break;

		case OBJTYPE_SET:
			CMgaMetaSet::Traverse(metaproject, me);
			break;

		case OBJTYPE_FOLDER:
			CMgaMetaFolder::Traverse(metaproject, me);
			break;

		case OBJTYPE_ASPECT:
			CMgaMetaAspect::Traverse(metaproject, me);
			break;

		case OBJTYPE_ROLE:
			CMgaMetaRole::Traverse(metaproject, me);
			break;

		case OBJTYPE_ATTRIBUTE:
			CMgaMetaAttribute::Traverse(metaproject, me);
			break;

		case OBJTYPE_PART:
			CMgaMetaPart::Traverse(metaproject, me);
			break;

		}
	}
	else
	{
		CComObjPtr<IMgaMetaConnJoint> connjoint;
		CComObjPtr<IMgaMetaPointerSpec> ptrspec;
		CComObjPtr<IMgaMetaRegNode> regnode;

		if( SUCCEEDED(QueryInterface(me, connjoint)) )
			CMgaMetaConnJoint::Traverse(metaproject, me);
		else if( SUCCEEDED(QueryInterface(me, ptrspec)) )
			CMgaMetaPointerSpec::Traverse(metaproject, me);
		else if( SUCCEEDED(QueryInterface(me, regnode)) )
			CMgaMetaRegNode::Traverse(metaproject, me);
	}
}

void TraverseCollection(CMgaMetaProject *metaproject, CCoreObjectPtr &me, attrid_type attrid)
{
	ASSERT( metaproject != NULL );
	ASSERT( me != NULL );

	coreobjects_type coreobjects;
	me.LoadCollectionValue(attrid, coreobjects);
	coreobjects_iterator i = coreobjects.begin();
	coreobjects_iterator e = coreobjects.end();
	while( i != e )
	{
		TraverseObject(metaproject, *i);

		++i;
	}
}


HRESULT check_location_compatibility(IMgaMetaBase *newobj, IMgaMetaBase *oldobj) {
	CComPtr<IMgaMetaProject> p, p2;
	HRESULT hr;
	if((hr = newobj->get_MetaProject(&p)) != S_OK) return hr;
	if(!oldobj) {
		//if(p->Open != CMgaMetaProject::Open) return E_SAMEPROJECT;
		if(IMgaMetaProject::Open != CMgaMetaProject::Open) return E_SAMEPROJECT;
	}
	else {
		if((hr = oldobj->get_MetaProject(&p2)) != S_OK) return hr;
		if(p != p2) return E_SAMEPROJECT;
	}
	return S_OK;
}

