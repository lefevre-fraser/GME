//################################################################################################
//
// Port part class (decorator part)
//	PortPart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "PortPart.h"
#include "PortBitmapPart.h"
#include "PortLabelPart.h"


namespace Decorator {

//################################################################################################
//
// CLASS : PortPart
//
//################################################################################################

PortPart::PortPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink, const CPoint& ptInner):
	BitmapAndLabelPart(pPart, eventSink)
{
	PortBitmapPart* portBitmapPart = new PortBitmapPart(this, eventSink, ptInner);
	PortLabelPart* portLabelPart = new PortLabelPart(this, eventSink);
	AddBitmapPart(portBitmapPart);
	AddLabelPart(portLabelPart);
}

PortPart::~PortPart()
{
}

CPoint PortPart::GetInnerPosition(void) const
{
#ifdef _DEBUG
	PortBitmapPart* portBitmapPart = dynamic_cast<PortBitmapPart*> (GetBitmapPart());
#else
	PortBitmapPart* portBitmapPart = static_cast<PortBitmapPart*> (GetBitmapPart());
#endif
	ASSERT(portBitmapPart != NULL);
	return portBitmapPart->GetInnerPosition();
}

long PortPart::GetLongest(void) const
{
#ifdef _DEBUG
	PortLabelPart* portLabelPart = dynamic_cast<PortLabelPart*> (GetLabelPart());
#else
	PortLabelPart* portLabelPart = static_cast<PortLabelPart*> (GetLabelPart());
#endif
	ASSERT(portLabelPart != NULL);
	return portLabelPart->GetLongest();
}

}; // namespace Decorator
