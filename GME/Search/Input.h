// Input.h: interface for the CInput class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_INPUT_H
#define AFX_INPUT_H

#include "RegExp.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/** \brief Stores Input
*
* The CInput class holds validated input to pass from
* CGMESearchDialog to CSearch
*/
class CInput  
{
public:
	CInput();
	virtual ~CInput();

	void GetInput(CString name, CString role, CString kind, CString attrname, int attrtype,
				CString attrval, BOOL spl, BOOL mod, BOOL atom, BOOL ref, BOOL set, BOOL full, 
				 IMgaFCO *root, int searchscope, BOOL caseMatch, BOOL bScopedSearch);

	/// The name of the object the user is searching for.
	CRegExp objName;
	/// The role of the object the user is searching for.
	CRegExp objRole;
	/// The kind of object the user is searching for.
	CRegExp objKind;
	/// The name of the attribute the user wants to search for.
	CRegExp objAttrName;
	/// The type of attribute the user wants to search for.
	attval_enum getAttrType;
	/// The value of the attribute the user wants to search for.
	CRegExp objAttrVal;
	CString objattribName;
	CString objVal;

	/// Does the user want to do a special reference search?
	BOOL getSplSearch;

	/// Does the user want to search for Models?
	BOOL getModels;
	/// Does the user want to search for Atoms?
	BOOL getAtoms;
	/// Does the user want to search for References?
	BOOL getReferences;
	/// Does the user want to search for Sets?
	BOOL getSets;

	/// Where to start the search from.
	//CComPtr<IMgaFCO> searchroot; // Looks Obsolete to me [Zolmol]

//	int doReferenceSearch;
	/// The variable used for determining the Search Type - Global(0) or Local(1)
	//int doGlobalSearch; // Looks Obsolete to me [Zolmol]

	/// Does the user want caseMatching search
	BOOL getCaseIgnored;

	/// Is the search restricted to a scope?
	BOOL doScopedSearch;
};

#endif 
