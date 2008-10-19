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

	virtual void	Draw						(CDC* pDC);

	virtual CPoint	GetTextPosition				(void) const;
	virtual void	SetTextRelYPosition			(long relYPosition) {};	// This doesn't make sense in case of box label decorator: label text location is computed automatically from box location and text alignment
	virtual CRect	GetTextLocation				(void) const;
	virtual void	ExecuteOperation			(const CString& newString);
};

}; // namespace DecoratorSDK

#endif //__LABELPART_H_
