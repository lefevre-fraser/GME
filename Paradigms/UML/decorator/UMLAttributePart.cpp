//################################################################################################
//
// UML attribute part class (decorator part)
//	UMLAttributePart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "UMLAttributePart.h"

#include "UMLClassPart.h"


namespace UMLDecor {

//################################################################################################
//
// CLASS : UMLAttributePart
//
//################################################################################################

UMLAttributePart::UMLAttributePart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink,
								   const CString& nameStr, const CString& typeStr, CComPtr<IMgaFCO>& pFCO):
	AttributePart(pPart, eventSink),
	m_spActualFCO(pFCO)
{
	SetName(nameStr);
	SetType(typeStr);
}

UMLAttributePart::~UMLAttributePart()
{
}

void UMLAttributePart::ExecuteOperation(const CString& newString)
{
	// transaction operation begin
	m_strText = newString;
	UMLClassPart* umlClassPart = dynamic_cast<UMLClassPart*> (GetParent());
	ASSERT(umlClassPart != NULL);
	umlClassPart->ModifyAttributes(m_spActualFCO);
	// transaction operation end
}

}; // namespace UMLDecor
