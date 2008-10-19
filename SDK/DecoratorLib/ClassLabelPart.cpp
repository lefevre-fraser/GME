//################################################################################################
//
// Class label part class (decorator part)
//	ClassLabelPart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "ClassLabelPart.h"


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : ClassLabelPart
//
//################################################################################################

ClassLabelPart::ClassLabelPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink, bool bIsAbstract):
	TextPart(pPart, eventSink),
	m_bIsAbstract(bIsAbstract)
{
	// TODO
	textStringVariableName		= "";	// disable
	textFontVariableName		= PREF_LABELFONT;
	textMaxLengthVariableName	= PREF_LABELLENGTH;
	textColorVariableName		= PREF_LABELCOLOR;
	textLocationVariableName	= PREF_LABELLOCATION;
	textStatusVariableName		= PREF_LABELENABLED;
	textWrapStatusVariableName	= PREF_LABELWRAP;
}

ClassLabelPart::~ClassLabelPart()
{
}

void ClassLabelPart::Draw(CDC* pDC)
{
	if (m_bTextEnabled) {
		CRect loc = GetLocation();
		long centerline = (loc.left + loc.right) / 2;
		getFacilities().drawText(pDC,
								 m_strText,
								 CPoint(centerline, loc.top + m_labelRelYPosition),
								 getFacilities().getFont(m_iFontKey)->pFont,
								 (m_bActive) ? m_crText : COLOR_GRAYED_OUT,
								 TA_BOTTOM | TA_CENTER,
								 m_iMaxTextLength,
								 "",
								 "",
								 false);
	}
	if (m_spFCO)
		resizeLogic.Draw(pDC);
}

// New functions
void ClassLabelPart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
								  HWND parentWnd, PreferenceMap& preferences)
{
	TextPart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);

	if (m_bIsAbstract)
		m_iFontKey = FONT_ABSTRACT;
}

CPoint	ClassLabelPart::GetTextPosition(void) const
{
	return GetLabelLocation().TopLeft();
}

CRect ClassLabelPart::GetTextLocation(void) const
{
	CRect loc = GetLocation();

	CDC dc;
	dc.CreateCompatibleDC(NULL);
	dc.SelectObject(getFacilities().getFont(m_iFontKey)->pFont);
	CSize cSize = dc.GetTextExtent(m_strText);

	long centerline = (loc.left + loc.right) / 2;
	return CRect(centerline - cSize.cx / 2,
				 loc.top + m_labelRelYPosition - cSize.cy,
				 centerline + cSize.cx / 2,
				 loc.top + m_labelRelYPosition);
}

void ClassLabelPart::ExecuteOperation(const CString& newString)
{
	// transaction operation begin
	m_strText = newString;
	CComBSTR bstr;
	CopyTo(newString, bstr);
	COMTHROW(m_spFCO->put_Name(bstr));
	// transaction operation end
}

}; // namespace DecoratorSDK
