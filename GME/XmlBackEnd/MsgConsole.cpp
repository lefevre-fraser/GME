#include "stdafx.h"
#include "MsgConsole.h"


// MsgConsole
MsgConsole::MsgConsole( bool p_create)
{
	if( p_create)
		m_gme.CoCreateInstance( L"GME.Application");
}

void MsgConsole::sendMsg( const std::string& p_msg, int p_mtype)
{
	if( m_gme)
	{
		m_gme->put_Visible( VARIANT_TRUE);
		CComBSTR msg( p_msg.c_str());
		m_gme->ConsoleMessage( msg, (msgtype_enum) p_mtype);
	}
}

//static
void MsgConsole::ssendMsg( const std::string& p_msg, int p_mtype)
{
	CComPtr<IGMEOLEApp> gme;
	gme.CoCreateInstance( L"GME.Application");
	if( gme)
	{
		gme->put_Visible( VARIANT_TRUE);
		CComBSTR msg( p_msg.c_str());
		gme->ConsoleMessage( msg, (msgtype_enum) p_mtype);
	}
}

