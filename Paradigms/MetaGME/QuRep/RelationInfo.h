#pragma once
#include <atlbase.h>

class RelationInfo
{
	CComBSTR          m_relName;
	bool              m_allowedAsSrc;
	bool              m_allowedAsDst;
public:
	CComBSTR          getRelName()  { return m_relName; };
	bool              mayBeSrc()    { return m_allowedAsSrc; };
	bool              mayBeDst()    { return m_allowedAsDst; };

	RelationInfo( CComBSTR p_relName, bool p_allowedAsSrc = true, bool p_allowedAsDst = true);
	~RelationInfo(void);
};
