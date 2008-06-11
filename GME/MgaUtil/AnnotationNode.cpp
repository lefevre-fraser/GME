// AnnotationNode.cpp: implementation of the CAnnotationNode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mgautil.h"
#include "AnnotationNode.h"
#include "..\Annotator\AnnotationDefs.h"
#include "AnnotationBrowserDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
LOGFONT	CAnnotationNode::defFont;
COLORREF CAnnotationNode::defColor;
COLORREF CAnnotationNode::defBgcolor;
bool CAnnotationNode::classIsInitialized = false;
bool CAnnotationNode::defInheritable     = false;
bool CAnnotationNode::defHidden          = false;
bool CAnnotationNode::defCanBeRederived  = false;

CAnnotationNode::CAnnotationNode(const CComPtr<IMgaRegNode> &regNode)
{
	m_regNode = regNode;
	if (!classIsInitialized) {
		InitializeClass();
	}
}

void CAnnotationNode::Read(CAnnotationBrowserDlg *dlg)
{
	// virtual: if status of m_regNode is 'inherited'
	try {
		m_virtual = false;
		long st;
		COMTHROW( m_regNode->get_Status( &st));
		if( st > ATTSTATUS_HERE) // -1: meta, 0: here, >=1: inherited
			m_virtual = true;
	} 
	catch (hresult_exception &) {
		ASSERT(("Error while reading annotation from registry.", false));
		m_virtual = false;
	}

	// it can be rederived if 'broken deriv' entry present with '1'
	try {
		m_canBeRederived = defCanBeRederived;
		CComBSTR bstr;
		CComPtr<IMgaRegNode> lfNode;
		CComBSTR lfName(AN_BROKEN_DERIV);
		COMTHROW(m_regNode->get_SubNodeByName(lfName, &lfNode));
		if (lfNode != NULL) {
			COMTHROW(lfNode->get_Value(&bstr));
			if( bstr == "1")
				m_canBeRederived = true;
		}
	} 
	catch (hresult_exception &) {
		m_canBeRederived = defCanBeRederived;
	}


	// Annotation name
	try {
		CComBSTR bstr;
		COMTHROW(m_regNode->get_Name(&bstr));
		m_name = bstr;
	} 
	catch (hresult_exception &) {
		ASSERT(("Error while reading annotation from registry.", false));
		m_name = "ERROR!!!";
	}
	
	// Annotation text
	try {
		CComBSTR bstr;
		COMTHROW(m_regNode->get_Value(&bstr));
		m_text = bstr;
		m_text.Replace("\n", "\r\n");
	} 
	catch (hresult_exception &) {
		ASSERT(("Error while reading annotation from registry.", false));
		m_text = "Unable to read annotation text.";
	}

	// 'Inheritable'
	try {
		m_inheritable = defInheritable;
		CComBSTR bstr;
		CComPtr<IMgaRegNode> lfNode;
		CComBSTR lfName(AN_INHERITABLE);
		COMTHROW(m_regNode->get_SubNodeByName(lfName, &lfNode));
		if (lfNode != NULL) {
			COMTHROW(lfNode->get_Value(&bstr));
			if( bstr == "1")
				m_inheritable = true;
		}
	} 
	catch (hresult_exception &) {
		m_inheritable = defInheritable;
	}

	// 'Hidden'
	try {
		m_hidden = defHidden;
		CComBSTR bstr;
		CComPtr<IMgaRegNode> lfNode;
		CComBSTR lfName(AN_HIDDEN);
		COMTHROW(m_regNode->get_SubNodeByName(lfName, &lfNode));
		if (lfNode != NULL) {
			COMTHROW(lfNode->get_Value(&bstr));
			if( bstr == "1")
				m_hidden = true;
		}
	} 
	catch (hresult_exception &) {
		m_hidden = defHidden;
	}

	// Font
	try {
		CComBSTR bstr;
		CComPtr<IMgaRegNode> lfNode;
		CComBSTR lfName(AN_FONT_PREF);
		COMTHROW(m_regNode->get_SubNodeByName(lfName, &lfNode));
		if (lfNode != NULL) {
			COMTHROW(lfNode->get_Value(&bstr));
		}
		CString str(bstr);
		if (!LogfontDecode(str, &m_logfont)) {
			throw hresult_exception();
		}
	} 
	catch (hresult_exception &) {
		memcpy(&m_logfont, &defFont, sizeof(LOGFONT));
	}

	// Text Color
	try {
		CComBSTR bstr;
		CComPtr<IMgaRegNode> colNode;
		CComBSTR colName(AN_COLOR_PREF);
		COMTHROW(m_regNode->get_SubNodeByName(colName, &colNode));
		if (colNode != NULL) {
			COMTHROW(colNode->get_Value(&bstr));
		}
		CString strVal(bstr);
		unsigned int val;
		if (_stscanf(strVal,_T("%x"),&val) == 1) {
			unsigned int r = (val & 0xff0000) >> 16;
			unsigned int g = (val & 0xff00) >> 8;
			unsigned int b = val & 0xff;
			m_color = RGB(r,g,b);
		}
		else {
			throw hresult_exception();
		}
	} 
	catch (hresult_exception &) {
		m_color = defColor;
	}

	// Background Color
	try {
		CComBSTR bstr;
		CComPtr<IMgaRegNode> bgcolNode;
		CComBSTR bgcolName(AN_BGCOLOR_PREF);
		COMTHROW(m_regNode->get_SubNodeByName(bgcolName, &bgcolNode));
		if (bgcolNode != NULL) {
			COMTHROW(bgcolNode->get_Value(&bstr));
		}
		CString strVal(bstr);
		unsigned int val;
		if (_stscanf(strVal,_T("%x"),&val) == 1) {
			unsigned int r = (val & 0xff0000) >> 16;
			unsigned int g = (val & 0xff00) >> 8;
			unsigned int b = val & 0xff;
			m_bgcolor = RGB(r,g,b);
		}
		else {
			m_bgcolor = defBgcolor;
		}
	} 
	catch (hresult_exception &) {
		m_bgcolor = AN_DEFAULT_BGCOLOR;
	}
	
	// Aspects
	m_aspects.SetSize(dlg->m_aspectNames.GetSize());
	CComPtr<IMgaRegNode> aspRoot;
	CComBSTR aspRootName(AN_ASPECTS);
	COMTHROW(m_regNode->get_SubNodeByName(aspRootName, &aspRoot));
	for (int aspIdx = 0; aspIdx < dlg->m_aspectNames.GetSize(); aspIdx++) {
		if (aspIdx == 0) {
			m_aspects[aspIdx].m_isLocDef = false;

			CComBSTR defName(AN_DEFASPECT);
			CComPtr<IMgaRegNode> defNode;
			COMTHROW(aspRoot->get_SubNodeByName(defName, &defNode));
			long status;
			COMTHROW(defNode->get_Status(&status));
			m_aspects[aspIdx].m_isVisible = (status != ATTSTATUS_UNDEFINED);

			CComBSTR  rootVal;
			COMTHROW(aspRoot->get_Value(&rootVal));
			CString rootValStr(rootVal);
			long lx, ly;
			if(_stscanf(rootValStr,_T("%d,%d"), &lx, &ly) == 2) {
				m_aspects[aspIdx].m_loc = CPoint(lx,ly);	
			}
			else {
				m_aspects[aspIdx].m_loc = CPoint(0,0);
			}
		}
		else {
			CComBSTR aspName(dlg->m_aspectNames[aspIdx]);
			CComPtr<IMgaRegNode> aspNode;
			COMTHROW(aspRoot->get_SubNodeByName(aspName, &aspNode));
			long status;
			COMTHROW(aspNode->get_Status(&status));
			if (status == ATTSTATUS_UNDEFINED) {
				m_aspects[aspIdx].m_isVisible = false;
				m_aspects[aspIdx].m_loc = m_aspects[0].m_loc;
				m_aspects[aspIdx].m_isLocDef = true;
			}
			else {
				m_aspects[aspIdx].m_isVisible = true;
				CComBSTR  aspVal;
				COMTHROW(aspNode->get_Value(&aspVal));
				CString aspValStr(aspVal);
				long lx, ly;
				if(_stscanf(aspValStr,_T("%d,%d"), &lx, &ly) == 2) {
					m_aspects[aspIdx].m_loc = CPoint(lx,ly);
					m_aspects[aspIdx].m_isLocDef = false;
				}
				else {
					m_aspects[aspIdx].m_loc = m_aspects[0].m_loc;
					m_aspects[aspIdx].m_isLocDef = true;
				}
			}
		}
	}
}

void CAnnotationNode::Write(CAnnotationBrowserDlg *dlg)
{
	// it will notify if we just broke an annotation inheritance relationship (if text in the derived becomes different than the base's text)
	bool broken_inheritance = false;

	// Drop previous node, start new one
	try {
		CComPtr<IMgaRegNode> parentNode;
		COMTHROW(m_regNode->get_ParentNode(&parentNode));

		// get the old text, used later to check if subtypes/instances break the derivation chain of the annotation
		CComBSTR bstr1;
		COMTHROW(m_regNode->get_Value(&bstr1));
		CString old_m_text = bstr1;
		old_m_text.Replace("\n", "\r\n");

		if(!m_virtual) COMTHROW(m_regNode->RemoveTree()); // remove the old node if it was HERE, because we will write a new node there
		else // virtual node: still inherited
		{ 
			// keep the derivation chain if the text has not been changed
			if( old_m_text == m_text)
				return;
			else// This value will only signal that the chain is broken.
				// By writing under the same node into a subtype's registry
				// we can hide the inherited value with a HERE value.
				broken_inheritance = true;
		}

		bool collision = true;
		while (collision) {
			m_regNode = NULL;
			CComBSTR bstrName(m_name);
			COMTHROW(parentNode->get_SubNodeByName(bstrName, &m_regNode));
			long status;
			COMTHROW(m_regNode->get_Status(&status));
			if (status == ATTSTATUS_UNDEFINED) {
				collision = false;
			}
			else {
				if(broken_inheritance // if we broke right now the inheritance
				 || m_canBeRederived) // or it was broken in the past
					collision = false;// don't signal a 'collision' since we
				                      // have to hide the old (i)nherited value
				                      // with a (h)ere value
				else
					m_name += _T("Copy");
			}
		}
	}
	catch (hresult_exception &) {
		ASSERT(("Error while creating annotation to registry.", false));
		return;
	}

	// Store text
	try {
		CString tmpstr(m_text);
		tmpstr.Replace("\r\n", "\n");
		CComBSTR bstr(tmpstr);
		COMTHROW(m_regNode->put_Value(bstr));
	}
	catch (hresult_exception &) {
		ASSERT(("Error while writing annotation to registry.", false));
	}

	// Store 'broken derivation' preference (if text has been altered in the subtyped object's annotation)
	// either broken in the past (canBeRederived) or broken right now(broken_inh)
	if( m_canBeRederived || broken_inheritance) {
		try {
			CComBSTR bstr("1");
			CComPtr<IMgaRegNode> lfNode;
			CComBSTR lfName(AN_BROKEN_DERIV);
			COMTHROW(m_regNode->get_SubNodeByName(lfName, &lfNode));
			COMTHROW(lfNode->put_Value(bstr));
		}
		catch (hresult_exception &) {
			ASSERT(("Error while writing annotation to registry.", false));
		}
	}

	// Store 'inheritable' preference
	{
		try {
			CString str(m_inheritable?"1":"0");
			CComBSTR bstr(str);
			CComPtr<IMgaRegNode> lfNode;
			CComBSTR lfName(AN_INHERITABLE);
			COMTHROW(m_regNode->get_SubNodeByName(lfName, &lfNode));
			COMTHROW(lfNode->put_Value(bstr));
		}
		catch (hresult_exception &) {
			ASSERT(("Error while writing annotation to registry.", false));
		}
	}

	// Store 'hidden' preference
	{
		try {
			CString str(m_hidden?"1":"0");
			CComBSTR bstr(str);
			CComPtr<IMgaRegNode> lfNode;
			CComBSTR lfName(AN_HIDDEN);
			COMTHROW(m_regNode->get_SubNodeByName(lfName, &lfNode));
			COMTHROW(lfNode->put_Value(bstr));
		}
		catch (hresult_exception &) {
			ASSERT(("Error while writing annotation to registry.", false));
		}
	}

	// Store color,bgcolor,font preferences
	if (memcmp(&m_logfont, &defFont, sizeof(LOGFONT)) != 0) {
		try {
			CString str;
			LogfontEncode(str, &m_logfont);
			CComBSTR bstr(str);
			CComPtr<IMgaRegNode> lfNode;
			CComBSTR lfName(AN_FONT_PREF);
			COMTHROW(m_regNode->get_SubNodeByName(lfName, &lfNode));
			COMTHROW(lfNode->put_Value(bstr));
		}
		catch (hresult_exception &) {
			ASSERT(("Error while writing annotation to registry.", false));
		}
	}

	if (m_color != defColor) {
		try {
			unsigned long ival = m_color;
			unsigned long r = (ival & 0xff0000) >> 16;
			unsigned long g = (ival & 0xff00) >> 8;
			unsigned long b = ival & 0xff;
			ival = (unsigned long)(RGB(r,g,b));
			CString str;
			str.Format(_T("0x%06x"), (unsigned long)ival);
			CComBSTR bstr(str);
			CComPtr<IMgaRegNode> colNode;
			CComBSTR colName(AN_COLOR_PREF);
			COMTHROW(m_regNode->get_SubNodeByName(colName, &colNode));
			COMTHROW(colNode->put_Value(bstr));
		
		}
		catch (hresult_exception &) {
			ASSERT(("Error while writing annotation to registry.", false));
		}
	}
	if (m_bgcolor != defBgcolor) {
		try {
			unsigned long ival = m_bgcolor;
			unsigned long r = (ival & 0xff0000) >> 16;
			unsigned long g = (ival & 0xff00) >> 8;
			unsigned long b = ival & 0xff;
			ival = (unsigned long)(RGB(r,g,b));
			CString str;
			str.Format(_T("0x%06x"), (unsigned long)ival);
			CComBSTR bstr(str);
			CComPtr<IMgaRegNode> bgcolNode;
			CComBSTR bgcolName(AN_BGCOLOR_PREF);
			COMTHROW(m_regNode->get_SubNodeByName(bgcolName, &bgcolNode));
			COMTHROW(bgcolNode->put_Value(bstr));
		
		}
		catch (hresult_exception &) {
			ASSERT(("Error while writing annotation to registry.", false));
		}
	}

	// Store default location & aspect visibility
	CComPtr<IMgaRegNode> aspRoot;
	CComBSTR aspRootName(AN_ASPECTS);
	COMTHROW(m_regNode->get_SubNodeByName(aspRootName, &aspRoot));
	for (int aspIdx = 0; aspIdx < dlg->m_aspectNames.GetSize(); aspIdx++) {
		if (aspIdx == 0) {
			CString rootValStr;
			rootValStr.Format(_T("%d,%d"), m_aspects[aspIdx].m_loc.x, m_aspects[aspIdx].m_loc.y);
			CComBSTR  rootVal(rootValStr);
			COMTHROW(aspRoot->put_Value(rootVal));

			CComBSTR defName(AN_DEFASPECT);
			CComPtr<IMgaRegNode> defNode;
			COMTHROW(aspRoot->get_SubNodeByName(defName, &defNode));
			if (m_aspects[aspIdx].m_isVisible) {
				CComBSTR defVal(AN_VISIBLE_DEFAULT);
				COMTHROW(defNode->put_Value(defVal));
			}
			else // by default a value is inserted into the AN_DEFASPECT key in the registry
			{    // in CGMEView::OnCntxInsertannotation() so we remove in case the user 
				 // did UNCHECK that option
				long st;
				COMTHROW( defNode->get_Status( &st));
				if( st == ATTSTATUS_HERE) COMTHROW( defNode->Clear());
			}
		}
		else {
			if (m_aspects[aspIdx].m_isVisible) {
				CComBSTR aspName(dlg->m_aspectNames[aspIdx]);
				CComPtr<IMgaRegNode> aspNode;
				COMTHROW(aspRoot->get_SubNodeByName(aspName, &aspNode));
				CString aspValStr;
				if (m_aspects[aspIdx].m_isLocDef) {
					aspValStr = AN_VISIBLE_DEFAULT;
				}
				else {
					aspValStr.Format("%d,%d", m_aspects[aspIdx].m_loc.x, m_aspects[aspIdx].m_loc.y);
				}
				CComBSTR  aspVal(aspValStr);
				COMTHROW(aspNode->put_Value(aspVal));
			}
		}
	}
}

void CAnnotationNode::InitializeClass()
{
		memset(&defFont, 0, sizeof(LOGFONT));
		defFont.lfHeight = -MulDiv(AN_DEFAULT_FONT_HEIGHT, GetDeviceCaps(::GetWindowDC(NULL), LOGPIXELSY), 72);
		_tcsncpy(defFont.lfFaceName, AN_DEFAULT_FONT_FACE, LF_FACESIZE);
		defFont.lfPitchAndFamily = FF_DONTCARE | DEFAULT_PITCH;
		defFont.lfQuality = DEFAULT_QUALITY;
		defFont.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
		defFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
		defFont.lfCharSet = ANSI_CHARSET;
		defFont.lfItalic  = FALSE;
		defFont.lfUnderline = FALSE;
		defFont.lfStrikeOut = FALSE;
		defFont.lfWeight = FW_DONTCARE;
		defFont.lfWidth = 0;

		defColor = AN_DEFAULT_COLOR;

		defBgcolor = AN_DEFAULT_BGCOLOR;

		classIsInitialized = true;
}

void CAnnotationNode::LogfontEncode(CString &str, const LOGFONT * lfp)
{	
	TCHAR buff[6];
	buff[5] = _T('0');

	str.Empty();
	for (int i = 0; i < sizeof(LOGFONT); i++) {
		unsigned int ch = ((const unsigned char *)lfp)[i];
		_sntprintf(buff, 5, _T("%02x "), ch);
		str += buff;
	}
}

bool CAnnotationNode::LogfontDecode(const CString &str, LOGFONT * lfp)
{
	int i = 0;
	int pos = 0;
	int epos = 0;
	epos = str.Find(_T(' '), pos);
	while (epos > 0) {
		unsigned int ch;
		if (_stscanf(str.Mid(pos,epos-pos), _T("%2x"), &ch) != 1) {
			return false;
		}
		((unsigned char *)lfp)[i++] = ch;
		pos = epos+1;
		epos = str.Find(_T(' '), pos);
	}
	return (i == sizeof(LOGFONT));
}
