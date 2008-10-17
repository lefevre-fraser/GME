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

ComplexCoordCommand::ComplexCoordCommand(CoordinateConstants coordConst):
	CoordCommand()
{
	m_coordConstList.push_back(coordConst);
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
	double result = static_cast<double> (ResolveCoord(m_coordConstList[0], extents));
	for (unsigned long i = 0; i < m_coordOperationList.size(); i++) {
		switch (m_coordOperationList[i]) {
			case CoordAdd:			result = result + ResolveCoord(m_coordConstList[i + 1], extents) * m_coordWeightList[i]; break;
			case CoordSubstract:	result = result - ResolveCoord(m_coordConstList[i + 1], extents) * m_coordWeightList[i]; break;
			case CoordDivide:		result = result / ResolveCoord(m_coordConstList[i + 1], extents) * m_coordWeightList[i]; break;
			case CoordMultiply:		result = result * ResolveCoord(m_coordConstList[i + 1], extents) * m_coordWeightList[i]; break;
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
	ResizablePart(pPart, eventSink)
{
	penColorVariableName	= PREF_COLOR;
	burshColorVariableName	= PREF_COLOR;
}

VectorPart::~VectorPart()
{
	RemoveAllCommands();
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
			case VectorCommand::EndPath:			pDC->EndPath();												break;
			case VectorCommand::StrokeAndFillPath:	pDC->StrokeAndFillPath();									break;
			case VectorCommand::MoveTo:				pDC->MoveTo((*ii).GetResolvedCoords(m_Extents).TopLeft());	break;
			case VectorCommand::LineTo:				pDC->LineTo((*ii).GetResolvedCoords(m_Extents).TopLeft());	break;
			case VectorCommand::Rectangle:			pDC->Rectangle((*ii).GetResolvedCoords(m_Extents));			break;
			case VectorCommand::Ellipse:			pDC->Ellipse((*ii).GetResolvedCoords(m_Extents));			break;
		}
	}
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
}

void VectorPart::SetPen(CDC* pDC)
{
	pDC->SelectObject(DecoratorSDK::getFacilities().getPen(m_bActive ? m_crPen : COLOR_GRAYED_OUT));
}

void VectorPart::SetBrush(CDC* pDC)
{
	pDC->SelectObject(DecoratorSDK::getFacilities().getBrush(m_bActive ? m_crBrush : COLOR_GRAYED_OUT));
}

}; // namespace DecoratorSDK
