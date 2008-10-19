//################################################################################################
//
// UML stereo label part class (decorator part)
//	UMLStereoLabelPart.h
//
//################################################################################################

#ifndef __UMLSTEREOLABELPART_H_
#define __UMLSTEREOLABELPART_H_


#include "StdAfx.h"
#include "StereoLabelPart.h"


namespace UMLDecor {

//################################################################################################
//
// CLASS : StereoLabelPart
//
//################################################################################################

class UMLStereoLabelPart: public DecoratorSDK::StereoLabelPart
{
protected:
	CComPtr<IMgaFCO>	m_spActualFCO;
	long				m_labelRelYPosition;	// bottom of the text because of the bottom alignment

public:
	UMLStereoLabelPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink, CComPtr<IMgaFCO>& pFCO);
	virtual ~UMLStereoLabelPart();

	virtual void	ExecuteOperation			(const CString& newString);
};

}; // namespace UMLDecor

#endif //__UMLSTEREOLABELPART_H_
