//################################################################################################
//
// Label part class (decorator part)
//	LabelPart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "LabelPart.h"


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : LabelPart
//
//################################################################################################

LabelPart::LabelPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink):
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

LabelPart::~LabelPart()
{
}

CRect LabelPart::GetLabelLocation(void) const
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
