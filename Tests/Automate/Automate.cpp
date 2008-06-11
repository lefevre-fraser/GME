#include "StdAfx.h"
#include "Automate.h"

MyParser::MyParser(Animator &a) : anim(a) {
};


MyParser::funs *MyParser::selectfun(const CString token) {
	static MyParser::funs funswitch[] = {
		funs("test", Test, End_Test),
		funs("mainmenu", Menu, NULL),
		funs("dialog", Dialog, End_Dialog),
		funs("list", List, NULL),
		funs("edit", Edit, NULL),
		funs("button", Button, NULL),
		funs("wait", Wait, NULL),
	};
	for(int i = 0; i != DIM(funswitch); i++) {
		if(funswitch[i].name == token) {
			return funswitch+i;
		}
	}
	throw AutoErr("No handler for XML token: " + token);
}


void MyParser::Test(const AttributeList &) {
//	anim.StartApp(CString(a.getValue("startapp")));
	;	
}

void MyParser::End_Test() {
	
}

void MyParser::Menu(const AttributeList &a) {
	anim.SelectMenuCmd(a.getValue("cmd"));
}


void MyParser::Dialog(const AttributeList &a) {
	anim.SetDialogCaption(a.getValue("caption"));
}

void MyParser::End_Dialog() {
	anim.SetDialogCaption("");
}

void MyParser::Edit(const AttributeList &a) {
	anim.SetEdit(a.getValue("caption"), a.getValue("setvalue"));
}

void MyParser::List(const AttributeList &a) {
	anim.SetList(a.getValue("caption"), a.getValue("select"));
}

void MyParser::Button(const AttributeList &a) {
	CString mode = a.getValue("setcheck");
	anim.DoButton(a.getValue("caption"), mode.CompareNoCase("uncheck") ? 1 : 0);
}

void MyParser::Wait(const AttributeList &a) {
	CString attr = a.getValue("millisecs");
	DWORD millis;
	if(!sscanf(attr, "%lu", &millis)) throw AutoErr("Invalid number format"); 
	Sleep(millis);
}


void MyParser::startElement(const   XMLCh* const    name, AttributeList&  attrs) {
#ifdef DEBUG

static CString log;
log += CString(name) + "\n";

#endif
	funs *f=selectfun(name);
	if(f->fun) (this->*(f->fun))(attrs);
}


void MyParser::endElement(const XMLCh* const name) {
	funs *f=selectfun(name);
	if(f->end_fun) (this->*(f->end_fun))();
}

void MyParser::endDocument() { 
}


struct pars {
	pars(HWND h, CString &s) : hwnd(h), file(s) {;};
	HWND hwnd;
	CString file;
};

DWORD WINAPI AutomateThread(LPVOID v) {
	Animator anim;
	
	anim.Attach(GetWindowThreadProcessId(((struct pars *)v)->hwnd, NULL));
	try {
		XMLPlatformUtils::Initialize();
		SAXParser parser;
		MyParser handler(anim);

		parser.setDoValidation(true);
		parser.setDocumentHandler(&handler);
		parser.setErrorHandler(&handler);
		parser.setEntityResolver(&handler);

		parser.parse(((struct pars *)v)->file);
	} 
	catch(AutoErr &e) {
		AfxMessageBox(e.msg);
		return 0xFFFFFFFF;
	}
	catch(...) {
		AfxMessageBox("Unknown exception");
		return 0xFFFFFFFF;
	}

	delete (struct pars *)v;
	return 0;
}

void Automate(CWnd *w, CString file) {
	if(!CreateThread(NULL, 10000, AutomateThread, 
		new pars(w->m_hWnd, file), NULL, NULL)) {
		AfxMessageBox("Cannot start thread");
	}
}


#ifdef AUTOMATE_STANDALONE 

int main(int argc, char **argv) {
	Animator anim;
	if(argc != 2) {
		AfxMessageBox("Usage: Automate  <testscript.xml>");
		return 1;
	}

	try {
		if(!SetProcessPriorityBoost(GetCurrentProcess(), TRUE) ||
			!SetThreadPriorityBoost(GetCurrentThread(), TRUE) ||
			!SetPriorityClass(GetCurrentProcess(), IDLE_PRIORITY_CLASS) ||
			!SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_IDLE) ) {
			throw AutoErr("Cannot lower process priority");
		}

		XMLPlatformUtils::Initialize();
		SAXParser parser;
		MyParser handler(anim);

		parser.setDoValidation(true);
		parser.setDocumentHandler(&handler);
		parser.setErrorHandler(&handler);
		parser.setEntityResolver(&handler);

		parser.parse(argv[1]);
	} 
	catch(AutoErr &e) {
		AfxMessageBox(e.msg);
		return -1;
	}
	catch(...) {
		AfxMessageBox("Unknown exception");
		return 0;
	}

	if(anim.Running()) {
		AfxMessageBox("The application has not terminated");
	}
	return 0;
}

#endif
