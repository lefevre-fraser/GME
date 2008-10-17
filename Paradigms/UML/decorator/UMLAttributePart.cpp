//################################################################################################
//
// UML attribute part class (decorator part)
//	UMLAttributePart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "UMLAttributePart.h"


namespace UMLDecor {

//################################################################################################
//
// CLASS : UMLAttributePart
//
//################################################################################################

UMLAttributePart::UMLAttributePart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink,
								   const CString& nameStr, const CString& typeStr):
	AttributePart(pPart, eventSink)
{
	SetName(nameStr);
	SetType(typeStr);
	// TODO
/*	textStringVariableName		= PREF_LABEL;
	textFontVariableName		= PREF_LABELFONT;
	textMaxLengthVariableName	= PREF_LABELLENGTH;
	textColorVariableName		= PREF_LABELCOLOR;
	textLocationVariableName	= PREF_LABELLOCATION;
	textStatusVariableName		= PREF_LABELENABLED;
	textWrapStatusVariableName	= PREF_LABELWRAP;*/
}

UMLAttributePart::~UMLAttributePart()
{
}

}; // namespace UMLDecor
