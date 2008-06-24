/////////////////////////////////////////////////////////////////////////
//
// CSizingControlBar            Version 2.3
// Created: Jan 24, 1998        Last Modified: Dec 12, 1999
//
// See the official page at www.datamekanix.com for documentation and
// the latest news.
//
/////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998, 1999 by Cristi Posea. All rights reserved.
//
// This code is free for personal and commercial use, providing this 
// notice remains intact in the source files and all eventual changes are
// clearly marked with comments.
//
// You must obtain the author's consent before you can include this code
// in a software library.
//
// No warrantee of any kind, express or implied, is included with this
// software; use at your own risk, responsibility for damages (if any) to
// anyone resulting from the use of this software rests entirely with the
// user.
//
// Send bug reports, bug fixes, enhancements, requests, flames, etc. to:
//
//      cristi@datamekanix.com 
//
// Copies of the article/sources are also available at:
//  o   www.codeproject.com
//  o   www.codeguru.com
// Look for a "Docking Windows" section on the sites above and check
// the version to be sure you get the latest one ;)
//
// Hint: This class is intended to be used as a base class. Do not simply
// add your code to this file - instead create a new class derived from
// CSizingControlBar and put there what you need.
// Modify this file only to fix bugs, and don't forget to send me a copy.
//
/////////////////////////////////////////////////////////////////////////
// Modified by: Zoltan Molnar, @ Vanderbilt Univ. in 2006 in order to 
// work better with the CMiniDockFrameWnd MFC class, version VS.NET 2003
// Details: when floating the MFC class already displays a caption and 
//          close button (x), so we avoid painting the gripper and (x) 
/////////////////////////////////////////////////////////////////////////

#if !defined(__SIZECBAR_H__)
#define __SIZECBAR_H__

#include <afxpriv.h>    // for CDockContext
#include <afxtempl.h>   // for CArray

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////
// CSCBButton (button info) helper class

class CSCBButton
{
public:
    CSCBButton();

    void Move(CPoint ptTo) {ptOrg = ptTo; };
    CRect GetRect() { return CRect(ptOrg, CSize(11, 11)); };
    void Paint(CDC* pDC);

    BOOL    bPushed;
    BOOL    bRaised;

protected:
    CPoint  ptOrg;
};

/////////////////////////////////////////////////////////////////////////
// CSCBDockBar dummy class for access to protected members

class CSCBDockBar : public CDockBar
{
    friend class CSizingControlBar;
};

/////////////////////////////////////////////////////////////////////////
// CSizingControlBar control bar styles

#define SCBS_EDGELEFT       0x00000001
#define SCBS_EDGERIGHT      0x00000002
#define SCBS_EDGETOP        0x00000004
#define SCBS_EDGEBOTTOM     0x00000008
#define SCBS_EDGEALL        0x0000000F
#define SCBS_SHOWEDGES      0x00000010
#define SCBS_GRIPPER        0x00000020

/////////////////////////////////////////////////////////////////////////
// CSizingControlBar control bar

#ifndef baseCSizingControlBar
#define baseCSizingControlBar CControlBar
#endif

class CSizingControlBar;
typedef CTypedPtrArray <CPtrArray, CSizingControlBar*> CSCBArray;

class CSizingControlBar : public baseCSizingControlBar
{
    DECLARE_DYNAMIC(CSizingControlBar);

// Construction
protected:
    CSizingControlBar();

public:
    virtual BOOL Create(LPCTSTR lpszWindowName, CWnd* pParentWnd,
        CSize sizeDefault, BOOL bHasGripper, UINT nID,
        DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP);

// Attributes
public:
    CSize m_szHorz;
    CSize m_szVert;
    CSize m_szFloat;
    const BOOL IsFloating() const;
    const BOOL IsHorzDocked() const;
    const BOOL IsVertDocked() const;
    const BOOL IsSideTracking() const;
	virtual IDispatch * GetInterface() = 0;

// Operations
public:
    void EnableDocking(DWORD dwDockStyle);
    virtual void LoadState(LPCTSTR lpszProfileName);
    virtual void SaveState(LPCTSTR lpszProfileName);
    static void GlobalLoadState(LPCTSTR lpszProfileName);
    static void GlobalSaveState(LPCTSTR lpszProfileName);

// Overridables
    virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);

// Overrides
public:
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CSizingControlBar)
    public:
    virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
    virtual CSize CalcDynamicLayout(int nLength, DWORD dwMode);
    virtual BOOL DestroyWindow();
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CSizingControlBar();
    
protected:
    // implementation helpers
    UINT GetEdgeHTCode(int nEdge);
    BOOL GetEdgeRect(CRect rcWnd, UINT nHitTest, CRect& rcEdge);
    virtual void StartTracking(UINT nHitTest);
    virtual void StopTracking();
    virtual void OnTrackUpdateSize(CPoint& point);
    virtual void OnTrackInvertTracker();
    virtual void NcPaintGripper(CDC* pDC, CRect rcClient);

    virtual void AlignControlBars();
    const int FindSizingBar(CControlBar* pBar) const;
    void GetRowInfo(int& nFirst, int& nLast, int& nThis);
    void GetRowSizingBars(CSCBArray& arrSCBars);
    BOOL NegotiateSpace(int nLengthTotal, BOOL bHorz);

protected:
    static CSCBArray    m_arrBars;

    DWORD   m_dwSCBStyle;
    UINT    m_htEdge;

    CSize   m_szMin;
    CSize   m_szMinT;
    CSize   m_szMaxT;
    CSize   m_szOld;
    CPoint  m_ptOld;
    BOOL    m_bTracking;
    BOOL    m_bKeepSize;
    BOOL    m_bParentSizing;
    BOOL    m_bDragShowContent;
    UINT    m_nDockBarID;
    int     m_cxEdge;
    int     m_cyGripper;

    CSCBButton m_biHide;

// Generated message map functions
protected:
    //{{AFX_MSG(CSizingControlBar)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnNcPaint();
    afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
    afx_msg LRESULT OnNcHitTest(CPoint point);
    afx_msg void OnCaptureChanged(CWnd *pWnd);
    afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
    afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
    afx_msg void OnPaint();
    //}}AFX_MSG
    afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);

    DECLARE_MESSAGE_MAP()
    friend class CSCBMiniDockFrameWnd;
};

/////////////////////////////////////////////////////////////////////////
// CSCBDockContext dockcontext

class CSCBDockContext : public CDockContext
{
public:
// Construction
    CSCBDockContext(CControlBar* pBar) : CDockContext(pBar) {}

// Drag Operations
    virtual void StartDrag(CPoint pt);
};

/////////////////////////////////////////////////////////////////////////
// CSCBMiniDockFrameWnd miniframe

#ifndef baseCSCBMiniDockFrameWnd
#define baseCSCBMiniDockFrameWnd CMiniDockFrameWnd
#endif

class CSCBMiniDockFrameWnd : public baseCSCBMiniDockFrameWnd
{
    DECLARE_DYNCREATE(CSCBMiniDockFrameWnd)

// Implementation
public:
    CSizingControlBar* GetSizingControlBar();

    //{{AFX_MSG(CSCBMiniDockFrameWnd)
    afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#endif // !defined(__SIZECBAR_H__)

