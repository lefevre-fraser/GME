
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
	router = new CAutoRouterGraph();
	ASSERT( router != NULL );
	routeret = 1;
}

CAutoRouter::~CAutoRouter()
{
	ASSERT( router != NULL );

	router->Destroy();
	delete router;
	mapPath2Conn.RemoveAll();
}

bool CAutoRouter::AutoRoute(long aspect)
{
	if (CGMEView::IsHugeModel())
		return true;

	long res = router->AutoRoute(aspect);
	bool wereThereDeletion = RemoveDeletedCustomPathDataFromGuiConnections();
	routeret = res;
	return wereThereDeletion;
}

void CAutoRouter::AutoRoute(CGuiFcoList& fcos, long aspect)
{
	if (CGMEView::IsHugeModel())
		return;
	bool wereThereDeletion = false;
	do {
		Fill(fcos);
		wereThereDeletion = AutoRoute(aspect);
	} while (routeret == -2 && wereThereDeletion);
}

void CAutoRouter::Fill(CGuiFcoList& fcos)
{
	Clear(fcos);
	AddObjects(fcos);
}

void CAutoRouter::Clear(CGuiFcoList& fcos)
{
	mapPath2Conn.RemoveAll();

	router->DeleteAll(true);

	POSITION pos = fcos.GetHeadPosition();
	while (pos) {
		CGuiFco* fco = fcos.GetNext(pos);
		ASSERT(fco != NULL);
		CGuiConnection* conn = fco->dynamic_cast_CGuiConnection();
		if (conn) {
			conn->SetRouterPath(NULL);
		} else {
			CGuiObject* obj = fco->dynamic_cast_CGuiObject();
			VERIFY(obj);
			if (obj->IsVisible()) {
				obj->SetRouterBox(NULL);
				obj->SetRouterNameBox(NULL);
				POSITION ppos = obj->GetPorts().GetHeadPosition();
				while (ppos) {
					obj->GetPorts().GetNext(ppos)->SetRouterPort(NULL) ;
				}
			}
		}
	}
}

void CAutoRouter::AddObjects(CGuiFcoList& fcos)
{
	if (CGMEView::IsHugeModel())
		return;
	CGuiConnectionList conns;
	POSITION pos = fcos.GetHeadPosition();
	while (pos) {
		CGuiFco* fco = fcos.GetNext(pos);
		ASSERT(fco != NULL);
		if (fco->IsVisible()) {
			CGuiConnection* conn = fco->dynamic_cast_CGuiConnection();
			if (conn)
				conns.AddTail(conn);
			else
				AddFco(fco);
		}
	}
	pos = conns.GetHeadPosition();
	while (pos)
		AddFco(conns.GetNext(pos));
}

void CAutoRouter::SetPortPreferences(CAutoRouterPort* portBox, CGuiPort* port)
{

	if (CGMEView::IsHugeModel())
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

void CAutoRouter::SetPathPreferences(CAutoRouterPath* path, CGuiConnection* conn)
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

	// Load the customized edge data which corresponds to the needed aspect
	std::vector<CustomPathData> cpd = conn->GetCurrentPathCustomizations();
	path->SetCustomPathData(cpd);
}

bool CAutoRouter::RemoveDeletedCustomPathDataFromGuiConnections(void)
{
	bool wereThereDeletion = false;

	POSITION pos = mapPath2Conn.GetStartPosition();
	CAutoRouterPath* key;
	while (pos) {
		CGuiConnection* value;
		mapPath2Conn.GetNextAssoc(pos, key, value);
		if (key->AreThereDeletedPathCustomizations()) {
			std::vector<CustomPathData> cpd;
			key->GetDeletedCustomPathData(cpd);
			value->RemoveDeletedPathCustomizations(cpd);
			wereThereDeletion = true;
		}
	}

	return wereThereDeletion;
}

void CAutoRouter::AddFco(CGuiFco* fco)
{
	if (CGMEView::IsHugeModel())
		return;
	ASSERT(fco != NULL);
	CGuiConnection* conn = fco->dynamic_cast_CGuiConnection();
	if (conn) {
		AddConnection(conn);
	} else {
		CGuiObject* obj = fco->dynamic_cast_CGuiObject();
		VERIFY(obj);
		AddObject(obj);
	}
}

void CAutoRouter::AddObject(CGuiObject* object)
{
	if (CGMEView::IsHugeModel())
		return;

	CAutoRouterBox* box = router->CreateBox();

	CRect loc = object->GetLocation();
	box->SetRect(loc);

	CAutoRouterBox* nameBox = NULL;
	if (theApp.labelAvoidance) {
		nameBox = router->CreateBox();
		nameBox->SetRect(object->GetNameLocation());
	}

	CGuiPortList& ports = object->GetPorts();
	POSITION pos = ports.GetHeadPosition();
	while (pos) {
		CGuiPort* port = ports.GetNext(pos);
		CAutoRouterPort* portBox = box->CreatePort();
		// real ports most obey the rule that the only dir allowed is
		// the one on which side of their parent they are laid out
		portBox->SetLimitedDirs(port->IsRealPort());
		CRect r = port->GetLocation() + loc.TopLeft();
		portBox->SetRect(r);
		SetPortPreferences(portBox, port);
		port->SetRouterPort(portBox);
		box->AddPort(portBox);
	}

	object->SetRouterBox(box);
	if (theApp.labelAvoidance)
		object->SetRouterNameBox(nameBox);

	router->AddBox(box);

	if (theApp.labelAvoidance)
		router->AddBox(nameBox);
}

void CAutoRouter::AddConnections(CGuiConnectionList& connList)
{
	if (CGMEView::IsHugeModel())
		return;
	POSITION pos = connList.GetHeadPosition();
	while (pos)
		AddConnection(connList.GetNext(pos));
}

void CAutoRouter::AddConnection(CGuiConnection* conn)
{
	if (CGMEView::IsHugeModel())
		return;
	if (!conn->IsVisible())
		return;

	CAutoRouterPort* asrc = conn->srcPort->GetRouterPort();
	CAutoRouterPort* adst = conn->dstPort->GetRouterPort();

	CAutoRouterPath* path = router->AddPath(conn->IsAutoRouted(), asrc, adst);

	SetPathPreferences(path, conn);
	conn->SetRouterPath(path);
	// Later if we get an AutoRouterPath from AutoRouterGraph while searching for a connection line,
	// we want to get the CGuiConnection object corresponding to that path. So we build a hash map for that
	// (the other association direction is clear: CGuiConnection contains an CAutoRouterPath*)
	mapPath2Conn.SetAt(path, conn);
}

void CAutoRouter::DeleteObjects(CGuiObjectList &objs)
{
	if (CGMEView::IsHugeModel())
		return;
	POSITION pos = objs.GetHeadPosition();
	while (pos) {
		CGuiObject *obj = objs.GetNext(pos);
		if (obj && obj->IsVisible()) {
			DeleteObject(obj);
		}
	}
}

void CAutoRouter::DeleteObject(CGuiObject *object)
{
	if (CGMEView::IsHugeModel())
		return;
	if (object->IsVisible()) {
		router->DeleteBox(object->GetRouterBox());

		if (theApp.labelAvoidance) {
			CAutoRouterBox* nameBox = object->GetRouterNameBox();
			if (nameBox != NULL) {
				router->DeleteBox(nameBox);
			}
		}

		object->SetRouterBox(NULL);
		object->SetRouterNameBox(NULL);
		ClearRouterPorts(object->GetPorts());
	}
}

void CAutoRouter::ClearRouterPorts(CGuiPortList &portList)
{
	POSITION pos = portList.GetHeadPosition();
	while (pos)
		portList.GetNext(pos)->SetRouterPort(NULL);
}

void CAutoRouter::DeleteConnection(CGuiConnection *conn)
{
	if (CGMEView::IsHugeModel())
		return;

	if (conn->GetRouterPath() != NULL) {
		CAutoRouterPath* currPath = conn->GetRouterPath();
		// Update the hash map, otherwise it could contain destroyed CGuiConnection* object pointers
		mapPath2Conn.RemoveKey(currPath);
		router->DeletePath(currPath);
		conn->SetRouterPath(NULL);
	}
}

CGuiConnection* CAutoRouter::FindConnection(CPoint& pt) const
{
	if (CGMEView::IsHugeModel())
		return 0;

	CAutoRouterPath* path = router->GetPathAt(pt, 3);

	if (path != NULL)
	{
		// We could get an AutoRouterPath from AutoRouterGraph while searching for a connection line,
		// we want to get the CGuiConnection object corresponding to that path. We have a hash map for that
		// (the other association direction is clear: CGuiConnection contains an CAutoRouterPath*)
		CGuiConnection* connAddr = NULL;
		mapPath2Conn.Lookup(path, connAddr);

		return connAddr;
	}
	else
	{
		return NULL;
	}
}

void CAutoRouter::NudgeObjects(CGuiObjectList& objectList, int right, int down, long aspect)
{
	if (CGMEView::IsHugeModel())
		return;
	CPoint offs = CPoint(right * GME_GRID_SIZE, down * GME_GRID_SIZE);
	POSITION pos = objectList.GetHeadPosition();
	while(pos) {
		CGuiObject* obj = objectList.GetNext(pos);

		router->ShiftBoxBy(obj->GetRouterBox(), offs);

		if (theApp.labelAvoidance) {
			CAutoRouterBox* nameBox = obj->GetRouterNameBox();
			if (nameBox) {
				router->ShiftBoxBy(nameBox, offs);
			}
			
		}
	}
	AutoRoute(aspect);
}
