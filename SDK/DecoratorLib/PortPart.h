//################################################################################################
//
// Port part class (decorator part)
//	PortPart.h
//
//################################################################################################

#ifndef __PORTPART_H_
#define __PORTPART_H_


#include "StdAfx.h"
#include "ObjectAndTextPart.h"


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : PortPart
//
//################################################################################################

class PortPart: public ObjectAndTextPart
{
public:
	PortPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink, const CPoint& ptInner);
	virtual ~PortPart();

// =============== resembles IMgaNewDecorator
public:
	virtual CPoint	GetInnerPosition			(void) const;
	virtual long	GetLongest					(void) const;
};

}; // namespace DecoratorSDK

#endif //__PORTPART_H_
