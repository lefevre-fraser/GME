
#include "stdafx.h"

#include "GuiMeta.h"
#include "GuiObject.h"
#include "ArGraph.h"
#include "AutoRouter.h"

#include "GMEView.h"

////////////////////////////////// CAutoRouter //////////////////////////////////

CAutoRouter::CAutoRouter()
{
	router = new CArGraph();
	ASSERT( router != NULL );
}

CAutoRouter::~CAutoRouter()
{
	ASSERT( router != NULL );
	delete router;
}

void CAutoRouter::AutoRoute()
{
	if(CGMEView::IsHugeModel())
		return;
	routeret = router->AutoRoute();
}

void CAutoRouter::AutoRoute(CGuiFcoList &fcos)
{
	if(CGMEView::IsHugeModel())
		return;
	Fill(fcos);
	AutoRoute();
}

void CAutoRouter::Fill(CGuiFcoList &fcos)
{
	Clear(fcos);
	AddObjects(fcos);
}

void CAutoRouter::Clear(CGuiFcoList &fcos)
{
	router->DeleteAll();

	POSITION pos = fcos.GetHeadPosition();
	while(pos) {
		CGuiFco *fco = fcos.GetNext(pos);
		CGuiConnection *conn = dynamic_cast<CGuiConnection *>(fco);
		if(conn) {
			conn->SetRouterPath(0);
		}
		else {
			CGuiObject *obj = dynamic_cast<CGuiObject *>(fco);
			VERIFY(obj);
			if (obj->IsVisible()) {
				obj->SetRouterBox(0);
				obj->SetRouterNameBox(0);
				POSITION ppos = obj->GetPorts().GetHeadPosition();
				while (ppos) {
					obj->GetPorts().GetNext(ppos)->SetRouterPort(0) ;
				}
			}
		}
	}
}

void CAutoRouter::AddObjects(CGuiFcoList &fcos)
{
	if(CGMEView::IsHugeModel())
		return;
	CGuiConnectionList conns;
	POSITION pos = fcos.GetHeadPosition();
	while(pos) {
		CGuiFco *fco = fcos.GetNext(pos);
		if(fco->IsVisible()) {
			CGuiConnection *conn = dynamic_cast<CGuiConnection *>(fco);
			if(conn)
				conns.AddTail(conn);
			else
				AddFco(fco);
		}
	}
	pos = conns.GetHeadPosition();
	while(pos)
		AddFco(conns.GetNext(pos));
}

void CAutoRouter::SetPortPreferences(CArPort * portBox,CGuiPort * port)
{

	if(CGMEView::IsHugeModel())
		return;
	
	unsigned long attr = 0;
	
	if (port->GetARPref(GME_START_NORTH))
		attr |= ARPORT_StartOnTop;
	if (port->GetARPref(GME_START_SOUTH))
		attr |= ARPORT_StartOnBottom;
	if (port->GetARPref(GME_START_EAST))
		attr |= ARPORT_StartOnRight;
	if (port->GetARPref(GME_START_WEST))
		attr |= ARPORT_StartOnLeft;

	if (port->GetARPref(GME_END_NORTH))
		attr |= ARPORT_EndOnTop;
	if (port->GetARPref(GME_END_SOUTH))
		attr |= ARPORT_EndOnBottom;
	if (port->GetARPref(GME_END_EAST))
		attr |= ARPORT_EndOnRight;
	if (port->GetARPref(GME_END_WEST))
		attr |= ARPORT_EndOnLeft;

	portBox->SetAttributes(attr);
}

void CAutoRouter::SetPathPreferences(CArPath *path, CGuiConnection *conn)
{
	if(CGMEView::IsHugeModel())
		return;

	ASSERT( path != NULL );
	unsigned int arpath_start = ARPATH_Default, arpath_end = ARPATH_Default;

	if (conn->GetARPref(GME_START_NORTH))
		arpath_start |= ARPATH_StartOnTop;
	if (conn->GetARPref(GME_START_SOUTH))
		arpath_start |= ARPATH_StartOnBottom;
	if (conn->GetARPref(GME_START_EAST))
		arpath_start |= ARPATH_StartOnRight;
	if (conn->GetARPref(GME_START_WEST))
		arpath_start |= ARPATH_StartOnLeft;

	if (conn->GetARPref(GME_END_NORTH))
		arpath_end |= ARPATH_EndOnTop;
	if (conn->GetARPref(GME_END_SOUTH))
		arpath_end |= ARPATH_EndOnBottom;
	if (conn->GetARPref(GME_END_EAST))
		arpath_end |= ARPATH_EndOnRight;
	if (conn->GetARPref(GME_END_WEST))
		arpath_end |= ARPATH_EndOnLeft;


	ASSERT( (arpath_start & (~ARPATH_StartMask)) == 0 );
	ASSERT( (arpath_end & (~ARPATH_EndMask)) == 0 );

	path->SetStartDir(arpath_start);
	path->SetEndDir(arpath_end);
}


void CAutoRouter::AddFco(CGuiFco *fco)
{
	if(CGMEView::IsHugeModel())
		return;
	CGuiConnection *conn = dynamic_cast<CGuiConnection *>(fco);
	if(conn)
		AddConnection(conn);
	else {
		CGuiObject *obj = dynamic_cast<CGuiObject *>(fco);
		VERIFY(obj);
		AddObject(obj);
	}
}


void CAutoRouter::AddObject(CGuiObject *object)
{
	if(CGMEView::IsHugeModel())
		return;

	CArBox *box;
	box = router->CreateBox();
	CRect loc = object->GetLocation();
	box->SetRect(loc);

	CArBox *nameBox = NULL;
	if (theApp.labelAvoidance) {
		nameBox = router->CreateBox();
		CRect nameLoc = object->GetNameLocation();
		nameBox->SetRect(nameLoc);
	}

	CGuiPortList &ports = object->GetPorts();
	POSITION pos = ports.GetHeadPosition();
	while(pos) {
		CGuiPort *port = ports.GetNext(pos);
		CArPort *portBox = box->CreatePort();
		// real ports most obey the rule that the only dir allowed is
		// the one on which side of their parent they are laid out
		portBox->SetLimitedDirs( port->IsRealPort());
		portBox->SetRect(port->GetLocation() + loc.TopLeft());
		SetPortPreferences(portBox,port);
		port->SetRouterPort(portBox);
		// ????? box->SetAtomicPort(portBox);
		box->Add(portBox);
	}

	object->SetRouterBox(box);
	if (theApp.labelAvoidance) {
		object->SetRouterNameBox(nameBox);
	}

	router->Add(box);

	if (theApp.labelAvoidance) {
		router->Add(nameBox);
	}
}

void CAutoRouter::AddConnections(CGuiConnectionList &connList)
{
	if(CGMEView::IsHugeModel())
		return;
	POSITION pos = connList.GetHeadPosition();
	while(pos)
		AddConnection(connList.GetNext(pos));
}

void CAutoRouter::AddConnection(CGuiConnection *conn)
{
	if(CGMEView::IsHugeModel())
		return;
	if(!(conn->IsVisible()))
		return;
	CArPort *asrc = conn->srcPort->GetRouterPort();
	CArPort *adst = conn->dstPort->GetRouterPort();
	CArPath *path = router->AddPath(asrc,adst);
	SetPathPreferences(path, conn);
	conn->SetRouterPath(path);
	path->SetExtPtr(conn);
}

void CAutoRouter::DeleteObjects(CGuiObjectList &objs)
{
	if(CGMEView::IsHugeModel())
		return;
	POSITION pos = objs.GetHeadPosition();
	while(pos) {
		CGuiObject *obj = objs.GetNext(pos);
		if (obj && obj->IsVisible()) {
			DeleteObject(obj);
		}
	}
}

void CAutoRouter::DeleteObject(CGuiObject *object)
{
	if(CGMEView::IsHugeModel())
		return;
	if (object->IsVisible()) {
		router->Delete(object->GetRouterBox());
		if (theApp.labelAvoidance) {
			CArBox *nameBox = object->GetRouterNameBox();
			if (nameBox) {
				router->Delete(nameBox);
			}
		}
		object->SetRouterBox(0);
		object->SetRouterNameBox(0);
		ClearRouterPorts(object->GetPorts());
	}
}

void CAutoRouter::DeleteObject(CGuiPort *port)
{
	if(CGMEView::IsHugeModel())
		return;
	CArPort *portBox = port->GetRouterPort();
	CArBox *box = portBox->GetOwner();
	box->Delete(portBox);
	port->SetRouterPort(0);
}

void CAutoRouter::ClearRouterPorts(CGuiPortList &portList)
{
	POSITION pos = portList.GetHeadPosition();
	while(pos)
		portList.GetNext(pos)->SetRouterPort(0);
}


void CAutoRouter::DeleteConnection(CGuiConnection *conn)
{
	if(CGMEView::IsHugeModel())
		return;
	if(conn->GetRouterPath()) {
		router->Delete(conn->GetRouterPath());
		conn->SetRouterPath(0);
	}
}


CGuiConnection *CAutoRouter::FindConnection(CPoint &pt) const
{
	if(CGMEView::IsHugeModel())
		return 0;
	CArPath *path = router->GetPathAt(pt,3);
	return path ? ((CGuiConnection *)(path->GetExtPtr())) : 0;
}

void CAutoRouter::NudgeObjects(CGuiObjectList &objectList,int right,int down)
{
	if(CGMEView::IsHugeModel())
		return;
	CSize offs = CSize(right * GME_GRID_SIZE,down * GME_GRID_SIZE);
	POSITION pos = objectList.GetHeadPosition();
	while(pos) {
		CGuiObject *obj = objectList.GetNext(pos);
		router->ShiftBy(obj->GetRouterBox(),offs);
		if (theApp.labelAvoidance) {
			CArBox *nameBox = obj->GetRouterNameBox();
			if (nameBox) {
				router->ShiftBy(nameBox,offs);
			}
			
		}
	}
	AutoRoute();
}

// --- Autoroute debug
/*
SArEdge* CAutoRouter::GetArEdgeAt(CPoint point)
{
}
*/
/*
void CAutoRouter::ArAutoRoute()
{
	router->AutoRoute();
}

void CAutoRouter::ArConnect()
{
	router->ConnectAllDisconnectedPaths();
}

void CAutoRouter::ArUnconnect()
{
	router->DisconnectAll();
}

void CAutoRouter::ArSimplify()
{
	router->SimplifyPaths();
}

#include "GMEDoc.h"

void CAutoRouter::ArCheck(CGMEView* view)
{
	ASSERT( view != NULL );

	CEdtModel* base = view->currentModel;
	CEdtObjectList& objects = view->currentModel->GetModels();
	CGMEDoc* doc = view->GetDocument();
 
	srand( (unsigned)time( NULL ) );

	for(int i = 0; i < 100000; i++)
	{
		POSITION pos = objects.GetHeadPosition();
		while( pos )
		{
			CEdtObject* o = objects.GetNext(pos);
			modelGrid.Reset(o);
			o->SetModelPosition(CPoint(10+(rand()%400), 10+(rand()%400)));
		}

		view->AutoRoute();

		if( routeret == -1 )
			break;
	}

	doc->SetModifiedFlag(TRUE);
	view->Invalidate();
}

void CAutoRouter::ArLeft()
{
	if( !router->vertical.Block_ScanForward() )
		MessageBeep(MB_ICONEXCLAMATION);
}

void CAutoRouter::ArRight()
{
	if( !router->vertical.Block_ScanBackward() )
		MessageBeep(MB_ICONEXCLAMATION);
}

void CAutoRouter::ArUp()
{
	if( !router->horizontal.Block_ScanForward() )
		MessageBeep(MB_ICONEXCLAMATION);
}

void CAutoRouter::ArDown()
{
	if( !router->horizontal.Block_ScanBackward() )
		MessageBeep(MB_ICONEXCLAMATION);
}

void CAutoRouter::ArHorizontal()
{
	if( !router->horizontal.Block_SwitchWrongs() )
		MessageBeep(MB_ICONEXCLAMATION);
}

void CAutoRouter::ArVertical()
{
	if( !router->vertical.Block_SwitchWrongs() )
		MessageBeep(MB_ICONEXCLAMATION);
}

*/