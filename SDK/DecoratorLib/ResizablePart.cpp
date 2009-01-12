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
	PartBase			(pPart, eventSink),
	m_bReadCustomSize	(true),
	m_bResetSize		(false),
	resizeLogic			(NULL)
{
	resizeLogic.SetParentPart(this);
}

ResizablePart::~ResizablePart()
{
}

void ResizablePart::Initialize(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO)
{
	if (m_spFCO)
		resizeLogic.SetResizeFeatures(ResizeLogic::Resizeable);

	PartBase::Initialize(pProject, pPart, pFCO);
}

void ResizablePart::Destroy(void)
{
	if (m_bResizable)
		resizeLogic.Destroy();
	OperationCanceledByGME();
}

feature_code ResizablePart::GetFeatures(void) const
{
	return m_bResizable ? F_RESIZABLE | F_MOUSEEVENTS : 0;
}

CSize ResizablePart::GetPreferredSize(void) const
{
	long cx = 0;
	long cy = 0;

	if (m_bResizable && m_bReadCustomSize) {
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
					if (part) {
						CComBSTR regName(PREF_PREFERREDSIZE);
						COMTHROW(part->get_RegistryValue(regName, &bstrVal));
					}
				}

				m_spProject->CommitTransaction();
			} else {
				COMTHROW(m_spFCO->get_Part(mAspect, &part));
				if (part) {
					CComBSTR regName(PREF_PREFERREDSIZE);
					COMTHROW(part->get_RegistryValue(regName, &bstrVal));
				}
			}

			if (bstrVal) {
				int numConverted = swscanf(bstrVal, OLESTR("%ld,%ld"), &cx, &cy);
				if (numConverted != 2) {
					cx = 0;
					cy = 0;
				}
			}
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
	resizeLogic.SetResizeTargetLocation(location);
}

CRect ResizablePart::GetLocation(void) const
{
	return PartBase::GetLocation();
}

void ResizablePart::Draw(CDC* pDC, Gdiplus::Graphics* gdip)
{
	if (m_bResizable)
		resizeLogic.Draw(pDC, gdip);
}

// New functions
void ResizablePart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
								 HWND parentWnd, PreferenceMap& preferences)
{
	if (pFCO)
		resizeLogic.InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);
	PartBase::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);
}

bool ResizablePart::MouseMoved(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	if (m_bResizable)
		return resizeLogic.MouseMoved(nFlags, point, transformHDC);

	return false;
}

bool ResizablePart::MouseLeftButtonDown(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	if (m_bResizable)
		return resizeLogic.MouseLeftButtonDown(nFlags, point, transformHDC);

	return false;
}

bool ResizablePart::MouseLeftButtonUp(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	if (m_bResizable)
		return resizeLogic.MouseLeftButtonUp(nFlags, point, transformHDC);

	return false;
}

bool ResizablePart::MouseRightButtonDown(HMENU hCtxMenu, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	if (m_bResizable && m_bActive && ResizablePart::GetPreferredSize() != CSize(0, 0))
		return resizeLogic.MouseRightButtonDown(hCtxMenu, nFlags, point, transformHDC);

	return false;
}

bool ResizablePart::MenuItemSelected(UINT menuItemId, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	bool handled = false;
	if (m_bResizable) {
		m_bReadCustomSize = false;
		handled = resizeLogic.MenuItemSelected(menuItemId, nFlags, point, transformHDC);
		m_bReadCustomSize = true;
	}

	return handled;
}

bool ResizablePart::OperationCanceledByGME(void)
{
	SetLocation(resizeLogic.GetOriginalLocation());
	if (m_bResizable)
		return resizeLogic.OperationCanceledByGME();

	return false;
}

void ResizablePart::WindowResizing(UINT nSide, CRect& location)
{
	ASSERT(m_bResizable);
	SetLocation(location);
	PartBase::WindowResizing(nSide, location);
}

void ResizablePart::WindowResizingFinished(UINT nSide, CRect& location)
{
	ASSERT(m_bResizable);
	SetLocation(location);
	if (m_bResizable && resizeLogic.IsSizeChanged()) {
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

				ASSERT(part);
				if (part) {
					CPoint pt = location.TopLeft();
					COMTHROW(part->SetGmeAttrs(0, pt.x, pt.y));
					// Save preferred size part
					CSize size(m_bResetSize ? 0 : location.Width(), m_bResetSize ? 0 : location.Height());
					if (size.cx >= 0 && size.cy >= 0) {
						OLECHAR bbc[40];
						swprintf(bbc, 40, OLESTR("%ld,%ld"), size.cx, size.cy);
						CComBSTR bb(bbc);
						COMTHROW(part->put_RegistryValue(CComBSTR(PREF_PREFERREDSIZE), bb));
					}
				}
			}

			if (!inTrans) {
				m_spProject->CommitTransaction();
			}
		}
		catch(hresult_exception &e)
		{
			m_bResetSize = false;
			ASSERT(FAILED(e.hr));
			SetErrorInfo(e.hr);
		}
	}
	m_bResetSize = false;
	PartBase::WindowResizingFinished(nSide, location);
}

}; // namespace DecoratorSDK
