//################################################################################################
//
// Image and label composite part class (decorator part)
//	ImageAndLabelPart.h
//
//################################################################################################

#ifndef __IMAGEANDLABELPART_H_
#define __IMAGEANDLABELPART_H_


#include "StdAfx.h"
#include "CompositePart.h"
#include <vector>


namespace DecoratorSDK {

class LabelPart;
class ResizablePart;

//################################################################################################
//
// CLASS : ImageAndLabelPart
//
//################################################################################################

class ImageAndLabelPart: public CompositePart
{
public:
	ImageAndLabelPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink);
	virtual ~ImageAndLabelPart();

public:		// new functions
	virtual void			AddImagePart		(ResizablePart* part);
	virtual void			AddLabelPart		(LabelPart* part);
	virtual ResizablePart*	GetImagePart		(void) const;
	virtual LabelPart*		GetLabelPart		(void) const;
};

}; // namespace DecoratorSDK

#endif //__IMAGEANDLABELPART_H_
