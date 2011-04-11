
#ifndef MGA_COMMONMGATRUKK_H
#define MGA_COMMONMGATRUKK_H

#include <memory>

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
	std::unique_ptr<CComPtr<iftype>[]> array(new CComPtr<iftype>[iter_count]); \
	CComPtr<iftype> *arrptr, *arrend; \
	if(iter_count > 0) \
		COMTHROW( collifptr->GetAll(iter_count, &(*array.get())) ); \
	arrend = array.get()+iter_count; \
	for(arrptr = array.get(); arrptr != arrend; arrptr++)

#define MGACOLL_ITER (*arrptr)

#define MGACOLL_AT_END (arrptr == arrend)

#define MGACOLL_ITERATE_END }

#endif//MGA_COMMONMGATRUKK_H

