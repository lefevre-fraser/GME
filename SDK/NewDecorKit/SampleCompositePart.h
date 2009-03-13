//################################################################################################
//
// Sample decorator composite part class
//	SampleCompositePart.h
// Contains the specific decorator parts which compose the final decorator
//
//################################################################################################

#ifndef __SAMPLECOMPOSITEPART_H_
#define __SAMPLECOMPOSITEPART_H_


#include "StdAfx.h"
#include "ObjectAndTextPart.h"


class COleDataObject;

namespace SampleDecor {

//################################################################################################
//
// CLASS : SampleCompositePart
//
//################################################################################################

class SampleCompositePart: public DecoratorSDK::ObjectAndTextPart
{
public:
	SampleCompositePart(DecoratorSDK::PartBase* pPart, CComPtr<IMgaElementDecoratorEvents>& eventSink);
	virtual ~SampleCompositePart();

// =============== resembles IMgaElementDecorator
public:
	//
	// TODO: Override any needed function here
	//		 For function list see: SampleDecorator.h or DecoratorSDK::DecoratorInterface
	//
	virtual CRect	GetPortLocation				(CComPtr<IMgaFCO>& fco) const;
	virtual CRect	GetLabelLocation			(void) const;

	virtual void	InitializeEx				(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd, DecoratorSDK::PreferenceMap& preferences);
	virtual void	InitializeEx				(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd);

	virtual bool	MouseLeftButtonDoubleClick	(UINT nFlags, const CPoint& point, HDC transformHDC);
	virtual bool	MouseRightButtonDown		(HMENU hCtxMenu, UINT nFlags, const CPoint& point, HDC transformHDC);
	virtual bool	DragEnter					(DROPEFFECT* dropEffect, COleDataObject* pDataObject, DWORD dwKeyState, const CPoint& point, HDC transformHDC);
	virtual bool	DragOver					(DROPEFFECT* dropEffect, COleDataObject* pDataObject, DWORD dwKeyState, const CPoint& point, HDC transformHDC);
	virtual bool	Drop						(COleDataObject* pDataObject, DROPEFFECT dropEffect, const CPoint& point, HDC transformHDC);
	virtual bool	DropFile					(HDROP p_hDropInfo, const CPoint& point, HDC transformHDC);
	virtual bool	MenuItemSelected			(UINT menuItemId, UINT nFlags, const CPoint& point, HDC transformHDC);
};

}; // namespace SampleDecor

#endif //__SAMPLECOMPOSITEPART_H_
