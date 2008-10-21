//################################################################################################
//
// Meta stereo label part class (decorator part)
//	MetaStereoLabelPart.h
//
//################################################################################################

#ifndef __METASTEREOLABELPART_H_
#define __METASTEREOLABELPART_H_


#include "StdAfx.h"
#include "StereoLabelPart.h"


namespace MetaDecor {

//################################################################################################
//
// CLASS : MetaStereoLabelPart
//
//################################################################################################

class MetaStereoLabelPart: public DecoratorSDK::StereoLabelPart
{
public:
	MetaStereoLabelPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink);
	virtual ~MetaStereoLabelPart();

	virtual void	InitializeEx				(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd, DecoratorSDK::PreferenceMap& preferences);
	virtual bool	MouseMoved					(UINT nFlags, const CPoint& point, HDC transformHDC);
	virtual bool	MouseLeftButtonDown			(UINT nFlags, const CPoint& point, HDC transformHDC);
	virtual bool	MouseRightButtonDown		(HMENU hCtxMenu, UINT nFlags, const CPoint& point, HDC transformHDC);
	virtual bool	MenuItemSelected			(UINT menuItemId, UINT nFlags, const CPoint& point, HDC transformHDC);
	virtual void	ExecuteOperation			(const CString& newString);
};

}; // namespace MetaDecor

#endif //__METASTEREOLABELPART_H_
