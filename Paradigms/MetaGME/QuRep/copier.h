#pragma once
#include "RelationInfo.h"
#include "GMECOM.h"

class Copier
{
	CComPtr<IMgaFCO>       m_oldFco;
	CComPtr<IMgaFCO>       m_newFco;

	// methods
	bool COMEQUAL( CComPtr<IMgaFCO> p1, CComPtr<IMgaFCO> p2);
	void task( RelationInfo* p_rels, int p_sz);
	void copyInnerProperties( CComPtr<IMgaFCO> p_anOldFco, CComPtr<IMgaFCO> p_aNewFco);

public:
	Copier( CComPtr<IMgaFCO> p_oldFco, CComPtr<IMgaFCO> p_newFco);
	~Copier(void);

	void relations();
	void aspMemberships();

	static void name          ( CComPtr<IMgaFCO> p_oldFco, CComPtr<IMgaFCO> p_newFco);
	static void regNodes      ( CComPtr<IMgaFCO> p_oldFco, CComPtr<IMgaFCO> p_newFco);
	static void attribs       ( CComPtr<IMgaFCO> p_oldFco, CComPtr<IMgaFCO> p_newFco);

	static void traverseRegNds( CComPtr<IMgaRegNodes>& p_rnds, CComPtr<IMgaFCO>& p_newFco);
};
