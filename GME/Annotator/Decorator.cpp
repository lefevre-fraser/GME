// UMLDecorator.cpp : Implementation of CUMLDecorator
#include "stdafx.h"
#include "Decorator.h"
#include "..\MgaUtil\AnnotationUtil.h"

#include "..\Common\CommonError.h"

#define VERIFY_INIT   { if (!m_isInitialized) return E_DECORATOR_UNINITIALIZED; }
#define VERIFY_LOCSET { if (!m_isLocSet) return E_DECORATOR_LOCISNOTSET; }


/////////////////////////////////////////////////////////////////////////////
// CDecorator
STDMETHODIMP CDecorator::Initialize(IMgaProject *project, IMgaMetaPart *metaPart, IMgaFCO *obj)
{
	return S_OK;
}

STDMETHODIMP CDecorator::Destroy()
{
	VERIFY_INIT;
	m_isInitialized = false;
	m_isLocSet = false;

	return S_OK;
}

STDMETHODIMP CDecorator::GetMnemonic(BSTR *mnemonic)
{	
	*mnemonic = CComBSTR(DECORATOR_NAME).Detach();
	return S_OK;
}

STDMETHODIMP CDecorator::GetFeatures(feature_code *features)
{
	*features = F_RESIZABLE | F_MOUSEEVENTS | F_RESIZEAFTERMOD;
	return S_OK;
}

STDMETHODIMP CDecorator::SetParam(BSTR name, VARIANT value)
{
	// VERIFY_INIT;
	CString param(name);
	if (!param.CompareNoCase(AN_PARAM_ROOTNODE)) {
		CComVariant	variantval(value);
		try {
			COMTHROW(variantval.ChangeType(VT_UNKNOWN));
			CComPtr<IUnknown> unk(variantval.punkVal);
			COMTHROW(unk.QueryInterface(&m_regRoot));
			ReadPreferences();
			m_isInitialized = true;
		}
		catch (hresult_exception &) {
			return E_ANNOTATOR_INVALID_PARAMVALUE;
		}
	}
	else {
		return E_DECORATOR_UNKNOWN_PARAMETER;
	}
	return S_OK;
}

STDMETHODIMP CDecorator::GetParam(BSTR name, VARIANT* value)
{
	// VERIFY_INIT;
	CString param(name);
	if (!param.CompareNoCase(AN_PARAM_ROOTNODE)) {
		CComVariant	variantval;
		variantval.Attach(value);
		variantval = m_regRoot;
	}
	else {
		return E_DECORATOR_UNKNOWN_PARAMETER;
	}
	return S_OK;
}

STDMETHODIMP CDecorator::SetActive(VARIANT_BOOL isActive)
{
	VERIFY_INIT;
	m_isActive = (isActive != VARIANT_FALSE);
	return S_OK;
}

STDMETHODIMP CDecorator::GetPreferredSize(long* sizex, long* sizey) 
{
	VERIFY_INIT;

	CSize size;
	CalcNativeSize(size);

	*sizex = size.cx;
	*sizey = size.cy;
	return S_OK;
}


STDMETHODIMP CDecorator::SetLocation(long sx, long sy, long ex, long ey)
{
	VERIFY_INIT;
	m_sx = sx;
	m_sy = sy;
	m_ex = ex;
	m_ey = ey;
	m_isLocSet = true;
	return S_OK;
}

STDMETHODIMP CDecorator::GetLocation(long *sx, long *sy, long *ex, long *ey)
{
	VERIFY_INIT;
	VERIFY_LOCSET;
	*sx = m_sx;
	*sy = m_sy;
	*ex = m_ex;
	*ey = m_ey;
	return S_OK;
}

STDMETHODIMP CDecorator::GetLabelLocation(long *sx, long *sy, long *ex, long *ey)
{
	//
	// TODO: Return the location of the text box of your label if you support labels.
	// (currently GME does not call this)
	//
	VERIFY_INIT;
	VERIFY_LOCSET;
	return S_OK;
}

STDMETHODIMP CDecorator::GetPortLocation(IMgaFCO *fco, long *sx, long *sy, long *ex, long *ey)
{
	VERIFY_INIT;
	VERIFY_LOCSET;

	return E_DECORATOR_PORTNOTFOUND;
}

STDMETHODIMP CDecorator::GetPorts(IMgaFCOs **portFCOs)
{
	VERIFY_INIT;
	CComPtr<IMgaFCOs> coll;
	HRESULT hr = coll.CoCreateInstance(OLESTR("Mga.MgaFCOs"));
	*portFCOs = coll.Detach();
	return hr;
}


STDMETHODIMP CDecorator::Draw(HDC hdc)
{
	VERIFY_INIT;
	VERIFY_LOCSET;

	CDC dc;
	dc.Attach(hdc);
	CRect rect(m_sx, m_sy, m_ex, m_ey);

	CFont myfont;
	myfont.CreateFontIndirect(&m_logfont);
	CFont *oldfont = dc.SelectObject(&myfont);
	dc.SetTextColor(m_isActive ? m_color : GME_GRAYED_OUT_COLOR);


	dc.SelectStockObject(NULL_PEN);

	if ( m_isActive && (m_bgcolor != AN_COLOR_TRANSPARENT) ) {
		CBrush mybrush(m_bgcolor);
		CPen mypen(PS_SOLID, 1, m_bgcolor);
		CPen   *oldpen = dc.SelectObject(&mypen);
		CBrush *oldbrush = dc.SelectObject(&mybrush);
		dc.Rectangle(&rect);
		dc.SelectObject(oldpen);
		dc.SelectObject(oldbrush);
	}

	int oldbkmode = dc.SetBkMode( ((!m_isActive) || m_bgcolor == AN_COLOR_TRANSPARENT) ? TRANSPARENT : OPAQUE);
	COLORREF oldbkcolor = dc.SetBkColor(m_bgcolor);
	dc.SetTextAlign(TA_LEFT | TA_TOP);
	rect.bottom -= 	AN_MARGIN;
	rect.top += AN_MARGIN;
	rect.left += AN_MARGIN;
	rect.right -= AN_MARGIN;

	// enlarge area where the text will be written
	// in order to show the whole text when different
	// zoom levels are used (the bounding box still remains
	// the old one) being calculated based on GetLocation()
	rect.right+= (int)( rect.Width() * 0.33);
	rect.bottom+= (int)( rect.Height() * 0.33);
	// annotations can be shown under/behind objects anyway
	// so why feel guilty about allocating much bigger space
	// that would be needed at 100% zoom

	// note: fonts are scaled down differently than guifcos
	// that is why zooming distorts a bit
	// different font sizes are used in different zoom levels
	dc.DrawText( m_text, &rect, DT_LEFT | DT_EXPANDTABS | DT_NOPREFIX);
	// DT_WORDBREAK removed, do not break lines if space is limited,
	// it conflicts with the native size allocated and calculated before
	// altered by zolmol

	dc.SetBkColor(oldbkcolor);
	dc.SetBkMode(oldbkmode);
	dc.SelectObject(oldfont);
	dc.Detach();
	return S_OK;
}

STDMETHODIMP CDecorator::SaveState()
{
	VERIFY_INIT;
	return S_OK;
}


//////////// Decorator private functions
CDecorator::CDecorator() : m_sx(0), m_sy(0), m_ex(0), m_ey(0), 
	m_isActive(true), m_isInitialized(false), m_isLocSet(false),
	m_regRoot(NULL), m_color(AN_DEFAULT_COLOR), m_bgcolor(AN_DEFAULT_BGCOLOR)
{
	memset(&m_logfont, 0, sizeof(LOGFONT));
}

CDecorator::~CDecorator()
{
}

void CDecorator::ReadPreferences()
{
	try {
		CComBSTR bstr;
		COMTHROW(m_regRoot->get_Value(&bstr));
		m_text = bstr;
		m_text.Replace("\n", "\r\n");
	}
	catch (hresult_exception &) {
		m_text = "Unable to read annotation !";
	}

	try {
		CComBSTR bstr;
		COMTHROW(m_regRoot->get_Name(&bstr));
		m_name = bstr;
	}
	catch (hresult_exception &) {
		m_name = "Unknown";
	}

	try {
		CComBSTR bstr;
		CComPtr<IMgaRegNode> lfNode;
		CComBSTR lfName(AN_FONT_PREF);
		COMTHROW(m_regRoot->get_SubNodeByName(lfName, &lfNode));
		if (lfNode != NULL) {
			COMTHROW(lfNode->get_Value(&bstr));
		}
		CString str(bstr);
		if (!CAnnotationUtil::LogfontDecode(str, &m_logfont)) {
			// throw hresult_exception();
			CAnnotationUtil::FillLogFontWithDefault(&m_logfont);
		}
	}
	catch (hresult_exception &) {
		CAnnotationUtil::FillLogFontWithDefault(&m_logfont);
	}

	try {
		CComBSTR bstr;
		CComPtr<IMgaRegNode> colNode;
		CComBSTR colName(AN_COLOR_PREF);
		COMTHROW(m_regRoot->get_SubNodeByName(colName, &colNode));
		if (colNode != NULL) {
			COMTHROW(colNode->get_Value(&bstr));
		}
		CString strVal(bstr);
		unsigned int val;
		if (_stscanf(strVal,_T("%x"),&val) == 1) {
			unsigned int r = (val & 0xff0000) >> 16;
			unsigned int g = (val & 0xff00) >> 8;
			unsigned int b = val & 0xff;
			m_color = RGB(r,g,b);
		}
		else {
			throw hresult_exception();
		}
	}
	catch (hresult_exception &) {
		m_color = AN_DEFAULT_COLOR;
	}

	try {
		CComBSTR bstr;
		CComPtr<IMgaRegNode> bgcolNode;
		CComBSTR bgcolName(AN_BGCOLOR_PREF);
		COMTHROW(m_regRoot->get_SubNodeByName(bgcolName, &bgcolNode));
		if (bgcolNode != NULL) {
			COMTHROW(bgcolNode->get_Value(&bstr));
		}
		CString strVal(bstr);
		unsigned int val;
		if (_stscanf(strVal,_T("%x"),&val) == 1) {
			unsigned int r = (val & 0xff0000) >> 16;
			unsigned int g = (val & 0xff00) >> 8;
			unsigned int b = val & 0xff;
			m_bgcolor = RGB(r,g,b);
		}
		else {
			m_bgcolor = AN_DEFAULT_BGCOLOR;
		}
	}
	catch (hresult_exception &) {
		m_bgcolor = AN_DEFAULT_BGCOLOR;
	}
}

void CDecorator::CalcNativeSize(CSize &size)
{
	CDC	dc;

	dc.CreateCompatibleDC(NULL);
	CFont myfont;
	myfont.CreateFontIndirect(&m_logfont);
	CFont *oldfont = dc.SelectObject(&myfont);
	CRect rect(0,0,0,0);
	dc.DrawText(m_text, &rect, DT_EXPANDTABS | DT_NOPREFIX | DT_CALCRECT);

	// size = dc.GetTabbedTextExtent(m_text, 0, NULL);
	size = rect.Size();
	size.cx += 2*AN_MARGIN;
	size.cy += 2*AN_MARGIN;
	dc.SelectObject(oldfont);
}