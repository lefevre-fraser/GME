#ifndef GME_AutoRouter_h
#define GME_AutoRouter_h

class CAutoRouterBox;
class CAutoRouterPort;
class CAutoRouterPath;
class CAutoRouterGraph;

typedef CList<CPoint, CPoint&>	CPointList;

class CAutoRouter {
public:
	CAutoRouter();
	~CAutoRouter();

	friend CAutoRouterGraph;

public:
	CComPtr<IAutoRouterGraph> router;
	int routeret;

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