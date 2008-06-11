//*****************************************************************************
// rephelp.h
//
// This file contains functions which make setting and retrieving 
// Repository object properties easier for the C++ developer using the
// Microsoft Active Template Library.
//
// Copyright (c) 1998 by Microsoft Corporation, All Rights Reserved
// 
// This software is provided as is without warranty of any kind.  The entire
// risk as to the results and performance of this software is assumed by the user.
// Microsoft disclaims all warranties, either express or implied, including but
// not limited, the implied warranties of merchantability, fitness for a
// particular purpose, title and noninfringement, with respect to this software.
//
//*****************************************************************************

#ifndef __REPHELP_H__
#define __REPHELP_H__



#include <atlbase.h>
#include <windows.h>
//#import  <C:\Program Files\Common Files\Microsoft Shared\Repostry\repodbc.dll> // Should change the path if repository is installed to some other path
#include "repapi.h"
#include "reptim2.h"
#include "repauto.h"
//*****************************************************************************
// This method sets the specified lDispID property on pIDisp property interface.
//*****************************************************************************
inline HRESULT put_RepProp(					// Return status.
	IDispatch	*pIDisp,				// Interface to set property on.
	DISPID		lDispID,				// DISPID of the property being set.
	CComVariant	vValue)					// Value of the property being set.
{
	DISPID		lDispPut=DISPID_PROPERTYPUT;
	DISPPARAMS	sDispParams;			// Tmp. buffer for dispatch parameters.
	EXCEPINFO	sExInfo;				// Tmp. buffer for exception information.

	// Initialize sDispParams.
	sDispParams.cArgs = 1;
	sDispParams.cNamedArgs = 1;
	sDispParams.rgdispidNamedArgs = &lDispPut;
	sDispParams.rgvarg = &vValue;
	lDispPut = DISPID_PROPERTYPUT;
	
	return (pIDisp->Invoke(lDispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, 
		DISPATCH_PROPERTYPUT, &sDispParams, NULL, &sExInfo, NULL));
}

//*****************************************************************************
// This method retrieves the specified lDispID property on pIDisp property interface.
//*****************************************************************************
inline HRESULT get_RepProp(
	IDispatch	*pIDisp,				// Interface to retrieve property from.
	DISPID		lDispID,				// DISPID of the property being retrieved.
	CComVariant	*pvValue)				// Return buffer for property.
{
	DISPPARAMS	sDispParams;			// Tmp. buffer for dispatch parameters.
	EXCEPINFO	sExInfo;				// Tmp. buffer for exception information.
	HRESULT		hr=S_OK;

	// Initialize sDispParams.
	sDispParams.cArgs = 0;
	sDispParams.cNamedArgs = 0;
	sDispParams.rgdispidNamedArgs = 0;
	sDispParams.rgvarg = NULL;
	
	// Now, make the 'Invoke' call.
	return (pIDisp->Invoke(lDispID, IID_NULL, LOCALE_SYSTEM_DEFAULT,
		DISPATCH_PROPERTYGET, &sDispParams, pvValue, &sExInfo, NULL));
	
	return hr;
}

//*****************************************************************************
// This method retrieves the relationship collection specified by lDispID from
// pIDisp interface.
//*****************************************************************************
inline HRESULT get_RepRelshipCol(				// Return status.
	IDispatch	*pIDisp,				// Interface to fetch collection from.
	DISPID		lDispID,				// DISPID of the collection being retrieved.
	IRelationshipCol	**pIRelCol)		// Return buffer for relationship collection.
{
	CComVariant	vRepProp;				// Tmp. buffer to store retrieved collection.
	HRESULT		hr=S_OK;

	// Fetch the collection.
	if (FAILED(hr = get_RepProp(pIDisp, lDispID, &vRepProp)))
		return (hr);

	// Return IRelationshipCol interface of the returned Dispatch interface.
	if (vRepProp.vt != VT_DISPATCH)
		return (E_FAIL);

	return (vRepProp.pdispVal->QueryInterface(IID_IRelationshipCol, (void **) pIRelCol));
}

inline HRESULT get_RepRelshipCol(					// Return status.
	IRepositoryObject *pISrc,			// Object whose collection to get.
	IID			sIfaceIID,				// Interface where the collection is defined.
	DISPID		sDispID,				// DispID of the collection.
	IRelationshipCol **pIRelshipCol)	// The Collection
{
	CIfacePtr<IDispatch> pIRD;
	CComVariant	sRepVar;
	HRESULT		hr;

	if (FAILED(hr = pISrc->QueryInterface(sIfaceIID, (PVOID *) &pIRD))) 
		return (hr);
	if (FAILED(hr = get_RepRelshipCol(pIRD, sDispID, pIRelshipCol))) 
		return (hr);

	return (S_OK);
}

//*****************************************************************************
// This method retrieves the target object collection specified by lDispID from
// pIDisp interface.
//*****************************************************************************
inline HRESULT get_RepTargetObjCol(			// Return status.
	IDispatch	*pIDisp,				// Interface to fetch collection from.
	DISPID		lDispID,				// DISPDI of the collection being retrieved.
	ITargetObjectCol	**pITargetObjCol)// Return buffer for target object collection.
{
	CComVariant	vRepProp;				// Tmp. buffer to store retrieved collection.
	HRESULT		hr=S_OK;

	// Fetch the collection.
	if (FAILED(hr = get_RepProp(pIDisp, lDispID, &vRepProp)))
		return (hr);

	// Return IRelationshipCol interface of the returned Dispatch interface.
	if (vRepProp.vt != VT_DISPATCH)
		return (E_FAIL);

	return (vRepProp.pdispVal->QueryInterface(IID_ITargetObjectCol, (void **) pITargetObjCol));
}

inline HRESULT get_RepTargetObjCol(			// Return status.
	IRepositoryObject *pISrc,			// Object whose collection to get.
	IID			sIfaceIID,				// Interface where the collection is defined.
	DISPID		sDispID,				// DispID of the collection.
	ITargetObjectCol **pITgtObjCol)	// The Collection
{
	CIfacePtr<IDispatch> pIRD;
	CComVariant	sRepVar;
	HRESULT		hr;

	if (FAILED(hr = pISrc->QueryInterface(sIfaceIID, (PVOID *) &pIRD))) 
		return (hr);
	if (FAILED(hr = get_RepTargetObjCol(pIRD, sDispID, pITgtObjCol))) 
		return (hr);

	return (S_OK);
}


//*****************************************************************************
// This method retrieves the repository object corresponding to pIReposObj's
// type.
//*****************************************************************************
inline HRESULT get_RepMetaObject(				// Return status.
	IRepositoryObject	*pIReposObj,	// Repository object of interest.
	IRepositoryObject	**pIMetaObj)	// Return buffer for type 
{
	CComVariant		sType;				// Tmp. VARIANT to pIReposObj's type.
	CComPtr<IRepository>	pRepos;		// Tmp. repository pointer.
	HRESULT			hr=S_OK;
	
	// Fetch pIReposObj's repository.
	if (FAILED(hr = pIReposObj->get_Repository(&pRepos)))
		return (hr);

	// Fetch the object ID of the meta-object using the 'Type' property of 
	// IRepositoryObject interface.
	if (FAILED(hr = pIReposObj->get_Type(&sType)))
		return (hr);

	// Retrieve the repository object corresponding to sType.
	return (pRepos->get_Object(sType, pIMetaObj));
}


#endif	// __REPHELP_H__
