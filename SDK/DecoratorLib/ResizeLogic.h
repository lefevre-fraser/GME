//################################################################################################
//
// Resize logic common codes class
//	ResizeLogic.h
//
//################################################################################################

#ifndef __RESIZELOGIC_H_
#define __RESIZELOGIC_H_


#include "StdAfx.h"
#include "PartBase.h"


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : ResizeLogic
//
//################################################################################################

class ResizeLogic
{
public:
	enum ResizeType {
		NotInResize				= 0,
		RightEdgeResize			= 1,	// Horizontal resize
		BottomEdgeResize		= 2,	// Vertical resize
		LeftEdgeResize			= 3,	// Horizontal resize
		TopEdgeResize			= 4,	// Vertical resize
		TopLeftCornerResize		= 5,	// H + V resize
		TopRightCornerResize	= 6,	// H + V resize
		BottomRightCornerResize	= 7,	// H + V resize
		BottomLeftCornerResize	= 8,	// H + V resize
		MoveOperation			= 9
	};

	enum ResizeFeatures {
		Resizeable				= 0x0001,
		Movable					= 0x0002,
		DrawResizeCorner		= 0x0004,
		DrawSelectionRectangle	= 0x0008
	};

protected:
	PartBase*			m_parentPart;
	HWND				m_parentWnd;

	ResizeType			m_resizeState;
	short				m_resizeFeatures;
	CRect				m_targetLocation;

	CRect				m_originalLocation;
	CPoint				m_originalMousePosition;
	HCURSOR				m_originalCursor;
	bool				m_bCursorSaved;
	mutable CSize		m_minSize;

public:
	ResizeLogic(PartBase* pPart);
	virtual ~ResizeLogic();

	virtual short	GetResizeFeatures			(void) const			{ return m_resizeFeatures; };
	virtual void	SetResizeFeatures			(short resizeFeatures)	{ m_resizeFeatures = resizeFeatures; };
	virtual CRect	GetResizeTargetLocation		(void) const			{ return m_targetLocation; };
	virtual void	SetResizeTargetLocation		(CRect targetLocation)	{ m_targetLocation = targetLocation; };
	virtual void	SetParentPart				(PartBase* pPart)		{ m_parentPart = pPart; };

// =============== resembles IMgaElementDecorator
	virtual void	Initialize					(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO);
	virtual void	Destroy						(void);
	virtual void	Draw						(CDC* pDC, Gdiplus::Graphics* gdip);

	virtual void	InitializeEx				(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd, PreferenceMap& preferences);
	virtual bool	MouseMoved					(UINT nFlags, const CPoint& point, HDC transformHDC);
	virtual bool	MouseLeftButtonDown			(UINT nFlags, const CPoint& point, HDC transformHDC);
	virtual bool	MouseLeftButtonUp			(UINT nFlags, const CPoint& point, HDC transformHDC);
	virtual bool	MouseRightButtonDown		(HMENU hCtxMenu, UINT nFlags, const CPoint& point, HDC transformHDC);
	virtual bool	MenuItemSelected			(UINT menuItemId, UINT nFlags, const CPoint& point, HDC transformHDC);
	virtual bool	OperationCanceledByGME		(void);

	ResizeType		DeterminePotentialResize	(CPoint cursorPoint) const;
	bool			IsSizeChanged				(void) const { return m_targetLocation.EqualRect(m_originalLocation) == FALSE; };
	CRect			GetOriginalLocation			(void) const { return m_originalLocation; };
	void			SetMinimumSize				(CSize minSize) const { m_minSize = minSize; };

private:
	void			ChangeCursorForm			(ResizeType resizeType, bool notify = true);
	void			RestoreCursor				(void);
};

}; // namespace DecoratorSDK

#endif //__RESIZELOGIC_H_
