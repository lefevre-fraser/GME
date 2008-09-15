//################################################################################################
//
// Model complex part class (decorator part)
//	ModelComplexPart.h
//
//################################################################################################

#ifndef __MODELCOMPLEXPART_H_
#define __MODELCOMPLEXPART_H_


#include "../StdAfx.h"
#include "TypeableBitmapPart.h"
#include "PortPart.h"

namespace Decorator {

struct PortPartData;

//################################################################################################
//
// CLASS : ModelComplexPart
//
//################################################################################################

class ModelComplexPart: public TypeableBitmapPart
{
protected:
	std::vector<PortPart*>		m_LeftPorts;
	std::vector<PortPart*>		m_RightPorts;
	long						m_iMaxPortTextLength;
	COLORREF					m_crPortText;
	bool						m_bPortLabelInside;
	long						m_iLongestPortTextLength;

public:
	ModelComplexPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink);
	virtual ~ModelComplexPart();

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

	virtual void	DrawBackground				(CDC* pDC);

	virtual void 	LoadPorts					(void);
	virtual void 	OrderPorts					(std::vector<PortPartData*>& vecPorts);
	virtual void	SetBoxLocation				(const CRect& cRect);
	virtual void	SetReferenced				(bool referenced);
	virtual void	SetParentPart				(PartBase* pPart);
	std::vector<PortPart*>	GetPorts			(void);
	PortPart*		GetPort						(CComPtr<IMgaFCO> spFCO);
};

}; // namespace Decorator

#endif //__MODELCOMPLEXPART_H_
