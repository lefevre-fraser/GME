//################################################################################################
//
// Stereo label part class (decorator part)
//	StereoLabelPart.h
//
//################################################################################################

#ifndef __STEREOLABELPART_H_
#define __STEREOLABELPART_H_


#include "StdAfx.h"
#include "TextPart.h"


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : StereoLabelPart
//
//################################################################################################

class StereoLabelPart: public TextPart
{
protected:
	long		m_labelRelYPosition;	// bottom of the text because of the bottom alignment

public:
	StereoLabelPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink);
	virtual ~StereoLabelPart();

	virtual void	Draw						(CDC* pDC);

	virtual CPoint	GetTextPosition				(void) const;
	virtual void	SetTextRelYPosition			(long relYPosition) { m_labelRelYPosition = relYPosition; };
	virtual CRect	GetTextLocation				(void) const;
};

}; // namespace DecoratorSDK

#endif //__STEREOLABELPART_H_
