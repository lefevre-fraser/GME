#pragma once
#include "ComponentLib.h"
#include <string>

class Console
{
	typedef CComPtr<IGMEOLEApp> GMEAppPtr;
	GMEAppPtr   m_gme;
public:
	Console(void);
	~Console(void);

	GMEAppPtr getGME( IMgaProject* project);
	void init( IMgaProject* project);

	void sendMsg( const std::string& p_msg, msgtype_enum p_type);
	static void ssendMsg( const std::string& p_msg, msgtype_enum p_type);
};
