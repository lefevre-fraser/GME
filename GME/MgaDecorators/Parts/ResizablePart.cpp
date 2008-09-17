//################################################################################################
//
// Resizable part class (decorator part)
//	ResizablePart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "ResizablePart.h"
#include "../DecoratorExceptions.h"


namespace Decorator {

//################################################################################################
//
// CLASS : ResizablePart
//
//################################################################################################

ResizablePart::ResizablePart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink):
	PartBase(pPart, eventSink),
	resizeLogic(NULL)
{
	resizeLogic.SetParentPart(this);
}

ResizablePart::~ResizablePart()
{
	resizeLogic.Destroy();
}

void ResizablePart::Initialize(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO)
{
	location.SetRectEmpty();
	resizeLogic.SetResizeFeatures(ResizeLogic::Resizeable);

	PartBase::Initialize(pProject, pPart, pFCO);
}

void ResizablePart::Destroy(void)
{
	resizeLogic.Destroy();
	OperationCanceledByGME();
}

feature_code ResizablePart::GetFeatures(void) const
{
	return F_RESIZABLE | F_MOUSEEVENTS;
}

CSize ResizablePart::GetPreferredSize(void) const
{
	long cx = 0;
	long cy = 0;

	COMTRY {
		CComPtr<IMgaMetaAspect> mAspect;
		COMTHROW(m_spPart->get_ParentAspect(&mAspect));
		CComPtr<IMgaPart> part;
		COMTHROW(m_spFCO->get_Part(mAspect, &part));
		CComBSTR regName(PREF_PREFERREDSIZE);
		CComBSTR bstrVal;
		COMTHROW(part->get_RegistryValue(regName, &bstrVal));
		CString sizeStr;
		CopyTo(bstrVal, sizeStr);
		if (!sizeStr.IsEmpty())
			ASSERT(sscanf(sizeStr, "%ld,%ld", &cx, &cy) == 2);
	}
	catch(hresult_exception &e)
	{
		ASSERT(FAILED(e.hr));
		SetErrorInfo(e.hr);
	}

	return CSize(cx, cy);
}


void ResizablePart::SetLocation(const CRect& location)
{
	PartBase::SetLocation(location);
	resizeLogic.SetResizeTargetLocation(location);
}

CRect ResizablePart::GetLocation(void) const
{
	return PartBase::GetLocation();
}

void ResizablePart::Draw(CDC* pDC)
{
	resizeLogic.Draw(pDC);
}

// New functions
void ResizablePart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
								 HWND parentWnd, PreferenceMap& preferences)
{
	resizeLogic.InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);
	PartBase::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);
}

bool ResizablePart::MouseMoved(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return resizeLogic.MouseMoved(nFlags, point, transformHDC);
}

bool ResizablePart::MouseLeftButtonDown(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return resizeLogic.MouseLeftButtonDown(nFlags, point, transformHDC);
}

bool ResizablePart::MouseLeftButtonUp(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return resizeLogic.MouseLeftButtonUp(nFlags, point, transformHDC);
}

bool ResizablePart::OperationCanceledByGME(void)
{
	return resizeLogic.OperationCanceledByGME();
}

void ResizablePart::WindowResizing(UINT nSide, CRect& location)
{
	SetLocation(location);
	PartBase::WindowResizing(nSide, location);
}

void ResizablePart::WindowResizingFinished(UINT nSide, CRect& location)
{
	SetLocation(location);
	PartBase::WindowResizingFinished(nSide, location);
}

}; // namespace Decorator
