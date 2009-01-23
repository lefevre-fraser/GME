//################################################################################################
//
// Annotator text part class
//	AnnotatorTextPart.h
//
//################################################################################################

#ifndef __ANNOTATORTEXTPART_H_
#define __ANNOTATORTEXTPART_H_


#include "StdAfx.h"
#include "ClassComplexPart.h"

#include "DecoratorStd.h"


namespace AnnotatorDecor {

//################################################################################################
//
// CLASS : AnnotatorTextPart
//
//################################################################################################

class AnnotatorTextPart: public DecoratorSDK::TextPart
{
protected:
	CComPtr<IMgaRegNode>	m_regRoot;
	CString					m_strName;
	COLORREF				m_crBgColor;
	COLORREF				m_crShadow;
	COLORREF				m_crGradient;
	bool					m_bGradientFill;
	long					m_iGradientDirection;
	bool					m_bCastShadow;
	long					m_iShadowDepth;
	long					m_iShadowDirection;
	bool					m_bRoundCornerRect;
	long					m_iRoundCornerRadius;
	LOGFONT					m_logFont;

public:
	AnnotatorTextPart(DecoratorSDK::PartBase* pPart, CComPtr<IMgaNewDecoratorEvents>& eventSink);
	virtual ~AnnotatorTextPart();

// =============== resembles IMgaNewDecorator
public:
	virtual void	SetParam					(const CString& strName, VARIANT vValue);
	virtual bool	GetParam					(const CString& strName, VARIANT* pvValue);
	virtual CSize	GetPreferredSize			(void) const;
	virtual void	Draw						(CDC* pDC, Gdiplus::Graphics* gdip);
	virtual void	InitializeEx				(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd, DecoratorSDK::PreferenceMap& preferences);

	virtual CPoint	GetTextPosition				(CDC* pDC, Gdiplus::Graphics* gdip) const;
	virtual void	SetTextRelYPosition			(long relYPosition) {};	// This doesn't make sense in case of annotator decorator
	virtual CRect	GetTextLocation				(CDC* pDC, Gdiplus::Graphics* gdip) const;
	virtual void	ExecuteOperation			(const CString& newString);

protected:
	void			ReadPreferences				(void);
};

}; // namespace AnnotatorDecor

#endif //__ANNOTATORTEXTPART_H_
