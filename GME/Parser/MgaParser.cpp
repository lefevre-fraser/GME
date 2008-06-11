
#include "stdafx.h"
#include "Parser.h"
#include "MgaParser.h"
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/SAXParser.hpp>
#include <stdio.h>

#include "../Common/CommonCollection.h"
#include <list>//slist

const char * magic_exit_str = "Analysis done.Quit parsing.";
// --------------------------- CMgaParser

STDMETHODIMP CMgaParser::ParseFCOs(IMgaObject *here, BSTR filename)
{
	CHECK_IN(here);
	m_maintainGuids = false;

	try
	{
		CloseAll();

		COMTHROW( progress.CoCreateInstance(L"Mga.MgaProgressDlg") );
		COMTHROW( progress->SetTitle(PutInBstr("Importing XML file...")) );
		COMTHROW( progress->StartProgressDialog(NULL) );

		CComObjPtr<IMgaProject> p;
		COMTHROW( here->get_Project(PutOut(p)) );
		ASSERT( p != NULL );
		COMTHROW( p->get_Preferences(&project_prefs_orig) );
		manual_relid_mode = project_prefs_orig & MGAPREF_MANUAL_RELIDS ? true : false;

		m_GME = get_GME( p); // by zolmol

		COMTHROW( p->Notify(APPEVENT_XML_IMPORT_FCOS_BEGIN));

		COMTHROW( p->CreateTerritory(NULL, PutOut(territory), NULL) );
		COMTHROW( p->BeginTransaction(territory, TRANSACTION_NON_NESTED) );

		// PETER: put the 'here' object into the parser's territory
		CComObjPtr<IMgaObject> target;
		COMTHROW(territory->OpenObj(here, PutOut(target)));

		project_prefs = project_prefs_orig | MGAPREF_IGNORECONNCHECKS;
		COMTHROW( p->put_Preferences(project_prefs) );

		COMTHROW( resolver.CoCreateInstance(L"Mga.MgaResolver") );
		ASSERT( resolver != NULL );

		project = p;

		CopyTo(filename, xmlfile);

		m_resolveDerFuncPtr = CMgaParser::ResolveDerivation;
		try
		{
			XMLPlatformUtils::Initialize();

			SAXParser parser;
			parser.setDoValidation(true);
			parser.setDocumentHandler(this);
			parser.setErrorHandler(this);
			parser.setEntityResolver(this);

			elementfuncs = elementfuncs_mga;

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
		COMTHROW( project->Notify(APPEVENT_XML_IMPORT_FCOS_END));
		project = NULL;

		CloseAll();
		clear_GME( m_GME);
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

STDMETHODIMP CMgaParser::ParseProject(IMgaProject *p, BSTR filename)
{
	CHECK_IN(p);
	m_maintainGuids = true; //will be set to false if p is NOT empty

	try
	{
		CloseAll();

		COMTHROW( progress.CoCreateInstance(L"Mga.MgaProgressDlg") );
		COMTHROW( progress->SetTitle(PutInBstr("Importing XML file...")) );
		COMTHROW( progress->StartProgressDialog(NULL) );


		project = p;
		COMTHROW( project->get_Preferences(&project_prefs_orig) );
		manual_relid_mode = project_prefs_orig & MGAPREF_MANUAL_RELIDS ? true : false;

		m_GME = get_GME( p); // by zolmol

		COMTHROW( project->Notify(APPEVENT_XML_IMPORT_BEGIN));

		COMTHROW( project->CreateTerritory(NULL, PutOut(territory), NULL) );
		COMTHROW( project->BeginTransaction(territory, TRANSACTION_NON_NESTED) );

		CComObjPtr<IMgaFolder> rfld;
		COMTHROW( project->get_RootFolder( PutOut(rfld)));
		if( rfld) 
		{
			CComObjPtrVector<IMgaFolder> fols;
			CComObjPtrVector<IMgaFCO> chld;
			COMTHROW( rfld->get_ChildFCOs( PutOut( chld)));
			COMTHROW( rfld->get_ChildFolders( PutOut( fols)));
			
			m_maintainGuids = fols.empty() && chld.empty(); // maintain guids if and only if project is empty
		}
		
		project_prefs = project_prefs_orig | MGAPREF_IGNORECONNCHECKS;
		COMTHROW( project->put_Preferences(project_prefs) );

		COMTHROW( resolver.CoCreateInstance(L"Mga.MgaResolver") );
		ASSERT( resolver != NULL );

		CopyTo(filename, xmlfile);

		m_resolveDerFuncPtr = CMgaParser::ResolveDerivation;
		try
		{
			XMLPlatformUtils::Initialize();

			SAXParser parser;
			parser.setDoValidation(true);
			parser.setDocumentHandler(this);
			parser.setErrorHandler(this);
			parser.setEntityResolver(this);

			elementfuncs = elementfuncs_mga;

			// we do the first pass manually

			pass_count = 1;

			ranges.clear();
			ranges.push_front();
			ranges.front().begin = 1;
			ranges.front().end = (counter_type)-1;
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

		// readonly flag and library name can't be applied if done in wrong order
		// because of the readonly flag is applied all way down the hierarchy
		// (preventing put_LibraryName for inner libs to succeed)

		// the order of libraries in libstodo is the sequential order as they appear
		// in the xme file (depth first traversal), thus if the vector is traversed
		// in reverse order (children libraries are always handled before their parent)
		// the libroot_flag and library_flag flags can be applied with success
		for(librecords::reverse_iterator i = libstodo.rbegin(); i != libstodo.rend(); i++) {
			COMTHROW(i->f->put_LibraryName(CComBSTR(i->libname.c_str())));
			COMTHROW(i->f->put_Exempt(VARIANT_FALSE));
		}
		libstodo.clear();
		
		COMTHROW( project->put_GUID(projectguid) );

		COMTHROW( project->CommitTransaction() );
		COMTHROW( project->Notify(APPEVENT_XML_IMPORT_END));
		project = NULL;

		CloseAll();
		clear_GME( m_GME);
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

STDMETHODIMP CMgaParser::GetXMLInfo(BSTR filename, BSTR *paradigm, BSTR* parversion, VARIANT *parguid, BSTR* basename, BSTR* version) {

//	CHECK_IN(filename);
	CHECK_OUT(paradigm);
	CHECK_OUT(parversion);
	CHECK_OUT(parguid);
	CHECK_OUT(basename);
	CHECK_OUT(version);

	try
	{
		CloseAll();
		COMTHROW( progress.CoCreateInstance(L"Mga.MgaProgressDlg") );
		COMTHROW( progress->SetTitle(PutInBstr("Analyzing XML file...")) );
		COMTHROW( progress->StartProgressDialog(NULL) );


		CopyTo(filename, xmlfile);

		try
		{
			XMLPlatformUtils::Initialize();

			SAXParser parser;
			parser.setDoValidation(false);
			parser.setDocumentHandler(this);
			parser.setErrorHandler(this);
			parser.setEntityResolver(this);

			elementfuncs = elementfuncs_mgainfo;

			pass_count = 1;

			ranges.clear();
			ranges.push_front();
			ranges.front().begin = 1;
			ranges.front().end = (counter_type)-1;
			skip_element_level = 0;

			infoparname = paradigm;
			infoparversion = parversion;
			infoparguid = parguid;
			infoprojname = basename;
			infoversion = version;

			parser.parse(xmlfile.c_str());

		}
		catch(const SAXException &e)
		{
			char * p_msg = XMLString::transcode( e.getMessage());
			if( 0 != strcmp( p_msg, magic_exit_str))
			{
				ThrowXmlError( p_msg);
			}
			XMLString::release( &p_msg);
			// else just ignore it, we threw an exception for a good purpose:
			// to quit the costly parsing operation
		}
		catch(const XMLException &e)
		{
			XmlStr desc(e.getMessage());

			ThrowXmlError(desc.c_str());
		}

		CloseAll();
	}
	catch(hresult_exception &e)
	{
		CloseAll();

		ASSERT( FAILED(e.hr) );
		if( e.hr == E_XMLPARSER )
			SetErrorInfo(errorinfo);
		else
			SetErrorInfo2(e.hr);

		return e.hr;
	}
	return S_OK;
}

void CMgaParser::CloseAll()
{
	elements.clear();
	ranges.clear();

	if( progress != NULL )
	{
		progress->StopProgressDialog();
		progress = NULL;
	}

	resolver.Release();

	if( project != NULL )
	{
		project->put_Preferences(project_prefs_orig);
		project->AbortTransaction();
		project->Notify(APPEVENT_XML_IMPORT_END);
	}

	if( territory != NULL )
		territory->Destroy();

	territory = NULL;
	project = NULL;

	manual_relid_mode = false;
	relid = -2;
	
	GUID tmpguid;
	memset(&tmpguid, 0, sizeof(GUID));
	CopyTo(tmpguid, projectguid);
};

// ------- Passes

char progress_msg[512];
char refresh_counter;

void CMgaParser::startElement(const XMLCh* const name, AttributeList& attributes)
{
	ASSERT( !ranges.empty() );

	++counter;

	if( ++refresh_counter == 0 )
	{
		sprintf(progress_msg, "Phase: %d, number of parsed objects: %ld", pass_count, (long)counter/2);
		COMTHROW( progress->SetLine(0, PutInBstr(progress_msg)) );

		if( pass_count == 1 )
			max_counter = counter + 10000;

		COMTHROW( progress->SetProgress(counter, max_counter) );
	}

	if( skip_element_level > 0 )
	{
		ASSERT( ranges.front().begin != counter );
		++skip_element_level;
	}
	else if( ranges.front().begin <= counter && counter <= ranges.front().end )
	{
		if( ranges.front().begin == counter )
		{
			ASSERT( elements.empty() );
			elements.push_back(ranges.front().previous);
		}
		ASSERT( !elements.empty() );

		try
		{
			CGenParser::startElement(name, attributes);
		}
		catch(pass_exception &)
		{
			ASSERT( skip_element_level == 0 );

			ranges.push_back();
			ranges.back().begin = elements.back().begin;
			elements.pop_back();
			ranges.back().previous = elements.back();
			skip_element_level = 1;
		}
	}
}

void CMgaParser::endElement(const XMLCh* const name)
{
	ASSERT( !ranges.empty() );

	++counter;

	if( skip_element_level > 0 )
	{
		--skip_element_level;

		if( skip_element_level == 0 )
		{
			ranges.back().end = counter;
		}
	}
	else if( ranges.front().begin <= counter && counter <= ranges.front().end )
	{
		try
		{
			CGenParser::endElement(name);
		}
		catch(pass_exception &)
		{
			ASSERT( skip_element_level == 0 );

			ranges.push_back();
			ranges.back().begin = elements.back().begin;
			ranges.back().end = elements.back().end;
			elements.pop_back();
			ranges.back().previous = elements.back();
		}
	}

	if( ranges.front().end == counter )
	{
		ASSERT( elements.size() == 1 );

		elements.clear();
		ranges.pop_front();

		// no more ranges, skip everything
		if( ranges.empty() )
		{
			ranges.push_back();
			ranges.back().begin = (counter_type)-1;
			ranges.back().end = (counter_type)-1;
		}
	}
}

// ------- Lookup

void CMgaParser::LookupByID(const std::string &id, CComObjPtr<IMgaObject> &ret)
{
	ASSERT( project != NULL );

	ret.Release();

	id_lookup_iterator i = id_lookup.find(id);
	if( i != id_lookup.end() )
	{
		// we intentionally do not check the HRSULT
		project->GetObjectByID((*i).second, PutOut(ret));
	}
}

void CMgaParser::LookupByID(const std::string &id, CComObjPtr<IMgaFCO> &ret)
{
	ASSERT( project != NULL );

	ret.Release();

	id_lookup_iterator i = id_lookup.find(id);
	if( i != id_lookup.end() )
	{
		// we intentionally do not check the HRSULT
		project->GetFCOByID((*i).second, PutOut(ret));
	}
}

void CMgaParser::RegisterLookup(const std::string &id, IMgaObject *object)
{
	ASSERT( object != NULL );

	CComBstrObj &mgaid = id_lookup[id];
	ASSERT( mgaid.p == NULL );

	COMTHROW( object->get_ID(PutOut(mgaid)) );
}

void CMgaParser::RegisterLookup(const attributes_type &attributes, IMgaObject *object)
{
	bool perm_present = false; // currently the perm attribute appears only if the object is readonly
	attributes_iterator i = attributes.begin();
	attributes_iterator e = attributes.end();
	while( i != e )
	{
		if( (*i).first == "id" )
		{
			RegisterLookup((*i).second, object);
			//break;
		}
		else if( m_maintainGuids && (*i).first == "guid")
		{
				// when fco was created already got a fresh GUID, but we need to maintain
				// the old guid, thus we overwrite the old value with the parsed one
			object->PutGuidDisp( CComBSTR( (*i).second.c_str()));
		}
		else if( (*i).first == "perm" )
		{
			// the plain presence of the attribute indicates 'ro' flag
			// no need to parse the value: (*i).second
			perm_present = true;
		}

		++i;
	}
	
	readonly_stack.push_back( perm_present); // we insert a value anyway into the stack
}

CMgaParser::elementfunc CMgaParser::elementfuncs_mga[] = 
{
	elementfunc("project", StartProject, EndNone),
	elementfunc("name", StartNone, EndName),
	elementfunc("comment", StartNone, EndComment),
	elementfunc("author", StartNone, EndAuthor),
	elementfunc("value", StartNone, EndValue),
	elementfunc("folder", StartFolder, EndObject),
	elementfunc("model", StartModel, EndObject),
	elementfunc("atom", StartAtom, EndObject),
	elementfunc("regnode", StartRegNode, EndNone),
	elementfunc("attribute", StartAttribute, EndNone),
	elementfunc("connection", StartConnection, EndObject),
	elementfunc("connpoint", StartConnPoint, EndNone),
	elementfunc("constraint", StartNone, EndConstraint),
	elementfunc("reference", StartReference, EndObject),
	elementfunc("set", StartSet, EndObject),
	elementfunc("clipboard", StartClipboard, EndNone),
	elementfunc("", NULL, NULL)
};

// ------- Element Handlers

void CMgaParser::StartProject(const attributes_type &attributes)
{
	ASSERT( project != NULL );

	GetCurrent().object = project;

	// get metaproject
	CComObjPtr<IMgaMetaProject> metaproject;
	if( project) COMTHROW( project->get_RootMeta(PutOut(metaproject)) );
	ASSERT( metaproject != NULL );
	
	// obtain the current paradigm name
	CComBSTR host_pn;
	if( metaproject) COMTHROW( metaproject->get_Name( &host_pn));

	// is the resolver interactive?
	VARIANT_BOOL int_mode = VARIANT_FALSE;
	COMTHROW( resolver->get_IsInteractive( &int_mode));

	attributes_iterator i = attributes.begin();
	attributes_iterator e = attributes.end();
	while( i != e )
	{
		if( i->first == "guid" )
		{
			CComBstrObj bstr;
			CopyTo(i->second, bstr);

			GUID guid;
			CopyTo(bstr, guid);

			CopyTo(guid, projectguid);
		}
		else if( i->first == "metaname")
		{
			// if host paradigm != imported project's paradigm
			if( host_pn != CComBSTR( i->second.c_str()))
			{
				if( int_mode == VARIANT_TRUE) // if interactive
				{
					resolver->getUserOptions();
				}
			}
		}

		++i;
	}
}

void CMgaParser::StartClipboard(const attributes_type &attributes)
{
	ASSERT( project != NULL );
	ASSERT( GetPrevName() == "start" );
	ASSERT( GetPrevious().object != NULL );
	if( !GetPrevious().object) HR_THROW(E_XMLPARSER);//by ZolMol

	const CComObjPtr<IUnknown> &obj = GetPrevious().object;
	GetCurrent().object = obj;

	// get metaproject
	CComObjPtr<IMgaMetaProject> metaproject;
	if( project) COMTHROW( project->get_RootMeta(PutOut(metaproject)) );
	ASSERT( metaproject != NULL );
	
	// obtain the current paradigm name
	CComBSTR host_pn;
	if( metaproject) COMTHROW( metaproject->get_Name( &host_pn));

	// is the resolver interactive?
	VARIANT_BOOL int_mode = VARIANT_FALSE;
	COMTHROW( resolver->get_IsInteractive( &int_mode));

	CComObjPtr<IMgaModel> model;
	CComObjPtr<IMgaFolder> folder;

	if( SUCCEEDED(obj.QueryInterface(model)) )
		GetCurrent().name = "model";
	else if( SUCCEEDED(obj.QueryInterface(folder)) )
		GetCurrent().name = "folder";
	// Commented, thus allowing clipboard snippets to be 
	// dropped onto atoms/sets/references/connections too
	//else
	//	HR_THROW(E_INVALID_FILENAME);

	const std::string *parname_hint = GetByNameX(attributes, "paradigmnamehint");
	// importing from different paradigm
	if( parname_hint != NULL && host_pn != CComBSTR( parname_hint->c_str()))
	{
		if( int_mode == VARIANT_TRUE)
		{
			resolver->getUserOptions();
		}
	}
}

void CMgaParser::EndName()
{
	if( GetPrevName() == "project" )
	{
		COMTHROW( project->put_Name(PutInBstr(GetCurrData())) );
	}
	else if( GetPrevName() == "constraint" )
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

void CMgaParser::EndComment()
{
	if( GetPrevName() == "project" )
	{
		COMTHROW( project->put_Comment(PutInBstr(GetCurrData())) );
	}
	else
		HR_THROW(E_INVALID_DTD);
}

void CMgaParser::EndAuthor()
{
	if( GetPrevName() == "project" )
	{
		COMTHROW( project->put_Author(PutInBstr(GetCurrData())) );
	}
	else
		HR_THROW(E_INVALID_DTD);
}

void CMgaParser::EndValue()
{
	// skip if the object is ignored
	if( GetPrevious().object == NULL )
		return;

	if( GetPrevName() == "constraint" )
	{
		constraint_value = GetCurrData();
	}
	else if( GetPrevName() == "regnode" )
	{
		CComObjPtr<IMgaRegNode> regnode;
		GetPrevObj(regnode);

		long status;
		COMTHROW( regnode->get_Status(&status) );

		// when we create the registry node, 
		// we fill it by an empty string if not inherited or not undefined
		if( status == 0 )
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




void CMgaParser::preparerelid(const attributes_type &attributes) {
	const std::string & relidattr = GetByName(attributes, "relid");
	ASSERT(relid == -2);
	if(relidattr.size()) {
		relid = strtol(relidattr.c_str(),NULL, 0);
		if(!manual_relid_mode) {
			COMTHROW(project->put_Preferences(project_prefs | MGAPREF_MANUAL_RELIDS));
		}
		ASSERT(relid >= 0 && 
			   relid <= RELID_BASE_MAX && 
			   GetPrevious().exnuminfo >= relid);
	}	
	else {
		if(!manual_relid_mode) {
			COMTHROW(project->put_Preferences(project_prefs & ~MGAPREF_MANUAL_RELIDS));
		}
		relid = -1;
	}
}


void CMgaParser::assignrelid(IMgaObject *obj) {
	ASSERT(relid != -2);
	if(relid > 0) {
		COMTHROW(obj->put_RelID(relid));
	}
	relid = -2;
}

void CMgaParser::StartFolder(const attributes_type &attributes)
{
	CComObjPtr<IMgaFolder> folder;

	if( GetPrevName() == "project" )
	{
		COMTHROW( project->get_RootFolder(PutOut(folder)) );
	}
	else
	{
		CComObjPtr<IMgaFolder> prev;
		GetPrevObj(prev);

		CComObjPtr<IMgaMetaFolder> meta;
		CComBSTR fname( PutInBstrAttr(attributes, "kind"));
		const std::string &libn = GetByName(attributes,"libref");

		preparerelid(attributes);

		VARIANT_BOOL previactmode;
		COMTHROW(resolver->get_IsInteractive(&previactmode));
		COMTHROW(resolver->put_IsInteractive(VARIANT_FALSE));
		HRESULT hr = resolver->get_FolderByStr(prev, fname, PutOut(meta));
		COMTHROW(resolver->put_IsInteractive(previactmode));

		bool cheat = false;
		if(hr != S_OK && libn.size()) {
			CComPtr<IMgaMetaProject> mp;  // it is a library, maybe a rootfolder
			COMTHROW(project->get_RootMeta(&mp));
			COMTHROW(mp->get_RootFolder(PutOut(meta)));
			CComBSTR nn;
			COMTHROW(meta->get_Name(&nn));
			if(wcscmp(nn, fname)) {
				COMTHROW(hr);
			}
			COMTHROW(project->CheckSupress(VARIANT_TRUE));
			cheat = true;
		}
		ASSERT(meta);
	
		hr = prev->CreateFolder(meta, PutOut(folder));
		if(cheat) {
			if(folder) COMTHROW(folder->put_Exempt(VARIANT_TRUE));
			COMTHROW(project->CheckSupress(VARIANT_FALSE));
		}
		COMTHROW(hr);
		assignrelid(folder);
		if(libn.size()) {
			librecord lr;
			lr.f = folder;
			lr.libname = libn;
			libstodo.push_back(lr);
		}
	}
	ASSERT( folder != NULL );
	GetCurrent().object = folder;

	long crid = toLong(GetByName(attributes,"childrelidcntr"));
	GetCurrent().exnuminfo = crid;
	COMTHROW(folder->put_ChildRelIDCounter(crid));

	//RegisterReadOnlyStatus( attributes);
	RegisterLookup(attributes, folder);
}

void CMgaParser::ResolveDerivation(const attributes_type &attributes, deriv_type &deriv)
{
	const std::string *s = GetByNameX(attributes, "derivedfrom");
	if( s == NULL )
	{
		deriv.from.Release();
		return;
	}

	LookupByID(*s, deriv.from);
	if( deriv.from == NULL )
		throw pass_exception();

	s = GetByNameX(attributes, "isinstance");
	deriv.isinstance = ( s != NULL && *s == "yes" ) ? VARIANT_TRUE : VARIANT_FALSE;

	s = GetByNameX(attributes, "isprimary");
	deriv.isprimary = ( s != NULL && *s == "no" ) ? false : true;
}

void CMgaParser::StartModel(const attributes_type &attributes)
{
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
		}
		else
		{
			CComObjPtr<IMgaMetaFCO> meta;
			COMTHROW( resolver->get_KindByStr(prev, PutInBstrAttr(attributes, "kind"), 
				OBJTYPE_MODEL, PutOut(meta)) );
			ASSERT( meta != NULL );

			COMTHROW( prev->CreateRootObject(meta, PutOut(model)) );
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
		}
		else
		{
			preparerelid(attributes);
			COMTHROW( prev->CreateChildObject(role, PutOut(model)) );
			assignrelid(model);
		}
	}
	ASSERT( model != NULL );

	GetCurrent().object = model;
	long crid = toLong(GetByName(attributes,"childrelidcntr"));
	GetCurrent().exnuminfo = crid;
	COMTHROW(CComQIPtr<IMgaModel>(model)->put_ChildRelIDCounter(crid));

	//RegisterReadOnlyStatus( attributes);
	RegisterLookup(attributes, model);
}

void CMgaParser::StartAtom(const attributes_type &attributes)
{
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
		}
		else
		{
			CComObjPtr<IMgaMetaFCO> meta;
			COMTHROW( resolver->get_KindByStr(prev, PutInBstrAttr(attributes, "kind"),
				OBJTYPE_ATOM, PutOut(meta)) );
			ASSERT( meta != NULL );

			preparerelid(attributes);
			COMTHROW( prev->CreateRootObject(meta, PutOut(atom)) );
			assignrelid(atom);
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
		}
		else
		{
			preparerelid(attributes);
			COMTHROW( prev->CreateChildObject(role, PutOut(atom)) );
			assignrelid(atom);
		}
	}

	ASSERT( atom != NULL );
	GetCurrent().object = atom;

	//RegisterReadOnlyStatus( attributes);
	RegisterLookup(attributes, atom);
}

void CMgaParser::StartRegNode(const attributes_type &attributes)
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
	else if( GetPrevName()== "attribute" )
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

	if( GetByNameX(attributes, "status") == NULL )
		COMTHROW( regnode->put_Value(NULL) );

	if( GetByName(attributes, "isopaque") == "yes" )
		COMTHROW( regnode->put_Opacity(VARIANT_TRUE) );

	GetCurrent().object = regnode;
}

void CMgaParser::StartAttribute(const attributes_type &attributes)
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

	if( GetByNameX(attributes, "status") == NULL )
	{
		// we set some value, and from the "value" element we set the actual value

		CComVariant v;
		COMTHROW( attr->get_Value(PutOut(v)) );
		COMTHROW( attr->put_Value(v) );
	}
}

void CMgaParser::StartConnection(const attributes_type &attributes)
{
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
		}
		else
		{
			preparerelid(attributes);
			COMTHROW( prev->CreateChildObject(role, PutOut(conn)) );
			assignrelid(conn);
		}
	}
	ASSERT( conn != NULL );
	GetCurrent().object = conn;

	if( GetByName(attributes, "isbound") == "yes" ) GetCurrent().exstrinfo = "skip";

	//RegisterReadOnlyStatus( attributes);
	RegisterLookup(attributes, conn);
}

void CMgaParser::StartConnPoint(const attributes_type &attributes)
{
	ASSERT( GetPrevName() == "connection" );
	CComObjPtr<IMgaConnection> conn;
	GetPrevObj(conn);

	if( GetPrevious().exstrinfo == "skip" || GetByName(attributes, "isbound") == "yes" ) return;

	CComObjPtr<IMgaFCO> target;
	LookupByID(GetByName(attributes, "target"), target);
	if( target == NULL )
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

	const std::string& role = GetByName(attributes, "role");
	CComBSTR brole;
	CopyTo( role, &brole);

	// Since the Refresh operation created some derived connections
	// in its own way, some derived connections might have been
	// dumped with connroles, so that when the import happened
	// the number of connroles went up to 4 or 6 or ...
	// So to mitigate this issue the parser has been enhanced
	// to eliminate superfuous connroles in case of derived conns
	CComPtr<IMgaConnPoints> connpoints;
	COMTHROW( conn->get_ConnPoints( &connpoints));
	long c = 0;
	if( connpoints) COMTHROW( connpoints->get_Count( &c));
	for( long i = 1; i <= c; ++i)
	{
		CComPtr<IMgaConnPoint> old_cp;
		COMTHROW( connpoints->get_Item( i, &old_cp));
		if( old_cp)
		{
			CComBSTR old_role;
			COMTHROW( old_cp->get_ConnRole( &old_role));
			if( old_role == brole) // check if targets are equal
			{
				CComPtr<IMgaFCO> old_tgt;
				COMTHROW( old_cp->get_Target( &old_tgt));
				if( old_tgt == target)
				{
					// same role not inserted twice
					CComBSTR msg( "Warning: Superfluous connection role ignored!");
					if( m_GME) COMTHROW( m_GME->ConsoleMessage( msg, MSG_WARNING));
					return;
				}
			}
		}
	}

	COMTHROW( conn->AddConnPoint(PutInBstr(GetByName(attributes, "role")), 0,	// FIXME: multiplicity
		target, coll, PutOut(connpoint)) );
}

void CMgaParser::EndConstraint()
{
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

void CMgaParser::StartReference(const attributes_type &attributes)
{
	CComObjPtr<IMgaFCO> fco;

	deriv_type deriv;
	//ResolveDerivation(attributes, deriv);
	(*this.*m_resolveDerFuncPtr)(attributes, deriv);

	CComObjPtr<IMgaFCO> referred;

	const std::string *s = GetByNameX(attributes, "referred");
	if( s != NULL )
	{
		LookupByID(*s, referred);

		if( referred == NULL )
			throw pass_exception();
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

	//RegisterReadOnlyStatus( attributes);
	RegisterLookup(attributes, fco);
}

void CMgaParser::StartSet(const attributes_type &attributes)
{
	CComObjPtr<IMgaFCO> fco;

	deriv_type deriv;
	//ResolveDerivation(attributes, deriv);
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

	//RegisterReadOnlyStatus( attributes);
	RegisterLookup(attributes, fco);
}

// ------- ElementFuncs -- info

CMgaParser::elementfunc CMgaParser::elementfuncs_mgainfo[] = 
{
	elementfunc("project", StartProjectInfo, EndNone),
	elementfunc("name", StartNone, EndNameInfo),
	elementfunc("", NULL, NULL)
};


void CMgaParser::StartProjectInfo(const attributes_type &attributes)
{

	attributes_iterator i = attributes.begin();
	attributes_iterator e = attributes.end();
	while( i != e )
	{
		if( i->first == "metaguid" )
		{
			CComBstrObj bstr;
			CopyTo(i->second, bstr);

			GUID guid;
			CopyTo(bstr, guid);

			CComVariant v;
			CopyTo(guid, v);

			v.Detach(infoparguid);

		}

		if( i->first == "metaname" )
		{
			CComBstrObj bstr;
			CopyTo(i->second, bstr);

			*infoparname = bstr.Detach();

		}

		if( i->first == "metaversion" )
		{
			CComBstrObj bstr;
			CopyTo(i->second, bstr);

			*infoparversion = bstr.Detach();

		}

		if( i->first == "version" )
		{
			CComBstrObj bstr;
			CopyTo(i->second, bstr);

			*infoversion = bstr.Detach();

		}


		++i;
	}
}

void CMgaParser::EndNameInfo()
{
	if( GetPrevName() == "project" )
	{
		CComBstrObj nn = PutInBstr(GetCurrData());
		*infoprojname = nn.Detach();
		// analysis done, why waste time by processing further the xme file?
		throw SAXException( magic_exit_str); // trick used & handled only by GetXMLInfo()
	}
}

CMgaParser::elementfunc CMgaParser::elementfuncs_clipmgainfo[] = 
{
	elementfunc("clipboard", StartClipboardInfo, EndNone),
	elementfunc("", NULL, NULL)
};

void CMgaParser::StartClipboardInfo(const attributes_type &attributes)
{
	bool closure_version_found = false;
	*closversion = 0;
	*closacckind = 0;
	attributes_iterator i = attributes.begin();
	attributes_iterator e = attributes.end();
	while( i != e )
	{
		if( i->first == "closureversion" )
		{
			closure_version_found = true;
			CComBstrObj bstr;
			CopyTo(i->second, bstr); // if the value is "" then the bstr will be null, so bool introduced to correctly check the presence of "closureversion" token

			*closversion = bstr.Detach();
		}
		else if( i->first == "acceptingkind" )
		{
			CComBstrObj bstr;
			CopyTo(i->second, bstr);

			*closacckind = bstr.Detach();
		}
		++i;
	}
	if( !closure_version_found && *closversion == 0) // not found such token
	{
		CComBSTR bstr("0");
		*closversion = bstr.Detach();
	}
}

STDMETHODIMP CMgaParser::GetClipXMLInfo(BSTR filename, IMgaObject *target, VARIANT_BOOL *is_acceptable, BSTR* p_acckind, BSTR* p_version) 
{
	try
	{
		CloseAll();
		COMTHROW( progress.CoCreateInstance(L"Mga.MgaProgressDlg") );
		COMTHROW( progress->SetTitle(PutInBstr("Analyzing clipboard data...")) );
		COMTHROW( progress->StartProgressDialog(NULL) );


		CopyTo(filename, xmlfile);

		try
		{
			XMLPlatformUtils::Initialize();

			SAXParser parser;
			parser.setDoValidation(false);
			parser.setDocumentHandler(this);
			parser.setErrorHandler(this);
			parser.setEntityResolver(this);

			elementfuncs = elementfuncs_clipmgainfo;

			pass_count = 1;

			ranges.clear();
			ranges.push_front();
			ranges.front().begin = 1;
			ranges.front().end = (counter_type)-1;
			skip_element_level = 0;

			closversion = p_version; // the result stored in these returning parameters p_...
			closacckind = p_acckind;

			parser.parse(xmlfile.c_str());

		}
		catch(const XMLException &e)
		{
			XmlStr desc(e.getMessage());

			ThrowXmlError(desc.c_str());
		}

		CloseAll();
	}
	catch(hresult_exception &e)
	{
		CloseAll();

		ASSERT( FAILED(e.hr) );
		if( e.hr == E_XMLPARSER )
			SetErrorInfo(errorinfo);
		else
			SetErrorInfo2(e.hr);

		return e.hr;
	}

	return S_OK;
}

//void CMgaParser::RegisterReadOnlyStatus( const attributes_type &attributes)
//{
//	readonly_stack.push_back( GetByNameX( attributes, "perm") != 0);
//}

bool CMgaParser::GetIntendedReadOnlyFlag( bool *p_isReadOnly)
{
	ASSERT( !readonly_stack.empty());
	if( readonly_stack.empty()) return false;

	ASSERT( p_isReadOnly);
	*p_isReadOnly = readonly_stack.back();
	readonly_stack.pop_back();

	return true;
}

void CMgaParser::EndObject()
{
	bool ro = false; // should be made read only?
	bool re = GetIntendedReadOnlyFlag( &ro); // re: is stack ok?
	if( ro && re)
	{
		CComQIPtr<IMgaObject> obj( GetCurrent().object);
		ASSERT( obj);
		if( obj) COMTHROW( obj->PutReadOnlyAccess( VARIANT_TRUE));
	} // else if( re) stack error
}
