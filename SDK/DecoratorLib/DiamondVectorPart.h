//################################################################################################
//
// Diamond vector part decorator class
//	DiamondVectorPart.h
//
//################################################################################################

#ifndef __DIAMONDVECTORPART_H_
#define __DIAMONDVECTORPART_H_


#include "StdAfx.h"
#include "VectorPart.h"


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : DiamondVectorPart
//
//################################################################################################

class DiamondVectorPart: public VectorPart
{
protected:
	long						m_diamondWidth;
	long						m_diamondHeight;
	std::vector<CoordCommand*>	m_coordCommands;

public:
	DiamondVectorPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink, long diamondWidth, long diamondHeight);
	virtual ~DiamondVectorPart();

// =============== resembles IMgaNewDecorator
public:
	virtual void			Initialize			(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO);
	virtual CSize			GetPreferredSize	(void) const;

	virtual void			InitializeEx		(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd, PreferenceMap& preferences);

	virtual void	SetBrush					(CDC* pDC);
};

}; // namespace DecoratorSDK

#endif //__DIAMONDVECTORPART_H_
