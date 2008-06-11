// Property.cpp: implementation of the CProperty class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "objectinspector.h"
#include "ObjectInspectorCtl.h"

#include "Property.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/************** Properties to display *************

  * General Properties (All)
	- Type
	- Kind
	- Meta ID
	- Object ID
	- Rel ID
	- GUID

  * FCO Properties
	- Role
	- Aspect

  * M(odel)A(tom)R(eference)S(et) Properties
	- Depends
	- Refers

  * Folder
	- Library Reference

  * Connection
	- Source
	- Source Port
	- Destination
	- Destination Port

***************************************************/



CProperty::CProperty()
{

}

CProperty::~CProperty()
{

}

void CProperty::CreateGeneralList(const CMgaFCOPtrList& MgaFCOPtrList,const CMgaFolderPtrList& MgaFolderPtrList,CArray<CListItem,CListItem&> &ListItemArray)
{

	// Adding "General Properties" container
	CListItem GeneralListItem;
	GeneralListItem.bIsReadOnly=true;
	GeneralListItem.bIsContainer=true;
	GeneralListItem.strName="General Properties";

	ListItemArray.Add(GeneralListItem);


	m_bIsAllFCO=MgaFolderPtrList.IsEmpty()!=FALSE;
	m_bIsAllFolder=MgaFCOPtrList.IsEmpty()!=FALSE;
	m_bIsAllConnection=m_bIsAllFCO;
	m_bIsAllMARS=true;

	bool bIsMultiple=((MgaFCOPtrList.GetCount()+MgaFolderPtrList.GetCount())>1?true:false);
	
	CString strType;
	CString strKindName;
	CString strMetaID;
	CString strObjectID;
	CString strRelID;
	CString strGUID;

	bool bIsTypeDirty=false;
	bool bIsKindNameDirty=false;
	bool bIsFirst=true;


	CString strTemp;

	// Iterating through the FCO list
	POSITION posFCO=MgaFCOPtrList.GetHeadPosition();

	while(posFCO)
	{
		CComPtr<IMgaFCO> ccpMgaFCO=MgaFCOPtrList.GetNext(posFCO);
				
		CComPtr<IMgaObject> ccpMgaObject;
		ccpMgaFCO.QueryInterface(&ccpMgaObject);

		GetGeneralProperties(ccpMgaObject,strType,strKindName,strMetaID,strObjectID,
							 strRelID,strGUID, bIsTypeDirty, bIsKindNameDirty,bIsMultiple,
							 bIsFirst);

		bIsFirst=false;
	}

	POSITION posFolder= MgaFolderPtrList.GetHeadPosition();

	while(posFolder)
	{
		CComPtr<IMgaFolder> ccpMgaFolder= MgaFolderPtrList.GetNext(posFolder);
		CComPtr<IMgaObject> ccpMgaObject;

		ccpMgaFolder.QueryInterface(&ccpMgaObject);

		GetGeneralProperties(ccpMgaObject,strType,strKindName,strMetaID,strObjectID,
							 strRelID,strGUID, bIsTypeDirty, bIsKindNameDirty,bIsMultiple,
							 bIsFirst);

		bIsFirst=false;
	}


	CListItem ListItem;
	ListItem.bIsReadOnly=true;
	ListItem.bIsDefault=false;

	// Type
	ListItem.bIsDifferentValue=bIsTypeDirty;
	ListItem.strName="Type";
	ListItem.strToolTip="Type of the object.";
	ListItem.Value.SetStringValue(strType);

	ListItemArray.Add(ListItem);
	
	// Kind
	ListItem.bIsDifferentValue=bIsKindNameDirty;
	ListItem.strName="Kind";
	ListItem.strToolTip="Kind of the object.";
	ListItem.Value.SetStringValue(strKindName);

	ListItemArray.Add(ListItem);

	// IDs do not make sense in multiple selection
	if(!bIsMultiple)
	{
		ListItem.bIsDifferentValue=false;
		ListItem.strName="Object ID";
		ListItem.strToolTip="Unique ID of the object.";
		ListItem.Value.SetStringValue(strObjectID);

		ListItemArray.Add(ListItem);

		ListItem.bIsDifferentValue=false;
		ListItem.strName="Relative ID";
		ListItem.strToolTip="Relative ID of the object, corresponds with creation order. The object with greater relative ID was created later.";
		ListItem.Value.SetStringValue(strRelID);

		ListItemArray.Add(ListItem);

		ListItem.bIsDifferentValue=false;
		ListItem.strName="Meta ID";
		ListItem.strToolTip="Meta ID of the object.";
		ListItem.Value.SetStringValue(strMetaID);

		ListItemArray.Add(ListItem);


		ListItem.bIsDifferentValue=false;
		ListItem.strName="GUID";
		ListItem.strToolTip="Universally unique ID of the object.";
		ListItem.Value.SetStringValue(strGUID);

		ListItemArray.Add(ListItem);
	}
}



void CProperty::GetGeneralProperties(const CComPtr<IMgaObject>& ccpMgaObject,
									 CString &strType, CString &strKindName,
									 CString &strMetaID, CString &strObjectID, 
									 CString &strRelID, CString &strGUID, bool &bIsTypeDirty,
									 bool &bIsKindNameDirty, bool bIsMultiple, 
									 bool bIsFirst)
{
		
		static CString strTypeNameArray[] = { "Invalid", "Model", "Atom", "Reference", "Connection", "Set", "Folder" };
		CString strTemp;
		objtype_enum oeObjType;
		COMTHROW(ccpMgaObject->get_ObjType(&oeObjType));
		
		if(oeObjType==OBJTYPE_CONNECTION)
		{
			m_bIsAllMARS=false;
		}
		else
		{
			m_bIsAllConnection=false;
		}

		
		//////////// Type /////////////////////////////////////////////
		if ( (oeObjType == OBJTYPE_ATOM) || 
			 (oeObjType == OBJTYPE_MODEL) || 
			 (oeObjType == OBJTYPE_REFERENCE) ||  
			 (oeObjType == OBJTYPE_SET) )
		{
			CComPtr<IMgaFCO> ccpFCOType;
			CComQIPtr<IMgaFCO> ccpMgaFCO(ccpMgaObject);
			
			// A model should be able to be converted to FCO
			ASSERT(ccpMgaFCO);
			
			COMTHROW(ccpMgaFCO->get_DerivedFrom(&ccpFCOType));
			
			if(ccpFCOType != 0) // Instance or Subtype
			{
				// Get base name
				CComBSTR bstrBaseName;
				COMTHROW(ccpFCOType->get_Name(&bstrBaseName));
				CString baseName(bstrBaseName);
				
				VARIANT_BOOL vtbIsInstance;
				COMTHROW(ccpMgaFCO->get_IsInstance(&vtbIsInstance));

				// If it is an instance
				if(vtbIsInstance != VARIANT_FALSE) 
				{
					strTemp.Format("%s (instance of %s)",strTypeNameArray[oeObjType],baseName);
				}
				else
				{
					strTemp.Format("%s (subtype of %s)",strTypeNameArray[oeObjType],baseName);
				}
			}
			else // Archetype
			{
				strTemp.Format("%s (Archetype)",strTypeNameArray[oeObjType]);
			}
		}
		else
		{
			strTemp=strTypeNameArray[oeObjType];
		}

		if(bIsFirst)
		{
			strType=strTemp;
		}
		else
		{
			if(strTemp!=strType)
			{
				bIsTypeDirty=true;
			}
		}
	
		///////////////// Kind ////////////////////////////////////
		
		// Getting kind
		strTemp = "N/A";

		// Get Meta
		CComPtr<IMgaMetaBase> ccpMetaBase;
		COMTHROW(ccpMgaObject->get_MetaBase(&ccpMetaBase));

		CComBSTR bstrMetaName;
		COMTHROW(ccpMetaBase->get_DisplayedName(&bstrMetaName));
		strTemp=bstrMetaName;

		if(bIsFirst)
		{
			strKindName=strTemp;
		}
		else
		{
			if(strTemp!=strKindName)
			{
				bIsKindNameDirty=true;
			}
		}

		// IDs do not make sense in multiple selection
		if(!bIsMultiple)
		{

			// Querying ObjectID
			CComBSTR bstrObjectID;
		 	COMTHROW(ccpMgaObject->get_ID(&bstrObjectID));
  			strObjectID.Format("%s",CString(bstrObjectID));

			// Getting RelID (this carries the creation order of an MgaObject)
			long lRelID;
			COMTHROW(ccpMgaObject->get_RelID(&lRelID));
			strRelID.Format("0x%08X",lRelID);
		
	
			// Get Meta ID
			metaref_type mtMetaID = 0;
			COMTHROW(ccpMetaBase->get_MetaRef(&mtMetaID));
			strMetaID.Format("%ld",(long)mtMetaID);

			// Get GUID
			CComBSTR bstrGUID;
		 	COMTHROW(ccpMgaObject->GetGuidDisp(&bstrGUID));
  			strGUID = CString( bstrGUID);
		}
}		



void CProperty::CreateFCOList(const CMgaFCOPtrList& MgaFCOPtrList,CArray<CListItem,CListItem&> &ListItemArray)
{

	// Adding "FCO Properties" container
	CListItem FCOListItem;
	FCOListItem.bIsContainer=true;
	FCOListItem.bIsReadOnly=true;
	FCOListItem.strName="FCO Properties";

	ListItemArray.Add(FCOListItem);

	CString strRole;
	CString strAspect;
	CString strTemp;
		
	bool bIsRoleDirty=false;
	bool bIsAspectDirty=false;

	bool bIsFirst=true;

	POSITION posFCO=MgaFCOPtrList.GetHeadPosition();

	while(posFCO)
	{
		CComPtr<IMgaFCO> ccpMgaFCO=MgaFCOPtrList.GetNext(posFCO);

			
		// Get role
		CComPtr<IMgaMetaRole> ccpMetaRole;
		COMTHROW(ccpMgaFCO->get_MetaRole(&ccpMetaRole));
		
		strTemp = "N/A";
		if(ccpMetaRole != 0) 
		{
			CComBSTR bstrRoleName;
			COMTHROW(ccpMetaRole->get_DisplayedName(&bstrRoleName));
			strTemp=bstrRoleName;
		}
		
		if(bIsFirst)
		{
			strRole=strTemp;
		}
		else
		{
			if(strRole!=strTemp)
			{
				bIsRoleDirty=true;
			}
		}
		
		/////////////////////////////// Aspects: ////////////////////////////////////
		// Multiple aspects are possible and one may be primary

		bool bFirst = true;

		objtype_enum oeParentObjType;

		CComPtr<IMgaObject> ccpParentObject;
		COMTHROW( ccpMgaFCO->GetParent(&ccpParentObject, &oeParentObjType) ); 


		CComPtr<IMgaParts> ccpMgaParts;

		if(oeParentObjType != OBJTYPE_FOLDER) 
		{

			COMTHROW(ccpMgaFCO->get_Parts(&ccpMgaParts));
		}

		CComPtr<IMgaPart> ccpCurrPart;

		if(ccpMgaParts != NULL) 
		{
			// Iterate through contained aspects
			MGACOLL_ITERATE(IMgaPart,ccpMgaParts) 
			{

				ccpCurrPart= MGACOLL_ITER;

				ASSERT(ccpCurrPart != NULL);

				// Get MetaAspect
				CComPtr<IMgaMetaAspect> ccpMetaAspect;
				COMTHROW( ccpCurrPart->get_MetaAspect(&ccpMetaAspect) );

				// Get Meta Aspect name
				CComBSTR bstrAspectName;					
				COMTHROW( ccpMetaAspect->get_Name(&bstrAspectName));

				if (!bFirst) 
				{
					strTemp += "; "; 
				} 
				else 
				{
					strTemp.Empty();
					bFirst = false; 
				}

				strTemp += CString(bstrAspectName);

	//!!! Arpad's comment: Simplify here when IMgaPart::get_AccessMask() is available 

				CComPtr<IMgaMetaPart> ccpMetaPart;
				COMTHROW( ccpCurrPart->get_Meta(&ccpMetaPart));

				ASSERT( ccpMetaPart != NULL );

				// Checking if aspect is primary
				VARIANT_BOOL vbtIsPrimary = VARIANT_FALSE;

				COMTHROW( ccpMetaPart->get_IsPrimary(&vbtIsPrimary) );

				if (vbtIsPrimary != VARIANT_FALSE) 
				{
					strTemp += " (Primary)";
				}
			}
			MGACOLL_ITERATE_END;
		}

		// Setting dirty
		if(bIsFirst)
		{
			strAspect=strTemp;
		}
		else
		{
			if(strAspect!=strTemp)
			{
				bIsAspectDirty=true;
			}
		}

		bIsFirst=false;
	}



	CListItem ListItem;
	ListItem.bIsReadOnly=true;

	// Role
	ListItem.bIsDifferentValue=bIsRoleDirty;
	ListItem.strName="Role";
	ListItem.strToolTip="Role name of the FCO.";
	ListItem.Value.SetStringValue(strRole);

	ListItemArray.Add(ListItem);

	// Aspect
	ListItem.bIsDifferentValue=bIsAspectDirty;
	ListItem.strName="Aspect";
	ListItem.strToolTip="Aspects which this FCO contains.";
	ListItem.Value.SetStringValue(strAspect);

	ListItemArray.Add(ListItem);


}


void CProperty::CreateMarsList(const CMgaFCOPtrList& MgaFCOPtrList,CArray<CListItem,CListItem&> &ListItemArray)
{

	// Adding "MARS Properties" container
	CListItem MarsListItem;
	MarsListItem.bIsContainer=true;
	MarsListItem.bIsReadOnly=true;
	MarsListItem.strName="MARS Properties";
	MarsListItem.strToolTip="Common properties for M(odel),A(tom),R(eference),S(et) model elements";

	ListItemArray.Add(MarsListItem);


	CString strDepends;
	CString strRefers;
	CString strTemp;
	
		
	bool bIsDependsDirty=false;
	bool bIsRefersDirty=false;

	bool bIsFirst=true;

	POSITION posFCO=MgaFCOPtrList.GetHeadPosition();

	while(posFCO)
	{
		CComPtr<IMgaFCO> ccpMgaFCO=MgaFCOPtrList.GetNext(posFCO);

		/////////////////////////////// Dependency //////////////////////////////////

		strTemp="N/A";
		CComPtr<IMgaFCO> ccpAncestorFCO;
		COMTHROW(ccpMgaFCO->get_DerivedFrom(&ccpAncestorFCO));
		if(ccpAncestorFCO) 
		{
			CComPtr<IMgaReference> ccpMgaDependReference;
			short wDepends;
			
			if(ccpMgaFCO.QueryInterface(&ccpMgaDependReference) == S_OK) 
			{
		 		COMTHROW(ccpMgaDependReference->CompareToBase(&wDepends));
				if(wDepends > 0)
				{
					strTemp="False";
				}
				else 
				{
					strTemp="True";
				}
			}
			else 
			{
				CComPtr<IMgaSet> ccpMgaSet;
				if(ccpMgaFCO.QueryInterface(&ccpMgaSet) == S_OK) 
				{
			 		COMTHROW(ccpMgaSet->CompareToBase(&wDepends));
					if(wDepends > 0)
					{
						strTemp="False";
					}
					else 
					{
						strTemp="True";
					}
				}
			}
		}
		
		if(bIsFirst)
		{
			strDepends=strTemp;
		}
		else
		{
			if(strTemp!=strDepends)
			{
				bIsDependsDirty=true;
			}
		}


		//////////////////////////////// Referece ////////////////////////////////
		strTemp="N/A";
		CComPtr<IMgaReference> ccpMgaReference;
		if(ccpMgaFCO.QueryInterface(&ccpMgaReference) == S_OK) // If FCO is a reference
		{
			// Obtaining references
			CComPtr<IMgaFCO> ccpReferredFCO;
	 		COMTHROW(ccpMgaReference->get_Referred(&ccpReferredFCO));

			if(ccpReferredFCO != 0) // Not NULL reference
			{
				CComBSTR bstrReferredName;
				COMTHROW(ccpReferredFCO->get_Name(&bstrReferredName));

				CComBSTR bstrReferredID;
				COMTHROW(ccpReferredFCO->get_ID(&bstrReferredID));

				CComPtr<IMgaMetaFCO> ccpMetaReferredFCO;
				COMTHROW(ccpReferredFCO->get_Meta(&ccpMetaReferredFCO));
				
				CComBSTR bstrMetaReferredName;
				COMTHROW(ccpMetaReferredFCO->get_DisplayedName(&bstrMetaReferredName));

				strTemp.Format(" %s (%s, ObjectID=%s)",CString(bstrReferredName),CString(bstrMetaReferredName),CString(bstrReferredID));
			}
			else // NULL reference
			{
				strTemp="<Null reference>";
			}	
		}
		
		// Setting dirty
		if(bIsFirst)
		{
			strRefers=strTemp;
		}
		else
		{
			if(strRefers!=strTemp)
			{
				bIsRefersDirty=true;
			}
		}


		bIsFirst=false;
	}

	CListItem ListItem;
	ListItem.bIsReadOnly=true;

	// Depends
	ListItem.bIsDifferentValue=bIsDependsDirty;
	ListItem.strName="Depends";
	ListItem.strToolTip="Dependencies of the FCO.";
	ListItem.Value.SetStringValue(strDepends);

	ListItemArray.Add(ListItem);

	// Refers
	ListItem.bIsDifferentValue=bIsRefersDirty;
	ListItem.strName="References";
	ListItem.strToolTip="FCO to which this reference refers.";
	ListItem.Value.SetStringValue(strRefers);

	ListItemArray.Add(ListItem);

}



void CProperty::CreateConnectionList(const CMgaFCOPtrList& MgaFCOPtrList,CArray<CListItem,CListItem&> &ListItemArray)
{

	// Adding "Connection Properties" container
	CListItem ConnListItem;
	ConnListItem.bIsContainer=true;
	ConnListItem.bIsReadOnly=true;
	ConnListItem.strName="Connection Properties";
	

	ListItemArray.Add(ConnListItem);


	CString strSource;
	CString strSourcePort;
	CString strDest;
	CString strDestPort;
		
	bool bIsSourceDirty=false;
	bool bIsSourcePortDirty=false;
	bool bIsDestDirty=false;
	bool bIsDestPortDirty=false;


	bool bIsFirst=true;

	POSITION posFCO=MgaFCOPtrList.GetHeadPosition();

	while(posFCO)
	{
		CComPtr<IMgaFCO> ccpMgaFCO=MgaFCOPtrList.GetNext(posFCO);

		CComPtr<IMgaFCO> ccpTempFCO;
		CComBSTR bstrTemp;

		CComPtr<IMgaSimpleConnection> ccpMgaSimpleConn;
		COMTHROW(ccpMgaFCO.QueryInterface(&ccpMgaSimpleConn));


		// Querying source side information - strSource
		COMTHROW( ccpMgaSimpleConn->get_Src(&ccpTempFCO) );
		ASSERT(ccpTempFCO != NULL);
		if( !ccpTempFCO) 
			continue;
		COMTHROW( ccpTempFCO->get_Name(&bstrTemp) );

		objtype_enum oeParentObjType;
		CComPtr<IMgaObject> ccpParentSrc;
		COMTHROW( ccpTempFCO->GetParent(&ccpParentSrc, &oeParentObjType) );

		ASSERT( ccpParentSrc != NULL );
		CString strSrcName=bstrTemp;
	
		// Setting dirty
		if(bIsFirst)
		{
			strSource=strSrcName;
		}
		else
		{
			if(strSource!=strSrcName)
			{
				bIsSourceDirty=true;
			}
		}
		
		bstrTemp.Empty();
		ccpTempFCO = NULL;

		// Querying destination side information - strDest
		COMTHROW( ccpMgaSimpleConn->get_Dst(&ccpTempFCO) );
		ASSERT(ccpTempFCO != NULL);
		if( !ccpTempFCO) 
			continue;

		COMTHROW( ccpTempFCO->get_Name(&bstrTemp) );

		CComPtr<IMgaObject> ccpParentDst;
		COMTHROW( ccpTempFCO->GetParent(&ccpParentDst, &oeParentObjType) );

		ASSERT( ccpParentDst != NULL );
		CString strDstName=bstrTemp;

		// Setting dirty
		if(bIsFirst)
		{
			strDest=strDstName;
		}
		else
		{
			if(strDest!=strDstName)
			{
				bIsDestDirty=true;
			}
		}

		bstrTemp.Empty();
		ccpTempFCO = NULL;

		VARIANT_BOOL vtbIsParentsEqual=VARIANT_FALSE;
  		COMTHROW( ccpParentSrc->get_IsEqual(ccpParentDst, &vtbIsParentsEqual) );

		CString strSrcPortName;
		CString strDstPortName;
		if (vtbIsParentsEqual != VARIANT_FALSE)  // If parents are equal
		{

			strSrcPortName ="-";
			strDstPortName ="-";
		} 
		else 
		{

			bstrTemp.Empty();
			COMTHROW( ccpParentSrc->get_Name(&bstrTemp) );
			strSrcPortName = bstrTemp;

			bstrTemp.Empty();
			COMTHROW( ccpParentDst->get_Name(&bstrTemp) );
			strDstPortName = bstrTemp;
		}

		// Setting dirty
		if(bIsFirst)
		{
			strSourcePort=strSrcPortName;
			strDestPort=strDstPortName;
		}
		else
		{
			if(strSourcePort!=strSrcPortName)
			{
				bIsSourcePortDirty=true;
			}

			if(strDestPort!=strDstPortName)
			{
				bIsDestPortDirty=true;
			}

		}

		bIsFirst=false;
	}

	CListItem ListItem;
	ListItem.bIsReadOnly=true;
	
	// strSource
	ListItem.bIsDifferentValue=bIsSourceDirty;
	ListItem.strName="Source";
	ListItem.strToolTip="Connection source side.";
	ListItem.Value.SetStringValue(strSource);

	ListItemArray.Add(ListItem);

	// strSourcePort
	ListItem.bIsDifferentValue=bIsSourcePortDirty;
	ListItem.strName="Source Port";
	ListItem.strToolTip="Connection source side port.";
	ListItem.Value.SetStringValue(strSourcePort);

	ListItemArray.Add(ListItem);

	// strDest
	ListItem.bIsDifferentValue=bIsDestDirty;
	ListItem.strName="Destination";
	ListItem.strToolTip="Connection destination side.";
	ListItem.Value.SetStringValue(strDest);

	ListItemArray.Add(ListItem);

	// strSourcePort
	ListItem.bIsDifferentValue=bIsDestPortDirty;
	ListItem.strName="Destination Port";
	ListItem.strToolTip="Connection destination side port.";
	ListItem.Value.SetStringValue(strDestPort);

	ListItemArray.Add(ListItem);


}


void CProperty::CreateFolderList(const CMgaFolderPtrList& MgaFolderPtrList,CArray<CListItem,CListItem&> &ListItemArray)
{
	// Adding "Folder Properties" container
	CListItem FolderListItem;
	FolderListItem.bIsContainer=true;
	FolderListItem.bIsReadOnly=true;
	FolderListItem.strName="Folder Properties";
	

	ListItemArray.Add(FolderListItem);


	CString strTemp;

	CString strLibraryRef;
	bool bIsLibraryRefDirty=false;

	bool bIsFirst=true;

	POSITION posFolder=MgaFolderPtrList.GetHeadPosition();

	while(posFolder)
	{
		CComPtr<IMgaFolder> ccpMgaFolder=MgaFolderPtrList.GetNext(posFolder);

		// Get Library Name		
		CComBSTR bstrLibraryName;
 		COMTHROW(ccpMgaFolder->get_LibraryName(&bstrLibraryName));
  		strTemp=bstrLibraryName;

		// Setting dirty
		if(bIsFirst)
		{
			strLibraryRef=strTemp;
			bIsFirst=false;
		}
		else
		{
			if(strLibraryRef!=strTemp)
			{
				bIsLibraryRefDirty=true;
			}
		}
	}

	CListItem ListItem;

	ListItem.bIsReadOnly=true;
	// strLibraryRef
	ListItem.bIsDifferentValue=bIsLibraryRefDirty;
	ListItem.strName="Library Name";
	ListItem.strToolTip="Library is a folder incorporating an MGA file using the same paradigm as meta.";
	ListItem.Value.SetStringValue(strLibraryRef);

	ListItemArray.Add(ListItem);

}



// Must be in read only transaction
void CProperty::CreateList(const CMgaFCOPtrList& MgaFCOPtrList,const CMgaFolderPtrList& MgaFolderPtrList,CArray<CListItem,CListItem&> &ListItemArray)
{
	ListItemArray.RemoveAll();
	
	if(MgaFCOPtrList.IsEmpty() && MgaFolderPtrList.IsEmpty())
	{
		return;
	}


	CreateGeneralList(MgaFCOPtrList,MgaFolderPtrList,ListItemArray);

	if(MgaFolderPtrList.IsEmpty())
	{
		CreateFCOList(MgaFCOPtrList,ListItemArray);

		if(m_bIsAllConnection)
		{
			// Create connection
			CreateConnectionList(MgaFCOPtrList,ListItemArray);
		}

		if(m_bIsAllMARS)
		{
			// CreateMARS
			CreateMarsList(MgaFCOPtrList,ListItemArray);
		}
	}
	else
	{
		if(MgaFCOPtrList.IsEmpty())
		{
			// CreateFolder
			CreateFolderList(MgaFolderPtrList,ListItemArray);
		}
	}
}		



