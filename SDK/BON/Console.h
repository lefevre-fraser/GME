#pragma once
#include "ComHelp.h"
#include "GMECOM.h"
#include "Formatter.h"

namespace GMEConsole
{
	class Console
	{
	friend class RawComponent;

		static CComPtr<IGMEOLEApp> gmeoleapp;
		static void SetupConsole(CComPtr<IMgaProject> project); 
	public:

		static void WriteLine(const CString& message, msgtype_enum type)
		{
			SCODE code = gmeoleapp->ConsoleMessage( CComBSTR(message.GetLength(),message),type);
			if(S_OK != code)
			{
				AfxThrowOleException(code);
			}
		}

		static void Clear()
		{

			gmeoleapp->put_ConsoleContents(L"");
		}

		static void SetContents(const CString& contents)
		{
			SCODE code = gmeoleapp->put_ConsoleContents( CComBSTR(contents.GetLength(),contents));
			if(S_OK != code)
			{
				AfxThrowOleException(code);
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
			static void writeLine(const CString& message)
			{
				Console::WriteLine(message,MSG_INFO);
			}
		};
	};
}