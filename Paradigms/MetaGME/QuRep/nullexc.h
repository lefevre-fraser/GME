#pragma once
#include <string>

class NullExc
{
	std::string            m_descr;
public:
	std::string            getDescr()             { return m_descr; }

	NullExc( void);
	NullExc( const std::string& p_msg);
	~NullExc(void);
};
