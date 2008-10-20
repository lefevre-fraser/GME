//################################################################################################
//
// Inheritance vector part decorator class
//	VectorPart.h
//
//################################################################################################

#ifndef __INHERITANCEVECTORPART_H_
#define __INHERITANCEVECTORPART_H_


#include "StdAfx.h"
#include "TriangleVectorPart.h"


namespace MetaDecor {

enum InheritanceType {
	NormalInheritance,
	ImplementationInheritance,
	InterfaceInheritance
};

//################################################################################################
//
// CLASS : InheritanceVectorPart
//
//################################################################################################

class InheritanceVectorPart: public DecoratorSDK::TriangleVectorPart
{
protected:
	InheritanceType		m_inheritanceType;

public:
	InheritanceVectorPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink,
						  long inheritanceWidth, long inheritanceHeight, InheritanceType inheritanceType);
	virtual ~InheritanceVectorPart();

// =============== resembles IMgaNewDecorator
public:
	virtual void			Initialize			(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO);

	virtual void			InitializeEx		(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd, DecoratorSDK::PreferenceMap& preferences);
};

}; // namespace MetaDecor

#endif //__INHERITANCEVECTORPART_H_
