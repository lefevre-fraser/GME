// AutoRouterPath.cpp : Implementation of CAutoRouterPath

#include "stdafx.h"
#include "AutoRouterPath.h"
#include "AutoRouterBox.h"
#include "AutoRouterGraph.h"
#include "AutoRouterPort.h"


void InitCustomPathData(CustomPathData& pathData)
{
	pathData.version					= CONNECTIONCUSTOMIZATIONDATAVERSION;
	pathData.aspect						= 0;
	pathData.edgeIndex					= 0;
	pathData.edgeCount					= 0;
	pathData.type						= SimpleEdgeDisplacement;
	pathData.horizontalOrVerticalEdge	= VARIANT_TRUE;
	pathData.x							= 0;
	pathData.y							= 0;
	pathData.numOfExtraLongData			= 0;
	pathData.l1							= 0;
	pathData.l2							= 0;
	pathData.l3							= 0;
	pathData.l4							= 0;
	pathData.numOfExtraDoubleData		= 0;
	pathData.d1							= 0.0;
	pathData.d2							= 0.0;
	pathData.d3							= 0.0;
	pathData.d4							= 0.0;
	pathData.d5							= 0.0;
	pathData.d6							= 0.0;
	pathData.d7							= 0.0;
	pathData.d8							= 0.0;
}

void CopyCustomPathData(const CustomPathData& src, CustomPathData& dst)
{
	dst.version						= src.version;
	dst.aspect						= src.aspect;
	dst.edgeIndex					= src.edgeIndex;
	dst.edgeCount					= src.edgeCount;
	dst.type						= src.type;
	dst.horizontalOrVerticalEdge	= src.horizontalOrVerticalEdge;
	dst.x							= src.x;
	dst.y							= src.y;
	dst.numOfExtraLongData			= src.numOfExtraLongData;
	dst.l1							= src.l1;
	dst.l2							= src.l2;
	dst.l3							= src.l3;
	dst.l4							= src.l4;
	dst.numOfExtraDoubleData		= src.numOfExtraDoubleData;
	dst.d1							= src.d1;
	dst.d2							= src.d2;
	dst.d3							= src.d3;
	dst.d4							= src.d4;
	dst.d5							= src.d5;
	dst.d6							= src.d6;
	dst.d7							= src.d7;
	dst.d8							= src.d8;
}

// Functions for CMapAutoRouterPath2CGuiConnection and CMapCARPath2CPointList, see AutoRouter.h and AutoRouterGraph.h
template<>
UINT AFXAPI HashKey<IAutoRouterPath*> (IAutoRouterPath* key)
{
	return (UINT)key;
}

template<>
BOOL AFXAPI CompareElements<LPIAutoRouterPath, LPIAutoRouterPath>
	 (const LPIAutoRouterPath* pElement1, const LPIAutoRouterPath* pElement2)
{
	if (*pElement1 == *pElement2)
		return true;
	return false;
}


// CAutoRouterPath implementation

CAutoRouterPath::CAutoRouterPath():
	owner(NULL),
	startport(NULL),
	endport(NULL),
	attributes(ARPATH_Default),
	state(ARPATHST_Default),
	isAutoRoutingOn(true)
{
}

HRESULT CAutoRouterPath::FinalConstruct(void)
{
	return S_OK;
}

void CAutoRouterPath::FinalRelease(void)
{
	DeleteAll();
	this->SetOwner(NULL);
}

// --- Points

POSITION CAutoRouterPath::GetPointPosAt(const CPoint& point, int nearness) const
{
	POSITION pos = points.GetHeadPosition();
	while( pos != NULL )
	{
		POSITION oldpos = pos;
		if( IsPointNear(points.GetNext(pos), point, nearness) )
			return oldpos;
	}
	
	return NULL;
}

POSITION CAutoRouterPath::GetEdgePosAt(const CPoint& point, int nearness) const
{
	CPoint a;
	CPoint b;

	POSITION pos = points.GetTailEdge(a, b);
	while( pos != NULL )
	{
		if( IsPointNearLine(point, a, b, nearness) )
			return pos;

		points.GetPrevEdge(pos, a, b);
	}

	return NULL;
}

bool CAutoRouterPath::IsConnected(void) const
{
	return (state & ARPATHST_Connected) != 0;
}

STDMETHODIMP CAutoRouterPath::AddTail(long px, long py)
{
	ASSERT( !IsConnected() );
	points.AddTail(CPoint(px, py));

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::DeleteAll()
{
	points.RemoveAll();
	state = ARPATHST_Default;

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::HasNoPoint(VARIANT_BOOL* result)
{
	if (points.IsEmpty())
		*result = VARIANT_TRUE;
	else
		*result = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::GetPointCount(long* result)
{
	*result = points.GetCount();

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::GetStartPoint(long* resultX, long* resultY)
{
	ASSERT( points.GetCount() >= 2 );
	const CPoint& pt = points.GetHead();
	*resultX = pt.x;
	*resultY = pt.y;

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::GetEndPoint(long* resultX, long* resultY)
{
	ASSERT( points.GetCount() >= 2 );
	const CPoint& pt = points.GetTail();
	*resultX = pt.x;
	*resultY = pt.y;

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::GetStartBox(long* p1, long* p2, long* p3, long* p4)
{
	CComPtr<IAutoRouterBox> startbox;
	HRESULT hr = startport->GetOwner(&startbox);
	ASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
		return hr;

	hr = startbox->GetRect(p1, p2, p3, p4);
	ASSERT(SUCCEEDED(hr));

	return hr;
}

STDMETHODIMP CAutoRouterPath::GetEndBox(long* p1, long* p2, long* p3, long* p4)
{
	CComPtr<IAutoRouterBox> endbox;
	HRESULT hr = endport->GetOwner(&endbox);
	ASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
		return hr;

	hr = endbox->GetRect(p1, p2, p3, p4);
	ASSERT(SUCCEEDED(hr));

	return hr;
}

STDMETHODIMP CAutoRouterPath::GetOutOfBoxStartPoint(long* resultX, long* resultY, RoutingDirection hintDir)
{
	long p1, p2, p3, p4;
	HRESULT hr = GetStartBox(&p1, &p2, &p3, &p4);
	ASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
		return hr;
	const CRect startBoxRect(p1, p2, p3, p4);

	ASSERT( hintDir != Dir_Skew );
	ASSERT( points.GetCount() >= 2 );
	POSITION pos = points.GetHeadPosition();
	CPoint p = points.GetNext(pos);
	RoutingDirection d = GetDir(points.GetAt(pos) - p);
	if (d == Dir_Skew)
		d = hintDir;
	ASSERT( IsRightAngle(d) );

	GetPointCoord(p, d) = GetRectOuterCoord(startBoxRect, d);
	ASSERT( points.GetAt(pos) == p || GetDir(points.GetAt(pos) - p) == d ); 

	*resultX = p.x;
	*resultY = p.y;

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::GetOutOfBoxEndPoint(long* resultX, long* resultY, RoutingDirection hintDir)
{
	long p1, p2, p3, p4;
	HRESULT hr = GetEndBox(&p1, &p2, &p3, &p4);
	ASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
		return hr;
	const CRect endBoxRect(p1, p2, p3, p4);

	ASSERT( hintDir != Dir_Skew );
	ASSERT( points.GetCount() >= 2 );
	POSITION pos = points.GetTailPosition();
	CPoint p = points.GetPrev(pos);
	RoutingDirection d = GetDir(points.GetAt(pos) - p);
	if (d == Dir_Skew)
		d = hintDir;
	ASSERT( IsRightAngle(d) );

	GetPointCoord(p, d) = GetRectOuterCoord(endBoxRect, d);
	ASSERT( points.GetAt(pos) == p || GetDir(points.GetAt(pos) - p) == d ); 

	*resultX = p.x;
	*resultY = p.y;

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::SimplifyTrivially()
{
	ASSERT( !IsConnected() );

	if( points.GetCount() <= 2 )
		return S_OK;
	
	POSITION pos = points.GetHeadPosition();

	POSITION pos1 = pos;
	ASSERT( pos1 != NULL );
	CPoint p1 = points.GetNext(pos);

	POSITION pos2 = pos;
	ASSERT( pos2 != NULL );
	CPoint p2 = points.GetNext(pos);

	RoutingDirection dir12 = GetDir(p2-p1);

	POSITION pos3 = pos;
	ASSERT( pos3 != NULL );
	CPoint p3 = points.GetNext(pos);

	RoutingDirection dir23 = GetDir(p3-p2); 

	for(;;)
	{
		if( dir12 == Dir_None || dir23 == Dir_None ||
			(dir12 != Dir_Skew && dir23 != Dir_Skew &&
			(dir12 == dir23 || dir12 == ReverseDir(dir23)) ) )
		{
			points.RemoveAt(pos2);
			dir12 = GetDir(p3-p1);
		}
		else
		{
			pos1 = pos2;
			p1 = p2;
			dir12 = dir23;
		}

		if( pos == NULL )
			return S_OK;

		pos2 = pos3;
		p2 = p3;

		pos3 = pos;
		p3 = points.GetNext(pos);

		dir23 = GetDir(p3-p2);
	}

#ifdef _DEBUG
	AssertValidPoints();
#endif

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::ModifyPoints(SAFEARRAY* pArr)
{
	//one dim., long elements
	if ((pArr)->cDims == 1 && (pArr)->cbElements == 4)
	{
		//length
		long elementNum = (pArr)->rgsabound[0].cElements;
		ASSERT(elementNum % 2 == 0);
		bool equalLength = points.GetSize() == elementNum / 2;
		ASSERT(equalLength);
		if (!equalLength)
			return E_FAIL;
		if (elementNum > 0)
		{
			//lock it before use
			SafeArrayLock(pArr);
			long* pArrElements = (long*) (pArr)->pvData;
			POSITION pos = points.GetHeadPosition();
			for (int i = 0; i < elementNum / 2 && pos != NULL; i++)
			{
				CPoint p(pArrElements[2 * i], pArrElements[2 * i + 1]);
				points.GetNext(pos) = p;
			}
			SafeArrayUnlock(pArr);
		}
	}

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::SetPoints(SAFEARRAY* pArr)
{
	//one dim., long elements
	if ((pArr)->cDims == 1 && (pArr)->cbElements == 4)
	{
		points.RemoveAll();
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

	return S_OK;
}

// --- Data

STDMETHODIMP CAutoRouterPath::GetSurroundRect(long* p1, long* p2, long* p3, long* p4)
{
	CRect rect(INT_MAX,INT_MAX,INT_MIN,INT_MIN);

	POSITION pos = points.GetHeadPosition();
	while( pos != NULL )
	{
		CPoint point = points.GetNext(pos);

		rect.left = min(rect.left, point.x);
		rect.top = min(rect.top, point.y);
		rect.right = max(rect.right, point.x);
		rect.bottom = max(rect.bottom, point.y);
	}

	if( rect.left == INT_MAX || rect.top == INT_MAX ||
		rect.right == INT_MIN || rect.bottom == INT_MIN )
	{
		rect.SetRectEmpty();
	}

	*p1 = rect.left;
	*p2 = rect.top;
	*p3 = rect.right;
	*p4 = rect.bottom;

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::IsEmpty(VARIANT_BOOL* result)
{
	if (points.IsEmpty() == TRUE)
		*result = VARIANT_TRUE;
	else
		*result = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::IsPathAt(long px, long py, long nearness, VARIANT_BOOL* result)
{
	if (GetEdgePosAt(CPoint(px, py), nearness) != NULL)
		*result = VARIANT_TRUE;
	else
		*result = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::IsPathClip(long p1, long p2, long p3, long p4, VARIANT_BOOL* result)
{
	CPoint a;
	CPoint b;

	POSITION pos = points.GetTailEdge(a, b);
	while( pos != NULL )
	{
		if( IsLineClipRect(a, b, CRect(p1, p2, p3, p4)) )
		{
			*result = VARIANT_TRUE;
			return S_OK;
		}

		points.GetPrevEdge(pos, a, b);
	}

	*result = VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CAutoRouterPath::SetAttributes(long attr)
{
	attributes = attr;

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::GetAttributes(long* result)
{
	*result = attributes;

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::IsFixed(VARIANT_BOOL* result)
{
	if ((attributes & ARPATH_Fixed) != 0)
		*result = VARIANT_TRUE;
	else
		*result = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::IsMoveable(VARIANT_BOOL* result)
{
	if ((attributes & ARPATH_Fixed) == 0)
		*result = VARIANT_TRUE;
	else
		*result = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::IsHighLighted(VARIANT_BOOL* result)
{
	if ((attributes & ARPATH_HighLighted) != 0)
		*result = VARIANT_TRUE;
	else
		*result = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::GetState(long* result)
{
	*result = state;

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::IsConnected(VARIANT_BOOL* result)
{
	if (IsConnected())
		*result = VARIANT_TRUE;
	else
		*result = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::SetState(long s)
{
	ASSERT( owner != NULL );

	state = s;

#ifdef _DEBUG
	AssertValid();
#endif

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::GetEndDir(RoutingDirection* result)
{
	unsigned int a = attributes & ARPATH_EndMask;
	*result =	a & ARPATH_EndOnTop ? Dir_Top :
				a & ARPATH_EndOnRight ? Dir_Right :
				a & ARPATH_EndOnBottom ? Dir_Bottom :
				a & ARPATH_EndOnLeft ? Dir_Left : Dir_None;

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::GetStartDir(RoutingDirection* result)
{
	unsigned int a = attributes & ARPATH_StartMask;
	*result =	a & ARPATH_StartOnTop ? Dir_Top :
				a & ARPATH_StartOnRight ? Dir_Right :
				a & ARPATH_StartOnBottom ? Dir_Bottom :
				a & ARPATH_StartOnLeft ? Dir_Left : Dir_None;

	return S_OK;
}

// COM interface

STDMETHODIMP CAutoRouterPath::GetOwner(IAutoRouterGraph** result)
{
	return owner->QueryInterface(IID_IAutoRouterGraph,(void**)result);
}

STDMETHODIMP CAutoRouterPath::HasOwner(VARIANT_BOOL* result)
{
	if (owner != NULL)
		*result = VARIANT_TRUE;
	else
		*result = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::SetOwner(IAutoRouterGraph* graph)
{
	owner = graph;

	return S_OK;
}

// --- Ports

STDMETHODIMP CAutoRouterPath::SetStartPort(IAutoRouterPort* port)
{
	startport = port;

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::SetEndPort(IAutoRouterPort* port)
{
	endport = port;

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::ClearPorts()
{
	startport = NULL;
	endport = NULL;

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::GetStartPort(IAutoRouterPort** result)
{
	ASSERT( startport != NULL );

	return ::QueryInterface(startport, result);
}

STDMETHODIMP CAutoRouterPath::GetEndPort(IAutoRouterPort** result)
{
	ASSERT( endport != NULL );

	return ::QueryInterface(endport, result);
}

STDMETHODIMP CAutoRouterPath::GetPointList(SAFEARRAY **pArr)
{
	if (!pArr)
		return E_POINTER;

	ASSERT(*pArr == NULL);
	*pArr = SafeArrayCreateVector(VT_I4, 0, 2 * points.GetSize());

	HRESULT hr = S_OK;
	long position = 0;
	POSITION pos = points.GetHeadPosition();
	while(pos && SUCCEEDED(hr))
	{
		CPoint point = points.GetNext(pos);
		hr = SafeArrayPutElement(*pArr, &position, &point.x);
		ASSERT(SUCCEEDED(hr));
		position++;
		hr = SafeArrayPutElement(*pArr, &position, &point.y);
		ASSERT(SUCCEEDED(hr));
		position++;
	}
	
	return hr;

	//usage:
	//if ((*pArr)->cDims != 1 || (*pArr)->cbElements != 4)
}

STDMETHODIMP CAutoRouterPath::SetEndDir(long arpath_end)
{
	attributes = (attributes & ~ARPATH_EndMask) + (unsigned int)arpath_end;
	return S_OK;
}

STDMETHODIMP CAutoRouterPath::SetStartDir(long arpath_start)
{
	attributes = (attributes & ~ARPATH_StartMask) + (unsigned int)arpath_start;
	return S_OK;
}

STDMETHODIMP CAutoRouterPath::SetCustomPathData(SAFEARRAY* pArr)
{
	HRESULT hr = S_OK;

	if (!pArr)
		return E_POINTER;

	CustomPathData* pData;
	hr = SafeArrayAccessData(pArr, (void**)&pData);
	ASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
		return hr;

	customPathData.clear();
	for (unsigned long i = 0; i < pArr->rgsabound->cElements; i++)
	{
		CustomPathData pathData;
		CopyCustomPathData(pData[i], pathData);
		customPathData.push_back(pathData);
	}

	hr = SafeArrayUnaccessData(pArr);
	ASSERT(SUCCEEDED(hr));

	return hr;
}

STDMETHODIMP CAutoRouterPath::ApplyCustomizationsBeforeAutoConnectPoints(SAFEARRAY** pArr)
{
	if (customPathData.empty())
		return S_OK;

	CPointListPath ret;

	std::vector<CustomPathData>::iterator ii = customPathData.begin();
	while (ii != customPathData.end()) {
		if ((*ii).type == SimpleEdgeDisplacement) {
			// it is done in a next phase
		} else if ((*ii).type == CustomPointCustomization) {
			if (!isAutoRoutingOn)
				ret.AddTail(CPoint((*ii).x, (*ii).y));
		} else {
			// unknown displacement type
		}
		++ii;
	}

	if (ret.GetSize() > 0) {
		SafeArrayDestroy(*pArr);
		*pArr = SafeArrayCreateVector(VT_I4, 0, 2 * ret.GetSize());
		long position = 0;
		HRESULT hr = S_OK;
		POSITION pos = ret.GetHeadPosition();
		while(pos && SUCCEEDED(hr))
		{
			CPoint point = ret.GetNext(pos);
			hr = SafeArrayPutElement(*pArr, &position, &point.x);
			ASSERT(SUCCEEDED(hr));
			position++;
			hr = SafeArrayPutElement(*pArr, &position, &point.y);
			ASSERT(SUCCEEDED(hr));
			position++;
		}
	}

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::ApplyCustomizationsAfterAutoConnectPointsAndStuff(void)
{
	if (customPathData.empty())
		return S_OK;

	if (isAutoRoutingOn) {
		std::vector<CustomPathData>::iterator ii = customPathData.begin();
		int numEdges = points.GetSize() - 1;
		while (ii != customPathData.end()) {
			if ((*ii).edgeCount != numEdges &&
				(*ii).type == SimpleEdgeDisplacement)
			{
				pathDataToDelete.push_back(*ii);
				ii = customPathData.erase(ii);
			} else {
				++ii;
			}
		}
	}

	CPoint* startpoint = NULL;
	CPoint* endpoint = NULL;

	int currEdgeIndex = 0;
	POSITION pos = points.GetHeadEdgePtrs(startpoint, endpoint);
	while (pos != NULL) {
		std::vector<CustomPathData>::iterator ii = customPathData.begin();
		while (ii != customPathData.end()) {
			bool increment = true;
			if (currEdgeIndex == (*ii).edgeIndex) {
				if ((*ii).type == SimpleEdgeDisplacement) {
					RoutingDirection dir = GetDir(*endpoint - *startpoint);
					VARIANT_BOOL isHorizontalVar = (IsHorizontal(dir) != 0 ? VARIANT_TRUE : VARIANT_FALSE);
					if ((*ii).horizontalOrVerticalEdge == isHorizontalVar) {
						if ((*ii).horizontalOrVerticalEdge == VARIANT_TRUE) {
							startpoint->y = (*ii).y;
							endpoint->y = (*ii).y;
						} else {
							startpoint->x = (*ii).x;
							endpoint->x = (*ii).x;
						}
					} else {
						// something went wrong, invalid data: direction (horz/vert) not match
						ASSERT(false);
						pathDataToDelete.push_back(*ii);
						ii = customPathData.erase(ii);
						increment = false;
					}
				} else if ((*ii).type == CustomPointCustomization) {
					// it is done in a previous phase
				} else {
					// unknown displacement type
				}
			}
			if (increment)
				++ii;
		}

		points.GetNextEdgePtrs(pos, startpoint, endpoint);
		currEdgeIndex++;
	}

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::RemovePathCustomizations(void)
{
	std::vector<CustomPathData>::iterator ii = customPathData.begin();
	while (ii != customPathData.end()) {
		pathDataToDelete.push_back(*ii);
		++ii;
	}
	customPathData.clear();

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::MarkPathCustomizationsForDeletion(long asp)
{
	std::vector<CustomPathData>::iterator ii = customPathData.begin();
	while (ii != customPathData.end()) {
		if ((*ii).aspect == asp)
			pathDataToDelete.push_back(*ii);
		++ii;
	}

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::RemoveInvalidPathCustomizations(long asp)
{
	// We only inhibit/delete those edges, which has an edge count
	// (redundand data intended for this very sanity check)
	// doesn't equal to edge count
	std::vector<CustomPathData>::iterator ii = customPathData.begin();
	int numEdges = points.GetSize() - 1;
	while (ii != customPathData.end()) {
		if ((*ii).aspect == asp) {
			if ((*ii).edgeCount != numEdges &&
				(*ii).type == SimpleEdgeDisplacement)
			{
				ii = customPathData.erase(ii);
			} else {
				++ii;
			}
		} else {
			++ii;
		}
	}

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::AreTherePathCustomizations(VARIANT_BOOL* result)
{
	if (!customPathData.empty())
		*result = VARIANT_TRUE;
	else
		*result = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::AreThereDeletedPathCustomizations(VARIANT_BOOL* result)
{
	if (!pathDataToDelete.empty())
		*result = VARIANT_TRUE;
	else
		*result = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::GetDeletedCustomPathData(SAFEARRAY** pArr)
{
	HRESULT hr = S_OK;

	if (!pArr)
		return E_POINTER;

	//set bounds
	SAFEARRAYBOUND bound[1];
	bound[0].lLbound	= 0;
	bound[0].cElements	= pathDataToDelete.size();
	CustomPathData* pData;
	IRecordInfo* pRI;

	hr = GetRecordInfoFromGuids(LIBID_GmeLib, 1, 0, 0x409, __uuidof(CustomPathData), &pRI);
	ASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
		return hr;

	//create safearray
	*pArr = SafeArrayCreateEx(VT_RECORD, 1, bound, pRI);
	pRI->Release();
	pRI = NULL;

	//access safearray
	hr = SafeArrayAccessData(*pArr, (void**)&pData);
	ASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
		return hr;

	std::vector<CustomPathData>::iterator ii = pathDataToDelete.begin();
	long i = 0;
	while(ii != pathDataToDelete.end()) {
		CopyCustomPathData((*ii), pData[i]);
		i++;
		++ii;
	}

	//unaccess safearray
	hr = SafeArrayUnaccessData(*pArr);
	ASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
		return hr;
	
	return hr;
}

STDMETHODIMP CAutoRouterPath::GetCustomizedEdgeIndexes(SAFEARRAY** pArr)
{
	if (!pArr)
		return E_POINTER;

	ASSERT(*pArr == NULL);
	*pArr = SafeArrayCreateVector(VT_I4, 0, customPathData.size());

	HRESULT hr = S_OK;
	long position = 0;
	std::vector<CustomPathData>::iterator ii = customPathData.begin();
	while(ii != customPathData.end() && SUCCEEDED(hr))
	{
		long edgeIndex = (*ii).edgeIndex;
		hr = SafeArrayPutElement(*pArr, &position, &edgeIndex);
		ASSERT(SUCCEEDED(hr));
		position++;
		++ii;
	}

	return hr;

	//usage:
	//if ((*pArr)->cDims != 1 || (*pArr)->cbElements != 4)
}

STDMETHODIMP CAutoRouterPath::IsAutoRouted(VARIANT_BOOL* result)
{
	if (isAutoRoutingOn)
		*result = VARIANT_TRUE;
	else
		*result = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::SetAutoRouting(VARIANT_BOOL autoRoutingState)
{
	isAutoRoutingOn = (autoRoutingState == VARIANT_TRUE);

	return S_OK;
}

STDMETHODIMP CAutoRouterPath::Destroy()
{
	SetStartPort(NULL);
	SetEndPort(NULL);

	return S_OK;
}

// --- Debug

#ifdef _DEBUG

void CAutoRouterPath::AssertValid()
{
	if( startport != NULL )
		static_cast<CAutoRouterPort*> (startport.p)->AssertValid();

	if( endport != NULL )
		static_cast<CAutoRouterPort*> (endport.p)->AssertValid();

	if( IsConnected() )
		ASSERT( !points.IsEmpty() );
	else
		ASSERT( points.IsEmpty() );
}

void CAutoRouterPath::AssertValidPos(POSITION pos) const
{
	points.AssertValidPos(pos);
}

#pragma warning( disable : 4701 )

void CAutoRouterPath::AssertValidPoints() const
{
	points.AssertValid();

	if( points.IsEmpty() )
		return;

#ifdef _DEBUG_DEEP
	TRACE("CAutoRouterPath::AssertValidPoints (count=%ld) START\n", points.GetCount());
#endif

	POSITION pos = points.GetHeadPosition();
	ASSERT( points.GetCount() >= 2 && pos != NULL );

	POSITION p1p = NULL;
	POSITION p2p = NULL;
	POSITION p3p;

	CPoint p1;
	CPoint p2;

	RoutingDirection d12;
	RoutingDirection d23;
	d23 = d12 = Dir_None;// init by zolmol

	while( pos != NULL )
	{
		p3p = p2p;
		p2p = p1p;
		p1p = pos;

		p2 = p1;
		p1 = points.GetNext(pos);

#ifdef _DEBUG_DEEP
		TRACE("%p (%ld,%ld)\n", p1p, p1.x, p1.y);
#endif
		d23 = d12;
		if( p2p != NULL )
		{
			d12 = GetDir(p2 - p1);
			ASSERT( d12 == Dir_Skew || IsRightAngle(d12) );
		}

		if( p3p != NULL && d12 != Dir_Skew && d23 != Dir_Skew )
			ASSERT( AreInRightAngle(d12, d23) );
	}

#ifdef _DEBUG_DEEP
	TRACE("CAutoRouterPath::AssertValidPoints END\n");
#endif

}

#endif

// CAutoRouterPath
