#include "StdAfx.h"

#pragma warning( push )
#pragma warning( disable : 4100 )
#include <sax\EntityResolver.hpp>
#include <dom/DOM_Document.hpp>
#include <dom/DOM_Element.hpp>
#include <util/XMLString.hpp>
#include <util/PlatformUtils.hpp>
#include <parsers/DOMParser.hpp>
#include <sax/ErrorHandler.hpp>
#include <sax/SAXParseException.hpp>
#include <framework\LocalFileInputSource.hpp>
#include <framework\MemBufInputSource.hpp>
#include <sax\HandlerBase.hpp>
#include <parsers\SAXParser.hpp>
#pragma warning(pop)


#define DIM(x) (sizeof(x) / sizeof((x)[0]))




class AutoErr {
public:
	CString msg;
	AutoErr(const CString m) : msg(m) { ; };
	AutoErr(const LPSTR m) : msg(m) { ; };
};


CString GetClassName(CWnd *w);

class Animator {
	PROCESS_INFORMATION pi;
	CString mainwindowclass, dialogname;
public:
	Animator();
	~Animator();
	bool Running();
//	void StartApp(const char *cmdline);
	void Attach(DWORD thread) {
		pi.dwThreadId = thread;
		pi.hProcess = GetCurrentProcess();
		mainwindowclass = GetClassName(WaitForWindowActive(NULL, NULL));
	}
	void Detach() {
		pi.hProcess = NULL;
	}
	CWnd *WaitForWindowActive(const char *classname, const char *wndname, 
						  long timeout = 10000);

	void SelectMenuCmd(CString select);
//	static VOID TerminateCallback(PVOID, BOOLEAN);

	void SetDialogCaption(const CString c) { dialogname = c;}
	void SetEdit(const CString caption, const CString newval);
	void SetList(const CString caption, const CString selectval);
	void DoButton(const CString caption, const int check);
};


// XML UTILITIES


class MyParser : public HandlerBase
{
	Animator &anim;
public:
	MyParser(Animator &a);

private:
	typedef struct funs {
		funs(const char *n, void (MyParser::*f)(const AttributeList &), void (MyParser::*ef)()) 
			: name(n), fun(f), end_fun(ef) { ; }		
		CString name; 
		void (MyParser::*fun)(const AttributeList &);
		void (MyParser::*end_fun)(void);
	};

	funs *selectfun(const CString name);
//
	void Test(const AttributeList &);	
	void End_Test();

	void Menu(const AttributeList &);	
	void Wait(const AttributeList &);	
	void Dialog(const AttributeList &);	
	void End_Dialog();	
	void Edit(const AttributeList &);	
	void List(const AttributeList &);	
	void Button(const AttributeList &);	
// documenthandler
	virtual void startElement(const   XMLCh* const    name, AttributeList&  attrs);
    virtual void endElement(const XMLCh* const name);
    virtual void endDocument();

// errorhandler
public:
	virtual void  warning (const SAXParseException&) { }
	virtual void  error (const SAXParseException& exception) { fatalError(exception); }

	virtual void  fatalError (const SAXParseException& exception);
	virtual void  resetErrors () { }
// entityresolver
public:
  virtual InputSource* resolveEntity(const   XMLCh* const    publicId, const XMLCh* const systemId);
};

