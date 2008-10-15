// UMLDecorator.cpp : Implementation of CUMLDecorator
#include "stdafx.h"
#include "Decorator.h"
#include "BitmapUtil.h"

#include "CommonError.cpp"

#define VERIFY_INIT   { if (!m_isInitialized) return E_DECORATOR_UNINITIALIZED; }
#define VERIFY_LOCSET { if (!m_isLocSet) return E_DECORATOR_LOCISNOTSET; }

#pragma message( "TODO: calculate labelpos" )
#pragma message( "TODO: problems with printing" )
#pragma message( "TODO: collect equivalent classes..." )


struct ShapePair {
	char*	  kind;
	ShapeCode shape;
};

const static ShapePair shapeMap[] = {
	{META_ATOM_KIND, CLASS},
	{META_ATOMPROXY_KIND, CLASSPROXY},
	{META_MODEL_KIND, CLASS},
	{META_MODELPROXY_KIND, CLASSPROXY},
	{META_REFERENCE_KIND, CLASS},
	{META_REFERENCEPROXY_KIND, CLASSPROXY},
	{META_SET_KIND, CLASS},
	{META_SETPROXY_KIND, CLASSPROXY},
	{META_CONNECTION_KIND, CLASS},
	{META_CONNECTIONPROXY_KIND, CLASSPROXY},
	{META_FCO_KIND, CLASS},
	{META_FCOPROXY_KIND, CLASSPROXY},
	{META_FOLDER_KIND, CLASS},
	{META_FOLDERPROXY_KIND, CLASSPROXY},
	{META_ASPECT_KIND, CLASS},
	{META_ASPECTPROXY_KIND, CLASSPROXY},
	{META_BOOLEANATTR_KIND, CLASS},
	{META_ENUMATTR_KIND, CLASS},
	{META_FIELDATTR_KIND, CLASS},

	{META_CONSTRAINT_KIND, CONSTRAINT},
	{META_CONSTRAINTFUNC_KIND, CONSTRAINTFUNC},

	{META_CONNECTOR_KIND, CONNECTOR},

	{META_EQUIVALENCE_KIND, EQUIVALENCE},
	{META_SAMEFOLDER_KIND, EQUIVALENCE},
	{META_SAMEASPECT_KIND, EQUIVALENCE},

	{META_INHERITANCE_KIND, INHERITANCE},
	{META_IMPINHERITANCE_KIND, IMPINHERITANCE},
	{META_INTINHERITANCE_KIND, INTINHERITANCE},

	{NULL,NULLSHAPE}
};

const char *fcos[] = {
	META_ATOM_KIND,
	META_ATOMPROXY_KIND,
	META_MODEL_KIND,
	META_MODELPROXY_KIND,
	META_REFERENCE_KIND,
	META_REFERENCEPROXY_KIND,
	META_SET_KIND,
	META_SETPROXY_KIND,
	META_CONNECTION_KIND,
	META_CONNECTIONPROXY_KIND,
	META_FCO_KIND,
	META_FCOPROXY_KIND,
	NULL
};

/////////////////////////////////////////////////////////////////////////////
// CDecorator
STDMETHODIMP CDecorator::Initialize(IMgaProject *project, IMgaMetaPart *metaPart, IMgaFCO *obj)
{
	m_mgaFco = obj;		// obj == NULL, if we are in the PartBrowser
	
	if (!DecoratorSDK::getFacilities().getMetaFCO(metaPart, m_metaFco)) {
		return E_DECORATOR_INIT_WITH_NULL;
	}
	else {
		m_isInitialized = true;
	}	

	// Get ShapeCode
	try {
		CComBSTR bstr;
		COMTHROW(m_metaFco->get_Name(&bstr));
		m_stereotype = bstr;

		int i = 0;
		while(shapeMap[i].kind) {
			if (shapeMap[i].kind == m_stereotype) {
				m_shape = shapeMap[i].shape;
				break;
			}
			i++;
		}
		if (m_shape == NULLSHAPE) {
			m_isInitialized = false;
			return E_METADECORATOR_KINDNOTSUPPORTED;
		}
	}
	catch (hresult_exception &e) {
		m_isInitialized = false;
		return e.hr;
	}

	// Init bitmap
	if (m_shape == CLASSPROXY) {
		AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
		m_bitmap = DecoratorSDK::getFacilities().getMaskedBitmap(IDB_BITMAP_PROXY, META_TRANSPARENT_COLOR, GME_GRAYED_OUT_COLOR);
	}
	else if (m_shape == CONSTRAINT) {
		AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
		m_bitmap = DecoratorSDK::getFacilities().getMaskedBitmap(IDB_BITMAP_CONSTRAINT, META_TRANSPARENT_COLOR, GME_GRAYED_OUT_COLOR);
	}
	else if (m_shape == CONSTRAINTFUNC) {
		AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
		m_bitmap = DecoratorSDK::getFacilities().getMaskedBitmap(IDB_BITMAP_CONSTRAINTFUNC, META_TRANSPARENT_COLOR, GME_GRAYED_OUT_COLOR);
	}

	// Get Name
	try {
		if (IsReal()) {
			CComBSTR bstr;
			COMTHROW(m_mgaFco->get_Name(&bstr));
			m_name = bstr;
		}
		else {
			CComBSTR bstr;
			COMTHROW(m_metaFco->get_DisplayedName(&bstr));
			if (bstr.Length() == 0 ) {
				m_name = m_stereotype;
			}
			else {
				m_name = bstr;
			}
		}
	}
	catch (hresult_exception &e) {
		m_isInitialized = false;
		return e.hr;
	}

	if (!DecoratorSDK::getFacilities().getPreference(m_mgaFco, m_metaFco, COLOR_PREF, m_color)) {
		m_color = GME_BLACK_COLOR;
	}
	if (!DecoratorSDK::getFacilities().getPreference(m_mgaFco, m_metaFco, NAME_COLOR_PREF, m_nameColor)) {
		m_nameColor = GME_BLACK_COLOR;
	}
	if (IsReal() && ( (m_shape == CLASS) || (m_shape == CLASSPROXY) ) ) {
		SetupClass();
	}
	CalcRelPositions();
	return S_OK;
}

STDMETHODIMP CDecorator::Destroy()
{
	VERIFY_INIT;
	m_isInitialized = false;
	m_isLocSet = false;
	m_metaFco = NULL; m_mgaFco = NULL;
	return S_OK;
}

STDMETHODIMP CDecorator::GetMnemonic(BSTR *mnemonic)
{	
	*mnemonic = CComBSTR(DECORATOR_NAME).Detach();
	return S_OK;
}

STDMETHODIMP CDecorator::GetFeatures(feature_code *features)
{	
	*features = 0;
	return S_OK;
}

STDMETHODIMP CDecorator::SetParam(BSTR name, VARIANT value)
{
	// VERIFY_INIT;
	CString param = name;
	if (!param.CompareNoCase(META_PARAM_SHOWATTRIBUTES)) {
		CComVariant	variantval(value);
		try {
			COMTHROW(variantval.ChangeType(VT_BSTR));
			CString val = variantval.bstrVal;
			if (!val.CompareNoCase(META_PARAM_VAL_TRUE)) {
				m_showAttributes = true;
			}
			else if (!val.CompareNoCase(META_PARAM_VAL_FALSE)) {
				m_showAttributes = false;
			}
			else {
				return E_METADECORATOR_INVALID_PARAMVALUE;
			}
		}
		catch (hresult_exception &) {
			return E_METADECORATOR_INVALID_PARAMVALUE;
		}
	}
	else if (!param.CompareNoCase(META_PARAM_SHOWABSTRACT)) {
		CComVariant	variantval(value);
		try {
			COMTHROW(variantval.ChangeType(VT_BSTR));
			CString val = variantval.bstrVal;
			if (!val.CompareNoCase(META_PARAM_VAL_TRUE)) {
				m_showAbstract = true;
			}
			else if (!val.CompareNoCase(META_PARAM_VAL_FALSE)) {
				m_showAbstract = false;
			}
			else {
				return E_METADECORATOR_INVALID_PARAMVALUE;
			}
		}
		catch (hresult_exception &) {
			return E_METADECORATOR_INVALID_PARAMVALUE;
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
	CString param = name;
	if (!param.CompareNoCase(META_PARAM_SHOWATTRIBUTES)) {
		CComVariant	variantval;
		variantval.Attach(value);
		variantval = (m_showAttributes ? META_PARAM_VAL_TRUE : META_PARAM_VAL_FALSE);
		
	}
	else if (!param.CompareNoCase(META_PARAM_SHOWABSTRACT)) {
		CComVariant	variantval;
		variantval.Attach(value);
		variantval = (m_showAttributes ? META_PARAM_VAL_TRUE : META_PARAM_VAL_FALSE);
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

	if (m_shape == CLASS || m_shape == CLASSPROXY) {
		*sizex = ((m_calcSize.cx + ((2*GME_GRID_SIZE) - 1)) / (2*GME_GRID_SIZE)) * (2*GME_GRID_SIZE);
		*sizey = m_calcSize.cy;
		// *sizey = ((m_calcSize.cy + ((2*GME_GRID_SIZE) - 1)) / (2*GME_GRID_SIZE)) * (2*GME_GRID_SIZE);
	}
	else {
		*sizex = m_calcSize.cx;
		*sizey = m_calcSize.cy;
	}
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
	VERIFY_INIT;
	VERIFY_LOCSET;
	*sx = m_sx;
	*sy = m_sy;
	*ex = m_ex;
	*ey = m_ey;
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
	HRESULT hr=coll.CoCreateInstance(OLESTR("Mga.MgaFCOs"));
	if(hr==S_OK)
		*portFCOs = coll.Detach();
	return hr;
}


STDMETHODIMP CDecorator::Draw(HDC hdc)
{
	VERIFY_INIT;
	VERIFY_LOCSET;

	CDC dc;
	dc.Attach(hdc);
	
	double scalex = ((double)(m_ex - m_sx)) / (m_calcSize.cx);
	double scaley = ((double)(m_ey - m_sy)) / (m_calcSize.cy);

	switch (m_shape) {
		case CONNECTOR:
		{
			dc.SelectObject(DecoratorSDK::getFacilities().getPen(m_isActive ? m_color : GME_GRAYED_OUT_COLOR));
			dc.SelectObject(DecoratorSDK::getFacilities().getBrush(m_isActive ? m_color : GME_GRAYED_OUT_COLOR));
			dc.Ellipse(m_sx, m_sy, m_ex, m_ey);
			if (InPartBrowser()) {
				CPoint namePos(m_sx + (long)(scalex * m_namePos.x), (long)(m_sy + scaley * m_namePos.y));
				DecoratorSDK::getFacilities().drawText(&dc, m_name, namePos,
														DecoratorSDK::getFacilities().getFont(DecoratorSDK::FONT_PORTNAME)->pFont,
														(m_isActive ? m_nameColor : GME_GRAYED_OUT_COLOR),
														TA_TOP | TA_CENTER);
			}
		}
		break;
	case CONSTRAINT:
	case CONSTRAINTFUNC:
		{
			if (m_bitmap->isInitialized()) {
				CPoint cpt;
				cpt.x = m_sx + ((m_calcSize.cx - (m_ex - m_sx))/2);
				cpt.y = m_sy + ((m_calcSize.cy - (m_ey - m_sy))/2);

				CRect destRect(cpt.x, cpt.y, cpt.x + m_bitmap->getWidth(), cpt.y + m_bitmap->getHeight());
				UINT modifFlags = DecoratorSDK::MF_TRANSPARENT;
				if (!m_isActive)
					modifFlags |= DecoratorSDK::MF_GREYED;
				m_bitmap->draw(&dc, CRect(), destRect, SRCCOPY, modifFlags);
				//m_bitmap.Draw(&dc, cpt.x, cpt.y);
			}
			CPoint namePos(m_sx + (long)(scalex * m_namePos.x), m_sy + (long)(scaley * m_namePos.y));
			DecoratorSDK::getFacilities().drawText(&dc,
													m_name,
													namePos,
													DecoratorSDK::getFacilities().getFont(DecoratorSDK::FONT_PORTNAME)->pFont,
													(m_isActive ? m_nameColor : GME_GRAYED_OUT_COLOR),
													TA_TOP | TA_CENTER);
		}
		break;
	case EQUIVALENCE:
		{
			int cx = m_sx + ((m_ex - m_sx) /2);
			int cy = m_sy + ((m_ey - m_sy) /2);
			dc.SelectObject(DecoratorSDK::getFacilities().getBrush(META_CLASS_BGCOLOR));
			dc.SelectObject(DecoratorSDK::getFacilities().getPen(m_isActive ? m_color : GME_GRAYED_OUT_COLOR));
			dc.BeginPath();
			dc.MoveTo(m_sx, cy);
			dc.LineTo(cx, m_ey);
			dc.LineTo(m_ex, cy);
			dc.LineTo(cx, m_sy);
			dc.LineTo(m_sx, cy);
			dc.EndPath();
			dc.StrokeAndFillPath();
			if (InPartBrowser()) {
				CPoint namePos(m_sx + (long)(scalex * m_namePos.x), m_sy + (long)(scaley * m_namePos.y));
				DecoratorSDK::getFacilities().drawText(&dc,
														m_name,
														namePos,
														DecoratorSDK::getFacilities().getFont(DecoratorSDK::FONT_PORTNAME)->pFont,
														(m_isActive ? m_nameColor : GME_GRAYED_OUT_COLOR),
														TA_TOP | TA_CENTER);
			}
		}
		break;
	case INHERITANCE:
	case IMPINHERITANCE:
	case INTINHERITANCE:
		{
			dc.SelectObject(DecoratorSDK::getFacilities().getBrush(META_CLASS_BGCOLOR));
			dc.SelectObject(DecoratorSDK::getFacilities().getPen(m_isActive ? m_color : GME_GRAYED_OUT_COLOR));
			dc.BeginPath();
			dc.MoveTo(m_sx, m_ey);
			dc.LineTo(m_ex, m_ey);
			dc.LineTo(m_sx + (m_ex-m_sx)/2, m_sy);
			dc.LineTo(m_sx, m_ey);
			dc.EndPath();
			dc.StrokeAndFillPath();

			if (m_shape == IMPINHERITANCE || m_shape == INTINHERITANCE) {
				dc.SelectObject(DecoratorSDK::getFacilities().getBrush(m_isActive ? m_color : GME_GRAYED_OUT_COLOR));
				/* Looks awful
				if (m_shape == IMPINHERITANCE) {
					dc.SelectStockObject(NULL_PEN);
				}
				*/
				if (m_shape == INTINHERITANCE) {
					dc.SelectStockObject(NULL_BRUSH);
				}
				int cx = m_sx + ((m_ex - m_sx)/2);
				int cy = m_sy + (2*(m_ey - m_sy)/3);
				int rx = (long)(scalex * META_INHERITANCE_RADIUS);
				int ry = (long)(scaley * META_INHERITANCE_RADIUS);
				CRect rect(cx - rx + 1, cy - ry + 1, cx + rx, cy + ry);
				dc.Ellipse(&rect);
			}
			if (InPartBrowser()) {
				CPoint namePos(m_sx + (long)(scalex * m_namePos.x), m_sy + (long)(scaley * m_namePos.y));
				DecoratorSDK::getFacilities().drawText(&dc,
														m_name,
														namePos,
														DecoratorSDK::getFacilities().getFont(DecoratorSDK::FONT_PORTNAME)->pFont,
														(m_isActive ? m_nameColor : GME_GRAYED_OUT_COLOR),
														TA_TOP | TA_CENTER);
			}
		}
		break;
	case CLASS:
	case CLASSPROXY:
		{
			// Draw lines
			dc.SelectObject(DecoratorSDK::getFacilities().getBrush(META_CLASS_BGCOLOR));
			dc.SelectObject(DecoratorSDK::getFacilities().getPen(m_isActive ? m_color : GME_GRAYED_OUT_COLOR));
			dc.Rectangle(m_sx, m_sy, m_ex, m_ey);
			dc.MoveTo(m_sx + (long)(scalex * m_sepLoc.left), m_sy + (long)(scaley * m_sepLoc.top));
			dc.LineTo(m_sx + (long)(scalex * m_sepLoc.right), m_sy + (long)(scaley * m_sepLoc.bottom));

			// Draw labels
			if (IsReal()) {
				CPoint namePos(m_sx + (long)(scalex * m_namePos.x), m_sy + (long)(scaley * m_namePos.y));
				DecoratorSDK::getFacilities().drawText(&dc,
														m_name,
														namePos,
														DecoratorSDK::getFacilities().getFont(m_isAbstract ? DecoratorSDK::FONT_ABSTRACT: DecoratorSDK::FONT_PORTNAME)->pFont,
														(m_isActive ? m_nameColor : GME_GRAYED_OUT_COLOR),
														TA_BOTTOM | TA_CENTER);
			}
			CPoint stereotypePos(m_sx + (long)(scalex * m_stereotypePos.x), m_sy + (long)(scaley * m_stereotypePos.y));
			DecoratorSDK::getFacilities().drawText(&dc,
													DecoratorSDK::getFacilities().getStereotyped(m_stereotype),
													stereotypePos,
													DecoratorSDK::getFacilities().getFont(DecoratorSDK::FONT_PORTNAME)->pFont,
													(m_isActive ? m_nameColor : GME_GRAYED_OUT_COLOR),
													TA_BOTTOM | TA_CENTER);
			
			// Draw attributes
			POSITION pos = m_attrs.GetHeadPosition();
			while (pos) {
				CMetaAttr *attr = m_attrs.GetNext(pos);
				CPoint anamePos(m_sx + (long)(scalex * attr->m_namePos.x),  m_sy + (long)(scaley * attr->m_namePos.y));
				DecoratorSDK::getFacilities().drawText(&dc,
														attr->m_name + META_ATTRIBUTE_SEP,
														anamePos,
														DecoratorSDK::getFacilities().getFont(DecoratorSDK::FONT_PORTNAME)->pFont,
														(m_isActive ? m_nameColor : GME_GRAYED_OUT_COLOR),
														TA_BOTTOM | TA_LEFT);
				CPoint typePos(m_sx + (long)(scalex * attr->m_typePos.x),  m_sy + (long)(scaley * attr->m_typePos.y));
				DecoratorSDK::getFacilities().drawText(&dc,
														attr->m_type,
														typePos,
														DecoratorSDK::getFacilities().getFont(DecoratorSDK::FONT_PORTNAME)->pFont,
														(m_isActive ? m_nameColor : GME_GRAYED_OUT_COLOR),
														TA_BOTTOM | TA_RIGHT);
			}
			// Draw Proxy Sign
			if (m_shape == CLASSPROXY && m_bitmap->isInitialized()) {
				CPoint cpt;
				cpt.x = m_sx + (long)(scalex * m_proxySignPos.x);
				cpt.y = m_sy + (long)(scaley * m_proxySignPos.y);

				CRect destRect(cpt.x, cpt.y, cpt.x + m_bitmap->getWidth(), cpt.y + m_bitmap->getHeight());
				UINT modifFlags = DecoratorSDK::MF_TRANSPARENT;
				if (!m_isActive)
					modifFlags |= DecoratorSDK::MF_GREYED;
				m_bitmap->draw(&dc, CRect(), destRect, SRCCOPY, modifFlags);
			}
		}
		break;
	}

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
	m_isActive(true), m_mgaFco(0), m_metaFco(0),
	m_isInitialized(false), m_isLocSet(false), m_isAbstract(false),
	m_color(GME_BLACK_COLOR), m_nameColor(GME_BLACK_COLOR),
	m_shape(NULLSHAPE), m_sepLoc(0,0,0,0), m_calcSize(DWORD(0)),
	m_proxySignPos(DWORD(0)), m_namePos(DWORD(0)), m_stereotypePos(DWORD(0)),
	m_showAbstract(META_DEFAULT_SHOWABSTRACT), m_showAttributes(META_DEFAULT_SHOWATTRIBUTES)
{
}

CDecorator::~CDecorator()
{
	POSITION pos = m_attrs.GetHeadPosition();
	while (pos) {
		delete m_attrs.GetNext(pos);
	}
}

void CDecorator::CalcRelPositions()
{
	switch (m_shape) {
	case CONNECTOR:
		{
			m_calcSize.cx = m_calcSize.cy = 2 * META_CONNECTOR_RAIDUS;
			if (InPartBrowser()) {
				m_namePos.x = m_calcSize.cx / 2;
				m_namePos.y = m_calcSize.cy;
			}
		}
		break;
	case CONSTRAINT:
	case CONSTRAINTFUNC:
		if (m_bitmap->isInitialized()) {
			m_calcSize.cx = m_bitmap->getWidth();
			m_calcSize.cy = m_bitmap->getHeight();
			m_namePos.x = m_calcSize.cx / 2;
			m_namePos.y = m_calcSize.cy;
		}
		break;
	case EQUIVALENCE:
		{
			m_calcSize.cx = (long)META_EQUIVALENCE_WIDTH;
			m_calcSize.cy = (long)META_EQUIVALENCE_HEIGHT;
			if (InPartBrowser()) {
				m_namePos.x = m_calcSize.cx / 2;
				m_namePos.y = m_calcSize.cy;
			}
		}
		break;
	case INHERITANCE:
	case IMPINHERITANCE:
	case INTINHERITANCE:
		{
			m_calcSize.cx = META_INHERITANCE_WIDTH;
			m_calcSize.cy = (long)META_INHERITANCE_HEIGHT;
			if (InPartBrowser()) {
				m_namePos.x = m_calcSize.cx / 2;
				m_namePos.y = m_calcSize.cy;
			}
		}
		break;
	case CLASS:
	case CLASSPROXY:
		{
			int maxHeight = 0, maxWidth = 0;
			CSize ext;
			CDC	dc;
			
			dc.Attach(GetDC(NULL));			// Trick
			CFont *oldfont = dc.SelectObject(DecoratorSDK::getFacilities().getFont(DecoratorSDK::FONT_PORTNAME)->pFont);
			
			if (IsReal()) {
				CFont *normfont;
				if (m_isAbstract) {
					normfont = dc.SelectObject(DecoratorSDK::getFacilities().getFont(DecoratorSDK::FONT_ABSTRACT)->pFont);
				}
				ext = dc.GetTextExtent(m_name);
				maxWidth = max(maxWidth, ext.cx);
				maxHeight = max(maxHeight, ext.cy);
				if (m_isAbstract) {
					dc.SelectObject(normfont);
				}
			}

			POSITION pos = m_attrs.GetHeadPosition();
			while (pos) {
				CMetaAttr *attr = m_attrs.GetNext(pos);
				ext = dc.GetTextExtent(attr->m_name + META_ATTRIBUTE_SEP + attr->m_type);
				maxWidth = max(maxWidth, ext.cx);
				maxHeight = max(maxHeight, ext.cy);
			}

			ext = dc.GetTextExtent(DecoratorSDK::getFacilities().getStereotyped(m_stereotype));
			maxWidth = max(maxWidth, ext.cx);
			maxHeight = max(maxHeight, ext.cy);
			

			int xcenterpos = (2 * META_DECORATOR_MARGINX + maxWidth) / 2; 
			int	xleftpos = META_DECORATOR_MARGINX;
			int	xrightpos = META_DECORATOR_MARGINX + maxWidth;
			int ypos = META_DECORATOR_MARGINY;

			if (IsReal()) {
				m_namePos.x = xcenterpos;
				m_namePos.y = (ypos +=maxHeight);

				ypos += META_DECORATOR_GAPY;
			}

			m_stereotypePos.x = xcenterpos;
			m_stereotypePos.y = (ypos += maxHeight);

			
			ypos += META_DECORATOR_MARGINY;

			m_sepLoc.left = 0;
			m_sepLoc.top = m_sepLoc.bottom = ypos;
			m_sepLoc.right = xrightpos + META_DECORATOR_MARGINX -1;

			ypos += META_DECORATOR_MARGINY;
			
			pos = m_attrs.GetHeadPosition();
			while (pos) {
				CMetaAttr *attr = m_attrs.GetNext(pos);
				attr->m_namePos.x = xleftpos;
				attr->m_namePos.y = (ypos += maxHeight);
				attr->m_typePos.x = xrightpos;
				attr->m_typePos.y = ypos;
				ypos += META_DECORATOR_GAPY;
			}


			if (m_shape == CLASSPROXY && m_bitmap->isInitialized()) {
				ypos += META_DECORATOR_MARGINY;
				m_proxySignPos.x = xleftpos;
				m_proxySignPos.y = ypos;
				ypos += m_bitmap->getHeight();
			}
			else if (m_attrs.GetCount() ==0) {
				ypos += META_DECORATOR_MINATTRSIZE;
			}
			m_calcSize.cx = xrightpos + META_DECORATOR_MARGINX;
			m_calcSize.cy = ypos + META_DECORATOR_MARGINY;
		}
		break;
	default:
		m_calcSize.cx = m_calcSize.cy = 0;
	}	
}

void CDecorator::SetupClass()
{
	int i = 0;
	bool bRealFco = false;
	while(fcos[i]) {
		if (m_stereotype == fcos[i]) {
			bRealFco = true;
			break;
		}
		i++;
	}
	if (!bRealFco) {
		return;
	}

	if (m_showAbstract || m_showAttributes) {
		CComPtr<IMgaFCOs> coll;
		try {
			// Collect proxies & the real class
			CComPtr<IMgaReference> ref;
			CComPtr<IMgaFCO> real;
			if (SUCCEEDED(m_mgaFco.QueryInterface(&ref))) {
				COMTHROW(ref->get_Referred(&real));
				if (!real) {
					COMTHROW(coll.CoCreateInstance(OLESTR("Mga.MgaFCOs")));
					COMTHROW(coll->Append(m_mgaFco));
				}
			}
			else {
				real = m_mgaFco;
			}
			if (real) {
				COMTHROW(real->get_ReferencedBy(&coll));
				COMTHROW(coll->Append(real));
			}

			CComPtr<IMgaFCO> fco;
			MGACOLL_ITERATE(IMgaFCO,coll) {
				fco = MGACOLL_ITER;
				// Figure out isAbstract
				if (m_showAbstract) {
					bool isAbstract;
					if (DecoratorSDK::getFacilities().getAttribute(fco ? fco : m_mgaFco, META_ABSTRACT_ATTR, isAbstract) && isAbstract) {
						m_isAbstract = true;
					}
				}
				// Collect attributes
				if (m_showAttributes) {
					CollectAttributes(fco);
					SortAttributes();
				}
			} MGACOLL_ITERATE_END;
		}
		catch (hresult_exception &) {
			m_isAbstract = false;
			m_attrs.RemoveAll();
		}
	}
}

void CDecorator::CollectAttributes(const CComPtr<IMgaFCO> &fco)
{
	CComPtr<IMgaConnPoints>	connPoints;
	COMTHROW(fco->get_PartOfConns(&connPoints));
	CComPtr<IMgaConnPoint> connPoint;
	MGACOLL_ITERATE(IMgaConnPoint,connPoints) {
		connPoint = MGACOLL_ITER;

		CComPtr<IMgaConnection> conn;
		COMTHROW(connPoint->get_Owner(&conn));
		CComPtr<IMgaConnPoints>	targetConnPoints;

		COMTHROW(conn->get_ConnPoints(&targetConnPoints));
		CComPtr<IMgaConnPoint> targetConnPoint;
		MGACOLL_ITERATE(IMgaConnPoint,targetConnPoints) {
			targetConnPoint = MGACOLL_ITER;
			if (!connPoint.IsEqualObject(targetConnPoint)) {
				CComPtr<IMgaFCO> targetFco;
				COMTHROW(targetConnPoint->get_Target(&targetFco));
				CComPtr<IMgaMetaFCO>	targetMetaFco;
				COMTHROW(targetFco->get_Meta(&targetMetaFco));
				CComBSTR bstr;
				COMTHROW(targetMetaFco->get_Name(&bstr));
				
				CComBSTR attrPosBstr; // zolmol added: sort by [y, x]
				COMTHROW(targetFco->get_RegistryValue( L"PartRegs/Attributes/Position", &attrPosBstr));
				CString attr_pos = attrPosBstr;
				CPoint pos( 0, 0);
				int res = sscanf( (LPCTSTR)attr_pos, "%d,%d", &pos.x, &pos.y);
				if( res != 2) { pos = CPoint( 0, 0);}
				
				CString targetKind = bstr;
				if (targetKind == META_BOOLEANATTR_KIND) {
					CComBSTR nameBstr;
					COMTHROW(targetFco->get_Name(&nameBstr));
					CString targetName = nameBstr;
					m_attrs.AddTail(new CMetaAttr(targetName, META_BOOLEANATTR_LABEL, pos));
				}
				if (targetKind == META_ENUMATTR_KIND) {
					CComBSTR nameBstr;
					COMTHROW(targetFco->get_Name(&nameBstr));
					CString targetName = nameBstr;
					m_attrs.AddTail(new CMetaAttr(targetName, META_ENUMATTR_LABEL, pos));
				}
				if (targetKind == META_FIELDATTR_KIND) {
					CComBSTR nameBstr;
					COMTHROW(targetFco->get_Name(&nameBstr));
					CString targetName = nameBstr;
					m_attrs.AddTail(new CMetaAttr(targetName, META_FIELDATTR_LABEL, pos));
				}
			}
		} MGACOLL_ITERATE_END;

	} MGACOLL_ITERATE_END;
}

// Bubble-sort
void CDecorator::SortAttributes() {
	if (m_attrs.GetCount() < 2) {
		return;
	}

	POSITION ipos = m_attrs.GetTailPosition();
	//m_attrs.GetPrev(ipos); //ZolMol: iPos already points to last element if any
	while (ipos) {
		POSITION jpos = m_attrs.GetHeadPosition();
		while (jpos != ipos) {
			POSITION jnpos = jpos;
			CMetaAttr *jattr = m_attrs.GetNext(jnpos);
			CMetaAttr *jnattr = m_attrs.GetAt(jnpos);
			if( jattr->m_boxPos.y > jnattr->m_boxPos.y || jattr->m_boxPos.y == jnattr->m_boxPos.y && jattr->m_boxPos.x > jnattr->m_boxPos.x) {
				m_attrs.SetAt(jpos, jnattr);
				m_attrs.SetAt(jnpos, jattr);
			}
			m_attrs.GetNext(jpos);
		}
		m_attrs.GetPrev(ipos);
	}
}
