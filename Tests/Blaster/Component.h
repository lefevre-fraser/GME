#ifndef GME_INTERPRETER_H
#define GME_INTERPRETER_H

//#include "Builder2000.h"
#include <exception>
#include <windows.h>
#include <stdio.h>
#include <mapi.h>

#include "GMECOM.h"
#ifndef __COMHELP_H
#include "ComHelp.h"
#endif

class CMetaObj;
class CMetaFolder;
class CMetaRole;
class CMetaAttribute;

typedef CTypedPtrList<CPtrList, CMetaObj *> CMetaObjList;
typedef CTypedPtrList<CPtrList, IMgaObject *> MgaObjList;
typedef CTypedPtrList<CPtrList, IMgaAttribute *> MgaAttrList;
typedef CTypedPtrList<CPtrList, IMgaConnPoint *> MgaConnPtList;
typedef CTypedPtrList<CPtrList, IUnknown *> ComPtrList;

class CComponent {
public:
//	void Invoke(CBuilder &builder,CBuilderObjectList &selected, long param);
	void Invoke(IMgaProject *gme, IMgaFCOs *psa, long param);	// CYT4
};

class CMetaObj : public CObject {
public:
	CString GetName(void);
	CMetaObj(CComPtr<IMgaMetaBase> obj) { this->obj = obj; }
	CMetaObj() { }
	CMetaObj& operator=(const CMetaObj &o) { this->obj = o.obj; return *this; }
	void GetAttributes(CMetaObjList &attlist);
	void DeepBlast();
	void BlastAttributes();
	CComPtr<IMgaMetaBase> GetCOM() { return obj; }

protected:
	CComPtr<IMgaMetaBase> obj;
};

class CMetaFolder : public CMetaObj {
public:
	CMetaFolder(CComPtr<IMgaMetaFolder> fdr) { this->fdr = fdr; fdr.QueryInterface(&obj); }
	CMetaFolder& operator=(const CMetaFolder &f) { this->obj = f.obj; this->fdr = f.fdr; return *this; }
	CComPtr<IMgaMetaFolder> GetCOM() { return fdr; }
	void GetFCOs(CMetaObjList &fcolist);
	void GetFolders(CMetaObjList &fdrlist);
protected:
	CComPtr<IMgaMetaFolder> fdr;
};

class CMetaFCO : public CMetaObj {
public:
	CMetaFCO(CComPtr<IMgaMetaFCO> fco) { this->fco = fco; fco.QueryInterface(&obj); }
	CMetaFCO() { }
	CMetaFCO& operator=(const CMetaFCO &f) { this->obj = f.obj; this->fco = f.fco; return *this; }
	CComPtr<IMgaMetaFCO> GetCOM() { return fco; }
	void GetRoles(CMetaObjList &list);
protected:
	CComPtr<IMgaMetaFCO> fco;
};

class CMetaRole : public CMetaObj {
public:
	CMetaRole(CComPtr<IMgaMetaRole> role) { this->role = role; role.QueryInterface(&obj); }
	CMetaRole& operator=(const CMetaRole &r) { this->obj = r.obj; this->role = r.role; return *this; }
	CComPtr<IMgaMetaRole> GetCOM() { return role; }
protected:
	CComPtr<IMgaMetaRole> role;
};

class CMetaAttribute : public CMetaObj {
public:
	CMetaAttribute(CComPtr<IMgaMetaAttribute> attr) { this->attr = attr; attr.QueryInterface(&obj); }
	CMetaAttribute& operator=(const CMetaAttribute &a) { this->obj = a.obj; this->attr = a.attr; return *this; }
	CComPtr<IMgaMetaAttribute> GetCOM() { return attr; }
protected:
	CComPtr<IMgaMetaAttribute> attr;
};

class CMetaReference : public CMetaFCO {
public:
	CMetaReference(CComPtr<IMgaMetaReference> ref) { this->ref = ref; ref.QueryInterface(&obj); }
	CMetaReference& operator=(const CMetaReference &r) { this->obj = r.obj; this->fco = r.fco; this->ref = r.ref; return *this; }
	CComPtr<IMgaMetaReference> GetCOM() { return ref; }
	void GetTargetRoles(CMetaObjList &list, CComPtr<IMgaModel> mod);
	void GetTargetKinds(CMetaObjList &list);
protected:
	CComPtr<IMgaMetaReference> ref;
};

class CMetaSet : public CMetaFCO {
public:
	CMetaSet(CComPtr<IMgaMetaSet> set) { this->set = set; set.QueryInterface(&obj); }
	CMetaSet& operator=(const CMetaSet &s) { this->obj = s.obj; this->fco = s.fco; this->set = set; }
	CComPtr<IMgaMetaSet> GetCOM() { return set; }
	void GetMemberRoles(CMetaObjList &list, CMetaRole *setRole);
protected:
	CComPtr<IMgaMetaSet> set;
};

// global scope functions

void GetNamePath(CComPtr<IMgaFCO> fco, CBstr &namepath);
void GetNamePath(CComPtr<IMgaModel> mod, CBstr &namepath);
void GetNamePath(CComPtr<IMgaFolder> fdr, CBstr &namepath);
void GetNamePath(CComPtr<IMgaObject> object,CString &namePath);
void GetMGASortKey(IMgaObject *o, CBstr &key);
void GetMGASortKey(IMgaAttribute *a, CBstr &key);
void GetMGASortKey(IMgaMetaBase *mb, CBstr &key);
void GetMGASortKey(IMgaMetaEnumItem *mei, CBstr &key);
void GetMGASortKey(IMgaMetaPointerSpec *mps, CBstr &key);
void GetMGASortKey(IMgaMetaPointerItem *mpi, CBstr &key);

template<class PTR_TYPE>
void InsertIntoMGAObjectCollection(CComPtr<PTR_TYPE> ptr, ComPtrList &sList);

template<class CYT_COLL, class CYT_COLL_TYPE>
void SortMGAObjectCollection(CComPtr<CYT_COLL> coll, ComPtrList &sList);

//void ParseRoleString(CString role_str,CStringList& role_list);
void ParseDelimitedString(CString str,CStringList& list, char delimiter);
CString ltoCStr(long n);
void AddIdentifier(CBstr& str);
void GetExtendedName(CComPtr<IMgaObject> object, CString &extName,CString separator,bool startWithRoot);
void wipeList(CMetaObjList &objlist);

void GetMetaFolders(CComPtr<IMgaMetaFolder> fdr);
void GetFolderMetaFCOs(CComPtr<IMgaMetaFolder> fdr);
void GetModelMetaFCOs(CComPtr<IMgaMetaModel> mod);
void CreateAllPossibleFolders(CComPtr<IMgaFolder> fdr);
void CreateAllPossibleFCOs(CComPtr<IMgaModel> mod);
void CreateAllPossibleFCOs(CComPtr<IMgaFolder> fdr);
void DeleteSelfAndAllDescendants(CComPtr<IMgaFolder> fdr);
void DeleteSelfAndAllDescendants(CComPtr<IMgaFCO> fco);
void CreateConnections(CMetaRole *role,CComPtr<IMgaModel> mod);
void ConnectToAllPossibleDsts(CMetaRole *role, CComPtr<IMgaModel> conn_mod, CComPtr<IMgaModel> src_mod, CComPtr<IMgaMetaRole> srcRole, CComPtr<IMgaFCO> src_ref, CComPtr<IMgaMetaPointerItems> dst_items);
bool AreConnectionAspectsOK(CMetaRole *connRole, CComPtr<IMgaFCO> srcHolder, CComPtr<IMgaFCO> dstHolder, CComPtr<IMgaModel> connModel);
void SetAllAttributes(CComPtr<IMgaFCO> fco);
void AddAllPossibleMembersToSet(CComPtr<IMgaSet> set);

void CreateSubTypesAndInstances(CComPtr<IMgaModel> mod);
void BlastSubTypesAndInstances(CComPtr<IMgaFolder> fdr);

void BlastFolder(CComPtr<IMgaFolder> fdr, int depth = 0);
void BlastFCO(CComPtr<IMgaFCO> fco, int depth = 0);
void BlastProject(CComPtr<IMgaProject> proj);
void BlastReferences(CComPtr<IMgaProject> proj);

void InitRandomFCOs();
CComPtr<IMgaFCO> GetRandomFCO();
bool SetRandomAttribute(CComPtr<IMgaFCO> fco);
bool ClearRandomAttribute(CComPtr<IMgaFCO> fco);
void CreateRandomChild(CComPtr<IMgaModel> mod);
void CreateRandomFCO(CMetaFCO *kind, CComPtr<IMgaFCO> &fco);
void GetFirstFCOOfKind(CMetaFCO *kind, CComPtr<IMgaFCO> &fco);
void GetDescendantFolders(CComPtr<IMgaFolder> fdr, ComPtrList &list);
CComPtr<IMgaFCO> CreateRandomConnection(CMetaRole *role, CComPtr<IMgaModel> mod);
CComPtr<IMgaFCO> ConnectToRandomDst(CMetaRole *role, CComPtr<IMgaModel> conn_mod, CComPtr<IMgaModel> src_mod, CComPtr<IMgaMetaRole> srcRole, CComPtr<IMgaFCO> src_ref, CComPtr<IMgaMetaPointerItems> dst_items);
void RemoveRandomMemberFromSet(CComPtr<IMgaSet> set);
void AddRandomMemberToSet(CComPtr<IMgaSet> set);
void RemoveAllMembersFromSet(CComPtr<IMgaSet> set);
void DirectRandomReference(CComPtr<IMgaReference> ref);
void ClearRandomReference(CComPtr<IMgaReference> ref);
void RevertRandomReference(CComPtr<IMgaReference> ref);
void DeleteRandomFCO(CComPtr<IMgaFCO> fco);
void CreateReferences(CComPtr<IMgaReference> ref);
bool IsNullRedirectAllowed(CComPtr<IMgaReference> ref);
bool IsRefUsedByConns(CComPtr<IMgaReference> ref);
bool IsSuitableRedirectTarget(CComPtr<IMgaReference> ref, CComPtr<IMgaFCO> target);
bool IsObjectDerived(CComPtr<IMgaFCO> type_target, CComPtr<IMgaFCO> test_target);
void PrepareCopyOrMoveChildren(CComPtr<IMgaModel> mod, bool isCopy);
void CopyOrMoveFCOsToRandomDst(CComPtr<IMgaFCOs> fcos, bool isCopy);
bool CheckCopyOrMoveLegal(CComPtr<IMgaModel> src, CComPtr<IMgaModel> dst, bool isCopy);
void PerformRandomTesting(int count);

void LogWrite(CString text);
void ReadConfigFile();
bool GenerateRandomTestFile(CString filename, int length);
void PrintFromRandomTestFile(CString filename);

void SendMail(CString msg);

#endif // whole file
