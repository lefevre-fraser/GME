//################################################################################################
//
// Vector decorator class
//	VectorPart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "VectorPart.h"


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : VectorPart
//
//################################################################################################

VectorPart::VectorPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink):
	ResizablePart(pPart, eventSink)
{
}

VectorPart::~VectorPart()
{
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

void VectorPart::Draw(CDC* pDC)
{
// TODO: setting colors and brush
//	dc.SelectObject(DecoratorSDK::getFacilities().getBrush(META_CLASS_BGCOLOR));
//	dc.SelectObject(DecoratorSDK::getFacilities().getPen(m_isActive ? m_color : GME_GRAYED_OUT_COLOR));

	for(std::vector<VectorCommand>::iterator ii = m_Commands.begin(); ii != m_Commands.end(); ++ii) {
		switch((*ii).code) {
			case VectorCommand::BeginPath:			pDC->BeginPath();
			case VectorCommand::EndPath:			pDC->EndPath();
			case VectorCommand::StrokeAndFillPath:	pDC->StrokeAndFillPath();
			case VectorCommand::MoveTo:				pDC->MoveTo((*ii).coords.TopLeft());
			case VectorCommand::LineTo:				pDC->LineTo((*ii).coords.TopLeft());
			case VectorCommand::Rectangle:			pDC->Rectangle((*ii).coords);
		}
	}
	ResizablePart::Draw(pDC);
}

// New functions
void VectorPart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
							  HWND parentWnd, PreferenceMap& preferences)
{
	ResizablePart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);
}

CRect	VectorPart::ResolveCoordinateConstants(const CRect& rect)
{
	ASSERT(!m_Extents.IsRectEmpty());
	CRect resolved = rect;
	resolved.left	= ResolveCoordinate(resolved.left);
	resolved.right	= ResolveCoordinate(resolved.right);
	resolved.top	= ResolveCoordinate(resolved.top);
	resolved.bottom	= ResolveCoordinate(resolved.bottom);

	return resolved;
}

long	VectorPart::ResolveCoordinate(long coord)
{
	switch (coord) {
	case VectorCommand::LeftMost:
		return m_Extents.left;
	case VectorCommand::RightMost:
		return m_Extents.right;
	case VectorCommand::TopMost:
		return m_Extents.top;
	case VectorCommand::BottomMost:
		return m_Extents.bottom;
	}

	return coord;
}

}; // namespace DecoratorSDK
