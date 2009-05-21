// AutoRouterBox.cpp : Implementation of CAutoRouterBox

#include "stdafx.h"
#include "AutoRouterBox.h"
#include "AutoRouterPort.h"
#include "AutoRouterGraph.h"


CAutoRouterBox::CAutoRouterBox():
	owner(NULL),
	rect(0, 0, 0, 0),
	atomic(0)
{
	CalculateSelfPoints();
}

HRESULT CAutoRouterBox::FinalConstruct(void)
{
	return S_OK;
}

void CAutoRouterBox::FinalRelease(void)
{
}

void CAutoRouterBox::CalculateSelfPoints()
{
	selfpoints[0].x = rect.left;
	selfpoints[0].y = rect.top;

	selfpoints[1].x = rect.right - 1;
	selfpoints[1].y = rect.top;

	selfpoints[2].x = rect.right - 1;
	selfpoints[2].y = rect.bottom - 1;

	selfpoints[3].x = rect.left;
	selfpoints[3].y = rect.bottom - 1;
}

void CAutoRouterBox::DeleteAllPorts()
{
	for (CAutoRouterPortList::size_type i = 0; i < ports.size(); i++)
	{
		ports[i]->SetOwner(NULL);
	}

	ports.clear();

	atomic = 0;
}

STDMETHODIMP CAutoRouterBox::GetOwner(IAutoRouterGraph** result)
{
	return owner->QueryInterface(IID_IAutoRouterGraph,(void**)result);
}

STDMETHODIMP CAutoRouterBox::HasOwner(VARIANT_BOOL* result)
{
	if (result == NULL)
		return E_POINTER;

	if (owner != NULL)
		*result = VARIANT_TRUE;
	else
		*result = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAutoRouterBox::SetOwner(IAutoRouterGraph* graph)
{
	owner = graph;

	return S_OK;
}

STDMETHODIMP CAutoRouterBox::CreatePort(IAutoRouterPort** result)
{
	if (result == NULL)
		return E_POINTER;

	CComObjPtr<CAutoRouterPort> port;
	CreateComObject(port);

	return ::QueryInterface(port, result);
}

STDMETHODIMP CAutoRouterBox::HasNoPort(VARIANT_BOOL* result)
{
	if (result == NULL)
		return E_POINTER;

	if (ports.size() == 0)
		*result = VARIANT_TRUE;
	else
		*result = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAutoRouterBox::GetPortCount(long* result)
{
	if (result == NULL)
		return E_POINTER;

	*result = ports.size();

	return S_OK;
}

STDMETHODIMP CAutoRouterBox::IsAtomic(VARIANT_BOOL* result)
{
	if (result == NULL)
		return E_POINTER;

	if (atomic)
		*result = VARIANT_TRUE;
	else
		*result = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAutoRouterBox::AddPort(IAutoRouterPort* port)
{
	if (port == NULL)
		return E_POINTER;

	CComPtr<IAutoRouterPort> p = port;

	p->SetOwner(this);

	ports.push_back(p);

#ifdef _DEBUG
	AssertValidPort(p);
#endif

	return S_OK;
}

STDMETHODIMP CAutoRouterBox::DeletePort(IAutoRouterPort* port)
{
	ASSERT( port != NULL );
	if (port == NULL)
		return E_POINTER;

#ifdef _DEBUG
	CComPtr<IAutoRouterBox> ownerBox;
	HRESULT hr = port->GetOwner(&ownerBox);
	ASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
		return hr;
	ASSERT( ownerBox.p == this );

	AssertValidPort(static_cast<CAutoRouterPort*>(port));

	if( atomic )
		ASSERT( ports.size() == 1 );
#endif

	std::vector<CComPtr<IAutoRouterPort> >::iterator iter = std::find(ports.begin(), ports.end(), port);

	if (iter == ports.end())
	{
		//error
		return S_FALSE;
	}

	(*iter)->SetOwner(NULL);

	ports.erase(iter);
	atomic = 0;
	
	return S_OK;
}

STDMETHODIMP CAutoRouterBox::GetPortList(SAFEARRAY** pArr)
{
	if (pArr == NULL)
		return E_POINTER;

	//create safearray
	ASSERT(*pArr == NULL);
	*pArr = SafeArrayCreateVector(VT_UNKNOWN, 0, ports.size());

	HRESULT hr = S_OK;
	for(long i = 0; i < (long)ports.size() && SUCCEEDED(hr); i++)
	{
		CComPtr<IAutoRouterPort> pUnk = ports[i];
		hr = SafeArrayPutElement(*pArr, &i, pUnk);
	}

	return hr;

	//usage:
	//if ((*pArr)->cDims != 1 || (*pArr)->cbElements != 8)
}

STDMETHODIMP CAutoRouterBox::GetRect(long* p1, long* p2, long* p3, long* p4)
{
	if (p1 == NULL || p2 == NULL || p3 == NULL || p4 == NULL)
		return E_POINTER;

	*p1 = rect.left;
	*p2 = rect.top;
	*p3 = rect.right;
	*p4 = rect.bottom;

	return S_OK;
}

STDMETHODIMP CAutoRouterBox::IsRectEmpty(VARIANT_BOOL* result)
{
	if (result == NULL)
		return E_POINTER;

	if (rect.IsRectEmpty())
		*result = VARIANT_TRUE;
	else
		*result = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAutoRouterBox::SetRect(long p1, long p2, long p3, long p4)
{
	CRect r(p1, p2, p3, p4);

	ASSERT( r.Width() >= 3 && r.Height() >= 3 );
	ASSERT( r.TopLeft().x >= ED_MINCOORD && r.TopLeft().y >= ED_MINCOORD );
	ASSERT( r.BottomRight().x <= ED_MAXCOORD && r.BottomRight().y <= ED_MAXCOORD );
	ASSERT( ports.size() == 0 || atomic );

	rect = r;
	CalculateSelfPoints();

	if( atomic )
	{
		ASSERT( ports.size() == 1 );
		ports[0]->SetRect(r.left, r.top, r.right, r.bottom);
	}

	return S_OK;
}

STDMETHODIMP CAutoRouterBox::SetRectByPoint(long px, long py)
{
	const CPoint& point = (CPoint(px, py) - rect.TopLeft());
	ShiftBy(point.x, point.y);

	return S_OK;
}

STDMETHODIMP CAutoRouterBox::ShiftBy(long offsetx, long offsety)
{
	const CPoint offset(offsetx, offsety);
	rect += offset;

	HRESULT hr;
	for(CAutoRouterPortList::size_type i = 0; i < ports.size(); i++)
	{
		hr = ports[i]->ShiftBy(offsetx, offsety);
		ASSERT(SUCCEEDED(hr));
		if (FAILED(hr))
			return hr;
	}

	CalculateSelfPoints();

	return S_OK;
}

STDMETHODIMP CAutoRouterBox::GetSelfPoints(long* p1x, long* p1y, long* p2x, long* p2y, long* p3x, long* p3y, long* p4x, long* p4y)
{
	if (p1x == NULL || p1y == NULL || p2x == NULL || p2y == NULL || p3x == NULL || p3y == NULL || p4x == NULL || p4y == NULL)
		return E_POINTER;

	*p1x = selfpoints[0].x;
	*p1y = selfpoints[0].y;
	*p2x = selfpoints[1].x;
	*p2y = selfpoints[1].y;
	*p3x = selfpoints[2].x;
	*p3y = selfpoints[2].y;
	*p4x = selfpoints[3].x;
	*p4y = selfpoints[3].y;

	return S_OK;
}

STDMETHODIMP CAutoRouterBox::IsBoxAt(long px, long py, long nearness, VARIANT_BOOL* result)
{
	if (result == NULL)
		return E_POINTER;

	const CPoint point(px, py);
	if (IsPointIn(point, rect, nearness))
		*result = VARIANT_TRUE;
	else
		*result = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAutoRouterBox::IsBoxClip(long p1, long p2, long p3, long p4, VARIANT_BOOL* result)
{
	if (result == NULL)
		return E_POINTER;

	const CRect r(p1, p2, p3, p4);
	if (IsRectClip(rect, r))
		*result = VARIANT_TRUE;
	else
		*result = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAutoRouterBox::IsBoxIn(long p1, long p2, long p3, long p4, VARIANT_BOOL* result)
{
	if (result == NULL)
		return E_POINTER;

	const CRect r(p1, p2, p3, p4);
	if (IsRectIn(rect, r))
		*result = VARIANT_TRUE;
	else
		*result = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAutoRouterBox::Destroy()
{
	//ideally it could be placed in the finaldestruct(), 
	//but the deleted ports hold references to this box, 
	//so the finaldestruct() is not called until the ports are deleted
	
	this->SetOwner(NULL);
	DeleteAllPorts();

	this->AddRef();
	this->Release();

	return S_OK;
}

// --- Debug

#ifdef _DEBUG

void CAutoRouterBox::AssertValid() const
{
	for (CAutoRouterPortList::size_type i = 0; i < ports.size(); i++)
	{
		AssertValidPort(ports[i]);
	}
}

void CAutoRouterBox::AssertValidPort(CComPtr<IAutoRouterPort> port) const
{
	static_cast<CAutoRouterPort*>(port.p)->AssertValid();

	if( owner != NULL ) {
		CComPtr<IAutoRouterBox> ownerBox;
		COMTHROW(port->GetOwner(&ownerBox));
		ASSERT( ownerBox.p == this );
	}

	long p1, p2, p3, p4;
	COMTHROW(port->GetRect(&p1, &p2, &p3, &p4));
	ASSERT( IsRectIn(CRect(p1, p2, p3, p4), rect) );
}

#endif

// CAutoRouterBox

