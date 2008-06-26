
#include "stdafx.h"
#include "Parser.h"
#include "MetaParser.h"
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/SAXParser.hpp>

#include <stdio.h>
#include <fstream>//fstream.h
// --------------------------- CMetaParser

CMetaParser::CMetaParser():currentPass(FIRST_PASS)
{
}

CMetaParser::~CMetaParser()
{
}

// ------- Methods

STDMETHODIMP CMetaParser::Parse(BSTR filename, BSTR connection)
{
	try
	{
		CloseAll();

		ASSERT( metaproject == NULL );
		COMTHROW( metaproject.CoCreateInstance(L"Mga.MgaMetaProject") );

		COMTHROW( metaproject->Create(connection) );
		COMTHROW( metaproject->BeginTransaction() );

		CopyTo(filename, xmlfile);


		try
		{
			XMLPlatformUtils::Initialize();

			foundconstraints = false;
			explicitguid = false;
			{
				SAXParser parser;
				parser.setDoValidation(true);
				parser.setDocumentHandler(this);
				parser.setErrorHandler(this);
				parser.setEntityResolver(this);

				
				//elementfuncs = elementfuncs_firstpass;
				currentPass = FIRST_PASS;
				parser.parse(xmlfile.c_str());
			}

			{
				SAXParser parser;
				parser.setDoValidation(false);
				parser.setDocumentHandler(this);
				parser.setErrorHandler(this);
				parser.setEntityResolver(this);

				
				//elementfuncs = elementfuncs_secondpass;
				currentPass = SECOND_PASS;
				parser.parse(xmlfile.c_str());
			}
			if (!explicitguid) {
				// Old pradigm guid logic
//calculate checksum:
				int sum = 0, cyc = 0;
				std::ifstream inf(xmlfile.c_str());
				while(inf.good()) {
					int l = inf.get();
					if(inf.eof()) break;
					sum += l << cyc;
					cyc = (cyc + 1) % 20;
				}
				sum += 1;    // compensate for meta bug in registering MetaID-s (January 2002)
//
				OLECHAR buf[40];
				swprintf(buf, 40, L"{%08X-DEAD-BEEF-FEED-DAD00000000%c}",sum, foundconstraints?'1':'0');
				CComBstrObj bstr(buf);
				
				GUID guid;
				CopyTo(bstr, guid);
	
				CComVariant v;
				CopyTo(guid, v);
				
	
				COMTHROW( metaproject->put_GUID(v) );
			}
		}
	    catch(const XMLException &e)
		{
			XmlStr desc(e.getMessage());

			ThrowXmlError(desc.c_str());
		}

		COMTHROW( metaproject->CommitTransaction() );

		CloseAll();
	}
	catch(hresult_exception &e)
	{
		if( metaproject != NULL )
			metaproject->AbortTransaction();

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

void CMetaParser::CloseAll()
{
	elements.clear();

	if( metaproject != NULL )
		metaproject->Close();

	metaproject = NULL;
};

// ------- Attributes

const std::string CMetaParser::GetNextToken(std::string::const_iterator &i,
	std::string::const_iterator &e, std::string::const_iterator end)
{
	i = e;
	while( i != end && *i == ' ' )
		++i;

	e = i;
	while( e != end && *e != ' ' )
		++e;

	return std::string(i, e);
}


void CMetaParser::fireStartFunction(const std::string & namestr, const attributes_type& attributes)
{
	if(currentPass == FIRST_PASS)
	{
		for(unsigned int index = 0; !elementfuncs_firstpass[index].name.empty(); index++)
		{
				if( namestr == elementfuncs_firstpass[index].name )
				{
					elementfuncs_firstpass[index].Start(this, attributes);
					break;
				}
		}
	}
	else
	{
		for(unsigned int index = 0; !elementfuncs_secondpass[index].name.empty(); index++)
		{
				if( namestr == elementfuncs_secondpass[index].name )
				{
					elementfuncs_secondpass[index].Start(this, attributes);
					break;
				}
		}

	}
}


void CMetaParser::fireEndFunction(const std::string & namestr)
{
	if(currentPass == FIRST_PASS)
	{
		for(unsigned int index = 0; !elementfuncs_firstpass[index].name.empty(); index++)
		{
				if( namestr == elementfuncs_firstpass[index].name )
				{
					elementfuncs_firstpass[index].End(this);
					break;
				}
		}
	}
	else
	{
		for(unsigned int index = 0; !elementfuncs_secondpass[index].name.empty(); index++)
		{
				if( namestr == elementfuncs_secondpass[index].name )
				{
					elementfuncs_secondpass[index].End(this);
					break;
				}
		}

	}
}


// ------- ElementFuncs

CMetaParser::elementfunc CMetaParser::elementfuncs_firstpass[] = 
{
	elementfunc("paradigm", StartParadigm, EndNone),
	elementfunc("comment", StartNone, EndComment),
	elementfunc("author", StartNone, EndAuthor),
	elementfunc("dispname", StartNone, EndDispName),
	elementfunc("folder", StartFolder, EndNone),
	elementfunc("atom", StartAtom, EndNone),
	elementfunc("model", StartModel, EndNone),
	elementfunc("connection", StartConnection, EndNone),
	elementfunc("reference", StartReference, EndNone),
	elementfunc("set", StartSet, EndNone),
	elementfunc("attrdef", StartAttrDef, EndNone),
	elementfunc("regnode", StartRegNode, EndNone),
	elementfunc("connjoint", StartConnJoint, EndNone),
	elementfunc("pointerspec", StartPointerSpec, EndNone),
	elementfunc("pointeritem", StartPointerItem, EndNone),
	elementfunc("enumitem", StartEnumItem, EndNone),
	elementfunc("constraint", StartConstraint, EndConstraint),
	elementfunc("", NULL, NULL)
};

CMetaParser::elementfunc CMetaParser::elementfuncs_secondpass[] = 
{
	elementfunc("folder", StartFolder2, EndNone),
	elementfunc("model", StartFCO2, EndNone),
	elementfunc("atom", StartFCO2, EndNone),
	elementfunc("connection", StartFCO2, EndNone),
	elementfunc("reference", StartFCO2, EndNone),
	elementfunc("set", StartFCO2, EndNone),
	elementfunc("role", StartRole2, EndNone),
	elementfunc("aspect", StartAspect2, EndNone),
	elementfunc("part", StartPart2, EndNone),
	elementfunc("regnode", StartRegNode, EndNone),
	elementfunc("dispname", StartNone, EndDispName),
	elementfunc("", NULL, NULL)
};

// ------- Element Handlers

void CMetaParser::StartParadigm(const attributes_type &attributes)
{
	GetCurrent().object = metaproject;

	attributes_iterator i = attributes.begin();
	attributes_iterator e = attributes.end();
	while( i != e )
	{
		Attr(i, "name", metaproject, &IMgaMetaProject::put_Name);
		Attr(i, "version", metaproject, &IMgaMetaProject::put_Version);
		
		/*  New Paradigm GUID logic */	
		if( i->first == "guid" )
		{
			CComBstrObj bstr;
			CopyTo(i->second, bstr);

			GUID guid;
			CopyTo(bstr, guid);

			CComVariant v;
			CopyTo(guid, v);

			COMTHROW( metaproject->put_GUID(v) );
			explicitguid = true;
		}

		Attr(i, "cdate", metaproject, &IMgaMetaProject::put_CreatedAt);
		Attr(i, "mdate", metaproject, &IMgaMetaProject::put_ModifiedAt);

		++i;
	}
}

void CMetaParser::EndComment()
{
	if( GetPrevName() == "paradigm" )
	{
		COMTHROW( metaproject->put_Comment(PutInBstr(GetCurrData())) );
	}
	else
		HR_THROW(E_INVALID_DTD);
}

void CMetaParser::EndAuthor()
{
	if( GetPrevName() == "paradigm" )
	{
		COMTHROW( metaproject->put_Author(PutInBstr(GetCurrData())) );
	}
	else
		HR_THROW(E_INVALID_DTD);
}

void CMetaParser::EndDispName()
{
	if( GetPrevious().object == NULL )
		return;

	if( GetPrevName() == "paradigm" )
	{
		COMTHROW( metaproject->put_DisplayedName(PutInBstr(GetCurrData())) );
	}
	else if( GetPrevName() == "constraint" )
	{
		CComObjPtr<IMgaMetaConstraint> c;
		GetPrevObj(c);
		COMTHROW( c->put_DisplayedName(PutInBstr(GetCurrData())) );
	}
	else if( GetPrevious().object != NULL ) 
	{
		CComObjPtr<IMgaMetaBase> prev;
		GetPrevObj(prev);
		COMTHROW( prev->put_DisplayedName(PutInBstr(GetCurrData())) );
	}
}

void CMetaParser::StartFolder(const attributes_type &attributes)
{
	CComObjPtr<IMgaMetaFolder> folder;

	if( GetPrevName() == "paradigm" )
	{
		COMTHROW( metaproject->get_RootFolder(PutOut(folder)) );
	}
	else
	{
		CComObjPtr<IMgaMetaFolder> prev;
		GetPrevObj(prev);
		COMTHROW( prev->DefineFolder(PutOut(folder)) );
	}

	ASSERT( folder != NULL );
	GetCurrent().object = folder;

	attributes_iterator i = attributes.begin();
	attributes_iterator e = attributes.end();
	while( i != e )
	{
		Attr(i, "name", folder, &IMgaMetaFolder::put_Name);
		Attr(i, "metaref", folder, &IMgaMetaFolder::put_MetaRef);

		++i;
	}
}

void CMetaParser::StartFolder2(const attributes_type &attributes)
{
	ASSERT( GetCurrent().object == NULL );

	CComObjPtr<IMgaMetaFolder> folder;

	if( GetPrevName() == "paradigm" )
	{
		ASSERT( metaproject != NULL );
		COMTHROW( metaproject->get_RootFolder(PutOut(folder)) );
	}
	else
	{
		CComObjPtr<IMgaMetaFolder> prev;
		GetPrevObj(prev);

		HRESULT hr = prev->get_DefinedFolderByName(PutInBstr(GetByName(attributes, "name")),
			VARIANT_FALSE, PutOut(folder));

		if( hr == E_NOTFOUND )
			ThrowXmlError("Parent folder %s was not found", GetByName(attributes, "name").c_str());
		else
			COMTHROW(hr);
	}

	ASSERT( folder != NULL );
	GetCurrent().object = folder;

	attributes_iterator i = attributes.begin();
	attributes_iterator e = attributes.end();
	while( i != e )
	{
		if( i->first == "subfolders" )
		{
			std::string::const_iterator ip = i->second.begin();
			std::string::const_iterator ep = ip;
			std::string::const_iterator xp = i->second.end();
			for(;;)
			{
				std::string token = GetNextToken(ip, ep, xp);
				if( ip == xp )
					break;

				ASSERT( !token.empty() );

				CComObjPtr<IMgaMetaFolder> child;
				HRESULT hr = folder->get_DefinedFolderByName(PutInBstr(token),
					VARIANT_TRUE, PutOut(child));

				if( hr == E_NOTFOUND )
					ThrowXmlError("Defined folder %s was not found", token.c_str());
				else
					COMTHROW(hr);

				COMTHROW( folder->AddLegalChildFolder(child) );
			}
		}
		else if( i->first == "rootobjects" )
		{
			std::string::const_iterator ip = i->second.begin();
			std::string::const_iterator ep = ip;
			std::string::const_iterator xp = i->second.end();
			for(;;)
			{
				std::string token = GetNextToken(ip, ep, xp);
				if( ip == xp )
					break;

				ASSERT( !token.empty() );

				CComObjPtr<IMgaMetaFCO> fco;
				HRESULT hr = folder->get_DefinedFCOByName(PutInBstr(token),
					VARIANT_TRUE, PutOut(fco));

				if( hr == E_NOTFOUND )
					ThrowXmlError("No definition for FCO %s was not found", token.c_str());
				else
					COMTHROW(hr);

				COMTHROW( folder->AddLegalRootObject(fco) );
			}
		}

		++i;
	}

}

void CMetaParser::StartAtom(const attributes_type &attributes)
{
	CComObjPtr<IMgaMetaAtom> atom;

	if( GetPrevName() == "folder" )
	{
		CComObjPtr<IMgaMetaFolder> prev;
		GetPrevObj(prev);
		COMTHROW( prev->DefineAtom(PutOut(atom)) );
	}
	else
	{
		CComObjPtr<IMgaMetaModel> prev;
		GetPrevObj(prev);
		COMTHROW( prev->DefineAtom(PutOut(atom)) );
	}

	ASSERT( atom != NULL );
	GetCurrent().object = atom;

	attributes_iterator i = attributes.begin();
	attributes_iterator e = attributes.end();
	while( i != e )
	{
		Attr(i, "name", atom, &IMgaMetaAtom::put_Name);
		Attr(i, "metaref", atom, &IMgaMetaAtom::put_MetaRef);
		++i;
	}
	COMTHROW(atom->put_AliasingEnabled((GetByName(attributes, "aliasenabled") == "yes" ) ? VARIANT_TRUE : VARIANT_FALSE));
}

void CMetaParser::StartConnection(const attributes_type &attributes)
{
	CComObjPtr<IMgaMetaConnection> conn;

	if( GetPrevName() == "folder" )
	{
		CComObjPtr<IMgaMetaFolder> prev;
		GetPrevObj(prev);
		COMTHROW( prev->DefineConnection(PutOut(conn)) );
	}
	else
	{
		CComObjPtr<IMgaMetaModel> prev;
		GetPrevObj(prev);
		COMTHROW( prev->DefineConnection(PutOut(conn)) );
	}

	ASSERT( conn != NULL );
	GetCurrent().object = conn;

	attributes_iterator i = attributes.begin();
	attributes_iterator e = attributes.end();
	while( i != e )
	{
		Attr(i, "name", conn, &IMgaMetaConnection::put_Name);
		Attr(i, "metaref", conn, &IMgaMetaConnection::put_MetaRef);
		++i;
	}
	COMTHROW(conn->put_AliasingEnabled((GetByName(attributes, "aliasenabled") == "yes" ) ? VARIANT_TRUE : VARIANT_FALSE));
}

void CMetaParser::StartConnJoint(const attributes_type &attributes)
{
	CComObjPtr<IMgaMetaConnJoint> joint;

	CComObjPtr<IMgaMetaConnection> prev;
	GetPrevObj(prev);
	COMTHROW( prev->CreateJoint(PutOut(joint)) );

	ASSERT( joint != NULL );
	GetCurrent().object = joint;
}

void CMetaParser::StartPointerSpec(const attributes_type &attributes)
{
	CComObjPtr<IMgaMetaPointerSpec> spec;

	if( GetPrevName() == "connjoint" )
	{
		CComObjPtr<IMgaMetaConnJoint> prev;
		GetPrevObj(prev);
		COMTHROW( prev->CreatePointerSpec(PutOut(spec)) );
	}
	else if( GetPrevName() == "reference" )
	{
		CComObjPtr<IMgaMetaReference> prev;
		GetPrevObj(prev);
		COMTHROW( prev->get_RefSpec(PutOut(spec)) );
	}
	else
	{
		ASSERT( GetPrevName() == "set" );

		CComObjPtr<IMgaMetaSet> prev;
		GetPrevObj(prev);
		COMTHROW( prev->get_MemberSpec(PutOut(spec)) );
	}

	ASSERT( spec != NULL );
	GetCurrent().object = spec;

	attributes_iterator i = attributes.begin();
	attributes_iterator e = attributes.end();
	while( i != e )
	{
		if( i->first == "name" )
			COMTHROW( spec->put_Name(PutInBstr(i->second)) );

		++i;
	}
}

void CMetaParser::StartPointerItem(const attributes_type &attributes)
{
	CComObjPtr<IMgaMetaPointerItem> item;

	CComObjPtr<IMgaMetaPointerSpec> prev;
	GetPrevObj(prev);
	COMTHROW( prev->CreateItem(PutOut(item)) );

	attributes_iterator i = attributes.begin();
	attributes_iterator e = attributes.end();
	while( i != e )
	{
		Attr(i, "desc", item, &IMgaMetaPointerItem::put_Desc);

		++i;
	}
}

void CMetaParser::StartReference(const attributes_type &attributes)
{
	CComObjPtr<IMgaMetaReference> reference;

	if( GetPrevName() == "folder" )
	{
		CComObjPtr<IMgaMetaFolder> prev;
		GetPrevObj(prev);
		COMTHROW( prev->DefineReference(PutOut(reference)) );
	}
	else
	{
		CComObjPtr<IMgaMetaModel> prev;
		GetPrevObj(prev);
		COMTHROW( prev->DefineReference(PutOut(reference)) );
	}

	ASSERT( reference != NULL );
	GetCurrent().object = reference;

	attributes_iterator i = attributes.begin();
	attributes_iterator e = attributes.end();
	while( i != e )
	{
		Attr(i, "name", reference, &IMgaMetaReference::put_Name);
		Attr(i, "metaref", reference, &IMgaMetaReference::put_MetaRef);
		++i;
	}
	COMTHROW(reference->put_AliasingEnabled((GetByName(attributes, "aliasenabled") == "yes" ) ? VARIANT_TRUE : VARIANT_FALSE));
}

void CMetaParser::StartSet(const attributes_type &attributes)
{
	CComObjPtr<IMgaMetaSet> set;

	if( GetPrevName() == "folder" )
	{
		CComObjPtr<IMgaMetaFolder> prev;
		GetPrevObj(prev);
		COMTHROW( prev->DefineSet(PutOut(set)) );
	}
	else
	{
		CComObjPtr<IMgaMetaModel> prev;
		GetPrevObj(prev);
		COMTHROW( prev->DefineSet(PutOut(set)) );
	}

	ASSERT( set != NULL );
	GetCurrent().object = set;

	attributes_iterator i = attributes.begin();
	attributes_iterator e = attributes.end();
	while( i != e )
	{
		Attr(i, "name", set, &IMgaMetaSet::put_Name);
		Attr(i, "metaref", set, &IMgaMetaSet::put_MetaRef);

		++i;
	}
	COMTHROW(set->put_AliasingEnabled((GetByName(attributes, "aliasenabled") == "yes" ) ? VARIANT_TRUE : VARIANT_FALSE));
}

void CMetaParser::StartModel(const attributes_type &attributes)
{
	CComObjPtr<IMgaMetaModel> model;

	if( GetPrevName() == "folder" )
	{
		CComObjPtr<IMgaMetaFolder> prev;
		GetPrevObj(prev);
		COMTHROW( prev->DefineModel(PutOut(model)) );
	}
	else
	{
		CComObjPtr<IMgaMetaModel> prev;
		GetPrevObj(prev);
		COMTHROW( prev->DefineModel(PutOut(model)) );
	}

	ASSERT( model != NULL );
	GetCurrent().object = model;

	attributes_iterator i = attributes.begin();
	attributes_iterator e = attributes.end();
	while( i != e )
	{
		Attr(i, "name", model, &IMgaMetaModel::put_Name);
		Attr(i, "metaref", model, &IMgaMetaModel::put_MetaRef);

		++i;
	}
	COMTHROW(model->put_AliasingEnabled((GetByName(attributes, "aliasenabled") == "yes" ) ? VARIANT_TRUE : VARIANT_FALSE));
}

void CMetaParser::StartFCO2(const attributes_type &attributes)
{
	ASSERT( GetCurrent().object == NULL );

	CComObjPtr<IMgaMetaFCO> fco;
	HRESULT hr;

	if( GetPrevName() == "folder" )
	{
		CComObjPtr<IMgaMetaFolder> prev;
		GetPrevObj(prev);
		hr = prev->get_DefinedFCOByName(PutInBstr(GetByName(attributes, "name")),
			VARIANT_FALSE, PutOut(fco));
	}
	else
	{
		CComObjPtr<IMgaMetaModel> prev;
		GetPrevObj(prev);
		hr = prev->get_DefinedFCOByName(PutInBstr(GetByName(attributes, "name")),
			VARIANT_FALSE, PutOut(fco));
	}

	if( hr == E_NOTFOUND )
		ThrowXmlError("Parent FCO %s was not found", GetByName(attributes, "name").c_str());
	else
		COMTHROW(hr);

	ASSERT( fco != NULL );
	GetCurrent().object = fco;

	attributes_iterator i = attributes.begin();
	attributes_iterator e = attributes.end();
	while( i != e )
	{
		if( i->first == "attributes" )
		{
			std::string::const_iterator ip = i->second.begin();
			std::string::const_iterator ep = ip;
			std::string::const_iterator xp = i->second.end();
			for(;;)
			{
				std::string token = GetNextToken(ip, ep, xp);
				if( ip == xp )
					break;

				ASSERT( !token.empty() );

				CComObjPtr<IMgaMetaAttribute> attr;
				HRESULT hr = fco->get_DefinedAttributeByName(PutInBstr(token),
					VARIANT_TRUE, PutOut(attr));

				if( hr == E_NOTFOUND )
					ThrowXmlError("Defined attribute %s was not found", token.c_str());
				else
					COMTHROW(hr);

				COMTHROW( fco->AddAttribute(attr) );
			}
		}

		++i;
	}
}

void CMetaParser::StartAttrDef(const attributes_type &attributes)
{
	CComObjPtr<IMgaMetaAttribute> attr;

	if( GetPrevName() == "folder" )
	{
		CComObjPtr<IMgaMetaFolder> prev;
		GetPrevObj(prev);
		COMTHROW( prev->DefineAttribute(PutOut(attr)) );
	}
	else
	{
		CComObjPtr<IMgaMetaFCO> prev;
		GetPrevObj(prev);
		COMTHROW( prev->DefineAttribute(PutOut(attr)) );
	}

	ASSERT( attr != NULL );
	GetCurrent().object = attr;
	
	attr->put_Viewable( VARIANT_TRUE); // default behaviour if no 'viewable' attribute is found

	attributes_iterator i = attributes.begin();
	attributes_iterator e = attributes.end();
	while( i != e )
	{
		Attr(i, "name", attr, &IMgaMetaAttribute::put_Name);
		Attr(i, "defvalue", attr, &IMgaMetaAttribute::put_DefaultValue);
		Attr(i, "metaref", attr, &IMgaMetaAttribute::put_MetaRef);

		if( i->first == "valuetype" )
		{
			attval_enum attval;

			if( i->second == "integer" )
				attval = ATTVAL_INTEGER;
			else if( i->second == "double" )
				attval = ATTVAL_DOUBLE;
			else if( i->second == "boolean" )
				attval = ATTVAL_BOOLEAN;
			else if( i->second == "string" )
				attval = ATTVAL_STRING;
			else if( i->second == "enum" )
				attval = ATTVAL_ENUM;
			else if( i->second == "dynamic" )
				attval = ATTVAL_DYNAMIC;
			else
				HR_THROW(E_XMLPARSER);

			COMTHROW( attr->put_ValueType(attval) );
		}

		if( i->first == "viewable" && i->second == "no")
			attr->put_Viewable( VARIANT_FALSE);

		++i;
	}
}

void CMetaParser::StartEnumItem(const attributes_type &attributes)
{
	CComObjPtr<IMgaMetaEnumItem> item;

	CComObjPtr<IMgaMetaAttribute> prev;
	GetPrevObj(prev);
	COMTHROW( prev->CreateEnumItem(PutOut(item)) );

	attributes_iterator i = attributes.begin();
	attributes_iterator e = attributes.end();
	while( i != e )
	{
		Attr(i, "dispname", item, &IMgaMetaEnumItem::put_DisplayedName);
		Attr(i, "value", item, &IMgaMetaEnumItem::put_Value);

		++i;
	}
}

void CMetaParser::StartRole2(const attributes_type &attributes)
{
	CComObjPtr<IMgaMetaModel> prev;
	GetPrevObj(prev);

	CComObjPtr<IMgaMetaFCO> fco;
	HRESULT hr = prev->get_DefinedFCOByName(PutInBstr(GetByName(attributes, "kind")),
		VARIANT_TRUE, PutOut(fco));

	if( hr == E_NOTFOUND )
		ThrowXmlError("Kind FCO %s was not found", GetByName(attributes, "kind").c_str());
	else
		COMTHROW(hr);

	ASSERT( fco != NULL );

	CComObjPtr<IMgaMetaRole> role;
	COMTHROW( prev->CreateRole(fco, PutOut(role)) );

	ASSERT( role != NULL );
	GetCurrent().object = role;

	attributes_iterator i = attributes.begin();
	attributes_iterator e = attributes.end();
	while( i != e )
	{
		Attr(i, "name", role, &IMgaMetaRole::put_Name);
		Attr(i, "metaref", role, &IMgaMetaRole::put_MetaRef);

		++i;
	}
}

void CMetaParser::StartAspect2(const attributes_type &attributes)
{
	CComObjPtr<IMgaMetaAspect> aspect;

	CComObjPtr<IMgaMetaModel> prev;
	GetPrevObj(prev);
	COMTHROW( prev->CreateAspect(PutOut(aspect)) );

	CComObjPtr<IMgaMetaModel> model;
	COMTHROW( prev.QueryInterface(model) );

	ASSERT( aspect != NULL );
	GetCurrent().object = aspect;

	attributes_iterator i = attributes.begin();
	attributes_iterator e = attributes.end();
	while( i != e )
	{
		Attr(i, "name", aspect, &IMgaMetaAspect::put_Name);
		Attr(i, "metaref", aspect, &IMgaMetaAspect::put_MetaRef);

		if( i->first == "attributes" )
		{
			std::string::const_iterator ip = i->second.begin();
			std::string::const_iterator ep = ip;
			std::string::const_iterator xp = i->second.end();
			for(;;)
			{
				std::string token = GetNextToken(ip, ep, xp);
				if( ip == xp )
					break;

				ASSERT( !token.empty() );

				CComObjPtr<IMgaMetaAttribute> attr;
				HRESULT hr = model->get_AttributeByName(PutInBstr(token), PutOut(attr));

				if( hr == E_NOTFOUND )
					ThrowXmlError("Attribute %s was not found", token.c_str());
				else
					COMTHROW(hr);

				COMTHROW( aspect->AddAttribute(attr) );
			}
		}
	
		++i;
	}
}

void CMetaParser::StartPart2(const attributes_type &attributes)
{
	CComObjPtr<IMgaMetaPart> part;

	CComObjPtr<IMgaMetaAspect> prev;
	GetPrevObj(prev);

	ASSERT( elements.size() >= 3 );
	ASSERT( elements[elements.size()-3].name == "model" );

	CComObjPtr<IMgaMetaModel> model;
	COMTHROW( elements[elements.size()-3].object.QueryInterface(model) );
	ASSERT( model != NULL );

	CComObjPtr<IMgaMetaRole> role;
	HRESULT hr = model->get_RoleByName(PutInBstr(GetByName(attributes, "role")), PutOut(role));

	if( hr == E_NOTFOUND )
		ThrowXmlError("Role %s was not found", GetByName(attributes, "role").c_str());
	else
		COMTHROW(hr);

	ASSERT( role != NULL );

	COMTHROW( prev->CreatePart(role, PutOut(part)) );
	ASSERT( part != NULL );

	attributes_iterator i = attributes.begin();
	attributes_iterator e = attributes.end();
	while( i != e )
	{
		Attr(i, "kindaspect", part, &IMgaMetaPart::put_KindAspect);
		Attr(i, "metaref", part, &IMgaMetaPart::put_MetaRef);

		if( i->first == "primary" )
		{
			COMTHROW( part->put_IsPrimary(i->second == "yes" ? VARIANT_TRUE : VARIANT_FALSE) );
		}
		else if( i->first == "linked" )
		{
			COMTHROW( part->put_IsLinked(i->second == "yes" ? VARIANT_TRUE : VARIANT_FALSE) );
		}

		++i;
	}

}

void CMetaParser::StartRegNode(const attributes_type &attributes)
{
	if( GetPrevious().object == NULL )
		return;

	CComObjPtr<IMgaMetaRegNode> regnode;

	const std::string &name = GetByName(attributes, "name");

	if( GetPrevName() == "part" )
	{
		CComObjPtr<IMgaMetaPart> prev;
		GetPrevObj(prev);
		COMTHROW( prev->get_RegistryNode(PutInBstr(name), PutOut(regnode)) );
	}
	else if( GetPrevName() == "regnode" )
	{
		CComObjPtr<IMgaMetaRegNode> prev;
		GetPrevObj(prev);
		COMTHROW( prev->get_RegistryNode(PutInBstr(name), PutOut(regnode)) );
	}
	else
	{
		CComObjPtr<IMgaMetaBase> prev;
		GetPrevObj(prev);
		COMTHROW( prev->get_RegistryNode(PutInBstr(name), PutOut(regnode)) );
	}

	ASSERT( regnode != NULL );
	GetCurrent().object = regnode;

	attributes_iterator i = attributes.begin();
	attributes_iterator e = attributes.end();
	while( i != e )
	{
		Attr(i, "value", regnode, &IMgaMetaRegNode::put_Value);

		++i;
	}
}

void CMetaParser::StartConstraint(const attributes_type &attributes)
{
	CComObjPtr<IMgaMetaConstraint> c;

	CComObjPtr<IMgaMetaBase> prev;
	GetPrevObj(prev);
	COMTHROW( prev->CreateConstraint(PutOut(c)) );

	ASSERT( c != NULL );
	GetCurrent().object = c;

	foundconstraints = true;


	attributes_iterator i = attributes.begin();
	attributes_iterator e = attributes.end();
	while( i != e )
	{
		Attr(i, "name", c, &IMgaMetaConstraint::put_Name);
		Attr(i, "eventmask", c, &IMgaMetaConstraint::put_EventMask);
		Attr(i, "priority", c, &IMgaMetaConstraint::put_Priority);
		Attr(i, "defdfornamesp", c, &IMgaMetaConstraint::SetDefinedForNamespace);

		if( i->first == "depth" )
		{
			constraint_depth_enum depth;
			if( i->second == "0" )
				depth = CONSTRAINT_DEPTH_ZERO;
			else if( i->second == "any" )
				depth = CONSTRAINT_DEPTH_ANY;
			else
				depth = CONSTRAINT_DEPTH_ONE;
			COMTHROW( c->put_Depth(depth) );
		}
		else if( i->first == "type" )
		{
			constraint_type_enum type;
			if( i->second == "ondemand" )
				type = CONSTRAINT_TYPE_ONDEMAND;
			else if( i->second == "function" )
				type = CONSTRAINT_TYPE_FUNCTION;
			else
				type = CONSTRAINT_TYPE_EVENTBASED;
			COMTHROW( c->put_Type(type) );
		}

		++i;
	}
}

void CMetaParser::EndConstraint()
{
	CComObjPtr<IMgaMetaConstraint> c;

	ASSERT( GetCurrent().object != NULL );
	COMTHROW( GetCurrent().object.QueryInterface(c) );
	ASSERT( c != NULL );

	COMTHROW( c->put_Expression(PutInBstr(GetCurrData())) );
}
