// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "GMEApp.h"

#include "ChildFrm.h"

#include "GMEView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_WM_CREATE()
	ON_COMMAND_EX(CG_ID_VIEW_MODELPROPERTIESBAR, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_MODELPROPERTIESBAR, OnUpdateControlBarMenu)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	sendEvent = true;
	view = 0;
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Add a menu item that will toggle the visibility of the
	// dialog bar named "ModelPropertiesBar":
	//   1. In ResourceView, open the menu resource that is used by
	//      the CChildFrame class
	//   2. Select the View submenu
	//   3. Double-click on the blank item at the bottom of the submenu
	//   4. Assign the new item an ID: CG_ID_VIEW_MODELPROPERTIESBAR
	//   5. Assign the item a Caption: ModelPropertiesBar

	// TODO: Change the value of CG_ID_VIEW_MODELPROPERTIESBAR to an appropriate value:
	//   1. Open the file resource.h
	// CG: The following block was inserted by the 'Dialog Bar' component
#if !defined(ACTIVEXGMEVIEW)
	{
		// Initialize dialog bar propBar
		if (!propBar.Create(this, CG_IDD_MODELPROPERTIESBAR,
			CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE,
			CG_ID_VIEW_MODELPROPERTIESBAR))
		{
			TRACE0("Failed to create dialog bar propBar\n");
			return -1;		// fail to create
		}
		// terge 
		int zoomvals[] = {ZOOM_MIN, 10, 25, 50, 75, ZOOM_NO, 150, 200, 300, ZOOM_MAX, ZOOM_WIDTH, ZOOM_HEIGHT, ZOOM_ALL, 0};
//		int zoomvals[] = {ZOOM_NO, 150, 200, 250, 300, 350, 400, 0}; // for test
		propBar.SetZoomList(zoomvals);
	}
#endif

	return 0;
}

void CChildFrame::OnClose() 
{
	bool doClose = true;
	if(sendEvent && view) 
		doClose = ((CGMEView *)view)->SendCloseModelEvent();
	sendEvent = true;

	if(doClose)
		CMDIChildWndEx::OnClose();

	// CMDIChildWndEx::OnClose: when the last ChildWnd is closed
	// the document is considered closed and the title changes to Paradigm
	// that's why we call this:
	theApp.UpdateMainTitle();
}

void CChildFrame::OnSize(UINT nType, int cx, int cy)
{
	CMDIChildWndEx::OnSize(nType, cx, cy);

	// it is necessary to change the title manually especially
	// when the first childwnd is created
	// when the childwnd's are maximized
	theApp.UpdateMainTitle();
}
