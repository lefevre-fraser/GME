#include "stdafx.h"
#include ".\relationinfo.h"

RelationInfo::RelationInfo( CComBSTR p_relName, bool p_allowedAsSrc /*= true*/, bool p_allowedAsDst /*= true*/)
	: m_relName( p_relName)
	, m_allowedAsSrc( p_allowedAsSrc)
	, m_allowedAsDst( p_allowedAsDst)
{
}

RelationInfo::~RelationInfo(void)
{
}
