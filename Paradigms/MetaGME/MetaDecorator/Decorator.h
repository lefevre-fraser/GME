// UMLDecorator.h : Declaration of the CUMLDecorator

#ifndef __UMLDECORATOR_H_
#define __UMLDECORATOR_H_

#include "DecoratorStd.h"
#include "DecoratorConfig.h"
#include "Resource.h"       // main symbols
#include "DecoratorLib.h"
#include "DecoratorUtil.h"
#include "MaskedBitmap.h"

typedef enum {NULLSHAPE, CLASS, CLASSPROXY, CONNECTOR, CONSTRAINT, EQUIVALENCE, INHERITANCE, INTINHERITANCE, IMPINHERITANCE, CONSTRAINTFUNC } ShapeCode;

class CMetaAttr;
typedef CTypedPtrList<CPtrList, CMetaAttr *>		CMetaAttrList;

#define	 META_DEFAULT_SHOWABSTRACT		true
#define	 META_DEFAULT_SHOWATTRIBUTES	true

#define  META_STEREOTYPE_LEFT		"<<"
#define  META_STEREOTYPE_RIGHT		">>"
#define  META_ATTRIBUTE_SEP			" : "

#define	 META_DECORATOR_MARGINX		6
#define	 META_DECORATOR_MARGINY		4
#define	 META_DECORATOR_GAPY		0
#define  META_DECORATOR_MINATTRSIZE	13
#define  META_INHERITANCE_WIDTH		24
#define	 META_INHERITANCE_HEIGHT	(0.866 * META_INHERITANCE_WIDTH)
#define	 META_INHERITANCE_RADIUS	(META_INHERITANCE_HEIGHT / 4)
#define  META_EQUIVALENCE_WIDTH		(2 * META_INHERITANCE_HEIGHT)
#define	 META_EQUIVALENCE_HEIGHT	META_INHERITANCE_WIDTH
#define	 META_CONNECTOR_RAIDUS		4

#define	 META_CLASS_BGCOLOR			RGB(0xFF,0xFF,0xFF)
#define	 META_TRANSPARENT_COLOR		RGB(0xFF,0xFF,0xFF)

#define  META_ABSTRACT_ATTR			"IsAbstract"

#define	 META_ATOM_KIND				"Atom"
#define	 META_ATOMPROXY_KIND		"AtomProxy"
#define	 META_MODEL_KIND			"Model"
#define	 META_MODELPROXY_KIND		"ModelProxy"
#define	 META_REFERENCE_KIND		"Reference"
#define	 META_REFERENCEPROXY_KIND	"ReferenceProxy"
#define	 META_SET_KIND				"Set"
#define	 META_SETPROXY_KIND			"SetProxy"
#define	 META_CONNECTION_KIND		"Connection"
#define	 META_CONNECTIONPROXY_KIND	"ConnectionProxy"
#define	 META_FCO_KIND				"FCO"
#define	 META_FCOPROXY_KIND			"FCOProxy"

#define	 META_FOLDER_KIND			"Folder"
#define	 META_FOLDERPROXY_KIND		"FolderProxy"

#define	 META_ASPECT_KIND			"Aspect"
#define	 META_ASPECTPROXY_KIND		"AspectProxy"

#define	 META_BOOLEANATTR_KIND		"BooleanAttribute"
#define	 META_ENUMATTR_KIND			"EnumAttribute"
#define	 META_FIELDATTR_KIND		"FieldAttribute"

#define	 META_CONSTRAINT_KIND		"Constraint"
#define	 META_CONSTRAINTFUNC_KIND	"ConstraintFunc"

#define	 META_CONNECTOR_KIND		"Connector"

#define	 META_EQUIVALENCE_KIND		"Equivalence"
#define	 META_SAMEFOLDER_KIND		"SameFolder"
#define	 META_SAMEASPECT_KIND		"SameAspect"


#define	 META_INHERITANCE_KIND		"Inheritance"
#define	 META_IMPINHERITANCE_KIND	"ImplementationInheritance"
#define	 META_INTINHERITANCE_KIND	"InterfaceInheritance"

#define  META_BOOLEANATTR_LABEL		"bool"
#define  META_ENUMATTR_LABEL		"enum"
#define  META_FIELDATTR_LABEL		"field"

#define  META_PARAM_SHOWATTRIBUTES	"showattributes"
#define  META_PARAM_SHOWABSTRACT	"showabstract"
#define  META_PARAM_VAL_TRUE		"true"
#define  META_PARAM_VAL_FALSE		"false"

#define  E_METADECORATOR_KINDNOTSUPPORTED	0x80737050
#define  E_METADECORATOR_INVALID_PARAMVALUE	0x80737051

/////////////////////////////////////////////////////////////////////////////
// CDecorator
class ATL_NO_VTABLE CDecorator : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IMgaDecorator,
	public CComCoClass<CDecorator, &CLSID_Decorator>
{
public:
	CDecorator();
	~CDecorator();

DECLARE_REGISTRY_RESOURCEID(IDR_DECORATOR)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDecorator)
	COM_INTERFACE_ENTRY(IMgaDecorator)
END_COM_MAP()

// IMgaDecorator
public:
	STDMETHOD(Initialize)(/*[in]*/ IMgaProject *project, /*[in]*/ IMgaMetaPart *meta, /*[in]*/ IMgaFCO *obj);
	STDMETHOD(Destroy)();
	STDMETHOD(GetMnemonic)(/*[out]*/ BSTR *mnemonic);
	STDMETHOD(GetFeatures)(/*[out]*/ feature_code *features);
	STDMETHOD(SetParam)(/*[in]*/ BSTR name, /*[in]*/ VARIANT value);
	STDMETHOD(GetParam)(/*[in]*/ BSTR name, /*[out]*/ VARIANT* value);
	STDMETHOD(SetActive)(/*[in]*/ VARIANT_BOOL isActive);
	STDMETHOD(GetPreferredSize)(/*[out]*/ long* sizex, /*[out]*/ long* sizey);
	STDMETHOD(SetLocation)(/*[in]*/ long sx, /*[in]*/ long sy, /*[in]*/ long ex, /*[in]*/ long ey);
	STDMETHOD(GetLocation)(/*[out]*/ long *sx, /*[out]*/ long *sy, /*[out]*/ long *ex, /*[out]*/ long *ey);	
	STDMETHOD(GetLabelLocation)( /*[out]*/ long *sx, /*[out]*/ long *sy, /*[out]*/ long *ex, /*[out]*/ long *ey);
	STDMETHOD(GetPortLocation)(/*[in]*/ IMgaFCO *fco, /*[out]*/ long *sx, /*[out]*/ long *sy, /*[out]*/ long *ex, /*[out]*/ long *ey);
	STDMETHOD(GetPorts)(/*[out, retval]*/ IMgaFCOs **portFCOs);
	STDMETHOD(Draw)(/*[in]*/ HDC hdc);
	STDMETHOD(SaveState)();
	
protected:
	bool m_isInitialized;
	bool m_isLocSet;
	long m_sy;
	long m_sx;
	long m_ey;
	long m_ex;
	bool m_isActive;
	CComPtr<IMgaFCO>	m_mgaFco;
	CComPtr<IMgaMetaFCO>	m_metaFco;
	bool		m_isAbstract;
	CString		m_name;
	CString		m_stereotype;

	COLORREF	m_color;
	COLORREF	m_nameColor;

	ShapeCode	m_shape;
	CMaskedBitmap		m_bitmap;					// for proxies or constraints
	CRect		m_sepLoc;
	CSize		m_calcSize;
	CPoint		m_proxySignPos;
	CPoint		m_namePos;
	CPoint		m_stereotypePos;

	CMetaAttrList	m_attrs;

	bool		m_showAttributes;
	bool		m_showAbstract;

private:
	bool InPartBrowser()			{ return (m_mgaFco == NULL) ; }
	bool IsReal()					{ return (m_mgaFco != NULL) ; }
	bool GetMetaFCO(const CComPtr<IMgaMetaPart> &metaPart, CComPtr<IMgaMetaFCO> &metaFco);
	bool GetPreference(CString &val, const CString &path);
	bool GetPreference(int &val, const CString &path, bool hex = false);
	bool GetColorPreference(COLORREF &color, const CString &path);
	bool GetAttribute(CString &val, const CString &attrname, CComPtr<IMgaFCO> mgaFco = NULL);
	bool GetAttribute(bool &val, const CString &attrname, CComPtr<IMgaFCO> mgaFco = NULL);
	void CalcRelPositions();
	void CollectAttributes(const CComPtr<IMgaFCO> &fco);
	void SortAttributes();
	void SetupClass();
};

class	CMetaAttr {
friend class CDecorator;

private:
	CMetaAttr(const CString &name, const CString &type, const CPoint &boxPos) : m_name(name), m_type(type), m_namePos(DWORD(0)), m_typePos(DWORD(0)), m_boxPos( boxPos) {}

	CString m_name;
	CPoint	m_namePos;
	CString m_type;
	CPoint	m_typePos;
	CPoint  m_boxPos;
};

#endif //__UMLDECORATOR_H_
