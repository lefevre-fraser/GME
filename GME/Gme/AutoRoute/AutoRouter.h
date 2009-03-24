#ifndef GME_AutoRouter_h
#define GME_AutoRouter_h

#include "stdafx.h"
#include "afxcoll.h"
#include "afxtempl.h"

#include "AutoRouterPath.h"

class CGuiConnection;

typedef CList<CPoint, CPoint&>	CPointList;
typedef CMap<CAutoRouterPath*, CAutoRouterPath*, CGuiConnection*, CGuiConnection* > CMapAutoRouterPath2CGuiConnection;

// Functions for CMapAutoRouterPath2CGuiConnection, see AutoRouter.h
template<>
UINT AFXAPI HashKey< CAutoRouterPath* > (CAutoRouterPath* key);

typedef CAutoRouterPath* LPCCAutoRouterPath;

template<>
BOOL AFXAPI CompareElements< LPCCAutoRouterPath, LPCCAutoRouterPath >
	 (const LPCCAutoRouterPath* pElement1, const LPCCAutoRouterPath* pElement2);
// End of functions for CMapAutoRouterPath2CGuiConnection, see AutoRouter.h


class CAutoRouter {
public:
	CAutoRouter();
	~CAutoRouter();

	friend CAutoRouterGraph;

public:
	CComPtr<IAutoRouterGraph> router;
	int routeret;
	CMapAutoRouterPath2CGuiConnection mapPath2Conn;

public:
	void AutoRoute();
	void AutoRoute(CGuiFcoList &fcos);
	void Fill(CGuiFcoList &fcos);
	void Clear(CGuiFcoList &fcos);
	void SetPortPreferences(CComPtr<IAutoRouterPort> portBox, CGuiPort *object);
	void SetPathPreferences(CComPtr<IAutoRouterPath> path, CGuiConnection *conn);
	void AddObjects(CGuiFcoList &fcos);
	void AddFco(CGuiFco *fco);
	void AddObject(CGuiObject *obj);
	void AddConnections(CGuiConnectionList &connList);
	void AddConnection(CGuiConnection *conn);
	void DeleteObjects(CGuiObjectList &objectList);
	void DeleteObject(CGuiObject *model);
	void ClearRouterPorts(CGuiPortList &portList);
	void DeleteConnection(CGuiConnection *conn);
	CGuiConnection *FindConnection(CPoint &pt) const;
	void NudgeObjects(CGuiObjectList &objectList,int right,int down);
/*
// --- Autoroute debug

public:
	void ArAutoRoute();
	void ArConnect();
	void ArSimplify();
	void ArUnconnect();
	void ArCheck(CGMEView* view);

	void ArLeft();
	void ArRight();
	void ArUp();
	void ArDown();

	void ArHorizontal();
	void ArVertical();
*/
};

#endif // whole file