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
		getFacilities().drawText(pDC,
								 m_strText + ATTRIBUTE_SEP,
								 m_namePosition,
								 getFacilities().getFont(m_iFontKey)->pFont,
								 (m_bActive) ? m_crText : COLOR_GREY,
								 TA_BOTTOM | TA_LEFT,
								 m_iMaxTextLength,
								 "",
								 "",
								 false);
		getFacilities().drawText(pDC,
								 m_strType,
								 m_typePosition,
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
	return m_namePosition;
}

void AttributePart::SetTextPosition(const CPoint& pos)
{
	SetNamePosition(pos);
}

CRect AttributePart::GetTextLocation(void) const
{
	CPoint pt = GetTextPosition();

	CDC dc;
	dc.CreateCompatibleDC(NULL);
	dc.SelectObject(getFacilities().getFont(m_iFontKey)->pFont);
	CSize cSize = dc.GetTextExtent(DecoratorSDK::getFacilities().getStereotyped(m_strText));

	return CRect(pt.x, pt.y, pt.x + cSize.cx, pt.y + cSize.cy);
}

void AttributePart::ExecuteOperation(void)
{
	// TODO
	// transaction operation begin
/*	CComBSTR bstr;
	CopyTo(m_strText, bstr);
	COMTHROW(m_spFCO->put_Name(bstr));*/
	// transaction operation end
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
