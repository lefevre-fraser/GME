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
}

void ResizablePart::Initialize(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO)
{
	location.SetRectEmpty();
	if (m_spFCO)
		resizeLogic.SetResizeFeatures(ResizeLogic::Resizeable);

	PartBase::Initialize(pProject, pPart, pFCO);
}

void ResizablePart::Destroy(void)
{
	if (m_spFCO)
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

	if (m_spFCO) {
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
	}

	return CSize(cx, cy);
}


void ResizablePart::SetLocation(const CRect& location)
{
	PartBase::SetLocation(location);
	if (m_spFCO)
		resizeLogic.SetResizeTargetLocation(location);
}

CRect ResizablePart::GetLocation(void) const
{
	return PartBase::GetLocation();
}

void ResizablePart::Draw(CDC* pDC)
{
	if (m_spFCO)
		resizeLogic.Draw(pDC);
}

// New functions
void ResizablePart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
								 HWND parentWnd, PreferenceMap& preferences)
{
	if (m_spFCO)
		resizeLogic.InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);
	PartBase::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);
}

bool ResizablePart::MouseMoved(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	if (m_spFCO)
		return resizeLogic.MouseMoved(nFlags, point, transformHDC);

	return false;
}

bool ResizablePart::MouseLeftButtonDown(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	if (m_spFCO)
		return resizeLogic.MouseLeftButtonDown(nFlags, point, transformHDC);

	return false;
}

bool ResizablePart::MouseLeftButtonUp(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	if (m_spFCO)
		return resizeLogic.MouseLeftButtonUp(nFlags, point, transformHDC);

	return false;
}

bool ResizablePart::OperationCanceledByGME(void)
{
	if (m_spFCO)
		return resizeLogic.OperationCanceledByGME();

	return false;
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
