//################################################################################################
//
// Decorator parts base class
//	PartBase.h
//
//################################################################################################

#ifndef __PARTBASE_H_
#define __PARTBASE_H_


#include "../StdAfx.h"
#include "MgaDecorator.h"
#include "mga.h"
#include "../DecoratorDefs.h"
#include "../DecoratorUtil.h"
#include "PartInterface.h"
#include "../BitmapUtil.h"


namespace Decorator {

//################################################################################################
//
// CLASS : PartBase
//
//################################################################################################

class PartBase: public PartInterface
{
protected:
	PartBase*						m_parentPart;
	CComPtr<IMgaNewDecoratorEvents>	m_eventSink;

	CComPtr<IMgaProject>			m_spProject;
	CComPtr<IMgaMetaPart>			m_spPart;
	CComPtr<IMgaFCO>				m_spFCO;
	HWND							m_parentWnd;
	HDC								m_viewDC;

	CRect							m_Rect;
	objtype_enum					m_eType;
	bool							m_bHasViolation;
	bool							m_bActive;
	bool							m_bSelected;
	long							m_lBorderWidth;
	bool							m_bReferenced;

public:
	PartBase(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink);
	virtual ~PartBase();

	virtual void	SetParentPart				(PartBase* pPart) { m_parentPart = pPart; };

// =============== resembles IMgaNewDecorator
	virtual void			Initialize			(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO);
	virtual void			Destroy				(void);										// default (no) implementation
	virtual CString			GetMnemonic			(void) const;								// default (no) implementation
	virtual feature_code	GetFeatures			(void) const;								// default (no) implementation
	virtual void			SetParam			(const CString& strName, VARIANT vValue);	// default (no) implementation
	virtual bool			GetParam			(const CString& strName, VARIANT* pvValue);	// default (no) implementation
	virtual void			SetActive			(bool bIsActive);
	virtual CSize			GetPreferredSize	(void) const;								// default (no) implementation
	virtual void			SetLocation			(const CRect& location);
	virtual CRect			GetLocation			(void) const;
	virtual CRect			GetLabelLocation	(void) const;								// default (no) implementation
	virtual CRect			GetPortLocation		(CComPtr<IMgaFCO>& fco) const;				// default (no) implementation
	virtual bool			GetPorts			(CComPtr<IMgaFCOs>& portFCOs) const;		// default (no) implementation
	virtual void			Draw				(CDC* pDC);									// default (no) implementation
	virtual void			SaveState			(void);										// default (no) implementation

	virtual void	InitializeEx				(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd, PreferenceMap& preferences);
	virtual void	SetSelected					(bool bIsSelected);
	virtual bool	MouseMoved					(UINT nFlags, const CPoint& point, HDC transformHDC);	// default (no) implementation
	virtual bool	MouseLeftButtonDown			(UINT nFlags, const CPoint& point, HDC transformHDC);	// default (no) implementation
	virtual bool	MouseLeftButtonUp			(UINT nFlags, const CPoint& point, HDC transformHDC);	// default (no) implementation
	virtual bool	MouseLeftButtonDoubleClick	(UINT nFlags, const CPoint& point, HDC transformHDC);	// default (no) implementation
	virtual bool	MouseRightButtonDown		(HMENU hCtxMenu, UINT nFlags, const CPoint& point, HDC transformHDC);	// default (no) implementation
	virtual bool	MouseRightButtonUp			(UINT nFlags, const CPoint& point, HDC transformHDC);	// default (no) implementation
	virtual bool	MouseRightButtonDoubleClick	(UINT nFlags, const CPoint& point, HDC transformHDC);	// default (no) implementation
	virtual bool	MouseMiddleButtonDown		(UINT nFlags, const CPoint& point, HDC transformHDC);	// default (no) implementation
	virtual bool	MouseMiddleButtonUp			(UINT nFlags, const CPoint& point, HDC transformHDC);	// default (no) implementation
	virtual bool	MouseMiddleButtonDoubleClick(UINT nFlags, const CPoint& point, HDC transformHDC);	// default (no) implementation
	virtual bool	MouseWheelTurned			(UINT nFlags, short distance, const CPoint& point, HDC transformHDC);	// default (no) implementation
	virtual bool	MenuItemSelected			(UINT menuItemId, UINT nFlags, const CPoint& point, HDC transformHDC);	// default (no) implementation
	virtual bool	OperationCanceledByGME		(void);										// default (no) implementation

// =============== resembles IMgaNewDecoratorEvents
	virtual void	Refresh						(void);
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
	virtual void	WindowResized				(UINT nType, CSize& size);


// === Helper functions ===
	virtual ECoordRefPoint	GetAlignment		(ELocation loc) const;
	virtual long	GetBorderWidth				(bool bActive = true) const;
	virtual void	SetBoxLocation				(const CRect& cRect);
	virtual CRect	GetBoxLocation				(bool bWithBorder = false) const;
	virtual void	SetReferenced				(bool referenced);
	virtual CComPtr<IMgaFCO> GetFCO				(void) const { return m_spFCO; };
	PartBase*		GetParent					(void) const { return m_parentPart; };
	virtual bool	IsActive					(void) const { return m_bActive; };
	virtual bool	IsSelected					(void) const { return m_bSelected; };
};

};	// namespace Decorator

#endif //__PARTBASE_H_
