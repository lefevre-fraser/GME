
#include "stdafx.h"
#include "GenParser.h"

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/SAXParser.hpp>
#include <xercesc/sax/Locator.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/framework\MemBufInputSource.hpp>
#include <stdio.h>

// --------------------------- XmlStr

XmlStr::XmlStr(const XMLCh* const input)
{
	resize(GetCharLength(input, -1));
	CopyTo(input, -1, &(operator[](0)), length());
	ASSERT( operator[](length()-1) == 0 );
	erase( length() - 1); // was: pop_back();
}

XmlStr::XmlStr(const XMLCh* const input, unsigned int len)
{
	resize(GetCharLength(input, len));
	CopyTo(input, len, &(operator[](0)), length());
}

void CGenParser::SetErrorInfo2(HRESULT hr)
{
	std::string str;
	Format(str, "in file %s at line %ld, char %ld", 
		xmlfile.c_str(), err_line, err_column);

	SetErrorInfo(hr, PutInBstr(str));
}

void CGenParser::ThrowXmlError(const char *format, ...)
{
	ASSERT( format != NULL );

	va_list args;
	va_start(args, format);

	std::string desc;
	vFormat(desc, format, args);

	std::string str;
	if( locator != NULL )
		Format(str, 
			"XML parser error in file %s at line %d, char %d : %s",
			xmlfile.c_str(), (int)locator->getLineNumber(),
			(int)locator->getColumnNumber(), desc.c_str());
	else
		Format(str,
			"XML parser error in file %s : %s", xmlfile.c_str(), desc.c_str());

	CopyTo(str, errorinfo);
	HR_THROW(E_XMLPARSER);
}

// ------- Handler Base

InputSource *CGenParser::resolveEntity(const XMLCh* const publicId, const XMLCh* const systemId)
{
	do
	{
		XmlStr sysid = systemId;
		std::string syssid = sysid;

		HMODULE hm = GetModuleHandle("PARSER.DLL");
		if( hm == NULL )
			break;

		HRSRC res = FindResource(hm, syssid.c_str(), "DTD");
		if(res) {
			XMLByte *bytes = (XMLByte *)LockResource(LoadResource(hm, res));
			if(!bytes) COMTHROW(E_INVALID_DTD); 
			return new MemBufInputSource(bytes, SizeofResource(hm, res), syssid.c_str());
		}

		
		char filename[200];
		int a = GetModuleFileName(hm, filename, 200);
		a -= 10;
		if( a <= 0 )
			break;

		if( _stricmp(filename + a, "PARSER.DLL") != 0 )
			break;

		strcpy(filename + a, sysid.c_str());

		FILE *file = fopen(filename, "r");
		if( file == NULL )
			break;

		fclose(file);

		return new LocalFileInputSource(PutInBstr(filename));

	} while(false);

	return HandlerBase::resolveEntity(publicId, systemId);
}

void CGenParser::startDocument()
{
	counter = 0;
}

void CGenParser::endDocument()
{
	locator = NULL;
}

void CGenParser::startElement(const XMLCh* const name, AttributeList& attrlist)
{
#ifdef _DEBUG
	int cur_line, cur_column;
	if( locator != NULL )
	{
		cur_line = (int)locator->getLineNumber();
		cur_column = (int)locator->getColumnNumber();
	}
#endif

	try
	{
		attributes_type attributes;

		unsigned int len = attrlist.getLength();
		for(unsigned int index = 0; index < len; index++)
		{
			attributes.push_back( std::pair<std::string,std::string>(
				XmlStr(attrlist.getName(index)), XmlStr(attrlist.getValue(index))) );
		}

		XmlStr namestr(name);

		elements.push_back(element_type());
		elements.back().name = namestr;
		elements.back().begin = counter;

		for(unsigned int index = 0; !elementfuncs[index].name.empty(); index++)
		{
			if( namestr == elementfuncs[index].name )
			{
				elementfuncs[index].Start(this, attributes);
				break;
			}
		}
	}
	catch(hresult_exception &)
	{
		if( locator != NULL )
		{
			err_line = locator->getLineNumber();
			err_column = locator->getColumnNumber();

			// we compose and set the error message for exceptions
			// [which come from the MGA layer because of meta incompatibility]
			std::string str;
			Format(str, "Improper use of object error in file %s at line %d, char %d.", xmlfile.c_str(), err_line, err_column);
			CopyTo(str, errorinfo);
		}

		throw;
	}
}

void CGenParser::endElement(const XMLCh* const name)
{
	try
	{
		XmlStr namestr(name);

		ASSERT( !elements.empty() );

//	we modify the names, see clipboard
//	ASSERT( elements.back().name == namestr );

		elements.back().end = counter;

		for(int index = 0; !elementfuncs[index].name.empty(); index++)
		{
			if( namestr == elementfuncs[index].name )
			{
				elementfuncs[index].End(this);
				break;
			}
		}

		elements.pop_back();
	}
	catch(hresult_exception &)
	{
		if( locator != NULL )
		{
			err_line = locator->getLineNumber();
			err_column = locator->getColumnNumber();

			// we compose and set the error message for exceptions
			// [which come from the MGA layer because of meta incompatibility]
			std::string str;
			Format(str, "Improper use of object error in file %s at line %d, char %d.", xmlfile.c_str(), err_line, err_column);
			CopyTo(str, errorinfo);
		}

		throw;
	}

}

void CGenParser::characters(const XMLCh* const chars, const unsigned int length)
{
	if( !elements.empty() )
		elements.back().chardata += XmlStr(chars, length);
}

void CGenParser::error(const SAXParseException &e)
{
	ThrowXmlError(
		"(at line %d, char %d) %s",
		(int)e.getLineNumber(),(int)e.getColumnNumber(),
		XmlStr(e.getMessage()).c_str());
}

void CGenParser::fatalError(const SAXParseException &e)
{
	error(e);
}

void CGenParser::setDocumentLocator(const Locator *const loc)
{
	locator = loc;
}

// ------- Attributes

const std::string *CGenParser::GetByNameX(const attributes_type &attributes, const char *name)
{
	attributes_iterator i = attributes.begin();
	attributes_iterator e = attributes.end();
	while( i != e )
	{
		if( (*i).first == name )
			return &(*i).second;

		++i;
	}

	return NULL;
}

long CGenParser::toLong(std::string s)
{
	const char *c = s.c_str();
	char *e;

	long a = strtol(c, &e, 0);

	if( (e - c) != (int) s.length() )
		HR_THROW(E_INVALID_XML_LONG);

	return a;
}

unsigned long CGenParser::toULong(std::string s)
{
	const char *c = s.c_str();
	char *e;

	long a = strtoul(c, &e, 0);

	if( (e - c) != (int) s.length() )
		HR_THROW(E_INVALID_XML_LONG);

	return a;
}