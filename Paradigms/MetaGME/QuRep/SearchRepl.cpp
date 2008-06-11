#include "stdafx.h"
#include ".\searchrepl.h"
#include "NullExc.h"
#include "Copier.h"

SearchRepl::SearchRepl( IMgaProject* pr)
	: m_pr( pr)
{
}

SearchRepl::~SearchRepl(void)
{
	m_pr.Release();
}

void SearchRepl::findMetaRole( CComBSTR p_kind, CComPtr<IMgaMetaRole>& p_res1, CComPtr<IMgaMetaRole>& p_res2)
{
	if( !m_pr)
		return;

	CComPtr<IMgaMetaProject> metaproj;
	COMTHROW( m_pr->get_RootMeta( &metaproj));

	if( !metaproj)
		return;

	CComPtr<IMgaMetaFolder> metaroot;
	COMTHROW( metaproj->get_RootFolder( &metaroot));

	if( !metaroot)
		return;

	CComPtr<IMgaMetaFCO> mfco;
	COMTHROW( metaroot->get_LegalRootObjectByName( CComBSTR( "ParadigmSheet"), &mfco));

	if( !mfco)
		return;

	CComPtr<IMgaMetaModel> mmod;
	//mmod.QueryInterface( &mfco);
	mfco.QueryInterface( &mmod);

	if( !mmod)
		return;

	COMTHROW( mmod->get_RoleByName( p_kind, &p_res1));

	p_kind.Append( "Proxy");

	COMTHROW( mmod->get_RoleByName( p_kind, &p_res2));
}

//void SearchRepl::collect( CComPtr<IMgaFCO> p_elem, IMgaFCOs* *p_ptrEqClass)
void SearchRepl::collect( CComPtr<IMgaFCO>    p_elem, CComPtr<IMgaFCOs>& p_eqClass)
{
	if( !p_elem) return;

	// derived elements are not handled
	CComPtr<IMgaFCO> from;
	COMTHROW( p_elem->get_DerivedFrom( &from));
	if( from) 
		return;

	COMTHROW( p_elem->get_ReferencedBy( &p_eqClass));
	
	COMTHROW( p_eqClass->Insert( p_elem, 1)); // in the front
}

void SearchRepl::createSiblings( IMgaFCOs* p_eqClass, CComPtr<IMgaMetaRole> mrole_fco, CComPtr<IMgaMetaRole> mrole_prx)
{
	//CComPtr<IMgaFCOs> counterparts;
	//counterparts.CoCreateInstance( L"Mga.MgaFCOs");
	CComPtr<IMgaFCO> new_class_resp; // the counterpart proxies will be directed towards this
	long c = 0;
	if( p_eqClass) COMTHROW( p_eqClass->get_Count( &c));
	for( long i = 1; i <= c; ++i)
	{
		CComPtr<IMgaFCO> el;
		COMTHROW( p_eqClass->get_Item( i, &el));
		if( !el)
			throw NullExc( "Null ptr in createSiblings");

		
		CComPtr<IMgaFCO> newel;
		CComPtr<IMgaModel> mod;

		COMTHROW( el->get_ParentModel( &mod));
		if( !mod)
			throw NullExc( "Null model parent found in createSiblings");

		CComQIPtr<IMgaReference> el_ref( el);
		if( el_ref) // old el is a proxy, new el will also be a proxy
		{
			COMTHROW( mod->CreateChildObject( mrole_prx, &newel));
			if( new_class_resp)
			{
				CComQIPtr<IMgaReference> newref( newel);
				if( newref) // set these proxies to point to the new class rep
					COMTHROW( newref->put_Referred( new_class_resp));
			}
		}
		else // old el is an elem, new el will also be an elem
		{
			COMTHROW( mod->CreateChildObject( mrole_fco, &newel));
			if( i == 1) // store the first elem
				new_class_resp = newel;
		}

		if( newel)
		{
			copy( el, newel);
			//COMTHROW( counterparts)->Append( newel));
		}
	}
}

void SearchRepl::copy( CComPtr<IMgaFCO> p_old, CComPtr<IMgaFCO> p_new)
{
	// specific relations can't be copied: like RefersTo or SetMembers or Containment, HasAspect
	// which originate from p_old
	// those relations which -in contrast- end up at p_old: Cointained, ReferredBy, PartOfSet
	// PartOfAspect, can be copied
	// HasAttribute, HasConstraint also can be copied

	Copier::name(     p_old, p_new);
	Copier::attribs(  p_old, p_new);
	Copier::regNodes( p_old, p_new);

	Copier cp( p_old, p_new);
	cp.relations();
	cp.aspMemberships();
}

void SearchRepl::remove( CComPtr<IMgaFCOs>& p_eqClass)
{
	long c = 0;
	if( p_eqClass) COMTHROW( p_eqClass->get_Count( &c));
	for( long i = 1; i <= c; ++i)
	{
		CComPtr<IMgaFCO> el;
		COMTHROW( p_eqClass->get_Item( i, &el));
		if( !el)
			throw NullExc( "Null ptr in remove()");

		COMTHROW( el->DestroyObject());
	}
}

void SearchRepl::exec( IMgaFCO* el, CComBSTR newKind)
{
	CComPtr<IMgaFCOs> eqclass;
	
	try
	{
		CComPtr<IMgaMetaRole> metarole_fco;
		CComPtr<IMgaMetaRole> metarole_prx;
		findMetaRole( newKind, metarole_fco, metarole_prx);
		if( !metarole_fco || !metarole_prx)
			throw NullExc( "Could not find metarole");

		collect( el, eqclass);
		createSiblings( eqclass, metarole_fco, metarole_prx);
		remove( eqclass);
		eqclass.Release();
	}
	catch( NullExc& e)
	{
		std::string msg = e.getDescr();
	}
	catch( ...)//hresult_exception& )
	{
		eqclass.Release();
		int k = 9;
		++k;
	}
}

bool SearchRepl::qualifies( IMgaFCO* el)
{
	if( !el) return false;
	CComPtr<IMgaMetaFCO> meta;
	COMTHROW( el->get_Meta( &meta));

	objtype_enum typ;
	COMTHROW( el->get_ObjType( &typ));

	CComBSTR kind;
	COMTHROW( meta->get_Name( &kind));

	// paradigmsheets, connections, or aspects will not be altered (folders neither, but they are not an IMgaFCO)
	if( typ == OBJTYPE_CONNECTION || typ == OBJTYPE_SET || typ == OBJTYPE_MODEL)
		return false;

	// the following atoms or references may
	if( kind == "Atom" || kind == "Reference" || kind == "Model" || kind == "Set" || kind == "Connection" || kind == "FCO" || kind == "Folder"
	 || kind == "AtomProxy" || kind == "ReferenceProxy" || kind == "ModelProxy" || kind == "SetProxy" || kind == "ConnectionProxy" || kind == "FCOProxy" || kind == "FolderProxy")
		return true;

	return false;
}
