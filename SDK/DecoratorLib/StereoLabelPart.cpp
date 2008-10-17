//################################################################################################
//
// Stereo label part class (decorator part)
//	StereoLabelPart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "StereoLabelPart.h"


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : StereoLabelPart
//
//################################################################################################

StereoLabelPart::StereoLabelPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink):
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

StereoLabelPart::~StereoLabelPart()
{
}

CRect StereoLabelPart::GetLabelLocation(void) const
{
	CPoint pt = GetTextPosition();

	CDC dc;
	dc.CreateCompatibleDC(NULL);
	dc.SelectObject(getFacilities().getFont(m_iFontKey)->pFont);
	CSize cSize = dc.GetTextExtent(DecoratorSDK::getFacilities().getStereotyped(m_strText));

	return CRect(pt.x, pt.y, pt.x + cSize.cx, pt.y + cSize.cy);
}

void StereoLabelPart::Draw(CDC* pDC)
{
	if (m_bTextEnabled) {
		CPoint pt = GetTextPosition();
		getFacilities().drawText(pDC,
								 DecoratorSDK::getFacilities().getStereotyped(m_strText),
								 CPoint(pt.x, pt.y),
								 getFacilities().getFont(m_iFontKey)->pFont,
								 (m_bActive) ? m_crText : COLOR_GREY,
								 TA_BOTTOM | TA_CENTER,
								 m_iMaxTextLength,
								 "",
								 "",
								 false);
	}
	if (m_spFCO)
		resizeLogic.Draw(pDC);
}

CPoint	StereoLabelPart::GetTextPosition(void) const
{
	return m_labelPosition;
}

void StereoLabelPart::SetTextPosition(const CPoint& pos)
{
	m_labelPosition = pos;
}

void StereoLabelPart::ExecuteOperation(void)
{
	// transaction operation begin
	// TODO
	// transaction operation end
}

}; // namespace DecoratorSDK
