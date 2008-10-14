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
	textStringVariableName		= PREF_LABEL;
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
		ECoordRefPoint eAlign = GetAlignment(m_eTextLocation);
		int iAlign = 0;
		switch (eAlign) {
			case CRP_BEGIN:		iAlign = TA_LEFT;	break;
			case CRP_CENTER:	iAlign = TA_CENTER;	break;
			case CRP_END:
			default:			iAlign = TA_RIGHT;	break;
		}
		iAlign |= TA_TOP;

		int iAttributeSize = getFacilities().getFont(m_iFontKey)->iSize;
		CPoint pt = GetTextPosition();
		for (unsigned int i = 0; i < m_vecText.size(); i++)
			getFacilities().drawText(pDC,
									 m_vecText[i],
									 CPoint(pt.x, pt.y + i * iAttributeSize),
									 getFacilities().getFont(m_iFontKey)->pFont,
									 (m_bActive) ? m_crText : COLOR_GRAY,
									 iAlign,
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
	CPoint pt;
	CRect cRect = GetLocation();	// GetBoxLocation(true)
	int iAttributeSize = getFacilities().getFont(m_iFontKey)->iSize * m_vecText.size();
	switch(m_eTextLocation) {
		case L_NORTH:
		case L_NORTHWEST:
		case L_NORTHEAST:
			pt.y = cRect.top - iAttributeSize - GAP_LABEL;
			break;
		case L_SOUTH:
		case L_SOUTHWEST:
		case L_SOUTHEAST:
			pt.y = cRect.bottom + GAP_LABEL;
			break;
		default:
			pt.y = cRect.CenterPoint().y - iAttributeSize / 2;
			break;
	}
	switch(m_eTextLocation) {
		case L_WEST:
		case L_NORTHWEST:
		case L_SOUTHWEST:
			pt.x = cRect.left - GAP_LABEL;
			break;
		case L_NORTH:
		case L_CENTER:
		case L_SOUTH:
			pt.x = cRect.CenterPoint().x;
			break;
		default:
			pt.x = cRect.right + GAP_LABEL;
			break;
	}
	return pt;
}

CRect AttributePart::GetTextLocation(void) const
{
	CPoint pt = GetTextPosition();
	ECoordRefPoint eAlign = GetAlignment(m_eTextLocation);

	CDC dc;
	dc.CreateCompatibleDC(NULL);
	dc.SelectObject(getFacilities().getFont(m_iFontKey)->pFont);
	CSize cSize(0,0);
	for (unsigned int i = 0 ; i < m_vecText.size(); i++) {
		CSize tmpSize = dc.GetTextExtent(m_vecText[i]);
		cSize.cy += tmpSize.cy;
		cSize.cx = max(cSize.cx, tmpSize.cx);
	}

	if (eAlign == CRP_CENTER)
		pt.x -= cSize.cx / 2;
	else if (eAlign == CRP_END)
		pt.x -= cSize.cx;

	return CRect(pt.x, pt.y, pt.x + cSize.cx, pt.y + cSize.cy);
}

}; // namespace DecoratorSDK
