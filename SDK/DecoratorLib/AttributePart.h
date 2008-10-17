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
	CPoint			m_namePosition;
	CPoint			m_typePosition;

public:
	AttributePart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink);
	virtual ~AttributePart();

	virtual void	Draw						(CDC* pDC);

	virtual CPoint	GetTextPosition				(void) const;
	virtual void	SetTextPosition				(const CPoint& position);
	virtual CRect	GetTextLocation				(void) const;
	virtual void	ExecuteOperation			(void);

	virtual CSize	GetNameSize					(CDC* pDC) const;
	virtual CSize	GetTypeSize					(CDC* pDC) const;
	virtual CSize	GetTextSize					(CDC* pDC) const;
	virtual void	SetNamePosition				(const CPoint& namePosition) { m_namePosition = namePosition; };
	virtual void	SetTypePosition				(const CPoint& typePosition) { m_typePosition = typePosition; };
	virtual void	SetName						(const CString& nameStr) { m_strText = nameStr; };
	virtual void	SetType						(const CString& typeStr) { m_strType = typeStr; };
};

}; // namespace DecoratorSDK

#endif //__ATTRIBUTEPART_H_
