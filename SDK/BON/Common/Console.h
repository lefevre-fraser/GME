#pragma once
#include "ComHelp.h"
#include "GMECOM.h"
#include "Gme.h"
//#include "Formatter.h"


namespace GMEConsole
{
	class Console
	{
	public:

		static CComPtr<IGMEOLEApp> gmeoleapp;
		
		static void SetupConsole(CComPtr<IMgaProject> project); 
		static void ReleaseConsole() {
			if (gmeoleapp)
				gmeoleapp.Release();
		}

		static void WriteLine(const CString& message, msgtype_enum type=MSG_INFO)
		{
			if (gmeoleapp == 0) {
				switch (type) {
				case MSG_NORMAL:
				case MSG_INFO:
				case MSG_WARNING:
					_tprintf("%s\n", message);
					break;
				case MSG_ERROR:
					_ftprintf(stderr, "%s\n", message);
					break;
				}
			}
			else {
				COMTHROW(gmeoleapp->ConsoleMessage( CComBSTR(message.GetLength(),message),type));
			}
		}

		static void Clear()
		{
			if (gmeoleapp != 0) {
				CComBSTR empty(L"");
				COMTHROW(gmeoleapp->put_ConsoleContents(empty));
			}
		}

		static void SetContents(const CString& contents)
		{
			if (gmeoleapp != 0) {
				COMTHROW(gmeoleapp->put_ConsoleContents( CComBSTR(contents.GetLength(),contents)));
			}
		}

		static void NavigateTo(const CString& url)
		{
			if (gmeoleapp != 0) {
				COMTHROW(gmeoleapp->ConsoleNavigateTo(CComBSTR(url.GetLength(), url)));
			}
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
			// deprecated
			static void writeLine(const CString& message)
			{
				Console::WriteLine(message,MSG_INFO);
			}
			static void WriteLine(const CString& message)
			{
				Console::WriteLine(message,MSG_INFO);
			}
		};
	};
}