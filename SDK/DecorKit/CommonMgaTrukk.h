
#ifndef MGA_COMMONMGATRUKK_H
#define MGA_COMMONMGATRUKK_H

template < class t >
class SmartMultiPtr {
	CComPtr< t > *m_ptr;
public:
	SmartMultiPtr(CComPtr< t > *x) : m_ptr(x) { ; }
	~SmartMultiPtr() { delete[] m_ptr; }
	operator CComPtr< t > *() { return m_ptr; }
	t **operator &() { return &(m_ptr[0]); }
};

#define MGACOLL_ITERATE(iftype, collifptr) \
{ \
	ASSERT( collifptr != NULL ); \
	long iter_count = 0; \
	COMTHROW( collifptr->get_Count(&iter_count) ); \
	ASSERT( iter_count >= 0 ); \
	CComPtr<iftype> *arrptr, *arrend, *array = new CComPtr<iftype>[iter_count]; \
	if(iter_count > 0) \
		COMTHROW( collifptr->GetAll(iter_count, &(*array)) ); \
	arrend = array+iter_count; \
	for(arrptr = array; arrptr != arrend; arrptr++)

#define MGACOLL_ITER (*arrptr)

#define MGACOLL_AT_END (arrptr == arrend)

#define MGACOLL_ITERATE_END \
	delete[] array; \
}

#endif//MGA_COMMONMGATRUKK_H

