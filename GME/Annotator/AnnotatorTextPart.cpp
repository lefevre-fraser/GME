//################################################################################################
//
// Annotator text part class
//	AnnotatorTextPart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "AnnotatorTextPart.h"
#include "..\MgaUtil\AnnotationUtil.h"
#include "DecoratorExceptions.h"


namespace AnnotatorDecor {

//################################################################################################
//
// CLASS : AnnotatorTextPart
//
//################################################################################################

AnnotatorTextPart::AnnotatorTextPart(DecoratorSDK::PartBase* pPart, CComPtr<IMgaNewDecoratorEvents>& eventSink):
	TextPart		(pPart, eventSink),
	m_regRoot		(NULL),
	m_crBgColor		(AN_DEFAULT_BGCOLOR)
{
	m_crText					= AN_DEFAULT_COLOR;
	m_crShadow					= AN_DEFAULT_SHADOWCOLOR;
	m_crGradient				= AN_DEFAULT_GRADIENTCOLOR;
	memset(&m_logFont, 0, sizeof(LOGFONT));

	textStringVariableName		= "";	// disable
	textColorVariableName		= "";	// disable
	textMaxLengthVariableName	= DecoratorSDK::PREF_LABELLENGTH;
}

AnnotatorTextPart::~AnnotatorTextPart()
{
}

void AnnotatorTextPart::SetParam(const CString& strName, VARIANT vValue)
{
	if (!strName.CompareNoCase(AN_PARAM_ROOTNODE)) {
		CComVariant	variantval(vValue);
		try {
			if (!m_regRoot) {
				COMTHROW(variantval.ChangeType(VT_UNKNOWN));
				CComPtr<IUnknown> unk(variantval.punkVal);
				COMTHROW(unk.QueryInterface(&m_regRoot));
			}
			ReadPreferences();
		}
		catch (hresult_exception&) {
			throw DecoratorException((DecoratorExceptionCode)E_DECORATOR_UNKNOWN_PARAMETER);
		}
	} else {
		throw DecoratorException((DecoratorExceptionCode)E_DECORATOR_UNKNOWN_PARAMETER);
	}
}

bool AnnotatorTextPart::GetParam(const CString& strName, VARIANT* pvValue)
{
	if (!strName.CompareNoCase(AN_PARAM_ROOTNODE)) {
		CComVariant	variantval;
		variantval.Attach(pvValue);
		variantval = m_regRoot;
	} else {
		throw DecoratorException((DecoratorExceptionCode)E_DECORATOR_UNKNOWN_PARAMETER);
	}
	return true;
}

CSize AnnotatorTextPart::GetPreferredSize(void) const
{
	CDC	dc;
	dc.CreateCompatibleDC(NULL);
	Gdiplus::Graphics* gdip = new Gdiplus::Graphics(dc.m_hDC);
	gdip->SetPageUnit(Gdiplus::UnitPixel);
	gdip->SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
	gdip->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);

	Gdiplus::Font myFont(dc.m_hDC, &m_logFont);
	CSize size = DecoratorSDK::getFacilities().MeasureText(gdip, &myFont, m_strText);
	size.cx += 2 * AN_MARGIN;
	size.cy += 2 * AN_MARGIN;
	return size;
}

void AnnotatorTextPart::Draw(CDC* pDC, Gdiplus::Graphics* gdip)
{
	if (m_bTextEnabled) {
		CRect loc = GetLocation();
		loc.InflateRect(-AN_MARGIN, -AN_MARGIN, 0, 0);
		Gdiplus::Font myFont(pDC->m_hDC, &m_logFont);
		DecoratorSDK::getFacilities().DrawString(gdip,
												 m_strText,
												 CRect(loc.left, loc.top, loc.right, loc.bottom),
												 &myFont,
												 (m_bActive) ? m_crText : GME_GRAYED_OUT_COLOR,
												 TA_LEFT | TA_TOP,
												 m_iMaxTextLength,
												 "",
												 "",
												 false);
	}
	if (m_spFCO)
		resizeLogic.Draw(pDC, gdip);
}

// New functions
void AnnotatorTextPart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
									 HWND parentWnd, DecoratorSDK::PreferenceMap& preferences)
{
	preferences[DecoratorSDK::PREF_FILLCOLOR]			= DecoratorSDK::PreferenceVariant(m_crBgColor);
	preferences[DecoratorSDK::PREF_SHADOWCOLOR]			= DecoratorSDK::PreferenceVariant(m_crShadow);
	preferences[DecoratorSDK::PREF_GRADIENTCOLOR]		= DecoratorSDK::PreferenceVariant(m_crGradient);
	preferences[DecoratorSDK::PREF_ITEMGRADIENTFILL]	= DecoratorSDK::PreferenceVariant(m_bGradientFill);
	preferences[DecoratorSDK::PREF_GRADIENTDIRECTION]	= DecoratorSDK::PreferenceVariant(m_iGradientDirection);
	preferences[DecoratorSDK::PREF_ITEMSHADOWCAST]		= DecoratorSDK::PreferenceVariant(m_bCastShadow);
	preferences[DecoratorSDK::PREF_SHADOWTHICKNESS]		= DecoratorSDK::PreferenceVariant(m_iShadowDepth);
	preferences[DecoratorSDK::PREF_SHADOWDIRECTION]		= DecoratorSDK::PreferenceVariant(m_iShadowDirection);
	preferences[DecoratorSDK::PREF_ROUNDCORNERRECT]		= DecoratorSDK::PreferenceVariant(m_bRoundCornerRect);
	preferences[DecoratorSDK::PREF_ROUNDCORNERRADIUS]	= DecoratorSDK::PreferenceVariant(m_iRoundCornerRadius);

	preferences[DecoratorSDK::PREF_LABELLENGTH]			= DecoratorSDK::PreferenceVariant((long)-1);
	preferences[DecoratorSDK::PREF_TEXTOVERRIDE]		= DecoratorSDK::PreferenceVariant(true);
	preferences[DecoratorSDK::PREF_TEXTCOLOROVERRIDE]	= DecoratorSDK::PreferenceVariant(true);
	preferences[DecoratorSDK::PREF_MULTILINEINPLACEEDIT]= DecoratorSDK::PreferenceVariant(true);
	TextPart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);
}

CPoint AnnotatorTextPart::GetTextPosition(CDC* pDC, Gdiplus::Graphics* gdip) const
{
	return GetTextLocation(pDC, gdip).TopLeft();
}

CRect AnnotatorTextPart::GetTextLocation(CDC* pDC, Gdiplus::Graphics* gdip) const
{
	return GetLocation();
}

void AnnotatorTextPart::ExecuteOperation(const CString& newString)
{
	// transaction operation begin
	try {
		m_strText = newString;
		CString strText = newString;
		m_strText.Replace("\r\n", "\n");
		CComBSTR bstr;
		CopyTo(strText, bstr);
		COMTHROW(m_regRoot->put_Value(bstr));
	}
	catch (hresult_exception&) {
//		m_strText = "Unable to write annotation!";
	}
	// transaction operation end
}

void AnnotatorTextPart::ReadPreferences(void)
{
	try {
		CComBSTR bstr;
		COMTHROW(m_regRoot->get_Value(&bstr));
		m_strText = bstr;
		m_strText.Replace("\n", "\r\n");
	}
	catch (hresult_exception&) {
		m_strText = "Unable to read annotation !";
	}

	try {
		CComBSTR bstr;
		COMTHROW(m_regRoot->get_Name(&bstr));
		m_strName = bstr;
	}
	catch (hresult_exception&) {
		m_strName = "Unknown";
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
		if (!CAnnotationUtil::LogfontDecode(str, &m_logFont)) {
			// throw hresult_exception();
			CAnnotationUtil::FillLogFontWithDefault(&m_logFont);
		}
	}
	catch (hresult_exception&) {
		CAnnotationUtil::FillLogFontWithDefault(&m_logFont);
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
			m_crText = RGB(r,g,b);
		} else {
			throw hresult_exception();
		}
	}
	catch (hresult_exception&) {
		m_crText = AN_DEFAULT_COLOR;
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
			m_crBgColor = RGB(r,g,b);
		} else {
			m_crBgColor = AN_DEFAULT_BGCOLOR;
		}
	}
	catch (hresult_exception&) {
		m_crBgColor = AN_DEFAULT_BGCOLOR;
	}

	try {
		CComBSTR bstr;
		CComPtr<IMgaRegNode> shadowcolNode;
		CComBSTR shadowcolName(AN_SHADOWCOLOR_PREF);
		COMTHROW(m_regRoot->get_SubNodeByName(shadowcolName, &shadowcolNode));
		if (shadowcolNode != NULL) {
			COMTHROW(shadowcolNode->get_Value(&bstr));
		}
		CString strVal(bstr);
		unsigned int val;
		if (_stscanf(strVal,_T("%x"),&val) == 1) {
			unsigned int r = (val & 0xff0000) >> 16;
			unsigned int g = (val & 0xff00) >> 8;
			unsigned int b = val & 0xff;
			m_crShadow = RGB(r,g,b);
		} else {
			m_crShadow = AN_DEFAULT_SHADOWCOLOR;
		}
	}
	catch (hresult_exception&) {
		m_crShadow = AN_DEFAULT_SHADOWCOLOR;
	}

	try {
		CComBSTR bstr;
		CComPtr<IMgaRegNode> gradientcolNode;
		CComBSTR gradientcolName(AN_GRADIENTCOLOR_PREF);
		COMTHROW(m_regRoot->get_SubNodeByName(gradientcolName, &gradientcolNode));
		if (gradientcolNode != NULL) {
			COMTHROW(gradientcolNode->get_Value(&bstr));
		}
		CString strVal(bstr);
		unsigned int val;
		if (_stscanf(strVal,_T("%x"),&val) == 1) {
			unsigned int r = (val & 0xff0000) >> 16;
			unsigned int g = (val & 0xff00) >> 8;
			unsigned int b = val & 0xff;
			m_crGradient = RGB(r,g,b);
		} else {
			m_crGradient = AN_DEFAULT_GRADIENTCOLOR;
		}
	}
	catch (hresult_exception&) {
		m_crGradient = AN_DEFAULT_GRADIENTCOLOR;
	}

	try {
		m_bGradientFill = AN_DEFAULT_GRADIENTFILL;
		CComBSTR bstr;
		CComPtr<IMgaRegNode> lfNode;
		CComBSTR lfName(AN_GRADIENTFILL_PREF);
		COMTHROW(m_regRoot->get_SubNodeByName(lfName, &lfNode));
		if (lfNode != NULL) {
			COMTHROW(lfNode->get_Value(&bstr));
			if (bstr == "1")
				m_bGradientFill = true;
			else
				m_bGradientFill = false;
		}
	}
	catch (hresult_exception &) {
		m_bGradientFill = AN_DEFAULT_GRADIENTFILL;
	}

	// 'GradientDirection'
	try {
		m_iGradientDirection = AN_DEFAULT_GRADIENTDIRECTION;
		CComBSTR bstr;
		CComPtr<IMgaRegNode> lfNode;
		CComBSTR lfName(AN_GRADIENTDIRECTION_PREF);
		COMTHROW(m_regRoot->get_SubNodeByName(lfName, &lfNode));
		if (lfNode != NULL) {
			COMTHROW(lfNode->get_Value(&bstr));
			CString strVal(bstr);
			if (_stscanf(strVal,_T("%ld"),&m_iGradientDirection) != 1) {
				m_iGradientDirection = AN_DEFAULT_GRADIENTDIRECTION;
			}
		}
	}
	catch (hresult_exception &) {
		m_iGradientDirection = AN_DEFAULT_GRADIENTDIRECTION;
	}

	// 'CastShadow'
	try {
		m_bCastShadow = AN_DEFAULT_CASTSHADOW;
		CComBSTR bstr;
		CComPtr<IMgaRegNode> lfNode;
		CComBSTR lfName(AN_CASTSHADOW_PREF);
		COMTHROW(m_regRoot->get_SubNodeByName(lfName, &lfNode));
		if (lfNode != NULL) {
			COMTHROW(lfNode->get_Value(&bstr));
			if (bstr == "1")
				m_bCastShadow = true;
			else
				m_bCastShadow = false;
		}
	}
	catch (hresult_exception &) {
		m_bCastShadow = AN_DEFAULT_CASTSHADOW;
	}

	// 'ShadowDepth'
	try {
		m_iShadowDepth = AN_DEFAULT_SHADOWDEPTH;
		CComBSTR bstr;
		CComPtr<IMgaRegNode> lfNode;
		CComBSTR lfName(AN_SHADOWDEPTH_PREF);
		COMTHROW(m_regRoot->get_SubNodeByName(lfName, &lfNode));
		if (lfNode != NULL) {
			COMTHROW(lfNode->get_Value(&bstr));
			CString strVal(bstr);
			if (_stscanf(strVal,_T("%ld"),&m_iShadowDepth) != 1) {
				m_iShadowDepth = AN_DEFAULT_SHADOWDEPTH;
			}
		}
	}
	catch (hresult_exception &) {
		m_iShadowDepth = AN_DEFAULT_SHADOWDEPTH;
	}

	// 'ShadowDirection'
	try {
		m_iShadowDirection = AN_DEFAULT_SHADOWDIRECTION;
		CComBSTR bstr;
		CComPtr<IMgaRegNode> lfNode;
		CComBSTR lfName(AN_SHADOWDIRECTION_PREF);
		COMTHROW(m_regRoot->get_SubNodeByName(lfName, &lfNode));
		if (lfNode != NULL) {
			COMTHROW(lfNode->get_Value(&bstr));
			CString strVal(bstr);
			if (_stscanf(strVal,_T("%ld"),&m_iShadowDirection) != 1) {
				m_iShadowDirection = AN_DEFAULT_SHADOWDIRECTION;
			}
		}
	}
	catch (hresult_exception &) {
		m_iShadowDirection = AN_DEFAULT_SHADOWDIRECTION;
	}

	// 'RoundCornerRect'
	try {
		m_bRoundCornerRect = AN_DEFAULT_ROUNDCORNERRECT;
		CComBSTR bstr;
		CComPtr<IMgaRegNode> lfNode;
		CComBSTR lfName(AN_ROUNDCORNERRECT_PREF);
		COMTHROW(m_regRoot->get_SubNodeByName(lfName, &lfNode));
		if (lfNode != NULL) {
			COMTHROW(lfNode->get_Value(&bstr));
			if (bstr == "1")
				m_bRoundCornerRect = true;
			else
				m_bRoundCornerRect = false;
		}
	}
	catch (hresult_exception &) {
		m_bRoundCornerRect = AN_DEFAULT_ROUNDCORNERRECT;
	}

	// 'RoundCornerRadius'
	try {
		m_iRoundCornerRadius = AN_DEFAULT_ROUNDCORNERRADIUS;
		CComBSTR bstr;
		CComPtr<IMgaRegNode> lfNode;
		CComBSTR lfName(AN_ROUNDCORNERRADIUS_PREF);
		COMTHROW(m_regRoot->get_SubNodeByName(lfName, &lfNode));
		if (lfNode != NULL) {
			COMTHROW(lfNode->get_Value(&bstr));
			CString strVal(bstr);
			if (_stscanf(strVal,_T("%ld"),&m_iRoundCornerRadius) != 1) {
				m_iRoundCornerRadius = AN_DEFAULT_ROUNDCORNERRADIUS;
			}
		}
	}
	catch (hresult_exception &) {
		m_iRoundCornerRadius = AN_DEFAULT_ROUNDCORNERRADIUS;
	}
}

}; // namespace AnnotatorDecor
