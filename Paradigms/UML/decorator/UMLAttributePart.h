//################################################################################################
//
// UML attribute part class (decorator part)
//	UMLAttributePart.h
//
//################################################################################################

#ifndef __UMLATTRIBUTEPART_H_
#define __UMLATTRIBUTEPART_H_


#include "StdAfx.h"
#include "AttributePart.h"


namespace UMLDecor {

//################################################################################################
//
// CLASS : UMLAttributePart
//
//################################################################################################

class UMLAttributePart: public DecoratorSDK::AttributePart
{
public:
	UMLAttributePart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink,
					 const CString& nameStr, const CString& typeStr);
	virtual ~UMLAttributePart();
};

}; // namespace UMLDecor

#endif //__UMLATTRIBUTEPART_H_
