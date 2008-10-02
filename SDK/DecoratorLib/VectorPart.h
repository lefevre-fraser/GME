//################################################################################################
//
// Vector part class (decorator part)
//	VectorPart.h
//
//################################################################################################

#ifndef __VECTORPART_H_
#define __VECTORPART_H_


#include "StdAfx.h"
#include "ResizablePart.h"
#include <vector>


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : VectorPart
//
//################################################################################################

class VectorPart: public ResizablePart
{
	std::vector<CRect>		lines;

public:
	VectorPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink);
	virtual ~VectorPart();

	void			SetLines					(std::vector<CRect> pLine) { lines = pLine; };
	void			AddLine						(const CRect& line) { lines.push_back(line); };
	long			GetLineNumber				(void) const { return (long)lines.size(); };
	void			RemoveLine					(long index);
	CRect			GetLine						(long index) const;

// =============== resembles IMgaNewDecorator
public:
	virtual void			Initialize			(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO);
	virtual feature_code	GetFeatures			(void) const;
	virtual void			Draw				(CDC* pDC);

	virtual void			InitializeEx		(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd, PreferenceMap& preferences);
};

}; // namespace DecoratorSDK

#endif //__VECTORPART_H_
