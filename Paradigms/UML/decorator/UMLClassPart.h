//################################################################################################
//
// New UML decorator class part class
//	UMLClassPart.h
//
//################################################################################################

#ifndef __UMLCLASSPART_H_
#define __UMLCLASSPART_H_


#include "StdAfx.h"
#include "ClassComplexPart.h"


namespace UMLDecor {

//################################################################################################
//
// CLASS : UMLClassPart
//
//################################################################################################

class UMLClassPart: public DecoratorSDK::ClassComplexPart
{
public:
	UMLClassPart(DecoratorSDK::PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink);
	virtual ~UMLClassPart();

// =============== resembles IMgaNewDecorator
public:
	virtual void	InitializeEx				(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd, DecoratorSDK::PreferenceMap& preferences);

	virtual void	CollectAttributes			(CComPtr<IMgaFCO> mgaFco = NULL);

protected:
	void			CreateCopyBitmapPart		(DecoratorSDK::PreferenceMap& preferences);
};

}; // namespace UMLDecor

#endif //__UMLCLASSPART_H_
