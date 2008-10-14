//################################################################################################
//
// Attribute part class (decorator part)
//	AttributePart.h
//
//################################################################################################

#ifndef __ATTRIBUTEPART_H_
#define __ATTRIBUTEPART_H_


#include "StdAfx.h"
#include "TextPart.h"


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : AttributePart
//
//################################################################################################

class AttributePart: public TextPart
{
public:
	AttributePart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink);
	virtual ~AttributePart();

	virtual void	Draw						(CDC* pDC);

	virtual CPoint	GetTextPosition				(void) const;
	virtual CRect	GetTextLocation				(void) const;
};

}; // namespace DecoratorSDK

#endif //__ATTRIBUTEPART_H_
