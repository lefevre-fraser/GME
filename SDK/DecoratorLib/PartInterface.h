//################################################################################################
//
// Part interface class (decorator parts)
//	PartInterface.h
//
//################################################################################################

#ifndef __PARTINTERFACE_H_
#define __PARTINTERFACE_H_


#include "StdAfx.h"
#include "MgaDecorator.h"
#include "mga.h"
#include "PreferenceVariant.h"


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : PartInterface
//
//################################################################################################

class PartInterface
{
public:
	PartInterface();
	virtual ~PartInterface();

// =============== resembles IMgaNewDecorator
// === every function can throw DecoratorException ===
public:
	virtual void			Initialize			(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO) = 0;
	virtual void			Destroy				(void) = 0;
	virtual CString			GetMnemonic			(void) const = 0;
	virtual feature_code	GetFeatures			(void) const = 0;
	virtual void			SetParam			(const CString& strName, VARIANT vValue) = 0;
	virtual bool			GetParam			(const CString& strName, VARIANT* pvValue) = 0;
	virtual void			SetActive			(bool bIsActive) = 0;
	virtual CSize			GetPreferredSize	(void) const = 0;
	virtual void			SetLocation			(const CRect& location) = 0;
	virtual CRect			GetLocation			(void) const = 0;
	virtual CRect			GetLabelLocation	(void) const = 0;
	virtual CRect			GetPortLocation		(CComPtr<IMgaFCO>& fco) const = 0;
	virtual bool			GetPorts			(CComPtr<IMgaFCOs>& portFCOs) const = 0;
	virtual void			Draw				(CDC* pDC, Gdiplus::Graphics* gdip) = 0;
	virtual void			SaveState			(void) = 0;

	virtual void	InitializeEx				(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd,
												 PreferenceMap& preferences) = 0;
	virtual void	SetSelected					(bool bIsSelected) = 0;
	virtual bool	MouseMoved					(UINT nFlags, const CPoint& point, HDC transformHDC) = 0;
	virtual bool	MouseLeftButtonDown			(UINT nFlags, const CPoint& point, HDC transformHDC) = 0;
	virtual bool	MouseLeftButtonUp			(UINT nFlags, const CPoint& point, HDC transformHDC) = 0;
	virtual bool	MouseLeftButtonDoubleClick	(UINT nFlags, const CPoint& point, HDC transformHDC) = 0;
	virtual bool	MouseRightButtonDown		(HMENU hCtxMenu, UINT nFlags, const CPoint& point, HDC transformHDC) = 0;
	virtual bool	MouseRightButtonUp			(UINT nFlags, const CPoint& point, HDC transformHDC) = 0;
	virtual bool	MouseRightButtonDoubleClick	(UINT nFlags, const CPoint& point, HDC transformHDC) = 0;
	virtual bool	MouseMiddleButtonDown		(UINT nFlags, const CPoint& point, HDC transformHDC) = 0;
	virtual bool	MouseMiddleButtonUp			(UINT nFlags, const CPoint& point, HDC transformHDC) = 0;
	virtual bool	MouseMiddleButtonDoubleClick(UINT nFlags, const CPoint& point, HDC transformHDC) = 0;
	virtual bool	MouseWheelTurned			(UINT nFlags, short distance, const CPoint& point, HDC transformHDC) = 0;
	virtual bool	MenuItemSelected			(UINT menuItemId, UINT nFlags, const CPoint& point, HDC transformHDC) = 0;
	virtual bool	OperationCanceledByGME		(void) = 0;


// =============== resembles IMgaNewDecoratorEvents
// === every function can throw DecoratorException ===
	virtual void	Refresh						(void) = 0;
	virtual void	OperationCanceledByDecorator(void) = 0;
	virtual void	CursorChanged				(long newCursorID) = 0;
	virtual void	CursorRestored				(void) = 0;

	virtual void	TitleEditingStarted			(CRect& location) = 0;
	virtual void	TitleEditingFinished		(CRect& location) = 0;
	virtual void	TitleChanged				(CString& newTitle) = 0;
	virtual void	TitleMovingStarted			(UINT nType, CRect& location) = 0;
	virtual void	TitleMoving					(UINT nSide, CRect& location) = 0;
	virtual void	TitleMovingFinished			(UINT nType, CRect& location) = 0;
	virtual void	TitleMoved					(UINT nType, CPoint& point) = 0;
	virtual void	TitleResizingStarted		(UINT nType, CRect& location) = 0;
	virtual void	TitleResizing				(UINT nSide, CRect& location) = 0;
	virtual void	TitleResizingFinished		(UINT nType, CRect& locatiot) = 0;
	virtual void	TitleResized				(UINT nType, CSize& size) = 0;

	virtual void	WindowMovingStarted			(UINT nType, CRect& location) = 0;
	virtual void	WindowMoving				(UINT nSide, CRect& location) = 0;
	virtual void	WindowMovingFinished		(UINT nType, CRect& location) = 0;
	virtual void	WindowMoved					(UINT nType, CPoint& point) = 0;

	virtual void	WindowResizingStarted		(UINT nType, CRect& location) = 0;
	virtual void	WindowResizing				(UINT nSide, CRect& location) = 0;
	virtual void	WindowResizingFinished		(UINT nType, CRect& location) = 0;
	virtual void	WindowResized				(UINT nType, CSize& size) = 0;
};

};	// namespace DecoratorSDK

#endif //__PARTINTERFACE_H_
