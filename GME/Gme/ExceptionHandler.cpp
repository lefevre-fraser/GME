/////////////////////////////////////////////////////////////////////////////
//
// ExceptionHandler.cpp : Exception handler filter,
//						  minidump and XML crash dump writer
//
// Thanks to:
// Johen Kalbach:
//	Walking the callstack
//	http://www.codeproject.com/KB/threads/StackWalker.aspx
//	http://blog.kalmbach-software.de/
//
// Matt Pietrek's various Exception Handling Courses on MSJ (MS Journal) and MSDN Magazine:
//	A Crash Course on the Depths of Win32 Structured Exception Handling, January 1997
//	http://www.microsoft.com/msj/0197/Exception/Exception.aspx
//	Under The Hood April 1997
//	http://www.microsoft.com/msj/0497/hood/hood0497.aspx
//	Under The Hood May 1997
//	http://www.microsoft.com/msj/0597/hood0597.aspx
//	March 2002 issue of MSDN Magazine: Improved Error Reporting with DBGHELP 5.1 APIs
//	http://msdn2.microsoft.com/en-us/magazine/cc301692.aspx
//
// Oleg Starodumov
//	effective minidumps
//	http://www.debuginfo.com/articles/effminidumps.html
//	minidump examples
//	http://www.debuginfo.com/examples/effmdmpexamples.html
//
/////////////////////////////////////////////////////////////////////////////

#define WIN32_LEAN_AND_MEAN

//////////////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ExceptionHandler.h"
#include "ExceptionXMLTags.h"
#include "GMEVersion.h"
#include <float.h>

//#pragma comment(linker, "/defaultlib:dbghelp.lib")
//#pragma comment(lib, "dbghelp.lib")
#pragma comment(lib, "version.lib")	// for VerQueryValue, GetFileVersionInfo, GetFileVersionInfoSize


//////////////////////////////////////////////////////////////////////////////
// Types
//////////////////////////////////////////////////////////////////////////////

typedef BOOL
(_stdcall *tSymFromAddr)(
	IN		HANDLE							hProcess,
	IN		DWORD64							Address,
	OUT		PDWORD64						Displacement,
	IN OUT	PSYMBOL_INFO					Symbol
	);

typedef DWORD
(WINAPI *tSymGetOptions)(
	);

typedef DWORD
(WINAPI *tSymSetOptions)(
	IN		DWORD							SymOptions
	);

typedef BOOL
(WINAPI *tSymCleanup)(
	IN		HANDLE							hProcess
	);

typedef BOOL
(WINAPI *tSymInitialize)(
	IN		HANDLE							hProcess,
	IN		PSTR							UserSearchPath,
	IN		BOOL							fInvadeProcess
	);

typedef LPAPI_VERSION
(WINAPI *tImgHlpApiVersion)(
	);

typedef BOOL
(WINAPI *tSymEnumSymbols)(
	IN		HANDLE							hProcess,
	IN		ULONG64							BaseOfDll,
	IN		PCSTR							Mask,
	IN		PSYM_ENUMERATESYMBOLS_CALLBACK	EnumSymbolsCallback,
	IN		PVOID							UserContext
	);

typedef ULONG
(WINAPI *tSymSetContext)(
	HANDLE									hProcess,
	PIMAGEHLP_STACK_FRAME					StackFrame,
	PIMAGEHLP_CONTEXT						Context
	);

typedef BOOL
(WINAPI *tSymGetLineFromAddr)(
	IN		HANDLE							hProcess,
	IN		DWORD							dwAddr,
	OUT		PDWORD							pdwDisplacement,
	OUT		PIMAGEHLP_LINE					Line
	);

typedef BOOL
(WINAPI *tStackWalk)(
	DWORD									MachineType,
	HANDLE									hProcess,
	HANDLE									hThread,
	LPSTACKFRAME							StackFrame,
	PVOID									ContextRecord,
	PREAD_PROCESS_MEMORY_ROUTINE			ReadMemoryRoutine,
	PFUNCTION_TABLE_ACCESS_ROUTINE			FunctionTableAccessRoutine,
	PGET_MODULE_BASE_ROUTINE				GetModuleBaseRoutine,
	PTRANSLATE_ADDRESS_ROUTINE				TranslateAddress
	);

typedef PVOID
(WINAPI *tSymFunctionTableAccess)(
	HANDLE									hProcess,
	DWORD									AddrBase
	);

typedef DWORD
(WINAPI *tSymGetModuleBase)(
	IN		HANDLE							hProcess,
	IN		DWORD							dwAddr
	);

typedef BOOL
(WINAPI *tSymGetTypeInfo)(
	IN		HANDLE							hProcess,
	IN		DWORD64							ModBase,
	IN		ULONG							TypeId,
	IN		IMAGEHLP_SYMBOL_TYPE_INFO		GetType,
	OUT		PVOID							pInfo
	);

typedef BOOL
(WINAPI *tMiniDumpWriteDump)(
	HANDLE									hProcess,
	DWORD									ProcessId,
	HANDLE									hFile,
	MINIDUMP_TYPE							DumpType,
	PMINIDUMP_EXCEPTION_INFORMATION			ExceptionParam,
	PMINIDUMP_USER_STREAM_INFORMATION		UserStreamParam,
	PMINIDUMP_CALLBACK_INFORMATION			CallbackParam
	);


//////////////////////////////////////////////////////////////////////////////
// Static
//////////////////////////////////////////////////////////////////////////////

static tSymCleanup				pSymCleanup;
static tSymInitialize			pSymInitialize;
static tImgHlpApiVersion		pImgHlpApiVersion;
static tSymGetOptions			pSymGetOptions;
static tSymSetOptions			pSymSetOptions;
static tSymEnumSymbols			pSymEnumSymbols;
static tSymSetContext			pSymSetContext;
static tSymGetLineFromAddr		pSymGetLineFromAddr;
static tSymFromAddr				pSymFromAddr;
static tStackWalk				pStackWalk;
static tSymFunctionTableAccess	pSymFunctionTableAccess;
static tSymGetModuleBase		pSymGetModuleBase;
static tSymGetTypeInfo			pSymGetTypeInfo;
static tMiniDumpWriteDump		pMiniDumpWriteDump;


//============================================================
// XMLTag
// Helper function for writing the XML format data
//============================================================

void XMLTag::AddTabs(void)
{
	AddTabs(0);
}


void XMLTag::AddTabs(DWORD additionalTabCount)
{
	for (DWORD i = 0; i < m_openedXmlTags.size() + additionalTabCount; i++)
		AddRawText(_T("\t"));
}


void XMLTag::AddRawText(CString text, bool escape)
{
	// For XML well formedness
	if (escape) {
		text.Replace("&", "&amp;");
		text.Replace("<", "&lt;");
		text.Replace(">", "&gt;");
		text.Replace("'", "&apos;");
		text.Replace("\"", "&quot;");
	}
	m_UserCrashData = m_UserCrashData + text;
}


void XMLTag::PrintTag(const TCHAR* tagString, bool open, bool withTabs, bool nl)
{
	if (withTabs)
		AddTabs();
	AddRawText(_T("<"), false);
	if (!open)
		AddRawText(_T("/"));
	AddRawText(tagString);
	AddRawText(_T(">"), false);
	if (nl)
		AddRawText(_T("\n"));
}


XMLTag::XMLTag(const TCHAR* tagString, std::vector<CString>& openedXmlTags, CString& userCrashData):
	m_openedXmlTags(openedXmlTags),
	m_UserCrashData(userCrashData),
	m_closed(false)
{
	OpenTag(tagString);
}


XMLTag::XMLTag(const TCHAR* tagString, const TCHAR* text, std::vector<CString>& openedXmlTags, CString& userCrashData):
	m_openedXmlTags(openedXmlTags),
	m_UserCrashData(userCrashData),
	m_closed(false)
{
	OpenTag(tagString, true, false);
	Append(text);
	CloseTag(false, true);
}


XMLTag::XMLTag(const TCHAR* tagString, const WCHAR* text, std::vector<CString>& openedXmlTags, CString& userCrashData):
	m_openedXmlTags(openedXmlTags),
	m_UserCrashData(userCrashData),
	m_closed(false)
{
	OpenTag(tagString, true, false);
	AddRawText(text);
	CloseTag(false, true);
}


XMLTag::XMLTag(const TCHAR* tagString, DWORD value, const TCHAR* formatString, std::vector<CString>& openedXmlTags,
			   CString& userCrashData):
	m_openedXmlTags(openedXmlTags),
	m_UserCrashData(userCrashData),
	m_closed(false)
{
	OpenTag(tagString, true, false);
	CString buffer;
	buffer.Format(formatString, value);
	Append(buffer);
	CloseTag(false, true);
}


XMLTag::XMLTag(const TCHAR* tagString, std::vector<CString>& openedXmlTags, CString& userCrashData,
			   DWORD64 value, const TCHAR* formatString):
	m_openedXmlTags(openedXmlTags),
	m_UserCrashData(userCrashData),
	m_closed(false)
{
	OpenTag(tagString, true, false);
	CString buffer;
	buffer.Format(formatString, value);
	Append(buffer);
	CloseTag(false, true);
}


XMLTag::XMLTag(const TCHAR* tagString, DWORD value, std::vector<CString>& openedXmlTags, CString& userCrashData):
	m_openedXmlTags(openedXmlTags),
	m_UserCrashData(userCrashData),
	m_closed(false)
{
	OpenTag(tagString, true, false);
	CString buffer;
	buffer.Format("%08X", value);
	Append(buffer);
	CloseTag(false, true);
}


XMLTag::~XMLTag()
{
	CloseTag();
}


void XMLTag::OpenTag(const TCHAR* tagString, bool withTabs, bool nl)
{
	PrintTag(tagString, true, withTabs, nl);
	m_openedXmlTags.push_back(tagString);
}


void XMLTag::Print(const TCHAR* text)
{
	AddTabs(1);
	AddRawText(text);
}


void XMLTag::Println(const TCHAR* text)
{
	Print(text);
	AddRawText(_T("\n"));
}


void XMLTag::Append(const TCHAR* text)
{
	AddRawText(text);
}


void XMLTag::Appendln(const TCHAR* text)
{
	AddRawText(text);
	AddRawText(_T("\n"));
}


void XMLTag::CloseTag(bool withTabs, bool nl)
{
	if (!m_closed) {
		CString tagString = m_openedXmlTags.back();
		m_openedXmlTags.pop_back();
		PrintTag(tagString, false, withTabs, nl);
		m_closed = true;
	}
}


//============================================================
// ExceptionHandler
// UnhandledExceptionFilter and helper functions and members
//============================================================

//////////////////////////////////////////////////////////////////////////////
// global instance
//////////////////////////////////////////////////////////////////////////////
static	ExceptionHandler		g_ExceptionHandler;	// Global instance of ExceptionHandler

//////////////////////////////////////////////////////////////////////////////
// Static initalizations
//////////////////////////////////////////////////////////////////////////////
LPTOP_LEVEL_EXCEPTION_FILTER	ExceptionHandler::m_previousFilter;
bool							ExceptionHandler::m_FirstUnhandledExceptionFilterFired = false;
SYSTEMTIME						ExceptionHandler::m_sessionStart;
OSVERSIONINFO					ExceptionHandler::m_osVers;
BOOL							ExceptionHandler::m_gotVersionInfo;
BOOL							ExceptionHandler::m_wow64Process;
HANDLE							ExceptionHandler::m_hProcess;
CRITICAL_SECTION				ExceptionHandler::m_crashDumpLock;
TCHAR							ExceptionHandler::m_szMinidumpDir[MAX_PATH];
MINIDUMP_TYPE					ExceptionHandler::m_minidumpType = MiniDumpNormal;
HMODULE							ExceptionHandler::m_hDbgHelpDll = NULL;
CString							ExceptionHandler::m_UserCrashData;
CString							ExceptionHandler::m_FaultingModuleName;
std::vector<CString>			ExceptionHandler::m_openedXmlTags;
UINT							ExceptionHandler::m_maxStackDepth = 100;
UINT							ExceptionHandler::m_maxTypeDumpDepth = 5;
INT								ExceptionHandler::m_callCount = 0;


ExceptionHandler::ExceptionHandler(void)
{
	m_previousFilter = SetUnhandledExceptionFilter(UnhandledExceptionFilter);

	GetSystemTime(&m_sessionStart);

	InitializeCriticalSection(&m_crashDumpLock);

	m_hProcess = GetCurrentProcess();

	//	Retrieving operating system info - needed in several functions
	m_osVers.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	m_gotVersionInfo = GetVersionEx(&m_osVers);

	m_wow64Process = FALSE;
	typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
	LPFN_ISWOW64PROCESS fnIsWow64Process = (LPFN_ISWOW64PROCESS) GetProcAddress(GetModuleHandle("kernel32"), "IsWow64Process");
	if (fnIsWow64Process != NULL) {
		fnIsWow64Process(m_hProcess, &m_wow64Process);
	}

	m_minidumpType = MiniDumpNormal;

	if (SUCCEEDED(SHGetFolderPath(NULL,
								  CSIDL_APPDATA | CSIDL_FLAG_CREATE,
								  NULL,
								  0,
								  m_szMinidumpDir)))
	{
		PathAppend(m_szMinidumpDir, "GME");
	}
	CreateDirectory(m_szMinidumpDir, 0);
}


ExceptionHandler::~ExceptionHandler(void)
{
	DeleteCriticalSection(&m_crashDumpLock);

	SetUnhandledExceptionFilter(m_previousFilter);
}


LONG WINAPI ExceptionHandler::UnhandledExceptionFilterOfMain(unsigned long xcptnum, PEXCEPTION_POINTERS pExp)
{
	m_FirstUnhandledExceptionFilterFired = true;

	UnhandledExceptionFilterCore("Unhandled Exception from CGMEApp::Run", pExp);

	return EXCEPTION_EXECUTE_HANDLER;
}


LONG WINAPI ExceptionHandler::UnhandledExceptionFilter(PEXCEPTION_POINTERS pExp)
{
	// This filter is installed as the UnhandledExceptionFilter
	m_FirstUnhandledExceptionFilterFired = true;

	if (!m_FirstUnhandledExceptionFilterFired)
		UnhandledExceptionFilterCore("Unhandled Exception for installed handler", pExp);

	return EXCEPTION_EXECUTE_HANDLER;
}


void ExceptionHandler::UnhandledExceptionFilterCore (const char* msg, PEXCEPTION_POINTERS pExp)
{
	EnterCriticalSection(&m_crashDumpLock);
	m_callCount++;

	if (m_callCount <= 2) {	// avoid stack overflow/infinite loop
		if (::GetCapture() != NULL)	// If the crash was during an in-place edit or any other operation which issues SetCapture, then release it!
			::ReleaseCapture();
		int retVal =
			AfxMessageBox("GME encountered an error! Do you want to generate a crash dump file?\n\n"
						  "The error can be analyzed with the help of this crash dump (Microsoft MiniDump) report file, "
						  "so it can significantly improve the quality of the program. "
						  "The file contains call stack, CPU register dump, and other crash related information. "
						  "Please click the checkbox below if you are willing to generate the crash dump. "
						  "You can find the file in the "
						  "\"%OSDir%\\Documents and Settings\\%UserName%\\Application Data\\GME\" folder on Windows XP or "
						  "\"%OSDir%\\Users\\%UserName%\\AppData\\Roaming\\GME\" folder on Windows Vista or Windows 7. "
						  "You can send the recent crash dump(s) to the following e-mail address: gme-supp@isis.vanderbilt.edu",
						  MB_ICONEXCLAMATION | MB_YESNO);
		if (retVal == IDYES) {
			LoadDbgHelpDll();
			GenerateUserStreamData(msg, pExp);
//			TRACE0(m_UserCrashData);
			TCHAR generatedFileName[MAX_PATH];
			GenerateFileName(generatedFileName);
			GenerateMiniDump(pExp, generatedFileName);
//			ShellExecute(NULL, "explore", m_szMinidumpDir, NULL, NULL, SW_SHOWNORMAL);	// Open up a Windows Explorer
		}
	}

	m_callCount--;
	LeaveCriticalSection(&m_crashDumpLock);
}


void ExceptionHandler::LoadDbgHelpDll(void)
{
	m_hDbgHelpDll = NULL;
	TCHAR szDbgHelpPath[_MAX_PATH];
	if (GetModuleFileName(NULL, szDbgHelpPath, _MAX_PATH)) {
		TCHAR *pSlash = _tcsrchr(szDbgHelpPath, '\\');
		if (pSlash) {
			_tcscpy(pSlash + 1, _T("DBGHELP.DLL"));
			m_hDbgHelpDll = LoadLibrary(szDbgHelpPath);
		}
	}

	if (m_hDbgHelpDll == NULL)
		m_hDbgHelpDll = LoadLibrary("DBGHELP.DLL");

	if (m_hDbgHelpDll) {
		pSymCleanup				= (tSymCleanup)				GetProcAddress(m_hDbgHelpDll, "SymCleanup");
		pSymInitialize			= (tSymInitialize)			GetProcAddress(m_hDbgHelpDll, "SymInitialize");
		pImgHlpApiVersion		= (tImgHlpApiVersion)		GetProcAddress(m_hDbgHelpDll, "ImagehlpApiVersion");
		pSymGetOptions			= (tSymGetOptions)			GetProcAddress(m_hDbgHelpDll, "SymGetOptions");
		pSymSetOptions			= (tSymSetOptions)			GetProcAddress(m_hDbgHelpDll, "SymSetOptions");
		pSymEnumSymbols			= (tSymEnumSymbols)			GetProcAddress(m_hDbgHelpDll, "SymEnumSymbols");
		pSymSetContext			= (tSymSetContext)			GetProcAddress(m_hDbgHelpDll, "SymSetContext");
		pSymGetLineFromAddr		= (tSymGetLineFromAddr)		GetProcAddress(m_hDbgHelpDll, "SymGetLineFromAddr");
		pSymFromAddr			= (tSymFromAddr)			GetProcAddress(m_hDbgHelpDll, "SymFromAddr");
		pStackWalk				= (tStackWalk)				GetProcAddress(m_hDbgHelpDll, "StackWalk");
		pSymFunctionTableAccess	= (tSymFunctionTableAccess)	GetProcAddress(m_hDbgHelpDll, "SymFunctionTableAccess");
		pSymGetModuleBase		= (tSymGetModuleBase)		GetProcAddress(m_hDbgHelpDll, "SymGetModuleBase");
		pSymGetTypeInfo			= (tSymGetTypeInfo)			GetProcAddress(m_hDbgHelpDll, "SymGetTypeInfo");
		pMiniDumpWriteDump		= (tMiniDumpWriteDump)		GetProcAddress(m_hDbgHelpDll, "MiniDumpWriteDump");
	}
}


void ExceptionHandler::GenerateFileName(TCHAR* pGeneratedFilePath)
{
	_tcscpy(pGeneratedFilePath, _T(""));

	TCHAR miniDumpFilePath[MAX_PATH];
	_tcscpy(miniDumpFilePath, m_szMinidumpDir);

	TCHAR minidumpFileName[MAX_PATH];
	_stprintf(
		minidumpFileName,
		_T("GME_CrashDump-%04d-%02d-%02d_(%02d-%02d-%02d)_%lu_%lu.dmp"),
		m_sessionStart.wYear,
		m_sessionStart.wMonth,
		m_sessionStart.wDay,
		m_sessionStart.wHour,
		m_sessionStart.wMinute,
		m_sessionStart.wSecond,
		GetCurrentProcessId(),
		GetCurrentThreadId()
	);

	// _tcscat(miniDumpFilePath, minidumpFileName);
	PathAppend(miniDumpFilePath, minidumpFileName);

	_tcscpy(pGeneratedFilePath, miniDumpFilePath);
}


void ExceptionHandler::GenerateMiniDump(PEXCEPTION_POINTERS pExceptionInfo, TCHAR* pGeneratedFilePath)
{
	if (pExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_STACK_OVERFLOW)
		return;

	if (m_hDbgHelpDll == NULL)
		return;

	if (pMiniDumpWriteDump == NULL) {
		FreeLibrary(m_hDbgHelpDll);
		return;
	}

	HANDLE hMiniDumpFile = CreateFile(pGeneratedFilePath, GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_ALWAYS, FILE_FLAG_WRITE_THROUGH, 0);
	if (hMiniDumpFile != INVALID_HANDLE_VALUE) {
		_MINIDUMP_EXCEPTION_INFORMATION minidumpExInfo;

		minidumpExInfo.ThreadId				= GetCurrentThreadId();
		minidumpExInfo.ExceptionPointers	= pExceptionInfo;
		minidumpExInfo.ClientPointers		= NULL;

		MINIDUMP_USER_STREAM user_stream;
		user_stream.Type		= LastReservedStream + 1;
		user_stream.Buffer		= m_UserCrashData.GetBuffer();
		user_stream.BufferSize	= m_UserCrashData.GetLength();
		MINIDUMP_USER_STREAM_INFORMATION user_stream_info;
		user_stream_info.UserStreamCount = 1;
		user_stream_info.UserStreamArray = &user_stream;

		pMiniDumpWriteDump(
			m_hProcess,
			GetCurrentProcessId(),
			hMiniDumpFile,
			m_minidumpType,
			&minidumpExInfo,
			&user_stream_info,
			NULL
		);

		CloseHandle(hMiniDumpFile);
	}

	FreeLibrary(m_hDbgHelpDll);
}


void ExceptionHandler::GenerateUserStreamData(const char* msg, PEXCEPTION_POINTERS pExceptionInfo)
{
	XMLTag xmlTag(CrashDumpXMLTag, m_openedXmlTags, m_UserCrashData);
	LogProgramInfo();
	LogOSInfo();
	LogExceptionInfo(msg, pExceptionInfo->ExceptionRecord);
	LogRegisters(pExceptionInfo->ContextRecord);
	LogFloatRegisters(pExceptionInfo->ContextRecord, pExceptionInfo->ExceptionRecord->ExceptionCode);
	LogCallStack(pExceptionInfo->ContextRecord, true);
}


void ExceptionHandler::LogProgramInfo(void)
{
	XMLTag programInfoTag(ProgramInfoXMLTag, m_openedXmlTags, m_UserCrashData);

	{
		char versionString[256];
		if (GetVersionString(NULL, versionString))
			XMLTag commandLineTag(ModulVersionXMLTag, versionString, m_openedXmlTags, m_UserCrashData);
	}

	{
		XMLTag programVersionTag(ProgramVersionXMLTag, m_openedXmlTags, m_UserCrashData);
		// Output Major Version
		XMLTag majorVersionTag(MajorVersionXMLTag, GME_VERSION_MAJOR, "%lu", m_openedXmlTags, m_UserCrashData);
		// Output Minor Version
		XMLTag minorVersionTag(MinorVersionXMLTag, GME_VERSION_MINOR, "%lu", m_openedXmlTags, m_UserCrashData);
		// Output Patch Level
		XMLTag patchLevelTag(PatchLevelXMLTag, GME_VERSION_PLEVEL, "%lu", m_openedXmlTags, m_UserCrashData);
	}

	// Output Command Line
	XMLTag commandLineTag(CommandLineXMLTag, GetCommandLine(), m_openedXmlTags, m_UserCrashData);
	// Output Process Id
	XMLTag processIdTag(ProcessIDXMLTag, GetCurrentProcessId(), "%lu", m_openedXmlTags, m_UserCrashData);
	// Output Thread Id
	XMLTag threadIdTag(ThreadIDXMLTag, GetCurrentThreadId(), "%lu", m_openedXmlTags, m_UserCrashData);
}


void ExceptionHandler::LogOSInfo(void)
{
	XMLTag osInfoTag(OSInfoXMLTag, m_openedXmlTags, m_UserCrashData);

	if (m_gotVersionInfo) {
		XMLTag osVersionTag(VersionInfoXMLTag, m_openedXmlTags, m_UserCrashData);
		DWORD buildNum = 0;
		switch (m_osVers.dwPlatformId) {
			case VER_PLATFORM_WIN32_WINDOWS: {
					XMLTag xmlTag(PlatformIdXMLTag, Windows9xPlatform, m_openedXmlTags, m_UserCrashData);
					buildNum = LOWORD(m_osVers.dwBuildNumber);
				}
				break;
			case VER_PLATFORM_WIN32_NT: {
					XMLTag xmlTag(PlatformIdXMLTag, WindowsNTPlatform, m_openedXmlTags, m_UserCrashData);
					buildNum = m_osVers.dwBuildNumber;
				}
				break;
		}
		// Output Major Version
		XMLTag majorVersionTag(MajorVersionXMLTag, m_osVers.dwMajorVersion, "%lu", m_openedXmlTags, m_UserCrashData);
		// Output Minor Version
		XMLTag minorVersionTag(MinorVersionXMLTag, m_osVers.dwMinorVersion, "%lu", m_openedXmlTags, m_UserCrashData);
		// Output Build Number
		XMLTag buildNumberTag(BuildNumberXMLTag, buildNum, "%lu", m_openedXmlTags, m_UserCrashData);
		// Output Bit Length (32/64)
		if (m_wow64Process) {
			XMLTag xmlTag(BitLengthXMLTag, Length64Bit, m_openedXmlTags, m_UserCrashData);
		} else {
			XMLTag xmlTag(BitLengthXMLTag, Length32Bit, m_openedXmlTags, m_UserCrashData);
		}
		// Output CSD Version
		XMLTag csdVersionTag(CSDVersionXMLTag, m_osVers.szCSDVersion, m_openedXmlTags, m_UserCrashData);
	}
}


void ExceptionHandler::LogExceptionInfo(const char* msg, PEXCEPTION_RECORD pExceptionRecord)
{
	XMLTag exceptionInfoTag(ExceptionInfoXMLTag, m_openedXmlTags, m_UserCrashData);

	// Output Exception Code
	XMLTag exceptionCodeTag(ExceptionCodeXMLTag, pExceptionRecord->ExceptionCode, m_openedXmlTags, m_UserCrashData);
	// Output Exception String (corresponding to the code)
	XMLTag exceptionStringTag(ExceptionStringXMLTag, GetExceptionString(pExceptionRecord->ExceptionCode), m_openedXmlTags, m_UserCrashData);
	// Output Exception User Message
	XMLTag exceptionUserMessageTag(ExceptionUserInfoXMLTag, msg, m_openedXmlTags, m_UserCrashData);

	XMLTag exceptionAddressTag(ExceptionAddressXMLTag, m_openedXmlTags, m_UserCrashData);
	// Output Fault Address

	XMLTag faultAddressTag(FaultAddressXMLTag, (DWORD)pExceptionRecord->ExceptionAddress, m_openedXmlTags, m_UserCrashData);
	if (IsBadReadPtr(pExceptionRecord->ExceptionAddress, 1)) {
		// Output Illegal address string
		XMLTag xmlTag(FaultingModuleXMLTag, IllegalAddressString, m_openedXmlTags, m_UserCrashData);
	} else {
		TCHAR szFaultingModule[MAX_PATH];
		DWORD section, offset;
		GetLogicalAddress(
			pExceptionRecord->ExceptionAddress,
			szFaultingModule,
			sizeof(szFaultingModule),
			section,
			offset
		);
		m_FaultingModuleName = szFaultingModule;

		// Output Image Section
		XMLTag imageSectionTag(ImageSectionXMLTag, section, "%04X", m_openedXmlTags, m_UserCrashData);
		// Output Address Offset
		XMLTag addressoOffsetTag(OffsetXMLTag, offset, m_openedXmlTags, m_UserCrashData);
		// Output Faulting Module
		XMLTag faultingModuleTag(FaultingModuleXMLTag, szFaultingModule, m_openedXmlTags, m_UserCrashData);
	}
}


void ExceptionHandler::LogRegisters(PCONTEXT pContextRecord)
{
	XMLTag registersTag(RegistersXMLTag, m_openedXmlTags, m_UserCrashData);

#if defined(_M_IX86) || defined(_M_X64)	// X86 Only!
	// Output EAX
	XMLTag eaxTag(EAXRegisterXMLTag, pContextRecord->Eax, m_openedXmlTags, m_UserCrashData);
	// Output EBX
	XMLTag ebxTag(EBXRegisterXMLTag, pContextRecord->Ebx, m_openedXmlTags, m_UserCrashData);
	// Output ECX
	XMLTag ecxTag(ECXRegisterXMLTag, pContextRecord->Ecx, m_openedXmlTags, m_UserCrashData);
	// Output EDX
	XMLTag edxTag(EDXRegisterXMLTag, pContextRecord->Edx, m_openedXmlTags, m_UserCrashData);
	// Output ESI
	XMLTag esiTag(ESIRegisterXMLTag, pContextRecord->Esi, m_openedXmlTags, m_UserCrashData);
	// Output EDI
	XMLTag ediTag(EDIRegisterXMLTag, pContextRecord->Edi, m_openedXmlTags, m_UserCrashData);

	// Output CS
	XMLTag csTag(CSRegisterXMLTag, pContextRecord->SegCs, "%04X", m_openedXmlTags, m_UserCrashData);
	// Output EIP
	XMLTag eipTag(EIPRegisterXMLTag, pContextRecord->Eip, m_openedXmlTags, m_UserCrashData);

	// Output SS
	XMLTag ssTag(SSRegisterXMLTag, pContextRecord->SegSs, "%04X", m_openedXmlTags, m_UserCrashData);
	// Output ESP
	XMLTag espTag(ESPRegisterXMLTag, pContextRecord->Esp, m_openedXmlTags, m_UserCrashData);
	// Output EBP
	XMLTag ebpTag(EBPRegisterXMLTag, pContextRecord->Ebp, m_openedXmlTags, m_UserCrashData);

	// Output DS
	XMLTag dsTag(DSRegisterXMLTag, pContextRecord->SegDs, "%04X", m_openedXmlTags, m_UserCrashData);
	// Output ES
	XMLTag esTag(ESRegisterXMLTag, pContextRecord->SegEs, "%04X", m_openedXmlTags, m_UserCrashData);
	// Output FS
	XMLTag fsTag(FSRegisterXMLTag, pContextRecord->SegFs, "%04X", m_openedXmlTags, m_UserCrashData);
	// Output GS
	XMLTag gsTag(GSRegisterXMLTag, pContextRecord->SegGs, "%04X", m_openedXmlTags, m_UserCrashData);

	// Output EFlags
	XMLTag flagsTag(GSRegisterXMLTag, pContextRecord->EFlags, m_openedXmlTags, m_UserCrashData);
#endif
}


#if defined(_M_IX86) || defined(_M_X64)	// X86 Only!
static double TempReal2Double(const unsigned char* pTempReal)
{
	double	retValue;
	char	buffer[10];

	CopyMemory(buffer, pTempReal, sizeof(buffer));

	__asm FNINIT;
	__asm FLD TBYTE PTR buffer;
	__asm FSTP retValue;
	__asm FNCLEX;

	return retValue;
}
#endif


void ExceptionHandler::LogFloatRegisters(PCONTEXT pContextRecord, DWORD exceptionCode)
{
	XMLTag fpRegistersTag(FPRegistersXMLTag, m_openedXmlTags, m_UserCrashData);

#if defined (_M_IX86)
	// Output Control Word
	XMLTag controlWordTag(ControlWordXMLTag, pContextRecord->FloatSave.ControlWord, "%04X", m_openedXmlTags, m_UserCrashData);
	// Output Status Word
	XMLTag statusWordTag(StatusWordXMLTag, pContextRecord->FloatSave.StatusWord, "%04X", m_openedXmlTags, m_UserCrashData);
	// Output Tag Word
	XMLTag tagWordTag(TagWordXMLTag, pContextRecord->FloatSave.TagWord, "%04X", m_openedXmlTags, m_UserCrashData);

	// Output Error Selector
	XMLTag errorSelectorTag(ErrorSelectorXMLTag, pContextRecord->FloatSave.ErrorSelector, "%04X", m_openedXmlTags, m_UserCrashData);
	// Output Error Offset
	XMLTag errorOffsetTag(ErrorOffsetXMLTag, pContextRecord->FloatSave.ErrorOffset, m_openedXmlTags, m_UserCrashData);

	// Output Data Selector
	XMLTag dataSelectorTag(DataSelectorXMLTag, pContextRecord->FloatSave.DataSelector, "%04X", m_openedXmlTags, m_UserCrashData);
	// Output Data Offset
	XMLTag dataOffsetTag(DataOffsetXMLTag, pContextRecord->FloatSave.DataOffset, m_openedXmlTags, m_UserCrashData);

	// Output Cr0Npx State
	XMLTag cr0NpxStateTag(Cr0NpxStateXMLTag, pContextRecord->FloatSave.Cr0NpxState, m_openedXmlTags, m_UserCrashData);

	int topOfStack = (pContextRecord->FloatSave.StatusWord & 0x3800) >> 11;
	for (int i = 0 ; i < 8 ; i++) {
		int index = (topOfStack + i) % 8;
		int tag = (pContextRecord->FloatSave.TagWord & (0x3 << (2 * index))) >> (2 * index);
		switch (tag) {
			case 0:
			case 1:
				if (exceptionCode != EXCEPTION_FLT_INVALID_OPERATION) {
					CString buffer;
					buffer.Format("%+026.18E", TempReal2Double(&pContextRecord->FloatSave.RegisterArea[i * 10]));
					XMLTag fpRegisterTag(FPRegisterXMLTag, buffer, m_openedXmlTags, m_UserCrashData);
				}
				break;
			case 2: {
					XMLTag fpRegisterTag(FPRegisterXMLTag, "NAN", m_openedXmlTags, m_UserCrashData);
				}
				break;
			case 3: {
					XMLTag fpRegisterTag(FPRegisterXMLTag, "EMPTY", m_openedXmlTags, m_UserCrashData);
				}
				break;
			default: {
					XMLTag fpRegisterTag(FPRegisterXMLTag, "???", m_openedXmlTags, m_UserCrashData);
				}
				break;
		}
		{
			CString buffer;
			buffer.Format("%016I64X", *(__int64*)(&pContextRecord->FloatSave.RegisterArea[i * 10]));
			XMLTag fpHexaStrTag(FPHexStringXMLTag, buffer, m_openedXmlTags, m_UserCrashData);
		}
	}

	if (exceptionCode == EXCEPTION_FLT_INVALID_OPERATION) {
		_clearfp();
	}
#endif
}


//============================================================
// Walks the stack, and logs the results
// bWriteVariables: true if local/params should be output
//============================================================
void ExceptionHandler::LogCallStack(PCONTEXT pContextRecord, bool bWriteVariables)
{
	XMLTag callStackTag(CallStackXMLTag, m_openedXmlTags, m_UserCrashData);

	if (m_hDbgHelpDll != NULL) {
		char versionString[256];
		if (GetVersionString(m_hDbgHelpDll, versionString))
			XMLTag commandLineTag(DbgHelpVersionXMLTag, versionString, m_openedXmlTags, m_UserCrashData);

		if (pImgHlpApiVersion != NULL) {
			API_VERSION* pApiVersion = pImgHlpApiVersion();
			if (pApiVersion != NULL) {
				XMLTag imageHelpApiVersionTag(ImageHelpApiVersionXMLTag, m_openedXmlTags, m_UserCrashData);
				// Output Major Version
				XMLTag majorVersionTag(MajorVersionXMLTag, pApiVersion->MajorVersion, "%lu", m_openedXmlTags, m_UserCrashData);
				// Output Minor Version
				XMLTag minorVersionTag(MinorVersionXMLTag, pApiVersion->MinorVersion, "%lu", m_openedXmlTags, m_UserCrashData);
				// Output Revision Number
				XMLTag revisionNumberTag(RevisionNumberXMLTag, pApiVersion->Revision, "%lu", m_openedXmlTags, m_UserCrashData);
				// Output Reserved Data
				XMLTag reservedTag(ReservedXMLTag, pApiVersion->Reserved, "%lu", m_openedXmlTags, m_UserCrashData);
			}
		}
	} else {
		return;
	}

	if (pStackWalk				== NULL ||
		pSymFunctionTableAccess	== NULL ||
		pSymGetModuleBase		== NULL)
	{
		return;
	}

	DWORD dwMachineType = 0;
	// Could use SymSetOptions here to add the SYMOPT_DEFERRED_LOADS flag

	STACKFRAME sf;
	memset(&sf, 0, sizeof(sf));

#ifdef _M_IX86
	// Initialize the STACKFRAME structure for the first call. This is only
	// necessary for Intel CPUs, and isn't mentioned in the documentation.
	sf.AddrPC.Offset		= pContextRecord->Eip;
	sf.AddrPC.Mode			= AddrModeFlat;
	sf.AddrStack.Offset		= pContextRecord->Esp;
	sf.AddrStack.Mode		= AddrModeFlat;
	sf.AddrFrame.Offset		= pContextRecord->Ebp;
	sf.AddrFrame.Mode		= AddrModeFlat;

	dwMachineType = IMAGE_FILE_MACHINE_I386;
#elif _M_X64
	imageType = IMAGE_FILE_MACHINE_AMD64;
	sf.AddrPC.Offset		= pContextRecord->Rip;
	sf.AddrPC.Mode			= AddrModeFlat;
	sf.AddrFrame.Offset		= pContextRecord->Rsp;
	sf.AddrFrame.Mode		= AddrModeFlat;
	sf.AddrStack.Offset		= pContextRecord->Rsp;
	sf.AddrStack.Mode		= AddrModeFlat;
#else
#error "Platform not supported!"
#endif

	// Set up the symbol engine.
	DWORD dwOpts = pSymGetOptions();

	// Turn on line loading and deferred loading.
	pSymSetOptions(dwOpts					|
				   SYMOPT_DEFERRED_LOADS	|
				   SYMOPT_UNDNAME			|
				   SYMOPT_LOAD_LINES);

	// Initialize DbgHelp
	if (!pSymInitialize(m_hProcess, 0, TRUE))
		return;

/*
#if defined(_M_IX86) || defined(_M_X64)	// X86 Only!
	XMLTag globalVariablesTag(GlobalVariablesXMLTag, m_openedXmlTags, m_UserCrashData);

	if (bWriteVariables && pSymEnumSymbols != NULL && m_FaultingModuleName.GetLength() > 0) {
		m_maxTypeDumpDepth = 1;
		if (!pSymEnumSymbols(m_hProcess,
							 (DWORD64)GetModuleHandle(m_FaultingModuleName),
							 0, EnumerateSymbolsCallback, 0))
		{
			globalVariablesTag.Println("Unsuccesful Enumeration");
		}
	}
#endif	// X86 Only!
*/

	UINT m_stackDepth = 0;
	while (m_stackDepth < m_maxStackDepth) {
		// Get the next stack frame
		if (!pStackWalk(dwMachineType,
						m_hProcess,
						GetCurrentThread(),
						&sf,
						pContextRecord,
						0,
						pSymFunctionTableAccess,
						pSymGetModuleBase,
						0))
			break;

		if (0 == sf.AddrFrame.Offset)	// Basic sanity check to make sure
			break;						// the frame is OK. Bail if not.

		XMLTag stackLevelTag(StackLevelXMLTag, m_openedXmlTags, m_UserCrashData);

		XMLTag addresTag(AddressXMLTag, m_openedXmlTags, m_UserCrashData, sf.AddrPC.Offset, "%I64X");
		XMLTag frameTag(FrameXMLTag, m_openedXmlTags, m_UserCrashData, sf.AddrFrame.Offset, "%I64X");

		// Get the name of the function for this stack frame entry
		BYTE symbolBuffer[sizeof(SYMBOL_INFO) + 1024];
		PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)symbolBuffer;
		pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
		pSymbol->MaxNameLen = 1024;
						
		DWORD64 symDisplacement = 0;	// Displacement of the input address,
										// relative to the start of the symbol

		if (pSymFromAddr != NULL && pSymFromAddr(m_hProcess, sf.AddrPC.Offset, &symDisplacement, pSymbol)) {
			XMLTag symbolNameTag(SymbolNameXMLTag, pSymbol->Name, m_openedXmlTags, m_UserCrashData);
			XMLTag symbolDispTag(SymbolDisplacementXMLTag, m_openedXmlTags, m_UserCrashData, symDisplacement, "%I64X");
		} else {
			// No symbol found. Print out the logical address instead.
			TCHAR szModule[MAX_PATH] = _T("");
			DWORD section = 0;
			DWORD offset = 0;

			GetLogicalAddress((PVOID)sf.AddrPC.Offset, szModule, sizeof(szModule), section, offset);

			// Output Image Section
			XMLTag imageSectionTag(ImageSectionXMLTag, section, "%04X", m_openedXmlTags, m_UserCrashData);
			// Output Address Offset
			XMLTag addressoOffsetTag(OffsetXMLTag, offset, m_openedXmlTags, m_UserCrashData);
			// Output Module Name
			XMLTag moduleNameTag(ModuleNameXMLTag, szModule, m_openedXmlTags, m_UserCrashData);
		}

		// Get the source line for this stack frame entry
		IMAGEHLP_LINE lineInfo;
		memset(&lineInfo, 0, sizeof(IMAGEHLP_LINE));
		lineInfo.SizeOfStruct = sizeof(IMAGEHLP_LINE);
		DWORD dwLineDisplacement;
		if (pSymGetLineFromAddr != NULL && pSymGetLineFromAddr(m_hProcess, sf.AddrPC.Offset, &dwLineDisplacement, &lineInfo)) {
			// Output Source File
			XMLTag sourceFileTag(SourceFileXMLTag, lineInfo.FileName, m_openedXmlTags, m_UserCrashData);
			// Output Line Info
			XMLTag lineInfoTag(LineInfoXMLTag, lineInfo.LineNumber, "%lu", m_openedXmlTags, m_UserCrashData);
		}

#if defined(_M_IX86) || defined(_M_X64)	// X86 Only!
		// Write out the variables, if desired
		if (bWriteVariables &&
			pSymSetContext	!= NULL &&
			pSymEnumSymbols	!= NULL &&
			pSymGetTypeInfo	!= NULL)
		{
			XMLTag variablesTag(VariablesXMLTag, m_openedXmlTags, m_UserCrashData);

			// Use SymSetContext to get just the locals/params for this frame
			IMAGEHLP_STACK_FRAME imagehlpStackFrame;
			imagehlpStackFrame.InstructionOffset = sf.AddrPC.Offset;
			pSymSetContext(m_hProcess, &imagehlpStackFrame, 0);

			// Enumerate the locals/parameters
			m_maxTypeDumpDepth = 5;
			pSymEnumSymbols(m_hProcess, 0, 0, EnumerateSymbolsCallback, &sf);
		}
#endif
		m_stackDepth++;
	}

	pSymCleanup(m_hProcess);
}


CString ExceptionHandler::GetExceptionString(DWORD exceptionCode)
{
	#define EXCEPTION(x) case EXCEPTION_##x: return _T(#x);

	switch (exceptionCode) {
		EXCEPTION(ACCESS_VIOLATION)
		EXCEPTION(DATATYPE_MISALIGNMENT)
		EXCEPTION(BREAKPOINT)
		EXCEPTION(SINGLE_STEP)
		EXCEPTION(ARRAY_BOUNDS_EXCEEDED)
		EXCEPTION(FLT_DENORMAL_OPERAND)
		EXCEPTION(FLT_DIVIDE_BY_ZERO)
		EXCEPTION(FLT_INEXACT_RESULT)
		EXCEPTION(FLT_INVALID_OPERATION)
		EXCEPTION(FLT_OVERFLOW)
		EXCEPTION(FLT_STACK_CHECK)
		EXCEPTION(FLT_UNDERFLOW)
		EXCEPTION(INT_DIVIDE_BY_ZERO)
		EXCEPTION(INT_OVERFLOW)
		EXCEPTION(PRIV_INSTRUCTION)
		EXCEPTION(IN_PAGE_ERROR)
		EXCEPTION(ILLEGAL_INSTRUCTION)
		EXCEPTION(NONCONTINUABLE_EXCEPTION)
		EXCEPTION(STACK_OVERFLOW)
		EXCEPTION(INVALID_DISPOSITION)
		EXCEPTION(GUARD_PAGE)
		EXCEPTION(INVALID_HANDLE)
	}

	// If not one of the "known" exceptions, try to get the string
	// from NTDLL.DLL's message table.
	TCHAR szBuffer[512] = { 0 };

	FormatMessage(
		FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_HMODULE,
		GetModuleHandle(_T("NTDLL.DLL")),
		exceptionCode,
		0,
		szBuffer,
		sizeof(szBuffer),
		0
	);

	CString buffer(szBuffer);
	return buffer;
}


BOOL ExceptionHandler::GetLogicalAddress(PVOID addr, PTSTR szModule, DWORD len, DWORD& section, DWORD& offset)
{
	MEMORY_BASIC_INFORMATION mbi;

	if (!VirtualQuery(addr, &mbi, sizeof(mbi)))
		return FALSE;

	DWORD hMod = (DWORD) mbi.AllocationBase;

	char exePath[_MAX_PATH];
	if (!GetModuleFileName((HMODULE) hMod, exePath, sizeof(exePath)))
		return FALSE;

	char exeFname[_MAX_FNAME];
	char exeExt[_MAX_EXT];
	_splitpath(exePath, NULL, NULL, exeFname, exeExt);
	char exeFile[_MAX_PATH];
	_makepath(exeFile, NULL, NULL, exeFname, exeExt);
	strncpy(szModule, exeFile, len);

	if (hMod == NULL)
		return FALSE;

	// Point to the DOS header in memory
	PIMAGE_DOS_HEADER pDosHdr		= (PIMAGE_DOS_HEADER)hMod;
	// From the DOS header, find the NT (PE) header
	PIMAGE_NT_HEADERS pNtHdr		= (PIMAGE_NT_HEADERS)(hMod + pDosHdr->e_lfanew);

	PIMAGE_SECTION_HEADER pSection	= IMAGE_FIRST_SECTION(pNtHdr);

	DWORD rva = (DWORD) addr - hMod;	// RVA is offset from module load address

	// Iterate through the section table, looking for the one that encompasses
	// the linear address.
	for (unsigned int i = 0; i < pNtHdr->FileHeader.NumberOfSections; i++, pSection++) {
		DWORD sectionStart = pSection->VirtualAddress;
		DWORD sectionEnd = sectionStart + max (pSection->SizeOfRawData, pSection->Misc.VirtualSize);

		// Is the address in this section???
		if ((rva >= sectionStart) && (rva <= sectionEnd)) {
			// Yes, address is in the section.  Calculate section and offset,
			// and store in the "section" & "offset" params, which were
			// passed by reference.
			section = i + 1;
			offset = rva - sectionStart;
			return TRUE;
		}
	}

	return FALSE;	// Should never get here!
}


BOOL ExceptionHandler::GetVersionString(HINSTANCE hModul, char* versionString)
{
	char	fileName[256];
	char	puffer[256];
	char*	stringData;
	DWORD	dwHandle;
	DWORD	verInfoSize;
	DWORD*	dwTranslation;
	void*	pVerInfo;
	UINT	uLen;

	if (versionString == NULL)
		return FALSE;

	strcpy(versionString, "");

	GetModuleFileName(hModul, fileName, sizeof(fileName));
	verInfoSize = GetFileVersionInfoSize(fileName, &dwHandle);

	if (verInfoSize == 0)
		return FALSE;

	pVerInfo = malloc(verInfoSize);

	if (pVerInfo == NULL)
		return FALSE;

	if (!GetFileVersionInfo(fileName, dwHandle, verInfoSize, pVerInfo)) {
		free(pVerInfo);
		return FALSE;
	}

#if defined (_DEBUG)
	dwTranslation = NULL;
#endif
	if (!VerQueryValue(pVerInfo, (LPTSTR) "\\VarFileInfo\\Translation", (LPVOID*) &dwTranslation, &uLen)) {
		uLen = 0;
	}

	if (uLen != sizeof(DWORD)) {
		free(pVerInfo);
		return FALSE;
	}

	if (dwTranslation == NULL) {
		free(pVerInfo);
		return FALSE;
	}

	wsprintf(
		puffer,
		"\\StringFileInfo\\%04x%04x\\FileVersion",
		LOWORD (*(DWORD *) (dwTranslation)),
		HIWORD (*(DWORD *) (dwTranslation))
	);

	if (VerQueryValue(pVerInfo, puffer, (LPVOID*) &stringData, &uLen)) {
		if (uLen != 0)
			CopyMemory(versionString, stringData, uLen);
	}

	free(pVerInfo);

	return TRUE;
}


//////////////////////////////////////////////////////////////////////////////
// The function invoked by SymEnumSymbols
//////////////////////////////////////////////////////////////////////////////
BOOL CALLBACK ExceptionHandler::EnumerateSymbolsCallback(PSYMBOL_INFO pSymInfo, ULONG SymbolSize, PVOID UserContext)
{
	__try
	{
		FormatSymbolValue(pSymInfo, (STACKFRAME*)UserContext);
	}
	__except(1)
	{
		TRACE0("Variable enumeration error during stack walk.\n");
	}

	return TRUE;
}


//////////////////////////////////////////////////////////////////////////////
// Given a SYMBOL_INFO representing a particular variable, displays its
// contents. If it's a user defined type, display the members and their
// values.
//////////////////////////////////////////////////////////////////////////////
bool ExceptionHandler::FormatSymbolValue(PSYMBOL_INFO pSym, STACKFRAME* sf)
{
	XMLTag* variableTag = NULL;
	// Indicate if the variable is a local or parameter
	if (pSym->Flags & IMAGEHLP_SYMBOL_INFO_PARAMETER)
		variableTag = new XMLTag(ParameterXMLTag, m_openedXmlTags, m_UserCrashData);
	else if (pSym->Flags & IMAGEHLP_SYMBOL_INFO_LOCAL)
		variableTag = new XMLTag(LocalXMLTag, m_openedXmlTags, m_UserCrashData);

	// If it's a function, don't do anything.
	if (pSym->Tag == 5) {	// SymTagFunction from CVCONST.H from the DIA SDK
		variableTag->Appendln(SymTagFunctionXMLTag);
		delete variableTag;
		return false;
	}

	// Emit the variable name
	XMLTag variableNameTag(VariableNameXMLTag, pSym->Name, m_openedXmlTags, m_UserCrashData);

	DWORD_PTR pVariable = 0;	// Will point to the variable's data in memory

	if (pSym->Flags & IMAGEHLP_SYMBOL_INFO_REGRELATIVE) {
		// if ( pSym->Register == 8 )	// EBP is the value 8 (in DBGHELP 5.1)
		if (sf != NULL) {				// This may change!!!
			pVariable = sf->AddrFrame.Offset;
			pVariable += (DWORD_PTR)pSym->Address;
		}
		// else {
		//	delete variableTag;
		//	return false;
		// }
	} else if (pSym->Flags & IMAGEHLP_SYMBOL_INFO_REGISTER) {		
		XMLTag registerTag(RegisterXMLTag, m_openedXmlTags, m_UserCrashData);
		delete variableTag;
		return false;	// Don't try to report register variable
	} else {
		pVariable = (DWORD_PTR)pSym->Address;	// It must be a global variable
	}

	// Determine if the variable is a user defined type (UDT). IF so, bHandled
	// will return true.
	bool bHandled = DumpTypeIndex(pSym->ModBase, pSym->TypeIndex, pVariable, 0);

	if (!bHandled) {
		// The symbol wasn't a UDT, so do basic, stupid formatting of the
		// variable.  Based on the size, we're assuming it's a char, WORD, or
		// DWORD.
		BasicType basicType = GetBasicType(pSym->TypeIndex, pSym->ModBase);
		
		FormatOutputValue(basicType, pSym->Size, (PVOID)pVariable);
	}
	delete variableTag;
	return true;
}


//////////////////////////////////////////////////////////////////////////////
// If it's a user defined type (UDT), recurse through its members until we're
// at fundamental types. When he hit fundamental types, return
// bHandled = false, so that FormatSymbolValue() will format them.
//////////////////////////////////////////////////////////////////////////////
bool ExceptionHandler::DumpTypeIndex(DWORD64 modBase, DWORD dwTypeIndex, DWORD_PTR offset, UINT level)
{
	XMLTag TypeDumpTag(TypeDumpXMLTag, m_openedXmlTags, m_UserCrashData);

	// Get the name of the symbol. This will either be a Type name (if a UDT),
	// or the structure member name.
	WCHAR* pwszTypeName;
	if (pSymGetTypeInfo(m_hProcess, modBase, dwTypeIndex, TI_GET_SYMNAME, &pwszTypeName)) {
		XMLTag typeNameTag(TypeNameXMLTag, pwszTypeName, m_openedXmlTags, m_UserCrashData);
		LocalFree(pwszTypeName);
	}

	// Determine how many children this type has.
	DWORD dwChildrenCount = 0;
	pSymGetTypeInfo(m_hProcess, modBase, dwTypeIndex, TI_GET_CHILDRENCOUNT, &dwChildrenCount);

	if (!dwChildrenCount)	// If no children, we're done
		return false;

	// Prepare to get an array of "TypeIds", representing each of the children.
	// SymGetTypeInfo(TI_FINDCHILDREN) expects more memory than just a
	// TI_FINDCHILDREN_PARAMS struct has.  Use derivation to accomplish this.
	struct FINDCHILDREN : TI_FINDCHILDREN_PARAMS
	{
		ULONG	MoreChildIds[1024];
		FINDCHILDREN() { Count = sizeof(MoreChildIds) / sizeof(MoreChildIds[0]); }
	} children;

	children.Count = dwChildrenCount;
	children.Start= 0;

	// Get the array of TypeIds, one for each child type
	if (!pSymGetTypeInfo(m_hProcess, modBase, dwTypeIndex, TI_FINDCHILDREN, &children))
		return false;

	// Iterate through each of the children
	for (unsigned long i = 0; i < dwChildrenCount; i++) {
		// Recurse for each of the child types
		bool bHandled2 = false;
		if (level < m_maxTypeDumpDepth)
			bHandled2 = DumpTypeIndex(modBase, children.ChildId[i], offset, level + 1);

		// If the child wasn't a UDT, format it appropriately
		if (!bHandled2) {
			// Get the offset of the child member, relative to its parent
			DWORD dwMemberOffset;
			pSymGetTypeInfo(m_hProcess, modBase, children.ChildId[i], TI_GET_OFFSET, &dwMemberOffset);

			// Get the real "TypeId" of the child.  We need this for the
			// SymGetTypeInfo(TI_GET_TYPEID) call below.
			DWORD typeId;
			pSymGetTypeInfo(m_hProcess, modBase, children.ChildId[i], TI_GET_TYPEID, &typeId);

			// Get the size of the child member
			ULONG64 length;
			pSymGetTypeInfo(m_hProcess, modBase, typeId, TI_GET_LENGTH, &length);

			// Calculate the address of the member

			DWORD_PTR dwFinalOffset = offset + dwMemberOffset;

			BasicType basicType = GetBasicType(children.ChildId[i], modBase);

			FormatOutputValue(basicType, length, (PVOID)dwFinalOffset);
		}
	}

	return true;
}


void ExceptionHandler::FormatOutputValue(BasicType basicType, DWORD64 length, PVOID pAddress)
{
	// Format appropriately (assuming it's a 1, 2, or 4 bytes (!!!)
	char valueString[256] = "";
	if (length == 1) {
		sprintf(valueString, "%X", *(PBYTE)pAddress);
	} else if (length == 2) {
		sprintf(valueString, "%X", *(PWORD)pAddress);
	} else if (length == 4) {
		if (basicType == btFloat) {
			sprintf(valueString, "%f", *(PFLOAT)pAddress);
		} else if (basicType == btChar) {
			sprintf(valueString, "%lX", *(PDWORD)pAddress);
		} else {
			sprintf(valueString, "%lX", *(PDWORD)pAddress);
		}
	} else if (length == 8) {
		if (basicType == btFloat)
			sprintf(valueString, "%lf", *(double *)pAddress);
		else
			sprintf(valueString, "%I64X", *(DWORD64*)pAddress);
	}
	XMLTag valueTag(ValueXMLTag, valueString, m_openedXmlTags, m_UserCrashData);
}


BasicType ExceptionHandler::GetBasicType(DWORD typeIndex, DWORD64 modBase)
{
	BasicType basicType;
	if (pSymGetTypeInfo(m_hProcess, modBase, typeIndex, TI_GET_BASETYPE, &basicType))
		return basicType;

	// Get the real "TypeId" of the child.  We need this for the
	// SymGetTypeInfo( TI_GET_TYPEID ) call below.
	DWORD typeId;
	if (pSymGetTypeInfo(m_hProcess,modBase, typeIndex, TI_GET_TYPEID, &typeId)) {
		if (pSymGetTypeInfo(m_hProcess, modBase, typeId, TI_GET_BASETYPE, &basicType))
			return basicType;
	}

	return btNoType;
}

