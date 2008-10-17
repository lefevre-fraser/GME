//################################################################################################
//
// Class label part class (decorator part)
//	ClassLabelPart.h
//
//################################################################################################

#ifndef __CLASSLABELPART_H_
#define __CLASSLABELPART_H_


#include "StdAfx.h"
#include "TextPart.h"


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : ClassLabelPart
//
//################################################################################################

class ClassLabelPart: public TextPart
{
protected:
	CPoint		m_labelPosition;

public:
	ClassLabelPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink);
	virtual ~ClassLabelPart();

	virtual CRect	GetLabelLocation			(void) const;
	virtual void	Draw						(CDC* pDC);

	virtual CPoint	GetTextPosition				(void) const;
	virtual void	SetTextPosition				(const CPoint& pos);
	virtual void	ExecuteOperation			(void);
};

}; // namespace DecoratorSDK

#endif //__CLASSLABELPART_H_
