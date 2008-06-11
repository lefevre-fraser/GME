#pragma once

class MsgConsole
{
	CComPtr<IGMEOLEApp>   m_gme;
public:
	MsgConsole( bool p_create);
	void          sendMsg  ( const std::string&, int mtype );
	
	static void   ssendMsg ( const std::string&, int mtype );
};

