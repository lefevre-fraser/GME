
#include "stdafx.h"

#include "GuiMeta.h"
#include "GuiObject.h"
#include "AutoRouterGraph.h"
#include "AutoRouterPort.h"
#include "AutoRouter.h"

#include "GMEView.h"

////////////////////////////////// CAutoRouter //////////////////////////////////

CAutoRouter::CAutoRouter()
{
	//todo vt:
	COMTHROW(CAutoRouterGraph::CreateInstance(&router));
}

CAutoRouter::~CAutoRouter()
{
	ASSERT( router != NULL );

	router->Destroy();
}

void CAutoRouter::AutoRoute()
{
	if(CGMEView::IsHugeModel())
		return;
	 
	long res;
	router->AutoRoute(&res);
	routeret = res;
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
			CComPtr<IAutoRouterPath> path;
			conn->SetRouterPath(path);
		}
		else {
			CGuiObject *obj = dynamic_cast<CGuiObject *>(fco);
			VERIFY(obj);
			if (obj->IsVisible()) {
				CComPtr<IAutoRouterBox> box1;
				CComPtr<IAutoRouterBox> box2;
				obj->SetRouterBox(box1);
				obj->SetRouterNameBox(box2);
				POSITION ppos = obj->GetPorts().GetHeadPosition();
				while (ppos) {
					CComPtr<IAutoRouterPort> port;
					obj->GetPorts().GetNext(ppos)->SetRouterPort(port) ;
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

void CAutoRouter::SetPortPreferences(CComPtr<IAutoRouterPort> portBox,CGuiPort * port)
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

void CAutoRouter::SetPathPreferences(CComPtr<IAutoRouterPath> path, CGuiConnection *conn)
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

	CComPtr<IAutoRouterBox> box;
	COMTHROW(router->CreateBox(&box));

	CRect loc = object->GetLocation();
	box->SetRect(loc.left, loc.top, loc.right, loc.bottom);

	CComPtr<IAutoRouterBox> nameBox;
	if (theApp.labelAvoidance) {
		COMTHROW(router->CreateBox(&nameBox));
		CRect nameLoc = object->GetNameLocation();
		nameBox->SetRect(nameLoc.left, nameLoc.top, nameLoc.right, nameLoc.bottom);
	}

	CGuiPortList &ports = object->GetPorts();
	POSITION pos = ports.GetHeadPosition();
	while(pos) {
		CGuiPort *port = ports.GetNext(pos);
		CComPtr<IAutoRouterPort> portBox; 
		COMTHROW(box->CreatePort(&portBox));
		// real ports most obey the rule that the only dir allowed is
		// the one on which side of their parent they are laid out
		portBox->SetLimitedDirs( port->IsRealPort());
		CRect r = port->GetLocation() + loc.TopLeft();
		portBox->SetRect(r.left, r.top, r.right, r.bottom);
		SetPortPreferences(portBox,port);
		port->SetRouterPort(portBox);
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
	CComPtr<IAutoRouterPort> asrc = conn->srcPort->GetRouterPort();
	CComPtr<IAutoRouterPort> adst = conn->dstPort->GetRouterPort();
	CComPtr<IAutoRouterPath> path; 

	COMTHROW(router->AddPath(asrc, adst, &path));

	SetPathPreferences(path, conn);
	conn->SetRouterPath(path);
	// hack no 1: this is a little hack: 
	// only the address is needed, thus it should be void*
	path->SetExtPtr((ULONGLONG)conn);
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
		router->DeleteBox(object->GetRouterBox());

		if (theApp.labelAvoidance) {
			CComPtr<IAutoRouterBox> nameBox = object->GetRouterNameBox();
			if (nameBox.p) {
				router->DeleteBox(nameBox);
			}
		}

		CComPtr<IAutoRouterBox> box1;
		CComPtr<IAutoRouterBox> box2;
		object->SetRouterBox(box1);
		object->SetRouterNameBox(box2);
		ClearRouterPorts(object->GetPorts());
	}
}

void CAutoRouter::ClearRouterPorts(CGuiPortList &portList)
{
	POSITION pos = portList.GetHeadPosition();
	while(pos)
	{
		CComPtr<IAutoRouterPort> port;
		portList.GetNext(pos)->SetRouterPort(port);
	}
}

void CAutoRouter::DeleteConnection(CGuiConnection *conn)
{
	if(CGMEView::IsHugeModel())
		return;
	if(conn->GetRouterPath().p) {
		router->DeletePath(conn->GetRouterPath());
		CComPtr<IAutoRouterPath> path;
		conn->SetRouterPath(path);
	}
}


CGuiConnection *CAutoRouter::FindConnection(CPoint &pt) const
{
	if(CGMEView::IsHugeModel())
		return 0;

	CComPtr<IAutoRouterPath> path;
	router->GetPathAt(pt.x,pt.y,3,&path);

	if (path.p != NULL)
	{
		// hack no 2: this is the same hack as in hack no 1.
		ULONGLONG address;
		path->GetExtPtr(&address);
		return (CGuiConnection*)(address);
	}
	else
	{
		return NULL;
	}
}

void CAutoRouter::NudgeObjects(CGuiObjectList &objectList,int right,int down)
{
	if(CGMEView::IsHugeModel())
		return;
	CSize offs = CSize(right * GME_GRID_SIZE,down * GME_GRID_SIZE);
	POSITION pos = objectList.GetHeadPosition();
	while(pos) {
		CGuiObject *obj = objectList.GetNext(pos);

		router->ShiftBy(obj->GetRouterBox(),offs.cx, offs.cy);

		if (theApp.labelAvoidance) {
			CComPtr<IAutoRouterBox> nameBox = obj->GetRouterNameBox();
			if (nameBox.p) {
				router->ShiftBy(nameBox,offs.cx, offs.cy);
			}
			
		}
	}
	AutoRoute();
}
