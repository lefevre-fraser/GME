//################################################################################################
//
// Vector decorator class
//	VectorPart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "VectorPart.h"


namespace DecoratorSDK {

static long	ResolveCoord(CoordinateConstants coordConst, const CRect& extents)
{
	switch (coordConst) {
		case ZeroConstant:	return 0;
		case LeftMost:		return extents.left;
		case TopMost:		return extents.top;
		case RightMost:		return extents.right;
		case BottomMost:	return extents.bottom;
		case OneConstant:	return 1;
	}
	return -1;
}

//################################################################################################
//
// CLASS : SimpleCoordCommand
//
//################################################################################################

long	SimpleCoordCommand::ResolveCoordinate(const CRect& extents) const
{
	return ResolveCoord(m_CoordConst, extents);
}

//################################################################################################
//
// CLASS : ComplexCoordCommand
//
//################################################################################################

ComplexCoordCommand::ComplexCoordCommand(CoordinateConstants coordConst, double weight, CoordinateOperations operation):
	CoordCommand()
{
	m_coordConstList.push_back(coordConst);
	m_coordWeightList.push_back(weight);
	m_coordOperationList.push_back(operation);
}

ComplexCoordCommand::~ComplexCoordCommand()
{
	m_coordConstList.clear();
	m_coordWeightList.clear();
	m_coordOperationList.clear();
}

void ComplexCoordCommand::AddCommand(CoordinateConstants constant, double weight, CoordinateOperations operation)
{
	m_coordConstList.push_back(constant);
	m_coordWeightList.push_back(weight);
	m_coordOperationList.push_back(operation);
}

long	ComplexCoordCommand::ResolveCoordinate(const CRect& extents) const
{
	double result = 0.0;
	for (unsigned long i = 0; i < m_coordOperationList.size(); i++) {
		switch (m_coordOperationList[i]) {
			case CoordAdd:			result = result + ResolveCoord(m_coordConstList[i], extents) * m_coordWeightList[i]; break;
			case CoordSubstract:	result = result - ResolveCoord(m_coordConstList[i], extents) * m_coordWeightList[i]; break;
			case CoordDivide:		result = result / ResolveCoord(m_coordConstList[i], extents) * m_coordWeightList[i]; break;
			case CoordMultiply:		result = result * ResolveCoord(m_coordConstList[i], extents) * m_coordWeightList[i]; break;
		}
	}

	return static_cast<long> (result);
}

//################################################################################################
//
// CLASS : VectorCommand
//
//################################################################################################

CRect	VectorCommand::GetResolvedCoords(const CRect& extents) const
{
	ASSERT(!extents.IsRectEmpty());
	CRect resolved;
	unsigned long size = m_CoordCmds.size();
	resolved.left	= size >= 1 ? m_CoordCmds[0]->ResolveCoordinate(extents) : 0;
	resolved.top	= size >= 2 ? m_CoordCmds[1]->ResolveCoordinate(extents) : 0;
	resolved.right	= size >= 3 ? m_CoordCmds[2]->ResolveCoordinate(extents) : resolved.left;
	resolved.bottom	= size >= 4 ? m_CoordCmds[3]->ResolveCoordinate(extents) : resolved.top;

	return resolved;
}

std::vector<long> VectorCommand::GetResolvedValues(const CRect& extents) const
{
	std::vector<long> resolvedValues;
	for (std::vector<const CoordCommand*>::const_iterator ii = m_CoordCmds.begin(); ii != m_CoordCmds.end(); ++ii) {
		resolvedValues.push_back((*ii)->ResolveCoordinate(extents));
	}
	return resolvedValues;
}

VectorCommand::~VectorCommand()
{
	m_CoordCmds.clear();
};

//################################################################################################
//
// CLASS : VectorPart
//
//################################################################################################

VectorPart::VectorPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink):
	ResizablePart				(pPart, eventSink),
	m_mainPath					(NULL),
	m_shadowPath				(NULL),
	m_bInMainPathDefinition		(false),
	m_bInShadowPathDefinition	(false),
	m_bShadowCasted				(false),
	m_bShadowEnabled			(true)
{
	penColorVariableName	= PREF_COLOR;
	brushColorVariableName	= PREF_BORDERCOLOR;
	borderColorVariableName	= PREF_BORDERCOLOR;
}

VectorPart::~VectorPart()
{
	RemoveAllCommands();
	DisposeCoordCommands();
	if (m_mainPath != NULL) {
		delete m_mainPath;
		m_mainPath = NULL;
	}
	if (m_shadowPath != NULL) {
		delete m_shadowPath;
		m_shadowPath = NULL;
	}
}

void VectorPart::RemoveCommand(long index)
{
	ASSERT(index >= 0 && index < GetCommandNumber());
	long i = 0;
	for(std::vector<VectorCommand>::iterator ii = m_Commands.begin(); i < GetCommandNumber() && ii != m_Commands.end(); i++, ++ii) {
		if (i == index) {
			m_Commands.erase(ii);
		}
	}
}

void VectorPart::RemoveLastCommand(long cmdCount)
{
	ASSERT(cmdCount >= 1);
	ASSERT(cmdCount <= GetCommandNumber());
	for (long i = 0; i < cmdCount; i++)
		m_Commands.pop_back();
}

void VectorPart::DisposeCoordCommands(void)
{
	for(unsigned long i = 0; i < m_coordCommands.size(); i++) {
		delete m_coordCommands[i];
	}
	m_coordCommands.clear();
}

VectorCommand VectorPart::GetCommand(long index) const
{
	ASSERT(index >= 0 && index < GetCommandNumber());
	return m_Commands[index];
}

feature_code VectorPart::GetFeatures(void) const
{
	// TODO: it depends, if it is resizable
	return F_RESIZABLE | F_MOUSEEVENTS;
}

void VectorPart::SetLocation(const CRect& location)
{
	m_Extents = location;
	ResizablePart::SetLocation(location);
}

void VectorPart::Draw(CDC* pDC, Gdiplus::Graphics* gdip)
{
	COLORREF penColor = m_bActive ? m_crPen : COLOR_GRAYED_OUT;
	m_CurrentPen = DecoratorSDK::getFacilities().GetPen(penColor);

	COLORREF brushColor = m_bActive ? m_crBrush : COLOR_GRAYED_OUT;
	m_CurrentBrush = DecoratorSDK::getFacilities().GetBrush(brushColor);

	for(std::vector<VectorCommand>::iterator ii = m_Commands.begin(); ii != m_Commands.end(); ++ii) {
		long cmdCode = (*ii).GetCode();
		switch(cmdCode) {
			case VectorCommand::DrawLine: {
					CRect rc = (*ii).GetResolvedCoords(m_Extents);
					gdip->DrawLine(m_CurrentPen, rc.left, rc.top, rc.right, rc.bottom);
				}
				break;
			case VectorCommand::DrawRectangle: {
					CRect rc = (*ii).GetResolvedCoords(m_Extents);
					gdip->DrawRectangle(m_CurrentPen, rc.left, rc.top, rc.Width(), rc.Height());
				}
				break;
			case VectorCommand::DrawEllipse: {
					CRect rc = (*ii).GetResolvedCoords(m_Extents);
					gdip->DrawEllipse(m_CurrentPen, rc.left, rc.top, rc.Width(), rc.Height());
				}
				break;
			case VectorCommand::DrawPolygon: {
					std::vector<long> points = (*ii).GetResolvedValues(m_Extents);
					long coordNum = static_cast<long> (points.size() / 2);
					Gdiplus::Point* ppoints = new Gdiplus::Point[coordNum];
					for (long i = 0; i < coordNum; i++)
						ppoints[i] = Gdiplus::Point(points[2 * i], points[2 * i + 1]);
					gdip->DrawPolygon(m_CurrentPen, ppoints, coordNum);
					delete [] ppoints;
				}
				break;
			case VectorCommand::FillRectangle: {
					CRect rc = (*ii).GetResolvedCoords(m_Extents);
					gdip->FillRectangle(m_CurrentBrush, rc.left, rc.top, rc.Width(), rc.Height());
				}
				break;
			case VectorCommand::FillEllipse: {
					CRect rc = (*ii).GetResolvedCoords(m_Extents);
					gdip->FillEllipse(m_CurrentBrush, rc.left, rc.top, rc.Width(), rc.Height());
				}
				break;
			case VectorCommand::FillPolygon: {
					std::vector<long> points = (*ii).GetResolvedValues(m_Extents);
					long coordNum = static_cast<long> (points.size() / 2);
					Gdiplus::Point* ppoints = new Gdiplus::Point[coordNum];
					for (long i = 0; i < coordNum; i++)
						ppoints[i] = Gdiplus::Point(points[2 * i], points[2 * i + 1]);
					gdip->FillPolygon(m_CurrentBrush, ppoints, coordNum);
					delete [] ppoints;
				}
				break;
			case VectorCommand::SelectPen: {
					std::vector<long> colors = (*ii).GetResolvedValues(m_Extents);
					ASSERT(colors.size() == 2);
					COLORREF penColor = m_bActive ? colors[0] : colors[1];
					m_CurrentPen = DecoratorSDK::getFacilities().GetPen(penColor);
				}
				break;
			case VectorCommand::SelectBrush: {
					std::vector<long> colors = (*ii).GetResolvedValues(m_Extents);
					ASSERT(colors.size() == 2);
					COLORREF brushColor = m_bActive ? colors[0] : colors[1];
					m_CurrentBrush = DecoratorSDK::getFacilities().GetBrush(brushColor);
				}
				break;
			case VectorCommand::BeginPath: {
					ASSERT(m_mainPath == NULL);
					if (m_mainPath != NULL)
						delete m_mainPath;
					m_mainPath = new Gdiplus::GraphicsPath();
					m_bInMainPathDefinition = true;
				}
				break;
			case VectorCommand::EndPath: {
					ASSERT(m_mainPath != NULL);
					m_bInMainPathDefinition = false;
				}
				break;
			case VectorCommand::BeginShadowPath:
				{
					ASSERT(m_shadowPath == NULL && m_bInMainPathDefinition == false);
					if (m_shadowPath != NULL)
						delete m_shadowPath;
					m_shadowPath = new Gdiplus::GraphicsPath();
					m_bInShadowPathDefinition = true;
				}
				break;
			case VectorCommand::EndShadowPath:
			case VectorCommand::CopyShadowPath: {
					ASSERT(m_shadowPath != NULL || cmdCode == VectorCommand::CopyShadowPath);
					if (cmdCode == VectorCommand::CopyShadowPath) {
						if (m_shadowPath != NULL)
							delete m_shadowPath;
						m_shadowPath = new Gdiplus::GraphicsPath();
						m_shadowPath->AddPath(m_mainPath, FALSE);
					}
					m_bInShadowPathDefinition = false;
				}
				break;
			case VectorCommand::CastShadowPath: {
					long shadowThickness = 0;
					std::vector<long> points = (*ii).GetResolvedValues(m_Extents);
					if (points.size() > 0)
						shadowThickness = points[0];
					else
						shadowThickness = 9;
					if (shadowThickness > 0 && m_bShadowEnabled) {
						if (m_shadowPath == NULL) {
							m_shadowPath = new Gdiplus::GraphicsPath();
							m_shadowPath->AddPath(m_mainPath, FALSE);
						}
						Gdiplus::Matrix shadowTranslationMatrix;
						shadowTranslationMatrix.Translate(static_cast<float> (shadowThickness), static_cast<float> (shadowThickness));
						m_shadowPath->Transform(&shadowTranslationMatrix);

						Gdiplus::PathGradientBrush shadowPathGradientBrush(m_shadowPath);
						m_shadowStartColor = m_bActive ? m_crPen : COLOR_GRAYED_OUT;

						// Set blend factors and positions for the path gradient brush.
						Gdiplus::Color shadowStartColor = Gdiplus::Color(255,
																		 GetRValue(m_shadowStartColor),
																		 GetGValue(m_shadowStartColor),
																		 GetBValue(m_shadowStartColor));
						Gdiplus::Color shadowBlendedColor = Gdiplus::Color(128,
																		   GetRValue(m_shadowStartColor),
																		   GetGValue(m_shadowStartColor),
																		   GetBValue(m_shadowStartColor));
						Gdiplus::Color shadowEndColor = Gdiplus::Color(0,
																	   GetRValue(m_shadowStartColor),
																	   GetGValue(m_shadowStartColor),
																	   GetBValue(m_shadowStartColor));
						Gdiplus::Color presetColors[] = {
														shadowEndColor,
														shadowBlendedColor,
														shadowStartColor };
						float shadowBorder = static_cast<float> (shadowThickness / (m_Extents.Width() / 2.0));
						if (shadowBorder > 1.0)
							shadowBorder = 1.0;
						float interpolationPositions[] = {
							0.0f,
							shadowBorder,
							1.0f };
						shadowPathGradientBrush.SetInterpolationColors(presetColors, interpolationPositions, 3);

						gdip->FillPath(&shadowPathGradientBrush, m_shadowPath);
					}
					m_bShadowCasted = true;
				}
				break;
			case VectorCommand::FillPath:
			case VectorCommand::StrokePath:
			case VectorCommand::StrokeAndFillPath: {
					if (cmdCode == VectorCommand::FillPath || cmdCode == VectorCommand::StrokeAndFillPath) {
						std::vector<long> colors = (*ii).GetResolvedValues(m_Extents);
						ASSERT(colors.size() == 0 || colors.size() == 2);
						if (m_bShadowCasted || colors.size() == 2) {
							Gdiplus::SolidBrush* fillBrush = NULL;
							if (colors.size() == 2)
								fillBrush = DecoratorSDK::getFacilities().GetBrush((COLORREF)(m_bActive ? colors[0] : colors[1]));
							else
								fillBrush = DecoratorSDK::getFacilities().GetBrush(m_shadowEndColor);
							gdip->FillPath(fillBrush, m_mainPath);
						}
					}
					if (cmdCode == VectorCommand::StrokePath || cmdCode == VectorCommand::StrokeAndFillPath) {
						COLORREF penColor = m_bActive ? m_crPen : COLOR_GRAYED_OUT;
						Gdiplus::Pen* strokePen = DecoratorSDK::getFacilities().GetPen(penColor);
						gdip->DrawPath(strokePen, m_mainPath);
					}
				}
				break;
			case VectorCommand::AddLineToPath: {
					CRect rc = (*ii).GetResolvedCoords(m_Extents);
					if (m_bInMainPathDefinition)
						m_mainPath->AddLine(rc.left, rc.top, rc.right, rc.bottom);
					if (m_bInShadowPathDefinition)
						m_shadowPath->AddLine(rc.left, rc.top, rc.right, rc.bottom);
				}
				break;
			case VectorCommand::AddEllipseToPath: {
					CRect rc = (*ii).GetResolvedCoords(m_Extents);
					if (m_bInMainPathDefinition)
						m_mainPath->AddEllipse(rc.left, rc.top, rc.Width(), rc.Height());
					if (m_bInShadowPathDefinition)
						m_shadowPath->AddEllipse(rc.left, rc.top, rc.Width(), rc.Height());
				}
				break;
			case VectorCommand::AddPolygonToPath: {
					std::vector<long> points = (*ii).GetResolvedValues(m_Extents);
					long coordNum = static_cast<long> (points.size() / 2);
					Gdiplus::Point* ppoints = new Gdiplus::Point[coordNum];
					for (long i = 0; i < coordNum; i++)
						ppoints[i] = Gdiplus::Point(points[2 * i], points[2 * i + 1]);
					if (m_bInMainPathDefinition)
						m_mainPath->AddPolygon(ppoints, coordNum);
					if (m_bInShadowPathDefinition)
						m_shadowPath->AddPolygon(ppoints, coordNum);
					delete [] ppoints;
				}
				break;
			case VectorCommand::AddArcToPath: {
					std::vector<long> values = (*ii).GetResolvedValues(m_Extents);
					ASSERT(values.size() == 6);
					if (m_bInMainPathDefinition)
						m_mainPath->AddArc(values[0], values[1], values[2], values[3], (float)values[4], (float)values[5]);
					if (m_bInShadowPathDefinition)
						m_shadowPath->AddArc(values[0], values[1], values[2], values[3], (float)values[4], (float)values[5]);
				}
				break;
			default: ASSERT(true);
		}
	}
	if (m_mainPath != NULL) {
		delete m_mainPath;
		m_mainPath = NULL;
	}
	if (m_shadowPath != NULL) {
		delete m_shadowPath;
		m_shadowPath = NULL;
	}

	ResizablePart::Draw(pDC, gdip);
}

// New functions
void VectorPart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
							  HWND parentWnd, PreferenceMap& preferences)
{
	DecoratorSDK::getFacilities().getMetaFCO(pPart, m_spMetaFCO);
	ResizablePart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);

	// Pen's Color
	m_crPen = COLOR_BLACK;
	PreferenceMap::iterator it = preferences.find(penColorVariableName);
	if (it != preferences.end()) {
		m_crPen = it->second.uValue.crValue;
	} else {
		getFacilities().getPreference(m_spFCO, m_spMetaFCO, penColorVariableName, m_crPen);
	}

	// Brush's Color
	m_crBrush = COLOR_WHITE;
	it = preferences.find(brushColorVariableName);
	if (it != preferences.end()) {
		m_crBrush = it->second.uValue.crValue;
	} else {
		getFacilities().getPreference(m_spFCO, m_spMetaFCO, penColorVariableName, m_crBrush);
	}

	m_shadowEndColor = COLOR_WHITE;
	it = preferences.find(borderColorVariableName);
	if (it != preferences.end()) {
		m_shadowEndColor = it->second.uValue.crValue;
	} else {
		getFacilities().getPreference(m_spFCO, m_spMetaFCO, borderColorVariableName, m_shadowEndColor);
	}

	m_bShadowEnabled = true;
	it = preferences.find(PREF_ITEMSHADOWCAST);
	if (it != preferences.end())
		m_bShadowEnabled = it->second.uValue.bValue;
}

}; // namespace DecoratorSDK
