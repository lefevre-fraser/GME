// AnnotationUtil.cpp: implementation of the CAnnotationNode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AnnotationUtil.h"
#include "..\Annotator\AnnotationDefs.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


void CAnnotationUtil::LogfontEncode(CString &str, const LOGFONT* lfp)
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

bool CAnnotationUtil::LogfontDecode(const CString &str, LOGFONT* lfp)
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

void CAnnotationUtil::FillLogFontWithDefault(LOGFONT* lfp)
{
	ASSERT(lfp != NULL);
	memset(lfp, 0, sizeof(LOGFONT));
	lfp->lfHeight			= -MulDiv(AN_DEFAULT_FONT_HEIGHT, GetDeviceCaps(::GetWindowDC(NULL), LOGPIXELSY), 72);
	_tcsncpy(lfp->lfFaceName, AN_DEFAULT_FONT_FACE, LF_FACESIZE);
	lfp->lfPitchAndFamily	= FF_DONTCARE | DEFAULT_PITCH;
	lfp->lfQuality			= DEFAULT_QUALITY;
	lfp->lfClipPrecision	= CLIP_DEFAULT_PRECIS;
	lfp->lfOutPrecision		= OUT_DEFAULT_PRECIS;
	lfp->lfCharSet			= ANSI_CHARSET;
	lfp->lfItalic			= FALSE;
	lfp->lfUnderline		= FALSE;
	lfp->lfStrikeOut		= FALSE;
	lfp->lfWeight			= FW_DONTCARE;
	lfp->lfWidth			= 0;
}
