//################################################################################################
//
// Attribute part class (decorator part)
//	AttributePart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "AttributePart.h"


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : AttributePart
//
//################################################################################################

AttributePart::AttributePart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink):
	TextPart(pPart, eventSink)
{
	textStringVariableName		= "";	// disable
	textFontVariableName		= PREF_LABELFONT;
	textMaxLengthVariableName	= PREF_LABELLENGTH;
	textColorVariableName		= PREF_LABELCOLOR;
	textLocationVariableName	= PREF_LABELLOCATION;
	textStatusVariableName		= PREF_LABELENABLED;
	textWrapStatusVariableName	= PREF_LABELWRAP;
}

AttributePart::~AttributePart()
{
}

void AttributePart::Draw(CDC* pDC)
{
	if (m_bTextEnabled) {
		CRect loc = GetLocation();
		getFacilities().drawText(pDC,
								 m_strText + ATTRIBUTE_SEP,
								 CPoint(loc.left + DECORATOR_MARGINX, loc.top + m_textRelYPosition),
								 getFacilities().getFont(m_iFontKey)->pFont,
								 (m_bActive) ? m_crText : COLOR_GREY,
								 TA_BOTTOM | TA_LEFT,
								 m_iMaxTextLength,
								 "",
								 "",
								 false);
		getFacilities().drawText(pDC,
								 m_strType,
								 CPoint(loc.right - DECORATOR_MARGINX, loc.top + m_textRelYPosition),
								 getFacilities().getFont(m_iFontKey)->pFont,
								 (m_bActive) ? m_crText : COLOR_GREY,
								 TA_BOTTOM | TA_RIGHT,
								 m_iMaxTextLength,
								 "",
								 "",
								 false);
	}
	if (m_spFCO)
		resizeLogic.Draw(pDC);
}

CPoint	AttributePart::GetTextPosition(void) const
{
	return GetTextLocation().TopLeft();
}

CRect AttributePart::GetTextLocation(void) const
{
	CRect loc = GetLocation();

	CDC dc;
	dc.CreateCompatibleDC(NULL);
	dc.SelectObject(getFacilities().getFont(m_iFontKey)->pFont);
	CSize cSize = dc.GetTextExtent(DecoratorSDK::getFacilities().getStereotyped(m_strText));

	return CRect(loc.left + DECORATOR_MARGINX,
				 loc.top + m_textRelYPosition - cSize.cy,
				 loc.left + DECORATOR_MARGINX + cSize.cx,
				 loc.top + m_textRelYPosition);
}

CSize AttributePart::GetNameSize(CDC* pDC) const
{
	ASSERT(pDC != NULL);
	return pDC->GetTextExtent(m_strText);
}

CSize AttributePart::GetTypeSize(CDC* pDC) const
{
	ASSERT(pDC != NULL);
	CSize extent = pDC->GetTextExtent(m_strType);
	return extent;
}

CSize AttributePart::GetTextSize(CDC* pDC) const
{
	ASSERT(pDC != NULL);
	return pDC->GetTextExtent(m_strText + ATTRIBUTE_SEP + m_strType);
}

}; // namespace DecoratorSDK
