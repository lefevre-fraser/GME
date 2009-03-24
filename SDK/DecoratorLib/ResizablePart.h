//################################################################################################
//
// Resizable part class (decorator part)
//	ResizablePart.h
//
//################################################################################################

#ifndef __RESIZABLEPART_H_
#define __RESIZABLEPART_H_


#include "StdAfx.h"
#include "PartBase.h"
#include "ResizeLogic.h"


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : ResizablePart
//
//################################################################################################

class ResizablePart: public PartBase
{
public:
	bool			m_bReadCustomSize;	// For temporary use, when you want to determine intended size
	bool			m_bResetSize;		// For temporary use, siganling that size reset is needed
	ResizeLogic		resizeLogic;

	ResizablePart(PartBase* pPart, CComPtr<IMgaCommonDecoratorEvents>& eventSink);
	virtual ~ResizablePart();

// =============== resembles IMgaElementDecorator
public:
	virtual void			Initialize			(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO);
	virtual void			Destroy				(void);
	virtual feature_code	GetFeatures			(void) const;
	virtual CSize			GetPreferredSize	(void) const;
	virtual void			SetLocation			(const CRect& location);
	virtual CRect			GetLocation			(void) const;
	virtual void			Draw				(CDC* pDC, Gdiplus::Graphics* gdip);

	virtual void	InitializeEx				(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd, PreferenceMap& preferences);
	virtual bool	MouseMoved					(UINT nFlags, const CPoint& point, HDC transformHDC);
	virtual bool	MouseLeftButtonDown			(UINT nFlags, const CPoint& point, HDC transformHDC);
	virtual bool	MouseLeftButtonUp			(UINT nFlags, const CPoint& point, HDC transformHDC);
	virtual bool	MouseRightButtonDown		(HMENU hCtxMenu, UINT nFlags, const CPoint& point, HDC transformHDC);
	virtual bool	MenuItemSelected			(UINT menuItemId, UINT nFlags, const CPoint& point, HDC transformHDC);
	virtual bool	OperationCanceledByGME		(void);

	virtual void	WindowResizing				(UINT nSide, CRect& location);
	virtual void	WindowResizingFinished		(UINT nSide, CRect& location);
};

}; // namespace DecoratorSDK

#endif //__RESIZABLEPART_H_
