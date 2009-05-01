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
    or=TRUE;
}

CInput::~CInput()
{

}

//Get the search criterias
void CInput::GetInput(CString name, CString role, CString kind, CString attrname,CString name2,CString role2,CString kind2,CString attribute2,
                      CString attrval, BOOL mod, BOOL atom, BOOL ref, BOOL set, BOOL full, 
                      IMgaFCO*, int, //WAS: IMgaFCO *root, int searchscope,
                      BOOL bMatchCase, int scopedSearch,int logicalExpr)
{
    //doScopedSearch = bScopedSearch;

    getCaseIgnored = !bMatchCase;
    if( getCaseIgnored)
    {
        name.MakeLower();
        role.MakeLower();
        kind.MakeLower();
        attrname.MakeLower();
        attrval.MakeLower();
        //addded
        name2.MakeLower();
        role2.MakeLower();
        kind2.MakeLower();
        attribute2.MakeLower();
    }
    objAttrib2=attribute2;
    objattrib=attrname;
    this->full=full;

    objName=GetRegExp(name);
    objRole = GetRegExp(role);
    objKind = GetRegExp(kind);
    objAttrName = GetRegExp(attrname);

    objName2=GetRegExp(name2);
    objKind2=GetRegExp(kind2);
    objRole2=GetRegExp(role2);

    objVal = attrval;
    //objattribName = attrname;
    this->name=name;
    this->kind=kind;
    this->role=role;
    this->name2=name2;
    this->kind2=kind2;
    this->role2=role2;

    if(name2.Trim()=="" && kind2.Trim()==""&& role2.Trim()=="" && attribute2.Trim()=="")
    {
        doSecond=FALSE;
    }
    else doSecond=TRUE;
    //getSplSearch = spl;

    getModels = mod;
    getAtoms = atom;
    getReferences = ref;
    getSets = set;
    scope=scopedSearch;
    logical=logicalExpr;
    ParseAttribute();
}

//Parses attribute expressions and keeps it in stack
//Two stacks are used for both lhs and rhs search criteria
void CInput::ParseAttribute()
{
    //CString attrName=objAttrName.st

    if(getCaseIgnored)
    {
        objattrib.MakeLower();
        objAttrib2.MakeLower();
    }
    CString temp=objattrib;
    CString oper,temp2;

    //FInd individual parts of the attribute expression
    //and put it on the stack for Lhs search criteria
    //this keeps overall expression on the stack for eg if expression is 
    // a<b & b<c,  element is stack wiil be a<b, &, b<c
    //thus it will be divided into 3 elements
    int index= temp.FindOneOf("&|");
    if(index==-1 && temp!="")
        expr1.push_back(Attrib(temp.Trim()));

    int i=0;
    while(index!=-1)
    {
        oper=temp[index];
        AfxExtractSubString(temp2,temp,0,temp[index]);
        expr1.push_back(Attrib(temp2.Trim()));
        expr1.push_back(Attrib(CString(temp[index])));
        temp=temp.Right(temp.GetLength()-index-1);
        //i++;
        index= temp.FindOneOf("&|");
        if(index==-1) expr1.push_back(Attrib(temp.Trim()));
    }


     //FInd individual parts of the attribute expression
    //and put it on the stack for rhs search criteria
    i=0;
    temp=objAttrib2;
    index=temp.FindOneOf("&|");
    if(index==-1 && temp!="")
        expr2.push_back(Attrib(temp.Trim()));
    while(index!=-1)
    {
        AfxExtractSubString(temp2,temp,i,temp[index]);
        expr2.push_back(Attrib(temp2.Trim()));
        expr2.push_back(Attrib(CString(temp[index])));
        //i++;
        temp=temp.Right(temp.GetLength()-index-1);
        index= temp.FindOneOf("&|");
        if(index==-1) expr1.push_back(Attrib(temp.Trim()));
    }
}

//Obtain regular expression form of the string
//supplied
CRegExp CInput::GetRegExp(CString name)
{
    CString temp="";
    if(name.IsEmpty())
    {
        return CRegExp(name);
    }
    if(full)
    {
        temp="^";
        temp+=name;
        temp+="$";
        return CRegExp(temp);
    }

    return CRegExp(name);
}
