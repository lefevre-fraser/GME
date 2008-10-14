// UMLDecorator.cpp : Implementation of CUMLDecorator
//
// 12/06/2002 - modified by Ed Willink, Thales Research and Technology (abstract classes)
//
#include "stdafx.h"
#define __Meta_h__
#define __Mga_h__
#include "UMLDecoratorLib.h"
#include "UMLDecorator.h"
#include "BitmapUtil.h"
#include "DecoratorStd.h"
#include "TokenEx.h"

static long stereotypeCharacterType = 1;

#define VERIFY_INIT   { if (!m_isInitialized) return E_DECORATOR_UNINITIALIZED; }
#define VERIFY_LOCSET { if (!m_isLocSet) return E_DECORATOR_LOCISNOTSET; }


/////////////////////////////////////////////////////////////////////////////
// CUMLDecorator
STDMETHODIMP CUMLDecorator::Initialize(IMgaProject *project, IMgaMetaPart *metaPart, IMgaFCO *obj)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

	COMTRY {
		DecoratorSDK::getFacilities().getMetaFCO(metaPart, m_metaFco);
		m_mgaFco = obj;		// obj == NULL, if we are in the PartBrowser
		
		if (!m_metaFco) {
			return E_DECORATOR_INIT_WITH_NULL;
		}
		else {
			m_isInitialized = true;
		}	
		
		if (SetupInheritance()) {
			if (!DecoratorSDK::getFacilities().getPreference(m_mgaFco, m_metaFco, COLOR_PREF, m_color)) {
				m_color = GME_BLACK_COLOR;
			}
			m_name = UML_INHERITANCE_NAME;
			return S_OK;
		}

		if (SetupConstraint()) {
			if (m_mgaFco) {
				CComBSTR bstr;
				COMTHROW(m_mgaFco->get_Name(&bstr));
				m_name = bstr;
			}
			else {
				m_name = UML_CONSTRAINT_NAME;
			}
			return S_OK;
		}

		if (SetupConstraintDefinition()) {
			if (m_mgaFco) {
				CComBSTR bstr;
				COMTHROW(m_mgaFco->get_Name(&bstr));
				m_name = bstr;
			}
			else {
				m_name = UML_CONSTRAINT_DEFINITION_NAME;
			}
			return S_OK;
		}

		if (SetupConnector()) {
			if (!DecoratorSDK::getFacilities().getPreference(m_mgaFco, m_metaFco, COLOR_PREF, m_color)) {
				m_color = GME_BLACK_COLOR;
			}
			m_name = UML_CONNECTOR_NAME;
			return S_OK;
		}

		if (m_mgaFco) {
			objtype_enum	objtype;
			COMTHROW(m_mgaFco->get_ObjType(&objtype));
			if (objtype == OBJTYPE_REFERENCE) {
				m_copyBitmap = DecoratorSDK::getFacilities().getMaskedBitmap(IDB_BITMAP_COPY, UML_TRANSPARENT_COLOR, GME_GRAYED_OUT_COLOR);
				m_isCopy = true;
				CComPtr<IMgaFCO> mgaFco = m_mgaFco;
				while(objtype == OBJTYPE_REFERENCE) {
					CComPtr<IMgaReference> ref;
					COMTHROW(mgaFco.QueryInterface(&ref));
					mgaFco = NULL;
					COMTHROW(ref->get_Referred(&mgaFco));
					if (mgaFco) {
						COMTHROW(mgaFco->get_ObjType(&objtype));
					}
					else {
						objtype = OBJTYPE_NULL;
					}
				}
				if (objtype == OBJTYPE_NULL) {
					m_stereotype.Empty();
					m_attrs.RemoveAll();
				}
				else {
					if (!DecoratorSDK::getFacilities().getAttribute(mgaFco ? mgaFco : m_mgaFco, UML_STEREOTYPE_ATTR, m_stereotype)) {
						m_stereotype.Empty();
					}
					bool isAbstract;
					if (DecoratorSDK::getFacilities().getAttribute(mgaFco ? mgaFco : m_mgaFco, UML_ABSTRACT_ATTR, isAbstract) && isAbstract) {
						m_isAbstract = true;
					}
					CollectAttributes(mgaFco);
				}
			}
			else {
				m_isCopy = false;
				if (!DecoratorSDK::getFacilities().getAttribute(m_mgaFco, UML_STEREOTYPE_ATTR, m_stereotype)) {
					m_stereotype.Empty();
				}
				bool isAbstract;
				if (DecoratorSDK::getFacilities().getAttribute(m_mgaFco, UML_ABSTRACT_ATTR, isAbstract) && isAbstract) {
					m_isAbstract = true;
				}
				CollectAttributes();
			}
			CComBSTR bstr;
			COMTHROW(m_mgaFco->get_Name(&bstr));
			m_name = bstr;
		}
		else {
			objtype_enum objtype;
			COMTHROW(m_metaFco->get_ObjType(&objtype));
			if (objtype == OBJTYPE_REFERENCE) {
				m_copyBitmap = DecoratorSDK::getFacilities().getMaskedBitmap(IDB_BITMAP_COPY, UML_TRANSPARENT_COLOR, GME_GRAYED_OUT_COLOR);
				m_isCopy = true;
			}
			else {
				m_isCopy = false;
			}
			m_stereotype.Empty();
			CComBSTR bstr;
			COMTHROW(m_metaFco->get_DisplayedName(&bstr));
			if (bstr.Length() == 0 ) {
				bstr.Empty();
				COMTHROW(m_metaFco->get_Name(&bstr));
			}
			m_name = bstr;
		}

		if (!DecoratorSDK::getFacilities().getPreference(m_mgaFco, m_metaFco, COLOR_PREF, m_color)) {
			m_color = GME_BLACK_COLOR;
		}
		if (!DecoratorSDK::getFacilities().getPreference(m_mgaFco, m_metaFco, NAME_COLOR_PREF, m_nameColor)) {
			m_nameColor = GME_BLACK_COLOR;
		}
		CalcRelPositions();
	} COMCATCH(;);

	return S_OK;
}

STDMETHODIMP CUMLDecorator::Destroy()
{
	VERIFY_INIT;
	m_isInitialized = false;
	m_isLocSet = false;
	m_metaFco = NULL; m_mgaFco = NULL;
	return S_OK;
}

STDMETHODIMP CUMLDecorator::GetMnemonic(BSTR *mnemonic)
{	
	*mnemonic = CComBSTR("UML").Detach();
	return S_OK;
}

STDMETHODIMP CUMLDecorator::GetFeatures(feature_code *features)
{	
	*features = F_RESIZABLE | F_HASLABEL;
	return S_OK;
}

STDMETHODIMP CUMLDecorator::SetParam(BSTR name, VARIANT value)
{
	// VERIFY_INIT;
	return E_DECORATOR_UNKNOWN_PARAMETER;
}

STDMETHODIMP CUMLDecorator::GetParam(BSTR name, VARIANT* value)
{
	// VERIFY_INIT;
	return E_DECORATOR_UNKNOWN_PARAMETER;
}

STDMETHODIMP CUMLDecorator::SetActive(VARIANT_BOOL isActive)
{
	VERIFY_INIT;
	m_isActive = (isActive != VARIANT_FALSE);
	return S_OK;
}

STDMETHODIMP CUMLDecorator::GetPreferredSize(long* sizex, long* sizey) 
{
	VERIFY_INIT;
	*sizex = m_calcSize.cx;
	*sizey = m_calcSize.cy;
	return S_OK;
}


STDMETHODIMP CUMLDecorator::SetLocation(long sx, long sy, long ex, long ey)
{
	VERIFY_INIT;
	m_sx = sx;
	m_sy = sy;
	m_ex = ex;
	m_ey = ey;
	m_isLocSet = true;
	return S_OK;
}

STDMETHODIMP CUMLDecorator::GetLocation(long *sx, long *sy, long *ex, long *ey)
{
	VERIFY_INIT;
	VERIFY_LOCSET;
	*sx = m_sx;
	*sy = m_sy;
	*ex = m_ex;
	*ey = m_ey;
	return S_OK;
}

STDMETHODIMP CUMLDecorator::GetLabelLocation(long *sx, long *sy, long *ex, long *ey)
{
	VERIFY_INIT;
	VERIFY_LOCSET;

// TODO !!!
	*sx = 0;
	*sy = 0;
	*ex = 0;
	*ey = 0;
	return S_OK;
}

STDMETHODIMP CUMLDecorator::GetPortLocation(IMgaFCO *fco, long *sx, long *sy, long *ex, long *ey)
{
	VERIFY_INIT;
	VERIFY_LOCSET;

	return E_DECORATOR_PORTNOTFOUND;
}

STDMETHODIMP CUMLDecorator::GetPorts(IMgaFCOs **portFCOs)
{
	VERIFY_INIT;
	COMTRY {
		CComPtr<IMgaFCOs> coll;
		COMTHROW(coll.CoCreateInstance(OLESTR("Mga.MgaFCOs")));
		*portFCOs = coll.Detach();
	} COMCATCH(;);
	return S_OK;
}


STDMETHODIMP CUMLDecorator::Draw(HDC hdc)
{
	VERIFY_INIT;
	VERIFY_LOCSET;

	CDC dc;
	dc.Attach(hdc);
	if (dc.IsPrinting() && (!m_isInheritance) && (!m_isConstraint) && (!m_isConnector) && (!m_isConstraintDefinition) ) {
		CalcRelPositions(&dc);
	}
	double scalex = ((double)(m_ex - m_sx)) / (m_calcSize.cx);
	double scaley = ((double)(m_ey - m_sy)) / (m_calcSize.cy);

	if (m_isInheritance) {
		dc.SelectObject(DecoratorSDK::getFacilities().getPen(m_isActive ? m_color : GME_GRAYED_OUT_COLOR));
		dc.SelectStockObject(NULL_BRUSH);
		dc.BeginPath();
		dc.MoveTo(m_sx, m_ey);
		dc.LineTo(m_ex, m_ey);
		dc.LineTo(m_sx + (m_ex-m_sx)/2, m_sy);
		dc.LineTo(m_sx, m_ey);
		dc.EndPath();
		dc.StrokeAndFillPath();
		if (!m_mgaFco) {
			CPoint namePos(m_sx + ((m_ex - m_sx) / 2), m_ey);
			DecoratorSDK::getFacilities().drawText(&dc,
													m_name,
													namePos,
													DecoratorSDK::getFacilities().getFont(DecoratorSDK::FONT_PORTNAME)->pFont,
													(m_isActive ? m_color : GME_GRAYED_OUT_COLOR),
													TA_TOP | TA_CENTER);
		}
		dc.Detach();
		return S_OK;
	}

	if (m_isConnector) {
		dc.SelectObject(DecoratorSDK::getFacilities().getPen(m_isActive ? m_color : GME_GRAYED_OUT_COLOR));
		dc.SelectObject(DecoratorSDK::getFacilities().getBrush(m_isActive ? m_color : GME_GRAYED_OUT_COLOR));
		dc.Ellipse(m_sx, m_sy, m_ex, m_ey);
		if (!m_mgaFco) {
			CPoint namePos(m_sx + ((m_ex - m_sx) / 2), m_ey);
			DecoratorSDK::getFacilities().drawText(&dc,
													m_name,
													namePos,
													DecoratorSDK::getFacilities().getFont(DecoratorSDK::FONT_PORTNAME)->pFont,
													(m_isActive ? m_color : GME_GRAYED_OUT_COLOR),
													TA_TOP | TA_CENTER);
		}
		dc.Detach();
		return S_OK;
	}

	if (m_isConstraint && m_constraintBitmap->isInitialized()) {
		CRect destRect(m_sx, m_sy, m_sx + m_constraintBitmap->getWidth(), m_sy + m_constraintBitmap->getHeight());
		UINT modifFlags = DecoratorSDK::MF_TRANSPARENT;
		if (!m_isActive)
			modifFlags |= DecoratorSDK::MF_GREYED;
		m_constraintBitmap->draw(&dc, CRect(), destRect, SRCCOPY, modifFlags);

		CPoint namePos(m_sx + ((m_ex - m_sx) / 2), m_ey);
		DecoratorSDK::getFacilities().drawText(&dc,
												m_name,
												namePos,
												DecoratorSDK::getFacilities().getFont(DecoratorSDK::FONT_PORTNAME)->pFont,
												(m_isActive ? m_color : GME_GRAYED_OUT_COLOR),
												TA_TOP | TA_CENTER);
		dc.Detach();
		return S_OK;
	}

	if (m_isConstraintDefinition && m_constraintDefBitmap->isInitialized()) {
		CRect destRect(m_sx, m_sy, m_sx + m_constraintDefBitmap->getWidth(), m_sy + m_constraintDefBitmap->getHeight());
		UINT modifFlags = DecoratorSDK::MF_TRANSPARENT;
		if (!m_isActive)
			modifFlags |= DecoratorSDK::MF_GREYED;
		m_constraintDefBitmap->draw(&dc, CRect(), destRect, SRCCOPY, modifFlags);

		CPoint namePos(m_sx + ((m_ex - m_sx) / 2), m_ey);
		DecoratorSDK::getFacilities().drawText(&dc,
												m_name,
												namePos,
												DecoratorSDK::getFacilities().getFont(DecoratorSDK::FONT_PORTNAME)->pFont,
												(m_isActive ? m_color : GME_GRAYED_OUT_COLOR),
												TA_TOP | TA_CENTER);
		dc.Detach();
		return S_OK;
	}

	// Draw lines
	dc.SelectObject(DecoratorSDK::getFacilities().getPen(m_isActive ? m_color : GME_GRAYED_OUT_COLOR));
	dc.SelectStockObject(NULL_BRUSH);
	dc.Rectangle(m_sx, m_sy, m_ex, m_ey);
	dc.MoveTo(static_cast<long> (m_sx + scalex * m_sepLoc.left), static_cast<long> (m_sy + scaley * m_sepLoc.top));
	dc.LineTo(static_cast<long> (m_sx + scalex * m_sepLoc.right), static_cast<long> (m_sy + scaley * m_sepLoc.bottom));

	// Draw labels
	CPoint namePos(static_cast<long> (m_sx + scalex * m_namePos.x), static_cast<long> (m_sy + scaley * m_namePos.y));
	DecoratorSDK::getFacilities().drawText(&dc,
											m_name,
											namePos,
											DecoratorSDK::getFacilities().getFont(m_isAbstract ? DecoratorSDK::FONT_ABSTRACT: DecoratorSDK::FONT_PORTNAME)->pFont,
											(m_isActive ? m_nameColor : GME_GRAYED_OUT_COLOR),
											TA_BOTTOM | TA_CENTER);
	if (!m_stereotype.IsEmpty()) {
		CPoint stereotypePos(static_cast<long> (m_sx + scalex * m_stereotypePos.x), static_cast<long> (m_sy + scaley * m_stereotypePos.y));
		DecoratorSDK::getFacilities().drawText(&dc,
												(stereotypeCharacterType ? UML_STEREOTYPE_LEFTB : UML_STEREOTYPE_LEFTA) + m_stereotype + (stereotypeCharacterType ? UML_STEREOTYPE_RIGHTB : UML_STEREOTYPE_RIGHTA),
												stereotypePos,
												DecoratorSDK::getFacilities().getFont(DecoratorSDK::FONT_PORTNAME)->pFont,
												(m_isActive ? m_nameColor : GME_GREY_COLOR),
												TA_BOTTOM | TA_CENTER);
	}
	
	POSITION pos = m_attrs.GetHeadPosition();
	while (pos) {
		CUMLAttr *attr = m_attrs.GetNext(pos);
		CPoint anamePos(static_cast<long> (m_sx + scalex * attr->m_namePos.x), static_cast<long> (m_sy + scaley * attr->m_namePos.y));
		DecoratorSDK::getFacilities().drawText(&dc,
												attr->m_name + UML_ATTRIBUTE_SEP,
												anamePos,
												DecoratorSDK::getFacilities().getFont(DecoratorSDK::FONT_PORTNAME)->pFont,
												(m_isActive ? (m_isCopy ? UML_GREY_COLOR : m_nameColor) : GME_GRAYED_OUT_COLOR),
												TA_BOTTOM | TA_LEFT);
		CPoint typePos(static_cast<long> (m_sx + scalex * attr->m_typePos.x), static_cast<long> (m_sy + scaley * attr->m_typePos.y));
		DecoratorSDK::getFacilities().drawText(&dc,
												attr->m_type,
												typePos,
												DecoratorSDK::getFacilities().getFont(DecoratorSDK::FONT_PORTNAME)->pFont,
												(m_isActive ? (m_isCopy ? UML_GREY_COLOR : m_nameColor) : GME_GRAYED_OUT_COLOR),
												TA_BOTTOM | TA_RIGHT);

	}

	// Draw Copy Sign
	if (m_isCopy && m_copyBitmap->isInitialized()) {
		CPoint cpt = m_copySignPos;
		cpt.x = static_cast<long> (m_sx + scalex * m_copySignPos.x);
		cpt.y = static_cast<long> (m_sy + scaley * m_copySignPos.y);
		CRect destRect(cpt.x, cpt.y, cpt.x + m_copyBitmap->getWidth(), cpt.y + m_copyBitmap->getHeight());
		UINT modifFlags = DecoratorSDK::MF_TRANSPARENT;
		if (!m_isActive)
			modifFlags |= DecoratorSDK::MF_GREYED;
		m_copyBitmap->draw(&dc, CRect(), destRect, SRCCOPY, modifFlags);
	}

	dc.Detach();
	return S_OK;
}

STDMETHODIMP CUMLDecorator::SaveState()
{
	VERIFY_INIT;
	return S_OK;
}


//////////// UMLDecorator private functions
CUMLDecorator::CUMLDecorator() : m_sx(0), m_sy(0), m_ex(0), m_ey(0), 
	m_isActive(true), m_mgaFco(0), m_metaFco(0), m_isCopy(false), 
	m_isInheritance(false), m_isConstraint(false), m_isConnector(false), m_isConstraintDefinition( false ),
	m_isInitialized(false), m_isLocSet(false), m_isAbstract(false),
	m_namePos(DWORD(0)), m_stereotypePos(DWORD(0)), m_calcSize(DWORD(0)), 
	m_copySignPos(DWORD(0)), m_sepLoc(0,0,0,0),
	m_color(GME_BLACK_COLOR), m_nameColor(GME_BLACK_COLOR)
{
}

CUMLDecorator::~CUMLDecorator()
{
	POSITION pos = m_attrs.GetHeadPosition();
	while (pos) {
		delete m_attrs.GetNext(pos);
	}
	m_attrs.RemoveAll();
}


void CUMLDecorator::CalcRelPositions(CDC *pDC)
{
	int maxHeight = 0, maxWidth = 0;
	CSize ext;
	CDC	dc;
	
	dc.Attach(pDC ? pDC->m_hDC : GetDC(NULL));			// Trick
	CFont *oldfont = dc.SelectObject(DecoratorSDK::getFacilities().getFont(DecoratorSDK::FONT_PORTNAME)->pFont);
	
	ext = dc.GetTextExtent(m_name);
	maxWidth = max(maxWidth, ext.cx);
	maxHeight = max(maxHeight, ext.cy);

	if (!m_stereotype.IsEmpty()) {
		ext = dc.GetTextExtent((stereotypeCharacterType ? UML_STEREOTYPE_LEFTB : UML_STEREOTYPE_LEFTA) + m_stereotype + (stereotypeCharacterType ? UML_STEREOTYPE_RIGHTB : UML_STEREOTYPE_RIGHTA));
		maxWidth = max(maxWidth, ext.cx);
		maxHeight = max(maxHeight, ext.cy);
	}

	POSITION pos = m_attrs.GetHeadPosition();
	while (pos) {
		CUMLAttr *attr = m_attrs.GetNext(pos);

		ext = dc.GetTextExtent(attr->m_name + UML_ATTRIBUTE_SEP + attr->m_type);
		maxWidth = max(maxWidth, ext.cx);
		maxHeight = max(maxHeight, ext.cy);
	}

	int xcenterpos = (2 * UML_DECORATOR_MARGINX + maxWidth) / 2; 
	int	xleftpos = UML_DECORATOR_MARGINX;
	int	xrightpos = UML_DECORATOR_MARGINX + maxWidth;
	int ypos = UML_DECORATOR_MARGINY;

	m_namePos.x = xcenterpos;
	m_namePos.y = (ypos +=maxHeight);

	if (!m_stereotype.IsEmpty()) {
		ypos += UML_DECORATOR_GAPY;

		m_stereotypePos.x = xcenterpos;
		m_stereotypePos.y = (ypos += maxHeight);
	}
	
	ypos += UML_DECORATOR_MARGINY;
	m_sepLoc.left = 0;
	m_sepLoc.top = m_sepLoc.bottom = ypos;
	m_sepLoc.right = xrightpos + UML_DECORATOR_MARGINX -1;

	ypos += UML_DECORATOR_MARGINY;

	pos = m_attrs.GetHeadPosition();
	while (pos) {
		CUMLAttr *attr = m_attrs.GetNext(pos);
		attr->m_namePos.x = xleftpos;
		attr->m_namePos.y = (ypos += maxHeight);
		attr->m_typePos.x = xrightpos;
		attr->m_typePos.y = ypos;
		ypos += UML_DECORATOR_GAPY;
	}

	if (m_isCopy && m_copyBitmap->isInitialized()) {
		ypos += UML_DECORATOR_MARGINY;
		m_copySignPos.x = xleftpos;
		m_copySignPos.y = ypos;
		ypos += m_copyBitmap->getHeight();
	}
	else if (m_attrs.GetCount() == 0){
		ypos += UML_DECORATOR_MINATTRSIZE;
	}
	m_calcSize.cx = xrightpos + UML_DECORATOR_MARGINX;
	m_calcSize.cy = ypos + UML_DECORATOR_MARGINY;
	if (pDC) {
		dc.SelectObject(oldfont);
		dc.Detach();
	}
}

void CUMLDecorator::CollectAttributes(CComPtr<IMgaFCO> mgaFco)
{
	if (!mgaFco) {
		mgaFco = m_mgaFco;
	}
	CString attrStr;
	if (DecoratorSDK::getFacilities().getAttribute(mgaFco, UML_ATTRIBUTES_ATTR, attrStr)) {
		CStringArray	attrPairs;
		CTokenEx		tok;
		tok.Split(attrStr, "\n", attrPairs);
		for (int i = 0; i < attrPairs.GetSize(); i++) {
			CStringArray attrPair;
			tok.Split(attrPairs[i], ":", attrPair);
			if (attrPair.GetSize() == 1) {
				attrPair.Add("unknown");
			}
			if (attrPair.GetSize() == 2) {
				attrPair[0].TrimLeft();
				attrPair[0].TrimRight();
				attrPair[1].TrimLeft();
				attrPair[1].TrimRight();
				CUMLAttr *attr = new CUMLAttr(attrPair[0], attrPair[1]);
				m_attrs.AddTail(attr);
			}
		}
	}
}

bool CUMLDecorator::SetupInheritance()
{
	ASSERT(m_metaFco);
	CComBSTR	bstr;
	try {
		COMTHROW(m_metaFco->get_Name(&bstr));
		CString name(bstr);
		if (name == UML_INHERITANCE_NAME) {
			m_isInheritance = true;
			m_calcSize.cx = static_cast<long> (UML_INHERITANCE_WIDTH);
			m_calcSize.cy = static_cast<long> (UML_INHERITANCE_HEIGHT);
			return true;
		}
	}
	catch (hresult_exception &) {
	}
	return false;
}

bool CUMLDecorator::SetupConstraint()
{
	ASSERT(m_metaFco);
	CComBSTR	bstr;
	try {
		COMTHROW(m_metaFco->get_Name(&bstr));
		CString name(bstr);
		if (name == UML_CONSTRAINT_NAME) {
			m_isConstraint = true;
			m_constraintBitmap = DecoratorSDK::getFacilities().getMaskedBitmap(IDB_BITMAP_CONSTRAINT, UML_TRANSPARENT_COLOR, GME_GRAYED_OUT_COLOR);
			if (m_constraintBitmap->isInitialized()) {
				m_calcSize.cx = m_constraintBitmap->getWidth();
				m_calcSize.cy = m_constraintBitmap->getHeight();
				return true;
			}
		}
	}
	catch (hresult_exception &) {
	}
	return false;
}

bool CUMLDecorator::SetupConstraintDefinition()
{
	ASSERT(m_metaFco);
	CComBSTR	bstr;
	try {
		COMTHROW(m_metaFco->get_Name(&bstr));
		CString name(bstr);
		if (name == UML_CONSTRAINT_DEFINITION_NAME) {
			m_isConstraintDefinition = true;
			m_constraintDefBitmap = DecoratorSDK::getFacilities().getMaskedBitmap(IDB_BITMAP_CDEFINITION, UML_TRANSPARENT_COLOR, GME_GRAYED_OUT_COLOR);
			if (m_constraintDefBitmap->isInitialized()) {
				m_calcSize.cx = m_constraintDefBitmap->getWidth();
				m_calcSize.cy = m_constraintDefBitmap->getHeight();
				return true;
			}
		}
	}
	catch (hresult_exception &) {
	}
	return false;
}

bool CUMLDecorator::SetupConnector()
{
	ASSERT(m_metaFco);
	CComBSTR	bstr;
	try {
		COMTHROW(m_metaFco->get_Name(&bstr));
		CString name(bstr);
		if (name == UML_CONNECTOR_NAME) {
			m_isConnector = true;
			m_calcSize.cx = UML_CONNECTOR_WIDTH;
			m_calcSize.cy = UML_CONNECTOR_HEIGHT;
			return true;
		}
	}
	catch (hresult_exception &) {
	}
	return false;
}
