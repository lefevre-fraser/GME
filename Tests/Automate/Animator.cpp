#include "StdAfx.h"
#include "Automate.h"

#define DIALOGCLASS "#32770"

CString GetClassName(CWnd *w) {
		static char buf[100];
// INFO: Built in windows classnames (from MSDN)
// ----------------------------------------------
//#32768 The class for a menu. 
//#32769 The class for the desktop window. 
//#32770 The class for a dialog box. 
//#32771 The class for the task switch window. 
//#32772 Windows NT/2000/XP: The class for icon titles. 
//Button	The class for a button. 
//ComboBox	The class for a combo box. 
//Edit		The class for an edit control. 
//ListBox	The class for a list box. 
//MDIClient The class for an MDI client window. 
//ScrollBar The class for a scroll bar. 
//Static	The class for a static control. 
// others: msctls_hotkey32, msctls_progress32, msctls_statusbar32, msctls_trackbar32, 
// msctls_updown32, SysAnimate32, SysHeader32, 
// SysListView32, SysTabControl32, or SysTreeView32.

		GetClassName(w->m_hWnd, buf, sizeof(buf));		 
		return buf;
}

CString GetCaption(CWnd *w) {
			CString caption;
			w->GetWindowText(caption);
			caption.Replace("&","");
			return caption;
}

// return true if match
bool CheckClassName(CWnd *w, CString expected) {
	return !expected.Compare(GetClassName(w));
}

// return true if match
bool CheckCaption(CWnd *w, CString expected) {
	if(!w->IsWindowEnabled()) return false;
	return !strnicmp(GetCaption(w), expected, expected.GetLength());
}




UINT SelectMenuCmd(CMenu *menu, CString select) {
		CString rest;
		int k = select.Find('/');
		if(k > 0) {
			rest = select.Mid(k+1);
			select = select.Left(k);
		}
		if(k == 0) throw AutoErr("Invalid select attr for menucmd");
		for(UINT i = 0; i < menu->GetMenuItemCount(); i++) {
			CString caption;
			menu->GetMenuString(i,caption,MF_BYPOSITION);
			caption.Replace("&","");
			if(strnicmp(caption, select,select.GetLength()) == 0) {
				UINT n = menu->GetMenuItemID(i);
				if(n == UINT(-1)) {
					if(rest.IsEmpty()) throw AutoErr("Invalid item specified by select attr");
					return SelectMenuCmd(menu->GetSubMenu(i), rest);
				}
				else {
					if(!rest.IsEmpty()) throw AutoErr("Invalid item specified by select attr");
					return n;
				}
			}
		}
		throw AutoErr("Invalid item specified by select attr");
}


void Animator::SelectMenuCmd(CString select) {
			CWnd *w = WaitForWindowActive(mainwindowclass,NULL);
			w->PostMessage(WM_COMMAND, ::SelectMenuCmd(w->GetMenu(),select), NULL);
}



Animator::Animator() { 
	pi.hProcess = NULL;
}

Animator::~Animator() { 
	if(Running()) {
//		TerminateProcess(pi.hProcess, -1);
		pi.hProcess = NULL;
	}
}





#ifdef AUTOMATE_STANDALONE 

void Animator::StartApp(const char *cmdline) {
	SID_IDENTIFIER_AUTHORITY SIDAuthWorld = SECURITY_WORLD_SID_AUTHORITY;
	PSID pEveryoneSID = NULL;

// Create a well-known SID for the Everyone group.
	
	if(! AllocateAndInitializeSid( &SIDAuthWorld, 1,
                 SECURITY_WORLD_RID,
                 0, 0, 0, 0, 0, 0, 0,
                 &pEveryoneSID) ) {
		printf( "AllocateAndInitializeSid Error %u\n", GetLastError() );
		throw AutoErr("Sec");
	}

// Initialize an EXPLICIT_ACCESS structure for an ACE.
// The ACE will allow Everyone read access to the key.

	EXPLICIT_ACCESS ea_t, ea_p;

	ZeroMemory(&ea_t, sizeof(EXPLICIT_ACCESS));
	ea_t.grfAccessPermissions = THREAD_ALL_ACCESS | 0xF000FFFF;
	ea_t.grfAccessMode = SET_ACCESS;
	ea_t.grfInheritance= SUB_CONTAINERS_AND_OBJECTS_INHERIT;
	ea_t.Trustee.TrusteeForm = TRUSTEE_IS_SID;
	ea_t.Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
	ea_t.Trustee.ptstrName  = (LPTSTR) pEveryoneSID;


	ZeroMemory(&ea_p, sizeof(EXPLICIT_ACCESS));
	ea_p.grfAccessPermissions = PROCESS_ALL_ACCESS | 0xF000FFFF;
	ea_p.grfAccessMode = SET_ACCESS;
	ea_p.grfInheritance= SUB_CONTAINERS_AND_OBJECTS_INHERIT;
	ea_p.Trustee.TrusteeForm = TRUSTEE_IS_SID;
	ea_p.Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
	ea_p.Trustee.ptstrName  = (LPTSTR) pEveryoneSID;


	PACL pACL_t = NULL, pACL_p = NULL;
// Create a new ACL that contains the new ACEs.

	DWORD dwRes = SetEntriesInAcl(1, &ea_t, NULL, &pACL_t);
	if (ERROR_SUCCESS != dwRes) {
		printf( "SetEntriesInAcl Error %u\n", GetLastError() );
		throw AutoErr("Sec");
	}

	dwRes = SetEntriesInAcl(1, &ea_p, NULL, &pACL_p);
	if (ERROR_SUCCESS != dwRes) {
		printf( "SetEntriesInAcl Error %u\n", GetLastError() );
		throw AutoErr("Sec");
	}

// Initialize a security descriptor.  
	PSECURITY_DESCRIPTOR pSD_t, pSD_p;
 
	pSD_t = (PSECURITY_DESCRIPTOR) LocalAlloc(LPTR, 
                         SECURITY_DESCRIPTOR_MIN_LENGTH); 
	pSD_p = (PSECURITY_DESCRIPTOR) LocalAlloc(LPTR, 
                         SECURITY_DESCRIPTOR_MIN_LENGTH); 
	if (pSD_t == NULL || pSD_p == NULL) { 
	    printf( "LocalAlloc Error %u\n", GetLastError() );
		throw AutoErr("Sec");
	} 
 
	if (!InitializeSecurityDescriptor(pSD_t, SECURITY_DESCRIPTOR_REVISION) || 
		!InitializeSecurityDescriptor(pSD_p, SECURITY_DESCRIPTOR_REVISION) ) {  
		 printf( "InitializeSecurityDescriptor Error %u\n", 
			                    GetLastError() );
		throw AutoErr("Sec");
	} 
 
// Add the ACL to the security descriptor. 
 
	if (!SetSecurityDescriptorDacl(pSD_t, TRUE, pACL_t, FALSE) ||
		!SetSecurityDescriptorDacl(pSD_p, TRUE, pACL_p, FALSE) ) 
	{  
		printf( "SetSecurityDescriptorDacl Error %u\n", GetLastError() );
		throw AutoErr("Sec");
	} 

// Initialize a security attributes structure.

	SECURITY_ATTRIBUTES sa_t, sa_p;

	sa_t.nLength = sizeof (SECURITY_ATTRIBUTES);
	sa_t.lpSecurityDescriptor = pSD_t;
	sa_t.bInheritHandle = FALSE;

	sa_p.nLength = sizeof (SECURITY_ATTRIBUTES);
	sa_p.lpSecurityDescriptor = pSD_p;
	sa_p.bInheritHandle = FALSE;

	STARTUPINFO si = {
		sizeof(STARTUPINFO),
		NULL,
		"Default",
		NULL,
		0, 0, 0, 0, 
		0, 0, 0, 
		NORMAL_PRIORITY_CLASS,   // flag
		0,   // show window
		0,
		NULL,
		NULL, NULL, NULL};



	if(!CreateProcess("c:\\GME\\GME\\Debug\\GME.exe", NULL, &sa_p, &sa_t, 
						FALSE, 0, 
						NULL, NULL, &si, &pi)) {
		throw AutoErr("Cannot start process");
	}
	mainwindowclass = GetClassName(WaitForWindowActive(NULL, NULL));
/*
	HANDLE ww;
	if(!RegisterWaitForSingleObject(&ww, pi.hProcess, Animator::TerminateCallBack, this, INFINITE,
								WT_EXECUTEDEFAULT | WT_EXECUTEONLYONCE) {
		AfxMessageBox("Could not register process callback");
	}
*/

    if (pEveryoneSID) 
        FreeSid(pEveryoneSID);
    if (pACL_t) 
        LocalFree(pACL_t);
    if (pSD_t) 
        LocalFree(pSD_t);

    if (pACL_p) 
        LocalFree(pACL_p);
    if (pSD_p) 
        LocalFree(pSD_p);



}

VOID Animator::TerminateCallback(PVOID hh, BOOLEAN) {
	Animator *thiss = (Animator *)hh;
	thiss->pi.hProcess = NULL;
	AfxMessageBox("Process termninated");
}

#endif

bool Animator::Running() {
	return pi.hProcess != NULL;
}	


CWnd *Animator::WaitForWindowActive(const char *classname, const char *wndname, long timeout) {
	int k = 0;
#ifdef DEBUG
	CString mm, mmc;
#endif
 while(true) { 
  try {
	Sleep(200);
	if(WaitForInputIdle(pi.hProcess, timeout)) {
		throw AutoErr("WaitForWindowActive timeout");
	}
#ifdef AUTOMATE_STANDALONE 
	GUITHREADINFO guii = { sizeof(GUITHREADINFO) };
	if(!GetGUIThreadInfo(pi.dwThreadId, &guii)) {
		throw AutoErr("GetGUIThreadInfo err");
	}
HWND h1 = guii.hwndActive;
#else
	struct {
		HWND hwndActive;
	} guii; 
	if(!AttachThreadInput(GetCurrentThreadId(),
			pi.dwThreadId, true)) {
				throw AutoErr("Cannot attach");
	}
	guii.hwndActive = ::GetActiveWindow();
	if(!AttachThreadInput(GetCurrentThreadId(),
			pi.dwThreadId, false)) {
				throw AutoErr("Cannot attach");
	}
#endif

	if(!IsWindow(guii.hwndActive)) {
		throw AutoErr("Bad window reported active");
	}
	CWnd *w = CWnd::FromHandle(guii.hwndActive);
#ifdef DEBUG
    mm = GetCaption(w);
	mmc = GetClassName(w);
#endif
	if( classname && !CheckClassName(w, classname) ) {
		throw AutoErr("Window class mismatch");
	}	
	if( wndname && !CheckCaption(w, wndname) ) {
		throw AutoErr("Window caption mismatch: " + GetCaption(w) + " != " + CString(wndname));
	}	
	return w;
  } catch(AutoErr &) {
	  if(k++ >= 50) {
	      Sleep(5000);
		  throw;
	  }	
  }	
 }
}



void Animator::SetList(const CString id, const CString value) {
	CWnd *dialog = WaitForWindowActive(DIALOGCLASS, dialogname);

CString aa = GetCaption(dialog);

	for(CWnd *child = dialog->GetWindow(GW_CHILD); child; child = child->GetWindow(GW_HWNDNEXT)) {
// the following code line does not work (probably by MFC design)
//		if(child->IsKindOf(RUNTIME_CLASS(CListCtrl))) {
// I use the following hack instead (semi-documented in MSDN)
		if(CheckClassName(child, "SysListView32")) {  // this indicates listview controls
			if(!id.IsEmpty()) {
				// TODO compare ID spec....
			}
// We hope that this conversion happens without problem....
// It should be OK, as long as CListCtrl does not have significant data members.
			CListCtrl *list = (CListCtrl *)child;
			for(int i = 0; i < list->GetItemCount(); i++) {
				if(!strnicmp(list->GetItemText(i,0), value, value.GetLength())) {
					list->SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
					return;
				}
			}
		}
	}
	throw AutoErr("Item not found in list");
}	

void Animator::SetEdit(const CString id, const CString value) {
	CWnd *dialog = WaitForWindowActive(DIALOGCLASS, dialogname);

	for(CWnd *child = dialog->GetWindow(GW_CHILD); child; child = child->GetWindow(GW_HWNDNEXT)) {
// the following code line does not work (probably by MFC design)
//		if(child->IsKindOf(RUNTIME_CLASS(CListCtrl))) {
// I use the following hack instead (semi-documented in MSDN)
		if(CheckClassName(child, "Edit")) {  // this indicates listview controls
			if(!id.IsEmpty()) {
				// TODO compare ID spec....
			}
// We hope that this conversion happens without problem....
// It should be OK, as long as CEditCtrl does not have significant data members.
			if(!::SetWindowText(child->m_hWnd, value)) {
				throw AutoErr("Could not set edit control");
			}
//			child->RedrawWindow();
			CString tests;
			child->GetWindowText(tests);
			if(value.Compare(tests)) {
				throw AutoErr("Could not set edit control");
			}
			return;
		}
	}
	throw AutoErr("Edit control not found");
}	

void Animator::DoButton(const CString searchcaption, const int check = 1) {
	CWnd *dialog = WaitForWindowActive(DIALOGCLASS, dialogname);

CString s1 = GetCaption(dialog);
	for(CWnd *child = dialog->GetWindow(GW_CHILD); child; child = child->GetWindow(GW_HWNDNEXT)) {
// the following code line does not work (probably by MFC design)
//		if(child->IsKindOf(RUNTIME_CLASS(CListCtrl))) {
// I use the following hack instead (semi-documented in MSDN)
CString s1 = GetCaption(child);
		if(CheckClassName(child, "Button")) {  // this indicates Button windows
			if(CheckCaption(child, searchcaption)) {
// for Radio buttons ONLY
// clear radio buttons in the same group
				if(child->SendMessage(WM_GETDLGCODE, 0, NULL) & DLGC_RADIOBUTTON) {
					CWnd *sib = child;
					while(!(sib->GetStyle() & WS_GROUP)) {
						sib = sib->GetWindow(GW_HWNDPREV);
					}	
					do {
						if(sib->SendMessage(WM_GETDLGCODE, 0, NULL) & DLGC_RADIOBUTTON)  {
							((CButton *)sib)->SetCheck(0);
						}
						sib = sib->GetWindow(GW_HWNDNEXT);
					} while(sib && !(sib->GetStyle() & WS_GROUP));
				}
				((CButton *)child)->SetCheck(check);

// This is where a pushbutton is operated
				dialog->PostMessage(WM_COMMAND, child->GetDlgCtrlID(), (long)child->m_hWnd);
				return;
			}
		}
	}
	throw AutoErr("Button not found");
}	

