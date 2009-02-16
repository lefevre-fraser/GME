// Decorator.cpp : Implementation of CDecorator
#include "stdafx.h"
#include "Decorator.h"


#define VERIFY_INITIALIZATION	{ if (!m_isInitialized) return E_DECORATOR_UNINITIALIZED; }
#define VERIFY_LOCATION			{ if (!m_isLocSet) return E_DECORATOR_LOCISNOTSET; }

CDecoratorUtil	d_util;

#define SAMPLE_SIZEX	40
#define SAMPLE_SIZEY	20

/////////////////////////////////////////////////////////////////////////////
// CDecorator
STDMETHODIMP CDecorator::Initialize(IMgaProject* project, IMgaMetaPart* metaPart, IMgaFCO* obj)
{
	//
	// TODO: read all important data from MGA and cache them for later use
	//
	m_mgaFco = obj;		// obj == NULL, if we are in the PartBrowser
	
	if (!GetMetaFCO(metaPart, m_metaFco)) {
		return E_DECORATOR_INIT_WITH_NULL;
	} else {
		m_isInitialized = true;
	}	
	
	if (m_mgaFco) {
		CComBSTR bstr;
		COMTHROW(m_mgaFco->get_Name(&bstr));
		m_name = bstr;
	} else {
		CComBSTR bstr;
		COMTHROW(m_metaFco->get_DisplayedName(&bstr));
		if (bstr.Length() == 0 ) {
			bstr.Empty();
			COMTHROW(m_metaFco->get_Name(&bstr));
		}
		m_name = bstr;
	}

	if (!GetColorPreference(m_color,COLOR_PREF)) {
		m_color = GME_BLACK_COLOR;
	}
	if (!GetColorPreference(m_nameColor,NAME_COLOR_PREF)) {
		m_nameColor = GME_BLACK_COLOR;
	}
	return S_OK;
}

STDMETHODIMP CDecorator::Destroy()
{
	//
	// TODO: At least free all references to MGA objects
	//
	VERIFY_INITIALIZATION;
	m_isInitialized = false;
	m_isLocSet = false;
	m_metaFco = NULL;
	m_mgaFco = NULL;
	return S_OK;
}

STDMETHODIMP CDecorator::GetMnemonic(BSTR* mnemonic)
{	
	//
	// TODO: Return the logical name of the decorator (currently not used by GME)
	//
	*mnemonic = CComBSTR(DECORATOR_NAME).Detach();
	return S_OK;
}

STDMETHODIMP CDecorator::GetFeatures(feature_code *features)
{	
	//
	// TODO: Return supported features (combine multiple features with bitwise-OR)
	// Available feature codes are found in MgaDecorator.idl
	// (curently not used by GME)
	*features = 0;
	return S_OK;
}

STDMETHODIMP CDecorator::SetParam(BSTR name, VARIANT value)
{
	//
	// TODO:  Parse and set all supported parameters, otherwise return error
	// (currently all values are BSTR type)
	//
	VERIFY_INITIALIZATION;
	return E_DECORATOR_UNKNOWN_PARAMETER;
}

STDMETHODIMP CDecorator::GetParam(BSTR name, VARIANT* value)
{
	//
	// TODO: Return values of supported and previously set parameters, otherwise return error
	// (currently GME does not use this method)
	//
	VERIFY_INITIALIZATION;
	return E_DECORATOR_UNKNOWN_PARAMETER;
}

STDMETHODIMP CDecorator::SetActive(VARIANT_BOOL isActive)
{
	//
	// TODO: If isActive==VARIANT_FALSE, draw your object in GME_GREYED_OUT, otherwise use the color of the object
	//
	VERIFY_INITIALIZATION;
	m_isActive = (isActive != VARIANT_FALSE);
	return S_OK;
}

STDMETHODIMP CDecorator::GetPreferredSize(long* sizex, long* sizey) 
{
	//
	// TODO: Give GME a hint about the object size. Do not expect GME to take it into account
	//
	VERIFY_INITIALIZATION;
	*sizex = SAMPLE_SIZEX;
	*sizey = SAMPLE_SIZEY;
	return S_OK;
}


STDMETHODIMP CDecorator::SetLocation(long sx, long sy, long ex, long ey)
{
	//
	// TODO: Draw the object exactly to the this location later
	//
	VERIFY_INITIALIZATION;
	m_sx = sx;
	m_sy = sy;
	m_ex = ex;
	m_ey = ey;
	m_isLocSet = true;
	return S_OK;
}

STDMETHODIMP CDecorator::GetLocation(long* sx, long* sy, long* ex, long* ey)
{
	//
	// TODO: Return previously set location parameters
	// (currently GME does not call this)
	// 
	VERIFY_INITIALIZATION;
	VERIFY_LOCATION;
	*sx = m_sx;
	*sy = m_sy;
	*ex = m_ex;
	*ey = m_ey;
	return S_OK;
}

STDMETHODIMP CDecorator::GetLabelLocation(long* sx, long* sy, long* ex, long* ey)
{
	//
	// TODO: Return the location of the text box of your label if you support labels.
	// (currently GME does not call this)
	//
	VERIFY_INITIALIZATION;
	VERIFY_LOCATION;
	return S_OK;
}

STDMETHODIMP CDecorator::GetPortLocation(IMgaFCO* fco, long* sx, long* sy, long* ex, long* ey)
{
	//
	// TODO: Return the location of the specified port if ports are supported in the decorator
	//
	VERIFY_INITIALIZATION;
	VERIFY_LOCATION;

	return E_DECORATOR_PORTNOTFOUND;
}

STDMETHODIMP CDecorator::GetPorts(IMgaFCOs** portFCOs)
{
	//
	// TODO: Return a collection of mga objects represented as ports.
	//
	VERIFY_INITIALIZATION;
	CComPtr<IMgaFCOs> coll;
	COMTHROW(coll.CoCreateInstance(OLESTR("Mga.MgaFCOs")));
	*portFCOs = coll.Detach();
	return S_OK;
}


STDMETHODIMP CDecorator::Draw(HDC hdc)
{
	//
	// TODO: Draw your object. Saving & restoring the HDC is a good practice, however it is not a strict requirement
	// Use d_util for brushes/pens/fonts.
	//
	VERIFY_INIT;
	VERIFY_LOCSET;

	CDC dc;
	dc.Attach(hdc);
	CRect rect(m_sx, m_sy, m_ex, m_ey);
	d_util.DrawFlatBox(&dc, rect, m_color, m_color);
	d_util.DrawText(&dc, m_name, rect.CenterPoint(), d_util.GetFont(GME_NAME_FONT), m_nameColor, TA_BOTTOM | TA_CENTER);
	dc.Detach();
	return S_OK;
}

STDMETHODIMP CDecorator::SaveState()
{
	//
	// TODO: The only method where we are in read-write transaction. Store all permanent information
	// (currently GME does not support this) 
	//
	VERIFY_INIT;
	return S_OK;
}


//////////// Decorator private functions
CDecorator::CDecorator() :
	m_sx(0),
	m_sy(0),
	m_ex(0),
	m_ey(0),
	m_isActive(true),
	m_mgaFco(0),
	m_metaFco(0),
	m_isInitialized(false),
	m_isLocSet(false),
	m_color(GME_BLACK_COLOR),
	m_nameColor(GME_BLACK_COLOR)
{
}

CDecorator::~CDecorator()
{
}

bool CDecorator::GetMetaFCO(const CComPtr<IMgaMetaPart>& metaPart, CComPtr<IMgaMetaFCO> &metaFco)
{
	if (!metaPart) {
		return false;
	}

	metaFco = NULL;
	CComPtr<IMgaMetaRole> metaRole;
	try {
		COMTHROW(metaPart->get_Role(&metaRole));
		COMTHROW(metaRole->get_Kind(&metaFco));
	}
	catch (hresult_exception &) {
		metaFco = NULL;
	}
	return (metaFco != NULL);
}

bool CDecorator::GetPreference(CString& val, const CString& path)
{
	CComBSTR pathBstr(path);
	CComBSTR bstrVal;
	if (m_mgaFco) {
		COMTHROW(m_mgaFco->get_RegistryValue(pathBstr, &bstrVal));
	}
	else {
		COMTHROW(m_metaFco->get_RegistryValue(pathBstr, &bstrVal));
	}
	val = bstrVal;
	return !val.IsEmpty();
}

bool CDecorator::GetPreference(int& val, const CString& path, bool hex)
{
	CString strVal;
	GetPreference(strVal, path);
	return (sscanf(strVal, hex ? "%x" : "%d", &val) == 1);
}

bool CDecorator::GetColorPreference(unsigned long& color, const CString& path)
{
	int i;
	if (GetPreference(i, path, true)) {
		unsigned int r = (i & 0xff0000) >> 16;
		unsigned int g = (i & 0xff00) >> 8;
		unsigned int b = i & 0xff;
		color = RGB(r, g, b);
		return true;
	}
	return false;
}