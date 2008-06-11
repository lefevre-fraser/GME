// MgaEventLogger.cpp: implementation of the CMgaEventLogger class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MgaEventLogger.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMgaEventLogger::CMgaEventLogger():initialized(false),newLine(true)
{
}

CMgaEventLogger::~CMgaEventLogger()
{

}

STDMETHODIMP CMgaEventLogger::LogEvent(BSTR eventMsg)
{
	if(initialized)
	{
		CString s(eventMsg);
		if(newLine)
		{
			CTime time = CTime::GetCurrentTime();
			CString CurrentTime = time.Format("%b %d, %H:%M:%S ");
			fprintf(EventLog,CurrentTime);
			newLine = false;
		}
		if(s.Find("\r\n")!=-1)
		{
			newLine = true;
		}
		fprintf(EventLog,s);
		fflush(EventLog);
	}
	return S_OK;
}

STDMETHODIMP CMgaEventLogger::StartLogging()
{
	if(!initialized) //if already initialized, don't do anything
	{
		CString path;
		char gmepath[200];
		if(SHGetSpecialFolderPath( NULL, gmepath, CSIDL_APPDATA, true)) //most likely C:\Documents and Settings\<username>\Application Data
		{
			path = CString(gmepath) + "\\GME"; // add \GME to the path
			_mkdir(path.GetBuffer(4)); //in case GME dir not there, make it, if this function fails because GME already exists, don't care
			CTime time = CTime::GetCurrentTime(); //to make unique logfile names
			CString CurrentTime = time.Format( "\\GME_%b-%d_%H.%M.%S.log" );
			EventLog = fopen(path+CurrentTime,"w");

			if (EventLog != NULL) //fopen succeded
			{	
				initialized = true;
				newLine = true;
				CComBSTR b = "CMgaEventLogger::StartLogging\r\n";
				LogEvent(b);
			}
		}
	}
	return S_OK;
}

STDMETHODIMP CMgaEventLogger::StopLogging()
{
	if(initialized)
	{
		CComBSTR b = "CMgaEventLogger::StopLogging\r\n";
		LogEvent(b);
		fflush(EventLog);
		fclose(EventLog);
	}
	initialized = false;
	EventLog = NULL;
	return S_OK;
}

STDMETHODIMP CMgaEventLogger::EmergencyEvent()
{
	CComBSTR b = "CMgaEventLogger::EmergencyEvent\r\n";
	LogEvent(b);
	StopLogging();
	return S_OK;
}