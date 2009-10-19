/////////////////////////////////////////////////////////////////////////////
//
// ExceptionHandler.h : Exception handler filter,
//						minidump and XML crash dump writer
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(EXCEPTION_HANDLER_INCLUDED)
#define EXCEPTION_HANDLER_INCLUDED

//////////////////////////////////////////////////////////////////////////////
// Includes
//////////////////////////////////////////////////////////////////////////////

#include <Windows.h>
#include <DbgHelp.h>
#include <vector>


//////////////////////////////////////////////////////////////////////////////
// Types
//////////////////////////////////////////////////////////////////////////////

enum BasicType {	// Stolen from CVCONST.H in the DIA 2.0 SDK
	btNoType	= 0,
	btVoid		= 1,
	btChar		= 2,
	btWChar		= 3,
	btInt		= 6,
	btUInt		= 7,
	btFloat		= 8,
	btBCD		= 9,
	btBool		= 10,
	btLong		= 13,
	btULong		= 14,
	btCurrency	= 25,
	btDate		= 26,
	btVariant	= 27,
	btComplex	= 28,
	btBit		= 29,
	btBSTR		= 30,
	btHresult	= 31
};


//============================================================
// XMLTag
// Helper function for writing the XML format data
//============================================================
class XMLTag
{
	std::vector<CString>&	m_openedXmlTags;
	CString&				m_UserCrashData;
	bool					m_closed;

	void AddTabs(void);
	void AddTabs(DWORD tabCount);
	void AddRawText(CString text, bool escape = true);
	void PrintTag(const TCHAR* tagString, bool open, bool withTabs, bool nl);

public:
	XMLTag(const TCHAR* tagString, std::vector<CString>& openedXmlTags, CString& userCrashData);
	XMLTag(const TCHAR* tagString, const TCHAR* text, std::vector<CString>& openedXmlTags, CString& userCrashData);
	XMLTag(const TCHAR* tagString, const WCHAR* text, std::vector<CString>& openedXmlTags, CString& userCrashData);
	XMLTag(const TCHAR* tagString, DWORD value, const TCHAR* formatString, std::vector<CString>& openedXmlTags,
		   CString& userCrashData);
	XMLTag(const TCHAR* tagString, std::vector<CString>& openedXmlTags, CString& userCrashData,
		   DWORD64 value, const TCHAR* formatString);
	XMLTag(const TCHAR* tagString, DWORD value, std::vector<CString>& openedXmlTags, CString& userCrashData);
	~XMLTag();

	void OpenTag(const TCHAR* tagString, bool withTabs = true, bool nl = true);
	void Print(const TCHAR* text);
	void Println(const TCHAR* text);
	void Append(const TCHAR* text);
	void Appendln(const TCHAR* text);
	void CloseTag(bool withTabs = true, bool nl = true);
};


//============================================================
// ExceptionHandler
// UnhandledExceptionFilter and helper functions and members
//============================================================
class ExceptionHandler
{
	static LPTOP_LEVEL_EXCEPTION_FILTER	m_previousFilter;
	static bool							m_FirstUnhandledExceptionFilterFired;
	static SYSTEMTIME					m_sessionStart;
	static OSVERSIONINFO				m_osVers;
	static BOOL							m_gotVersionInfo;
	static BOOL							m_wow64Process;
	static HANDLE						m_hProcess;
	static CRITICAL_SECTION				m_crashDumpLock;
	static TCHAR						m_szMinidumpDir[MAX_PATH];
	static MINIDUMP_TYPE				m_minidumpType;

	static HMODULE						m_hDbgHelpDll;
	static CString						m_UserCrashData;
	static CString						m_FaultingModuleName;
	static std::vector<CString>			m_openedXmlTags;
	static UINT							m_maxStackDepth;
	static UINT							m_maxTypeDumpDepth;
	static INT							m_callCount;	// To avoid recursive crash reports, like in case of crash in OnActivate, AfxMessageBox causes another Activate, see JIRA GME-216

public:
	ExceptionHandler(void);
	~ExceptionHandler(void);

	static LONG WINAPI		UnhandledExceptionFilterOfMain(unsigned long xcptnum, PEXCEPTION_POINTERS pExp);
	static LONG WINAPI		UnhandledExceptionFilter(PEXCEPTION_POINTERS pExp);

private:
	static void				UnhandledExceptionFilterCore (const char* msg, PEXCEPTION_POINTERS pExp);

	static void				LoadDbgHelpDll(void);
	static void				GenerateFileName(TCHAR* pGeneratedFilePath);
	static void				GenerateMiniDump(PEXCEPTION_POINTERS pExceptionInfo, TCHAR* miniDumpPath);
	static void				GenerateUserStreamData(const char* msg, PEXCEPTION_POINTERS pExceptionInfo);

	static void				LogProgramInfo(void);
	static void				LogOSInfo(void);
	static void				LogExceptionInfo(const char* msg, PEXCEPTION_RECORD pExceptionRecord);
	static void				LogRegisters(PCONTEXT pContextRecord);
	static void				LogFloatRegisters(PCONTEXT pContextRecord, DWORD exceptionCode);
	static void				LogCallStack(PCONTEXT pContextRecord, bool bWriteVariables);

	static CString			GetExceptionString(DWORD exceptionCode);
	static BOOL				GetLogicalAddress(PVOID addr, PTSTR szModule, DWORD len, DWORD& section, DWORD& offset);
	static BOOL				GetVersionString(HINSTANCE hModul, char* versionString);

	static BOOL CALLBACK	EnumerateSymbolsCallback(PSYMBOL_INFO pSymInfo, ULONG SymbolSize, PVOID UserContext);
	static bool				FormatSymbolValue(PSYMBOL_INFO pSym, STACKFRAME* sf);
	static bool				DumpTypeIndex(DWORD64 modBase, DWORD dwTypeIndex, DWORD_PTR offset, UINT level);
	static void				FormatOutputValue(BasicType basicType, DWORD64 length, PVOID pAddress);
	static BasicType		GetBasicType(DWORD typeIndex, DWORD64 modBase);
};

#endif // !defined(EXCEPTION_HANDLER_INCLUDED)
