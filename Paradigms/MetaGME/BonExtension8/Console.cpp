#include "stdafx.h"
#include ".\console.h"
#include "myUtil.h"

Console::Console(void)
: m_gme( 0)
{
}

Console::~Console(void)
{
	m_gme = 0;
}

Console::GMEAppPtr Console::getGME( IMgaProject* project)
{
	if (!m_gme) {
		CComBSTR bstrName("GME.Application");
		CComQIPtr<IMgaClient> pClient;
		HRESULT hr = project->GetClientByName( bstrName, &pClient);
		if (SUCCEEDED( hr) && pClient) {
			CComQIPtr<IDispatch> pDispatch;
			COMTHROW(pClient->get_OLEServer(&pDispatch));
			if (pDispatch) {
				COMTHROW(pDispatch.QueryInterface( &m_gme));
			}
		}
	}
	return m_gme;
}

void Console::init( IMgaProject* project)
{
	m_gme = getGME( project);
}

void Console::sendMsg( const std::string& p_msg, msgtype_enum p_type)
{
	if( m_gme)
		m_gme->ConsoleMessage( Util::Copy( p_msg), p_type);
	else
		ssendMsg( p_msg, p_type);
}

//static 
Console::ssendMsg( const std::string& p_msg, msgtype_enum p_type)
{
	//GMEAppPtr p_gme = getGME( 0);
	GMEAppPtr p;
	p.CoCreateInstance( L"GME.Application");
	p->ConsoleMessage( Util::Copy( p_msg), p_type);
}