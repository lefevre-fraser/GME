// MgaObjectProxy.cpp: implementation of the CMgaObjectProxy class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gmeactivebrowser.h"
#include "MgaObjectProxy.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMgaObjectProxy::CMgaObjectProxy(LPUNKNOWN pMgaObject, objtype_enum type) 
{
	m_pMgaObject=pMgaObject;
	m_TypeInfo=type;

}

CMgaObjectProxy::CMgaObjectProxy(CMgaObjectProxy& rSourceObjectProxy)
{
	*this=rSourceObjectProxy;
}

CMgaObjectProxy::~CMgaObjectProxy()
{

}

void CMgaObjectProxy::operator =(CMgaObjectProxy &rSourceObjectProxy)
{
	m_pMgaObject=rSourceObjectProxy.m_pMgaObject;
	m_TypeInfo=rSourceObjectProxy.m_TypeInfo;

}
