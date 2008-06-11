#pragma once
//#include "ComHelp.h"
#include "GMECOM.h"

class SearchRepl
{
	CComPtr<IMgaProject>      m_pr;

	// methods
	void findMetaRole( CComBSTR p_kind, CComPtr<IMgaMetaRole>& p_res1, CComPtr<IMgaMetaRole>& p_res2);

	void collect           ( CComPtr<IMgaFCO>    p_elem,         CComPtr<IMgaFCOs>& p_eqClass);
	void createSiblings    ( IMgaFCOs*           p_eqClass,      CComPtr<IMgaMetaRole> mrole_fco, CComPtr<IMgaMetaRole> mrole_prx);
	void copy              ( CComPtr<IMgaFCO>    p_old,          CComPtr<IMgaFCO> p_new);
	void remove            ( CComPtr<IMgaFCOs>&  p_eqClass);


public:
	SearchRepl( IMgaProject* pr);
	~SearchRepl(void);

	bool qualifies( IMgaFCO* el);
	void exec( IMgaFCO* el, CComBSTR newKind);
};
