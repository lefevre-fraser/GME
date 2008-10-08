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

class VectorCommand {
public:
	enum Codes {
		BeginPath			= 0,
		EndPath				= 1,
		StrokeAndFillPath	= 2,
		MoveTo				= 3,
		LineTo				= 4,
		Rectangle			= 5
	};

	enum CoordinateConstants {
		LeftMost			= LONG_MAX - 1,
		RightMost			= LONG_MAX - 2,
		TopMost				= LONG_MAX - 3,
		BottomMost			= LONG_MAX - 4
	};

	CRect		coords;
	long		code;
};

//################################################################################################
//
// CLASS : VectorPart
//
//################################################################################################

class VectorPart: public ResizablePart
{
	CRect						m_Extents;
	std::vector<VectorCommand>	m_Commands;

public:
	VectorPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink);
	virtual ~VectorPart();

	void			SetExtents					(const CRect& extents) { m_Extents = extents; };
	void			AddCommand					(const VectorCommand& cmd) { m_Commands.push_back(cmd); };
	long			GetCommandNumber			(void) const { return (long)m_Commands.size(); };
	void			RemoveCommand				(long index);
	VectorCommand	GetCommand					(long index) const;

// =============== resembles IMgaNewDecorator
public:
	virtual void			Initialize			(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO);
	virtual feature_code	GetFeatures			(void) const;
	virtual void			Draw				(CDC* pDC);

	virtual void			InitializeEx		(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd, PreferenceMap& preferences);

private:
	CRect	ResolveCoordinateConstants			(const CRect& rect);
	long	ResolveCoordinate					(long coord);
};

}; // namespace DecoratorSDK

#endif //__VECTORPART_H_
