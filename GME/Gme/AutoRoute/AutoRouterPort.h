// AutoRouterPort.h : Declaration of the CAutoRouterPort

#pragma once
#include "resource.h"       // main symbols

#include "AutoRoute/ArHelper.h" 

#include "AutoRouterBox.h"

#include "GME.h"
#include "gmelib.h"

#include <vector>

#define ARPORT_EndOnTop					0x0001
#define ARPORT_EndOnRight				0x0002
#define ARPORT_EndOnBottom				0x0004
#define ARPORT_EndOnLeft				0x0008
#define ARPORT_EndOnAll					0x000F

#define ARPORT_StartOnTop				0x0010
#define ARPORT_StartOnRight				0x0020
#define ARPORT_StartOnBottom			0x0040
#define ARPORT_StartOnLeft				0x0080
#define ARPORT_StartOnAll				0x00F0

#define ARPORT_ConnectOnAll				0x00FF
#define ARPORT_ConnectToCenter			0x0100

#define ARPORT_StartEndHorizontal		0x00AA
#define ARPORT_StartEndVertical			0x0055

#define ARPORT_Default					0x00FF



class CAutoRouterBox;
class CAutoRouterEdgeList;
class CAutoRouterGraph;

// CAutoRouterPort

class ATL_NO_VTABLE CAutoRouterPort : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAutoRouterPort, &CLSID_AutoRouterPort>,
	public IDispatchImpl<IAutoRouterPort, &IID_IAutoRouterPort, &LIBID_GmeLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CAutoRouterPort();

DECLARE_REGISTRY_RESOURCEID(IDR_AUTOROUTERPORT)


BEGIN_COM_MAP(CAutoRouterPort)
	COM_INTERFACE_ENTRY(IAutoRouterPort)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct(void);
	void FinalRelease(void);

private:
	void CalculateSelfPoints();

public:
	STDMETHOD(GetOwner)(IAutoRouterBox** result);
	STDMETHOD(HasOwner)(VARIANT_BOOL* result);
	STDMETHOD(SetOwner)(IAutoRouterBox* box);

	STDMETHOD(GetRect)(long* p1, long* p2, long* p3, long* p4);
	STDMETHOD(IsRectEmpty)(VARIANT_BOOL* result);
	STDMETHOD(GetCenter)(long* px, long* py);
	STDMETHOD(SetRect)(long p1, long p2, long p3, long p4);
	STDMETHOD(ShiftBy)(long offsetx, long offsety);
	STDMETHOD(GetSelfPoints)(long* p1x, long* p1y, long* p2x, long* p2y, long* p3x, long* p3y, long* p4x, long* p4y);

	STDMETHOD(GetAttributes)(long* result);
	STDMETHOD(SetAttributes)(long attr);
	STDMETHOD(IsConnectToCenter)(VARIANT_BOOL* result);
	STDMETHOD(HasLimitedDirs)(VARIANT_BOOL* result);
	STDMETHOD(SetLimitedDirs)(VARIANT_BOOL ltd);

	STDMETHOD(IsPortAt)(long px, long py, long nearness, VARIANT_BOOL* result);
	STDMETHOD(IsPortClip)(long p1, long p2, long p3, long p4, VARIANT_BOOL* result);
	STDMETHOD(IsPortIn)(long p1, long p2, long p3, long p4, VARIANT_BOOL* result);
	STDMETHOD(OnWhichEdge)(long px, long py, RoutingDirection* result);

	STDMETHOD(CanHaveStartEndPointOn)(RoutingDirection dir, long isstart, VARIANT_BOOL* result);
	STDMETHOD(CanHaveStartEndPoint)(long isstart, VARIANT_BOOL* result);
	STDMETHOD(CanHaveStartEndPointHorizontal)(long ishorizontal, VARIANT_BOOL* result);
	STDMETHOD(GetStartEndDirTo)(long px, long py, long isstart, RoutingDirection notthis, RoutingDirection* result);

	STDMETHOD(CanCreateStartEndPointAt)(long px, long py, long isstart, long nearness, VARIANT_BOOL* result);
	STDMETHOD(CreateStartEndPointAt)(long px, long py, long isstart, long* resultX, long* resultY);
	STDMETHOD(CreateStartEndPointTo)(long px, long py, long isstart, long* resultX, long* resultY);
	STDMETHOD(CreateStartEndPointOn)(RoutingDirection dir, long* resultX, long* resultY);

private:
	unsigned int attributes;

	bool  limitedDirections; // strictly respect the preferred directions (for ports East/West directions must be respected)
	CRect rect;
	CPoint selfpoints[4];

	CComPtr<IAutoRouterBox> owner;

#ifdef _DEBUG
public:
	virtual void AssertValid() const;
	void AssertValidStartEndPoint(const CPoint& point, RoutingDirection dir, int isstart);
#endif
};

OBJECT_ENTRY_AUTO(__uuidof(AutoRouterPort), CAutoRouterPort)
