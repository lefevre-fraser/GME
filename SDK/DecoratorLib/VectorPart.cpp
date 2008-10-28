//################################################################################################
//
// Vector decorator class
//	VectorPart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "VectorPart.h"


namespace DecoratorSDK {

static long	ResolveCoord(CoordinateConstants coordConst, const CRect& extents)
{
	switch (coordConst) {
		case ZeroConstant:	return 0;
		case LeftMost:		return extents.left;
		case TopMost:		return extents.top;
		case RightMost:		return extents.right;
		case BottomMost:	return extents.bottom;
		case OneConstant:	return 1;
	}
	return -1;
}

//################################################################################################
//
// CLASS : SimpleCoordCommand
//
//################################################################################################

long	SimpleCoordCommand::ResolveCoordinate(const CRect& extents) const
{
	return ResolveCoord(m_CoordConst, extents);
}

//################################################################################################
//
// CLASS : ComplexCoordCommand
//
//################################################################################################

ComplexCoordCommand::ComplexCoordCommand(CoordinateConstants coordConst, double weight, CoordinateOperations operation):
	CoordCommand()
{
	m_coordConstList.push_back(coordConst);
	m_coordWeightList.push_back(weight);
	m_coordOperationList.push_back(operation);
}

ComplexCoordCommand::~ComplexCoordCommand()
{
	m_coordConstList.clear();
	m_coordWeightList.clear();
	m_coordOperationList.clear();
}

void ComplexCoordCommand::AddCommand(CoordinateConstants constant, double weight, CoordinateOperations operation)
{
	m_coordConstList.push_back(constant);
	m_coordWeightList.push_back(weight);
	m_coordOperationList.push_back(operation);
}

long	ComplexCoordCommand::ResolveCoordinate(const CRect& extents) const
{
	double result = 0.0;
	for (unsigned long i = 0; i < m_coordOperationList.size(); i++) {
		switch (m_coordOperationList[i]) {
			case CoordAdd:			result = result + ResolveCoord(m_coordConstList[i], extents) * m_coordWeightList[i]; break;
			case CoordSubstract:	result = result - ResolveCoord(m_coordConstList[i], extents) * m_coordWeightList[i]; break;
			case CoordDivide:		result = result / ResolveCoord(m_coordConstList[i], extents) * m_coordWeightList[i]; break;
			case CoordMultiply:		result = result * ResolveCoord(m_coordConstList[i], extents) * m_coordWeightList[i]; break;
		}
	}

	return static_cast<long> (result);
}

//################################################################################################
//
// CLASS : VectorCommand
//
//################################################################################################

CRect	VectorCommand::GetResolvedCoords(const CRect& extents) const
{
	ASSERT(!extents.IsRectEmpty());
	CRect resolved;
	unsigned long size = m_CoordCmds.size();
	resolved.left	= size >= 1 ? m_CoordCmds[0]->ResolveCoordinate(extents) : 0;
	resolved.top	= size >= 2 ? m_CoordCmds[1]->ResolveCoordinate(extents) : 0;
	resolved.right	= size >= 3 ? m_CoordCmds[2]->ResolveCoordinate(extents) : resolved.left;
	resolved.bottom	= size >= 4 ? m_CoordCmds[3]->ResolveCoordinate(extents) : resolved.top;

	return resolved;
}

std::vector<long> VectorCommand::GetResolvedValues(const CRect& extents) const
{
	std::vector<long> resolvedValues;
	for (std::vector<const CoordCommand*>::const_iterator ii = m_CoordCmds.begin(); ii != m_CoordCmds.end(); ++ii) {
		resolvedValues.push_back((*ii)->ResolveCoordinate(extents));
	}
	return resolvedValues;
}

VectorCommand::~VectorCommand()
{
	m_CoordCmds.clear();
};

//################################################################################################
//
// CLASS : VectorPart
//
//################################################################################################

VectorPart::VectorPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink):
	ResizablePart			(pPart, eventSink),
	m_bOriginalPenSaved		(false),
	m_originalPen			(NULL),
	m_bOriginalBrushSaved	(false),
	m_originalBrush			(NULL)
{
	penColorVariableName	= PREF_COLOR;
	burshColorVariableName	= PREF_COLOR;
}

VectorPart::~VectorPart()
{
	RemoveAllCommands();
	DisposeCoordCommands();
}

void VectorPart::RemoveCommand(long index)
{
	ASSERT(index >= 0 && index < GetCommandNumber());
	long i = 0;
	for(std::vector<VectorCommand>::iterator ii = m_Commands.begin(); i < GetCommandNumber() && ii != m_Commands.end(); i++, ++ii) {
		if (i == index) {
			m_Commands.erase(ii);
		}
	}
}

void VectorPart::RemoveLastCommand(long cmdCount)
{
	ASSERT(cmdCount > 1);
	ASSERT(cmdCount <= GetCommandNumber());
	for (long i = 0; i < cmdCount; i++)
		m_Commands.pop_back();
}

void VectorPart::DisposeCoordCommands(void)
{
	for(unsigned long i = 0; i < m_coordCommands.size(); i++) {
		delete m_coordCommands[i];
	}
	m_coordCommands.clear();
}

VectorCommand VectorPart::GetCommand(long index) const
{
	ASSERT(index >= 0 && index < GetCommandNumber());
	return m_Commands[index];
}

void VectorPart::Initialize(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO)
{
	ResizablePart::Initialize(pProject, pPart, pFCO);
}

feature_code VectorPart::GetFeatures(void) const
{
	// TODO: it depends, if it is resizable
	return F_RESIZABLE | F_MOUSEEVENTS;
}

void VectorPart::SetLocation(const CRect& location)
{
	m_Extents = location;
	ResizablePart::SetLocation(location);
}

void VectorPart::Draw(CDC* pDC)
{
	SetPen(pDC);
	SetBrush(pDC);

	for(std::vector<VectorCommand>::iterator ii = m_Commands.begin(); ii != m_Commands.end(); ++ii) {
		switch((*ii).GetCode()) {
			case VectorCommand::BeginPath:			pDC->BeginPath();											break;
			case VectorCommand::StrokeAndFillPath:	pDC->StrokeAndFillPath();									break;
			case VectorCommand::MoveTo:				pDC->MoveTo((*ii).GetResolvedCoords(m_Extents).TopLeft());	break;
			case VectorCommand::LineTo:				pDC->LineTo((*ii).GetResolvedCoords(m_Extents).TopLeft());	break;
			case VectorCommand::Rectangle:			pDC->Rectangle((*ii).GetResolvedCoords(m_Extents));			break;
			case VectorCommand::Ellipse:			pDC->Ellipse((*ii).GetResolvedCoords(m_Extents));			break;
			case VectorCommand::Polygon: {
					std::vector<long> points = (*ii).GetResolvedValues(m_Extents);
					unsigned long coordNum = points.size() / 2;
					POINT* ppoints = new POINT[coordNum];
					for (unsigned long i = 0; i < coordNum; i++) {
						ppoints[i].x = points[2 * i];
						ppoints[i].y = points[2 * i + 1];
					}
					pDC->Polygon(ppoints, coordNum);
					delete [] ppoints;
				}
				break;
			case VectorCommand::AngleArc: {
					std::vector<long> values = (*ii).GetResolvedValues(m_Extents);
					pDC->AngleArc(values[0], values[1], values[2], (float)values[3], (float)values[4]);
				}
				break;
			case VectorCommand::SelectPen: {
					std::vector<long> colors = (*ii).GetResolvedValues(m_Extents);
					pDC->SelectObject(getFacilities().getPen((COLORREF)(m_bActive ? colors[0] : colors[1])));
				}
				break;
			case VectorCommand::SelectBrush: {
					std::vector<long> colors = (*ii).GetResolvedValues(m_Extents);
					pDC->SelectObject(getFacilities().getBrush((COLORREF)(m_bActive ? colors[0] : colors[1])));
				}
				break;
			case VectorCommand::SelectNullBrush:	pDC->SelectStockObject(NULL_BRUSH);							break;
			case VectorCommand::SelectNullPen:		pDC->SelectStockObject(NULL_PEN);							break;
			case VectorCommand::EndPath: {
					pDC->EndPath();

					bool bCastShadow = false;
					long shadowThickness = 9;
					if (bCastShadow && m_spFCO) {
						// Find out how many points are in the path. Note that
						// for long strings or complex fonts, this number might be
						// gigantic!
						int nNumPts = pDC->GetPath(NULL, NULL, 0);
						if (nNumPts > 0) {
							// Allocate memory to hold points and stroke types from
							// the path.
							LPPOINT lpPoints = new POINT[nNumPts];
							if (lpPoints == NULL)
								return;
							LPBYTE lpTypes = new BYTE[nNumPts];
							if (lpTypes == NULL) {
								delete [] lpPoints;
								return;
							}

							// Now that we have the memory, really get the path data.
							nNumPts = pDC->GetPath(lpPoints, lpTypes, nNumPts);
							if (nNumPts != -1) {
								CRect rgnExtents = m_Extents;
								rgnExtents.InflateRect(shadowThickness + 1, shadowThickness + 1);
								CRgn rgn;
								rgn.CreateRectRgn(rgnExtents.left, rgnExtents.top, rgnExtents.right, rgnExtents.bottom);
								pDC->SelectClipRgn(&rgn);
								pDC->SelectClipPath(RGN_DIFF);

								CPen* oldPen = NULL;
								m_shadowStartColor = m_bActive ? m_crPen : COLOR_GRAYED_OUT;
								COLORREF shadowColor;
								OffsetPolyPoints(lpPoints, nNumPts, shadowThickness - 1);
								for (long j = 0; j < shadowThickness; j++) {
									shadowColor = RGB(((shadowThickness - j) * GetRValue(m_shadowEndColor) + j * GetRValue(m_shadowStartColor)) / shadowThickness,
													  ((shadowThickness - j) * GetGValue(m_shadowEndColor) + j * GetGValue(m_shadowStartColor)) / shadowThickness,
													  ((shadowThickness - j) * GetBValue(m_shadowEndColor) + j * GetBValue(m_shadowStartColor)) / shadowThickness);
									CPen* savePen = pDC->SelectObject(DecoratorSDK::getFacilities().getPen(shadowColor, j == shadowThickness - 1 ? 1 : 2));
									if (j == 0)
										oldPen = savePen;
									OffsetPolyPoints(lpPoints, nNumPts, -1);
									pDC->PolyDraw(lpPoints, lpTypes, nNumPts);

									// If it worked, draw the lines. Win95 and Win98 don't support
									// the PolyDraw API, so we use our own member function to do
									// similar work. If you're targeting only Windows NT, you can
									// use the PolyDraw() API and avoid the COutlineView::PolyDraw()
									// member function.
//									PolyDraw(pDC, lpPoints, lpTypes, nNumPts);
								}
								pDC->SelectClipRgn(NULL);
								pDC->SelectObject(oldPen);
							}

							// Release the memory we used
							delete [] lpPoints;
							delete [] lpTypes;
						}
					}
				}
				break;
			default: ASSERT(true);
		}
	}

	pDC->SelectObject(m_originalPen);
	pDC->SelectObject(m_originalBrush);

	ResizablePart::Draw(pDC);
}

// New functions
void VectorPart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
							  HWND parentWnd, PreferenceMap& preferences)
{
	DecoratorSDK::getFacilities().getMetaFCO(pPart, m_spMetaFCO);
	ResizablePart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);

	// Pen's Color
	m_crPen = COLOR_BLACK;
	PreferenceMap::iterator it = preferences.find(penColorVariableName);
	if (it != preferences.end()) {
		m_crPen = it->second.uValue.crValue;
	} else {
		getFacilities().getPreference(m_spFCO, m_spMetaFCO, penColorVariableName, m_crPen);
	}

	// Brush's Color
	m_crBrush = COLOR_BLACK;
	it = preferences.find(burshColorVariableName);
	if (it != preferences.end()) {
		m_crBrush = it->second.uValue.crValue;
	} else {
		getFacilities().getPreference(m_spFCO, m_spMetaFCO, penColorVariableName, m_crBrush);
	}

	m_shadowEndColor = COLOR_WHITE;
	it = preferences.find(PREF_BORDERCOLOR);
	if (it != preferences.end()) {
		m_shadowEndColor = it->second.uValue.crValue;
	} else {
		getFacilities().getPreference(m_spFCO, m_spMetaFCO, PREF_BORDERCOLOR, m_shadowEndColor);
	}
}

void VectorPart::SetPen(CDC* pDC)
{
	CPen* oldPen = pDC->SelectObject(DecoratorSDK::getFacilities().getPen(m_bActive ? m_crPen : COLOR_GRAYED_OUT));
	if (!m_bOriginalPenSaved) {
		m_originalPen = oldPen;
		m_bOriginalPenSaved = true;
	}
}

void VectorPart::SetBrush(CDC* pDC)
{
	CBrush* oldBrush = pDC->SelectObject(DecoratorSDK::getFacilities().getBrush(m_bActive ? m_crBrush : COLOR_GRAYED_OUT));
	if (!m_bOriginalBrushSaved) {
		m_originalBrush = oldBrush;
		m_bOriginalBrushSaved = true;
	}
}

void VectorPart::PolyDraw(CDC* pDC, const LPPOINT lppt, const LPBYTE lpbTypes, int cCount) const
{
	int nIndex;
	LPPOINT pptLastMoveTo = NULL;

	// for each of the points we have...
	for (nIndex = 0; nIndex < cCount; nIndex++) {
		switch(lpbTypes[nIndex]) {
		// React to information from the path by drawing the data
		// we received. For each of the points, record our own
		// "last active point" so we can close figures, lines, and
		// Beziers.

		case PT_MOVETO:
			if (pptLastMoveTo != NULL && nIndex > 0)
				pDC->LineTo(pptLastMoveTo->x, pptLastMoveTo->y);
			pDC->MoveTo(lppt[nIndex].x, lppt[nIndex].y);
			pptLastMoveTo = &lppt[nIndex];
			break;

		case PT_LINETO | PT_CLOSEFIGURE:
			pDC->LineTo(lppt[nIndex].x, lppt[nIndex].y);
			if (pptLastMoveTo != NULL)
				pDC->LineTo(pptLastMoveTo->x, pptLastMoveTo->y);
			pptLastMoveTo = NULL;
			break;

		case PT_LINETO:
			pDC->LineTo(lppt[nIndex].x, lppt[nIndex].y);
			break;

		case PT_BEZIERTO | PT_CLOSEFIGURE:
			ASSERT(nIndex + 2 <= cCount);
			pDC->PolyBezierTo(&lppt[nIndex], 3);
			nIndex += 2;
			if (pptLastMoveTo != NULL)
				pDC->LineTo(pptLastMoveTo->x, pptLastMoveTo->y);
			pptLastMoveTo = NULL;
			break;

		case PT_BEZIERTO:
			ASSERT(nIndex + 2 <= cCount);
			pDC->PolyBezierTo(&lppt[nIndex], 3);
			nIndex += 2;
			break;
		}
	}

	// If the figure was never closed and should be,
	// close it now.
	if (pptLastMoveTo != NULL && nIndex > 1)
		pDC->LineTo(pptLastMoveTo->x, pptLastMoveTo->y);
}

void VectorPart::OffsetPolyPoints(const LPPOINT lppt, int cCount, int offset) const
{
	for (int nIndex = 0; nIndex < cCount; nIndex++) {
		lppt[nIndex].x = lppt[nIndex].x + offset;
		lppt[nIndex].y = lppt[nIndex].y + offset;
	}
}

}; // namespace DecoratorSDK
