#include "stdafx.h"
#include "Attribute.h"


Attribute::Attribute(void):eval(FALSE)
{
}
Attribute::Attribute(CString &strInput):eval(FALSE)
{
    if(strInput=="&" ||strInput=="|")
    {
        name =strInput;
        return;
    }
    name=strInput;

    //parse the attribute expressions for operators and operands
    //keep single lettered operators first
    Parse(strInput,"<");
    Parse(strInput,">");
    Parse(strInput,"=");
    Parse(strInput,">=");
    Parse(strInput,"<=");
    Parse(strInput,"!=");
 
}

void Attribute::Parse(const CString& strInput,const CString& operation)
{
    CString strTemp(strInput);
    int index=strTemp.Find(operation,0);
    //CString token=temp.Tokenize("<=",index);
    if(index!=-1)
    {
        name=strTemp.Left(index).Trim();
        this->operation=operation;
        value=strTemp.Right(strTemp.GetLength()-index-operation.GetLength()).Trim();
        return;
    }
    
}

Attribute::~Attribute(void)
{
}

BOOL Attribute::Compare(CString& rhs,int type)
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

//compare the integer values based on operator it has
BOOL Attribute::CheckInteger(int lhs,int rhs)
{
    if(operation==">=")
    {
        return lhs>=rhs;
    }
    if(operation=="<=")
    {
        return lhs<=rhs;
    }
    if(operation=="!=")
    {
        return lhs!=rhs;
    }
    if(operation=="=")
    {
        return lhs==rhs;
    }
    if(operation==">")
    {
        return lhs>rhs;
    }
    if(operation=="<")
    {
        return lhs<rhs;
    }
    return TRUE;
}

//Compare the double values best on operator it has
BOOL Attribute::CheckDouble(double lhs,double rhs)
{
    if(operation==">=")
    {
        return lhs>=rhs;
    }
    if(operation=="<=")
    {
        return lhs<=rhs;
    }
    if(operation=="!=")
    {
        return lhs!=rhs;
    }
    if(operation=="=")
    {
        return lhs==rhs;
    }
    if(operation==">")
    {
        return lhs>rhs;
    }
    if(operation=="<")
    {
        return lhs<rhs;
    }
    return TRUE;
}

BOOL Attribute::CheckBool(BOOL lhs,BOOL rhs)
{
    if(operation=="=")
    {
        return lhs==rhs;
    }
    else if(operation=="!=")
    {
        return lhs!=rhs;
    }
    return FALSE;
}

BOOL Attribute::CheckString(BOOL lhs)
{
    if(operation=="=")
        return lhs;
    else if(operation=="!=")
        return !lhs;
    return FALSE;
}

BOOL Attribute::LogicalCompare(BOOL lhs,const Attribute & operation,BOOL rhs)
{
    if(operation.name=="&")
    {
        return lhs&&rhs;
    }
    if(operation.name=="|")
    {
        return lhs||rhs;
    }
    return FALSE;
}

std::tr1::regex Attribute::GetRegExp(CString& str,BOOL full)
{
    CString strTemp;
    if(full)
    {
        strTemp.Append("^");
        strTemp.Append(str);
        strTemp.Append("$");

    }
    else
        strTemp=str;

    return std::tr1::regex(strTemp);
}
