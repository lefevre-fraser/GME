#include "stdafx.h"

#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "GMEApp.h"
#include "GMEstd.h"
#include "GMEOLEData.h"
#include "PendingObjectPosRequest.h"
#include "GMEView.h"
#include "GraphicsUtil.h"
#include "GuiMeta.h"
#include "GuiObject.h"
#include "ModelGrid.h"
#include "DecoratorEventSink.h"
#include "AnnotatorEventSink.h"

#include "AutoRoute/AutoRouterGraph.h"
#include "AutoRoute/AutoRouter.h"
#include "AutoRoute/AutoRouterPath.h"

#include "GMEEventLogger.h"
#include "MainFrm.h"


CModelGrid modelGrid;

/////////////////////////////// Helper functions /////////////////////////////////

void SetLocation(CRect& location, CPoint pt)
{
	CSize size = location.Size();
	int cx = pt.x + size.cx / 2;
	int cy = pt.y + size.cy / 2;
	cx = (cx / GME_GRID_SIZE) * GME_GRID_SIZE;
	cy = (cy / GME_GRID_SIZE) * GME_GRID_SIZE;
	while((cx - (size.cx / 2)) <= 0)
		cx += GME_GRID_SIZE;
	while((cy - (size.cy / 2)) <= 0)
		cy += GME_GRID_SIZE;
	pt.x = cx - size.cx / 2;
	pt.y = cy - size.cy / 2;
	location.right += pt.x - location.left;
	location.left = pt.x;
	location.bottom += pt.y - location.top;
	location.top = pt.y;
}

void SetSize(CRect& location, CSize s)
{
	if((s.cx % 2) == 0)
		s.cx--;
	if((s.cy % 2) == 0)
		s.cy--;

	CPoint pt = location.CenterPoint();
	int cx = pt.x;
	int cy = pt.y;
	pt.x = (cx / GME_GRID_SIZE) * GME_GRID_SIZE;
	pt.y = (cy / GME_GRID_SIZE) * GME_GRID_SIZE;
	while((pt.x - (s.cx / 2)) <= 0)
		pt.x += GME_GRID_SIZE;
	while((pt.y - (s.cy / 2)) <= 0)
		pt.y += GME_GRID_SIZE;
	location.left = pt.x - s.cx / 2;
	location.right = location.left + s.cx;
	location.top = pt.y - s.cy / 2;
	location.bottom = location.top + s.cy;
}

void SetCenter(CRect& location, CPoint pt)
{
	ASSERT((pt.x % GME_GRID_SIZE) == 0);
	ASSERT((pt.y % GME_GRID_SIZE) == 0);
	CSize size = location.Size();
	int dx = size.cx / 2;
	int dy = size.cy / 2;
	while(pt.x - dx <= 0)
		pt.x += GME_GRID_SIZE;
	while(pt.y - dy <= 0)
		pt.y += GME_GRID_SIZE;
	int x1 = pt.x - dx;
	int y1 = pt.y - dy;
	location.left = x1;
	location.right = x1 + size.cx;
	location.top = y1;
	location.bottom = y1 + size.cy;
}

void SetCenterNoMga(CRect& location, CPoint pt)
{
	CSize size = location.Size();
	int dx = size.cx / 2;
	int dy = size.cy / 2;
	int x1 = pt.x - dx;
	int y1 = pt.y - dy;
	location.left = x1;
	location.right = x1 + size.cx;
	location.top = y1;
	location.bottom = y1 + size.cy;
}

//////////////////////////////////// CGuiAspect /////////////////////////////

////////////////////////////////////
// Non-virtual methods of CGuiAspect
////////////////////////////////////
CGuiAspect::CGuiAspect(CGuiMetaAspect* meta, CGuiObject* p, int ind, int pind, const CComPtr<IMgaDecorator>& decor,
					   CComPtr<IMgaElementDecorator> newDecor, CDecoratorEventSink* decorEventSink):
	guiMeta(meta),
	parent(p),
	index(ind),
	parentIndex(pind),
	decorator(decor),
	newDecorator(newDecor),
	decoratorEventSink(decorEventSink),
	routerBox(0),
	routerNameBox(0)
{
	try {
		COMTHROW(decor->GetFeatures(&features));
	}
	catch (hresult_exception &) {
		features = 0UL;
	}
	name = meta->name;
	if (parent->IsReal()) {
		InitPorts();
	}

	if (features & F_ANIMATION) {
		parent->IncrementAnimRefCnt();
	}
}

CGuiAspect::~CGuiAspect()
{
	if (newDecorator) {
		COMTHROW(newDecorator->Destroy());
		newDecorator.Release();
		newDecorator = NULL;
	} else {
		COMTHROW(decorator->Destroy());
	}
	decorator.Release();
	decorator = NULL;
	if (decoratorEventSink != NULL) {
		ASSERT(decoratorEventSink->m_dwRef == 1);
		decoratorEventSink->ExternalRelease();	// calls InternalRelease which calls OnFinalRelease which calls delete this if m_dwRef is 0
		decoratorEventSink = NULL;
	}
	POSITION pos = ports.GetHeadPosition();
	while(pos) {
		delete ports.GetNext(pos);
	}
	if (features & F_ANIMATION) {
		parent->DecrementAnimRefCnt();
	}
}

void CGuiAspect::InitPorts()
{
	CComPtr<IMgaFCOs> portFcos;
	COMTHROW(decorator->GetPorts(&portFcos));
	if (portFcos) {
		CComPtr<IMgaFCO> fco;
		MGACOLL_ITERATE(IMgaFCO,portFcos) {
			fco = MGACOLL_ITER;
			CGuiPort *p = new CGuiPort(this,fco);
			ports.AddTail(p);
		}
		MGACOLL_ITERATE_END;
	}
	CGuiPort *p = new CGuiPort(this,parent->mgaFco);
	ports.AddTail(p);

}

void CGuiAspect::SetLocation(const CRect& location)
{
	loc = location; 
	
	try {
		COMTHROW(decorator->SetLocation(location.left, location.top, location.right, location.bottom));
		long sx, sy, ex, ey;
		COMTHROW(decorator->GetLabelLocation(&sx, &sy, &ex, &ey));
		
		/*
		sx = min(sx, location.right-1);
		ex = max(ex, location.left+1);
		sy = min(sy, location.bottom-1);
		ey = max(ey, location.top+1);
		*/
		if (sx != 0 && ex != 0 && sy != 0 && ey != 0) {
			sx = min(sx, location.right+1);
			ex = max(ex, location.left-1);
			sy = min(sy, location.bottom+1);
			ey = max(ey, location.top-1);
		}
		nameLoc.SetRect(sx, sy, ex, ey);
	} catch (hresult_exception &) {
			ASSERT(false);
	}
}
////////////////////////////////////
// Static methods of CGuiAspect
////////////////////////////////////

////////////////////////////////////
// Virtual methods of CGuiAspect
////////////////////////////////////


////////////////////////////////// CGuiPort /////////////////////////////

////////////////////////////////////
// Non-virtual methods of CGuiPort
////////////////////////////////////
CGuiPort::CGuiPort(CGuiAspect* asp, CComPtr<IMgaFCO> fco) : parent(asp), mgaFco(fco)
{
	CComBSTR bstr;
	COMTHROW(fco->get_Name(&bstr));
	CopyTo(bstr,name);

	bstr.Empty();
	COMTHROW(fco->get_ID(&bstr));
	CopyTo(bstr,id);

	if (!IsRealPort()) {
		ReadARPreferences();
	}

}

bool CGuiPort::GetPreference(CString &val, CString path)
{
	VERIFY(mgaFco);
	CComBSTR pathBstr;
	CopyTo(path, pathBstr);
	CComBSTR bstrVal;
	COMTHROW(mgaFco->get_RegistryValue(pathBstr,&bstrVal));
	CopyTo(bstrVal, val);
	return !val.IsEmpty();
}



void CGuiPort::ReadARPreferences()
{
	CString val;
	if (GetPreference(val, AUTOROUTER_PREF)) {
		autorouterPrefs[GME_START_NORTH] = (val.Find("N") != -1);
		autorouterPrefs[GME_START_EAST] = (val.Find("E") != -1);
		autorouterPrefs[GME_START_SOUTH] = (val.Find("S") != -1);
		autorouterPrefs[GME_START_WEST] = (val.Find("W") != -1);
		autorouterPrefs[GME_END_NORTH] = (val.Find("n") != -1);
		autorouterPrefs[GME_END_EAST] = (val.Find("e") != -1);
		autorouterPrefs[GME_END_SOUTH] = (val.Find("s") != -1);
		autorouterPrefs[GME_END_WEST] = (val.Find("w") != -1);
	}
	else {
		if (parent->GetParent()->dynamic_cast_CGuiCompound() != NULL) {
			autorouterPrefs[GME_START_NORTH] = true;
			autorouterPrefs[GME_START_EAST] = false;
			autorouterPrefs[GME_START_SOUTH] = true;
			autorouterPrefs[GME_START_WEST] = false;
			autorouterPrefs[GME_END_NORTH] = true;
			autorouterPrefs[GME_END_EAST] = false;
			autorouterPrefs[GME_END_SOUTH] = true;
			autorouterPrefs[GME_END_WEST] = false;
		} else {
			autorouterPrefs[GME_START_NORTH] = true;
			autorouterPrefs[GME_START_EAST] = true;
			autorouterPrefs[GME_START_SOUTH] = true;
			autorouterPrefs[GME_START_WEST] = true;
			autorouterPrefs[GME_END_NORTH] = true;
			autorouterPrefs[GME_END_EAST] = true;
			autorouterPrefs[GME_END_SOUTH] = true;
			autorouterPrefs[GME_END_WEST] = true;
		}
	}
}

bool CGuiPort::GetARPref(int dir)
{
	if (IsRealPort()) {
		CRect parentLoc = parent->GetLocation();
		if (GetLocation().CenterPoint().x < (parentLoc.Size().cx / 2)) {
			autorouterPrefs[GME_START_NORTH] = false;
			autorouterPrefs[GME_START_EAST] = false;
			autorouterPrefs[GME_START_SOUTH] = false;
			autorouterPrefs[GME_START_WEST] = true;
			autorouterPrefs[GME_END_NORTH] = false;
			autorouterPrefs[GME_END_EAST] = false;
			autorouterPrefs[GME_END_SOUTH] = false;
			autorouterPrefs[GME_END_WEST] = true;
		} else {
			autorouterPrefs[GME_START_NORTH] = false;
			autorouterPrefs[GME_START_EAST] = true;
			autorouterPrefs[GME_START_SOUTH] = false;
			autorouterPrefs[GME_START_WEST] = false;
			autorouterPrefs[GME_END_NORTH] = false;
			autorouterPrefs[GME_END_EAST] = true;
			autorouterPrefs[GME_END_SOUTH] = false;
			autorouterPrefs[GME_END_WEST] = false;

		}
	}
	return autorouterPrefs[dir];
}


bool CGuiPort::IsVisible()			// called on a tmp obj that only exists to get this info
{
	bool visible = true;
	VERIFY(parent);
	VERIFY(parent->parent);
	CComPtr<IMgaFCO> fco = parent->parent->mgaFco;
	CComBSTR bstr = "GME/ports";
	CComPtr<IMgaRegNode> root;
	COMTHROW(fco->get_RegistryNode(bstr,&root));
	CComPtr<IMgaRegNodes> nodes;

#pragma warning(disable: 4310) // cast truncates constant value
	VARIANT_BOOL vb = VARIANT_TRUE;
#pragma warning(default: 4310) // cast truncates constant value
	COMTHROW(root->get_SubNodes(vb,&nodes));
	MGACOLL_ITERATE(IMgaRegNode,nodes) {
		CComPtr<IMgaRegNode> reg;
		reg = MGACOLL_ITER;
		CComPtr<IMgaFCO> portFco;
		COMTHROW(reg->get_FCOValue(&portFco));
		if(IsEqualObject(portFco,mgaFco)) {
			CComPtr<IMgaRegNode> subreg;
			CComBSTR path = "visible";
			COMTHROW(reg->get_SubNodeByName(path,&subreg));
			if(subreg != 0) {
				CComBSTR val;
				COMTHROW(subreg->get_Value(&val));
				CString value;
				CopyTo(val,value);
				int v;
				if(_stscanf((LPCTSTR)value,_T("%d"),&v) > 0)
					visible = v ? true : false;
			}
			break;
		}
	}
	MGACOLL_ITERATE_END;
	return visible;
}

void CGuiPort::SetVisible(bool v)	// called on a tmp obj that only exists to set this info
{
	VERIFY(parent);
	VERIFY(parent->parent);
	CComPtr<IMgaFCO> fco = parent->parent->mgaFco;
	CComBSTR id;
	CComBSTR bstr = "GME/ports/";
	COMTHROW(mgaFco->get_ID(&id));
	bstr += id;
	CComPtr<IMgaRegNode> reg;
	COMTHROW(fco->get_RegistryNode(bstr,&reg));
	COMTHROW(reg->put_FCOValue(mgaFco));
	CComBSTR path = "visible";
	CComPtr<IMgaRegNode> subreg;
	COMTHROW(reg->get_SubNodeByName(path,&subreg));
	CComBSTR bstrval = v ? "1" : "0";
	COMTHROW(subreg->put_Value(bstrval));
}

CRect CGuiPort::GetLocation()
{
	long sx = 0;
	long sy = 0;
	long ex = 0;
	long ey = 0;
	if (!IsRealPort()) {
		CSize size = parent->GetLocation().Size();
		sx = sy = 0;
		ex = size.cx;
		ey = size.cy;
	}
	else {
		try {
			parent->GetDecorator()->GetPortLocation(mgaFco, &sx, &sy, &ex, &ey);
		}
		catch(hresult_exception& e) {
			if (e.hr != E_DECORATOR_PORTNOTFOUND) {
				throw e;
			}
		}
	}
	return CRect(sx, sy, ex, ey);
}

bool CGuiPort::IsRealPort() {
	return !mgaFco.IsEqualObject(parent->GetParent()->mgaFco);
}

////////////////////////////////////
// Static methods of CGuiPort
////////////////////////////////////

////////////////////////////////////
// Virtual methods of CGuiPort
////////////////////////////////////

////////////////////////////////// CGuiAnnotator /////////////////////////////

////////////////////////////////////
// Non-virtual methods of CGuiAnnotator
////////////////////////////////////
CGuiAnnotator::CGuiAnnotator(CComPtr<IMgaModel>& pModel, CComPtr<IMgaRegNode>& mRootNode, CGMEView* vw, int numAsp)
{
	model = pModel;
	rootNode = mRootNode;
	numParentAspects = numAsp;
	parentAspect = 0;
	grayedOut = false;
	view = vw;
	special = false;

	for (int i = 0; i < numAsp; i++) {
		decoratorData.push_back(new AnnotatorDecoratorData());
	}

	try {
		CComBSTR bName;
		COMTHROW(rootNode->get_Name(&bName));
		name = bName;

		long st; // if main node status is inherited it means it is a special node
		COMTHROW(rootNode->get_Status( &st));
		if( st > ATTSTATUS_HERE)
			special = true;

		id = view->name + ":" + name;		// Fake id

		CComPtr<IMgaRegNode> aspRootNode;
		CComBSTR aspRootName(AN_ASPECTS);
		COMTHROW(rootNode->get_SubNodeByName(aspRootName, &aspRootNode));

		if (aspRootNode) {
			CComPtr<IMgaRegNodes>	aspNodes;
#pragma warning(disable: 4310) // cast truncates constant value
			COMTHROW(aspRootNode->get_SubNodes(VARIANT_TRUE, &aspNodes));
#pragma warning(default: 4310) // cast truncates constant value
			MGACOLL_ITERATE(IMgaRegNode, aspNodes) {
				CComPtr<IMgaRegNode>	aspNode;
				aspNode = MGACOLL_ITER;
				CComBSTR aspName;
				COMTHROW(aspNode->get_Name(&aspName));
				CString aspNameStr(aspName);
				if (aspNameStr != AN_DEFASPECT) {
					CGuiMetaAspect *guiMetaAsp = view->guiMeta->FindAspect(aspNameStr);
					if (guiMetaAsp) {
						ReadLocation(guiMetaAsp->index, aspNode);
						InitDecorator(guiMetaAsp->index);
					}
				}
			}
			MGACOLL_ITERATE_END;

			CComPtr<IMgaRegNode> defAspNode;
			CComBSTR defAspName(AN_DEFASPECT);
			COMTHROW(aspRootNode->get_SubNodeByName(defAspName, &defAspNode));
			long status;
			COMTHROW(defAspNode->get_Status(&status));
			if (status != ATTSTATUS_UNDEFINED) {
				for (int i = 0; i < numParentAspects; i++) {
					if (decoratorData[i]->decorator == NULL) {
						ReadLocation(i, defAspNode);
						InitDecorator(i);
					}
				}
			}
		}
	}
	catch(hresult_exception &e) {
		for (std::vector<AnnotatorDecoratorData*>::iterator ii = decoratorData.begin(); ii != decoratorData.end(); ++ii) {
			if ((*ii)->decorator != NULL) {
				COMTHROW((*ii)->decorator->Destroy());
				(*ii)->decorator.Release();
				(*ii)->decorator = NULL;
			}
			CAnnotatorEventSink* annotatorEventSink = (*ii)->annotatorEventSink;
			delete (*ii);
			if (annotatorEventSink != NULL)
				annotatorEventSink->ExternalRelease();	// calls InternalRelease which calls OnFinalRelease which calls delete this if m_dwRef is 0
		}
		decoratorData.clear();

		numParentAspects = 0;
		parentAspect = 0;
		throw hresult_exception(e.hr);
		return;
	}
}

CGuiAnnotator::~CGuiAnnotator()
{
	for (std::vector<AnnotatorDecoratorData*>::iterator ii = decoratorData.begin(); ii != decoratorData.end(); ++ii) {
		if ((*ii)->decorator != NULL)
			COMTHROW((*ii)->decorator->Destroy());
		CAnnotatorEventSink* annotatorEventSink = (*ii)->annotatorEventSink;
		delete (*ii);
		if (annotatorEventSink != NULL) {
			ASSERT(annotatorEventSink->m_dwRef == 1);
			annotatorEventSink->ExternalRelease();	// calls InternalRelease which calls OnFinalRelease which calls delete this if m_dwRef is 0
		}
	}
	decoratorData.clear();
}

void CGuiAnnotator::InitDecorator(int asp)
{
	try {
		CComPtr<IMgaElementDecoratorEvents> annotatorEventSinkIface;
		CString progId = AN_NEWDECORATOR_PROGID;
		COMTHROW(decoratorData[asp]->decorator.CoCreateInstance(PutInBstr(progId)));
		decoratorData[asp]->annotatorEventSink = new CAnnotatorEventSink();
		HRESULT hr = decoratorData[asp]->annotatorEventSink->QuerySinkInterface((void**) &annotatorEventSinkIface);
		if (hr == S_OK) {
			decoratorData[asp]->annotatorEventSink->SetView(view);
			decoratorData[asp]->annotatorEventSink->SetGuiAnnotator(this);
		}
		CComBSTR param(AN_PARAM_ROOTNODE);
		CComVariant value(rootNode);
		COMTHROW(decoratorData[asp]->decorator->SetParam(param, value));

		COMTHROW(decoratorData[asp]->decorator->InitializeEx(theApp.mgaProject, NULL, NULL, annotatorEventSinkIface, (ULONGLONG)view->m_hWnd));

		long sx, sy;
		COMTHROW(decoratorData[asp]->decorator->GetPreferredSize(&sx, &sy));
		decoratorData[asp]->location.right = decoratorData[asp]->location.left + sx;
		decoratorData[asp]->location.bottom = decoratorData[asp]->location.top + sy;

		COMTHROW(decoratorData[asp]->decorator->SetLocation(decoratorData[asp]->location.left, decoratorData[asp]->location.top,
															decoratorData[asp]->location.right, decoratorData[asp]->location.bottom));
	}
	catch (hresult_exception &) {
		AfxMessageBox("Cannot initialize annotator for annotation: " + name, MB_OK | MB_ICONSTOP);
		decoratorData[asp]->decorator = NULL;
	}
}

bool CGuiAnnotator::IsVisible(int aspect)
{
	if (aspect < 0) {
		aspect = parentAspect;
	}
	return (decoratorData[aspect]->decorator != NULL);
}

void CGuiAnnotator::Draw(HDC pDC, Gdiplus::Graphics* gdip)
{
	if (decoratorData[parentAspect]->decorator) {
		try {
			COMTHROW(decoratorData[parentAspect]->decorator->DrawEx(pDC, (ULONGLONG)gdip));
		}
		catch (hresult_exception &) {
			AfxMessageBox("Error in annotator [method Draw()]");
		}
	}
}

void CGuiAnnotator::GrayOut(bool set)
{
	if (decoratorData[parentAspect]->decorator) {
		grayedOut = set;
		try {
#pragma warning(disable: 4310) // cast truncates constant value
			COMTHROW(decoratorData[parentAspect]->decorator->SetActive(set ? VARIANT_FALSE : VARIANT_TRUE));
#pragma warning(default: 4310) // cast truncates constant value
		}
		catch (hresult_exception &) {
		}
	}
}

const CRect& CGuiAnnotator::GetLocation(int aspect)
{
	if (aspect < 0) {
		aspect = parentAspect;
	}
	return decoratorData[aspect]->location;
}

void  CGuiAnnotator::SetLocation(const CRect& toLoc, int aspect, bool doMga)
{
	if (aspect < 0) {
		aspect = parentAspect;
	}

	CRect loc(toLoc);
	if (loc.left < 0) {
		loc.right += -loc.left;
		loc.left = 0;
	}
	if (loc.top < 0) {
		loc.bottom += -loc.top;
		loc.top = 0;
	}

	decoratorData[aspect]->location = loc;
	try {
		COMTHROW(decoratorData[aspect]->decorator->SetLocation(loc.left, loc.top, loc.right, loc.bottom));
	}
	catch (hresult_exception &) {
		AfxMessageBox("Cannot set location of annotation " + name);
	}

	if (doMga) {
		WriteLocation(aspect);
	}
}

void  CGuiAnnotator::ReadLocation(int aspect, CComPtr<IMgaRegNode>& aspNode)
{
	decoratorData[aspect]->location.left = 0;
	decoratorData[aspect]->location.top = 0;

	try {
		CComBSTR bstr;
		COMTHROW(aspNode->get_Value(&bstr));
		CString str(bstr);
		long lx, ly;
		if(_stscanf(str,_T("%d,%d"), &lx, &ly) == 2) {
			decoratorData[aspect]->location.left = lx;
			decoratorData[aspect]->location.top = ly;
		}
		else {
			throw hresult_exception();
		}
	}
	catch (hresult_exception &) {
		try {
			CComPtr<IMgaRegNode> rootNode;
			COMTHROW(aspNode->get_ParentNode(&rootNode));
			CComBSTR bstrRoot;
			COMTHROW(rootNode->get_Value(&bstrRoot));
			CString strRoot(bstrRoot);
			long lxr, lyr;
			if(_stscanf(strRoot,_T("%d,%d"), &lxr, &lyr) == 2) {
				decoratorData[aspect]->location.left = lxr;
				decoratorData[aspect]->location.top = lyr;
			}
		}
		catch (hresult_exception &) {
		}
	}
}

void  CGuiAnnotator::WriteLocation(int aspect)
{
	if (aspect < 0) {
		aspect = parentAspect;
	}

	OLECHAR bbc[40];
	_snwprintf(bbc, 40, OLESTR("%ld,%ld"), decoratorData[aspect]->location.left, decoratorData[aspect]->location.top);
	CComBSTR bb(bbc);


	CComPtr<IMgaRegNode> aspRoot;
	CComBSTR aspRootName(AN_ASPECTS);
	COMTHROW(rootNode->get_SubNodeByName(aspRootName, &aspRoot));

	CComPtr<IMgaRegNode> aspNode;
	CComBSTR aspName(view->guiMeta->FindAspect(aspect)->name);
	COMTHROW(aspRoot->get_SubNodeByName(aspName, &aspNode));

	COMTHROW(aspNode->put_Value(bb));
}

////////////////////////////////////
// Static methods of CGuiAnnotator
////////////////////////////////////
void CGuiAnnotator::SetAspect(CGuiAnnotatorList& list, int asp)
{
	POSITION pos = list.GetHeadPosition();
	while (pos) {
		list.GetNext(pos)->SetAspect(asp);
	}
}

void CGuiAnnotator::GrayOutAnnotations(CGuiAnnotatorList& list, bool set)
{
	POSITION pos = list.GetHeadPosition();
	while (pos) {
		list.GetNext(pos)->GrayOut(set);
	}
}


void CGuiAnnotator::NudgeAnnotations(CGuiAnnotatorList& annotatorList, int right, int down)
{
	CGMEEventLogger::LogGMEEvent("CGuiAnnotator::NudgeAnnotations ");
	GMEEVENTLOG_GUIANNOTATORS(annotatorList);
	ASSERT(right == 0 || down == 0); // cannot nudge diagonally for now
	POSITION pos = annotatorList.GetHeadPosition();
	while(pos) {
		CGuiAnnotator* ann = annotatorList.GetNext(pos);
		VERIFY(ann->IsVisible());
		CRect rect = ann->GetLocation();
		rect.top += down * GME_GRID_SIZE;
		rect.bottom += down * GME_GRID_SIZE;
		rect.left += right * GME_GRID_SIZE;
		rect.right += right * GME_GRID_SIZE;
		ann->SetLocation(rect);
	}
}

void CGuiAnnotator::GetExtent(CGuiAnnotatorList& annotatorList, CRect& rect)
{
	CGuiAnnotator* ann;
	CRect cur1, cur2;
	POSITION pos = annotatorList.GetHeadPosition();
	rect = CRect(0,0,0,0);
	while(pos) {
		ann = annotatorList.GetNext(pos);
		if(ann && ann->IsVisible()) {
			cur2 = ann->GetLocation();
			cur1 = rect;
			rect.UnionRect(&cur1, &cur2);
		}
	}
}

void CGuiAnnotator::GetRectList(CGuiAnnotatorList &annotatorList, CRectList &annRects)
{
	POSITION pos = annotatorList.GetHeadPosition();
	while(pos) {
		CRect* rect = new CRect(annotatorList.GetNext(pos)->GetLocation());
		annRects.AddTail(rect);
	}
}


void CGuiAnnotator::FindUpperLeft(CGuiAnnotatorList& anns, int& left, int& top)
{
	bool start = true;
	POSITION pos = anns.GetHeadPosition();
	CGuiAnnotator* ann;
	CRect r;
	while(pos) {
		ann = anns.GetNext(pos);
		if(ann->IsVisible()) {
			r = ann->GetLocation();
			if(start) {
				left = r.left;
				top = r.top;
				start = false;
			}
			else {
				if(r.left < left)
					left = r.left;
				if(r.top < top)
					top = r.top;
			}
		}
	}
}

void CGuiAnnotator::ShiftAnnotations(CGuiAnnotatorList& annList, CPoint& shiftBy)
{
	CGMEEventLogger::LogGMEEvent("CGuiAnnotator::ShiftAnnotations ");
	GMEEVENTLOG_GUIANNOTATORS(annList);
	POSITION pos = annList.GetHeadPosition();
	while(pos) {
		CGuiAnnotator* ann = annList.GetNext(pos);
		VERIFY(ann->IsVisible());
		CRect newLoc = ann->GetLocation();
		newLoc.OffsetRect(shiftBy);
		ann->SetLocation(newLoc);
	}
}

// static
int CGuiAnnotator::Hide(CComPtr<IMgaRegNode>& mRootNode )
{
	CComBSTR val;
	COMTHROW(mRootNode->get_Value( &val));
	COMTHROW(mRootNode->put_Value( val));
	// thus we made the value of the annotator defined 'HERE'
	// which will decide whether an annotation regnode is virtual (inherited) or not

	CComBSTR bstr("1");

	// inheritance broken node inserted
	CComPtr<IMgaRegNode> brokNode;
	CComBSTR brokNm(AN_BROKEN_DERIV);
	COMTHROW( mRootNode->get_SubNodeByName(brokNm, &brokNode));
	COMTHROW( brokNode->put_Value(bstr));

	// hidden node set to true
	CComPtr<IMgaRegNode> hideNode;
	CComBSTR hideNm(AN_HIDDEN);
	COMTHROW(mRootNode->get_SubNodeByName( hideNm, &hideNode));
	COMTHROW( hideNode->put_Value( bstr));

	return S_OK;
}

// static
bool CGuiAnnotator::Showable( CComPtr<IMgaRegNode>& mRootNode )
{   // decides whether an annotation should be displayed in case of a subtype/instance
	// Subtype/instance may have: owned annotations (not present in the ancestor) -> main status = ATTSTATUS_HERE
	//                            inherited annotations                           -> main status = ATTSTATUS_INHERITED1,2,...
	//                            inherited, but modified annotations             -> main status = ATTSTATUS_HERE
	try {
		CComBSTR bName;
		COMTHROW(mRootNode->get_Name(&bName));

		// if value of rootnode defined HERE, then show it only iff 'hide' not set
		long status;
		COMTHROW(mRootNode->get_Status(&status));
		if( status == ATTSTATUS_HERE)
		{
			bool hidden_set = false;
			CComPtr<IMgaRegNode> hideNode;
			CComBSTR hideNm(AN_HIDDEN);
			COMTHROW(mRootNode->get_SubNodeByName( hideNm, &hideNode));
			if (hideNode)
			{
				long hideStatus;
				COMTHROW( hideNode->get_Status( &hideStatus));
				if( hideStatus != ATTSTATUS_UNDEFINED)  // meta, here or inherited
				{
					CComBSTR bstr;
					COMTHROW( hideNode->get_Value( &bstr));
					if( bstr == "1")
						hidden_set = true;
				}
			}

			return !hidden_set;
		}

		// the value of mRootNode is inherited (is NOT HERE)
		CComPtr<IMgaRegNode> inheritNode;
		CComBSTR inhName(AN_INHERITABLE);
		COMTHROW(mRootNode->get_SubNodeByName( inhName, &inheritNode));

		if (inheritNode) {
			CComBSTR bstr;
			COMTHROW(inheritNode->get_Value( &bstr));
			if (bstr == "1") // if "inheritable" is 1 show it
				return true;
		}
	}
	catch(hresult_exception &e) {
		throw hresult_exception(e.hr);
		return false;
	}

	return false;
}

////////////////////////////////////
// Virtual methods of CGuiAnnotator
////////////////////////////////////



//////////////////////////////////// CGuiFco /////////////////////////////

//////////////////////////////////
// Non-virtual methods of CGuiFco
//////////////////////////////////

CGuiFco::CGuiFco(CComPtr<IMgaFCO>& pt, CComPtr<IMgaMetaRole>& role, CGMEView* vw, int numAsp) :
	CGuiBase(),
	mgaFco(pt),
	metaRole(role),
	view(vw),
	numParentAspects(numAsp),
	parentAspect(0),
	grayedOut(false),
	isType(false)
{
	{
		CComBSTR bstr;
		COMTHROW(role->get_Name(&bstr));
		CopyTo(bstr, roleName);
	}
	{
		CComBSTR bstr;
		COMTHROW(role->get_DisplayedName(&bstr));
		CopyTo(bstr, roleDisplayedName);
	}
	{
		COMTHROW(role->get_Kind(&metaFco));
	}
	{
		CComBSTR bstr;
		COMTHROW(metaFco->get_Name(&bstr));
		CopyTo(bstr, kindName);
	}
	{
		CComBSTR bstr;
		COMTHROW(metaFco->get_DisplayedName(&bstr));
		CopyTo(bstr, kindDisplayedName);
	}
	if (pt) {
		CComBSTR bstr;
		COMTHROW(mgaFco->get_ID(&bstr));
		CopyTo(bstr, id);
	}
	if (pt) {
		CComBSTR bstr;
		COMTHROW(mgaFco->get_Name(&bstr));
		CopyTo(bstr, name);
	}

	metaref_type metaRef;
	COMTHROW(metaFco->get_MetaRef(&metaRef));
	guiMeta = CGuiMetaProject::theInstance->GetGuiMetaFco(metaRef);
}

metaref_type CGuiFco::GetRoleMetaRef()
{
	metaref_type tp;
	VERIFY(metaRole);
	COMTHROW(metaRole->get_MetaRef(&tp));
	return tp;
}

bool CGuiFco::IsPrimary(CGuiMetaModel* guiMetaModel, int aspectInd)
{
	bool prim = false;
	CGuiMetaAspect *aspect = guiMetaModel->FindAspect(aspectInd);
	if(aspect)
		prim = CGuiFco::IsPrimary(guiMetaModel, aspect, metaRole);
	return prim;
}

bool CGuiFco::IsPrimary(CGuiMetaModel* guiMetaModel, CGuiMetaAspect* aspect)
{
	return CGuiFco::IsPrimary(guiMetaModel, aspect, metaRole);
}

bool CGuiFco::GetPreference(CString& val, CString path)
{
	CComBSTR pathBstr;
	CopyTo(path, pathBstr);
	CComBSTR bstrVal;
	if (mgaFco) {
		COMTHROW(mgaFco->get_RegistryValue(pathBstr, &bstrVal));
	}
	else {
		COMTHROW(metaFco->get_RegistryValue(pathBstr, &bstrVal));
	}
	CopyTo(bstrVal, val);
	return !val.IsEmpty();
}


bool CGuiFco::GetPreference(int& val, CString path, bool hex)
{
	CComBSTR pathBstr;
	CopyTo(path, pathBstr);
	CComBSTR bstrVal;
	if(mgaFco == 0) {
		COMTHROW(metaFco->get_RegistryValue(pathBstr, &bstrVal));
	}
	else {
		COMTHROW(mgaFco->get_RegistryValue(pathBstr, &bstrVal));
	}
	CString strVal;
	CopyTo(bstrVal,strVal);
	return (_stscanf(strVal,hex ? _T("%x") : _T("%d"),&val) == 1);
}

bool CGuiFco::GetColorPreference(unsigned long& color, CString path)
{
	int i;
	if(GetPreference(i,path,true)) {
		unsigned int r = (i & 0xff0000) >> 16;
		unsigned int g = (i & 0xff00) >> 8;
		unsigned int b = i & 0xff;
		color = RGB(r,g,b);
		return true;
	}
	return false;
}

CGuiMetaModel *CGuiFco::GetGuiMetaParent()
{
	CComPtr<IMgaMetaModel>	metaParent;
	COMTHROW(metaRole->get_ParentModel(&metaParent));
	VERIFY(metaParent);
	metaref_type metaRef;
	COMTHROW(metaParent->get_MetaRef(&metaRef));
	return CGuiMetaProject::theInstance->GetGuiMetaModel(metaRef);

}

////////////////////////////
// Static methods of CGuiFco
/////////////////////////////
bool CGuiFco::IsPrimary(CGuiMetaModel* guiMetaModel, CGuiMetaAspect* guiAspect, CComPtr<IMgaMetaRole>& metaRole)
{
	VARIANT_BOOL prim = VARIANT_FALSE;
	CComPtr<IMgaMetaAspect> mAspect;
	guiAspect->GetMetaAspect(mAspect);
	CComPtr<IMgaMetaPart> part;
	guiMetaModel->GetPartByRole(metaRole, mAspect, part);
	if(part != 0)
		COMTHROW(part->get_IsPrimary(&prim));
	return prim != VARIANT_FALSE;
}

void CGuiFco::SetAspect(CGuiFcoList& modelList, int asp)
{
	POSITION pos = modelList.GetHeadPosition();
	while(pos)
		modelList.GetNext(pos)->SetAspect(asp);
}


CGuiConnection* CGuiFco::FindConnection(CComPtr<IMgaFCO>& fco, CGuiConnectionList& conns)
{
	POSITION pos = conns.GetHeadPosition();
	while(pos) {
		CGuiConnection* conn = conns.GetNext(pos);
		VARIANT_BOOL b;
		COMTHROW(conn->mgaFco->get_IsEqual(fco, &b));
		if(b != VARIANT_FALSE)
			return conn;
	}
	return 0;
}

void CGuiFco::GrayOutFcos(CGuiFcoList& list, bool set)
{
	POSITION pos = list.GetHeadPosition();
	while(pos)
		list.GetNext(pos)->GrayOut(set);
}

void CGuiFco::GrayOutFcos(CGuiConnectionList& list, bool set)
{
	POSITION pos = list.GetHeadPosition();
	while(pos)
		list.GetNext(pos)->GrayOut(set);
}

void CGuiFco::GrayOutNonInternalConnections(CGuiConnectionList& list)
{
	POSITION pos = list.GetHeadPosition();
	while(pos) {
		CGuiConnection *conn = list.GetNext(pos);
		if(conn->src && conn->dst)
			conn->GrayOut(conn->src->grayedOut || conn->dst->grayedOut);
	}
}

void CGuiFco::ResetFlags(CGuiFcoList& list)
{
	POSITION pos = list.GetHeadPosition();
	while(pos)
		list.GetNext(pos)->flag = 0;
}

////////////////////////////
// Virtual methods of CGuiFco
/////////////////////////////


CGuiMetaAttributeList *CGuiFco::GetMetaAttributes()
{
	return &guiMeta->attrs;
}


////////////////////////////////// CGuiObject /////////////////////////////

//////////////////////////////////
// Non-virtual methods of CGuiObject
//////////////////////////////////
CGuiObject::CGuiObject(CComPtr<IMgaFCO>& pt, CComPtr<IMgaMetaRole>& role, CGMEView* vw, int numAsp) : CGuiFco(pt, role, vw, numAsp)
{
	guiAspects.SetSize(numAsp);
	for (int i = 0; i<numAsp; i++) {
		guiAspects[i] = NULL;
	}
}

void CGuiObject::InitObject(CWnd* viewWnd)
{
	try {
		CComPtr<IMgaMetaParts> mmParts;
		COMTHROW(metaRole->get_Parts(&mmParts));
		MGACOLL_ITERATE(IMgaMetaPart,mmParts) {
			CComPtr<IMgaMetaPart> mmPart;
			mmPart = MGACOLL_ITER;
			CComPtr<IMgaMetaAspect> mmAspect;
			COMTHROW(mmPart->get_ParentAspect(&mmAspect));
			CComBSTR bstr;
			COMTHROW(mmAspect->get_Name(&bstr));
			CString aspName;
			CopyTo(bstr,aspName);
			CGuiMetaAspect *guiMetaAsp = GetGuiMetaParent()->FindAspect(aspName);
			VERIFY(guiMetaAsp);
			VERIFY(guiMetaAsp->index < numParentAspects);
			CString decoratorStr;
			GetDecoratorStr(decoratorStr);
			InitAspect(guiMetaAsp->index, mmPart, decoratorStr, viewWnd);
		}
		MGACOLL_ITERATE_END;

		CString hotspotPref;
		GetPreference(hotspotPref, HOTSPOT_PREF);
		if (hotspotPref == HOTSPOT_FALSE) {
			isHotspotEnabled = false;
		}
		else {
			isHotspotEnabled = true;
		}
	}
	catch(hresult_exception &e) {
		numParentAspects = 0;
		parentAspect = 0;
		throw hresult_exception(e.hr);
		return;
	}
	if (IsReal()) {
		ReadAllLocations();
	}
	else {
		SetAllSizesToNative();
	}
}

CGuiObject::~CGuiObject()
{
	if (view) {
		POSITION ppos = view->pendingRequests.GetHeadPosition();
		while (ppos) {
			POSITION tmp = ppos;
			CPendingObjectPosRequest *req = dynamic_cast<CPendingObjectPosRequest*> (view->pendingRequests.GetNext(ppos));
			if (req) {
				if ( req->object == this ) {
					view->pendingRequests.RemoveAt(tmp);
					delete req;
				}
			}
		}
	}

	for (int i = 0; i < guiAspects.GetSize(); i++) {
		delete guiAspects[i];
	}
	guiAspects.RemoveAll();
}

void CGuiObject::InitAspect(int asp, CComPtr<IMgaMetaPart>& metaPart, CString& decorStr, CWnd* viewWnd)
{
	VERIFY(asp < numParentAspects);
	CGuiMetaAspect* metaAspect = GetKindAspect(metaPart);
	VERIFY(metaAspect);

	CString	progId;
	CStringList params;
	CStringList values;

	if (!decorStr.IsEmpty()) {	// no decorator progId and no paarmeters => use default box decorator later
		if (decorStr.FindOneOf("\n\t ,=") == -1) {	// just a progId, no parameters
			progId = decorStr;
		} else {	// there is some parameter
			LPTSTR lpsz = new TCHAR[decorStr.GetLength()+1];
			LPTSTR tok = new TCHAR[decorStr.GetLength()+1];
			_tcscpy(lpsz, decorStr);
			int curpos = 0, tokpos = 0;
			int state = 0;  // 0:progid, 1:var, 2:val
			bool	gotOne = false;
			TCHAR	ch;

			while ( (ch = lpsz[curpos++]) != 0) {
				if (ch == _T('\n') || ch == _T('\t') || ch == _T(' ')) {
					if (gotOne) {
						state = 1;
						gotOne = false;
						tok[tokpos] = 0;
						progId = tok;
						tokpos = 0;
					}
					continue;
				}
				switch (state) {
					case 0:
						gotOne = true;
						tok[tokpos++] = ch;
						break;
					case 1:
						if (ch == _T('=')) {
							state = 2;
							tok[tokpos] = 0;
							params.AddTail(tok);
							tokpos = 0;
						}
						else {
							tok[tokpos++] = ch;
						}
						break;
					case 2:
						if (ch == _T(',')) {
							state = 1;
							tok[tokpos] = 0;
							values.AddTail(tok);
							tokpos = 0;
						}
						else {
							tok[tokpos++] = ch;
						}
						break;
				}
			}
			if (state == 0) {
				tok[tokpos] = 0;
				progId = tok;
			}
			if (state == 2) {
				tok[tokpos] = 0;
				values.AddTail(tok);
			}

			delete [] lpsz; // WAS: delete lpsz;
			delete [] tok;; // WAS: delete tok;;
		}
	}

	if (progId.IsEmpty()) {
		progId = GME_DEFAULT_DECORATOR;
	}
	CComPtr<IMgaDecorator> decor;
	CComPtr<IMgaElementDecorator> newDecor;

	CDecoratorEventSink* decoratorEventSink = NULL;
	try {
		CComPtr<IMgaElementDecoratorEvents> decoratorEventSinkIface;
		HRESULT hres = newDecor.CoCreateInstance(PutInBstr(progId));
		if (SUCCEEDED(hres)) {
			decoratorEventSink = new CDecoratorEventSink();
			HRESULT hr = decoratorEventSink->QuerySinkInterface((void**) &decoratorEventSinkIface);
			if (hr == S_OK) {
				decoratorEventSink->SetView(view);
				decoratorEventSink->SetGuiObject(this);
			}
			decor = CComQIPtr<IMgaDecorator>(newDecor);
		} else {
			COMTHROW(decor.CoCreateInstance(PutInBstr(progId)));
		}

		POSITION ppos = params.GetHeadPosition();
		POSITION vpos = values.GetHeadPosition();
		while (ppos && vpos) {
			CComBSTR param(params.GetNext(ppos));
			CComVariant value(values.GetNext(vpos));
			COMTHROW(decor->SetParam(param, value));
		}
		if (newDecor)
			COMTHROW(newDecor->InitializeEx(theApp.mgaProject, metaPart, mgaFco, decoratorEventSinkIface, (ULONGLONG)viewWnd->m_hWnd));
		else
			COMTHROW(decor->Initialize(theApp.mgaProject, metaPart, mgaFco));
	}
	catch (hresult_exception &e) {
		CMainFrame::theInstance->m_console.Message("Cannot create " + progId + " decorator! Trying default " + GME_DEFAULT_DECORATOR + " decorator.", 3);
		try {
			if (progId != GME_DEFAULT_DECORATOR) {
				// AfxMessageBox does not work here becase some stupid Win32 event mechanisms
				// AfxMessageBox("Cannot create specified (" + progId +") decorator for object: " + name + "\nCreating default decorator.");
				progId = GME_DEFAULT_DECORATOR;
				decor = NULL;
				COMTHROW(decor.CoCreateInstance(PutInBstr(progId)));
				COMTHROW(decor->Initialize(theApp.mgaProject, metaPart, mgaFco));
			}
			else {
				throw hresult_exception(e.hr);
			}
		}
		catch (hresult_exception &e) {
			CMainFrame::theInstance->m_console.Message("Cannot create default decorator.\nGiving up.", 3);
			throw hresult_exception(e.hr);
		}
	}
	guiAspects[asp] = new CGuiAspect(metaAspect, this, metaAspect->index, asp, decor, newDecor, decoratorEventSink);
	parentAspect = 0;
}

void CGuiObject::GetDecoratorStr(CString& decorStr)
{
	if (!GetPreference(decorStr, DECORATOR_PREF))
		decorStr = GME_DEFAULT_DECORATOR;
}

void CGuiObject::SetCenter(CPoint& pt, int aspect, bool doMga)
{
	if(aspect < 0)
		aspect = parentAspect;
	VERIFY(aspect >= 0);
	VERIFY(guiAspects[aspect] != NULL);
	CRect loc = guiAspects[aspect]->GetLocation();
	if (IsReal()) {
		::SetCenter(loc,pt);
	}
	else {
		::SetCenterNoMga(loc, pt);
	}
	guiAspects[aspect]->SetLocation(loc);
	if(IsReal() && doMga)
		WriteLocation(aspect);
}

void CGuiObject::SetSize(CSize& s, int aspect, bool doMga)
{
	if(aspect < 0)
		aspect = parentAspect;
	VERIFY(aspect >= 0);
	VERIFY(guiAspects[aspect] != NULL);
		CRect loc = guiAspects[aspect]->GetLocation();
	::SetSize(loc,s);
	guiAspects[aspect]->SetLocation(loc);
	if(IsReal() && doMga)
		WriteLocation(aspect);
}

void CGuiObject::SetAllSizes(CSize& s, bool doMga)
{
	for(int i = 0; i < numParentAspects; i++)
		if(guiAspects[i] != NULL)
			SetSize(s,i,doMga);
}

void CGuiObject::SetLocation(CRect& r, int aspect, bool doMga/*, bool savePreferredSize*/)
{
	if(aspect < 0)
		aspect = parentAspect;
	VERIFY(aspect >= 0);
	VERIFY(guiAspects[aspect] != NULL);
	guiAspects[aspect]->SetLocation(r);
	if(IsReal() && doMga)
		WriteLocation(aspect/*, savePreferredSize*/);
}

CSize CGuiObject::GetNativeSize(int aspect)
{
	if(aspect < 0)
		aspect = parentAspect;
	VERIFY(aspect >= 0);
	if(guiAspects[aspect] == NULL)
		return CSize(0,0);
	try {
		long sizex, sizey;
		COMTHROW(guiAspects[aspect]->GetDecorator()->GetPreferredSize(&sizex, &sizey));
		return CSize(sizex, sizey);
	}
	catch (hresult_exception &) {
		return false;
	}
	//return true;// unreachable code
}


void CGuiObject::SetAllSizesToNative()
{
	CSize s;
	for(int i = 0; i < numParentAspects; i++) {
		if(guiAspects[i]) {
			s=GetNativeSize(i);
			CRect loc(0, 0, 0, 0);
			guiAspects[i]->SetLocation(loc);
			SetSize(s, i, false);
		}
	}
}

void CGuiObject::GetNeighbors(CGuiFcoList& list)
{
	VERIFY(GetCurrentAspect());
	POSITION ppos = GetCurrentAspect()->GetPortList().GetHeadPosition();
	while (ppos) {
		CGuiPort *port = GetCurrentAspect()->GetPortList().GetNext(ppos);
		POSITION cpos = port->GetInConns().GetHeadPosition();
		while(cpos) {
			CGuiConnection *conn = port->GetInConns().GetNext(cpos);
			if(conn->src->flag == 0) {
				list.AddTail(conn->src);
				conn->src->flag = 1;
			}
		}
		cpos = port->GetOutConns().GetHeadPosition();
		while(cpos) {
			CGuiConnection *conn = port->GetOutConns().GetNext(cpos);
			if(conn->dst->flag == 0) {
				list.AddTail(conn->dst);
				conn->dst->flag = 1;
			}
		}
	}
}

void CGuiObject::GetRelationsInOut(CGuiConnectionList& p_list, bool p_inOrOut)
{
	VERIFY(GetCurrentAspect());
	
	// acquire ports
	POSITION ppos = GetCurrentAspect()->GetPortList().GetHeadPosition();
	while (ppos) 
	{
		// one port
		CGuiPort *port = GetCurrentAspect()->GetPortList().GetNext(ppos);

		ASSERT( port); 
		if( !port) continue;

		// acquire the in/out connections through the current port
		POSITION cpos = p_inOrOut? port->GetInConns().GetHeadPosition(): port->GetOutConns().GetHeadPosition();
		while(cpos) 
		{
			// one connection
			CGuiConnection* conn = p_inOrOut? port->GetInConns().GetNext(cpos): port->GetOutConns().GetNext(cpos);

			ASSERT( conn);
			if( !conn) continue;

			// store it
			p_list.AddTail( conn);
		}
	}
}

void CGuiObject::ReadAllLocations()
{
	try {
		CComPtr<IMgaMetaParts> mmParts;
		CComPtr<IMgaMetaPart> mmPart;
		COMTHROW(metaRole->get_Parts(&mmParts));
		MGACOLL_ITERATE(IMgaMetaPart,mmParts) {
			mmPart = MGACOLL_ITER;
			CComPtr<IMgaMetaAspect> mmAspect;
			COMTHROW(mmPart->get_ParentAspect(&mmAspect));
			CComBSTR bstr;
			COMTHROW(mmAspect->get_Name(&bstr));
			CString aspName;
			CopyTo(bstr,aspName);
			CGuiMetaAspect *guiMetaAsp = GetGuiMetaParent()->FindAspect(aspName);
			VERIFY(guiMetaAsp);
			VERIFY(guiMetaAsp->index < numParentAspects);
			int aspIndex = guiMetaAsp->index;
			VERIFY(aspIndex >= 0);
			CComPtr<IMgaPart> part;
			COMTHROW(mgaFco->get_Part(mmAspect,&part));
			CComBSTR icon;
			long x;
			long y;

			CRect loc(0, 0, 0, 0);
			CSize s = GetNativeSize(aspIndex);
			::SetSize(loc,s);

			if(part->GetGmeAttrs(0, &x, &y) == S_OK) {
				::SetLocation(loc, CPoint(x, y));
				guiAspects[aspIndex]->SetLocation(loc);
			}
			else { // unparsable integer pair found, use (-1, -1) like in CMgaPart::GetGmeAttrs
				::SetLocation(loc,CPoint(-1, -1));
				guiAspects[aspIndex]->SetLocation(loc);
			}
		}
		MGACOLL_ITERATE_END;
	}
	catch(hresult_exception &e) {
		throw hresult_exception(e.hr);
	}
}

void CGuiObject::WriteLocation(int aspect)
{
	VERIFY(IsReal());
	if(aspect < 0)
		aspect = parentAspect;
	VERIFY(aspect >= 0);
	VERIFY(guiAspects[aspect]);
	try {
		view->BeginTransaction();
		CComPtr<IMgaPart> part;
		CGuiMetaAspect *guiAsp = GetGuiMetaParent()->FindAspect(aspect);
		CComPtr<IMgaMetaBase> mBase = guiAsp->mgaMeta;
		CComPtr<IMgaMetaAspect> mAspect;
		mBase.QueryInterface(&mAspect);
		COMTHROW(mgaFco->get_Part(mAspect,&part));
		CRect r = guiAspects[aspect]->GetLocation();
		// Save position part
		CPoint pt = r.TopLeft();
		COMTHROW(part->SetGmeAttrs(0, pt.x, pt.y));
		// This would be too agressive: to delete any connecting connections customizations if the box is moved
		// DeleteCustomizationOfInOutConnections(aspect);
		view->CommitTransaction();
	}
	catch(hresult_exception &e) {
		view->AbortTransaction(e.hr);
	}
}

void CGuiObject::DeleteCustomizationOfConnections(CGuiConnectionList& conns, long aspect)
{
	POSITION pos = conns.GetHeadPosition();
	while(pos) {
		CGuiConnection* conn = conns.GetNext(pos);
		if (conn->HasPathCustomization())
			if (conn->DeleteAllPathCustomizationsForAnAspect(aspect))
				conn->WriteCustomPathData(false);
	}
}

void CGuiObject::DeleteCustomizationOfInOutConnections(long aspect)
{
	CGuiConnectionList inConns;
	GetRelationsInOut(inConns, true);
	DeleteCustomizationOfConnections(inConns, aspect);
	CGuiConnectionList outConns;
	GetRelationsInOut(outConns, false);
	DeleteCustomizationOfConnections(outConns, aspect);
}

void CGuiObject::GrayOutNeighbors()
{
	CGuiFcoList neighbors;
	GetNeighbors(neighbors);
	GrayOutFcos(neighbors, grayedOut);
	ResetFlags(neighbors);
}

bool CGuiObject::IsInside(CPoint& pt, bool lookNearToo)
{
	CRect loc = GetLocation();
	if (lookNearToo)
		loc.InflateRect(3, 3);
	return (loc.PtInRect(pt) == TRUE);
}

bool CGuiObject::IsLabelInside(CPoint& pt, bool lookNearToo)
{
	CRect loca = GetLocation();
	CRect loc = GetNameLocation();
	if (lookNearToo)
		loc.InflateRect(3, 3);
	return (loc.PtInRect(pt) == TRUE);
}

CGuiPort* CGuiObject::FindPort(CPoint& pt, bool lookNearToo)
{
	CGuiPort* found = NULL;
	CSize foundSize(0, 0);
	VERIFY(GetCurrentAspect());
	POSITION pos = GetCurrentAspect()->GetPortList().GetHeadPosition();
	while(pos) {
		CGuiPort* port = GetCurrentAspect()->GetPortList().GetNext(pos);
		// The last one in the list is weird one: fco is the object's fco, skip that.
		// See CGuiAspect::InitPorts
		if (!mgaFco.IsEqualObject(port->mgaFco))
		{
			CRect r = port->GetLocation() + GetLocation().TopLeft();
			CRect rInflated = r;
			rInflated.InflateRect(3, 3);
			if (r.PtInRect(pt) == TRUE || lookNearToo && rInflated.PtInRect(pt) == TRUE)
			{
				CSize psize = port->GetLocation().Size();
				if (found)
				{
					if (psize.cx < foundSize.cx && psize.cy < foundSize.cy ) {
						foundSize = psize;
						found = port;
					}
				}
				else
				{
					foundSize = psize;
					found = port;
				}
			}
		}
	}
	return found;
}

CGuiPort *CGuiObject::FindPort(CComPtr<IMgaFCO> mgaFco)
{
	ASSERT(GetCurrentAspect());
	POSITION pos = GetCurrentAspect()->GetPortList().GetHeadPosition();
	while(pos) {
		CGuiPort* port = GetCurrentAspect()->GetPortList().GetNext(pos);
		VARIANT_BOOL b;
		COMTHROW(port->mgaFco->get_IsEqual(mgaFco, &b));
		if (b)
			return port;
	}
	return 0;
}

void CGuiObject::IncrementAnimRefCnt()
{
	if (view) {
		if (!(view->animRefCnt++)) {
			view->timerID = view->SetTimer(GME_ANIM_EVENT_ID, GME_ANIM_INTERVAL, NULL);
		}
	}
}

void CGuiObject::DecrementAnimRefCnt()
{
	if (view) {
		ASSERT(view->animRefCnt);
		if (!(--view->animRefCnt)) {
			if (view->timerID) {
				view->KillTimer(view->timerID);
				view->timerID = 0;
			}
		}
	}
}


//////////////////////////////////
// Static methods of CGuiObject
//////////////////////////////////

void CGuiObject::GetExtent(CGuiFcoList& objectList, CRect& rect)
{
	CGuiObject* obj;
	CRect cur1, cur2;
	POSITION pos = objectList.GetHeadPosition();
	rect = CRect(0, 0, 10, 10);
	while (pos) {
		CGuiFco* fco = objectList.GetNext(pos);
		ASSERT(fco != NULL);
		obj = fco->dynamic_cast_CGuiObject();
		if(obj && obj->IsVisible()) {
			cur2 = obj->GetLocation();
			cur1 = rect;
			rect.UnionRect(&cur1, &cur2);
		}
	}
}

void CGuiObject::GetExtent(CGuiObjectList& objectList, CRect& rect)
{
	CGuiObject* obj;
	CRect cur1, cur2;
	POSITION pos = objectList.GetHeadPosition();
	rect = CRect(0, 0, 0, 0);
	while(pos) {
		obj = objectList.GetNext(pos);
		if(obj && obj->IsVisible()) {
			cur2 = obj->GetLocation();
			cur1 = rect;
			rect.UnionRect(&cur1, &cur2);
		}
	}
}

void CGuiObject::MoveObjects(CGuiFcoList& fcoList, CPoint& pt)
{
	CGuiObjectList objs;
	POSITION pos = fcoList.GetHeadPosition();
	while(pos) {
		CGuiFco* fco = fcoList.GetNext(pos);
		ASSERT(fco != NULL);
		CGuiObject* obj = fco->dynamic_cast_CGuiObject();
		if (obj)
			objs.AddTail(obj);
	}
	MoveObjects(objs, pt);
}

void CGuiObject::MoveObjects(CGuiObjectList& objList, CPoint& pt)
{
	int left, top;
	FindUpperLeft(objList, left, top);
	CPoint diff = pt - CPoint(left, top);
	ShiftModels(objList, diff);
}


void CGuiObject::FindUpperLeft(CGuiObjectList& objs, int& left, int& top)
{
	bool start = true;
	POSITION pos = objs.GetHeadPosition();
	CGuiObject* obj;
	CRect r;
	while(pos) {
		obj = objs.GetNext(pos);
		if(obj->IsVisible()) {
			r = obj->GetLocation();
			if(start) {
				left = r.left;
				top = r.top;
				start = false;
			}
			else {
				if(r.left < left)
					left = r.left;
				if(r.top < top)
					top = r.top;
			}
		}
	}
}

void CGuiObject::ShiftModels(CGuiObjectList& objList, CPoint& shiftBy)
{
	CGMEEventLogger::LogGMEEvent("CGuiObject::ShiftModels ");
	GMEEVENTLOG_GUIOBJS(objList);

	CGuiObject* first_obj = objList.IsEmpty() ? 0 : objList.GetHead();
	if( first_obj && first_obj->GetView() && first_obj->GetView() != modelGrid.GetSource())
	{
		// if the view where the object was moved and the view of the grid 
		// do not correspond, we must clear & update the grid.
		// possible because if a port is moved inside a model, then the model
		// is redrawn as well, and modelGrid is a global variable.
		// clearing only the grid would be too dangerous, would allow any movement
		// because other objects will disappear from the radar
		// but a Clear with a FillModelGrid will do the correct update
		modelGrid.Clear();
		first_obj->GetView()->FillModelGrid();
	}

	POSITION pos = objList.GetHeadPosition();
	while(pos) {
		CGuiObject* obj = objList.GetNext(pos);
		modelGrid.Reset(obj);
	}
	pos = objList.GetHeadPosition();
	while(pos) {
		CGuiObject* obj = objList.GetNext(pos);
		VERIFY(obj->IsVisible());
		CPoint point = obj->GetCenter() + shiftBy;
		if(!modelGrid.GetClosestAvailable(obj, point)) {
			AfxMessageBox("Too Many Models! Internal Program Error!",MB_OK | MB_ICONSTOP);
			return;
		}
		obj->SetCenter(point);
		modelGrid.Set(obj);
	}
}

void CGuiObject::ResizeObject(const CRect& newLocation/*, bool doMga*/)
{
	CGMEEventLogger::LogGMEEvent("CGuiObject::ResizeObject\n");

	VERIFY(IsVisible());
	SetLocation((CRect)newLocation, -1, false/*doMga, true*/);
	// Note: there's no need to update modelgrid now, because after finishing the resize operation
	//		 there will be a full GMEView::Reset induced by the transaction commit
}

bool CGuiObject::NudgeObjects(CGuiObjectList& modelList, int right, int down)
{
	CGMEEventLogger::LogGMEEvent("CGuiObject::NudgeObjects ");
	GMEEVENTLOG_GUIOBJS(modelList);
	ASSERT(right == 0 || down == 0); // cannot nudge diagonally for now

	CGuiObject* first_obj = modelList.IsEmpty() ? 0 : modelList.GetHead();
	if( first_obj && first_obj->GetView() && first_obj->GetView() != modelGrid.GetSource())
	{
		// if the view where the object was nudged and the view of the grid 
		// do not correspond, we must clear & update the grid
		// possible because if a port is moved inside a model, then the model
		// is redrawn as well, and modelGrid is a global variable.
		// clearing only the grid would be too dangerous, would allow nudging always
		// because other objects will not seem to sit in their places
		// but a Clear with a FillModelGrid will do the correct update
		modelGrid.Clear();
		first_obj->GetView()->FillModelGrid();
	}

	POSITION pos = modelList.GetHeadPosition();
	while(pos) {
		CGuiObject* model = modelList.GetNext(pos);
		VERIFY(model->IsVisible());
		modelGrid.Reset(model);
	}
	bool canDo = true;
	pos = modelList.GetHeadPosition();
	while(pos) {
		CGuiObject* model = modelList.GetNext(pos);
		if(!modelGrid.CanNudge(model, right, down)) {
			canDo = false;
			break;
		}
	}
	if(canDo) {
		POSITION pos = modelList.GetHeadPosition();
		while(pos) {
			CGuiObject *model = modelList.GetNext(pos);
			CPoint point = model->GetCenter() + CPoint(right * GME_GRID_SIZE, down * GME_GRID_SIZE);
			ASSERT(point.x % GME_GRID_SIZE == 0);
			ASSERT(point.y % GME_GRID_SIZE == 0);
			model->SetCenter(point);
			ASSERT(modelGrid.IsAvailable(model));
			modelGrid.Set(model);
		}
	}
	else {
		POSITION pos = modelList.GetHeadPosition();
		while(pos) {
			CGuiObject* model = modelList.GetNext(pos);
			modelGrid.Set(model);
		}
	}
	return canDo;
}

CGuiObject* CGuiObject::FindObject(CComPtr<IMgaFCO>& fco, CGuiFcoList& fcoList)
{
	POSITION pos = fcoList.GetHeadPosition();
	while(pos) {
		CGuiFco* ofco = fcoList.GetNext(pos);
		ASSERT(ofco != NULL);
		CGuiObject* obj = ofco->dynamic_cast_CGuiObject();
		if (obj) {
			VARIANT_BOOL b;
			COMTHROW(obj->mgaFco->get_IsEqual(fco, &b));
			if (b)
				return obj;
		}
	}
	return 0;
}

void CGuiObject::GetRectList(CGuiObjectList& objList, CRectList& rects)
{
	POSITION pos = objList.GetHeadPosition();
	while(pos) {
		CRect* rect = new CRect(objList.GetNext(pos)->GetLocation());
		rects.AddTail(rect);
	}
}


//////////////////////////////////
// Virtual methods of CGuiObject
//////////////////////////////////
void CGuiObject::Draw(HDC pDC, Gdiplus::Graphics* gdip)
{
	VERIFY(parentAspect >= 0);
	VERIFY(GetCurrentAspect());

	try {
		CGuiAspect* aspect = GetCurrentAspect();
		if (aspect->GetNewDecorator())
			COMTHROW(GetCurrentAspect()->GetNewDecorator()->DrawEx(pDC, (ULONGLONG)gdip));
		else
			COMTHROW(GetCurrentAspect()->GetDecorator()->Draw(pDC));
	}
	catch (hresult_exception &) {
		AfxMessageBox("Error in decorator [method Draw()]");
	}

// #define _ARDEBUG
#ifdef _ARDEBUG
	CPen arPen(PS_DOT, 1, 0x000000ff);
	CPen *oldPen = pDC->SelectObject(&arPen);
	pDC->SelectStockObject(HOLLOW_BRUSH);
	//pDC->Rectangle(GetCurrentAspect()->GetLocation());
	//pDC->Rectangle(GetCurrentAspect()->GetNameLocation());
	if (GetRouterBox()) {
		pDC->Rectangle(GetRouterBox()->GetRect());
	}
	if (GetRouterNameBox()) {
		pDC->Rectangle(GetRouterNameBox()->GetRect());
	}
	pDC->SelectObject(oldPen);
#endif

}

void CGuiObject::GrayOut(bool set)
{
	CGuiFco::GrayOut(set);

	for (int i = 0; i< guiAspects.GetSize(); i++) {
		if (IsVisible(i)) {
#pragma warning(disable: 4310) // cast truncates constant value
			COMTHROW(guiAspects[i]->GetDecorator()->SetActive(set ? VARIANT_FALSE : VARIANT_TRUE));
#pragma warning(default: 4310) // cast truncates constant value
		}
	}
}

CGuiMetaAspect *CGuiObject::GetKindAspect(CComPtr<IMgaMetaPart> metaPart)
{
	// Kindaspect is the same as parentaspect in regular objects
	CComBSTR bstr;
	CComPtr<IMgaMetaAspect>	pAspect;
	COMTHROW(metaPart->get_ParentAspect(&pAspect));
	COMTHROW(pAspect->get_Name(&bstr));
	CString aspName;
	CopyTo(bstr, aspName);
	return GetGuiMetaParent()->FindAspect(aspName);
}

////////////////////////////////// CGuiCompound /////////////////////////////

////////////////////////////////////////
// Non-virtual methods of CGuiCompound
////////////////////////////////////////

///////////////////////////////////////
// Static methods of CGuiCompound
///////////////////////////////////////

///////////////////////////////////////
// Virtual methods of CGuiCompound
///////////////////////////////////////


////////////////////////////////// CGuiModel /////////////////////////////

///////////////////////////////////////
// Non-virtual methods of CGuiModel
///////////////////////////////////////
CGuiModel::CGuiModel(CComPtr<IMgaFCO>& pt, CComPtr<IMgaMetaRole>& role,CGMEView* vw, int numAsp) : CGuiCompound(pt, role, vw, numAsp)
{
	if (IsReal()) {
		VARIANT_BOOL inst;
		COMTHROW(pt->get_IsInstance(&inst));
		isType = (inst == VARIANT_FALSE);
	}
}

///////////////////////////////////////
// Static methods of CGuiModel
///////////////////////////////////////

///////////////////////////////////////
// Virtual methods of CGuiModel
///////////////////////////////////////
CGuiMetaAttributeList* CGuiModel::GetMetaAttributes()
{
	return &(GetCurrentAspect()->guiMeta->attrs);
}

CGuiMetaAspect* CGuiModel::GetKindAspect(CComPtr<IMgaMetaPart> metaPart)
{
	CGuiMetaModel* guiMetaModel = dynamic_cast<CGuiMetaModel*>(guiMeta);
	VERIFY(guiMetaModel);
	CGuiMetaAspect* metaAspect = NULL;
	CComBSTR bstr;
	COMTHROW(metaPart->get_KindAspect(&bstr));
	CString kindAspect;
	CopyTo(bstr, kindAspect);
	if (kindAspect.IsEmpty()) {
		CComBSTR bstr;
		CComPtr<IMgaMetaAspect>	pAspect;
		COMTHROW(metaPart->get_ParentAspect(&pAspect));
		COMTHROW(pAspect->get_Name(&bstr));
		CopyTo(bstr, kindAspect);
		metaAspect = guiMetaModel->FindAspect(kindAspect);
		if(!metaAspect)	{
			metaAspect = guiMetaModel->GetFirstAspect();
			/*
			CComBSTR bstr;
			COMTHROW(metaRole->get_Name(&bstr));
			CString roleName;
			CopyTo(bstr,roleName);
			AfxMessageBox("Missing aspect mapping specification for model " + name + " aspect " + kindAspect +
					" role " + roleName + "!\nFirst aspect " + metaAspect->name + " is used!");
			*/
		}
	}
	else {
		metaAspect = guiMetaModel->FindAspect(kindAspect);
	}
	return metaAspect;
}
////////////////////////////////// CReference /////////////////////////////

///////////////////////////////////////
// Non-virtual methods of CReference
///////////////////////////////////////

CReference::CReference(CComPtr<IMgaFCO> mgaRefd, CComPtr<IMgaFCO> mgaTermRefd) : mgaReferee(mgaRefd), mgaTerminalReferee(mgaTermRefd)
{
	mgaReferee = mgaRefd;
	mgaTerminalReferee = mgaTermRefd;
	if(!IsNull()) {
		{
			CComBSTR bstr;
			COMTHROW(mgaRefd->get_Name(&bstr));
			CopyTo(bstr,targetName);
		}
		{
			CComPtr<IMgaMetaFCO> meta;
			COMTHROW(mgaRefd->get_Meta(&meta));
			CComBSTR bstr;
			COMTHROW(meta->get_DisplayedName(&bstr));
			CopyTo(bstr, targetKindDisplayedName);
		}
	}
}

CString CReference::GetInfoText(CString &name)
{
	CString txt;
	if(IsNull())
		txt = name + " -> null ";
	else
		txt.Format("%s -> %s (%s) ", name, targetName, targetKindDisplayedName);
	return CString(txt);
}
///////////////////////////////////////
// Static methods of CReference
///////////////////////////////////////

///////////////////////////////////////
// Virtual methods of CReference
///////////////////////////////////////

////////////////////////////////// CGuiReference /////////////////////////////

///////////////////////////////////////
// Non-virtual methods of CGuiReference
///////////////////////////////////////
///////////////////////////////////////
// Static methods of CGuiReference
///////////////////////////////////////
///////////////////////////////////////
// Virtual methods of CGuiReference
///////////////////////////////////////


/////////////////////////////// CGuiCompoundReference //////////////////////////
////////////////////////////////////////////////
// Non-virtual methods of CGuiCompoundReference
////////////////////////////////////////////////

////////////////////////////////////////////////
// Static methods of CGuiCompoundReference
////////////////////////////////////////////////

////////////////////////////////////////////////
// Virtual methods of CGuiCompoundReference
////////////////////////////////////////////////

CGuiMetaAttributeList* CGuiCompoundReference::GetMetaAttributes()
{
	return &guiMeta->attrs;
}

CGuiMetaAspect* CGuiCompoundReference::GetKindAspect(CComPtr<IMgaMetaPart> metaPart)
{
	CComPtr<IMgaMetaFCO> metaFcoForAM;
	COMTHROW(GetTerminalReferee()->get_Meta(&metaFcoForAM));
	metaref_type metaRef;
	COMTHROW(metaFcoForAM->get_MetaRef(&metaRef));
	CGuiMetaModel* guiMetaModel = CGuiMetaProject::theInstance->GetGuiMetaModel(metaRef);
	VERIFY(guiMetaModel);

	CGuiMetaAspect* metaAspect = NULL;
	CComBSTR bstr;
	COMTHROW(metaPart->get_KindAspect(&bstr));
	CString kindAspect;
	CopyTo(bstr, kindAspect);
	if (kindAspect.IsEmpty()) {
		CComBSTR bstr;
		CComPtr<IMgaMetaAspect>	pAspect;
		COMTHROW(metaPart->get_ParentAspect(&pAspect));
		COMTHROW(pAspect->get_Name(&bstr));
		CopyTo(bstr, kindAspect);
		metaAspect = guiMetaModel->FindAspect(kindAspect);
		if(!metaAspect)	{
			metaAspect = guiMetaModel->GetFirstAspect();
			/*
			CComBSTR bstr;
			COMTHROW(metaRole->get_Name(&bstr));
			CString roleName;
			CopyTo(bstr,roleName);
			AfxMessageBox("Missing aspect mapping specification for model " + name + " aspect " + kindAspect +
					" role " + roleName + "!\nFirst aspect " + metaAspect->name + " is used!");
			*/
		}
	}
	else {
		metaAspect = guiMetaModel->FindAspect(kindAspect);
	}
	return metaAspect;
}


//////////////////////////////////// CGuiSet ////////////////////////////////

////////////////////////////////////////////////
// Non-virtual methods of CGuiSet
////////////////////////////////////////////////

void CGuiSet::Init(CGuiFcoList& objs, CGuiConnectionList& conns)
{
	if (!IsReal()) {
		return;
	}
	CComPtr<IMgaSet> mgaSet;
	COMTHROW(mgaFco.QueryInterface(&mgaSet));

	CComPtr<IMgaFCOs> fcos;
	COMTHROW(mgaSet->get_Members(&fcos));
	MGACOLL_ITERATE(IMgaFCO,fcos) {
		CComPtr<IMgaFCO> member;
		member = MGACOLL_ITER;
		CGuiFco* obj =  CGuiObject::FindObject(member, objs);
		if(!obj)
			obj =  CGuiObject::FindConnection(member, conns);
		VERIFY(obj);
		members.AddTail(obj);
	}
	MGACOLL_ITERATE_END;
}

bool CGuiSet::CheckMember(CGuiFco* fco)
{
	CComPtr<IMgaMetaSet> metaSet;
	COMTHROW(metaFco.QueryInterface(&metaSet));

	metaref_type mr = fco->GetRoleMetaRef();
	CString path;
	path.Format("%d", mr);
	CComBSTR bstr;
	CopyTo(path, bstr);

	VARIANT_BOOL ok = VARIANT_FALSE;
	COMTHROW(metaSet->CheckPath(bstr, &ok));

	return (ok != VARIANT_FALSE);
}

bool CGuiSet::ToggleMember(CGuiFco* member)
{
	VERIFY(mgaFco);
	CComPtr<IMgaSet> mgaSet;
	COMTHROW(mgaFco.QueryInterface(&mgaSet));
	POSITION pos = members.Find(member);
	if(pos) {
		COMTHROW(mgaSet->RemoveMember(member->mgaFco));
	}
	else {
		COMTHROW(mgaSet->AddMember(member->mgaFco));
	}
	return pos == 0;
}


////////////////////////////////////////////////
// Static methods of CGuiSet
////////////////////////////////////////////////

////////////////////////////////////////////////
// Virtual methods of CGuiSet
////////////////////////////////////////////////

////////////////////////////////// CGuiConnectionLabel /////////////////////////////

CGuiConnectionLabel::CGuiConnectionLabel():
	alignment(TA_BASELINE | TA_CENTER),
	primary(false)
{
}

void CGuiConnectionLabel::SetLabel(const CString& l)
{
	label = l;
}

void CGuiConnectionLabel::SetLocation(const CPoint& endPoint, const CPoint& nextPoint, const CRect& box)
{
	if (label.IsEmpty())
		return;

	int diffx = 3;
	int diffy = 3;
	BOOL f_center = box.IsRectNull();

	loc = endPoint;
	CPoint center = box.CenterPoint();

	bool skew = (endPoint.x != nextPoint.x && endPoint.y != nextPoint.y);
	double alpha = 0.0;
	bool moreVerticalThanHorizontal = true;
	if (skew) {
		alpha = atan2(-((double)nextPoint.y - endPoint.y), (double)nextPoint.x - endPoint.x);
		moreVerticalThanHorizontal = (alpha >= -3 * M_PI_4 && alpha < -M_PI_4) || (alpha < 3 * M_PI_4 && alpha >= M_PI_4);
	}
	RoutingDirection lineDir = Dir_None;
	if (!f_center)
		lineDir = PointOnSide(endPoint, box);

	if (f_center)
	{
		if (endPoint.x == nextPoint.x || skew && moreVerticalThanHorizontal)	// vertical line
		{
			alignment = TA_BASELINE | (primary ? TA_RIGHT : TA_LEFT);
			loc.x += primary ? -diffx : diffx;
		}
		else if (endPoint.y == nextPoint.y || skew && !moreVerticalThanHorizontal)	// horizontal line
		{
			alignment = TA_CENTER | (primary ? TA_BOTTOM : TA_TOP);
		}
		else
		{
			ASSERT(false);
		}
	}
	else
	{
		switch(lineDir) {
			case Dir_Top:	// up
				{
					loc.y -= diffy;
					loc.x += primary ? -diffx : diffx;
					alignment = TA_BOTTOM | (primary ? TA_RIGHT : TA_LEFT);
				}
				break;
			case Dir_Bottom:	// down
				{
					loc.y += diffy;
					loc.x += primary ? -diffx : diffx;
					alignment = TA_TOP | (primary ? TA_RIGHT : TA_LEFT);
				}
				break;
			case Dir_Left:		// left
				{
					loc.x -= diffx;
					alignment = TA_RIGHT | (primary ? TA_BOTTOM : TA_TOP);
				}
				break;
			default:
				ASSERT(false);
			case Dir_Right:		// right
				{
					loc.x += diffx;
					alignment = TA_LEFT | (primary ? TA_BOTTOM : TA_TOP);
				}
				break;
		}
	}
}

void CGuiConnectionLabel::Draw(Gdiplus::Graphics* gdip, COLORREF color, CGuiConnection* conn)
{
	if (label.IsEmpty())
		return;

	label.Replace("%name%", (LPCSTR)(conn->name));
	label.Replace("%kind%", (LPCSTR)(conn->kindDisplayedName));
	label.Replace("%role%", (LPCSTR)(conn->roleDisplayedName));

	CGuiMetaAttributeList *metaAttrs = conn->GetMetaAttributes();
	POSITION pos = metaAttrs->GetHeadPosition();
	while (pos) {
		CGuiMetaAttribute *metaAttr = metaAttrs->GetNext(pos);
		CString attrName;
		attrName += "%";
		attrName += metaAttr->name;
		attrName += "%";
		label.Replace(attrName, conn->attributeCache[metaAttr->name]);
	}

	if (label.IsEmpty())
		return;
	graphics.DrawGdipText(gdip, label, loc, graphics.GetGdipFont(GME_CONNLABEL_FONT), color, alignment);
}

////////////////////////////////// CGuiConnectionLabel /////////////////////////////

CGuiConnectionLabelSet::CGuiConnectionLabelSet()
{
	labels[GME_CONN_SRC_LABEL1].SetPrimary(false);
	labels[GME_CONN_SRC_LABEL2].SetPrimary(true);
	labels[GME_CONN_DST_LABEL1].SetPrimary(false);
	labels[GME_CONN_DST_LABEL2].SetPrimary(true);
	labels[GME_CONN_MAIN_LABEL].SetPrimary(true);
}

void CGuiConnectionLabelSet::SetLabel(int index, const CString& label)
{
	if (index < 0 || index >= GME_CONN_LABEL_NUM)
		return;
	labels[index].SetLabel(label);
}

void CGuiConnectionLabelSet::SetLocation(int index, const CPoint& endPoint, const CPoint& nextPoint, const CRect& box)
{
	if (index < 0 || index >= GME_CONN_LABEL_NUM)
		return;
	labels[index].SetLocation(endPoint, nextPoint, box);
}

void CGuiConnectionLabelSet::Draw(Gdiplus::Graphics* gdip, COLORREF color, CGuiConnection* conn)
{
	for(int i = 0; i < GME_CONN_LABEL_NUM; i++)
		labels[i].Draw(gdip, color, conn);
}


////////////////////////////////// CGuiConnection /////////////////////////////

////////////////////////////////////////////////
// Non-virtual methods of CGuiConnection
////////////////////////////////////////////////

CGuiConnection::CGuiConnection(CComPtr<IMgaFCO>& pt, CComPtr<IMgaMetaRole>& role, CGMEView* vw, int numAsp, bool resolve):
	CGuiFco(pt, role, vw, numAsp),
	visible					(NULL),
	src						(NULL),
	srcPort					(NULL),
	dst						(NULL),
	dstPort					(NULL),
	hovered					(false),
	selected				(false),
	connRegAutoRouteNotSet	(true),
	isAutoRouted			(theApp.useAutoRouting)
{
	CComPtr<IAutoRouterPath> dummy;
	routerPath = dummy;

	if (resolve)
		Resolve();

	{
		CString pref;
		GetPreference(pref, CONN_LINE_TYPE_PREF);
		lineType = (pref == "dash") ? GME_LINE_DASH : GME_LINE_SOLID;
	}
	{
		CString pref;
		GetPreference(pref, CONN_SRC_END_STYLE_PREF);
		if ( pref == "arrow" )
			srcStyle = GME_ARROW_END;
		else if ( pref == "diamond" )
			srcStyle = GME_DIAMOND_END;
		else if ( pref == "empty diamond" )
			srcStyle = GME_EMPTYDIAMOND_END;
		else if ( pref == "apex" )
			srcStyle = GME_APEX_END;
		else if ( pref == "empty apex" )
			srcStyle = GME_EMPTYAPEX_END;
		else if ( pref == "bullet" )
			srcStyle = GME_BULLET_END;
		else if ( pref == "empty bullet" )
			srcStyle = GME_EMPTYBULLET_END;
		else if ( pref == "left half arrow" )
			srcStyle = GME_HALFARROWLEFT_END;
		else if ( pref == "right half arrow" )
			srcStyle = GME_HALFARROWRIGHT_END;
		else
			srcStyle = GME_BUTT_END;
	}
	{
		CString pref;
		GetPreference(pref, CONN_DST_END_STYLE_PREF);
		if ( pref == "arrow" )
			dstStyle = GME_ARROW_END;
		else if ( pref == "diamond" )
			dstStyle = GME_DIAMOND_END;
		else if ( pref == "empty diamond" )
			dstStyle = GME_EMPTYDIAMOND_END;
		else if ( pref == "apex" )
			dstStyle = GME_APEX_END;
		else if ( pref == "empty apex" )
			dstStyle = GME_EMPTYAPEX_END;
		else if ( pref == "bullet" )
			dstStyle = GME_BULLET_END;
		else if ( pref == "empty bullet" )
			dstStyle = GME_EMPTYBULLET_END;
		else if ( pref == "left half arrow" )
			dstStyle = GME_HALFARROWLEFT_END;
		else if ( pref == "right half arrow" )
			dstStyle = GME_HALFARROWRIGHT_END;
		else
			dstStyle = GME_BUTT_END;
	}

	{
		ReadARPreferences();
	}
	{
		CString pref;

		GetPreference(pref,CONN_LABEL_FORMATSTR_PREF);
		labelset.SetLabel(GME_CONN_MAIN_LABEL, pref);
		GetPreference(pref,CONN_SRC_LABEL1_PREF);
		labelset.SetLabel(GME_CONN_SRC_LABEL1, pref);
		GetPreference(pref,CONN_SRC_LABEL2_PREF);
		labelset.SetLabel(GME_CONN_SRC_LABEL2, pref);
		GetPreference(pref,CONN_DST_LABEL1_PREF);
		labelset.SetLabel(GME_CONN_DST_LABEL1, pref);
		GetPreference(pref,CONN_DST_LABEL2_PREF);
		labelset.SetLabel(GME_CONN_DST_LABEL2, pref);
	}
	if (!GetColorPreference(color, COLOR_PREF)) {
		color = GME_BLACK_COLOR;
	}
	if (!GetColorPreference(nameColor, NAME_COLOR_PREF)) {
		nameColor = GME_BLACK_COLOR;
	}
	ReadCustomPathData();
	ReadAutoRouteState();
	RefreshAttributeCache();
}

void CGuiConnection::GiveConnectionEndErroMessage(const CString& mainMsg, const CGuiPort* otherPort) const
{
	if (!view->ShouldSupressConnectionCheckAlert()) {
		CString msgEx;
		msgEx.Append("Connection properties:\n");
		msgEx.Append("\nName: ");
		msgEx.Append(name);
		msgEx.Append("\nKind Name: ");
		msgEx.Append(kindDisplayedName);
		msgEx.Append("\nRole Name: ");
		msgEx.Append(roleDisplayedName);
		msgEx.Append("\nID: ");
		msgEx.Append(id);
		msgEx.Append("\nEndpoint properties:");
		msgEx.Append("\n\tName: ");
		msgEx.Append(otherPort->name);
		msgEx.Append("\n\tID: ");
		msgEx.Append(otherPort->id);
		msgEx.Append("\nMissing endpoints sometimes can be generated by UDM based interpreters.");
		msgEx.Append("\nCancel button supress further connection error messages like this.");
		int retVal = view->MessageBox(msgEx, mainMsg, MB_OKCANCEL | MB_ICONERROR);
		if (retVal == IDCANCEL)
			view->SupressConnectionCheckAlert();
	}
}

void CGuiConnection::Resolve()
{
	try {
		view->BeginTransaction(TRANSACTION_READ_ONLY);
		CComPtr<IMgaSimpleConnection> conn;
		mgaFco.QueryInterface(&conn);
		VERIFY(conn);

		// Compute visibility
		visible = new bool[numParentAspects];
		memset(visible, 0, numParentAspects * sizeof(bool));
		CComPtr<IMgaMetaParts> mmParts;
		COMTHROW(metaRole->get_Parts(&mmParts));
		MGACOLL_ITERATE(IMgaMetaPart,mmParts) {
			CComPtr<IMgaMetaPart> mmPart;
			mmPart = MGACOLL_ITER;
			CComPtr<IMgaMetaAspect> mmAspect;
			COMTHROW(mmPart->get_ParentAspect(&mmAspect));
			CComBSTR bstr;
			COMTHROW(mmAspect->get_Name(&bstr));
			CString aspName;
			CopyTo(bstr,aspName);
			CGuiMetaAspect *guiMetaAsp = view->guiMeta->FindAspect(aspName);
			VERIFY(guiMetaAsp);
			VERIFY(guiMetaAsp->index < numParentAspects);
			visible[guiMetaAsp->index] = true;
		}
		MGACOLL_ITERATE_END;
		
		srcPort = NULL;
		dstPort = NULL;
		if(visible[parentAspect]) {
			CComPtr<IMgaFCO> mgaSrc;

			// Lookup first conn. reference first
			CComPtr<IMgaFCOs> mgaSrcRefs;
			bool src_err = false;
			HRESULT src_hr = S_OK;
			{
				try {
					src_hr = conn->get_SrcReferences(&mgaSrcRefs);
				}
				catch(hresult_exception &e)
				{
					ASSERT(FAILED(e.hr));
					SetErrorInfo(e.hr);
					src_hr = e.hr;
				}
			}
			if (SUCCEEDED(src_hr) || mgaSrcRefs) {
				long nSrcRef = 0;
				COMTHROW(mgaSrcRefs->get_Count(&nSrcRef));
				if (nSrcRef > 0) {
					COMTHROW(mgaSrcRefs->get_Item(1, &mgaSrc));
				}
				else {
					COMTHROW(conn->get_Src(&mgaSrc));
				}

				POSITION pos = view->children.GetHeadPosition();
				while (pos) {
					CGuiFco* fco = view->children.GetNext(pos);
					ASSERT(fco != NULL);
					CGuiObject* srcObj = fco->dynamic_cast_CGuiObject();
					if (srcObj && srcObj->IsVisible()) {
						srcPort = srcObj->FindPort(mgaSrc);
						if (srcPort) {
							CGuiCompoundReference* modelRefObj = srcObj->dynamic_cast_CGuiCompoundReference();
							if (modelRefObj) {
								CComPtr<IMgaFCO> mgaSrcPort;
								COMTHROW(conn->get_Src(&mgaSrcPort));
								CGuiPort *srcFPort = srcObj->FindPort(mgaSrcPort);
								srcPort = srcFPort ? srcFPort : srcPort;
								if ((srcPort->IsRealPort()) && (!nSrcRef) ) {
									continue;
								}
							}
							src = srcPort->parent->GetParent();
							VERIFY(src);
							break;
						}
					}
				}
				if (!srcPort) {
					visible[parentAspect] = false;
				}
			} else {
				src_err = true;
			}

			CComPtr<IMgaFCO> mgaDst;

			// Lookup first conn. reference first
			HRESULT dst_hr = S_OK;
			CComPtr<IMgaFCOs> mgaDstRefs;
			bool dst_err = false;
			{
				try {
					dst_hr = conn->get_DstReferences(&mgaDstRefs);
				}
				catch(hresult_exception &e)
				{
					ASSERT(FAILED(e.hr));
					SetErrorInfo(e.hr);
					dst_hr = e.hr;
				}
			}
			if (SUCCEEDED(dst_hr) && mgaDstRefs) {
				long nDstRef = 0;
				COMTHROW(mgaDstRefs->get_Count(&nDstRef));
				if (nDstRef > 0) {
					COMTHROW(mgaDstRefs->get_Item(1, &mgaDst));
				}
				else {
					COMTHROW(conn->get_Dst(&mgaDst));
				}

				POSITION pos = view->children.GetHeadPosition();
				while (pos) {
					CGuiFco* fco = view->children.GetNext(pos);
					ASSERT(fco != NULL);
					CGuiObject* dstObj = fco->dynamic_cast_CGuiObject();
					if (dstObj && dstObj->IsVisible()) {
						dstPort = dstObj->FindPort(mgaDst);
						if (dstPort) {
							CGuiCompoundReference* modelRefObj = dstObj->dynamic_cast_CGuiCompoundReference();
							if (modelRefObj) {
								CComPtr<IMgaFCO> mgaDstPort;
								COMTHROW(conn->get_Dst(&mgaDstPort));
								CGuiPort *dstFPort = dstObj->FindPort(mgaDstPort);
								dstPort = dstFPort ? dstFPort : dstPort;
								if ((dstPort->IsRealPort()) && (!nDstRef) ) {
									continue;
								}
							}
							dst = dstPort->parent->GetParent();
							VERIFY(dst);
							break;
						}
					}
				}
				if (!dstPort) {
					visible[parentAspect] = false;
				}
			} else {
				dst_err = true;
			}
			if (src_err || dst_err) {
				if (src_err) {
					GiveConnectionEndErroMessage("Source endpoint error", dstPort);
				} else if (dst_err) {
					GiveConnectionEndErroMessage("Destination endpoint error", srcPort);
				}
			}

			if (visible[parentAspect]) {
				if( !srcPort->outConns.Find( this)) // WAS: outConns.AddTail(this); and as a result as aspects have cycled the collection got bigger and bigger
					srcPort->outConns.AddTail(this);// NOW: added only if ptr was not already stored in outConns
				
				if( !dstPort->inConns.Find( this)) // WAS: inConns.AddTail(this);
					dstPort->inConns.AddTail(this);// NOW: added only if ptr was not already stored in inConns
			}

		}
		view->CommitTransaction();
	}
	catch (hresult_exception e) {
		view->AbortTransaction(e.hr);
	}
}

void CGuiConnection::Draw(HDC pDC, Gdiplus::Graphics* gdip)
{
	if(!IsVisible())
		return;
	VERIFY(src->IsVisible());
	VERIFY(dst->IsVisible());

	CPointList points;
	GetPointList(points);

	if (points.GetSize() <= 0) {
		ASSERT(false);
		return;
	}

	std::vector<long> customizedEdgeIndexes;
	if (selected && IsAutoRouted())
		customizedEdgeIndexes = GetRelevantCustomizedEdgeIndexes();
	graphics.DrawConnection(gdip, points, customizedEdgeIndexes, grayedOut ? GME_GRAYED_OUT_COLOR : color,
							lineType, srcStyle, dstStyle, view->m_zoomVal > ZOOM_NO, !IsAutoRouted() && selected,
							selected ? 3 : hovered ? 5 : 1);

	if (points.GetSize() < 2) {
		ASSERT(false);
		return;
	}

	POSITION pos = points.GetHeadPosition();
	CPoint start = points.GetNext(pos);
	CPoint start2 = points.GetNext(pos);
	pos = points.GetTailPosition();
	CPoint end = points.GetPrev(pos);
	CPoint end2 = points.GetPrev(pos);

	// Get the center position of the whole connection

	int segments = points.GetCount();
	pos = points.FindIndex((int)(segments/2)-1);
	CPoint middle = points.GetNext(pos);
	CPoint middle2 = points.GetNext(pos);
	CRect tmpRect(middle, middle2);
	middle = tmpRect.CenterPoint();

	const CRect srcRect = src->GetLocation();
	const CRect dstRect = dst->GetLocation();

	CRect box;
	box = src->GetLocation();
	if (srcPort != NULL && srcPort->IsRealPort())
		box = srcPort->GetLocation() + box.TopLeft();
	labelset.SetLocation(0, start, start2, box);
	labelset.SetLocation(1, start, start2, box);
	box = dst->GetLocation();
	if (dstPort != NULL && dstPort->IsRealPort())
		box = dstPort->GetLocation() + box.TopLeft();
	labelset.SetLocation(2, end, end2, box);
	labelset.SetLocation(3, end, end2, box);
	box = CRect(0, 0, 0, 0);
	labelset.SetLocation(GME_CONN_MAIN_LABEL, middle, middle2, box);


	labelset.Draw(gdip, (grayedOut ? GME_GRAYED_OUT_COLOR : nameColor), this);
}

void CGuiConnection::RemoveFromRouter(CAutoRouter &router)
{
	router.DeleteConnection(this);
}

void CGuiConnection::GrayOutEndPoints()
{
	src->GrayOut(grayedOut);
	dst->GrayOut(grayedOut);
}

void CGuiConnection::RefreshAttributeCache()
{
	attributeCache.RemoveAll();

	CGuiMetaAttributeList* guiMetaAttrs = GetMetaAttributes();
	POSITION pos = guiMetaAttrs->GetHeadPosition();

	while (pos) {
		CGuiMetaAttribute* guiMetaAttr = guiMetaAttrs->GetNext(pos);
		CComPtr<IMgaAttribute> attr;
		CComPtr<IMgaMetaAttribute> metaAttr;
		attval_enum	tp;
		COMTHROW(guiMetaAttr->mgaMeta.QueryInterface(&metaAttr));
		COMTHROW(metaAttr->get_ValueType(&tp));
		COMTHROW(mgaFco->get_Attribute(metaAttr, &attr));
		CComVariant	attrValue;
		COMTHROW(attr->get_Value(&attrValue));

		CString aval;
		CString aname = guiMetaAttr->name;

		if (tp == ATTVAL_BOOLEAN) {
			VERIFY(attrValue.vt == VT_BOOL);
			aval = attrValue.boolVal ? "True" : "False";
		}
		else if (tp == ATTVAL_REFERENCE) {
			aval = "Reference attr. label not supported";	// Sorry, maybe later
		}
		else if (tp == ATTVAL_ENUM) {
			VERIFY(attrValue.vt == VT_BSTR);
			CString attrValueStr(attrValue.bstrVal);
			/* CGuiMenuCtrl *guiMenuCtrl = dynamic_cast<CGuiMenuCtrl *>(guiMetaAttr->depCtrl);
			if (guiMenuCtrl) {
				aval = attrValue.bstrVal;
				int idx = guiMenuCtrl->FindItemByValue(aval);
				if (idx != -1)
					aval = (guiMenuCtrl->items[idx]).label;
				else
					aval = "N/A";
			}
			else {
				aval = "N/A";
			} */
			aval = "N/A";
			CComPtr<IMgaMetaEnumItems> metaEnumItems;
			COMTHROW(metaAttr->get_EnumItems(&metaEnumItems));

			MGACOLL_ITERATE(IMgaMetaEnumItem,metaEnumItems)
			{
				CComBSTR bstrItemLabel;
				CComBSTR bstrItemValue;
				COMTHROW(MGACOLL_ITER->get_DisplayedName(&bstrItemLabel));
				COMTHROW(MGACOLL_ITER->get_Value(&bstrItemValue));

				CString strItemValue(bstrItemValue);
				if (strItemValue == attrValueStr) {
					aval = bstrItemLabel;
				}
			}
			MGACOLL_ITERATE_END;

		}
		else {
			if (attrValue.vt != VT_BSTR)
				attrValue.ChangeType(VT_BSTR);
			aval = attrValue.bstrVal;
		}
		attributeCache[aname] = aval;
	}
}

void CGuiConnection::ReadARPreferences()
{
	CString val;
	if (GetPreference(val, AUTOROUTER_PREF)) {
		autorouterPrefs[GME_START_NORTH]	= (val.Find("N") != -1);
		autorouterPrefs[GME_START_EAST]		= (val.Find("E") != -1);
		autorouterPrefs[GME_START_SOUTH]	= (val.Find("S") != -1);
		autorouterPrefs[GME_START_WEST]		= (val.Find("W") != -1);
		autorouterPrefs[GME_END_NORTH]		= (val.Find("n") != -1);
		autorouterPrefs[GME_END_EAST]		= (val.Find("e") != -1);
		autorouterPrefs[GME_END_SOUTH]		= (val.Find("s") != -1);
		autorouterPrefs[GME_END_WEST]		= (val.Find("w") != -1);
	} else {
		autorouterPrefs[GME_START_NORTH]	= false;
		autorouterPrefs[GME_START_EAST]		= false;
		autorouterPrefs[GME_START_SOUTH]	= false;
		autorouterPrefs[GME_START_WEST]		= false;
		autorouterPrefs[GME_END_NORTH]		= false;
		autorouterPrefs[GME_END_EAST]		= false;
		autorouterPrefs[GME_END_SOUTH]		= false;
		autorouterPrefs[GME_END_WEST]		= false;
	}
}

void CGuiConnection::GetPointList(CPointList& points) const
{
	if (routerPath.p)
	{
		//retrieve data from AutoRouter
		//CAutoRouterPath* p = static_cast<CAutoRouterPath*>(routerPath.p);

		// TODO: using CComSafeArray anywhere, see http://msdn.microsoft.com/de-de/library/3xzbsee8.aspx
		//There was a problem with uninitialized safearrays, so create a dummy:
		SAFEARRAY* pArr = NULL;

		COMTHROW(routerPath->GetPointList(&pArr));

		//one dim., long elements
		if ((pArr)->cDims == 1 && (pArr)->cbElements == 4)
		{
			//length
			long elementNum = (pArr)->rgsabound[0].cElements;

			if (elementNum > 0)
			{
				//lock it before use
				SafeArrayLock(pArr);
				long* pArrElements = (long*) (pArr)->pvData;

				for (int i = 0; i < elementNum / 2; i++)
				{
					CPoint p(pArrElements[2 * i], pArrElements[2 * i + 1]);
					points.AddTail(p);
				}

				SafeArrayUnlock(pArr);
			}
		}
		//clear memory
		SafeArrayDestroy(pArr);
	}

	if (!routerPath.p || points.GetSize() <= 0)
	{
		CPoint start = srcPort->GetLocation().CenterPoint() + src->GetLocation().TopLeft();
		CPoint end   = dstPort->GetLocation().CenterPoint() + dst->GetLocation().TopLeft();
		points.AddHead(start);
		points.AddTail(end);
	}
}

int CGuiConnection::GetEdgeCount(void) const
{
	CPointList points;
	GetPointList(points);
	return points.GetSize() - 1;
}

bool CGuiConnection::AdjustCoordLimits(CPointList& points, int edgeIndex, bool isPathEnd, bool xOrY, POSITION pos,
									   int ptCoord, int lastlastCoord, int& coordMinLimit, int& coordMaxLimit) const
{
	if (!isPathEnd) {
		// Internal edge
		CPoint nextPt = points.GetNext(pos);
		int nextPtCoord = xOrY ? nextPt.x : nextPt.y;
		if (ptCoord < nextPtCoord && ptCoord < lastlastCoord)
			coordMinLimit = LONG_MIN;
		else
			coordMinLimit = min(nextPtCoord, lastlastCoord);
		if (ptCoord > nextPtCoord && ptCoord > lastlastCoord)
			coordMaxLimit = LONG_MAX;
		else
			coordMaxLimit = max(nextPtCoord, lastlastCoord);
	} else {
		// Inspect entities at the end to calculate limits
		CRect portRect;
		portRect.SetRectEmpty();
		if (edgeIndex == 0) {
			if (srcPort != NULL && srcPort->IsRealPort()) {
				return true;
			} else if (src != NULL) {
				portRect = src->GetLocation();
			}
		} else {
			if (dstPort != NULL && dstPort->IsRealPort()) {
				return true;
			} else if (dst != NULL) {
				portRect = dst->GetLocation();
			}
		}

		if (!portRect.IsRectEmpty()) {
			if (xOrY) {
				coordMinLimit = portRect.left;
				coordMaxLimit = portRect.right;
			} else {
				coordMinLimit = portRect.top;
				coordMaxLimit = portRect.bottom;
			}
		} else {
			ASSERT(false);
			return true;
		}
	}

	return false;
}

int CGuiConnection::GetEdgeIndex(const CPoint& point, CPoint& startPoint, CPoint& endPoint, CPoint& thirdPoint,
								 ConnectionPartMoveType& connectionMoveMethod, bool& horizontalOrVerticalEdge,
								 bool& isPartFixed, int& xMinLimit, int& xMaxLimit, int& yMinLimit, int& yMaxLimit) const
{
	CPointList points;
	GetPointList(points);

	int numEdges = points.GetSize() - 1;
	CPoint last = emptyPoint;
	CPoint lastlast = emptyPoint;
	POSITION pos = points.GetHeadPosition();
	int i = 0;
	CComPtr<IAutoRouterGraph> comAg;
	COMTHROW(routerPath->GetOwner(&comAg));
	ASSERT(comAg);
	if (pos) {
		CPoint pt = points.GetNext(pos);
		last = pt;
		while (pos) {
			pt = points.GetNext(pos);
			if (IsAutoRouted()) {
				bool moveAction = false;
				if (last.x == pt.x) {	// vertical edge, horizontal move
					if (abs(pt.x - point.x) <= 3 &&
						(point.y >= min(last.y, pt.y) - 3 ||
						 point.y <= max(last.y, pt.y) + 3))
					{
						connectionMoveMethod = HorizontalEdgeMove;
						horizontalOrVerticalEdge = false;
						moveAction = true;
					}
				} else {	// horizontal line, vertical move
					if (abs(pt.y - point.y) <= 3 &&
						(point.x >= min(last.x, pt.x) - 3 ||
						 point.x <= max(last.x, pt.x) + 3))
					{
						connectionMoveMethod = VerticalEdgeMove;
						horizontalOrVerticalEdge = true;
						moveAction = true;
					}
				}
				if (i < numEdges - 1 &&		// We can't drag two connected edges at the last point!
					abs(pt.x - point.x) <= 3 &&
					abs(pt.y - point.y) <= 3)
				{
					connectionMoveMethod = AdjacentEdgeMove;
				}
				if (moveAction) {
					VARIANT_BOOL comIsFixed = VARIANT_FALSE;
					comAg->IsEdgeFixed(routerPath, last.x, last.y, pt.x, pt.y, &comIsFixed);
					isPartFixed = (comIsFixed == VARIANT_TRUE);

					startPoint = last;
					endPoint = pt;
					bool isPathEnd = (i == 0 || i == numEdges - 1);

					bool isPartFixed2 = false;
					if (connectionMoveMethod == HorizontalEdgeMove) {
						isPartFixed2 = AdjustCoordLimits(points, i, isPathEnd, true, pos,
														 pt.x, lastlast.x, xMinLimit, xMaxLimit);
					} else if (connectionMoveMethod == VerticalEdgeMove) {
						isPartFixed2 = AdjustCoordLimits(points, i, isPathEnd, false, pos,
														 pt.y, lastlast.y, yMinLimit, yMaxLimit);
					} else  if (connectionMoveMethod == AdjacentEdgeMove) {
						POSITION nextPos = pos;
						CPoint nextPt = points.GetNext(nextPos);
						thirdPoint = nextPt;
						if (horizontalOrVerticalEdge) {
							isPartFixed2 = AdjustCoordLimits(points, i, isPathEnd, false, pos,
															 pt.y, lastlast.y, yMinLimit, yMaxLimit);
							if (isPartFixed2) {
								connectionMoveMethod = HorizontalEdgeMove;
								isPartFixed2 = false;
							}
							isPartFixed2 = AdjustCoordLimits(points, i + 1, i >= numEdges - 2, true, nextPos,
															 nextPt.x, last.x, xMinLimit, xMaxLimit);
							if (isPartFixed2) {
								if (connectionMoveMethod != HorizontalEdgeMove) {
									connectionMoveMethod = VerticalEdgeMove;
									isPartFixed2 = false;
								}
							}
						} else {
							isPartFixed2 = AdjustCoordLimits(points, i, isPathEnd, true, pos,
															 pt.x, lastlast.x, xMinLimit, xMaxLimit);
							if (isPartFixed2) {
								connectionMoveMethod = VerticalEdgeMove;
								isPartFixed2 = false;
							}
							isPartFixed2 = AdjustCoordLimits(points, i + 1, i >= numEdges - 2, false, nextPos,
															 nextPt.y, last.y, yMinLimit, yMaxLimit);
							if (isPartFixed2) {
								if (connectionMoveMethod != VerticalEdgeMove) {
									connectionMoveMethod = HorizontalEdgeMove;
									isPartFixed2 = false;
								}
							}
						}
					}
					isPartFixed |= isPartFixed2;

					return i;
				}
			} else {
				if (abs(pt.x - point.x) <= 3 && abs(pt.y - point.y) <= 3) {
					startPoint = last;
					CPoint next = points.GetNext(pos);
					endPoint = next;

					connectionMoveMethod = ModifyExistingCustomPoint;
					isPartFixed = false;
					return i;
				} else {
					if (IsOnEdge(last, pt, point))
					{
						startPoint = last;
						endPoint = pt;

						connectionMoveMethod = InsertNewCustomPoint;
						isPartFixed = false;
						return i;
					}
				}
			}

			i++;
			lastlast = last;
			last = pt;
		}
	}

	return -1;
}

int CGuiConnection::IsPathAt(const CPoint& point, ConnectionPartMoveType& connectionMoveMethod,
							 bool& horizontalOrVerticalEdge, bool& isPartFixed) const
{
	CPoint tmpPoint;
	int tmpLimit;
	return GetEdgeIndex(point, tmpPoint, tmpPoint, tmpPoint, connectionMoveMethod, horizontalOrVerticalEdge,
						isPartFixed, tmpLimit, tmpLimit, tmpLimit, tmpLimit);
}

long CGuiConnection::IsPointOnSectionAndDeletable(long edgeIndex, const CPoint& point)
{
	CPointList points;
	GetPointList(points);

	int numEdges = points.GetSize() - 1;
	CPoint last;
	CPoint lastlast;
	POSITION pos = points.GetHeadPosition();
	int i = 0;
	if (pos) {
		CPoint pt = points.GetNext(pos);
		last = pt;
		while (pos) {
			pt = points.GetNext(pos);

			if (i == edgeIndex) {
				if (pos) {
					CPoint next = points.GetNext(pos);

					if (IsOnEdge(last, next, point, 5)) {
						return i;
					}
				}
				return -1;
			}

			i++;
			lastlast = last;
			last = pt;
		}
	}

	return -1;
}

std::vector<long> CGuiConnection::GetRelevantCustomizedEdgeIndexes(void)
{
	long asp = view->currentAspect->index;
	std::vector<long> customizedEdgeIndexes;
	std::vector<CustomPathData>::iterator ii = customPathData.begin();
	while (ii != customPathData.end()) {
		if ((*ii).aspect == asp || asp == -1) {
			if (IsAutoRouted() && (*ii).type == SimpleEdgeDisplacement ||
				!IsAutoRouted() && (*ii).type != SimpleEdgeDisplacement)
			{
				customizedEdgeIndexes.push_back((*ii).edgeIndex);
			}
		}
		++ii;
	}
	return customizedEdgeIndexes;
}

void CGuiConnection::FillOutCustomPathData(CustomPathData& pathData, PathCustomizationType custType, long asp,
										   int newPosX, int newPosY, int edgeIndex, bool horizontalOrVerticalEdge)
{
	InitCustomPathData(pathData);
	pathData.version					= CONNECTIONCUSTOMIZATIONDATAVERSION;
	pathData.aspect						= asp;
	pathData.edgeIndex					= edgeIndex;
	pathData.edgeCount					= GetEdgeCount();
	pathData.type						= custType;
	pathData.horizontalOrVerticalEdge	= horizontalOrVerticalEdge ? VARIANT_TRUE : VARIANT_FALSE;
	if (custType == SimpleEdgeDisplacement) {
		pathData.x						= !horizontalOrVerticalEdge ? newPosX : 0;
		pathData.y						= horizontalOrVerticalEdge ? newPosX : 0;
	} else {
		pathData.x						= newPosX;
		pathData.y						= newPosY;
	}
}

std::vector<CustomPathData> CGuiConnection::GetCurrentPathCustomizations(void)
{
	std::vector<CustomPathData> cd;
	for (std::vector<CustomPathData>::iterator ii = customPathData.begin(); ii != customPathData.end(); ++ii) {
		if ((*ii).aspect == parentAspect)
			cd.push_back(*ii);
	}
	return cd;
}

bool CGuiConnection::HasPathCustomization(void) const
{
	return customPathData.size() > 0;
}

bool CGuiConnection::HasPathCustomizationForCurrentAspect(int edgeIndex) const
{
	return HasPathCustomizationForAspect(view->currentAspect->index, edgeIndex);
}

bool CGuiConnection::HasPathCustomizationForAspect(long asp, int edgeIndex) const
{
	return HasPathCustomizationForTypeAndAspect(asp, Invalid, edgeIndex);
}

bool CGuiConnection::HasPathCustomizationForTypeAndCurrentAspect(PathCustomizationType custType, int edgeIndex) const
{
	return HasPathCustomizationForTypeAndAspect(view->currentAspect->index, custType, edgeIndex);
}

bool CGuiConnection::HasPathCustomizationForTypeAndAspect(long asp, PathCustomizationType custType, int edgeIndex) const
{
	for (std::vector<CustomPathData>::const_iterator ii = customPathData.begin(); ii != customPathData.end(); ++ii) {
		if ((*ii).aspect == asp &&
			((*ii).edgeIndex == edgeIndex || edgeIndex == -1) &&
			((*ii).type == custType || custType == Invalid))
		{
			return true;
		}
	}
	return false;
}

void CGuiConnection::ReadCustomPathData(void)
{
	customPathData.clear();
	CString pref;
	if (GetPreference(pref, CUSTOMCONNECTIONDATA)) {
		if (pref != EMPTYCONNECTIONCUSTOMIZATIONDATAMAGIC) {	// -1 is a magic number for deleted data
			CString subStr;
			int curPos = 0;
			subStr = pref.Tokenize(";", curPos);
			while (subStr != "") {
				TRACE1("\tResulting token: %s\n", subStr);
				CustomPathData pathData;
				InitCustomPathData(pathData);
				int curSubPos = 0;
				CString versionStr = subStr.Tokenize(",", curSubPos);
				pathData.version = strtol(versionStr, NULL, 10);
				ASSERT(pathData.version == CONNECTIONCUSTOMIZATIONDATAVERSION);
				if (pathData.version == CONNECTIONCUSTOMIZATIONDATAVERSION) {
					CString aspectStr = subStr.Tokenize(",", curSubPos);
					pathData.aspect = strtol(aspectStr, NULL, 10);
					CString edgeIndexStr = subStr.Tokenize(",", curSubPos);
					pathData.edgeIndex = strtol(edgeIndexStr, NULL, 10);
					CString edgeCountStr = subStr.Tokenize(",", curSubPos);
					pathData.edgeCount = strtol(edgeCountStr, NULL, 10);
					CString edgeCustomTypeStr = subStr.Tokenize(",", curSubPos);
					pathData.type = (PathCustomizationType)strtol(edgeCustomTypeStr, NULL, 10);
					TRACE("\tAsp %ld, Ind %ld, Cnt %d, Typ %ld", pathData.aspect, pathData.edgeIndex,
																 pathData.edgeCount, pathData.type);
					CString directionStr = subStr.Tokenize(",", curSubPos);
					pathData.horizontalOrVerticalEdge = (strtol(directionStr, NULL, 10) != 0 ? VARIANT_TRUE : VARIANT_FALSE);
					CString positionStr = subStr.Tokenize(",", curSubPos);
					pathData.x = strtol(positionStr, NULL, 10);
					positionStr = subStr.Tokenize(",", curSubPos);
					pathData.y = strtol(positionStr, NULL, 10);
					positionStr = subStr.Tokenize(",", curSubPos);
					pathData.numOfExtraLongData = strtol(positionStr, NULL, 10);
					ASSERT(pathData.numOfExtraLongData >= 0 && pathData.numOfExtraLongData <= 4);
					if (pathData.numOfExtraLongData > 0) {
						positionStr = subStr.Tokenize(",", curSubPos);
						pathData.l1 = strtol(positionStr, NULL, 10);
					}
					if (pathData.numOfExtraLongData > 1) {
						positionStr = subStr.Tokenize(",", curSubPos);
						pathData.l2 = strtol(positionStr, NULL, 10);
					}
					if (pathData.numOfExtraLongData > 2) {
						positionStr = subStr.Tokenize(",", curSubPos);
						pathData.l3 = strtol(positionStr, NULL, 10);
					}
					if (pathData.numOfExtraLongData > 3) {
						positionStr = subStr.Tokenize(",", curSubPos);
						pathData.l4 = strtol(positionStr, NULL, 10);
					}

					TRACE3(", Dir %ld, x %ld, y %ld",
						pathData.horizontalOrVerticalEdge == VARIANT_TRUE ? 1 : 0, pathData.x, pathData.y);
					if (pathData.numOfExtraLongData)
						TRACE(", num %ld, l1 %ld, l2 %ld, l3 %ld, l4 %ld\n",
							pathData.numOfExtraLongData, pathData.l1, pathData.l2, pathData.l3, pathData.l4);
					else
						TRACE("\n");

					positionStr = subStr.Tokenize(",", curSubPos);
					pathData.numOfExtraDoubleData = strtol(positionStr, NULL, 10);
					ASSERT(pathData.numOfExtraDoubleData >= 0 && pathData.numOfExtraDoubleData <= 8);
					if (pathData.numOfExtraDoubleData > 0) {
						positionStr = subStr.Tokenize(",", curSubPos);
						pathData.d1 = atof(positionStr);
					}
					if (pathData.numOfExtraDoubleData > 1) {
						positionStr = subStr.Tokenize(",", curSubPos);
						pathData.d2 = atof(positionStr);
					}
					if (pathData.numOfExtraDoubleData > 2) {
						positionStr = subStr.Tokenize(",", curSubPos);
						pathData.d3 = atof(positionStr);
					}
					if (pathData.numOfExtraDoubleData > 3) {
						positionStr = subStr.Tokenize(",", curSubPos);
						pathData.d4 = atof(positionStr);
					}
					if (pathData.numOfExtraDoubleData > 4) {
						positionStr = subStr.Tokenize(",", curSubPos);
						pathData.d5 = atof(positionStr);
					}
					if (pathData.numOfExtraDoubleData > 5) {
						positionStr = subStr.Tokenize(",", curSubPos);
						pathData.d6 = atof(positionStr);
					}
					if (pathData.numOfExtraDoubleData > 6) {
						positionStr = subStr.Tokenize(",", curSubPos);
						pathData.d7 = atof(positionStr);
					}
					if (pathData.numOfExtraDoubleData > 7) {
						positionStr = subStr.Tokenize(",", curSubPos);
						pathData.d8 = atof(positionStr);
					}

					if (pathData.numOfExtraDoubleData > 0) {
						TRACE("\t num %ld, d1 %lf, d2 %lf, d3 %lf, d4 %lf, d5 %lf, d6 %lf, d7 %lf, d8 %lf\n",
							pathData.numOfExtraDoubleData,
							pathData.d1, pathData.d2, pathData.d3, pathData.d4,
							pathData.d5, pathData.d6, pathData.d7, pathData.d8);
					}

					customPathData.push_back(pathData);
				} else {
					;	// TODO: Convert from older version to newer
				}
				subStr = pref.Tokenize(";", curPos);
			}
		}
	}
}

void CGuiConnection::WriteCustomPathData(bool handleTransaction)
{
	CString valStr;
	for (std::vector<CustomPathData>::iterator ii = customPathData.begin(); ii != customPathData.end(); ++ii) {
		CString edgeStr;
		edgeStr.Format("%ld,%ld,%ld,%d,%ld", (*ii).version, (*ii).aspect, (*ii).edgeIndex, (*ii).edgeCount, (*ii).type);
		CString additionalDataStr;
		additionalDataStr.Format(",%ld,%ld,%ld,%ld", (*ii).horizontalOrVerticalEdge == VARIANT_TRUE ? 1 : 0, (*ii).x, (*ii).y, (*ii).numOfExtraLongData);
		edgeStr.Append(additionalDataStr);
		if ((*ii).numOfExtraLongData > 0) {
			additionalDataStr.Format(",%ld", (*ii).l1);
			edgeStr.Append(additionalDataStr);
		}
		if ((*ii).numOfExtraLongData > 1) {
			additionalDataStr.Format(",%ld", (*ii).l2);
			edgeStr.Append(additionalDataStr);
		}
		if ((*ii).numOfExtraLongData > 2) {
			additionalDataStr.Format(",%ld", (*ii).l3);
			edgeStr.Append(additionalDataStr);
		}
		if ((*ii).numOfExtraLongData > 3) {
			additionalDataStr.Format(",%ld", (*ii).l4);
			edgeStr.Append(additionalDataStr);
		}
		additionalDataStr.Format(",%ld", (*ii).numOfExtraDoubleData);
		edgeStr.Append(additionalDataStr);
		if ((*ii).numOfExtraDoubleData > 0) {
			additionalDataStr.Format(",%lf", (*ii).d1);
			edgeStr.Append(additionalDataStr);
		}
		if ((*ii).numOfExtraDoubleData > 1) {
			additionalDataStr.Format(",%lf", (*ii).d2);
			edgeStr.Append(additionalDataStr);
		}
		if ((*ii).numOfExtraDoubleData > 2) {
			additionalDataStr.Format(",%lf", (*ii).d3);
			edgeStr.Append(additionalDataStr);
		}
		if ((*ii).numOfExtraDoubleData > 3) {
			additionalDataStr.Format(",%lf", (*ii).d4);
			edgeStr.Append(additionalDataStr);
		}
		if ((*ii).numOfExtraDoubleData > 4) {
			additionalDataStr.Format(",%lf", (*ii).d5);
			edgeStr.Append(additionalDataStr);
		}
		if ((*ii).numOfExtraDoubleData > 5) {
			additionalDataStr.Format(",%lf", (*ii).d6);
			edgeStr.Append(additionalDataStr);
		}
		if ((*ii).numOfExtraDoubleData > 6) {
			additionalDataStr.Format(",%lf", (*ii).d7);
			edgeStr.Append(additionalDataStr);
		}
		if ((*ii).numOfExtraDoubleData > 7) {
			additionalDataStr.Format(",%lf", (*ii).d8);
			edgeStr.Append(additionalDataStr);
		}
		if (valStr != "")
			valStr.Append(";");
		valStr.Append(edgeStr);
	}
	VERIFY(mgaFco);
	CComBSTR pathBstr;
	CopyTo(CUSTOMCONNECTIONDATA, pathBstr);
	CComBSTR bstrVal;
	if (valStr == "")
		bstrVal = EMPTYCONNECTIONCUSTOMIZATIONDATAMAGIC;
	else
		CopyTo(valStr, bstrVal);
	if (handleTransaction)
		view->BeginTransaction();
	COMTHROW(mgaFco->put_RegistryValue(pathBstr, bstrVal));
	if (handleTransaction)
		view->CommitTransaction();
}

void CGuiConnection::InsertCustomPathData(CustomPathData& pathData)
{
	// Note:
	//	We assume that element are in ascending order by edgeIndexes
	//	Types and aspects can be mixed up, but edgeIndexes shoudl be in order within an aspect and type

	// Update indexes
	std::vector<CustomPathData>::iterator jj;	// insertion point
	bool found = false;
	for (std::vector<CustomPathData>::iterator ii = customPathData.begin(); ii != customPathData.end(); ++ii) {
		ASSERT((*ii).version == pathData.version);
		if ((*ii).aspect == pathData.aspect &&
			(*ii).type == pathData.type &&
			(*ii).edgeIndex >= pathData.edgeIndex)
		{
			if (!found)
				jj = ii;
			found = true;
			if (pathData.type == CustomPointCustomization)
				(*ii).edgeIndex = (*ii).edgeIndex + 1;
			else if (pathData.type == SimpleEdgeDisplacement)
				break;
			// TODO: other cases
		}
	}
	if (found)
		// Insert
		customPathData.insert(jj, pathData);
	else
		// If we didn't find elements with bigger or equal edgeIndexes, then we should insert it as last one (ascending order)
		customPathData.push_back(pathData);
}

void CGuiConnection::UpdateCustomPathData(CustomPathData& pathData)
{
	for (std::vector<CustomPathData>::iterator ii = customPathData.begin(); ii != customPathData.end(); ++ii) {
		ASSERT((*ii).version == pathData.version);
		if ((*ii).aspect == pathData.aspect &&
			(*ii).type == pathData.type &&
			(*ii).edgeIndex == pathData.edgeIndex)
		{
			CopyCustomPathData(pathData, (*ii));
			return;
		}
	}

	// not found => insert it, preserving order
	InsertCustomPathData(pathData);
}

void CGuiConnection::DeletePathCustomization(CustomPathData& pathData)
{
	long i = 0;
	bool found = false;
	for (std::vector<CustomPathData>::iterator ii = customPathData.begin(); ii != customPathData.end(); ++ii, i++) {
		ASSERT((*ii).version == pathData.version);
		if ((*ii).aspect == pathData.aspect &&
			(*ii).type == pathData.type)
		{
			if (pathData.type == SimpleEdgeDisplacement) {
				if ((*ii).edgeIndex == pathData.edgeIndex) {
					ASSERT((*ii).horizontalOrVerticalEdge == pathData.horizontalOrVerticalEdge);
					ii = customPathData.erase(ii);
					found = true;
					return;
				}
			} else if (pathData.type == CustomPointCustomization) {
				// in case of CustomPointCustomization delete by array index and not edgeIndex
				if (i == pathData.edgeIndex) {
					ii = customPathData.erase(ii);
					found = true;
					break;
				}
			} else {
				// TODO: other checks for other types
			}
		}
	}
	// update indexes in case of full customization
	if (pathData.type == CustomPointCustomization) {
		for (std::vector<CustomPathData>::iterator ii = customPathData.begin(); ii != customPathData.end(); ++ii) {
			ASSERT((*ii).version == pathData.version);
			if ((*ii).aspect == pathData.aspect &&
				(*ii).type == pathData.type)
			{
				ASSERT((*ii).edgeIndex != pathData.edgeIndex);	// because we just deleted it
				if ((*ii).edgeIndex > pathData.edgeIndex) {
					(*ii).edgeIndex = (*ii).edgeIndex - 1;
				}
			}
		}
	}
	// not found
	ASSERT(found);
}

bool CGuiConnection::DeleteAllPathCustomizationsForAnAspect(long asp)
{
	bool wereThereAnyDeletion = false;
	std::vector<CustomPathData>::iterator ii = customPathData.begin();
	while (ii != customPathData.end()) {
		if ((*ii).aspect == asp &&
			(IsAutoRouted() && (*ii).type == SimpleEdgeDisplacement ||
			!IsAutoRouted() && (*ii).type != SimpleEdgeDisplacement))
		{
			wereThereAnyDeletion = true;
			ii = customPathData.erase(ii);
		} else {
			++ii;
		}
	}
	return wereThereAnyDeletion;
}

bool CGuiConnection::DeleteAllPathCustomizationsForCurrentAspect(void)
{
	return DeleteAllPathCustomizationsForAnAspect(view->currentAspect->index);
}

void CGuiConnection::RemoveDeletedPathCustomizations(const std::vector<CustomPathData>& customPathDat)
{
	std::vector<CustomPathData>::const_iterator ii = customPathDat.begin();
	while (ii != customPathDat.end()) {
		std::vector<CustomPathData>::iterator jj = customPathData.begin();
		while (jj != customPathData.end()) {
			if ((*ii).aspect == (*jj).aspect &&
				(*ii).edgeIndex == (*jj).edgeIndex &&
				(*ii).type == (*jj).type)
			{
				jj = customPathData.erase(jj);
			} else {
				++jj;
			}
		}
		++ii;
	}
}

void CGuiConnection::SnapCoordIfApplicable(CustomPathData* coordToSet, const CPoint& last, const CPoint& pt)
{
	double radEps = 2.0 / 360.0 * 2 * M_PI;
	RoutingDirection dir = GetDir(last - pt);
	if (dir == Dir_Skew) {
		bool modify = false;
		RoutingDirection dirToGo = GetSkewDir(last - pt);
		if (dirToGo == Dir_Left || dirToGo == Dir_Right) {
			if (abs(last.y - pt.y) <= 3) {
				modify = true;
			} else if (abs(last.x - pt.x) != 0) {
				double alpha = atan2(-((double)pt.y - last.y), (double)pt.x - last.x);
				TRACE2("Horizontal alpha %lf %lf\n", alpha / M_PI * 180.0, alpha);
				if (abs(alpha + M_PI) < radEps || abs(alpha) < radEps || abs(alpha - M_PI) < radEps)
					modify = true;
			}
			if (modify)
				coordToSet->y = last.y;
		} else if (dirToGo == Dir_Top || dirToGo == Dir_Bottom) {
			if (abs(last.x - pt.x) <= 3) {
				modify = true;
			} else if (abs(last.y - pt.y) != 0) {
				double alpha = atan2((double)pt.x - last.x, -((double)pt.y - last.y));
				TRACE2("Vertical alpha %lf %lf\n", alpha / M_PI * 180.0, alpha);
				if (abs(alpha + M_PI) < radEps || abs(alpha) < radEps || abs(alpha - M_PI) < radEps)
					modify = true;
			}
			if (modify)
				coordToSet->x = last.x;
		}
	}
}

bool CGuiConnection::VerticalAndHorizontalSnappingOfConnectionLineSegments(long asp, int edgeIndex)
{
	if (IsAutoRouted() && customPathData.size() < 1)
		return false;

	CPointList points;
	GetPointList(points);

	int i = 0;
	CustomPathData* lastData = NULL;
	for (std::vector<CustomPathData>::iterator ii = customPathData.begin(); ii != customPathData.end(); ++ii) {
		ASSERT((*ii).version == CONNECTIONCUSTOMIZATIONDATAVERSION);
		if ((*ii).aspect == asp) {
			if ((*ii).type == CustomPointCustomization) {
				CPoint pt((*ii).x, (*ii).y);
				CPoint last;
				if (lastData != NULL) {
					last = CPoint(lastData->x, lastData->y);
				} else {
					last = points.GetHead();
				}
				if (edgeIndex == -1 || i == edgeIndex - 1 || i == edgeIndex)	// Apply snapping only to the point neighbour edges
					SnapCoordIfApplicable(&(*ii), last, pt);
				lastData = &(*ii);
				i++;
			}
		}
	}
	// see the very last connection line segment
	if (lastData != NULL && (edgeIndex == -1 || i == edgeIndex - 1 || i == edgeIndex)) {
		CPoint pt(lastData->x, lastData->y);
		CPoint last = points.GetTail();
		SnapCoordIfApplicable(lastData, last, pt);
	}

	return false;
}

bool CGuiConnection::IsAutoRouted(void) const
{
	if (view->beforeSecondAutoRoute && NeedsRouterPathConversion())
		return true;	// user just switched it, but we lie temporarily in order to be able to get the autorouted route

	return isAutoRouted;
}

void CGuiConnection::ConvertAutoRoutedPathToCustom(long asp)
{
	CPointList points;
	GetPointList(points);
	int numPoints = points.GetSize();

	POSITION pos = points.GetHeadPosition();
	int i = 0;
	while (pos) {
		CPoint pt = points.GetNext(pos);
		if (i > 0 && i < numPoints - 1) {	// do not include the start and end point
			CustomPathData pathData;
			FillOutCustomPathData(pathData, CustomPointCustomization, asp, pt.x, pt.y, i - 1, true);
			UpdateCustomPathData(pathData);
		}
		i++;
	}

	WriteCustomPathData(false);
}

void CGuiConnection::ReadAutoRouteState(void)
{
	CString autoRoutingStateStr;

	// The parent model's setting overrides the global (theApp.useAutoRouting) settings
	bool connRegAutoRoute = view->isModelAutoRouted;
	// The connection setting overrides the global or model settings
	if (GetPreference(autoRoutingStateStr, CONNECTIONAUTOROUTING)) {
		if (autoRoutingStateStr == "false")
			connRegAutoRoute = false;
		else
			connRegAutoRoute = true;
		connRegAutoRouteNotSet = false;
	} else {
		connRegAutoRouteNotSet = true;
	}
	isAutoRouted = connRegAutoRoute;
}

bool CGuiConnection::NeedsRouterPathConversion(void) const
{
	return (customPathData.size() < 1 && connRegAutoRouteNotSet && !isAutoRouted);
}

////////////////////////////////////////////////
// Static methods of CGuiConnection
////////////////////////////////////////////////

////////////////////////////////////////////////
// Virtual methods of CGuiConnection
////////////////////////////////////////////////



