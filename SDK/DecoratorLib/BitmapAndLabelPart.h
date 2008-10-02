//################################################################################################
//
// Bitmap and label composite part class (decorator part)
//	BitmapAndLabelPart.h
//
//################################################################################################

#ifndef __BITMAPANDLABELPART_H_
#define __BITMAPANDLABELPART_H_


#include "StdAfx.h"
#include "CompositePart.h"
#include <vector>


namespace DecoratorSDK {

class TypeableBitmapPart;
class LabelPart;

//################################################################################################
//
// CLASS : BitmapAndLabelPart
//
//################################################################################################

class BitmapAndLabelPart: public CompositePart
{
public:
	BitmapAndLabelPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink);
	virtual ~BitmapAndLabelPart();

protected:	// disabled
	virtual void			AddPart				(PartBase* part);
	virtual void			RemovePart			(PartBase* part);
	virtual void			RemovePart			(int index);
	virtual PartBase*		GetPart				(int index);
	virtual long			GetSize				(void) const;

public:
	virtual void			AddBitmapPart		(TypeableBitmapPart* part);
	virtual void			AddLabelPart		(LabelPart* part);
	virtual TypeableBitmapPart*	GetBitmapPart	(void) const;
	virtual LabelPart*		GetLabelPart		(void) const;
};

}; // namespace DecoratorSDK

#endif //__BITMAPANDLABELPART_H_
