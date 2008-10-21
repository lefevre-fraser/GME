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
// CLASS : CoordinateConstants
//
//################################################################################################

enum CoordinateConstants
{
	ZeroConstant		= 0,
	LeftMost			= 1,
	TopMost				= 2,
	RightMost			= 3,
	BottomMost			= 4
};

enum CoordinateOperations
{
	CoordAdd			= 0,
	CoordSubstract		= 1,
	CoordDivide			= 2,
	CoordMultiply		= 3
};

//################################################################################################
//
// CLASS : CoordCommand
//
//################################################################################################

class CoordCommand {
public:
	CoordCommand() {};
	virtual ~CoordCommand() {};

	virtual long	ResolveCoordinate	(const CRect& extents) const { return 0; };
};

//################################################################################################
//
// CLASS : NopCoordCommand
//
//################################################################################################

class NopCoordCommand: public CoordCommand {
	CoordinateConstants	m_CoordConst;

public:
	NopCoordCommand(): CoordCommand() {};
	virtual ~NopCoordCommand() {};
};

//################################################################################################
//
// CLASS : SimpleCoordCommand
//
//################################################################################################

class SimpleCoordCommand: public CoordCommand {
	CoordinateConstants	m_CoordConst;

public:
	SimpleCoordCommand(CoordinateConstants coordConst): CoordCommand(), m_CoordConst(coordConst) {};
	virtual ~SimpleCoordCommand() {};

	virtual long	ResolveCoordinate	(const CRect& extents) const;
};

//################################################################################################
//
// CLASS : AbsoluteCoordCommand
//
//################################################################################################

class AbsoluteCoordCommand: public CoordCommand {
	long	m_Coord;

public:
	AbsoluteCoordCommand(long coord): CoordCommand(), m_Coord(coord) {};
	virtual ~AbsoluteCoordCommand() {};

	virtual long	ResolveCoordinate	(const CRect& extents) const { return m_Coord; };
};

//################################################################################################
//
// CLASS : ComplexCoordCommand
//
//################################################################################################

class ComplexCoordCommand: public CoordCommand {
	std::vector<CoordinateConstants>	m_coordConstList;
	std::vector<double>					m_coordWeightList;
	std::vector<CoordinateOperations>	m_coordOperationList;

public:
	ComplexCoordCommand(CoordinateConstants coordConst);
	virtual ~ComplexCoordCommand();

	void AddCommand(CoordinateConstants constant, double weight, CoordinateOperations operation);

	virtual long	ResolveCoordinate	(const CRect& extents) const;
};

//################################################################################################
//
// CLASS : VectorCommand
//
//################################################################################################

class VectorCommand {
public:
	enum Codes {
		BeginPath			= 0,
		EndPath				= 1,
		StrokeAndFillPath	= 2,
		MoveTo				= 3,
		LineTo				= 4,
		Rectangle			= 5,
		Ellipse				= 6,
		SelectBrush			= 7,
		SelectPen			= 8,
		SelectNullBrush		= 9,
		SelectNullPen		= 10
	};

public:
	VectorCommand(long code):
		m_Code(code) {};
	VectorCommand(const CoordCommand* sxCmd, long code):
		m_Code(code) { m_CoordCmds.push_back(sxCmd); };
	VectorCommand(const CoordCommand* sxCmd, const CoordCommand* syCmd, long code):
		m_Code(code) { m_CoordCmds.push_back(sxCmd); m_CoordCmds.push_back(syCmd); };
	VectorCommand(const CoordCommand* sxCmd, const CoordCommand* syCmd, const CoordCommand* exCmd, const CoordCommand* eyCmd, long code):
		m_Code(code) { m_CoordCmds.push_back(sxCmd); m_CoordCmds.push_back(syCmd); m_CoordCmds.push_back(exCmd); m_CoordCmds.push_back(eyCmd); };
	virtual ~VectorCommand();

	CRect	GetResolvedCoords	(const CRect& extents) const;
	long	GetCode				(void) const { return m_Code; };

protected:
	std::vector<const CoordCommand*>	m_CoordCmds;
	long								m_Code;
};

//################################################################################################
//
// CLASS : VectorPart
//
//################################################################################################

class VectorPart: public ResizablePart
{
	// Preference variable name strings
	CString						penColorVariableName;
	CString						burshColorVariableName;

	CRect						m_Extents;
	std::vector<VectorCommand>	m_Commands;
	COLORREF					m_crPen;
	COLORREF					m_crBrush;

public:
	VectorPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink);
	virtual ~VectorPart();

	void			SetExtents					(const CRect& extents) { m_Extents = extents; };
	void			AddCommand					(const VectorCommand& cmd) { m_Commands.push_back(cmd); };
	long			GetCommandNumber			(void) const { return (long)m_Commands.size(); };
	void			RemoveCommand				(long index);
	void			RemoveAllCommands			(void) { m_Commands.clear(); };
	VectorCommand	GetCommand					(long index) const;

// =============== resembles IMgaNewDecorator
public:
	virtual void			Initialize			(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO);
	virtual feature_code	GetFeatures			(void) const;
	virtual void			SetLocation			(const CRect& location);
	virtual void			Draw				(CDC* pDC);

	virtual void			InitializeEx		(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd, PreferenceMap& preferences);

protected:
	virtual void	SetBrush					(CDC* pDC);
	virtual void	SetPen						(CDC* pDC);
};

}; // namespace DecoratorSDK

#endif //__VECTORPART_H_
