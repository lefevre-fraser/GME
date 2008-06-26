#include "stdafx.h"
#include "Parser.h"
#include "MgaParser.h"
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/SAXParser.hpp>
#include <stdio.h>
#include <algorithm>

#include "../Common/CommonCollection.h"
#include "../Common/CommonMgaTrukk.h"
#include <list>//slist
#include "helper.h"
#include "GUIDcreate.h"

// --------------------------- CMgaParser - copy closure dumped data parsing

STDMETHODIMP CMgaParser::ParseClos4(IMgaObject *here, BSTR filename, int options)
{
	CHECK_IN(here);

	try
	{
		CloseAll();

		COMTHROW( progress.CoCreateInstance(L"Mga.MgaProgressDlg") );
		COMTHROW( progress->SetTitle(PutInBstr("Importing SmartCopied XML data...")) );
		COMTHROW( progress->StartProgressDialog(NULL) );

		CComObjPtr<IMgaProject> p;
		COMTHROW( here->get_Project(PutOut(p)) );
		ASSERT( p != NULL );
		COMTHROW( p->get_Preferences(&project_prefs_orig) );
		manual_relid_mode = project_prefs_orig & MGAPREF_MANUAL_RELIDS ? true : false;

		m_GME = get_GME( p);//by zolmol

		COMTHROW( p->Notify(APPEVENT_XML_IMPORT_SPECIAL_BEGIN));

		COMTHROW( p->CreateTerritory(NULL, PutOut(territory), NULL) );
		COMTHROW( p->BeginTransaction(territory, TRANSACTION_NON_NESTED) );

		CComObjPtr<IMgaObject> target;
		COMTHROW(territory->OpenObj(here, PutOut(target)));

		//by zolmol
		m_maintainGuids = false; // do not preserve guids found in data pasted
		m_mergeAllowed = (options & MERGE) != 0;
		m_target = target;
		m_resolveDerFuncPtr = &CMgaParser::ResolveClosure4Derivation;
		m_clVerStr = "4";//end

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

			funcTableState = SC_MGA;
			//elementfuncs = elementfuncs_scmga;

			// manual first pass

			pass_count = 1;

			ranges.clear();
			ranges.push_front(range_type());
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
				if( ++pass_count >= 1 )//<!> reduced from 100 to 5
				{
					msgSC( CComBSTR("Exception during parsing."), MSG_ERROR);
					HR_THROW(E_TOOMANYPASSES);
				}

				parser.parse(xmlfile.c_str());
			}

			ASSERT( elements.empty() );
			ranges.clear();

			if( isNeedFor2ndStep())
			{
				CComBSTR bstr1("Some objects were not found during parsing.");
				CComBSTR bstr2("Invoking 2nd step...");
				msgSC( bstr1, MSG_ERROR);
				msgSC( bstr2, MSG_INFO);
				
				tryToFindMissedReferreds();
				tryToFindMissedSetMembers();
			}
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
		if( m_GME) m_GME->ConsoleMessage( errorinfo, MSG_ERROR);
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

CMgaParser::elementfunc CMgaParser::elementfuncs_scmga[] = // special handlers for all elements
{
	//elementfunc("project",  StartProject,      EndNone),
	elementfunc("name",       StartNone,         EndSCName),
	//elementfunc("comment",  StartNone,         EndComment),
	//elementfunc("author",   StartNone,         EndAuthor),
	elementfunc("value",      StartNone,         EndSCValue),
	elementfunc("regnode",    StartSCRegNode,    EndSCRegNode),
	elementfunc("attribute",  StartSCAttribute,  EndNone),
	elementfunc("constraint", StartNone,         EndSCConstraint),
	elementfunc("folder",     StartSCFolder,     EndNone),
	elementfunc("model",      StartSCModel,      EndNone),
	elementfunc("atom",       StartSCAtom,       EndNone),
	elementfunc("connection", StartSCConnection, EndSCConnection),
	elementfunc("connpoint",  StartSCConnPoint,  EndNone),
	elementfunc("reference",  StartSCReference,  EndNone),
	elementfunc("set",        StartSCSet,        EndNone),
	elementfunc("clipboard",  StartBCClipboard,  EndNone),	// common for closures
	elementfunc("", NULL, NULL)
};

void CMgaParser::ResolveClosure4Derivation(const attributes_type &attributes, deriv_type &deriv)
{
	const std::string *s = GetByNameX(attributes, "derivedfrom");
	if( s == NULL )
	{
		s = GetByNameX(attributes, "closurelibderivedfrom");
		if( s != NULL)
		{
			CComObjPtr<IMgaObject> obj;
			findObjOnAbsPath( project, *s, obj, "archetype");
			if( obj)
				COMTHROW( obj.QueryInterface( deriv.from));
			else
			{
				CComBSTR bstr("Archetype can not be found in library. Basetype lost. ");
				bstr.Append("Search path used: ");
				bstr.Append( makeViewable(*s).c_str());
				msgSC( bstr, MSG_ERROR);
			}

		}
		else //if( s == NULL)
		{
			const std::string* g;
			g = GetByNameX( attributes, "smartDerivedFromGUID");
			s = GetByNameX( attributes, "closure2derivedfrom");

			std::string rel_path_changed = s? *s: "";
			// since the derfrom is calculated relatively to the fco, 
			// we have to modify the path so that it could be found
			// with a search starting from its container
			if( rel_path_changed.substr(0, 4) == "/@..")
				rel_path_changed = rel_path_changed.substr(4);
			// else: the object has similar name to its archetype
			// else: the derfrom object cannot be inside the derived object

			CComObjPtr<IMgaObject> place;
			GetPrevObj(place);

			if( g != NULL)
			{
				if( s != NULL) // try a combined search stepping up in the hierarchy then use guid
					findFCOWithRelPathAndGUID( place, rel_path_changed, *g, deriv.from);

				if( !deriv.from) // not found, then search in the whole project with GUID
				{
					CComObjPtr<IMgaProject> pr;
					COMTHROW( place->get_Project( PutOut( pr)));
					CComObjPtr<IMgaFolder>  rf;
					COMTHROW( pr->get_RootFolder( PutOut( rf)));
					findFCOWithGUIDInTree( CComObjPtr<IMgaObject>( rf), *g, deriv.from);
				}
			}

			if( !deriv.from && s != NULL)
			{
				CComObjPtr<IMgaObject> obj;
				findObjOnRelPath( CComObjPtr<IMgaObject>(place), rel_path_changed, obj, "archetype");

				if( obj)
					COMTHROW( obj.QueryInterface( deriv.from));
				else // error report
				{
					CComBSTR bstr("Archetype can not be found. Basetype lost. ");
					bstr.Append("Search path used: ");
					bstr.Append( makeViewable(rel_path_changed).c_str());
					msgSC( bstr, MSG_ERROR);
				}
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

// ------- Element Handlers
void CMgaParser::StartSCConnection(const attributes_type &attributes)
{
	bool skip_inner_elements = false;
	CComObjPtr<IMgaFCO> conn;
	deriv_type deriv;
	//ResolveDerivation(attributes, deriv);
	(*this.*m_resolveDerFuncPtr)(attributes, deriv);

	if( GetPrevName() == "folder" )
	{
		CComObjPtr<IMgaFolder> prev;
		GetPrevObj(prev);

		preparerelid(attributes);
		if( deriv.from != NULL )
		{
			COMTHROW( prev->DeriveRootObject(deriv.from, deriv.isinstance, PutOut(conn)) );

			// user info
			CComBSTR msg = makeLink( conn, makeNameViewable( GetByName(attributes, "closurename")), true);
			msg.Append( " connection derived from ");
			msg.AppendBSTR( makeLink( deriv.from));
			msgSC( msg, MSG_INFO);
		}
		else
		{
			CComObjPtr<IMgaMetaFCO> meta;
			COMTHROW( resolver->get_KindByStr(prev, PutInBstrAttr(attributes, "kind"), 
				OBJTYPE_CONNECTION, PutOut(meta)) );
			ASSERT( meta != NULL );

			COMTHROW( prev->CreateRootObject(meta, PutOut(conn)) );
		}
		assignrelid(conn);
	}
	else
	{
		ASSERT( GetPrevName() == "model" );

		CComObjPtr<IMgaModel> prev;
		GetPrevObj(prev);

		CComObjPtr<IMgaMetaRole> role;
		COMTHROW( resolver->get_RoleByStr(prev, 
			PutInBstrAttr(attributes, "kind"), OBJTYPE_CONNECTION,
			PutInBstrAttr(attributes, "role"), NULL, PutOut(role)) );
		ASSERT( role != NULL );

		if( deriv.from != NULL )
		{
			CComObjPtr<IMgaConnection> derivedfrom;
			COMTHROW( deriv.from.QueryInterface(derivedfrom) );

			if( deriv.isprimary )
			{
				preparerelid(attributes);
				COMTHROW( prev->DeriveChildObject(derivedfrom, role, deriv.isinstance, PutOut(conn)) );
				assignrelid(conn);
			}
			else
			{
				COMTHROW( prev->get_ChildDerivedFrom(derivedfrom, PutOut(conn)) );
			}

			// user info
			CComBSTR msg = makeLink( conn, makeNameViewable( GetByName(attributes, "closurename")), true);
			msg.Append( " connection derived from ");
			msg.AppendBSTR( makeLink( deriv.from));
			msgSC( msg, MSG_INFO);
		}
		else
		{
			// 'attributes' contains the id of the object (in the source project)
			bool found = findObject( prev, attributes, conn, 'C');

			// create only if not found 
			if( !found)
			{
				// parse the connection end info
				CComObjPtr<IMgaFCO> o1, o2;
				CComObjPtr<IMgaFCOs> chain1, chain2;
				parseConnection( CComObjPtr<IMgaObject>( prev), attributes, o1, o2, chain1, chain2);
				if( o1 && o2)
				{
					preparerelid(attributes);
					COMTHROW( prev->CreateSimpleConn( role, o1, o2, chain1, chain2, PutOut(conn)));
					assignrelid(conn);

					// user info
					CComBSTR msg = makeLink( conn, makeNameViewable( GetByName(attributes, "closurename")));
					msg.Append( " connection created.");
					msgSC( msg, MSG_INFO);
				}
				else
				{
					// error, could not find a correct reference chain
					CComBSTR bstr("Connection \"");
					bstr.Append( makeNameViewable( GetByName(attributes, "closurename")).c_str());
					bstr.Append("\": could not be created.");
					msgSC( bstr, MSG_ERROR);

					bstr.Empty();
					bstr.Append("   Reference chain involved: ");
					if( !o1) bstr.Append( makeViewable( GetByName( attributes, "smart0RefChain" )).c_str());
					else if( !o2) bstr.Append( makeViewable( GetByName( attributes, "smart1RefChain" )).c_str());
					msgSC( bstr, MSG_ERROR);

					bstr.Empty();
					bstr.Append("   Target path used: ");
					if( !o1) bstr.Append( makeViewable( GetByName( attributes, "smart0Target" )).c_str());
					else if( !o2) bstr.Append( makeViewable( GetByName( attributes, "smart1Target" )).c_str());
					msgSC( bstr, MSG_ERROR);

					// to safely pass through hard times (parsing internal connpoints, attributes, regnodes...
					// we create a temporary connection with "handicapped" extrsinfo
					// which will be deleted by EndSCConnection
					
					preparerelid(attributes);
					COMTHROW( prev->CreateChildObject(role, PutOut(conn)) );
					assignrelid(conn);
					
					GetCurrent().exstrinfo = "handicapped";
				}
			}
			else // will skip contained elements/attribute values/regnode entries/constraints/name element
			{    // will use the object found
				skip_inner_elements = true;

				// user info
				CComBSTR msg = "Merging ";
				msg.AppendBSTR(makeLink( conn));
				msg.Append( " connection.");
				msgSC( msg, MSG_INFO);
			}

		}
	}
	ASSERT( conn != NULL );
	GetCurrent().object = conn;

	if( GetByName(attributes, "isbound") == "yes" 
		|| skip_inner_elements) 
		GetCurrent().exstrinfo = "skip";

	RegisterLookup(attributes, conn);
}

bool CMgaParser::findConnectionEnd
		( CComObjPtr<IMgaObject> pPrev
		, const std::string& isbound
		, const std::string& role
		, const std::string& targetGUID
		, const std::string& targetPATH
		, const std::string& refchainGUID
		, const std::string& refchainPATH
		, CComObjPtr<IMgaFCO>& pFoundObj
		, CComObjPtr<IMgaFCOs>& pFoundRefChain
		)
{
	std::vector< std::string> guid_closure_ref_vec;
	if( !refchainGUID.empty())
	{
		int pos = refchainGUID.find_first_not_of(' ', 0);
		ASSERT( pos >= 0 );
		while( pos < (int) refchainGUID.length() )
		{
			int pos2 = refchainGUID.find_first_of(' ', pos);
			if( pos2 < 0 )
				pos2 = refchainGUID.length();
			ASSERT( pos2 > pos );

			
			guid_closure_ref_vec.push_back( std::string(refchainGUID, pos, pos2-pos));
			pos = pos2+1;
		}
	}

	std::vector< std::string> name_closure_ref_vec;
	if( !refchainPATH.empty())
	{
		int pos = refchainPATH.find_first_not_of(' ', 0);
		ASSERT( pos >= 0 );
		while( pos < (int) refchainPATH.length() )
		{
			int pos2 = refchainPATH.find_first_of(' ', pos);
			if( pos2 < 0 )
				pos2 = refchainPATH.length();
			ASSERT( pos2 > pos );

			
			name_closure_ref_vec.push_back( std::string(refchainPATH, pos, pos2-pos));
			pos = pos2+1;
		}
	}

	if( guid_closure_ref_vec.size() < name_closure_ref_vec.size()) 
		guid_closure_ref_vec.clear(); // invalid guid chain string info

	// will try to reconstruct the reference chain (into pFoundRefChain) based on the refs and closure2refs attribute value
	COMTHROW( pFoundRefChain.CoCreateInstance(L"Mga.MgaFCOs"));

	CComObjPtr<IMgaModel> container; // this is the container we will look in for the target

	if( !guid_closure_ref_vec.empty())
	{
		// based on guid

		// try to find the first elements in the ref chain inside the container where conn is present
		CComObjPtr<IMgaFCO> next_obj;
		CComObjPtr<IMgaFCO> last_obj; // this will be a model

		// search based on closurerefs
		findFCOWithGUID( CComObjPtr<IMgaObject>( pPrev), guid_closure_ref_vec[0], next_obj);

		// we will build up the collection of references
		unsigned int i;
		for( i = 0; next_obj != 0 && i < guid_closure_ref_vec.size(); ++i)
		{
			// we don't have to deal with name_closure_ref_vec[i] except if i == 0
			// just inquire the referred object by next_obj reference

			objtype_enum type;
			COMTHROW( next_obj->get_ObjType( &type));
			if( type == OBJTYPE_REFERENCE)
			{
				CComObjPtr<IMgaReference> ref;
				COMTHROW( next_obj.QueryInterface( ref));
				if( ref)
				{
					CComObjPtr<IMgaFCO> refd;
					COMTHROW( ref->get_Referred( PutOut( refd)));
					
					if( refd)
					{
						// we could check the guid of refd against guid_closure_ref_vec[i]
						
						// put the latest valid reference at the end of the collection
						COMTHROW(pFoundRefChain->Append(next_obj));

						objtype_enum type;
						COMTHROW( refd->get_ObjType( &type));
						if( type == OBJTYPE_REFERENCE)
							next_obj = refd;
						else
						{
							next_obj = 0;
							if( type == OBJTYPE_MODEL)
								last_obj = refd;
						}
					}
				}
			}
		}
		//  i == size should we check this?
		if( i == guid_closure_ref_vec.size() && last_obj) COMTHROW( last_obj.QueryInterface( container));
	}
	
	if( !container && name_closure_ref_vec.size() > 0) // not found based on GUID
	{
		// try to find the first elements in the ref chain inside the container where conn is present

		CComObjPtr<IMgaFCO> next_obj;
		CComObjPtr<IMgaFCO> last_obj; // this will be a model

		CComObjPtr<IMgaObject> nx_obj;

		// search based on closurerefs
		findObjOnRelPath( CComObjPtr<IMgaObject>( pPrev), name_closure_ref_vec[0], nx_obj, "reference chain");
		if( nx_obj) COMTHROW( nx_obj.QueryInterface( next_obj));

		// we will build up the collection of references
		unsigned int i;
		for( i = 0; next_obj != 0 && i < name_closure_ref_vec.size(); ++i)
		{
			// we don't have to deal with name_closure_ref_vec[i] except if i == 0
			// just inquire the referred object by next_obj reference

			objtype_enum type;
			COMTHROW( next_obj->get_ObjType( &type));
			if( type == OBJTYPE_REFERENCE)
			{
				CComObjPtr<IMgaReference> ref;
				COMTHROW( next_obj.QueryInterface( ref));
				if( ref)
				{
					CComObjPtr<IMgaFCO> refd;
					COMTHROW( ref->get_Referred( PutOut( refd)));
					
					if( refd)
					{
						// put the latest valid reference at the end of the collection
						COMTHROW(pFoundRefChain->Append(next_obj));

						objtype_enum type;
						COMTHROW( refd->get_ObjType( &type));
						if( type == OBJTYPE_REFERENCE)
							next_obj = refd;
						else
						{
							next_obj = 0;
							if( type == OBJTYPE_MODEL)
								last_obj = refd;
						}
					}
				}
			}
		}

		// i == size should we check this?
		if( i == name_closure_ref_vec.size() && last_obj) COMTHROW( last_obj.QueryInterface( container));
	}

	else // plain connection
	{
		CComQIPtr<IMgaModel> m( pPrev);
		container = m; // must be in a model
	}


	if( !container)
	{
		//throw pass_exception();
		//pFoundRefChain->removeall();
		return false;
	}
	else	// container is a valid model
	{		// find the target object in it identified by targetGUID/targetPATH
		if( !targetGUID.empty())
		{
			findFCOWithGUID( CComObjPtr<IMgaObject>( pPrev), targetGUID, pFoundObj);
		}
		
		if( !pFoundObj && !targetPATH.empty())
		{
			CComObjPtr<IMgaObject> t_target;
			findObjOnRelPath( CComObjPtr<IMgaObject>( pPrev), targetPATH, t_target, "target");
			if( t_target) COMTHROW( t_target.QueryInterface( pFoundObj));
		}
	}

	return (pFoundObj != 0);
}

bool CMgaParser::parseConnection
			( CComObjPtr<IMgaObject> pPrev
			, const attributes_type &pAttributes
			, CComObjPtr<IMgaFCO>& pSrcObj
			, CComObjPtr<IMgaFCO>& pDstObj
			, CComObjPtr<IMgaFCOs>& pFoundSrcRefChain
			, CComObjPtr<IMgaFCOs>& pFoundDstRefChain
			)
{
	const char *role_attr []       = { "smart0Role"         , "smart1Role"         };
	const char *targetGUID_attr [] = { "smart0TargetGUID"   , "smart1TargetGUID"   };
	const char *target_attr []     = { "smart0Target"       , "smart1Target"       };
	const char *refchainGUID_attr[]= { "smart0RefChainGUID" , "smart1RefChainGUID" };
	const char *refchain_attr []   = { "smart0RefChain"     , "smart1RefChain"     };
	const char *isbound_attr []    = { "smart0IsBound"      , "smart1IsBound"      };

	CComObjPtr<IMgaFCO> obj[2];
	CComObjPtr<IMgaFCOs> coll[2];
	for( int i = 0 ; i < 2; ++i)
	{
		std::string isbound         = GetByName( pAttributes, isbound_attr[i]);
		std::string role            = GetByName( pAttributes, role_attr[i]);
		std::string targetGUID      = GetByName( pAttributes, targetGUID_attr[i]);
		std::string refchainGUID    = GetByName( pAttributes, refchainGUID_attr[i]);
		std::string target          = GetByName( pAttributes, target_attr[i]);
		std::string refchain        = GetByName( pAttributes, refchain_attr[i]);
		findConnectionEnd( pPrev, isbound, role, targetGUID, target, refchainGUID, refchain, obj[i], coll[i]);
	}

	if( obj[0] && obj[1]) 
	{
		pSrcObj = obj[0];
		pDstObj = obj[1];
		pFoundSrcRefChain = coll[0];
		pFoundDstRefChain = coll[1];
		return true;
	}

	return false;
}


void CMgaParser::EndSCConnection()
{
	CComObjPtr<IMgaConnection> fresh_conn;

	ASSERT( GetCurrent().object);
	COMTHROW( GetCurrent().object.QueryInterface( fresh_conn));
	if( !fresh_conn) 
	{
		ASSERT(0); // it should be a connection at least
		return;
	}

	CComObjPtrVector<IMgaConnPoint> cps;
	COMTHROW( fresh_conn->get_ConnPoints( PutOut( cps)));
	if( cps.size() < 2 || GetCurrent().exstrinfo == "handicapped") // handicapped connection, error must have occurred
	{
		COMTHROW( fresh_conn->DestroyObject());
		return;
	}
}

void CMgaParser::StartSCConnPoint(const attributes_type &attributes)
{
}

void CMgaParser::StartSCReference(const attributes_type &attributes)
{
	CComObjPtr<IMgaObject> obj_prev;
	bool skip_inner_elements = false;
	bool needs_target = true;
	CComObjPtr<IMgaFCO> fco;

	deriv_type deriv;
	//ResolveDerivation(attributes, deriv);
	(*this.*m_resolveDerFuncPtr)(attributes, deriv);

	CComObjPtr<IMgaFCO> referred;

	if( GetPrevName() == "folder" )
	{
		CComObjPtr<IMgaFolder> prev;
		GetPrevObj(prev);
		obj_prev = prev;

		if( deriv.from != NULL )
		{
			preparerelid(attributes);
			COMTHROW( prev->DeriveRootObject(deriv.from, deriv.isinstance, PutOut(fco)) );
			assignrelid(fco);

			// user info
			CComBSTR msg = makeLink( fco, makeNameViewable( GetByName(attributes, "closurename")), true);
			msg.Append( " reference derived from ");
			msg.AppendBSTR( makeLink( deriv.from));
			msgSC( msg, MSG_INFO);

		}
		else
		{
			// 'attributes' contains the id of the object (in the source project)
			bool found = findObject( prev, attributes, fco, 'R');

			// create only if not found 
			if( !found)
			{
				CComObjPtr<IMgaMetaFCO> meta;
				COMTHROW( resolver->get_KindByStr(prev, PutInBstrAttr(attributes, "kind"), 
					OBJTYPE_REFERENCE, PutOut(meta)) );
				ASSERT( meta != NULL );

				preparerelid(attributes);
				COMTHROW( prev->CreateRootObject(meta, PutOut(fco)) );
				assignrelid(fco);

				// user info
				CComBSTR msg = makeLink( fco, makeNameViewable( GetByName(attributes, "closurename")));
				msg.Append( " reference created.");
				msgSC( msg, MSG_INFO);
			}
			else // will skip contained elements/attribute values/regnode entries/constraints/name element
			{    // will use the object found
				skip_inner_elements = true;
				needs_target = isNullRef( fco);

				// user info
				CComBSTR msg = "Merging ";
				msg.AppendBSTR(makeLink( fco));
				if( needs_target) msg.Append(" null");
				msg.Append( " reference.");
				msgSC( msg, MSG_INFO);
			}
		}
	}
	else
	{
		ASSERT( GetPrevName() == "model" );

		CComObjPtr<IMgaModel> prev;
		GetPrevObj(prev);
		obj_prev = prev;

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
			
			// user info
			CComBSTR msg = makeLink( fco, makeNameViewable( GetByName(attributes, "closurename")), true);
			msg.Append( " reference derived from ");
			msg.AppendBSTR( makeLink( deriv.from));
			msgSC( msg, MSG_INFO);
		}
		else
		{
			// 'attributes' contains the id of the object (in the source project)
			bool found = findObject( prev, attributes, fco, 'R');

			// create only if not found 
			if( !found)
			{
				preparerelid(attributes);
				COMTHROW( prev->CreateChildObject(role, PutOut(fco)) );
				assignrelid(fco);

				// user info
				CComBSTR msg = makeLink( fco, makeNameViewable( GetByName(attributes, "closurename")));
				msg.Append( " reference created.");
				msgSC( msg, MSG_INFO);
			}
			else // will skip contained elements/attribute values/regnode entries/constraints/name element
			{    // will use the object found
				skip_inner_elements = true;
				needs_target = isNullRef( fco);

				// user info
				CComBSTR msg = "Merging ";
				msg.AppendBSTR(makeLink( fco));
				if( needs_target) msg.Append(" null");
				msg.Append( " reference.");
				msgSC( msg, MSG_INFO);
			}
		}

	}
	ASSERT( fco != NULL );
	//fco is the reference just created or selected from the already existing ones

	bool bound = GetByName(attributes, "isbound") == "yes"; // if bound it does NOT need referees set by hand
	if( needs_target && !bound)
	{
		const std::string *s;
		s = GetByNameX(attributes, "closurelibreferred");
		if( s != NULL)
		{
			CComObjPtr<IMgaObject> obj;
			findObjOnAbsPath( project, *s, obj, "referred object");

			if( obj)
				COMTHROW( obj.QueryInterface( referred));
			else // report error
			{
				CComBSTR bstr("Reference ");
				bstr.Append( makeLink( fco, makeNameViewable( GetByName( attributes, "closurename")), true));
				bstr.Append(": target not found in library. ");
				bstr.Append("Search path used: ");
				bstr.Append( makeViewable( *s).c_str());
				msgSC(bstr, MSG_ERROR);
			}
		}
		
		if( s == NULL || !referred)
		{
			// first try to find referred object based on GUID
			std::string guid = GetByName(attributes, "smartReferredGUID");
			std::string path = GetByName(attributes, "closure2referred");
			
			if( !guid.empty())
			{
				if( !path.empty())
				{
					// use closure2referred info for stepping up in the hierarchy (if needed) and only then use search on GUID
					findFCOWithRelPathAndGUID( CComObjPtr<IMgaObject>( fco), path, guid, referred);
				}
				
				if( !referred) // not found, then search in the whole project with GUID
				{
					CComObjPtr<IMgaProject> pr;
					COMTHROW( obj_prev->get_Project( PutOut( pr)));
					CComObjPtr<IMgaFolder>  rf;
					COMTHROW( pr->get_RootFolder( PutOut( rf)));
					findFCOWithGUIDInTree( CComObjPtr<IMgaObject>( rf), guid, referred);
				}
			}
			
			// finally perform a closure2referred based search
			if( !referred && !path.empty())
			{
				CComObjPtr<IMgaObject> obj;
				findObjOnRelPath( CComObjPtr<IMgaObject>(fco), path, obj, "referred object");

				if ( obj)
					COMTHROW( obj.QueryInterface( referred));
				else // report error
				{
					CComBSTR bstr("Reference ");
					bstr.Append( makeLink( fco, makeNameViewable( GetByName( attributes, "closurename")), true));
					bstr.Append(": target not found. ");
					bstr.Append("Search path used: ");
					bstr.Append( makeViewable( path).c_str());
					msgSC(bstr, MSG_ERROR);

					// store data to process in 2nd step
					m_notFoundReferredObject[ fco ] = path;
				}
			}
		}

		//WAS: if( !(GetByName(attributes, "isbound") == "yes") && referred != NULL )
		if( referred != NULL )
		{
			CComObjPtr<IMgaReference> ref;
			COMTHROW( fco.QueryInterface(ref) );

			COMTHROW( ref->put_Referred(referred) );
		}
	}

	GetCurrent().object = fco;
	if( skip_inner_elements)
		GetCurrent().exstrinfo = "skip";

	RegisterLookup(attributes, fco);
}

void CMgaParser::StartSCSet(const attributes_type &attributes)
{
	CComObjPtr<IMgaObject> obj_prev;
	bool skip_inner_elements = false;
	bool needs_members = true;
	CComObjPtr<IMgaFCO> fco;

	deriv_type deriv;
	//ResolveDerivation(attributes, deriv);
	(*this.*m_resolveDerFuncPtr)(attributes, deriv);

	if( GetPrevName() == "folder" )
	{
		CComObjPtr<IMgaFolder> prev;
		GetPrevObj(prev);
		obj_prev = prev;

		if( deriv.from != NULL )
		{
			preparerelid(attributes);
			COMTHROW( prev->DeriveRootObject(deriv.from, deriv.isinstance, PutOut(fco)) );
			assignrelid(fco);

			// user info
			CComBSTR msg = makeLink( fco, makeNameViewable( GetByName(attributes, "closurename")), true);
			msg.Append( " set derived from ");
			msg.AppendBSTR( makeLink( deriv.from));
			msgSC( msg, MSG_INFO);
		}
		else
		{
			// 'attributes' contains the id of the object (in the source project)
			bool found = findObject( prev, attributes, fco, 'S');

			// create only if not found 
			if( !found)
			{
				CComObjPtr<IMgaMetaFCO> meta;
				COMTHROW( resolver->get_KindByStr(prev, PutInBstrAttr(attributes, "kind"), 
					OBJTYPE_SET, PutOut(meta)) );
				ASSERT( meta != NULL );

				preparerelid(attributes);
				COMTHROW( prev->CreateRootObject(meta, PutOut(fco)) );
				assignrelid(fco);

				// user info
				CComBSTR msg = makeLink( fco, makeNameViewable( GetByName(attributes, "closurename")));
				msg.Append( " set created.");
				msgSC( msg, MSG_INFO);
			}
			else // will skip contained connpoints/elements/attribute values/regnode entries/constraints/name element
			{    // will use the object found
				skip_inner_elements = true;
				//needs_members = isEmptySet( fco); //try to add to each set new members

				// user info
				CComBSTR msg = "Merging ";
				msg.AppendBSTR(makeLink( fco));
				//if( needs_members) msg.Append(" empty");
				msg.Append( " set.");
				msgSC( msg, MSG_INFO);
			}
		}
	}
	else
	{
		ASSERT( GetPrevName() == "model" );

		CComObjPtr<IMgaModel> prev;
		GetPrevObj(prev);
		obj_prev = prev;

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

			// user info
			CComBSTR msg = makeLink( fco, makeNameViewable( GetByName(attributes, "closurename")), true);
			msg.Append( " set derived from ");
			msg.AppendBSTR( makeLink( deriv.from));
			msgSC( msg, MSG_INFO);
		}
		else
		{
			// 'attributes' contains the id of the object (in the source project)
			bool found = findObject( prev, attributes, fco, 'S');

			// create only if not found 
			if( !found)
			{
				preparerelid(attributes);
				COMTHROW( prev->CreateChildObject(role, PutOut(fco)) );
				assignrelid(fco);

				// user info
				CComBSTR msg = makeLink( fco, makeNameViewable( GetByName(attributes, "closurename")));
				msg.Append( " set created.");
				msgSC( msg, MSG_INFO);
			}
			else // will skip contained connpoints/elements/attribute values/regnode entries/constraints/name element
			{    // will use the object found
				skip_inner_elements = true;
				//needs_members = isEmptySet( fco); //try to add to each set new members

				// user info
				CComBSTR msg = "Merging ";
				msg.AppendBSTR(makeLink( fco));
				//if( needs_members) msg.Append(" empty");
				msg.Append( " set.");
				msgSC( msg, MSG_INFO);
			}
		}
	}
	ASSERT( fco != NULL );

	bool bound = GetByName(attributes, "isbound") == "yes"; // if bound it does NOT need members added by hand
	if( needs_members && !bound)
	{
		std::list< CComObjPtr<IMgaFCO> > members;//slist
		
		// mixed form is used in smartMemberGUIDs
		// i.e. {E200BEEB-34BC-4271-A134-AA5728C18124}\\/@../@module_ref1|kind=module_ref|relpos=0
		std::string combineds = GetByName(attributes, "smartMemberGUIDs");
		std::list< std::string> combinedV = tokenizer( combineds, ' ', false);

		// not needed currently, because the combined attr contains a series of <guid\\path>s
		//std::string paths = GetByName(attributes, "closure2members");
		//std::list< std::string> nameV = tokenizer( paths, ' ', false);

		std::list< std::string>::iterator li = combinedV.begin();
		for( ; li != combinedV.end(); ++li)
		{
			CComObjPtr<IMgaFCO> mem;
			
			std::string guid_s, path_s;
			if( (*li).size() >= GLOBAL_ID_LEN && (*li)[0] == '{' && (*li)[GLOBAL_ID_LEN-1] == '}' && (*li)[GLOBAL_ID_LEN] == '\\') // a guid form
			{
				guid_s = (*li).substr( 0, GLOBAL_ID_LEN);
				path_s = (*li).substr( GLOBAL_ID_LEN + 1);
			}
			else
			{
				guid_s = "";
				path_s = *li;
			}

			// search based on guid first, in the container only
			if( !guid_s.empty()) // guid not empty
			{
				findFCOWithGUID( obj_prev, guid_s, mem);
			}

			// either no guid, or not found with guid -> in each case we have to search with path
			if( !mem)
			{
				CComObjPtr<IMgaObject> obj;
				findObjOnRelPath( CComObjPtr<IMgaObject>(fco), path_s, obj, "set member");
				CComObjPtr<IMgaFCO> mem;
				if( obj) obj.QueryInterface( mem);
			}

			// if element found, and is not found in the already found members container
			if( mem)
			{
				if( std::find( members.begin(), members.end(), mem) == members.end())
					members.push_back( mem);
			}
			else
			{
				CComBSTR bstr( "Set ");
				bstr.Append( makeLink( fco, makeNameViewable( GetByName(attributes, "closurename")), true));
				bstr.Append( ": member not found. ");
				bstr.Append( "Search path used: ");
				bstr.Append( makeViewable( path_s).c_str());
				msgSC(bstr, MSG_ERROR);

				// insert data to process in 2nd step
				m_notFoundSetMembers[ fco ].push_back( path_s);
			}
		}

		CComObjPtr<IMgaSet> mgaset;
		COMTHROW( fco.QueryInterface(mgaset) );

		//WAS: if( !(GetByName(attributes, "isbound") == "yes") ) {
		{
			COMTHROW( mgaset->RemoveAll() ); //by ZolMol: if not bound then the members are different, remove the inherited members
			std::list< CComObjPtr<IMgaFCO> >::iterator i = members.begin();//slist
			while( i != members.end() )
			{
				COMTHROW( mgaset->AddMember(*i) );
				++i;
			}
		}
	}
	GetCurrent().object = fco;
	if( skip_inner_elements)
		GetCurrent().exstrinfo = "skip";

	RegisterLookup(attributes, fco);
}

void CMgaParser::StartSCModel(const attributes_type &attributes)
{
	bool skip_inner_elements = false;
	CComObjPtr<IMgaFCO> model;

	deriv_type deriv;
	//ResolveDerivation(attributes, deriv);
	(*this.*m_resolveDerFuncPtr)(attributes, deriv);


	if( GetPrevName() == "folder" )
	{
		CComObjPtr<IMgaFolder> prev;
		GetPrevObj(prev);

		preparerelid(attributes);
		if( deriv.from != NULL )
		{
			COMTHROW( prev->DeriveRootObject(deriv.from, deriv.isinstance, PutOut(model)) );

			// user info
			CComBSTR msg = makeLink( model, makeNameViewable( GetByName(attributes, "closurename")), true);
			msg.Append( " model derived from ");
			msg.AppendBSTR( makeLink( deriv.from));
			msgSC( msg, MSG_INFO);
		}
		else
		{
			// 'attributes' contains the id of the object (in the source project)
			bool found = findObject( prev, attributes, model, 'M');

			// create only if not found 
			if( !found)
			{
				CComObjPtr<IMgaMetaFCO> meta;
				COMTHROW( resolver->get_KindByStr(prev, PutInBstrAttr(attributes, "kind"), 
					OBJTYPE_MODEL, PutOut(meta)) );
				ASSERT( meta != NULL );

				COMTHROW( prev->CreateRootObject(meta, PutOut(model)) );

				// user info
				CComBSTR msg = makeLink( model, makeNameViewable( GetByName(attributes, "closurename")));
				msg.Append( " model created.");
				msgSC( msg, MSG_INFO);
			}
			else // will use the object found
			{    // will skip contained elements/attribute values/regnode entries/constraints/name element
				skip_inner_elements = true;

				// user info
				CComBSTR msg = "Merging ";
				msg.AppendBSTR(makeLink( model));
				msg.Append( " model.");
				msgSC( msg, MSG_INFO);
			}
		}
		assignrelid(model);
	}
	else
	{
		ASSERT( GetPrevName() == "model" );

		CComObjPtr<IMgaModel> prev;
		GetPrevObj(prev);

		CComObjPtr<IMgaMetaRole> role;
		COMTHROW( resolver->get_RoleByStr(prev, 
			PutInBstrAttr(attributes, "kind"), OBJTYPE_MODEL,
			PutInBstrAttr(attributes, "role"), NULL, PutOut(role)) );
		ASSERT( role != NULL );

		if( deriv.from != NULL )
		{
			CComObjPtr<IMgaModel> derivedfrom;
			COMTHROW( deriv.from.QueryInterface(derivedfrom) );

			if( deriv.isprimary )
			{
				preparerelid(attributes);
				COMTHROW( prev->DeriveChildObject(derivedfrom, role, deriv.isinstance, PutOut(model)) );
				assignrelid(model);
			}
			else
			{
				COMTHROW( prev->get_ChildDerivedFrom(derivedfrom, PutOut(model)) );
			}

			// user info
			CComBSTR msg = makeLink( model, makeNameViewable( GetByName(attributes, "closurename")), true);
			msg.Append( " model derived from ");
			msg.AppendBSTR( makeLink( deriv.from));
			msgSC( msg, MSG_INFO);
		}
		else
		{
			// 'attributes' contains the id of the object (in the source project)
			bool found = findObject( prev, attributes, model, 'M');

			// create only if not found 
			if( !found)
			{
				preparerelid(attributes);
				COMTHROW( prev->CreateChildObject(role, PutOut(model)) );
				assignrelid(model);

				// user info
				CComBSTR msg = makeLink( model, makeNameViewable( GetByName(attributes, "closurename")));
				msg.Append( " model created.");
				msgSC( msg, MSG_INFO);
			}
			else // will use the object found
			{
				skip_inner_elements = true;

				// user info
				CComBSTR msg = "Merging ";
				msg.AppendBSTR(makeLink( model));
				msg.Append( " model.");
				msgSC( msg, MSG_INFO);
			}
		}
	}
	ASSERT( model != NULL );

	GetCurrent().object = model;
	long crid = toLong(GetByName(attributes,"childrelidcntr"));
	GetCurrent().exnuminfo = crid;
	COMTHROW(CComQIPtr<IMgaModel>(model)->put_ChildRelIDCounter(crid));

	if( skip_inner_elements)
		GetCurrent().exstrinfo = "skip";

	RegisterLookup(attributes, model);
}

void CMgaParser::StartSCAtom(const attributes_type &attributes)
{
	bool skip_inner_elements = false;
	CComObjPtr<IMgaFCO> atom;

	deriv_type deriv;
	//ResolveDerivation(attributes, deriv);
	(*this.*m_resolveDerFuncPtr)(attributes, deriv);

	if( GetPrevName() == "folder" )
	{
		CComObjPtr<IMgaFolder> prev;
		GetPrevObj(prev);

		if( deriv.from != NULL )
		{
			COMTHROW( prev->DeriveRootObject(deriv.from, deriv.isinstance, PutOut(atom)) );

			// user info
			CComBSTR msg = makeLink( atom, makeNameViewable( GetByName(attributes, "closurename")), true);
			msg.Append( " atom derived from ");
			msg.AppendBSTR( makeLink( deriv.from));
			msgSC( msg, MSG_INFO);
		}
		else
		{
			// 'attributes' contains the id of the object (in the source project)
			bool found = findObject( prev, attributes, atom, 'A');

			// create only if not found
			if( !found)
			{
				CComObjPtr<IMgaMetaFCO> meta;
				COMTHROW( resolver->get_KindByStr(prev, PutInBstrAttr(attributes, "kind"),
					OBJTYPE_ATOM, PutOut(meta)) );
				ASSERT( meta != NULL );

				preparerelid(attributes);
				COMTHROW( prev->CreateRootObject(meta, PutOut(atom)) );
				assignrelid(atom);

				// user info
				CComBSTR msg = makeLink( atom, makeNameViewable( GetByName(attributes, "closurename")));
				msg.Append( " atom created.");
				msgSC( msg, MSG_INFO);
			}
			else // will use the object found
			{
				skip_inner_elements = true;

				// user info
				CComBSTR msg = "Merging ";
				msg.AppendBSTR(makeLink( atom));
				msg.Append( " atom.");
				msgSC( msg, MSG_INFO);
			}
		}
	}
	else
	{
		ASSERT( GetPrevName() == "model" );

		CComObjPtr<IMgaModel> prev;
		GetPrevObj(prev);

		CComObjPtr<IMgaMetaRole> role;
		COMTHROW( resolver->get_RoleByStr(prev, 
			PutInBstrAttr(attributes, "kind"), OBJTYPE_ATOM,
			PutInBstrAttr(attributes, "role"), NULL, PutOut(role)) );
		ASSERT( role != NULL );

		if( deriv.from != NULL )
		{
			CComObjPtr<IMgaAtom> derivedfrom;
			COMTHROW( deriv.from.QueryInterface(derivedfrom) );

			if( deriv.isprimary )
			{
				preparerelid(attributes);
				COMTHROW( prev->DeriveChildObject(derivedfrom, role, deriv.isinstance, PutOut(atom)) );
				assignrelid(atom);
			}
			else
			{
				COMTHROW( prev->get_ChildDerivedFrom(derivedfrom, PutOut(atom)) );
			}

			// user info
			CComBSTR msg = makeLink( atom, makeNameViewable( GetByName(attributes, "closurename")), true);
			msg.Append( " atom derived from ");
			msg.AppendBSTR( makeLink( deriv.from));
			msgSC( msg, MSG_INFO);
		}
		else
		{
			// 'attributes' contains the id of the object (in the source project)
			bool found = findObject( prev, attributes, atom, 'A');
			if( !found)
			{
				// create only if not found 
				preparerelid(attributes);
				COMTHROW( prev->CreateChildObject(role, PutOut(atom)) );
				assignrelid(atom);

				// user info
				CComBSTR msg = makeLink( atom, makeNameViewable( GetByName(attributes, "closurename")));
				msg.Append( " atom created.");
				msgSC( msg, MSG_INFO);
			}
			else // will skip contained elements
			{
				skip_inner_elements = true;

				// user info
				CComBSTR msg = "Merging ";
				msg.AppendBSTR(makeLink( atom));
				msg.Append( " atom.");
				msgSC( msg, MSG_INFO);
			}
		}
	}

	ASSERT( atom != NULL );
	GetCurrent().object = atom;

	if( skip_inner_elements)
		GetCurrent().exstrinfo = "skip";

	RegisterLookup(attributes, atom);
}

void CMgaParser::StartSCFolder(const attributes_type &attributes)
{
	bool skip_inner_elements = false;
	CComObjPtr<IMgaFolder> folder;

	//if( GetPrevName() == "project" )
	//{
	//	COMTHROW( project->get_RootFolder(PutOut(folder)) );
	//}
	//else
	{
		CComObjPtr<IMgaFolder> prev;
		GetPrevObj(prev);

		CComObjPtr<IMgaMetaFolder> meta;
		CComBSTR fname( PutInBstrAttr(attributes, "kind"));

		VARIANT_BOOL previactmode;
		COMTHROW(resolver->get_IsInteractive(&previactmode));
		COMTHROW(resolver->put_IsInteractive(VARIANT_FALSE));
		HRESULT hr = resolver->get_FolderByStr(prev, fname, PutOut(meta));
		COMTHROW(resolver->put_IsInteractive(previactmode));

		ASSERT(meta);
	
//
		bool found = findFolderIn( prev, attributes, folder);

		// create only if not found
		if( !found)
		{
			preparerelid(attributes);
			COMTHROW( prev->CreateFolder(meta, PutOut(folder)));
			assignrelid(folder);

			// user info
			CComBSTR msg = makeLink(CComObjPtr<IMgaObject>(folder), makeNameViewable( GetByName(attributes, "closurename")));
			msg.Append( " folder created.");
			msgSC( msg, MSG_INFO);
		}
		else // will use the object found
		{
			skip_inner_elements = true;

			// user info
			CComBSTR msg = "Merging ";
			msg.AppendBSTR(makeLink( CComObjPtr<IMgaObject>(folder)));
			msg.Append( " folder.");
			msgSC( msg, MSG_INFO);
		}
	}
	ASSERT( folder != NULL );
	GetCurrent().object = folder;
	if( skip_inner_elements)
		GetCurrent().exstrinfo = "skip";

	long crid = toLong(GetByName(attributes,"childrelidcntr"));
	GetCurrent().exnuminfo = crid;
	COMTHROW(folder->put_ChildRelIDCounter(crid));

	RegisterLookup(attributes, folder);
}

void CMgaParser::StartSCRegNode(const attributes_type &attributes)
{
	CComObjPtr<IMgaRegNode> regnode;

	CComBstrObj name;
	CopyTo(GetByName(attributes, "name"), name);

	if( GetPrevName() == "regnode" )
	{
		CComObjPtr<IMgaRegNode> prev;
		GetPrevObj(prev);

		COMTHROW( prev->get_SubNodeByName(name, PutOut(regnode)) );
	}
	else if( GetPrevName() == "folder" )
	{
		CComObjPtr<IMgaFolder> prev;
		GetPrevObj(prev);

		COMTHROW( prev->get_RegistryNode(name, PutOut(regnode)) );
	}
	else if( GetPrevName() == "attribute" )
	{
		CComObjPtr<IMgaAttribute> prev;
		GetPrevObj(prev);

		COMTHROW( prev->get_RegistryNode(name, PutOut(regnode)) );
	}
	else
	{
		CComObjPtr<IMgaFCO> prev;
		GetPrevObj(prev);

		COMTHROW( prev->get_RegistryNode(name, PutOut(regnode)) );
	}
	ASSERT( regnode != NULL );

	// check its status
	long st;
	COMTHROW( regnode->get_Status( &st));
	
	// if MERGE case (skip) and if value is defined HERE, then skip it (don't touch) its value
	// but the subnodes may change! even in this case if UNDEF, or they may be created if they not exist
	if( GetPrevious().exstrinfo == "skip" && st == ATTSTATUS_HERE)
	{
		GetCurrent().exstrinfo = "skip"; // might have subelements so skip those as well
		GetCurrent().object = regnode;
		return;
	}

	if( GetByNameX(attributes, "status") == NULL )
		COMTHROW( regnode->put_Value(NULL) );

	if( GetByName(attributes, "isopaque") == "yes" )
		COMTHROW( regnode->put_Opacity(VARIANT_TRUE) );

	GetCurrent().object = regnode;
}

void CMgaParser::EndSCRegNode()
{
	if( GetPrevious().exstrinfo == "skip") // if merge return, deal only with new regnodes
		return;

	CComObjPtr<IMgaRegNode> fresh_regnode;

	ASSERT( GetCurrent().object);
	COMTHROW( GetCurrent().object.QueryInterface( fresh_regnode));
	if( !fresh_regnode) return;


	// responsible for shifting the guid related regnodes:
	// guid goes to guid/prev node
	// new guid to be created int guid node

	CComBSTR nm;
	COMTHROW( fresh_regnode->get_Name( &nm));

	if( nm != GLOBAL_ID_STR)
		return;
		
	long status;
	COMTHROW( fresh_regnode->get_Status( &status));

	if( status != 0) // guid NOT defined here
		return;

	CComBSTR guid;
	// guid in the old project
	COMTHROW( fresh_regnode->get_Value( &guid));

	// replace the old GUID with a new one
	COMTHROW( fresh_regnode->put_Value( GuidCreate::newGuid()));
			
	if( guid.Length() != GLOBAL_ID_LEN) // guid invalid, do not store it in prev subnode
		return;

	// store the old GUID in 'prev' subnode
	CComPtr<IMgaRegNode> subnd;
	COMTHROW( fresh_regnode->get_SubNodeByName( CComBSTR(PREV_ID_STR), &subnd));

	if( subnd) COMTHROW( subnd->put_Value( PutInBstr( guid)) );

}

void CMgaParser::StartSCAttribute(const attributes_type &attributes)
{
	CComObjPtr<IMgaAttribute> attr;

	CComObjPtr<IMgaFCO> fco;
	GetPrevObj(fco);

	CComObjPtr<IMgaMetaAttribute> metaattr;
	HRESULT hr = resolver->get_AttrByStr(fco, PutInBstrAttr(attributes, "kind"), PutOut(metaattr));

    if( FAILED(hr) || metaattr == NULL )
    {
        GetCurrent().object = NULL;
        return;
    }

	COMTHROW( fco->get_Attribute(metaattr, PutOut(attr)) );

	ASSERT( attr != NULL );
	GetCurrent().object = attr;

	long st; // check its status: if value is defined HERE, then skip it (don't touch)
	COMTHROW( attr->get_Status( &st));

	// in case parent is merged (skipped) and attr is defined HERE, skip inner contents:
	if( GetPrevious().exstrinfo == "skip" && st == ATTSTATUS_HERE)
	{
		GetCurrent().exstrinfo = "skip"; // might have subelements so skip those as well
		return;
	}

	if( GetByNameX(attributes, "status") == NULL )
	{
		// we set some value, and from the "value" element we set the actual value

		CComVariant v;
		COMTHROW( attr->get_Value(PutOut(v)) );
		COMTHROW( attr->put_Value(v) );
	}
}

void CMgaParser::EndSCName()
{
	if( GetPrevious().exstrinfo == "skip") // has no sub elements
		return;

	//if( GetPrevName() == "project" )
	//{
	//	COMTHROW( project->put_Name(PutInBstr(GetCurrData())) );
	//}
	//else
	if( GetPrevName() == "constraint" )
	{
		constraint_name = GetCurrData();
	}
	else if( GetPrevious().object != NULL ) 
	{
		CComObjPtr<IMgaObject> prev;
		GetPrevObj(prev);
		COMTHROW( prev->put_Name(PutInBstr(GetCurrData())) );
	}
}

void CMgaParser::EndSCValue()
{
	if( GetPrevious().exstrinfo == "skip") // has no sub elements
		return;

	// skip if the object is ignored
    if( GetPrevious().object == NULL )
        return;

	if( GetPrevName() == "constraint" )
	{
		constraint_value = GetCurrData();
	}
	else 
		if( GetPrevName() == "regnode" )
	{
		CComObjPtr<IMgaRegNode> regnode;
		GetPrevObj(regnode);

		long status;
		COMTHROW( regnode->get_Status(&status) );

		// when we create the registry node, 
		// we fill it by an empty string if not inherited or not undefined
		if( status == 0)
			COMTHROW( regnode->put_Value(PutInBstr(GetCurrData())) );
	}
	else if( GetPrevName() == "attribute" ) 
	{
		CComObjPtr<IMgaAttribute> attr;
		GetPrevObj(attr);

		long status;
		COMTHROW( attr->get_Status(&status) );

		// if inherited, then do not modify the value
		if( status != 0 )
			return;

		CComObjPtr<IMgaMetaAttribute> metaattr;
		COMTHROW( attr->get_Meta(PutOut(metaattr)) );
		ASSERT( metaattr != NULL );

		attval_enum attval;
		COMTHROW( metaattr->get_ValueType(&attval) );

		CComVariant v;

		switch( attval )
		{
		case ATTVAL_STRING:
		case ATTVAL_ENUM:
		case ATTVAL_DYNAMIC:
			CopyTo(GetCurrData(), v);
			break;

		case ATTVAL_INTEGER:
			CopyTo(GetCurrData(), v);
			COMTHROW( v.ChangeType(VT_I4) );
			break;

		case ATTVAL_DOUBLE:
			CopyTo(GetCurrData(), v);
			COMTHROW( v.ChangeType(VT_R8) );
			break;

		case ATTVAL_BOOLEAN:
			{
				char c = tolower(*GetCurrData().c_str());
				CopyTo( (c == 't' || c == '1' || c == 'y') ? VARIANT_TRUE : VARIANT_FALSE, v);
				break;
			}

		case ATTVAL_REFERENCE:
			{
				CComObjPtr<IMgaFCO> object;
				LookupByID(GetCurrData(), object);

				if( object == NULL )
					throw pass_exception();

				CopyTo(object, v);
			}

		default:
			HR_THROW(E_INVALID_META);

		};

		COMTHROW( attr->put_Value(v) );
	}
}

void CMgaParser::EndSCConstraint()
{
	if( GetPrevious().exstrinfo == "skip")
	{
		GetCurrent().exstrinfo = "skip"; // might have subelements, so skip those as well
		return;
	}

	CComObjPtr<IMgaConstraint> constraint;

	if( GetPrevName() == "folder" )
	{
		CComObjPtr<IMgaFolder> folder;
		GetPrevObj(folder);

		COMTHROW( folder->DefineConstraint(PutInBstr(constraint_name), 0, // FIXME: the mask
			PutInBstr(constraint_value), PutOut(constraint)) );
	}
	else
	{
		CComObjPtr<IMgaFCO> fco;
		GetPrevObj(fco);

		COMTHROW( fco->DefineConstraint(PutInBstr(constraint_name), 0, // FIXME: the mask
			PutInBstr(constraint_value), PutOut(constraint)) );
	}
}


