//################################################################################################
//
// Text part class (decorator part)
//	TextPart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "TextPart.h"
#include "PortLabelPart.h"
#include "DecoratorExceptions.h"
#include "InPlaceEditSingleLineDialog.h"
#include "InPlaceEditMultiLineDialog.h"
//#include "InPlaceNativeDialog.h"

namespace DecoratorSDK {

//################################################################################################
//
// CLASS : TextPart
//
//################################################################################################

TextPart::TextPart(PartBase* pPart, CComPtr<IMgaCommonDecoratorEvents>& eventSink):
	PartBase			(pPart, eventSink),
	resizeLogic			(NULL),
	m_bCursorSaved		(false),
	m_eTextLocation		(L_SOUTH),
	m_bTextEnabled		(true),	// ?
	m_bTextEditable		(true),
	m_iTextWrapCount	(0),
	m_crText			(COLOR_BLACK),
	m_iFontKey			(FONT_LABEL),
	m_iMaxTextLength	(MAX_LABEL_LENGTH),
	m_bMultiLine		(false)
{
	resizeLogic.SetParentPart(this);
}

TextPart::~TextPart()
{
}

void TextPart::Initialize(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO)
{
	if (m_spFCO)
		resizeLogic.SetResizeFeatures(ResizeLogic::Resizeable | /* TODO: temp ResizeLogic::Movable |*/ ResizeLogic::DrawSelectionRectangle);

	PartBase::Initialize(pProject, pPart, pFCO);
}

void TextPart::Destroy(void)
{
	OperationCanceledByGME();
	if (m_spFCO)
		resizeLogic.Destroy();
}

feature_code TextPart::GetFeatures(void) const
{
	return m_bTextEditable ? F_MOUSEEVENTS : 0 | F_HASLABEL;
}

CSize TextPart::GetPreferredSize(void) const
{
	return CSize(0, 0);
}

CRect TextPart::GetLabelLocation(void) const
{
	return GetTextLocation();
}

// New functions
void TextPart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
							HWND parentWnd, PreferenceMap& preferences)
{
	// Check if editability is disabled/enabled
	PreferenceMap::iterator it = preferences.find(PREF_ITEMEDITABLE);
	if (it != preferences.end())
		m_bTextEditable = it->second.uValue.bValue;

	it = preferences.find(PREF_MULTILINEINPLACEEDIT);
	if (it != preferences.end())
		m_bMultiLine = it->second.uValue.bValue;

	if (m_spFCO)
		resizeLogic.InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);
	PartBase::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);

	// Get Text
	it = preferences.find(DecoratorSDK::PREF_TEXTOVERRIDE);
	if (it == preferences.end()) {
		it = preferences.find(textStringVariableName);
		bool bTextDefined = (it != preferences.end());
		if (bTextDefined)
			m_strText = *it->second.uValue.pstrValue;

		CComBSTR bstrText;
		CComPtr<IMgaMetaFCO> spMetaFCO;
		if (!m_spFCO) {
			if (m_spPart) {
				CComPtr<IMgaMetaRole> spRole;
				COMTHROW(m_spPart->get_Role(&spRole));
				COMTHROW(spRole->get_Kind(&spMetaFCO));

				if (!bTextDefined) {
					COMTHROW(spMetaFCO->get_DisplayedName(&bstrText));
					if (bstrText.Length() == 0) {
						bstrText.Empty();
						COMTHROW(spRole->get_DisplayedName(&bstrText));
					}
					if (bstrText.Length() == 0) {
						bstrText.Empty();
						COMTHROW(spMetaFCO->get_Name(&bstrText));
					}
				}
			}
		} else {
			if (!bTextDefined)
				COMTHROW(m_spFCO->get_Name(&bstrText));
		}
		if (!bTextDefined)
			CopyTo(bstrText, m_strText);
		if (m_strText == "Condition") {
			m_strText = "Condition";
		}
	}

	// Text's Font
	m_iFontKey = FONT_LABEL;
	it = preferences.find(textFontVariableName);
	if (it != preferences.end())
		m_iFontKey = it->second.uValue.lValue;

	// Text's Max Length
	m_iMaxTextLength = MAX_LABEL_LENGTH;
	it = preferences.find(textMaxLengthVariableName);
	if (it != preferences.end())
		m_iMaxTextLength = it->second.uValue.lValue;

	// Text's Color
	it = preferences.find(DecoratorSDK::PREF_TEXTCOLOROVERRIDE);
	if (it == preferences.end()) {
		m_crText = COLOR_BLACK;
		it = preferences.find(textColorVariableName);
		if (it != preferences.end()) {
			m_crText = it->second.uValue.crValue;
		} else {
			if (m_spFCO)
				getFacilities().getPreference(m_spFCO, textColorVariableName, m_crText);
		}
	}

	// Text's Location
	m_eTextLocation = L_SOUTH;
	it = preferences.find(textLocationVariableName);
	if (it != preferences.end()) {
		m_eTextLocation = it->second.uValue.eLocation;
	} else {
		if (m_spFCO)
			getFacilities().getPreference(m_spFCO, textLocationVariableName, m_eTextLocation);
	}

	// Text's Enabled
	if (m_spFCO) {
		if (!getFacilities().getPreference(m_spFCO, textStatusVariableName, m_bTextEnabled))
			m_bTextEnabled = true;
	} else {
		m_bTextEnabled = true;
	}

	// Text's Wrap
	if (m_spFCO) {
		if (getFacilities().getPreference(m_spFCO, textWrapStatusVariableName, m_iTextWrapCount)) {
			m_iTextWrapCount = max(m_iTextWrapCount, 0L);
		} else {
			m_iTextWrapCount = 0;
		}
	} else {
		m_iTextWrapCount = 0;
	}

	m_vecText = getFacilities().wrapString(m_strText, m_iTextWrapCount, m_iMaxTextLength);
}

bool TextPart::MouseMoved(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	if (m_bActive && m_bSelected && m_bTextEditable) {
		CRect ptRect = GetTextLocation();
		CRect ptRectInflated = ptRect;
		ptRectInflated.InflateRect(3, 3);
		if (ptRect.PtInRect(point)) {
			HCURSOR wantedCursor = LoadCursor(NULL, IDC_IBEAM);
			m_originalCursor = SetCursor(wantedCursor);
			CursorChanged((long)IDC_IBEAM);
			m_bCursorSaved = true;
			return true;
		} else {
			if (m_bCursorSaved) {
				SetCursor(m_originalCursor);
				m_bCursorSaved = false;
				CursorRestored();
			}
		}
	} else {
		if (m_bCursorSaved) {
			SetCursor(m_originalCursor);
			m_bCursorSaved = false;
			CursorRestored();
		}
	}

	return false;
}

bool TextPart::MouseLeftButtonDown(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return HandleTextEditOperation(false, point, transformHDC);
}

bool TextPart::MouseLeftButtonDoubleClick(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return HandleTextEditOperation(true, point, transformHDC);
}

bool TextPart::MouseRightButtonDown(HMENU hCtxMenu, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	if (m_bActive && m_bSelected && m_bTextEditable) {
		CRect ptRect = GetTextLocation();
		CRect ptRectInflated = ptRect;
		ptRectInflated.InflateRect(3, 3);
		if (ptRectInflated.PtInRect(point)) {
			::AppendMenu(hCtxMenu, MF_STRING | MF_ENABLED, CTX_MENU_ID_RENAME, CTX_MENU_STR_RENAME);
			return true;
		}
	}

	return false;
}

bool TextPart::MenuItemSelected(UINT menuItemId, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	if (menuItemId == CTX_MENU_ID_RENAME)	// simulate left click -> starting text editing action
		return MouseLeftButtonDown(nFlags, point, transformHDC);

	return false;
}

bool TextPart::OperationCanceledByGME(void)
{
	// destroy inplace edit window and stuff if needed
	// can't happen currently because of Modal dialog style
	if (m_spFCO)
		return resizeLogic.OperationCanceledByGME();

	return false;
}

long TextPart::GetLongest(void) const
{
	long maxv = 0;
	for (unsigned int i = 0; i < m_vecText.size(); i++) {
		long ilen = m_vecText[i].GetLength();
		if (m_iMaxTextLength > 0)
			ilen = min(ilen, m_iMaxTextLength);
		if (maxv < ilen)
			maxv = ilen;
	}
	return maxv;
}

CRect TextPart::GetTextLocation(void) const
{
	CRect txtLoc;

	txtLoc = GetTextLocation(getFacilities().getCDC(), getFacilities().getGraphics());

	return txtLoc;
}

bool TextPart::HandleTextEditOperation(bool isDoubleClick, const CPoint& point, HDC transformHDC)
{
	if (m_bActive && (m_bSelected || isDoubleClick) && m_bTextEditable) {
		CRect ptRect = GetTextLocation();
		CRect ptRectInflated = ptRect;
		ptRectInflated.InflateRect(3, 3);
		if (!ptRectInflated.PtInRect(point))
			return false;

		bool isPermanentCWnd = true;
		CWnd* cWnd = CWnd::FromHandlePermanent(m_parentWnd);
		if (cWnd == NULL) {
			isPermanentCWnd = false;
			cWnd = CWnd::FromHandle(m_parentWnd);
		}

		CDC dc;
		dc.Attach(transformHDC);
		// font scaling
		Gdiplus::Font* originalFont = getFacilities().GetFont(m_iFontKey)->gdipFont;
		LOGFONT lf;
		originalFont->GetLogFontA(getFacilities().getGraphics(), &lf);
		CSize windowExt = dc.GetWindowExt();
		CSize viewPortExt = dc.GetViewportExt();
		ASSERT(viewPortExt.cx / windowExt.cx == viewPortExt.cy / windowExt.cy);
		double zoom = (double)viewPortExt.cx / (double)windowExt.cx;
		lf.lfHeight = (long)(lf.lfHeight * zoom);
		CFont* scaled_font = new CFont();
		scaled_font->CreateFontIndirect(&lf);
		// end font scaling
		dc.SelectObject(scaled_font);
		// Do scaling and offset because of possible zoom and horizontal/vertical scrolling

		CSize cSize;
		if (!m_bMultiLine) {
			cSize = dc.GetTextExtent(m_strText);
		} else {
			// Determine Text Width and Height
			CSize oSize;
			// Determine the line Height
			oSize = dc.GetTextExtent(CString(_T(" ")));
			cSize.cy = oSize.cy;
			// Text Width
			cSize.cx = 0;
			CString oStr;
			int i = 0;
			// Parse the string; the lines in a multiline Edit are separated by "\r\n"
			for(i = 0; TRUE == ::AfxExtractSubString(oStr, m_strText, i, _T('\n')); i++) {
				int iLen = oStr.GetLength() - 1;
				if (iLen >= 0) {
					// Eliminate last '\r'
					if (_T('\r') == oStr.GetAt(iLen))
						oStr = oStr.Left(iLen);
					oSize = dc.GetTextExtent(oStr);
					if (cSize.cx < oSize.cx)
						cSize.cx = oSize.cx;
				}
			}
			// Text Height
			cSize.cy *= i;
		}

		POINT editLeftTopPt = { ptRect.left, ptRect.top };
		BOOL success = ::LPtoDP(transformHDC, &editLeftTopPt, 1);
		CRect editLocation(editLeftTopPt, cSize);

		CInPlaceEditDialog* inPlaceEditDlg = NULL;
		if (m_bMultiLine)
			inPlaceEditDlg = new CInPlaceEditMultiLineDialog(cWnd);
		else
			inPlaceEditDlg = new CInPlaceEditSingleLineDialog(cWnd);

		bool inflateToRight = true;
		PortLabelPart* portLabelPart = dynamic_cast_PortLabelPart();
		if (portLabelPart != NULL)
			if (portLabelPart->GetLocationAdjust() == L_WEST)
				inflateToRight = false;
		CPoint screenPt = point;
		cWnd->ClientToScreen(&screenPt);
		inPlaceEditDlg->SetProperties(m_strText, this, editLocation, screenPt, m_parentWnd, cWnd, scaled_font,
									  isPermanentCWnd, inflateToRight);
		inPlaceEditDlg->Create(m_bMultiLine ? IDD_INPLACEEDITMLDIALOG : IDD_INPLACEEDITSLDIALOG, cWnd);
		inPlaceEditDlg->ShowWindow(SW_SHOWNORMAL);

		return true;
	}

	return false;
}

}; // namespace DecoratorSDK
