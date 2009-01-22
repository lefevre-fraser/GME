//################################################################################################
//
// Constraint vector part decorator class
//	ConstraintVectorPart.h
//
//################################################################################################

#ifndef __CONSTRAINTVECTORPART_H_
#define __CONSTRAINTVECTORPART_H_


#include "StdAfx.h"
#include "VectorPart.h"


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : ConstraintVectorPart
//
//################################################################################################

class ConstraintVectorPart: public VectorPart
{
protected:
	COLORREF				m_crFill;
	double					m_thicknessRatio;
	long					m_constraintWidth;
	long					m_constraintHeight;

public:
	ConstraintVectorPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents>& eventSink, COLORREF fillColor,
						 double thicknessRatio, long constraintWidth, long constraintHeight);
	virtual ~ConstraintVectorPart();

// =============== resembles IMgaNewDecorator
public:
	virtual CSize			GetPreferredSize	(void) const;

	virtual void			InitializeEx		(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd, PreferenceMap& preferences);
};

}; // namespace DecoratorSDK

#endif //__CONSTRAINTVECTORPART_H_
