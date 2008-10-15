//################################################################################################
//
// Class complex part class (decorator part)
//	ClassComplexPart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "ClassComplexPart.h"
#include "DecoratorExceptions.h"
#include <algorithm>


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : ClassComplexPart
//
//################################################################################################

ClassComplexPart::ClassComplexPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink):
	VectorPart					(pPart, eventSink),

	m_LabelPart					(NULL),
	m_StereotypePart			(NULL),
	m_crAttributeText			(COLOR_BLACK),
	m_iLongestTextLength		(0),
	m_iShortestTextLength		(LONG_MAX)
{
}

ClassComplexPart::~ClassComplexPart()
{
}

void ClassComplexPart::Initialize(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO)
{
	m_LabelPart->Initialize(pProject, pPart, pFCO);
	if (m_StereotypePart != NULL)
		m_StereotypePart->Initialize(pProject, pPart, pFCO);
	for (std::vector<AttributePart*>::iterator ii = m_AttributeParts.begin(); ii != m_AttributeParts.end(); ++ii) {
		(*ii)->Initialize(pProject, pPart, pFCO);
	}
	VectorPart::Initialize(pProject, pPart, pFCO);
}

void ClassComplexPart::Destroy()
{
	m_LabelPart->Destroy();
	if (m_StereotypePart != NULL)
		m_StereotypePart->Destroy();
	for (std::vector<AttributePart*>::iterator ii = m_AttributeParts.begin(); ii != m_AttributeParts.end(); ++ii) {
		(*ii)->Destroy();
	}
	VectorPart::Destroy();
}

CString ClassComplexPart::GetMnemonic(void) const
{
	return VectorPart::GetMnemonic();
}

feature_code ClassComplexPart::GetFeatures(void) const
{
	feature_code featureCodes = 0;

	feature_code labelFeatureCodes = m_LabelPart->GetFeatures();
	featureCodes |= labelFeatureCodes;
	if (m_StereotypePart != NULL) {
		feature_code stereotypeFeatureCodes = m_StereotypePart->GetFeatures();
		featureCodes |= stereotypeFeatureCodes;
	}

	for (std::vector<AttributePart*>::const_iterator ii = m_AttributeParts.begin(); ii != m_AttributeParts.end(); ++ii) {
		feature_code attrubuteFeatureCodes = (*ii)->GetFeatures();
		featureCodes |= attrubuteFeatureCodes;
	}

	feature_code partFeatureCodes = VectorPart::GetFeatures();
	featureCodes |= partFeatureCodes;

	return featureCodes;
}

void ClassComplexPart::SetParam(const CString& strName, VARIANT vValue)
{
	m_LabelPart->SetParam(strName, vValue);
	if (m_StereotypePart != NULL)
		m_StereotypePart->SetParam(strName, vValue);
	for (std::vector<AttributePart*>::iterator ii = m_AttributeParts.begin(); ii != m_AttributeParts.end(); ++ii) {
		(*ii)->SetParam(strName, vValue);
	}
	VectorPart::SetParam(strName, vValue);
}

bool ClassComplexPart::GetParam(const CString& strName, VARIANT* pvValue)
{
	try {
		if (VectorPart::GetParam(strName, pvValue))
			return true;
	}
	catch(UnknownParameterException&) {
	}
	return false;
}

void ClassComplexPart::SetActive(bool bIsActive)
{
	m_LabelPart->SetActive(bIsActive);
	if (m_StereotypePart != NULL)
		m_StereotypePart->SetActive(bIsActive);
	for (std::vector<AttributePart*>::iterator ii = m_AttributeParts.begin(); ii != m_AttributeParts.end(); ++ii) {
		(*ii)->SetActive(bIsActive);
	}
	VectorPart::SetActive(bIsActive);
}

CSize ClassComplexPart::GetPreferredSize(void) const
{
	CSize size = ResizablePart::GetPreferredSize();
	if (size.cx * size.cy != 0)
		return size;

/*	if (m_LeftPorts.empty() && m_RightPorts.empty()) {
		if (!m_pBitmap || m_pBitmap->getName() == createResString(IDB_MODEL)) {
			return CSize(WIDTH_MODEL, HEIGHT_MODEL);
		} else {
			return VectorPart::GetPreferredSize();
		}
	}

	LOGFONT logFont;
	getFacilities().getFont(FONT_PORT)->pFont->GetLogFont(&logFont);
	long lWidth = 0;
	if (m_bPortLabelInside) {
		ASSERT(m_iLongestPortTextLength >= 0 && m_iLongestPortTextLength <= 1000);
		ASSERT(m_iMaxPortTextLength >= 0 && m_iMaxPortTextLength <= 1000);
		ASSERT(m_iMaxPortTextLength); // m_iMaxPortTextLength > 0 !!! since
		long lw = min(m_iMaxPortTextLength, m_iLongestPortTextLength);
		lWidth = (24 + 5 * (lw - 3) + GAP_LABEL + WIDTH_PORT + GAP_XMODELPORT) * 2 + GAP_PORTLABEL;
	} else {
		lWidth = (8 * 3 + GAP_LABEL + WIDTH_PORT + GAP_XMODELPORT) * 2 + GAP_PORTLABEL;
	}

	long lHeight = GAP_YMODELPORT * 2 +
					max(m_LeftPorts.size(), m_RightPorts.size()) * (HEIGHT_PORT + GAP_PORT) - GAP_PORT;
*/
	return CSize(WIDTH_MODEL, HEIGHT_MODEL);
}

void ClassComplexPart::SetLocation(const CRect& location)
{
	m_LabelPart->SetLocation(location);
	if (m_StereotypePart != NULL)
		m_StereotypePart->SetLocation(location);
	for (std::vector<AttributePart*>::iterator ii = m_AttributeParts.begin(); ii != m_AttributeParts.end(); ++ii) {
		(*ii)->SetLocation(location);
	}
	VectorPart::SetLocation(location);
	CalcRelPositions();
}

CRect ClassComplexPart::GetLocation(void) const
{
	return VectorPart::GetLocation();
}

CRect ClassComplexPart::GetLabelLocation(void) const
{
	CRect labelLocation;
	try {
		labelLocation = m_LabelPart->GetLabelLocation();
	}
	catch(NotImplementedException&) {
	}
	return labelLocation;
}

void ClassComplexPart::Draw(CDC* pDC)
{
	CalcRelPositions(pDC);
	m_LabelPart->Draw(pDC);
	if (m_StereotypePart != NULL)
		m_StereotypePart->Draw(pDC);
	for (std::vector<AttributePart*>::iterator ii = m_AttributeParts.begin(); ii != m_AttributeParts.end(); ++ii) {
		(*ii)->Draw(pDC);
	}
	VectorPart::Draw(pDC);
}

void ClassComplexPart::SaveState()
{
	m_LabelPart->SaveState();
	if (m_StereotypePart != NULL)
		m_StereotypePart->SaveState();
	for (std::vector<AttributePart*>::iterator ii = m_AttributeParts.begin(); ii != m_AttributeParts.end(); ++ii) {
		(*ii)->SaveState();
	}
	VectorPart::SaveState();
}

// New functions
void ClassComplexPart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
									HWND parentWnd, PreferenceMap& preferences)
{
/*	preferences[PREF_ICONDEFAULT]	= PreferenceVariant(createResString(IDB_MODEL));
	preferences[PREF_TILESDEFAULT]	= PreferenceVariant(getFacilities().getTileVector(TILE_MODELDEFAULT));
	preferences[PREF_TILESUNDEF]	= PreferenceVariant(getFacilities().getTileVector(TILE_PORTDEFAULT));

	if (pFCO) {
		PreferenceMap::iterator it = preferences.find(PREF_PORTLABELCOLOR);
		if (it != preferences.end())
			m_crPortText = it->second.uValue.crValue;
		else
			getFacilities().getPreference(pFCO, PREF_PORTLABELCOLOR, m_crPortText);

		it = preferences.find(PREF_PORTLABELINSIDE);
		if (it != preferences.end())
			m_bPortLabelInside = it->second.uValue.bValue;
		else
			getFacilities().getPreference(pFCO, PREF_PORTLABELINSIDE, m_bPortLabelInside);

		long o = m_iMaxPortTextLength;
		it = preferences.find(PREF_PORTLABELLENGTH);
		if (it != preferences.end()) {
			m_iMaxPortTextLength = it->second.uValue.lValue;
		} else {
			if (getFacilities().getPreference(pFCO, PREF_PORTLABELLENGTH, m_iMaxPortTextLength))
				m_iMaxPortTextLength = abs(m_iMaxPortTextLength);	//convert any negative value to positive
			else	//if not found in registry
				m_iMaxPortTextLength = MAX_PORT_LENGTH;	// the default value in Preferences
		}
		if (m_iMaxPortTextLength == 0)	// if 0 it means it has to show all way long
			m_iMaxPortTextLength = 999;	// so we set a huge value

		it = preferences.find(PREF_BORDERCOLOR);
		if (it != preferences.end())
			m_crBorder = it->second.uValue.crValue;
		else
			getFacilities().getPreference(pFCO, PREF_BORDERCOLOR, m_crBorder);

		TypeableBitmapPart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);
	} else {
		TypeableBitmapPart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);
	}

	if (m_LeftPorts.empty() && m_RightPorts.empty())
		m_pTileVector = getFacilities().getTileVector(TILE_ATOMDEFAULT);*/
}

void ClassComplexPart::SetSelected(bool bIsSelected)
{
	m_LabelPart->SetSelected(bIsSelected);
	if (m_StereotypePart != NULL)
		m_StereotypePart->SetSelected(bIsSelected);
	for (std::vector<AttributePart*>::iterator ii = m_AttributeParts.begin(); ii != m_AttributeParts.end(); ++ii) {
		(*ii)->SetSelected(bIsSelected);
	}
	VectorPart::SetSelected(bIsSelected);
}

bool ClassComplexPart::MouseMoved(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	HRESULT retVal = S_OK;
	try {
		if (VectorPart::MouseMoved(nFlags, point, transformHDC))
			return true;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		try {
			if (m_LabelPart->MouseMoved(nFlags, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	if (m_StereotypePart != NULL && (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED)) {
		try {
			if (m_StereotypePart->MouseMoved(nFlags, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<AttributePart*>::iterator ii = m_AttributeParts.begin(); ii != m_AttributeParts.end(); ++ii) {
			try {
				if ((*ii)->MouseMoved(nFlags, point, transformHDC))
					return true;
			}
			catch(hresult_exception& e) {
				retVal = e.hr;
			}
			catch(DecoratorException& e) {
				retVal = e.GetHResult();
			}
			if (retVal != S_OK && retVal != S_DECORATOR_EVENT_NOT_HANDLED && retVal != E_DECORATOR_NOT_IMPLEMENTED)
				break;
		}
	}

	return false;
}

bool ClassComplexPart::MouseLeftButtonDown(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	HRESULT retVal = S_OK;
	try {
		if (VectorPart::MouseLeftButtonDown(nFlags, point, transformHDC))
			return true;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		try {
			if (m_LabelPart->MouseLeftButtonDown(nFlags, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	if (m_StereotypePart != NULL && (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED)) {
		try {
			if (m_StereotypePart->MouseLeftButtonDown(nFlags, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<AttributePart*>::iterator ii = m_AttributeParts.begin(); ii != m_AttributeParts.end(); ++ii) {
			try {
				if ((*ii)->MouseLeftButtonDown(nFlags, point, transformHDC))
					return true;
			}
			catch(hresult_exception& e) {
				retVal = e.hr;
			}
			catch(DecoratorException& e) {
				retVal = e.GetHResult();
			}
			if (retVal != S_OK && retVal != S_DECORATOR_EVENT_NOT_HANDLED && retVal != E_DECORATOR_NOT_IMPLEMENTED)
				break;
		}
	}

	return false;
}

bool ClassComplexPart::MouseLeftButtonUp(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	HRESULT retVal = S_OK;
	try {
		if (VectorPart::MouseLeftButtonUp(nFlags, point, transformHDC))
			return true;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		try {
			if (m_LabelPart->MouseLeftButtonUp(nFlags, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	if (m_StereotypePart != NULL && (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED)) {
		try {
			if (m_StereotypePart->MouseLeftButtonUp(nFlags, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<AttributePart*>::iterator ii = m_AttributeParts.begin(); ii != m_AttributeParts.end(); ++ii) {
			try {
				if ((*ii)->MouseLeftButtonUp(nFlags, point, transformHDC))
					return true;
			}
			catch(hresult_exception& e) {
				retVal = e.hr;
			}
			catch(DecoratorException& e) {
				retVal = e.GetHResult();
			}
			if (retVal != S_OK && retVal != S_DECORATOR_EVENT_NOT_HANDLED && retVal != E_DECORATOR_NOT_IMPLEMENTED)
				break;
		}
	}

	return false;
}

bool ClassComplexPart::MouseLeftButtonDoubleClick(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	HRESULT retVal = S_OK;
	try {
		if (VectorPart::MouseLeftButtonDoubleClick(nFlags, point, transformHDC))
			return true;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		try {
			if (m_LabelPart->MouseLeftButtonDoubleClick(nFlags, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	if (m_StereotypePart != NULL && (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED)) {
		try {
			if (m_StereotypePart->MouseLeftButtonDoubleClick(nFlags, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<AttributePart*>::iterator ii = m_AttributeParts.begin(); ii != m_AttributeParts.end(); ++ii) {
			try {
				if ((*ii)->MouseLeftButtonDoubleClick(nFlags, point, transformHDC))
					return true;
			}
			catch(hresult_exception& e) {
				retVal = e.hr;
			}
			catch(DecoratorException& e) {
				retVal = e.GetHResult();
			}
			if (retVal != S_OK && retVal != S_DECORATOR_EVENT_NOT_HANDLED && retVal != E_DECORATOR_NOT_IMPLEMENTED)
				break;
		}
	}

	return false;
}

bool ClassComplexPart::MouseRightButtonDown(HMENU hCtxMenu, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	HRESULT retVal = S_OK;
	try {
		if (VectorPart::MouseRightButtonDown(hCtxMenu, nFlags, point, transformHDC))
			return true;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		try {
			if (m_LabelPart->MouseRightButtonDown(hCtxMenu, nFlags, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	if (m_StereotypePart != NULL && (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED)) {
		try {
			if (m_StereotypePart->MouseRightButtonDown(hCtxMenu, nFlags, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<AttributePart*>::iterator ii = m_AttributeParts.begin(); ii != m_AttributeParts.end(); ++ii) {
			try {
				if ((*ii)->MouseRightButtonDown(hCtxMenu, nFlags, point, transformHDC))
					return true;
			}
			catch(hresult_exception& e) {
				retVal = e.hr;
			}
			catch(DecoratorException& e) {
				retVal = e.GetHResult();
			}
			if (retVal != S_OK && retVal != S_DECORATOR_EVENT_NOT_HANDLED && retVal != E_DECORATOR_NOT_IMPLEMENTED)
				break;
		}
	}

	return false;
}

bool ClassComplexPart::MouseRightButtonUp(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	HRESULT retVal = S_OK;
	try {
		if (VectorPart::MouseRightButtonUp(nFlags, point, transformHDC))
			return true;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		try {
			if (m_LabelPart->MouseRightButtonUp(nFlags, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	if (m_StereotypePart != NULL && (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED)) {
		try {
			if (m_StereotypePart->MouseRightButtonUp(nFlags, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<AttributePart*>::iterator ii = m_AttributeParts.begin(); ii != m_AttributeParts.end(); ++ii) {
			try {
				if ((*ii)->MouseRightButtonUp(nFlags, point, transformHDC))
					return true;
			}
			catch(hresult_exception& e) {
				retVal = e.hr;
			}
			catch(DecoratorException& e) {
				retVal = e.GetHResult();
			}
			if (retVal != S_OK && retVal != S_DECORATOR_EVENT_NOT_HANDLED && retVal != E_DECORATOR_NOT_IMPLEMENTED)
				break;
		}
	}

	return false;
}

bool ClassComplexPart::MouseRightButtonDoubleClick(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	HRESULT retVal = S_OK;
	try {
		if (VectorPart::MouseRightButtonDoubleClick(nFlags, point, transformHDC))
			return true;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		try {
			if (m_LabelPart->MouseRightButtonDoubleClick(nFlags, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	if (m_StereotypePart != NULL && (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED)) {
		try {
			if (m_StereotypePart->MouseRightButtonDoubleClick(nFlags, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<AttributePart*>::iterator ii = m_AttributeParts.begin(); ii != m_AttributeParts.end(); ++ii) {
			try {
				if ((*ii)->MouseRightButtonDoubleClick(nFlags, point, transformHDC))
					return true;
			}
			catch(hresult_exception& e) {
				retVal = e.hr;
			}
			catch(DecoratorException& e) {
				retVal = e.GetHResult();
			}
			if (retVal != S_OK && retVal != S_DECORATOR_EVENT_NOT_HANDLED && retVal != E_DECORATOR_NOT_IMPLEMENTED)
				break;
		}
	}

	return false;
}

bool ClassComplexPart::MouseMiddleButtonDown(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	HRESULT retVal = S_OK;
	try {
		if (VectorPart::MouseMiddleButtonDown(nFlags, point, transformHDC))
			return true;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		try {
			if (m_LabelPart->MouseMiddleButtonDown(nFlags, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	if (m_StereotypePart != NULL && (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED)) {
		try {
			if (m_StereotypePart->MouseMiddleButtonDown(nFlags, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<AttributePart*>::iterator ii = m_AttributeParts.begin(); ii != m_AttributeParts.end(); ++ii) {
			try {
				if ((*ii)->MouseMiddleButtonDown(nFlags, point, transformHDC))
					return true;
			}
			catch(hresult_exception& e) {
				retVal = e.hr;
			}
			catch(DecoratorException& e) {
				retVal = e.GetHResult();
			}
			if (retVal != S_OK && retVal != S_DECORATOR_EVENT_NOT_HANDLED && retVal != E_DECORATOR_NOT_IMPLEMENTED)
				break;
		}
	}

	return false;
}

bool ClassComplexPart::MouseMiddleButtonUp(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	HRESULT retVal = S_OK;
	try {
		if (VectorPart::MouseMiddleButtonUp(nFlags, point, transformHDC))
			return true;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		try {
			if (m_LabelPart->MouseMiddleButtonUp(nFlags, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	if (m_StereotypePart != NULL && (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED)) {
		try {
			if (m_StereotypePart->MouseMiddleButtonUp(nFlags, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<AttributePart*>::iterator ii = m_AttributeParts.begin(); ii != m_AttributeParts.end(); ++ii) {
			try {
				if ((*ii)->MouseMiddleButtonUp(nFlags, point, transformHDC))
					return true;
			}
			catch(hresult_exception& e) {
				retVal = e.hr;
			}
			catch(DecoratorException& e) {
				retVal = e.GetHResult();
			}
			if (retVal != S_OK && retVal != S_DECORATOR_EVENT_NOT_HANDLED && retVal != E_DECORATOR_NOT_IMPLEMENTED)
				break;
		}
	}

	return false;
}

bool ClassComplexPart::MouseMiddleButtonDoubleClick(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	HRESULT retVal = S_OK;
	try {
		if (VectorPart::MouseMiddleButtonDoubleClick(nFlags, point, transformHDC))
			return true;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		try {
			if (m_LabelPart->MouseMiddleButtonDoubleClick(nFlags, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	if (m_StereotypePart != NULL && (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED)) {
		try {
			if (m_StereotypePart->MouseMiddleButtonDoubleClick(nFlags, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<AttributePart*>::iterator ii = m_AttributeParts.begin(); ii != m_AttributeParts.end(); ++ii) {
			try {
				if ((*ii)->MouseMiddleButtonDoubleClick(nFlags, point, transformHDC))
					return true;
			}
			catch(hresult_exception& e) {
				retVal = e.hr;
			}
			catch(DecoratorException& e) {
				retVal = e.GetHResult();
			}
			if (retVal != S_OK && retVal != S_DECORATOR_EVENT_NOT_HANDLED && retVal != E_DECORATOR_NOT_IMPLEMENTED)
				break;
		}
	}

	return false;
}

bool ClassComplexPart::MouseWheelTurned(UINT nFlags, short distance, const CPoint& point, HDC transformHDC)
{
	HRESULT retVal = S_OK;
	try {
		if (VectorPart::MouseWheelTurned(nFlags, distance, point, transformHDC))
			return true;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		try {
			if (m_LabelPart->MouseWheelTurned(nFlags, distance, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	if (m_StereotypePart != NULL && (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED)) {
		try {
			if (m_StereotypePart->MouseWheelTurned(nFlags, distance, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<AttributePart*>::iterator ii = m_AttributeParts.begin(); ii != m_AttributeParts.end(); ++ii) {
			try {
				if ((*ii)->MouseWheelTurned(nFlags, distance, point, transformHDC))
					return true;
			}
			catch(hresult_exception& e) {
				retVal = e.hr;
			}
			catch(DecoratorException& e) {
				retVal = e.GetHResult();
			}
			if (retVal != S_OK && retVal != S_DECORATOR_EVENT_NOT_HANDLED && retVal != E_DECORATOR_NOT_IMPLEMENTED)
				break;
		}
	}

	return false;
}

bool ClassComplexPart::MenuItemSelected(UINT menuItemId, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	HRESULT retVal = S_OK;
	try {
		if (VectorPart::MenuItemSelected(menuItemId, nFlags, point, transformHDC))
			return true;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		try {
			if (m_LabelPart->MenuItemSelected(menuItemId, nFlags, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	if (m_StereotypePart != NULL && (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED)) {
		try {
			if (m_StereotypePart->MenuItemSelected(menuItemId, nFlags, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<AttributePart*>::iterator ii = m_AttributeParts.begin(); ii != m_AttributeParts.end(); ++ii) {
			try {
				if ((*ii)->MenuItemSelected(menuItemId, nFlags, point, transformHDC))
					return true;
			}
			catch(hresult_exception& e) {
				retVal = e.hr;
			}
			catch(DecoratorException& e) {
				retVal = e.GetHResult();
			}
			if (retVal != S_OK && retVal != S_DECORATOR_EVENT_NOT_HANDLED && retVal != E_DECORATOR_NOT_IMPLEMENTED)
				break;
		}
	}

	return false;
}

bool ClassComplexPart::OperationCanceledByGME(void)
{
	HRESULT retVal = S_OK;
	try {
		if (VectorPart::OperationCanceledByGME())
			return true;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		try {
			if (m_LabelPart->OperationCanceledByGME())
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	if (m_StereotypePart != NULL && (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED)) {
		try {
			if (m_StereotypePart->OperationCanceledByGME())
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<AttributePart*>::iterator ii = m_AttributeParts.begin(); ii != m_AttributeParts.end(); ++ii) {
			try {
				if ((*ii)->OperationCanceledByGME())
					return true;
			}
			catch(hresult_exception& e) {
				retVal = e.hr;
			}
			catch(DecoratorException& e) {
				retVal = e.GetHResult();
			}
			if (retVal != S_OK && retVal != S_DECORATOR_EVENT_NOT_HANDLED && retVal != E_DECORATOR_NOT_IMPLEMENTED)
				break;
		}
	}

	return false;
}

void ClassComplexPart::CollectAttributes(CComPtr<IMgaFCO> mgaFco)
{
}

void ClassComplexPart::CalcRelPositions(CDC *pDC)
{
}

void ClassComplexPart::SetBoxLocation(const CRect& cRect)
{
/*	TypeableBitmapPart::SetBoxLocation(cRect);
	long lY = (m_Rect.Height() - m_LeftPorts.size() * (HEIGHT_PORT + GAP_PORT) + GAP_PORT) / 2;

	for (std::vector<PortPart*>::iterator ii = m_LeftPorts.begin(); ii != m_LeftPorts.end(); ++ii) {
		(*ii)->SetBoxLocation(CRect(GAP_XMODELPORT, lY, GAP_XMODELPORT + WIDTH_PORT, lY + HEIGHT_PORT));
		lY += HEIGHT_PORT + GAP_PORT;
	}
	lY = (m_Rect.Height() - m_RightPorts.size() * (HEIGHT_PORT + GAP_PORT) + GAP_PORT) / 2;
	for (std::vector<PortPart*>::iterator ii = m_RightPorts.begin(); ii != m_RightPorts.end(); ++ii) {
		(*ii)->SetBoxLocation(CRect(cRect.Width() - GAP_XMODELPORT - WIDTH_PORT, lY, cRect.Width() - GAP_XMODELPORT, lY + HEIGHT_PORT));
		lY += HEIGHT_PORT + GAP_PORT;
	}*/
}

void ClassComplexPart::SetReferenced(bool referenced)
{
	m_LabelPart->SetReferenced(referenced);
	if (m_StereotypePart != NULL)
		m_StereotypePart->SetReferenced(referenced);
	for (std::vector<AttributePart*>::iterator ii = m_AttributeParts.begin(); ii != m_AttributeParts.end(); ++ii) {
		(*ii)->SetReferenced(referenced);
	}
	VectorPart::SetReferenced(referenced);
}

void ClassComplexPart::SetParentPart(PartBase* pPart)
{
	m_LabelPart->SetParentPart(pPart);
	if (m_StereotypePart != NULL)
		m_StereotypePart->SetParentPart(pPart);
	for (std::vector<AttributePart*>::iterator ii = m_AttributeParts.begin(); ii != m_AttributeParts.end(); ++ii) {
		(*ii)->SetParentPart(pPart);
	}
	VectorPart::SetParentPart(pPart);
}

}; // namespace DecoratorSDK
