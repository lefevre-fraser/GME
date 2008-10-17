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
	CPoint		m_labelPosition;

public:
	StereoLabelPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink);
	virtual ~StereoLabelPart();

	virtual CRect	GetLabelLocation			(void) const;
	virtual void	Draw						(CDC* pDC);

	virtual CPoint	GetTextPosition				(void) const;
	virtual void	SetTextPosition				(const CPoint& pos);
	virtual void	ExecuteOperation			(void);
};

}; // namespace DecoratorSDK

#endif //__STEREOLABELPART_H_
