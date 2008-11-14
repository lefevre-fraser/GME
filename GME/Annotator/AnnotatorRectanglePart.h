//################################################################################################
//
// Annotator rectangle part decorator class
//	AnnotatorRectanglePart.h
//
//################################################################################################

#ifndef __ANNOTATORRECTANGLEPART_H_
#define __ANNOTATORRECTANGLEPART_H_


#include "StdAfx.h"
#include "VectorPart.h"


namespace AnnotatorDecor {

//################################################################################################
//
// CLASS : AnnotatorRectanglePart
//
//################################################################################################

class AnnotatorRectanglePart: public DecoratorSDK::VectorPart
{
public:
	AnnotatorRectanglePart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink);
	virtual ~AnnotatorRectanglePart();

// =============== resembles IMgaNewDecorator
public:
	virtual void			Draw				(CDC* pDC, Gdiplus::Graphics* gdip);
	virtual void			InitializeEx		(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd, DecoratorSDK::PreferenceMap& preferences);
};

}; // namespace AnnotatorDecor

#endif //__ANNOTATORRECTANGLEPART_H_
