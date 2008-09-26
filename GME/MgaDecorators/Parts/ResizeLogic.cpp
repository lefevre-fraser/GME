//################################################################################################
//
// Resize logic common codes class
//	ResizeLogic.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "ResizeLogic.h"
#include "../DecoratorExceptions.h"


namespace Decorator {

//################################################################################################
//
// CLASS : ResizeLogic
//
//################################################################################################

const int	ResizeLogic::sensitivityDistance = 6;

ResizeLogic::ResizeLogic(PartBase* pPart):
	m_parentPart(pPart)
{
}

ResizeLogic::~ResizeLogic()
{
}

void ResizeLogic::Initialize(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO)
{
	m_resizeState				= NotInResize;
	m_resizeFeatures			= Resizeable;
	m_targetLocation.SetRectEmpty();
	m_bCursorSaved				= false;
}

void ResizeLogic::Destroy(void)
{
	OperationCanceledByGME();
}

void ResizeLogic::Draw(CDC* pDC)
{
	if ((m_resizeFeatures & DrawResizeCorner) != 0) {
		// draw resize corner
	} else if ((m_resizeFeatures & DrawSelectionRectangle) != 0) {
		// draw selection rectangle
	}
}

// New functions
void ResizeLogic::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
							   HWND parentWnd, PreferenceMap& preferences)
{
	m_parentWnd = parentWnd;
	Initialize(pProject, pPart, pFCO);
}

bool ResizeLogic::MouseMoved(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	if (m_parentPart->IsActive()) {
		m_targetLocation = m_parentPart->GetLocation();
		ResizeType resizeTypeCandidate = DeterminePotentialResize(point);
		HRESULT retVal = S_OK;
		if (m_resizeState == NotInResize) {
			if (resizeTypeCandidate != NotInResize) {
				ChangeCursorForm(resizeTypeCandidate);
				m_bCursorSaved = true;
				return true;
			} else {
				RestoreCursor();
			}
		} else {
			long deltax = point.x - m_previousMousePosition.x;
			long deltay = point.y - m_previousMousePosition.y;
			// Change size/m_targetLocation
			switch(m_resizeState) {
				case RightEdgeResize:			m_targetLocation.InflateRect(0,			0,			deltax,	0		);	break;
				case BottomEdgeResize:			m_targetLocation.InflateRect(0,			0,			0,		deltay	);	break;
				case LeftEdgeResize:			m_targetLocation.InflateRect(-deltax,	0,			0,		0		);	break;
				case TopEdgeResize:				m_targetLocation.InflateRect(0,			-deltay,	0,		0		);	break;
				case TopLeftCornerResize:		m_targetLocation.InflateRect(-deltax,	-deltay,	0,		0		);	break;
				case TopRightCornerResize:		m_targetLocation.InflateRect(0,			-deltay,	deltax,	0		);	break;
				case BottomRightCornerResize:	m_targetLocation.InflateRect(0,			0,			deltax,	deltay	);	break;
				case BottomLeftCornerResize:	m_targetLocation.InflateRect(-deltax,	0,			0,		deltay	);	break;
				case MoveOperation:				m_targetLocation.OffsetRect(deltax, deltay);							break;
			}
			if (m_resizeState == MoveOperation)
				m_parentPart->WindowMoving(nFlags, m_targetLocation);
			else
				m_parentPart->WindowResizing(nFlags, m_targetLocation);
			m_previousMousePosition = point;
			return true;
		}
	} else {
		RestoreCursor();
	}

	return false;
}

bool ResizeLogic::MouseLeftButtonDown(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	if (m_parentPart->IsActive() && m_resizeState == NotInResize) {
		ResizeType resizeTypeCandidate = DeterminePotentialResize(point);
		if (resizeTypeCandidate != NotInResize) {
			m_originalMousePosition = point;
			m_previousMousePosition = point;
			m_originalLocation = m_targetLocation;
			m_resizeState = resizeTypeCandidate;
			if (resizeTypeCandidate == MoveOperation)
				m_parentPart->WindowMovingStarted(nFlags, m_targetLocation);
			else
				m_parentPart->WindowResizingStarted(nFlags, m_targetLocation);
			return true;
		}
	}

	return false;
}

bool ResizeLogic::MouseLeftButtonUp(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	if (m_parentPart->IsActive() && m_resizeState != NotInResize) {
		if (m_resizeState == MoveOperation) {
			long deltax = m_targetLocation.left - m_originalLocation.left;
			long deltay = m_targetLocation.top - m_originalLocation.top;
			m_parentPart->WindowMoved(nFlags, CPoint(deltax, deltay));
			m_parentPart->WindowMovingFinished(nFlags, m_targetLocation);
		} else {
			long deltax = m_targetLocation.Width() - m_originalLocation.Width();
			long deltay = m_targetLocation.Height() - m_originalLocation.Height();
			m_parentPart->WindowResized(nFlags, CSize(deltax, deltay));
			m_parentPart->WindowResizingFinished(nFlags, m_targetLocation);
		}
		m_resizeState = NotInResize;
		RestoreCursor();
		return true;
	}

	return false;
}

bool ResizeLogic::MouseRightButtonDown(HMENU hCtxMenu, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	if (m_parentPart->IsActive()) {
		CRect ptRect = m_parentPart->GetLocation();
		if (ptRect.PtInRect(point)) {
			::AppendMenu(hCtxMenu, MF_STRING | MF_ENABLED, CTX_MENU_ID_RESETSIZE, CTX_MENU_STR_RESETSIZE);
			return true;
		}
	}

	return false;
}

bool ResizeLogic::MenuItemSelected(UINT menuItemId, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	if (menuItemId == CTX_MENU_ID_RESETSIZE) {
		CRect pRect = m_parentPart->GetLocation();
		CSize normalPreferredSize = m_parentPart->GetPreferredSize();
		long deltax = normalPreferredSize.cx - pRect.Width();
		long deltay = normalPreferredSize.cy - pRect.Height();
		if (deltax != 0 || deltay != 0) {
			m_parentPart->WindowResizingStarted(nFlags, pRect);
			pRect.InflateRect(0, 0, deltax, deltay);
			m_parentPart->WindowResizing(nFlags, pRect);
			m_parentPart->WindowResized(nFlags, CSize(deltax, deltay));
			m_parentPart->WindowResizingFinished(nFlags, pRect);
		}
		return true;
	}

	return false;
}

bool ResizeLogic::OperationCanceledByGME(void)
{
	if (m_resizeState != NotInResize) {
		m_resizeState = NotInResize;
		RestoreCursor();
		m_targetLocation = m_originalLocation;
	}
	return true;
}

ResizeLogic::ResizeType ResizeLogic::DeterminePotentialResize(CPoint cursorPoint) const
{
	// Topleft corner
	CRect cornerRect(m_targetLocation.left, m_targetLocation.top, m_targetLocation.left + 1, m_targetLocation.top + 1);
	cornerRect.InflateRect(sensitivityDistance, sensitivityDistance);
	if (cornerRect.PtInRect(cursorPoint))
		return TopLeftCornerResize;
	// Topright corner
	cornerRect.SetRect(m_targetLocation.right - 1, m_targetLocation.top, m_targetLocation.right, m_targetLocation.top + 1);
	cornerRect.InflateRect(sensitivityDistance, sensitivityDistance);
	if (cornerRect.PtInRect(cursorPoint))
		return TopRightCornerResize;
	// Bottomright corner
	cornerRect.SetRect(m_targetLocation.right - 1, m_targetLocation.bottom - 1, m_targetLocation.right, m_targetLocation.bottom);
	cornerRect.InflateRect(sensitivityDistance, sensitivityDistance);
	if (cornerRect.PtInRect(cursorPoint))
		return BottomRightCornerResize;
	// Bottomleft corner
	cornerRect.SetRect(m_targetLocation.left, m_targetLocation.bottom - 1, m_targetLocation.left + 1, m_targetLocation.bottom);
	cornerRect.InflateRect(sensitivityDistance, sensitivityDistance);
	if (cornerRect.PtInRect(cursorPoint))
		return BottomLeftCornerResize;

	// Left edge
	cornerRect.SetRect(m_targetLocation.left, m_targetLocation.top, m_targetLocation.left + 1, m_targetLocation.bottom);
	cornerRect.InflateRect(sensitivityDistance, sensitivityDistance);
	if (cornerRect.PtInRect(cursorPoint))
		return LeftEdgeResize;
	// Top edge
	cornerRect.SetRect(m_targetLocation.left, m_targetLocation.top, m_targetLocation.right, m_targetLocation.top + 1);
	cornerRect.InflateRect(sensitivityDistance, sensitivityDistance);
	if (cornerRect.PtInRect(cursorPoint))
		return TopEdgeResize;
	// Right edge
	cornerRect.SetRect(m_targetLocation.right - 1, m_targetLocation.top, m_targetLocation.right, m_targetLocation.bottom);
	cornerRect.InflateRect(sensitivityDistance, sensitivityDistance);
	if (cornerRect.PtInRect(cursorPoint))
		return RightEdgeResize;
	// Bottom edge
	cornerRect.SetRect(m_targetLocation.left, m_targetLocation.bottom - 1, m_targetLocation.right, m_targetLocation.bottom);
	cornerRect.InflateRect(sensitivityDistance, sensitivityDistance);
	if (cornerRect.PtInRect(cursorPoint))
		return BottomEdgeResize;

	// Inside rect: move operation possible
	if ((m_resizeFeatures & Movable) != 0) {
		cornerRect = m_targetLocation;
		cornerRect.InflateRect(-sensitivityDistance, -sensitivityDistance);
		if (cornerRect.PtInRect(cursorPoint))
			return MoveOperation;
	}

	return NotInResize;
}

void ResizeLogic::ChangeCursorForm(ResizeType resizeType, bool notify)
{
	LPTSTR cursorRes = NULL;
	switch(resizeType) {
		case NotInResize:				cursorRes = IDC_ARROW;		break;
		case RightEdgeResize:			cursorRes = IDC_SIZEWE;		break;
		case BottomEdgeResize:			cursorRes = IDC_SIZENS;		break;
		case LeftEdgeResize:			cursorRes = IDC_SIZEWE;		break;
		case TopEdgeResize:				cursorRes = IDC_SIZENS;		break;
		case TopLeftCornerResize:		cursorRes = IDC_SIZENWSE;	break;
		case TopRightCornerResize:		cursorRes = IDC_SIZENESW;	break;
		case BottomRightCornerResize:	cursorRes = IDC_SIZENWSE;	break;
		case BottomLeftCornerResize:	cursorRes = IDC_SIZENESW;	break;
		case MoveOperation:				cursorRes = IDC_SIZEALL;	break;
	}
	HCURSOR wantedCursor = LoadCursor(NULL, cursorRes);
	m_originalCursor = SetCursor(wantedCursor);
	if (notify)
		m_parentPart->CursorChanged((long)cursorRes);
}

void ResizeLogic::RestoreCursor(void)
{
	if (m_bCursorSaved) {
		SetCursor(m_originalCursor);
		m_bCursorSaved = false;
		m_parentPart->CursorRestored();
	}
}

}; // namespace Decorator
