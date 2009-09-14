#if !defined(AFX_DIALOGTEMPLATE_H__38B753AD_BDF3_4f9b_8224_1AB10FA65608__INCLUDED_)
#define AFX_DIALOGTEMPLATE_H__38B753AD_BDF3_4f9b_8224_1AB10FA65608__INCLUDED_

// from Max McGuire
// http://www.flipcode.com/archives/Dialog_Template.shtml

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogTemplate.h : header file
//

#include "stdafx.h"

// CDialogTemplate class

class CDialogTemplate
{
public:
	CDialogTemplate(LPCSTR caption, DWORD style, int x, int y, int w, int h, LPCSTR font = NULL, WORD fontSize = 8);
	virtual ~CDialogTemplate();
	operator const DLGTEMPLATE*() const;

	void AddButton		(LPCSTR caption, DWORD style, DWORD exStyle, int x, int y, int w, int h, WORD id);
	void AddEditBox		(LPCSTR caption, DWORD style, DWORD exStyle, int x, int y, int w, int h, WORD id);
	void AddStatic		(LPCSTR caption, DWORD style, DWORD exStyle, int x, int y, int w, int h, WORD id);
	void AddListBox		(LPCSTR caption, DWORD style, DWORD exStyle, int x, int y, int w, int h, WORD id);
	void AddScrollBar	(LPCSTR caption, DWORD style, DWORD exStyle, int x, int y, int w, int h, WORD id);
	void AddComboBox	(LPCSTR caption, DWORD style, DWORD exStyle, int x, int y, int w, int h, WORD id);
	void AddRichEdit	(LPCSTR caption, DWORD style, DWORD exStyle, int x, int y, int w, int h, WORD id);

protected:
	void AddStandardComponent(WORD type, LPCSTR caption, DWORD style, DWORD exStyle, int x, int y, int w, int h, WORD id);
	void AddComponent(WORD type, LPCSTR classId, LPCSTR caption, DWORD style, DWORD exStyle, int x, int y, int w, int h, WORD id);
	void AlignData(int size);
	void AppendString(LPCSTR string);
	void AppendData(void* data, int dataLength);
	void EnsureSpace(int length);

private:
	DLGTEMPLATE* dialogTemplate;

	int totalBufferLength;
	int usedBufferLength;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGTEMPLATE_H__38B753AD_BDF3_4f9b_8224_1AB10FA65608__INCLUDED_)
