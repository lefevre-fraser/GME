///////////////////////////////////////////////////////////////////////////////
//
// ExtractCrashDumpXML.cpp
//
// Read user data streams from the minidump
//
// Original code by: Oleg Starodumov (www.debuginfo.com)
//
//


///////////////////////////////////////////////////////////////////////////////
// Include files
//

#include <stdafx.h>

#include <windows.h>
#include <tchar.h>
#include <dbghelp.h>
#include <crtdbg.h>

#include <stdio.h>


///////////////////////////////////////////////////////////////////////////////
// Directives
//

#pragma comment(lib, "dbghelp.lib")


///////////////////////////////////////////////////////////////////////////////
// Stream identifiers
//

// Stream identifiers
// (LastReservedStream constant is defined in MINIDUMP_STREAM_TYPE
// enumeration in DbgHelp.h; all user data stream identifiers
// must be larger than LastReservedStream)
const ULONG32 cUserStreamID = LastReservedStream + 1;


///////////////////////////////////////////////////////////////////////////////
// main() function 
//

int _tmain(int argc, TCHAR* argv[])
{
	// Check parameters

	if (argc < 2) {
		_tprintf(_T("Usage: ExtractCrashDumpXML <MiniDumpFile>\n"));
		_tprintf(_T("\tThe output is the user XML stream in the MiniDump file\n"));
		_tprintf(_T("\twith the same name as the minidump but with xml extension\n"));
		return 0;
	}

	const TCHAR* pMiniDumpFileName = argv[1];
	_tprintf(_T("Minidump: %s\n"), pMiniDumpFileName);

	TCHAR pCrashDumpXMLName[MAX_PATH + 1];
	_tcscpy(pCrashDumpXMLName, pMiniDumpFileName);
	PTSTR p = _tcsrchr(pCrashDumpXMLName, _T('.'));
	if (p) {
		p++;
		if (_tcslen(p) >= 3)
			_tcscpy(p, _T("xml"));
	}
	_tprintf(_T("XML dump: %s\n"), pCrashDumpXMLName);

	// Read the user data streams and display their contents

	HANDLE hMiniDumpFile = NULL;
	HANDLE hMapFile = NULL;
	PVOID pViewOfFile = NULL;
	HANDLE hXMLDumpFile = NULL;

	hXMLDumpFile = CreateFile(pCrashDumpXMLName, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, NULL);
	if ((hXMLDumpFile == NULL) || (hXMLDumpFile == INVALID_HANDLE_VALUE)) {
		_tprintf(_T("Error: CreateFile failed. Error: %lu \n"), GetLastError());
		return -1;
	}

	// Map the minidump into memory

	hMiniDumpFile = CreateFile(pMiniDumpFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	if ((hMiniDumpFile == NULL) || (hMiniDumpFile == INVALID_HANDLE_VALUE)) {
		_tprintf(_T("Error: CreateFile failed. Error: %lu\n"), GetLastError());
		return -1;
	}

	hMapFile = CreateFileMapping(hMiniDumpFile, NULL, PAGE_READONLY, 0, 0, NULL);

	if (hMapFile == NULL) {
		_tprintf(_T("Error: CreateFileMapping failed. Error: %lu\n"), GetLastError());
		return -1;
	}

	pViewOfFile = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);

	if(pViewOfFile == NULL) {
		_tprintf(_T("Error: MapViewOfFile failed. Error: %lu\n"), GetLastError());
		return -1;
	}

	// Show the contents of user data stream

	ULONG StreamID = cUserStreamID;

	PMINIDUMP_DIRECTORY	pMiniDumpDir	= 0;
	PVOID				pStream			= 0;
	ULONG				StreamSize		= 0;

	if (!MiniDumpReadDumpStream(pViewOfFile, StreamID, &pMiniDumpDir, &pStream, &StreamSize)) {
		DWORD ErrCode = GetLastError();
		if (ErrCode != 0)	// 0 -> no such stream in the dump 
			_tprintf(_T("Error: MiniDumpReadDumpStream failed. Error: %lu \n"), ErrCode);
		else
			_tprintf(_T("Stream (id %lu) not found in the minidump.\n"), StreamID);
	} else {
		// Show the contents

		if ((pStream == 0) || (StreamSize == 0)) {
			_tprintf(_T("Invalid stream (id %lu).\n"), StreamID);
		} else if (IsBadStringPtrA((LPCSTR)pStream, StreamSize)) {
			_tprintf(_T("Invalid stream data (id %lu).\n"), StreamID);
		} else {
			DWORD bytesWritten;
			WriteFile(hXMLDumpFile, pStream, StreamSize, &bytesWritten, NULL);

			CloseHandle(hXMLDumpFile);

			if (bytesWritten < StreamSize)
				_tprintf(_T("Less data written: %lu < %lu.\n"), bytesWritten, StreamSize);
		}
	}

	// Cleanup

	if (hMapFile != NULL)
		CloseHandle(hMapFile);

	if (hMiniDumpFile != NULL)
		CloseHandle(hMiniDumpFile);

	// Complete

	return 0;
}

