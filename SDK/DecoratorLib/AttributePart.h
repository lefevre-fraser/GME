//################################################################################################
//
// Attribute part class (decorator part)
//	AttributePart.h
//
//################################################################################################

#ifndef __ATTRIBUTEPART_H_
#define __ATTRIBUTEPART_H_


#include "StdAfx.h"
#include "TextPart.h"


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : AttributePart
//
//################################################################################################

class AttributePart: public TextPart
{
protected:
	CString			m_strType;
	long			m_textRelYPosition;	// bottom of the text because of the bottom alignment

public:
	AttributePart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink);
	virtual ~AttributePart();

	virtual void	Draw						(CDC* pDC);

	virtual CPoint	GetTextPosition				(void) const;
	virtual void	SetTextRelYPosition			(long relYPosition) { m_textRelYPosition = relYPosition; };
	virtual CRect	GetTextLocation				(void) const;

	virtual CSize	GetNameSize					(CDC* pDC) const;
	virtual CSize	GetTypeSize					(CDC* pDC) const;
	virtual CSize	GetTextSize					(CDC* pDC) const;
	virtual void	SetName						(const CString& nameStr) { m_strText = nameStr; };
	virtual void	SetType						(const CString& typeStr) { m_strType = typeStr; };
	virtual CString	GetName						(void) const { return m_strText; };
	virtual CString	GetType						(void) const { return m_strType; };
};

}; // namespace DecoratorSDK

#endif //__ATTRIBUTEPART_H_
