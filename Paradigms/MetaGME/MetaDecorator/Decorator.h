// UMLDecorator.h : Declaration of the CUMLDecorator

#ifndef __UMLDECORATOR_H_
#define __UMLDECORATOR_H_

#include "DecoratorStd.h"
#include "DecoratorConfig.h"
#include "Resource.h"       // main symbols
#define __Meta_h__
#define __Mga_h__
#include "DecoratorLib.h"
#include "DecoratorUtil.h"

class CMetaAttr;
typedef CTypedPtrList<CPtrList, CMetaAttr *>		CMetaAttrList;

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
	DecoratorSDK::BitmapBase*	m_bitmap;					// for proxies or constraints
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
