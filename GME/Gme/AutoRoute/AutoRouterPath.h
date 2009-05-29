// AutoRouterPath.h : Declaration of the CAutoRouterPath

#pragma once
#include "resource.h"       // main symbols

#include <vector>
//#include <oleauto.h>

#include "AutoRoute/ArHelper.h"

#include "AutoRouterPort.h"
#include "AutoRouterBox.h"

//#include "GME.h"
#include "gmelib.h"

#define ARPATH_EndOnDefault		0x0000
#define ARPATH_EndOnTop			0x0010
#define ARPATH_EndOnRight		0x0020
#define ARPATH_EndOnBottom		0x0040
#define ARPATH_EndOnLeft		0x0080
#define ARPATH_EndMask			(ARPATH_EndOnTop | ARPATH_EndOnRight | ARPATH_EndOnBottom | ARPATH_EndOnLeft)


#define ARPATH_StartOnDefault	0x0000
#define ARPATH_StartOnTop		0x0100
#define ARPATH_StartOnRight		0x0200
#define ARPATH_StartOnBottom	0x0400
#define ARPATH_StartOnLeft		0x0800
#define ARPATH_StartMask		(ARPATH_StartOnTop | ARPATH_StartOnRight | ARPATH_StartOnBottom | ARPATH_StartOnLeft)

#define ARPATH_HighLighted		0x0002		// attributes
#define ARPATH_Fixed			0x0001
#define ARPATH_Default			0x0000

#define ARPATHST_Connected		0x0001		// states
#define ARPATHST_Default		0x0000


// Version of edge data structure
#define CONNECTIONCUSTOMIZATIONDATAVERSION			0
#define EMPTYCONNECTIONCUSTOMIZATIONDATAMAGIC		"-1"

void InitCustomPathData(CustomPathData& pathData);
void CopyCustomPathData(const CustomPathData& src, CustomPathData& dst);

typedef CList<CPoint, CPoint&>	CPointList;


class CAutoRouterGraph;
class CAutoRouterPort;

// CAutoRouterPath

class ATL_NO_VTABLE CAutoRouterPath : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAutoRouterPath, &CLSID_AutoRouterPath>,
	public IDispatchImpl<IAutoRouterPath, &IID_IAutoRouterPath, &LIBID_GmeLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CAutoRouterPath();

DECLARE_REGISTRY_RESOURCEID(IDR_AUTOROUTERPATH)


BEGIN_COM_MAP(CAutoRouterPath)
	COM_INTERFACE_ENTRY(IAutoRouterPath)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct(void);
	void FinalRelease(void);

private:
	CComPtr<IAutoRouterGraph> owner;

// --- Ports

	CComPtr<IAutoRouterPort> startport;							// reference
	CComPtr<IAutoRouterPort> endport;							// reference

	POSITION GetPointPosAt(const CPoint& point, int nearness = 0) const;
	POSITION GetEdgePosAt(const CPoint& point, int nearness = 0) const;

// --- Points

	bool IsConnected(void) const;

// --- Edges
	CPointListPath points;

private:
	unsigned int attributes;
	int state;
	bool isAutoRoutingOn;

	std::vector<CustomPathData> customPathData;
	std::vector<CustomPathData> pathDataToDelete;

public:
	STDMETHOD(GetOwner)(IAutoRouterGraph** result);
	STDMETHOD(HasOwner)(VARIANT_BOOL* result);
	STDMETHOD(SetOwner)(IAutoRouterGraph* graph);
	// Ports
	STDMETHOD(SetStartPort)(IAutoRouterPort* port);
	STDMETHOD(SetEndPort)(IAutoRouterPort* port);
	STDMETHOD(ClearPorts)();
	STDMETHOD(GetStartPort)(IAutoRouterPort** result);
	STDMETHOD(GetEndPort)(IAutoRouterPort** result);
	// Points
	STDMETHOD(AddTail)(long px, long py);
	STDMETHOD(DeleteAll)();

	STDMETHOD(HasNoPoint)(VARIANT_BOOL* result);
	STDMETHOD(GetPointCount)(long* result);

	STDMETHOD(GetStartPoint)(long* resultX, long* resultY);
	STDMETHOD(GetEndPoint)(long* resultX, long* resultY);
	STDMETHOD(GetStartBox)(long* p1, long* p2, long* p3, long* p4);
	STDMETHOD(GetEndBox)(long* p1, long* p2, long* p3, long* p4);
	STDMETHOD(GetOutOfBoxStartPoint)(long* resultX, long* resultY, RoutingDirection hintDir);
	STDMETHOD(GetOutOfBoxEndPoint)(long* resultX, long* resultY, RoutingDirection hintDir);

	STDMETHOD(SimplifyTrivially)();

	STDMETHOD(ModifyPoints)(SAFEARRAY* pArr);
	STDMETHOD(SetPoints)(SAFEARRAY* pArr);
	STDMETHOD(GetPointList)(SAFEARRAY** pArr);
	// Edges

	STDMETHOD(GetSurroundRect)(long* p1, long* p2, long* p3, long* p4);

	STDMETHOD(IsEmpty)(VARIANT_BOOL* result);
	STDMETHOD(IsPathAt)(long px, long py, long nearness, VARIANT_BOOL* result);
	STDMETHOD(IsPathClip)(long p1, long p2, long p3, long p4, VARIANT_BOOL* result);

	STDMETHOD(SetAttributes)(long attr);
	STDMETHOD(GetAttributes)(long* result);

	STDMETHOD(IsFixed)(VARIANT_BOOL* result);
	STDMETHOD(IsMoveable)(VARIANT_BOOL* result);
	STDMETHOD(IsHighLighted)(VARIANT_BOOL* result);

	STDMETHOD(GetState)(long* result);
	STDMETHOD(IsConnected)(VARIANT_BOOL* result);
	STDMETHOD(SetState)(long state);

	STDMETHOD(GetEndDir)(RoutingDirection* result);
	STDMETHOD(GetStartDir)(RoutingDirection* result);

	STDMETHOD(SetEndDir)(long arpath_end);
	STDMETHOD(SetStartDir)(long arpath_start);
	// CustomData
	STDMETHOD(SetCustomPathData)(SAFEARRAY* pArr);
	STDMETHOD(ApplyCustomizationsBeforeAutoConnectPoints)(SAFEARRAY** pArr);
	STDMETHOD(ApplyCustomizationsAfterAutoConnectPointsAndStuff)(void);
	STDMETHOD(RemovePathCustomizations)(void);
	STDMETHOD(MarkPathCustomizationsForDeletion)(long asp);
	STDMETHOD(RemoveInvalidPathCustomizations)(long asp);
	STDMETHOD(AreTherePathCustomizations)(VARIANT_BOOL* result);
	STDMETHOD(AreThereDeletedPathCustomizations)(VARIANT_BOOL* result);
	STDMETHOD(GetDeletedCustomPathData)(SAFEARRAY** pArr);
	STDMETHOD(GetCustomizedEdgeIndexes)(SAFEARRAY** pArr);

	STDMETHOD(IsAutoRouted)(VARIANT_BOOL* result);
	STDMETHOD(SetAutoRouting)(VARIANT_BOOL autoRoutingState);
	// Other
	STDMETHOD(Destroy)();

// --- Debug
#ifdef _DEBUG
public:
	virtual void AssertValid();
	void AssertValidPos(POSITION pos) const;
	void AssertValidPoints() const;
#endif
};

OBJECT_ENTRY_AUTO(__uuidof(AutoRouterPath), CAutoRouterPath)
