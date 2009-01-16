// PartBrowserPane.cpp : implementation file
//

#include "stdafx.h"
#include "PartBrowserPane.h"
#include "PartBrowserPaneFrame.h"
#include "..\Interfaces\MgaDecorator.h"
#include "..\Annotator\AnnotationDefs.h"
#include "..\Gme\GMEOLEData.h"
#include "DecoratorEventSink.h"
#include "Gme_i.c"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// from GME
typedef enum { GME_NAME_FONT = 0, GME_PORTNAME_FONT, GME_CONNLABEL_FONT, GME_FONT_KIND_NUM } GMEFontKind;
static int  fontSizes[GME_FONT_KIND_NUM]	= { 18, 15, 12 };
#define GME_DEFAULT_DECORATOR		"MGA.NewBoxDecorator"
#define DECORATOR_PREF				"decorator"
typedef CTypedPtrList<CPtrList, CRect *>	CRectList;

/////////////////////////////////////////////////////////////////////////////
// CPartBrowserPane

CPartBrowserPane::CPartBrowserPane():
	mgaProject(NULL),
	mgaMetaModel(NULL),
	currentAspectIndex(-1),
	omitPaintMessages(true)
{
	backgroundColor = ::GetSysColor(COLOR_APPWORKSPACE);
	txtMetricFont.CreateFont(fontSizes[GME_NAME_FONT], 0, 0, 0, FW_NORMAL, false, 0, 0, ANSI_CHARSET,
							 OUT_DEVICE_PRECIS, CLIP_DEFAULT_PRECIS,
							 PROOF_QUALITY, FF_SWISS, "Arial");
}

CPartBrowserPane::~CPartBrowserPane()
{
	txtMetricFont.DeleteObject();
}

CComBSTR CPartBrowserPane::GetDecoratorProgId(CComPtr<IMgaMetaFCO> metaFCO)
{
	CComBSTR pathBstr(DECORATOR_PREF);
	CComBSTR bstrVal;
	COMTHROW(metaFCO->get_RegistryValue(pathBstr,&bstrVal));
	if (bstrVal.Length() <= 0)
		bstrVal = GME_DEFAULT_DECORATOR;
	return bstrVal;
}

bool CPartBrowserPane::IsPartDisplayable(CComPtr<IMgaMetaPart> metaPart, bool debugPrint)
{
	ASSERT(metaPart != NULL);
	VARIANT_BOOL vb_primary;
	COMTHROW(metaPart->get_IsPrimary(&vb_primary));
	CComPtr<IMgaMetaRole> mmRole;
	COMTHROW(metaPart->get_Role(&mmRole));
	CComPtr<IMgaMetaFCO> mFco;
	COMTHROW(mmRole->get_Kind(&mFco));
	objtype_enum oType;
	COMTHROW(mFco->get_ObjType(&oType));

	if (debugPrint) {
		CComBSTR bstrName;
		COMTHROW(metaPart->get_Name(&bstrName));
		objtype_enum eType;
		COMTHROW(metaPart->get_ObjType(&eType));
		CString cString;
		CopyTo(bstrName, cString);
		CComBSTR bstrRoleName;
		COMTHROW(mmRole->get_DisplayedName(&bstrRoleName));
		CString cString2;
		CopyTo(bstrRoleName, cString2);
	}

	if (vb_primary != VARIANT_FALSE &&
		(oType == OBJTYPE_MODEL ||
		 oType == OBJTYPE_REFERENCE ||
		 oType != OBJTYPE_CONNECTION))
	{
		return true;
	}
	return false;
}

bool CPartBrowserPane::FindObject(CPoint &pt, PartWithDecorator& pdt)
{
	if (currentAspectIndex < 0 || pdts.size() <= 0)
		return NULL;

	try {
		std::vector<PartWithDecorator> pdtv = pdts[currentAspectIndex];
		// calculate the maximum size
		for (std::vector<PartWithDecorator>::iterator ii = pdtv.begin(); ii != pdtv.end(); ++ii) {
			ASSERT((*ii).decorator != NULL);
			long x1 = 0; long y1 = 0;
			long x2 = 0; long y2 = 0;
			COMTHROW((*ii).decorator->GetLocation(&x1, &y1, &x2, &y2));
			CRect rc (x1, y1, x2, y2);
			if (rc.PtInRect(pt)) {
				pdt = (*ii);

				long sizeX = 0;
				long sizeY = 0;
				COMTHROW((*ii).decorator->GetPreferredSize(&sizeX, &sizeY));

				return true;
			}
		}
	}
	catch (hresult_exception&) {
	}

	return false;
}

void CPartBrowserPane::CreateDecorators(CComPtr<IMgaMetaParts> metaParts)
{
	std::vector<PartWithDecorator> pdt;
	try {
		CComPtr<IMgaMetaPart> metaPart;
		MGACOLL_ITERATE(IMgaMetaPart, metaParts) {
			metaPart = MGACOLL_ITER;
			if (IsPartDisplayable(metaPart)) {
				PartWithDecorator triple;
				triple.part = metaPart;
				triple.decorEventSink = NULL;

				CComPtr<IMgaMetaRole> mmRole;
				COMTHROW(metaPart->get_Role(&mmRole));
				CComPtr<IMgaMetaFCO> mFco;
				COMTHROW(mmRole->get_Kind(&mFco));
				CComPtr<IMgaDecorator> decorator;
				CComPtr<IMgaNewDecorator> newDecorator;
				CComBSTR decoratorProgId = GetDecoratorProgId(mFco);

				CComPtr<IMgaNewDecoratorEvents> decorEventSinkIface;
				HRESULT hres = newDecorator.CoCreateInstance(PutInBstr(decoratorProgId));
				if (SUCCEEDED(hres)) {
					triple.decorEventSink = new CDecoratorEventSink();
					HRESULT hr = triple.decorEventSink->QuerySinkInterface((void**) &decorEventSinkIface);
					decorator = CComQIPtr<IMgaDecorator>(newDecorator);
					COMTHROW(newDecorator->InitializeEx(mgaProject, metaPart, NULL, decorEventSinkIface, (ULONGLONG)m_hWnd));
				} else {
					COMTHROW(decorator.CoCreateInstance(PutInBstr(decoratorProgId)));
					COMTHROW(decorator->Initialize(mgaProject, metaPart, NULL));
				}

				long sx, sy;
				COMTHROW(decorator->GetPreferredSize(&sx, &sy));
				COMTHROW(decorator->SetLocation(0, 0, sx, sy));
				triple.decorator = decorator;

				pdt.push_back(triple);
			}
		}
		MGACOLL_ITERATE_END;
	}
	catch (hresult_exception&) {
	}
	pdts.push_back(pdt);
}

void CPartBrowserPane::DestroyDecorators(void)
{
	for (std::vector<std::vector<PartWithDecorator> >::iterator ii = pdts.begin(); ii != pdts.end(); ++ii) {
		for (std::vector<PartWithDecorator>::iterator jj = (*ii).begin(); jj != (*ii).end(); ++jj) {
			(*jj).decorator->Destroy();
			(*jj).decorator.Release();
			(*jj).part.Release();
			if ((*jj).decorEventSink != NULL)
				delete (*jj).decorEventSink;
		}
		(*ii).clear();
	}
	pdts.clear();
}

void CPartBrowserPane::Resize(CRect r)
{
	if (!mgaMetaModel || currentAspectIndex < 0 || pdts.size() <= 0 || currentAspectIndex >= (int)pdts.size())
		return;

	bool oldOmitPaintMessages = omitPaintMessages;
	omitPaintMessages = true;
	ChangeAspect(currentAspectIndex);
	omitPaintMessages = oldOmitPaintMessages;

	const int leftMargin = 10;
	const int rightMargin = 10;
	const int topMargin = 10;
	const int bottomMargin = 30;

	const int xPadding = 10;
	const int yPadding = 30;

	// set the location
	int objColumn = 0;
	int leftStartPos = leftMargin + maxSize.cx / 2;
	int rowHeight = 0;

	// calculate the actual offset
	int objNumInRow = (r.Width() - leftMargin - rightMargin + xPadding) / (maxSize.cx + xPadding);
	if (objNumInRow < 1) {
		objNumInRow = 1;
		leftStartPos = r.Width() / 2 - 3;
	}

	// the pt contains the x center point, and y top point
	CPoint pt = CPoint(leftStartPos, topMargin);

	try {
		std::vector<PartWithDecorator> pdtv = pdts[currentAspectIndex];
		// calculate the maximum size
		for (std::vector<PartWithDecorator>::iterator ii = pdtv.begin(); ii != pdtv.end(); ++ii) {
			ASSERT((*ii).decorator != NULL);
			long sizeX = 0;
			long sizeY = 0;
			COMTHROW((*ii).decorator->GetPreferredSize(&sizeX, &sizeY));
			CSize size(sizeX, sizeY);

			// calculate the row height
			if (objColumn == 0) {
				rowHeight = size.cy;

				std::vector<PartWithDecorator>::iterator iibak = ii;
				for (std::vector<PartWithDecorator>::iterator jj = ++ii; jj != pdtv.end() && (objColumn + 1) < objNumInRow; ++jj) {
					ASSERT((*jj).decorator != NULL);
					long sizeX2 = 0;
					long sizeY2 = 0;
					COMTHROW((*jj).decorator->GetPreferredSize(&sizeX2, &sizeY2));
					CSize size2 (sizeX2, sizeY2);

					if (rowHeight < size2.cy)
						rowHeight = size2.cy;

					++objColumn;
				}
				ii = iibak;

				objColumn = 0;
				pt.y += rowHeight / 2;
			}

			// set the location (based on center: pt is the center)
			COMTHROW((*ii).decorator->SetLocation(pt.x - (size.cx - size.cx / 2), pt.y - (size.cy - size.cy / 2), pt.x + size.cx / 2, pt.y + size.cy / 2));

			if (++objColumn >= objNumInRow) {
				objColumn = 0;
				pt.x = leftStartPos;
				pt.y += rowHeight / 2 + yPadding;
			} else {
				pt.x += maxSize.cx + xPadding;
			}
		}
	}
	catch (hresult_exception&) {
	}

	omitPaintMessages = false;

	// if no object in this row
	if (objColumn == 0)
		pt.y -= yPadding;
	else
		pt.y += rowHeight / 2;

	pt.y += bottomMargin;

	CPartBrowserPaneFrame* parent = (CPartBrowserPaneFrame*)GetParent();
	ASSERT(parent != NULL);

	parent->SetLogicalHeight(pt.y);
	parent->SetPageHeight(r.Height());
	parent->SetScrollBar();

	Invalidate();
}

void CPartBrowserPane::SetCurrentProject(CComPtr<IMgaProject> project)
{
	if (mgaProject != NULL)
		mgaProject.Release();
	mgaProject = project;
}

void CPartBrowserPane::SetMetaModel(CComPtr<IMgaMetaModel> meta)
{
	if (mgaMetaModel != NULL)
		mgaMetaModel.Release();
	mgaMetaModel = meta;

	DestroyDecorators();
	// Store parts and crate & initialize decorators
	if (meta) {
		CComPtr<IMgaMetaAspects> mmAspects;
		COMTHROW(mgaMetaModel->get_Aspects(&mmAspects));
		long aspect_count = 0;
		COMTHROW(mmAspects->get_Count(&aspect_count));
		CComPtr<IMgaMetaAspect> mmAspect;
		MGACOLL_ITERATE(IMgaMetaAspect, mmAspects) {
			mmAspect = MGACOLL_ITER;

			CComBSTR bstr;
			COMTHROW(mmAspect->get_DisplayedName(&bstr));
			CString cString;
			CopyTo(bstr, cString);

			CComPtr<IMgaMetaParts> metaParts;
			COMTHROW(mmAspect->get_Parts(&metaParts));
			CreateDecorators(metaParts);
		}
		MGACOLL_ITERATE_END;
	}
}

void CPartBrowserPane::SetBgColor(COLORREF bgColor)
{
	backgroundColor = bgColor;
}

void CPartBrowserPane::ChangeAspect(int index)
{
	currentAspectIndex = index;
	if (currentAspectIndex < 0 || pdts.size() <= 0)
		return;

	// create a DC for text metric
	CDC textMetric;
	textMetric.CreateCompatibleDC(NULL);
	CFont* oldCFont = textMetric.SelectObject(&txtMetricFont);
	HFONT oldFont = (HFONT)oldCFont->GetSafeHandle();

	// just to be safe
	maxSize.cx = 30;
	maxSize.cy = 10;

	try {
		std::vector<PartWithDecorator> pdtv = pdts[currentAspectIndex];
		// calculate the maximum size
		for (std::vector<PartWithDecorator>::iterator ii = pdtv.begin(); ii != pdtv.end(); ++ii) {
			ASSERT((*ii).part != NULL);
			ASSERT((*ii).decorator != NULL);

			long sizeX = 0;
			long sizeY = 0;
			COMTHROW((*ii).decorator->GetPreferredSize(&sizeX, &sizeY));
			CSize size(sizeX, sizeY);

			if (maxSize.cx < size.cx)
				maxSize.cx = size.cx;

			if (maxSize.cy < size.cy)
				maxSize.cy = size.cy;

			CComBSTR nameBStr;
			COMTHROW((*ii).part->get_Name(&nameBStr));
			CString nameCString;
			CopyTo(nameBStr, nameCString);
			int text_cx = textMetric.GetTextExtent(nameCString).cx;
			if (maxSize.cx < text_cx)
				maxSize.cx = text_cx;
		}
	}
	catch (hresult_exception&) {
	}

	CPartBrowserPaneFrame* parent = (CPartBrowserPaneFrame*)GetParent();
	ASSERT(parent != NULL);

	Invalidate();

	CFont* oldCFont2 = CFont::FromHandle(oldFont);
	textMetric.SelectObject(oldCFont2);
}


BEGIN_MESSAGE_MAP(CPartBrowserPane, CWnd)
	//{{AFX_MSG_MAP(CPartBrowserPane)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPartBrowserPane message handlers

void CPartBrowserPane::OnPaint()
{
	if (omitPaintMessages) {
		CWnd::OnPaint();
		return;
	}

	CPartBrowserPaneFrame* parent = (CPartBrowserPaneFrame*)GetParent();
	ASSERT(parent != NULL);

	CPaintDC dc(this); // device context for painting
	dc.SetWindowOrg(0, parent->GetScrollPosition ());

	if (pdts.size() > 0 && currentAspectIndex >= 0) {
		try {
			std::vector<PartWithDecorator> pdtv = pdts[currentAspectIndex];
			for (std::vector<PartWithDecorator>::iterator ii = pdtv.begin(); ii != pdtv.end(); ++ii) {
				ASSERT((*ii).decorator != NULL);
				COMTHROW((*ii).decorator->Draw(dc.m_hDC));
			}
		}
		catch (hresult_exception&) {
		}
	}

	// Do not call CWnd::OnPaint() for painting messages
}

BOOL CPartBrowserPane::OnEraseBkgnd(CDC* pDC)
{
	RECT r;
	GetClientRect(&r);
	pDC->FillSolidRect(&r, backgroundColor);
	return TRUE;
	
//	return CWnd::OnEraseBkgnd(pDC);
}

void CPartBrowserPane::OnLButtonDown(UINT nFlags, CPoint point) 
{
//	CGMEEventLogger::LogGMEEvent("CPartBrowserPane::OnLButtonDown\r\n");
	
	// Needed to flush the Object Inspector and the Browser (JIRA #GME-52)
	SetFocus();

	CPartBrowserPaneFrame* parent = (CPartBrowserPaneFrame*)GetParent();
	ASSERT(parent != NULL);

	point.y += parent->GetScrollPosition ();

	PartWithDecorator pdt;
	bool found = FindObject(point, pdt);

	if (found) {
//		CGMEEventLogger::LogGMEEvent("    LButton over " + guiObj->GetName() + "\r\n");

		CRect rectAwake = CRect(point.x, point.y, point.x + 1, point.y + 1);
		rectAwake.InflateRect(3, 3);

		long x1 = 0; long y1 = 0;
		long x2 = 0; long y2 = 0;
		COMTHROW(pdt.decorator->GetLocation(&x1, &y1, &x2, &y2));
		CRect partRect (x1, y1, x2, y2);
		CPoint ptClickOffset(point.x - partRect.left, point.y - partRect.top);

		CRectList rects;
		rects.AddTail(&partRect);

		CRectList dummyAnnList;
		CGMEDataDescriptor desc(rects, dummyAnnList, point, ptClickOffset);
//		CGMEDataDescriptor::destructList(rects);

		CGMEDataSource dataSource(mgaProject);
		CComPtr<IMgaMetaRole> mmRole;
		COMTHROW(pdt.part->get_Role(&mmRole));
		dataSource.SetMetaRole(mmRole);
		dataSource.CacheDescriptor(&desc);
		DROPEFFECT de = dataSource.DoDragDrop(DROPEFFECT_COPY, &rectAwake);
	}

	CWnd::OnLButtonDown(nFlags, point);
}
