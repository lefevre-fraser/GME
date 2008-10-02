//################################################################################################
//
// Label part class (decorator part)
//	LabelPart.h
//
//################################################################################################

#ifndef __LABELPART_H_
#define __LABELPART_H_


#include "StdAfx.h"
#include "TextPart.h"


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : LabelPart
//
//################################################################################################

class LabelPart: public TextPart
{
public:
	LabelPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink);
	virtual ~LabelPart();

	virtual CRect	GetLabelLocation			(void) const;
};

}; // namespace DecoratorSDK

#endif //__LABELPART_H_
