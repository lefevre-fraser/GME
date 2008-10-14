//################################################################################################
//
// Inheritance vector part decorator class
//	VectorPart.h
//
//################################################################################################

#ifndef __INHERITANCEVECTORPART_H_
#define __INHERITANCEVECTORPART_H_


#include "StdAfx.h"
#include "VectorPart.h"
#include "InheritanceVectorPart.h"


//################################################################################################
//
// CLASS : InheritanceVectorPart
//
//################################################################################################

class InheritanceVectorPart: public DecoratorSDK::VectorPart
{
	std::vector<DecoratorSDK::CoordCommand*>	coordCommands;

public:
	InheritanceVectorPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink);
	virtual ~InheritanceVectorPart();

// =============== resembles IMgaNewDecorator
public:
	virtual void			Initialize			(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO);
	virtual CSize			GetPreferredSize	(void) const;

	virtual void			InitializeEx		(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd, DecoratorSDK::PreferenceMap& preferences);

	virtual void	SetBrush					(CDC* pDC);
};

#endif //__INHERITANCEVECTORPART_H_
