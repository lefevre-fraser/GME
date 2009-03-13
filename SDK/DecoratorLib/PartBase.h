//################################################################################################
//
// Decorator parts base class
//	PartBase.h
//
//################################################################################################

#ifndef __PARTBASE_H_
#define __PARTBASE_H_


#include "StdAfx.h"
#include "MgaDecorator.h"
#include "mga.h"
#include "DecoratorDefs.h"
#include "DecoratorUtil.h"
#include "PartInterface.h"
#include "BitmapUtil.h"


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : PartBase
//
//################################################################################################

class PartBase: public PartInterface
{
protected:
	PartBase*						m_parentPart;
	CComPtr<IMgaElementDecoratorEvents>	m_eventSink;

	CComPtr<IMgaProject>			m_spProject;
	CComPtr<IMgaMetaPart>			m_spPart;
	CComPtr<IMgaFCO>				m_spFCO;
	CComPtr<IMgaMetaFCO>			m_spMetaFCO;
	HWND							m_parentWnd;
	HDC								m_viewDC;

	CRect							m_Rect;
	objtype_enum					m_eType;
	bool							m_bHasViolation;
	bool							m_bActive;
	bool							m_bSelected;
	long							m_lBorderWidth;
	bool							m_bReferenced;
	bool							m_bResizable;

public:
	PartBase(PartBase* pPart, CComPtr<IMgaElementDecoratorEvents>& eventSink);
	virtual ~PartBase();

	virtual void	SetParentPart				(PartBase* pPart) { m_parentPart = pPart; };

// =============== resembles IMgaElementDecorator
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
	virtual void			Draw				(CDC* pDC, Gdiplus::Graphics* gdip);		// default (no) implementation
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
	virtual bool	DragEnter					(DROPEFFECT* dropEffect, COleDataObject* pDataObject, DWORD dwKeyState, const CPoint& point, HDC transformHDC);	// default (no) implementation
	virtual bool	DragOver					(DROPEFFECT* dropEffect, COleDataObject* pDataObject, DWORD dwKeyState, const CPoint& point, HDC transformHDC);	// default (no) implementation
	virtual bool	Drop						(COleDataObject* pDataObject, DROPEFFECT dropEffect, const CPoint& point, HDC transformHDC);					// default (no) implementation
	virtual bool	DropFile					(HDROP p_hDropInfo, const CPoint& point, HDC transformHDC);				// default (no) implementation
	virtual bool	MenuItemSelected			(UINT menuItemId, UINT nFlags, const CPoint& point, HDC transformHDC);	// default (no) implementation
	virtual bool	OperationCanceledByGME		(void);																	// default (no) implementation

// =============== resembles IMgaElementDecoratorEvents
	virtual void	Refresh						(void);
	virtual void	OperationCanceledByDecorator(void);
	virtual void	CursorChanged				(long newCursorID);
	virtual void	CursorRestored				(void);

	virtual void	LabelEditingStarted			(CRect& location);
	virtual void	LabelEditingFinished		(CRect& location);
	virtual void	LabelChanged				(CString& newLabel);
	virtual void	LabelMovingStarted			(UINT nType, CRect& location);
	virtual void	LabelMoving					(UINT nSide, CRect& location);
	virtual void	LabelMovingFinished			(UINT nType, CRect& location);
	virtual void	LabelMoved					(UINT nType, CPoint& point);
	virtual void	LabelResizingStarted		(UINT nType, CRect& location);
	virtual void	LabelResizing				(UINT nSide, CRect& location);
	virtual void	LabelResizingFinished		(UINT nType, CRect& locatiot);
	virtual void	LabelResized				(UINT nType, CSize& size);

	virtual void	WindowMovingStarted			(UINT nType, CRect& location);
	virtual void	WindowMoving				(UINT nSide, CRect& location);
	virtual void	WindowMovingFinished		(UINT nType, CRect& location);
	virtual void	WindowMoved					(UINT nType, CPoint& point);

	virtual void	WindowResizingStarted		(UINT nType, CRect& location);
	virtual void	WindowResizing				(UINT nSide, CRect& location);
	virtual void	WindowResizingFinished		(UINT nType, CRect& location);
	virtual void	WindowResized				(UINT nType, CSize& size);

	virtual void	GeneralOperationStarted		(void* operationData);
	virtual void	GeneralOperationFinished	(void* operationData);

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

};	// namespace DecoratorSDK

#endif //__PARTBASE_H_
