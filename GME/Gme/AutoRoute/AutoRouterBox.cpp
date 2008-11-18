// AutoRouterBox.cpp : Implementation of CAutoRouterBox

#include "stdafx.h"
#include "AutoRouterBox.h"
#include "AutoRouterPort.h"
#include "AutoRouterGraph.h"


CAutoRouterBox::CAutoRouterBox():	owner(NULL),
									rect(0,0,0,0),
									atomic(0)
{	
	CalculateSelfPoints();
}

void CAutoRouterBox::DeleteAllPorts()
{
	for (CAutoRouterPortList::size_type i = 0; i<ports.size(); i++)
	{
		ports[i]->SetOwner(NULL);
	}

	ports.clear();

	atomic = 0;
}

void CAutoRouterBox::ShiftBy(CSize offset)
{
	rect += offset;

	for(CAutoRouterPortList::size_type i=0; i<ports.size();i++)
	{
		ports[i]->ShiftBy(offset);
	}

	CalculateSelfPoints();
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


void CAutoRouterBox::SetOwner(CComObjPtr<CAutoRouterGraph> o)
{
	owner = o;
}

STDMETHODIMP CAutoRouterBox::CreatePort(IAutoRouterPort** result)
{
	CComObjPtr<CAutoRouterPort> port;
	
	CreateComObject(port);

	return ::QueryInterface(port,result);
}
STDMETHODIMP CAutoRouterBox::Add(IAutoRouterPort* port)
{
	CComObjPtr<CAutoRouterPort> p = static_cast<CAutoRouterPort*>(port);

	p->SetOwner(this);

	ports.push_back(p);

	return S_OK;
}
STDMETHODIMP CAutoRouterBox::Delete(IAutoRouterPort* port)
{
	vector<CComObjPtr<CAutoRouterPort> >::iterator iter = std::find(ports.begin(), ports.end(), port);

	if (iter == ports.end())
	{
		//error
		return S_FALSE;
	}

	(*iter)->SetOwner(NULL);

	ports.erase(iter);
	atomic=0;
	
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

STDMETHODIMP CAutoRouterBox::GetOwner(IAutoRouterGraph** result)
{
	return owner->QueryInterface(IID_IAutoRouterGraph,(void**)result);
}

STDMETHODIMP CAutoRouterBox::SetRect(long p1, long p2, long p3, long p4)
{
	CRect r(p1,p2,p3,p4);

	ASSERT( r.Width() >= 3 && r.Height() >= 3 );
	ASSERT( r.TopLeft().x >= ED_MINCOORD && r.TopLeft().y >= ED_MINCOORD );
	ASSERT( r.BottomRight().x <= ED_MAXCOORD && r.BottomRight().y <= ED_MAXCOORD );
	ASSERT( HasNoPort() || atomic );

	rect = r;
	CalculateSelfPoints();

	if( atomic )
	{
		ASSERT( ports.size() == 1 );
		(static_cast<CAutoRouterPort*>(ports[0].p))->SetRect(r.left, r.top, r.right, r.bottom);
	}

	return S_OK;
}

// CAutoRouterBox

