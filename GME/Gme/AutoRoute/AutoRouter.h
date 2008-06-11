#ifndef GME_AutoRouter_h
#define GME_AutoRouter_h

class CArBox;
class CArPort;
class CArPath;
class CArGraph;

typedef CList<CPoint, CPoint&>	CPointList;

class CAutoRouter {
public:
	CAutoRouter();
	~CAutoRouter();

public:
	CArGraph *router;
	int routeret;

public:
	void AutoRoute();
	void AutoRoute(CGuiFcoList &fcos);
	void Fill(CGuiFcoList &fcos);
	void Clear(CGuiFcoList &fcos);
	void SetPortPreferences(CArPort *portBox,CGuiPort *object);
	void SetPathPreferences(CArPath *path, CGuiConnection *conn);
	void AddObjects(CGuiFcoList &fcos);
	void AddFco(CGuiFco *fco);
	void AddCompound(CGuiCompound *compound);
	void AddObject(CGuiObject *obj);
	void AddConnections(CGuiConnectionList &connList);
	void AddConnection(CGuiConnection *conn);
	void DeleteObjects(CGuiObjectList &objectList);
	void DeleteObject(CGuiObject *model);
	void DeleteObject(CGuiPort *port);
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