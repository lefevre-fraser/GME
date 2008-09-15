//################################################################################################
//
// Vector decorator class
//	VectorPart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "VectorPart.h"


namespace Decorator {

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

void VectorPart::RemoveLine(long index)
{
	ASSERT(index >= 0 && index < GetLineNumber());
	long i = 0;
	for(std::vector<CRect>::iterator ii = lines.begin(); i < GetLineNumber() && ii != lines.end(); i++, ++ii) {
		if (i == index) {
			lines.erase(ii);
		}
	}
}

CRect VectorPart::GetLine(long index) const
{
	ASSERT(index >= 0 && index < GetLineNumber());
	return lines[index];
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
	for(std::vector<CRect>::iterator ii = lines.begin(); ii != lines.end(); ++ii) {
		// TODO: draw line
	}
	// TODO: draw the vector graphics to the DC into desired size
	ResizablePart::Draw(pDC);
}

// New functions
void VectorPart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
							  HWND parentWnd, PreferenceMap& preferences)
{
	ResizablePart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);
}

}; // namespace Decorator
