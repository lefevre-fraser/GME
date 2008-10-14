//################################################################################################
//
// Composite part class (decorator part)
//	ImageAndLabelPart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "ImageAndLabelPart.h"
#include "LabelPart.h"
#include "ResizablePart.h"
#include "DecoratorExceptions.h"


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : ImageAndLabelPart
//
//################################################################################################

ImageAndLabelPart::ImageAndLabelPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink):
	CompositePart(pPart, eventSink)
{
}

ImageAndLabelPart::~ImageAndLabelPart()
{
	for (std::vector<PartBase*>::iterator ii = m_compositeParts.begin(); ii != m_compositeParts.end(); ++ii) {
		if ((*ii) != NULL) {
			delete (*ii);
		}
	}
	m_compositeParts.clear();
}

void ImageAndLabelPart::AddImagePart(ResizablePart* part)
{
	ASSERT(part != NULL);
	ASSERT(m_compositeParts.size() == 0);

	part->SetParentPart(this);
	m_compositeParts.push_back(part);
}

void ImageAndLabelPart::AddLabelPart(LabelPart* part)
{
	ASSERT(part != NULL);
	ASSERT(m_compositeParts.size() == 1);

	part->SetParentPart(this);
	m_compositeParts.push_back(part);
}

ResizablePart* ImageAndLabelPart::GetImagePart(void) const
{
	ASSERT(m_compositeParts.size() >= 1);
#ifdef _DEBUG
	ResizablePart* part = dynamic_cast<ResizablePart*> (m_compositeParts[0]);
	ASSERT(part != NULL);
	return part;
#else
	return static_cast<ResizablePart*> (m_compositeParts[0]);
#endif
}

LabelPart* ImageAndLabelPart::GetLabelPart(void) const
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
