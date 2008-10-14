//################################################################################################
//
// Bitmap and label composite part class (decorator part)
//	BitmapAndLabelPart.h
//
//################################################################################################

#ifndef __BITMAPANDLABELPART_H_
#define __BITMAPANDLABELPART_H_


#include "StdAfx.h"
#include "ImageAndLabelPart.h"
#include <vector>


namespace DecoratorSDK {

class TypeableBitmapPart;

//################################################################################################
//
// CLASS : BitmapAndLabelPart
//
//################################################################################################

class BitmapAndLabelPart: public ImageAndLabelPart
{
public:
	BitmapAndLabelPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink);
	virtual ~BitmapAndLabelPart();

public:
	virtual void				AddBitmapPart	(TypeableBitmapPart* part);
	virtual TypeableBitmapPart*	GetBitmapPart	(void) const;
};

}; // namespace DecoratorSDK

#endif //__BITMAPANDLABELPART_H_
