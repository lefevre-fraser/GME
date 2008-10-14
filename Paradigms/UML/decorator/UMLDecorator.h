// UMLDecorator.h : Declaration of the CUMLDecorator
//
// 12/06/2002 - modified by Ed Willink, Thales Research and Technology (abstract classes)
//

#ifndef __UMLDECORATOR_H_
#define __UMLDECORATOR_H_

#include "resource.h"       // main symbols
#include "decoratorstd.h"
#include "DecoratorUtil.h"

class CUMLAttr;
typedef CTypedPtrList<CPtrList, CUMLAttr *>		CUMLAttrList;

/////////////////////////////////////////////////////////////////////////////
// CUMLDecorator
class ATL_NO_VTABLE CUMLDecorator : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IMgaDecorator,
	public CComCoClass<CUMLDecorator, &CLSID_UMLDecorator>
{
public:
	CUMLDecorator();
	~CUMLDecorator();

DECLARE_REGISTRY_RESOURCEID(IDR_UMLDECORATOR)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CUMLDecorator)
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
	bool m_isAbstract;
	bool m_isActive;
	bool m_isCopy;
	bool m_isInheritance;
	bool m_isConstraint;
	bool m_isConstraintDefinition;
	bool m_isConnector;
	CComPtr<IMgaFCO>	m_mgaFco;
	CComPtr<IMgaMetaFCO>	m_metaFco;
	CString m_name;
	CPoint	m_namePos;
	CString m_stereotype;
	CPoint	m_stereotypePos;
	CUMLAttrList	m_attrs;
	CSize	m_calcSize;
	CPoint	m_copySignPos;
	CRect	m_sepLoc;
	DecoratorSDK::BitmapBase* m_copyBitmap;
	DecoratorSDK::BitmapBase* m_constraintBitmap;
	DecoratorSDK::BitmapBase* m_constraintDefBitmap;

	COLORREF	m_color;
	COLORREF	m_nameColor;

private:
	void CollectAttributes(CComPtr<IMgaFCO> mgaFco = NULL);
	void CalcRelPositions(CDC *pDC = NULL);
	bool SetupInheritance();
	bool SetupConstraint();
	bool SetupConnector();
	bool SetupConstraintDefinition();
};


class	CUMLAttr {
friend class CUMLDecorator;

private:
	CUMLAttr(const CString &name, const CString &type) : m_name(name), m_type(type), m_namePos(DWORD(0)), m_typePos(DWORD(0)) {}

	CString m_name;
	CPoint	m_namePos;
	CString m_type;
	CPoint	m_typePos;
};


#endif //__UMLDECORATOR_H_
