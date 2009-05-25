#include "stdafx.h"
#include "Console.h"



namespace GMEConsole
{
	CComPtr<IGMEOLEApp> Console::gmeoleapp = 0;

	void Console::SetupConsole(CComPtr<IMgaProject> project)
	{
		CComPtr<IMgaClient> client;	
		CComQIPtr<IDispatch> pDispatch;
		HRESULT s1 = project->GetClientByName(L"GME.Application", &client);

		if ((SUCCEEDED(s1)) && (client != 0))
		{
			HRESULT s2 = client->get_OLEServer(&pDispatch);
			if ((SUCCEEDED(s2)) && (pDispatch != 0) && gmeoleapp == 0)
			{
				COMTHROW(pDispatch->QueryInterface(&gmeoleapp));
			}
		}
	}
}