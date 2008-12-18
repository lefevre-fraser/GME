#pragma once
#include "ComHelp.h"
#include "GMECOM.h"
//#include "Formatter.h"


namespace GMEConsole
{
	class Console
	{

		static CComPtr<IGMEOLEApp> gmeoleapp;
		
	public:

		static void SetupConsole(CComPtr<IMgaProject> project); 

		static void WriteLine(const CString& message, msgtype_enum type)
		{
			if (gmeoleapp == 0) {
				switch (type) {
				case MSG_NORMAL:
				case MSG_INFO:
				case MSG_WARNING:
					_tprintf(message);
					break;
				case MSG_ERROR:
					_ftprintf(stderr, message);
					break;
				}
			}
			else {
				COMTHROW(gmeoleapp->ConsoleMessage( CComBSTR(message.GetLength(),message),type));
			}
		}

		static void Clear()
		{
			COMTHROW(gmeoleapp->put_ConsoleContents(L""));
		}

		static void SetContents(const CString& contents)
		{
			COMTHROW(gmeoleapp->put_ConsoleContents( CComBSTR(contents.GetLength(),contents)));
		}

		static void NavigateTo(const CString& url)
		{
			COMTHROW(gmeoleapp->ConsoleNavigateTo(CComBSTR(url.GetLength(), url)));
		}

		class Error
		{
		public:
			static void WriteLine(const CString& message)
			{
				Console::WriteLine(message,MSG_ERROR);
			}
		};
		class Out
		{
		public:
			static void WriteLine(const CString& message)
			{
				Console::WriteLine(message, MSG_NORMAL);
			}
		};
		class Warning
		{
		public:
			static void WriteLine(const CString& message)
			{
				Console::WriteLine(message, MSG_WARNING);
			}
		};
		class Info
		{
		public:
			static void writeLine(const CString& message)
			{
				Console::WriteLine(message,MSG_INFO);
			}
		};
	};
}