//################################################################################################
//
// Vector and label composite part class (decorator part)
//	VectorAndLabelPart.h
//
//################################################################################################

#ifndef __VECTORANDLABELPART_H_
#define __VECTORANDLABELPART_H_


#include "StdAfx.h"
#include "ImageAndLabelPart.h"
#include <vector>


namespace DecoratorSDK {

class VectorPart;

//################################################################################################
//
// CLASS : VectorAndLabelPart
//
//################################################################################################

class VectorAndLabelPart: public ImageAndLabelPart
{
public:
	VectorAndLabelPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink);
	virtual ~VectorAndLabelPart();

public:
	virtual void				AddVectorPart	(VectorPart* part);
	virtual VectorPart*			GetVectorPart	(void) const;
};

}; // namespace DecoratorSDK

#endif //__VECTORANDLABELPART_H_
