// AnnotationNode.h: interface for the CAnnotationNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANNOTATIONNODE_H__A60720A0_33C3_4FFE_9995_8439D58246E8__INCLUDED_)
#define AFX_ANNOTATIONNODE_H__A60720A0_33C3_4FFE_9995_8439D58246E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CAnnotationBrowserDlg;
class CAnnotationAspect;
class CAnnotationNode;

typedef CTypedPtrList<CPtrList, CAnnotationNode *> CAnnotationNodeList;

class CAnnotationAspect {
public:
	bool	m_isVisible;
	CPoint	m_loc;
	bool	m_isLocDef;

	CAnnotationAspect() : m_isVisible(false), m_loc(0,0), m_isLocDef(true) {}
};

typedef CArray<CAnnotationAspect,CAnnotationAspect&> CAnnotationAspectArray;

class CAnnotationNode  
{
public:
	CComPtr<IMgaRegNode> m_regNode;
	LOGFONT m_logfont;
	COLORREF m_bgcolor;
	COLORREF m_color;
	CString m_text;
	CString m_name;
	bool m_virtual;         // if status of the main regnode is 'inherited'
	bool m_canBeRederived;  // the "broken_deriv" entry signals that 
	                        // the annotation was once inherited, 
	                        // so it could be rederived
	
	bool m_inheritable;     // can be shown in subtypes/instances
	bool m_hidden;          // hide inherited annotation in this subtype/instance only
	CAnnotationAspectArray	m_aspects;

	CAnnotationNode(const CComPtr<IMgaRegNode> &regNode);
	void Read(CAnnotationBrowserDlg *dlg);
	void Write(CAnnotationBrowserDlg *dlg);

public:
	static void InitializeClass();
	static bool classIsInitialized;
	static bool     defCanBeRederived;
	static bool     defInheritable;
	static bool     defHidden;
	static LOGFONT	defFont;
	static COLORREF	defColor;
	static COLORREF defBgcolor;
};

#endif // !defined(AFX_ANNOTATIONNODE_H__A60720A0_33C3_4FFE_9995_8439D58246E8__INCLUDED_)