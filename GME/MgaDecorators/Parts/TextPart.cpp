//################################################################################################
//
// Text part class (decorator part)
//	TextPart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "TextPart.h"
#include "../DecoratorExceptions.h"
#include "InPlaceEditDialog.h"


namespace Decorator {

//################################################################################################
//
// CLASS : TextPart
//
//################################################################################################

TextPart::TextPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink):
	PartBase(pPart, eventSink),
	resizeLogic(NULL)
{
	if (m_spFCO)
		resizeLogic.SetParentPart(this);
}

TextPart::~TextPart()
{
}

void TextPart::Initialize(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO)
{
	// TODO: initialize text location somehow
	textPosition.SetRectEmpty();
	if (m_spFCO)
		resizeLogic.SetResizeFeatures(ResizeLogic::Resizeable | /* TODO: temp ResizeLogic::Movable |*/ ResizeLogic::DrawSelectionRectangle);

	PartBase::Initialize(pProject, pPart, pFCO);
}

void TextPart::Destroy(void)
{
	if (m_spFCO)
		resizeLogic.Destroy();
	OperationCanceledByGME();
}

feature_code TextPart::GetFeatures(void) const
{
	return F_RESIZABLE | F_MOUSEEVENTS | F_HASLABEL;
}

CSize TextPart::GetPreferredSize(void) const
{
	return CSize(0, 0);
}

void TextPart::Draw(CDC* pDC)
{
	if (m_bTextEnabled) {
		ECoordRefPoint eAlign = GetAlignment(m_eTextLocation);
		int iAlign = 0;
		switch (eAlign) {
			case CRP_BEGIN:		iAlign = TA_LEFT;	break;
			case CRP_CENTER:	iAlign = TA_CENTER;	break;
			case CRP_END:
			default:			iAlign = TA_RIGHT;	break;
		}
		iAlign |= TA_TOP;

		int iLabelSize = getFacilities().getFont(m_iFontKey)->iSize;
		CPoint pt = GetTextPosition();
		for (unsigned int i = 0; i < m_vecText.size(); i++)
			getFacilities().drawText(pDC,
									 m_vecText[i],
									 CPoint(pt.x, pt.y + i * iLabelSize),
									 getFacilities().getFont(m_iFontKey)->pFont,
									 (m_bActive) ? m_crText : COLOR_GRAY,
									 iAlign,
									 m_iMaxTextLength,
									 "",
									 "",
									 false);
	}
	if (m_spFCO)
		resizeLogic.Draw(pDC);
}

// New functions
void TextPart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
							HWND parentWnd, PreferenceMap& preferences)
{
	if (m_spFCO)
		resizeLogic.InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);
	PartBase::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);

	// Get Text
	PreferenceMap::iterator it = preferences.find(textStringVariableName);
	bool bTextDefined = it != preferences.end();
	if (bTextDefined)
		m_strText = *it->second.uValue.pstrValue;

	CComBSTR bstrText;
	CComPtr<IMgaMetaFCO> spMetaFCO;
	if (!m_spFCO) {
		CComPtr<IMgaMetaRole> spRole;
		COMTHROW(m_spPart->get_Role(&spRole));
		COMTHROW(spRole->get_Kind(&spMetaFCO));

		if (!bTextDefined) {
			COMTHROW(spRole->get_DisplayedName(&bstrText));
			if (bstrText.Length() == 0) {
				bstrText.Empty();
				COMTHROW(spMetaFCO->get_Name(&bstrText));
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
	m_crText = COLOR_BLACK;
	it = preferences.find(textColorVariableName);
	if (it != preferences.end()) {
		m_crText = it->second.uValue.crValue;
	} else {
		if (m_spFCO)
			getFacilities().getPreference(m_spFCO, textColorVariableName, m_crText);
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
	if (m_bActive && m_bSelected) {
		CRect ptRect = GetLabelLocation();
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
	if (m_spFCO && m_bActive && m_bSelected) {
		CRect ptRect = GetLabelLocation();
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
		CFont* originalFont = getFacilities().getFont(m_iFontKey)->pFont;
		LOGFONT lf;
		originalFont->GetLogFont(&lf);
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
		CSize cSize = dc.GetTextExtent(m_strText);
		POINT editLeftTopPt = { ptRect.left, ptRect.top };
		BOOL success = ::LPtoDP(transformHDC, &editLeftTopPt, 1);
		CRect editLocation(editLeftTopPt, cSize);

		CInPlaceEditDialog inPlaceEditDlg(cWnd);
		inPlaceEditDlg.SetText(m_strText);
		inPlaceEditDlg.SetInitialRect(editLocation);
		inPlaceEditDlg.SetParentWnd(m_parentWnd, cWnd);
		inPlaceEditDlg.SetFont(scaled_font);

		TitleEditingStarted(editLocation);
		if (inPlaceEditDlg.DoModal() == IDOK) {
			m_strText = inPlaceEditDlg.GetText();
			// transaction operation begin
			CComBSTR bstr;
			CopyTo(m_strText, bstr);
			COMTHROW(m_spFCO->put_Name(bstr));
			// transaction operation end
			TitleChanged(m_strText);
		}
		TitleEditingFinished(editLocation);
		delete scaled_font;
		scaled_font = NULL;

		if (!isPermanentCWnd) {
			cWnd->Detach();
			// delete is not needed, cause others created the CWnd, it'll be deleted in one OnIdle run by MFC
		}

		return true;
	}

	return false;
}

bool TextPart::MouseRightButtonDown(HMENU hCtxMenu, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	if (m_spFCO && m_bActive && m_bSelected) {
//		CPoint pt = GetTextPosition();	// TODO
		CRect ptRect = GetLabelLocation();
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

long	TextPart::GetLongest(void) const
{
	long maxv = 0;
	for (unsigned int i = 0; i < m_vecText.size(); i++) {
		long ilen = m_vecText[i].GetLength();
		if (maxv < ilen)
			maxv = ilen;
	}
	return maxv;
}

CPoint	TextPart::GetTextPosition(void) const
{
	CPoint pt;
	CRect cRect = GetLocation();	// GetBoxLocation(true)
	int iLabelSize = getFacilities().getFont(m_iFontKey)->iSize * m_vecText.size();
	switch(m_eTextLocation) {
		case L_NORTH:
		case L_NORTHWEST:
		case L_NORTHEAST:
			pt.y = cRect.top - iLabelSize - GAP_LABEL;
			break;
		case L_SOUTH:
		case L_SOUTHWEST:
		case L_SOUTHEAST:
			pt.y = cRect.bottom + GAP_LABEL;
			break;
		default:
			pt.y = cRect.CenterPoint().y - iLabelSize / 2;
			break;
	}
	switch(m_eTextLocation) {
		case L_WEST:
		case L_NORTHWEST:
		case L_SOUTHWEST:
			pt.x = cRect.left - GAP_LABEL;
			break;
		case L_NORTH:
		case L_CENTER:
		case L_SOUTH:
			pt.x = cRect.CenterPoint().x;
			break;
		default:
			pt.x = cRect.right + GAP_LABEL;
			break;
	}
	return pt;
}

}; // namespace Decorator
