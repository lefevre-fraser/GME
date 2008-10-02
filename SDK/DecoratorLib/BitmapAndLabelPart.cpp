//################################################################################################
//
// Composite part class (decorator part)
//	BitmapAndLabelPart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "BitmapAndLabelPart.h"
#include "TypeableBitmapPart.h"
#include "LabelPart.h"
#include "DecoratorExceptions.h"


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : BitmapAndLabelPart
//
//################################################################################################

BitmapAndLabelPart::BitmapAndLabelPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink):
	CompositePart(pPart, eventSink)
{
}

BitmapAndLabelPart::~BitmapAndLabelPart()
{
	for (std::vector<PartBase*>::iterator ii = m_compositeParts.begin(); ii != m_compositeParts.end(); ++ii) {
		if ((*ii) != NULL) {
			delete (*ii);
		}
	}
	m_compositeParts.clear();
}

void BitmapAndLabelPart::AddPart(PartBase* part)
{
	throw NotImplementedException();
}

void BitmapAndLabelPart::RemovePart(PartBase* part)
{
	throw NotImplementedException();
}

void BitmapAndLabelPart::RemovePart(int index)
{
	throw NotImplementedException();
}

PartBase* BitmapAndLabelPart::GetPart(int index)
{
	throw NotImplementedException();
}

long BitmapAndLabelPart::GetSize(void) const
{
	return 2;
}

void BitmapAndLabelPart::AddBitmapPart(TypeableBitmapPart* part)
{
	ASSERT(part != NULL);
	ASSERT(m_compositeParts.size() == 0);

	part->SetParentPart(this);
	m_compositeParts.push_back(part);
}

void BitmapAndLabelPart::AddLabelPart(LabelPart* part)
{
	ASSERT(part != NULL);
	ASSERT(m_compositeParts.size() == 1);

	part->SetParentPart(this);
	m_compositeParts.push_back(part);
}

TypeableBitmapPart* BitmapAndLabelPart::GetBitmapPart(void) const
{
	ASSERT(m_compositeParts.size() >= 1);
#ifdef _DEBUG
	TypeableBitmapPart* part = dynamic_cast<TypeableBitmapPart*> (m_compositeParts[0]);
	ASSERT(part != NULL);
	return part;
#else
	return static_cast<TypeableBitmapPart*> (m_compositeParts[0]);
#endif
}

LabelPart* BitmapAndLabelPart::GetLabelPart(void) const
{
	ASSERT(m_compositeParts.size() == 2);
#ifdef _DEBUG
	LabelPart* part = dynamic_cast<LabelPart*> (m_compositeParts[1]);
	ASSERT(part != NULL);
	return part;
#else
	return static_cast<LabelPart*> (m_compositeParts[1]);
#endif
}

}; // namespace DecoratorSDK
