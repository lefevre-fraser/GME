#include "stdafx.h"
#include "CommonSmart.h"
#include "ComponentLib_h.h"
#include ".\merge.h"

#pragma warning(disable:4244)

Merge::Merge()
{
}

Merge::~Merge()
{
}

void Merge::test1()
{
	ObjMap act;
	
	addSubTreeToMap( CComPtr<IMgaObject>(act_root), act );

	ObjMap::iterator it = act.begin();
	while( it!=act.end() )
	{	
		CComPtr<IMgaObject> o( it->second );

		int type = getType(o);
		if( type==OBJTYPE_MODEL || type==OBJTYPE_ATOM || type==OBJTYPE_REFERENCE ||
			type==OBJTYPE_CONNECTION || type==OBJTYPE_SET )
		{
			CComPtr<IMgaFCO> fco;
			COMTHROW( o->QueryInterface( &fco ) );

			CComPtr<IMgaFCO> type;
			VARIANT_BOOL     instance;
			VARIANT_BOOL     primary;
			GUID             guid;
			GUID             type_guid;

			guid = getGuid(o);

			COMTHROW( fco->get_DerivedFrom(&type));
			COMTHROW( fco->get_IsInstance(&instance));
			COMTHROW( fco->get_IsPrimaryDerived(&primary) );

			if( type.p != NULL && primary==VARIANT_TRUE )
			{
				type_guid = getGuid(CComPtr<IMgaObject>(type));

				COMTHROW( fco->DetachFromArcheType() );
				fco->AttachToArcheType( type, instance );
			}

			fco.Release();
		}

		o.Release();

		it++;
	}	
}


void Merge::doMerge( IMgaProject * act_proj, IMgaProject * mergein_proj )
{	try
	{
		long project_prefs_org;
		long project_prefs;

		// set input
		act_project.Attach( act_proj );
		mergein_project.Attach( mergein_proj );

		COMTHROW( act_project->get_Preferences(&project_prefs_org) );
		project_prefs = project_prefs_org | MGAPREF_IGNORECONNCHECKS;
		COMTHROW( act_project->put_Preferences(project_prefs) );

		// begin transactions
		CComPtr<IMgaTerritory> terr0, terr1;
		COMTHROW(act_project->CreateTerritory(NULL, &terr0));
		COMTHROW(act_project->BeginTransaction(terr0));
		COMTHROW(mergein_project->CreateTerritory(NULL, &terr1));
		COMTHROW(mergein_project->BeginTransaction(terr1));

		// check if paradigms match
		checkParadigms();

		// get and check root folders
		checkRootFolders();


		doMerge();

		COMTHROW( act_project->put_Preferences(project_prefs_org) );

		// commit transactions
		COMTHROW(act_project->CommitTransaction());
		COMTHROW(mergein_project->CommitTransaction());
	}
	catch(...)
	{		
		act_project->AbortTransaction();
		mergein_project->AbortTransaction();
		AfxMessageBox("Merge failed!");
	}
}

void Merge::checkParadigms()
{
	CComVariant v0, v1;

	COMTHROW( act_project->get_MetaGUID(&v0) );
	COMTHROW( mergein_project->get_MetaGUID(&v1) );

	GUID g0, g1;
	CopyTo(v0, g0);
	CopyTo(v1, g1);

	if( memcmp(&g0, &g1, sizeof(g0) ))
	{
		AfxMessageBox("Paradigm mismatch error!");
		throw 0;
	}	
}

void Merge::checkRootFolders()
{
	COMTHROW( act_project->get_RootFolder( &act_root ) );
	COMTHROW( mergein_project->get_RootFolder( &mergein_root ) );

	GUID g0 = getGuid( CComPtr<IMgaObject>(act_root) );
	GUID g1 = getGuid( CComPtr<IMgaObject>(mergein_root) );

	if( !IsEqualGUID( g0, g1 ) )
	{
		AfxMessageBox("GUIDs of root folders do not match!");
		throw 0;
	}
}

void Merge::doMerge()
{
	//test1();
	//return;

	deleteObjects();

	savePointers();

	mergeFolders( act_root, mergein_root );

	restoreTypes();
	restoreReferences();
	restoreConnections();
	restoreSets();
}

void Merge::deleteObjects()
{
	ObjMap act, mergin;
	ObjVec destroy;
	
	addSubTreeToMap( CComPtr<IMgaObject>(act_root), act );
	addSubTreeToMap( CComPtr<IMgaObject>(mergein_root), mergin );

	int closure_id = getMerginClosureID();

	ObjMap::iterator it = act.begin();
	while( it!=act.end() )
	{	
		if( inClosure( it->second, closure_id ) )
		{
			ObjMap::iterator it2 = mergin.find(it->first);
			if( it2 == mergin.end() )
				destroy.push_back( it->second );
		}
		it++;
	}	

	// destroy objects
	ObjVec::iterator it3 = destroy.begin();
	while( it3 != destroy.end() )
	{
		(*it3)->DestroyObject();
		it3++;
	}
}

void Merge::savePointers()
{
	savePointers( CComPtr<IMgaObject>(act_root) );
	savePointers( CComPtr<IMgaObject>(mergein_root) );
}

void Merge::savePointers( CComPtr<IMgaObject> parent )
{
	int  type = getType( parent );
	GUID guid = getGuid(parent);

	// save set info
	if( type==OBJTYPE_SET )
	{
		long i,n;
		CComPtr<IMgaSet>		set;
		CComPtr<IMgaFCOs>		members;
		CComPtr<IMgaFCO>		member;

		COMTHROW( parent->QueryInterface( &set ) );
		COMTHROW( set->get_Members(&members) );
		COMTHROW( members->get_Count(&n) );

		GUIDVec v;
		for( i=1; i<=n; ++i )
		{
			COMTHROW( members->get_Item(i,&member) );
			v.push_back(getGuid( CComPtr<IMgaObject>(member) ));
			member.Release();
		}

		GUIDVecMap::iterator it = set_info.find(guid);
		if( it == set_info.end() )
			set_info.insert( GUIDVecMap::value_type( guid, v ) );
	}

	// save connection info
	if( type==OBJTYPE_CONNECTION )
	{
		long i,n;
		CComPtr<IMgaConnection> conn;
		CComPtr<IMgaConnPoints> conn_points;
		CComPtr<IMgaConnPoint>  conn_point;
		CComPtr<IMgaFCO>        target;

		COMTHROW( parent->QueryInterface( &conn ) );
		COMTHROW( conn->get_ConnPoints(&conn_points) );
		COMTHROW( conn_points->get_Count(&n) );

		ConnPointVec v;
		for( i=1; i<=n; ++i )
		{
			COMTHROW( conn_points->get_Item(i,&conn_point) );
			COMTHROW( conn_point->get_Target( &target ) );
			ConnPoint c;
			c.target = getGuid( CComPtr<IMgaObject>(target) );
			COMTHROW( conn_point->get_ConnRole(&c.role_name) );
			v.push_back(c);
			conn_point.Release();
			target.Release();
		}

		ConnInfoMap::iterator it = conn_info.find(guid);
		if( it == conn_info.end() )
			conn_info.insert( ConnInfoMap::value_type( guid, v ) );
	}

	// save ref info
	if( type==OBJTYPE_REFERENCE )
	{
		CComPtr<IMgaReference> ref;
		CComPtr<IMgaFCO>	   reffered;

		COMTHROW( parent->QueryInterface( &ref ) );
		COMTHROW( ref->get_Referred(&reffered));

		if( reffered.p != NULL )
		{
			GUID ref_guid = getGuid(CComPtr<IMgaObject>(reffered));

			RefInfoMap::iterator it = ref_info.find(guid);
			if( it==ref_info.end() )
				ref_info.insert(RefInfoMap::value_type(guid,ref_guid));
			else
				it->second = ref_guid;
		}
	}
		
	// save type info
	if( type==OBJTYPE_MODEL || type==OBJTYPE_ATOM || type==OBJTYPE_REFERENCE ||
		type==OBJTYPE_CONNECTION || type==OBJTYPE_SET )
	{
		CComPtr<IMgaFCO> fco;
		CComPtr<IMgaFCO> type_fco;
		VARIANT_BOOL     primary;

		COMTHROW( parent->QueryInterface( &fco ) );
		COMTHROW( fco->get_DerivedFrom(&type_fco));
		COMTHROW( fco->get_IsPrimaryDerived(&primary) );
		
		if( type_fco.p != NULL && primary )
		{			
			GUID type_guid = getGuid(CComPtr<IMgaObject>(type_fco));

			VARIANT_BOOL instance;
			COMTHROW( fco->get_IsInstance(&instance) );

			TypeInfoMap::iterator it = type_info.find( guid );
			if( it == type_info.end() )
			{
				TypeInfo t;
				t.type = type_guid;
				t.instance = instance;
				type_info.insert(TypeInfoMap::value_type(guid,t));
			}
		}
	}

	// for all children
	if( type==OBJTYPE_MODEL || type==OBJTYPE_FOLDER )
	{
		long                 n,i;
		CComPtr<IMgaObjects> children;
		CComPtr<IMgaObject>  obj;

		COMTHROW( parent->get_ChildObjects( &children ) );
		COMTHROW( children->get_Count(&n) );
		for( i=1; i<=n; ++i )
		{
			COMTHROW( children->get_Item( i, &obj ) );
			savePointers( obj  );
			obj.Release();
		}
	}
}

void Merge::restoreTypes()
{
	TypeInfoMap::iterator it = type_info.begin();
	while( it!=type_info.end() )
	{		
		CComPtr<IMgaFCO> fco  = findFCO(act_root,it->first); 
		CComPtr<IMgaFCO> type = findFCO(act_root,it->second.type); 

		GUID fco_g = it->first;
		GUID type_g = it->second.type;

		VARIANT_BOOL writeable;

		COMTHROW( fco->get_IsWritable( &writeable ) );

		if( fco.p != NULL && writeable )
		{
			//CComPtr<IMgaFCO> org_type;
			//COMTHROW( fco->get_DerivedFrom(&org_type));

			//COMTHROW( fco->DetachFromArcheType() );
			//COMTHROW( fco->AttachToArcheType( type, it->second.instance ) );
			try
			{
				fco->AttachToArcheType( type, it->second.instance );
			}
			catch(...)
			{
			}

			/*if( org_type.p != NULL )
			{
				GUID org_type_g = getGuid( CComPtr<IMgaObject>(org_type) );				
				if( !IsEqualGUID( type_g, org_type_g ) )
				{
					COMTHROW( fco->AttachToArcheType( type, it->second.instance ) );
				}				
				else
					COMTHROW( fco->AttachToArcheType( type, it->second.instance ) );
			}
			else
				COMTHROW( fco->AttachToArcheType( type, it->second.instance ) );*/

			/*// hack! AttachToArcheType sometimes throws an exception.
			try
			{
				COMTHROW( fco->AttachToArcheType( type, it->second.instance ) );
			}
			catch(...)
			{				
			}*/
		}

		fco.Release();
		type.Release();

		it++;
	}
}

void Merge::restoreReferences()
{
	RefInfoMap::iterator it = ref_info.begin();
	while( it!=ref_info.end() )
	{		
		CComPtr<IMgaFCO> fco      = findFCO(act_root,it->first);
		CComPtr<IMgaFCO> reffered = findFCO(act_root,it->second);		

		if( fco.p != NULL )
		{
			VARIANT_BOOL	 writeable;
			COMTHROW( fco->get_IsWritable( &writeable ) );

			if( writeable )
			{
				CComPtr<IMgaReference> ref;

				COMTHROW( fco->QueryInterface( &ref ) );

				ref->put_Referred( reffered );
			}
		}
		it++;
	}
}

void Merge::restoreConnections()
{
	ConnInfoMap::iterator it = conn_info.begin();
	while( it!=conn_info.end() )
	{				
		CComPtr<IMgaFCO> fco = findFCO(act_root,it->first);		
		if( fco.p != NULL )
		{			
			CComPtr<IMgaConnection> conn;
			CComPtr<IMgaConnPoint>  conn_point;
			VARIANT_BOOL			writeable;

			COMTHROW( fco->QueryInterface( &conn) );
			COMTHROW( fco->get_IsWritable( &writeable ) );

			if( writeable )
			{
				// check if all targets exist
				bool found_all = true;
				ConnPointVec::iterator it2 = it->second.begin();
				while( it2!=it->second.end() )
				{
					CComPtr<IMgaFCO> target = findFCO(act_root,it2->target);
					if( target.p == NULL )
					{
						found_all = false;
						break;
					}
					else
					{
						//COMTHROW( conn->AddConnPoint(it2->role_name,0,target,NULL,&conn_point) );
						HRESULT hres = conn->AddConnPoint(it2->role_name,0,target,NULL,&conn_point);
						if( hres != S_OK )
						{
							printf("alma");
						}
						conn_point.Release();
					}
					it2++;
				}

				if( !found_all )
					conn->DestroyObject();
			}
		}
		it++;
	}
}

void Merge::restoreSets()
{
	GUIDVecMap::iterator it = set_info.begin();
	while( it!=set_info.end() )
	{
		CComPtr<IMgaFCO> fco  = findFCO(act_root,it->first);
		
		if( fco.p != NULL )
		{
			CComPtr<IMgaSet> set;

			COMTHROW( fco.QueryInterface(&set) );
			COMTHROW( set->RemoveAll() );

			GUIDVec::iterator it2 = it->second.begin();
			while( it2 != it->second.end() )
			{
				CComPtr<IMgaFCO> member = findFCO(act_root,*it2);
				if( member.p != NULL )
				{
					COMTHROW( set->AddMember( member ) );
					member.Release();
				}
				it2++;
			}
		}

		it++;
	}
}

bool Merge::shouldFollowLink( CComPtr<IMgaFCO> fco )
{
	VARIANT_BOOL	  primary_derived;
	CComPtr<IMgaFCO>  derived_from;

	//VARIANT_BOOL instance;
	//COMTHROW( act->get_IsInstance(&instance) );

	COMTHROW( fco->get_IsPrimaryDerived(&primary_derived) );
	COMTHROW( fco->get_DerivedFrom(&derived_from) );

	return (derived_from.p == NULL || primary_derived == VARIANT_TRUE );
}

void Merge::mergeFolders( CComPtr<IMgaFolder> act, CComPtr<IMgaFolder> mergein )
{
	long i,n;

	// child FCOs
	CComPtr<IMgaFCOs> mergein_children;
	CComPtr<IMgaFCO>  mergein_fco;
	CComPtr<IMgaFCO>  act_fco;

	COMTHROW( mergein->get_ChildFCOs(&mergein_children) );
	COMTHROW( mergein_children->get_Count(&n) );
	for( i=1; i<=n; ++i )
	{
		COMTHROW( mergein_children->get_Item(i,&mergein_fco) );
		int type = getType(CComPtr<IMgaObject>(mergein_fco));

		GUID guid = getGuid(CComPtr<IMgaObject>(mergein_fco));
		act_fco = findFCOInChildren( act, guid );

		if( !shouldFollowLink(mergein_fco) || (act_fco.p!=NULL && !shouldFollowLink(act_fco) ))
		{
			mergein_fco.Release();
			act_fco.Release();
			continue;
		}

		if( act_fco.p == NULL )
		{
			// delete if found anywhere (moved objects)
			CComPtr<IMgaFCO> moved_fco = findFCO( act, guid );
			if( moved_fco.p != NULL )
				COMTHROW( moved_fco->DestroyObject() );

			// create fco
			act_fco = copyFCO( mergein_fco, act );
		}
		else
		{
			copyAttribsAndRegistry(mergein_fco, act_fco);
		}

		if( type == OBJTYPE_MODEL )
		{
			CComPtr<IMgaModel> mergin_model;
			CComPtr<IMgaModel> act_model;
			COMTHROW( mergein_fco->QueryInterface(&mergin_model) );
			COMTHROW( act_fco->QueryInterface(&act_model) );
			mergeModels( act_model, mergin_model );
		}

		act_fco.Release();
		mergein_fco.Release();
	}

	// subfolders
	CComPtr<IMgaFolders> mergein_subfolders;
	CComPtr<IMgaFolder>  mergein_folder;
	CComPtr<IMgaFolder>	 act_folder;

	COMTHROW( mergein->get_ChildFolders(&mergein_subfolders) );
	COMTHROW( mergein_subfolders->get_Count(&n) );
	for( i=1; i<=n; ++i )
	{
		COMTHROW( mergein_subfolders->get_Item(i,&mergein_folder) );

		GUID guid = getGuid(CComPtr<IMgaObject>(mergein_folder));
		act_folder = findFolderInChildren( act, guid );

		if( act_folder.p == NULL )
		{
			// delete if found anywhere (moved objects)
			CComPtr<IMgaFolder> moved_folder = findFolder( act_root, guid );
			if( moved_folder.p != NULL )
				COMTHROW( moved_folder->DestroyObject() );

			// create folder
			CComPtr<IMgaFolder> new_folder = copyFolder( mergein_folder, act );			

			COMTHROW( new_folder->QueryInterface(&act_folder) );
			
			// TODO: copy registry!!
		}
		else
		{
			// TODO: copy registry!!
		}

		mergeFolders( act_folder, mergein_folder );

		act_folder.Release();
		mergein_folder.Release();
	}
}

void Merge::mergeModels( CComPtr<IMgaModel> act, CComPtr<IMgaModel> mergein )
{
	long i,n;
	CComPtr<IMgaFCOs> mergein_children;
	CComPtr<IMgaFCO>  mergein_fco;
	CComPtr<IMgaFCO>  act_fco;

	if( !shouldFollowLink(CComPtr<IMgaFCO>(act)) || !shouldFollowLink(CComPtr<IMgaFCO>(mergein)) )
		return;	

	COMTHROW( mergein->get_ChildFCOs(&mergein_children) );
	COMTHROW( mergein_children->get_Count(&n) );
	for( i=1; i<=n; ++i )
	{
		COMTHROW( mergein_children->get_Item(i,&mergein_fco) );
		
		GUID guid = getGuid(CComPtr<IMgaObject>(mergein_fco));
		int  type = getType(CComPtr<IMgaObject>(mergein_fco));

		act_fco = findFCOInChildren( act, guid );

		if( !shouldFollowLink(mergein_fco) || (act_fco.p!=NULL && !shouldFollowLink(act_fco) ))
		{
			mergein_fco.Release();
			act_fco.Release();
			continue;
		}

		if( act_fco.p == NULL )
		{
			// delete if found anywhere (moved objects)
			CComPtr<IMgaFCO> moved_fco = findFCO( act_root, guid );
			if( moved_fco.p != NULL )
				COMTHROW( moved_fco->DestroyObject() );

			// create fco
			act_fco = copyFCO( mergein_fco, act );
		}
		else
		{
			copyAttribsAndRegistry(mergein_fco, act_fco);
		}

		if( type == OBJTYPE_MODEL )
		{
			CComPtr<IMgaModel> mergin_model;
			CComPtr<IMgaModel> act_model;
			COMTHROW( mergein_fco->QueryInterface(&mergin_model) );
			COMTHROW( act_fco->QueryInterface(&act_model) );
			mergeModels( act_model, mergin_model );
		}

		act_fco.Release();
		mergein_fco.Release();
	}
}

CComPtr<IMgaFCO> Merge::copyFCO( CComPtr<IMgaFCO> src, CComPtr<IMgaModel> parent )
{
	CComPtr<IMgaMetaRole>  src_role;
	CComBSTR			   role_name;
	CComPtr<IMgaMetaFCO>   meta_fco;
	CComPtr<IMgaMetaModel> meta_model;
	CComPtr<IMgaMetaRole>  role;
	CComPtr<IMgaFCO>	   new_fco;
	CComBSTR			   name;
	GUID				   guid; 
	
	// get name and guid
	guid = getGuid(CComPtr<IMgaObject>(src));
	COMTHROW( src->get_Name( &name ));

	// create fco
	COMTHROW( src->get_MetaRole(&src_role) );
	COMTHROW( src_role->get_Name(&role_name) );
	COMTHROW( parent->get_Meta(&meta_fco) );
	COMTHROW( meta_fco->QueryInterface(&meta_model) );
	COMTHROW( meta_model->get_RoleByName(role_name, &role ) );
	COMTHROW( parent->CreateChildObject(role, &new_fco ) );

	// set guid
	COMTHROW( new_fco->PutGuidDisp( CComBSTR(formatGuid(guid)) ));
	
	// set name
	COMTHROW( new_fco->put_Name( name ));	

	// copy attribs and registry
	copyAttribsAndRegistry( CComPtr<IMgaFCO>(src), CComPtr<IMgaFCO>(new_fco) );      

	return new_fco;
}

CComPtr<IMgaFCO> Merge::copyFCO( CComPtr<IMgaFCO> src, CComPtr<IMgaFolder> parent )
{
	CComPtr<IMgaMetaFCO>    src_meta_fco;
	CComPtr<IMgaMetaFCO>    meta_fco;
	CComPtr<IMgaMetaModel>  meta_model;
	CComPtr<IMgaMetaFolder> meta_folder;

	CComPtr<IMgaFCO>	    new_fco;
	CComBSTR			    deffco_name;
	CComBSTR			    name;
	GUID				    guid;
	
	// get name and guid
	guid = getGuid(CComPtr<IMgaObject>(src));
	COMTHROW( src->get_Name( &name ));

	// create model
	COMTHROW( src->get_Meta(&src_meta_fco));
	COMTHROW( src_meta_fco->get_Name(&deffco_name));
	COMTHROW( parent->get_MetaFolder(&meta_folder) );
	COMTHROW( meta_folder->get_DefinedFCOByName(deffco_name, VARIANT_TRUE, &meta_fco ));
	COMTHROW( parent->CreateRootObject(meta_fco, &new_fco ) );

	// set guid
	COMTHROW( new_fco->PutGuidDisp( CComBSTR(formatGuid(guid)) ));

	// set name
	COMTHROW( new_fco->put_Name( name ));
    
	// copy attribs and registry
	copyAttribsAndRegistry( CComPtr<IMgaFCO>(src), CComPtr<IMgaFCO>(new_fco) );      

	return new_fco;
}

CComPtr<IMgaFolder> Merge::copyFolder( CComPtr<IMgaFolder> src, CComPtr<IMgaFolder> parent )
{
	CComPtr<IMgaMetaFolder> src_meta_folder;
	CComPtr<IMgaMetaFolder> parent_meta_folder;
	CComPtr<IMgaMetaFolder> meta_folder;
	CComBSTR			    name_disp;
	CComPtr<IMgaFolder>	    new_folder;
	CComBSTR			    name;
	GUID				    guid;

	// get name and guid
	guid = getGuid(CComPtr<IMgaObject>(src));
	COMTHROW( src->get_Name( &name ));

	// create folder
	COMTHROW( src->get_MetaFolder( &src_meta_folder ));
	COMTHROW( src_meta_folder->get_Name( &name_disp ));
	COMTHROW( parent->get_MetaFolder( &parent_meta_folder ));
	COMTHROW( parent_meta_folder->get_DefinedFolderByName(name_disp, VARIANT_TRUE, &meta_folder ));
	COMTHROW( parent->CreateFolder( meta_folder, &new_folder ));

	// set guid
	COMTHROW( new_folder->PutGuidDisp( CComBSTR(formatGuid(guid)) ));

	// set name
	COMTHROW( new_folder->put_Name( name ));
    
	// copy attributes
	copyFolderAttribs( src, new_folder );

	return new_folder;
}

void Merge::copyRegistry( CComPtr<IMgaFCO> src, CComPtr<IMgaFCO> dest )
{
	CComPtr<IMgaRegNodes> src_reg_nodes;

	COMTHROW( src->get_Registry(VARIANT_FALSE,&src_reg_nodes) );
	copyRegistry( src_reg_nodes, dest );
}

void Merge::copyRegistry( CComPtr<IMgaRegNodes> nodes, CComPtr<IMgaFCO> dest )
{
	long                  n,i;
	CComPtr<IMgaRegNodes> sub_nodes;
	CComPtr<IMgaRegNode>  node;
	CComBSTR			  path;
	CComBSTR			  value;

	COMTHROW( nodes->get_Count(&n) );
	for( i=1; i<=n; ++i )
	{
		COMTHROW( nodes->get_Item(i,&node) );

		COMTHROW( node->get_Path(&path) );
		COMTHROW( node->get_Value(&value) );
		COMTHROW( dest->put_RegistryValue(path,value) );

		// sub nodes
		COMTHROW( node->get_SubNodes( VARIANT_FALSE, &sub_nodes ) );
		if( sub_nodes.p != NULL )
			copyRegistry( sub_nodes, dest );		

		sub_nodes.Release();
		node.Release();
	}
}

void Merge::copyRegistry( CComPtr<IMgaRegNodes> nodes, CComPtr<IMgaFolder> dest )
{
	long                  n,i;
	CComPtr<IMgaRegNodes> sub_nodes;
	CComPtr<IMgaRegNode>  node;
	CComBSTR			  path;
	CComBSTR			  value;

	COMTHROW( nodes->get_Count(&n) );
	for( i=1; i<=n; ++i )
	{
		COMTHROW( nodes->get_Item(i,&node) );

		COMTHROW( node->get_Path(&path) );
		COMTHROW( node->get_Value(&value) );
		COMTHROW( dest->put_RegistryValue(path,value) );

		// sub nodes
		COMTHROW( node->get_SubNodes( VARIANT_FALSE, &sub_nodes ) );
		if( sub_nodes.p != NULL )
			copyRegistry( sub_nodes, dest );		

		sub_nodes.Release();
		node.Release();
	}
}

void Merge::copyAttribs( CComPtr<IMgaFCO> src, CComPtr<IMgaFCO> dest )
{
	long n,i;

	CComPtr<IMgaAttributes> dest_attribs;
	CComPtr<IMgaAttributes> src_attribs;
	CComPtr<IMgaAttribute>  src_attrib;
	CComPtr<IMgaAttribute>  dest_attrib;

	CComPtr<IMgaMetaAttribute> meta_attrib;

	COMTHROW( src->get_Attributes(&src_attribs) );
	COMTHROW( dest->get_Attributes(&dest_attribs) );
	COMTHROW( src_attribs->get_Count(&n) );
	for( i=1; i<=n; ++i )
	{
		COMTHROW( src_attribs->get_Item(i,&src_attrib) );
		COMTHROW( dest_attribs->get_Item(i,&dest_attrib) );

		COMTHROW( src_attrib->get_Meta( &meta_attrib ) );
		
		CComVariant val;
		COMTHROW( src_attrib->get_Value(&val) );
		COMTHROW( dest_attrib->put_Value(val) );

		src_attrib.Release();
		dest_attrib.Release();
		meta_attrib.Release();		
	}
}

void Merge::copyAttribsAndRegistry( CComPtr<IMgaFCO>(src), CComPtr<IMgaFCO>(new_fco) )
{
	// set name
	CComBSTR name;	
	COMTHROW( src->get_Name(&name) );
	COMTHROW( new_fco->put_Name(name) );

	copyAttribs( src, new_fco );
	copyRegistry( src, new_fco );
}

void Merge::copyFolderAttribs( CComPtr<IMgaFolder> src, CComPtr<IMgaFolder> new_folder )
{
	// name
	CComBSTR name;
	COMTHROW( src->get_Name(&name) );
	COMTHROW( new_folder->put_Name(name) );

	// registry
	CComPtr<IMgaRegNodes> src_reg_nodes;
	COMTHROW( src->get_Registry(VARIANT_FALSE,&src_reg_nodes) );
	copyRegistry( src_reg_nodes, new_folder );
}

GUID Merge::getGuid( CComPtr<IMgaObject> o )
{
	long l1,l2,l3,l4;
	COMTHROW( o->GetGuid( &l1, &l2, &l3, &l4 ) );    

	GUID g;

	// based on MgaFCO.cpp function: HRESULT FCO::GetGuidDisp( BSTR *p_pGuidStr)
	g.Data1    = l1;
	g.Data2    = (l2 >> 16);
	g.Data3    = (l2 << 16) >> 16;
	g.Data4[0] = (l3 >> 24);
	g.Data4[1] = (l3 << 8) >> 24;
	g.Data4[2] = (l3 << 16) >> 24;
	g.Data4[3] = (l3 << 24) >> 24;
	g.Data4[4] = (l4 >> 24);
	g.Data4[5] = (l4 << 8) >> 24;
	g.Data4[6] = (l4 << 16) >> 24;
	g.Data4[7] = (l4 << 24) >> 24;
    
	return g;
}

CString Merge::formatGuid( GUID g )
{
	char buff[39];
	sprintf( buff, "{%08lX-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X}",
			g.Data1, g.Data2, g.Data3,
			g.Data4[0], g.Data4[1], g.Data4[2], g.Data4[3],
			g.Data4[4], g.Data4[5], g.Data4[6], g.Data4[7]);
	return CString(buff);
}

int Merge::getType( CComPtr<IMgaObject> o )
{
	objtype_enum t;
	COMTHROW( o->get_ObjType(&t) );
	return t;
}

CComPtr<IMgaFCO> Merge::findFCO( CComPtr<IMgaModel> parent, GUID g )
{
	if( IsEqualGUID( getGuid(CComPtr<IMgaObject>(parent)), g ))
		return CComPtr<IMgaFCO>(parent);

	long			   i,n;
	CComPtr<IMgaFCOs>  children;

	COMTHROW( parent->get_ChildFCOs(&children) );
	COMTHROW( children->get_Count(&n) );

	for( i=1; i<=n; ++i )
	{
		CComPtr<IMgaFCO> fco;
		COMTHROW( children->get_Item(i,&fco) );

		if( getType(CComPtr<IMgaObject>(fco)) == OBJTYPE_MODEL )
		{
			CComPtr<IMgaModel> model;
			COMTHROW( fco->QueryInterface(&model) );
			CComPtr<IMgaFCO> res = findFCO( model, g );
			if( res.p != NULL )
				return res;
		}
		else if( IsEqualGUID( getGuid(CComPtr<IMgaObject>(fco)), g ))
			return fco;

		fco.Release();
	}

	return CComPtr<IMgaFCO>();
}

CComPtr<IMgaFCO> Merge::findFCO( CComPtr<IMgaFolder> parent, GUID g )
{
	// child fcos
	long			   i,n;
	CComPtr<IMgaFCOs>  children;

	COMTHROW( parent->get_ChildFCOs(&children) );
	COMTHROW( children->get_Count(&n) );

	for( i=1; i<=n; ++i )
	{
		CComPtr<IMgaFCO> fco;
		COMTHROW( children->get_Item(i,&fco) );

		if( IsEqualGUID( getGuid(CComPtr<IMgaObject>(fco)), g ))
			return fco;
		else if( getType(CComPtr<IMgaObject>(fco)) == OBJTYPE_MODEL )
		{
			CComPtr<IMgaModel> model;
			COMTHROW( fco->QueryInterface(&model) );
			CComPtr<IMgaFCO> res = findFCO( model, g );
			if( res.p != NULL )
				return res;
		}

		fco.Release();
	}

	// subfolders
	CComPtr<IMgaFolders> subfolders;
	CComPtr<IMgaFolder>  folder;
	
	COMTHROW( parent->get_ChildFolders(&subfolders) );
	COMTHROW( subfolders->get_Count(&n) );
	for( i=1; i<=n; ++i )
	{
		COMTHROW( subfolders->get_Item(i,&folder) );
		CComPtr<IMgaFCO> res = findFCO( folder, g );
		folder.Release();
		if( res.p != NULL )
			return res;
	}

	return CComPtr<IMgaFCO>();
}

CComPtr<IMgaFCO> Merge::findFCOInChildren( CComPtr<IMgaModel> parent, GUID g )
{	
	long i,n;
	CComPtr<IMgaFCOs> children;

	COMTHROW( parent->get_ChildFCOs(&children) );
	COMTHROW( children->get_Count(&n) );
	for( i=1; i<=n; ++i )
	{
		CComPtr<IMgaFCO> fco;
		COMTHROW( children->get_Item(i,&fco) );

		if( IsEqualGUID( getGuid(CComPtr<IMgaObject>(fco)), g ))
			return fco;
	}
	return CComPtr<IMgaFCO>();
}

CComPtr<IMgaFCO> Merge::findFCOInChildren( CComPtr<IMgaFolder> parent, GUID g )
{	
	long i,n;
	CComPtr<IMgaFCOs> children;

	COMTHROW( parent->get_ChildFCOs(&children) );
	COMTHROW( children->get_Count(&n) );
	for( i=1; i<=n; ++i )
	{
		CComPtr<IMgaFCO> fco;
		COMTHROW( children->get_Item(i,&fco) );

		if( IsEqualGUID( getGuid(CComPtr<IMgaObject>(fco)), g ))
			return fco;
	}
	return CComPtr<IMgaFCO>();
}

CComPtr<IMgaFolder> Merge::findFolder( CComPtr<IMgaFolder> parent, GUID g )
{	
	if( IsEqualGUID( getGuid(CComPtr<IMgaObject>(parent)), g ))
		return parent;

	long i,n;
	CComPtr<IMgaFolders> children;

	COMTHROW( parent->get_ChildFolders(&children) );
	COMTHROW( children->get_Count(&n) );
	for( i=1; i<=n; ++i )
	{
		CComPtr<IMgaFolder> folder;
		COMTHROW( children->get_Item(i,&folder) );

		CComPtr<IMgaFolder> res = findFolder( folder, g );

		if( res.p != NULL )
			return res;
	}
	return CComPtr<IMgaFolder>();
}

CComPtr<IMgaFolder> Merge::findFolderInChildren( CComPtr<IMgaFolder> parent, GUID g )
{	
	long i,n;
	CComPtr<IMgaFolders> children;

	COMTHROW( parent->get_ChildFolders(&children) );
	COMTHROW( children->get_Count(&n) );
	for( i=1; i<=n; ++i )
	{
		CComPtr<IMgaFolder> folder;
		COMTHROW( children->get_Item(i,&folder) );

		if( IsEqualGUID( getGuid(CComPtr<IMgaObject>(folder)), g ))
			return folder;

		folder.Release();
	}
	return CComPtr<IMgaFolder>();
}

int Merge::getMerginClosureID()
{
	CComPtr<IMgaClosure> cl;
	long id;

	COMTHROW( cl.CoCreateInstance(L"Mga.MgaClosure") );
	COMTHROW( cl->GetLastClosureId( mergein_project, &id ) );
	return (int)id;
}

bool Merge::inClosure( CComPtr<IMgaObject> obj, int closureID )
{
	CComPtr<IMgaRegNode> node;
	CComBSTR			 val;
	CComBSTR			 path = "inClosure";
	int					 type = getType(obj);

	if( type >= OBJTYPE_MODEL && type <= OBJTYPE_SET )
	{
		CComPtr<IMgaFCO> fco;
		COMTHROW( obj->QueryInterface(&fco) );
		COMTHROW( fco->get_RegistryNode(path, &node ) );
	}
	else if( type == OBJTYPE_FOLDER )
	{
		CComPtr<IMgaFolder> folder;
		COMTHROW( obj->QueryInterface(&folder) );
		COMTHROW( folder->get_RegistryNode(path, &node ) );
	}
	else
		return false;

	if( node.p == NULL )
		return false;

	COMTHROW( node->get_Value(&val) );
	CString val2 = val;

	IntSet closures = parseClosureString( val2 );

	return ( closures.find(closureID) != closures.end() );
}

IntSet Merge::parseClosureString( const char * str )
{
	// format: (',' NUM)*

	IntSet ret;
	char * ch = (char*)str + 1;
	char * last_num = ch;
	while( *ch!=0 )
	{
		ch++;
		if( *ch==',' || *ch==0 )
		{
			ret.insert( atoi(last_num) );
			last_num = ch+1;
		}
	}

	return ret;
}

void Merge::addSubTreeToMap( CComPtr<IMgaObject> o, ObjMap& map )
{
	GUID g = getGuid(o);

	if( map.find(g)==map.end() )
		map.insert( ObjMap::value_type(g,o) );

	int type = getType(o);
	if( type==OBJTYPE_MODEL || type==OBJTYPE_FOLDER )
	{
		long i,n;
		CComPtr<IMgaObjects> children;

		COMTHROW( o->get_ChildObjects(&children) );
		COMTHROW( children->get_Count(&n) );
		for( i=1; i<=n; ++i )
		{
			CComPtr<IMgaObject> child;
			COMTHROW( children->get_Item(i,&child) );
			addSubTreeToMap( child, map );
			child.Release();
		}
	}
}
