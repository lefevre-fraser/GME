//################################################################################################
//
// Composite part class (decorator part)
//	CompositePart.h
//
//################################################################################################

#ifndef __COMPOSITEPART_H_
#define __COMPOSITEPART_H_


#include "../StdAfx.h"
#include "PartBase.h"
#include <vector>


namespace Decorator {

//################################################################################################
//
// CLASS : CompositePart
//
//################################################################################################

class CompositePart: public PartBase
{
protected:
	std::vector<PartBase*>	m_compositeParts;

public:
	CompositePart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink);
	virtual ~CompositePart();

	virtual void			AddPart				(PartBase* part);
	virtual void			RemovePart			(PartBase* part);
	virtual void			RemovePart			(int index);
	virtual PartBase*		GetPart				(int index);
	virtual long			GetSize				(void) const;

// =============== resembles IMgaNewDecorator
public:
	virtual void			Initialize			(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO);
	virtual void			Destroy				(void);
	virtual CString			GetMnemonic			(void) const;
	virtual feature_code	GetFeatures			(void) const;
	virtual void			SetParam			(const CString& strName, VARIANT vValue);
	virtual bool			GetParam			(const CString& strName, VARIANT* pvValue);
	virtual void			SetActive			(bool bIsActive);
	virtual CSize			GetPreferredSize	(void) const;
	virtual void			SetLocation			(const CRect& location);
	virtual CRect			GetLocation			(void) const;
	virtual CRect			GetLabelLocation	(void) const;
	virtual CRect			GetPortLocation		(CComPtr<IMgaFCO>& fco) const;
	virtual bool			GetPorts			(CComPtr<IMgaFCOs>& portFCOs) const;
	virtual void			Draw				(CDC* pDC);
	virtual void			SaveState			(void);

	virtual void	InitializeEx				(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd, PreferenceMap& preferences);
	virtual void	SetSelected					(bool bIsSelected);
	virtual bool	MouseMoved					(UINT nFlags, const CPoint& lpoint, const CPoint& dpoint, long zoomPercent);
	virtual bool	MouseLeftButtonDown			(UINT nFlags, const CPoint& lpoint, const CPoint& dpoint, long zoomPercent);
	virtual bool	MouseLeftButtonUp			(UINT nFlags, const CPoint& lpoint, const CPoint& dpoint, long zoomPercent);
	virtual bool	MouseLeftButtonDoubleClick	(UINT nFlags, const CPoint& lpoint, const CPoint& dpoint, long zoomPercent);
	virtual bool	MouseRightButtonDown		(HMENU hCtxMenu, UINT nFlags, const CPoint& lpoint, const CPoint& dpoint, long zoomPercent);
	virtual bool	MouseRightButtonUp			(UINT nFlags, const CPoint& lpoint, const CPoint& dpoint, long zoomPercent);
	virtual bool	MouseRightButtonDoubleClick	(UINT nFlags, const CPoint& lpoint, const CPoint& dpoint, long zoomPercent);
	virtual bool	MouseMiddleButtonDown		(UINT nFlags, const CPoint& lpoint, const CPoint& dpoint, long zoomPercent);
	virtual bool	MouseMiddleButtonUp			(UINT nFlags, const CPoint& lpoint, const CPoint& dpoint, long zoomPercent);
	virtual bool	MouseMiddleButtonDoubleClick(UINT nFlags, const CPoint& lpoint, const CPoint& dpoint, long zoomPercent);
	virtual bool	MouseWheelTurned			(UINT nFlags, short distance, const CPoint& lpoint, const CPoint& dpoint, long zoomPercent);
	virtual bool	MenuItemSelected			(UINT menuItemId, UINT nFlags, const CPoint& lpoint, const CPoint& dpoint, long zoomPercent);
	virtual bool	OperationCanceledByGME		(void);

	virtual void	SetBoxLocation				(const CRect& cRect);
	virtual void	SetReferenced				(bool referenced);
	virtual void	SetParentPart				(PartBase* pPart);
};

}; // namespace Decorator

#endif //__COMPOSITEPART_H_
