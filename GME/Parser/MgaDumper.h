
#ifndef MGA_MGADUMPER_H
#define MGA_MGADUMPER_H

#include <fstream> //fstream.h
#include "resource.h"
#include "CommonVersionInfo.h"
#include "Transcoder.h"
#include "helper.h"

class GmeEqual
{
	public:
		GmeEqual( CComObjPtr<IMgaObject>);
		GmeEqual( CComObjPtr<IMgaFCO>);
		GmeEqual( CComObjPtr<IMgaFolder>);
		GmeEqual( CComObjPtr<IMgaModel>);

		bool operator() ( CComObjPtr<IMgaObject>& );
		bool operator() ( CComObjPtr<IMgaFCO>& );
		bool operator() ( CComObjPtr<IMgaFolder>& );
		bool operator() ( CComObjPtr<IMgaModel>& );
	private:
		CComObjPtr<IMgaObject>	m_objToFind;
		CComObjPtr<IMgaFCO>		m_fcoToFind;
		CComObjPtr<IMgaFolder>	m_folderToFind;
		CComObjPtr<IMgaModel>	m_modelToFind;
		int						m_which; // which variable is set
};



// --------------------------- CMgaDumper

class ATL_NO_VTABLE CMgaDumper : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMgaDumper, &CLSID_MgaDumper>,
	public ISupportErrorInfoImpl<&IID_IMgaDumper>,
	public IDispatchImpl<IMgaDumper, &IID_IMgaDumper, &LIBID_PARSERLib>,
	public IMgaVersionInfoImpl
{
public:
	CMgaDumper()
		: dumpversion( 1)
		, m_closureDump( false)
		, m_strictDump( true)
		, m_dumpRelids( true)
		, m_dumpLibraryStubs(false) 
		, m_dumpGuids( false)
	{ }

DECLARE_REGISTRY_RESOURCEID(IDR_MGADUMPER)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMgaDumper)
	COM_INTERFACE_ENTRY(IMgaDumper)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY_IID(IID_IMgaVersionInfo, IMgaVersionInfoImpl)
END_COM_MAP()

// ------- Methods

public:
	void InitDump(IMgaProject *p, BSTR xmlfile);
	void DoneDump(bool abort);

	STDMETHOD(DumpProject)(IMgaProject *p, BSTR xmlfile);
	STDMETHOD(DumpFCOs)(IMgaProject *proj, IMgaFCOs *p, IMgaFolders *f, IMgaRegNodes *r, BSTR xmlfile);
	STDMETHOD(DumpClos)( IMgaFCOs *sel_fco, IMgaFolders *sel_fold, BSTR xmlfile, int lib_stub);
	STDMETHOD(DumpClosR)( IMgaFCOs *sel_fco, IMgaFolders *sel_fold, BSTR xmlfile, IMgaFCOs *top_fco, IMgaFolders *top_fold, int options, BSTR abspath, BSTR acceptingkinds);
	STDMETHOD(put_FormatVersion)(long p) { dumpversion = p; return S_OK; }

// ------- Low level stuff
	void Indent(int i);
	void StartElem(const char *name);
	void Attr(const char *name, const char *value);
	void Attr(const char *name, const char *value, int len);
	static bool HasMarkup(const char *value, int len);
	void Data(const char *value, int len);
	void EndElem();

	void Attr(const char *name, std::string &value)
	{
		Attr(name, value.data(), value.length());
	}

	void Attr(const char *name, const CComBstrObj &value)
	{
		std::string t;
		CopyTo(value, t);
		Attr(name, t);
	}

	void Data(std::string &value)
	{
		Data(value.data(), value.length());
	}

	void Data(const CComBstrObj &value)
	{
		std::string t;
		CopyTo(value, t);
		Data(t);
	}

	template<class INTERFACE, class FUNC_INTERFACE>
	void Attr(const char *name, INTERFACE p, HRESULT (__stdcall FUNC_INTERFACE::*func)(BSTR *))
	{
		FUNC_INTERFACE *q = p;
		ASSERT( q != NULL );

		CComBstrObj value;
		COMTHROW( (q->*func)(PutOut(value)) );

		Attr(name, value);
	}

	template<class INTERFACE, class FUNC_INTERFACE>
	void LAttr(const char *name, INTERFACE p, HRESULT (__stdcall FUNC_INTERFACE::*func)(long *))
	{
		FUNC_INTERFACE *q = p;
		ASSERT( q != NULL );

		long value;
		COMTHROW( (q->*func)(&value) );

		char buf[16] = "0x";
		ltoa(value,buf+2, 16);

		Attr(name, buf);
	}

	template<class INTERFACE, class FUNC_INTERFACE>
	void Data(INTERFACE p, HRESULT (__stdcall FUNC_INTERFACE::*func)(BSTR *))
	{
		FUNC_INTERFACE *q = p;
		ASSERT( q != NULL );

		CComBstrObj value;
		COMTHROW( (q->*func)(PutOut(value)) );

		Data(value);
	}

	template<class INTERFACE, class FUNC_INTERFACE, class COLLECTION>
	void Dump(INTERFACE p, HRESULT (__stdcall FUNC_INTERFACE::*func)(COLLECTION **q))
	{
		FUNC_INTERFACE *q = p;
		ASSERT( q != NULL );

		typedef TYPENAME_COLL2ELEM(COLLECTION) element_type;

		CComObjPtrVector<element_type> v;
		COMTHROW( (q->*func)(PutOut(v)) );

		Sort(&v);

		CComObjPtrVector<element_type>::iterator i = v.begin();
		CComObjPtrVector<element_type>::iterator e = v.end();
		while( i != e )
		{
			if ( CheckInClosure( *i)) // by ZolMol
				Dump(*i);

			++i;
		}
	}

	bool CheckInClosure( CComObjPtr<IMgaFCO>);
	bool CheckInClosure( CComObjPtr<IMgaFolder>);
	bool CheckInClosure( CComObjPtr<IMgaAttribute>);
	bool CheckInClosure( CComObjPtr<IMgaConnPoint>);
	

// ------- Dumpers

public:

	void Dump(IMgaProject *project);
	void Dump(IMgaFolder *folder);
	void Dump(IMgaRegNode *regnode);
	void Dump(IMgaObject *obj);
	void Dump(IMgaModel *model);
	void Dump(IMgaConstraint *constraint);
	void Dump(IMgaAttribute *attribute);
	void Dump(IMgaAtom *atom);
	void Dump(IMgaReference *reference);
	void Dump(IMgaConnection *connection);
	void Dump(IMgaSet *set);
	void Dump(IMgaConnPoint *connpoint);

	void DumpFCO(IMgaFCO *fco, bool dump_attrs = true,
		bool dump_name = true, bool dump_elems = true);
	void DumpConstraints(IMgaObject *object);
	void DumpIDRefs(const char *name, CComObjPtrVector<IMgaFCO> &fcos);
	std::string DumpGUIDRefs( CComObjPtrVector<IMgaFCO>& fcos);
	std::string DumpMixedGUIDRefs( CComObjPtrVector<IMgaFCO>& fcos);
	void DumpConnDetails(CComObjPtr<IMgaConnection> connection);

// ------- Sorters

public:
	void Sort(CComObjPtrVector<IMgaRegNode> *v);
	void Sort(CComObjPtrVector<IMgaAttribute> *v);
	void Sort(CComObjPtrVector<IMgaConnPoint> *v);
	void Sort(CComObjPtrVector<IMgaFolder> *v);	
	void Sort(CComObjPtrVector<IMgaFCO> *v);


// ------- Attributes

public:
	Transcoder ofs;

	struct elem
	{
		std::string name;
		bool inbody;
		bool indata;
	};

	std::vector<elem> elems;

	long fco_count;
	int dumpversion;// >=1 means new xme format, ==2 means do not dump relids
	bool m_dumpGuids;

	bool m_closureDump;
	bool m_dumpRelids;
	bool m_strictDump; // if true then containers dump their children only if the child is present in the closure collection
	bool m_dumpLibraryStubs; // if true the libreferred attribute is dumped

	inline bool isInLibrary( IMgaObject * obj)
	{
		VARIANT_BOOL vbLibrary;
		COMTHROW( obj->get_IsLibObject( &vbLibrary ) );
		return ( vbLibrary ) ? true : false;
	}

	CComObjPtr<IMgaProject>			project;
	CComObjPtr<IMgaTerritory>		territory;
	
	CComObjPtrVector<IMgaFCO>		m_selFcos;		// selected objects for dump or closure
	CComObjPtrVector<IMgaFolder>	m_selFolders;
	CComObjPtrVector<IMgaRegNode>	m_selRegNodes;
	void removeInnerObjs();

	void putInTerritory( CComObjPtrVector<IMgaFCO>&);
	void putInTerritory( CComObjPtrVector<IMgaFolder>&);

	//std::string m_curTopPath; // used for the 'closurename' calc
	std::string m_currAbsPath;//? it is needed any more?
	//std::string m_currParAbsPath; // used for 'closurepath' calc
	bool m_v2;

};

#endif //__MGADUMPER_H_
