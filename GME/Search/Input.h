// Input.h: interface for the CInput class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_INPUT_H
#define AFX_INPUT_H

//#include "RegExp.h"
#include <vector>
#include "attribute.h"
#include <regex>
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using namespace std::tr1;

/** \brief Stores Input
*
* The CInput class holds validated input to pass from
* CGMESearchDialog to CSearch
*/
class CInput  
{
protected:
    void ParseAttribute();
    void PrepareExpressionStack(const CString & strAttributeExpression, std::vector<Attribute> &stack);
    regex GetRegExp(CString name);
public:
	CInput();
	virtual ~CInput();

	void CInput::GetInput(CString strNameFirst, CString strRoleFirst, CString strKindFirst, CString strAttributeFirst,CString strNameSecond,CString strRoleSecond,CString strKindSecond,CString strAttributeSecond,
                      CString attrval, BOOL mod, BOOL atom, BOOL ref, BOOL set, BOOL full, 
                      IMgaFCO*, int, //WAS: IMgaFCO *root, int searchscope,
                      BOOL bMatchCase, int scopedSearch,int logicalExpr);

    //Getter methods
    regex &GetFirstNameRegExp() {return m_regNameFirst;}
    regex &GetFirstRoleRegExp() {return m_regRoleFirst;}
    regex &GetFirstKindRegExp() {return m_regKindFirst;}
    regex &GetFirstAttributeRegExp() {return m_regAttributeFirst;}

    regex &GetSecondNameRegExp() {return m_regNameSecond;}
    regex &GetSecondRoleRegExp() {return m_regRoleSecond;}
    regex &GetSecondKindRegExp() {return m_regKindSecond;}
    regex &GetSecondAttributeRegExp() {return m_regAttributeSecond;}

    //getter methods string forms
    CString &GetFirstName() {return m_strNameFirst;}
    CString &GetFirstRole() {return m_strRoleFirst;}
    CString &GetFirstKind() {return m_strKindFirst;}
    CString &GetFirstAttribute() {return m_strAttributeFirst;}

    CString &GetSecondName() {return m_strNameSecond;}
    CString &GetSecondKind() {return m_strKindSecond;}
    CString &GetSecondRole() {return m_strRoleSecond;}
    CString &GetSecondAttribute() {return m_strAttributeSecond;}

    //other
    BOOL &GetModels() {return m_bGetModels;}
    BOOL &GetAtoms() {return m_bGetAtoms;}
    BOOL &GetSets() {return m_bGetSets;}
    BOOL &GetReferences() {return m_bGetReferences;}
    BOOL &IsCaseIgnored() {return m_bGetCaseIgnored;}
    BOOL &DoScopedSearch() {return m_bDoScopedSearch;}
    int &GetSearchScope(){return m_intScope;}
    int &GetLogicalOperator() {return m_intLogical;}
    BOOL &UseSecondCriteria() {return m_bDoSecond;}
    BOOL &MatchWholeWord() {return m_bFull;}

    std::vector<Attribute>& GetFirstAttributeStack(){return  m_stackExpressionFirst;}
    std::vector<Attribute>& GetSecondAttributeStack() {return m_stackExpressionSecond;}

private:
	/// The name of the object the user is searching for.
    regex m_regNameFirst;
	/// The role of the object the user is searching for.
	regex m_regRoleFirst;
	/// The kind of object the user is searching for.
	regex m_regKindFirst;
	/// The name of the attribute the user wants to search for.
	regex m_regAttributeFirst;
	/// The type of attribute the user wants to search for.
	//attval_enum getAttrType;
	/// The value of the attribute the user wants to search for.
    regex m_regNameSecond;
    regex m_regRoleSecond;
    regex m_regKindSecond;
    regex m_regAttributeSecond;
   
	//String forms of input
    CString m_strNameFirst;
    CString m_strRoleFirst;
    CString m_strKindFirst;
    CString m_strAttributeFirst;
    CString m_strNameSecond;
    CString m_strRoleSecond;
    CString m_strKindSecond;
	CString m_strAttributeSecond;
	

	/// Does the user want to do a special reference search?
	BOOL m_bGetSplSearch;

	/// Does the user want to search for Models?
	BOOL m_bGetModels;
	/// Does the user want to search for Atoms?
	BOOL m_bGetAtoms;
	/// Does the user want to search for References?
	BOOL m_bGetReferences;
	/// Does the user want to search for Sets?
	BOOL m_bGetSets;

    /// Does the user want caseMatching search
	BOOL m_bGetCaseIgnored;

	/// Is the search restricted to a scope?
	BOOL m_bDoScopedSearch;
  
    int m_intScope;
    int m_intLogical;
   // attval_enum getAttrType2;
    
    //matches whole word
    BOOL m_bFull;

    //if second criteria needs to be processed
    BOOL m_bDoSecond;

  
    std::vector<Attribute> m_stackExpressionFirst;
    std::vector<Attribute> m_stackExpressionSecond;
};

#endif 
