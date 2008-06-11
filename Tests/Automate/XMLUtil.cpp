#include "StdAfx.h"
#include "Automate.h"

void  MyParser::fatalError (const SAXParseException& exception)
	{
		char buffer[34];

		CString description = "Error at file '";
		description += exception.getSystemId();

		description += "', line ";
		_itoa(exception.getLineNumber(), buffer, 10);
		description += buffer;

		description += ", column ";
		_itoa(exception.getColumnNumber(), buffer, 10);
		description += buffer;

		description += ". Message: ";
		description += exception.getMessage();

		throw AutoErr(description);
}



InputSource* MyParser::resolveEntity(const   XMLCh* const    publicId, const XMLCh* const systemId) {

	CString sysid = systemId;
	HRSRC res = FindResource(NULL, sysid, "DTD");
	if(res) {
		XMLByte *bytes = (XMLByte *)LockResource(LoadResource(NULL, res));
		if(!bytes) throw AutoErr("Error loading resource"); 
		return new MemBufInputSource(bytes, SizeofResource(NULL, res), sysid);
	}
	CString filename;
	if(GetFileAttributes(sysid) != DWORD(-1L)) {
		filename = sysid;
	}
	else if(sysid.Find(":\\") == -1) {   // if it is a name without path
		char buf[200];
		GetModuleFileName(NULL, buf, DIM(buf));
		*strrchr(buf,'\\') = '\0';
		CString p(buf + CString("\\") + sysid);
		if(GetFileAttributes(p) != DWORD(-1L)) filename = p;	// look for file in the executable's path
		else {
			char *k;			
			while(filename.IsEmpty() && (k = strrchr(buf,'\\'))) {
				*k = '\0';
				CString p(buf + CString("\\doc\\") + sysid);		// or in ../doc	relative to the executable	
				if(GetFileAttributes(p) != DWORD(-1L)) filename = p;
				else {
					CString p(buf + CString("\\documents\\") + sysid);
					if(GetFileAttributes(p) != DWORD(-1L)) filename = p;  // or in ../documents relative to the executable
				}
			}
		}			
	}

	if(!filename.IsEmpty()) {
		return new LocalFileInputSource(DOMString(filename).rawBuffer());
	}
	else return HandlerBase().resolveEntity(publicId, systemId);
};

