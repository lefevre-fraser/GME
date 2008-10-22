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

void StereoLabelPart::Draw(CDC* pDC)
{
	if (m_bTextEnabled) {
		CRect loc = GetLocation();
		long centerline = (loc.left + loc.right) / 2;
		getFacilities().drawText(pDC,
								 DecoratorSDK::getFacilities().getStereotyped(m_strText),
								 CPoint(centerline, loc.top + m_labelRelYPosition),
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
	return GetLabelLocation().TopLeft();
}

CRect StereoLabelPart::GetTextLocation(void) const
{
	CRect loc = GetLocation();

	CDC dc;
	dc.CreateCompatibleDC(NULL);
	dc.SelectObject(getFacilities().getFont(m_iFontKey)->pFont);
	CSize cSize = dc.GetTextExtent(DecoratorSDK::getFacilities().getStereotyped(m_strText));

	long centerline = (loc.left + loc.right) / 2;
	return CRect(centerline - cSize.cx / 2,
				 loc.top + m_labelRelYPosition - cSize.cy,
				 centerline + cSize.cx / 2,
				 loc.top + m_labelRelYPosition);
}

}; // namespace DecoratorSDK
