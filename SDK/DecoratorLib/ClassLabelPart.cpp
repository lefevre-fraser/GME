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

ClassLabelPart::ClassLabelPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink):
	TextPart(pPart, eventSink)
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

CRect ClassLabelPart::GetLabelLocation(void) const
{
	CPoint pt = GetTextPosition();

	CDC dc;
	dc.CreateCompatibleDC(NULL);
	dc.SelectObject(getFacilities().getFont(m_iFontKey)->pFont);
	CSize cSize = dc.GetTextExtent(m_strText);

	return CRect(pt.x, pt.y, pt.x + cSize.cx, pt.y + cSize.cy);
}

void ClassLabelPart::Draw(CDC* pDC)
{
	if (m_bTextEnabled) {
		CPoint pt = GetTextPosition();
		getFacilities().drawText(pDC,
								 m_strText,
								 CPoint(pt.x, pt.y),
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

CPoint	ClassLabelPart::GetTextPosition(void) const
{
	return m_labelPosition;
}

void ClassLabelPart::SetTextPosition(const CPoint& pos)
{
	m_labelPosition = pos;
}

void ClassLabelPart::ExecuteOperation(void)
{
	// transaction operation begin
	CComBSTR bstr;
	CopyTo(m_strText, bstr);
	COMTHROW(m_spFCO->put_Name(bstr));
	// transaction operation end
}

}; // namespace DecoratorSDK
