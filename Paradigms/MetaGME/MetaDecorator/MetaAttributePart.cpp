//################################################################################################
//
// Meta attribute part class (decorator part)
//	MetaAttributePart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "MetaAttributePart.h"

#include "MetaClassPart.h"


namespace MetaDecor {

//################################################################################################
//
// CLASS : MetaAttributePart
//
//################################################################################################

MetaAttributePart::MetaAttributePart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents>& eventSink,
									 const CString& nameStr, const CString& typeStr, const CPoint& boxPos,
									 CComPtr<IMgaFCO>& pFCO):
	AttributePart	(pPart, eventSink),
	m_boxPos		(boxPos),
	m_spActualFCO	(pFCO)
{
	SetName(nameStr);
	SetType(typeStr);
}

MetaAttributePart::~MetaAttributePart()
{
}

void MetaAttributePart::ExecuteOperation(const CString& newString)
{
	// transaction operation begin
	m_strText = newString;
	CComBSTR bstr;
	CopyTo(newString, bstr);
	COMTHROW(m_spActualFCO->put_Name(bstr));
	// transaction operation end
}

bool MetaAttributePart::IsLesser(const AttributePart* other)
{
	const MetaAttributePart* otherMa = static_cast<const MetaAttributePart*> (other);
	CPoint boxPos = otherMa->GetBoxPos();
	return (m_boxPos.y < boxPos.y || m_boxPos.y == boxPos.y && m_boxPos.x < boxPos.x);
}

}; // namespace MetaDecor
