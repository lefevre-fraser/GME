#include "stdafx.h"
#include "Parser.h"
#include "MgaParser.h"
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/SAXParser.hpp>
#include <stdio.h>

#include "../Common/CommonCollection.h"
#include "../Common/CommonMgaTrukk.h"
#include <list>//slist
#include "helper.h"

// --------------------------- CMgaParser - basic copy closure dumped data parsing

STDMETHODIMP CMgaParser::ParseClos1(IMgaObject *here, BSTR filename)
{
	CHECK_IN(here);

	try
	{
		CloseAll();

		COMTHROW( progress.CoCreateInstance(L"Mga.MgaProgressDlg") );
		COMTHROW( progress->SetTitle(PutInBstr("Importing CopyClosured XML data...")) );
		COMTHROW( progress->StartProgressDialog(NULL) );

		CComObjPtr<IMgaProject> p;
		COMTHROW( here->get_Project(PutOut(p)) );
		ASSERT( p != NULL );
		COMTHROW( p->get_Preferences(&project_prefs_orig) );
		manual_relid_mode = project_prefs_orig & MGAPREF_MANUAL_RELIDS ? true : false;

		m_GME = get_GME( p); // by zolmol

		COMTHROW( p->Notify(APPEVENT_XML_IMPORT_SPECIAL_BEGIN));

		COMTHROW( p->CreateTerritory(NULL, PutOut(territory), NULL) );
		COMTHROW( p->BeginTransaction(territory, TRANSACTION_NON_NESTED) );

		CComObjPtr<IMgaObject> target;
		COMTHROW(territory->OpenObj(here, PutOut(target)));

		//by zolmol
		m_maintainGuids = false; // do not preserve guids found in data pasted
		m_target = target;
		m_resolveDerFuncPtr = CMgaParser::ResolveClosure1Derivation;
		//m_clVer = 1;
		m_clVerStr = "1";//end

		if( m_target && m_GME) 
		{
			CComBSTR bstr, id, nm;
			COMTHROW( m_target->get_ID( &id));
			COMTHROW( m_target->get_Name( &nm));
			bstr.Append("[Closure Parser] Inserting copy closured data into: <A HREF=\"mga:");
			bstr.AppendBSTR( id);
			bstr.Append("\">");
			bstr.AppendBSTR( nm);
			bstr.Append("</A>");
			COMTHROW( m_GME->ConsoleMessage(bstr, MSG_INFO));
		}

		project_prefs = project_prefs_orig | MGAPREF_IGNORECONNCHECKS;
		COMTHROW( p->put_Preferences(project_prefs) );

		COMTHROW( resolver.CoCreateInstance(L"Mga.MgaResolver") );
		ASSERT( resolver != NULL );

		project = p;

		CopyTo(filename, xmlfile);

		try
		{
			XMLPlatformUtils::Initialize();

			SAXParser parser;
			parser.setDoValidation(true);
			parser.setDocumentHandler(this);
			parser.setErrorHandler(this);
			parser.setEntityResolver(this);

			elementfuncs = elementfuncs_bcmga;

			// manual first pass

			pass_count = 1;

			ranges.clear();
			ranges.push_front();
			ranges.front().begin = 1;
			ranges.front().end = (counter_type)-1;
			ranges.front().previous.name = "start";
			ranges.front().previous.object = target;
			skip_element_level = 0;
			
			parser.parse(xmlfile.c_str());

			ASSERT( ranges.front().begin == 1 );
			ranges.pop_front();
			elements.clear();

			max_counter = counter;

			// the other passes

			parser.setDoValidation(false);

			while( !ranges.empty() && ranges.front().begin != (counter_type)-1 )
			{
				// FIXME: better algorithm for infinite loop
				if( ++pass_count >= 100 )
					HR_THROW(E_TOOMANYPASSES);

				parser.parse(xmlfile.c_str());
			}

			ASSERT( elements.empty() );
			ranges.clear();
		}
	    catch(const XMLException &e)
		{
			XmlStr desc(e.getMessage());

			ThrowXmlError(desc.c_str());
		}
		COMTHROW( project->put_Preferences(project_prefs_orig) );

		for(librecords::reverse_iterator i = libstodo.rbegin(); i != libstodo.rend(); i++) { // copied from ParseProject in order to recognize libraries (zolmol)
			COMTHROW(i->f->put_LibraryName(CComBSTR(i->libname.c_str())));
			COMTHROW(i->f->put_Exempt(VARIANT_FALSE));
		}
		libstodo.clear();

		COMTHROW( project->CommitTransaction() );
		COMTHROW( project->Notify(APPEVENT_XML_IMPORT_SPECIAL_END));
		project = NULL;
		clear_GME( m_GME);

		CloseAll();
	}
	catch(hresult_exception &e)
	{
		CloseAll();
		// in case we rethrew the [probably MGA originated] exception 
		// we have set into errorinfo the location info
		if( m_GME) COMTHROW( m_GME->ConsoleMessage( errorinfo, MSG_ERROR));
		clear_GME( m_GME);

		ASSERT( FAILED(e.hr) );
		if( e.hr == E_XMLPARSER )
			SetErrorInfo(errorinfo);
		else
			SetErrorInfo2(e.hr);

		return e.hr;
	}
	return S_OK;
}

CMgaParser::elementfunc CMgaParser::elementfuncs_bcmga[] = 
{
	//elementfunc("project", StartProject, EndNone),
	elementfunc("name", StartNone, EndName),
	elementfunc("comment", StartNone, EndComment),
	elementfunc("author", StartNone, EndAuthor),
	elementfunc("value", StartNone, EndValue),
	elementfunc("regnode", StartRegNode, EndNone),
	elementfunc("attribute", StartAttribute, EndNone),
	elementfunc("constraint", StartNone, EndConstraint),
	elementfunc("folder", StartFolder, EndNone),
	elementfunc("model", StartModel, EndNone),
	elementfunc("atom", StartAtom, EndNone),
	elementfunc("connection", StartConnection, EndNone),
	elementfunc("connpoint", StartBCConnPoint, EndNone),	// diff
	elementfunc("reference", StartBCReference, EndNone),	// diff
	elementfunc("set", StartBCSet, EndNone),				// diff
	elementfunc("clipboard", StartBCClipboard, EndNone),	// diff, common for closure clipboards
	elementfunc("", NULL, NULL)
};

// ------- Element Handlers
void CMgaParser::StartBCClipboard(const attributes_type &attributes)
{
	ASSERT( project != NULL );
	ASSERT( GetPrevName() == "start" );
	ASSERT( GetPrevious().object != NULL );

	const CComObjPtr<IUnknown> &obj = GetPrevious().object;
	GetCurrent().object = obj;

	CComObjPtr<IMgaModel> model;
	CComObjPtr<IMgaFolder> folder;

	if( SUCCEEDED(obj.QueryInterface(model)) )
		GetCurrent().name = "model";
	else if( SUCCEEDED(obj.QueryInterface(folder)) )
		GetCurrent().name = "folder";
	else
		HR_THROW(E_INVALID_FILENAME);

	const std::string *ver = GetByNameX(attributes, "closureversion");

	ASSERT( ver);
	ASSERT( ver->compare(m_clVerStr) == 0);

	const std::string *acceptingkinds = GetByNameX(attributes, "acceptingkind");
	if( acceptingkinds != NULL)
	{
		CComBstrObj kind_name;
		if( model)
		{
			CComObjPtr<IMgaMetaFCO> k_meta;
			COMTHROW( model->get_Meta( PutOut( k_meta)));
			COMTHROW( k_meta->get_Name( PutOut(kind_name)) );
		}
		else if( folder)
		{
			CComObjPtr<IMgaMetaFolder> f_meta;
			COMTHROW( folder->get_MetaFolder( PutOut( f_meta)));
			COMTHROW( f_meta->get_Name( PutOut(kind_name)) );
		}
			
		// check if the accepting kind exists among the accepting kinds
		std::string kind_nm;
		CopyTo( kind_name, kind_nm);

		if( acceptingkinds->empty()) // if "" token avoid check
		{
			CComBSTR bstr("[Parser] \"clipboard\" element has empty \"acceptingkind\" attribute.");
			if( m_GME) COMTHROW( m_GME->ConsoleMessage(bstr, MSG_WARNING));
		}
		else if( !findExact( *acceptingkinds, kind_nm))
		{
			CComBSTR bstr("[Parser] Target kind \"");
			bstr.Append( kind_nm.c_str());
			bstr.Append("\" not found among accepting kinds: \"");
			bstr.Append( acceptingkinds->c_str());
			bstr.Append("\". If you'd like to avoid this check remove or modify to \"\" the \"acceptingkind\" attribute of \"clipboard\" element in an editor.");
			if( m_GME) COMTHROW( m_GME->ConsoleMessage(bstr, MSG_ERROR));
			HR_THROW(E_INVALID_MGA);
		}

	}

}

void CMgaParser::ResolveClosure1Derivation(const attributes_type &attributes, deriv_type &deriv)
{
	const std::string *s = GetByNameX(attributes, "derivedfrom");
	if( s == NULL )
	{
		s = GetByNameX(attributes, "closurelibderivedfrom");
		if( s == NULL)
		{
			deriv.from.Release();
			return;
		}

		CComObjPtr<IMgaObject> obj;
		COMTHROW( project->get_ObjectByPath( PutInBstr( *s), PutOut( obj)) );
		if ( obj)
			COMTHROW( obj.QueryInterface( deriv.from));
		else // if nonunique is allowed
		{
			COMTHROW( project->get_NthObjectByPath( 0, PutInBstr( *s), PutOut( obj)) );
			if( obj)
				COMTHROW( obj.QueryInterface( deriv.from));

			//<!> warning about non uniqueness
			if( obj && m_GME) 
			{
				CComBSTR bstr, id, nm;
				COMTHROW( obj->get_ID( &id));
				COMTHROW( obj->get_Name( &nm));
				bstr.Append("[Closure Parser] Name ambiguity found. Selected: <A HREF=\"mga:");
				bstr.AppendBSTR( id);
				bstr.Append("\">");
				bstr.AppendBSTR( nm);
				bstr.Append("</A> as basetype. Search path used: ");
				bstr.Append( makeViewable(*s).c_str());

				COMTHROW( m_GME->ConsoleMessage(bstr, MSG_ERROR));
			}
		}

		if ( deriv.from == NULL) // do not throw exception in case of closurelibderivedfrom
		{
			deriv.from.Release();
			return;
		}
	}
	else
	{
		LookupByID(*s, deriv.from);

		if( deriv.from == NULL )
			throw pass_exception();
	}

	s = GetByNameX(attributes, "isinstance");
	deriv.isinstance = ( s != NULL && *s == "yes" ) ? VARIANT_TRUE : VARIANT_FALSE;

	s = GetByNameX(attributes, "isprimary");
	deriv.isprimary = ( s != NULL && *s == "no" ) ? false : true;
}


void CMgaParser::StartBCConnPoint(const attributes_type &attributes)
{
	ASSERT( GetPrevName() == "connection" );
	CComObjPtr<IMgaConnection> conn;
	GetPrevObj(conn);

	if( GetPrevious().exstrinfo == "skip" || GetByName(attributes, "isbound") == "yes" ) return;

	CComObjPtr<IMgaFCO> target;

	// prefer the closurelibtarget over the target:
	const std::string *libtg = GetByNameX(attributes, "closurelibtarget");
	if ( libtg != NULL)
	{
		CComObjPtr<IMgaObject> obj;
		COMTHROW( project->get_ObjectByPath( PutInBstr( *libtg), PutOut( obj)) );
		if ( obj)
			COMTHROW( obj.QueryInterface( target));
		else // if nonunique is allowed
		{
			COMTHROW( project->get_NthObjectByPath( 0, PutInBstr( *libtg), PutOut( obj)) );
			if( obj)
				COMTHROW( obj.QueryInterface( target));

			//<!> warning about non uniqueness
			if( obj && m_GME) 
			{
				CComBSTR bstr, id, nm;
				COMTHROW( obj->get_ID( &id));
				COMTHROW( obj->get_Name( &nm));
				bstr.Append("[Closure Parser] Name ambiguity found. Selected: <A HREF=\"mga:");
				bstr.AppendBSTR( id);
				bstr.Append("\">");
				bstr.AppendBSTR( nm);
				bstr.Append("</A> as connection target. Search path used: ");
				bstr.Append( makeViewable(*libtg).c_str());

				COMTHROW( m_GME->ConsoleMessage(bstr, MSG_ERROR));
			}
		}
	}

	const std::string *tg = GetByNameX(attributes, "target");
	if( tg != NULL && libtg == NULL) // valid info in target iff no closurelibtarget token
	{
		LookupByID( *tg, target);
	}

	// throw even if closurelibtarget present but not found the needed object
	if ( target == NULL)
		throw pass_exception();

	CComObjPtr<IMgaFCOs> coll;
	COMTHROW(coll.CoCreateInstance(L"Mga.MgaFCOs"));

	const std::string *s = GetByNameX(attributes, "refs");
	if( s != NULL )
	{
		int pos = s->find_first_not_of(' ', 0);
		ASSERT( pos >= 0 );
		while( pos < (int) s->length() )
		{
			int pos2 = s->find_first_of(' ', pos);
			if( pos2 < 0 )
				pos2 = s->length();
			ASSERT( pos2 > pos );

			CComObjPtr<IMgaFCO> ref;
			LookupByID(std::string(*s, pos, pos2-pos), ref);

			if( ref == NULL )
				throw pass_exception();

			COMTHROW(coll->Append(ref));

			pos = pos2+1;
		}
	}

	CComObjPtr<IMgaConnPoint> connpoint;

	COMTHROW( conn->AddConnPoint(PutInBstr(GetByName(attributes, "role")), 0,	// FIXME: multiplicity
		target, coll, PutOut(connpoint)) );
}

void CMgaParser::StartBCReference(const attributes_type &attributes)
{
	CComObjPtr<IMgaFCO> fco;

	deriv_type deriv;
	(*this.*m_resolveDerFuncPtr)(attributes, deriv);

	CComObjPtr<IMgaFCO> referred;

	const std::string *s = GetByNameX(attributes, "referred");
	if( s != NULL )
	{
		LookupByID(*s, referred);

		if( referred == NULL )
			throw pass_exception();
	}
	else // by ZolMol
	{
		s = GetByNameX(attributes, "closurelibreferred");
		if( s != NULL)
		{
			CComObjPtr<IMgaObject> obj;
			COMTHROW( project->get_ObjectByPath( PutInBstr( *s), PutOut( obj)) );
			if ( obj)
				COMTHROW( obj.QueryInterface( referred));
			else // if nonunique is allowed
			{
				COMTHROW( project->get_NthObjectByPath( 0, PutInBstr( *s), PutOut( obj)) );
				if( obj)
					COMTHROW( obj.QueryInterface( referred));

				//<!> warning about non uniqueness
				if( obj && m_GME) 
				{
					CComBSTR bstr, id, nm;
					COMTHROW( obj->get_ID( &id));
					COMTHROW( obj->get_Name( &nm));
					bstr.Append("[Closure Parser] Name ambiguity found. Selected: <A HREF=\"mga:");
					bstr.AppendBSTR( id);
					bstr.Append("\">");
					bstr.AppendBSTR( nm);
					bstr.Append("</A> as library reference. Search path used: ");
					bstr.Append( makeViewable(*s).c_str());

					COMTHROW( m_GME->ConsoleMessage(bstr, MSG_ERROR));
				}
			}
		}
	}

	if( GetPrevName() == "folder" )
	{
		CComObjPtr<IMgaFolder> prev;
		GetPrevObj(prev);

		preparerelid(attributes);
		if( deriv.from != NULL )
		{
			COMTHROW( prev->DeriveRootObject(deriv.from, deriv.isinstance, PutOut(fco)) );
		}
		else
		{
			CComObjPtr<IMgaMetaFCO> meta;
			COMTHROW( resolver->get_KindByStr(prev, PutInBstrAttr(attributes, "kind"), 
				OBJTYPE_REFERENCE, PutOut(meta)) );
			ASSERT( meta != NULL );

			COMTHROW( prev->CreateRootObject(meta, PutOut(fco)) );
		}
		assignrelid(fco);
	}
	else
	{
		ASSERT( GetPrevName() == "model" );
		CComObjPtr<IMgaModel> prev;
		GetPrevObj(prev);

		CComObjPtr<IMgaMetaRole> role;
		COMTHROW( resolver->get_RoleByStr(prev, 
			PutInBstrAttr(attributes, "kind"), OBJTYPE_REFERENCE,
			PutInBstrAttr(attributes, "role"), NULL, PutOut(role)) );
		ASSERT( role != NULL );

		if( deriv.from != NULL )
		{
			CComObjPtr<IMgaReference> derivedfrom;
			COMTHROW( deriv.from.QueryInterface(derivedfrom) );

			if( deriv.isprimary )
			{
				preparerelid(attributes);
				COMTHROW( prev->DeriveChildObject(derivedfrom, role, deriv.isinstance, PutOut(fco)) );
				assignrelid(fco);
			}
			else
			{
				COMTHROW( prev->get_ChildDerivedFrom(derivedfrom, PutOut(fco)) );
			}
		}
		else
		{
			preparerelid(attributes);
			COMTHROW( prev->CreateChildObject(role, PutOut(fco)) );
			assignrelid(fco);
		}
	}
	ASSERT( fco != NULL );

	if( !(GetByName(attributes, "isbound") == "yes") && referred != NULL )
	{
		CComObjPtr<IMgaReference> ref;
		COMTHROW( fco.QueryInterface(ref) );

		COMTHROW( ref->put_Referred(referred) );
	}

	GetCurrent().object = fco;

	RegisterLookup(attributes, fco);
}

void CMgaParser::StartBCSet(const attributes_type &attributes)
{
	CComObjPtr<IMgaFCO> fco;

	deriv_type deriv;
	(*this.*m_resolveDerFuncPtr)(attributes, deriv);

	std::list< CComObjPtr<IMgaFCO> > members;//slist

	const std::string *s = GetByNameX(attributes, "members");
	if( s != NULL )
	{
		int pos = s->find_first_not_of(' ', 0);
		ASSERT( pos >= 0 );
		while( pos < (int) s->length() )
		{
			int pos2 = s->find_first_of(' ', pos);
			if( pos2 < 0 )
				pos2 = s->length();
			ASSERT( pos2 > pos );

			CComObjPtr<IMgaFCO> member;
			LookupByID(std::string(*s, pos, pos2-pos), member);

			if( member == NULL )
				throw pass_exception();

			members.push_front(member);

			pos = pos2+1;
		}
	}

	if( GetPrevName() == "folder" )
	{
		CComObjPtr<IMgaFolder> prev;
		GetPrevObj(prev);

		preparerelid(attributes);
		if( deriv.from != NULL )
		{
			COMTHROW( prev->DeriveRootObject(deriv.from, deriv.isinstance, PutOut(fco)) );
		}
		else
		{
			CComObjPtr<IMgaMetaFCO> meta;
			COMTHROW( resolver->get_KindByStr(prev, PutInBstrAttr(attributes, "kind"), 
				OBJTYPE_SET, PutOut(meta)) );
			ASSERT( meta != NULL );

			COMTHROW( prev->CreateRootObject(meta, PutOut(fco)) );
		}
		assignrelid(fco);
	}
	else
	{
		ASSERT( GetPrevName() == "model" );
		CComObjPtr<IMgaModel> prev;
		GetPrevObj(prev);

		CComObjPtr<IMgaMetaRole> role;
		COMTHROW( resolver->get_RoleByStr(prev, 
			PutInBstrAttr(attributes, "kind"), OBJTYPE_SET,
			PutInBstrAttr(attributes, "role"), NULL, PutOut(role)) );
		ASSERT( role != NULL );

		if( deriv.from != NULL )
		{
			CComObjPtr<IMgaSet> derivedfrom;
			COMTHROW( deriv.from.QueryInterface(derivedfrom) );

			if( deriv.isprimary )
			{
				preparerelid(attributes);
				COMTHROW( prev->DeriveChildObject(derivedfrom, role, deriv.isinstance, PutOut(fco)) );
				assignrelid(fco);
			}
			else
			{
				preparerelid(attributes);
				COMTHROW( prev->get_ChildDerivedFrom(derivedfrom, PutOut(fco)) );
				assignrelid(fco);
			}
		}
		else
		{
			preparerelid(attributes);
			COMTHROW( prev->CreateChildObject(role, PutOut(fco)) );
			assignrelid(fco);
		}
	}
	ASSERT( fco != NULL );

	CComObjPtr<IMgaSet> mgaset;
	COMTHROW( fco.QueryInterface(mgaset) );

	if( !(GetByName(attributes, "isbound") == "yes") ) {
		COMTHROW( mgaset->RemoveAll() ); //by ZolMol: if not bound then the members are different, remove the inherited members
		std::list< CComObjPtr<IMgaFCO> >::iterator i = members.begin();//slist
		while( i != members.end() )
		{
			COMTHROW( mgaset->AddMember(*i) );
			++i;
		}
	}
	GetCurrent().object = fco;

	RegisterLookup(attributes, fco);
}

