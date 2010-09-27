
#ifndef MGA_GENPARSER_H
#define MGA_GENPARSER_H

#include <xercesc/sax/HandlerBase.hpp>

XERCES_CPP_NAMESPACE_USE

template<class DERIVED>
struct CGenParserFunc ;

class CMgaMetaParser;


// --------------------------- XmlStr

class XmlStr : public std::string
{
public:
	XmlStr() { };
	XmlStr(const XMLCh* const input);
	XmlStr(const XMLCh* const input, unsigned int len);
};

// --------------------------- CGenParser

//struct CGenParserFunc_Base;

class CGenParser : public HandlerBase
{
public:
	typedef std::vector< std::pair<std::string, std::string> > attributes_type;
	typedef attributes_type::const_iterator attributes_iterator;


	CGenParser() : locator(NULL),/* elementfuncs(NULL),*/ err_line(0), err_column(0) { }

// ------- Erros

public:
	void SetErrorInfo2(HRESULT hr);
	void ThrowXmlError(const char *format, ...);

// ------- Handler Base

public:
	virtual InputSource *resolveEntity (const XMLCh* const publicId, const XMLCh* const systemId);

    virtual void startDocument();
    virtual void endDocument();

    virtual void startElement(const XMLCh* const name, AttributeList& attributes);
    virtual void endElement(const XMLCh* const name);

	virtual void characters(const XMLCh* const chars, const unsigned int length);

    virtual void error(const SAXParseException& exception);
    virtual void fatalError(const SAXParseException& exception);

	virtual void setDocumentLocator(const Locator *const locator);
	virtual void fireStartFunction(const std::string& name, const attributes_type& attributes) = 0;
	virtual void fireEndFunction(const std::string& name) = 0;

public:
	const Locator *locator;

// ------- Attributes


	


	static const std::string *GetByNameX(const attributes_type &attributes, const char *name);

	static const std::string &GetByName(const attributes_type &attributes, const char *name)
	{
		const std::string *p = GetByNameX(attributes, name);
		const static std::string nullstr;

		if( p == NULL ) p = &nullstr;
//			HR_THROW(E_INVALID_DTD);

		return *p;
	}

	template<class INTERFACE, class FUNC_INTERFACE>
	void Attr(attributes_iterator i, const char *name, INTERFACE p, 
		HRESULT (__stdcall FUNC_INTERFACE::*func)(BSTR))
	{
		if( i->first == name )
		{
			FUNC_INTERFACE *q = p;
			ASSERT( q != NULL );

			COMTHROW( (q->*func)(PutInBstr(i->second)) );
		}
	}

	static long toLong(std::string s);
	static unsigned long toULong(std::string s);

	template<class INTERFACE, class FUNC_INTERFACE>
	void Attr(attributes_iterator i, const char *name, INTERFACE p,
	HRESULT (__stdcall FUNC_INTERFACE::*func)(long))
	{
		if( i->first == name )
		{
			FUNC_INTERFACE *q = p;
			ASSERT( q != NULL );

			COMTHROW( (q->*func)(toLong(i->second)) );
		}
	}

	template<class INTERFACE, class FUNC_INTERFACE>
	void Attr(attributes_iterator i, const char *name, INTERFACE p,
	HRESULT (__stdcall FUNC_INTERFACE::*func)(unsigned long))
	{
		if( i->first == name )
		{
			FUNC_INTERFACE *q = p;
			ASSERT( q != NULL );

			COMTHROW( (q->*func)(toULong(i->second)) );
		}
	}

// ------- ElementFuncs

public:

	// Used to be: CGenParserFunc_Base *elementfuncs;
	//CGenParserFunc <CMgaMetaParser> *elementfuncs;

	void StartNone(const attributes_type &attributes) { }
	void EndNone() { }

// ------- Properties

public:
	std::string xmlfile;
	CComBstrObj errorinfo;
	long err_line;
	long err_column;

	typedef unsigned long counter_type;
	counter_type counter;		// we do not advance the counter in GenParser

	struct element_type
	{
		std::string name;
		std::string chardata;
		CComObjPtr<IUnknown> object;
		std::string exstrinfo;
		long   exnuminfo;

		counter_type begin;
		counter_type end;
	};

	std::vector<element_type> elements;

public:
	element_type &GetCurrent() { ASSERT( !elements.empty() ); return elements.back(); }
	const element_type &GetPrevious() const
	{
		ASSERT( elements.size() >= 2 );

		std::vector<element_type>::const_iterator i = elements.end();
		--i; --i;
		return *i;
	}

	std::string &GetCurrData() { return GetCurrent().chardata; }
	const std::string &GetPrevName() const { return GetPrevious().name; }
	
	template<class T>
	void GetPrevObj(CComObjPtr<T> &obj) const
	{
		ASSERT( GetPrevious().object != NULL );
		COMTHROW( GetPrevious().object.QueryInterface(obj) );
		ASSERT( obj != NULL );
	}

	PutInBstr PutInBstrAttr(const attributes_type &attributes, const char *name)
	{
		const std::string *s = GetByNameX(attributes, name);
		if( s == NULL )
			return "";

		return *s;
	}
};

// --------------------------- CGenParserFunc
/*
struct CGenParserFunc_Base
{
	CGenParserFunc_Base(const char *n) : name(n) { }

	std::string name;

	virtual void Start(CGenParser *parser, const CGenParser::attributes_type &attributes) = 0;
	virtual void End(CGenParser *parser) = 0;
};
*/
template<class DERIVED>
struct CGenParserFunc //: public CGenParserFunc_Base
{
	typedef void (DERIVED::*StartFunc)(const CGenParser::attributes_type &);
	typedef void (DERIVED::*EndFunc)();

	CGenParserFunc(const char *n) : name(n) { }

	std::string name;

	virtual void Start(CGenParser *parser, const CGenParser::attributes_type &attributes)
	{ 
		(static_cast<DERIVED*>(parser)->*start)(attributes);  
	}

	virtual void End(CGenParser *parser)
	{
		(static_cast<DERIVED*>(parser)->*end)();
	}

	CGenParserFunc(const char *n, StartFunc s, EndFunc e) : 
		name(n), start(s), end(e) { }

	StartFunc start;
	EndFunc end;
};

#endif//MGA_GENPARSER_H
