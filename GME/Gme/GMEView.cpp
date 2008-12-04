// GMEView.cpp : implementation of the CGMEView class
//

#include "stdafx.h"
#include "GMEApp.h"
#include <math.h>
#include <algorithm>
#include "GMEstd.h"

#include "GuiMeta.h"
#include "GMEDoc.h"
#include "PendingObjectPosRequest.h"
#include "GMEView.h"
#include "ChildFrm.h"
#include "ModelGrid.h"
#include "Mainfrm.h"
#include "GMEBrowser.h"
#include "GMEEventLogger.h"
#include "GmePrintDialog.h"
#include "ConnityDlg.h"
#if defined(ADDCRASHTESTMENU)
#include "CrashTest.h"
#endif

#include "Autoroute/AutoRouter.h"

#include "GraphicsUtil.h"

#include "GMEOLEModel.h"

CGraphics graphics;
static CViewList viewsToKill;

#define MIN_ZOOM_RECT 12 // the minimal size of zoomable rectangle
/*
int setZoomPercents[GME_ZOOM_LEVEL_NUM] = {
	GME_ZOOM_LEVEL_0,
	GME_ZOOM_LEVEL_1,
	GME_ZOOM_LEVEL_2,
	GME_ZOOM_LEVEL_3,
	GME_ZOOM_LEVEL_4,
	GME_ZOOM_LEVEL_5,
	GME_ZOOM_LEVEL_6,
	GME_ZOOM_LEVEL_7
};*/

// #define END_SCROLL_OFFSET 50 // not used - instead EXTENT_ERROR_CORR

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void DumpCDC(CDC* pDC) {
	CSize ve = pDC->GetViewportExt();
	CSize vo = pDC->GetViewportOrg();
	CSize we = pDC->GetWindowExt();
	CSize wo = pDC->GetWindowOrg();
	CRect clipBox;
	int clipRgnType = pDC->GetClipBox(&clipBox);
	TRACE("\t%p %p mm %ld ve(%ld,%ld) vo(%ld,%ld) cb(%ld)(%ld,%ld,%ld,%ld) we(%ld,%ld) wo(%ld,%ld)\n",
		pDC->m_hDC, pDC, pDC->GetMapMode(), ve.cx, ve.cy, vo.cx, vo.cy,
		clipRgnType, clipBox.left, clipBox.top, clipBox.Width(), clipBox.Height(),
		we.cx, we.cy, wo.cx, wo.cy);
}

/////////////////////////////////////////////////////////////////////////////
// CViewDriver
bool CViewDriver::attrNeedsRefresh = false;

STDMETHODIMP CViewDriver::GlobalEvent(globalevent_enum event)
{
	POSITION ppos;

	if(view == 0)
		return S_OK;

	CGMEView::inEventHandler = true;
	switch(event) {
	case GLOBALEVENT_UNDO:
	case GLOBALEVENT_REDO:
		ppos = view->pendingRequests.GetHeadPosition();
		while (ppos)
			delete view->pendingRequests.GetNext(ppos);
		view->pendingRequests.RemoveAll();

		// PETER: Let's reset only the view....
		VERIFY(view);
		long status;
		COMTHROW(view->currentModel->get_Status(&status));
		if (status != OBJECT_EXISTS) {
			view->alive = false;
			view->frame->sendEvent = false;
			view->frame->PostMessage(WM_CLOSE);
		}
		if (view->alive) {
			view->Reset(true);
			view->needsReset = false;
		}
		// view->GetDocument()->ResetAllViews();
		// PETER END
		break;
    case GLOBALEVENT_ABORT_TRANSACTION:
        view->Reset(true);
        break;    
	case GLOBALEVENT_NOTIFICATION_READY: 
		VERIFY(view);
		POSITION pos = viewsToKill.GetHeadPosition();
		while(pos) {
			CGMEView *v = viewsToKill.GetNext(pos);
			v->alive = false;
			v->frame->sendEvent = false;
			v->frame->PostMessage(WM_CLOSE);
		}
		viewsToKill.RemoveAll();
		if(view->alive && view->needsReset) {
			view->Reset(true);
			view->needsReset = false;
		}
		if(attrNeedsRefresh) {
			attrNeedsRefresh = false;
		}
		break;        
	}
	CGMEView::inEventHandler = false;
	return S_OK;
}

STDMETHODIMP CViewDriver::ObjectEvent(IMgaObject *obj, unsigned long eventmask,VARIANT /*v*/)
{
	if(view == 0)
		return S_OK;
	CGMEView::inEventHandler = true;


	// Clear all invalidated PendingRequests
	POSITION ppos = view->pendingRequests.GetHeadPosition();
	while (ppos) {
		POSITION tmp = ppos;
		CPendingObjectPosRequest *req = dynamic_cast<CPendingObjectPosRequest *> (view->pendingRequests.GetNext(ppos));
		if (req) {
			if ( req->object->mgaFco == obj ) {
					view->pendingRequests.RemoveAt(tmp);
					delete req;
			}
		}
	}

	if(IsEqualObject(obj,view->currentModel)) {
		// PARENT EVENT!!!
		if(eventmask & OBJEVENT_DESTROYED) {
			if( theApp.isHistoryEnabled() && view && view->GetDocument())
			{
				CComBSTR id; 
				COMTHROW( obj->get_ID( &id)); // get the id of the deleted object
				view->GetDocument()->eraseFromHistory( PutInCString( id)); // clear from history
			}
			TRACE("   OBJEVENT_DESTROYED\n");
			viewsToKill.AddTail(view);
			attrNeedsRefresh = true;
		}
		if(eventmask & OBJEVENT_NEWCHILD) {
			TRACE("   OBJEVENT_NEWCHILD\n");
			view->needsReset = true;
		}
		if(eventmask & OBJEVENT_LOSTCHILD) {
			TRACE("   OBJEVENT_LOSTCHILD\n");
			view->needsReset = true;
		}
		if(eventmask & OBJEVENT_REGISTRY) {
			view->needsReset = true;
		}
		if(eventmask & OBJEVENT_PROPERTIES) {
			TRACE("   OBJEVENT_PROPERTIES\n");
			view->SetName();
			attrNeedsRefresh = true;
		}
	}
	else if(IsEqualObject(obj,view->baseType)) {
		if(eventmask & OBJEVENT_PROPERTIES) {
			TRACE("   OBJEVENT_PROPERTIES\n");
			view->SetTypeNameProperty();
		}
	}
	else {
		// CHILD EVENT!!!
		if(eventmask & OBJEVENT_CREATED) {
			view->needsReset = true;
			TRACE("   OBJEVENT_CREATED\n");
		}
		else if(eventmask & OBJEVENT_DESTROYED) {
			view->needsReset = true;
			attrNeedsRefresh = true;
			TRACE("   OBJEVENT_DESTROYED\n");
		}
		else if(eventmask & OBJEVENT_SETINCLUDED || eventmask & OBJEVENT_SETEXCLUDED) {
			view->needsReset = true;
		}
		else if(eventmask & OBJEVENT_RELATION) {
			view->needsReset = true;
		}
		else if(eventmask & OBJEVENT_REGISTRY) {
			view->needsReset = true;
		}
		else if(eventmask & OBJEVENT_ATTR) {
			view->needsReset = true;
			attrNeedsRefresh = true;
		}
		else if(eventmask & OBJEVENT_PROPERTIES) {	   	// Because of the connectionlabels
			view->needsReset = true;					// and attr browser
			attrNeedsRefresh = true;
		}
		else {
			CComPtr<IMgaObject> object = obj;
			CComPtr<IMgaFCO> fco;
			if(SUCCEEDED(object.QueryInterface(&fco))) {
				CGuiObject *guiObj = CGuiObject::FindObject(fco,view->children);
				CGuiConnection *conn = CGuiFco::FindConnection(fco,view->connections);
				if(guiObj) {
					if(eventmask & OBJEVENT_PROPERTIES) {
						CComBSTR bstr;
						COMTHROW(object->get_Name(&bstr));
						CopyTo(bstr,guiObj->GetName());
						view->Invalidate();
					}
				}
				else if(conn) {
					if(eventmask & OBJEVENT_PROPERTIES) {
						CComBSTR bstr;
						COMTHROW(object->get_Name(&bstr));
						CopyTo(bstr,conn->name);
						// ?? 
						view->Invalidate();
					}
				}
				else
					view->needsReset = true; // e.g. port name change etc.
			}
		}
	}
	CGMEView::inEventHandler = false;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CGMEView

bool CGMEView::offScreenCreated = false;
CDC * CGMEView::offScreen;
CBitmap *CGMEView::ofsbmp;
int CGMEView::instanceCount = 0;
int CGMEView::inTransaction = 0;
bool CGMEView::inRWTransaction = false;
bool CGMEView::inEventHandler = false;

HCURSOR CGMEView::autoconnectCursor;
HCURSOR CGMEView::autoconnect2Cursor;
HCURSOR CGMEView::disconnectCursor;
HCURSOR CGMEView::disconnect2Cursor;
HCURSOR CGMEView::setCursor;
HCURSOR CGMEView::set2Cursor;
HCURSOR CGMEView::zoomCursor;
HCURSOR CGMEView::visualCursor;
HCURSOR CGMEView::editCursor;

bool CGMEView::derivedDrop = false;
bool CGMEView::instanceDrop = false;

IMPLEMENT_DYNCREATE(CGMEView, CScrollZoomView)

BEGIN_MESSAGE_MAP(CGMEView, CScrollZoomView)
	//{{AFX_MSG_MAP(CGMEView)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	ON_WM_DROPFILES()
	ON_EN_KILLFOCUS(IDC_NAME, OnKillfocusNameProp)
	ON_CBN_SELCHANGE(IDC_ASPECT, OnSelChangeAspectProp)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_VIEW_PARENT, OnViewParent)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PARENT, OnUpdateViewParent)
	ON_COMMAND(ID_VIEW_GRID, OnViewGrid)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GRID, OnUpdateViewGrid)
	ON_COMMAND(ID_EDIT_NUDGEDOWN, OnEditNudgedown)
	ON_COMMAND(ID_EDIT_NUDGELEFT, OnEditNudgeleft)
	ON_COMMAND(ID_EDIT_NUDGERIGHT, OnEditNudgeright)
	ON_COMMAND(ID_EDIT_NUDGEUP, OnEditNudgeup)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditDelete)
	ON_COMMAND(ID_CNTX_PROPERTIES, OnContextProperties)
	ON_COMMAND(ID_CNTX_ATTRIBUTES, OnCntxAttributes)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_COPYCLOSURE, OnEditCopyClosure)
	ON_COMMAND(ID_EDIT_COPYSMART, OnEditCopySmart)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPYCLOSURE, OnUpdateEditCopyClosure)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPYSMART, OnUpdateEditCopySmart)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_CNTX_COPY, OnCntxCopy)
	ON_COMMAND(ID_CNTX_COPYCLOSURE, OnCntxCopyClosure)
	ON_COMMAND(ID_CNTX_COPYSMART, OnCntxCopySmart)
	ON_COMMAND(ID_CNTX_CUT, OnCntxCut)
	ON_COMMAND(ID_CNTX_DELETE, OnCntxDelete)
	ON_COMMAND(ID_SELFCNTX_COPY, OnSelfcntxCopy)
	ON_UPDATE_COMMAND_UI(ID_SELFCNTX_COPY, OnUpdateSelfcntxCopy)
	ON_COMMAND(ID_SELFCNTX_COPYCLOSURE, OnSelfcntxCopyClosure)
	ON_COMMAND(ID_SELFCNTX_COPYSMART, OnSelfcntxCopySmart)
	ON_UPDATE_COMMAND_UI(ID_SELFCNTX_COPYCLOSURE, OnUpdateSelfcntxCopyClosure)
	ON_UPDATE_COMMAND_UI(ID_SELFCNTX_COPYSMART, OnUpdateSelfcntxCopySmart)
	ON_COMMAND(ID_SELFCNTX_CUT, OnSelfcntxCut)
	ON_UPDATE_COMMAND_UI(ID_SELFCNTX_CUT, OnUpdateSelfcntxCut)
	ON_COMMAND(ID_SELFCNTX_DELETE, OnSelfcntxDelete)
	ON_UPDATE_COMMAND_UI(ID_SELFCNTX_DELETE, OnUpdateSelfcntxDelete)
	ON_COMMAND(ID_SELFCNTX_PASTE, OnSelfcntxPaste)
	ON_UPDATE_COMMAND_UI(ID_SELFCNTX_PASTE, OnUpdateSelfcntxPaste)
	ON_UPDATE_COMMAND_UI(ID_CNTX_ATTRIBUTES, OnUpdateCntxAttributes)
	ON_COMMAND(ID_EDIT_CANCEL, OnEditCancel)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CANCEL, OnUpdateEditCancel)
	ON_COMMAND(ID_CNTX_DISCONNECTALL, OnCntxDisconnectall)
	ON_UPDATE_COMMAND_UI(ID_CNTX_DISCONNECTALL, OnUpdateCntxDisconnectall)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	ON_COMMAND(ID_CONNCNTX_PROPERTIES, OnConncntxProperties)
	ON_COMMAND(ID_CONNCNTX_DELETE, OnConncntxDelete)
	ON_COMMAND(ID_CONNCNTX_FOLLOW, OnConnCntxFollow)
	ON_COMMAND(ID_CONNCNTX_REVERSE, OnConnCntxRevfollow)
	ON_COMMAND(ID_PORTCNTX_FOLLOWCONNECTION, OnPortCntxFollowConnection)
	ON_COMMAND(ID_PORTCNTX_REVERSECONNECTION, OnPortCntxRevfollowConnection)
	ON_COMMAND(ID_CNTX_FOLLOWCONNECTION, OnCntxFollowConnection)
	ON_COMMAND(ID_CNTX_REVERSECONNECTION, OnCntxRevfollowConnection)
	ON_COMMAND(ID_CNTX_SHOWPORTINPARENT, OnCntxPortShowInParent)
	ON_COMMAND(ID_CNTX_LOCATEPORTINBROWSER, OnCntxPortLocateInBrw)
	ON_COMMAND(ID_JUMPALONGCONN, OnJumpAlongConnection)
	ON_COMMAND(ID_BACKALONGCONN, OnBackAlongConnection)
	ON_COMMAND(ID_JUMPTOFIRSTOBJ, OnJumpToFirstObject)
	ON_COMMAND(ID_JUMPTONEXTOBJ, OnJumpToNextObject)
	ON_COMMAND(ID_SHOWCONTEXTMENU, OnShowContextMenu)
	ON_COMMAND(ID_CNTX_CLEAR, OnCntxClear)
	ON_UPDATE_COMMAND_UI(ID_CNTX_CLEAR, OnUpdateCntxClear)
	ON_COMMAND(ID_CNTX_RESET, OnCntxReset)
	ON_UPDATE_COMMAND_UI(ID_CNTX_RESET, OnUpdateCntxReset)
	ON_UPDATE_COMMAND_UI(ID_CNTX_DELETE, OnUpdateCntxDelete)
	ON_UPDATE_COMMAND_UI(ID_CONNCNTX_DELETE, OnUpdateConncntxDelete)
	ON_UPDATE_COMMAND_UI(ID_CNTX_CUT, OnUpdateCntxCut)
	ON_UPDATE_COMMAND_UI(ID_PORTCNTX_FOLLOWCONNECTION, OnUpdatePortCntxFollowConnection)
	ON_UPDATE_COMMAND_UI(ID_PORTCNTX_REVERSECONNECTION, OnUpdatePortCntxRevfollowConnection)
	ON_UPDATE_COMMAND_UI(ID_CNTX_FOLLOWCONNECTION, OnUpdateCntxFollowConnection)
	ON_UPDATE_COMMAND_UI(ID_CNTX_REVERSECONNECTION, OnUpdateCntxRevfollowConnection)
	ON_UPDATE_COMMAND_UI(ID_JUMPALONGCONN, OnUpdateJumpAlongConnection)
	ON_UPDATE_COMMAND_UI(ID_BACKALONGCONN, OnUpdateBackAlongConnection)
#if defined(ADDCRASHTESTMENU)
	ON_COMMAND(ID_CRASHTEST_ILLEGALWRITE, OnCrashTestIllegalWrite)
	ON_COMMAND(ID_CRASHTEST_ILLEGALREAD, OnCrashTestIllegalRead)
	ON_COMMAND(ID_CRASHTEST_ILLEGALREADINCRUNTIME, OnCrashTestIllegalReadInCRuntime)
	ON_COMMAND(ID_CRASHTEST_ILLEGALCODEREAD, OnCrashTestIllegalCodeRead)
	ON_COMMAND(ID_CRASHTEST_DIVIDEBYZERO, OnCrashTestDivideByZero)
	ON_UPDATE_COMMAND_UI(IDR_CRASH_TEST_MENU, OnUpdateCrashTestMenu)
	ON_UPDATE_COMMAND_UI(ID_CRASHTEST_ILLEGALWRITE, OnUpdateCrashTestIllegalWrite)
	ON_UPDATE_COMMAND_UI(ID_CRASHTEST_ILLEGALREAD, OnUpdateCrashTestIllegalRead)
	ON_UPDATE_COMMAND_UI(ID_CRASHTEST_ILLEGALREADINCRUNTIME, OnUpdateCrashTestIllegalReadInCRuntime)
	ON_UPDATE_COMMAND_UI(ID_CRASHTEST_ILLEGALCODEREAD, OnUpdateCrashTestIllegalCodeRead)
	ON_UPDATE_COMMAND_UI(ID_CRASHTEST_DIVIDEBYZERO, OnUpdateCrashTestDivideByZero)
#endif
	ON_COMMAND(ID_CNTX_PREFERENCES, OnCntxPreferences)
	ON_COMMAND(ID_EDIT_PREFERENCES, OnEditPreferences)
	ON_COMMAND(ID_HELP_HELP, OnHelpHelp)
	ON_COMMAND(ID_CNTX_HELP, OnCntxHelp)
	ON_COMMAND(ID_EDIT_SHOWTYPE, OnEditShowtype)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SHOWTYPE, OnUpdateEditShowtype)
	ON_COMMAND(ID_EDIT_SHOWBASETYPE, OnEditShowbasetype)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SHOWBASETYPE, OnUpdateEditShowbasetype)
	ON_COMMAND(ID_CNTX_SHOWTYPE, OnCntxShowtype)
	ON_UPDATE_COMMAND_UI(ID_CNTX_SHOWTYPE, OnUpdateCntxShowtype)
	ON_COMMAND(ID_CNTX_SHOWBASETYPE, OnCntxShowbasetype)
	ON_UPDATE_COMMAND_UI(ID_CNTX_SHOWBASETYPE, OnUpdateCntxShowbasetype)
	ON_COMMAND(ID_FILE_INTERPRET, OnFileInterpret)
	ON_COMMAND(ID_FILE_CHECK, OnFileCheck)
	ON_COMMAND(ID_FILE_CHECKSEL, OnFileCheckSelected)
	ON_COMMAND(ID_CNTX_INTERPRET, OnCntxInterpret)
	ON_COMMAND(ID_CNTX_CHECK, OnCntxCheck)
	ON_COMMAND(ID_CNTX_LOCATE, OnCntxLocate)
	ON_UPDATE_COMMAND_UI(ID_CNTX_INTERPRET, OnUpdateCntxInterpret)
	ON_UPDATE_COMMAND_UI(ID_CNTX_CHECK, OnUpdateCntxCheck)
	ON_UPDATE_COMMAND_UI(ID_CNTX_LOCATE, OnUpdateCntxLocate)
	ON_COMMAND(ID_CNTX_REGISTRY, OnCntxRegistry)
	ON_COMMAND(ID_EDIT_REGISTRY, OnEditRegistry)
	ON_COMMAND(ID_EDIT_SYNC, OnEditSync)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SYNC, OnUpdateEditSync)
	ON_COMMAND(ID_EDIT_SELECTALL, OnEditSelectall)
	ON_UPDATE_COMMAND_UI(ID_FILE_CHECK, OnUpdateFileCheck)
	ON_UPDATE_COMMAND_UI(ID_FILE_CHECKSEL, OnUpdateFileCheckSelected)
	ON_UPDATE_COMMAND_UI(ID_FILE_CLOSE, OnUpdateFileClose)
	ON_COMMAND(ID_EDIT_PASTESPECIAL_ASINSTANCE, OnEditPastespecialAsinstance)
	ON_COMMAND(ID_EDIT_PASTESPECIAL_ASREFERENCE, OnEditPastespecialAsreference)
	ON_COMMAND(ID_EDIT_PASTESPECIAL_ASSUBTYPE, OnEditPastespecialAssubtype)
	ON_COMMAND(ID_EDIT_PASTESPECIAL_ASCLOSURE, OnEditPastespecialAsclosure)
	ON_COMMAND(ID_EDIT_PASTESPECIAL_SMART_ADDITIVE, OnEditPastespecialAdditive)
	ON_COMMAND(ID_EDIT_PASTESPECIAL_SMART_MERGE, OnEditPastespecialMerge)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTESPECIAL_ASINSTANCE, OnUpdateEditPastespecialAsinstance)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTESPECIAL_ASREFERENCE, OnUpdateEditPastespecialAsreference)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTESPECIAL_ASSUBTYPE, OnUpdateEditPastespecialAssubtype)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTESPECIAL_ASCLOSURE, OnUpdateEditPastespecialAsclosure)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTESPECIAL_SMART_ADDITIVE, OnUpdateEditPastespecialAdditive)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTESPECIAL_SMART_MERGE, OnUpdateEditPastespecialMerge)
	ON_COMMAND(ID_CNTX_PASTESPECIAL_ASINSTANCE, OnCntxPastespecialAsinstance)
	ON_UPDATE_COMMAND_UI(ID_CNTX_PASTESPECIAL_ASINSTANCE, OnUpdateCntxPastespecialAsinstance)
	ON_COMMAND(ID_CNTX_PASTESPECIAL_ASREFERENCE, OnCntxPastespecialAsreference)
	ON_UPDATE_COMMAND_UI(ID_CNTX_PASTESPECIAL_ASREFERENCE, OnUpdateCntxPastespecialAsreference)
	ON_COMMAND(ID_CNTX_PASTESPECIAL_ASSUBTYPE, OnCntxPastespecialAssubtype)
	ON_UPDATE_COMMAND_UI(ID_CNTX_PASTESPECIAL_ASSUBTYPE, OnUpdateCntxPastespecialAssubtype)
	ON_COMMAND(ID_CNTX_PASTESPECIAL_ASCLOSURE, OnCntxPastespecialAsclosure)
	ON_UPDATE_COMMAND_UI(ID_CNTX_PASTESPECIAL_ASCLOSURE, OnUpdateCntxPastespecialAsclosure)
	ON_COMMAND(ID_CNTX_PASTESPECIAL_SMART_ADDITIVE, OnCntxPastespecialAdditive)
	ON_UPDATE_COMMAND_UI(ID_CNTX_PASTESPECIAL_SMART_ADDITIVE, OnUpdateCntxPastespecialAdditive)
	ON_COMMAND(ID_CNTX_PASTESPECIAL_SMART_MERGE, OnCntxPastespecialMerge)
	ON_UPDATE_COMMAND_UI(ID_CNTX_PASTESPECIAL_SMART_MERGE, OnUpdateCntxPastespecialMerge)
	ON_COMMAND(ID_CNTX_REDIRECTIONPASTE, OnCntxRedirectionpaste)
	ON_UPDATE_COMMAND_UI(ID_CNTX_REDIRECTIONPASTE, OnUpdateCntxRedirectionpaste)
	ON_COMMAND(ID_KEY_CONNECT, OnKeyConnect)
	ON_COMMAND(ID_CNTX_CONNECT, OnCntxConnect)
	ON_UPDATE_COMMAND_UI(ID_CNTX_CONNECT, OnUpdateCntxConnect)
	ON_COMMAND(ID_RESET_STICKY, OnResetSticky)
	ON_WM_NCMOUSEMOVE()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_UPDATE_COMMAND_UI(ID_CNTX_INSERTANNOTATION, OnUpdateCntxInsertannotation)
	ON_COMMAND(ID_CNTX_INSERTANNOTATION, OnCntxInsertannotation)
	ON_COMMAND(ID_CNTX_ANNOTATIONS, OnCntxAnnotations)
	ON_COMMAND(ID_EDIT_ANNOTATIONS, OnEditAnnotations)
	ON_UPDATE_COMMAND_UI( ID_CNTX_SRCAR_NORTH, OnUpdateCntxAutoRouters )
	ON_COMMAND(ID_CNTX_SRCAR_SOUTH, OnCntxSrcarSouth)
	ON_COMMAND(ID_CNTX_SRCAR_NORTH, OnCntxSrcarNorth)
	ON_COMMAND(ID_CNTX_SRCAR_EAST, OnCntxSrcarEast)
	ON_COMMAND(ID_CNTX_SRCAR_WEST, OnCntxSrcarWest)
	ON_COMMAND(ID_CNTX_DSTAR_EAST, OnCntxDstarEast)
	ON_COMMAND(ID_CNTX_DSTAR_NORTH, OnCntxDstarNorth)
	ON_COMMAND(ID_CNTX_DSTAR_SOUTH, OnCntxDstarSouth)
	ON_COMMAND(ID_CNTX_DSTAR_WEST, OnCntxDstarWest)
	ON_COMMAND(ID_CNTX_SRCAR_CLEAR, OnCntxSrcarClear)
	ON_COMMAND(ID_CNTX_DSTAR_CLEAR, OnCntxDstarClear)
	ON_COMMAND(ID_CNTX_SRCAR_SET, OnCntxSrcarSet)
	ON_COMMAND(ID_CNTX_DSTAR_SET, OnCntxDstarSet)
	ON_UPDATE_COMMAND_UI( ID_CNTX_DSTAR_NORTH, OnUpdateCntxAutoRouters )
	ON_UPDATE_COMMAND_UI( ID_CNTX_SRCAR_SOUTH, OnUpdateCntxAutoRouters )
	ON_UPDATE_COMMAND_UI( ID_CNTX_DSTAR_SOUTH, OnUpdateCntxAutoRouters )
	ON_UPDATE_COMMAND_UI( ID_CNTX_SRCAR_WEST, OnUpdateCntxAutoRouters )
	ON_UPDATE_COMMAND_UI( ID_CNTX_DSTAR_WEST, OnUpdateCntxAutoRouters )
	ON_UPDATE_COMMAND_UI( ID_CNTX_SRCAR_EAST, OnUpdateCntxAutoRouters )
	ON_UPDATE_COMMAND_UI( ID_CNTX_DSTAR_EAST, OnUpdateCntxAutoRouters )
	ON_UPDATE_COMMAND_UI( ID_CNTX_SRCAR_CLEAR, OnUpdateCntxAutoRouters )
	ON_UPDATE_COMMAND_UI( ID_CNTX_DSTAR_CLEAR, OnUpdateCntxAutoRouters )
	ON_UPDATE_COMMAND_UI( ID_CNTX_SRCAR_SET, OnUpdateCntxAutoRouters )
	ON_UPDATE_COMMAND_UI( ID_CNTX_DSTAR_SET, OnUpdateCntxAutoRouters )
	ON_COMMAND(ID_PRINT_METAFILE, OnPrintMetafile)
	ON_COMMAND(ID_CNTX_NMPOS_SOUTH, OnCntxNamePositionSouth)
	ON_COMMAND(ID_CNTX_NMPOS_NORTH, OnCntxNamePositionNorth)
	ON_COMMAND(ID_CNTX_NMPOS_EAST, OnCntxNamePositionEast)
	ON_COMMAND(ID_CNTX_NMPOS_WEST, OnCntxNamePositionWest)
	ON_UPDATE_COMMAND_UI( ID_CNTX_NMPOS_SOUTH, OnUpdateCntxNamePositionSouth )
	ON_UPDATE_COMMAND_UI( ID_CNTX_NMPOS_NORTH, OnUpdateCntxNamePositionNorth )
	ON_UPDATE_COMMAND_UI( ID_CNTX_NMPOS_EAST, OnUpdateCntxNamePositionEast )
	ON_UPDATE_COMMAND_UI( ID_CNTX_NMPOS_WEST, OnUpdateCntxNamePositionWest )
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollZoomView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollZoomView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollZoomView::OnFilePrintPreview)
	ON_COMMAND(ID_KEY_ZOOMIN, OnZoomIn)
	ON_COMMAND(ID_KEY_ZOOMOUT, OnZoomOut)
	ON_COMMAND(ID_KEY_CYCLEOBJINSPFRWD, OnKeyCycleObjInspectorFrwd)
	ON_COMMAND(ID_KEY_CYCLEOBJINSPBKWD, OnKeyCycleObjInspectorBkwd)
	ON_MESSAGE(WM_USER_ZOOM, OnZoom)
	ON_MESSAGE(WM_USER_PANNREFRESH, OnPannRefresh)
	ON_MESSAGE(WM_PANN_SCROLL, OnPannScroll)
	ON_COMMAND(ID_VIEW_SHOWSELMODEL, OnShowSelectedModel)
	ON_COMMAND(ID_VIEW_FOCUSBROWSER, OnFocusBrowser)
	ON_COMMAND(ID_VIEW_FOCUSINSPECTOR, OnFocusInspector)
	ON_COMMAND(ID_VIEW_CYCLEASPECTKEY, OnCycleAspect)
	ON_COMMAND(ID_VIEW_CYCLEALLASPECTS, OnCycleAllAspects)
	ON_COMMAND(ID_VIEW_HISTORYBACKKEY, OnHistoryBack)
	ON_COMMAND(ID_VIEW_HISTORYFORWKEY, OnHistoryForw)
	ON_COMMAND(ID_MULTIUSER_SHOWOWNER, OnViewMultiUserShowObjectOwner)
	ON_UPDATE_COMMAND_UI( ID_MULTIUSER_SHOWOWNER, OnUpdateViewMultiUserShowObjectOwner)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGMEView construction/destruction

CGMEView::CGMEView()
{
	m_isActive						= false;
	m_preview						= false;
	m_scalePrnPages					= 1;
	m_currPrnNumAsp					= 0;
	m_fullPrnAspNum					= 1;
	m_prevcurrasp					= NULL;
	m_prnpos						= NULL;
	m_lastPrnPage					= 0;
	m_zoomVal						= ZOOM_NO;
	m_refreshpannwin				= false;

	initDone						= false;
	inTransaction					= 0;

	autoconnectCursor				= AfxGetApp()->LoadCursor(IDC_AUTOCONNECT_CURSOR);
	autoconnect2Cursor				= AfxGetApp()->LoadCursor(IDC_AUTOCONNECT2_CURSOR);
	disconnectCursor				= AfxGetApp()->LoadCursor(IDC_DISCONNECT_CURSOR);
	disconnect2Cursor				= AfxGetApp()->LoadCursor(IDC_DISCONNECT2_CURSOR);
	setCursor						= AfxGetApp()->LoadCursor(IDC_SET_CURSOR);
	set2Cursor						= AfxGetApp()->LoadCursor(IDC_SET2_CURSOR);
	zoomCursor						= AfxGetApp()->LoadCursor(IDC_ZOOM_CURSOR);
	visualCursor					= AfxGetApp()->LoadCursor(IDC_VISUAL_CURSOR);
	editCursor						= LoadCursor(0,IDC_ARROW);

	drawGrid						= false;

	isCursorChangedByDecorator		= false;
	originalRect.SetRectEmpty();
	inNewDecoratorOperation			= false;
	inOpenedDecoratorTransaction	= false;
	isContextInitiatedOperation		= false;
	shouldCommitOperation			= false;
	decoratorOrAnnotator			= true;
	objectInDecoratorOperation		= NULL;
	annotatorInDecoratorOperation	= NULL;
	selectedObjectOfContext			= NULL;
	selectedAnnotationOfContext		= NULL;
	selectedConnection				= NULL;

	prevDropEffect					= DROPEFFECT_NONE;
	inDrag							= false;
	contextMenuLocation				= CPoint(0,0);

	guiMeta							= 0;
	currentAspect					= 0;
	currentSet						= 0;
	lastObject						= 0;
	lastPort						= 0;
	dragSource						= 0;

	needsReset						= false;
	alive							= true;

	instanceCount++;

	animRefCnt						= 0;
	timerID							= 0;

	driver							= new CComObject<CViewDriver>;
	driver->view					= this;

	contextSelection				= 0;
	contextAnnotation				= 0;
	contextPort						= 0;

	tmpConnectMode					= false;
	ClearConnSpecs();
}

CGMEView::~CGMEView()
{
	// a good idea to release ptrs
	baseType.Release();
	parent.Release();
	currentModel.Release();

	if(--instanceCount <= 0) {
		// update & disable some components
		theApp.UpdateCompList4CurrentKind( CGMEApp::m_no_model_open_string);

		delete offScreen;
		delete ofsbmp;
		offScreenCreated = false;
		if( CMainFrame::theInstance != NULL ) {
			CMainFrame::theInstance->SetPartBrowserMetaModel(NULL);
			CMainFrame::theInstance->SetPartBrowserBg(::GetSysColor(COLOR_APPWORKSPACE));
		}
	}
	POSITION pos = children.GetHeadPosition();
	while(pos)
		delete children.GetNext(pos);

	pos = annotators.GetHeadPosition();
	while(pos) {
		delete annotators.GetNext(pos);
	}

	pos = pendingRequests.GetHeadPosition();
	while(pos)
		delete pendingRequests.GetNext(pos);
	pendingRequests.RemoveAll();

	driver->view = 0;
}

BOOL CGMEView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollZoomView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGMEView drawing

#define PANNING_RATIO_MIN	4 // ??
void CGMEView::DoPannWinRefresh()
{
//	CMainFrame* main = (CMainFrame*)AfxGetMainWnd();
	CMainFrame* main = (CMainFrame*)theApp.m_pMainWnd;

	if (!main || !main->m_panningWindow.IsVisible())
		return;

	// the original size of the image
	CRect extent, objext, annext;
	CGuiObject::GetExtent(children,objext);
	CGuiAnnotator::GetExtent(annotators,annext);
	extent.UnionRect(&objext, &annext);
	extent.right = (int)(extent.right*EXTENT_ERROR_CORR); // ??
	extent.bottom = (int)(extent.bottom*EXTENT_ERROR_CORR); // ??
	
	CRect target = CRect(0, 0, extent.Width()/PANNING_RATIO_MIN, extent.Height()/PANNING_RATIO_MIN);

	// make a bitmap DC
	CDC *pannDC = new CDC();
	ASSERT(pannDC != NULL);
	CClientDC tmpDC(this);

	// TODO: Error checking
	pannDC->CreateCompatibleDC(&tmpDC);
	CBitmap * pannBmp = new CBitmap();
	ASSERT(pannBmp != NULL);

	// TODO: Error checking
	BOOL ret = pannBmp->CreateCompatibleBitmap(&tmpDC, target.Width(), target.Height());
	if( !ret) // introd' by zolmol
	{
		if( pannDC)
			delete pannDC;
		if( pannBmp) 
			delete pannBmp;

		return;
	}
	ASSERT(ret);
	pannDC->SelectObject(pannBmp);

	// set background color
	pannDC->SetMapMode(MM_TEXT);
	// DWORD dw1 = GetSysColor(COLOR_WINDOW);
	// BYTE r1 = GetRValue(dw1);
	// BYTE g1 = GetGValue(dw1); 
	// BYTE b1 = GetBValue(dw1); 
	pannDC->FillSolidRect(&target, bgColor); // RGB(r1,g1,b1));

	pannDC->SetMapMode(MM_ISOTROPIC);
	pannDC->SetWindowExt(extent.Width(), extent.Height());
	pannDC->SetViewportExt(target.Width(), target.Height());

	{
		// draw the image
		POSITION pos = annotators.GetHeadPosition();
			while (pos) {
			CGuiAnnotator *annotator = annotators.GetNext(pos);
			if (annotator->IsVisible()) {
				annotator->Draw(pannDC);
			}
		}

		pos = children.GetHeadPosition();
		while(pos) {
			CGuiFco *fco = children.GetNext(pos);
			if(fco->IsVisible()) {
				CGuiConnection *conn = dynamic_cast<CGuiConnection *>(fco);
				if(!conn)
					fco->Draw(pannDC);
			}
		}
	}

	// force CPanningWindow to reset the DC 
	main->m_panningWindow.SetBitmapDC(this, pannDC, extent, target, bgColor);
	notifyPanning(GetDeviceScrollPosition());
}

void CGMEView::OnDraw(CDC* pDC)
{
	CGMEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	onScreen = pDC;
	if(!onScreen->IsPrinting()  &&  !IsPreview()) { 
		pDC = offScreen;
		OnPrepareDC(pDC);
	}

	if(drawGrid && !pDC->IsPrinting() && !IsPreview() && /// zoomIdx >= GME_ZOOM_LEVEL_MED) 
			m_zoomVal >= ZOOM_NO)
	{
		Gdiplus::Graphics gdip(pDC->m_hDC);
		gdip.SetPageUnit(Gdiplus::UnitPixel);
		gdip.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
		gdip.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);

		CRect objext, annext, extent;
		CGuiObject::GetExtent(children, objext);
		CGuiAnnotator::GetExtent(annotators, annext);
		extent.UnionRect(&objext, &annext);
		extent.right = (int)(extent.right*EXTENT_ERROR_CORR); // ??
		extent.bottom = (int)(extent.bottom*EXTENT_ERROR_CORR); // ??
		CSize s(extent.right, extent.bottom);
//		s.cx = s.cx + END_SCROLL_OFFSET;
//		s.cy = s.cy + END_SCROLL_OFFSET;
		CRect rect;
		GetClientRect(&rect);
		graphics.DrawGrid(&gdip, GME_GRID_SIZE, GME_GRID_SIZE,
						  max(s.cx,rect.right), max(s.cy,rect.bottom));
	}

	 /*
	 // DEBUG

	CPoint spt = GetScrollPosition();
	pDC->LPtoDP(&spt);
	CRect clientRect;
	GetClientRect(&clientRect);
	clientRect += spt;
	COLORREF col = RGB(10,10,10);
	for (int x = clientRect.left; x < clientRect.right; x++) {
		for (int y = clientRect.top; y < clientRect.bottom; y++) {
			CPoint ppp(x, y);
			CoordinateTransfer(ppp);
			if (!modelGrid.IsAvailable(ppp.x, ppp.y)) {
				CPoint np((x - spt.x)*zoom, (y-spt.y)*zoom);
				pDC->DPtoLP(&np);
				pDC->SetPixel(np, col);
			}
		}
	}
	//END-DEBUG
	*/


	POSITION pos = annotators.GetHeadPosition();
	while (pos) {
		CGuiAnnotator *annotator = annotators.GetNext(pos);
		if (annotator->IsVisible()) {
			annotator->Draw(pDC);
		}
	}

	pos = children.GetHeadPosition();
	while (pos) {
		CGuiFco* fco = children.GetNext(pos);
		if (fco->IsVisible()) {
			CGuiConnection* conn = dynamic_cast<CGuiConnection*> (fco);
			if (!conn)
				fco->Draw(pDC);
		}
	}
	DrawConnections(pDC);

	if(pDoc->GetEditMode() == GME_EDIT_MODE || pDoc->GetEditMode() == GME_SET_MODE) {
		if( ( (selected.GetCount() > 0) || (selectedAnnotations.GetCount() > 0) ) 
					&& !pDC->IsPrinting() && !IsPreview()) {
			POSITION pos = selected.GetHeadPosition();
			CRectTracker tracker;
			CGuiObject *obj;
			while(pos) {
				obj = selected.GetNext(pos);
				tracker.m_rect = obj->GetLocation();
				pDC->LPtoDP(&tracker.m_rect);
				tracker.m_nStyle = CRectTracker::solidLine | CRectTracker::resizeInside;
				tracker.Draw(pDC);
			}

			pos = selectedAnnotations.GetHeadPosition();
			CGuiAnnotator *ann;
			while(pos) {
				ann = selectedAnnotations.GetNext(pos);
				if( ann->IsVisible()) // the selectedAnnotation might become hidden is this aspect
				{
					tracker.m_rect = ann->GetLocation();
					pDC->LPtoDP(&tracker.m_rect);
					tracker.m_nStyle = CRectTracker::solidLine | CRectTracker::resizeInside;
					tracker.Draw(pDC);
				}
			}
		}
	}

	if (GetFocus() == this && ((pDoc->GetEditMode() == GME_AUTOCONNECT_MODE || pDoc->GetEditMode() == GME_SHORTAUTOCONNECT_MODE) || (tmpConnectMode))) {
		if (connSrc) {
			Gdiplus::Graphics gdip(pDC->m_hDC);
			gdip.SetPageUnit(Gdiplus::UnitPixel);
			gdip.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
			gdip.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);

			CRect rect = connSrc->GetLocation();
			if (connSrcPort) {
				rect = connSrcPort->GetLocation() + rect.TopLeft();
			}
			Gdiplus::Pen* xorPen = graphics.GetGdipPen2(&gdip, GME_DARKRED_COLOR, false, m_zoomVal > ZOOM_NO, GME_CONNSELECT_WIDTH);
			gdip.DrawRectangle(xorPen, rect.left, rect.top, rect.Width(), rect.Height());

			if ((connSrcHotSide != GME_CENTER) && (!connSrcPort)) {
				CPoint hotSpot;
				switch (connSrcHotSide) {
				case GME_SOUTH:
					hotSpot.x = rect.CenterPoint().x;
					hotSpot.y = rect.bottom;
					break;
				case GME_NORTH:
					hotSpot.x = rect.CenterPoint().x;
					hotSpot.y = rect.top;
					break;
				case GME_WEST:
					hotSpot.x = rect.left;
					hotSpot.y = rect.CenterPoint().y;
					break;
				case GME_EAST:
					hotSpot.x = rect.right;
					hotSpot.y = rect.CenterPoint().y;
					break;
				}
				Gdiplus::Brush* xorBrush = graphics.GetGdipBrush(GME_DARKRED_COLOR);
				gdip.FillRectangle(xorBrush, hotSpot.x - GME_HOTSPOT_VISUAL_RADIUS, hotSpot.y - GME_HOTSPOT_VISUAL_RADIUS, 2 * GME_HOTSPOT_VISUAL_RADIUS, 2 * GME_HOTSPOT_VISUAL_RADIUS);
				//gdip.FillEllipse(xorBrush, hotSpot.x - GME_HOTSPOT_VISUAL_RADIUS, hotSpot.y - GME_HOTSPOT_VISUAL_RADIUS, 2 * GME_HOTSPOT_VISUAL_RADIUS, 2 * GME_HOTSPOT_VISUAL_RADIUS);
			}
		}
		if (connTmp) {
			Gdiplus::Graphics gdip(pDC->m_hDC);
			gdip.SetPageUnit(Gdiplus::UnitPixel);
			gdip.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
			gdip.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);

			CRect rect = connTmp->GetLocation();
			if (connTmpPort) {
				rect = connTmpPort->GetLocation() + rect.TopLeft();
			}
			Gdiplus::Pen* xorPen = graphics.GetGdipPen2(&gdip, GME_RED_COLOR, false, m_zoomVal > ZOOM_NO, GME_CONNSELECT_WIDTH);
			gdip.DrawRectangle(xorPen, rect.left, rect.top, rect.Width(), rect.Height());

			if ((connTmpHotSide != GME_CENTER) && (!connTmpPort)) {
				CPoint hotSpot;
				switch (connTmpHotSide) {
				case GME_SOUTH:
					hotSpot.x = rect.CenterPoint().x;
					hotSpot.y = rect.bottom;
					break;
				case GME_NORTH:
					hotSpot.x = rect.CenterPoint().x;
					hotSpot.y = rect.top;
					break;
				case GME_WEST:
					hotSpot.x = rect.left;
					hotSpot.y = rect.CenterPoint().y;
					break;
				case GME_EAST:
					hotSpot.x = rect.right;
					hotSpot.y = rect.CenterPoint().y;
					break;
				}
				Gdiplus::Brush* xorBrush = graphics.GetGdipBrush(GME_RED_COLOR);
				gdip.FillRectangle(xorBrush, hotSpot.x - GME_HOTSPOT_VISUAL_RADIUS, hotSpot.y - GME_HOTSPOT_VISUAL_RADIUS, 2 * GME_HOTSPOT_VISUAL_RADIUS, 2 * GME_HOTSPOT_VISUAL_RADIUS);
				//gdip.FillEllipse(xorBrush, hotSpot.x - GME_HOTSPOT_VISUAL_RADIUS, hotSpot.y - GME_HOTSPOT_VISUAL_RADIUS, 2 * GME_HOTSPOT_VISUAL_RADIUS, 2 * GME_HOTSPOT_VISUAL_RADIUS);
			}
		}
	}

	if(!onScreen->IsPrinting()  &&  !IsPreview()) {
		CRect r;
		GetClientRect(&r);
		onScreen->DPtoLP(&r);
		CPoint pt = GetScrollPosition();
		onScreen->BitBlt(pt.x-5,pt.y-5,r.Width()+10,r.Height()+10,offScreen,pt.x-5,pt.y-5,SRCCOPY);
		if (m_refreshpannwin)
		{
			m_refreshpannwin = false;
			DoPannWinRefresh();
		}
	}
}


void CGMEView::OnInitialUpdate()
{
	BeginWaitCursor();
	CScrollZoomView::OnInitialUpdate();
	frame = (CChildFrame *)(GetParentFrame());
	frame->view = this;

	dropTarget.Register(this);
	EnableToolTips(TRUE);

//	zoomIdx = GME_ZOOM_LEVEL_MED;
	m_zoomVal = ZOOM_NO;
	int zv = 0;
	int l = _stscanf( (LPCTSTR) theApp.getDefZoomLev(), _T("%d"), &zv);
	if( l == 1 && zv && zv >= ZOOM_MIN && zv <= ZOOM_MAX) // do not accept ZOOM_WIDTH,ZOOM_HEIGHT,ZOOM_ALL for now as ZoomValue
		m_zoomVal = zv;
	// sets the combo too 
	frame->propBar.SetZoomVal(m_zoomVal);
	CMainFrame::theInstance->WriteStatusZoom(m_zoomVal); // setZoomPercents[zoomIdx]);

	CreateOffScreen(GetDC());
	CComPtr<IMgaFCO> centerObj;

	try {
		COMTHROW(theApp.mgaProject->CreateTerritory(driver,&terry));
		BeginTransaction(TRANSACTION_READ_ONLY);

		{
		   CComPtr<IMgaObject> ob;
		   COMTHROW(terry->OpenObj(GetDocument()->nextToView, &ob));
		   GetDocument()->ResetNextToView();
		   COMTHROW(ob->QueryInterface(&currentModel));
		}

		COMTHROW(currentModel->Open());
		{
			CComBSTR bstr;
			COMTHROW(currentModel->get_Name(&bstr));
			CopyTo(bstr,name);
		}
		CComPtr<IMgaMetaFCO> meta;
		COMTHROW(currentModel->get_Meta(&meta));
		{
			CComBSTR bstr;
			COMTHROW(meta->get_Name(&bstr));
			CopyTo(bstr,kindName);
		}
		{
			CComBSTR bstr;
			COMTHROW(meta->get_DisplayedName(&bstr));
			CopyTo(bstr,kindDisplayedName);
		}

		CComBSTR modid;
		COMTHROW( currentModel->get_ID( &modid));
		currentModId = modid;

		metaref_type mt;
		COMTHROW(meta->get_MetaRef(&mt));
		guiMeta = CGuiMetaProject::theInstance->GetGuiMetaModel(mt);
		currentAspect = guiMeta->FindAspect(GetDocument()->nextAspect);
		if(!currentAspect)
			currentAspect = guiMeta->GetFirstAspect();

		{
			VARIANT_BOOL b;
			COMTHROW(currentModel->get_IsInstance(&b));
			isType = (b == VARIANT_FALSE);
			if(isType) {
				COMTHROW(currentModel->get_BaseType(&baseType));
			}
			else{
				COMTHROW(currentModel->get_Type(&baseType));
			}

			if(isType) {
				CComPtr<IMgaModel> type;
				FindDerivedFrom(currentModel,type);
				isSubType = (type != 0);
			}
		}

		CreateGuiObjects();
		SetProperties();
		SetBgColor();

		if (GetDocument()->initialCenterObj) {
			COMTHROW(terry->OpenFCO(GetDocument()->initialCenterObj, &centerObj));
			GetDocument()->initialCenterObj = NULL;
		}

		CommitTransaction();
	}
	catch(hresult_exception &e) {
		AbortTransaction(e.hr);
		AfxMessageBox("Unable to open model",MB_OK | MB_ICONSTOP);
		CGMEEventLogger::LogGMEEvent("CGMEView::OnInitialUpdate - Unable to open model.\r\n");
		frame->PostMessage(WM_CLOSE);
		EndWaitCursor();
		return;
	}

	CGMEEventLogger::LogGMEEvent("CGMEView::OnInitialUpdate() - opened model: "+path+name+"\r\n");

	// AutoRoute();
	TRACE("CGMEView::OnInitialUpdate DoPannWinRefresh\n");
	DoPannWinRefresh(); // terge - new window opened
	SetScroll();
	SetCenterObject(centerObj);
	initDone = true;
	EndWaitCursor();

	SendOpenModelEvent();
	DragAcceptFiles(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// CGMEView printing

#define LOGOSIZE		64 // 115

void CGMEView::PrintMultiLineText(Gdiplus::Graphics* gdip, CDC *pDC, CString txt, int x, int &y, int ry, int xwidth)
{
	Gdiplus::Font* font = graphics.GetGdipFont(GME_PORTNAME_FONT);
	CPoint pt(x,y);
	CSize size = graphics.MeasureText(gdip, txt, pt, font);
	if(size.cx < xwidth) {
		graphics.DrawGdipText(gdip, txt, pt, font, GME_BLACK_COLOR, TA_LEFT | TA_BOTTOM);
	}
	else {
		int incr = 2;
		int lng = txt.GetLength();
		int width = incr;
		for(int start = 0; start < lng; start += width ) {
			for(width = incr; ; width += incr) {
				bool printIt = false;
				CString cur = txt.Mid(start,width);
				if(start + width >= lng)
					printIt = true;
				else {
					CSize size = graphics.MeasureText(gdip, cur, pt, font);
					if(size.cx > xwidth) {
						width -= incr;
						cur = txt.Mid(start,width);
						printIt = true;
					}
				}
				if(printIt) {
					graphics.DrawGdipText(gdip, cur, pt, font, GME_BLACK_COLOR, TA_LEFT | TA_BOTTOM);
					pt.y += (int)(ry / 12);
					break;
				}
			}
		}
	}

	y = pt.y + (int)(ry / 25);
}

void CGMEView::PrintHeader(CDC* pDC, CPrintInfo* pInfo)
{
	PrintHeaderRect(pDC, pInfo->m_rectDraw);
}

void CGMEView::PrintHeaderRect(CDC* pDC, CRect &rectDraw)
{
	/*const static*/ int logdpi = 140;
	int savedID = pDC->SaveDC();

	CString line1;
	CString line2;
	line1 = name;
	line2 = "Paradigm: " + theApp.guiMetaProject->displayedName;
	line2 += "     Project: " + theApp.projectName;
	line2 += "     Model: " + kindDisplayedName;
	line2 += "     Aspect: " + currentAspect->displayedName;
	CString tim;
	{
		struct tm *newtime;
		char am_pm[] = "AM";
		time_t long_time;
		time( &long_time );                /* Get time as long integer. */
		newtime = localtime( &long_time ); /* Convert to local time. */
		if( newtime->tm_hour > 12 )        /* Set up extension. */
			strcpy( am_pm, "PM" );
		if( newtime->tm_hour > 12 )        /* Convert from 24-hour */
			newtime->tm_hour -= 12;		   /*   to 12-hour clock.  */
		if( newtime->tm_hour == 0 )        /* Set hour to 12 if midnight. */
			newtime->tm_hour = 12;
		tim.Format("%.19s  %s", asctime( newtime ), am_pm );
	}
	line2 += "     Time: " + tim;

	// Setup mapping mode to have 50 pixel in 1 inch
	pDC->SetMapMode(MM_ISOTROPIC);
	double inchX = pDC->GetDeviceCaps(LOGPIXELSX);
	double inchY = pDC->GetDeviceCaps(LOGPIXELSY);
	pDC->SetWindowExt(logdpi,logdpi);
	pDC->SetViewportExt((int)inchX,(int)inchY);

	int gap = (int)(logdpi / 40);                             // 1/40 inch
	int txty = gap * 6 ;
	int xx = LOGOSIZE/4 + 20;

	Gdiplus::Graphics gdip(pDC->m_hDC);
	gdip.SetPageUnit(Gdiplus::UnitPixel);
	gdip.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
	gdip.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);

	PrintMultiLineText(&gdip,pDC,line1,xx,txty,logdpi,rectDraw.Width() - xx);

	txty += 4 * gap;

	CPoint pt = CPoint(LOGOSIZE /4  + 20,txty);
// ??	PrintMultiLineText(&gdip, pDC, line2, LOGOSIZE /4  + 20, txty, logdpi, rectDraw.Width() - xx);
	graphics.DrawGdipText(&gdip,line2,pt,graphics.GetGdipFont(GME_PORTNAME_FONT),GME_BLACK_COLOR,TA_LEFT | TA_BOTTOM);
//	pt = CPoint(rectDraw.right-gap * 2,LOGOSIZE + 20);
//	graphics.DrawGdipText(&gdip,tim,pt,graphics.GetGdipFont(GME_PORTNAME_FONT),GME_BLACK_COLOR,TA_RIGHT | TA_BOTTOM);


	CBitmap logo;
	// TODO: Error checking
	logo.LoadBitmap(IDB_BITMAP_LOGO);
	CDC logoDC;
	// TODO: Error checking
	logoDC.CreateCompatibleDC(pDC);
	logoDC.SetMapMode(MM_TEXT);
	CBitmap * bmp = logoDC.SelectObject(&logo);
	int bits = pDC->GetDeviceCaps(BITSPIXEL);
	if (bits == 1) 
		pDC->SetStretchBltMode(HALFTONE);
//	BOOL ret2 = pDC->StretchBlt(0, txty-LOGOSIZE/4,LOGOSIZE/4,LOGOSIZE/4,&logoDC,0,0,LOGOSIZE, LOGOSIZE, SRCCOPY);
	// TODO: Error checking
	pDC->StretchBlt(0, txty-LOGOSIZE/2,LOGOSIZE/2,LOGOSIZE/2,&logoDC,0,0,LOGOSIZE, LOGOSIZE, SRCCOPY);
	if (bmp)
		bmp = logoDC.SelectObject((CBitmap*)bmp);
	logo.DeleteObject();


	int y = txty;
	CPen pen;
	CPen *oldpen;
	int pw = (int)(logdpi / 48);                              // 1/48 inch
	pen.CreatePen(PS_SOLID,pw,RGB(0,0,0));
	oldpen = pDC->SelectObject(&pen);
	pDC->MoveTo(0,y);
	pDC->LineTo(rectDraw.right,y);

	y += 3 * gap;
	CPoint offset(0,y);
	pDC->LPtoDP(&offset);

	pDC->SelectObject(oldpen);
	pen.DeleteObject();
	pDC->RestoreDC(savedID);
	pDC->DPtoLP(&offset);
	rectDraw.top += (offset.y < logdpi/3)? logdpi/3: offset.y; // one third of an inch
}

BOOL CGMEView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// change the PrintDialog to a customized one
	CGmePrintDialog *gpd = new CGmePrintDialog(this, guiMeta, FALSE);
	if (gpd  &&  pInfo->m_pPD)
		delete pInfo->m_pPD;
	if (gpd)
	{
		pInfo->m_pPD = gpd;
		pInfo->m_pPD->m_pd.Flags =	PD_ALLPAGES |  // actually the current aspect
									PD_ENABLEPRINTTEMPLATE | PD_NONETWORKBUTTON  | 
									PD_USEDEVMODECOPIES | PD_USEDEVMODECOPIESANDCOLLATE |
									PD_ENABLEPRINTHOOK | PD_ENABLESETUPHOOK |
									PD_RETURNDC ;
		pInfo->m_pPD->m_pd.nMinPage = 1;      // one based page numbers
        pInfo->m_pPD->m_pd.nMaxPage = 0xffff; // how many pages is unknown
		pInfo->m_pPD->m_pd.hInstance = AfxGetInstanceHandle();
		pInfo->m_pPD->m_pd.lpPrintTemplateName = MAKEINTRESOURCE(PRINTDLGORD);
	}

	if (!CScrollZoomView::DoPreparePrinting(pInfo))
		return FALSE;

	HDC hdc = pInfo->m_pPD->GetPrinterDC();
	CDC cdc;
	cdc.Attach(hdc);
    LPDEVMODE devmode = pInfo->m_pPD->GetDevMode();
	devmode->dmOrientation = (gpd->IsPortrait())? (short)DMORIENT_PORTRAIT: (short)DMORIENT_LANDSCAPE;
	m_scalePrnPages = (short)gpd->NumOfPages();
	pInfo->m_pPD->m_pd.nMinPage = 1;      
	m_fullPrnAspNum = gpd->NumOfSelAspects();
    pInfo->m_pPD->m_pd.nMaxPage = (short)(m_scalePrnPages * m_scalePrnPages * m_fullPrnAspNum); 
	pInfo->m_pPD->m_pd.nToPage = (unsigned short)(0xffff);
	cdc.ResetDC(devmode);
	cdc.Detach();
	m_currPrnNumAsp = 0;
	m_prnpos = NULL;
	m_lastPrnPage = 0; // hack
	return TRUE;
}

void CGMEView::PrepareAspectPrn(CPrintInfo* pInfo)
{
	CGuiMetaAspect *asp = NULL;
	CGmePrintDialog* pdlg = (CGmePrintDialog*)(pInfo->m_pPD);
	bool changeAsp = false;

	if (m_lastPrnPage == pInfo->m_nCurPage)
		return;

	if (pdlg->IsAllAspect()  ||  pdlg->IsSelAspect())
	{ // all or some Aspect selected
		if (!m_currPrnNumAsp)
		{  // find the first Aspect
			SaveCurrAsp();
			m_prnpos = guiMeta->aspects.GetHeadPosition();
		}
		if (m_scalePrnPages == 1  ||  
				pInfo->m_nCurPage % (m_scalePrnPages*m_scalePrnPages) == 1)
		{  // change aspect
			asp = guiMeta->aspects.GetNext(m_prnpos);
			if (pdlg->IsSelAspect()) 
			{
				while (!pdlg->IsSelectedAspect(asp->name))
				{
					if (m_prnpos)
						asp = guiMeta->aspects.GetNext(m_prnpos);
					else
					{
						asp = NULL;
						ASSERT(asp);
						break;
					}
				}
			}
			m_currPrnNumAsp++;
			changeAsp = true;
		}
		if (changeAsp)
		{
			if (ChangePrnAspect(asp->name))
			{
				if (pdlg->IsAutorotate()) // it doen't work in OnPrint only in OnPrepareDC
				{ // it works only before StartPage
					HDC hdc = pInfo->m_pPD->GetPrinterDC();
					CDC cdc;
					cdc.Attach(hdc);
					CRect extent, objext, annext;
					CGuiObject::GetExtent(children,objext);
					CGuiAnnotator::GetExtent(annotators,annext);
					extent.UnionRect(&objext, &annext);
					LPDEVMODE devmode = pInfo->m_pPD->GetDevMode();
					devmode->dmFields = DM_ORIENTATION;
					if (extent.Width() > extent.Height()) // rotate it
						devmode->dmOrientation = (short)DMORIENT_LANDSCAPE;
					else
						devmode->dmOrientation = (short)DMORIENT_PORTRAIT;
					// TODO: Error checking
					cdc.ResetDC(devmode); // done for the AttribDC
					cdc.Detach();
				}
			}
		}
	}
	m_lastPrnPage = pInfo->m_nCurPage;
}

void CGMEView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnPrint\r\n");
	CGmePrintDialog* pdlg = (CGmePrintDialog*)(pInfo->m_pPD);
	int headerY = 0;

	if (pdlg->HasHeader())
	{
		PrintHeader(pDC, pInfo);
		headerY = pInfo->m_rectDraw.top;
	}
	// setup the DC according to the current page number - multipage
	int line = (int)ceil((double)(pInfo->m_nCurPage % (m_scalePrnPages * m_scalePrnPages)) / m_scalePrnPages);
	int col = pInfo->m_nCurPage % (m_scalePrnPages * m_scalePrnPages) % m_scalePrnPages;
	col = (col)? col: m_scalePrnPages;
	line = (line)? line: m_scalePrnPages;
	line--; // starts with 0
	col--;

	{
		pDC->SetMapMode(MM_ISOTROPIC);
		CRect extent, objext, annext;
		CGuiObject::GetExtent(children,objext);
		CGuiAnnotator::GetExtent(annotators,annext);
		extent.UnionRect(&objext, &annext);
		extent.right = (int)(extent.right*EXTENT_ERROR_CORR); // ??
		extent.bottom = (int)(extent.bottom*EXTENT_ERROR_CORR); // ??
		double wpage, hpage;
		double wmargin = GetDeviceCaps(pDC->m_hDC,PHYSICALOFFSETX);
		double hmargin = GetDeviceCaps(pDC->m_hDC,PHYSICALOFFSETY);
		wpage = GetDeviceCaps(pDC->m_hDC,PHYSICALWIDTH) - 2*wmargin;
		hpage = GetDeviceCaps(pDC->m_hDC,PHYSICALHEIGHT)- 2*hmargin;

		// headerY was calculated with another scaling
		pDC->SetWindowExt(extent.right, extent.bottom);
		int devheader = (headerY)? (int)(pDC->GetDeviceCaps(LOGPIXELSY)/3): 0; // I know it is 1/3 inch - pfujj

		pDC->SetViewportExt((int)(m_scalePrnPages*wpage), (int)(m_scalePrnPages*(hpage-devheader)));
		pDC->SetViewportOrg((int)(-wpage*col), (int)(-(hpage-devheader)*line) +devheader);
	}

	OnDraw(pDC);

	// restore Aspect
	if (pInfo->m_pPD->m_pd.nMaxPage == pInfo->m_nCurPage  && m_currPrnNumAsp == m_fullPrnAspNum)
	{ 
		CGuiMetaAspect* lastcurr = GetSavedAsp();
		ChangePrnAspect(lastcurr->name);
		Invalidate();
	}
}

void CGMEView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
	if (timerID) {
		KillTimer(timerID);
		timerID = 0;
	}
	CMainFrame* main = (CMainFrame*)AfxGetMainWnd();

	CDocument* doc = GetDocument();
	POSITION pos = doc->GetFirstViewPosition();
	if (pos != NULL  &&  doc->GetNextView(pos)  &&  pos == NULL)
	{
		CRect extent(0,0,0,0), target(0,0,0,0); // terge
		main->m_panningWindow.SetBitmapDC(this, NULL, extent, target, bgColor);
	}

	CScrollZoomView::OnDestroy();
}

void CGMEView::OnSize(UINT nType, int cx, int cy)
{
	CScrollZoomView::OnSize(nType, cx, cy);
}

/////////////////////////////////////////////////////////////////////////////
// CGMEView diagnostics

#ifdef _DEBUG
void CGMEView::AssertValid() const
{
	CScrollZoomView::AssertValid();
}

void CGMEView::Dump(CDumpContext& dc) const
{
	CScrollZoomView::Dump(dc);
}

CGMEDoc* CGMEView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGMEDoc)));
	return (CGMEDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGMEView custom operations

void CGMEView::BeginTransaction(transactiontype_enum mode)
{
	VERIFY(inTransaction >= 0);
	if(!inEventHandler && ++inTransaction == 1) {
		inRWTransaction = (mode == TRANSACTION_GENERAL);
		COMTHROW(theApp.mgaProject->BeginTransaction(terry,mode));
	}
}

void CGMEView::CommitTransaction()
{
	if(inEventHandler)
		return;
	VERIFY(inTransaction > 0);
	if (inRWTransaction) {
		while (!pendingRequests.IsEmpty()) {
			CPendingRequest* req = pendingRequests.RemoveHead();
			if( CGMEDoc::theInstance && !CGMEDoc::theInstance->m_isClosing)
				req->Execute(this);
			delete req;
		}

	}
	if(inTransaction == 1)
		COMTHROW(theApp.mgaProject->CommitTransaction());
	inTransaction--;
	inRWTransaction = false;
}

void CGMEView::AbortTransaction(HRESULT hr)
{
	if(inEventHandler)
		return;
	VERIFY(inTransaction > 0);
	if(--inTransaction > 0)
		throw hresult_exception(hr);
	else
		theApp.mgaProject->AbortTransaction();
}


bool CGMEView::SendOpenModelEvent()
{
	bool ok = true;
	try {
		BeginTransaction();

		COMTHROW(currentModel->SendEvent(OBJEVENT_OPENMODEL));

		CommitTransaction();
	}
	catch(hresult_exception &e) {
		AbortTransaction(e.hr);
		ok = false;
	}
	return ok;
}

bool CGMEView::SendCloseModelEvent()
{
	bool ok = true;
	try {
		BeginTransaction();

		COMTHROW(currentModel->SendEvent(OBJEVENT_CLOSEMODEL));

		CommitTransaction();
	}
	catch(hresult_exception &e) {
		AbortTransaction(e.hr);
		ok = false;
	}
	return ok;
}

bool CGMEView::SendMouseOver4Object( CGuiObject * pObject)
{
	bool ok = true;
	try {
		BeginTransaction();

		if( pObject && pObject->mgaFco)
		{
			long oStatus;
			COMTHROW(pObject->mgaFco->get_Status(&oStatus));
			if(oStatus == OBJECT_EXISTS) // make sure it has not been deleted since then
				COMTHROW( pObject->mgaFco->SendEvent(OBJEVENT_MOUSEOVER));
		}

		CommitTransaction();
	}
	catch(hresult_exception &e) {
		AbortTransaction(e.hr);
		ok = false;
	}
	return ok;
}

bool CGMEView::SendSelecEvent4Object( CGuiObject* pSelection)
{
	bool ok = true;

	std::list<CGuiObject*>::iterator found = std::find( m_lstUnselect.begin(), m_lstUnselect.end(), pSelection);
	if( found != m_lstUnselect.end()) // it can't be unsel and sel at the same time
	{
		m_lstUnselect.erase( found);
	}

	found = std::find( m_lstSelect.begin(), m_lstSelect.end(), pSelection);
	if( found != m_lstSelect.end()) // it should not be twice in sel
	{
		m_lstSelect.erase( found);
	}

	m_lstSelect.push_back( pSelection);
	return ok;
}

bool CGMEView::SendUnselEvent4Object( CGuiObject* pUnselection)
{
	bool ok = true;

	std::list<CGuiObject*>::iterator found = std::find( m_lstSelect.begin(), m_lstSelect.end(), pUnselection);
	if( found != m_lstSelect.end()) // it can't be unsel and sel at the same time
	{
		m_lstSelect.erase( found);
	}

	found = std::find( m_lstUnselect.begin(), m_lstUnselect.end(), pUnselection);
	if( found != m_lstUnselect.end()) // it should not be twice in unsel
	{
		m_lstUnselect.erase( found);
	}

	m_lstUnselect.push_back( pUnselection);
	return ok;
}

bool CGMEView::SendSelecEvent4List( CGuiObjectList* pSelection)
{
	bool ok = true;
	// send select event for each object in list
	POSITION pos = pSelection->GetHeadPosition();
	CGuiObject *obj;
	while(pos) {
		obj = pSelection->GetNext(pos);
		bool ok2 = SendSelecEvent4Object( obj);
		ok = ok && ok2;
	}
	return ok;
}


bool CGMEView::SendUnselEvent4List( CGuiObjectList* pUnselection)
{
	bool ok = true;
	// send deselect event for each object in list
	POSITION pos = pUnselection->GetHeadPosition();
	CGuiObject *obj;
	while(pos) {
		obj = pUnselection->GetNext(pos);
		bool ok2 = SendUnselEvent4Object( obj);
		ok = ok && ok2;
	}
	return ok;
}

bool CGMEView::SendNow(bool onlyDecoratorNotification)
{
	if (m_lstSelect.empty() && m_lstUnselect.empty()) {
		return false;
	} else {
		if (selectedConnection != NULL) {
			selectedConnection->SetSelect(false);
			selectedConnection = NULL;
		}
	}

	bool ok = true;
	try {
		if (!onlyDecoratorNotification)
			BeginTransaction();

		std::list<CGuiObject*>::iterator it;
		for( it = m_lstUnselect.begin(); it != m_lstUnselect.end(); ++it)
		{
			CGuiObject * pUnselection = *it;
			if( pUnselection && pUnselection->mgaFco)
			{
				long oStatus;
				COMTHROW(pUnselection->mgaFco->get_Status(&oStatus));
				if(oStatus == OBJECT_EXISTS) {	// make sure it has not been deleted since then
					if (!onlyDecoratorNotification)
						COMTHROW( pUnselection->mgaFco->SendEvent(OBJEVENT_DESELECT));
					// Sending decorator events (for efficiency)
					CGuiAspect* pAspect = pUnselection->GetCurrentAspect();
					if (pAspect != NULL) {
						CComQIPtr<IMgaNewDecorator> newDecorator(pAspect->GetDecorator());
						if (newDecorator)
							HRESULT retVal = newDecorator->SetSelected(VARIANT_FALSE);
					}
				}
			}
		}

		for( it = m_lstSelect.begin(); it != m_lstSelect.end(); ++it)
		{
			CGuiObject * pSelection = *it;
			if( pSelection && pSelection->mgaFco)
			{
				long oStatus;
				COMTHROW(pSelection->mgaFco->get_Status(&oStatus));
				if (oStatus == OBJECT_EXISTS) {
					if (!onlyDecoratorNotification)
						COMTHROW( pSelection->mgaFco->SendEvent(OBJEVENT_SELECT));
					// Sending decorator events (for efficiency)
					CGuiAspect* pAspect = pSelection->GetCurrentAspect();
					if (pAspect != NULL) {
						CComQIPtr<IMgaNewDecorator> newDecorator(pAspect->GetDecorator());
						if (newDecorator)
							HRESULT retVal = newDecorator->SetSelected(VARIANT_TRUE);
					}
				}
			}
		}

		if (!onlyDecoratorNotification) {
			m_lstSelect.clear();
			m_lstUnselect.clear();

			CommitTransaction();
		}
	}
	catch(hresult_exception &e) {
		if (!onlyDecoratorNotification)
			AbortTransaction(e.hr);
		ok = false;
	}
	return ok;
}

void CGMEView::AddAnnotationToSelectionHead(CGuiAnnotator* ann)
{
	AddAnnotationToSelection(ann, true);
}

void CGMEView::AddAnnotationToSelectionTail(CGuiAnnotator* ann)
{
	AddAnnotationToSelection(ann, false);
}

void CGMEView::AddAnnotationToSelection(CGuiAnnotator* ann, bool headOrTail)
{
	ClearConnectionSelection();
	CComPtr<IMgaNewDecorator> newDecorator = ann->GetNewDecorator(currentAspect->index);
	if (newDecorator)
		HRESULT retVal = newDecorator->SetSelected(VARIANT_TRUE);
	if (headOrTail)
		selectedAnnotations.AddHead(ann);
	else
		selectedAnnotations.AddTail(ann);
}

void CGMEView::RemoveAllAnnotationFromSelection(void)
{
	POSITION pos = selectedAnnotations.GetHeadPosition();
	CGuiAnnotator *ann;
	while (pos) {
		ann = selectedAnnotations.GetNext(pos);
		CComPtr<IMgaNewDecorator> newDecorator = ann->GetNewDecorator(currentAspect->index);
		if (newDecorator)
			HRESULT retVal = newDecorator->SetSelected(VARIANT_FALSE);
	}
	selectedAnnotations.RemoveAll();
}

void CGMEView::RemoveAnnotationFromSelectionHead(void)
{
	CGuiAnnotator* head = selectedAnnotations.GetHead();
	CComPtr<IMgaNewDecorator> newDecorator = head->GetNewDecorator(currentAspect->index);
	if (newDecorator)
		HRESULT retVal = newDecorator->SetSelected(VARIANT_FALSE);
	selectedAnnotations.RemoveHead();
}

void CGMEView::RemoveAnnotationFromSelection(POSITION annPos)
{
	CGuiAnnotator* ann = selectedAnnotations.GetAt(annPos);
	CComPtr<IMgaNewDecorator> newDecorator = ann->GetNewDecorator(currentAspect->index);
	if (newDecorator)
		HRESULT retVal = newDecorator->SetSelected(VARIANT_FALSE);
	selectedAnnotations.RemoveAt(annPos);
}

void CGMEView::ClearConnectionSelection(void)
{
	if (selectedConnection != NULL) {
		selectedConnection->SetSelect(false);
		selectedConnection = NULL;
	}
}

void CGMEView::ResetParent()
{
#if !defined (ACTIVEXGMEVIEW)
	CGMEView *parentView = GetDocument()->FindView(parent);
	if(parentView) {
		parentView->Reset();
		parentView->Invalidate();
	}
#endif
}

// ??
void CGMEView::CreateGuiObjects(CComPtr<IMgaFCOs> &fcos,CGuiFcoList &objList,CGuiConnectionList &connList)
{
	CComPtr<IMgaFCO> fco;
	MGACOLL_ITERATE(IMgaFCO,fcos) {
		fco = MGACOLL_ITER;
		CComPtr<IMgaMetaRole> role;
		COMTHROW(fco->get_MetaRole(&role));
		objtype_enum tp;
		COMTHROW(fco->get_ObjType(&tp));
		CGuiFco *guiFco;
		if(tp == OBJTYPE_MODEL) {
			guiFco = new CGuiModel(fco,role,this,guiMeta->NumberOfAspects());
			((CGuiModel *)guiFco)->InitObject(this);
			((CGuiModel *)guiFco)->SetAspect(currentAspect->index);
		}
		else if(tp == OBJTYPE_REFERENCE) {
			// Immediate referred object
			CComPtr<IMgaFCO> refd;
			CComPtr<IMgaReference> ref;
			COMTHROW(fco.QueryInterface(&ref));
			COMTHROW(ref->get_Referred(&refd));

			// Final referred (non-reference) object
			CComPtr<IMgaFCO> termRefd;
			CComObjPtr<IMgaFCOs> refChain;
			COMTHROW(refChain.CoCreateInstance(L"Mga.MgaFCOs"));
// This seems to fix the ref-ref problem
// the GetRefereeChain() puts in this fco
//			COMTHROW(refChain->Append(fco));
			GetRefereeChain(refChain,fco);

			CComPtr<IMgaFCO> lastRef;
			long refChainCnt;
			COMTHROW(refChain->get_Count(&refChainCnt));
			COMTHROW(refChain->get_Item(refChainCnt, &lastRef));
			
			ref = NULL;
			COMTHROW(lastRef.QueryInterface(&ref));
			COMTHROW(ref->get_Referred(&termRefd));

			objtype_enum rtp = OBJTYPE_NULL;
			if (termRefd) {
				COMTHROW(termRefd->get_ObjType(&rtp));
			}
			
			if(rtp == OBJTYPE_MODEL) {
				guiFco = new CGuiCompoundReference(fco,role,this,guiMeta->NumberOfAspects(),refd,termRefd);
				((CGuiCompoundReference *)guiFco)->InitObject(this);
				((CGuiCompoundReference *)guiFco)->SetAspect(currentAspect->index);
			}
			else {
				guiFco = new CGuiReference(fco,role,this,guiMeta->NumberOfAspects(),refd,termRefd);
				((CGuiReference *)guiFco)->InitObject(this);
				((CGuiReference *)guiFco)->SetAspect(currentAspect->index);
			}
			
		}
		else if(tp == OBJTYPE_SET) {
			guiFco = new CGuiSet(fco,role,this,guiMeta->NumberOfAspects());
			((CGuiSet *)guiFco)->InitObject(this);
			((CGuiSet *)guiFco)->SetAspect(currentAspect->index);
			if(!currentSetID.IsEmpty()) {
				CComBSTR bstr;
				fco->get_ID(&bstr);
				CString setID;
				CopyTo(bstr,setID);
				if(setID == currentSetID)
					currentSet = dynamic_cast<CGuiSet *>(guiFco);
			}
		}
		else if(tp == OBJTYPE_CONNECTION) {
			guiFco = new CGuiConnection(fco,role,this,guiMeta->NumberOfAspects(),false);
		}
		else {
			guiFco = new CGuiObject(fco,role,this,guiMeta->NumberOfAspects());
			((CGuiObject *)guiFco)->InitObject(this);
			((CGuiObject *)guiFco)->SetAspect(currentAspect->index);
		}
		guiFco->SetAspect(currentAspect->index);
		CComBSTR bstr;
		COMTHROW(fco->get_Name(&bstr));
		CGuiObject *guiObj = dynamic_cast<CGuiObject *>(guiFco);
		if(guiObj) {
			guiObj->ReadAllLocations();
			CopyTo(bstr,guiObj->name);
			objList.AddTail(guiObj);
		}
		else {
			CGuiConnection *guiConn = dynamic_cast<CGuiConnection *>(guiFco);
			VERIFY(guiConn);
			CopyTo(bstr,guiConn->name);
			objList.AddTail(guiConn);
			connList.AddTail(guiConn);
		}
	}
	MGACOLL_ITERATE_END;
}

// ??
void CGMEView::CreateGuiObjects()
{
	CComBSTR bstr;
	COMTHROW(currentModel->get_Name(&bstr));
	CopyTo(bstr,name);

	CreateAnnotators();

	CComPtr<IMgaFCOs> fcos;
	COMTHROW(currentModel->get_ChildFCOs(&fcos));

	CreateGuiObjects(fcos,children,connections);

	InitSets();
	if(GetDocument()->GetEditMode() == GME_SET_MODE && currentSet) {
		CGuiFco::GrayOutFcos(children,true);
		CGuiFco::GrayOutFcos(connections,true);
		CGuiAnnotator::GrayOutAnnotations(annotators, true);
		currentSet->GrayOutMembers(false);
		currentSet->GrayOut(false);
	}

	CGuiFco::SetAspect(children,currentAspect->index);
	CGuiAnnotator::SetAspect(annotators, currentAspect->index);
	ResolveConnections();

	CComPtr<IMgaObject> cont;
	objtype_enum tp;
	COMTHROW(currentModel->GetParent(&cont,&tp));
	if(tp == OBJTYPE_MODEL) {
		parent = 0;
		COMTHROW(cont.QueryInterface(&parent));
	}
}

void CGMEView::CreateAnnotators(CComPtr<IMgaRegNodes> &regNodes, CGuiAnnotatorList &annList)
{
	MGACOLL_ITERATE(IMgaRegNode, regNodes) {
		CComPtr<IMgaRegNode> anNode;
		anNode = MGACOLL_ITER;
		bool arch = !isSubType && isType; // archetype if not subtype and not instance (type)
		if( arch || !arch && CGuiAnnotator::Showable( anNode ))
		{
			CGuiAnnotator *annotator = new CGuiAnnotator(currentModel, anNode, this, guiMeta->NumberOfAspects());
			annList.AddTail(annotator);
		}
	}
	MGACOLL_ITERATE_END;
}

void CGMEView::CreateAnnotators()
{
	try {
		CComPtr<IMgaRegNode> anRoot;
		CComBSTR path(AN_ROOT);
		COMTHROW(currentModel->get_RegistryNode(path, &anRoot));
		if (anRoot != NULL) {
			CComPtr<IMgaRegNodes> anNodes;
#pragma warning(disable: 4310) // cast truncates constant value
			COMTHROW(anRoot->get_SubNodes(VARIANT_TRUE, &anNodes));
#pragma warning(default: 4310) // cast truncates constant value
			CreateAnnotators(anNodes, annotators);
		}
	}
	catch (hresult_exception &) {
	}
}

void CGMEView::ResetPartBrowser()
{
	guiMeta->ResetParts();
	CMainFrame::theInstance->SetPartBrowserMetaModel(guiMeta);
	CMainFrame::theInstance->SetPartBrowserBg(bgColor);
	CMainFrame::theInstance->RePaintPartBrowser();
}


void CGMEView::Reset(bool doInvalidate)
{
//	CGMEView* gmeviewA = (CGMEView*)GetActiveView();
//	if (gmeviewA)
	if (m_isActive)
	{
		TRACE("CGMEView::Reset GetActiveView\n");
		/*gmeviewA->*/m_refreshpannwin = true; 
	}
	CComPtr<IMgaFCO> selConn;
	if (selectedConnection != NULL)
		selConn = selectedConnection->mgaFco;
	try {
	BeginTransaction(TRANSACTION_READ_ONLY);
		validGuiObjects = false;

		BeginWaitCursor();

		// store the ids of the objects placed into the notifiable objects
		CStringList lstSelBuffIDs;
		CStringList lstUnsBuffIDs;
		CString     cntxSelID;
		CString     cntxAnnID;
		if( contextSelection)
			cntxSelID = contextSelection->id;
		if( contextAnnotation)
			cntxAnnID = contextAnnotation->id;

		for( std::list<CGuiObject*>::iterator iti = m_lstSelect.begin(); iti != m_lstSelect.end(); ++iti)
			lstSelBuffIDs.AddTail( (*iti)->id);

		for( std::list<CGuiObject*>::iterator itj = m_lstUnselect.begin(); itj != m_lstUnselect.end(); ++itj)
			lstUnsBuffIDs.AddTail( (*itj)->id);

		CStringList selIDs;
		CStringList selAnIDs;
		if(newObjectIDs.IsEmpty()) {
			POSITION pos = selected.GetHeadPosition();
			while(pos) {
				CGuiObject *obj = selected.GetNext(pos);
				selIDs.AddTail(obj->id);
			}
			pos = selectedAnnotations.GetHeadPosition();
			while(pos) {
				selAnIDs.AddTail(selectedAnnotations.GetNext(pos)->id);
			}
		}
		else {
			selIDs.AddHead(&newObjectIDs);
			newObjectIDs.RemoveAll();
		}

		currentSetID.Empty();
		if(currentSet) {
			CComBSTR bstr;
			currentSet->mgaFco->get_ID(&bstr);
			CopyTo(bstr,currentSetID);
			currentSet = 0;
		}

		ClearConnSpecs();
		tmpConnectMode = false;

		POSITION pos = children.GetHeadPosition();
		while(pos) {
			CGuiFco *fco = children.GetNext(pos);
			CGuiObject *obj = dynamic_cast<CGuiObject *>(fco);
			if(obj && obj->IsVisible()) {
				if(obj->GetRouterBox())					// it may be a new object not yet routed
					obj->RemoveFromRouter(router);
			}
			delete obj;
		}

		RemoveAllAnnotationFromSelection();
		pos = annotators.GetHeadPosition();
		while(pos) {
			delete annotators.GetNext(pos);
		}

		ClearConnectionSelection();
		pos = connections.GetHeadPosition();
		while(pos) {
			CGuiConnection *conn = connections.GetNext(pos);
			//vt THIS MIGHT BE UNNECESSARY
			conn->RemoveFromRouter(router);
			delete conn;
		}


		m_lstSelect.clear(); // clear the contents of these buffers [will be refilled soon] 
		m_lstUnselect.clear();
		contextAnnotation = 0; contextSelection = 0; contextPort = 0;// these will be recalculated also
		children.RemoveAll();
		annotators.RemoveAll();
		connections.RemoveAll();
		selected.RemoveAll(); // we don't call here the this->SendUnselEvent4List( &selected); because it might contain freshly deleted objects, which can't be notified


		// Now build up new objectset

		CreateGuiObjects();
		SetProperties();
		SetBgColor();

		// Note: Refresh type/subtype/instance property - if it crashes, contact Peter
		{
			baseType = NULL;
			VARIANT_BOOL b;
			COMTHROW(currentModel->get_IsInstance(&b));
			isType = (b == VARIANT_FALSE);
			if(isType) {
				COMTHROW(currentModel->get_BaseType(&baseType));
			}
			else{
				COMTHROW(currentModel->get_Type(&baseType));
			}

			if(isType) {
				CComPtr<IMgaModel> type;
				FindDerivedFrom(currentModel,type);
				isSubType = (type != 0);
			}
		}
		// EndNote

		if( !(selIDs.IsEmpty() && lstSelBuffIDs.IsEmpty() && lstUnsBuffIDs.IsEmpty() && cntxSelID.IsEmpty()))
		{
			// filling up selected, m_lstSelect and m_lstUnselect lists
			POSITION oPos = children.GetHeadPosition();
			while(oPos) {
				CGuiObject *obj = dynamic_cast<CGuiObject *>(children.GetNext(oPos));
				if( obj)
				{
					if( !cntxSelID.IsEmpty() && obj->id == cntxSelID)
						contextSelection = obj;
					
					POSITION sPos = selIDs.GetHeadPosition();
					while( sPos) {
						CString id = selIDs.GetNext( sPos);
						if( id == obj->id)
						{
							selected.AddTail( obj);
							sPos = 0;
						}
					}

					bool found = false; // will save time because if obj is in lstSelBuffIDs (m_lstSelect), it can't be in lstUnsBuffIDs (m_lstUnselect)
					sPos = lstSelBuffIDs.GetHeadPosition();
					while( !found && sPos) {
						CString id = lstSelBuffIDs.GetNext( sPos);
						if( id == obj->id)
						{
							m_lstSelect.push_back( obj);
							found = true;
						}
					}

					sPos = lstUnsBuffIDs.GetHeadPosition();
					while( !found && sPos) {
						CString id = lstUnsBuffIDs.GetNext( sPos);
						if( id == obj->id)
						{
							m_lstUnselect.push_back( obj);
							found = true;
						}
					}
				}
			}
		}

		// selected was filled up previously like this:
		// now it is done along with m_lstSelect, m_lstUnselect
		//pos = selIDs.GetHeadPosition();
		//while(pos) {
		//	CString id = selIDs.GetNext(pos);
		//	POSITION oPos = children.GetHeadPosition();
		//	while(oPos) {
		//		CGuiObject *obj = dynamic_cast<CGuiObject *>(children.GetNext(oPos));
		//		if(obj) {
		//			if(id == obj->id)
		//				selected.AddTail(obj); // this->SendSelecEvent4Object( obj); omitted because of a READONLY transaction
		//		}
		//	}
		//}

		// selectedAnnotations was filled up previously like this:
		//pos = selAnIDs.GetHeadPosition();
		//while(pos) {
		//	CString id = selAnIDs.GetNext(pos);
		//	POSITION oPos = annotators.GetHeadPosition();
		//	while(oPos) {
		//		CGuiAnnotator *ann = annotators.GetNext(oPos);
		//		if (id == ann->id) {
		//			AddAnnotationToSelectionTail(ann);
		//		}
		//	}
		//}		

		pos = annotators.GetHeadPosition();
		while(pos) {
			CGuiAnnotator *ann = annotators.GetNext(pos);
			POSITION oPos = selAnIDs.GetHeadPosition();
			while(oPos) {
				CString id = selAnIDs.GetNext(oPos);
				if (id == ann->id) {
					AddAnnotationToSelectionTail(ann);
				}
			}
			if( !cntxAnnID.IsEmpty() && cntxAnnID == ann->id)
				contextAnnotation = ann;
		}

		CommitTransaction();
	}
	catch(hresult_exception &e) {
		AbortTransaction(e.hr);
		AfxMessageBox("Unable to refresh model");
		CGMEEventLogger::LogGMEEvent("CGMEView::Reset - Unable to refresh model.\r\n");
		frame->PostMessage(WM_CLOSE);
		EndWaitCursor();
		return;
	}


	Invalidate(doInvalidate);
	AutoRoute();

	EndWaitCursor();

	SendNow(true);

	POSITION pos = selected.GetHeadPosition();
	while (pos) {
		CGuiObject* go = selected.GetNext(pos);
		if (go && go->mgaFco) {
			long oStatus;
			COMTHROW(go->mgaFco->get_Status(&oStatus));
			if (oStatus == OBJECT_EXISTS) {	// make sure it has not been deleted since then
				// Sending decorator events (for efficiency)
				CGuiAspect* pAspect = go->GetCurrentAspect();
				if (pAspect != NULL) {
					CComQIPtr<IMgaNewDecorator> newDecorator(pAspect->GetDecorator());
					if (newDecorator)
						HRESULT retVal = newDecorator->SetSelected(VARIANT_TRUE);
				}
			}
		}
	}

	if (selConn != NULL) {
		pos = connections.GetHeadPosition();
		while(pos) {
			CGuiConnection *conn = connections.GetNext(pos);
			if (conn->mgaFco == selConn) {
				selectedConnection = conn;
				conn->SetSelect(true);
				break;
			}
		}
	}
}

void CGMEView::InitSets()
{
	POSITION pos = children.GetHeadPosition();
	while(pos) {
		CGuiSet *set = dynamic_cast<CGuiSet *>(children.GetNext(pos));
		if(set)
			set->Init(children,connections);
	}
}

void CGMEView::ChangeAttrPrefObjs(CGuiObjectList &objlist)
{
	CComPtr<IMgaObjects> mgaobjs;
	COMTHROW(mgaobjs.CoCreateInstance(L"Mga.MgaObjects"));
	POSITION pos = objlist.GetHeadPosition();
	while (pos) {
		CGuiObject *guiObj = objlist.GetNext(pos);
		CComPtr<IMgaObject> mgaobj;
		COMTHROW(guiObj->mgaFco.QueryInterface(&mgaobj));
		COMTHROW(mgaobjs->Append(mgaobj));
	}

	CGMEObjectInspector::theInstance->SetObjects(mgaobjs);
}

void CGMEView::ChangeAttrPrefFco(CGuiFco* guiFco)
{
	CGuiConnection* conn = dynamic_cast<CGuiConnection*> (guiFco);
	if (conn != NULL) {
		if (selectedConnection != conn) {
			if (selectedConnection != NULL)
				selectedConnection->SetSelect(false);
			conn->SetSelect(true);
			selectedConnection = conn;
		}
	} else {
		if (selectedConnection != NULL)
			selectedConnection->SetSelect(false);
		selectedConnection = NULL;
	}

	CComPtr<IMgaObjects> mgaobjs;
	COMTHROW(mgaobjs.CoCreateInstance(L"Mga.MgaObjects"));
	CComPtr<IMgaObject> mgaobj;
	COMTHROW(guiFco->mgaFco.QueryInterface(&mgaobj));
	COMTHROW(mgaobjs->Append(mgaobj));

	CGMEObjectInspector::theInstance->SetObjects(mgaobjs);
}

void CGMEView::ChangeAttrPrefFco() // currentModel
{
	if (selectedConnection != NULL)
		selectedConnection->SetSelect(false);
	selectedConnection = NULL;

	CComPtr<IMgaObjects> mgaobjs;
	COMTHROW(mgaobjs.CoCreateInstance(L"Mga.MgaObjects"));
	CComPtr<IMgaObject> mgaobj;
	COMTHROW(currentModel.QueryInterface(&mgaobj));
	COMTHROW(mgaobjs->Append(mgaobj));

	CGMEObjectInspector::theInstance->SetObjects(mgaobjs);
}

void CGMEView::ShowProperties(CGuiFco* guiFco)
{
	CGMEEventLogger::LogGMEEvent("CGMEView::ShowProperties("+guiFco->GetName()+" "+guiFco->GetID()+")\r\n");
    ChangeAttrPrefFco(guiFco);

	CGMEObjectInspector::theInstance->ShowPanel(2);
}

void CGMEView::ShowProperties()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::ShowProperties()\r\n");
    ChangeAttrPrefFco();

	CGMEObjectInspector::theInstance->ShowPanel(2);
}

void CGMEView::ShowAttributes(CGuiFco* guiFco)
{
	CGMEEventLogger::LogGMEEvent("CGMEView::ShowAttributes("+guiFco->GetName()+" "+guiFco->GetID()+")\r\n");
	ChangeAttrPrefFco(guiFco);

	CGMEObjectInspector::theInstance->ShowPanel(0);
}

// TODO
void CGMEView::ShowAttributes()	// currentModel
{
	CGMEEventLogger::LogGMEEvent("CGMEView::ShowAttributes() on "+path+name+"\r\n");
	ChangeAttrPrefFco();

	CGMEObjectInspector::theInstance->ShowPanel(0);
}

void CGMEView::ShowPreferences(CGuiFco *guiFco)
{
	CGMEEventLogger::LogGMEEvent("CGMEView::ShowPreferences("+guiFco->GetName()+" "+guiFco->GetID()+")\r\n");
	ChangeAttrPrefFco(guiFco);

	CGMEObjectInspector::theInstance->ShowPanel(1);
}


// TODO
void CGMEView::ShowPreferences()	// currentModel
{
	CGMEEventLogger::LogGMEEvent("CGMEView::ShowPreferences()\r\n");
	ChangeAttrPrefFco();

	CGMEObjectInspector::theInstance->ShowPanel(1);
}

void CGMEView::RetrievePath()
{
	if ( currentModel ) {
		BeginTransaction(TRANSACTION_READ_ONLY);
		path = "";
		CComPtr<IMgaObject> spObject = currentModel.p;
		while ( true ) {
			CComPtr<IMgaObject> spParent;
			if ( SUCCEEDED( spObject->GetParent( &spParent ) ) && spParent ) {;
				CComBSTR bstrName;
				COMTHROW( spParent->get_Name( &bstrName ) );
				path = CString( bstrName ) + "/" + path;
				spObject = spParent;
			}
			else
				break;
		}
		path = "/" + path;
		CommitTransaction();
	}
}

void CGMEView::SetName()
{
	if(currentModel != 0) {
		try {
			BeginTransaction(TRANSACTION_READ_ONLY);
			CComBSTR bstr;
			COMTHROW(currentModel->get_Name(&bstr));
			CopyTo(bstr,name);
			CommitTransaction();

			RetrievePath();

			frame->title = name + " - " + path;
			frame->OnUpdateFrameTitle(true);

			SetNameProperty();
		}
		catch(hresult_exception &e) {
			AbortTransaction(e.hr);
		}
	}
}

void CGMEView::SetBgColor()
{
	if(currentModel != 0) {
		try {
			BeginTransaction(TRANSACTION_READ_ONLY);
			CComBSTR bstr;
			CComBSTR path(MODEL_BACKGROUND_COLOR_PREF);
			COMTHROW(currentModel->get_RegistryValue(path, &bstr));
			CString strVal(bstr);
			unsigned int hexval;
			if (_stscanf(strVal,_T("%x"),&hexval) == 1) {
				unsigned int r = (hexval & 0xff0000) >> 16;
				unsigned int g = (hexval & 0xff00) >> 8;
				unsigned int b = hexval & 0xff;
				bgColor = RGB(r,g,b);
			}
			else {
				bgColor = ::GetSysColor(COLOR_WINDOW);
			}
			CMainFrame::theInstance->SetPartBrowserBg(bgColor);
			CMainFrame::theInstance->RePaintPartBrowser();
			CommitTransaction();
		}
		catch(hresult_exception &e) {
			AbortTransaction(e.hr);
		}
	}
}

// prevous zoom value : curzoom
// new zoom value stored in m_zoomVal
// point : win client coordinates - this image point has to be centered
void CGMEView::SetZoomPoint(int curzoom, CPoint point)
{
	CRect clientW(0,0,0,0);
	GetClientRect(&clientW);
	int w = clientW.Width(); 
	int h = clientW.Height(); 
	CPoint offset = CPoint(w,h);
	{
		CWindowDC dc(NULL);
		dc.SetMapMode(MM_ISOTROPIC);
		dc.SetWindowExt(100,100);
		dc.SetViewportExt(curzoom, curzoom);
		dc.DPtoLP((LPPOINT)&point);
	}
	{
		CWindowDC dc(NULL);
		dc.SetMapMode(MM_ISOTROPIC);
		dc.SetWindowExt(100,100);
		dc.SetViewportExt(m_zoomVal, m_zoomVal);
		dc.DPtoLP((LPPOINT)&offset);
	}
	offset.x /= 2;
	offset.y /= 2;

	CPoint scp = GetScrollPosition();       // upper corner of scrolling
	m_zoomP = scp+point-offset;

	m_zoomScroll = true;
}

void CGMEView::ZoomIn(CPoint point)
{
	CGMEEventLogger::LogGMEEvent("CGMEView::ZoomIn() in "+path+name+"\r\n");
//	zoomIdx = min(GME_ZOOM_LEVEL_NUM-1, zoomIdx+1);
	int curzoom = m_zoomVal;
	frame->propBar.NextZoomVal(m_zoomVal);
//	CMainFrame::theInstance->WriteStatusZoom(setZoomPercents[zoomIdx]);
	CMainFrame::theInstance->WriteStatusZoom(m_zoomVal);
	m_zoomP.x = m_zoomP.y = 0;
	if (curzoom == m_zoomVal)
		return;

	SetZoomPoint(curzoom, point);
}

void CGMEView::ZoomOut(CPoint point)
{
	CGMEEventLogger::LogGMEEvent("CGMEView::ZoomOut() in "+path+name+"\r\n");
//	zoomIdx = max(0, zoomIdx-1);
	int curzoom = m_zoomVal;
	frame->propBar.PrevZoomVal(m_zoomVal);
//	CMainFrame::theInstance->WriteStatusZoom(setZoomPercents[zoomIdx]);
	CMainFrame::theInstance->WriteStatusZoom(m_zoomVal);
	m_zoomP.x = m_zoomP.y = 0;
	if (curzoom == m_zoomVal)
		return;

	SetZoomPoint(curzoom, point);
}

void CGMEView::ShowHelp(CComPtr<IMgaFCO> fco)
{
	try {
		BeginTransaction(TRANSACTION_READ_ONLY);

		CGMEEventLogger::GMEEventPrintf("CGMEView::ShowHelp(%Z) in "+path+name+"\r\n",fco,NULL);
		CComObjPtr<IMgaLauncher> launcher;
		COMTHROW( launcher.CoCreateInstance(L"Mga.MgaLauncher") );
		COMTHROW( launcher->ShowHelp(fco) );
		CommitTransaction();
	}
	catch(hresult_exception &e) {
		AbortTransaction(e.hr);
		AfxMessageBox("Unable to access context-specific help information!",MB_OK | MB_ICONSTOP);
		CGMEEventLogger::LogGMEEvent("CGMEView::ShowHelp - Unable to access context-specific help information.\r\n");
	}
}

// ??
void CGMEView::ShowModel(CComPtr<IMgaModel> model,CString *aspect)
{
	// FIX for JIRA bug: GME-135
	if( !model) return;
#if !defined (ACTIVEXGMEVIEW)
	// endFIX
	CString newAspect = aspect ? *aspect : currentAspect->name;
	CGMEDoc *doc = GetDocument();
	CGMEView *view = doc->FindView(model);
	CComPtr<IMgaFCO> fakeObj;
	if(!view)
		doc->SetNextToView(model,newAspect, fakeObj);
	else
		view->ChangeAspect(newAspect);
	CMainFrame::theInstance->CreateNewView(view, model);
	if( theApp.isHistoryEnabled())
	{
		doc->tellHistorian( model, newAspect);
		doc->clearForwHistory();
	}
#endif
}

void CGMEView::GetModelInContext(CComPtr<IMgaModel> &model)
{
	if(contextSelection)
		VERIFY(SUCCEEDED(contextSelection->mgaFco.QueryInterface(&model)));
	else
		model = currentModel;
	VERIFY(model != 0);
}

void CGMEView::FindDerivedFrom(CComPtr<IMgaModel> model,CComPtr<IMgaModel> &type)
{
	CComPtr<IMgaFCO> der;
	try {
		BeginTransaction(TRANSACTION_READ_ONLY);
		CGMEEventLogger::GMEEventPrintf("CGMEView::FindDerivedFrom(model=%Z,type=%z)\r\n",model,type);
		COMTHROW(model->get_DerivedFrom(&der));
		if(der != 0)
			COMTHROW(der.QueryInterface(&type));
		CommitTransaction();
	}
	catch(hresult_exception e) {
		AbortTransaction(e.hr);
		AfxMessageBox("Unable to find type model",MB_ICONSTOP | MB_OK);
		CGMEEventLogger::LogGMEEvent("    Unable to find type model\r\n");
	}
}

void CGMEView::DrawConnections(CDC* pDC)
{
	Gdiplus::Graphics gdip(pDC->m_hDC);
	gdip.SetPageUnit(Gdiplus::UnitPixel);
	gdip.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
	gdip.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);

	POSITION pos = connections.GetHeadPosition();
	while (pos) {
		CGuiConnection* conn = connections.GetNext(pos);
		if (conn->IsVisible()) {
			conn->Draw(&gdip, pDC);
		}
	}
}

void CGMEView::AutoRoute()
{
	BeginWaitCursor();
	router.AutoRoute(children);  // Must reroute the whole thing, other code depends on it
	EndWaitCursor();
}

void CGMEView::IncrementalAutoRoute()
{
	BeginWaitCursor();
	router.AutoRoute();
	EndWaitCursor();
}

void CGMEView::ModeChange()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::ModeChange in "+path+name+"\r\n");
	this->SendUnselEvent4List( &selected);
	selected.RemoveAll();
	RemoveAllAnnotationFromSelection();
	ClearConnectionSelection();
	ClearConnSpecs();
	CGMEDoc *pDoc = GetDocument();
	CGuiAnnotator::GrayOutAnnotations(annotators, pDoc->GetEditMode() == GME_VISUAL_MODE);
	CGuiFco::GrayOutFcos(children,pDoc->GetEditMode() == GME_VISUAL_MODE);
	CGuiFco::GrayOutFcos(connections,pDoc->GetEditMode() == GME_VISUAL_MODE);
	tmpConnectMode = false;
	Invalidate();
}

int CGMEView::OnToolHitTest( CPoint point, TOOLINFO* pTI ) const
{
	static CGuiObject *oldObject = 0;
	static CGuiPort *oldPort = 0;
	CGMEView *self = const_cast<CGMEView *>(this);
	CoordinateTransfer(point);

#ifdef _ARDEBUG
	SArEdge* edge = router.router->GetListEdgeAt(point, 2);
	if( edge )
	{
		pTI->hwnd = m_hWnd;
		pTI->rect = CRect(point.x - 3, point.y - 3, point.x + 3, point.y + 3);
		pTI->uId = 1;
		CString str;
		str.Format("%p y=%f (%d,%d,%d,%d) prev=%p next=%p",
			edge, edge->position_y,
			edge->startpoint->x, edge->startpoint->y,
			edge->endpoint->x, edge->endpoint->y,
			edge->block_prev, edge->block_next);
		pTI->lpszText = _strdup(str);
		return 1;
	}
	return -1;
#endif
	CGuiConnection *conn= router.FindConnection(point);
	if(conn)
	{
		pTI->hwnd = m_hWnd;
		pTI->rect = CRect(point.x - 8, point.y - 8, point.x + 8, point.y + 8);
		pTI->uId = 1;
		CString str = conn->GetInfoText();
		pTI->lpszText = _strdup(str);
		return 1;
	}

	CGuiObject *object = self->FindObject(point);
	if(object) {
		CString portinfo;
		CRect rect = object->GetLocation();
		CGuiPort *port = object->FindPort(point);
		if(port && port->IsRealPort()) {
			portinfo = " : " + port->GetInfoText();
			rect = port->GetLocation() + rect.TopLeft();
		}
		if(object != oldObject || port != oldPort) {
			oldPort = port;
			oldObject = object;
			return -1;
		}

		CClientDC dc(self);
		self->OnPrepareDC(&dc);
		dc.LPtoDP(rect);
		pTI->hwnd = m_hWnd;
		pTI->rect = rect;
		pTI->uId = 1;
		pTI->lpszText = _strdup(object->GetInfoText() + portinfo);
		return 1;
	}
	oldObject = 0;
	return -1;
}

void CGMEView::CreateOffScreen(CDC *dc)
{
	if(offScreenCreated)
		return;
	offScreenCreated = true;
	offScreen = new CDC;
	offScreen->CreateCompatibleDC(dc);
	ASSERT(GetSystemMetrics(SM_SAMEDISPLAYFORMAT));
	// In multi-monitor systems a window can bigger than just one screen, monitor resolutions can be different, etc.
	// TODO: Maybe we should calculate with SM_CXMAXTRACK,SM_CYMAXTRACK? A window can be larger than the displays!!!
	// TODO: handle run-time resolution changes!
	int offScreenWidth = GetSystemMetrics(SM_CXMAXTRACK);
	int offScreenHeight = GetSystemMetrics(SM_CYMAXTRACK);
//	int offScreenWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
//	int offScreenHeight = GetSystemMetrics(SM_CYVIRTUALSCREEN);
	ofsbmp = new CBitmap;
	ofsbmp->CreateCompatibleBitmap(dc,offScreenWidth,offScreenHeight);
	// HACK: what about palettes?
	offScreen->SelectObject(ofsbmp);
}

void CGMEView::SetScroll()
{
	CRect objext, annext, extent;
	CGuiObject::GetExtent(children, objext);
	CGuiAnnotator::GetExtent(annotators, annext);
	extent.UnionRect(&objext, &annext);
	extent.right = (int)(extent.right*EXTENT_ERROR_CORR); // ??
	extent.bottom = (int)(extent.bottom*EXTENT_ERROR_CORR); // ??
	CSize s(extent.right, extent.bottom);
//	s.cx = s.cx + END_SCROLL_OFFSET;
//	s.cy = s.cy + END_SCROLL_OFFSET;

//	if (setZoomPercents[zoomIdx] == 100) {
	if (m_zoomVal == ZOOM_NO) {
		SetScrollSizes(MM_TEXT,s, m_zoomVal); // setZoomPercents[zoomIdx]);
	}
	else {
		SetScrollSizes(MM_ISOTROPIC,s, m_zoomVal); // setZoomPercents[zoomIdx]);
	}
}

void CGMEView::SetCenterObject(CComPtr<IMgaFCO> centerObj)
{
	if(centerObj != NULL) {
		CGuiObject *guiObj;
		try {
			BeginTransaction(TRANSACTION_READ_ONLY);
			guiObj = CGuiObject::FindObject(centerObj, children);
			CommitTransaction();
		}
		catch(hresult_exception e) {
			AbortTransaction(e.hr);
			guiObj = NULL;
		}

		// TODO: Connections
		if (guiObj) {
			CGMEEventLogger::LogGMEEvent("CGMEView::SetCenterObject("+guiObj->GetName()+" "+guiObj->GetID()+") in "+path+name+"\r\n");
			if (!guiObj->IsVisible()) {
				int aspNum = guiMeta->aspects.GetCount();
				for (int aindex = 0; aindex < aspNum; aindex++) {
					if (guiObj->IsVisible(aindex)) {
						ChangeAspect(aindex);
						CMainFrame::theInstance->ChangePartBrowserAspect(aindex);
						break;
					}
				}
			}
			if (guiObj->IsVisible()) {
				CDC *pDC = GetDC();
				OnPrepareDC(pDC);
				CPoint centerPt = guiObj->GetCenter();
				CRect wndRect;
				GetClientRect(&wndRect);
				pDC->DPtoLP(&wndRect);
				CSize totalSize = GetTotalSize();
				CPoint spos;
				spos.x = centerPt.x - (wndRect.Width()/2);
				spos.y = centerPt.y - (wndRect.Height()/2);

				spos.x = max(spos.x, 0L);
				spos.x = min(spos.x, totalSize.cx);
				spos.y = max(spos.y, 0L);
				spos.y = min(spos.y, totalSize.cy);

				this->SendUnselEvent4List( &selected);
				selected.RemoveAll();
				RemoveAllAnnotationFromSelection();
				ClearConnectionSelection();
				this->SendSelecEvent4Object( guiObj);
				selected.AddTail(guiObj);
				ScrollToPosition(spos);
				ChangeAttrPrefFco(guiObj);
				Invalidate();
				this->SendNow();
			}
		}
	}
}


void CGMEView::Invalidate(bool thorough)
{
	if(thorough) {
		modelGrid.Clear();
		FillModelGrid();
	}
	SetScroll();
	CScrollZoomView::Invalidate();
}

int CGMEView::GetAspectProperty()
{
	CComboBox *box;
	box = (CComboBox *)(frame->propBar.GetDlgItem(IDC_ASPECT));
	ASSERT(box);
	return box->GetCurSel();
}

void CGMEView::SetAspectProperty(int ind)
{
	CComboBox *box;
	box = (CComboBox *)(frame->propBar.GetDlgItem(IDC_ASPECT));
	ASSERT(box);
	box->SetCurSel(ind);
}

void CGMEView::SetNameProperty()
{
	CWnd *ctrl;
	ctrl = frame->propBar.GetDlgItem(IDC_NAME);
	ASSERT(ctrl);
	ctrl->SetWindowText( name );
	frame->title = name + " - " + path;
	frame->OnUpdateFrameTitle(true);
}

void CGMEView::GetNameProperty(CString &txt)
{
	CWnd *ctrl;
	ctrl = frame->propBar.GetDlgItem(IDC_NAME);
	ASSERT(ctrl);
	ctrl->GetWindowText(txt);
}

void CGMEView::SetKindNameProperty()
{
	CWnd *ctrl;
	ctrl = frame->propBar.GetDlgItem(IDC_KINDNAME);
	ASSERT(ctrl);
	ctrl->SetWindowText(kindDisplayedName);
}

void CGMEView::SetTypeProperty(bool type)
{
	if(type)
		frame->propBar.ShowType();
	else
		frame->propBar.ShowInstance();
}

void CGMEView::SetTypeNameProperty()
{
	CWnd *ctrl;
	ctrl = frame->propBar.GetDlgItem(IDC_TYPENAME);
	ASSERT(ctrl);
	CComPtr<IMgaFCO> fco;
	CComBSTR bstr;
	CString txt = "N/A";
	if(baseType != 0) {
		COMTHROW(baseType->get_Name(&bstr));
		CopyTo(bstr,txt);
	}
	RetrievePath();
	ctrl->SetWindowText(txt);
	frame->title = name + " - " + path;
	frame->OnUpdateFrameTitle(true);
}

void CGMEView::SetProperties()
{
	SetTypeProperty(isType);
	SetTypeNameProperty();
	SetNameProperty();
	SetKindNameProperty();

	CComboBox *box = (CComboBox *)(frame->propBar.GetDlgItem(IDC_ASPECT));
	ASSERT(box);
	if(box->GetCount() <= 0) {
		guiMeta->InitAspectBox(box);
		box->SetCurSel(currentAspect->index);
	}
}

void CGMEView::CoordinateTransfer(CPoint &point) const
{
	CClientDC dc(const_cast<CGMEView *>(this));
	(const_cast<CGMEView *>(this))->OnPrepareDC(&dc);
	dc.DPtoLP(&point);
}

CGuiObject *CGMEView::FindFirstObject()
{
	m_findNextAlreadyAchieved = 0; // reset the currently achieved minimum level to its default

	return HelpMeFindNextObject( false);
}

CGuiObject *CGMEView::FindNextObject()
{
	return HelpMeFindNextObject( true);
}

CGuiObject *CGMEView::HelpMeFindNextObject( bool p_secondFind)
{
	CGuiObject*      first     = 0;
	unsigned long    first_abs = 0; // distance square from (0,0)
	CPoint           first_pos( 0, 0);

	POSITION pos = children.GetHeadPosition();
	while(pos) {
		CGuiObject *cur = dynamic_cast<CGuiObject *>( children.GetNext( pos));
		if( cur && cur->IsVisible())
		{
			CPoint        cur_pos = cur->GetCenter();
			unsigned long cur_abs = cur_pos.x * cur_pos.x + cur_pos.y * cur_pos.y;

			// m_findNextAlreadyAchieved is the previously achieved minimum distance
			// and we need to get further now if not invoked from FindFirst
			// we disregard objects closer than m_curAbs
			if( p_secondFind && cur_abs <= m_findNextAlreadyAchieved)
				continue; // skip if its closer than the allowed/required level

			if( !first) 
			{
				first      = cur;
				first_pos  = cur_pos;
				first_abs  = cur_abs;
			}
			else
			{
				if( first_abs > cur_abs) // 'cur' closer to (0, 0) than 'first'?
				{
					first     = cur;
					first_pos = cur_pos;
					first_abs = cur_abs;
				}
			}
		}
	}

	if( first) // something found
		m_findNextAlreadyAchieved = first_abs;
	return first;
}

CGuiObject *CGMEView::FindObject(CPoint &pt, bool lookNearToo, bool lookForLabel)
{
	POSITION pos = children.GetHeadPosition();
	while(pos) {
		CGuiObject *obj = dynamic_cast<CGuiObject *>(children.GetNext(pos));
		if(obj && obj->IsVisible()) {
			if (!lookForLabel) {
				if (obj->IsInside(pt, lookNearToo))
					return obj;
			} else {
				if (obj->IsLabelInside(pt, lookNearToo))
					return obj;
			}
		}
	}
	return NULL;
}

CGuiAnnotator *CGMEView::FindAnnotation(CPoint &pt)
{
	POSITION pos = annotators.GetHeadPosition();
	while(pos) {
		CGuiAnnotator *ann = annotators.GetNext(pos);
		if (ann->IsVisible() && ann->GetLocation().PtInRect(pt)) {
			return ann;
		}
	}
	return 0;
}

bool CGMEView::FindObjects(CRect &rect,CGuiObjectList &objectList)
{
	bool ret = false;
	CGuiObject *obj;
	CRect r,dummy;
	POSITION pos = children.GetHeadPosition();
	while(pos) {
		obj = dynamic_cast<CGuiObject *>(children.GetNext(pos));
		if(obj) {
			if(!obj->IsVisible())
				continue;
			r = obj->GetLocation();
			if(dummy.IntersectRect(&r,&rect)) {
				objectList.AddTail(obj);
				ret = true;
			}
		}
	}
	return ret;
}

bool CGMEView::FindAnnotations(CRect &rect,CGuiAnnotatorList &annotatorList)
{
	bool ret = false;
	CRect r,dummy;
	POSITION pos = annotators.GetHeadPosition();
	while(pos) {
		CGuiAnnotator *ann = annotators.GetNext(pos);
		if(!ann->IsVisible())
			continue;
		r = ann->GetLocation();
		if(dummy.IntersectRect(&r,&rect)) {
			annotatorList.AddTail(ann);
			ret = true;
		}
	}
	return ret;
}

void CGMEView::DisconnectAll(CGuiObject *end,CGuiPort *endPort,bool onlyVisible)
{
	if(endPort)
		CGMEEventLogger::LogGMEEvent("CGMEView::DisconnectAll(end="+end->GetName()+" "+end->GetID()+" endPort="+endPort->GetName()+" "+endPort->GetID()+")\r\n");
	else
		CGMEEventLogger::LogGMEEvent("CGMEView::DisconnectAll(end="+end->GetName()+" "+end->GetID()+")\r\n");
	CGuiConnectionList conns;
	FindConnections(end,endPort,conns);
	POSITION pos = conns.GetHeadPosition();
	while(pos) {
		CGuiConnection *guiConn = conns.GetNext(pos);
		if(!onlyVisible || guiConn->IsVisible()) {
			try {
				BeginTransaction();
				long status;
				COMTHROW(guiConn->mgaFco->get_Status(&status));
				if(status == OBJECT_EXISTS)
					DeleteConnection(guiConn,false);
				CommitTransaction();
			}
			catch(hresult_exception e) {
				AbortTransaction(e.hr);
				AfxMessageBox("Unable to delete connection",MB_ICONSTOP | MB_OK);
				CGMEEventLogger::LogGMEEvent("    Unable to delete connection.\r\n");
			}
		}
	}
}

void CGMEView::FindConnections(CGuiObject *end,CGuiPort *endPort,CGuiConnectionList &res)
{
	POSITION pos = connections.GetHeadPosition();
	while(pos) {
		CGuiConnection *conn = connections.GetNext(pos);
		if(!conn->IsVisible())
			continue;
		if((conn->src == end && conn->srcPort == endPort) ||
				(conn->dst == end && conn->dstPort == endPort))
			res.AddTail(conn);
	}
}

void CGMEView::FindConnections(CGuiObject *end1,CGuiPort *end1Port,CGuiObject *end2,CGuiPort *end2Port,CGuiConnectionList &res)
{
	POSITION pos = connections.GetHeadPosition();
	while(pos) {
		CGuiConnection *conn = connections.GetNext(pos);
		if(!conn->IsVisible())
			continue;
		if((conn->src == end1 && end1Port == conn->srcPort && conn->dst == end2 && end2Port == conn->dstPort) ||
				(conn->src == end2 && end2Port == conn->srcPort &&	conn->dst == end1 && end1Port == conn->dstPort))
			res.AddTail(conn);
	}
}

bool CGMEView::DeleteConnection(CGuiConnection *guiConn,bool checkAspect)
{
	CGMEEventLogger::LogGMEEvent("CGMEView::DeleteConnection("+guiConn->GetName()+" "+guiConn->GetID()+") in "+path+name+"\r\n");
	bool ok = false;
	BeginWaitCursor();
	try {
		BeginTransaction();
		if(!checkAspect || guiConn->IsPrimary(guiMeta,currentAspect)) {
			COMTHROW(guiConn->mgaFco->DestroyObject());
			ok = true;
		}
		CommitTransaction();
	}
	catch(hresult_exception &e) {
		AbortTransaction(e.hr);
		AfxMessageBox("Unable to delete connection",MB_ICONSTOP | MB_OK);
		CGMEEventLogger::LogGMEEvent("    Unable to delete connection.\r\n");
	}
	this->SetFocus();
	return ok;
}

bool CGMEView::CheckBeforeDeleteObjects(CGuiObjectList &objectList,CString &txt)
{
	bool ok = true;
	try {
		BeginTransaction(TRANSACTION_READ_ONLY);
		POSITION pos = objectList.GetHeadPosition();
		while(pos) {
			CGuiObject *guiObj = objectList.GetNext(pos);
			if(!guiObj->IsPrimary(guiMeta,currentAspect)) {
				ok = false;
				txt += "\n   " + guiObj->name;
			}
		}
		CommitTransaction();
	}
	catch(hresult_exception e) {
		AbortTransaction(e.hr);
	}
	return ok;
}

bool CGMEView::DeleteObjects(CGuiObjectList &objectList)
{
	bool brw_refresh_needed = false;
	try {
		CGMEEventLogger::LogGMEEvent("CGMEView::DeleteObjects in "+path+name+"\r\n");
		CString msg;
		if(!CheckBeforeDeleteObjects(objectList,msg)) {
			AfxMessageBox("The following object(s) cannot be deleted: " + msg);
			CGMEEventLogger::LogGMEEvent("    The following object(s) cannot be deleted: "+msg+"\r\n");
			return true;
		}
		BeginWaitCursor();
		BeginTransaction();
		GMEEVENTLOG_GUIOBJS(objectList);
		POSITION pos = objectList.GetHeadPosition();
		while(pos) {
			CGuiObject *obj = objectList.GetNext(pos);

			POSITION pos2 = pendingRequests.GetHeadPosition();
			while (pos2) {
				POSITION tmp = pos2;
				CPendingObjectPosRequest *req = dynamic_cast<CPendingObjectPosRequest *> (pendingRequests.GetNext(pos2));
				if (req) {
					if ( req->object->mgaFco == obj->mgaFco ) {
						pendingRequests.RemoveAt(tmp);
						delete req;
					}
				}
			}

			if (obj->IsVisible()) {
				POSITION pos3 = obj->GetPorts().GetHeadPosition();
				while(pos3) {
						DisconnectAll(obj,obj->GetPorts().GetNext(pos3),false);
				}
			}
		}
		pos = objectList.GetHeadPosition();
		while(pos) {
			CGuiObject *obj = objectList.GetNext(pos);
			long oStatus;
			COMTHROW(obj->mgaFco->get_Status(&oStatus));
			// making sure that the fco was not deleted previously in the loop due to a dependency 
			if(oStatus == OBJECT_EXISTS) {
				// throws E_MGA_MUST_ABORT if user selects CANCEL
				brw_refresh_needed = AskUserAndDetachIfNeeded(obj->mgaFco); // detach the dependents if needed
				COMTHROW(obj->mgaFco->DestroyObject());
				COMTHROW(obj->mgaFco->Close());
			}
		}
		CommitTransaction();
	}
	catch(hresult_exception &e) {
		AbortTransaction(e.hr);
		if( e.hr == E_MGA_MUST_ABORT)
			CGMEEventLogger::LogGMEEvent("    Archetype delete cancelled by user.\r\n");
		else
		{
			AfxMessageBox("Unable to delete models",MB_ICONSTOP | MB_OK);
			CGMEEventLogger::LogGMEEvent("    Unable to delete models.\r\n");
		}
		EndWaitCursor();
		return false;
	}
	EndWaitCursor();
	ResetParent();
	if( brw_refresh_needed) CGMEBrowser::theInstance->RefreshAll();
	this->SetFocus();
	return true;
}

void CGMEView::DeleteAnnotations(CGuiAnnotatorList &annotatorList)
{
	try {
		CGMEEventLogger::LogGMEEvent("CGMEView::DeleteAnnotations() in "+path+name+"\r\n");
		GMEEVENTLOG_GUIANNOTATORS(annotatorList);
		BeginWaitCursor();
		BeginTransaction();
		POSITION pos = annotatorList.GetHeadPosition();
		while(pos) {
			CGuiAnnotator *ann = annotatorList.GetNext(pos);
			if( ann->IsSpecial())
				COMTHROW( CGuiAnnotator::Hide( ann->rootNode));
			else
				COMTHROW(ann->rootNode->RemoveTree());
		}
		CommitTransaction();
	}
	catch(hresult_exception &e) {
		AbortTransaction(e.hr);
		AfxMessageBox("Unable to delete annotations",MB_ICONSTOP | MB_OK);
		CGMEEventLogger::LogGMEEvent("    Unable to delete annotations.\r\n");
		EndWaitCursor();
		return;
	}
	EndWaitCursor();
	ResetParent();
}


bool CGMEView::DoPasteItem(COleDataObject* pDataObject,bool drag,bool move,bool reference,bool derive,bool instance,bool closure,bool merge, CGuiObject *ref,CPoint pt)
{
	CGMEEventLogger::LogGMEEvent("CGMEView::DoPasteItem");
	if(drag)
		CGMEEventLogger::LogGMEEvent(" DRAG");
	if(move)
		CGMEEventLogger::LogGMEEvent(" MOVE");
	if(reference)
		CGMEEventLogger::LogGMEEvent(" REFERENCE");
	if(derive)
		CGMEEventLogger::LogGMEEvent(" DERIVE");
	if(instance)
		CGMEEventLogger::LogGMEEvent(" INSTANCE");
	if(closure)
		CGMEEventLogger::LogGMEEvent(" CLOSURE");
	if(merge)
		CGMEEventLogger::LogGMEEvent(" SMART");
	CGMEEventLogger::LogGMEEvent(" in "+path+name+"\r\n");
	if(ref)
		VERIFY(reference);
	ASSERT(pDataObject != NULL);
	ASSERT_VALID(this);
	bool ok = false;

	try
	{
		CWaitCursor wait;

		if (CGMEDataSource::IsGmeNativeDataAvailable(pDataObject,theApp.mgaProject) && !closure)
		{
			ok = DoPasteNative(pDataObject,drag,move,reference,derive,instance,ref,pt);
		}
		else if( CGMEDataSource::IsXMLDataAvailable(pDataObject) )
		{
			if( closure && theApp.mgaConstMgr) theApp.mgaConstMgr->Enable( false); // if closure is inserted disable the constraint manager ...
			ok = CGMEDataSource::ParseXMLData(pDataObject, currentModel, merge);
			if( closure && theApp.mgaConstMgr) theApp.mgaConstMgr->Enable( true); // ... and enable it after done
		}
		else
			AfxThrowNotSupportedException();
	}
	catch(hresult_exception &)
	{
		// general cleanup
		TRACE0("failed to embed/link an OLE object\n");
		return false;
	}
	this->SetFocus();
	return ok;
}

void CGMEView::MakeSureGUIDIsUniqueForSmartCopy( CComPtr<IMgaFCO>& fco)
{
	// this method prevents cloned objects having the same guid
	// as their original ones
	CComBSTR bstr;
	COMTHROW( fco->get_RegistryValue( CComBSTR( "guid"), &bstr));
	if( bstr == 0 || bstr == "") return; // no guid present, no need to replace it

	GUID t_guid = GUID_NULL;
	::CoCreateGuid(&t_guid);
		
	if (t_guid != GUID_NULL)
	{
		CString str_guid;
		str_guid.Format("{%08lX-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X}",
			t_guid.Data1, t_guid.Data2, t_guid.Data3,
			t_guid.Data4[0], t_guid.Data4[1], t_guid.Data4[2], t_guid.Data4[3],
			t_guid.Data4[4], t_guid.Data4[5], t_guid.Data4[6], t_guid.Data4[7]);
		
		// thus replace the old guid with a new one
		COMTHROW( fco->put_RegistryValue( CComBSTR( "guid"), CComBSTR(str_guid)));
	}

	// store the previous guid in prev subnode
	COMTHROW( fco->put_RegistryValue( CComBSTR( "guid/prev"), bstr));
}

bool CGMEView::DoPasteNative(COleDataObject *pDataObject,bool drag,bool move,bool reference,bool derive,bool instance,CGuiObject *ref,CPoint point)
{
	CGMEEventLogger::LogGMEEvent("CGMEView::DoPasteNative");
	if(drag)
		CGMEEventLogger::LogGMEEvent(" DRAG");
	if(move)
		CGMEEventLogger::LogGMEEvent(" MOVE");
	if(reference)
		CGMEEventLogger::LogGMEEvent(" REFERENCE");
	if(derive)
		CGMEEventLogger::LogGMEEvent(" DERIVE");
	if(instance)
		CGMEEventLogger::LogGMEEvent(" INSTANCE");
	CGMEEventLogger::LogGMEEvent(" in "+path+name+"\r\n");
	CComPtr<IDataObject> p = pDataObject->GetIDataObject(FALSE);
	CComPtr<IMgaDataSource> pt;
	COMTHROW(p.QueryInterface(&pt));

	CGMEDoc *doc = GetDocument();

	CComPtr<IUnknown> unk;

	CComPtr<IMgaRegNodes> regNodes;
	COMTHROW(pt->get_RegistryData(&unk));
	if (unk != NULL) {
		if (FAILED(unk.QueryInterface(&regNodes))) {
			regNodes = NULL;
		}
	}

	unk = NULL;
	COMTHROW(pt->get_Data(&unk));
	CComPtr<IMgaFCOs> fcos;
	CComPtr<IMgaMetaRole> metaRole;

	if(unk && SUCCEEDED(unk.QueryInterface(&fcos))) {			// not dragging from PartBrowser
		CComPtr<IMgaMetaAspect> aspect;
		currentAspect->GetMetaAspect(aspect);
		try {
			BeginTransaction();
//			if(currentAspect->CheckFcosBeforeInsertion(fcos) || reference) {
			{
				// Handle annotations
				CComPtr<IMgaRegNodes> newRegNodes;
				COMTHROW(newRegNodes.CoCreateInstance(OLESTR("Mga.MgaRegNodes")));
				PasteAnnotations(currentModel, regNodes, newRegNodes, (drag && move));

				long l;
				CComPtr<IMgaFCOs> interrfcos;
				COMTHROW(terry->OpenFCOs( fcos, &interrfcos));
				COMTHROW( interrfcos->get_Count( &l));

				CComPtr<IMgaFCOs> newFcos;
				if( l > 0)
				{
				if ((drag && move) || (!reference && !derive)) {
					CComPtr<IMgaMetaRoles> newRoles;
					COMTHROW(newRoles.CoCreateInstance(OLESTR("Mga.MgaMetaRoles")));
					MGACOLL_ITERATE(IMgaFCO, fcos) {
						CComPtr<IMgaFCO> fco;
						COMTHROW(terry->OpenFCO(MGACOLL_ITER, &fco));
						CComPtr<IMgaMetaRole> role;
						COMTHROW(fco->get_MetaRole(&role));
						CComPtr<IMgaMetaFCO> kind;
						COMTHROW(fco->get_Meta(&kind));
						CComPtr<IMgaMetaRole> newRole;

						COMTHROW(doc->resolver->get_RoleByMeta(currentModel,kind,OBJTYPE_NULL,role,aspect,&newRole));
						COMTHROW(newRoles->Append(newRole));
					}
					MGACOLL_ITERATE_END;

					if (drag && move) {
						COMTHROW(currentModel->MoveFCOs(fcos,newRoles,&newFcos));
					}
					else if(!reference && !derive) {
						COMTHROW(currentModel->CopyFCOs(fcos,newRoles,&newFcos));
					}

					if(!reference && !derive) // smart copy subtask:
					{
						MGACOLL_ITERATE(IMgaFCO, newFcos) {
							MakeSureGUIDIsUniqueForSmartCopy( CComPtr<IMgaFCO>(MGACOLL_ITER));
						}
						MGACOLL_ITERATE_END;
					}

					MGACOLL_ITERATE(IMgaFCO, newFcos) {
						CComPtr<IMgaFCO> newFco;
						newFco = MGACOLL_ITER;
						CComBSTR bstr;
						COMTHROW(newFco->get_ID(&bstr));
						CString newID;
						CopyTo(bstr,newID);
						newObjectIDs.AddHead(newID);
					}
					MGACOLL_ITERATE_END;
				}
				else if(derive) {

					COMTHROW(newFcos.CoCreateInstance(L"Mga.MgaFCOs"));

					/*CComPtr<IMgaMetaFCO> metaFco;
					COMTHROW(currentModel->get_Meta(&metaFco));
					CComPtr<IMgaMetaModel> metaModel;
					COMTHROW(metaFco.QueryInterface(&metaModel));*/ // commented by zolmol, these vars are NOT used
					bool normalExit = true;
					HRESULT hr = S_OK;
					MGACOLL_ITERATE(IMgaFCO,fcos) {
						CComPtr<IMgaFCO> fco;
						COMTHROW(terry->OpenFCO(MGACOLL_ITER, &fco));
						CComBSTR bstr;
						COMTHROW(fco->get_Name(&bstr));
						CString fcoName;
						CopyTo(bstr,fcoName);
/*
						CComPtr<IMgaModel> model;
						HRESULT hr;
						if((hr = fco.QueryInterface(&model)) != S_OK) {
							AfxMessageBox(fcoName + " is not a model. Only models can be derived!");
							AbortTransaction(hr);
							newObjectIDs.RemoveAll();
							return false;
						}
						{
							CComPtr<IMgaFCO> base;
							COMTHROW(fco->get_DerivedFrom(&base));
							if(base != 0) {
								AfxMessageBox(fcoName + " is not a root model type. Only root model types can be derived!");
								AbortTransaction(hr);
								newObjectIDs.RemoveAll();
								return false;
							}
						}
*/
						CComPtr<IMgaMetaFCO> kind;
						COMTHROW(fco->get_Meta(&kind));
						CComPtr<IMgaMetaRole> role;
						COMTHROW(fco->get_MetaRole(&role));
						CComPtr<IMgaMetaRole> newRole;
						COMTHROW(doc->resolver->get_RoleByMeta(currentModel,kind,OBJTYPE_NULL,role,aspect,&newRole));
						if(newRole == 0)
						{
							AfxMessageBox("Cannot insert object derived from " + fcoName);
							CGMEEventLogger::LogGMEEvent("    Cannot insert object derived from "+fcoName+"\r\n");
						}
						else {
							CComPtr<IMgaFCO> obj;
#pragma warning(disable: 4310) // cast truncates constant value
							VARIANT_BOOL inst = instance ? VARIANT_TRUE : VARIANT_FALSE;
#pragma warning(default: 4310) // cast truncates constant value
							if((hr = currentModel->DeriveChildObject(fco,newRole,inst,&obj)) != S_OK) {
								CString msg( (LPCTSTR) fcoName); msg += " cannot be derived! Some of its ancestors or descendants may be already derived!";
								if( hr == E_MGA_NOT_DERIVABLE)
								{
									if( !CGMEConsole::theInstance) AfxMessageBox( msg + " [Error code E_MGA_NOT_DERIVABLE]");
									else CGMEConsole::theInstance->Message( msg + " [Error code E_MGA_NOT_DERIVABLE]", MSG_ERROR);
								}
								else
									AfxMessageBox( msg);
								CGMEEventLogger::LogGMEEvent("    " + msg + " \r\n");
								normalExit = false;
								break;
							}

							newFcos->Append(obj);

							CComBSTR bstr;
							COMTHROW(obj->get_ID(&bstr));
							CString newID;
							CopyTo(bstr,newID);
							newObjectIDs.AddHead(newID);
						}
					}
					MGACOLL_ITERATE_END;
					if(!normalExit) {
						AbortTransaction(hr);
						newObjectIDs.RemoveAll();
						return false;
					}
				}
				else if(reference) {
					if(ref) {
						CGMEEventLogger::LogGMEEvent("    ref="+ref->GetName()+" "+ref->GetID()+"\r\n");
						CComPtr<IMgaReference> mgaRef;
						COMTHROW(ref->mgaFco.QueryInterface(&mgaRef));
						long count;
						COMTHROW(fcos->get_Count(&count));
						/* if(count != 1) {
							AfxMessageBox("Only a single object can be dropped on a reference for redirection!");
							throw hresult_exception(E_FAIL);
						} */
						if(count < 1) {
							AfxMessageBox("Cannot redirect reference to specified object!");
							CGMEEventLogger::LogGMEEvent("    Cannot redirect reference to specified object.\r\n");
							throw hresult_exception(E_FAIL);
						}
						CComPtr<IMgaFCO> fco;
						COMTHROW(fcos->get_Item(1,&fco));// index modified from 0 to 1 [zolmol]
						if(!IsEqualObject(fco,mgaRef)) {
							try {
								COMTHROW(mgaRef->put_Referred(fco));

								CComBSTR bstr;
								COMTHROW(mgaRef->get_ID(&bstr));
								CString newID;
								CopyTo(bstr,newID);
								newObjectIDs.AddHead(newID);
							}
							catch(hresult_exception e) {
								AbortTransaction(e.hr);
								CGMEEventLogger::LogGMEEvent( "    Cannot redirect reference to specified object.\r\n");
								const char* t1 = "Cannot redirect reference to specified object because of active connections!";
								const char* t2 = "Cannot redirect reference to specified object.";
								if( e.hr == E_MGA_REFPORTS_USED)
								{
									if( !CGMEConsole::theInstance) AfxMessageBox( t1);
									else CGMEConsole::theInstance->Message( t1, MSG_ERROR);
								}
								else
									if( CGMEConsole::theInstance) AfxMessageBox( t2);
									else CGMEConsole::theInstance->Message( t2, MSG_ERROR);

								return false;
							}
						}
					}
					else {
						COMTHROW(newFcos.CoCreateInstance(L"Mga.MgaFCOs"));
						/*CComPtr<IMgaMetaFCO> metaFco;
						COMTHROW(currentModel->get_Meta(&metaFco));
						CComPtr<IMgaMetaModel> metaModel;
						COMTHROW(metaFco.QueryInterface(&metaModel));*/ // commented by zolmol, these vars are NOT used
						MGACOLL_ITERATE(IMgaFCO,fcos) {
							CComPtr<IMgaFCO> fco;
							COMTHROW(terry->OpenFCO(MGACOLL_ITER, &fco));
							CComPtr<IMgaConnection> conn;
							if(fco.QueryInterface(&conn) != S_OK) { // skip connections, they cannot be referenced
								CComPtr<IMgaMetaRole> role;
#pragma warning(disable: 4310) // cast truncates constant value
								COMTHROW(doc->resolver->put_IsStickyEnabled(::GetKeyState(VK_SHIFT) < 0 ? VARIANT_FALSE :VARIANT_TRUE));
#pragma warning(default: 4310) // cast truncates constant value
								COMTHROW(doc->resolver->get_RefRoleByMeta(currentModel,aspect,fco,&role));
								if(role == 0)
								{
									AfxMessageBox("Cannot create reference");
									CGMEEventLogger::LogGMEEvent("    Cannot create reference.\r\n");
								}
								else {
									CComPtr<IMgaFCO> ref;
									COMTHROW(currentModel->CreateReference(role,fco,&ref));
									newFcos->Append(ref);

									CComBSTR bstr;
									COMTHROW(ref->get_ID(&bstr));
									CString newID;
									CopyTo(bstr,newID);
									newObjectIDs.AddHead(newID);

									CComBSTR nmb;
									COMTHROW(fco->get_Name(&nmb));
									// After Larry's wishes
									/* CString nm;
									CopyTo(nmb,nm);
									nm += "Ref";
									CopyTo(nm,nmb); */
									COMTHROW(ref->put_Name(nmb));
								}
							}
						}
						MGACOLL_ITERATE_END;
					}
				}
				else
					VERIFY(false);	// shouldn't be here!
				} // endif l > 0

				if(drag && !ref) {
					CGuiObjectList newObjs;
					CGuiFcoList newGuiFcos;
					CGuiConnectionList newConnections;
					CGuiAnnotatorList newAnns;
					if( newFcos) CreateGuiObjects(newFcos,newGuiFcos,newConnections);
					POSITION fpos = newGuiFcos.GetHeadPosition();
					while (fpos) {
						CGuiObject * fgobj = dynamic_cast<CGuiObject*>(newGuiFcos.GetNext(fpos));
						if (fgobj) {
							newObjs.AddTail(fgobj);
						}
					}
					CreateAnnotators(newRegNodes, newAnns);

					int left = 0, top = 0, leftA = 0, topA = 0;
					bool valid = false, validA = false;
					if (newObjs.GetCount() > 0) {
						CGuiObject::FindUpperLeft(newObjs, left, top);
						valid = true;
					}
					if (newAnns.GetCount() > 0) {
						CGuiAnnotator::FindUpperLeft(newAnns, leftA, topA);
						validA = true;
					}
					if (valid && validA) {
						left = min(left, leftA);
						top = min(top, topA);
					}
					else if (validA) {
						left = leftA;
						top = topA;
					}
					else if (!valid) {
						ASSERT(("There is no object to move", false));
					}
					CPoint diff = point - CPoint(left,top);
					CGuiObject::ShiftModels(newObjs, diff);
					CGuiAnnotator::ShiftAnnotations(newAnns,diff);


					// CGuiAnnotatorList newAnns;
					// CreateGuiAnnotations(newAnns, );
					CGuiObject::MoveObjects(newObjs,point);

					// We don't need this, since reset
					// children.AddTail(&newGuiFcos);
					// annotators.AddTail(&newAnns);
					// Instead:

					POSITION dpos = newGuiFcos.GetHeadPosition();
					while(dpos) {
						delete newGuiFcos.GetNext(dpos);
					}

					dpos = newAnns.GetHeadPosition();
					while(dpos) {
						delete newAnns.GetNext(dpos);
					}



				}
				Invalidate(true);
				AutoRoute();
				CommitTransaction();
				ResetParent();
				ChangeAttrPrefObjs(selected);
				return true;
			}
	/*
			else {
				CommitTransaction();
				AfxMessageBox("Objects cannot be inserted!");
			}
	*/
		}
		catch(hresult_exception e) {
			AbortTransaction(e.hr);
//			AfxMessageBox("Unable to insert objects",MB_ICONSTOP | MB_OK);	// in most cases there was an error msg already...
			newObjectIDs.RemoveAll();
		}
		return false;
	}
	else if(unk && SUCCEEDED(unk.QueryInterface(&metaRole))) {			// dragging from PartBrowser
		try {
			BeginTransaction();
			bool ok = false;
			if(!CGuiFco::IsPrimary(guiMeta,currentAspect,metaRole)) {
				if(currentAspect->IsPrimaryByRoleName(metaRole)) {
					CComBSTR nm;
					COMTHROW(metaRole->get_Name(&nm));
					CString roleName;
					CopyTo(nm,roleName);
					metaRole = 0;
					if(currentAspect->GetRoleByName(roleName,metaRole))
						ok = true;
				}
			}
			else
				ok = true;
			if(ok) {
				CComPtr<IMgaFCO> child;
				COMTHROW(currentModel->CreateChildObject(metaRole,&child));
				CComBSTR nm;
				COMTHROW(metaRole->get_DisplayedName(&nm));
				COMTHROW(child->put_Name(nm));
				CComBSTR bstr;
				COMTHROW(child->get_ID(&bstr));
				CString newID;
				CopyTo(bstr,newID);
				newObjectIDs.AddHead(newID);

				SetObjectLocation(child,metaRole,point);

//				Invalidate(true);
//				AutoRoute();
				CommitTransaction();
				ChangeAttrPrefObjs(selected);
//				ResetParent();
			}
			else {
				CommitTransaction();
				AfxMessageBox("Paradigm violation: cannot insert new part!");
				CGMEEventLogger::LogGMEEvent("    Paradigm violation: cannot insert new part.\r\n");
				return false;
			}
		}
		catch(hresult_exception e) {
			AbortTransaction(e.hr);
			AfxMessageBox("Unable to insert objects",MB_ICONSTOP | MB_OK);
			CGMEEventLogger::LogGMEEvent("    Unable to insert objects.\r\n");
			newObjectIDs.RemoveAll();
            Reset(true); //BGY
			return false;
		}
	}
	return true;
}

void CGMEView::PasteAnnotations(CComPtr<IMgaModel> &targetModel, CComPtr<IMgaRegNodes> &regNodes, CComPtr<IMgaRegNodes> &newRegNodes, bool isMove)
{
	if (regNodes == NULL) {
		return;
	}
	MGACOLL_ITERATE(IMgaRegNode,regNodes) {
		CComPtr<IMgaRegNode> regNode;
		regNode = MGACOLL_ITER;

		CComBSTR nodePath;
		COMTHROW(regNode->get_Path(&nodePath));

		bool collision = true;
		while (collision) {
			CComPtr<IMgaRegNode> exRegNode;
			COMTHROW(targetModel->get_RegistryNode(nodePath, &exRegNode));
			long status;
			COMTHROW(exRegNode->get_Status(&status));
			if (status == ATTSTATUS_UNDEFINED) {
				collision = false;
			}
			else {
				nodePath.Append("Copy");
			}
		}

		CComPtr<IMgaRegNode> newNode;
		COMTHROW(targetModel->get_RegistryNode(nodePath, &newNode));
		COMTHROW(newRegNodes->Append(newNode));

		CopyRegTree(regNode, newNode);

		if (isMove) {
			COMTHROW(regNode->RemoveTree());
		}

		// Let's make it visible in all aspects
		CComPtr<IMgaRegNode> newAspRoot;
		CComBSTR aspRootName(AN_ASPECTS);
		COMTHROW(newNode->get_SubNodeByName(aspRootName, &newAspRoot));
		CComPtr<IMgaRegNodes> aspNodes;
		COMTHROW(newAspRoot->get_SubNodes(VARIANT_FALSE, &aspNodes));
		MGACOLL_ITERATE(IMgaRegNode,aspNodes) {
			CComPtr<IMgaRegNode> aspNode;
			aspNode = MGACOLL_ITER;
			COMTHROW(aspNode->RemoveTree());
		}
		MGACOLL_ITERATE_END;

		CComBSTR defAspName(AN_DEFASPECT);
		CComPtr<IMgaRegNode> defAspNode;
		COMTHROW(newAspRoot->get_SubNodeByName(defAspName, &defAspNode));
		CComBSTR defAspVal(AN_VISIBLE_DEFAULT);
		COMTHROW(defAspNode->put_Value(defAspVal));
	}
	MGACOLL_ITERATE_END;
}

void CGMEView::CopyRegTree(CComPtr<IMgaRegNode> &regNode, CComPtr<IMgaRegNode> &newNode)
{
	CComBSTR nodeValue;
	COMTHROW(regNode->get_Value(&nodeValue));
	COMTHROW(newNode->put_Value(nodeValue));

	CComPtr<IMgaRegNodes> subRegNodes;
	COMTHROW(regNode->get_SubNodes(VARIANT_FALSE, &subRegNodes));
	MGACOLL_ITERATE(IMgaRegNode,subRegNodes) {
		CComPtr<IMgaRegNode> subRegNode;
		subRegNode = MGACOLL_ITER;
		CComBSTR subName;
		COMTHROW(subRegNode->get_Name(&subName));
		CComPtr<IMgaRegNode> newSubNode;
		COMTHROW(newNode->get_SubNodeByName(subName, &newSubNode));
		CopyRegTree(subRegNode, newSubNode);
	}
	MGACOLL_ITERATE_END;
}

void CGMEView::FillModelGrid()
{
	BeginWaitCursor();
	modelGrid.SetSource(this);
	CGuiObject *obj;
	POSITION pos = children.GetHeadPosition();
	while(pos) {
		obj = dynamic_cast<CGuiObject *>(children.GetNext(pos));
		if(!obj || !obj->IsVisible())
			continue;
		CPoint pt = obj->GetLocation().CenterPoint();
		if(!modelGrid.IsAvailable(obj)) {
			if(!modelGrid.GetClosestAvailable(obj,pt)) {
				AfxMessageBox("Too Many Models! Internal Program Error!",MB_OK | MB_ICONSTOP);
				EndWaitCursor();
				return;
			}
			// obj->SetCenter(pt);
			CPendingObjectPosRequest *req = new CPendingObjectPosRequest(obj, pt, obj->GetLocation(), obj->GetParentAspect());
			pendingRequests.AddHead(req);

			obj->SetCenter(pt, -1, false);
		}
		modelGrid.Set(obj);
	}
	EndWaitCursor();
}

void CGMEView::SetObjectLocation(CComPtr<IMgaFCO> &child,CComPtr<IMgaMetaRole> &mmRole,CPoint pt)
{
	CRect loc = CRect(0,0,25,25);
	::SetLocation(loc,pt);

	// CPoint npt = loc.CenterPoint();
	// if(!modelGrid.IsAvailable(loc)) {
	// 	if(!modelGrid.GetClosestAvailable(loc.Size(),npt)) {
	//		AfxMessageBox("Too Many Models! Internal Program Error!",MB_OK | MB_ICONSTOP);
	//		EndWaitCursor();
	//		return;
	//	}
	// }

		try {
		CComPtr<IMgaMetaParts> mmParts;
		CComPtr<IMgaMetaPart> mmPart;
		COMTHROW(mmRole->get_Parts(&mmParts));
		MGACOLL_ITERATE(IMgaMetaPart,mmParts) {
			mmPart = MGACOLL_ITER;
			CComPtr<IMgaMetaAspect> mmAspect;
			COMTHROW(mmPart->get_ParentAspect(&mmAspect));
			CComPtr<IMgaPart> part;
			COMTHROW(child->get_Part(mmAspect,&part));
			COMTHROW(part->SetGmeAttrs(0,loc.TopLeft().x,loc.TopLeft().y));
			// COMTHROW(part->SetGmeAttrs(0,npt.x,npt.y));
		}
		MGACOLL_ITERATE_END;
	}
	catch(hresult_exception &e) {
		throw hresult_exception(e.hr);
	}
}

void CGMEView::GetRefereeChain(IMgaFCOs *refChain, IMgaFCO* fco)
{
	CComQIPtr<IMgaReference> ref(fco);
	if(ref) {
		// Avoid circular references
		long res;
		if ((refChain->Find(ref, 1L, &res)) == E_NOTFOUND) {
			refChain->Append(ref);
			CComPtr<IMgaFCO> refFco;
			COMTHROW(ref->get_Referred(&refFco));
			GetRefereeChain(refChain,refFco);
		}
	}
}

bool CGMEView::Connect(CGuiObject *src,CGuiPort *srcPort, int srcHotSide, CGuiObject *dst,CGuiPort *dstPort, int dstHotSide, bool nosticky)
{
	CGMEEventLogger::LogGMEEvent("CGMEView::Connect src="+src->GetName()+" "+src->GetID()+",dst="+dst->GetName()+" "+dst->GetID()+" in "+path+name+"\r\n");
	bool ret = false;
	CGMEDoc *doc = GetDocument();
	try {
		BeginTransaction();

		CComPtr<IMgaMetaRole> role;
		CComPtr<IMgaMetaAspect> aspect;
		currentAspect->GetMetaAspect(aspect);

		if (srcPort) {
			srcPort = srcPort->IsRealPort() ? srcPort : NULL;
			if (srcPort) CGMEEventLogger::LogGMEEvent("    srcPort="+srcPort->GetName()+" "+srcPort->GetID()+"\r\n");
		}
		if (dstPort) {
			dstPort = dstPort->IsRealPort() ? dstPort : NULL;
			if (dstPort) CGMEEventLogger::LogGMEEvent("    dstPort="+dstPort->GetName()+" "+dstPort->GetID()+"\r\n");
		}
#pragma warning(disable: 4310) // cast truncates constant value
		COMTHROW(doc->resolver->put_IsStickyEnabled(nosticky ? VARIANT_FALSE :VARIANT_TRUE));
#pragma warning(default: 4310) // cast truncates constant value
		COMTHROW(doc->resolver->get_ConnRoleByMeta(	currentModel,
													aspect,
													src->mgaFco,
													srcPort ? srcPort->mgaFco : NULL,
													dst->mgaFco,
													dstPort ? dstPort->mgaFco : NULL,
													&role));
		CComPtr<IMgaFCO> conn;
		if(role != 0) {
			CComObjPtr<IMgaFCOs> srcRefs, dstRefs;
			COMTHROW(srcRefs.CoCreateInstance(L"Mga.MgaFCOs"));
			COMTHROW(dstRefs.CoCreateInstance(L"Mga.MgaFCOs"));

// Bakay hack: avoid setting up refchains for atomrefs.
			if(srcPort) GetRefereeChain(srcRefs,src->mgaFco);
//			GetRefereeChain(srcRefs,src->mgaFco);
			if(dstPort) GetRefereeChain(dstRefs,dst->mgaFco);
//			GetRefereeChain(dstRefs,dst->mgaFco);

/*
// Bakay hack
// Atom references must pass the referenced atom as src and dst
			CComQIPtr<IMgaReference> refp;
			while((refp = src->mgaFco) != NULL) {
				src->mgaFco = NULL;
				COMTHROW(refp->get_Referred(&src->mgaFco));
			}
			while((refp = dst->mgaFco) != NULL) {
				dst->mgaFco = NULL;
				COMTHROW(refp->get_Referred(&dst->mgaFco));
			}
// Bakay hack ends
*/
			COMTHROW(currentModel->CreateSimpleConn(
				role,
				srcPort ? srcPort->mgaFco : src->mgaFco,
				dstPort ? dstPort->mgaFco : dst->mgaFco,
				srcRefs,
				dstRefs,
				&conn));
			CComBSTR nm;
			COMTHROW(role->get_DisplayedName(&nm));
			COMTHROW(conn->put_Name(nm));

			// Setup autorouter prefs
			CString routerPrefStr;
			switch (srcHotSide) {
			case GME_NORTH:
				routerPrefStr = "N";
				break;
			case GME_SOUTH:
				routerPrefStr = "S";
				break;
			case GME_WEST:
				routerPrefStr = "W";
				break;
			case GME_EAST:
				routerPrefStr = "E";
				break;
			}
			switch (dstHotSide) {
			case GME_NORTH:
				routerPrefStr += "n";
				break;
			case GME_SOUTH:
				routerPrefStr += "s";
				break;
			case GME_WEST:
				routerPrefStr += "w";
				break;
			case GME_EAST:
				routerPrefStr += "e";
				break;
			}
			if (!routerPrefStr.IsEmpty()) {
				CComBSTR	bstrPath(AUTOROUTER_PREF);
				CComBSTR	bstrVal(routerPrefStr);
				COMTHROW(conn->put_RegistryValue(bstrPath,bstrVal));
			}

			ret = true;
			CommitTransaction();
		}
		else {
			CommitTransaction();
			CGMEEventLogger::LogGMEEvent("    Paradigm violation: cannot connect selected objects!\r\n");
			AfxMessageBox("Paradigm violation: cannot connect selected objects!",MB_ICONSTOP | MB_OK);
		}
	}
	catch(hresult_exception &e) {
		CGMEEventLogger::LogGMEEvent("    Cannot Connect, hresult_exception in CGMEView::Connect\r\n");
		AbortTransaction(e.hr);
//		AfxMessageBox("Unable to connect specified parts!",MB_ICONSTOP | MB_OK);
        Reset(true); // BGY: something similar needed, otherwise the created conenction not 
        // deleted form the gui if the committransaction failed
		ret = false;
	}
	// error messages output to the console window
	// or simple refreshing of ActiveBrowser might leave
	// the focus set to another window, thus making the
	// connectmode cursor switch back to the normal one
	this->SetFocus();
	return ret;
}

void CGMEView::ResolveConnections()
{
	POSITION pos = connections.GetHeadPosition();
	while(pos)
		connections.GetNext(pos)->Resolve();
}

void CGMEView::InsertNewPart(CString roleName,CPoint pt)
{
	CGMEEventLogger::LogGMEEvent("CGMEView::InsertNewPart("+roleName+") in "+path+name+"\r\n");
	CComPtr<IMgaFCO> child;
	CComPtr<IMgaMetaRole> role;
	try {
		BeginTransaction();
		if(!currentAspect->GetRoleByName(roleName,role,true)) {
			AfxMessageBox("Internal Program Error in CGMEView::InsertNewPart");
			CGMEEventLogger::LogGMEEvent("    Internaml Program Error in CGMEView::InsertNewPart.\r\n");
			return;
		}
		COMTHROW(currentModel->CreateChildObject(role,&child));
		CComBSTR nm;
		COMTHROW(role->get_DisplayedName(&nm));
		COMTHROW(child->put_Name(nm));

		CComBSTR bstr;
		COMTHROW(child->get_ID(&bstr));
		CString newID;
		CopyTo(bstr,newID);
		newObjectIDs.AddHead(newID);

		SetObjectLocation(child,role,pt);
		CommitTransaction();
	}
	catch(hresult_exception &e) {
		AbortTransaction(e.hr);
		newObjectIDs.RemoveAll();
		AfxMessageBox("Unable to insert new part",MB_ICONSTOP | MB_OK);
		CGMEEventLogger::LogGMEEvent("    Unable to insert new part.\r\n");
		return;
	}
	ChangeAttrPrefObjs(selected);
	try {
		BeginTransaction(TRANSACTION_READ_ONLY);
		if(currentAspect->IsLinkedRole(role) && parent != 0)
			ResetParent();
		CommitTransaction();
	}
	catch(hresult_exception &e) {
		AbortTransaction(e.hr);
		AfxMessageBox("Unable to update parent",MB_ICONSTOP | MB_OK);
		CGMEEventLogger::LogGMEEvent("    Unable to update parent.\r\n");
	}
	Invalidate(true);
}

void CGMEView::ChangeAspect(CString aspName, bool p_eraseStack /*=true*/)
{
	CGMEEventLogger::LogGMEEvent("CGMEView::ChangeAspect("+aspName+") in "+path+name+"\r\n");
	if(currentAspect->name != aspName) {
		CGuiMetaAspect *newAsp = guiMeta->FindAspect(aspName);
		if(newAsp) {
			currentAspect = newAsp;
			SetAspectProperty(currentAspect->index);
			CGuiAnnotator::SetAspect(annotators, currentAspect->index);

			if( theApp.isHistoryEnabled())
			{
				if( m_isActive) // only the active view's changeaspect event is recorded
				{
					GetDocument()->tellHistorian( currentModel, currentAspect?currentAspect->name:"");
				}

				if( p_eraseStack)
				{
					GetDocument()->clearForwHistory();
				}
			}
			CGuiFco::SetAspect(children,currentAspect->index);
			ResolveConnections();

			currentSet = 0;
			if(GetDocument()->GetEditMode() == GME_SET_MODE) {
				CGuiAnnotator::GrayOutAnnotations(annotators,false);
				CGuiFco::GrayOutFcos(children,false);
				CGuiFco::GrayOutFcos(connections,false);
			}

			modelGrid.Clear();
			FillModelGrid();
			AutoRoute(); // HACK we may have size change here, reroute the whole thing for now
			this->SendUnselEvent4List( &selected);
			selected.RemoveAll();
			RemoveAllAnnotationFromSelection();
			ClearConnectionSelection();

//			CGMEView* gmeviewA = (CGMEView*)GetActiveView();
//			if (gmeviewA)
			if (m_isActive)
			{
				TRACE("CGMEView::ChangeAspect activeView\n");
				/*gmeviewA->*/m_refreshpannwin = true; 
			}
			Invalidate();
		}
	}
}

void CGMEView::ChangeAspect(int ind)
{
	CGuiMetaAspect *am = guiMeta->FindAspect(ind);
	VERIFY(am);
	ChangeAspect(am->name);
}

CString &CGMEView::GetAspectName(int ind)
{
	CGuiMetaAspect *am = guiMeta->FindAspect(ind);
	VERIFY(am);
	return am->name;
}

CGMEView *CGMEView::GetActiveView()
{
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
//	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetMainWnd( );
	if (!pFrame)
	{
		return NULL;
	}
	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
//	BOOL ismax = FALSE;
//	CMDIChildWnd *pChild = pFrame->MDIGetActive(&ismax);
	if (!pChild)
	{
		return NULL;
	}
	return ((CGMEView *)(pChild->GetActiveView()));
}

/////////////////////////////////////////////////////////////////////////////
// CGMEView message handlers

BOOL CGMEView::OnEraseBkgnd(CDC* pDC)
{
	if (!pDC->IsPrinting() && !IsPreview()) {
		OnPrepareDC(offScreen);
		CRect r;
		GetClientRect(&r);
		offScreen->DPtoLP(&r);
		r.InflateRect(5, 5);
		offScreen->FillSolidRect(&r,bgColor);
	}

	return TRUE;

//	return CScrollZoomView::OnEraseBkgnd(pDC);
}

BOOL CGMEView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (isCursorChangedByDecorator)
		return TRUE;

	if( GetFocus() != this )
		SetCursor(editCursor);
	else {
		CGMEDoc *pDoc = GetDocument();
		switch(pDoc->GetEditMode()) {
		case GME_AUTOCONNECT_MODE:
		case GME_SHORTAUTOCONNECT_MODE:
			SetCursor(connSrc ? autoconnect2Cursor : autoconnectCursor);
			break;
		case GME_DISCONNECT_MODE:
		case GME_SHORTDISCONNECT_MODE:
			SetCursor(connSrc ? disconnect2Cursor : disconnectCursor);
			break;
		case GME_SET_MODE:
			SetCursor(currentSet ? set2Cursor : setCursor);
			break;
		case GME_ZOOM_MODE:
			SetCursor(zoomCursor);
			break;
		case GME_VISUAL_MODE:
			SetCursor(visualCursor);
			break;
		default:
			SetCursor(tmpConnectMode ? autoconnect2Cursor : editCursor);
			break;
		}
	}

	ShowCursor(TRUE);
	return TRUE;
}

void CGMEView::OnDropFiles(HDROP p_hDropInfo)
{
	CPoint point;
	DragQueryPoint(p_hDropInfo, &point);
	CoordinateTransfer(point);

	CGuiObject* selection = FindObject(point);
	HRESULT retVal = S_OK;
	if (selection != NULL) {
		CGuiAspect* pAspect = selection->GetCurrentAspect();
		if (pAspect != NULL) {
			CComQIPtr<IMgaNewDecorator> newDecorator(pAspect->GetDecorator());
			if (newDecorator) {
				CClientDC transformDC(this);
				OnPrepareDC(&transformDC);
				retVal = newDecorator->DropFile((ULONGLONG)p_hDropInfo, point.x, point.y, (ULONGLONG)transformDC.m_hDC);
			}
		}
	}
	if (retVal == S_DECORATOR_EVENT_HANDLED)
		return;

	CMainFrame::theInstance->OnDropFiles(p_hDropInfo);
}

void CGMEView::OnKillfocusNameProp()
{
	if(!initDone)
		return;
	CString txt;
	GetNameProperty(txt);
	if(txt != name) {
		if(currentModel != 0) {
			try {
				BeginTransaction();
				CComBSTR bstr;
				CopyTo(txt,bstr);
				COMTHROW(currentModel->put_Name(bstr));
				CommitTransaction();
				RetrievePath();
				name = txt;
				frame->title = name + " - " + path;
				frame->OnUpdateFrameTitle(true);
			}
			catch(hresult_exception &e) {
				AbortTransaction(e.hr);
				AfxMessageBox("Unable to set model name");
				SetNameProperty();
			}
		}
	}
}

void CGMEView::OnSelChangeAspectProp()
{
	int ind = GetAspectProperty();
	CGuiMetaAspect *am = guiMeta->FindAspect(ind);
	VERIFY(am);
	CString aspName = am->name;
	if(currentAspect->name != aspName) 
	{
		currentAspect = guiMeta->FindAspect(aspName);
		CMainFrame::theInstance->ChangePartBrowserAspect(currentAspect->index);
		CGuiAnnotator::SetAspect(annotators, currentAspect->index);
		CGuiFco::SetAspect(children,currentAspect->index);
		ResolveConnections();
		if( theApp.isHistoryEnabled())
		{
			GetDocument()->tellHistorian( currentModel, currentAspect?currentAspect->name:"");
			GetDocument()->clearForwHistory();
		}

		currentSet = 0;
		if(GetDocument()->GetEditMode() == GME_SET_MODE) {
			CGuiAnnotator::GrayOutAnnotations(annotators,false);
			CGuiFco::GrayOutFcos(children,false);
			CGuiFco::GrayOutFcos(connections,false);
		}

		modelGrid.Clear();
		FillModelGrid();
		AutoRoute(); // HACK we may have size change here, reroute the whole thing for now
		this->SendUnselEvent4List( &selected);
		selected.RemoveAll();
		RemoveAllAnnotationFromSelection();
		ClearConnectionSelection();

		TRACE("CGMEView::OnSelChangeAspectProp\n");
		m_refreshpannwin = true;
		Invalidate();
	}
}

bool CGMEView::ChangePrnAspect(CString aspName)
{
	CGMEEventLogger::LogGMEEvent("CGMEView::ChangePrnAspect("+aspName+") in "+path+name+"\r\n");
	if(currentAspect->name == aspName)
		return true;
	CGuiMetaAspect *newAsp = guiMeta->FindAspect(aspName);
	if(!newAsp) 
		return false;
	currentAspect = newAsp;
	SetAspectProperty(currentAspect->index);
	CGuiAnnotator::SetAspect(annotators, currentAspect->index);
	CGuiFco::SetAspect(children,currentAspect->index);
	ResolveConnections();

	modelGrid.Clear();
	FillModelGrid();
	AutoRoute(); // HACK we may have size change here, reroute the whole thing for now
	this->SendUnselEvent4List( &selected);
	selected.RemoveAll();
	RemoveAllAnnotationFromSelection();
	ClearConnectionSelection();
	return true;
}

void CGMEView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnLButtonUp in " + path + name + "\r\n");

	CPoint ppoint = point;
	if (!tmpConnectMode) {
		CPoint trackPoint = point;
		CoordinateTransfer(point);

		CGMEDoc* doc = GetDocument();
		switch(doc->GetEditMode()) {
		case GME_EDIT_MODE:
			{
				CGMEEventLogger::LogGMEEvent("    mode=GME_EDIT_MODE\r\n");

				CGMEView* self = const_cast<CGMEView*> (this);
				CGuiObject*	object	= self		? self->FindObject(point, true) : 0;
//				CGuiPort*	port	= object	? object->FindPort(point, true) : 0;

				if (inNewDecoratorOperation) {
					CComPtr<IMgaNewDecorator> newDecorator;
					if (decoratorOrAnnotator) {
						ASSERT(objectInDecoratorOperation != NULL);
						CGuiAspect* pAspect = objectInDecoratorOperation->GetCurrentAspect();
						if (pAspect != NULL) {
							CComQIPtr<IMgaNewDecorator> newDecorator2(pAspect->GetDecorator());
							newDecorator = newDecorator2;
						}
					} else {
						ASSERT(annotatorInDecoratorOperation != NULL);
						newDecorator = annotatorInDecoratorOperation->GetNewDecorator(currentAspect->index);
					}
					if (newDecorator) {
						CClientDC transformDC(this);
						OnPrepareDC(&transformDC);
						HRESULT retVal = newDecorator->MouseLeftButtonUp(nFlags, point.x, point.y, (ULONGLONG)transformDC.m_hDC);
						if (retVal == S_DECORATOR_EVENT_HANDLED) {
							if (inOpenedDecoratorTransaction) {
								if (shouldCommitOperation) {
									CommitTransaction();
									shouldCommitOperation = false;
									objectInDecoratorOperation = NULL;
									annotatorInDecoratorOperation = NULL;
								} else {
									AbortTransaction(S_OK);
								}
								inOpenedDecoratorTransaction = false;
								isContextInitiatedOperation = false;
							}
							break;
						} else if (retVal != S_OK &&
								   retVal != S_DECORATOR_EVENT_NOT_HANDLED &&
								   retVal != E_DECORATOR_NOT_IMPLEMENTED)
						{
							CancelDecoratorOperation();
							COMTHROW(retVal);
						}
					}
				} else {
					CGuiAnnotator* annotation = NULL;
					CComPtr<IMgaNewDecorator> newDecorator;
					if (object != NULL) {
						CGuiAspect* pAspect = object->GetCurrentAspect();
						if (pAspect != NULL) {
							CComQIPtr<IMgaNewDecorator> newDecorator2(pAspect->GetDecorator());
							newDecorator = newDecorator2;
						}
					} else {
						annotation = FindAnnotation(point);
						if (annotation)
							newDecorator = annotation->GetNewDecorator(currentAspect->index);
					}
					if (newDecorator) {
						CClientDC transformDC(this);
						OnPrepareDC(&transformDC);
						HRESULT retVal = newDecorator->MouseLeftButtonUp(nFlags, point.x, point.y, (ULONGLONG)transformDC.m_hDC);
						if (retVal != S_OK &&
							retVal != S_DECORATOR_EVENT_HANDLED &&
							retVal != S_DECORATOR_EVENT_NOT_HANDLED &&
							retVal != E_DECORATOR_NOT_IMPLEMENTED)
						{
							CancelDecoratorOperation();
							COMTHROW(retVal);
						}
						if (inNewDecoratorOperation) {
							if (decoratorOrAnnotator)
								objectInDecoratorOperation = object;
							else
								annotatorInDecoratorOperation = annotation;
						}
					}
				}
			}	//case
		}	// switch
	}	// if (!tmpConnectMode)
	CScrollZoomView::OnLButtonUp(nFlags, ppoint);
}

void CGMEView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnLButtonDown in "+path+name+"\r\n");
	if (!(nFlags & MK_LBUTTON)) {
		// PETER: this was needed to discard "got focus" situations: eg.: add-on dialog appears during attribute editing
		return;
	}

	CPoint trackPoint = point;
	CPoint ppoint = point;
	CoordinateTransfer(point);

	if(tmpConnectMode) {
		if(connTmp && (connSrc != 0)) {
			Connect(connSrc, connSrcPort, connSrcHotSide, connTmp, connTmpPort, connTmpHotSide, 0 != (nFlags & MK_SHIFT));
			ClearConnSpecs();
		}
		tmpConnectMode = false;
		SetCursor(editCursor);
		ShowCursor(TRUE);
	}
	else {
		CGMEDoc *doc = GetDocument();
		switch(doc->GetEditMode()) {
		case GME_EDIT_MODE:
			{
				CGMEEventLogger::LogGMEEvent("    mode=GME_EDIT_MODE\r\n");

				CGMEView* self = const_cast<CGMEView*> (this);
				CGuiObject*	object	= self		? self->FindObject(point, true) : 0;
//				CGuiPort*	port	= object	? object->FindPort(point, true) : 0;
				if (object == NULL)
					object = self ? self->FindObject(point, true, true) : 0;

				if (isContextInitiatedOperation || inNewDecoratorOperation) {
					if (isContextInitiatedOperation) {
						if (::GetCapture() != NULL)
							::ReleaseCapture();
						inNewDecoratorOperation = true;
						CScrollZoomView::OnLButtonDown(nFlags, ppoint);
						return;
					}
					CComPtr<IMgaNewDecorator> newDecorator;
					if (decoratorOrAnnotator) {
						ASSERT(objectInDecoratorOperation != NULL);
						CGuiAspect* pAspect = objectInDecoratorOperation->GetCurrentAspect();
						if (pAspect != NULL) {
							CComQIPtr<IMgaNewDecorator> newDecorator2(pAspect->GetDecorator());
							newDecorator = newDecorator2;
						}
					} else {
						ASSERT(annotatorInDecoratorOperation != NULL);
						newDecorator = annotatorInDecoratorOperation->GetNewDecorator(currentAspect->index);
					}
					if (newDecorator) {
						CClientDC transformDC(this);
						OnPrepareDC(&transformDC);
						HRESULT retVal = newDecorator->MouseLeftButtonDown(nFlags, point.x, point.y, (ULONGLONG)transformDC.m_hDC);
						if (retVal == S_DECORATOR_EVENT_HANDLED) {
							if (inOpenedDecoratorTransaction) {
								if (shouldCommitOperation) {
									CommitTransaction();
									shouldCommitOperation = false;
									objectInDecoratorOperation = NULL;
									annotatorInDecoratorOperation = NULL;
								} else {
									AbortTransaction(S_OK);
								}
								inOpenedDecoratorTransaction = false;
								isContextInitiatedOperation = false;
							}
						} else if (retVal != S_OK &&
								   retVal != S_DECORATOR_EVENT_NOT_HANDLED &&
								   retVal != E_DECORATOR_NOT_IMPLEMENTED)
						{
							CancelDecoratorOperation();
							COMTHROW(retVal);
						}
						CScrollZoomView::OnLButtonDown(nFlags, ppoint);
						return;
					}
				} else {
					CGuiAnnotator* annotation = NULL;
					CComPtr<IMgaNewDecorator> newDecorator;
					if (object != NULL) {
						CGuiAspect* pAspect = object->GetCurrentAspect();
						if (pAspect != NULL) {
							CComQIPtr<IMgaNewDecorator> newDecorator2(pAspect->GetDecorator());
							newDecorator = newDecorator2;
						}
					} else {
						annotation = FindAnnotation(point);
						if (annotation)
							newDecorator = annotation->GetNewDecorator(currentAspect->index);
					}
					if (newDecorator) {
						CClientDC transformDC(this);
						OnPrepareDC(&transformDC);
						HRESULT retVal = newDecorator->MouseLeftButtonDown(nFlags, point.x, point.y, (ULONGLONG)transformDC.m_hDC);
						if (retVal == S_DECORATOR_EVENT_HANDLED) {
							if (inOpenedDecoratorTransaction) {
								if (shouldCommitOperation) {
									CommitTransaction();
									shouldCommitOperation = false;
									objectInDecoratorOperation = NULL;
									annotatorInDecoratorOperation = NULL;
									inOpenedDecoratorTransaction = false;
									isContextInitiatedOperation = false;
									CScrollZoomView::OnLButtonDown(nFlags, ppoint);
									return;
								} else if (!inNewDecoratorOperation) {
									AbortTransaction(S_OK);
									inOpenedDecoratorTransaction = false;
									isContextInitiatedOperation = false;
									CScrollZoomView::OnLButtonDown(nFlags, ppoint);
									return;
								} else {
									if (::GetCapture() != NULL)
										::ReleaseCapture();
								}
							} else {
								if (inNewDecoratorOperation) {
									if (decoratorOrAnnotator)
										objectInDecoratorOperation = object;
									else
										annotatorInDecoratorOperation = annotation;
								}
								CScrollZoomView::OnLButtonDown(nFlags, ppoint);
								return;
							}
						} else if (retVal != S_OK &&
								   retVal != S_DECORATOR_EVENT_NOT_HANDLED &&
								   retVal != E_DECORATOR_NOT_IMPLEMENTED)
						{
							CancelDecoratorOperation();
							COMTHROW(retVal);
						}
						if (inNewDecoratorOperation) {
							if (decoratorOrAnnotator)
								objectInDecoratorOperation = object;
							else
								annotatorInDecoratorOperation = annotation;
						}
					}
				}
				if (inNewDecoratorOperation) {
					CScrollZoomView::OnLButtonDown(nFlags, ppoint);
					return;
				}

				CGuiObject* selection = FindObject(point);
				if (selection == NULL)	// select with label
					selection = FindObject(point, false, true);

				CGuiAnnotator* annotation = selection ? NULL : FindAnnotation(point);
				CGuiConnection* connection = router.FindConnection(point);

				POSITION alreadySelected = 0;
				if((selection != 0) || (annotation != 0)) {
					if (selection) {
						CGMEEventLogger::LogGMEEvent("    LButton over "+selection->GetName()+" "+selection->GetID()+"\r\n"); 
						alreadySelected = selected.Find(selection);
						if(alreadySelected)
						{
							this->SendUnselEvent4Object( selected.GetAt( alreadySelected));
							selected.RemoveAt(alreadySelected);
						}
						else if(!(nFlags & MK_CONTROL)) {
							RemoveAllAnnotationFromSelection();
							this->SendUnselEvent4List( &selected);
							selected.RemoveAll();
							ClearConnectionSelection();
						}

						this->SendSelecEvent4Object( selection);
						selected.AddHead(selection);
					}
					if (annotation) {
						CGMEEventLogger::LogGMEEvent("    LButton over "+annotation->GetName()+"\r\n"); 
						alreadySelected = selectedAnnotations.Find(annotation);
						if (alreadySelected) {
							RemoveAnnotationFromSelection(alreadySelected);
						} else if (!(nFlags & MK_CONTROL)) {
							this->SendUnselEvent4List( &selected);
							selected.RemoveAll();
							RemoveAllAnnotationFromSelection();
						}
						AddAnnotationToSelectionHead(annotation);
					}

					inDrag = true;
					CRect selRect(0,0,0,0);
					CRect selAnnRect(0,0,0,0);
					CGuiObject::GetExtent(selected,selRect);
					CGuiAnnotator::GetExtent(selectedAnnotations, selAnnRect);
					dragRect.UnionRect(selRect, selAnnRect);

					CPoint ptClickOffset(point.x - dragRect.left,
											point.y - dragRect.top);
					CRect rectAwake = CRect(trackPoint.x,trackPoint.y,trackPoint.x + 1,trackPoint.y + 1);
					rectAwake.InflateRect(3,3);
					ClientToScreen(&dragRect);
					ClientToScreen(&rectAwake);

					CRectList rects;
					CRectList annRects;
					CGuiObject::GetRectList(selected,rects);
					CGuiAnnotator::GetRectList(selectedAnnotations,annRects);
					CGMEDataDescriptor desc(rects,annRects,point,ptClickOffset);
					CGMEDataDescriptor::destructList( rects);
					CGMEDataDescriptor::destructList( annRects);

					validGuiObjects = true;
					dragSource = (selected.GetCount() > 0) ? selected.GetHead() : NULL;
					DROPEFFECT dropEffect = CGMEDoc::DoDragDrop(&selected, &selectedAnnotations, &desc,
						DROPEFFECT_MOVE | DROPEFFECT_COPY | DROPEFFECT_LINK, &rectAwake,this);

					if(validGuiObjects && dropEffect == DROPEFFECT_NONE) {
						if(nFlags & MK_CONTROL) {
							if (selection) {
								if(alreadySelected) {
									this->SendUnselEvent4Object( selected.GetHead());
									selected.RemoveHead();
									selection = selected.GetCount() ? selected.GetHead() : 0;
								}
								ChangeAttrPrefObjs(selected);
							}
							if (annotation) {
								if (alreadySelected) {
									RemoveAnnotationFromSelectionHead();
									annotation = selectedAnnotations.GetCount() ? selectedAnnotations.GetHead() : 0;
									/*
									if(annotation)
										ChangeAttrPrefFco(annotation);
									*/
								}
								else
									/*
									ChangeAttrPrefFco(annotation);
									*/ ;
							}
						}
						else {
							this->SendUnselEvent4List( &selected);
							selected.RemoveAll();
							RemoveAllAnnotationFromSelection();
							ClearConnectionSelection();
							if (selection) {
								if(!alreadySelected) {
									this->SendSelecEvent4Object( selection);
									selected.AddHead(selection);
									ChangeAttrPrefObjs(selected);
								}
							}
							if (annotation) {
								if(!alreadySelected) {
									AddAnnotationToSelectionHead(annotation);
									 /* ChangeAttrPrefFco(selectedAnnotations.GetTail()); */
								}
							}
						}
					}
					else {
						ChangeAttrPrefObjs(selected);
					}
					Invalidate();
					if(inDrag && dropEffect == DROPEFFECT_MOVE) {
/* HACK
						int num;
						if((num = currentModel->CheckForReferences(selected)) > 0) {
							char txt[128];
							sprintf(txt,"Selected model(s) cannot be deleted due to %ld reference(s)",num);
							AfxMessageBox(txt,MB_OK | MB_ICONSTOP);
						}
						else if((num = currentModel->CheckForInherited(selected)) > 0) {
							char txt[128];
							sprintf(txt,"Selected model(s) cannot be deleted due to %ld inherited part(s)",num);
							AfxMessageBox(txt,MB_OK | MB_ICONSTOP);
						}
						else {
							MoveToTrash(selected);
						 	CGMEDoc *doc = GetDocument();
							doc->SetModifiedFlag(TRUE);
							selected.RemoveAll();
							selection = 0;
						}
*/
					}
					inDrag = false;

				}
				else {
					this->SendUnselEvent4List( &selected);
					selected.RemoveAll();
					RemoveAllAnnotationFromSelection();
					ClearConnectionSelection();
					selection = 0;
					annotation = 0;

					if (connection) {
						ChangeAttrPrefFco(connection);
					}
					else {
						CRectTracker tracker;
						CClientDC dc(this);
						OnPrepareDC(&dc);
						if(tracker.TrackRubberBand(this, trackPoint,TRUE)) {
							tracker.m_rect.NormalizeRect();
							dc.DPtoLP(tracker.m_rect);
							FindObjects(tracker.m_rect,selected);
							this->SendSelecEvent4List( &selected);
							FindAnnotations(tracker.m_rect,selectedAnnotations);
							if(selected.GetCount() > 0) {
								selection = selected.GetHead();
							}
							else if (selectedAnnotations.GetCount() > 0 ){
								annotation = selectedAnnotations.GetHead();
								// ANNTODO: ChangeAttrPrefFco...
							}
							ChangeAttrPrefObjs(selected);
						}
					}
				}
				bool succ = this->SendNow();
				Invalidate( succ);
			}
			break;
		case GME_AUTOCONNECT_MODE:
		case GME_SHORTAUTOCONNECT_MODE:
			{
				CGMEEventLogger::LogGMEEvent("    mode=GME_AUTOCONNECT_MODE\r\n");
				if(connTmp) {
					if(connSrc == 0) {
						connSrc = connTmp;
						connSrcPort = connTmpPort;
						connSrcHotSide = connTmpHotSide;
					}
					else {
						Connect(connSrc, connSrcPort, connSrcHotSide, connTmp, connTmpPort, connTmpHotSide, 0 != (nFlags & MK_SHIFT));
						ClearConnSpecs();
						if( doc->GetEditMode() == GME_SHORTAUTOCONNECT_MODE)
							GetDocument()->SetMode(0); // switch back to GME_EDIT_MODE
					}

				}
			}
			Invalidate();
			break;
		case GME_DISCONNECT_MODE:
		case GME_SHORTDISCONNECT_MODE:
			{
				CGMEEventLogger::LogGMEEvent("    mode=GME_DISCONNECT_MODE\r\n");
				CGuiObject *selection = FindObject(point);
				if(selection) {
					CGuiPort *port = 0;
					port = selection->FindPort(point);
					if(connSrc == 0) {
						if (port != 0) {
							connSrc = port->parent->GetParent();
							connSrcPort = port;
							CGuiConnectionList conns;
							FindConnections(connSrc,connSrcPort,conns);
							if(conns.GetCount() < 2) {
								if(conns.GetCount() == 1) {
									if(!DeleteConnection(conns.GetHead())) {
										AfxMessageBox("Connection cannot be deleted!");
									}
								}
								else if(conns.GetCount() == 0) {
									AfxMessageBox("Selected object is not connected!");
								}
								ClearConnSpecs();
								if( doc->GetEditMode() == GME_SHORTDISCONNECT_MODE)
									GetDocument()->SetMode(0); // switch back to GME_EDIT_MODE
							}
						} else {
							AfxMessageBox("Cannot find port to connection!");
						}
					}
					else {
						CGuiConnectionList conns;
						FindConnections(connSrc,connSrcPort,selection,port,conns);
						if(conns.GetCount()) {
							if(!DeleteConnection(conns.GetHead()))
								AfxMessageBox("Connection cannot be deleted!");
						}
						else
							AfxMessageBox("Selected objects are not connected!");
						ClearConnSpecs();
						if( doc->GetEditMode() == GME_SHORTDISCONNECT_MODE)
							GetDocument()->SetMode(0); // switch back to GME_EDIT_MODE
					}
				}
				if(!selection) {
					CGuiConnection *conn = router.FindConnection(point);
					if(conn) {
						if(!DeleteConnection(conn))
							AfxMessageBox("Connection cannot be deleted!");
						ClearConnSpecs();
						if( doc->GetEditMode() == GME_SHORTDISCONNECT_MODE)
							GetDocument()->SetMode(0); // switch back to GME_EDIT_MODE
					}
				}
			}
			Invalidate();
			break;
		case GME_SET_MODE:
			{
				CGMEEventLogger::LogGMEEvent("    mode=GME_SET_MODE\r\n");
				if(!currentSet)
					break;
				CGuiFco *fco = 0;
				try {
					BeginTransaction(TRANSACTION_READ_ONLY);
					CGuiObject *object = FindObject(point);
					if(object) {
						CGMEEventLogger::LogGMEEvent("    LButton over "+object->GetName()+" "+object->GetID()+"\r\n");
						if(currentSet->CheckMember(object))
							fco = object;
					}
					else {
						CGuiConnection *conn = router.FindConnection(point);
						if(conn && currentSet->CheckMember(conn))
							fco = conn;
					}
					CommitTransaction();
				}
				catch(hresult_exception &e) {
					AbortTransaction(e.hr);
					break;
				}
				if(fco) {
					try {
						BeginTransaction();
						currentSet->ToggleMember(fco);	// nothing else needs to be done: events will be generated!
						CommitTransaction();
					}
					catch(hresult_exception &e) {
						AbortTransaction(e.hr);
						break;
					}
				}
			}
			break;
		case GME_ZOOM_MODE:
			{
				CGMEEventLogger::LogGMEEvent("    mode=GME_ZOOM_MODE\r\n");
                CRectTracker tracker;
				tracker.m_rect = CRect(0,0,0,0);
                if(tracker.TrackRubberBand(this, trackPoint,TRUE)) 
				{
					CRect truerect(0,0,0,0);
					tracker.GetTrueRect(&truerect);
					truerect.NormalizeRect();
					if (truerect.Height() <= MIN_ZOOM_RECT && truerect.Width() <= MIN_ZOOM_RECT)
						ZoomIn(ppoint); 
					else
						ZoomRect(truerect);
                }
				else
					ZoomIn(ppoint); 
				Invalidate();
			}
			break;
		case GME_VISUAL_MODE:
			{
				CGMEEventLogger::LogGMEEvent("    mode=GME_VISUAL_MODE\r\n");
				CGuiObject *obj = FindObject(point);
				if(obj) {
					CGMEEventLogger::LogGMEEvent("    LButton over "+obj->GetName()+" "+obj->GetID()+"\r\n");
					obj->ToggleGrayOut();
					CGuiFco::GrayOutNonInternalConnections(connections);
					Invalidate();
				}
				else {
					CGuiConnection *conn = router.FindConnection(point);
					if(conn) {
						CGMEEventLogger::LogGMEEvent("    LButton over "+conn->GetName()+" "+conn->GetID()+"\r\n");
						conn->ToggleGrayOut();
						conn->GrayOutEndPoints();
						Invalidate();
					}
					else {
						CGuiAnnotator *ann = FindAnnotation(point);
						if (ann) {
							CGMEEventLogger::LogGMEEvent("    LButton over "+ann->GetName()+"\r\n");
							ann->ToggleGrayOut();
							Invalidate();
						}
					}
				}
			}
			break;
		default:
			break;
		}
	}
	dragSource = 0;
	CScrollZoomView::OnLButtonDown(nFlags, point);
}

void CGMEView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnLButtonDblClk in " + path + name + "\r\n");
	CPoint ppoint = point;
	if (GetDocument()->GetEditMode() == GME_EDIT_MODE) {
		CoordinateTransfer(point);	// DPtoLP

		CGMEView* self = const_cast<CGMEView*> (this);
		CGuiObject*	object	= self ? self->FindObject(point, true, true) : 0;
		if (object == NULL)	// not label of the object but can be some port label inside the object
			object = self ? self->FindObject(point, true, false) : 0;
		CGuiAnnotator *annotation = FindAnnotation(point);

		if (object || annotation) {
			CComPtr<IMgaNewDecorator> newDecorator;
			if (object != NULL) {
				CGuiAspect* pAspect = object->GetCurrentAspect();
				if (pAspect != NULL) {
					CComQIPtr<IMgaNewDecorator> newDecorator2(pAspect->GetDecorator());
					newDecorator = newDecorator2;
				}
			} else {
				annotation = FindAnnotation(point);
				if (annotation)
					newDecorator = annotation->GetNewDecorator(currentAspect->index);
			}

			if (newDecorator) {
				CClientDC transformDC(this);
				OnPrepareDC(&transformDC);
				HRESULT retVal = newDecorator->MouseLeftButtonDoubleClick(nFlags, point.x, point.y, (ULONGLONG)transformDC.m_hDC);
				if (retVal == S_DECORATOR_EVENT_HANDLED) {
					if (inOpenedDecoratorTransaction) {
						if (shouldCommitOperation) {
							CommitTransaction();
							shouldCommitOperation = false;
							objectInDecoratorOperation = NULL;
							annotatorInDecoratorOperation = NULL;
						} else {
							AbortTransaction(S_OK);
						}
						inOpenedDecoratorTransaction = false;
						isContextInitiatedOperation = false;
					}
					CScrollZoomView::OnLButtonDblClk(nFlags, ppoint);
					return;
				} else if (retVal != S_OK &&
						   retVal != S_DECORATOR_EVENT_NOT_HANDLED &&
						   retVal != E_DECORATOR_NOT_IMPLEMENTED)
				{
					CancelDecoratorOperation();
					COMTHROW(retVal);
				}
			}
		} else {
			CancelDecoratorOperation();
		}

		CGuiObject *selection = FindObject(point);

		if(selection) {
			CGMEEventLogger::LogGMEEvent(    "LButton double clicked on "+selection->GetName()+" "+selection->GetID()+"\r\n");
			CString aspectName = currentAspect->name;;
			CComPtr<IMgaFCO> mgaFco = selection->mgaFco;
			CComPtr<IMgaModel> model;
			CComPtr<IMgaReference> ref;
			CComPtr<IMgaFCO> referred;
			CComBSTR         referred_id;
			if(FAILED(mgaFco.QueryInterface(&model))) {		// it is not a model
				if(SUCCEEDED(mgaFco.QueryInterface(&ref))) {		// it is a reference
					CComPtr<IMgaObject> obj;
					try {
						BeginTransaction(TRANSACTION_READ_ONLY);
						COMTHROW(ref->get_Referred(&referred));
						if(referred)
						{
							COMTHROW(referred->GetParent(&obj));
							COMTHROW(referred->get_ID( &referred_id));
						}
						CommitTransaction();
					}
					catch(hresult_exception e) {
						AbortTransaction(e.hr);
						CScrollZoomView::OnLButtonDblClk(nFlags, ppoint);
					}
					if(referred) {
						if(FAILED(obj.QueryInterface(&model))) {		// it is a root
							if (SUCCEEDED(referred.QueryInterface(&model))) {
								int aspi = selection->MapAspect(selection->GetParentAspect());
								if(aspi >= 0) {
									try {
										BeginTransaction(TRANSACTION_READ_ONLY);
										CGuiCompoundReference *compref = dynamic_cast<CGuiCompoundReference *>(selection);
										VERIFY(compref);
										CComPtr<IMgaMetaFCO> metaFco;
										COMTHROW(compref->GetTerminalReferee()->get_Meta(&metaFco));
										metaref_type metaRef;
										VERIFY(metaFco);
										COMTHROW(metaFco->get_MetaRef(&metaRef));
										CGuiMetaModel *guiMetaModel = CGuiMetaProject::theInstance->GetGuiMetaModel(metaRef);
										VERIFY(guiMetaModel);
										CGuiMetaAspect *asp = guiMetaModel->FindAspect(aspi);
										if(asp) {
											aspectName = asp->name;
										}
										CommitTransaction();
									}
									catch (hresult_exception &e) {
										AbortTransaction(e.hr);
									}
								}
							}
//							AfxMessageBox("Referenced model is a root model. Opening model."); // instead show target selected
							else // obj is not a model, referred is also not a model
							{
								CGMEConsole::theInstance->Message( "Reference target is child of a folder, thus it is shown in the TreeBrowser only.", MSG_INFO);
								CGMEBrowser::theInstance->FocusItem( referred_id);//CComBSTR( mgaObjectId));//FireLocateMgaObject( (LPCTSTR) (CString) referred_id);
								//CGMEBrowser::theInstance->FocusItem( CComBSTR( (LPCTSTR) CString( referred_id)));
								CScrollZoomView::OnLButtonDblClk(nFlags, point);
								return;
							}
						}
					}
					else
					{
						AfxMessageBox("Unable to show referred object of null reference!");
						CGMEEventLogger::LogGMEEvent("    Unable to show referred object of null reference.\r\n");
					}
				}
			}
			else {
				int aspi = selection->MapAspect(selection->GetParentAspect());
				if(aspi >= 0) {
					CGuiCompound *comp = dynamic_cast<CGuiCompound *>(selection);
					VERIFY(comp);
					CGuiMetaModel *guiMetaModel = dynamic_cast<CGuiMetaModel *>(comp->guiMeta);
					VERIFY(guiMetaModel);
					CGuiMetaAspect *asp = guiMetaModel->FindAspect(aspi);
					if(asp)
						aspectName = asp->name;
				}
			}
			if(model != 0) {
				ShowModel(model,&aspectName);
#if !defined (ACTIVEXGMEVIEW)
				CGMEView *view = CGMEDoc::theInstance->FindView(model);
				if(view)
					view->SetCenterObject(referred);
#endif
			}
		}
		else if (annotation) {
			CGMEEventLogger::LogGMEEvent(    "LButton double clicked on "+annotation->GetName()+"\r\n");
			CComPtr<IMgaFCO> fcoToShow;
			currentModel.QueryInterface(&fcoToShow);
			ShowAnnotationBrowser(fcoToShow, annotation->rootNode);
		}
		else {
			OnViewParent();	// double click on model background brings up the parent model
							// user requested standard behavior
		}
	}
	CScrollZoomView::OnLButtonDblClk(nFlags, ppoint);
}

void CGMEView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnRButtonDown in "+path+name+"\r\n");
	CPoint local = point;
	CPoint ppoint = point;
	CoordinateTransfer(local);	// DPtoLP
	contextMenuLocation = local;

	CGMEDoc* doc = GetDocument();
	contextPort = 0;
	contextSelection = FindObject(local);
	if (contextSelection == NULL && doc->GetEditMode() == GME_EDIT_MODE)
		contextSelection = FindObject(local, false, true);
	if( dynamic_cast<CGuiObject*>( contextSelection)) {
		CGuiPort *port = dynamic_cast<CGuiObject*>( contextSelection)->FindPort( local);
		if(port && port->IsRealPort()) {
			contextPort = port;
		}
	}

	if(contextSelection == 0)
		contextSelection = router.FindConnection(local);
	if(!contextSelection) {
		contextAnnotation = FindAnnotation(local);
	}
	else {
		contextAnnotation = NULL;
	}
	if(contextSelection)
		CGMEEventLogger::LogGMEEvent("    RButton over "+contextSelection->GetName()+" "+contextSelection->GetID()+"\r\n");
	else if(contextAnnotation)
		CGMEEventLogger::LogGMEEvent("    RButton over "+contextAnnotation->GetName()+"\r\n");

	switch(doc->GetEditMode()) {
	case GME_SET_MODE:
		{
			CGMEEventLogger::LogGMEEvent("    mode=GME_SET_MODE\r\n");
			selected.RemoveAll();
			RemoveAllAnnotationFromSelection();
			ClearConnectionSelection();
			CGuiSet *set = dynamic_cast<CGuiSet *>(contextSelection);
			if(set) {
				if(set == currentSet)
					currentSet = 0;
				else {
					currentSet = set;
					selected.AddHead(set);
					ChangeAttrPrefFco(set);
				}
			}
			else
				currentSet = 0;
			if(currentSet) {
				CGuiAnnotator::GrayOutAnnotations(annotators,true);
				CGuiFco::GrayOutFcos(children,true);
				CGuiFco::GrayOutFcos(connections,true);
				currentSet->GrayOutMembers(false);
				currentSet->GrayOut(false);
			}
			else {
				CGuiAnnotator::GrayOutAnnotations(annotators,false);
				CGuiFco::GrayOutFcos(children,false);
				CGuiFco::GrayOutFcos(connections,false);
			}
			Invalidate();
		}
		break;
	case GME_ZOOM_MODE:
		{
			CGMEEventLogger::LogGMEEvent("    mode=GME_ZOOM_MODE\r\n");
			ZoomOut(ppoint);
			Invalidate();
		}
		break;
	case GME_VISUAL_MODE:
		{
			CGMEEventLogger::LogGMEEvent("    mode=GME_VISUAL_MODE\r\n");
			CGuiObject *obj = dynamic_cast<CGuiObject *>(contextSelection);
			if(obj) {
				obj->ToggleGrayOut();
				obj->GrayOutNeighbors();
				CGuiFco::GrayOutNonInternalConnections(connections);
				Invalidate();
			}
			else {
				CGuiConnection *conn = dynamic_cast<CGuiConnection *>(contextSelection);
				if(conn) {
					conn->ToggleGrayOut();
					conn->GrayOutEndPoints();
					CGuiFco::GrayOutNonInternalConnections(connections);
					Invalidate();
				}
			}
			if (contextAnnotation) {
				contextAnnotation->ToggleGrayOut();
				Invalidate();
			}
		}
		break;
	case GME_EDIT_MODE:
		{
			CGMEEventLogger::LogGMEEvent("    mode=GME_EDIT_MODE\r\n");
			CPoint global = point;
			ClientToScreen(&global);

			// new selection logic 8/2/00
			CGuiObject* selection = FindObject(local);
			if (selection == NULL)	// select with label
				selection = FindObject(local, false, true);

			{
				CGuiAnnotator *annotation = selection ? NULL : FindAnnotation(local);

	 	 	 	POSITION alreadySelected = 0;
				if(selection != 0) {
					alreadySelected = selected.Find(selection);
					if(!(nFlags & MK_CONTROL)) {
						this->SendUnselEvent4List( &selected);
						selected.RemoveAll();
						RemoveAllAnnotationFromSelection();
						ClearConnectionSelection();
					}
					else if(alreadySelected) {
						this->SendUnselEvent4Object( selected.GetAt( alreadySelected));
						selected.RemoveAt(alreadySelected);
					}
					this->SendSelecEvent4Object( selection);
					selected.AddHead(selection);
					ChangeAttrPrefObjs(selected);
				} else {
					if (annotation != 0) {
						alreadySelected = selectedAnnotations.Find(annotation);
						if (!(nFlags & MK_CONTROL)) {
							this->SendUnselEvent4List( &selected);
							selected.RemoveAll();
							RemoveAllAnnotationFromSelection();
						} else if (alreadySelected) {
							RemoveAnnotationFromSelection(alreadySelected);
						}
						AddAnnotationToSelectionHead(annotation);
						// ANNTODO: ChangeAttrPref....
					}
				}

				Invalidate();
			}

			if (contextPort != NULL) {
				CString itemname = CString( "[") + (contextSelection?(contextSelection->GetInfoText() + CString(" : ")): CString("")) + contextPort->GetInfoText() + CString( "]");

				CMenu menu;
				menu.LoadMenu(IDR_PORTCONTEXT_MENU);

				CMenu *sm = menu.GetSubMenu(0); ASSERT( sm);
				if( sm) {
					sm->InsertMenu( 0, MF_BYPOSITION|MF_SEPARATOR); 
					sm->InsertMenu( 0, MF_BYPOSITION|MFS_DEFAULT, ID_CNTX_SHOWPORTINPARENT, itemname);
					sm->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, global.x,global.y,GetParent());
				}
			} else if (contextSelection != NULL) {
				HMENU decoratorAdditionalMenu = ::CreatePopupMenu();
				if (selection != NULL) {
					CGuiAspect* pAspect = selection->GetCurrentAspect();
					if (pAspect != NULL) {
						CComQIPtr<IMgaNewDecorator> newDecorator(pAspect->GetDecorator());
						HRESULT retVal = S_OK;
						if (newDecorator) {
							CClientDC transformDC(this);
							OnPrepareDC(&transformDC);
							retVal = newDecorator->MouseRightButtonDown((ULONGLONG)decoratorAdditionalMenu, nFlags, local.x, local.y, (ULONGLONG)transformDC.m_hDC);
						}
					}
				}
				CMenu menu;
				menu.LoadMenu(dynamic_cast<CGuiConnection*> (contextSelection) ? IDR_CONNCONTEXT_MENU : IDR_CONTEXT_MENU);
				CMenu* subMenu = menu.GetSubMenu(0);
				if (::GetMenuItemCount(decoratorAdditionalMenu) > 0) {
					subMenu->InsertMenu(0, MF_BYPOSITION | MF_SEPARATOR, 0, "");
					subMenu->InsertMenu(0, MF_BYPOSITION | MF_POPUP | MF_ENABLED, (UINT_PTR)(decoratorAdditionalMenu), "Decorator Edit");
				}
				UINT cmdId = (UINT)subMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
															global.x,global.y,GetParent());
				// Save state for possible later use, see OnCmdMsg
				ctxClkSt.nFlags = nFlags;
				ctxClkSt.lpoint = local;
				ctxClkSt.dpoint = ppoint;
				selectedObjectOfContext = selection;
				::DestroyMenu(decoratorAdditionalMenu);
			} else if (contextAnnotation != NULL) {
				HMENU decoratorAdditionalMenu = ::CreatePopupMenu();
				CComPtr<IMgaNewDecorator> newDecorator = contextAnnotation->GetNewDecorator(currentAspect->index);
				HRESULT retVal = S_OK;
				if (newDecorator) {
					CClientDC transformDC(this);
					OnPrepareDC(&transformDC);
					retVal = newDecorator->MouseRightButtonDown((ULONGLONG)decoratorAdditionalMenu, nFlags, local.x, local.y, (ULONGLONG)transformDC.m_hDC);
				}
				CMenu menu;
				menu.LoadMenu(IDR_ANNCONTEXT_MENU);
				CMenu* subMenu = menu.GetSubMenu(0);
				if (::GetMenuItemCount(decoratorAdditionalMenu) > 0) {
					subMenu->InsertMenu(0, MF_BYPOSITION | MF_SEPARATOR, 0, "");
					subMenu->InsertMenu(0, MF_BYPOSITION | MF_POPUP | MF_ENABLED, (UINT_PTR)(decoratorAdditionalMenu), "Decorator Edit");
				}
				UINT cmdId = (UINT)subMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
															global.x,global.y,GetParent());
				selectedAnnotationOfContext = contextAnnotation;
				::DestroyMenu(decoratorAdditionalMenu);
			} else {
				CMenu menu;
				menu.LoadMenu(IDR_SELFCONTEXT_MENU);
				CMenu *submenu = menu.GetSubMenu(0);
				currentAspect->InitContextMenu(submenu);
#if defined(ADDCRASHTESTMENU)
				CMenu crashTestMenu;
				crashTestMenu.LoadMenu(IDR_CRASH_TEST_MENU);
				submenu->AppendMenu(MF_POPUP, (UINT_PTR)((HMENU)crashTestMenu), "Debug");
#endif
				submenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
					   							global.x,global.y,GetParent());
				currentAspect->ResetContextMenu(submenu);
			}
		}
		break;

	case GME_AUTOCONNECT_MODE:
	case GME_SHORTAUTOCONNECT_MODE:
		CGMEEventLogger::LogGMEEvent("    mode=GME_AUTOCONNECT_MODE\r\n");
	case GME_DISCONNECT_MODE:
	case GME_SHORTDISCONNECT_MODE:
		{
			CGMEEventLogger::LogGMEEvent("    mode=GME_DISCONNECT_MODE\r\n");
			CPoint global = point;
			ClientToScreen(&global);
			if(contextSelection) {
				CMenu menu;
				menu.LoadMenu(dynamic_cast<CGuiConnection *>(contextSelection) ? IDR_CONNCONTEXT_MENU : IDR_CONTEXT_MENU);
				menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
													global.x,global.y,GetParent());
			}
			else if (contextAnnotation) {
				CMenu menu;
				menu.LoadMenu(IDR_ANNCONTEXT_MENU);
				menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
													global.x,global.y,GetParent());
			}
			else {
				CMenu menu;
				menu.LoadMenu(IDR_SELFCONTEXT_MENU);
				CMenu *submenu = menu.GetSubMenu(0);
				currentAspect->InitContextMenu(submenu);
				submenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
					   							global.x,global.y,GetParent());
				currentAspect->ResetContextMenu(submenu);
			}
		}
		break;
	}
	CScrollZoomView::OnRButtonDown(nFlags, ppoint);
	this->SendNow();
}


DROPEFFECT CGMEView::OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnDragEnter in "+path+name+"\r\n");
	ASSERT(prevDropEffect == DROPEFFECT_NONE);

	if(isType && CGMEDataSource::IsGmeNativeDataAvailable(pDataObject,theApp.mgaProject)) {
//	if(pDataObject->IsDataAvailable(CGMEDataSource::cfGMEDesc)) {

		if(dragDesc.Load(pDataObject)) {
			dragOffset = dragDesc.offset;
			dragPoint = point - CSize(1,1);
			return OnDragOver(pDataObject,dwKeyState,point);
		}
	}
	else if( isType && CGMEDataSource::IsXMLDataAvailable(pDataObject) )
		return DROPEFFECT_COPY;

	CoordinateTransfer(point);
	DROPEFFECT dropEffect = DROPEFFECT_NONE;
	HRESULT retVal = S_OK;
	CGuiObject* selection = FindObject(point);
	if (selection != NULL) {
		CGuiAspect* pAspect = selection->GetCurrentAspect();
		if (pAspect != NULL) {
			CComQIPtr<IMgaNewDecorator> newDecorator(pAspect->GetDecorator());
			if (newDecorator) {
				CClientDC transformDC(this);
				OnPrepareDC(&transformDC);
				retVal = newDecorator->DragEnter(&dropEffect, (ULONGLONG)pDataObject, dwKeyState, point.x, point.y, (ULONGLONG)transformDC.m_hDC);
			}
		}
	}
	if (dropEffect != DROPEFFECT_NONE) {
		dragPoint = point;
		return dropEffect;
	}

	CGuiAnnotator* annotation = FindAnnotation(point);
	if (annotation != NULL) {
		CComPtr<IMgaNewDecorator> newDecorator = annotation->GetNewDecorator(currentAspect->index);
		if (newDecorator) {
			CClientDC transformDC(this);
			OnPrepareDC(&transformDC);
			retVal = newDecorator->DragEnter(&dropEffect, (ULONGLONG)pDataObject, dwKeyState, point.x, point.y, (ULONGLONG)transformDC.m_hDC);
		}
	}
	if (dropEffect != DROPEFFECT_NONE) {
		dragPoint = point;
		return dropEffect;
	}

	return DROPEFFECT_NONE;
}

void CGMEView::OnDragLeave()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnDragLeave from "+path+name+"\r\n");
 	CClientDC dc(this);
	OnPrepareDC(&dc);
	if(prevDropEffect != DROPEFFECT_NONE) {
		dragDesc.Draw(&dc,dragPoint);
		prevDropEffect = DROPEFFECT_NONE;
	}
	dragDesc.Clean();
}

DROPEFFECT CGMEView::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnDragOver in "+path+name+"\r\n"); 
	//this event happens too much, logfile size could explode...
	if(!CGMEDataSource::IsGmeNativeDataAvailable(pDataObject,theApp.mgaProject))
//	if(!pDataObject->IsDataAvailable(CGMEDataSource::cfGMEDesc))
	{
		if(isType && CGMEDataSource::IsXMLDataAvailable(pDataObject))
			return DROPEFFECT_COPY;

		return DROPEFFECT_NONE;
	}

	CoordinateTransfer(point);
	CGuiObject *obj = FindObject(point);
	HRESULT retVal = S_OK;
	DROPEFFECT dropEffect = DROPEFFECT_NONE;
	if(obj) {
		CGMEEventLogger::LogGMEEvent("    Dragging over: "+obj->GetName()+" "+obj->GetID()+" in "+path+name+"\r\n");//better this way, not logging dragging over empty space

		CGuiAspect* pAspect = obj->GetCurrentAspect();
		if (pAspect != NULL) {
			CComQIPtr<IMgaNewDecorator> newDecorator(pAspect->GetDecorator());
			if (newDecorator) {
				CClientDC transformDC(this);
				OnPrepareDC(&transformDC);
				retVal = newDecorator->DragOver(&dropEffect, (ULONGLONG)pDataObject, dwKeyState, point.x, point.y, (ULONGLONG)transformDC.m_hDC);
			}
		}
		if (dropEffect != DROPEFFECT_NONE)
			return dropEffect;
	}

	CGuiAnnotator* annotation = FindAnnotation(point);
	if (annotation != NULL) {
		CComPtr<IMgaNewDecorator> newDecorator = annotation->GetNewDecorator(currentAspect->index);
		if (newDecorator) {
			CClientDC transformDC(this);
			OnPrepareDC(&transformDC);
			retVal = newDecorator->DragOver(&dropEffect, (ULONGLONG)pDataObject, dwKeyState, point.x, point.y, (ULONGLONG)transformDC.m_hDC);
		}
	}
	if (dropEffect != DROPEFFECT_NONE)
		return dropEffect;

	CGuiObject *ref = dynamic_cast<CGuiReference *>(obj);
	if(!ref)
		ref = dynamic_cast<CGuiCompoundReference *>(obj);

	if(ref && obj != dragSource && dragDesc.GetCount() <= 1)
		return DROPEFFECT_LINK;
	else if(!isType)
		return DROPEFFECT_NONE;

	DROPEFFECT de = DROPEFFECT_MOVE;
	if((dwKeyState & MK_CONTROL) != 0)
		de = (((dwKeyState & MK_SHIFT) == 0) ? DROPEFFECT_COPY : DROPEFFECT_LINK);

	if((dwKeyState & MK_ALT) != 0) {
		de = DROPEFFECT_COPY | DROPEFFECT_LINK;
		derivedDrop = true;
		instanceDrop = ((dwKeyState & MK_SHIFT) == 0);
	}
	else {
		derivedDrop = false;
		instanceDrop = false;
	}

	if(point == dragPoint)
		return de;

	CClientDC dc(this);
	OnPrepareDC(&dc);
	if(prevDropEffect != DROPEFFECT_NONE) {
		dragDesc.Draw(&dc,dragPoint);
	}
	prevDropEffect = de;
	if(prevDropEffect != DROPEFFECT_NONE) {
		dragPoint = point;
		dragDesc.Draw(&dc,point);
	}
	return de;
}

BOOL CGMEView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point)
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnDrop in "+path+name+"\r\n");
	if(dropEffect & DROPEFFECT_MOVE)
		CGMEEventLogger::LogGMEEvent("    DROPEFFECT_MOVE\r\n");
	if(dropEffect & DROPEFFECT_LINK)
		CGMEEventLogger::LogGMEEvent("    DROPEFFECT_LINK\r\n");
	if(dropEffect & DROPEFFECT_COPY)
		CGMEEventLogger::LogGMEEvent("    DROPEFFECT_COPY\r\n");
	if(dropEffect == DROPEFFECT_NONE) //DROPEFFECT_NONE==0
		CGMEEventLogger::LogGMEEvent("    DROPEFFECT_NONE\r\n");
	ASSERT_VALID(this);
	CGMEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CSize size;
	CPoint orig = point;
	CPoint testPoint = point;

	CoordinateTransfer(point);
	CoordinateTransfer(testPoint);

	point.x = (long)(point.x - dragOffset.x);
	point.y = (long)(point.y - dragOffset.y);

	OnDragLeave();
	if(isType) {
		if ((dropEffect & DROPEFFECT_MOVE) && inDrag)
		{
			ASSERT((selected.GetCount() + selectedAnnotations.GetCount()) > 0);
			CGMEEventLogger::LogGMEEvent("    Dropping:\r\n");
			GMEEVENTLOG_GUIOBJS(selected);
			GMEEVENTLOG_GUIANNOTATORS(selectedAnnotations);
			Invalidate();

			try {
				BeginTransaction();
				int left = 0, top = 0, leftA = 0, topA = 0;
				bool valid = false, validA = false;
				if (selected.GetCount() > 0) {
					CGuiObject::FindUpperLeft(selected, left, top);
					valid = true;
				}
				if (selectedAnnotations.GetCount() > 0) {
					CGuiAnnotator::FindUpperLeft(selectedAnnotations, leftA, topA);
					validA = true;
				}
				if (valid && validA) {
					left = min(left, leftA);
					top = min(top, topA);
				}
				else if (validA) {
					left = leftA;
					top = topA;
				}
				else if (!valid) {
					ASSERT(("There is no object to move",false));
				}
				CPoint diff = point - CPoint(left,top);
				CGuiObject::ShiftModels(selected, diff);
				CGuiAnnotator::ShiftAnnotations(selectedAnnotations,diff);
				CommitTransaction();
				ResetParent();
			}
			catch(hresult_exception e) {                
				AbortTransaction(e.hr);
				CGMEEventLogger::LogGMEEvent("    Unable to complete drop operation.\r\n");
				AfxMessageBox("Unable to complete drop operation",MB_ICONSTOP | MB_OK);
				Reset(true);
				return FALSE;
			}
			AutoRoute(); // HACK reroute the whole thing for now!
			Invalidate(true);
			inDrag = false;
			return TRUE;
		}
	}
	CGuiObject *target = FindObject(testPoint);
	HRESULT retVal = S_OK;
	if (target != NULL) {
		CGuiAspect* pAspect = target->GetCurrentAspect();
		if (pAspect != NULL) {
			CComQIPtr<IMgaNewDecorator> newDecorator(pAspect->GetDecorator());
			if (newDecorator) {
				CClientDC transformDC(this);
				OnPrepareDC(&transformDC);
				retVal = newDecorator->Drop((ULONGLONG)pDataObject, dropEffect, point.x, point.y, (ULONGLONG)transformDC.m_hDC);
			}
		}
	}
	if (retVal == S_DECORATOR_EVENT_HANDLED)
		return TRUE;

	CGuiAnnotator* annotation = FindAnnotation(point);
	if (annotation != NULL) {
		CComPtr<IMgaNewDecorator> newDecorator = annotation->GetNewDecorator(currentAspect->index);
		if (newDecorator) {
			CClientDC transformDC(this);
			OnPrepareDC(&transformDC);
			retVal = newDecorator->Drop((ULONGLONG)pDataObject, dropEffect, point.x, point.y, (ULONGLONG)transformDC.m_hDC);
		}
	}
	if (retVal == S_DECORATOR_EVENT_HANDLED)
		return TRUE;

	CGuiReference *guiRef = dynamic_cast<CGuiReference *>(target);
	CGuiCompoundReference *compRef = dynamic_cast<CGuiCompoundReference *>(target);
	bool sameTarget = (target == dragSource);
	if(isType || guiRef || compRef) {
		DoPasteItem(pDataObject,
					true,
					((dropEffect & DROPEFFECT_MOVE) != 0) && !(guiRef || compRef),
					(dropEffect & DROPEFFECT_LINK) != 0 || guiRef || compRef,
					derivedDrop,
					instanceDrop,
					false,
					false,
					((guiRef || compRef) && !sameTarget) ? target : 0,
					point);
		derivedDrop = instanceDrop = false;
//		GetDocument()->InvalidateAllViews(true);
		return TRUE;
	}
	CGMEEventLogger::LogGMEEvent("    Nothing Dropped\r\n");
	return FALSE;
}

void CGMEView::OnViewParent()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnViewParent from "+path+name+"\r\n");
	ShowModel(parent);
}

void CGMEView::OnUpdateViewParent(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(parent != 0);
}

void CGMEView::ShowGrid(bool show)
{
	drawGrid = show;
	Invalidate();
}

void CGMEView::OnViewGrid()
{
	drawGrid = !drawGrid;
	Invalidate();
}

void CGMEView::OnUpdateViewGrid(CCmdUI* pCmdUI)
{
//	pCmdUI->Enable(zoomIdx >= GME_ZOOM_LEVEL_MED);
	pCmdUI->Enable(m_zoomVal >= ZOOM_NO);
	pCmdUI->SetCheck(drawGrid);
}

void CGMEView::OnEditNudgedown()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnEditNudgedown in "+path+name+"\r\n");

	try {
		BeginTransaction();
		CGuiAnnotator::NudgeAnnotations(selectedAnnotations,0,1);
		if(isType && CGuiObject::NudgeObjects(selected,0,1))
			router.NudgeObjects(selected,0,1);
		Invalidate();

		CommitTransaction();
	}
	catch(hresult_exception e) {
		AbortTransaction(e.hr);
		AfxMessageBox("Unable to nudge objects",MB_ICONSTOP | MB_OK);
		CGMEEventLogger::LogGMEEvent("    Unable to nudge objects.\r\n");
		return;
	}
	ResetParent();
//  Workaround fixes sticky objects
	Invalidate(true);
}

void CGMEView::OnEditNudgeleft()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnEditNudgeleft in "+path+name+"\r\n");

	try {
		BeginTransaction();
		CGuiAnnotator::NudgeAnnotations(selectedAnnotations,-1,0);
		if(isType && CGuiObject::NudgeObjects(selected,-1,0))
			router.NudgeObjects(selected,-1,0);
		Invalidate();
		CommitTransaction();
	}
	catch(hresult_exception e) {
		AbortTransaction(e.hr);
		AfxMessageBox("Unable to nudge objects",MB_ICONSTOP | MB_OK);
		CGMEEventLogger::LogGMEEvent("    Unable to nudge objects.\r\n");
		return;
	}
	ResetParent();
//  Workaround fixes sticky objects
	Invalidate(true);
}

void CGMEView::OnEditNudgeright()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnEditNudgeright in "+path+name+"\r\n");

	try {
		BeginTransaction();
		CGuiAnnotator::NudgeAnnotations(selectedAnnotations,1,0);
		if(isType && CGuiObject::NudgeObjects(selected,1,0))
			router.NudgeObjects(selected,1,0);
		Invalidate();
		CommitTransaction();
	}
	catch(hresult_exception e) {
		AbortTransaction(e.hr);
		AfxMessageBox("Unable to nudge objects",MB_ICONSTOP | MB_OK);
		CGMEEventLogger::LogGMEEvent("    Unable to nudge objects.\r\n");
		return;
	}
	ResetParent();
//  Workaround fixes sticky objects
	Invalidate(true);
}

void CGMEView::OnEditNudgeup()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnEditNudgeup in "+path+name+"\r\n");

	try {
		BeginTransaction();
		CGuiAnnotator::NudgeAnnotations(selectedAnnotations,0,-1);
		if(isType && CGuiObject::NudgeObjects(selected,0,-1))
			router.NudgeObjects(selected,0,-1);
		Invalidate();
		CommitTransaction();
	}
	catch(hresult_exception e) {
		AbortTransaction(e.hr);
		AfxMessageBox("Unable to nudge objects",MB_ICONSTOP | MB_OK);
		CGMEEventLogger::LogGMEEvent("    Unable to nudge objects.\r\n");
		return;
	}
	ResetParent();
//  Workaround fixes sticky objects
	Invalidate(true);
}

BOOL CGMEView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	if (nID == ID_EDIT_CANCEL && inNewDecoratorOperation)	// capture ESC for decorator operation cancel
		CancelDecoratorOperation();

	if(CGuiMetaProject::theInstance->CmdIDInRange(nID))	{
		if(nCode == CN_COMMAND && pHandlerInfo == NULL) {
			CString label;
			switch (CGuiMetaProject::theInstance->CmdType(nID,label)) {
			case GME_CMD_CONTEXT:
				if(isType && currentAspect->FindCommand(nID,label))
					InsertNewPart(label,contextMenuLocation);
				break;
			default:
				ASSERT(FALSE);
				break;
			}
			return true;
		}
		else if(nCode == CN_UPDATE_COMMAND_UI && pExtra != NULL) {
			CCmdUI *pUI = (CCmdUI *)pExtra;
			pUI->Enable(isType);
			return true;
		}
	} else if (nID >= DECORATOR_CTX_MENU_MINID && nID < DECORATOR_CTX_MENU_MAXID) {
		if (nCode == CN_UPDATE_COMMAND_UI && pExtra != NULL) {
			CCmdUI* pUI = (CCmdUI*) pExtra;
			pUI->Enable(isType);
			return true;
		} else if (nCode == CN_COMMAND) {
			if (selectedObjectOfContext != NULL || selectedAnnotationOfContext != NULL) {
				// Send command using saved state
				CComPtr<IMgaNewDecorator> newDecorator;
				if (selectedObjectOfContext != NULL) {
					CGuiAspect* pAspect = selectedObjectOfContext->GetCurrentAspect();
					if (pAspect != NULL) {
						CComQIPtr<IMgaNewDecorator> newDecorator2(pAspect->GetDecorator());
						newDecorator = newDecorator2;
					}
				} else {
					newDecorator = selectedAnnotationOfContext->GetNewDecorator(currentAspect->index);
				}
				if (newDecorator) {
					isContextInitiatedOperation = true;
					if (selectedObjectOfContext != NULL)
						objectInDecoratorOperation = selectedObjectOfContext;
					else
						annotatorInDecoratorOperation = selectedAnnotationOfContext;
					CClientDC transformDC(this);
					OnPrepareDC(&transformDC);
					HRESULT retVal = newDecorator->MenuItemSelected(nID, ctxClkSt.nFlags, ctxClkSt.lpoint.x, ctxClkSt.lpoint.y,
																	(ULONGLONG)transformDC.m_hDC);
					if (retVal == S_DECORATOR_EVENT_HANDLED) {
						if (inOpenedDecoratorTransaction) {
							if (shouldCommitOperation) {
								CommitTransaction();
								shouldCommitOperation = false;
								objectInDecoratorOperation = NULL;
								annotatorInDecoratorOperation = NULL;
							} else {
								AbortTransaction(S_OK);
							}
							inOpenedDecoratorTransaction = false;
							isContextInitiatedOperation = false;
						}
					} else if (retVal != S_OK &&
								retVal != S_DECORATOR_EVENT_NOT_HANDLED &&
								retVal != E_DECORATOR_NOT_IMPLEMENTED)
					{
						CancelDecoratorOperation();
						COMTHROW(retVal);
					}
				}
			}
		}
	}
	return CScrollZoomView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CGMEView::OnEditDelete()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnEditDelete in "+path+name+"\r\n");

	GMEEVENTLOG_GUIANNOTATORS(selectedAnnotations);
	DeleteAnnotations(selectedAnnotations);
	RemoveAllAnnotationFromSelection();
	ClearConnectionSelection();

	if(!isType)
		return;

	GMEEVENTLOG_GUIOBJS(selected);
	this->SendUnselEvent4List( &selected);
	if(DeleteObjects( selected))
		selected.RemoveAll();
}

void CGMEView::OnUpdateEditDelete(CCmdUI* pCmdUI)
{
	if( !selected.IsEmpty())
		pCmdUI->Enable( isType);
	else
		pCmdUI->Enable(!selectedAnnotations.IsEmpty());
}

void CGMEView::OnContextProperties()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnContextProperties in "+path+name+"\r\n");
    if(contextSelection) {
		CGuiObject *guiObj = dynamic_cast<CGuiObject *>(contextSelection);
		if(guiObj)
			ShowProperties(guiObj);
		else {
			CGuiConnection *guiConn = dynamic_cast<CGuiConnection *>(contextSelection);
			if(guiConn)
				ShowProperties(guiConn);
		}
	}
	else
		ShowProperties();
	contextSelection = 0;
	contextPort = 0;

	/*CComPtr<IMgaFCO> fco;
	try {
		BeginTransaction();
		if(contextSelection)
			fco = contextSelection->mgaFco;
		else
			COMTHROW(currentModel.QueryInterface(&fco));

		VERIFY(fco);
		CComObjPtr<IMgaLauncher>	launcher;
		COMTHROW(launcher.CoCreateInstance(L"Mga.MgaLauncher") );

		launcher->PropDlg(fco);
		CommitTransaction();
	}
	catch(hresult_exception e) {
		AbortTransaction(e.hr);
		AfxMessageBox("Internal Program Error in CGMEView::OnContextProperties()");
		contextSelection = 0;
		return;
	}*/
}

void CGMEView::AttributepanelPage(long page)
{
	switch (page)
	{
	case 0:
		ShowAttributes();
		break;
	case 1:
		ShowPreferences();
		break;
	case 2:
		ShowProperties();
		break;
	}
}

void CGMEView::OnCntxPreferences()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxPreferences in "+path+name+"\r\n");
	if(contextSelection) {
		CGuiObject *guiObj = dynamic_cast<CGuiObject *>(contextSelection);
		if(guiObj)
			ShowPreferences(guiObj);
		else {
			CGuiConnection *guiConn = dynamic_cast<CGuiConnection *>(contextSelection);
			if(guiConn)
				ShowPreferences(guiConn);
		}
	}
	else {
		ShowPreferences();
	}

	contextSelection = 0;
	contextAnnotation = 0;
	contextPort = 0;
}

void CGMEView::OnCntxDisconnectall()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxDisconnectall in "+path+name+"\r\n");
	if(!isType)
		return;
	if(contextSelection) {
		CGuiObject *guiObj = dynamic_cast<CGuiObject *>(contextSelection);
		if(guiObj && guiObj->IsVisible()) {
			try {
				BeginTransaction();
				POSITION pos = guiObj->GetPorts().GetHeadPosition();
				while(pos) {
						DisconnectAll(guiObj,guiObj->GetPorts().GetNext(pos));
				}
				contextSelection = 0;
				contextPort = 0;
				CommitTransaction();
			}
			catch(hresult_exception e) {
				AbortTransaction(e.hr);
				AfxMessageBox("Could not complete disconnect operation",MB_OK | MB_ICONSTOP);
				CGMEEventLogger::LogGMEEvent("    Could not complete disconnect operation.\r\n");
			}
		}
	}
}

void CGMEView::OnUpdateCntxDisconnectall(CCmdUI* pCmdUI)
{
	// HACK
	pCmdUI->Enable(isType);
}

void CGMEView::OnCntxAttributes()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxAttributes in "+path+name+"\r\n");
	if(contextSelection) {
		CGuiObject *guiObj = dynamic_cast<CGuiObject *>(contextSelection);
		if(guiObj)
			ShowAttributes(guiObj);
		else {
			CGuiConnection *guiConn = dynamic_cast<CGuiConnection *>(contextSelection);
			if(guiConn)
				ShowAttributes(guiConn);
		}
	}
	else
		ShowAttributes();
	contextSelection = 0;
	contextPort = 0;
}

void CGMEView::OnUpdateCntxAttributes(CCmdUI* pCmdUI)
{
	bool enable = false;
	CGuiMetaAttributeList *metaAttrs = 0;
	try {
		BeginTransaction(TRANSACTION_READ_ONLY);
		metaAttrs = contextSelection ? contextSelection->GetMetaAttributes() : &currentAspect->attrs;
		if(metaAttrs->GetCount() > 0)
			enable = true;
		CommitTransaction();
	}
	catch(hresult_exception &e) {
		AbortTransaction(e.hr);
		AfxMessageBox("Unable to get model attributes",MB_OK | MB_ICONSTOP);
		CGMEEventLogger::LogGMEEvent("    Unable to get model attributes.\r\n");
	}
	pCmdUI->Enable(enable);
}

void CGMEView::OnEditUndo() 
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnEditUndo\r\n");
	theApp.mgaProject->Undo();
	this->SetFocus();
}

void CGMEView::OnEditRedo() 
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnEditRedo\r\n");
	theApp.mgaProject->Redo();
	this->SetFocus();
}

void CGMEView::OnEditCopy()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnEditCopy in "+path+name+"\r\n");
	if(selected.GetCount() + selectedAnnotations.GetCount() > 0) {
		GMEEVENTLOG_GUIOBJS(selected);
		GMEEVENTLOG_GUIANNOTATORS(selectedAnnotations);
		CPoint pt = CPoint(0,0);
		CRectList rects, annRects;
		CGuiObject::GetRectList(selected,rects);
		CGuiAnnotator::GetRectList(selectedAnnotations,annRects);
		CGMEDataDescriptor desc(rects,annRects,pt,pt);
		CGMEDataDescriptor::destructList( rects);
		CGMEDataDescriptor::destructList( annRects);
		GetDocument()->CopyToClipboard(&selected,&selectedAnnotations,&desc,this);
	}
}

void CGMEView::OnEditCopyClosure()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnEditCopyClosure in "+path+name+"\r\n");
	if(selected.GetCount() > 0) {
		GMEEVENTLOG_GUIOBJS(selected);
		GMEEVENTLOG_GUIANNOTATORS(selectedAnnotations);
		CPoint pt = CPoint(0,0);
		CRectList rects, annRects;
		CGuiObject::GetRectList(selected,rects);
		CGuiAnnotator::GetRectList(selectedAnnotations,annRects);
		CGMEDataDescriptor desc(rects,annRects,pt,pt);
		CGMEDataDescriptor::destructList( rects);
		CGMEDataDescriptor::destructList( annRects);
		GetDocument()->CopyClosureToClipboard( &selected, &selectedAnnotations, &desc, this);
	}
}

void CGMEView::OnEditCopySmart()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnEditCopySmart in "+path+name+"\r\n");
	if(selected.GetCount() > 0) {
		GMEEVENTLOG_GUIOBJS(selected);
		GMEEVENTLOG_GUIANNOTATORS(selectedAnnotations);
		CPoint pt = CPoint(0,0);
		CRectList rects, annRects;
		CGuiObject::GetRectList(selected,rects);
		CGuiAnnotator::GetRectList(selectedAnnotations,annRects);
		CGMEDataDescriptor desc(rects,annRects,pt,pt);
		CGMEDataDescriptor::destructList( rects);
		CGMEDataDescriptor::destructList( annRects);
		CGuiFcoList fcoList;// copy selected->selectedFco
		POSITION pos = selected.GetHeadPosition();
		while( pos != NULL ) fcoList.AddTail( selected.GetNext( pos ));

		GetDocument()->CopySmartToClipboard( &fcoList, &selectedAnnotations, &desc, this);
	}
}

void CGMEView::OnUpdateEditCopy(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(selected.GetCount() + selectedAnnotations.GetCount() > 0);
}

void CGMEView::OnUpdateEditCopyClosure(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(selected.GetCount() > 0);
}

void CGMEView::OnUpdateEditCopySmart(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(selected.GetCount() > 0);
}

void CGMEView::OnEditCut()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnEditCut in "+path+name+"\r\n");
	if(selected.GetCount() + selectedAnnotations.GetCount() > 0) {
		if(isType) GMEEVENTLOG_GUIOBJS(selected);
		GMEEVENTLOG_GUIANNOTATORS(selectedAnnotations);
		CPoint pt = CPoint(0,0);
		CRectList rects,annRects;
		if(isType) CGuiObject::GetRectList(selected,rects);
		CGuiAnnotator::GetRectList(selectedAnnotations,annRects);
		CGMEDataDescriptor desc(rects,annRects,pt,pt);
		CGMEDataDescriptor::destructList( rects);
		CGMEDataDescriptor::destructList( annRects);
		GetDocument()->CopyToClipboard(&selected,&selectedAnnotations,&desc,this);
		if(isType) DeleteObjects(selected);
		DeleteAnnotations(selectedAnnotations);
		if(isType) selected.RemoveAll();
		RemoveAllAnnotationFromSelection();
		ClearConnectionSelection();
	}
}

void CGMEView::OnUpdateEditCut(CCmdUI* pCmdUI)
{
	if( !selectedAnnotations.IsEmpty() && selected.IsEmpty())
		pCmdUI->Enable( TRUE); // allow if annotations are selected only
	else
		pCmdUI->Enable(isType && selected.GetCount() + selectedAnnotations.GetCount() > 0);
}

void CGMEView::OnEditPaste()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnEditPaste in "+path+name+"\r\n");
	if(isType) {
		COleDataObject clipboardData;
		clipboardData.AttachClipboard();
		derivedDrop = instanceDrop = false;
		DoPasteItem(&clipboardData);
	}
}

void CGMEView::OnUpdateEditPaste(CCmdUI* pCmdUI)
{
	COleDataObject dataObj;
	BOOL bEnable = isType && dataObj.AttachClipboard() &&
		((CGMEDataSource::IsGmeNativeDataAvailable(&dataObj,theApp.mgaProject)) ||
		(CGMEDataSource::IsXMLDataAvailable(&dataObj))
		);

	pCmdUI->Enable(bEnable);
}

void CGMEView::OnCntxCopy()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxCopy in "+path+name+"\r\n");
	if(contextSelection) {
		CGuiObject *guiObj = dynamic_cast<CGuiObject *>(contextSelection);
		if(guiObj) {
			CGMEEventLogger::LogGMEEvent("    "+guiObj->GetName()+" "+guiObj->GetID()+"\r\n");
			CGuiObjectList list;
			CGuiAnnotatorList dummyList;
			list.AddTail(guiObj);
			CPoint pt = CPoint(0,0);
			CRectList rects;
			CGuiObject::GetRectList(list,rects);
			CRectList dummyAnnList;
			CGMEDataDescriptor desc(rects,dummyAnnList,pt,pt);
			CGMEDataDescriptor::destructList( rects);
			GetDocument()->CopyToClipboard(&list,&dummyList,&desc,this);
		}
		contextSelection = 0;
		contextPort = 0;
	}
	else if (contextAnnotation) {
		CGMEEventLogger::LogGMEEvent("    "+contextAnnotation->GetName()+"/r/n");
		CGuiObjectList dummyList;
		CGuiAnnotatorList list;
		list.AddTail(contextAnnotation);
		CPoint pt = CPoint(0,0);
		CRectList rects;
		CGuiAnnotator::GetRectList(list,rects);
		CRectList dummyObjList;
		CGMEDataDescriptor desc(dummyObjList,rects,pt,pt);
		CGMEDataDescriptor::destructList( rects);
		GetDocument()->CopyToClipboard(&dummyList,&list,&desc,this);
		contextAnnotation = 0;
	}
}

void CGMEView::OnCntxCopyClosure()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxCopyClosure in "+path+name+"\r\n");
	if(contextSelection) {
		CGuiObject *guiObj = dynamic_cast<CGuiObject *>(contextSelection);
		if(guiObj) {
			CGMEEventLogger::LogGMEEvent("    "+guiObj->GetName()+" "+guiObj->GetID()+"\r\n");
			CGuiObjectList list;
			CGuiAnnotatorList dummyList;
			list.AddTail(guiObj);
			CPoint pt = CPoint(0,0);
			CRectList rects;
			CGuiObject::GetRectList(list,rects);
			CRectList dummyAnnList;
			CGMEDataDescriptor desc(rects,dummyAnnList,pt,pt);
			CGMEDataDescriptor::destructList( rects);
			GetDocument()->CopyClosureToClipboard( &list, &dummyList, &desc, this);
		}
		contextSelection = 0;
		contextPort = 0;
	}
	else if (contextAnnotation) {
		CGMEEventLogger::LogGMEEvent("    "+contextAnnotation->GetName()+"/r/n");
		CGuiObjectList dummyList;
		CGuiAnnotatorList list;
		list.AddTail(contextAnnotation);
		CPoint pt = CPoint(0,0);
		CRectList rects;
		CGuiAnnotator::GetRectList(list,rects);
		CRectList dummyObjList;
		CGMEDataDescriptor desc(dummyObjList,rects,pt,pt);
		CGMEDataDescriptor::destructList( rects);
		GetDocument()->CopyClosureToClipboard(&dummyList,&list,&desc,this);
		contextAnnotation = 0;
	}
}

void CGMEView::OnCntxCopySmart()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxCopySmart in "+path+name+"\r\n");
	if(contextSelection) {
		CGuiObject *guiObj = dynamic_cast<CGuiObject *>(contextSelection);
		if(guiObj) {
			CGMEEventLogger::LogGMEEvent("    "+guiObj->GetName()+" "+guiObj->GetID()+"\r\n");
			CGuiObjectList list;
			CGuiAnnotatorList dummyList;
			list.AddTail(guiObj);
			CPoint pt = CPoint(0,0);
			CRectList rects;
			CGuiObject::GetRectList(list,rects);
			CRectList dummyAnnList;
			CGMEDataDescriptor desc(rects,dummyAnnList,pt,pt);
			CGMEDataDescriptor::destructList( rects);

			CGuiFcoList fcoList;
			POSITION pos = list.GetHeadPosition();// copy list->fcoList
			while( pos != NULL ) fcoList.AddTail( list.GetNext( pos ));

			GetDocument()->CopySmartToClipboard( &fcoList, &dummyList, &desc, this);
		}
		else 
		{
			CGuiConnection *guiConn = dynamic_cast<CGuiConnection *>(contextSelection);
			if( guiConn) // a valid connection
			{
				CGMEEventLogger::LogGMEEvent("    "+guiConn->GetName()+" "+guiConn->GetID()+"\r\n");
				CGuiFcoList list;
				CGuiAnnotatorList dummyList;
				list.AddTail(guiConn);
				CPoint pt = CPoint(0,0);
				CRectList dummyRects;
				CRectList dummyAnnList;
				CGMEDataDescriptor desc(dummyRects,dummyAnnList,pt,pt);
				GetDocument()->CopySmartToClipboard( &list, &dummyList, &desc, this);
			}
		}
		contextSelection = 0;
		contextPort = 0;
	}
	else if (contextAnnotation) {
		CGMEEventLogger::LogGMEEvent("    "+contextAnnotation->GetName()+"/r/n");
		CGuiFcoList dummyList;
		CGuiAnnotatorList list;
		list.AddTail(contextAnnotation);
		CPoint pt = CPoint(0,0);
		CRectList rects;
		CGuiAnnotator::GetRectList(list,rects);
		CRectList dummyObjList;
		CGMEDataDescriptor desc(dummyObjList,rects,pt,pt);
		CGMEDataDescriptor::destructList( rects);
		GetDocument()->CopySmartToClipboard(&dummyList,&list,&desc,this);
		contextAnnotation = 0;
	}
}


void CGMEView::OnCntxCut()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxCut in "+path+name+"\r\n");
	if(isType && contextSelection) {
		CGuiObject *guiObj = dynamic_cast<CGuiObject *>(contextSelection);
		if(guiObj) {
			CGMEEventLogger::LogGMEEvent("    "+guiObj->GetName()+" "+guiObj->GetID()+"\r\n");
			CGuiObjectList list;
			CGuiAnnotatorList dummyList;
			list.AddTail(guiObj);
			CPoint pt = CPoint(0,0);
			CRectList rects;
			CGuiObject::GetRectList(list,rects);
			CRectList dummyAnnList;
			CGMEDataDescriptor desc(rects,dummyAnnList,pt,pt);
			CGMEDataDescriptor::destructList( rects);
			GetDocument()->CopyToClipboard(&list,&dummyList,&desc,this);
			DeleteObjects(list);
		}
		contextSelection = 0;
		contextPort = 0;
	}
	else if (contextAnnotation) {
		CGMEEventLogger::LogGMEEvent("    "+contextAnnotation->GetName()+"/r/n");
		CGuiObjectList dummyList;
		CGuiAnnotatorList list;
		list.AddTail(contextAnnotation);
		CPoint pt = CPoint(0,0);
		CRectList rects;
		CGuiAnnotator::GetRectList(list,rects);
		CRectList dummyObjList;
		CGMEDataDescriptor desc(dummyObjList,rects,pt,pt);
		CGMEDataDescriptor::destructList( rects);
		GetDocument()->CopyToClipboard(&dummyList,&list,&desc,this);
		DeleteAnnotations(list);
		contextAnnotation = 0;
	}
}

void CGMEView::OnUpdateCntxCut(CCmdUI* pCmdUI)
{
	if( contextAnnotation)
		pCmdUI->Enable( TRUE);
	else
		pCmdUI->Enable(isType);
}

void CGMEView::OnCntxDelete()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxDelete in "+path+name+"\r\n");
	if(isType && contextSelection) {
		CGuiObject *guiObj = dynamic_cast<CGuiObject *>(contextSelection);
		if(guiObj) {
			CGMEEventLogger::LogGMEEvent("    "+guiObj->GetName()+" "+guiObj->GetID()+"\r\n");
			CGuiObjectList list;
			list.AddTail(guiObj);
			DeleteObjects(list);
		}
		contextSelection = 0;
		contextPort = 0;
	}
	if( contextAnnotation) {
		CGMEEventLogger::LogGMEEvent("    "+contextAnnotation->GetName()+"/r/n");
		CGuiAnnotatorList list;
		list.AddTail(contextAnnotation);
		DeleteAnnotations(list);
		contextAnnotation = 0;
	}
}

void CGMEView::OnUpdateCntxDelete(CCmdUI* pCmdUI)
{
	if( contextAnnotation && !contextSelection)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(isType);
}

void CGMEView::OnSelfcntxCopy()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnSelfcntxCopy in "+path+name+"\r\n");
	OnEditCopy();
}

void CGMEView::OnUpdateSelfcntxCopy(CCmdUI* pCmdUI)
{
	OnUpdateEditCopy(pCmdUI);
}

void CGMEView::OnSelfcntxCopyClosure()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnSelfcntxCopyClosure in "+path+name+"\r\n");
	OnEditCopyClosure();
}

void CGMEView::OnSelfcntxCopySmart()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnSelfcntxCopySmart in "+path+name+"\r\n");
	OnEditCopySmart();
}

void CGMEView::OnUpdateSelfcntxCopyClosure(CCmdUI* pCmdUI)
{
	OnUpdateEditCopyClosure(pCmdUI);
}

void CGMEView::OnUpdateSelfcntxCopySmart(CCmdUI* pCmdUI)
{
	OnUpdateEditCopySmart(pCmdUI);
}

void CGMEView::OnSelfcntxCut()
{
	OnEditCut();
}

void CGMEView::OnUpdateSelfcntxCut(CCmdUI* pCmdUI)
{
	OnUpdateEditCut(pCmdUI);
}

void CGMEView::OnSelfcntxDelete()
{
	OnEditDelete();
}

void CGMEView::OnUpdateSelfcntxDelete(CCmdUI* pCmdUI)
{
	OnUpdateEditDelete(pCmdUI);
}

void CGMEView::OnSelfcntxPaste()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnSelfcntxPaste in "+path+name+"\r\n");
	if(isType) {
		COleDataObject clipboardData;
		clipboardData.AttachClipboard();
		derivedDrop = instanceDrop = false;
		DoPasteItem(&clipboardData,true,false,false,false,false,false,false,0,contextMenuLocation);
	}
}

void CGMEView::OnUpdateSelfcntxPaste(CCmdUI* pCmdUI)
{
	OnUpdateEditPaste(pCmdUI);
}

void CGMEView::OnActivateFrame( UINT nState, CFrameWnd* pFrameWnd )
{

//	CGMEView* gmeviewA = (CGMEView*)GetActiveView();
//	if (gmeviewA)
	if (m_isActive)
	{
		TRACE("CGMEView::OnActivateFrame\n");
		/*gmeviewA->*/m_refreshpannwin = true; 
	}
	CScrollZoomView::OnActivateFrame(nState, pFrameWnd);
}


void CGMEView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	CString s = bActivate ? "ACTIVATE ":"DEACTIVATE ";
	CGMEEventLogger::LogGMEEvent("CGMEView::OnActivateView "+s+path+name+"\r\n");
	//I tried logging pActivateView and pDeactiveView, but they always seemed to be "this"
	//anyways, OnActivateView is called on both views, so you would know if going from
	//one to another by the ACTIVATE/DEACTIVATE - Brian
	
	if(bActivate) {
		if( theApp.isHistoryEnabled())
		{
			GetDocument()->tellHistorian( currentModId, currentAspect?currentAspect->name:"");
		}

		modelGrid.Clear();
		FillModelGrid();
		AutoRoute();
		ClearConnSpecs();
		if(guiMeta) {
			theApp.UpdateCompList4CurrentKind( guiMeta->name);
			CMainFrame::theInstance->SetPartBrowserMetaModel(guiMeta);
			CMainFrame::theInstance->SetPartBrowserBg(bgColor);
			CMainFrame::theInstance->ChangePartBrowserAspect(currentAspect->index);
		}
	}
	else if(tmpConnectMode) {
		tmpConnectMode = false;
		ClearConnSpecs();
	}
	//comm'd by zolmol
	//CMainFrame::theInstance->UpdateTitle(theApp.projectName);

//	CGMEView * gmeviewA = (CGMEView *)pActivateView;
//	CGMEView * gmeviewI = (CGMEView *)pDeactiveView;
	if (bActivate)
		m_isActive = true;
	else 
		m_isActive = false;
	if (bActivate)
	{
//		if (gmeviewA  &&  guiMeta)
		{
			TRACE("CGMEView::OnActivateView DoPannWinRefresh\n");
			DoPannWinRefresh();
		}
	}
	TRACE("CGMEView::OnActivateView final false\n");
	m_refreshpannwin = false;
	CScrollZoomView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}


void CGMEView::OnEditCancel()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnEditCancel in "+path+name+"\r\n");
	if(tmpConnectMode) {
		tmpConnectMode = false;
		ClearConnSpecs();
		SetCursor(editCursor);
		ShowCursor(TRUE);
	}
	else {
	 	CGMEDoc *doc = GetDocument();
		if(doc->GetEditMode() == GME_AUTOCONNECT_MODE
		|| doc->GetEditMode() == GME_SHORTAUTOCONNECT_MODE) {
			ClearConnSpecs();
			SetCursor(autoconnectCursor);
			Invalidate();
		}
		else if(doc->GetEditMode() == GME_DISCONNECT_MODE
			|| doc->GetEditMode() == GME_SHORTDISCONNECT_MODE) {
			ClearConnSpecs();
			SetCursor(disconnectCursor);
			Invalidate();
		}
	}
}

void CGMEView::OnUpdateEditCancel(CCmdUI* pCmdUI)
{
 	CGMEDoc *doc = GetDocument();
	pCmdUI->Enable(((doc->GetEditMode() == GME_AUTOCONNECT_MODE || doc->GetEditMode() == GME_SHORTAUTOCONNECT_MODE) && connSrc) ||
					((doc->GetEditMode() == GME_DISCONNECT_MODE || doc->GetEditMode() == GME_SHORTDISCONNECT_MODE) && connSrc));

}

BOOL CGMEView::PreTranslateMessage(MSG* pMsg)
{
	ASSERT( m_hWnd != NULL && theApp.m_GMEView_hAccel != NULL && pMsg != NULL );
	if( TranslateAccelerator(m_hWnd, theApp.m_GMEView_hAccel, pMsg) )
		return TRUE;

	return CScrollZoomView::PreTranslateMessage(pMsg);
}

void CGMEView::OnFileClose()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnFileClose() in "+path+name+"\r\n");
	frame->sendEvent = true;
	frame->PostMessage(WM_CLOSE);
}

void CGMEView::OnFileInterpret()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnFileInterpret in "+path+name+"\r\n");
	RunComponent("");
}

void CGMEView::RunComponent(CString compname)
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnRunComponent "+compname+" in "+path+name+"\r\n");
	CGMEEventLogger::LogGMEEvent("    Selected FCOs:");
	GMEEVENTLOG_GUIFCOS(selected);
	MSGTRY
	{
		CComObjPtr<IMgaLauncher> launcher;
		COMTHROW( launcher.CoCreateInstance(L"Mga.MgaLauncher") );
		if(!launcher) {
			AfxMessageBox("Cannot start up component launcher");
			CGMEEventLogger::LogGMEEvent("    Cannot start up component launcher.\r\n");
		}
		else {
			CComPtr<IMgaFCO> focus;
			CComPtr<IMgaFCOs> selfcos;
			COMTHROW(selfcos.CoCreateInstance(OLESTR("Mga.MgaFCOs")));
			COMTHROW(currentModel.QueryInterface(&focus));
			POSITION pos = selected.GetHeadPosition();
			while (pos) {
				CGuiFco *gfco = selected.GetNext(pos);
				COMTHROW(selfcos->Append(gfco->mgaFco));
			}

			if(theApp.bNoProtect) COMTHROW( launcher->put_Parameter(CComVariant(true)));
			if(launcher->RunComponent(NULL, theApp.mgaProject, focus, selfcos, GME_MAIN_START) != S_OK) {
				AfxMessageBox("Component execution failed");
				CGMEEventLogger::LogGMEEvent("    Component execution failed.\r\n");
			}
		}
	}
	MSGCATCH("Error while trying to run the interpreter",;)
}

void CGMEView::SetEditCursor(void)
{
	SetCursor(editCursor);
	isCursorChangedByDecorator = false;
}

void CGMEView::CancelDecoratorOperation(bool notify)
{
	if (inNewDecoratorOperation) {
		if (::GetCapture() != NULL)
			::ReleaseCapture();
		shouldCommitOperation = false;
		if (originalRect.IsRectEmpty() == FALSE) {
			if (decoratorOrAnnotator)
				objectInDecoratorOperation->ResizeObject(originalRect);
//			else
//				annotatorInDecoratorOperation->ResizeObject(originalRect);
			Invalidate();
			originalRect.SetRectEmpty();
		}
		inNewDecoratorOperation = false;
		if (isCursorChangedByDecorator)
			SetEditCursor();
		if (notify) {
			CComPtr<IMgaNewDecorator> newDecorator;
			if (objectInDecoratorOperation != NULL) {
				CGuiAspect* pAspect = objectInDecoratorOperation->GetCurrentAspect();
				if (pAspect != NULL) {
					CComQIPtr<IMgaNewDecorator> newDecorator2(pAspect->GetDecorator());
					newDecorator2 = newDecorator;
				}
			} else if (annotatorInDecoratorOperation != NULL) {
				newDecorator = annotatorInDecoratorOperation->GetNewDecorator(currentAspect->index);
			}
			if (newDecorator)
				HRESULT retVal = newDecorator->OperationCanceled();
		}
		objectInDecoratorOperation = NULL;
		annotatorInDecoratorOperation = NULL;
		isContextInitiatedOperation = false;
	}
	if (inOpenedDecoratorTransaction) {
		AbortTransaction(S_OK);
		inOpenedDecoratorTransaction = false;
	}
}

void CGMEView::OnConncntxProperties()
{
	OnContextProperties(); // We now use the Launcher COM interface.
}

void CGMEView::OnConncntxDelete()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnConncntxDelete in "+path+name+"\r\n");
	if(isType) {
		CGuiConnection *conn = dynamic_cast<CGuiConnection *>(contextSelection);
		if(!conn || !DeleteConnection(conn))
			AfxMessageBox("Connection cannot be deleted!");
		contextSelection = 0;
		contextPort = 0;
	}
}

void CGMEView::OnUpdateConncntxDelete(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(isType);
}

void CGMEView::OnShowContextMenu() // called from Accelerators like SHIFT+F10 or Property (VK_APPS)
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnShowContextMenu in "+path+name+"\r\n");

	CGMEDoc *doc = GetDocument();
	if( doc && doc->GetEditMode() == GME_EDIT_MODE)
	{
		CRect cr;// GetWindowRect( &cr);
		GetClientRect( &cr);
		ClientToScreen( &cr);
		CPoint global( cr.TopLeft() + CPoint( 10, 10));
		if( selected.GetCount() > 0)
		{
			CGuiObject* head = selected.GetHead();
			CPoint local = !head? CPoint( 0, 0): head->GetLocation().TopLeft();//GetCenter()); // overwrite the menu's topleft placement

			// reverse CoordinateTransfer
			CClientDC fernst(this);
			(const_cast<CGMEView *>(this))->OnPrepareDC(&fernst);
			fernst.LPtoDP( &local);

			global.Offset( local);
			CMenu menu;
			menu.LoadMenu( dynamic_cast< CGuiConnection *>( head)? IDR_CONNCONTEXT_MENU: IDR_CONTEXT_MENU);
			menu.GetSubMenu( 0)->TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON, global.x, global.y, GetParent());
		}
		else if( selectedAnnotations.GetCount() > 0)
		{
			CGuiAnnotator* head = selectedAnnotations.GetHead();
			CPoint local = !head? CPoint( 0, 0): head->GetLocation().TopLeft();

			// reverse CoordinateTransfer
			CClientDC fernst(this);
			(const_cast<CGMEView *>(this))->OnPrepareDC(&fernst);
			fernst.LPtoDP( &local);

			global.Offset( local); // overwrite the menu's topleft placement
			CMenu menu;
			menu.LoadMenu( IDR_ANNCONTEXT_MENU);
			menu.GetSubMenu( 0)->TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON, global.x, global.y, GetParent());
		}
		else
		{
			CMenu menu;
			menu.LoadMenu( IDR_SELFCONTEXT_MENU);
			CMenu *submenu = menu.GetSubMenu( 0);
			currentAspect->InitContextMenu( submenu);
			submenu->TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON, global.x, global.y, GetParent());
			currentAspect->ResetContextMenu( submenu);
		}
	}
}

void CGMEView::OnJumpToFirstObject()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnJumpToFirstObject in "+path+name+"\r\n");

	CGuiObject* first = FindFirstObject();

	if( first && first->mgaFco && CGMEDoc::theInstance)
	{
		CGMEDoc::theInstance->ShowObject( CComPtr<IUnknown>( first->mgaFco), TRUE);
	}
}

void CGMEView::OnJumpToNextObject()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnJumpToNextObject in "+path+name+"\r\n");

	CGuiObject* next = FindNextObject();

	if( next && next->mgaFco && CGMEDoc::theInstance)
	{
		CGMEDoc::theInstance->ShowObject( CComPtr<IUnknown>( next->mgaFco), TRUE);
	}
}

void CGMEView::OnConnCntxFollow() // 'Go to Dst' context command of a connection 
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnConnCntxFollow in "+path+name+"\r\n");
	if(contextSelection) {
		CGuiConnection *conn = dynamic_cast<CGuiConnection *>(contextSelection);
		FollowLine( conn, false, ::GetKeyState( VK_CONTROL) < 0);
		contextSelection = 0;
		contextPort = 0;
	}
}

void CGMEView::OnConnCntxRevfollow() // 'Go to Src' context command of a connection
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnConnCntxRevfollow in "+path+name+"\r\n");
	if(contextSelection) {
		CGuiConnection *conn = dynamic_cast<CGuiConnection *>(contextSelection);
		FollowLine( conn, true, ::GetKeyState( VK_CONTROL) < 0);
		contextSelection = 0;
		contextPort = 0;
	}
}

void CGMEView::OnPortCntxFollowConnection() // 'Follow Connection' context command of a port
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnPortCntxFollowConnection in "+path+name+"\r\n");
	if( contextPort)
	{
		FollowLine( contextPort, false, ::GetKeyState( VK_CONTROL) < 0);
		contextSelection = 0;
		contextPort = 0;
	}
}

void CGMEView::OnPortCntxRevfollowConnection() // 'Follow Reverse Connection' context command of a port
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxRevfollowConnection in "+path+name+"\r\n");
	if( contextPort)
	{
		FollowLine( contextPort, true, ::GetKeyState( VK_CONTROL) < 0);
		contextSelection = 0;
		contextPort = 0;
	}
}

void CGMEView::OnCntxFollowConnection() // 'Follow Connection' context command of an fco
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxFollowConnection in "+path+name+"\r\n");
	if( selected.GetCount() > 0)
		FollowLine( selected.GetHead(), false, ::GetKeyState( VK_CONTROL) < 0);
}

void CGMEView::OnCntxRevfollowConnection() // 'Follow Reverse Connection' context command of an fco
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxRevfollowConnection in "+path+name+"\r\n");
	if( selected.GetCount() > 0)
		FollowLine( selected.GetHead(), true, ::GetKeyState( VK_CONTROL) < 0);
}

void CGMEView::OnCntxPortShowInParent() // 'Show Port in Parent' context command of a PORT
{
	if( !contextPort) return;
	
	CGMEDoc::theInstance->ShowObject( CComPtr<IUnknown>( contextPort->mgaFco), TRUE);
	contextPort = 0;
}

void CGMEView::OnCntxPortLocateInBrw() // 'Locate Port in Browser' context command of a PORT
{
	if( !contextPort) return;

	CGMEBrowser::theInstance->FocusItem( CComBSTR( contextPort->id));
	contextPort = 0;
}

void CGMEView::OnJumpAlongConnection() // 'Jump Along Conn' command on the Navigation toolbar
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnJumpAlongConnection in "+path+name+"\r\n");
	if( selected.GetCount() > 0)
		FollowLine( selected.GetHead(), false, ::GetKeyState( VK_CONTROL) < 0);
}

void CGMEView::OnBackAlongConnection() // 'Jump back Along Conn' on Navigation toolbar
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnBackAlongConnection in "+path+name+"\r\n");
	if( selected.GetCount() > 0)
		FollowLine( selected.GetHead(), true, ::GetKeyState( VK_CONTROL) < 0);
}

bool jumpToSelectedEnd( CGuiConnectionList& p_collOfConns, bool p_reverse, bool p_tryPort)
{
	int hmany = p_collOfConns.GetCount();

	if( hmany > 0)
	{
		CGuiConnection*     a_conn       = p_collOfConns.GetHead();
		CGuiFco*            a_neighbor   = a_conn? p_reverse? a_conn->src: a_conn->dst: 0;
		CGuiPort*           a_port       = a_conn? p_reverse? a_conn->srcPort: a_conn->dstPort: 0;

		if( hmany > 1)
		{
			CConnityDlg dlg( p_reverse);
			dlg.setList( p_collOfConns);
			if( IDOK != dlg.DoModal())
				return false;

			a_conn     = dlg.getSelectedC(); // owerwrite with the selected one (if > 1)
			a_neighbor = a_conn? p_reverse? a_conn->src: a_conn->dst: 0;
			a_port     = a_conn? p_reverse? a_conn->srcPort: a_conn->dstPort: 0;
		}
			
		if( a_neighbor)
		{
			if( p_tryPort && a_port && a_port->IsRealPort())
				CGMEDoc::theInstance->ShowObject( CComPtr<IUnknown>( a_port->mgaFco), TRUE);
			else
				CGMEDoc::theInstance->ShowObject( CComPtr<IUnknown>( a_neighbor->mgaFco), TRUE);
			return true;
		}
	}
	return false;
}

bool CGMEView::FollowLine( CGuiConnection *p_guiConn, bool p_reverse, bool p_tryPort)
{
	if( !p_guiConn) 
		return false;

	CGuiConnectionList curr_conns;
	curr_conns.AddTail( p_guiConn);

	return jumpToSelectedEnd( curr_conns, p_reverse, p_tryPort);
}

bool CGMEView::FollowLine( CGuiPort* p_guiPort, bool p_reverse, bool p_tryPort)
{
	if( !p_guiPort)
		return false;

	CGuiConnectionList& curr_conns = p_reverse? p_guiPort->inConns: p_guiPort->outConns;
	return jumpToSelectedEnd( curr_conns, p_reverse, p_tryPort);
}

bool CGMEView::FollowLine( CGuiObject* p_guiObj, bool p_reverse, bool p_tryPort)
{
	if( !p_guiObj)
		return false;

	CGuiConnectionList curr_conns;
	p_guiObj->GetRelationsInOut( curr_conns, p_reverse);
	return jumpToSelectedEnd( curr_conns, p_reverse, p_tryPort);
}

bool areConnsForSels( CGuiObjectList& p_sels, bool p_inOrOut)
{
	CGuiConnectionList conn_list;
	if( p_sels.GetCount() == 1)
	{
		CGuiObject* head = p_sels.GetHead();
		if( head) head->GetRelationsInOut( conn_list, p_inOrOut);
	}
	return conn_list.GetCount() > 0;
}

bool areConnsForPort( CGuiPort* p_contextPort, bool p_inOrOut)
{
	return p_contextPort && (p_inOrOut? p_contextPort->inConns: p_contextPort->outConns).GetCount() > 0;
}

void CGMEView::OnUpdatePortCntxFollowConnection( CCmdUI* pCmdUI)
{
	pCmdUI->Enable( areConnsForPort( contextPort, false));
}

void CGMEView::OnUpdatePortCntxRevfollowConnection( CCmdUI* pCmdUI)
{
	pCmdUI->Enable( areConnsForPort( contextPort, true));
}

void CGMEView::OnUpdateCntxFollowConnection( CCmdUI* pCmdUI)
{
	pCmdUI->Enable( areConnsForSels( selected, false));
}

void CGMEView::OnUpdateCntxRevfollowConnection( CCmdUI* pCmdUI)
{
	pCmdUI->Enable( areConnsForSels( selected, true));
}

void CGMEView::OnUpdateJumpAlongConnection(CCmdUI* pCmdUI)
{
	pCmdUI->Enable( areConnsForSels( selected, false));
}

void CGMEView::OnUpdateBackAlongConnection(CCmdUI* pCmdUI)
{
	pCmdUI->Enable( areConnsForSels( selected, true));
}

#if defined(ADDCRASHTESTMENU)
void CGMEView::OnCrashTestIllegalWrite(void) 
{
	CrashTest::IllegalWrite();
}

void CGMEView::OnCrashTestIllegalRead(void) 
{
	CrashTest::IllegalRead();
}

void CGMEView::OnCrashTestIllegalReadInCRuntime(void) 
{
	CrashTest::IllegalReadInCRuntime();
}

void CGMEView::OnCrashTestIllegalCodeRead(void) 
{
	CrashTest::IllegalCodeRead();
}

void CGMEView::OnCrashTestDivideByZero(void) 
{
	CrashTest::DivideByZero();
}

void CGMEView::OnUpdateCrashTestMenu(CCmdUI* pCmdUI)
{
	pCmdUI->Enable();
}

void CGMEView::OnUpdateCrashTestIllegalWrite(CCmdUI* pCmdUI)
{
	pCmdUI->Enable();
}

void CGMEView::OnUpdateCrashTestIllegalRead(CCmdUI* pCmdUI)
{
	pCmdUI->Enable();
}

void CGMEView::OnUpdateCrashTestIllegalReadInCRuntime(CCmdUI* pCmdUI)
{
	pCmdUI->Enable();
}

void CGMEView::OnUpdateCrashTestIllegalCodeRead(CCmdUI* pCmdUI)
{
	pCmdUI->Enable();
}

void CGMEView::OnUpdateCrashTestDivideByZero(CCmdUI* pCmdUI)
{
	pCmdUI->Enable();
}
#endif

void CGMEView::OnCntxClear()	// set refs to null, delete all members from set
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxClear in "+path+name+"\r\n");
	if(!isType)
		return;
	CGuiObject *obj = dynamic_cast<CGuiReference *>(contextSelection);
	if(!obj)
		obj = dynamic_cast<CGuiCompoundReference *>(contextSelection);
	if(obj) {
		try {
			CGMEEventLogger::LogGMEEvent("    "+obj->GetName()+" "+obj->GetID()+"\r\n");
			BeginTransaction();
			CComPtr<IMgaReference> mgaRef;
			COMTHROW(obj->mgaFco.QueryInterface(&mgaRef));
			CComPtr<IMgaFCO> nullFco;
			COMTHROW(mgaRef->put_Referred(nullFco));
			CommitTransaction();
		}
		catch(hresult_exception e) {
			AbortTransaction(e.hr);
			const char* t1 = "Cannot clear reference because of active connections!";
			const char* t2 = "Cannot clear reference.";
			if( e.hr == E_MGA_REFPORTS_USED)
			{
				if( !CGMEConsole::theInstance) AfxMessageBox( t1);
				else CGMEConsole::theInstance->Message( t1, MSG_ERROR);
			}
			else
				if( !CGMEConsole::theInstance) AfxMessageBox( t2);
				else CGMEConsole::theInstance->Message( t2, MSG_ERROR);
		}
	}
	else {
		CGuiSet *set = dynamic_cast<CGuiSet *>(contextSelection);
		if(set) {
			try {
				CGMEEventLogger::LogGMEEvent("    "+set->GetName()+" "+set->GetID()+"\r\n");
				BeginTransaction();
				CComPtr<IMgaSet> mgaSet;
				COMTHROW(set->mgaFco.QueryInterface(&mgaSet));
				COMTHROW(mgaSet->RemoveAll());
				CommitTransaction();
			}
			catch(hresult_exception e) {
				AbortTransaction(e.hr);
			}
		}
	}
}

void CGMEView::OnUpdateCntxClear(CCmdUI* pCmdUI)
{
	CGuiObject *obj = dynamic_cast<CGuiReference *>(contextSelection);
	if(!obj)
		obj = dynamic_cast<CGuiCompoundReference *>(contextSelection);
	if(!obj)
		obj = dynamic_cast<CGuiSet *>(contextSelection);
	pCmdUI->Enable(isType && obj != 0);
}

void CGMEView::OnCntxReset()	// revert to base i.e. reestablish dependency chain for refs and sets
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxReset in "+path+name+"\r\n");
	CGuiObject *obj = dynamic_cast<CGuiReference *>(contextSelection);
	if(!obj)
		obj = dynamic_cast<CGuiCompoundReference *>(contextSelection);
	if(obj) {
		try {
			CGMEEventLogger::LogGMEEvent("    "+obj->GetName()+" "+obj->GetID()+"\r\n");
			BeginTransaction();
			CComPtr<IMgaReference> mgaRef;
			COMTHROW(obj->mgaFco.QueryInterface(&mgaRef));
			COMTHROW(mgaRef->RevertToBase());
			CommitTransaction();
		}
		catch(hresult_exception e) {
			AbortTransaction(e.hr);
		}
	}
	else {
		CGuiSet *set = dynamic_cast<CGuiSet *>(contextSelection);
		if(set) {
			try {
				CGMEEventLogger::LogGMEEvent("    "+set->GetName()+" "+set->GetID()+"\r\n");
				BeginTransaction();
				CComPtr<IMgaSet> mgaSet;
				COMTHROW(set->mgaFco.QueryInterface(&mgaSet));
				COMTHROW(mgaSet->RevertToBase());
				CommitTransaction();
			}
			catch(hresult_exception e) {
				AbortTransaction(e.hr);
			}
		}
	}
}

void CGMEView::OnUpdateCntxReset(CCmdUI* pCmdUI)
{
	CGuiObject *obj = dynamic_cast<CGuiReference *>(contextSelection);
	if(!obj)
		obj = dynamic_cast<CGuiCompoundReference *>(contextSelection);
	if(!obj)
		obj = dynamic_cast<CGuiSet *>(contextSelection);
	pCmdUI->Enable(baseType != 0 && obj != 0);
}

void CGMEView::OnEditPreferences()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnEditPreferences in "+path+name+"\r\n");
	ShowPreferences();
}

void CGMEView::OnHelpHelp()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnHelpHelp in "+path+name+"\r\n");
	CComPtr<IMgaFCO> fco;
	POSITION pos = selected.GetHeadPosition();
	if( pos) // if any object selected
	{
		CGuiObject *obj = selected.GetAt( pos);
		CGMEEventLogger::LogGMEEvent("CGMEView::OnHelpHelp for selected: "+obj->GetID()+"\r\n");
		fco = obj->mgaFco;
	}
	else
		COMTHROW(currentModel.QueryInterface(&fco));

	ShowHelp(fco);
}

void CGMEView::OnCntxHelp()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxHelp in "+path+name+"\r\n");
	CComPtr<IMgaFCO> fco;
	if(contextSelection)
	{
		CGMEEventLogger::LogGMEEvent("    "+contextSelection->GetName()+" "+contextSelection->GetID()+"\r\n");
		fco = contextSelection->mgaFco;
	}
	else
		currentModel.QueryInterface(&fco);

	ShowHelp(fco);

	contextSelection = 0;
	contextPort = 0;
}



void CGMEView::OnEditShowtype()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnEditShowtype in "+path+name+"\r\n");
	contextSelection = 0;	// just to be on the safe side
	contextPort = 0;
	CComPtr<IMgaModel> type;
	FindDerivedFrom(currentModel,type);
	ShowModel(type);
	contextSelection = 0;
}

void CGMEView::OnUpdateEditShowtype(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!isType);
}

void CGMEView::OnEditShowbasetype()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnShowbasetype in "+path+name+"\r\n");
	CComPtr<IMgaModel> type;
	FindDerivedFrom(currentModel,type);
	ShowModel(type);
	contextSelection = 0;
	contextPort = 0;
}

void CGMEView::OnUpdateEditShowbasetype(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(isSubType);
}

void CGMEView::OnCntxShowtype()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxShowtype in "+path+name+"\r\n");
	CComPtr<IMgaModel> model;
	GetModelInContext(model);
	CComPtr<IMgaModel> type;
	FindDerivedFrom(model,type);
	ShowModel(type);
	contextSelection = 0;
	contextPort = 0;
}

void CGMEView::OnUpdateCntxShowtype(CCmdUI* pCmdUI)
{
	bool type = (contextSelection ? contextSelection->IsType() : isType);
	bool model = (contextSelection ? (dynamic_cast<CGuiModel *>(contextSelection) != 0) : true);
	pCmdUI->Enable(model && !type);
}

void CGMEView::OnCntxShowbasetype()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxShowbasetype in "+path+name+"\r\n");
	CComPtr<IMgaModel> model;
	GetModelInContext(model);
	CComPtr<IMgaModel> type;
	FindDerivedFrom(model,type);
	ShowModel(type);
	contextSelection = 0;
	contextPort = 0;
}

void CGMEView::OnUpdateCntxShowbasetype(CCmdUI* pCmdUI)
{
	bool ok = false;
	bool type = contextSelection ? contextSelection->IsType() : isType;
	bool model = (contextSelection ? (dynamic_cast<CGuiModel *>(contextSelection) != 0) : true);
	if(type && model) {
		CComPtr<IMgaModel> model;
		GetModelInContext(model);
		CComPtr<IMgaModel> type;
		FindDerivedFrom(model,type);
		ok = (type != 0);
	}
	pCmdUI->Enable(ok);
}


void CGMEView::OnUpdateFileCheck(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(theApp.mgaConstMgr != NULL);
	// TODO: Add your command update UI handler code here

}

void CGMEView::OnUpdateFileCheckSelected(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(theApp.mgaConstMgr != NULL && selected.GetCount());
}

void CGMEView::OnFileCheck()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnFileCheck in "+path+name+"\r\n");
	if(currentModel)
	{
		// message boxes displayed from constraint manager if in interactive mode
		theApp.mgaConstMgr->ObjectsInvokeEx(theApp.mgaProject, currentModel, NULL, NULL);
	}
	else
		AfxMessageBox("No context selection for CM.");
}


void CGMEView::OnFileCheckSelected()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnFileCheckSelected in "+path+name+"\r\n");
	GMEEVENTLOG_GUIOBJS(selected);
	POSITION pos = selected.GetHeadPosition();
	if(pos)
	{

#if(0)   // while we cannot add connections
		while(pos) {
			theApp.mgaConstMgr->ObjectsInvokeEx(
					theApp.mgaProject,
					selected.GetNext(pos)->mgaFco,
					NULL, NULL);
		}
#else
		CComPtr<IMgaFCOs> fcos;
		if(CGMEDoc::CreateFcoList(&selected,fcos,this)) {
			MGACOLL_ITERATE(IMgaFCO, fcos) {
				theApp.mgaConstMgr->ObjectsInvokeEx(
						theApp.mgaProject,
						MGACOLL_ITER,
						NULL, NULL);
			} MGACOLL_ITERATE_END;
		}
#endif
	}
	else
		AfxMessageBox("No context selection for CM.");
}

void CGMEView::OnCntxCheck()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxCheck\r\n");
	CGMEEventLogger::LogGMEEvent("    Selected FCOs:");
	GMEEVENTLOG_GUIFCOS(selected);

	ASSERT(theApp.mgaConstMgr);
	if(!theApp.mgaConstMgr) 
		return;

	MSGTRY
	{
		CComPtr<IMgaFCO> selfco;

		if (selected.IsEmpty())
			selfco = currentModel;
		else
		{
			POSITION pos = selected.GetHeadPosition();
			selfco = selected.GetNext(pos)->mgaFco;
		}
		theApp.mgaConstMgr->ObjectsInvokeEx(theApp.mgaProject, selfco, NULL, NULL);
	}
	MSGCATCH("Error while trying to check the selected or current model",;)
}

void CGMEView::OnCntxInterpret()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxInterpret in "+path+name+"\r\n");
	CGMEEventLogger::LogGMEEvent("    Selected FCOs:");
	GMEEVENTLOG_GUIFCOS(selected);
	MSGTRY
	{
		CComObjPtr<IMgaLauncher> launcher;
		COMTHROW( launcher.CoCreateInstance(L"Mga.MgaLauncher") );
		if(!launcher) {
			AfxMessageBox("Cannot start up component launcher");
		}
		else {
			CComPtr<IMgaFCO> focus;
			CComPtr<IMgaFCOs> selfcos;
			COMTHROW(selfcos.CoCreateInstance(OLESTR("Mga.MgaFCOs")));
			COMTHROW(currentModel.QueryInterface(&focus));
			POSITION pos = selected.GetHeadPosition();
			while (pos) {
				CGuiFco *gfco = selected.GetNext(pos);
				COMTHROW(selfcos->Append(gfco->mgaFco));
			}

			if(theApp.bNoProtect) COMTHROW( launcher->put_Parameter(CComVariant(true)));
			if(launcher->RunComponent(NULL, theApp.mgaProject, focus, selfcos, contextSelection ? GME_CONTEXT_START :  GME_BGCONTEXT_START) != S_OK) {
				AfxMessageBox("Component execution failed");
			}
		}
	}
	MSGCATCH("Error while trying to run the interpreter",;)
}

void CGMEView::OnCntxLocate()
{
	// ?? 
	// position the Object Browser to the selected or current object
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxLocate\r\n");
	CGMEEventLogger::LogGMEEvent("    Selected FCO:");
	GMEEVENTLOG_GUIFCOS(selected);

	MSGTRY
	{
		CComPtr<IMgaFCO> selfco;

		if (selected.IsEmpty())
			selfco = currentModel;
		else
		{
			POSITION pos = selected.GetHeadPosition();
			selfco = selected.GetNext(pos)->mgaFco;
		}
		BeginTransaction(TRANSACTION_READ_ONLY);
		BSTR IDObj = NULL;
		selfco->get_ID(&IDObj);
		CommitTransaction();
		CGMEBrowser::theInstance->FocusItem(IDObj);
	}
	MSGCATCH("Error while trying to check the selected or current model",;)
}

void CGMEView::OnUpdateCntxCheck(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!selected.IsEmpty()  ||  currentModel != NULL); 
}

void CGMEView::OnUpdateCntxInterpret(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!selected.IsEmpty());
}

void CGMEView::OnUpdateCntxLocate(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!selected.IsEmpty()  ||  currentModel != NULL); 
}

void CGMEView::OnCntxRegistry()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxRegistry in "+path+name+"\r\n");
	CComPtr<IMgaFCO> fco;
	if(contextSelection)
	{
		CGMEEventLogger::LogGMEEvent("    "+contextSelection->GetName()+" "+contextSelection->GetID()+"\r\n");
		fco = contextSelection->mgaFco;
	}
	else
		currentModel.QueryInterface(&fco);

	ShowRegistryBrowser(fco);

	contextSelection = 0;
	contextPort = 0;

}

void CGMEView::OnEditRegistry()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnEditRegistry in "+path+name+"\r\n");
	CComPtr<IMgaFCO> fco;
	COMTHROW(currentModel.QueryInterface(&fco));
	ShowRegistryBrowser(fco);
}

void CGMEView::OnEditAnnotations()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnEditAnnotations in "+path+name+"\r\n");
	CComPtr<IMgaFCO> fco;
	COMTHROW(currentModel.QueryInterface(&fco));
	ShowAnnotationBrowser(fco, NULL);
}


void CGMEView::ShowRegistryBrowser(CComPtr<IMgaFCO> fco)
{
	CGMEEventLogger::LogGMEEvent("CGMEView::ShowRegistryBrowser in "+path+name+"\r\n");
	try {
		BeginTransaction();

		CComObjPtr<IMgaLauncher> launcher;
		COMTHROW( launcher.CoCreateInstance(L"Mga.MgaLauncher") );
		COMTHROW( launcher->RegistryBrowser(fco) );
		CommitTransaction();
	}
	catch(hresult_exception &e) {
		AbortTransaction(e.hr);
		AfxMessageBox("Unable to access object registry",MB_OK | MB_ICONSTOP);
		CGMEEventLogger::LogGMEEvent("    Unable to access object registry.\r\n");
	}
}

void CGMEView::ShowAnnotationBrowser(CComPtr<IMgaFCO> fco, CComPtr<IMgaRegNode> focus)
{
	CGMEEventLogger::LogGMEEvent("CGMEView::ShowAnnotationBrowser in "+path+name+"\r\n");
	try {
		BeginTransaction();
		CComObjPtr<IMgaLauncher> launcher;
		COMTHROW( launcher.CoCreateInstance(L"Mga.MgaLauncher") );
		COMTHROW( launcher->AnnotationBrowser(fco, focus) );
		CommitTransaction();
	}
	catch(hresult_exception &e) {
		AbortTransaction(e.hr);
		AfxMessageBox("Unable to access annotations",MB_OK | MB_ICONSTOP);
		CGMEEventLogger::LogGMEEvent("    Unable to access annotations.\r\n");
	}
}

void CGMEView::OnEditSync()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnEditSync in "+path+name+"\r\n");
	CAspectSyncDlg dlg;

	POSITION apos = guiMeta->aspects.GetHeadPosition();
	dlg.m_srcAspect = (apos ? guiMeta->aspects.GetAt(apos) : NULL);
	while (apos) {
		CGuiMetaAspect *metaAspect = guiMeta->aspects.GetNext(apos);
		dlg.m_allAspects.AddTail(metaAspect);

		if (currentAspect == metaAspect) {
			dlg.m_dstAspects.AddTail(metaAspect);
		}
	}

	POSITION opos = children.GetHeadPosition();
	while (opos) {
		CGuiObject	*obj = dynamic_cast<CGuiObject*>(children.GetNext(opos));

		if (!obj) {
			// It is a connection
			continue;
		}

		bool isMoving;
		if (selected.GetCount() > 0)
			isMoving = (selected.Find(obj) != NULL);
		else
			isMoving = obj->IsVisible();

		dlg.m_allObjects.AddTail(obj);
		if (isMoving)
			dlg.m_movingObjects.AddTail(obj);
	}


	if (dlg.DoModal() == IDOK) {
		CGuiMetaAspectList dstAspects;
		CGuiMetaAspect*    srcAspect;
		CGuiObjectList	   movingObjects;
		CGuiObjectList	   sedentaryObjects;

		dstAspects.AddTail(&dlg.m_dstAspects);
		srcAspect = dlg.m_srcAspect;
		movingObjects.AddTail(&dlg.m_movingObjects);


		POSITION opos = dlg.m_allObjects.GetHeadPosition();
		while (opos) {
			CGuiObject* obj = (CGuiObject*)dlg.m_allObjects.GetNext(opos);
			if (!dlg.m_movingObjects.Find(obj))
				sedentaryObjects.AddTail(obj);
		}
		SyncAspects(srcAspect, dstAspects, movingObjects, sedentaryObjects, dlg.m_priorityForSrcVisible == TRUE, dlg.m_priorityForSelected == TRUE);
	}
}

void CGMEView::OnUpdateEditSync(CCmdUI* pCmdUI)
{
	pCmdUI->Enable((guiMeta->aspects.GetCount()>1));
}


void CGMEView::SyncAspects(CGuiMetaAspect *srcAspect, CGuiMetaAspectList &dstAspects, CGuiObjectList &movingObjects, CGuiObjectList &sedentaryObjects,  bool priorityForSrcVisible, bool priorityForSelected)
{
	CGMEEventLogger::LogGMEEvent("CGMEView::SyncAspects in "+path+name+"\r\n");
	if(srcAspect)
		CGMEEventLogger::LogGMEEvent("    srcAspect="+srcAspect->name+"\r\n");
	CGMEEventLogger::LogGMEEvent("    moving objects:");
	GMEEVENTLOG_GUIOBJS(movingObjects);
	CGMEEventLogger::LogGMEEvent("    sedentary objects:");
	GMEEVENTLOG_GUIOBJS(sedentaryObjects);
	CGMEEventLogger::LogGMEEvent("    dstAspects:\r\n");
	try {
		BeginTransaction(TRANSACTION_GENERAL);
		BeginWaitCursor();

		modelGrid.SetSource(this);

		POSITION apos = dstAspects.GetHeadPosition();
		while (apos) {
			CGuiMetaAspect *dstAspect = dstAspects.GetNext(apos);
			if (dstAspect == srcAspect)
				continue;
			CGMEEventLogger::LogGMEEvent("    "+dstAspect->name+"\r\n");

			modelGrid.Clear();

			POSITION pos;

			if (!priorityForSelected) {
				pos = sedentaryObjects.GetHeadPosition();
				while (pos) {
					CGuiObject *obj = sedentaryObjects.GetNext(pos);
					if (obj->IsVisible(dstAspect->index)) {
						SyncOnGrid(obj, dstAspect->index, dstAspect->index);
					}
				}
			}

			CGuiObjectList	lowPriorityObjects;
			pos = movingObjects.GetHeadPosition();
			while (pos) {
				CGuiObject *obj = movingObjects.GetNext(pos);
				if (obj->IsVisible(dstAspect->index)) {
					if (priorityForSrcVisible) {
						if (obj->IsVisible(srcAspect->index)) {
							SyncOnGrid(obj, srcAspect->index, dstAspect->index);
						}
						else {
							lowPriorityObjects.AddTail(obj);
						}

					}
					else {
						if (obj->IsVisible(srcAspect->index)) {
							lowPriorityObjects.AddTail(obj);
						}
						else {
							SyncOnGrid(obj, dstAspect->index, dstAspect->index);
						}
					}
				}
			}

			pos = lowPriorityObjects.GetHeadPosition();
			while (pos) {
				CGuiObject *obj = lowPriorityObjects.GetNext(pos);
				if (priorityForSrcVisible) {
					SyncOnGrid(obj, dstAspect->index, dstAspect->index);
				}
				else {
					SyncOnGrid(obj, srcAspect->index, dstAspect->index);
				}
			}

			if (priorityForSelected) {
				pos = sedentaryObjects.GetHeadPosition();
				while (pos) {
					CGuiObject *obj = sedentaryObjects.GetNext(pos);
					if (obj->IsVisible(dstAspect->index)) {
						SyncOnGrid(obj, dstAspect->index, dstAspect->index);
					}
				}
			}
		}

		needsReset = true;
		EndWaitCursor();
		CommitTransaction();
	}
	catch(hresult_exception &e) {
		AbortTransaction(e.hr);
		AfxMessageBox("Unable to synchronize aspects",MB_OK | MB_ICONSTOP);
		CGMEEventLogger::LogGMEEvent("    Unable to synchronize aspects.\r\n");
		EndWaitCursor();
		return;
	}

}

void CGMEView::SyncOnGrid(CGuiObject *obj, int aspectIndexFrom, int aspectIndexTo)
{
	// aspectIndexTo might be equal with aspectIndexFrom
	CPoint center = obj->GetLocation(aspectIndexFrom).CenterPoint();//take the pos from the aspFrom (source) aspect

	if (!modelGrid.IsAvailable(obj, aspectIndexFrom)) {//is enough space to occupy the pos taken from the aspFrom aspect?
		if (!modelGrid.GetClosestAvailable(obj, center, aspectIndexTo)) { // if cannot get any position close to the position got above
			AfxMessageBox("Too Many Models! Internal Program Error!",MB_OK | MB_ICONSTOP);
			throw hresult_exception();
		}
	}
	obj->SetCenter(center, aspectIndexTo);
	modelGrid.Set(obj, FALSE, aspectIndexTo);
}


void CGMEView::OnEditSelectall()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnEditSelectall in "+path+name+"\r\n");
	this->SendUnselEvent4List( &selected);
	selected.RemoveAll();
	RemoveAllAnnotationFromSelection();
	ClearConnectionSelection();
	POSITION pos = children.GetHeadPosition();
	while(pos) {
		CGuiObject *obj = dynamic_cast<CGuiObject *>(children.GetNext(pos));
		if(obj && obj->IsVisible()) {
			this->SendSelecEvent4Object( obj);
			selected.AddTail(obj);
		}
	}

	GMEEVENTLOG_GUIOBJS(selected);

	pos = annotators.GetHeadPosition();
	while(pos) {
		CGuiAnnotator *ann = annotators.GetNext(pos);
		if (ann->IsVisible()) {
			AddAnnotationToSelectionTail(ann);
		}
	}

	GMEEVENTLOG_GUIANNOTATORS(selectedAnnotations);
	Invalidate();
	this->SendNow();
}


void CGMEView::OnUpdateFileClose(CCmdUI* pCmdUI)
// we use File/Close Model, because the dynamic menus are always used together with this one.
{
	theApp.UpdateDynMenus(pCmdUI->m_pMenu);
}

void CGMEView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	CScrollZoomView::OnPrepareDC(pDC, pInfo);

	if (pDC->IsPrinting()) 
	{
		PrepareAspectPrn(pInfo);
/*
		pDC->SetMapMode(MM_ISOTROPIC);
		CRect extent, objext, annext;
		CGuiObject::GetExtent(children,objext);
		CGuiAnnotator::GetExtent(annotators,annext);
		extent.UnionRect(&objext, &annext);
		pDC->SetWindowExt(extent.right, extent.bottom);
		double w, h;
		w = GetDeviceCaps(pDC->m_hDC,PHYSICALWIDTH) - 4*GetDeviceCaps(pDC->m_hDC,PHYSICALOFFSETX);
		h = GetDeviceCaps(pDC->m_hDC,PHYSICALHEIGHT)- 4*GetDeviceCaps(pDC->m_hDC,PHYSICALOFFSETY);
		pDC->SetViewportExt((int)w, (int)h);
*/
	}
}

void CGMEView::OnEditPastespecialAssubtype()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnEditPastespecialAssubtype in "+path+name+"\r\n");
	if(isType) {
		COleDataObject clipboardData;
		clipboardData.AttachClipboard();
		derivedDrop = instanceDrop = false;
		DoPasteItem(&clipboardData,false,false,false,true,false);
	}
}

void CGMEView::OnEditPastespecialAsinstance()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnEditPastespecialAsinstance in "+path+name+"\r\n");
	if(isType) {
		COleDataObject clipboardData;
		clipboardData.AttachClipboard();
		derivedDrop = instanceDrop = false;
		DoPasteItem(&clipboardData,false,false,false,true,true);
	}
}

void CGMEView::OnEditPastespecialAsreference()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnEditPastespecialAsreference in "+path+name+"\r\n");
	if(isType) {
		COleDataObject clipboardData;
		clipboardData.AttachClipboard();
		derivedDrop = instanceDrop = false;
		DoPasteItem(&clipboardData,false,false,true);
	}
}

void CGMEView::OnEditPastespecialAsclosure()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnEditPastespecialAsclosure in "+path+name+"\r\n");
	if(isType) {
		COleDataObject clipboardData;
		clipboardData.AttachClipboard();
		derivedDrop = instanceDrop = false;
		DoPasteItem(&clipboardData,false,false,false,false,false,true, false);
	}
}

void CGMEView::OnEditPastespecialAdditive()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnEditPastespecialAdditive in "+path+name+"\r\n");
	if(isType) {
		COleDataObject clipboardData;
		clipboardData.AttachClipboard();
		derivedDrop = instanceDrop = false;
		DoPasteItem(&clipboardData,false,false,false,false,false,true, false);
	}
}

void CGMEView::OnEditPastespecialMerge()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnEditPastespecialMerge in "+path+name+"\r\n");
	if(isType) {
		COleDataObject clipboardData;
		clipboardData.AttachClipboard();
		derivedDrop = instanceDrop = false;
		DoPasteItem(&clipboardData,false,false,false,false,false,true, true);
	}
}

void CGMEView::OnUpdateEditPastespecialAsinstance(CCmdUI* pCmdUI)
{
	OnUpdateEditPaste(pCmdUI);
}

void CGMEView::OnUpdateEditPastespecialAsreference(CCmdUI* pCmdUI)
{
	OnUpdateEditPaste(pCmdUI);
}

void CGMEView::OnUpdateEditPastespecialAssubtype(CCmdUI* pCmdUI)
{
	OnUpdateEditPaste(pCmdUI);
}

void CGMEView::OnUpdateEditPastespecialAsclosure(CCmdUI* pCmdUI)
{
	OnUpdateEditPaste(pCmdUI);
}

void CGMEView::OnUpdateEditPastespecialAdditive(CCmdUI* pCmdUI)
{
	OnUpdateEditPaste(pCmdUI);
}

void CGMEView::OnUpdateEditPastespecialMerge(CCmdUI* pCmdUI)
{
	OnUpdateEditPaste(pCmdUI);
}

void CGMEView::OnCntxPastespecialAsinstance()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxPastespecialAsinstance in "+path+name+"\r\n");
	if(isType) {
		COleDataObject clipboardData;
		clipboardData.AttachClipboard();
		derivedDrop = instanceDrop = true;
		DoPasteItem(&clipboardData,true,false,false,true,true,false,false,0,contextMenuLocation);
	}
}

void CGMEView::OnUpdateCntxPastespecialAsinstance(CCmdUI* pCmdUI)
{
	OnUpdateEditPaste(pCmdUI);
}

void CGMEView::OnCntxPastespecialAsreference()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxPastespecialAsreference in "+path+name+"\r\n");
	if(isType) {
		COleDataObject clipboardData;
		clipboardData.AttachClipboard();
		derivedDrop = instanceDrop = false;
		DoPasteItem(&clipboardData,true,false,true,false,false,false,false,0,contextMenuLocation);
	}
}

void CGMEView::OnUpdateCntxPastespecialAsreference(CCmdUI* pCmdUI)
{
	OnUpdateEditPaste(pCmdUI);
}

void CGMEView::OnCntxPastespecialAssubtype()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxPastespecialAssubtype in "+path+name+"\r\n");
	if(isType) {
		COleDataObject clipboardData;
		clipboardData.AttachClipboard();
		derivedDrop = true;
		instanceDrop = false;
		DoPasteItem(&clipboardData,true,false,false,true,false,false,false,0,contextMenuLocation);
	}
}

void CGMEView::OnUpdateCntxPastespecialAssubtype(CCmdUI* pCmdUI)
{
	OnUpdateEditPaste(pCmdUI);
}

void CGMEView::OnCntxPastespecialAsclosure()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxPastespecialAsclosure in "+path+name+"\r\n");
	if(isType) {
		COleDataObject clipboardData;
		clipboardData.AttachClipboard();
		derivedDrop = true;
		instanceDrop = false;
		DoPasteItem(&clipboardData,false,false,false,false,false,true,false,0,contextMenuLocation);
	}
}

void CGMEView::OnUpdateCntxPastespecialAsclosure(CCmdUI* pCmdUI)
{
	OnUpdateEditPaste(pCmdUI);
}

void CGMEView::OnCntxPastespecialAdditive()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxPastespecialAdditive in "+path+name+"\r\n");
	if(isType) {
		COleDataObject clipboardData;
		clipboardData.AttachClipboard();
		derivedDrop = true;
		instanceDrop = false;
		DoPasteItem(&clipboardData,false,false,false,false,false,true,false,0,contextMenuLocation);
	}
}

void CGMEView::OnUpdateCntxPastespecialAdditive(CCmdUI* pCmdUI)
{
	OnUpdateEditPaste(pCmdUI);
}

void CGMEView::OnCntxPastespecialMerge()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxPastespecialMerge in "+path+name+"\r\n");
	if(isType) {
		COleDataObject clipboardData;
		clipboardData.AttachClipboard();
		derivedDrop = true;
		instanceDrop = false;
		DoPasteItem(&clipboardData,false,false,false,false,false,true,true,0,contextMenuLocation);
	}
}

void CGMEView::OnUpdateCntxPastespecialMerge(CCmdUI* pCmdUI)
{
	OnUpdateEditPaste(pCmdUI);
}

void CGMEView::OnCntxRedirectionpaste()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxRedirectionpaste in "+path+name+"\r\n");
	if(isType && contextSelection) {
		CGuiObject *ref = dynamic_cast<CGuiReference *>(contextSelection);
		if(!ref)
			ref = dynamic_cast<CGuiCompoundReference *>(contextSelection);
		if(ref) {
			COleDataObject clipboardData;
			clipboardData.AttachClipboard();
			derivedDrop = instanceDrop = false;
			DoPasteItem(&clipboardData,true,false,true,false,false,false,false,ref,contextMenuLocation);
		}
	}
}

void CGMEView::OnUpdateCntxRedirectionpaste(CCmdUI* pCmdUI)
{
	BOOL bEnable = (contextSelection != 0);
	CGuiObject *ref = dynamic_cast<CGuiReference *>(contextSelection);
	if(!ref)
		ref = dynamic_cast<CGuiCompoundReference *>(contextSelection);
	bEnable = bEnable && (ref != 0);
	COleDataObject dataObj;
	bEnable = bEnable && dataObj.AttachClipboard() &&
		(CGMEDataSource::IsGmeNativeDataAvailable(&dataObj,theApp.mgaProject));

	pCmdUI->Enable(bEnable);
}

void CGMEView::OnCntxConnect()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxConnect in "+path+name+"\r\n");
	if(contextSelection) {
		CGuiObject *obj = dynamic_cast<CGuiObject *>(contextSelection);
		if(obj) {
			CGuiPort *port = obj->FindPort(contextMenuLocation);
			if(connSrc == 0) {
				connSrc = obj;
				connSrcPort = port;
				connSrcHotSide = GME_CENTER;
				tmpConnectMode = true;
				SetCursor(autoconnect2Cursor);
			}
			else {
				Connect(connSrc,connSrcPort,connSrcHotSide,obj,port, GME_CENTER, ::GetKeyState(VK_SHIFT) < 0);
				ClearConnSpecs();
				tmpConnectMode = false;
				SetCursor(editCursor);
			}
			ShowCursor(TRUE);
		}
	}
}

void CGMEView::OnUpdateCntxConnect(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GetDocument()->GetEditMode() == GME_EDIT_MODE);
}

void CGMEView::OnResetSticky()
{
	CGMEDoc *doc = GetDocument();
	if(doc && doc->resolver) {
		COMTHROW(doc->resolver->Clear());
	}
}

void CGMEView::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	if (nHitTest != HTCLIENT && !inNewDecoratorOperation && isCursorChangedByDecorator)
		SetEditCursor();
}

void CGMEView::OnMouseMove(UINT nFlags, CPoint screenpoint)
{
	CGMEView *self = const_cast<CGMEView *>(this);
	CPoint point(screenpoint);
	CoordinateTransfer(point);

	if( theApp.isMouseOverNotifyEnabled()/* && GetDocument()->GetEditMode() == GME_EDIT_MODE*/) {
		//static CGuiObject *lastObject = 0;
		CGuiObject *object = self  ?self->FindObject(point):0;
		CGuiPort   *port   = object?object->FindPort(point):0;
		if(object) {
			if( object != lastObject)
				this->SendMouseOver4Object( object);
		}
		lastObject = object;
		lastPort   = port;
	}

	if (GetDocument()->GetEditMode() == GME_EDIT_MODE) { // new decorator notification logic
		//static CGuiObject* lastObject = 0;
		CGuiObject*	object	= self		? self->FindObject(point, true) : 0;
		CGuiPort*	port	= object	? object->FindPort(point, true) : 0;
		if (object == NULL)
			object = self ? self->FindObject(point, true, true) : 0;
		CGuiAnnotator* annotation = FindAnnotation(point);

		if (inNewDecoratorOperation) {
			CComPtr<IMgaNewDecorator> newDecorator;
			if (decoratorOrAnnotator) {
				ASSERT(objectInDecoratorOperation != NULL);
				CGuiAspect* pAspect = objectInDecoratorOperation->GetCurrentAspect();
				if (pAspect != NULL) {
					CComQIPtr<IMgaNewDecorator> newDecorator2(pAspect->GetDecorator());
					newDecorator = newDecorator2;
				}
			} else {
				ASSERT(annotatorInDecoratorOperation != NULL);
				newDecorator = annotatorInDecoratorOperation->GetNewDecorator(currentAspect->index);
			}
			if (newDecorator) {
				CClientDC transformDC(this);
				OnPrepareDC(&transformDC);
				HRESULT retVal = newDecorator->MouseMoved(nFlags, point.x, point.y, (ULONGLONG)transformDC.m_hDC);
				if (retVal == S_DECORATOR_EVENT_HANDLED) {
					CScrollZoomView::OnMouseMove(nFlags, screenpoint);
					return;
				} else if (retVal != S_OK &&
						   retVal != S_DECORATOR_EVENT_NOT_HANDLED &&
						   retVal != E_DECORATOR_NOT_IMPLEMENTED)
				{
					CancelDecoratorOperation();
					COMTHROW(retVal);
				}
			}
		} else if (object != NULL || annotation != NULL) {
			CComPtr<IMgaNewDecorator> newDecorator;
			if (object != NULL) {
				CGuiAspect* pAspect = object->GetCurrentAspect();
				if (pAspect != NULL) {
					CComQIPtr<IMgaNewDecorator> newDecorator2(pAspect->GetDecorator());
					newDecorator = newDecorator2;
				}
			} else {
				ASSERT(annotation != NULL);
				newDecorator = annotation->GetNewDecorator(currentAspect->index);
			}
			if (newDecorator) {
				CClientDC transformDC(this);
				OnPrepareDC(&transformDC);
				HRESULT retVal = newDecorator->MouseMoved(nFlags, point.x, point.y, (ULONGLONG)transformDC.m_hDC);
				if (retVal == S_DECORATOR_EVENT_HANDLED) {
					CScrollZoomView::OnMouseMove(nFlags, screenpoint);
					return;
				} else if (retVal != S_OK &&
						   retVal != S_DECORATOR_EVENT_NOT_HANDLED &&
						   retVal != E_DECORATOR_NOT_IMPLEMENTED)
				{
					CancelDecoratorOperation();
					COMTHROW(retVal);
				}
			}
		} else {
			if (isCursorChangedByDecorator)
				SetEditCursor();
		}
	}

	if (GetDocument()->GetEditMode() == GME_VISUAL_MODE)
	{
		CGuiObject *object = self? self->FindObject(point): 0;
		// if object found, curr_Connection will be 0
		CGuiConnection        *curr_Connection = object? 0: router.FindConnection( point);
		static CGuiConnection *last_Connection = 0;
		if( last_Connection != curr_Connection) // state change for at most two connections
		{
			if( last_Connection) last_Connection->ToggleHover(); // if a previous was selected, now it will become unselected
			if( curr_Connection) curr_Connection->ToggleHover(); // toggle the new one
			last_Connection = curr_Connection;
			Invalidate();
		} 
	}
	if ((GetDocument()->GetEditMode() == GME_AUTOCONNECT_MODE || GetDocument()->GetEditMode() == GME_SHORTAUTOCONNECT_MODE) || (tmpConnectMode)) {
		CGuiObject *object = self->FindObject(point);
		if(object) {
			CRect rect = object->GetLocation();
			CGuiPort *port = object->FindPort(point);
			int hotSide = GME_CENTER;
			if(port && port->IsRealPort()) {
				rect = port->GetLocation() + rect.TopLeft();
			}
			else {
				port = NULL;

				if (object->IsHotspotEnabled()) {
					int mx = rect.CenterPoint().x;
					int my = rect.CenterPoint().y;
					int hsRadx = GME_HOTSPOT_RADIUS;
					int hsRady = GME_HOTSPOT_RADIUS;
					if (rect.Width() < (GME_HOTSPOT_RADIUS * 3)) {
						hsRadx = rect.Width()/3;
					}
					if (rect.Height() < (GME_HOTSPOT_RADIUS * 3)) {
						hsRady = rect.Height()/3;
					}
					if ( abs(point.x - mx) < hsRadx) {
						if ( abs(point.y - rect.top) < hsRady ) {
							hotSide = GME_NORTH;
						}
						if ( abs(point.y - rect.bottom) < hsRady ) {
							hotSide = GME_SOUTH;
						}
					}
					else if ( abs(point.y - my) < hsRady) {
						if ( abs(point.x - rect.left) < hsRadx ) {
							hotSide = GME_WEST;
						}
						if ( abs(point.x - rect.right) < hsRadx ) {
							hotSide = GME_EAST;
						}
					}
				}
			}

			if((object != connTmp) || (port != connTmpPort) || (hotSide != connTmpHotSide)) {
					connTmp = object;
					connTmpPort = port;
					connTmpHotSide = hotSide;
					Invalidate();
			}
		}
		else {
			connTmp = NULL;
			connTmpPort = NULL;
			connTmpHotSide = GME_CENTER;
			Invalidate();
		}
	}

	CScrollZoomView::OnMouseMove(nFlags, screenpoint);
}

void CGMEView::ClearConnSpecs()
{
	connSrc = NULL;
	connSrcPort = NULL;
	connSrcHotSide = GME_CENTER;
	connTmp = NULL;
	connTmpPort = NULL;
	connTmpHotSide = GME_CENTER;
}

void CGMEView::OnTimer(UINT nIDEvent)
{
	if (nIDEvent == GME_ANIM_EVENT_ID) {
		Invalidate();
	}
	CScrollZoomView::OnTimer(nIDEvent);
}

void CGMEView::OnUpdateCntxInsertannotation(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CGMEView::OnCntxInsertannotation()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxInsertannotation in "+path+name+"\r\n");
	CComPtr<IMgaRegNode> rootReg;
	try {
		BeginTransaction();
		int annID = 0;
		bool found = false;

		while (!found) {
			rootReg = NULL;
			CString path;
			path.Format("%s/%s%d", AN_ROOT, AN_DEFANNOTATION_NAME, annID++);
			CComBSTR bstr(path);
			COMTHROW(currentModel->get_RegistryNode(bstr, &rootReg));
			long status;
			COMTHROW(rootReg->get_Status(&status));
			if (status == ATTSTATUS_UNDEFINED) {
				found = true;
			}
		}

		CComBSTR value(AN_DEFAULTANNOTATION_TXT);
		COMTHROW(rootReg->put_Value(value));

		CComPtr<IMgaRegNode> aspRoot;
		CComBSTR aspName(AN_ASPECTS);
		COMTHROW(rootReg->get_SubNodeByName(aspName, &aspRoot));
		CString pos;
		pos.Format("%d,%d", contextMenuLocation.x, contextMenuLocation.y);
		CComBSTR posval(pos);
		COMTHROW(aspRoot->put_Value(posval));

		CComPtr<IMgaRegNode> defAspNode;
		CComBSTR defAspName(AN_DEFASPECT);
		COMTHROW(aspRoot->get_SubNodeByName(defAspName, &defAspNode));
		CComBSTR bstrVis(AN_VISIBLE_DEFAULT);
		COMTHROW(defAspNode->put_Value(bstrVis));

		CComPtr<IMgaFCO> fcoToShow;
		currentModel.QueryInterface(&fcoToShow);

		ShowAnnotationBrowser(fcoToShow, rootReg);

		// ANNTODO: new object id list
		CommitTransaction();
	}
	catch(hresult_exception &e) {
		AbortTransaction(e.hr);
		AfxMessageBox("Unable to insert annotation",MB_ICONSTOP | MB_OK);
		CGMEEventLogger::LogGMEEvent("    Unable to insert annotation.\r\n");
		return;
	}
	Invalidate(true);
}

void CGMEView::OnCntxAnnotations()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxAnnotations in "+path+name+"\r\n");
	CComPtr<IMgaFCO> fco;
	currentModel.QueryInterface(&fco);
	ShowAnnotationBrowser(fco, contextAnnotation ? contextAnnotation->rootNode : NULL);
	contextAnnotation = NULL;
	contextSelection = NULL;
}

void CGMEView::OnUpdateCntxAutoRouters( CCmdUI* pCmdUI )
{
	pCmdUI->Enable();
	if ( contextSelection ) {
		CComPtr<IMgaFCO> spFCO = contextSelection->mgaFco;
		if ( spFCO ) {
			BeginTransaction(TRANSACTION_READ_ONLY);
			CComBSTR bstrPref;
			COMTHROW( spFCO->get_RegistryValue( CComBSTR( "autorouterPref" ), &bstrPref ) );
			CommitTransaction();
			CString strPref( bstrPref );
			switch ( pCmdUI->m_nID ) {
				case ID_CNTX_SRCAR_NORTH : 	pCmdUI->SetCheck( ( strPref.Find( "N" ) != -1 ) ? 1 : 0 ); return;
				case ID_CNTX_SRCAR_SOUTH : 	pCmdUI->SetCheck( ( strPref.Find( "S" ) != -1 ) ? 1 : 0 ); return;
				case ID_CNTX_SRCAR_WEST :	pCmdUI->SetCheck( ( strPref.Find( "W" ) != -1 ) ? 1 : 0 ); return;
				case ID_CNTX_SRCAR_EAST :	pCmdUI->SetCheck( ( strPref.Find( "E" ) != -1 ) ? 1 : 0 ); return;
				case ID_CNTX_DSTAR_NORTH :	pCmdUI->SetCheck( ( strPref.Find( "n" ) != -1 ) ? 1 : 0 ); return;
				case ID_CNTX_DSTAR_SOUTH :	pCmdUI->SetCheck( ( strPref.Find( "s" ) != -1 ) ? 1 : 0 ); return;
				case ID_CNTX_DSTAR_WEST :	pCmdUI->SetCheck( ( strPref.Find( "w" ) != -1 ) ? 1 : 0 ); return;
				case ID_CNTX_DSTAR_EAST :	pCmdUI->SetCheck( ( strPref.Find( "e" ) != -1 ) ? 1 : 0 ); return;
			}
			int iCnt = 0;
			bool bSet = pCmdUI->m_nID == ID_CNTX_SRCAR_SET || pCmdUI->m_nID == ID_CNTX_DSTAR_SET;
			CString str = ( pCmdUI->m_nID == ID_CNTX_SRCAR_SET || pCmdUI->m_nID == ID_CNTX_SRCAR_CLEAR ) ? "NEWS" : "news";
			for ( int i = 0 ; i < 4 ; i++ )
				if ( strPref.Find( str.Mid( i, 1 ) ) != -1 ) iCnt++;
			if ( iCnt == 4 && bSet || iCnt == 0 && ! bSet )
				pCmdUI->Enable( FALSE );
		}
	}
}

void CGMEView::OnCntxSrcarSouth()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxSrcarSouth in "+path+name+"\r\n");
	SwapAutoRouterPref( "S" );
}

void CGMEView::OnCntxSrcarNorth()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxSrcarNorth in "+path+name+"\r\n");
	SwapAutoRouterPref( "N" );
}

void CGMEView::OnCntxSrcarEast()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxSrcarEast in "+path+name+"\r\n");
	SwapAutoRouterPref( "E" );
}

void CGMEView::OnCntxSrcarWest()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxSrcarWest in "+path+name+"\r\n");
	SwapAutoRouterPref( "W" );
}

void CGMEView::OnCntxDstarEast()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxDstarEast in "+path+name+"\r\n");
	SwapAutoRouterPref( "e" );
}

void CGMEView::OnCntxDstarNorth()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxDstarNorth in "+path+name+"\r\n");
	SwapAutoRouterPref( "n" );
}

void CGMEView::OnCntxDstarSouth()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxDstarSouth in "+path+name+"\r\n");
	SwapAutoRouterPref( "s" );
}

void CGMEView::OnCntxDstarWest()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxDstarWest in "+path+name+"\r\n");
	SwapAutoRouterPref( "w" );
}

void CGMEView::OnCntxDstarClear()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxDstarClear in "+path+name+"\r\n");
	SetAllAutoRouterPref( false, true );
}

void CGMEView::OnCntxSrcarClear()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxSrcarClear in "+path+name+"\r\n");
	SetAllAutoRouterPref( true, true );
}

void CGMEView::OnCntxDstarSet()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxDstarSet in "+path+name+"\r\n");
	SetAllAutoRouterPref( false, false );
}

void CGMEView::OnCntxSrcarSet()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnCntxSrcarSet in "+path+name+"\r\n");
	SetAllAutoRouterPref( true, false );
}

void CGMEView::SwapAutoRouterPref( const CString& strP )
{
	CGMEEventLogger::LogGMEEvent("CGMEView::SwapAutoRouterPref in "+path+name+"\r\n");
	if( contextSelection ) {
		CGMEEventLogger::LogGMEEvent("    "+contextSelection->GetName()+" "+contextSelection->GetID()+"\r\n");
		CComPtr<IMgaFCO> spFCO = contextSelection->mgaFco;
		if ( spFCO ) {
			BeginTransaction(TRANSACTION_GENERAL);
			CComBSTR bstrPref;
			COMTHROW( spFCO->get_RegistryValue( CComBSTR( "autorouterPref" ), &bstrPref ) );
			CString strPref( bstrPref );
			int iPos = strPref.Find( strP );
			if ( iPos == -1 )
				if ( strP == "n" || strP == "s" || strP == "w" || strP == "e" )
					strPref = strP + strPref;
				else
					strPref += strP;
			else
				strPref.Replace( strP, "" );
			COMTHROW( spFCO->put_RegistryValue( CComBSTR( "autorouterPref" ), CComBSTR( strPref ) ) );
			CommitTransaction();
		}
	}
}

void CGMEView::SetAllAutoRouterPref( bool bSrc, bool bClear )
{
	CGMEEventLogger::LogGMEEvent("CGMEView::SetAllAutoRouterPref in "+path+name+"\r\n");
	if( contextSelection ) {
		CGMEEventLogger::LogGMEEvent("    "+contextSelection->GetName()+" "+contextSelection->GetID()+"\r\n");
		CComPtr<IMgaFCO> spFCO = contextSelection->mgaFco;
		if ( spFCO ) {
			BeginTransaction(TRANSACTION_GENERAL);
			CComBSTR bstrPref;
			COMTHROW( spFCO->get_RegistryValue( CComBSTR( "autorouterPref" ), &bstrPref ) );
			CString strPref( bstrPref );
			CString src = "NEWS";
			CString dst = "news";
			for ( int i = 0 ; i < 4 ; i++ )
				strPref.Replace( ( bSrc ) ? src.Mid( i, 1 ) : dst.Mid( i, 1 ), "" );
			if ( ! bClear )
				if ( bSrc )
					strPref = src + strPref;
				else
					strPref += dst;
			COMTHROW( spFCO->put_RegistryValue( CComBSTR( "autorouterPref" ), CComBSTR( strPref ) ) );
			CommitTransaction();
		}
	}
}

void CGMEView::OnPrintMetafile() 
{
	CString filePath = ""; // "c:\\tmp\\meta.emf";
	// call FileOpenDialog
	CFileDialog filedlg(FALSE, "emf", NULL, OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,
		"Enhanced Metafile Files (*.emf)|*.emf|All Files (*.*)|*.*||");
	if (filedlg.DoModal() != IDOK)
		return;
	filePath = filedlg.GetPathName();
	CMetaFileDC cDC;
	BOOL ret = cDC.CreateEnhanced(GetDC(),filePath,NULL,_T("GME Model"));
	if (ret == FALSE) {
		AfxMessageBox("Unable to create metafile.", MB_OK | MB_ICONSTOP);
		return;
	}

	cDC.m_bPrinting = TRUE;		// HACK by Peter (c)

	OnDraw(&cDC);

	HENHMETAFILE hEmf = cDC.CloseEnhanced();
	if ( hEmf ) {
		DeleteEnhMetaFile(hEmf);
	}
}

void CGMEView::ZoomRect(CRect srect)
{
	CRect crect;
	GetClientRect(&crect);
	int curzoom = m_zoomVal;
	CPoint home = CPoint(srect.left, srect.top);
	CSize orisize_srect(srect.Width(), srect.Height());
	srect.OffsetRect(-home);

	// convert srect to client coordinates like extent
	{
		CWindowDC dc(NULL);
		dc.SetMapMode(MM_ISOTROPIC);
		dc.SetWindowExt(100,100);
		dc.SetViewportExt(curzoom, curzoom);
		dc.DPtoLP(&srect);
	}
	int zoom = (int)min(100.*crect.Height()/srect.Height(), 100.*crect.Width()/srect.Width());
	m_zoomVal = (zoom<ZOOM_MIN)? ZOOM_MIN: ((zoom>ZOOM_MAX)? ZOOM_MAX: zoom);

	if (m_zoomVal != curzoom)
		frame->propBar.SetZoomVal(m_zoomVal);
	CMainFrame::theInstance->WriteStatusZoom(m_zoomVal);
	m_zoomP.x = m_zoomP.y = 0;
	if (curzoom == m_zoomVal)
		return;

	CPoint point = home;
	point.x += orisize_srect.cx/2;
	point.y += orisize_srect.cy/2;

// prevous zoom value : curzoom
// new zoom value stored in m_zoomVal
// point : win client coordinates - this image point has to be centered
	SetZoomPoint(curzoom, point);
	Invalidate();
}

void CGMEView::ZoomToFCOs(CRect srect)
{
	// perform a zoom to that rectangle
	CRect crect;
	GetClientRect(&crect);
	CSize sizeSb;
	GetScrollBarSizes(sizeSb);
	if (m_noHscroll)	// let's suppose it will be after zoom
		crect.bottom -= sizeSb.cy; 
	if (m_noVscroll)	// let's suppose it will be
		crect.right -= sizeSb.cx;

	int curzoom = m_zoomVal;
	CRect ori_proj = srect;
	srect.OffsetRect(-CPoint(srect.left, srect.top));

	int zoom = (int)min(100.*crect.Height()/srect.Height(), 100.*crect.Width()/srect.Width());
	m_zoomVal = (zoom<ZOOM_MIN)? ZOOM_MIN: ((zoom>ZOOM_MAX)? ZOOM_MAX: zoom);

	if (m_zoomVal != curzoom)
		frame->propBar.SetZoomVal(m_zoomVal);
	CMainFrame::theInstance->WriteStatusZoom(m_zoomVal);
	m_zoomP.x = m_zoomP.y = 0;

	CPoint scp = GetScrollPosition();       // upper corner of scrolling

	{
		CWindowDC dc(NULL);
		dc.SetMapMode(MM_ISOTROPIC);
		dc.SetWindowExt(100,100);
		dc.SetViewportExt(curzoom, curzoom);
		dc.LPtoDP(&ori_proj);
		dc.LPtoDP(&scp);
	}
	CPoint home = CPoint(ori_proj.left, ori_proj.top);
	CSize orisize_srect(ori_proj.Width(), ori_proj.Height());

	CPoint point = home - scp;
	point.x += orisize_srect.cx/2;
	point.y += orisize_srect.cy/2;

// prevous zoom value : curzoom
// new zoom value stored in m_zoomVal
// point : win client coordinates - this image point has to be centered
	SetZoomPoint(curzoom, point);
	Invalidate();
}

void CGMEView::OnZoomIn()
{
	int zoom = m_zoomVal+5;
	zoom = (zoom<ZOOM_MIN)? ZOOM_MIN: ((zoom>ZOOM_MAX)? ZOOM_MAX: zoom);
	ZoomPercent( zoom);
}

void CGMEView::OnZoomOut()
{
	int zoom = m_zoomVal-5;
	zoom = (zoom<ZOOM_MIN)? ZOOM_MIN: ((zoom>ZOOM_MAX)? ZOOM_MAX: zoom);
	ZoomPercent( zoom);
}

void CGMEView::ZoomPercent(long percent)
{
	OnZoom(0, (LPARAM)percent);
}

LRESULT CGMEView::OnZoom(WPARAM, LPARAM lParam)
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnZoom() in "+path+name+"\r\n");
	// BOOL userdef = (BOOL)wParam;
	int zoom = (int)lParam;

	// zoom it 
	if (zoom > 0)
	{
		int curzoom = m_zoomVal;
		m_zoomVal = (zoom<ZOOM_MIN)? ZOOM_MIN: ((zoom>ZOOM_MAX)? ZOOM_MAX: zoom);
		if (m_zoomVal != zoom)
			frame->propBar.SetZoomVal(m_zoomVal);
		CMainFrame::theInstance->WriteStatusZoom(m_zoomVal);
		m_zoomP.x = m_zoomP.y = 0;
		if (curzoom == m_zoomVal)
			return 0;

		CPoint point;
		CRect client(0,0,0,0);
		GetClientRect(&client);

		CRect rect;
		GetClientRect(&rect);

		CRect objext, annext, extent;
		CGuiObject::GetExtent(children, objext);
		CGuiAnnotator::GetExtent(annotators, annext);
		extent.UnionRect(&objext, &annext);
		extent.right = (int)(extent.right*EXTENT_ERROR_CORR); // ??
		extent.bottom = (int)(extent.bottom*EXTENT_ERROR_CORR); // ??
		CSize s(extent.right, extent.bottom);

		CWindowDC dc(NULL);
		dc.SetMapMode(MM_ISOTROPIC);
		dc.SetWindowExt(100,100);
		dc.SetViewportExt(curzoom, curzoom);
		CPoint expoint(extent.right, extent.bottom);
		dc.LPtoDP((LPPOINT)&expoint);

		point.x = (expoint.x < client.Width())? point.x = expoint.x/2 :point.x = client.Width()/2;
		point.y = (expoint.y < client.Height())? point.y = expoint.y/2 :point.y = client.Height()/2;
		
		SetZoomPoint(curzoom, point);
		frame->propBar.SetZoomVal(m_zoomVal);
		CMainFrame::theInstance->WriteStatusZoom(m_zoomVal);
		Invalidate();
	}
	else
	{
		CRect rect;
		GetClientRect(&rect);

		CRect objext, annext, extent;
		CGuiObject::GetExtent(children, objext);
		CGuiAnnotator::GetExtent(annotators, annext);
		extent.UnionRect(&objext, &annext);
		extent.right = (int)(extent.right*EXTENT_ERROR_CORR); // ??
		extent.bottom = (int)(extent.bottom*EXTENT_ERROR_CORR); // ??
		CSize s(extent.right, extent.bottom);
//		s.cx = s.cx + END_SCROLL_OFFSET;
//		s.cy = s.cy + END_SCROLL_OFFSET;
		switch (zoom)
		{
		case ZOOM_WIDTH:
			m_zoomVal = (int)(100.*rect.Width()/s.cx);
			break;
		case ZOOM_HEIGHT:
			m_zoomVal = (int)(100.*rect.Height()/s.cy);
			break;
		case ZOOM_ALL:
			m_zoomVal = (int)min(100.*rect.Height()/s.cy, 100.*rect.Width()/s.cx);
			break;
		}
		frame->propBar.SetZoomVal(m_zoomVal);
		CMainFrame::theInstance->WriteStatusZoom(m_zoomVal);
		Invalidate();
	}
	return 0;
}

LRESULT CGMEView::OnPannRefresh(WPARAM, LPARAM)
{
	DoPannWinRefresh();
	return 0;
}

LRESULT CGMEView::OnPannScroll(WPARAM wParam, LPARAM lParam)
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnPannScroll() in "+path+name+"\r\n");
	int relx = (DWORD)wParam;
	int rely = (DWORD)lParam;
	CPoint current = GetScrollPosition();       // upper corner of scrolling
	current.x += relx;
	current.y += rely;
	ScrollToPosition(current);				    // set upper left position
	Invalidate();
	return 0;
}

void CGMEView::OnCntxNamePositionNorth()
{
	ChangeNamePosition(0);
}
void CGMEView::OnCntxNamePositionEast()
{
	ChangeNamePosition(2);
}
void CGMEView::OnCntxNamePositionSouth()
{
	ChangeNamePosition(4);
}
void CGMEView::OnCntxNamePositionWest()
{
	ChangeNamePosition(6);
}
void CGMEView::OnUpdateCntxNamePositionNorth( CCmdUI* pCmdUI )
{
	UpdateNamePositionMenuItem( pCmdUI, 0);
}
void CGMEView::OnUpdateCntxNamePositionEast( CCmdUI* pCmdUI )
{
	UpdateNamePositionMenuItem( pCmdUI, 2);
}
void CGMEView::OnUpdateCntxNamePositionSouth( CCmdUI* pCmdUI )
{
	UpdateNamePositionMenuItem( pCmdUI, 4);
}
void CGMEView::OnUpdateCntxNamePositionWest( CCmdUI* pCmdUI )
{
	UpdateNamePositionMenuItem( pCmdUI, 6);
}
void CGMEView::UpdateNamePositionMenuItem( CCmdUI* pCmdUI, int p_this_value)
{
	CGMEEventLogger::LogGMEEvent("CGMEView::UpdateNamePositionMenuItem\r\n");

	ASSERT(p_this_value == 0 || p_this_value == 2 || p_this_value == 4 || p_this_value == 6);

	bool any_sel = !selected.IsEmpty();
	pCmdUI->Enable( any_sel);
	if( !any_sel) return;

	// calculate the common selected namePos attribute value of the selected objects
	int common_value( -1);
	bool all_equal( true);

	try {
		BeginTransaction(TRANSACTION_READ_ONLY);

		bool first_value( true), res;
		POSITION pos = selected.GetHeadPosition();
		while(pos && all_equal) {
			CGuiObject *obj = selected.GetNext(pos);
			int v( -1);

			if( obj && obj->mgaFco)
				res = GetNamePositionVal( obj->mgaFco, &v);

			if( first_value)
			{
				common_value = v;
				first_value = false;
			}
			all_equal = all_equal && res && common_value == v && common_value == p_this_value;
		}

		CommitTransaction();
	}
	catch(hresult_exception &e) {
		all_equal = false;
		AbortTransaction(e.hr);
		CGMEEventLogger::LogGMEEvent("CGMEView::UpdateNamePositionMenuItem - Unable to get NamePosition preference value.\r\n");
	}

	// set the radiobutton like icon on/off based on the all_equal
	pCmdUI->SetRadio( all_equal);
}

void CGMEView::ChangeNamePosition( int p_val)
{
	CGMEEventLogger::LogGMEEvent("CGMEView::ChangeNamePosition\r\n");

	try {
		BeginTransaction();
		POSITION pos = selected.GetHeadPosition();
		while(pos) {
			CGuiObject *obj = selected.GetNext(pos);
			if( obj && obj->mgaFco)
				SetNamePositionVal( obj->mgaFco, p_val);
		}

		CommitTransaction();
	}
	catch(hresult_exception &e) {
		AbortTransaction(e.hr);
		CGMEEventLogger::LogGMEEvent("CGMEView::ChangeNamePosition - Unable to change NamePosition preference value.\r\n");
	}
}

// 
// code below has to be in sync with the objectinspector's preference.cpp
//
void CGMEView::SetNamePositionVal(CComPtr<IMgaFCO>& p_ccpMgaFCO, int val)
{	
	CGMEEventLogger::LogGMEEvent("CGMEView::SetNamePositionVal\r\n");

	ASSERT( p_ccpMgaFCO);
	if( !p_ccpMgaFCO) return;

	static const CComBSTR bstrRegPath("namePosition");
	CString valString;
	valString.Format("%d", val);
	CComBSTR bstrValue( valString);

	// For a specific object we modify the registry value
	COMTHROW(p_ccpMgaFCO->put_RegistryValue(bstrRegPath,bstrValue));
}

bool CGMEView::GetNamePositionVal(CComPtr<IMgaFCO>& p_ccpMgaFCO, int* p_valRet)
{	
	ASSERT( p_ccpMgaFCO);
	ASSERT( p_valRet);
	if( !p_ccpMgaFCO) return false;

	static const CComBSTR bstrRegPath("namePosition");
	CString strRegValue;

	// Getting regnode
	CComPtr<IMgaRegNode> ccpMgaRegNode;
	COMTHROW(p_ccpMgaFCO->get_RegistryNode(bstrRegPath,&ccpMgaRegNode));

	// Getting regnode status
	long lRegNodeStatus;
	COMTHROW(ccpMgaRegNode->get_Status(&lRegNodeStatus));


	//Status of definition: 0: this node, -1: in meta, >=1: inherited
	if(lRegNodeStatus==0)
	{
		/* Getting the value of the registry node */

		CComBSTR bstrRegValue;
		COMTHROW(ccpMgaRegNode->get_Value(&bstrRegValue));

		strRegValue=bstrRegValue;

	}
	else if(lRegNodeStatus==-1)
	{
		/* Getting value from meta */

		// Getting Meta
		CComPtr<IMgaMetaFCO> ccpMetaFCO;
		COMTHROW(p_ccpMgaFCO->get_Meta(&ccpMetaFCO));

		// Getting registry value from meta
		CComBSTR bstrRegValue;
		COMTHROW(ccpMetaFCO->get_RegistryValue(bstrRegPath,&bstrRegValue));

		strRegValue=bstrRegValue;
	}
	else if(lRegNodeStatus>=1)
	{
		/* Getting inherited value */

		// Getting ancestor FCO
		CComPtr<IMgaFCO> ccpAncestorFCO;
		COMTHROW(p_ccpMgaFCO->get_DerivedFrom(&ccpAncestorFCO));

		// Getting registry value from the ancestor
		CComBSTR bstrRegValue;
		COMTHROW(ccpAncestorFCO->get_RegistryValue(bstrRegPath,&bstrRegValue));

		strRegValue=bstrRegValue;
	}
	else if(lRegNodeStatus==-2)  // ATTRSTATUS_INVALID - It does happen.
	{
		strRegValue="";
	}
	else
	{
		ASSERT(("Undocumented(and undesired) MGA feature",false));
		CGMEEventLogger::LogGMEEvent("CGMEView::GetNamePositionVal: Undocumented(and undesired) MGA feature\r\n");
		strRegValue="";
	}

	int val = -1;
	if( _stscanf((LPCTSTR)strRegValue, _T("%d"), &val) != 1 || val < 0 || val > 8)
	{
		*p_valRet = -1;
		return false;
	}

	*p_valRet = val;
	return true;
}

bool CGMEView::AskUserAndDetachIfNeeded( CComPtr<IMgaFCO>& mgaFco)
{
	// check whether dependends of mgaFco exist
	CComPtr<IMgaFCOs> der_objs;
	COMTHROW(mgaFco->get_DerivedObjects( &der_objs));
	long cnt = 0;
	if( der_objs) COMTHROW( der_objs->get_Count( &cnt));
	if( cnt > 0) // if dependents exist should they be deleted?
	{
		bool question_asked = false;
		bool detach_answered = false;
		MGACOLL_ITERATE(IMgaFCO, der_objs) {
			CComPtr<IMgaFCO> one_derived(MGACOLL_ITER);

			VARIANT_BOOL prim_deriv;
			COMTHROW( one_derived->get_IsPrimaryDerived( &prim_deriv));
			if( prim_deriv == VARIANT_TRUE)
			{
				if( !question_asked) // pop up dialog only for the first time
				{
					CComBSTR nm;
					COMTHROW( mgaFco->get_Name( &nm));
					CString msg = "There are objects primary derived from: \"";
					msg += nm;
					msg += "\". Would you like to delete them as well?\n";
					msg += "If you answer 'No' the derived objects will be detached, thus preserved.";

					// this answer will be applied to all deriveds of this fco
					int resp = AfxMessageBox( msg, MB_YESNOCANCEL);
					if( resp == IDCANCEL) COMTHROW(E_MGA_MUST_ABORT);
					else if( resp == IDNO) detach_answered = true;
					
					question_asked = true;
				}

				// if detach and preserve selected by the user:
				if( detach_answered)
					COMTHROW( one_derived->DetachFromArcheType());
			}
		}MGACOLL_ITERATE_END;

		return detach_answered; // refresh needed for GMEActiveBrowser?
	}
	return false;
}

// called when VK_RETURN pressed on a model in a view
void CGMEView::OnShowSelectedModel()
{
	if(selected.GetCount()) {
		GMEEVENTLOG_GUIOBJS(selected);
		CComPtr<IMgaFCOs> coll;
		GetDocument()->CreateFcoList( &selected, coll, this);

		long cnt = 0;
		try {
			BeginTransaction(TRANSACTION_READ_ONLY);
			if( coll) COMTHROW( coll->get_Count( &cnt));
			CommitTransaction();
		}
		catch(hresult_exception e) {
			AbortTransaction(e.hr);
		}

		for( long i = 1; i <= cnt; ++i) {
			try {
				BeginTransaction(TRANSACTION_READ_ONLY);
				CComPtr<IMgaFCO> fco;
				COMTHROW( coll->get_Item( i, &fco));
				objtype_enum ot = OBJTYPE_ATOM;
				if( fco) COMTHROW( fco->get_ObjType( &ot));
				CommitTransaction();

				if( fco && ot == OBJTYPE_MODEL)
				{
					CComPtr<IMgaModel> cm;
					COMTHROW( fco.QueryInterface( &cm));
					if( cm) ShowModel( cm);
				}
				else if( fco && ot == OBJTYPE_REFERENCE) 
				{
					CComPtr<IMgaModel> next_mod;
					CComPtr<IMgaFCO> next_fco;
					CComBSTR         special_case_id_of_next_fco; // next_fco might sit in a folder, we will
					                                              // focus on it in the treebrowser in this case
					CComQIPtr<IMgaReference> rf( fco);
					try {
						BeginTransaction(TRANSACTION_READ_ONLY);
						COMTHROW( rf->get_Referred( &next_fco));
						objtype_enum ot = OBJTYPE_ATOM;
						if( next_fco) 
						{
							COMTHROW( next_fco->get_ObjType( &ot));
							if( ot == OBJTYPE_MODEL)
							{
								COMTHROW( next_fco.QueryInterface( &next_mod));
							}
							else
							{
								CComPtr<IMgaObject> parent;
								COMTHROW( next_fco->GetParent( &parent));
								
								if( parent)
								{
									HRESULT hr = parent.QueryInterface( &next_mod);
									if( FAILED( hr)) // next_fco is sitting in a folder
										COMTHROW( next_fco->get_ID( &special_case_id_of_next_fco));
								}
							}
						}
						
						CommitTransaction();
					}
					catch(hresult_exception e) {
						AbortTransaction(e.hr);
						next_mod = 0;
					}

					if( special_case_id_of_next_fco.Length() > 0)
					{
						CGMEConsole::theInstance->Message( "Reference target is child of a folder, thus it is shown in the TreeBrowser only.", MSG_INFO);
						CGMEBrowser::theInstance->FocusItem( special_case_id_of_next_fco);
					}
					else if( next_fco && next_mod) ShowModel( next_mod);
				}
			}
			catch(hresult_exception e) {
				AbortTransaction(e.hr);
			}
		}
	}
}

// called when VK_B + CTRL is pressed
void CGMEView::OnFocusBrowser()
{
	OnCntxLocate();
}

// called when VK_I + CTRL is pressed
void CGMEView::OnFocusInspector()
{
	HWND hwnd = CGMEObjectInspector::theInstance->GetSafeHwnd();
	if( hwnd) ::SetFocus( hwnd);
}

// called when TAB is pressed
void CGMEView::OnCycleAspect()
{
	ASSERT( currentAspect);
	ASSERT( guiMeta);
	if( !currentAspect || !guiMeta) return;
	int aspNum = guiMeta->aspects.GetCount();
	ASSERT( aspNum >= 1);
	if( aspNum <= 1) return; // if 1 aspect no reason for continuing

	ChangeAspect( (currentAspect->index + 1) % aspNum);
	// statement above changes the currentAspect->index to the new value
	if( CMainFrame::theInstance)
		CMainFrame::theInstance->ChangePartBrowserAspect( currentAspect->index);
}

// called when '`' is pressed (above the TAB key)
void CGMEView::OnCycleAllAspects()
{
	if( CMainFrame::theInstance)
		CMainFrame::theInstance->CyclePartBrowserAspect();
}

void CGMEView::OnHistoryBack()
{
	GetDocument()->back();
}

void CGMEView::OnHistoryForw()
{
	GetDocument()->forw();
}

void CGMEView::OnKeyConnect()
{
	CGMEEventLogger::LogGMEEvent("CGMEView::OnKeyConnect in "+path+name+"\r\n");
	if( lastObject) {
		CGuiObject *obj = lastObject;
		if(obj) {
			CGuiPort *port = lastPort;
			if(connSrc == 0) {
				connSrc = obj;
				connSrcPort = port;
				connSrcHotSide = GME_CENTER;
				tmpConnectMode = true;
				SetCursor(autoconnect2Cursor);
			}
			else {
				Connect(connSrc,connSrcPort,connSrcHotSide,obj,port, GME_CENTER, ::GetKeyState(VK_SHIFT) < 0);
				ClearConnSpecs();
				tmpConnectMode = false;
				SetCursor(editCursor);
			}
			ShowCursor(TRUE);
		}
	}
}

void CGMEView::OnKeyCycleObjInspectorFrwd()
{
	CGMEObjectInspector::theInstance->CyclePanel( VARIANT_TRUE);
}

void CGMEView::OnKeyCycleObjInspectorBkwd()
{
	CGMEObjectInspector::theInstance->CyclePanel( VARIANT_FALSE);
}

void CGMEView::OnViewMultiUserShowObjectOwner()
{
	theApp.mgaProject->SourceControlObjectOwner( currentModId);
}

void CGMEView::OnUpdateViewMultiUserShowObjectOwner( CCmdUI* pCmdUI)
{
	pCmdUI->Enable( theApp.isMultiUserProj());
}
