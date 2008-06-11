// Input.cpp: implementation of the CInput class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "ComHelp.h"
//#include "GMECOM.h"
//#include "ComponentConfig.h"
//#include "RawComponent.h"
#include "Input.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInput::CInput()
{
	
}

CInput::~CInput()
{

}

void CInput::GetInput(CString name, CString role, CString kind, CString attrname, int attrtype, 
					  CString attrval, BOOL spl, BOOL mod, BOOL atom, BOOL ref, BOOL set, BOOL full, 
					  IMgaFCO*, int, //WAS: IMgaFCO *root, int searchscope,
					  BOOL bMatchCase, BOOL bScopedSearch)
{
	doScopedSearch = bScopedSearch;

	getCaseIgnored = !bMatchCase;
	if( getCaseIgnored)
	{
		name.MakeLower();
		role.MakeLower();
		kind.MakeLower();
		attrname.MakeLower();
		attrval.MakeLower();
	}

	if (full)
	{
		CString temp("");
		
		if (!name.IsEmpty())
		{
			//AfxMessageBox(name);
			temp = "^";
			temp += name;
			temp += "$";
			objName = CRegExp(temp);
			temp = "";
		}
		else
			objName = CRegExp(name);

		if (!role.IsEmpty())
		{
			//AfxMessageBox(role);
			temp = "^";
			temp += role;
			temp += "$";
			objRole = CRegExp(temp);
			temp = "";
		}
		else
			objRole = CRegExp(role);

		if (!kind.IsEmpty())
		{
			//AfxMessageBox(kind);
			temp = "^";
			temp += kind;
			temp += "$";
			objKind = CRegExp(temp);
			temp = "";
		}
		else
			objKind = CRegExp(kind);

		if (!attrname.IsEmpty())
		{
			//AfxMessageBox(attrname);
			temp = "^";
			temp += attrname;
			temp += "$";
			objAttrName = CRegExp(temp);
			temp = "";
		}
		else
			objAttrName = CRegExp(attrname);

		if (!attrval.IsEmpty())
		{
			//AfxMessageBox(attrval);
			temp = "^";
			temp += attrval;
			temp += "$";
			objAttrVal = CRegExp(temp);
			temp = "";
		}
		else
			objAttrVal = CRegExp(attrval);
	}
	else
	{
		objName = CRegExp(name);
		objRole = CRegExp(role);
		objKind = CRegExp(kind);
		objAttrName = CRegExp(attrname);
		objAttrVal = CRegExp(attrval);
	}
	objVal = attrval;
	objattribName = attrname;

	switch(attrtype)
	{
		case 0: getAttrType = ATTVAL_STRING;	break;
		case 1: getAttrType = ATTVAL_INTEGER;	break;
		case 2: getAttrType = ATTVAL_DOUBLE;	break;
		case 3: getAttrType = ATTVAL_BOOLEAN;	break;
		case 4: getAttrType = ATTVAL_REFERENCE;	break;
		default: getAttrType = ATTVAL_STRING;		break;
	}

	getSplSearch = spl;

	getModels = mod;
	getAtoms = atom;
	getReferences = ref;
	getSets = set;

//	searchroot = root;// looks obsolete to me, replaced by doScopedSearch [zolmol]

//	doReferenceSearch = searchtype;
//	doGlobalSearch = searchscope; // looks obsolete to me, replaced by doScopedSearch [zolmol]

}