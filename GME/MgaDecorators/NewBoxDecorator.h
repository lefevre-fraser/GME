//################################################################################################
//
// New box decorator class
//	NewBoxDecorator.h
//
//################################################################################################

#ifndef __NEWBOXDECORATOR_H_
#define __NEWBOXDECORATOR_H_


#include "StdAfx.h"
#include "DecoratorInterface.h"
#include "Parts/PartInterface.h"


namespace Decorator {

//################################################################################################
//
// CLASS : NewBoxDecorator
//
//################################################################################################

class NewBoxDecorator: public DecoratorInterface
{
protected:
	PartInterface*						m_part;
	CComPtr<IMgaNewDecoratorEvents>		m_eventSink;

public:
	NewBoxDecorator(CComPtr<IMgaNewDecoratorEvents> eventSink);
	virtual ~NewBoxDecorator();

// =============== resembles IMgaNewDecorator
public:
	virtual void			Initialize			(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO);
	virtual void			Destroy				(void);
	virtual CString			GetMnemonic			(void) const;
	virtual feature_code	GetFeatures			(void) const;
	virtual void			SetParam			(const CString& strName, VARIANT vValue);
	virtual void			GetParam			(const CString& strName, VARIANT* pvValue);
	virtual void			SetActive			(bool bIsActive);
	virtual CSize			GetPreferredSize	(void) const;
	virtual void			SetLocation			(const CRect& location);
	virtual CRect			GetLocation			(void) const;
	virtual CRect			GetLabelLocation	(void) const;
	virtual CRect			GetPortLocation		(CComPtr<IMgaFCO>& fco) const;
	virtual void			GetPorts			(CComPtr<IMgaFCOs>& portFCOs) const;
	virtual void			Draw				(CDC* pDC);
	virtual void			SaveState			(void);

	virtual void	InitializeEx				(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd);
	virtual void	SetSelected					(bool bIsSelected);
	virtual bool	MouseMoved					(UINT nFlags, const CPoint& point, HDC transformHDC);
	virtual bool	MouseLeftButtonDown			(UINT nFlags, const CPoint& point, HDC transformHDC);
	virtual bool	MouseLeftButtonUp			(UINT nFlags, const CPoint& point, HDC transformHDC);
	virtual bool	MouseLeftButtonDoubleClick	(UINT nFlags, const CPoint& point, HDC transformHDC);
	virtual bool	MouseRightButtonDown		(HMENU hCtxMenu, UINT nFlags, const CPoint& point, HDC transformHDC);
	virtual bool	MouseRightButtonUp			(UINT nFlags, const CPoint& point, HDC transformHDC);
	virtual bool	MouseRightButtonDoubleClick	(UINT nFlags, const CPoint& point, HDC transformHDC);
	virtual bool	MouseMiddleButtonDown		(UINT nFlags, const CPoint& point, HDC transformHDC);
	virtual bool	MouseMiddleButtonUp			(UINT nFlags, const CPoint& point, HDC transformHDC);
	virtual bool	MouseMiddleButtonDoubleClick(UINT nFlags, const CPoint& point, HDC transformHDC);
	virtual bool	MouseWheelTurned			(UINT nFlags, short distance, const CPoint& point, HDC transformHDC);
	virtual bool	MenuItemSelected			(UINT menuItemId, UINT nFlags, const CPoint& point, HDC transformHDC);
	virtual bool	OperationCanceledByGME		(void);

// =============== resembles IMgaNewDecoratorEvents
/*	virtual void	Refresh						(void);
	virtual void	OperationCanceledByDecorator(void);
	virtual void	CursorChanged				(long newCursorID);
	virtual void	CursorRestored				(void);

	virtual void	TitleEditingStarted			(CRect& location);
	virtual void	TitleEditingFinished		(CRect& location);
	virtual void	TitleChanged				(CString& newTitle);
	virtual void	TitleMovingStarted			(UINT nType, CRect& location);
	virtual void	TitleMoving					(UINT nSide, CRect& location);
	virtual void	TitleMovingFinished			(UINT nType, CRect& location);
	virtual void	TitleMoved					(UINT nType, CPoint& point);
	virtual void	TitleResizingStarted		(UINT nType, CRect& location);
	virtual void	TitleResizing				(UINT nSide, CRect& location);
	virtual void	TitleResizingFinished		(UINT nType, CRect& locatiot);
	virtual void	TitleResized				(UINT nType, CSize& size);

	virtual void	WindowMovingStarted			(UINT nType, CRect& location);
	virtual void	WindowMoving				(UINT nSide, CRect& location);
	virtual void	WindowMovingFinished		(UINT nType, CRect& location);
	virtual void	WindowMoved					(UINT nType, CPoint& point);

	virtual void	WindowResizingStarted		(UINT nType, CRect& location);
	virtual void	WindowResizing				(UINT nSide, CRect& location);
	virtual void	WindowResizingFinished		(UINT nType, CRect& location);
	virtual void	WindowResized				(UINT nType, CSize& size);*/
};

}; // namespace Decorator

#endif //__NEWBOXDECORATOR_H_
