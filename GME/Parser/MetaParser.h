
#ifndef MGA_METAPARSER_H
#define MGA_METAPARSER_H

#ifndef MGA_GENPARSER_H
#include "GenParser.h"
#endif

#include "resource.h"
#include "CommonVersionInfo.h"

// --------------------------- CMetaParser

class ATL_NO_VTABLE CMetaParser : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMetaParser, &CLSID_MetaParser>,
	public ISupportErrorInfoImpl<&IID_IMetaParser>,
	public IDispatchImpl<IMetaParser, &IID_IMetaParser, &LIBID_PARSERLib>,
	public IMgaVersionInfoImpl,
	public CGenParser
{
	bool foundconstraints;
	bool explicitguid;
public:
	CMetaParser();
	~CMetaParser();

DECLARE_REGISTRY_RESOURCEID(IDR_METAPARSER)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMetaParser)
	COM_INTERFACE_ENTRY(IMetaParser)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY_IID(IID_IMgaVersionInfo, IMgaVersionInfoImpl)
END_COM_MAP()

// ------- Methods

public:
	STDMETHOD(Parse)(BSTR filename, BSTR connection);
	
	void CloseAll();

// ------- Attributes

public:
	static const std::string GetNextToken(std::string::const_iterator &i, 
		std::string::const_iterator &e, std::string::const_iterator end);

	typedef CGenParserFunc<CMetaParser> elementfunc;

	static elementfunc elementfuncs_firstpass[];
	static elementfunc elementfuncs_secondpass[];

	CComObjPtr<IMgaMetaProject> metaproject;

// ------- Element Handlers

public:
	void StartParadigm(const attributes_type &attributes);
	void EndComment();
	void EndAuthor();
	void EndDispName();
	void StartFolder(const attributes_type &attributes);
	void StartFolder2(const attributes_type &attributes);
	void StartAtom(const attributes_type &attributes);
	void StartModel(const attributes_type &attributes);
	void StartConnection(const attributes_type &attributes);
	void StartReference(const attributes_type &attributes);
	void StartSet(const attributes_type &attributes);
	void StartAttrDef(const attributes_type &attributes);
	void StartFCO2(const attributes_type &attributes);
	void StartRole2(const attributes_type &attributes);
	void StartAspect2(const attributes_type &attributes);
	void StartPart2(const attributes_type &attributes);
	void StartRegNode(const attributes_type &attributes);
	void StartConnJoint(const attributes_type &attributes);
	void StartPointerSpec(const attributes_type &attributes);
	void StartPointerItem(const attributes_type &attributes);
	void StartEnumItem(const attributes_type &attributes);
	void StartConstraint(const attributes_type &attributes);
	void EndConstraint();
};

#endif//MGA_METAPARSER_H
