#ifndef _GUIOBJECT_INCLUDED_
#define _GUIOBJECT_INCLUDED_

#include "Autoroute/AutoRouter.h"
#include "GMEStd.h"
#include <vector>

class CGMEView;
class CModelGrid;
class CDecoratorEventSink;
class CAnnotatorEventSink;

extern CModelGrid modelGrid;

void SetLocation(CRect& location, CPoint pt);
void SetSize(CRect& location, CSize s);
void SetCenter(CRect& location, CPoint pt);

class CGuiBase : public CObject
{
public:
	CGuiBase() : flag(0) {}
	CString& GetName() {return name;}
	CString& GetID() {return id;}

public:
	CString name;
	CString id;

protected:
	int flag;
};

class CGuiAspect : public CGuiBase
{
public:
	CGuiAspect(CGuiMetaAspect* meta, CGuiObject* p, int ind, int pind, const CComPtr<IMgaDecorator>& decor,
			   CComPtr<IMgaElementDecorator> newDecor, CDecoratorEventSink* decorEventSink);
	virtual ~CGuiAspect();


public:
	void InitPorts();
	
	CComPtr<IAutoRouterBox> GetRouterBox()							{ return routerBox; }
	void SetRouterBox(CComPtr<IAutoRouterBox> rbox)					{ routerBox = rbox; }
	CComPtr<IAutoRouterBox> GetRouterNameBox()						{ return routerNameBox; }
	void SetRouterNameBox(CComPtr<IAutoRouterBox> rnbox)			{ routerNameBox = rnbox; }

	const CRect& GetLocation()						{ return loc; }
	const CRect& GetNameLocation()					{ return nameLoc; }
	void SetLocation(const CRect& location);
	CComPtr<IMgaDecorator> GetDecorator()			{ return decorator; }
	CComPtr<IMgaElementDecorator> GetNewDecorator()	{ return newDecorator; }
	int	GetIndex()									{ return index; }
	CGuiPortList& GetPortList()						{ return ports; }
	CGuiObject* GetParent()							{ return parent; }
	
public:
	CGuiObject*				parent;
	CGuiMetaAspect*			guiMeta;

private:
	int						parentIndex;
	int						index;
	CGuiPortList			ports;
	CComPtr<IMgaDecorator>	decorator;
	CComPtr<IMgaElementDecorator>	newDecorator;
	CDecoratorEventSink*	decoratorEventSink;
	unsigned long			features;
	CRect					loc;
	CRect					nameLoc;
	CComPtr<IAutoRouterBox> routerBox;
	CComPtr<IAutoRouterBox> routerNameBox;
};

class CGuiPort : public CGuiBase
{
public:
	CGuiPort(CGuiAspect *asp,CComPtr<IMgaFCO> fco);
public:
	const CGuiConnectionList& GetInConns()		{ return inConns; }
	const CGuiConnectionList& GetOutConns()		{ return outConns; }

	void ReadARPreferences();
	bool GetPreference(CString& val, CString path);
	bool GetARPref(int dir);
	bool IsVisible();
	void SetVisible(bool v);
	CRect GetLocation();
	CComPtr<IAutoRouterPort> GetRouterPort()					{ return routerPort; }
	void SetRouterPort(CComPtr<IAutoRouterPort> port)			{ routerPort = port; }
	CString GetInfoText()						{ return name; }
	bool IsRealPort();

public:
	CComPtr<IMgaFCO> mgaFco;
	CGuiAspect* parent;
	CGuiConnectionList inConns;
	CGuiConnectionList outConns;

private:
	bool autorouterPrefs[GME_AR_NUM];
	CComPtr<IAutoRouterPort> routerPort;
};

class AnnotatorDecoratorData
{
public:
	AnnotatorDecoratorData()
		{ decorator = NULL; annotatorEventSink = NULL; };
	AnnotatorDecoratorData(CComPtr<IMgaElementDecorator>& nD, CAnnotatorEventSink* aES, const CRect& loc):
		decorator(nD), annotatorEventSink(aES), location(loc) {};
	~AnnotatorDecoratorData() {};

	CComPtr<IMgaElementDecorator>	decorator;
	CAnnotatorEventSink*			annotatorEventSink;
	CRect							location;
};

class CGuiAnnotator : public CGuiBase
{
public:
	CGuiAnnotator(CComPtr<IMgaModel>& pModel, CComPtr<IMgaRegNode>& mRootNode, CGMEView* vw, int numAsp);
	virtual ~CGuiAnnotator();

	void InitDecorator(int asp);
	void ToggleGrayOut()							{ GrayOut(!grayedOut); }
	void SetAspect(int a)							{ parentAspect = (a < numParentAspects ? a : 0); }
	bool IsVisible(int aspect = -1);
	bool IsSpecial()                                { return special; }
	void Draw(HDC pDC, Gdiplus::Graphics* gdip);
	void GrayOut(bool set = true);

	const CRect& GetLocation(int aspect = -1);
	void  SetLocation(const CRect& loc, int aspect = -1, bool doMga = true);
	void  ReadLocation(int aspect, CComPtr<IMgaRegNode> &aspNode);
	void  WriteLocation(int aspect = -1);

	static void SetAspect(CGuiAnnotatorList& list, int asp);
	static void GrayOutAnnotations(CGuiAnnotatorList& list, bool set = true);
	static void NudgeAnnotations(CGuiAnnotatorList& annotatorList, int right, int down);
	static void GetExtent(CGuiAnnotatorList& annotatorList, CRect& rect);
	static void GetRectList(CGuiAnnotatorList& selectedAnnotations, CRectList& annRects);
	static void MoveAnnotations(CGuiAnnotatorList& annList, CPoint& pt);
	static void FindUpperLeft(CGuiAnnotatorList& anns, int& left, int& top);
	static void ShiftAnnotations(CGuiAnnotatorList& annList, CPoint& shiftBy);
	static bool Showable( CComPtr<IMgaRegNode>& mRootNode);
	static int  Hide( CComPtr<IMgaRegNode>& mRootNode);
	CComPtr<IMgaElementDecorator> GetDecorator(int asp) { return decoratorData[asp]->decorator; }

public:
	CComPtr<IMgaRegNode>						rootNode;

protected:
	CComPtr<IMgaModel>							model;
	int											numParentAspects;
	int											parentAspect;
	bool										grayedOut;
	CGMEView*									view;
	std::vector<AnnotatorDecoratorData*>		decoratorData;
	bool										special;
};

class CGuiFco : public CGuiBase
{
public:
	CGuiFco(CComPtr<IMgaFCO>& pt, CComPtr<IMgaMetaRole>& role, CGMEView* vw, int numAsp);
	virtual ~CGuiFco() {}

public:
	bool IsReal()									{return (mgaFco != NULL);}
	bool IsType()									{return isType;}
	void ToggleGrayOut()							{ GrayOut(!grayedOut); }
	void SetAspect(int a)							{ /*VERIFY(a < numParentAspects);*/ parentAspect = (a < numParentAspects ? a : 0); }
	metaref_type GetRoleMetaRef();
	bool IsPrimary(CGuiMetaModel* guiMetaModel, int aspectInd);
	bool IsPrimary(CGuiMetaModel* guiMetaModel, CGuiMetaAspect* guiAspect);
	bool GetPreference(CString& val, CString path);
	bool GetPreference(int& val, CString path, bool hex);
	bool GetColorPreference(unsigned long& color, CString path);
	int	 GetParentAspect()							{ return parentAspect; }
	CGuiMetaModel*	GetGuiMetaParent();
	CGMEView*		GetView()						{ return view; }
	
	static bool IsPrimary(CGuiMetaModel* guiMetaModel, CGuiMetaAspect* guiAspect, CComPtr<IMgaMetaRole>& metaRole);
	static void SetAspect(CGuiFcoList& list, int asp);
	static CGuiConnection* FindConnection(CComPtr<IMgaFCO>& fco,CGuiConnectionList& conns);
	static void GrayOutFcos(CGuiFcoList &list,bool set = true);
	static void GrayOutFcos(CGuiConnectionList &list,bool set = true);
	static void GrayOutNonInternalConnections(CGuiConnectionList& list);
	static void ResetFlags(CGuiFcoList &list);

	virtual CString GetInfoText()					{ return name + " (" + roleDisplayedName + ")"; }
	virtual CGuiMetaAttributeList* GetMetaAttributes();
	virtual void RemoveFromRouter(CAutoRouter &router) = 0;
	virtual bool IsVisible(int aspect = -1) = 0;
	virtual void Draw(HDC pDC, Gdiplus::Graphics* gdip) = 0;
	virtual void GrayOut(bool set = true)			{ grayedOut = set; }

public:
	CComPtr<IMgaFCO> mgaFco;
	CComPtr<IMgaMetaRole> metaRole;
	CGuiMetaFco *guiMeta;
	CString kindName;
	CString roleName;
	CString kindDisplayedName;
	CString roleDisplayedName;

protected:
	CComPtr<IMgaMetaFCO> metaFco;
	int numParentAspects;
	int parentAspect;
	bool grayedOut;
	bool isType;
	CGMEView* view;
};

class CGuiObject : public CGuiFco
{
friend class CDecoratorEventSink;

public:
	CGuiObject(CComPtr<IMgaFCO>& pt, CComPtr<IMgaMetaRole>& role, CGMEView* vw, int numAsp);					// regular objects
	virtual ~CGuiObject();
	void InitObject(CWnd* viewWnd);								// Need this because of virtual functions

public:
	void InitAspect(int asp, CComPtr<IMgaMetaPart>& metaPart, CString& decorStr, CWnd* viewWnd);
	void GetDecoratorStr(CString& str);
	const CRect& GetLocation(int aspect = -1)			{ aspect = (aspect < 0) ? parentAspect : aspect;  return guiAspects[aspect]->GetLocation(); }
	const CRect& GetNameLocation(int aspect = -1)		{ aspect = (aspect < 0) ? parentAspect : aspect;  return guiAspects[aspect]->GetNameLocation(); }
	CSize GetSize(int aspect = -1)						{ return GetLocation(aspect).Size(); }
	CPoint GetCenter()									{ CRect rect = GetLocation(); return rect.CenterPoint();}
	void SetCenter(CPoint& pt, int aspect = -1, bool doMga = true);
	void SetSize(CSize& s, int aspect = -1, bool doMga = true);
	void SetAllSizes(CSize& s, bool doMga = true);
	void SetLocation(CRect& r, int aspect = -1, bool doMga = true);
	CSize GetNativeSize(int aspect = -1);
	void SetAllSizesToNative();							// Used by non real objects
	int	MapAspect(int parent)							{ return guiAspects[parent] ? guiAspects[parent]->GetIndex() : -1; }
	void GetNeighbors(CGuiFcoList& list);
	void GetRelationsInOut(CGuiConnectionList& list, bool inOrOut);
	CGuiPortList& GetPorts()							{ VERIFY(GetCurrentAspect()); return GetCurrentAspect()->GetPortList(); }
	CGuiAspect* GetCurrentAspect()						{ return guiAspects[parentAspect]; }
	CGuiPort* FindPort(CPoint& pt, bool lookNearToo = false);
	CGuiPort* FindPort(CComPtr<IMgaFCO> mgaFco);
	CComPtr<IAutoRouterBox> GetRouterBox()				{ return GetCurrentAspect()->GetRouterBox(); }
	CComPtr<IAutoRouterBox>  GetRouterNameBox()			{ return GetCurrentAspect()->GetRouterNameBox(); }
	void SetRouterBox(CComPtr<IAutoRouterBox> rbox)		{ GetCurrentAspect()->SetRouterBox(rbox) ; }
	void SetRouterNameBox(CComPtr<IAutoRouterBox> rnbox){ GetCurrentAspect()->SetRouterNameBox(rnbox) ; }
	void ReadAllLocations();
	void WriteLocation(int aspect = -1);
	bool IsHotspotEnabled() const						{ return isHotspotEnabled; }
	void DeleteCustomizationOfConnections(CGuiConnectionList& conns, int aspect);
	void DeleteCustomizationOfInOutConnections(int aspect);

public:
	void GrayOutNeighbors();
	bool IsInside(CPoint& pt, bool lookNearToo = false);
	bool IsLabelInside(CPoint& pt, bool lookNearToo = false);

	void IncrementAnimRefCnt();
	void DecrementAnimRefCnt();

	static void GetExtent(CGuiFcoList& objectList, CRect& rect);
	static void GetExtent(CGuiObjectList& objectList,CRect& rect);
	static CSize GetExtent(CGuiFcoList& list)			{CRect rect; GetExtent(list, rect); return rect.Size();}
	static void MoveObjects(CGuiFcoList& fcoList, CPoint& pt);
	static void MoveObjects(CGuiObjectList& objectList, CPoint& pt);
	static void FindUpperLeft(CGuiObjectList& objs, int& left, int& top);
	static void ShiftModels(CGuiObjectList& objList, CPoint& shiftBy);
	void ResizeObject(const CRect& newLocation);
	static bool NudgeObjects(CGuiObjectList& modelList, int right, int down);
	static CGuiObject* FindObject(CComPtr<IMgaFCO>& fco, CGuiFcoList& fcoList);
	static void GetRectList(CGuiObjectList& objList, CRectList& rects);

	virtual bool IsVisible(int aspect = -1)				{ return guiAspects[(aspect < 0 ? parentAspect : aspect)] != NULL; }
	virtual void RemoveFromRouter(CAutoRouter& router)	{ router.DeleteObject(this); }
	virtual void Draw(HDC pDC, Gdiplus::Graphics* gdip);
	virtual void GrayOut(bool set);
	virtual CGuiMetaAspect* GetKindAspect(CComPtr<IMgaMetaPart> metaPart);

protected:
	CArray<CGuiAspect*,CGuiAspect*>	guiAspects;
	bool isHotspotEnabled;
};


class CGuiCompound : public CGuiObject
{
public:
	CGuiCompound(CComPtr<IMgaFCO>& pt,CComPtr<IMgaMetaRole>& role, CGMEView* vw, int numAsp) : CGuiObject(pt, role, vw, numAsp) {}
};

class CGuiModel : public CGuiCompound
{
public:
	CGuiModel(CComPtr<IMgaFCO>& pt, CComPtr<IMgaMetaRole>& role, CGMEView* vw, int numAsp);

	virtual CGuiMetaAspect* GetKindAspect(CComPtr<IMgaMetaPart> metaPart);
	virtual CGuiMetaAttributeList* GetMetaAttributes();
};

class CReference
{
public:
	CReference(CComPtr<IMgaFCO> mgaRefd, CComPtr<IMgaFCO> mgaTermRefd);

public:
	bool IsNull()							{ return mgaReferee == NULL; }
	CComPtr<IMgaFCO>& GetTerminalReferee()	{ return mgaTerminalReferee; }
	CString GetInfoText(CString &name);

protected:
	CComPtr<IMgaFCO> mgaReferee;
	CComPtr<IMgaFCO> mgaTerminalReferee;
	CString targetName;
	CString targetKindDisplayedName;
};

// both null and atom ref
class CGuiReference : public CGuiObject, public CReference
{
public:
	CGuiReference(CComPtr<IMgaFCO>& pt, CComPtr<IMgaMetaRole>& role, CGMEView* vw, int numAsp, CComPtr<IMgaFCO> mgaRefd, CComPtr<IMgaFCO> mgaTermRefd) : CGuiObject(pt, role, vw, numAsp), CReference(mgaRefd, mgaTermRefd) {}
public:
	virtual CString GetInfoText() { return CReference::GetInfoText(name); }
};

class CGuiCompoundReference : public CGuiCompound, public CReference
{
public:
	CGuiCompoundReference(CComPtr<IMgaFCO>& pt, CComPtr<IMgaMetaRole>& role, CGMEView* vw, int numAsp, CComPtr<IMgaFCO> mgaRefd, CComPtr<IMgaFCO> mgaTermRefd) : CGuiCompound(pt, role, vw, numAsp), CReference(mgaRefd, mgaTermRefd) {}
public:
	virtual CString GetInfoText() { return CReference::GetInfoText(name); }
	virtual CGuiMetaAttributeList* GetMetaAttributes();
	virtual CGuiMetaAspect* GetKindAspect(CComPtr<IMgaMetaPart> metaPart);
};


class CGuiSet : public CGuiObject
{
public:
	CGuiSet(CComPtr<IMgaFCO>& pt, CComPtr<IMgaMetaRole>& role, CGMEView* vw, int numAsp) : CGuiObject(pt, role, vw, numAsp) {}

public:
	void Init(CGuiFcoList& fcos, CGuiConnectionList& conns);
	bool CheckMember(CGuiFco* fco);
	bool ToggleMember(CGuiFco* member);
	void GrayOutMembers(bool set = true)	{ GrayOutFcos(members, set); }

protected:
	CGuiFcoList members;
};

class CGuiConnectionLabel {
private:
	CString label;
	CPoint loc;
	int alignment;
	bool primary;
public:
	CGuiConnectionLabel();
	virtual ~CGuiConnectionLabel() {};
	void SetLabel(const CString& l);
	void SetPrimary(bool prim)	{ primary = prim; }
	void SetLocation(const CPoint& endPoint, const CPoint& nextPoint, const CRect& box);
	void Draw(Gdiplus::Graphics* gdip, COLORREF color, CGuiConnection* conn);
};

class CGuiConnectionLabelSet {
public:
	CGuiConnectionLabelSet();
	virtual ~CGuiConnectionLabelSet() {};
private:
	CGuiConnectionLabel labels[GME_CONN_LABEL_NUM];
public:
	void SetLabel(int index, const CString& label);
	void SetLocation(int index, const CPoint& endPoint, const CPoint& nextPoint, const CRect& box);
	void Draw(Gdiplus::Graphics* gdip, COLORREF color, CGuiConnection* conn);
};

enum ConnectionPartMoveType {
	HorizontalEdgeMove			= 0,
	VerticalEdgeMove			= 1,
	AdjacentEdgeMove			= 2,
	InsertNewCustomPoint		= 3,
	ModifyExistingCustomPoint	= 4
};

class CGuiConnection : public CGuiFco
{
public:
	CGuiConnection(CComPtr<IMgaFCO>& pt, CComPtr<IMgaMetaRole>& role, CGMEView* vw, int numAsp, bool resolve = true);
	virtual ~CGuiConnection() { delete visible; }

	void RefreshAttributeCache();
	CComPtr<IAutoRouterPath> GetRouterPath()				{ return routerPath; }
	void SetRouterPath(CComPtr<IAutoRouterPath> path) 		{ routerPath = path; }
	void GrayOutEndPoints();
	void ToggleHover()										{ hovered = !hovered; }
	void SetSelect(bool sel)								{ selected = sel; }
	void GiveConnectionEndErroMessage(const CString& mainMsg, const CGuiPort* otherPort) const;
	void Resolve();
	void ReadARPreferences();
	bool GetARPref(int dir) const { return autorouterPrefs[dir]; }
	void GetPointList(CPointList& points) const;
	int GetEdgeCount(void) const;
	bool AdjustCoordLimits(CPointList& points, int edgeIndex, bool isPathEnd, bool xOrY, POSITION pos,
						   int ptCoord, int lastlastCoord, int& coordMinLimit, int& coordMaxLimit) const;
	int GetEdgeIndex(const CPoint& point, CPoint& startPoint, CPoint& endPoint, CPoint& thirdPoint,
					 ConnectionPartMoveType& connectionMoveMethod, bool& horizontalOrVerticalEdge,
					 bool& isPartFixed, int& xMinLimit, int& xMaxLimit,
					 int& yMinLimit, int& yMaxLimit) const;
	int IsPathAt(const CPoint& point, ConnectionPartMoveType& connectionMoveMethod, bool& horizontalOrVerticalEdge,
				 bool& isPartFixed) const;
	void ReadCustomPathData(void);
	void WriteCustomPathData(bool handleTransaction = true);
	void InsertCustomPathData(CustomPathData& pathData);
	void UpdateCustomPathData(CustomPathData& pathData);
	std::vector<CustomPathData> GetCurrentPathCustomizations(void);
	bool HasPathCustomization(void) const;
	bool HasPathCustomization(int asp) const;
	bool HasPathCustomization(int asp, int pathIndex) const;
	void DeletePathCustomization(CustomPathData& pathData);
	bool DeleteAllPathCustomizationsForAnAspect(int asp);
	void RemoveDeletedPathCustomizations(const std::vector<CustomPathData>& customPathDat);
	bool IsConnectionAutoRouted(void) const;
	void SetConnectionAutoRouted(bool autoRouteState);
	void ReadConnectionAutoRouteState(void);
	void WriteConnectionAutoRouteState(bool handleTransaction = true);

	virtual bool IsVisible(int aspect = -1)				{ return visible && visible[aspect < 0 ? parentAspect : aspect]; }
	virtual void RemoveFromRouter(CAutoRouter &router);
	virtual void Draw(HDC pDC, Gdiplus::Graphics* gdip);

protected:

public:
	CGuiObject* src;
	CGuiPort* srcPort;
	CGuiObject* dst;
	CGuiPort* dstPort;
	CMapStringToString	attributeCache;

private:
	CComPtr<IAutoRouterPath> routerPath;
	CGuiConnectionLabelSet labelset;
	bool* visible;
	int lineType;
	int srcStyle;
	int dstStyle;
	COLORREF color;
	COLORREF nameColor;
	bool autorouterPrefs[GME_AR_NUM];
	bool hovered;
	bool selected;
	bool autoRouted;
	std::vector<CustomPathData> customPathData;
};





#endif // whole file
