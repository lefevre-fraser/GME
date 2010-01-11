// XMETidy.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "XMETidy.h"

// Global Variables:
HINSTANCE hInst;								// current instance


// Forward declarations of functions included in this code module:
INT_PTR CALLBACK	DialogProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

 	hInst = hInstance;
	HACCEL hAccelTable;
	hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDC_XMETIDY));

	return (int) DialogBox(hInst, MAKEINTRESOURCE(IDD), NULL, DialogProc );
}



INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
