//################################################################################################
//
// Resize logic common codes class
//	ResizeLogic.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "ResizeLogic.h"
#include "DecoratorExceptions.h"
#include "ResizablePart.h"


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : ResizeLogic
//
//################################################################################################

ResizeLogic::ResizeLogic(PartBase* pPart):
	m_parentPart(pPart)
{
	m_minSize.SetSize(0, 0);
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

void ResizeLogic::Draw(CDC* pDC, Gdiplus::Graphics* gdip)
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
			CRect newTargetLocation = m_targetLocation;
			switch(m_resizeState) {
				case RightEdgeResize:			newTargetLocation.InflateRect(0,		0,			deltax,	0		);	break;
				case BottomEdgeResize:			newTargetLocation.InflateRect(0,		0,			0,		deltay	);	break;
				case LeftEdgeResize:			newTargetLocation.InflateRect(-deltax,	0,			0,		0		);	break;
				case TopEdgeResize:				newTargetLocation.InflateRect(0,		-deltay,	0,		0		);	break;
				case TopLeftCornerResize:		newTargetLocation.InflateRect(-deltax,	-deltay,	0,		0		);	break;
				case TopRightCornerResize:		newTargetLocation.InflateRect(0,		-deltay,	deltax,	0		);	break;
				case BottomRightCornerResize:	newTargetLocation.InflateRect(0,		0,			deltax,	deltay	);	break;
				case BottomLeftCornerResize:	newTargetLocation.InflateRect(-deltax,	0,			0,		deltay	);	break;
				case MoveOperation:				newTargetLocation.OffsetRect(deltax, deltay);							break;
			}
			long widthMinLimit = max(5, m_minSize.cx);
			long heightMinLimit = max(5, m_minSize.cy);
			if ((m_resizeState == RightEdgeResize || m_resizeState == LeftEdgeResize) &&
				newTargetLocation.Width() < widthMinLimit)
			{
				return true;	// Don't resize
			} else if ((m_resizeState == BottomEdgeResize || m_resizeState == TopEdgeResize) &&
						newTargetLocation.Height() < heightMinLimit)
			{
				return true;	// Don't resize
			} else if (m_targetLocation.Width () == widthMinLimit && m_targetLocation.Height () == heightMinLimit &&
						deltax <= 0 && deltay <= 0)
			{
				return true;	// Don't resize
			} else if (m_resizeState == TopLeftCornerResize || m_resizeState == BottomLeftCornerResize ||
						m_resizeState == TopRightCornerResize || m_resizeState == BottomRightCornerResize)
			{
				if (newTargetLocation.Width() < widthMinLimit) {
					newTargetLocation.left = m_targetLocation.left;
					newTargetLocation.right = m_targetLocation.right;
				}
				if (newTargetLocation.Height() < heightMinLimit) {
					newTargetLocation.top = m_targetLocation.top;
					newTargetLocation.bottom = m_targetLocation.bottom;
				}
			}
			m_targetLocation = newTargetLocation;
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
		ResizablePart* resizablePart = dynamic_cast<ResizablePart*> (m_parentPart);
		if (resizablePart != NULL)
			resizablePart->m_bResetSize = true;
		m_parentPart->WindowResizingStarted(nFlags, pRect);
		pRect.InflateRect(0, 0, deltax, deltay);
		m_parentPart->WindowResizing(nFlags, pRect);
		m_parentPart->WindowResized(nFlags, CSize(deltax, deltay));
		m_parentPart->WindowResizingFinished(nFlags, pRect);
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
	long actualSensitivity = 0;
	long targetWidth = m_targetLocation.Width();
	long targetHeight = m_targetLocation.Height();
	if (targetWidth <= 35 || targetHeight <= 25) {
		actualSensitivity = DECORATOR_MINSENSITIVITYDISTANCE;
	} else if (targetWidth >= 80 && targetHeight >= 40) {
		actualSensitivity = DECORATOR_MAXSENSITIVITYDISTANCE;
	} else {
		long actualSensitivityByWidth = ((targetWidth - 35) * 6 + (80 - targetWidth) * 2) / targetWidth;
		long actualSensitivityByHeight = ((targetHeight - 25) * 6 + (40 - targetHeight) * 2) / targetHeight;
		actualSensitivity = min(actualSensitivityByWidth, actualSensitivityByHeight);
		actualSensitivity = min(max(actualSensitivity, DECORATOR_MINSENSITIVITYDISTANCE), DECORATOR_MAXSENSITIVITYDISTANCE);
	}
	CRect cornerRect(m_targetLocation.left, m_targetLocation.top, m_targetLocation.left + 1, m_targetLocation.top + 1);
	cornerRect.InflateRect(actualSensitivity, actualSensitivity);
	if (cornerRect.PtInRect(cursorPoint))
		return TopLeftCornerResize;
	// Topright corner
	cornerRect.SetRect(m_targetLocation.right - 1, m_targetLocation.top, m_targetLocation.right, m_targetLocation.top + 1);
	cornerRect.InflateRect(actualSensitivity, actualSensitivity);
	if (cornerRect.PtInRect(cursorPoint))
		return TopRightCornerResize;
	// Bottomright corner
	cornerRect.SetRect(m_targetLocation.right - 1, m_targetLocation.bottom - 1, m_targetLocation.right, m_targetLocation.bottom);
	cornerRect.InflateRect(actualSensitivity, actualSensitivity);
	if (cornerRect.PtInRect(cursorPoint))
		return BottomRightCornerResize;
	// Bottomleft corner
	cornerRect.SetRect(m_targetLocation.left, m_targetLocation.bottom - 1, m_targetLocation.left + 1, m_targetLocation.bottom);
	cornerRect.InflateRect(actualSensitivity, actualSensitivity);
	if (cornerRect.PtInRect(cursorPoint))
		return BottomLeftCornerResize;

	// Left edge
	cornerRect.SetRect(m_targetLocation.left, m_targetLocation.top, m_targetLocation.left + 1, m_targetLocation.bottom);
	cornerRect.InflateRect(actualSensitivity, actualSensitivity);
	if (cornerRect.PtInRect(cursorPoint))
		return LeftEdgeResize;
	// Top edge
	cornerRect.SetRect(m_targetLocation.left, m_targetLocation.top, m_targetLocation.right, m_targetLocation.top + 1);
	cornerRect.InflateRect(actualSensitivity, actualSensitivity);
	if (cornerRect.PtInRect(cursorPoint))
		return TopEdgeResize;
	// Right edge
	cornerRect.SetRect(m_targetLocation.right - 1, m_targetLocation.top, m_targetLocation.right, m_targetLocation.bottom);
	cornerRect.InflateRect(actualSensitivity, actualSensitivity);
	if (cornerRect.PtInRect(cursorPoint))
		return RightEdgeResize;
	// Bottom edge
	cornerRect.SetRect(m_targetLocation.left, m_targetLocation.bottom - 1, m_targetLocation.right, m_targetLocation.bottom);
	cornerRect.InflateRect(actualSensitivity, actualSensitivity);
	if (cornerRect.PtInRect(cursorPoint))
		return BottomEdgeResize;

	// Inside rect: move operation possible
	if ((m_resizeFeatures & Movable) != 0) {
		cornerRect = m_targetLocation;
		cornerRect.InflateRect(-actualSensitivity, -actualSensitivity);
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

}; // namespace DecoratorSDK
