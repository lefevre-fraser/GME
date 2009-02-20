// AutoRouterPort.h : Declaration of the CAutoRouterPort

#pragma once
#include "resource.h"       // main symbols

#include "AutoRoute/ArHelper.h" 

#include "GME.h"
#include "gmelib.h"

#include "AutoRouterBox.h"

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
class CAutoRouterPath;
class CAutoRouterGraph;

// CAutoRouterPort

class ATL_NO_VTABLE CAutoRouterPort : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAutoRouterPort, &CLSID_AutoRouterPort>,	
	public IDispatchImpl<IAutoRouterPort, &IID_IAutoRouterPort, &LIBID_GmeLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CAutoRouterPort();

	//only the COM interface methods are public, thus we need lots of friends
	friend CAutoRouterBox;
	friend CAutoRouterEdgeList;
	friend CAutoRouterGraph;

DECLARE_REGISTRY_RESOURCEID(IDR_AUTOROUTERPORT)


BEGIN_COM_MAP(CAutoRouterPort)
	COM_INTERFACE_ENTRY(IAutoRouterPort)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
		this->SetOwner(NULL);
	}

private:
	int CanHaveStartEndPointOn(EArDir dir, int isstart) const;
	int CanHaveStartEndPoint(int isstart) const;
	int CanHaveStartEndPointHorizontal(int ishorizontal) const;
	int IsConnectToCenter() const { return (attributes & ARPORT_ConnectToCenter) != 0; }
	EArDir GetStartEndDirTo(CPoint point, int isstart, EArDir notthis = Dir_None) const;

	int CanCreateStartEndPointAt(CPoint point, int isstart, int nearness = 0) const;
	CPoint CreateStartEndPointAt(CPoint point, int isstart) const;
	CPoint CreateStartEndPointOn(EArDir dir) const;
	CPoint CreateStartEndPointTo(CPoint point, int isstart) const;

	unsigned int GetAttributes() const { return attributes; }
	bool HasLimitedDirs() { return limitedDirections; }

	CRect GetRect() const { return rect; }
	CPoint GetCenter() const { return rect.CenterPoint(); }
	int IsRectEmpty() const { return rect.IsRectEmpty(); }
	EArDir OnWhichEdge(CPoint point) const { return ::OnWhichEdge(rect, point); }

	int IsPortAt(CPoint point, int nearness = 0) const { return IsPointIn(point, rect, nearness); }
	int IsPortIn(CRect r) const { return IsRectIn(rect, r); }
	int IsPortClip(CRect r) const { return IsRectClip(rect, r); }

	void CalculateSelfPoints();

	void ShiftBy(CSize offset);

	void SetOwner(CComObjPtr<CAutoRouterBox> box);

public:
	STDMETHOD(SetRect)(long p1, long p2, long p3, long p4);
	STDMETHOD(SetAttributes)(long attr);
	STDMETHOD(SetLimitedDirs)(long p_ltd);
	STDMETHOD(GetOwner)(IAutoRouterBox** result);

private:
	unsigned int attributes;

	bool  limitedDirections; // strictly respect the preferred directions (for ports East/West directions must be respected)
	CRect rect;
	CPoint selfpoints[4];

	CComObjPtr<CAutoRouterBox> owner;
};

inline CPoint CAutoRouterPort::CreateStartEndPointTo(CPoint point, int isstart) const
{
	return CreateStartEndPointOn(GetStartEndDirTo(point, isstart));
}

OBJECT_ENTRY_AUTO(__uuidof(AutoRouterPort), CAutoRouterPort)
