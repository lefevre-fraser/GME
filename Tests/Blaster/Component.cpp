#include "stdafx.h"
#include "Component.h"


//#define ID_BY_NAME	// identify objects by fully-qualified name instead of ID (stronger but slower)
#define RAND_ACTIONS 10	// number of actions possible in PerformRandomTesting switch statement

// all global variables

ofstream out;	// log file output stream
int depthLimit;
int saveFrequency;
BOOL useFQNames;
BOOL useExpCheckpoints;
BOOL useUIDs;
BOOL deleteWhenDone;
BOOL testBlast;
BOOL testTypesAndInstances;
BOOL testRandom;
int randCount;
int genPattern;

CString logFileName;
long uID;

CString pattFileName;
CString paradigms;

bool emailResults;
CStringList emailAddresses;

bool playback;
ofstream toPattFile;
ifstream fromPattFile;

CString lastLogEntry;

CBstr projName;

CComPtr<IMgaProject> proj;
CComPtr<IMgaTerritory> terr;

ComPtrList allFCOs_list;

// function implementations

void GetMGASortKey(IMgaObject *o, CBstr &key)
{
#ifdef ID_BY_NAME
	CString temp;
	GetNamePath(o,temp);
	key = temp;
#else
	COMVERIFY(o->get_ID((BSTR *) key));
#endif
}

void GetMGASortKey(IMgaAttribute *a, CBstr &key)
{
	CComPtr<IMgaMetaAttribute> meta_a;
	COMVERIFY(a->get_Meta(&meta_a));
	COMVERIFY(meta_a->get_Name((BSTR *) key));
}

// assuming unique names in the meta
void GetMGASortKey(IMgaMetaBase *mb, CBstr &key)
{
	COMVERIFY(mb->get_Name((BSTR *) key));
}

void GetMGASortKey(IMgaMetaEnumItem *mei, CBstr &key)
{
	COMVERIFY(mei->get_DisplayedName((BSTR *) key));
}

void GetMGASortKey(IMgaMetaPointerSpec *mps, CBstr &key)
{
	COMVERIFY(mps->get_Name((BSTR *) key));
}

void GetMGASortKey(IMgaMetaPointerItem *mpi, CBstr &key)
{
	COMVERIFY(mpi->get_Desc((BSTR *) key));
}
template<class PTR_TYPE>
void InsertIntoMGAObjectCollection(CComPtr<PTR_TYPE> ptr, ComPtrList &sList)
{
	sList.AddTail(ptr);
	ptr.p->AddRef();
}

template<class CYT_COLL, class CYT_COLL_TYPE>
void SortMGAObjectCollection(CComPtr<CYT_COLL> coll, ComPtrList &sList)
{
	MGACOLL_ITERATE(CYT_COLL_TYPE,coll) {
		CBstr iterID;
		GetMGASortKey(MGACOLL_ITER,iterID);		
		POSITION pos = sList.GetHeadPosition();
		if(!pos)
		{
			sList.AddTail(MGACOLL_ITER);
			MGACOLL_ITER.p->AddRef();
		}
		else
		{
			while(pos)
			{
				CComPtr<CYT_COLL_TYPE> currPtr = (CYT_COLL_TYPE *) sList.GetAt(pos);
				CBstr currID;
				GetMGASortKey(currPtr,currID);
				if ((CString) iterID > (CString) currID)
				{
					sList.InsertBefore(pos, MGACOLL_ITER);
					MGACOLL_ITER.p->AddRef();
					pos = NULL;
				}
				else
				{
					sList.GetNext(pos);
					if(pos == NULL)
					{
						sList.AddTail(MGACOLL_ITER);
						MGACOLL_ITER.p->AddRef();
					}
				}
			}
		}
	} MGACOLL_ITERATE_END
}

CString ltoCStr(long n)
{
	CString str;
	char *buf = str.GetBuffer(100);
	sprintf(buf, "%d", n);
	str.ReleaseBuffer();
	return str;
}

void AddIdentifier(CBstr& str)
{
	if(useUIDs)
	{
		str = str + ltoCStr(uID);
		uID++;
		if(uID == 0)
		{
			LogWrite("Warning: Unique ID counter has rolled over");
		}
	}
}

void GetExtendedName(CComPtr<IMgaObject> object, CString &extName,CString separator,bool startWithRoot)
{
	CBstr nametemp;

	if(!startWithRoot)
	{
		COMVERIFY(object->get_Name((BSTR *) nametemp));
		extName += (CString) nametemp;
	}
	
	CComPtr<IMgaObject> parent;
	if(!SUCCEEDED(object->GetParent(&parent)))
		parent = NULL;

	if(parent) {
		if(!startWithRoot)
			extName += separator;
		GetExtendedName(parent, extName,separator,startWithRoot);
		if(startWithRoot)
			extName += separator;
	}
	if(startWithRoot)
	{
		COMVERIFY(object->get_Name((BSTR *) nametemp));
		extName += (CString) nametemp;
	}
}

void GetNamePath(CComPtr<IMgaReference> ref, CBstr &namepath)
{
	CString c_namepath;
	CComPtr<IMgaObject> obj;
	COMVERIFY(ref.QueryInterface(&obj));
	GetNamePath(obj,c_namepath);
	namepath = c_namepath;
}

void GetNamePath(CComPtr<IMgaFCO> fco, CBstr &namepath)
{
	CString c_namepath;
	CComPtr<IMgaObject> obj;
	COMVERIFY(fco.QueryInterface(&obj));
	GetNamePath(obj,c_namepath);
	namepath = c_namepath;
}

void GetNamePath(CComPtr<IMgaSet> set, CBstr &namepath)
{
	CString c_namepath;
	CComPtr<IMgaObject> obj;
	COMVERIFY(set.QueryInterface(&obj));
	GetNamePath(obj,c_namepath);
	namepath = c_namepath;
}

void GetNamePath(CComPtr<IMgaModel> mod, CBstr &namepath)
{
	CString c_namepath;
	CComPtr<IMgaObject> obj;
	COMVERIFY(mod.QueryInterface(&obj));
	GetNamePath(obj,c_namepath);
	namepath = c_namepath;
}

void GetNamePath(CComPtr<IMgaFolder> fdr, CBstr &namepath)
{
	CString c_namepath;
	CComPtr<IMgaObject> obj;
	COMVERIFY(fdr.QueryInterface(&obj));
	GetNamePath(obj,c_namepath);
	namepath = c_namepath;
}

void GetNamePath(CComPtr<IMgaObject> object,CString &namePath)
{
	if(useFQNames)
	{
		GetExtendedName(object, namePath,":",true);
	}
	else
	{
		CBstr shortName;
		COMVERIFY(object->get_Name((BSTR *) shortName));
		namePath = shortName;
	}
}

void wipeList(CMetaObjList &objlist)	// deletes contents of a CMetaObjList
{
	POSITION pos = objlist.GetHeadPosition();
	while(pos)
	{
		delete(objlist.GetNext(pos));
	}
	objlist.RemoveAll();
}

void LogWrite(CString text)	// writes text plus timestamp to the log file
{
	// keep a copy of the most recent log entry for error reporting
	lastLogEntry = text;
	
	// make timestamp
	static int saveCount = 0;
	CTime currTime = CTime::GetCurrentTime();
	CString timeStr = currTime.Format("%m/%d/%y %H:%M:%S - ");

	saveCount++;

	if(saveCount == saveFrequency)
	{
		COMVERIFY(proj->CommitTransaction());
//		terr = NULL;
//		COMVERIFY(proj->CreateTerritory(NULL, &terr));
		COMVERIFY(proj->BeginTransaction(terr));
		// if using explicit checkpoints, create one
		if(useExpCheckpoints)
		{
			out << "<checkpoint>" << endl;
		}
		// close file and reopen in append mode
		out.close();
		out.open(logFileName,ios::out | ios::app);
		if(toPattFile.is_open())
		{
			toPattFile.close();
			toPattFile.open(pattFileName,ios::out | ios::app);
		}
		// reset saveCount
		saveCount = 0;
	}

	// write to log
	out << timeStr << text << endl;

}

// entry point
void CComponent::Invoke(IMgaProject *gme, IMgaFCOs *psa, long param)
{
//	AfxMessageBox("Blaster start", MB_OK | MB_ICONINFORMATION);
	cout << "Blaster start";
	
	// seed random number generator
	srand( (unsigned)time( NULL ) );

	proj = gme;

	COMVERIFY(proj->get_ActiveTerritory(&terr));

	{
		uID = 0;
		ReadConfigFile();
		out.open(logFileName);	// open new log file
		out.flags(out.flags() | ios::unitbuf);

		// get pointer to rootfolder
		CComPtr<IMgaFolder> rootf;
		COMVERIFY(proj->get_RootFolder(&rootf));

		if(testBlast)
		{
			// start blasting
			BlastProject(proj);
		}

		if(testRandom)
		{
			if(genPattern == 0)
			{
				toPattFile.open(pattFileName);
				toPattFile.flags(toPattFile.flags() | ios::unitbuf);
				playback = false;
			}
			else
			{
				fromPattFile.open(pattFileName);
				playback = true;
			}

			PerformRandomTesting(randCount);
		}

		if(deleteWhenDone)
		{
			// get and delete all child folders
			CComPtr<IMgaFolders> child_folders;
			COMVERIFY(rootf->get_ChildFolders(&child_folders));
			ComPtrList child_folders_list;
			SortMGAObjectCollection<IMgaFolders,IMgaFolder>(child_folders,child_folders_list);
			POSITION cflPos = child_folders_list.GetHeadPosition();
			while(cflPos)
			{
				CComPtr<IUnknown> iter_obj = child_folders_list.GetNext(cflPos);
				CComPtr<IMgaFolder> iter;
				COMVERIFY(iter_obj.QueryInterface(&iter));
				DeleteSelfAndAllDescendants(iter);
			}

			// get and delete all child FCOs
			CComPtr<IMgaFCOs> child_fcos;
			COMVERIFY(rootf->get_ChildFCOs(&child_fcos));

			ComPtrList child_fcos_list;
			SortMGAObjectCollection<IMgaFCOs,IMgaFCO>(child_fcos,child_fcos_list);
			POSITION pos = child_fcos_list.GetHeadPosition();
			while(pos)
			{
				CComPtr<IUnknown> iter_obj = child_fcos_list.GetNext(pos);
				CComPtr<IMgaFCO> iter;
				COMVERIFY(iter_obj.QueryInterface(&iter));
				DeleteSelfAndAllDescendants(iter);
			}
		}

		// if using explicit checkpoints, create one
		if(useExpCheckpoints)
		{
			out << "<checkpoint>" << endl;
		}
		out.close();	// close log file
		if(!playback)
			toPattFile.close();
		else
			fromPattFile.close();
	}

//	AfxMessageBox("Blaster stop", MB_OK | MB_ICONINFORMATION);
	cout << "Blaster stop";
	SendMail("Blaster completed without errors.");
	proj.Release();
	terr.Release();
}

CString CMetaObj::GetName()	// get name of a meta object
{
	CBstr name;
	COMVERIFY(obj->get_Name(name));
	return name;
}

void CMetaFolder::GetFolders(CMetaObjList &fdrlist)	// get child metafolders of a metafolder
{
	CComPtr<IMgaMetaFolders> folderkids;
	COMVERIFY(fdr->get_LegalChildFolders(&folderkids));
	
	ComPtrList folderkids_list;
	SortMGAObjectCollection<IMgaMetaFolders,IMgaMetaFolder>(folderkids,folderkids_list);
	POSITION pos = folderkids_list.GetHeadPosition();
	while(pos)
	{
		CComPtr<IUnknown> iter_obj = folderkids_list.GetNext(pos);
		CComPtr<IMgaMetaFolder> iter;
		COMVERIFY(iter_obj.QueryInterface(&iter));
		CMetaFolder *newFdr = new CMetaFolder(iter);
		fdrlist.AddTail(newFdr);

	}

}

void CMetaFolder::GetFCOs(CMetaObjList &fcolist)	// get child metafco's of a metafolder
{
	CComPtr<IMgaMetaFCOs> fcokids;
	COMVERIFY(fdr->get_LegalRootObjects(&fcokids));

	ComPtrList fcokids_list;
	SortMGAObjectCollection<IMgaMetaFCOs,IMgaMetaFCO>(fcokids,fcokids_list);
	POSITION pos = fcokids_list.GetHeadPosition();
	while(pos)
	{
		CComPtr<IUnknown> iter_obj = fcokids_list.GetNext(pos);
		CComPtr<IMgaMetaFCO> iter;
		COMVERIFY(iter_obj.QueryInterface(&iter));
		CMetaFCO *newFCO = new CMetaFCO(iter);
		fcolist.AddTail(newFCO);
	}
}

void CMetaFCO::GetRoles(CMetaObjList &list)		// get child metafco's of a metafco
{
	CComPtr<IMgaMetaModel> mod;
	fco.QueryInterface(&mod);
	CComPtr<IMgaMetaRoles> rolekids;
	COMVERIFY(mod->get_Roles(&rolekids));

	ComPtrList rolekids_list;
	SortMGAObjectCollection<IMgaMetaRoles,IMgaMetaRole>(rolekids,rolekids_list);
	POSITION pos = rolekids_list.GetHeadPosition();
	while(pos)
	{
		CComPtr<IUnknown> iter_obj = rolekids_list.GetNext(pos);
		CComPtr<IMgaMetaRole> iter;
		COMVERIFY(iter_obj.QueryInterface(&iter));
		CMetaRole *newRole = new CMetaRole(iter);
		list.AddTail(newRole);
	}
}

void CMetaReference::GetTargetRoles(CMetaObjList &list, CComPtr<IMgaModel> mod)
{
	CComPtr<IMgaMetaPointerSpec> spec;
	COMVERIFY(ref->get_RefSpec(&spec));

	CComPtr<IMgaMetaPointerItems> target_items;
	COMVERIFY(spec->get_Items(&target_items));

	CComPtr<IMgaMetaModel> meta_mod;
	CComPtr<IMgaMetaFCO> meta_fco;
	COMVERIFY(mod->get_Meta(&meta_fco));
	COMVERIFY(meta_fco.QueryInterface(&meta_mod));

	ComPtrList target_items_list;
	SortMGAObjectCollection<IMgaMetaPointerItems,IMgaMetaPointerItem>(target_items,target_items_list);
	POSITION pos = target_items_list.GetHeadPosition();
	while(pos)
	{
		CComPtr<IUnknown> iter_obj = target_items_list.GetNext(pos);
		CComPtr<IMgaMetaPointerItem> currItem;
		COMVERIFY(iter_obj.QueryInterface(&currItem));

		CBstr target_str;
		COMVERIFY(currItem->get_Desc((BSTR *) target_str));
		// now need to look it up by name
		CComPtr<IMgaMetaRole> role;
		HRESULT hr = meta_mod->get_RoleByName(target_str.Send(),&role);
		if(hr == S_OK)
		{
			CMetaRole *newRole = new CMetaRole(role);
			list.AddTail(newRole);
		}
	}
}

void CMetaReference::GetTargetKinds(CMetaObjList &list)
{
	// returns list of CMetaFCOs
	CComPtr<IMgaMetaPointerSpec> spec;
	COMVERIFY(ref->get_RefSpec(&spec));

	CComPtr<IMgaMetaPointerItems> target_items;
	COMVERIFY(spec->get_Items(&target_items));

	CComPtr<IMgaMetaProject> meta_proj;
	COMVERIFY(ref->get_MetaProject(&meta_proj));
	CComPtr<IMgaMetaFolder> meta_rootf;
	COMVERIFY(meta_proj->get_RootFolder(&meta_rootf));

	ComPtrList target_items_list;
	SortMGAObjectCollection<IMgaMetaPointerItems,IMgaMetaPointerItem>(target_items,target_items_list);
	POSITION pos = target_items_list.GetHeadPosition();
	while(pos)
	{
		CComPtr<IUnknown> iter_obj = target_items_list.GetNext(pos);
		CComPtr<IMgaMetaPointerItem> currItem;
		COMVERIFY(iter_obj.QueryInterface(&currItem));

		CBstr target_str;
		COMVERIFY(currItem->get_Desc((BSTR *) target_str));

		// now look for it in metarootfolder
		CComPtr<IMgaMetaFCO> meta_target;
		COMVERIFY(meta_rootf->get_DefinedFCOByName(target_str.Send(), true, &meta_target));

		CMetaFCO *wrap_meta_target = new CMetaFCO(meta_target);
		list.AddTail(wrap_meta_target);

	}

}

void CMetaSet::GetMemberRoles(CMetaObjList &list, CMetaRole *setRole)
{
	CComPtr<IMgaMetaPointerSpec> spec;
	COMVERIFY(set->get_MemberSpec(&spec));

	CComPtr<IMgaMetaPointerItems> member_items;
	COMVERIFY(spec->get_Items(&member_items));

	ComPtrList member_items_list;
	SortMGAObjectCollection<IMgaMetaPointerItems,IMgaMetaPointerItem>(member_items,member_items_list);
	POSITION pos = member_items_list.GetHeadPosition();
	while(pos)
	{
		CComPtr<IUnknown> iter_obj = member_items_list.GetNext(pos);
		CComPtr<IMgaMetaPointerItem> currItem;
		COMVERIFY(iter_obj.QueryInterface(&currItem));

		CBstr member_str;
		COMVERIFY(currItem->get_Desc((BSTR *) member_str));
		// now need to look it up by name
		CComPtr<IMgaMetaModel> parentModel;
		COMVERIFY(setRole->GetCOM()->get_ParentModel(&parentModel));
		CComPtr<IMgaMetaRole> role;
		COMVERIFY(parentModel->get_RoleByName(member_str.Send(),&role));
		CMetaRole *newRole = new CMetaRole(role);
		list.AddTail(newRole);

	}
}

void CMetaObj::GetAttributes(CMetaObjList &attlist)	// get metaAttributes of a metaobject
{
	CComPtr<IMgaMetaFCO> fco;
	obj.QueryInterface(&fco);
	if(fco)
	{
		
		CComPtr<IMgaMetaAttributes> attrs;
		COMVERIFY(fco->get_Attributes(&attrs));

		ComPtrList attrs_list;
		SortMGAObjectCollection<IMgaMetaAttributes,IMgaMetaAttribute>(attrs,attrs_list);
		POSITION cflPos = attrs_list.GetHeadPosition();
		while(cflPos)
		{
			CComPtr<IUnknown> iter_obj = attrs_list.GetNext(cflPos);
			CComPtr<IMgaMetaAttribute> iter;
			COMVERIFY(iter_obj.QueryInterface(&iter));
			CMetaAttribute *newAttr = new CMetaAttribute(iter);
			attlist.AddTail(newAttr);
		}
	}
}

void SetAllAttributes(CComPtr<IMgaFCO> fco)		// set all fco attributes to test values
{
	CBstr fco_name;
	GetNamePath(fco,fco_name);

	// get the metaAttributes from the metafco
	CComPtr<IMgaMetaFCO> meta_fco;
	COMVERIFY(fco->get_Meta(&meta_fco));
	CMetaFCO wrap_meta_fco(meta_fco);
	CMetaObjList attlist;
	wrap_meta_fco.GetAttributes(attlist);
	POSITION attPos = attlist.GetHeadPosition();
	while(attPos)
	{
		// get each attribute
		CMetaAttribute *currAttr = (CMetaAttribute *) attlist.GetNext(attPos);

		LogWrite("Setting attribute " + currAttr->GetName() + " in FCO " + fco_name);

		attval_enum attrType;
		COMVERIFY(currAttr->GetCOM()->get_ValueType(&attrType));
		CComPtr<IMgaAttribute> fco_attr;
		COMVERIFY(fco->get_Attribute(currAttr->GetCOM(), &fco_attr));

		CBstr strVal = "test value";
		long intVal = 1234567;
		double dbVal = 3.141592654;
		bool boolVal = true;
		CComPtr<IMgaMetaEnumItems> enum_vals;
		ComPtrList enum_vals_list;
		POSITION cflPos;

		// based on attribute type, fill with appropriate test value
		switch(attrType)
		{

		case ATTVAL_STRING:
			COMVERIFY(fco_attr->put_StringValue(strVal.Send()));
			break;
		case ATTVAL_INTEGER:
			COMVERIFY(fco_attr->put_IntValue(intVal));
			break;
		case ATTVAL_DOUBLE:
			COMVERIFY(fco_attr->put_FloatValue(dbVal));
			break;
		case ATTVAL_BOOLEAN:
			COMVERIFY(fco_attr->put_BoolValue(boolVal));
			break;
		case ATTVAL_ENUM:
			// need to get enum items from meta
			COMVERIFY(currAttr->GetCOM()->get_EnumItems(&enum_vals));
			// set for each one - will leave as the last one

			SortMGAObjectCollection<IMgaMetaEnumItems,IMgaMetaEnumItem>(enum_vals,enum_vals_list);
			cflPos = enum_vals_list.GetHeadPosition();
			while(cflPos)
			{
				CComPtr<IUnknown> iter_obj = enum_vals_list.GetNext(cflPos);
				CComPtr<IMgaMetaEnumItem> iter;
				COMVERIFY(iter_obj.QueryInterface(&iter));
				CBstr currEnumVal;
				COMVERIFY(iter->get_Value((BSTR *) currEnumVal));
				COMVERIFY(fco_attr->put_StringValue(currEnumVal.Send()));
			}
			break;
		default:	// write unsupported attr type to log
			LogWrite("ERROR - Unsupported attribute type.");
			break;

		}
	}
	wipeList(attlist);

}

void CreateAllPossibleFolders(CComPtr<IMgaFolder> fdr)	// create all possible folders in fdr
{
	CBstr parentName;
	GetNamePath(fdr,parentName);
	
	CComPtr<IMgaMetaFolder> meta_fdr;
	COMVERIFY(fdr->get_MetaFolder(&meta_fdr));
	CMetaFolder wrap_meta_fdr(meta_fdr);
	CMetaObjList meta_childFdrs;
	wrap_meta_fdr.GetFolders(meta_childFdrs);
	POSITION childPos = meta_childFdrs.GetHeadPosition();
	while(childPos)
	{
		CMetaFolder *currMFdr = (CMetaFolder *) meta_childFdrs.GetNext(childPos);
		CComPtr<IMgaFolder> newFdr;
		CBstr name = currMFdr->GetName();
		AddIdentifier(name);
		LogWrite("Creating a " + currMFdr->GetName() + " folder named " + name + " in folder " + parentName);
		COMVERIFY(fdr->CreateFolder(currMFdr->GetCOM(),&newFdr));
		COMVERIFY(newFdr->put_Name(name.Send()));
	}

	wipeList(meta_childFdrs);
}
void CreateAllPossibleFCOs(CComPtr<IMgaFolder> fdr)	// create all possible fco's in fdr
{
	CBstr parentName;
	GetNamePath(fdr,parentName);

	CComPtr<IMgaMetaFolder> meta_fdr;
	COMVERIFY(fdr->get_MetaFolder(&meta_fdr));
	CMetaFolder wrap_meta_fdr(meta_fdr);
	CMetaObjList meta_childFCOs;
	wrap_meta_fdr.GetFCOs(meta_childFCOs);
	POSITION childPos = meta_childFCOs.GetHeadPosition();
	while(childPos)
	{
		CMetaFCO *currMFCO = (CMetaFCO *) meta_childFCOs.GetNext(childPos);
		CComPtr<IMgaFCO> newFCO;
		CBstr name = currMFCO->GetName();
		AddIdentifier(name);
		LogWrite("Creating a " + currMFCO->GetName() + " FCO named " + name + " in folder " + parentName);
		COMVERIFY(fdr->CreateRootObject(currMFCO->GetCOM(),&newFCO));
		COMVERIFY(newFCO->put_Name(name.Send()));
	}

	wipeList(meta_childFCOs);

}

void DeleteSelfAndAllDescendants(CComPtr<IMgaFolder> fdr)
{
	CBstr thisName;
	GetNamePath(fdr,thisName);

	// get and delete all child folders
	CComPtr<IMgaFolders> child_folders;
	COMVERIFY(fdr->get_ChildFolders(&child_folders));

	ComPtrList child_folders_list;
	SortMGAObjectCollection<IMgaFolders,IMgaFolder>(child_folders,child_folders_list);
	POSITION cflPos = child_folders_list.GetHeadPosition();
	while(cflPos)
	{
		CComPtr<IUnknown> iter_obj = child_folders_list.GetNext(cflPos);
		CComPtr<IMgaFolder> iter;
		COMVERIFY(iter_obj.QueryInterface(&iter));
		DeleteSelfAndAllDescendants(iter);
	}

	// get and delete all child FCOs
	CComPtr<IMgaFCOs> child_fcos;
	COMVERIFY(fdr->get_ChildFCOs(&child_fcos));

	ComPtrList child_fcos_list;
	SortMGAObjectCollection<IMgaFCOs,IMgaFCO>(child_fcos,child_fcos_list);
	POSITION pos = child_fcos_list.GetHeadPosition();
	while(pos)
	{
		CComPtr<IUnknown> iter = child_fcos_list.GetNext(pos);
		CComPtr<IMgaFCO> iter_fco;
		COMVERIFY(iter.QueryInterface(&iter_fco));
		DeleteSelfAndAllDescendants(iter_fco);
	}

	// delete self, making sure self has not already been deleted
	long obj_status;
	COMVERIFY(fdr->get_Status(&obj_status));
	if(obj_status == OBJECT_EXISTS)
	{
		LogWrite("Deleting object " + thisName);
		COMVERIFY(fdr->DestroyObject());
	}
	else
	{
		LogWrite("Attempted to delete object " + thisName + " , but it has already been deleted.");
	}
}

void CreateAllPossibleFCOs(CComPtr<IMgaModel> mod)	// create all possible fco's in mod
{
	CBstr parentName;
	GetNamePath(mod,parentName);

	VARIANT_BOOL isInstance;
	COMVERIFY(mod->get_IsInstance(&isInstance));
	if(!isInstance)
	{
		CComPtr<IMgaMetaFCO> meta_fco;
		COMVERIFY(mod->get_Meta(&meta_fco));
		CMetaFCO wrap_meta_mod(meta_fco);
		CMetaObjList meta_childRoles;
		wrap_meta_mod.GetRoles(meta_childRoles);
		POSITION childPos = meta_childRoles.GetHeadPosition();
		while(childPos)
		{
			CMetaRole *currMRole = (CMetaRole *) meta_childRoles.GetNext(childPos);
			objtype_enum oType;
			CComPtr<IMgaMetaFCO> kind;
			COMVERIFY(currMRole->GetCOM()->get_Kind(&kind));
			COMVERIFY(kind->get_ObjType(&oType));
			if(oType != OBJTYPE_CONNECTION)
			{
				CComPtr<IMgaFCO> newFCO;
				CBstr name = currMRole->GetName();
				AddIdentifier(name);
				LogWrite("Creating a " + currMRole->GetName() + " FCO named " + name + " in model " + parentName);
				COMVERIFY(mod->CreateChildObject(currMRole->GetCOM(),&newFCO));
				COMVERIFY(newFCO->put_Name(name.Send()));
			}
			else
			{
				CreateConnections(currMRole,mod);
			}
		}

		wipeList(meta_childRoles);
	}
}

void DeleteSelfAndAllDescendants(CComPtr<IMgaFCO> fco)
{
	long obj_status;
	COMVERIFY(fco->get_Status(&obj_status));

	CBstr myName;
	if(obj_status == OBJECT_EXISTS)
	{
		GetNamePath(fco,myName);
	}
	else
	{
		COMVERIFY(fco->get_Name((BSTR *) myName));
	}
	CComPtr<IMgaFCO> archetype;
	COMVERIFY(fco->get_ArcheType(&archetype));
	if(!archetype)
	{
		// get and delete all child FCOs
		CComPtr<IMgaModel> mod;
		fco.QueryInterface(&mod);
		if(mod)
		{
			CComPtr<IMgaFCOs> child_fcos;
			COMVERIFY(mod->get_ChildFCOs(&child_fcos));

			ComPtrList child_fcos_list;
			SortMGAObjectCollection<IMgaFCOs,IMgaFCO>(child_fcos,child_fcos_list);
			POSITION pos = child_fcos_list.GetHeadPosition();
			while(pos)
			{
				CComPtr<IUnknown> iter = child_fcos_list.GetNext(pos);
				CComPtr<IMgaFCO> iter_fco;
				COMVERIFY(iter.QueryInterface(&iter_fco));
				DeleteSelfAndAllDescendants(iter_fco);
			}
		}
	}

	// delete self, making sure self has not already been deleted
	if(obj_status == OBJECT_EXISTS)
	{
		LogWrite("Deleting object " + myName);
		COMVERIFY(fco->DestroyObject());
	}
	else
	{
		LogWrite("Attempted to delete object " + myName + " , but it has already been deleted.");
	}

}

// create all possible connections with role in mod
void CreateConnections(CMetaRole *role,CComPtr<IMgaModel> mod)	
{
	CBstr src_str = "src";
	CBstr dst_str = "dst";
	
	CBstr mod_name;
	GetNamePath(mod,mod_name);

	CComPtr<IMgaMetaModel> meta_mod;
	CComPtr<IMgaMetaFCO> meta_fco;
	COMVERIFY(mod->get_Meta(&meta_fco));
	COMVERIFY(meta_fco.QueryInterface(&meta_mod));

	CComPtr<IMgaMetaFCO> kind;
	COMVERIFY(role->GetCOM()->get_Kind(&kind));
	CComPtr<IMgaMetaConnection> meta_conn;
	COMVERIFY(kind.QueryInterface(&meta_conn));
	CComPtr<IMgaMetaConnJoints> joints;
	COMVERIFY(meta_conn->get_Joints(&joints));

	// can't sort metaconnjoints!!!
	MGACOLL_ITERATE(IMgaMetaConnJoint,joints) {
		CComPtr<IMgaMetaConnJoint> currJoint = MGACOLL_ITER;
		CComPtr<IMgaMetaPointerSpec> src_spec;
		CComPtr<IMgaMetaPointerSpec> dst_spec;
		COMVERIFY(currJoint->get_PointerSpecByName(src_str.Send(), &src_spec));
		COMVERIFY(currJoint->get_PointerSpecByName(dst_str.Send(), &dst_spec));

		CComPtr<IMgaMetaPointerItems> src_items;
		COMVERIFY(src_spec->get_Items(&src_items));
		CComPtr<IMgaMetaPointerItems> dst_items;
		COMVERIFY(dst_spec->get_Items(&dst_items));

		ComPtrList src_items_list;
		SortMGAObjectCollection<IMgaMetaPointerItems,IMgaMetaPointerItem>(src_items,src_items_list);
		POSITION pos = src_items_list.GetHeadPosition();
		while(pos)
		{
			CComPtr<IUnknown> iter_obj = src_items_list.GetNext(pos);
			CComPtr<IMgaMetaPointerItem> currSrcItem;
			COMVERIFY(iter_obj.QueryInterface(&currSrcItem));

			CBstr currSrcDesc;
			COMVERIFY(currSrcItem->get_Desc((BSTR *) currSrcDesc));
			CStringList srcRoles;
//			ParseRoleString(currSrcDesc,srcRoles);
			ParseDelimitedString(currSrcDesc,srcRoles,' ');
			CBstr firstSrcRole_str = srcRoles.RemoveHead();
			CComPtr<IMgaMetaRole> firstSrcRole;
			HRESULT hr = meta_mod->get_RoleByName(firstSrcRole_str.Send(),&firstSrcRole);
			if(hr == S_OK)
			{
				CComPtr<IMgaMetaFCO> firstSrcKind;
				COMVERIFY(firstSrcRole->get_Kind(&firstSrcKind));
				objtype_enum firstSrcType;
				COMVERIFY(firstSrcKind->get_ObjType(&firstSrcType));
				if(firstSrcType == OBJTYPE_MODEL && (srcRoles.GetCount() > 0))
				{
					CComPtr<IMgaFCO> srcPortHolder;
					CComPtr<IMgaModel> srcPortHolder_mod;

					CBstr srcPortHolder_name;
					COMVERIFY(firstSrcRole->get_Name((BSTR *) srcPortHolder_name));
					AddIdentifier(srcPortHolder_name);

					LogWrite("Creating FCO " + srcPortHolder_name + " in model " + mod_name);
					COMVERIFY(mod->CreateChildObject(firstSrcRole,&srcPortHolder));
					COMVERIFY(srcPortHolder.QueryInterface(&srcPortHolder_mod));
					COMVERIFY(srcPortHolder->put_Name(srcPortHolder_name.Send()));
					
					CComPtr<IMgaMetaFCO> meta_srcPortHolder;
					COMVERIFY(srcPortHolder->get_Meta(&meta_srcPortHolder));
					CComPtr<IMgaMetaModel> meta_srcPortHolder_mod;
					COMVERIFY(meta_srcPortHolder.QueryInterface(&meta_srcPortHolder_mod));
					CBstr secondSrcRole_str = srcRoles.RemoveHead();
					CComPtr<IMgaMetaRole> secondSrcRole;
					COMVERIFY(meta_srcPortHolder_mod->get_RoleByName(secondSrcRole_str.Send(),&secondSrcRole));
					CComPtr<IMgaMetaFCO> secondSrcKind;
					COMVERIFY(secondSrcRole->get_Kind(&secondSrcKind));

					ConnectToAllPossibleDsts(role,mod,srcPortHolder_mod,secondSrcRole,NULL,dst_items);
				}
				else if(firstSrcType == OBJTYPE_REFERENCE && (srcRoles.GetCount() > 0))
				{
					CComPtr<IMgaMetaFCO> meta_ref_fco;
					COMVERIFY(firstSrcRole->get_Kind(&meta_ref_fco));
					CComPtr<IMgaMetaReference> meta_ref;
					COMVERIFY(meta_ref_fco.QueryInterface(&meta_ref));
					CMetaReference wrap_meta_ref(meta_ref);
					CMetaObjList target_kinds;
					wrap_meta_ref.GetTargetKinds(target_kinds);

					POSITION kindPos = target_kinds.GetHeadPosition();
					while(kindPos)
					{
						CMetaFCO *currKind = (CMetaFCO *) target_kinds.GetNext(kindPos);
						objtype_enum kindType;
						COMVERIFY(currKind->GetCOM()->get_ObjType(&kindType));
						if(kindType == OBJTYPE_MODEL)
						{
							CComPtr<IMgaFCO> remoteFCO;
							CComPtr<IMgaModel> remoteModel;
							CComPtr<IMgaMetaFCO> meta_remoteModel_fco;
							CComPtr<IMgaMetaModel> meta_remoteModel;
							CBstr remoteModel_name;

							// get remoteModel
							GetFirstFCOOfKind(currKind,remoteFCO);
							if(!remoteFCO)
							{
								CreateRandomFCO(currKind,remoteFCO);
							}

							COMVERIFY(remoteFCO.QueryInterface(&remoteModel));
							GetNamePath(remoteModel,remoteModel_name);
							COMVERIFY(remoteModel->get_Meta(&meta_remoteModel_fco));
							COMVERIFY(meta_remoteModel_fco.QueryInterface(&meta_remoteModel));
							// create a reference to act for the source
							CComPtr<IMgaFCO> srcRef;

							CBstr srcRef_name;
							COMVERIFY(firstSrcRole->get_Name((BSTR *) srcRef_name));
							AddIdentifier(srcRef_name);

							LogWrite("Creating reference " + srcRef_name + " in model " + mod_name);
							COMVERIFY(mod->CreateChildObject(firstSrcRole,&srcRef));
							COMVERIFY(srcRef->put_Name(srcRef_name.Send()));

							// direct the reference to the source
							srcRef_name = "";
							GetNamePath(srcRef,srcRef_name);
							LogWrite("Directing reference " + srcRef_name + " to model " + remoteModel_name);
							CComPtr<IMgaReference> srcRef_ref;
							COMVERIFY(srcRef.QueryInterface(&srcRef_ref));
							COMVERIFY(srcRef_ref->put_Referred(remoteModel));

							// find port role in remoteModel
							// look at second pointerspec item
							CBstr secondSrcRole_str = srcRoles.GetHead();
							CComPtr<IMgaMetaRole> secondSrcRole;
							HRESULT hr = meta_remoteModel->get_RoleByName(secondSrcRole_str.Send(),&secondSrcRole);
							if(hr == S_OK)
							{
								// create that role in the model
								// get the refport for it and use that as the conn src
								// refports are no longer in the IDL, so try directly using remotePort
								ConnectToAllPossibleDsts(role,mod,remoteModel,secondSrcRole,srcRef,dst_items);
							}
							else if(hr == 0x80731007)
							{
								// do nothing
							}
							else
							{
								// handle error
								COMVERIFY(hr);
							}

						}
					}
					wipeList(target_kinds);
				}
				else
				{
					ConnectToAllPossibleDsts(role,mod,mod,firstSrcRole,NULL,dst_items);
				}
			}
			else if(hr == 0x80731007)
			{
				// not found, do nothing
			}
			else
			{
				COMVERIFY(hr);
			}

		}

	} MGACOLL_ITERATE_END
}

void ConnectToAllPossibleDsts(CMetaRole *role, CComPtr<IMgaModel> conn_mod, CComPtr<IMgaModel> src_mod, CComPtr<IMgaMetaRole> srcRole, CComPtr<IMgaFCO> src_ref, CComPtr<IMgaMetaPointerItems> dst_items)
{
	CComPtr<IMgaMetaModel> meta_mod;
	CComPtr<IMgaMetaFCO> meta_fco;
	COMVERIFY(conn_mod->get_Meta(&meta_fco));
	COMVERIFY(meta_fco.QueryInterface(&meta_mod));

	CBstr parentName;
	GetNamePath(conn_mod,parentName);

	CBstr src_mod_name;
	GetNamePath(src_mod,src_mod_name);

	CComPtr<IMgaFCOs> srcRefs;

	if(src_ref)
	{
		COMVERIFY(srcRefs.CoCreateInstance(OLESTR("Mga.MgaFCOs")));
		COMVERIFY(srcRefs->Append(src_ref));
	}

	CBstr srcFCO_name;
	COMVERIFY(srcRole->get_Name((BSTR *) srcFCO_name));
	AddIdentifier(srcFCO_name);

	CComPtr<IMgaFCO> srcFCO;
	LogWrite("Creating FCO " + srcFCO_name + " in model " + src_mod_name);
	COMVERIFY(src_mod->CreateChildObject(srcRole,&srcFCO));
	COMVERIFY(srcFCO->put_Name(srcFCO_name.Send()));

	// now go find a dst!!!
	ComPtrList dst_items_list;
	SortMGAObjectCollection<IMgaMetaPointerItems,IMgaMetaPointerItem>(dst_items,dst_items_list);
	POSITION pos = dst_items_list.GetHeadPosition();
	while(pos)
	{
		CComPtr<IUnknown> iter_obj = dst_items_list.GetNext(pos);
		CComPtr<IMgaMetaPointerItem> currDstItem;
		COMVERIFY(iter_obj.QueryInterface(&currDstItem));

		CBstr currDstDesc;
		COMVERIFY(currDstItem->get_Desc((BSTR *) currDstDesc));
		CStringList dstRoles;
//		ParseRoleString(currDstDesc,dstRoles);
		ParseDelimitedString(currDstDesc,dstRoles,' ');
		CBstr firstDstRole_str = dstRoles.RemoveHead();
		CComPtr<IMgaMetaRole> firstDstRole;
		HRESULT hr = meta_mod->get_RoleByName(firstDstRole_str.Send(),&firstDstRole);
		if(hr == S_OK)
		{
			CComPtr<IMgaMetaFCO> firstDstKind;
			COMVERIFY(firstDstRole->get_Kind(&firstDstKind));
			objtype_enum firstDstType;
			COMVERIFY(firstDstKind->get_ObjType(&firstDstType));
			if(firstDstType == OBJTYPE_MODEL && (dstRoles.GetCount() > 0))
			{
				CComPtr<IMgaFCO> dstPortHolder;
				CComPtr<IMgaModel> dstPortHolder_mod;

				CBstr dstPortHolder_name;
				COMVERIFY(firstDstRole->get_Name((BSTR *) dstPortHolder_name));
				AddIdentifier(dstPortHolder_name);

				LogWrite("Creating FCO " + dstPortHolder_name + " in model " + parentName);
				COMVERIFY(conn_mod->CreateChildObject(firstDstRole,&dstPortHolder));
				COMVERIFY(dstPortHolder.QueryInterface(&dstPortHolder_mod));
				COMVERIFY(dstPortHolder->put_Name(dstPortHolder_name.Send()));
				
				CComPtr<IMgaMetaFCO> meta_dstPortHolder;
				COMVERIFY(dstPortHolder->get_Meta(&meta_dstPortHolder));
				CComPtr<IMgaMetaModel> meta_dstPortHolder_mod;
				COMVERIFY(meta_dstPortHolder.QueryInterface(&meta_dstPortHolder_mod));
				CBstr secondDstRole_str = dstRoles.GetHead();
				CComPtr<IMgaMetaRole> secondDstRole;
				COMVERIFY(meta_dstPortHolder_mod->get_RoleByName(secondDstRole_str.Send(),&secondDstRole));
				CComPtr<IMgaMetaFCO> secondDstKind;
				COMVERIFY(secondDstRole->get_Kind(&secondDstKind));

				CComPtr<IMgaFCO> dstFCO;

				CBstr dstFCO_name;
				COMVERIFY(secondDstRole->get_Name((BSTR *) dstFCO_name));
				AddIdentifier(dstFCO_name);

				CBstr dstPortHolder_mod_name;
				GetNamePath(dstPortHolder_mod,dstPortHolder_mod_name);
				LogWrite("Creating FCO " + dstFCO_name + " in model " + dstPortHolder_mod_name);
				COMVERIFY(dstPortHolder_mod->CreateChildObject(secondDstRole,&dstFCO));
				COMVERIFY(dstFCO->put_Name(dstFCO_name.Send()));

				// by this point, both src and dst are ready
				// now call createsimpleconn using the src and dst fco's
				CComPtr<IMgaFCO> srcPortHolder;
				if(srcRefs)
				{
					srcPortHolder = src_ref;
				}
				else if(!COM_EQUAL(src_mod,conn_mod))
				{
					srcPortHolder = src_mod;
				}
				else
				{
					srcPortHolder = srcFCO;
				}

				if(AreConnectionAspectsOK(role,srcPortHolder,dstPortHolder,conn_mod))
				{
					CComPtr<IMgaFCO> newConn;
					CBstr newConn_name = role->GetName();
					AddIdentifier(newConn_name);
					if(src_ref)
					{
						CBstr src_ref_name;
						GetNamePath(src_ref,src_ref_name);
						LogWrite("Creating a " + role->GetName() + " connection named " + newConn_name + " from " + srcFCO_name + " (through reference " + src_ref_name + ") to " + dstFCO_name + " in model " + parentName);
					}
					else
					{
						LogWrite("Creating a " + role->GetName() + " connection named " + newConn_name + " from " + srcFCO_name + " to " + dstFCO_name + " in model " + parentName);
					}

					COMVERIFY(conn_mod->CreateSimpleConn(role->GetCOM(), srcFCO, dstFCO, srcRefs, NULL, &newConn));
					COMVERIFY(newConn->put_Name(newConn_name.Send()));
				}
				else
				{
					LogWrite("Did not create a " + role->GetName() + " connection from " + srcFCO_name + " to " + dstFCO_name + " in model " + parentName + " because no common aspect available");
				}
			}
			else if(firstDstType == OBJTYPE_REFERENCE && (dstRoles.GetCount() > 0))
			{
				CComPtr<IMgaMetaFCO> meta_ref_fco;
				COMVERIFY(firstDstRole->get_Kind(&meta_ref_fco));
				CComPtr<IMgaMetaReference> meta_ref;
				COMVERIFY(meta_ref_fco.QueryInterface(&meta_ref));
				CMetaReference wrap_meta_ref(meta_ref);
				CMetaObjList target_kinds;
				wrap_meta_ref.GetTargetKinds(target_kinds);

				POSITION kindPos = target_kinds.GetHeadPosition();
				while(kindPos)
				{
					CMetaFCO *currKind = (CMetaFCO *) target_kinds.GetNext(kindPos);
					objtype_enum kindType;
					COMVERIFY(currKind->GetCOM()->get_ObjType(&kindType));
					if(kindType == OBJTYPE_MODEL)
					{
						CComPtr<IMgaFCO> remoteFCO;
						CComPtr<IMgaModel> remoteModel;
						CComPtr<IMgaMetaFCO> meta_remoteModel_fco;
						CComPtr<IMgaMetaModel> meta_remoteModel;
						CBstr remoteModel_name;

						// get remoteModel
						GetFirstFCOOfKind(currKind,remoteFCO);
						if(!remoteFCO)
						{
							CreateRandomFCO(currKind,remoteFCO);
						}

						COMVERIFY(remoteFCO.QueryInterface(&remoteModel));
						GetNamePath(remoteModel,remoteModel_name);
						COMVERIFY(remoteModel->get_Meta(&meta_remoteModel_fco));
						COMVERIFY(meta_remoteModel_fco.QueryInterface(&meta_remoteModel));

						// create a reference to act for the destination
						CComPtr<IMgaFCO> dstRef;

						CBstr dstRef_name;
						COMVERIFY(firstDstRole->get_Name((BSTR *) dstRef_name));
						AddIdentifier(dstRef_name);

						LogWrite("Creating reference " + dstRef_name + " in model " + parentName);
						COMVERIFY(conn_mod->CreateChildObject(firstDstRole,&dstRef));
						COMVERIFY(dstRef->put_Name(dstRef_name.Send()));

						// direct the reference to the source
						dstRef_name = "";
						GetNamePath(dstRef,dstRef_name);
						LogWrite("Directing reference " + dstRef_name + " to model " + remoteModel_name);
						CComPtr<IMgaReference> dstRef_ref;
						COMVERIFY(dstRef.QueryInterface(&dstRef_ref));
						COMVERIFY(dstRef_ref->put_Referred(remoteModel));

						// find port role in remoteModel
						// look at second pointerspec item
						CBstr secondDstRole_str = dstRoles.GetHead();
						CComPtr<IMgaMetaRole> secondDstRole;
						HRESULT hr = meta_remoteModel->get_RoleByName(secondDstRole_str.Send(),&secondDstRole);
						if(hr == S_OK)
						{
							// create that role in the model
							// get the refport for it and use that as the conn src
							CComPtr<IMgaFCO> remotePort;

							CBstr remotePort_name;
							COMVERIFY(secondDstRole->get_Name((BSTR *) remotePort_name));
							AddIdentifier(remotePort_name);

							LogWrite("Creating FCO " + remotePort_name + " in model " + remoteModel_name);
							COMVERIFY(remoteModel->CreateChildObject(secondDstRole,&remotePort));
							COMVERIFY(remotePort->put_Name(remotePort_name.Send()));

							// refports are no longer in the IDL, so try directly using remotePort
							CComPtr<IMgaFCOs> dstRefs;
							COMVERIFY(dstRefs.CoCreateInstance(OLESTR("Mga.MgaFCOs")));
							COMVERIFY(dstRefs->Append(dstRef_ref));

							// by this point, both src and dst are ready
							// now call createsimpleconn using the src and dst fco's
							CComPtr<IMgaFCO> srcPortHolder;
							if(srcRefs)
							{
								srcPortHolder = src_ref;
							}
							else if(!COM_EQUAL(src_mod,conn_mod))
							{
								srcPortHolder = src_mod;
							}
							else
							{
								srcPortHolder = srcFCO;
							}

							if(AreConnectionAspectsOK(role,srcPortHolder,dstRef,conn_mod))
							{
								CComPtr<IMgaFCO> newConn;
								CBstr newConn_name = role->GetName();
								AddIdentifier(newConn_name);
								if(src_ref)
								{
									CBstr src_ref_name;
									GetNamePath(src_ref,src_ref_name);
									LogWrite("Creating a " + role->GetName() + " connection named " + newConn_name + " from " + srcFCO_name + " (through reference " + src_ref_name + ") to " + remoteModel_name + " (through reference " + dstRef_name + ") in model " + parentName);
								}
								else
								{
									LogWrite("Creating a " + role->GetName() + " connection named " + newConn_name + " from " + srcFCO_name + " to " + remoteModel_name + " (through reference " + dstRef_name + ") in model " + parentName);
								}
								

								COMVERIFY(conn_mod->CreateSimpleConn(role->GetCOM(), srcFCO, remotePort, srcRefs, dstRefs, &newConn));
								COMVERIFY(newConn->put_Name(newConn_name.Send()));
							}
							else
							{
								CString logStr = "Did not create a ";
								logStr += role->GetName() + " connection from " + srcFCO_name;
								logStr += " to " + remoteModel_name + " in model " + parentName + " because no common aspect available";
								LogWrite(logStr);
							}

						}
						else if(hr == 0x80731007)
						{
							// do nothing
						}
						else
						{
							// handle error
							COMVERIFY(hr);
						}

					}
				}
				wipeList(target_kinds);
			}
			else
			{
				CComPtr<IMgaFCO> dstFCO;

				CBstr dstFCO_name;
				COMVERIFY(firstDstRole->get_Name((BSTR *) dstFCO_name));
				AddIdentifier(dstFCO_name);

				LogWrite("Creating FCO " + dstFCO_name + " in model " + parentName);
				COMVERIFY(conn_mod->CreateChildObject(firstDstRole,&dstFCO));
				COMVERIFY(dstFCO->put_Name(dstFCO_name.Send()));

				// by this point, both src and dst are ready
				// now call createsimpleconn using the src and dst fco's
				CComPtr<IMgaFCO> srcPortHolder;
				if(srcRefs)
				{
					srcPortHolder = src_ref;
				}
				else if(!COM_EQUAL(src_mod,conn_mod))
				{
					srcPortHolder = src_mod;
				}
				else
				{
					srcPortHolder = srcFCO;
				}

				if(AreConnectionAspectsOK(role,srcPortHolder,dstFCO,conn_mod))
				{
					CComPtr<IMgaFCO> newConn;
					CBstr newConn_name = role->GetName();
					AddIdentifier(newConn_name);
					if(src_ref)
					{
						CBstr src_ref_name;
						GetNamePath(src_ref,src_ref_name);
						LogWrite("Creating a " + role->GetName() + " connection named " + newConn_name + " from " + srcFCO_name + " (through reference " + src_ref_name + ") to " + dstFCO_name + " in model " + parentName);
					}
					else
					{
						LogWrite("Creating a " + role->GetName() + " connection named " + newConn_name + " from " + srcFCO_name + " to " + dstFCO_name + " in model " + parentName);
					}
					COMVERIFY(conn_mod->CreateSimpleConn(role->GetCOM(), srcFCO, dstFCO, srcRefs, NULL, &newConn));
					COMVERIFY(newConn->put_Name(newConn_name.Send()));
				}
				else
				{
					LogWrite("Did not create a " + role->GetName() + " connection from " + srcFCO_name + " to " + dstFCO_name + " in model " + parentName + " because no common aspect available");
				}
			}
		}
		else if(hr == 0x80731007)
		{
			// not found, do nothing
		}
		else
		{
			COMVERIFY(hr);
		}

	}
}
#if(0)
// used to parse list of space-delimited strings in role_str and fill up role_list
void ParseRoleString(CString role_str,CStringList& role_list)
{
	int lastSpace = -1;
	if(role_str.GetAt(role_str.GetLength() - 1) != ' ')
	{
		role_str += " ";
	}
	for(int i = 0; i < role_str.GetLength(); i++)
	{
		if(role_str.GetAt(i) == ' ')
		{
			role_list.AddTail(role_str.Mid(lastSpace+1,i-(lastSpace+1)));
			lastSpace = i;
		}
	}
}
#endif
// used to parse list of space-delimited strings in role_str and fill up role_list
void ParseDelimitedString(CString str,CStringList& list, char delimiter)
{
	int lastDelimiter = -1;
	if(str.GetAt(str.GetLength() - 1) != delimiter)
	{
		str += delimiter;
	}
	for(int i = 0; i < str.GetLength(); i++)
	{
		if(str.GetAt(i) == delimiter)
		{
			list.AddTail(str.Mid(lastDelimiter+1,i-(lastDelimiter+1)));
			lastDelimiter = i;
		}
	}
}

// blasts a folder; depth used to stop recursion once DEPTHLIMIT reached
void BlastFolder(CComPtr<IMgaFolder> fdr, int depth)
{
	depth++;
	CreateAllPossibleFolders(fdr);
	CreateAllPossibleFCOs(fdr);
	CComPtr<IMgaFolders> child_folders;
	COMVERIFY(fdr->get_ChildFolders(&child_folders));

	ComPtrList child_folders_list;
	SortMGAObjectCollection<IMgaFolders,IMgaFolder>(child_folders,child_folders_list);
	POSITION cflPos = child_folders_list.GetHeadPosition();
	while(cflPos)
	{
		CComPtr<IUnknown> iter_obj = child_folders_list.GetNext(cflPos);
		CComPtr<IMgaFolder> iter;
		COMVERIFY(iter_obj.QueryInterface(&iter));
		if(depth < depthLimit)
		{
			BlastFolder(iter,depth);
		}
	}
	
	CComPtr<IMgaFCOs> child_fcos;
	COMVERIFY(fdr->get_ChildFCOs(&child_fcos));

	ComPtrList child_fcos_list;
	SortMGAObjectCollection<IMgaFCOs,IMgaFCO>(child_fcos,child_fcos_list);
	POSITION pos = child_fcos_list.GetHeadPosition();
	while(pos)
	{
		CComPtr<IUnknown> iter = child_fcos_list.GetNext(pos);
		CComPtr<IMgaFCO> iter_fco;
		COMVERIFY(iter.QueryInterface(&iter_fco));
		BlastFCO(iter_fco,depth);
	}

}

// blasts an fco; depth used to stop recursion once DEPTHLIMIT reached
void BlastFCO(CComPtr<IMgaFCO> fco, int depth)
{
	depth++;
	SetAllAttributes(fco);
	CComPtr<IMgaModel> mod;
	fco.QueryInterface(&mod);
	if(mod)
	{
		CreateAllPossibleFCOs(mod);
		CComPtr<IMgaFCOs> child_fcos;
		COMVERIFY(mod->get_ChildFCOs(&child_fcos));

		ComPtrList child_fcos_list;
		SortMGAObjectCollection<IMgaFCOs,IMgaFCO>(child_fcos,child_fcos_list);
		POSITION pos = child_fcos_list.GetHeadPosition();
		while(pos)
		{
			CComPtr<IUnknown> iter_obj = child_fcos_list.GetNext(pos);
			CComPtr<IMgaFCO> iter;
			COMVERIFY(iter_obj.QueryInterface(&iter));
			if(depth < depthLimit)
			{
				BlastFCO(iter,depth);
			}
			else
			{
				SetAllAttributes(iter);
				CComPtr<IMgaSet> set;
				iter.QueryInterface(&set);
				if(set)
				{
					AddAllPossibleMembersToSet(set);
				}
			}
		}

	}
}

void BlastProject(CComPtr<IMgaProject> proj)
{
	CComPtr<IMgaFolder> rootFolder;
	COMVERIFY(proj->get_RootFolder(&rootFolder));

	BlastFolder(rootFolder);
	BlastReferences(proj);
	if(testTypesAndInstances)
	{
		BlastSubTypesAndInstances(rootFolder);
	}
}

void BlastReferences(CComPtr<IMgaProject> proj)
{
	CComPtr<IMgaFolder> rootFolder;
	CComPtr<IMgaFilter> filter;
	CComPtr<IMgaFCOs> allRefs;

	COMVERIFY(proj->get_RootFolder(&rootFolder));
	COMVERIFY(proj->CreateFilter(&filter));
	COMVERIFY(filter->put_Level(CComBSTR("0-")));
	COMVERIFY(filter->put_ObjType(CComBSTR("OBJTYPE_REFERENCE")));
	COMVERIFY(rootFolder->GetDescendantFCOs(filter, &allRefs));

	ComPtrList allRefs_list;
	SortMGAObjectCollection<IMgaFCOs,IMgaFCO>(allRefs,allRefs_list);
	POSITION pos = allRefs_list.GetHeadPosition();
	while(pos)
	{
		CComPtr<IUnknown> iter_obj = allRefs_list.GetNext(pos);
		CComPtr<IMgaReference> iter;
		COMVERIFY(iter_obj.QueryInterface(&iter));
		CreateReferences(iter);
	}
}

void CreateSubTypesAndInstances(CComPtr<IMgaModel> mod)
{
	CComPtr<IMgaObject> parent;
	CComPtr<IMgaFolder> parentFdr;

	CComPtr<IMgaFCO> subType;
	CComPtr<IMgaFCO> instance;
	COMVERIFY(mod->GetParent(&parent));
	COMVERIFY(parent.QueryInterface(&parentFdr));

	CBstr parentFdr_name;
	CBstr mod_name;
	GetNamePath(parentFdr,parentFdr_name);
	GetNamePath(mod,mod_name);

	// create subtype
	LogWrite("Creating subtype of " + mod_name + " in folder " + parentFdr_name);
	COMVERIFY(parentFdr->DeriveRootObject(mod,false,&subType));
	CBstr subType_name;
	COMVERIFY(subType->get_Name((BSTR *) subType_name));
	subType_name = (CString) subType_name + "_subType";
	AddIdentifier(subType_name);
	COMVERIFY(subType->put_Name(subType_name.Send()));
	
	// create instance
	LogWrite("Creating instance of " + mod_name + " in folder " + parentFdr_name);
	COMVERIFY(parentFdr->DeriveRootObject(mod,true,&instance));
	CBstr instance_name;
	COMVERIFY(instance->get_Name((BSTR *) instance_name));
	instance_name = (CString) instance_name + "_instance";
	AddIdentifier(instance_name);
	COMVERIFY(instance->put_Name(instance_name.Send()));
}

void BlastSubTypesAndInstances(CComPtr<IMgaFolder> fdr)
{
	// get root models
	CComPtr<IMgaFCOs> child_fcos;
	COMVERIFY(fdr->get_ChildFCOs(&child_fcos));

	ComPtrList child_fcos_list;
	SortMGAObjectCollection<IMgaFCOs,IMgaFCO>(child_fcos,child_fcos_list);
	POSITION pos = child_fcos_list.GetHeadPosition();
	while(pos)
	{
		CComPtr<IUnknown> iter_obj = child_fcos_list.GetNext(pos);
		CComPtr<IMgaModel> iter;
		COMVERIFY(iter_obj.QueryInterface(&iter));
		CreateSubTypesAndInstances(iter);
	}

	// get child folders and do recursive call on each one
	CComPtr<IMgaFolders> child_folders;
	COMVERIFY(fdr->get_ChildFolders(&child_folders));

	ComPtrList child_folders_list;
	SortMGAObjectCollection<IMgaFolders,IMgaFolder>(child_folders,child_folders_list);
	POSITION cflPos = child_folders_list.GetHeadPosition();
	while(cflPos)
	{
		CComPtr<IUnknown> iter_obj = child_folders_list.GetNext(cflPos);
		CComPtr<IMgaFolder> iter;
		COMVERIFY(iter_obj.QueryInterface(&iter));
		BlastSubTypesAndInstances(iter);
	}
}

void InitRandomFCOs()
{
	allFCOs_list.RemoveAll();

	CComPtr<IMgaFolder> rootFolder;
	CComPtr<IMgaFilter> filter;
	CComPtr<IMgaFCOs> allFCOs;

	COMVERIFY(proj->get_RootFolder(&rootFolder));
	COMVERIFY(proj->CreateFilter(&filter));
	COMVERIFY(filter->put_Level(CComBSTR("0-")));
	COMVERIFY(rootFolder->GetDescendantFCOs(filter, &allFCOs));

	SortMGAObjectCollection<IMgaFCOs,IMgaFCO>(allFCOs,allFCOs_list);

}

CComPtr<IMgaFCO> GetRandomFCO()
{
	int randIdx = 0;
	if(allFCOs_list.GetCount() != 0)
	{
		if(!playback)
		{
			randIdx =  rand() % allFCOs_list.GetCount();
			toPattFile << randIdx << " ";
		}
		else
			fromPattFile >> randIdx;
	}

	int counter = 0;
	POSITION pos = allFCOs_list.GetHeadPosition();
	while(pos)
	{
		if(counter == randIdx)
		{
			CComPtr<IUnknown> iter_obj = allFCOs_list.GetAt(pos);
			CComPtr<IMgaFCO> iter;
			COMVERIFY(iter_obj.QueryInterface(&iter));

			// if a deleted object found, purge from the list
			long status;
			bool goodObj = false;
			while(!goodObj && allFCOs_list.GetCount() > 0)
			{
				POSITION nextElem = pos;
				allFCOs_list.GetNext(nextElem);

				COMVERIFY(iter->get_Status(&status));
				if(status != OBJECT_EXISTS)
				{
					allFCOs_list.RemoveAt(pos);
					pos = nextElem;
					if(!allFCOs_list.IsEmpty())
					{
						iter_obj = NULL;
						iter = NULL;
						iter_obj = allFCOs_list.GetAt(pos);
						COMVERIFY(iter_obj.QueryInterface(&iter));
					}
				}
				else
				{
					goodObj = true;
				}
			}

			if(!goodObj)
			{
				return NULL;
			}

			return iter;
		}
		else
		{
			counter++;
			allFCOs_list.GetNext(pos);
		}
	}
	return NULL;
}

bool SetRandomAttribute(CComPtr<IMgaFCO> fco)
{
	CBstr fco_name;
	GetNamePath(fco,fco_name);

	// get the metaAttributes from the metafco
	CComPtr<IMgaMetaFCO> meta_fco;
	COMVERIFY(fco->get_Meta(&meta_fco));
	CMetaFCO wrap_meta_fco(meta_fco);
	CMetaObjList attlist;
	wrap_meta_fco.GetAttributes(attlist);

	int randIdx = 0;
	if(attlist.GetCount() != 0)
	{
		if(!playback)
		{
			randIdx = rand() % attlist.GetCount();
			toPattFile << randIdx << " ";
		}
		else
			fromPattFile >> randIdx;
	}

	POSITION attPos = attlist.FindIndex(randIdx);
	if(attPos != NULL)
	{
		// get the attribute
		CMetaAttribute *currAttr = (CMetaAttribute *) attlist.GetAt(attPos);

		LogWrite("Setting attribute " + currAttr->GetName() + " in FCO " + fco_name);

		attval_enum attrType;
		COMVERIFY(currAttr->GetCOM()->get_ValueType(&attrType));
		CComPtr<IMgaAttribute> fco_attr;
		COMVERIFY(fco->get_Attribute(currAttr->GetCOM(), &fco_attr));


		CBstr strVal = "test value";
		long intVal = 1234567;
		double dbVal = 3.141592654;
		bool boolVal = true;
		CComPtr<IMgaMetaEnumItems> enum_vals;
		ComPtrList enum_vals_list;
		POSITION cflPos;

		// based on attribute type, fill with appropriate test value
		switch(attrType)
		{

		case ATTVAL_STRING:
			COMVERIFY(fco_attr->put_StringValue(strVal.Send()));
			break;
		case ATTVAL_INTEGER:
			COMVERIFY(fco_attr->put_IntValue(intVal));
			break;
		case ATTVAL_DOUBLE:
			COMVERIFY(fco_attr->put_FloatValue(dbVal));
			break;
		case ATTVAL_BOOLEAN:
			COMVERIFY(fco_attr->put_BoolValue(boolVal));
			break;
		case ATTVAL_ENUM:
			// need to get enum items from meta
			COMVERIFY(currAttr->GetCOM()->get_EnumItems(&enum_vals));
			// set for each one - will leave as the last one

			SortMGAObjectCollection<IMgaMetaEnumItems,IMgaMetaEnumItem>(enum_vals,enum_vals_list);
			cflPos = enum_vals_list.GetHeadPosition();
			while(cflPos)
			{
				CComPtr<IUnknown> iter_obj = enum_vals_list.GetNext(cflPos);
				CComPtr<IMgaMetaEnumItem> iter;
				COMVERIFY(iter_obj.QueryInterface(&iter));
				CBstr currEnumVal;
				COMVERIFY(iter->get_Value((BSTR *) currEnumVal));
				COMVERIFY(fco_attr->put_StringValue(currEnumVal.Send()));
			}
			break;
		default:	// write unsupported attr type to log
			LogWrite("ERROR - Unsupported attribute type.");
			break;

		}
		wipeList(attlist);
		return true;
	}
	else
	{
		// no attribute found
		wipeList(attlist);
		return false;
	}
}

bool ClearRandomAttribute(CComPtr<IMgaFCO> fco)
{
	CBstr fco_name;
	GetNamePath(fco,fco_name);

	// get the metaAttributes from the metafco
	CComPtr<IMgaMetaFCO> meta_fco;
	COMVERIFY(fco->get_Meta(&meta_fco));
	CMetaFCO wrap_meta_fco(meta_fco);
	CMetaObjList attlist;
	wrap_meta_fco.GetAttributes(attlist);

	int randIdx = 0;
	if(attlist.GetCount() != 0)
	{
		if(!playback)
		{
			randIdx = rand() % attlist.GetCount();
			toPattFile << randIdx << " ";
		}
		else
			fromPattFile >> randIdx;
	}

	POSITION attPos = attlist.FindIndex(randIdx);
	if(attPos != NULL)
	{
		// get the attribute
		CMetaAttribute *currAttr = (CMetaAttribute *) attlist.GetAt(attPos);

		LogWrite("Clearing attribute " + currAttr->GetName() + " in FCO " + fco_name);

		attval_enum attrType;
		COMVERIFY(currAttr->GetCOM()->get_ValueType(&attrType));
		CComPtr<IMgaAttribute> fco_attr;
		COMVERIFY(fco->get_Attribute(currAttr->GetCOM(), &fco_attr));

		COMVERIFY(fco_attr->Clear());
		wipeList(attlist);
		return true;
	}
	else
	{
		wipeList(attlist);
		return false;
	}

}

void CreateRandomChild(CComPtr<IMgaModel> mod)
{
	CBstr parentName;
	GetNamePath(mod,parentName);

	VARIANT_BOOL isInstance;
	COMVERIFY(mod->get_IsInstance(&isInstance));
	if(!isInstance)
	{
		CComPtr<IMgaMetaFCO> meta_fco;
		COMVERIFY(mod->get_Meta(&meta_fco));
		CMetaFCO wrap_meta_mod(meta_fco);
		CMetaObjList meta_childRoles;
		wrap_meta_mod.GetRoles(meta_childRoles);

		int randIdx = 0;
		if(meta_childRoles.GetCount() != 0)
		{
			if(!playback)
			{
				randIdx = rand() % meta_childRoles.GetCount();
				toPattFile << randIdx << " ";
			}
			else
				fromPattFile >> randIdx;
		}

		POSITION childPos = meta_childRoles.FindIndex(randIdx);
		if(childPos != NULL)
		{
			CMetaRole *currMRole = (CMetaRole *) meta_childRoles.GetNext(childPos);
			objtype_enum oType;
			CComPtr<IMgaMetaFCO> kind;
			COMVERIFY(currMRole->GetCOM()->get_Kind(&kind));
			COMVERIFY(kind->get_ObjType(&oType));
			if(oType != OBJTYPE_CONNECTION)
			{
				CComPtr<IMgaFCO> newFCO;
				CBstr name = currMRole->GetName();
				AddIdentifier(name);
				LogWrite("Creating a " + currMRole->GetName() + " FCO named " + name + " in model " + parentName);
				COMVERIFY(mod->CreateChildObject(currMRole->GetCOM(),&newFCO));
				InsertIntoMGAObjectCollection<IMgaFCO>(newFCO,allFCOs_list);
				COMVERIFY(newFCO->put_Name(name.Send()));
			}
			else
			{
				CreateRandomConnection(currMRole,mod);
			}
		}
		wipeList(meta_childRoles);
	}
}

CComPtr<IMgaFCO> CreateRandomConnection(CMetaRole *role, CComPtr<IMgaModel> mod)
{
	CBstr src_str = "src";
	CBstr dst_str = "dst";
	
	CBstr mod_name;
	GetNamePath(mod,mod_name);

	CComPtr<IMgaMetaModel> meta_mod;
	CComPtr<IMgaMetaFCO> meta_fco;
	COMVERIFY(mod->get_Meta(&meta_fco));
	COMVERIFY(meta_fco.QueryInterface(&meta_mod));

	CComPtr<IMgaMetaFCO> kind;
	COMVERIFY(role->GetCOM()->get_Kind(&kind));
	CComPtr<IMgaMetaConnection> meta_conn;
	COMVERIFY(kind.QueryInterface(&meta_conn));
	CComPtr<IMgaMetaConnJoints> joints;
	COMVERIFY(meta_conn->get_Joints(&joints));
	long numJoints;
	COMVERIFY(joints->get_Count(&numJoints));
	int randIdx_joint = 0;
	if(numJoints != 0)
	{
		if(!playback)
		{
			randIdx_joint = rand() % numJoints;
			toPattFile << randIdx_joint << " ";
		}
		else
			fromPattFile >> randIdx_joint;
	}

	int joint_counter = 0;

	MGACOLL_ITERATE(IMgaMetaConnJoint,joints) {
		if(joint_counter == randIdx_joint)
		{
			CComPtr<IMgaMetaConnJoint> currJoint = MGACOLL_ITER;
			CComPtr<IMgaMetaPointerSpec> src_spec;
			CComPtr<IMgaMetaPointerSpec> dst_spec;
			COMVERIFY(currJoint->get_PointerSpecByName(src_str.Send(), &src_spec));
			COMVERIFY(currJoint->get_PointerSpecByName(dst_str.Send(), &dst_spec));

			CComPtr<IMgaMetaPointerItems> src_items;
			COMVERIFY(src_spec->get_Items(&src_items));
			CComPtr<IMgaMetaPointerItems> dst_items;
			COMVERIFY(dst_spec->get_Items(&dst_items));
			long numSrcItems;
			COMVERIFY(src_items->get_Count(&numSrcItems));
			int randIdx_srcItems = 0;
			if(numSrcItems != 0)
			{
				if(!playback)
				{
					randIdx_srcItems = rand() % numSrcItems;
					toPattFile << randIdx_srcItems << " ";
				}
				else
					fromPattFile >> randIdx_srcItems;
			}

			int srcItems_counter = 0;

			ComPtrList src_items_list;
			SortMGAObjectCollection<IMgaMetaPointerItems,IMgaMetaPointerItem>(src_items,src_items_list);
			POSITION pos = src_items_list.GetHeadPosition();
			while(pos)
			{
				CComPtr<IUnknown> iter_obj = src_items_list.GetNext(pos);
				CComPtr<IMgaMetaPointerItem> currSrcItem;
				COMVERIFY(iter_obj.QueryInterface(&currSrcItem));

				if(srcItems_counter == randIdx_srcItems)
				{
					CBstr currSrcDesc;
					COMVERIFY(currSrcItem->get_Desc((BSTR *) currSrcDesc));
					CStringList srcRoles;
//					ParseRoleString(currSrcDesc,srcRoles);
					ParseDelimitedString(currSrcDesc,srcRoles,' ');
					CBstr firstSrcRole_str = srcRoles.RemoveHead();
					CComPtr<IMgaMetaRole> firstSrcRole;
					HRESULT hr = meta_mod->get_RoleByName(firstSrcRole_str.Send(),&firstSrcRole);
					if(hr == S_OK)
					{
						CComPtr<IMgaMetaFCO> firstSrcKind;
						COMVERIFY(firstSrcRole->get_Kind(&firstSrcKind));
						objtype_enum firstSrcType;
						COMVERIFY(firstSrcKind->get_ObjType(&firstSrcType));
						if(firstSrcType == OBJTYPE_MODEL && (srcRoles.GetCount() > 0))
						{
							CComPtr<IMgaFCO> srcPortHolder;
							CComPtr<IMgaModel> srcPortHolder_mod;

							CBstr srcPortHolder_name;
							COMVERIFY(firstSrcRole->get_Name((BSTR *) srcPortHolder_name));
							AddIdentifier(srcPortHolder_name);

							LogWrite("Creating FCO " + srcPortHolder_name + " in model " + mod_name);
							COMVERIFY(mod->CreateChildObject(firstSrcRole,&srcPortHolder));
							InsertIntoMGAObjectCollection<IMgaFCO>(srcPortHolder,allFCOs_list);
							COMVERIFY(srcPortHolder.QueryInterface(&srcPortHolder_mod));
							COMVERIFY(srcPortHolder->put_Name(srcPortHolder_name.Send()));
							
							CComPtr<IMgaMetaFCO> meta_srcPortHolder;
							COMVERIFY(srcPortHolder->get_Meta(&meta_srcPortHolder));
							CComPtr<IMgaMetaModel> meta_srcPortHolder_mod;
							COMVERIFY(meta_srcPortHolder.QueryInterface(&meta_srcPortHolder_mod));
							CBstr secondSrcRole_str = srcRoles.GetHead();
							CComPtr<IMgaMetaRole> secondSrcRole;
							COMVERIFY(meta_srcPortHolder_mod->get_RoleByName(secondSrcRole_str.Send(),&secondSrcRole));
							CComPtr<IMgaMetaFCO> secondSrcKind;
							COMVERIFY(secondSrcRole->get_Kind(&secondSrcKind));

							return ConnectToRandomDst(role,mod,srcPortHolder_mod,secondSrcRole, NULL, dst_items);
						}
						else if(firstSrcType == OBJTYPE_REFERENCE && (srcRoles.GetCount() > 0))
						{
							CComPtr<IMgaMetaFCO> meta_ref_fco;
							COMVERIFY(firstSrcRole->get_Kind(&meta_ref_fco));
							CComPtr<IMgaMetaReference> meta_ref;
							COMVERIFY(meta_ref_fco.QueryInterface(&meta_ref));
							CMetaReference wrap_meta_ref(meta_ref);
							CMetaObjList target_kinds;
							wrap_meta_ref.GetTargetKinds(target_kinds);

							int randIdx_targetKinds = 0;
							if(target_kinds.GetCount() > 0)
							{
								if(!playback)
								{
									randIdx_targetKinds = rand() % target_kinds.GetCount();
									toPattFile << randIdx_targetKinds << " ";
								}
								else
									fromPattFile >> randIdx_targetKinds;
							}
							else
							{
								ASSERT(false);
							}

							POSITION kindPos = target_kinds.FindIndex(randIdx_targetKinds);
							CMetaFCO *currKind = (CMetaFCO *) target_kinds.GetAt(kindPos);
							objtype_enum kindType;
							COMVERIFY(currKind->GetCOM()->get_ObjType(&kindType));
							if(kindType == OBJTYPE_MODEL)
							{
								CComPtr<IMgaFCO> remoteFCO;
								CComPtr<IMgaModel> remoteModel;
								CComPtr<IMgaMetaFCO> meta_remoteModel_fco;
								CComPtr<IMgaMetaModel> meta_remoteModel;
								CBstr remoteModel_name;

								// somehow get remoteModel
								GetFirstFCOOfKind(currKind,remoteFCO);
								if(!remoteFCO)
								{
									CreateRandomFCO(currKind,remoteFCO);
								}

								COMVERIFY(remoteFCO.QueryInterface(&remoteModel));
								GetNamePath(remoteModel,remoteModel_name);
								COMVERIFY(remoteModel->get_Meta(&meta_remoteModel_fco));
								COMVERIFY(meta_remoteModel_fco.QueryInterface(&meta_remoteModel));
								// create a reference to act for the source
								CComPtr<IMgaFCO> srcRef;

								CBstr srcRef_name;
								COMVERIFY(firstSrcRole->get_Name((BSTR *) srcRef_name));
								AddIdentifier(srcRef_name);

								LogWrite("Creating reference " + srcRef_name + " in model " + mod_name);
								COMVERIFY(mod->CreateChildObject(firstSrcRole,&srcRef));
								COMVERIFY(srcRef->put_Name(srcRef_name.Send()));

								// direct the reference to the source
								srcRef_name = "";
								GetNamePath(srcRef,srcRef_name);
								LogWrite("Directing reference " + srcRef_name + " to model " + remoteModel_name);
								CComPtr<IMgaReference> srcRef_ref;
								COMVERIFY(srcRef.QueryInterface(&srcRef_ref));
								COMVERIFY(srcRef_ref->put_Referred(remoteModel));

								// find port role in remoteModel
								// look at second pointerspec item
								CBstr secondSrcRole_str = srcRoles.GetHead();
								CComPtr<IMgaMetaRole> secondSrcRole;
								HRESULT hr = meta_remoteModel->get_RoleByName(secondSrcRole_str.Send(),&secondSrcRole);
								if(hr == S_OK)
								{
									// create that role in the model
									// get the refport for it and use that as the conn src
									// refports are no longer in the IDL, so try directly using remotePort
						
									return ConnectToRandomDst(role,mod,remoteModel,secondSrcRole,srcRef,dst_items);
								}
								else if(hr == 0x80731007)
								{
									// do nothing
								}
								else
								{
									// handle error
									COMVERIFY(hr);
								}

							}
							
							wipeList(target_kinds);
						
						}
						else
						{
							return ConnectToRandomDst(role,mod,mod,firstSrcRole,NULL,dst_items);
						}
					}
					else if(hr == 0x80731007)
					{
						// not found, do nothing
					}
					else
					{
						COMVERIFY(hr);
					}
					break;
				}
				else
				{
					srcItems_counter++;
				}
			}
			break;
		}
		else
		{
			joint_counter++;
		}

	} MGACOLL_ITERATE_END

	return NULL;
}

CComPtr<IMgaFCO> ConnectToRandomDst(CMetaRole *role, CComPtr<IMgaModel> conn_mod, CComPtr<IMgaModel> src_mod, CComPtr<IMgaMetaRole> srcRole, CComPtr<IMgaFCO> src_ref, CComPtr<IMgaMetaPointerItems> dst_items)
{
	CComPtr<IMgaMetaModel> meta_mod;
	CComPtr<IMgaMetaFCO> meta_fco;
	COMVERIFY(conn_mod->get_Meta(&meta_fco));
	COMVERIFY(meta_fco.QueryInterface(&meta_mod));

	CBstr parentName;
	GetNamePath(conn_mod,parentName);

	CComPtr<IMgaFCOs> srcRefs;

	if(src_ref)
	{
		COMVERIFY(srcRefs.CoCreateInstance(OLESTR("Mga.MgaFCOs")));
		COMVERIFY(srcRefs->Append(src_ref));
	}

	CBstr srcFCO_name;
	COMVERIFY(srcRole->get_Name((BSTR *) srcFCO_name));
	AddIdentifier(srcFCO_name);

	CBstr src_mod_name;
	GetNamePath(src_mod,src_mod_name);

	CComPtr<IMgaFCO> srcFCO;
	LogWrite("Creating FCO " + srcFCO_name + " in model " + src_mod_name);
	COMVERIFY(src_mod->CreateChildObject(srcRole,&srcFCO));
	InsertIntoMGAObjectCollection<IMgaFCO>(srcFCO,allFCOs_list);
	COMVERIFY(srcFCO->put_Name(srcFCO_name.Send()));
	long numDstItems;
	COMVERIFY(dst_items->get_Count(&numDstItems));
	int randIdx_dstItems = 0;
	if(numDstItems != 0)
	{
		if(!playback)
		{
			randIdx_dstItems = rand() % numDstItems;
			toPattFile << randIdx_dstItems << " ";
		}
		else
			fromPattFile >> randIdx_dstItems;
	}

	int dstItems_counter = 0;

	// now go find a dst!!!

	ComPtrList dst_items_list;
	SortMGAObjectCollection<IMgaMetaPointerItems,IMgaMetaPointerItem>(dst_items,dst_items_list);
	POSITION pos = dst_items_list.GetHeadPosition();
	while(pos)
	{
		CComPtr<IUnknown> iter_obj = dst_items_list.GetNext(pos);
		CComPtr<IMgaMetaPointerItem> currDstItem;
		COMVERIFY(iter_obj.QueryInterface(&currDstItem));

		if(dstItems_counter == randIdx_dstItems)
		{
			CBstr currDstDesc;
			COMVERIFY(currDstItem->get_Desc((BSTR *) currDstDesc));
			CStringList dstRoles;
//			ParseRoleString(currDstDesc,dstRoles);
			ParseDelimitedString(currDstDesc,dstRoles,' ');
			CBstr firstDstRole_str = dstRoles.RemoveHead();
			CComPtr<IMgaMetaRole> firstDstRole;
			HRESULT hr = meta_mod->get_RoleByName(firstDstRole_str.Send(),&firstDstRole);
			if(hr == S_OK)
			{
				CComPtr<IMgaMetaFCO> firstDstKind;
				COMVERIFY(firstDstRole->get_Kind(&firstDstKind));
				objtype_enum firstDstType;
				COMVERIFY(firstDstKind->get_ObjType(&firstDstType));
				if(firstDstType == OBJTYPE_MODEL && (dstRoles.GetCount() > 0))
				{
					CComPtr<IMgaFCO> dstPortHolder;
					CComPtr<IMgaModel> dstPortHolder_mod;

					CBstr dstPortHolder_name;
					COMVERIFY(firstDstRole->get_Name((BSTR *) dstPortHolder_name));
					AddIdentifier(dstPortHolder_name);

					LogWrite("Creating FCO " + dstPortHolder_name + " in model " + parentName);
					COMVERIFY(conn_mod->CreateChildObject(firstDstRole,&dstPortHolder));
					InsertIntoMGAObjectCollection<IMgaFCO>(dstPortHolder,allFCOs_list);
					COMVERIFY(dstPortHolder.QueryInterface(&dstPortHolder_mod));
					COMVERIFY(dstPortHolder->put_Name(dstPortHolder_name.Send()));
					
					CComPtr<IMgaMetaFCO> meta_dstPortHolder;
					COMVERIFY(dstPortHolder->get_Meta(&meta_dstPortHolder));
					CComPtr<IMgaMetaModel> meta_dstPortHolder_mod;
					COMVERIFY(meta_dstPortHolder.QueryInterface(&meta_dstPortHolder_mod));
					CBstr secondDstRole_str = dstRoles.GetHead();
					CComPtr<IMgaMetaRole> secondDstRole;
					COMVERIFY(meta_dstPortHolder_mod->get_RoleByName(secondDstRole_str.Send(),&secondDstRole));
					CComPtr<IMgaMetaFCO> secondDstKind;
					COMVERIFY(secondDstRole->get_Kind(&secondDstKind));

					CComPtr<IMgaFCO> dstFCO;

					CBstr dstFCO_name;
					COMVERIFY(secondDstRole->get_Name((BSTR *) dstFCO_name));
					AddIdentifier(dstFCO_name);

					CBstr dstPortHolder_mod_name;
					GetNamePath(dstPortHolder_mod,dstPortHolder_mod_name);
					LogWrite("Creating FCO " + dstFCO_name + " in model " + dstPortHolder_mod_name);

					COMVERIFY(dstPortHolder_mod->CreateChildObject(secondDstRole,&dstFCO));
					InsertIntoMGAObjectCollection<IMgaFCO>(dstFCO,allFCOs_list);
					COMVERIFY(dstFCO->put_Name(dstFCO_name.Send()));

					// by this point, both src and dst are ready
					// now call createsimpleconn using the src and dst fco's
					CComPtr<IMgaFCO> srcPortHolder;
					if(srcRefs)
					{
						srcPortHolder = src_ref;
					}
					else if(!COM_EQUAL(src_mod,conn_mod))
					{
						srcPortHolder = src_mod;
					}
					else
					{
						srcPortHolder = srcFCO;
					}

					if(AreConnectionAspectsOK(role,srcPortHolder,dstPortHolder,conn_mod))
					{
						CComPtr<IMgaFCO> newConn;
						CBstr newConn_name = role->GetName();
						AddIdentifier(newConn_name);
						if(src_ref)
						{
							CBstr src_ref_name;
							GetNamePath(src_ref,src_ref_name);
							LogWrite("Creating a " + role->GetName() + " connection named " + newConn_name + " from " + srcFCO_name + " (through reference " + src_ref_name + ") to " + dstFCO_name + " in model " + parentName);
						}
						else
						{
							LogWrite("Creating a " + role->GetName() + " connection named " + newConn_name + " from " + srcFCO_name + " to " + dstFCO_name + " in model " + parentName);
						}
						COMVERIFY(conn_mod->CreateSimpleConn(role->GetCOM(), srcFCO, dstFCO, NULL, NULL, &newConn));
						COMVERIFY(newConn->put_Name(newConn_name.Send()));
						return newConn;
					}
					else
					{
						LogWrite("Did not create a " + role->GetName() + " connection from " + srcFCO_name + " to " + dstFCO_name + " in model " + parentName + " because no common aspect available");
					}
				}
				else if(firstDstType == OBJTYPE_REFERENCE)
				{
					CComPtr<IMgaMetaFCO> meta_ref_fco;
					COMVERIFY(firstDstRole->get_Kind(&meta_ref_fco));
					CComPtr<IMgaMetaReference> meta_ref;
					COMVERIFY(meta_ref_fco.QueryInterface(&meta_ref));
					CMetaReference wrap_meta_ref(meta_ref);
					CMetaObjList target_kinds;
					wrap_meta_ref.GetTargetKinds(target_kinds);

					int randIdx_targetKinds = 0;
					if(target_kinds.GetCount() > 0)
					{
						if(!playback)
						{
							randIdx_targetKinds = rand() % target_kinds.GetCount();
							toPattFile << randIdx_targetKinds << " ";
						}
						else
							fromPattFile >> randIdx_targetKinds;
					}
					else
					{
						ASSERT(false);
					}

					POSITION kindPos = target_kinds.FindIndex(randIdx_targetKinds);

					CMetaFCO *currKind = (CMetaFCO *) target_kinds.GetAt(kindPos);
					objtype_enum kindType;
					COMVERIFY(currKind->GetCOM()->get_ObjType(&kindType));
					if(kindType == OBJTYPE_MODEL)
					{
						CComPtr<IMgaFCO> remoteFCO;
						CComPtr<IMgaModel> remoteModel;
						CComPtr<IMgaMetaFCO> meta_remoteModel_fco;
						CComPtr<IMgaMetaModel> meta_remoteModel;
						CBstr remoteModel_name;

						// get remoteModel
						GetFirstFCOOfKind(currKind,remoteFCO);
						if(!remoteFCO)
						{
							CreateRandomFCO(currKind,remoteFCO);
						}

						COMVERIFY(remoteFCO.QueryInterface(&remoteModel));
						GetNamePath(remoteModel,remoteModel_name);
						COMVERIFY(remoteModel->get_Meta(&meta_remoteModel_fco));
						COMVERIFY(meta_remoteModel_fco.QueryInterface(&meta_remoteModel));

						// create a reference to act for the destination
						CComPtr<IMgaFCO> dstRef;

						CBstr dstRef_name;
						COMVERIFY(firstDstRole->get_Name((BSTR *) dstRef_name));
						AddIdentifier(dstRef_name);

						LogWrite("Creating reference " + dstRef_name + " in model " + parentName);
						COMVERIFY(conn_mod->CreateChildObject(firstDstRole,&dstRef));
						COMVERIFY(dstRef->put_Name(dstRef_name.Send()));

						// direct the reference to the source
						dstRef_name = "";
						GetNamePath(dstRef,dstRef_name);
						LogWrite("Directing reference " + dstRef_name + " to model " + remoteModel_name);
						CComPtr<IMgaReference> dstRef_ref;
						COMVERIFY(dstRef.QueryInterface(&dstRef_ref));
						COMVERIFY(dstRef_ref->put_Referred(remoteModel));

						// find port role in remoteModel
						// look at second pointerspec item
						CBstr secondDstRole_str = dstRoles.GetHead();
						CComPtr<IMgaMetaRole> secondDstRole;
						HRESULT hr = meta_remoteModel->get_RoleByName(secondDstRole_str.Send(),&secondDstRole);
						if(hr == S_OK)
						{
							// create that role in the model
							// get the refport for it and use that as the conn src
							CComPtr<IMgaFCO> remotePort;

							CBstr remotePort_name;
							COMVERIFY(secondDstRole->get_Name((BSTR *) remotePort_name));
							AddIdentifier(remotePort_name);
							
							LogWrite("Creating FCO " + remotePort_name + " in model " + remoteModel_name);
							COMVERIFY(remoteModel->CreateChildObject(secondDstRole,&remotePort));
							COMVERIFY(remotePort->put_Name(remotePort_name.Send()));

							// refports are no longer in the IDL, so try directly using remotePort
							CComPtr<IMgaFCOs> dstRefs;
							COMVERIFY(dstRefs.CoCreateInstance(OLESTR("Mga.MgaFCOs")));
							COMVERIFY(dstRefs->Append(dstRef_ref));

							// by this point, both src and dst are ready
							// now call createsimpleconn using the src and dst fco's
							CComPtr<IMgaFCO> srcPortHolder;
							if(srcRefs)
							{
								srcPortHolder = src_ref;
							}
							else if(!COM_EQUAL(src_mod,conn_mod))
							{
								srcPortHolder = src_mod;
							}
							else
							{
								srcPortHolder = srcFCO;
							}

							if(AreConnectionAspectsOK(role,srcPortHolder,dstRef,conn_mod))
							{
								CComPtr<IMgaFCO> newConn;
								CBstr newConn_name = role->GetName();
								AddIdentifier(newConn_name);

	//							LogWrite("Creating a " + role->GetName() + " connection named " + newConn_name + " from " + srcFCO_name + " to " + remoteModel_name + " in model " + parentName);
								if(src_ref)
								{
									CBstr src_ref_name;
									GetNamePath(src_ref,src_ref_name);
									LogWrite("Creating a " + role->GetName() + " connection named " + newConn_name + " from " + srcFCO_name + " (through reference " + src_ref_name + ") to " + remoteModel_name + " (through reference " + dstRef_name + ") in model " + parentName);
								}
								else
								{
									LogWrite("Creating a " + role->GetName() + " connection named " + newConn_name + " from " + srcFCO_name + " to " + remoteModel_name + " (through reference " + dstRef_name + ") in model " + parentName);
								}
								
								COMVERIFY(conn_mod->CreateSimpleConn(role->GetCOM(), srcFCO, remotePort, srcRefs, dstRefs, &newConn));
								COMVERIFY(newConn->put_Name(newConn_name.Send()));
							}
							else
							{
								LogWrite("Did not create a " + role->GetName() + " connection from " + srcFCO_name + " to " + remoteModel_name + " in model " + parentName + " because no common aspect available");
							}
						}
						else if(hr == 0x80731007)
						{
							// do nothing
						}
						else
						{
							// handle error
							COMVERIFY(hr);
						}

					}

					wipeList(target_kinds);
				}

				else
				{
					CComPtr<IMgaFCO> dstFCO;

					CBstr dstFCO_name;
					COMVERIFY(firstDstRole->get_Name((BSTR *) dstFCO_name));
					AddIdentifier(dstFCO_name);

					LogWrite("Creating FCO " + dstFCO_name + " in model " + parentName);
					COMVERIFY(conn_mod->CreateChildObject(firstDstRole,&dstFCO));
					InsertIntoMGAObjectCollection<IMgaFCO>(dstFCO,allFCOs_list);
					COMVERIFY(dstFCO->put_Name(dstFCO_name.Send()));

					// by this point, both src and dst are ready
					// now call createsimpleconn using the src and dst fco's
					CComPtr<IMgaFCO> srcPortHolder;
					if(srcRefs)
					{
						srcPortHolder = src_ref;
					}
					else if(!COM_EQUAL(src_mod,conn_mod))
					{
						srcPortHolder = src_mod;
					}
					else
					{
						srcPortHolder = srcFCO;
					}

					if(AreConnectionAspectsOK(role,srcPortHolder,dstFCO,conn_mod))
					{
						CComPtr<IMgaFCO> newConn;
						CBstr newConn_name = role->GetName();
						AddIdentifier(newConn_name);
	//					LogWrite("Creating a " + role->GetName() + " connection named " + newConn_name + " from " + srcFCO_name + " to " + dstFCO_name + " in model " + parentName);
						if(src_ref)
						{
							CBstr src_ref_name;
							GetNamePath(src_ref,src_ref_name);
							LogWrite("Creating a " + role->GetName() + " connection named " + newConn_name + " from " + srcFCO_name + " (through reference " + src_ref_name + ") to " + dstFCO_name + " in model " + parentName);
						}
						else
						{
							LogWrite("Creating a " + role->GetName() + " connection named " + newConn_name + " from " + srcFCO_name + " to " + dstFCO_name + " in model " + parentName);
						}

						COMVERIFY(conn_mod->CreateSimpleConn(role->GetCOM(), srcFCO, dstFCO, NULL, NULL, &newConn));
						COMVERIFY(newConn->put_Name(newConn_name.Send()));
						return newConn;
					}
					else
					{
						LogWrite("Did not create a " + role->GetName() + " connection from " + srcFCO_name + " to " + dstFCO_name + " in model " + parentName + " because no common aspect available");
					}
				}
			}
			else if(hr == 0x80731007)
			{
				// not found, do nothing
			}
			else
			{
				COMVERIFY(hr);
			}

			break;
		}
		else
		{
			dstItems_counter++;
		}

	}

	return NULL;
}

void PerformRandomTesting(int count)
{
	InitRandomFCOs();
	if(!playback)
	{
		for(int i = 0; i < count; i++)
		{
			CComPtr<IMgaFCO> fco = GetRandomFCO();
			if(!fco)
			{
				LogWrite("No FCOs to test with!");
				break;
			}
			int randIdx = 0;
			if(RAND_ACTIONS != 0)
			{
				randIdx = rand() % RAND_ACTIONS;
				toPattFile << randIdx << " ";
			}

			CComPtr<IMgaModel> mod;
			CComPtr<IMgaSet> set;
			CComPtr<IMgaReference> ref;
			bool success;

			switch(randIdx)
			{
			case 0: success = SetRandomAttribute(fco);
					if(!success)
					{
	//					i--;
					}
					break;
			case 1: success = ClearRandomAttribute(fco);
					if(!success)
					{
	//					i--;
					}
					break;
			case 2: fco.QueryInterface(&mod);
					if(mod)
					{
						CreateRandomChild(mod);
					}
					else
					{
	//					i--;
					}
					break;
			case 3: fco.QueryInterface(&set);
					if(set)
					{
						RemoveRandomMemberFromSet(set);
					}
					else
					{
	//					i--;
					}
					break;
			case 4: fco.QueryInterface(&set);
					if(set)
					{
						AddRandomMemberToSet(set);
					}
					else
					{
	//					i--;
					}
					break;
			case 5: fco.QueryInterface(&ref);
					if(ref)
					{
						DirectRandomReference(ref);
					}
					else
					{
	//					i--;
					}
					break;
			case 6: fco.QueryInterface(&ref);
					if(ref)
					{
						ClearRandomReference(ref);
					}
					else
					{
	//					i--;
					}
					break;
			case 7: fco.QueryInterface(&ref);
					if(ref)
					{
						RevertRandomReference(ref);
					}
					else
					{
	//					i--;
					}
					break;
			case 8: fco.QueryInterface(&mod);
					if(mod)
					{
						// move
						PrepareCopyOrMoveChildren(mod,false);
					}
					else
					{

					}
					break;
			case 9: fco.QueryInterface(&mod);
					if(mod)
					{
						// copy
						PrepareCopyOrMoveChildren(mod,true);
					}
					else
					{

					}
					break;
//			case 10:DeleteRandomFCO(fco);
//					break;
			default:LogWrite("ERROR - RAND_ACTIONS parameter too large!");
					break;

			}
		}

	}
	else
	{
		while(!fromPattFile.eof())
		{
			CComPtr<IMgaFCO> fco = GetRandomFCO();
			if(!fco)
			{
				LogWrite("No FCOs to test with!");
				break;
			}
			int randIdx = 0;
			fromPattFile >> randIdx;

			CComPtr<IMgaModel> mod;
			CComPtr<IMgaSet> set;
			CComPtr<IMgaReference> ref;
			bool success;

			switch(randIdx)
			{
			case 0: success = SetRandomAttribute(fco);
					if(!success)
					{
	//					i--;
					}
					break;
			case 1: success = ClearRandomAttribute(fco);
					if(!success)
					{
	//					i--;
					}
					break;
			case 2: fco.QueryInterface(&mod);
					if(mod)
					{
						CreateRandomChild(mod);
					}
					else
					{
	//					i--;	
					}
					break;
			case 3: fco.QueryInterface(&set);
					if(set)
					{
						RemoveRandomMemberFromSet(set);
					}
					else
					{
	//					i--;
					}
					break;
			case 4: fco.QueryInterface(&set);
					if(set)
					{
						AddRandomMemberToSet(set);
					}
					else
					{
	//					i--;
					}
					break;
			case 5: fco.QueryInterface(&ref);
					if(ref)
					{
						DirectRandomReference(ref);
					}
					else
					{
	//					i--;
					}
					break;
			case 6: fco.QueryInterface(&ref);
					if(ref)
					{
						ClearRandomReference(ref);
					}
					else
					{
	//					i--;
					}
					break;
			case 7: fco.QueryInterface(&ref);
					if(ref)
					{
						RevertRandomReference(ref);
					}
					else
					{
	//					i--;
					}
					break;
			case 8: fco.QueryInterface(&mod);
					if(mod)
					{
						// move
						PrepareCopyOrMoveChildren(mod,false);
					}
					else
					{

					}
					break;
			case 9: fco.QueryInterface(&mod);
					if(mod)
					{
						// copy
						PrepareCopyOrMoveChildren(mod,true);
					}
					else
					{

					}
					break;
//			case 10:DeleteRandomFCO(fco);
//					break;
			default:LogWrite("ERROR - RAND_ACTIONS parameter too large!");
					break;

			}
		}
	}
}

void AddAllPossibleMembersToSet(CComPtr<IMgaSet> set)
{
	CComPtr<IMgaObject> parentObj;
	COMVERIFY(set->GetParent(&parentObj));
	CComPtr<IMgaModel> parentModel;

	CBstr setName;
	COMVERIFY(set->get_Name((BSTR *) setName));

	if(SUCCEEDED(parentObj.QueryInterface(&parentModel)))
	{
		CBstr parentName;
		GetNamePath(parentModel,parentName);

		CComPtr<IMgaMetaSet> meta_set_ptr;
		CComPtr<IMgaMetaFCO> meta_fco_ptr;
		COMVERIFY(set->get_Meta(&meta_fco_ptr));
		COMVERIFY(meta_fco_ptr.QueryInterface(&meta_set_ptr));
		CMetaSet meta_set(meta_set_ptr);
		CComPtr<IMgaMetaRole> meta_role_ptr;
		COMVERIFY(set->get_MetaRole(&meta_role_ptr));
		CMetaRole set_role(meta_role_ptr);
		CMetaObjList member_roles;
		meta_set.GetMemberRoles(member_roles,&set_role);
		POSITION rolePos = member_roles.GetHeadPosition();
		while(rolePos)
		{
			CMetaRole *currRole = (CMetaRole *) member_roles.GetNext(rolePos);

			objtype_enum oType;
			CComPtr<IMgaMetaFCO> kind;
			COMVERIFY(currRole->GetCOM()->get_Kind(&kind));
			COMVERIFY(kind->get_ObjType(&oType));
			if(oType != OBJTYPE_CONNECTION)
			{
				// create the fco to add to the set
				CComPtr<IMgaFCO> newFCO;
				CBstr name = currRole->GetName();
				AddIdentifier(name);
				LogWrite("Creating a " + currRole->GetName() + " FCO named " + name + " in model " + parentName);
				COMVERIFY(parentModel->CreateChildObject(currRole->GetCOM(),&newFCO));
				COMVERIFY(newFCO->put_Name(name.Send()));

				// and add it to the set
				LogWrite("Adding FCO " + name + " to set " + setName + " in model " + parentName);
				COMVERIFY(set->AddMember(newFCO));

			}
			else
			{
				// just try to find an existing connection to add
//				CComPtr<IMgaFCO> newConn = CreateRandomConnection(currRole,parentModel);
				CComPtr<IMgaFCOs> modelKids;
				COMVERIFY(parentModel->get_ChildFCOs(&modelKids));
				ComPtrList modelKids_list;
				SortMGAObjectCollection<IMgaFCOs,IMgaFCO>(modelKids,modelKids_list);
				POSITION mkPos = modelKids_list.GetHeadPosition();
				while(mkPos)
				{
					CComPtr<IUnknown> currKid_unk = modelKids_list.GetNext(mkPos);
					CComPtr<IMgaFCO> currKid;
					COMVERIFY(currKid_unk.QueryInterface(&currKid));
					CComPtr<IMgaMetaRole> currKidRole;
					COMVERIFY(currKid->get_MetaRole(&currKidRole));
					if( COM_EQUAL(currKidRole,currRole->GetCOM()) )
					{
						CBstr name;
						COMVERIFY(currKid->get_Name((BSTR *) name));
						LogWrite("Adding FCO " + name + " to set " + setName + " in model " + parentName);
						COMVERIFY(set->AddMember(currKid));
						break;
					}
				}
			}
		}

		wipeList(member_roles);
	}

}

void RemoveRandomMemberFromSet(CComPtr<IMgaSet> set)
{
	CBstr setName;
	GetNamePath(set,setName);
	
	CComPtr<IMgaFCOs> members;
	COMVERIFY(set->get_Members(&members));

	long numMembers;
	COMVERIFY(members->get_Count(&numMembers));
	int randIdx_members = 0;
	if(numMembers != 0)
	{
		if(!playback)
		{
			randIdx_members = rand() % numMembers;
			toPattFile << randIdx_members << " ";
		}
		else
		{
			fromPattFile >> randIdx_members;
		}
	}

	int members_counter = 0;

	ComPtrList members_list;
	SortMGAObjectCollection<IMgaFCOs,IMgaFCO>(members,members_list);
	POSITION pos = members_list.GetHeadPosition();
	while(pos)
	{
		CComPtr<IUnknown> iter_obj = members_list.GetNext(pos);
		CComPtr<IMgaFCO> iter;
		COMVERIFY(iter_obj.QueryInterface(&iter));
		if(members_counter == randIdx_members)
		{
			CBstr iterName;
			COMVERIFY(iter->get_Name((BSTR *) iterName));
			LogWrite("Removing member " + iterName + " from set " + setName);
			COMVERIFY(set->RemoveMember(iter));
			break;
		}
		else
		{
			members_counter++;
		}

	}
}

void AddRandomMemberToSet(CComPtr<IMgaSet> set)
{
	CComPtr<IMgaObject> parentObj;
	COMVERIFY(set->GetParent(&parentObj));
	CComPtr<IMgaModel> parentModel;

	CBstr setName;
	GetNamePath(set,setName);

	bool mOK = SUCCEEDED(parentObj.QueryInterface(&parentModel)); 
	VARIANT_BOOL isInstance = 0;
	if(mOK)
	{
		COMVERIFY(parentModel->get_IsInstance(&isInstance));

		CBstr parentName;
		GetNamePath(parentModel,parentName);

		CComPtr<IMgaMetaSet> meta_set_ptr;
		CComPtr<IMgaMetaFCO> meta_fco_ptr;
		COMVERIFY(set->get_Meta(&meta_fco_ptr));
		COMVERIFY(meta_fco_ptr.QueryInterface(&meta_set_ptr));
		CMetaSet meta_set(meta_set_ptr);
		CComPtr<IMgaMetaRole> meta_role_ptr;
		COMVERIFY(set->get_MetaRole(&meta_role_ptr));
		CMetaRole set_role(meta_role_ptr);
		CMetaObjList member_roles;
		meta_set.GetMemberRoles(member_roles,&set_role);

		if(!isInstance)
		{
			int randIdx = 0;
			if(member_roles.GetCount() != 0)
			{
				if(!playback)
				{
					randIdx = rand() % member_roles.GetCount();
					toPattFile << randIdx << " ";
				}
				else
					fromPattFile >> randIdx;
			}

			POSITION rolePos = member_roles.FindIndex(randIdx);
			if(rolePos)
			{
				CMetaRole *currRole = (CMetaRole *) member_roles.GetAt(rolePos);
				// create the fco to add to the set
				CComPtr<IMgaFCO> newFCO;
				CBstr name = currRole->GetName();
				AddIdentifier(name);
				LogWrite("Creating a " + currRole->GetName() + " FCO named " + name + " in model " + parentName);
				COMVERIFY(parentModel->CreateChildObject(currRole->GetCOM(),&newFCO));
				InsertIntoMGAObjectCollection<IMgaFCO>(newFCO,allFCOs_list);
				COMVERIFY(newFCO->put_Name(name.Send()));

				// and add it to the set
				LogWrite("Adding FCO " + name + " to set " + setName + " in model " + parentName);
				COMVERIFY(set->AddMember(newFCO));
			}
			
		}
		else
		{
			// search the model for an existing member to add
			// and don't add one that's already a member
			CComPtr<IMgaFCOs> siblings;
			COMVERIFY(parentModel->get_ChildFCOs(&siblings));

			ComPtrList siblings_list;
			SortMGAObjectCollection<IMgaFCOs,IMgaFCO>(siblings,siblings_list);
			POSITION pos = siblings_list.GetHeadPosition();
			while(pos)
			{
				CComPtr<IUnknown> iter_obj = siblings_list.GetNext(pos);
				CComPtr<IMgaFCO> iter;
				COMVERIFY(iter_obj.QueryInterface(&iter));
				CComPtr<IMgaMetaRole> iter_metarole;
				COMVERIFY(iter->get_MetaRole(&iter_metarole));
				POSITION rolePos = member_roles.GetHeadPosition();
				while(rolePos)
				{
					CMetaRole *currRole = (CMetaRole *) member_roles.GetNext(rolePos);
					if( COM_EQUAL(currRole->GetCOM(),iter_metarole) )
					{
						// we have a candidate
						CComPtr<IMgaFCOs> iter_sets;
						COMVERIFY(iter->get_MemberOfSets(&iter_sets));

						bool alreadyMember = false;
						MGACOLL_ITERATE(IMgaFCO,iter_sets) {
							if( COM_EQUAL(MGACOLL_ITER,set) )
							{
								alreadyMember = true;
							}
						} MGACOLL_ITERATE_END
						if(!alreadyMember)
						{
							// add and return
							CBstr newMembName;
							COMVERIFY(iter->get_Name((BSTR *) newMembName));
							LogWrite("Adding FCO " + newMembName + " to set " + setName + " in model " + parentName);
							COMVERIFY(set->AddMember(iter));
							return;
						}
					}
				}
			}
		}

		wipeList(member_roles);
	}
}

void RemoveAllMembersFromSet(CComPtr<IMgaSet> set)
{
	CComPtr<IMgaObject> parentObj;
	COMVERIFY(set->GetParent(&parentObj));
	CComPtr<IMgaModel> parentModel;

	bool mOK = SUCCEEDED(parentObj.QueryInterface(&parentModel)); 
	VARIANT_BOOL isInstance = 0;
	if(mOK)
	{
		COMVERIFY(parentModel->get_IsInstance(&isInstance));
	}
	if(!isInstance)
	{
		CBstr name;
		GetNamePath(set,name);
		LogWrite("Removing all members from set " + name);
		COMVERIFY(set->RemoveAll());
	}
}

void DirectRandomReference(CComPtr<IMgaReference> ref)
{
	// just want to look for a suitable target
	// and point toward it instead
	// use full tree search

	if(IsRefUsedByConns(ref))
	{
		CBstr refName;
		GetNamePath(ref,refName);
		LogWrite("Reference " + refName + " cannot be redirected because it is being used by connections");
		return;
	}

	CComPtr<IMgaObject> parentObj;
	COMVERIFY(ref->GetParent(&parentObj));
	CComPtr<IMgaModel> parentModel;

	bool mOK = SUCCEEDED(parentObj.QueryInterface(&parentModel)); 
	VARIANT_BOOL isInstance = 0;
	if(mOK)
	{
		COMVERIFY(parentModel->get_IsInstance(&isInstance));
	}
	if(!isInstance)
	{
		CBstr ref_name;
		GetNamePath(ref,ref_name);

		CComPtr<IMgaFCO> old_target;
		COMVERIFY(ref->get_Referred(&old_target));
		CBstr old_target_name = "NULL";
		if(old_target)
		{
			GetNamePath(old_target,old_target_name);
		}

		CComPtr<IMgaMetaReference> meta_ref;
		CComPtr<IMgaMetaFCO> meta_fco;
		COMVERIFY(ref->get_Meta(&meta_fco));
		COMVERIFY(meta_fco.QueryInterface(&meta_ref));
		CMetaReference wrap_meta_ref(meta_ref);
		CMetaObjList kind_list;

		// *** add error check: if no target kinds, filter retrieves all!
		wrap_meta_ref.GetTargetKinds(kind_list);
		POSITION kindPos = kind_list.GetHeadPosition();
		if(!kindPos)
		{
			LogWrite("ERROR - Reference kind " + wrap_meta_ref.GetName() + " cannot point to anything!");
			return;
		}

		CBstr kindString = "";

		while(kindPos)
		{
			CMetaFCO *currKind = (CMetaFCO *) kind_list.GetNext(kindPos);
			kindString = kindString + currKind->GetName() + " ";
		}

		// get all possible targets in the project
		CComPtr<IMgaFolder> rootFolder;
		CComPtr<IMgaFilter> filter;
		CComPtr<IMgaFCOs> allTargets;

		COMVERIFY(proj->get_RootFolder(&rootFolder));
		COMVERIFY(proj->CreateFilter(&filter));
		COMVERIFY(filter->put_Level(CComBSTR("0-")));
		COMVERIFY(filter->put_Kind(kindString.Send()));
		COMVERIFY(rootFolder->GetDescendantFCOs(filter, &allTargets));

		long numTargets;
		COMVERIFY(allTargets->get_Count(&numTargets));
		int randIdx_targets = 0;
		if(numTargets != 0)
		{
			if(!playback)
			{
				randIdx_targets = rand() % numTargets;
				toPattFile << randIdx_targets << " ";
			}
			else
				fromPattFile >> randIdx_targets;
		}
		
		bool suitableTarget = false;
		int findTargetAttempts = 0;
		while(!suitableTarget && (findTargetAttempts <= numTargets) )
		{
			int targets_counter = 0;

			ComPtrList allTargets_list;
			SortMGAObjectCollection<IMgaFCOs,IMgaFCO>(allTargets,allTargets_list);
			POSITION pos = allTargets_list.GetHeadPosition();
			while(pos)
			{
				CComPtr<IUnknown> iter_obj = allTargets_list.GetNext(pos);
				CComPtr<IMgaFCO> iter;
				COMVERIFY(iter_obj.QueryInterface(&iter));
				if(targets_counter == randIdx_targets)
				{
					suitableTarget = IsSuitableRedirectTarget(ref,iter);
					if(suitableTarget)
					{
						CBstr iterName;
						GetNamePath(iter,iterName);
						// point the reference to the new object
						LogWrite("Redirecting reference " + ref_name + " from FCO " + old_target_name  + " to FCO " + iterName);
						COMVERIFY(ref->put_Referred(iter));
						break;
					}
					else
					{
						findTargetAttempts++;
						if(!playback)
						{
							randIdx_targets = rand() % numTargets;
							toPattFile << randIdx_targets << " ";
						}
						else
							fromPattFile >> randIdx_targets;
						continue;
					}
				}
				else
				{
					targets_counter++;
				}

			}
		}

		wipeList(kind_list);	
	}
}

void CreateReferences(CComPtr<IMgaReference> ref)
{
	CComPtr<IMgaMetaReference> meta_ref;
	CComPtr<IMgaMetaFCO> meta_fco;
	COMVERIFY(ref->get_Meta(&meta_fco));
	COMVERIFY(meta_fco.QueryInterface(&meta_ref));
	CMetaReference wrap_meta_ref(meta_ref);
	CMetaObjList kind_list;

	// get parent model of the original reference and ref's role
	CComPtr<IMgaModel> ref_parent;
	CComPtr<IMgaObject> ref_parent_obj;
	CComPtr<IMgaMetaRole> ref_metarole;
	CBstr ref_parent_name;
	
	COMVERIFY(ref->GetParent(&ref_parent_obj));
	COMVERIFY(ref_parent_obj.QueryInterface(&ref_parent));
	GetNamePath(ref_parent,ref_parent_name);
	COMVERIFY(ref->get_MetaRole(&ref_metarole));

	wrap_meta_ref.GetTargetKinds(kind_list);
	POSITION kindPos = kind_list.GetHeadPosition();
	while(kindPos)
	{
		CMetaFCO *currKind = (CMetaFCO *) kind_list.GetNext(kindPos);
		CBstr currKindName = currKind->GetName();
		// get all models in the project
		CComPtr<IMgaFolder> rootFolder;
		CComPtr<IMgaFilter> filter;
		CComPtr<IMgaFCOs> targetFCOs;

		COMVERIFY(proj->get_RootFolder(&rootFolder));
		COMVERIFY(proj->CreateFilter(&filter));
		COMVERIFY(filter->put_Level(CComBSTR("0-")));
		COMVERIFY(filter->put_Kind(currKindName.Send()));
		COMVERIFY(rootFolder->GetDescendantFCOs(filter, &targetFCOs));

		ComPtrList targetFCOs_list;
		SortMGAObjectCollection<IMgaFCOs,IMgaFCO>(targetFCOs,targetFCOs_list);

		// select a single suitable target
		CComPtr<IUnknown> target_obj = targetFCOs_list.GetHead();
		CComPtr<IMgaFCO> target;
		COMVERIFY(target_obj.QueryInterface(&target));
		CBstr target_name;
		GetNamePath(target,target_name);

		// create the new reference
		CBstr newRef_name = wrap_meta_ref.GetName();
		AddIdentifier(newRef_name);
		LogWrite("Creating a " + wrap_meta_ref.GetName() + " reference named " + newRef_name + " in model " + ref_parent_name);

		CComPtr<IMgaFCO> newRef_fco;
		CComPtr<IMgaReference> newRef;
		COMVERIFY(ref_parent->CreateChildObject(ref_metarole,&newRef_fco));
		COMVERIFY(newRef_fco.QueryInterface(&newRef));
		COMVERIFY(newRef->put_Name(newRef_name.Send()));

		// direct the reference
		LogWrite("Directing reference " + newRef_name + " to FCO " + target_name);
		COMVERIFY(newRef->put_Referred(target));

	}

	wipeList(kind_list);

}

void ClearRandomReference(CComPtr<IMgaReference> ref)
{
	CComPtr<IMgaObject> parentObj;
	COMVERIFY(ref->GetParent(&parentObj));
	CComPtr<IMgaModel> parentModel;

	bool mOK = SUCCEEDED(parentObj.QueryInterface(&parentModel)); 
	VARIANT_BOOL isInstance = 0;
	if(mOK)
	{
		COMVERIFY(parentModel->get_IsInstance(&isInstance));
	}

	if(IsSuitableRedirectTarget(ref,NULL))
	{
		CBstr name;
		GetNamePath(ref,name);

		if(IsRefUsedByConns(ref))
		{
			LogWrite("Reference " + name + " cannot be cleared because it is being used by connections");
			return;
		}

		CComPtr<IMgaFCO> old_target;
		COMVERIFY(ref->get_Referred(&old_target));
		CBstr old_target_name;
		if(old_target)
		{
			GetNamePath(old_target,old_target_name);
		}
		else
		{
			old_target_name = "NULL";
		}

		LogWrite("Redirecting reference " + name + " from " + old_target_name + " to NULL");
		CComPtr<IMgaFCO> nullFCO;
		COMVERIFY(ref->put_Referred(nullFCO));
	}
}

void RevertRandomReference(CComPtr<IMgaReference> ref)
{
	CComPtr<IMgaFCO> ref_type;
	COMVERIFY(ref->get_DerivedFrom(&ref_type));
	if(ref_type)
	{
		CBstr name;
		GetNamePath(ref,name);

		if(IsRefUsedByConns(ref))
		{
			LogWrite("Reference " + name + " cannot be reverted because it is being used by connections");
			return;
		}

		CComPtr<IMgaFCO> old_target;
		COMVERIFY(ref->get_Referred(&old_target));
		CBstr old_target_name;
		if(old_target)
		{
			GetNamePath(old_target,old_target_name);
		}
		else
		{
			old_target_name = "NULL";
		}

		LogWrite("Resetting reference " + name + " from " + old_target_name + " to base");
		COMVERIFY(ref->RevertToBase());
	}
	else
	{
		// nothing; not derived so cannot revert
	}
}

bool IsNullRedirectAllowed(CComPtr<IMgaReference> ref)
{
	// possibly extend to return the possible targets as well?
	bool ret = false;

	CComPtr<IMgaObject> parent_obj;
	COMVERIFY(ref->GetParent(&parent_obj));
	CComPtr<IMgaModel> parent_model;
	COMVERIFY(parent_obj.QueryInterface(&parent_model));
	CComPtr<IMgaFCO> type_parent;
	COMVERIFY(parent_model->get_DerivedFrom(&type_parent));
	if(!type_parent)
	{
		// then parent is an archetype; ref can be redirected to anything
		ret = true;
	}
	else
	{
		CComPtr<IMgaFCO> currentTarget;
		COMVERIFY(ref->get_Referred(&currentTarget));
		COMVERIFY(ref->RevertToBase());
		CComPtr<IMgaFCO> inheritedTarget;
		COMVERIFY(ref->get_Referred(&inheritedTarget));
		if(inheritedTarget == NULL)
		{
			ret = true;
		}
		COMVERIFY(ref->put_Referred(currentTarget));
	}

	return ret;
}

bool IsSuitableRedirectTarget(CComPtr<IMgaReference> ref, CComPtr<IMgaFCO> target)
{
	// should handle NULL as well - no need for IsNullRedirectAllowed
	bool ret = false;

	CComPtr<IMgaObject> parent_obj;
	COMVERIFY(ref->GetParent(&parent_obj));
	CComPtr<IMgaModel> parent_model;
	COMVERIFY(parent_obj.QueryInterface(&parent_model));
	CComPtr<IMgaFCO> type_parent;
	COMVERIFY(parent_model->get_DerivedFrom(&type_parent));
	if(!type_parent)
	{
		// then parent is an archetype; ref can be redirected to anything
		ret = true;
	}
	else
	{
		CComPtr<IMgaFCO> currentTarget;
		COMVERIFY(ref->get_Referred(&currentTarget));

		CBstr currentTarget_nm;
		if(currentTarget)
			GetNamePath(currentTarget,currentTarget_nm);
		CString currentTargetName = currentTarget_nm;

		CBstr ref_nm;
		if(ref)
			GetNamePath(ref,ref_nm);
		CString refName = ref_nm;

		// extra check for ref derivation
		CComPtr<IMgaFCO> refBase;
		COMVERIFY(ref->get_DerivedFrom(&refBase));
		if(refBase)
		{
			COMVERIFY(ref->RevertToBase());
			CComPtr<IMgaFCO> inheritedTarget;
			COMVERIFY(ref->get_Referred(&inheritedTarget));
			// <debug>
			CBstr inheritedTarget_nm;
			CBstr target_nm;
			if(inheritedTarget)
				GetNamePath(inheritedTarget,inheritedTarget_nm);
			if(target)
				GetNamePath(target,target_nm);
			CString inheritedTargetName = inheritedTarget_nm;
			CString targetName = target_nm;
			// </debug>
			
			if(inheritedTarget == NULL)
			{
				COMVERIFY(ref->put_Referred(currentTarget));
				ret = true;
			}

			else
			{
				// now it gets interesting
				// 1: a reference to a type in a type model can only be redirected to
				// subtypes or instances of the referred-to type or any instances of its subtypes
				// 2: A reference to an instance model in a type model cannot be redirected at all 
				// down the hierarchy
				// check for NULL target case
				if(!target)
				{
					ret = false;
				}
				else
				{
					VARIANT_BOOL isInstance;
					COMVERIFY(inheritedTarget->get_IsInstance(&isInstance));
					if(isInstance)
					{
						// handles case 2
						ret = false;
					}
					else
					{
						ret = IsObjectDerived(inheritedTarget,target);
					}
					// restore 
					COMVERIFY(ref->put_Referred(currentTarget));

				}
			}	
		}
		else
		{
			ret = true;
		}
	}

	return ret;
}

bool IsObjectDerived(CComPtr<IMgaFCO> type_target, CComPtr<IMgaFCO> test_target)
{
	bool ret = false;

	CComPtr<IMgaFCOs> deriveds;
	COMVERIFY(type_target->get_DerivedObjects(&deriveds));
	MGACOLL_ITERATE(IMgaFCO,deriveds) {
		if( COM_EQUAL(MGACOLL_ITER,test_target) )
		{
			return true;
		}
		else
		{
			ret = ret || IsObjectDerived(MGACOLL_ITER,test_target);
		}
	} MGACOLL_ITERATE_END

	return ret;
}

bool GenerateRandomTestFile(CString filename, int length)
{
	ofstream testfile;
	testfile.open(filename);

	int randNum;
	
	for(int i = 0; i < length; i++)
	{
		randNum = rand() % RAND_ACTIONS;
		testfile << randNum << " ";
	}

	testfile.close();

	return true;
}

void PrintFromRandomTestFile(CString filename)
{
	ifstream infile;
	infile.open(filename);

	int randNum;
	while(!infile.eof())
	{
		infile >> randNum;
		AfxMessageBox(ltoCStr(randNum));
	}
}

void CopyOrMoveFCOsToRandomDst(CComPtr<IMgaFCOs> fcos, bool isCopy)
{
	// assume all fcos have same parent
	// just handle models as possible parents for now
	// how to get separate fcos into one collection for copying?
	// are those collections overloaded with += operators
	// or do they contain member functions to add members? ->Add

	// get the common parent 
	CComPtr<IMgaObject> parent_obj;
	CComPtr<IMgaModel> parent;
	MGACOLL_ITERATE(IMgaFCO,fcos) {
		COMVERIFY(MGACOLL_ITER->GetParent(&parent_obj));
		parent_obj.QueryInterface(&parent);		
		break;
	} MGACOLL_ITERATE_END

	if(parent)
	{
		CBstr kind;
		CComPtr<IMgaMetaFCO> meta_parent;
		COMVERIFY(parent->get_Meta(&meta_parent));
		COMVERIFY(meta_parent->get_Name((BSTR *) kind));

		CComPtr<IMgaProject> proj;
		CComPtr<IMgaFolder> rootFolder;
		CComPtr<IMgaFilter> filter;
		CComPtr<IMgaFCOs> targetParents;

		COMVERIFY(parent->get_Project(&proj));
		COMVERIFY(proj->get_RootFolder(&rootFolder));
		COMVERIFY(proj->CreateFilter(&filter));
		COMVERIFY(filter->put_Level(CComBSTR("0-")));
		COMVERIFY(filter->put_Kind(kind.Send()));
		COMVERIFY(rootFolder->GetDescendantFCOs(filter, &targetParents));

		CBstr parent_name;
		GetNamePath(parent,parent_name);

		long targetParentCount;
		COMVERIFY(targetParents->get_Count(&targetParentCount));

		int randIdx = 0;
		if(targetParentCount != 0)
		{
			if(!playback)
			{
				randIdx =  rand() % targetParentCount;
				toPattFile << randIdx << " ";
			}
			else
				fromPattFile >> randIdx;
		}
		int counter = 0;

		ComPtrList targetParents_list;
		SortMGAObjectCollection<IMgaFCOs,IMgaFCO>(targetParents,targetParents_list);
		POSITION pos = targetParents_list.GetHeadPosition();
		while(pos)
		{
			CComPtr<IUnknown> iter_obj = targetParents_list.GetNext(pos);
			CComPtr<IMgaModel> iter;
			COMVERIFY(iter_obj.QueryInterface(&iter));
			if(counter == randIdx)
			{
				CComPtr<IMgaFCOs> copies;
				LogWrite("Attempting FCO copy/move ... ");
				CBstr iter_name;
				GetNamePath(iter,iter_name);
				bool isLegal = CheckCopyOrMoveLegal(parent,iter,isCopy);
				HRESULT hr;
				if(isLegal)
				{
					try 
					{
						if(isCopy)
						{
							hr = iter->CopyFCOs(fcos,NULL,&copies);
						}
						else
						{
							hr = iter->MoveFCOs(fcos,NULL,&copies);
						}
					}
					catch(exception &) {;}
				
					if(hr == S_OK)
					{
						// need to uniquely name the copies
						ComPtrList copies_list;
						SortMGAObjectCollection<IMgaFCOs,IMgaFCO>(copies,copies_list);
						POSITION cPos = copies_list.GetHeadPosition();
						while(cPos)
						{
							CComPtr<IUnknown> copy_obj = copies_list.GetNext(cPos);
							CComPtr<IMgaFCO> copy;
							COMVERIFY(copy_obj.QueryInterface(&copy));
							CBstr name;
							COMVERIFY(copy->get_Name((BSTR *) name));
							CBstr newName;
							if(isCopy)
							{
								newName = name + "_copy";
								AddIdentifier(newName);
								COMVERIFY(copy->put_Name(newName.Send()));
								LogWrite("Copy of FCO " + name + " from " + parent_name + " to " + iter_name + " succeeded (new name is " + newName + ")");

							}
							else
							{
								LogWrite("Move of FCO " + name + " from " + parent_name + " to " + iter_name + " succeeded");
							}
						}
					}
					else
					{
						ComPtrList fcos_list;
						SortMGAObjectCollection<IMgaFCOs,IMgaFCO>(fcos,fcos_list);
						POSITION fPos = fcos_list.GetHeadPosition();
						CString namesStr;
						while(fPos)
						{
							CComPtr<IUnknown> fco_obj = fcos_list.GetNext(fPos);
							CComPtr<IMgaFCO> fco;
							COMVERIFY(fco_obj.QueryInterface(&fco));
							CBstr name;
							COMVERIFY(fco->get_Name((BSTR *) name));
							namesStr += name + " ";
						}

						if(isCopy)
						{
							LogWrite("Copy operation from " + parent_name + " to " + iter_name + " failed.  Objects: " + namesStr);
						}
						else
						{
							LogWrite("Move operation from " + parent_name + " to " + iter_name + " failed.  Objects: " + namesStr);
						}

					}
				}
				else
				{
					LogWrite("DBG: Copy operation from " + parent_name + " to " + iter_name + " not performed.");
				}
				break;
			}
			else
			{
				counter++;
			}
		}
	}
}

void PrepareCopyOrMoveChildren(CComPtr<IMgaModel> mod, bool isCopy)
{
	// for now, do to all children
	CComPtr<IMgaFCOs> children;
	COMVERIFY(mod->get_ChildFCOs(&children));
	CopyOrMoveFCOsToRandomDst(children,isCopy);

}

bool CheckCopyOrMoveLegal(CComPtr<IMgaModel> src, CComPtr<IMgaModel> dst, bool isCopy)
{
	bool ret = true;

	bool isSrcInstance = false;
	bool isDstInstance = false;
	bool isSrcSubType = false;
	bool isDstSubType = false;
	bool isSrcArcheType = false;
	bool isDstArcheType = false;

	CComPtr<IMgaFCO> src_atype;
	CComPtr<IMgaFCO> dst_atype;

	VARIANT_BOOL tester;

	// is src an instance?
	COMVERIFY(src->get_IsInstance(&tester));
	isSrcInstance = tester != 0;
	if(!isSrcInstance)
	{
		COMVERIFY(src->get_ArcheType(&src_atype));
		if(src_atype)
		{
			isSrcSubType = true;
		}
		else
		{
			isSrcArcheType = true;
		}
	}	
	// is dst an instance?
	COMVERIFY(dst->get_IsInstance(&tester));
	isDstInstance = tester != 0;
	if(!isDstInstance)
	{
		COMVERIFY(dst->get_ArcheType(&dst_atype));
		if(dst_atype)
		{
			isDstSubType = true;
		}
		else
		{
			isDstArcheType = true;
		}
	}

	// can't move ANYWHERE from a subtype or instance
	if( (!isCopy) && (isSrcSubType || isSrcInstance) )
	{
		ret = false;
	}

	// can't move/copy into an instance
	if(isDstInstance)
	{
		ret = false;
	}

	// can't copy an instance into an ancestor subtype or archetype
	// can't copy a subtype into an ancestor subtype or archetype
	CComPtr<IMgaFCO> src_fco;
	CComPtr<IMgaFCO> dst_fco;
	COMVERIFY(src.QueryInterface(&src_fco));
	COMVERIFY(dst.QueryInterface(&dst_fco));

	if( IsObjectDerived(dst_fco,src_fco) && ( !COM_EQUAL(src_fco,dst_fco) ) )
	{
		ret = false;
	}

	// cant copy/move a type into one of its subtypes or instances
	if( IsObjectDerived(src_fco,dst_fco) && ( !COM_EQUAL(src_fco,dst_fco) ) )
	{
		ret = false;
	}

	// can't copy/move an object into one of its descendants
	CComPtr<IMgaFCOs> src_desc_models;
	CComPtr<IMgaFilter> filter;

	COMVERIFY(proj->CreateFilter(&filter));
	COMVERIFY(filter->put_Level(CComBSTR("0-")));
	COMVERIFY(filter->put_ObjType(CComBSTR("OBJTYPE_MODEL")));
	COMVERIFY(src->GetDescendantFCOs(filter, &src_desc_models));


	MGACOLL_ITERATE(IMgaFCO,src_desc_models) {
		CComPtr<IMgaFCO> iter = MGACOLL_ITER;
		if(COM_EQUAL(iter,dst))
		{
			ret = false;
			break;
		}

	} MGACOLL_ITERATE_END
	

	return ret;
}

void GetFirstFCOOfKind(CMetaFCO *kind, CComPtr<IMgaFCO> &fco)
{
	// search the tree, find the first of the kind
	CComPtr<IMgaFolder> rootFolder;
	CComPtr<IMgaFilter> filter;
	CComPtr<IMgaFCOs> allKindFCOs;

	COMVERIFY(proj->get_RootFolder(&rootFolder));
	COMVERIFY(proj->CreateFilter(&filter));
	COMVERIFY(filter->put_Level(CComBSTR("0-")));
	CBstr kindStr = kind->GetName();
	COMVERIFY(filter->put_Kind(kindStr.Send()));
	COMVERIFY(rootFolder->GetDescendantFCOs(filter, &allKindFCOs));

	ComPtrList allKindFCOs_list;
	SortMGAObjectCollection<IMgaFCOs,IMgaFCO>(allKindFCOs,allKindFCOs_list);
	if(allKindFCOs_list.IsEmpty())
	{
		fco = NULL;
		return;
	}
	CComPtr<IUnknown> currFCO_unk = allKindFCOs_list.GetHead();
	COMVERIFY(currFCO_unk.QueryInterface(&fco));

	// if a deleted object found, purge from the list
	long status;
	VARIANT_BOOL isInstance;
	bool goodObj = false;
	while(!goodObj && allKindFCOs_list.GetCount() > 0)
	{
		COMVERIFY(fco->get_Status(&status));
		COMVERIFY(fco->get_IsInstance(&isInstance));
		if(status != OBJECT_EXISTS && !isInstance)
		{
			allKindFCOs_list.RemoveHead();
			if(!allKindFCOs_list.IsEmpty())
			{
				currFCO_unk = NULL;
				fco = NULL;
				currFCO_unk = allKindFCOs_list.GetHead();
				COMVERIFY(currFCO_unk.QueryInterface(&fco));
			}
		}
		else
		{
			goodObj = true;
		}
	}

	if(!goodObj)
	{
		fco = NULL;
	}

}

void CreateRandomFCO(CMetaFCO *kind, CComPtr<IMgaFCO> &fco)
{
	// parent may be a folder or an fco - usedinroles, usedinfolders
	CComPtr<IMgaMetaModel> meta_parent;
	CComPtr<IMgaMetaFolders> parentFolders;
	CComPtr<IMgaMetaRoles> roles;
	CComPtr<IMgaMetaRole> meta_role;

	COMVERIFY(kind->GetCOM()->get_UsedInRoles(&roles));
	long rCount;
	COMVERIFY(roles->get_Count(&rCount));
	if(rCount == 0)
	{
		COMVERIFY(kind->GetCOM()->get_UsedInFolders(&parentFolders));
		ComPtrList parentFolders_list;
		SortMGAObjectCollection<IMgaMetaFolders,IMgaMetaFolder>(parentFolders,parentFolders_list);
		POSITION fPos = parentFolders_list.GetHeadPosition();

		if(!parentFolders_list.IsEmpty())
		{
			// *** pick a meta folder
			// just take the first one
			CComPtr<IUnknown> meta_fdr_unk = parentFolders_list.GetHead();
			CComPtr<IMgaMetaFolder> meta_fdr;
			COMVERIFY(meta_fdr_unk.QueryInterface(&meta_fdr));

			// *** find one of these folders

			// *** need to use get_ChildFolders recursively through a helper function
			CComPtr<IMgaFolder> rootFdr;
			COMVERIFY(proj->get_RootFolder(&rootFdr));
			ComPtrList descFdrs;
			GetDescendantFolders(rootFdr,descFdrs);

			// take the first one whose meta matches
			POSITION descPos = descFdrs.GetHeadPosition();
			while(descPos)
			{
				CComPtr<IMgaFolder> holderFdr;
				CBstr holderFdr_name;

				CComPtr<IUnknown> currFdr_unk = descFdrs.GetNext(descPos);
				COMVERIFY(currFdr_unk.QueryInterface(&holderFdr));
				GetNamePath(holderFdr,holderFdr_name);
				CComPtr<IMgaMetaFolder> meta_holderFdr;
				COMVERIFY(holderFdr->get_MetaFolder(&meta_holderFdr));
				if(COM_EQUAL(meta_holderFdr,meta_fdr))
				{
					// create the object and return through fco
					CBstr fco_name = kind->GetName();
					AddIdentifier(fco_name);

					LogWrite("Creating FCO " + fco_name + " in folder " + holderFdr_name);
					COMVERIFY(holderFdr->CreateRootObject(kind->GetCOM(),&fco));
					COMVERIFY(fco->put_Name(fco_name.Send()));
					return;
				}
			}

			fco = NULL;
			return;
		}
		else
		{
			fco = NULL;
			return;
		}
	}
	else
	{
		ComPtrList roles_list;
		SortMGAObjectCollection<IMgaMetaRoles,IMgaMetaRole>(roles,roles_list);

		// just pick the first role
		CComPtr<IUnknown> meta_role_unk = roles_list.GetHead();
		COMVERIFY(meta_role_unk.QueryInterface(&meta_role));
		COMVERIFY(meta_role->get_ParentModel(&meta_parent));

	}
	
	// only supports models currently
	// search the tree, find where this can be created, create it, and return it thru fco
	CComPtr<IMgaFolder> rootFolder;
	CComPtr<IMgaFilter> filter;
	CComPtr<IMgaFCOs> allModels;

	COMVERIFY(proj->get_RootFolder(&rootFolder));
	COMVERIFY(proj->CreateFilter(&filter));
	COMVERIFY(filter->put_Level(CComBSTR("0-")));
	COMVERIFY(filter->put_ObjType(CComBSTR("OBJTYPE_MODEL")));
	COMVERIFY(rootFolder->GetDescendantFCOs(filter, &allModels));

	ComPtrList allModels_list;
	SortMGAObjectCollection<IMgaFCOs,IMgaFCO>(allModels,allModels_list);
	POSITION amPos = allModels_list.GetHeadPosition();
	while(amPos)
	{
		CComPtr<IUnknown> currModel_obj = allModels_list.GetNext(amPos);
		CComPtr<IMgaModel> currModel;
		COMVERIFY(currModel_obj.QueryInterface(&currModel));
		CBstr currModel_name;
		GetNamePath(currModel,currModel_name);

		CComPtr<IMgaMetaFCO> currMeta;
		COMVERIFY(currModel->get_Meta(&currMeta));
		if(COM_EQUAL(meta_parent,currMeta))
		{
			// create the object
			CBstr fco_name;
			COMVERIFY(meta_role->get_Name((BSTR *) fco_name));
			AddIdentifier(fco_name);

			LogWrite("Creating FCO " + fco_name + " in model " + currModel_name);
			COMVERIFY(currModel->CreateChildObject(meta_role,&fco));
			COMVERIFY(fco->put_Name(fco_name.Send()));
			break;
		}
	}

}

void ReadConfigFile()
{
	COMVERIFY(proj->get_Name((BSTR *) projName));
	pattFileName = projName + "-pattern.txt";
	logFileName = projName + "-blasterlog.txt";

	ifstream cfgFile;
	cfgFile.open("blastcfg.txt");
	while(!cfgFile.eof())
	{
		CString currLine;
		cfgFile.getline(currLine.GetBuffer(256),256);
		currLine.ReleaseBuffer();
		int eqPos = currLine.Find("=");
		CString name = currLine.Left(eqPos);
		CString value = currLine.Right(currLine.GetLength() - 1 - eqPos);
		value.TrimRight();
		if(name == "saveFrequency")
		{
			saveFrequency = atoi(value);
		}
		else if(name == "depthLimit")
		{
			depthLimit = atoi(value);
		}
		else if(name == "useFQNames")
		{	
			if(value == "true")
			{
				useFQNames = true;
			}
			else if(value == "false")
			{
				useFQNames = false;
			}
			else
			{
				cerr << "useFQNames parameter in config file invalid.  Aborting.";
				throw("config file error");
			}
		}
		else if(name == "useExpCheckpoints")
		{	
			if(value == "true")
			{
				useExpCheckpoints = true;
			}
			else if(value == "false")
			{
				useExpCheckpoints = false;
			}
			else
			{
				cerr << "useExpCheckpoints parameter in config file invalid.  Aborting.";
				throw("config file error");
			}
		}
		else if(name == "logFileName")
		{
//			value.Remove('"');
//			logFileName = value;
		}
		else if(name == "useUIDs")
		{
			if(value == "true")
			{
				useUIDs = true;
			}
			else if(value == "false")
			{
				useUIDs = false;
			}
			else
			{
				cerr << "useUIDs parameter in config file invalid.  Aborting.";
				throw("config file error");
			} 
		}
		else if(name == "deleteWhenDone")
		{
			if(value == "true")
			{
				deleteWhenDone = true;
			}
			else if(value == "false")
			{
				deleteWhenDone = false;
			}
			else
			{
				cerr << "deleteWhenDone parameter in config file invalid.  Aborting.";
				throw("config file error");
			} 

		}
		else if(name == "testBlast")
		{
			if(value == "true")
			{
				testBlast = true;
			}
			else if(value == "false")
			{
				testBlast = false;
			}
			else
			{
				cerr << "testBlast parameter in config file invalid.  Aborting.";
				throw("config file error");
			} 

		}
		else if(name == "testRandom")
		{
			if(value == "true")
			{
				testRandom = true;
			}
			else if(value == "false")
			{
				testRandom = false;
			}
			else
			{
				cerr << "testRandom parameter in config file invalid.  Aborting.";
				throw("config file error");
			} 
		}
		else if(name == "testTypesAndInstances")
		{
			if(value == "true")
			{
				testTypesAndInstances = true;
			}
			else if(value == "false")
			{
				testTypesAndInstances = false;
			}
			else
			{
				cerr << "testTypesAndInstances parameter in config file invalid.  Aborting.";
				throw("config file error");
			} 
		}
		else if(name == "randCount")
		{
			randCount = atoi(value);
		}
		else if(name == "genPattern")
		{
			if(value == "true")
			{
				genPattern = 0;
			}
			else if(value == "false")
			{
				genPattern = 1;
			}
			else
			{
				cerr << "genPattern parameter in config file invalid.  Aborting.";
				throw("config file error");
			} 

		}
		else if(name == "pattFileName")
		{
//			value.Remove('"');			
//			pattFileName = value;

		}
		else if(name == "paradigms")
		{
			value.Remove('"');
			paradigms = value;
		}
		else if(name == "emailResults")
		{
			if(value == "true")
			{
				emailResults = true;
			}
			else if(value == "false")
			{
				emailResults = false;
			}
			else
			{
				cerr << "emailResults parameter in config file invalid.  Aborting.";
				throw("config file error");
			}
		}
		else if(name == "emailAddresses")
		{
			ParseDelimitedString(value,emailAddresses,',');
		}
		else
		{
			cerr << "Invalid parameter in config file: " << name << "\nAborting.";
			throw("config file error");
		}
	}
}

void DeleteRandomFCO(CComPtr<IMgaFCO> fco)
{

	long obj_status;
	COMVERIFY(fco->get_Status(&obj_status));

	CBstr myName;
	if(obj_status == OBJECT_EXISTS)
	{
		GetNamePath(fco,myName);
	}
	else
	{
		COMVERIFY(fco->get_Name((BSTR *) myName));
	}

	if(obj_status == OBJECT_EXISTS)
	{
		CComPtr<IMgaObject> parent;
		COMVERIFY(fco->GetParent(&parent));
		CComPtr<IMgaFCO> parent_fco;
		parent.QueryInterface(&parent_fco);
		bool deleteOK;
		if(parent_fco)
		{
			CComPtr<IMgaFCO> archetype;
			COMVERIFY(parent_fco->get_ArcheType(&archetype));
			if(!archetype)
			{
				deleteOK = true;
			}
			else
			{
				deleteOK = false;
			}
		}
		else
		{
			// must be parent folder; safe to delete
			deleteOK = true;
		}
		if(deleteOK)
		{
			POSITION pos = allFCOs_list.GetHeadPosition();
			while(pos)
			{
				CComPtr<IUnknown> iter_unk = allFCOs_list.GetAt(pos);
				if(COM_EQUAL(fco,iter_unk))
				{
					long opmask_old;

					COMVERIFY(proj->get_OperationsMask(&opmask_old));
					COMVERIFY(proj->put_OperationsMask(0));
					LogWrite("Deleting object " + myName);
					HRESULT hr = fco->DestroyObject();
					if(hr != S_OK)
					{
						LogWrite("Attempted to delete object " + myName + " , but could not because of other object dependencies.");
					}
					else
					{
						allFCOs_list.RemoveAt(pos);
						iter_unk.p->Release();						
					}
					COMVERIFY(proj->put_OperationsMask(opmask_old));
					// possible problem: when this destroy removes other objects, those objects aren't removed from the list.
					// if no way to detect which objects are destroyed, will have to set opmask to fail the operation and let me recover
					break;
				}
				else
				{
					allFCOs_list.GetNext(pos);
				}
			}
		}

	}
	else
	{
		LogWrite("Attempted to delete object " + myName + " , but it has already been deleted.");
	}
	
}

bool IsRefUsedByConns(CComPtr<IMgaReference> ref)
{
	CComPtr<IMgaConnPoints> cpts;
	COMVERIFY(ref->get_UsedByConns(&cpts));
	long count;
	COMVERIFY(cpts->get_Count(&count));
	if(count == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void SendMail(CString msg)
{
	CString subject = "Blaster results for " + projName;

	if(emailResults)
	{
		LPMAPILOGON lpfnMAPILogon;
		LPMAPISENDMAIL lpfnMAPISendMail;
		LPMAPILOGOFF lpfnMAPILogoff;

		MapiRecipDesc *recipients = new MapiRecipDesc[emailAddresses.GetCount()];
		char **addys = new char*[emailAddresses.GetCount()];

		POSITION pos = emailAddresses.GetHeadPosition();
		int posCount = 0;
		while(pos)
		{
			CString currAddr = emailAddresses.GetNext(pos);
			currAddr = "SMTP:" + currAddr;
			addys[posCount] = new char[currAddr.GetLength() + 1];
			strcpy(addys[posCount],currAddr);
			recipients[posCount].ulReserved = 0;
			recipients[posCount].ulRecipClass = MAPI_TO;
			recipients[posCount].lpszName = "GME Developer";
			recipients[posCount].lpszAddress = addys[posCount];
			recipients[posCount].ulEIDSize = 0;
			recipients[posCount].lpEntryID = NULL;
			posCount++;
		}

		MapiMessage message =
		{

			0, subject.GetBuffer(subject.GetLength()),

			msg.GetBuffer(msg.GetLength()),

			NULL, NULL, NULL, 0, NULL, emailAddresses.GetCount(), recipients, 0, NULL

		};
    
		LHANDLE lhSession;
		struct HINSTANCE__ * hMAPILib;

		hMAPILib = LoadLibrary("MAPI32.DLL");

		lpfnMAPILogon =
			(LPMAPILOGON)GetProcAddress(hMAPILib, "MAPILogon");

		lpfnMAPISendMail =
			(LPMAPISENDMAIL)GetProcAddress(hMAPILib, "MAPISendMail");

		lpfnMAPILogoff =
			(LPMAPILOGOFF)GetProcAddress(hMAPILib, "MAPILogoff");

		(*lpfnMAPILogon)(0, NULL, NULL, 0, 0,
						 &lhSession);
		(*lpfnMAPISendMail)(lhSession, 0, &message, 0, 0);
		(*lpfnMAPILogoff)(lhSession, 0, 0, 0);

		FreeLibrary(hMAPILib);
		subject.ReleaseBuffer();
		msg.ReleaseBuffer();

		delete[] addys;
		delete[] recipients;

	}
}

void GetDescendantFolders(CComPtr<IMgaFolder> fdr, ComPtrList &list)
{
	CComPtr<IMgaFolders> childFdrs;
	COMVERIFY(fdr->get_ChildFolders(&childFdrs));
	ComPtrList sortedChildren;
	SortMGAObjectCollection<IMgaFolders,IMgaFolder>(childFdrs,sortedChildren);

	POSITION childPos = sortedChildren.GetHeadPosition();
	while(childPos)
	{
		CComPtr<IUnknown> currFdr_unk = sortedChildren.GetNext(childPos);
		CComPtr<IMgaFolder> currFdr;
		COMVERIFY(currFdr_unk.QueryInterface(&currFdr));
		GetDescendantFolders(currFdr,list);
		list.AddTail(currFdr);
		currFdr.p->AddRef();
	}
}

bool AreConnectionAspectsOK(CMetaRole *connRole, CComPtr<IMgaFCO> srcHolder, CComPtr<IMgaFCO> dstHolder, CComPtr<IMgaModel> connModel)
{
	// verify that srcHolder and dstHolder have connModel as their common parent
	CComPtr<IMgaObject> srcHolder_parent;
	CComPtr<IMgaObject> dstHolder_parent;
	COMVERIFY(srcHolder->GetParent(&srcHolder_parent));
	COMVERIFY(dstHolder->GetParent(&dstHolder_parent));
	ASSERT(COM_EQUAL(srcHolder_parent,dstHolder_parent) && COM_EQUAL(srcHolder_parent,connModel));
	
	CComPtr<IMgaMetaParts> meta_parts;
	COMVERIFY(connRole->GetCOM()->get_Parts(&meta_parts));
	ComPtrList meta_parts_list;
	SortMGAObjectCollection<IMgaMetaParts,IMgaMetaPart>(meta_parts,meta_parts_list);
	POSITION mpPos = meta_parts_list.GetHeadPosition();
	while(mpPos)
	{
		CComPtr<IUnknown> metaPart_unk = meta_parts_list.GetNext(mpPos);
		CComPtr<IMgaMetaPart> metaPart;
		COMVERIFY(metaPart_unk.QueryInterface(&metaPart));
		CComPtr<IMgaMetaAspect> connAspect;
		COMVERIFY(metaPart->get_ParentAspect(&connAspect));
		CComPtr<IMgaPart> srcHolderPart;
		COMVERIFY(srcHolder->get_Part(connAspect,&srcHolderPart));
		CComPtr<IMgaPart> dstHolderPart;
		COMVERIFY(dstHolder->get_Part(connAspect,&dstHolderPart));
		if(srcHolderPart && dstHolderPart)
		{
			return true;
		}
	}

	// couldn't find an aspect that contained all three
	return false;
}