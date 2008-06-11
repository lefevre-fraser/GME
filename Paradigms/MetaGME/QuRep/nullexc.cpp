#include "stdafx.h"
#include ".\nullexc.h"

NullExc::NullExc(void)
{
}


NullExc::NullExc( const std::string& p_msg)
	: m_descr( p_msg)
{
}

NullExc::~NullExc(void)
{
}
