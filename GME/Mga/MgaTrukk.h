//
// Tricks, macros, definitions used throughout the Mga library
//

#include "CommonMgaTrukk.h"

#define DIM(x) (sizeof(x)/ sizeof((x)[0]))
#define PUTINCLEAN(x) ((x) = NULL, &(x))

extern const CComBSTR NULLSTR;
extern const CoreObj NULLCOREOBJ;
extern const CComVariant NULLVARIANT;


// ----------------------------------------
// Collection types
// ----------------------------------------

#define COLLECTIONTYPE_FOR2(t1, t2)  CCoreCollection<t2, std::vector<t1*>, t1, t1> 
#define CREATECOLLECTION_FOR2(t1, t2, q) \
   CComPtr< COLLECTIONTYPE_FOR2(t1, t2) > q; CreateComObject(q);

#define COLLECTIONTYPE_FOR(t)  COLLECTIONTYPE_FOR2(t, t##s)
#define CREATECOLLECTION_FOR(t,q) CREATECOLLECTION_FOR2(t, t##s, q)


// ----------------------------------------
// ITERATE through collections
// ----------------------------------------

// iterate through CoreObj colls

#define ITERATE_THROUGH(ci)  \
CoreObjs collifptr=ci; \
ASSERT( collifptr != NULL );				\
std::vector< CoreObj> vect;			\
GetAll2<ICoreObjects>(collifptr, vect);\
std::vector< CoreObj>::iterator it_i = vect.begin(), it_e = vect.end();	\
for(;it_i != it_e; it_i++ )

#define ITERATE_THROUGH_BACK(ci)  \
CoreObjs collifptr=ci; \
ASSERT( collifptr != NULL );				\
std::vector< CoreObj> vect;			\
GetAll2<ICoreObjects>(collifptr, vect);\
std::vector< CoreObj>::iterator it_b = vect.begin(), it_i = vect.end();	\
while(it_i-- != it_b) 

#define ITER  (*it_i)
#define ITER_BROKEN (it_i != it_e)

// ----------------------------------------
// CHECK PARAMETERS
// ----------------------------------------

#define COM_EQUAL(a, b) (static_cast<IUnknown *>(a) == b ? true : a.IsEqualObject(b))

#define CHECK_INPTRPAR(p)	 { if(p == NULL)				 COMTHROW( E_MGA_INPTR_NULL); }
#define CHECK_MYINPTRPARVALIDNULL(p)  { if(p != NULL) COMTHROW(p->CheckProject(mgaproject)); }
#define CHECK_MYINPTRPAR(p)	 { if(p == NULL)				 COMTHROW( E_MGA_INPTR_NULL); \
								COMTHROW(p->CheckProject(mgaproject)); }
#define CHECK_MYINPTRSPAR(p) { if(p == NULL)				 COMTHROW( E_MGA_INPTR_NULL); \
								COMTHROW( mgaproject->CheckCollection(p)); }
//by ZolMol
#define CHECK_MYINPTRSPARFOLDER(p) { if(p == NULL)				 COMTHROW( E_MGA_INPTR_NULL); \
								COMTHROW( mgaproject->CheckFolderCollection(p)); }
#define CHECK_INSTRPAR(p)	 { if(p == NULL)			p = NULLSTR; }
#define CHECK_OUTSTRPAR(p)   { if(p == NULL) COMTHROW(E_MGA_OUTPTR_NULL); if(*p != NULL) COMTHROW(E_MGA_OUTPTR_NONEMPTY); }
#define CHECK_OUTPTRPAR(p)   { if(p == NULL) COMTHROW(E_MGA_OUTPTR_NULL); if(*p != NULL) COMTHROW(E_MGA_OUTPTR_NONEMPTY); }
#define CHECK_OUTPTRPARVALIDNULL(p)  { if(p != NULL && *p != NULL) COMTHROW(E_MGA_OUTPTR_NONEMPTY); }
#define CHECK_INPAR(p)				
#define CHECK_INBOOLPAR(p)	 { if(p != VARIANT_FALSE && p != VARIANT_TRUE)	COMTHROW(E_MGA_BAD_ENUMVALUE);	}	
#define CHECK_OUTPAR(p)		 { if(p == NULL)				 COMTHROW(E_MGA_OUTPTR_NULL); }
#define CHECK_OUTVARIANTPAR(p)		 { if(p == NULL)				 COMTHROW(E_MGA_OUTPTR_NULL); }




//z! renamed to GetAll2 from GetAll (it was in conflict with GetAll defined in CommonCollection.h)
template<class COLLITF>
void GetAll2(COLLITF *coll, std::vector< CoreObj > &ret)
{
	ASSERT( coll != NULL );
	ASSERT( ret.empty() );

	long count = 0;
	COMTHROW( coll->get_Count(&count) );
	ASSERT( count >= 0 );

	ret.clear();
	ret.insert(ret.begin(), count, NULL);

	if(count > 0) COMTHROW( coll->GetAll(count, &ret.front().p) );
}



// ----------------------------------------
// STL compatible wrapped for CComBSTR
// ----------------------------------------
class CComBSTRNoAt : public CComBSTR {
public:
	CComBSTRNoAt() {;};
	CComBSTRNoAt(const CComBSTR &sss) : CComBSTR(sss) {;}
	CComBSTRNoAt* const operator&() {
		return this;
	}
};


// ----------------------------------------
// Operations and STL-derived datatypes defined on CoreObj
// ----------------------------------------

struct coreobj_hashfunc {
	size_t operator()(const CoreObj &ob) const	{		return (size_t)ob.p;	}
};
struct coreobj_eqfunc {
	bool operator()(const CoreObj &oba,const CoreObj &obb) const	{	
		return COM_EQUAL(const_cast<CoreObj &>(oba), const_cast<CoreObj &>(obb));	
	}
};

typedef std::hash_map<CoreObj, CoreObj, coreobj_hashfunc, coreobj_eqfunc> coreobjpairhash;
typedef std::hash_map<CoreObj, int, coreobj_hashfunc, coreobj_eqfunc> coreobjhash;



// ---------------------------------------
// sort a CoreObjs collection
// ----------------------------------------
template <class avt>
void Sort(CoreObjs &coll, attrid_type  ai) {
		CREATECOLLECTION_FOR(ICoreObject, q);
		std::vector< CoreObj> vect;			
		GetAll2<ICoreObjects>(coll, vect);
		std::vector< CoreObj>::iterator it_i = vect.begin(), it_e = vect.end();	
		std::vector< CoreObj>::iterator it_j, it_min;
		for(;it_i != it_e; it_i++ ) {
			it_j = it_i;
			avt min = (*it_j)[ai];
			it_min = it_j;
			while(++it_j != it_e) {
				avt l = (*it_j)[ai];
				if(l < min) {
					it_min = it_j;
					min = l;
				}
			}
			q->Add(*it_min);
			*it_min = *it_i;
		}
		coll.Attach(q.Detach());
}



// ----------------------------------------
// FCO SMART POINTER, compatible with STL collections
// ----------------------------------------
class FCO;

class FCOPtr {  //smart FCO pointer
	friend struct FCOPtr_hashfunc;
	FCO *p;
public:
	FCO * operator->() const { return  p; } 
	operator FCO* () const { return  p; } 
	void operator= (FCO *f);
	bool operator< (const FCOPtr &o) const;
	FCOPtr(FCOPtr const &o);
	FCOPtr(FCO *f);
	FCOPtr();
	~FCOPtr();
};

struct FCOPtr_hashfunc {
	size_t operator()(const FCOPtr &ob) const	{		return (((int)ob.p) % 19);	}
};


// ----------------------------------------
// UTILITIES FROM MGA.CPP 
// ----------------------------------------
/// THROW!!!
CComBSTR Now(void);  

// ----------------------------------------
// CLASS SIGNATURE MECHANISM USED FOR DEBUG 
// ----------------------------------------
#ifdef DEBUG
#define DEFSIG  char sig[5];
#define INITSIG(a)  { sig[0] = 'A'; sig[1] = 'B'; sig[2] = a; sig[3] = '0'; sig[4] = '\0'; }
#define MARKSIG(a)  sig[3] = a
#else
#define DEFSIG
#define INITSIG(a)
#define MARKSIG(a)
#endif


// ----------------------------------------
// ErrorInfoImpl
// ----------------------------------------
#define ISupportErrorInfoImpl IMyErrorInfoImpl


class ATL_NO_VTABLE IMyErrorInfoBase {
public:
	    BEGIN_INTERFACE
        virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject) = 0;
        
        virtual ULONG STDMETHODCALLTYPE AddRef( void) = 0;
        
        virtual ULONG STDMETHODCALLTYPE Release( void) = 0;
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) = 0;
};

template <const IID* piid>
class ATL_NO_VTABLE IMyErrorInfoImpl : public IMyErrorInfoBase {
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
//		return (InlineIsEqualGUID(riid,*piid)) ? S_OK : S_FALSE;
		ASSERT(InlineIsEqualGUID(riid,*piid));
		return S_OK;
	}
};


// ----------------------------------------
// Transaction class, {COMTRY,COMCATCH}_IN_TRANSACTION
// ----------------------------------------
#include "MgaProject.h"
#include "MgaFCO.h"
#include "MgaTerritory.h"

class Transaction {
	CMgaProject *pr;
public:
	HRESULT Begin(CMgaProject *ppr) {
		if(!ppr) return E_MGA_ZOMBIE_NOPROJECT;
		if(!ppr->opened) return E_MGA_ZOMBIE_CLOSED_PROJECT;
		if(!ppr->activeterr) return E_MGA_NOT_IN_TRANSACTION;
		if(ppr->alreadynested()) {
			pr = NULL;
			return S_OK;
		}
		else {
			pr = ppr;
			return pr->beginnested();
		}
	}

	HRESULT Abort() {
		if(pr) return pr->abortnested();
		else return S_OK;
	}
	HRESULT Commit() {
		if(pr) 	return pr->commitnested();
		else return S_OK;
	}
};

#define COMTRY_IN_TRANSACTION { \
	Transaction ttt; \
	HRESULT hr = ttt.Begin(mgaproject); \
	if(hr != S_OK) return hr; \
	try

void MgaSetErrorInfo(HRESULT hr);

#define COMCATCH_IN_TRANSACTION( CLEANUP )  \
	catch(hresult_exception &e) \
	{ \
		ASSERT( FAILED(e.hr) ); \
		{ \
			if((hr = ttt.Abort()) != S_OK) return hr; \
			CLEANUP; \
		} \
		MgaSetErrorInfo(e.hr); \
		return e.hr; \
	} \
	return ttt.Commit(); }

#define MODIFIED	{ if(mgaproject->opened < 1000) mgaproject->opened++; }
 
#undef COMCATCH
#define COMCATCH( CLEANUP )  \
	catch(hresult_exception &e) \
	{ \
		ASSERT( FAILED(e.hr) ); \
		{ \
			CLEANUP; \
		} \
		MgaSetErrorInfo(e.hr); \
		return e.hr; \
	} \
	return S_OK;



///////////////////////////////////////////////////////////////////////////////////
////////////////////////////// DERIVETREETASK /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

// Executes the virtual Do function for the object and all the derived types
// DoWithDeriveds is used to start the operation
//		- self : the CoreObj to work on (FCO or ConnRole, or SetNode)
//		- peers : the vector of the peer FCO-s (e.g. relation targets)
// Before starting with the initial object, it is determined 
// which targets are 'internal' i.e. to be adjusted for the subtypes
// 'false internals' are not detected, because in most cases they cannot occur.
// if they still may occur (e.g. RevertToBase), use the 'endreserve' parameter to
// explicitly indicate that they are not internals
/*class DeriveTreeTask  {
protected:
	int peercnt, internalpeercnt;
	int endreserve;   // the number of 'reserved' coreobjs at the end of the vector
	attrid_type masterattr;
private:
	std::vector<int> peerdepths;
	int selfdepth;
	virtual bool Do(CoreObj self, std::vector<CoreObj> *peers = NULL) = 0;
	void _DoWithDeriveds(CoreObj self, std::vector<CoreObj> *peers = NULL);
public:
	DeriveTreeTask() : endreserve(0), masterattr(0) { };
	void DoWithDeriveds(CoreObj self, std::vector<CoreObj> *peers = NULL);
};*/


// ----------------------------------------
// BOOLTEMPFLAG
// keeps a bool flag set as long as it is on the stack
// ----------------------------------------
class booltempflag {
	bool *flagptr;
public:
	booltempflag(bool &a)  {	flagptr = a ? NULL : &a; set();}
	bool set() { if(flagptr) *flagptr = true; return flagptr != 0; }
	bool reset() { if(flagptr) *flagptr = false; return flagptr != 0; }
	~booltempflag() { reset(); }
};

