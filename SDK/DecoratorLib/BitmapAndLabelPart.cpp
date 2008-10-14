//################################################################################################
//
// Bitmap and label composite part class (decorator part)
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
	ImageAndLabelPart(pPart, eventSink)
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

void BitmapAndLabelPart::AddBitmapPart(TypeableBitmapPart* part)
{
	AddImagePart(part);
}

TypeableBitmapPart* BitmapAndLabelPart::GetBitmapPart(void) const
{
	ASSERT(m_compositeParts.size() >= 1);
#ifdef _DEBUG
	TypeableBitmapPart* part = dynamic_cast<TypeableBitmapPart*> (GetImagePart());
	ASSERT(part != NULL);
	return part;
#else
	return static_cast<TypeableBitmapPart*> (GetImagePart());
#endif
}

}; // namespace DecoratorSDK
