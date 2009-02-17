// Decorator.h : Declaration of the CDecorator

#ifndef __DECORATOR_H_
#define __DECORATOR_H_

#include "DecoratorStd.h"
#include "DecoratorConfig.h"
#include "Resource.h"       // main symbols
#define __Meta_h__
#define __Mga_h__
#include "DecoratorLib.h"


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
	CComPtr<IMgaRegNode>	m_regRoot;
	CString		m_name;
	CString		m_text;
	COLORREF	m_color;
	COLORREF	m_bgcolor;
	LOGFONT		m_logfont;

private:
	void	CalcNativeSize(CSize &size);
	void	ReadPreferences();
};


#endif //__DECORATOR_H_
