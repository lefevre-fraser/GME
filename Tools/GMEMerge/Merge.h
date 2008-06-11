#pragma once

#include <map>
#include <string>
#include <vector>
#include <set>

struct GUID_less
{
	bool operator()(const GUID& a, const GUID& b) const
	{
        if( a.Data1 < b.Data1 )
            return true;
        else if( a.Data1 > b.Data1 )
            return false;
        else
        {
            DWORD * adw = (DWORD*)&a;
            DWORD * bdw = (DWORD*)&b;
            if( *(adw+1) < *(bdw+1) )
                return true;
            else if( *(adw+1) > *(bdw+1) )
                return false;
            else if( *(adw+2) < *(bdw+2) )
                return true;
            else if( *(adw+2) > *(bdw+2) )
                return false;
            else if( *(adw+3) < *(bdw+3) )
                return true;
            else 
                return false;
        }
	}
};

struct TypeInfo
{
	GUID		 type;
	VARIANT_BOOL instance;
};

struct ConnPoint
{
	GUID	 target;
	CComBSTR role_name;
	// TODO:references
};


typedef std::set<int>							     IntSet;
typedef std::vector<GUID>						     GUIDVec;
typedef std::map<GUID,TypeInfo,GUID_less>		     TypeInfoMap;
typedef std::map<GUID,GUID,GUID_less>			     RefInfoMap;
typedef std::vector<ConnPoint>					     ConnPointVec;
typedef std::map<GUID,ConnPointVec,GUID_less>	     ConnInfoMap;
typedef std::map<GUID,GUIDVec,GUID_less>		     GUIDVecMap;
typedef std::map<GUID,CComPtr<IMgaObject>,GUID_less> ObjMap;
typedef std::vector<CComPtr<IMgaObject> >			 ObjVec;


class Merge
{
protected:	
	CComPtr<IMgaProject> act_project;
	CComPtr<IMgaFolder>  act_root;

	CComPtr<IMgaProject> mergein_project;
	CComPtr<IMgaFolder>  mergein_root;

	TypeInfoMap			 type_info;
	RefInfoMap		     ref_info;
	ConnInfoMap		     conn_info;
	GUIDVecMap		     set_info;

public:
	Merge();
	~Merge();

	void doMerge( IMgaProject * act_proj, IMgaProject * mergein_proj );

protected:

	void test1();

	void checkParadigms();

	void checkRootFolders();

	void doMerge();

	void deleteObjects();

	void savePointers();

	void savePointers( CComPtr<IMgaObject> parent );

	void restoreTypes();

	void restoreReferences();

	void restoreConnections();

	void restoreSets();

	bool shouldFollowLink( CComPtr<IMgaFCO> fco );

	void mergeFolders( CComPtr<IMgaFolder> act, CComPtr<IMgaFolder> mergein );

	void mergeModels( CComPtr<IMgaModel> act, CComPtr<IMgaModel> mergein );

	CComPtr<IMgaFCO> copyFCO( CComPtr<IMgaFCO> src, CComPtr<IMgaModel> parent );

	CComPtr<IMgaFCO> copyFCO( CComPtr<IMgaFCO> src, CComPtr<IMgaFolder> parent );

	CComPtr<IMgaFolder> copyFolder( CComPtr<IMgaFolder> src, CComPtr<IMgaFolder> parent );

	//CComPtr<IMgaReference> copyRef( CComPtr<IMgaReference> src, CComPtr<IMgaModel> parent );

	void copyRegistry( CComPtr<IMgaFCO> src, CComPtr<IMgaFCO> dest );

	void copyRegistry( CComPtr<IMgaRegNodes> nodes, CComPtr<IMgaFCO> dest );

	void copyRegistry( CComPtr<IMgaRegNodes> nodes, CComPtr<IMgaFolder> dest );

	void copyAttribs( CComPtr<IMgaFCO> src, CComPtr<IMgaFCO> dest );	

	void copyAttribsAndRegistry( CComPtr<IMgaFCO>(src), CComPtr<IMgaFCO>(new_fco) );

	void copyFolderAttribs( CComPtr<IMgaFolder>(src), CComPtr<IMgaFolder>(new_folder) );

	// helper
	GUID				  getGuid( CComPtr<IMgaObject> o );

	CString				  formatGuid( GUID g );

	int					  getType( CComPtr<IMgaObject> o );

	CComPtr<IMgaFCO>      findFCO( CComPtr<IMgaModel> parent, GUID g );

	CComPtr<IMgaFCO>      findFCO( CComPtr<IMgaFolder> parent, GUID g );

	CComPtr<IMgaFCO>      findFCOInChildren( CComPtr<IMgaModel> parent, GUID g );

	CComPtr<IMgaFCO>      findFCOInChildren( CComPtr<IMgaFolder> parent, GUID g );

	CComPtr<IMgaFolder>   findFolder( CComPtr<IMgaFolder> parent, GUID g );

	CComPtr<IMgaFolder>	  findFolderInChildren( CComPtr<IMgaFolder> parent, GUID g );

	int					  getMerginClosureID();

	bool				  inClosure( CComPtr<IMgaObject> obj, int closureID );

	IntSet				  parseClosureString( const char * str );

	void				  addSubTreeToMap( CComPtr<IMgaObject> o, ObjMap& map );

	
	
};
