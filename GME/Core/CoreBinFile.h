
#ifndef MGA_COREBINFILE_H
#define MGA_COREBINFILE_H

#include <fstream>//fstream.h
#include <list>//slist
#include <map>
#include <vector>
#include <algorithm>

#include "windows.h"
class membuf
{
	public:
	membuf() : 
		begin(0), end(0), hFile(INVALID_HANDLE_VALUE), hFileMappingObject(INVALID_HANDLE_VALUE)
		{ }
	
	int open(const char* filename) {
		hFile = CreateFileA(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);
		if (hFile == INVALID_HANDLE_VALUE) {
			return 1;
		}
		hFileMappingObject = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
		if (hFileMappingObject == INVALID_HANDLE_VALUE) {
			return 1;
		}
		begin = (char*)MapViewOfFile(hFileMappingObject, FILE_MAP_READ, 0, 0, 0);
		if (begin == NULL) {
			return 1;
		}
		DWORD filesize = GetFileSize(hFile, NULL);
		if (filesize == INVALID_FILE_SIZE) {
			return 1;
		}
		end = begin + filesize;
		return 0;
	}

	~membuf() {
		UnmapViewOfFile(begin);
		CloseHandle(hFileMappingObject);
		CloseHandle(hFile);
	}

	char* getBegin() const {
		return begin;
	}
	char* getEnd() const {
		return end;
	}

	private:
		membuf(const membuf&);
		membuf& operator=(const membuf&);

		HANDLE hFile,hFileMappingObject;
		char* begin, * end;
};

class CCoreBinFile;
class BinAttrUnion;

// --------------------------- BinAttr
class __declspec(novtable) BinAttrBase
{
public:
	BinAttrBase() : attrid(ATTRID_NONE) { }
	BinAttrBase(attrid_type attrid) : attrid(attrid) { }
	virtual ~BinAttrBase() { }

	attrid_type attrid;

	static BinAttrBase *Create(BinAttrBase& attr, valtype_type valtype);

	virtual valtype_type GetValType() const NOTHROW = 0;
	virtual void Set(CCoreBinFile *binfile, VARIANT p) = 0;
	virtual void Get(CCoreBinFile *binfile, VARIANT *p) const = 0;
	virtual void Write(CCoreBinFile *binfile) const = 0;
	virtual void Read(CCoreBinFile *binfile) = 0;
	// virtual move constructor
	virtual void move(BinAttrUnion&& dest) = 0;
};

class __declspec(novtable) BinAttrUnion : public BinAttrBase
{
public:
	BinAttrUnion() { }
	explicit BinAttrUnion(attrid_type attrid) : BinAttrBase(attrid) { }
	virtual ~BinAttrUnion() { }

	virtual valtype_type GetValType() const NOTHROW { DebugBreak(); return 0; }
	virtual void Set(CCoreBinFile *binfile, VARIANT p) { DebugBreak(); }
	virtual void Get(CCoreBinFile *binfile, VARIANT *p) const { DebugBreak(); }
	virtual void Write(CCoreBinFile *binfile) const { DebugBreak(); }
	virtual void Read(CCoreBinFile *binfile) { DebugBreak(); }
	virtual void move(BinAttrUnion&& dest) { DebugBreak(); }

	// that is a subtype of BinAttrUnion
	// that must not be BinAttrUnion because of __declspec(novtable)
	BinAttrUnion(BinAttrUnion&& that) {
		// volatile to read the vtable of that
		BinAttrUnion* volatile that_ = &that;
		that_->move(std::move(*this));
	}

	BinAttrUnion& operator=(BinAttrUnion&& that) {
		BinAttrUnion* volatile that_ = &that;
		that_->move(std::move(*this));
		return *this;
	}
	BinAttrUnion(const BinAttrUnion& that) {
		// FIXME
	}
	// BinAttrUnion is guaranteed to have enough space to contain any BinAttr<*>
	// (Ideally we'd do union { char [sizeof(BinAttrBase) - sizeof(BinAttr<*>) }, but that requires method definitions for BinAttr<*>::* to be separated from the declaration)
#ifdef _DEBUG
	int pad[5];
#else
	int pad[2];
#endif
};

typedef std::vector<BinAttrUnion> binattrs_type;
typedef binattrs_type::iterator binattrs_iterator;

template<valtype_enum VALTYPE>
class BinAttr;


// --------------------------- BinObject

class BinObject
{
public:
	~BinObject() { DestroyAttributes(); }

	// binattrs actually contains elements of type BinAttr<*>
	binattrs_type binattrs;
	bool deleted;

	bool HasGuidAndStatAttributes( bool* p_guidFound, bool* p_statusFound);
	void CreateGuidAttributes( CCoreBinFile* p_bf);
	void CreateStatusAttribute( CCoreBinFile* p_bf);

	BinAttrBase *Find(attrid_type attrid)
	{
		binattrs_iterator i = binattrs.begin();
		binattrs_iterator e = binattrs.end();
		while( i != e && (i)->attrid != attrid )
			++i;

		if( i == e )
			HR_THROW(E_BINFILE);

		return &*i;
	}

	void CreateAttributes(ICoreMetaObject *metaobject);
	void DestroyAttributes();
	void Read(CCoreBinFile *binfile);
	void Write(CCoreBinFile *binfile);

	bool HasEmptyPointers() const;
};

typedef stdext::hash_map< metaobjidpair_type
                        , BinObject
                        , metaobjid2pair_hashfunc
                        > objects_type;
typedef objects_type::iterator objects_iterator;


// --------------------------- CCoreBinFile

class ATL_NO_VTABLE CCoreBinFile : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<ICoreStorage, &IID_ICoreStorage, &LIBID_MGACoreLib>,
	public ISupportErrorInfoImpl<&IID_ICoreStorage>,
	public CComCoClass<CCoreBinFile, &CLSID_CoreBinFile>
{
public:
	CCoreBinFile();
	~CCoreBinFile();

BEGIN_COM_MAP(CCoreBinFile)
	COM_INTERFACE_ENTRY(ICoreStorage)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

DECLARE_REGISTRY_RESOURCEID(IDR_COREBINFILE)

// ------- MetaProject

public:
	CComObjPtr<ICoreMetaProject> metaproject;
	bindata metaprojectid;

	STDMETHODIMP get_MetaProject(ICoreMetaProject **p);
	STDMETHODIMP put_MetaProject(ICoreMetaProject *p);

	void OpenMetaProject();
	void CloseMetaProject() NOTHROW;

// ------- MetaObject

public:
	CComObjPtr<ICoreMetaObject> metaobject;
	metaid_type metaid;

	STDMETHODIMP get_MetaObject(ICoreMetaObject **p);
	STDMETHODIMP put_MetaObject(ICoreMetaObject *p);

	STDMETHODIMP get_MetaID(metaid_type *p);
	STDMETHODIMP put_MetaID(metaid_type p);

	void OpenMetaObject();
	void CloseMetaObject() NOTHROW;

// ------- MetaAttribute

public:
	CComObjPtr<ICoreMetaAttribute> metaattribute;
	attrid_type attrid;

	STDMETHODIMP get_MetaAttribute(ICoreMetaAttribute **p);
	STDMETHODIMP put_MetaAttribute(ICoreMetaAttribute *p);

	STDMETHODIMP get_AttrID(attrid_type *p);
	STDMETHODIMP put_AttrID(attrid_type p);

	void OpenMetaAttribute();
	void CloseMetaAttribute() NOTHROW;

// ------- Ios

public:
	char* cifs;
	char* cifs_eof;

	std::ofstream ofs;

public:
#define CoreBinFile_read(a, size) if (size > cifs_eof - cifs) HR_THROW(E_FILEOPEN); memcpy(&a, cifs, size); cifs += size;
	void read(unsigned char &a) { CoreBinFile_read(a, sizeof(unsigned char)); }
	void read(short &a) { CoreBinFile_read(a, sizeof(short)); }
	void read(int &a) { CoreBinFile_read(a, sizeof(int)); }
	void read(long &a)  { CoreBinFile_read(a, sizeof(long)); }
	void read(double &a)  { CoreBinFile_read(a, sizeof(double)); }
	void read(CComBstrObj &a);
	void read(bindata &a);
	void read(unsigned char*& b, int& len);

	void write(unsigned char a) { ofs.write((const char*)&a, sizeof(unsigned char)); }
	void write(short a) { ofs.write((const char*)&a, sizeof(short)); }
	void write(int a) { ofs.write((const char*)&a, sizeof(int)); }
	void write(long a) { ofs.write((const char*)&a, sizeof(long)); }
	void write(double a) { ofs.write((const char*)&a, sizeof(double)); }
	void write(const CComBstrObj &a);
	void write(const bindata &a);
	void write(const unsigned char* a, int len);

// ------- Attribute

public:
	typedef std::map<BinAttrBase*, CComVariant> undos_type;
	typedef undos_type::iterator undos_iterator;

	undos_type undos;

	STDMETHODIMP get_AttributeValue(VARIANT *p);
	STDMETHODIMP put_AttributeValue(VARIANT p);

// ------- Object

public:
	objects_type objects;
	objects_iterator opened_object;
	bool isEmpty;

	typedef stdext::hash_map<metaid_type, objid_type> maxobjids_type;
	typedef maxobjids_type::iterator maxobjids_iterator;

	maxobjids_type maxobjids;
	std::list<objects_iterator> deleted_objects;//slist
	std::list<objects_iterator> created_objects;//slist

	struct resolve_type
	{
		objects_iterator obj;
		attrid_type attrid;
		metaobjidpair_type idpair;
	};

	typedef std::list<resolve_type> resolvelist_type;//slist
	resolvelist_type resolvelist;

	void InitMaxObjIDs();

public:
	STDMETHODIMP OpenObject(objid_type objid);
	STDMETHODIMP CreateObject(objid_type *objid);
	STDMETHODIMP CloseObject() NOTHROW;

	STDMETHODIMP DeleteObject();
	STDMETHODIMP LockObject();

// ------- Project

public:
	std::string filename;
	bool read_only;
	bool intrans;
	bool modified;

	bool IsOpened() const { return !filename.empty(); }
	bool InTransaction() const { return intrans; }

	void CancelProject() NOTHROW;
	void SaveProject();
	void LoadProject();

public:
	STDMETHODIMP OpenProject(BSTR connection, VARIANT_BOOL *ro_mode);
	STDMETHODIMP CreateProject(BSTR connection);
	STDMETHODIMP CloseProject( VARIANT_BOOL abort = VARIANT_FALSE) NOTHROW;
	STDMETHODIMP SaveProject(BSTR connection, VARIANT_BOOL keepoldname);
	STDMETHODIMP DeleteProject() { return E_NOTIMPL; }

	STDMETHODIMP BeginTransaction();
	STDMETHODIMP CommitTransaction();
	STDMETHODIMP AbortTransaction();

	STDMETHODIMP get_StorageType(long *p);
};

// --------------------------- BinAttr<VALTYPE_LONG>

template<>
class BinAttr<VALTYPE_LONG> : public BinAttrBase
{
public:
	BinAttr() : a(0) { }

	long a;

	virtual valtype_type GetValType() const NOTHROW { return VALTYPE_LONG; }
	virtual void Set(CCoreBinFile *binfile, VARIANT p)
	{ ASSERT( binfile != NULL ); binfile->modified = true; CopyTo(p, a); }

	virtual void Get(CCoreBinFile *binfile, VARIANT *p) const { CopyTo(a, p); }
	virtual void Write(CCoreBinFile *binfile) const { binfile->write(a); }
	virtual void Read(CCoreBinFile *binfile) { binfile->read(a); }

    BinAttr(BinAttr<VALTYPE_LONG>&& that) : BinAttrBase(that.attrid), a(that.a) { }
    virtual void move(BinAttrUnion&& dest) {
        new (&dest) BinAttr<VALTYPE_LONG>(std::move(*this));
    }
};

// --------------------------- BinAttr<VALTYPE_REAL>

template<>
class BinAttr<VALTYPE_REAL> : public BinAttrBase
{
public:
	BinAttr() : a(0) { }

	double a;

	virtual valtype_type GetValType() const NOTHROW { return VALTYPE_REAL; }
	virtual void Set(CCoreBinFile *binfile, VARIANT p)
	{ ASSERT( binfile != NULL ); binfile->modified = true; CopyTo(p, a); }

	virtual void Get(CCoreBinFile *binfile, VARIANT *p) const { CopyTo(a, p); }
	virtual void Write(CCoreBinFile *binfile) const { binfile->write(a); }
	virtual void Read(CCoreBinFile *binfile) { binfile->read(a); }
	BinAttr(BinAttr<VALTYPE_REAL>&& that) : BinAttrBase(that.attrid), a(that.a) { }
	virtual void move(BinAttrUnion&& dest) {
		new (&dest) BinAttr<VALTYPE_REAL>(std::move(*this));
	}
};

// --------------------------- BinAttr<VALTYPE_STRING>

template<>
class BinAttr<VALTYPE_STRING> : public BinAttrBase
{
public:
	BinAttr() { }

	CComBstrObj a;

	virtual valtype_type GetValType() const NOTHROW { return VALTYPE_STRING; }
	virtual void Set(CCoreBinFile *binfile, VARIANT p)
	{ ASSERT( binfile != NULL ); binfile->modified = true; CopyTo(p, a); }

	virtual void Get(CCoreBinFile *binfile, VARIANT *p) const { CopyTo(a, p); }
	virtual void Write(CCoreBinFile *binfile) const { binfile->write(a); }
	virtual void Read(CCoreBinFile *binfile) { binfile->read(a); }
	BinAttr(BinAttr<VALTYPE_STRING>&& that) : BinAttrBase(that.attrid), a(std::move(that.a)) { }
	virtual void move(BinAttrUnion&& dest) {
		new (&dest) BinAttr<VALTYPE_STRING>(std::move(*this));
	}
};

// --------------------------- BinAttr<VALTYPE_BINARY>

template<class Type>
struct free_deleter {
	void operator()(Type* p) { free(p); }
};

template<>
class BinAttr<VALTYPE_BINARY> : public BinAttrBase
{
public:
	BinAttr() : len(0) { }

	typedef std::unique_ptr<unsigned char, free_deleter<unsigned char> > ptr;
	ptr a;
	int len;

	virtual valtype_type GetValType() const NOTHROW { return VALTYPE_BINARY; }
	virtual void Set(CCoreBinFile *binfile, VARIANT v)
	{
		ASSERT( binfile != NULL );
		binfile->modified = true; 
		if( v.vt == (VT_I4 | VT_ARRAY) )
		{
			len = sizeof(long) * GetArrayLength(v);
			a = ptr((unsigned char*) malloc(len));
			CopyTo(v, (long*)a.get(), (long*)(a.get()) + len/sizeof(long));
		}
		else
		{
			if (GetArrayLength(v)==0)
			{
				len = 0;
			}
			else
			{
				len = GetArrayLength(v);
				a = ptr((unsigned char*) malloc(len));
				CopyTo(v, a.get(), a.get() + len);
			}
		}
	}

	virtual void Get(CCoreBinFile *binfile, VARIANT *p) const { 
		//if (len == 0) {
		//	unsigned char* pnull=NULL;
		//	CopyTo(pnull,pnull, p);
		//} else
		CopyTo(a.get(), a.get() + len, p);
	}
	virtual void Write(CCoreBinFile *binfile) const { 
		binfile->write(a.get(), len);
	}
	virtual void Read(CCoreBinFile *binfile) { 
		unsigned char* p;
		binfile->read(p, len);
		a = ptr(p);
	}
	BinAttr(BinAttr<VALTYPE_BINARY>&& that) : BinAttrBase(that.attrid), a(std::move(that.a)), len(len) { }
	virtual void move(BinAttrUnion&& dest) {
		new (&dest) BinAttr<VALTYPE_BINARY>(std::move(*this));
	}
};

// --------------------------- BinAttr<VALTYPE_LOCK>

template<>
class BinAttr<VALTYPE_LOCK> : public BinAttrBase
{
public:
	BinAttr() : a(0) { }

	lockval_type a;

	virtual valtype_type GetValType() const NOTHROW { return VALTYPE_LOCK; }
	virtual void Set(CCoreBinFile *binfile, VARIANT p) { CopyTo(p, a); }
	virtual void Get(CCoreBinFile *binfile, VARIANT *p) const { CopyTo(a, p); }
	virtual void Write(CCoreBinFile *binfile) const { }
	virtual void Read(CCoreBinFile *binfile) { a = 0; }
	BinAttr(BinAttr<VALTYPE_LOCK>&& that) : BinAttrBase(that.attrid), a(that.a) { }
	virtual void move(BinAttrUnion&& dest) {
		new (&dest) BinAttr<VALTYPE_LOCK>(std::move(*this)); 
	}
};
// --------------------------- BinAttr<VALTYPE_COLLECTION>

template<>
class BinAttr<VALTYPE_COLLECTION> : public BinAttrBase
{
public:
	std::unique_ptr<std::vector<objects_iterator>> backing;
	std::vector<objects_iterator>& getbacking() const { return *backing.get(); }
	__declspec(property(get = getbacking )) std::vector<objects_iterator>& a;

	BinAttr() : backing(new std::vector<objects_iterator>()) { }
	virtual valtype_type GetValType() const NOTHROW { return VALTYPE_COLLECTION; }
	virtual void Set(CCoreBinFile *binfile, VARIANT p) { ASSERT(false); }
	virtual void Get(CCoreBinFile *binfile, VARIANT *p) const
	{
		ASSERT( p != NULL && p->vt == VT_EMPTY );

		std::vector<metaobjidpair_type> idpairs;

		std::vector<objects_iterator>::const_iterator i = a.begin();
		std::vector<objects_iterator>::const_iterator e = a.end();
		while( i != e )
		{
			idpairs.push_back( (*i)->first );

			++i;
		}

		CopyTo(idpairs, p);
	}
	virtual void Write(CCoreBinFile *binfile) const { }
	virtual void Read(CCoreBinFile *binfile) { }
    BinAttr(BinAttr<VALTYPE_COLLECTION>&& that) : BinAttrBase(that.attrid), backing(std::move(that.backing)) { }
	virtual void move(BinAttrUnion&& dest) {
		new (&dest) BinAttr<VALTYPE_COLLECTION>(std::move(*this));
	}
};

// --------------------------- BinAttr<VALTYPE_POINTER>

template<>
class BinAttr<VALTYPE_POINTER> : public BinAttrBase
{
public:
	BinAttr() : isEmpty(true) { }

	objects_iterator a;
	bool isEmpty;

	virtual valtype_type GetValType() const NOTHROW { return VALTYPE_POINTER; }

	void Set(CCoreBinFile *binfile, objects_iterator b)
	{
		ASSERT( binfile != NULL );
		ASSERT( isEmpty ); 
		ASSERT( b != binfile->objects.end());

		binfile->modified = true;

		a = b;
		isEmpty = false;

		ASSERT( binfile->opened_object->second.Find(attrid) == this );

		BinAttrBase *base = a->second.Find(attrid + ATTRID_COLLECTION);
		ASSERT( base != NULL );
		
		ASSERT( base->GetValType() == VALTYPE_COLLECTION );
		std::vector<objects_iterator> &objs = ((BinAttr<VALTYPE_COLLECTION>*)base)->a;

	#ifdef DEBUG_CONTAINERS
		std::vector<objects_iterator>::iterator i = find(objs.begin(), objs.end(), a);
		ASSERT( i == objs.end() );
	#endif

		objs.push_back(binfile->opened_object);
	}

	virtual void Set(CCoreBinFile *binfile, VARIANT p)
	{
		if( !isEmpty )
		{
			BinAttrBase *base = a->second.Find(attrid + ATTRID_COLLECTION);
			ASSERT( base != NULL );
			
			ASSERT( base->GetValType() == VALTYPE_COLLECTION );
			std::vector<objects_iterator> &objs = ((BinAttr<VALTYPE_COLLECTION>*)base)->a;

			ASSERT( binfile->opened_object->second.Find(attrid) == this );

			std::vector<objects_iterator>::iterator i = std::find(objs.begin(), objs.end(), binfile->opened_object);
			ASSERT( i != objs.end() );

			objs.erase(i);
		}

		isEmpty = true;

		metaobjidpair_type idpair;
		CopyTo(p, idpair);

		if( idpair.metaid == METAID_NONE )
		{
			ASSERT( idpair.objid == OBJID_NONE );
		}
		else
		{
			ASSERT( idpair.objid != OBJID_NONE );

			Set(binfile, binfile->objects.find(idpair));
		}
	}
	virtual void Get(CCoreBinFile *binfile, VARIANT *p) const
	{
		if( isEmpty )
		{
			metaobjidpair_type idpair;
			idpair.metaid = METAID_NONE;
			idpair.objid = OBJID_NONE;
			CopyTo(idpair, p);
		}
		else
			CopyTo(a->first, p);
	}

	virtual void Write(CCoreBinFile *binfile) const
	{
		if( isEmpty )
		{
			binfile->write((metaid_type)METAID_NONE);
		}
		else
		{
			ASSERT( a->first.metaid != METAID_NONE );
			ASSERT( a->first.objid != OBJID_NONE );

			binfile->write((metaid_type)a->first.metaid);
			binfile->write((objid_type)a->first.objid);
		}
	}

	virtual void Read(CCoreBinFile *binfile)
	{
		ASSERT( isEmpty );

		metaid_type metaid;
		binfile->read(metaid);

		if( metaid != METAID_NONE )
		{
			objid_type objid;
			binfile->read(objid);

			ASSERT( objid != OBJID_NONE );

			binfile->resolvelist.push_front(CCoreBinFile::resolve_type());
			CCoreBinFile::resolve_type &b = binfile->resolvelist.front();

			ASSERT( !binfile->isEmpty );

			b.obj = binfile->opened_object;
			b.attrid = attrid;
			b.idpair.metaid = metaid;
			b.idpair.objid = objid;
		}
	}
	BinAttr(BinAttr<VALTYPE_POINTER>&& that) : BinAttrBase(that.attrid), a(std::move(that.a)), isEmpty(that.isEmpty) { }
	virtual void move(BinAttrUnion&& dest) {
		new (&dest) BinAttr<VALTYPE_POINTER>(std::move(*this));
	}
};


static_assert(sizeof(BinAttr<VALTYPE_LONG>) <= sizeof(BinAttrUnion), "BinAttrUnion is too small.");
static_assert(sizeof(BinAttr<VALTYPE_REAL>) <= sizeof(BinAttrUnion), "BinAttrUnion is too small.");
static_assert(sizeof(BinAttr<VALTYPE_STRING>) <= sizeof(BinAttrUnion), "BinAttrUnion is too small.");
static_assert(sizeof(BinAttr<VALTYPE_POINTER>) <= sizeof(BinAttrUnion), "BinAttrUnion is too small.");
static_assert(sizeof(BinAttr<VALTYPE_BINARY>) <= sizeof(BinAttrUnion), "BinAttrUnion is too small.");
static_assert(sizeof(BinAttr<VALTYPE_COLLECTION>) <= sizeof(BinAttrUnion), "BinAttrUnion is too small.");


#endif//MGA_COREBINFILE_H
