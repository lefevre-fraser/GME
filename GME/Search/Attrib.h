#pragma once

#include "regexp.h"
class Attrib
{
public:
    Attrib(void);
    Attrib(CString& str);
    ~Attrib(void);
    BOOL Compare(CString &rhs,int type);
    BOOL LogicalCompare(BOOL lhs,const Attrib & oper,BOOL rhs);
    CRegExp GetRegExp(CString& str,BOOL full);
    BOOL CheckInteger(int lhs,int rhs);
    BOOL CheckDouble(double lhs,double rhs);
    BOOL CheckBool(BOOL lhs,BOOL rhs);
    BOOL CheckString(BOOL lhs);
    BOOL IsOperator(){ return name=="&" || name=="|";
    }


public:
    CString name;
    CString oper;
    CString value;
    BOOL eval;
};
