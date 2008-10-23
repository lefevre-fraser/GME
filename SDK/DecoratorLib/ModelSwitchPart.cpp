//################################################################################################
//
// Model switch part class (decorator part)
//	ModelSwitchPart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "ModelSwitchPart.h"
#include "DecoratorExceptions.h"
#include <algorithm>


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : ModelSwitchPart
//
//################################################################################################

ModelSwitchPart::ModelSwitchPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink):
	CompositePart				(pPart, eventSink)
{
}

ModelSwitchPart::~ModelSwitchPart()
{
}

void ModelSwitchPart::Initialize(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO)
{
	for (std::vector<PortPart*>::iterator ii = m_LeftPorts.begin(); ii != m_LeftPorts.end(); ++ii) {
		(*ii)->Initialize(pProject, pPart, pFCO);
	}
	for (std::vector<PortPart*>::iterator ii = m_RightPorts.begin(); ii != m_RightPorts.end(); ++ii) {
		(*ii)->Initialize(pProject, pPart, pFCO);
	}
	if (m_expandPart != NULL)
		m_expandPart->Initialize(pProject, pPart, pFCO);
	TypeableBitmapPart::Initialize(pProject, pPart, pFCO);
}

void ModelSwitchPart::Destroy()
{
	for (std::vector<PortPart*>::iterator ii = m_LeftPorts.begin(); ii != m_LeftPorts.end(); ++ii) {
		(*ii)->Destroy();
	}
	for (std::vector<PortPart*>::iterator ii = m_RightPorts.begin(); ii != m_RightPorts.end(); ++ii) {
		(*ii)->Destroy();
	}
	if (m_expandPart != NULL)
		m_expandPart->Destroy();
	TypeableBitmapPart::Destroy();
}

CString ModelSwitchPart::GetMnemonic(void) const
{
	return TypeableBitmapPart::GetMnemonic();
}

feature_code ModelSwitchPart::GetFeatures(void) const
{
	feature_code featureCodes = 0;

	for (std::vector<PortPart*>::const_iterator ii = m_LeftPorts.begin(); ii != m_LeftPorts.end(); ++ii) {
		feature_code portFeatureCodes = (*ii)->GetFeatures();
		featureCodes |= portFeatureCodes;
	}
	for (std::vector<PortPart*>::const_iterator ii = m_RightPorts.begin(); ii != m_RightPorts.end(); ++ii) {
		feature_code portFeatureCodes = (*ii)->GetFeatures();
		featureCodes |= portFeatureCodes;
	}

	feature_code partFeatureCodes = TypeableBitmapPart::GetFeatures();
	featureCodes |= partFeatureCodes;

	return featureCodes;
}

void ModelSwitchPart::SetParam(const CString& strName, VARIANT vValue)
{
	for (std::vector<PortPart*>::iterator ii = m_LeftPorts.begin(); ii != m_LeftPorts.end(); ++ii) {
		(*ii)->SetParam(strName, vValue);
	}
	for (std::vector<PortPart*>::iterator ii = m_RightPorts.begin(); ii != m_RightPorts.end(); ++ii) {
		(*ii)->SetParam(strName, vValue);
	}
	if (m_expandPart != NULL)
		m_expandPart->SetParam(strName, vValue);
	TypeableBitmapPart::SetParam(strName, vValue);
}

bool ModelSwitchPart::GetParam(const CString& strName, VARIANT* pvValue)
{
	try {
		if (TypeableBitmapPart::GetParam(strName, pvValue))
			return true;
	}
	catch(UnknownParameterException&) {
	}
	return false;
}

void ModelSwitchPart::SetActive(bool bIsActive)
{
	TypeableBitmapPart::SetActive(bIsActive);
}

CSize ModelSwitchPart::GetPreferredSize(void) const
{
	CSize size = ResizablePart::GetPreferredSize();
	if (size.cx * size.cy != 0)
		return size;

	if (m_LeftPorts.empty() && m_RightPorts.empty()) {
		if (!m_pBitmap || m_pBitmap->getName() == createResString(IDB_MODEL)) {
			return CSize(WIDTH_MODEL, HEIGHT_MODEL);
		} else {
			return TypeableBitmapPart::GetPreferredSize();
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

	return CSize(max((long) WIDTH_MODEL, lWidth), max((long) HEIGHT_MODEL, lHeight));
}

void ModelSwitchPart::SetLocation(const CRect& location)
{
	for (std::vector<PortPart*>::iterator ii = m_LeftPorts.begin(); ii != m_LeftPorts.end(); ++ii) {
		(*ii)->SetLocation(location);
	}
	for (std::vector<PortPart*>::iterator ii = m_RightPorts.begin(); ii != m_RightPorts.end(); ++ii) {
		(*ii)->SetLocation(location);
	}
	TypeableBitmapPart::SetLocation(location);
}

CRect ModelSwitchPart::GetLocation(void) const
{
	return TypeableBitmapPart::GetLocation();
}

CRect ModelSwitchPart::GetLabelLocation(void) const
{
	CRect labelLocation;
	try {
		labelLocation = TypeableBitmapPart::GetLabelLocation();
	}
	catch(NotImplementedException&) {
		for (std::vector<PortPart*>::const_iterator ii = m_LeftPorts.begin(); ii != m_LeftPorts.end(); ++ii) {
			labelLocation = (*ii)->GetLabelLocation();
			if (!labelLocation.IsRectEmpty())
				break;
		}
		if (labelLocation.IsRectEmpty()) {
			for (std::vector<PortPart*>::const_iterator ii = m_RightPorts.begin(); ii != m_RightPorts.end(); ++ii) {
				labelLocation = (*ii)->GetLabelLocation();
				if (!labelLocation.IsRectEmpty())
					break;
			}
		}
	}
	return labelLocation;
}

void ModelSwitchPart::Draw(CDC* pDC)
{
	TypeableBitmapPart::Draw(pDC);
	if (m_expandPart != NULL)
		m_expandPart->Draw(pDC);
}

void ModelSwitchPart::SaveState()
{
	for (std::vector<PortPart*>::iterator ii = m_LeftPorts.begin(); ii != m_LeftPorts.end(); ++ii) {
		(*ii)->SaveState();
	}
	for (std::vector<PortPart*>::iterator ii = m_RightPorts.begin(); ii != m_RightPorts.end(); ++ii) {
		(*ii)->SaveState();
	}
	if (m_expandPart != NULL)
		m_expandPart->SaveState();
	TypeableBitmapPart::SaveState();
}

// New functions
void ModelSwitchPart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
									HWND parentWnd, PreferenceMap& preferences)
{
	preferences[PREF_ICONDEFAULT]	= PreferenceVariant(createResString(IDB_MODEL));
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

		LoadPorts();

		{
			preferences[PREF_ISMASKEDBITMAP]	= PreferenceVariant(true);
			preferences[PREF_ITEMRESIZABLE]		= PreferenceVariant(false);

			preferences[PREF_ICONDEFAULT]		= PreferenceVariant(createResString(IDB_ATOM));
			preferences[PREF_TILESDEFAULT]		= PreferenceVariant(getFacilities().getTileVector(TILE_ATOMDEFAULT));
			preferences[PREF_TILESUNDEF]		= PreferenceVariant(getFacilities().getTileVector(TILE_ATOMDEFAULT));
			preferences[PREF_TILES]				= PreferenceVariant(getFacilities().getTileVector(TILE_ATOMDEFAULT));

			preferences[PREF_ICON]				= PreferenceVariant((long)IDB_EXPAND_SIGN);
			preferences[PREF_TRANSPARENTCOLOR]	= PreferenceVariant(COLOR_TRANSPARENT);
			preferences[PREF_GRAYEDOUTCOLOR]	= PreferenceVariant(COLOR_GRAYED_OUT);

			m_expandPart = new BitmapPart(this, m_eventSink);
			m_expandPart->InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);
			preferences[PREF_ITEMRESIZABLE]		= PreferenceVariant(true);
		}
	} else {
		TypeableBitmapPart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);
	}

	if (m_LeftPorts.empty() && m_RightPorts.empty())
		m_pTileVector = getFacilities().getTileVector(TILE_ATOMDEFAULT);
}

void ModelSwitchPart::SetSelected(bool bIsSelected)
{
	for (std::vector<PortPart*>::iterator ii = m_LeftPorts.begin(); ii != m_LeftPorts.end(); ++ii) {
		(*ii)->SetSelected(bIsSelected);
	}
	for (std::vector<PortPart*>::iterator ii = m_RightPorts.begin(); ii != m_RightPorts.end(); ++ii) {
		(*ii)->SetSelected(bIsSelected);
	}
	if (m_expandPart != NULL)
		m_expandPart->SetSelected(bIsSelected);
	TypeableBitmapPart::SetSelected(bIsSelected);
}

bool ModelSwitchPart::MouseMoved(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	HRESULT retVal = S_OK;
	if (m_expandPart != NULL && (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED)) {
		try {
			if (m_expandPart->MouseMoved(nFlags, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	try {
		if (TypeableBitmapPart::MouseMoved(nFlags, point, transformHDC))
			return true;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<PortPart*>::iterator ii = m_LeftPorts.begin(); ii != m_LeftPorts.end(); ++ii) {
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
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<PortPart*>::iterator ii = m_RightPorts.begin(); ii != m_RightPorts.end(); ++ii) {
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

bool ModelSwitchPart::MouseLeftButtonDown(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	HRESULT retVal = S_OK;
	if (m_expandPart != NULL && (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED)) {
		try {
			if (m_expandPart->MouseLeftButtonDown(nFlags, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	try {
		if (TypeableBitmapPart::MouseLeftButtonDown(nFlags, point, transformHDC))
			return true;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<PortPart*>::iterator ii = m_LeftPorts.begin(); ii != m_LeftPorts.end(); ++ii) {
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
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<PortPart*>::iterator ii = m_RightPorts.begin(); ii != m_RightPorts.end(); ++ii) {
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

bool ModelSwitchPart::MouseLeftButtonUp(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	HRESULT retVal = S_OK;
	if (m_expandPart != NULL && (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED)) {
		try {
			if (m_expandPart->MouseLeftButtonUp(nFlags, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	try {
		if (TypeableBitmapPart::MouseLeftButtonUp(nFlags, point, transformHDC))
			return true;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<PortPart*>::iterator ii = m_LeftPorts.begin(); ii != m_LeftPorts.end(); ++ii) {
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
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<PortPart*>::iterator ii = m_RightPorts.begin(); ii != m_RightPorts.end(); ++ii) {
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

bool ModelSwitchPart::MouseLeftButtonDoubleClick(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	HRESULT retVal = S_OK;
	if (m_expandPart != NULL && (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED)) {
		try {
			if (m_expandPart->MouseLeftButtonDoubleClick(nFlags, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	try {
		if (TypeableBitmapPart::MouseLeftButtonDoubleClick(nFlags, point, transformHDC))
			return true;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<PortPart*>::iterator ii = m_LeftPorts.begin(); ii != m_LeftPorts.end(); ++ii) {
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
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<PortPart*>::iterator ii = m_RightPorts.begin(); ii != m_RightPorts.end(); ++ii) {
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

bool ModelSwitchPart::MouseRightButtonDown(HMENU hCtxMenu, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	HRESULT retVal = S_OK;
	if (m_expandPart != NULL && (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED)) {
		try {
			if (m_expandPart->MouseRightButtonDown(hCtxMenu, nFlags, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	try {
		if (TypeableBitmapPart::MouseRightButtonDown(hCtxMenu, nFlags, point, transformHDC))
			return true;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<PortPart*>::iterator ii = m_LeftPorts.begin(); ii != m_LeftPorts.end(); ++ii) {
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
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<PortPart*>::iterator ii = m_RightPorts.begin(); ii != m_RightPorts.end(); ++ii) {
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

bool ModelSwitchPart::MouseRightButtonUp(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	HRESULT retVal = S_OK;
	if (m_expandPart != NULL && (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED)) {
		try {
			if (m_expandPart->MouseRightButtonUp(nFlags, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	try {
		if (TypeableBitmapPart::MouseRightButtonUp(nFlags, point, transformHDC))
			return true;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<PortPart*>::iterator ii = m_LeftPorts.begin(); ii != m_LeftPorts.end(); ++ii) {
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
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<PortPart*>::iterator ii = m_RightPorts.begin(); ii != m_RightPorts.end(); ++ii) {
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

bool ModelSwitchPart::MouseRightButtonDoubleClick(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	HRESULT retVal = S_OK;
	if (m_expandPart != NULL && (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED)) {
		try {
			if (m_expandPart->MouseRightButtonDoubleClick(nFlags, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	try {
		if (TypeableBitmapPart::MouseRightButtonDoubleClick(nFlags, point, transformHDC))
			return true;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<PortPart*>::iterator ii = m_LeftPorts.begin(); ii != m_LeftPorts.end(); ++ii) {
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
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<PortPart*>::iterator ii = m_RightPorts.begin(); ii != m_RightPorts.end(); ++ii) {
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

bool ModelSwitchPart::MenuItemSelected(UINT menuItemId, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	HRESULT retVal = S_OK;
	if (m_expandPart != NULL && (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED)) {
		try {
			if (m_expandPart->MenuItemSelected(menuItemId, nFlags, point, transformHDC))
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	try {
		if (TypeableBitmapPart::MenuItemSelected(menuItemId, nFlags, point, transformHDC))
			return true;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<PortPart*>::iterator ii = m_LeftPorts.begin(); ii != m_LeftPorts.end(); ++ii) {
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
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<PortPart*>::iterator ii = m_RightPorts.begin(); ii != m_RightPorts.end(); ++ii) {
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

bool ModelSwitchPart::OperationCanceledByGME(void)
{
	HRESULT retVal = S_OK;
	try {
		if (TypeableBitmapPart::OperationCanceledByGME())
			return true;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<PortPart*>::iterator ii = m_LeftPorts.begin(); ii != m_LeftPorts.end(); ++ii) {
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
	if (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED) {
		for (std::vector<PortPart*>::iterator ii = m_RightPorts.begin(); ii != m_RightPorts.end(); ++ii) {
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
	if (m_expandPart != NULL && (retVal == S_OK || retVal == S_DECORATOR_EVENT_NOT_HANDLED || retVal == E_DECORATOR_NOT_IMPLEMENTED)) {
		try {
			if (m_expandPart->OperationCanceledByGME())
				return true;
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}

	return false;
}

void ModelSwitchPart::DrawBackground(CDC* pDC)
{
	CSize cExtentD = pDC->GetViewportExt();
	CSize cExtentL = pDC->GetWindowExt();
	CRect cRect = TypeableBitmapPart::GetBoxLocation(false);
	cRect.BottomRight() -= CPoint(1, 1);

#ifndef OLD_DECORATOR_LOOKANDFEEL
	TypeableBitmapPart::DrawBackground(pDC);
#else
	if (m_pBitmap->getName() != createResString(IDB_MODEL) && TypeableBitmapPart::m_bActive) {
		TypeableBitmapPart::DrawBackground(pDC);
	} else {
		int iDepth = (m_bReferenced) ? 2 : ((m_iTypeInfo == 3) ? 4 : 7);
		getFacilities().drawBox(pDC, cRect, (!m_bActive) ? COLOR_LIGHTGRAY : (m_bOverlay) ? m_crOverlay : COLOR_GRAY, iDepth);
		CRect cRect2 = cRect;
		cRect2.InflateRect(1, 1);
		getFacilities().drawRect(pDC, cRect2, (m_bActive) ? m_crBorder : COLOR_GRAY);
		/* Commented out // inner border for Types, and Referenced models // Requested by Akos
		if (m_iTypeInfo != 3 || m_bReferenced) {
			cRect2 = cRect;
			cRect2.DeflateRect(iDepth, iDepth);
			getFacilities().drawRect(pDC, cRect2, (m_bActive) ? m_crBorder : COLOR_GRAY);
		}
		*/
	}
#endif

	cRect.BottomRight() += CPoint(1, 1);
	CPoint ptOrigin = pDC->OffsetViewportOrg((long) (cRect.left * ((double) cExtentD.cx / cExtentL.cx)), (long) (cRect.top * ((double) cExtentD.cy / cExtentL.cy)));
	for (std::vector<PortPart*>::iterator ii = m_LeftPorts.begin(); ii != m_LeftPorts.end(); ++ii) {
		(*ii)->Draw(pDC);
	}
	for (std::vector<PortPart*>::iterator ii = m_RightPorts.begin(); ii != m_RightPorts.end(); ++ii) {
		(*ii)->Draw(pDC);
	}
	pDC->SetViewportOrg(ptOrigin);
}

void ModelSwitchPart::SetBoxLocation(const CRect& cRect)
{
	TypeableBitmapPart::SetBoxLocation(cRect);
	long lY = (m_Rect.Height() - m_LeftPorts.size() * (HEIGHT_PORT + GAP_PORT) + GAP_PORT) / 2;

	for (std::vector<PortPart*>::iterator ii = m_LeftPorts.begin(); ii != m_LeftPorts.end(); ++ii) {
		(*ii)->SetBoxLocation(CRect(GAP_XMODELPORT, lY, GAP_XMODELPORT + WIDTH_PORT, lY + HEIGHT_PORT));
		lY += HEIGHT_PORT + GAP_PORT;
	}
	lY = (m_Rect.Height() - m_RightPorts.size() * (HEIGHT_PORT + GAP_PORT) + GAP_PORT) / 2;
	for (std::vector<PortPart*>::iterator ii = m_RightPorts.begin(); ii != m_RightPorts.end(); ++ii) {
		(*ii)->SetBoxLocation(CRect(cRect.Width() - GAP_XMODELPORT - WIDTH_PORT, lY, cRect.Width() - GAP_XMODELPORT, lY + HEIGHT_PORT));
		lY += HEIGHT_PORT + GAP_PORT;
	}
	if (m_expandPart != NULL) {
		CSize iconSize = m_expandPart->GetPreferredSize();
		CPoint pos = CPoint(cRect.left + (cRect.right - cRect.left) / 2, cRect.top - iconSize.cy / 2);
		m_expandPart->SetLocation(CRect(pos, iconSize));
	}
}

void ModelSwitchPart::SetReferenced(bool referenced)
{
	for (std::vector<PortPart*>::iterator ii = m_LeftPorts.begin(); ii != m_LeftPorts.end(); ++ii) {
		(*ii)->SetReferenced(referenced);
	}
	for (std::vector<PortPart*>::iterator ii = m_RightPorts.begin(); ii != m_RightPorts.end(); ++ii) {
		(*ii)->SetReferenced(referenced);
	}
	if (m_expandPart != NULL)
		m_expandPart->SetReferenced(referenced);
	TypeableBitmapPart::SetReferenced(referenced);
}

void ModelSwitchPart::SetParentPart(PartBase* pPart)
{
	for (std::vector<PortPart*>::iterator ii = m_LeftPorts.begin(); ii != m_LeftPorts.end(); ++ii) {
		(*ii)->SetParentPart(pPart);
	}
	for (std::vector<PortPart*>::iterator ii = m_RightPorts.begin(); ii != m_RightPorts.end(); ++ii) {
		(*ii)->SetParentPart(pPart);
	}
	if (m_expandPart != NULL)
		m_expandPart->SetParentPart(pPart);
	TypeableBitmapPart::SetParentPart(pPart);
}

std::vector<PortPart*> ModelSwitchPart::GetPorts()
{
	std::vector<PortPart*> vecPorts(m_LeftPorts);
	for (std::vector<PortPart*>::iterator ii = m_RightPorts.begin(); ii != m_RightPorts.end(); ++ii) {
		vecPorts.push_back(*ii);
	}
	return vecPorts;
}

PortPart* ModelSwitchPart::GetPort(CComPtr<IMgaFCO> spFCO)
{
	for (std::vector<PortPart*>::iterator ii = m_LeftPorts.begin(); ii != m_LeftPorts.end(); ++ii) {
		if (spFCO == (*ii)->GetFCO()) {
			return (*ii);
		}
	}
	for (std::vector<PortPart*>::iterator ii = m_RightPorts.begin(); ii != m_RightPorts.end(); ++ii) {
		if (spFCO == (*ii)->GetFCO()) {
			return (*ii);
		}
	}
	return NULL;
}

}; // namespace DecoratorSDK
