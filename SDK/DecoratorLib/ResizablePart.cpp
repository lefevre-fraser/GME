//################################################################################################
//
// Resizable part class (decorator part)
//	ResizablePart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "ResizablePart.h"
#include "DecoratorExceptions.h"


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : ResizablePart
//
//################################################################################################

ResizablePart::ResizablePart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink):
	PartBase(pPart, eventSink),
	resizeLogic(NULL),
	m_readCustomSize(true)
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

	if (m_readCustomSize && m_spFCO) {
		COMTRY {
			CComPtr<IMgaMetaAspect> mAspect;
			COMTHROW(m_spPart->get_ParentAspect(&mAspect));

			long status;
			COMTHROW(m_spProject->get_ProjectStatus(&status));
			bool inTrans = (status & 0x08L) != 0;
			CComPtr<IMgaTerritory> terr;
			CComBSTR bstrVal;
			CComPtr<IMgaPart> part;
			if (!inTrans) {
				COMTHROW(m_spProject->CreateTerritory(NULL, &terr));
				COMTHROW(m_spProject->BeginTransaction(terr, TRANSACTION_READ_ONLY));

				CComPtr<IMgaFCO> terrFco;
				COMTHROW(terr->OpenFCO(m_spFCO, &terrFco));
				status = OBJECT_ZOMBIE;
				COMTHROW(terrFco->get_Status(&status));
				if (status == OBJECT_EXISTS) {
					COMTHROW(terrFco->get_Part(mAspect, &part));
					CComBSTR regName(PREF_PREFERREDSIZE);
					COMTHROW(part->get_RegistryValue(regName, &bstrVal));
				}

				m_spProject->CommitTransaction();
			} else {
//				COMTHROW(m_spProject->get_ActiveTerritory(&terr));

				COMTHROW(m_spFCO->get_Part(mAspect, &part));
				CComBSTR regName(PREF_PREFERREDSIZE);
				COMTHROW(part->get_RegistryValue(regName, &bstrVal));
			}

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

bool ResizablePart::MouseRightButtonDown(HMENU hCtxMenu, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	if (m_spFCO && m_bActive && ResizablePart::GetPreferredSize() != CSize(0, 0))
		return resizeLogic.MouseRightButtonDown(hCtxMenu, nFlags, point, transformHDC);

	return false;
}

bool ResizablePart::MenuItemSelected(UINT menuItemId, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	bool handled = false;
	if (m_spFCO) {
		m_readCustomSize = false;
		handled = resizeLogic.MenuItemSelected(menuItemId, nFlags, point, transformHDC);
		m_readCustomSize = true;
	}

	return handled;
}

bool ResizablePart::OperationCanceledByGME(void)
{
	SetLocation(resizeLogic.GetOriginalLocation());
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
	if (m_spFCO && resizeLogic.IsSizeChanged()) {
		COMTRY {
			CComPtr<IMgaMetaAspect> mAspect;
			COMTHROW(m_spPart->get_ParentAspect(&mAspect));

			long status;
			COMTHROW(m_spProject->get_ProjectStatus(&status));
			bool inTrans = (status & 0x08L) != 0;
			CComPtr<IMgaTerritory> terr;
			if (!inTrans) {
				COMTHROW(m_spProject->CreateTerritory(NULL, &terr));
				COMTHROW(m_spProject->BeginTransaction(terr, TRANSACTION_GENERAL));
			} else {
				COMTHROW(m_spProject->get_ActiveTerritory(&terr));
			}

			CComBSTR bstrVal;
			CComPtr<IMgaFCO> terrFco;
			COMTHROW(terr->OpenFCO(m_spFCO, &terrFco));
			status = OBJECT_ZOMBIE;
			COMTHROW(terrFco->get_Status(&status));
			if (status == OBJECT_EXISTS) {
				CComPtr<IMgaPart> part;
				COMTHROW(terrFco->get_Part(mAspect, &part));

				CPoint pt = location.TopLeft();
				COMTHROW(part->SetGmeAttrs(0, pt.x, pt.y));
				// Save preferred size part
				CSize size(location.Width(), location.Height());
				if (size.cx >= 0 && size.cy >= 0) {
					OLECHAR bbc[40];
					swprintf(bbc, 40, OLESTR("%ld,%ld"), size.cx, size.cy);
					CComBSTR bb(bbc);
					COMTHROW(part->put_RegistryValue(CComBSTR(PREF_PREFERREDSIZE), bb));
				}
			}

			if (!inTrans) {
				m_spProject->CommitTransaction();
			}
		}
		catch(hresult_exception &e)
		{
			ASSERT(FAILED(e.hr));
			SetErrorInfo(e.hr);
		}
	}
	PartBase::WindowResizingFinished(nSide, location);
}

}; // namespace DecoratorSDK
