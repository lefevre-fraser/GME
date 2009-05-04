#include "stdafx.h"
#include "Attrib.h"

Attrib::Attrib(void):eval(FALSE)
{
}
Attrib::Attrib(CString &str):eval(FALSE)
{
    
    if(str=="&" ||str=="|")
    {
        name =str;
        return;
    }
    CString temp(str);
    int index=temp.Find(">=",0);
    //CString token=temp.Tokenize("<=",index);
    if(index!=-1)
    {
        name=temp.Left(index).Trim();
        oper=">=";
        value=temp.Right(temp.GetLength()-index-2).Trim();
        return;
    }

    index=temp.Find("<=",0);
    if(index!=-1)
    {
        name=temp.Left(index).Trim();
        oper="<=";
        value=temp.Right(temp.GetLength()-index-2).Trim();
        return;
    }
    index=temp.Find("!=",0);
    if(index!=-1)
    {
        name=temp.Left(index).Trim();
        oper="!=";
        value=temp.Right(temp.GetLength()-index-2).Trim();
        return;
    }

    index=temp.Find("<",0);
    if(index!=-1)
    {
        name=temp.Left(index).Trim();
        oper="<";
        value=temp.Right(temp.GetLength()-index-1).Trim();
        return;
    }

    index=temp.Find(">",0);
    if(index!=-1)
    {
        name=temp.Left(index).Trim();
        oper=">";
        value=temp.Right(temp.GetLength()-index-1).Trim();
        return;
    }
    index=temp.Find("=",0);
    if(index!=-1)
    {
        name=temp.Left(index).Trim();
        oper="=";
        value=temp.Right(temp.GetLength()-index-1).Trim();
        return;
    }
    name=temp;
}
Attrib::~Attrib(void)
{
}

BOOL Attrib::Compare(CString& rhs,int type)
{
    switch(type)
	{
		case 0: 
            return strcmp(value,rhs);
            
		case 1: 
            return CheckInteger(atoi(value),atoi(rhs));
            
		case 2: 
            return CheckDouble(atof(value),atof(rhs));
            break;
		case 3: 
            return value==rhs;
            break;
		default:	
            break;
	}
    return TRUE;
}

BOOL Attrib::CheckInteger(int lhs,int rhs)
{
    if(oper==">=")
    {
        return lhs>=rhs;
    }
    if(oper=="<=")
    {
        return lhs<=rhs;
    }
    if(oper=="!=")
    {
        return lhs!=rhs;
    }
    if(oper=="=")
    {
        return lhs==rhs;
    }
    if(oper==">")
    {
        return lhs>rhs;
    }
    if(oper=="<")
    {
        return lhs<rhs;
    }
    return TRUE;
}

BOOL Attrib::CheckDouble(double lhs,double rhs)
{
    if(oper==">=")
    {
        return lhs>=rhs;
    }
    if(oper=="<=")
    {
        return lhs<=rhs;
    }
    if(oper=="!=")
    {
        return lhs!=rhs;
    }
    if(oper=="=")
    {
        return lhs==rhs;
    }
    if(oper==">")
    {
        return lhs>rhs;
    }
    if(oper=="<")
    {
        return lhs<rhs;
    }
    return TRUE;
}

BOOL Attrib::CheckBool(BOOL lhs,BOOL rhs)
{
    if(oper=="=")
    {
        return lhs==rhs;
    }
    else if(oper=="!=")
    {
        return lhs!=rhs;
    }
    return FALSE;
}

BOOL Attrib::CheckString(BOOL lhs)
{
    if(oper=="=")
        return lhs;
    else if(oper=="!=")
        return !lhs;
    return FALSE;
}

BOOL Attrib::LogicalCompare(BOOL lhs,const Attrib & oper,BOOL rhs)
{
    if(oper.name=="&")
    {
        return lhs&&rhs;
    }
    if(oper.name=="|")
    {
        return lhs||rhs;
    }
    return FALSE;
}

CRegExp Attrib::GetRegExp(CString& str,BOOL full)
{
    CString temp;
    if(full)
    {
        temp.Append("^");
        temp.Append(str);
        temp.Append("$");

    }
    else
        temp=str;

    return CRegExp(temp);
}
