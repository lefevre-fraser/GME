// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__BD235B4F_BD3F_11D3_91E2_00104B98EAD9__INCLUDED_)
#define AFX_MAINFRM_H__BD235B4F_BD3F_11D3_91E2_00104B98EAD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GMEPartBrowser.h"
#include "GMEBrowser.h"
#include "GMEObjectInspector.h"
#include "GMEConsole.h"
#include "GMESearch.h"
#include "GMEPanningWindow.h"
#include "GMEOLEApp.h"

// #include "..\include\stl\string"
//#include <string>


// Tooltip helper for components
class CComponentBar : public CMFCToolBar {
	DECLARE_DYNCREATE(CComponentBar)
	afx_msg BOOL OnTT(UINT, NMHDR * pNMHDR, LRESULT * );
	DECLARE_MESSAGE_MAP()
};

class CMainFrame : public CMDIFrameWndEx
{
	friend void CGMEApp::UpdateComponentLists(bool restart_addons);
	friend class CGMEOLEApp;
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:
	static CMainFrame *theInstance;

	int timePaneNo;
	int paradigmPaneNo;
	int modePaneNo;
	int zoomPaneNo;

// Operations
public:
	void ActivateView(CView *view);
	void CreateNewView(CView *view, CComPtr<IMgaModel>& model);
	void DestroyView(CView *view);
	void WriteStatusZoom(int zoomPct);
	void WriteStatusParadigm(const char *txt);
	void WriteStatusMode(const char *txt);
	void WriteStatusText(int pane,const char *txt);
	void UpdateTitle(LPCTSTR title);
	void SetPartBrowserMetaModel(CGuiMetaModel* meta)	{ m_partBrowser.SetMetaModel(meta); }
	void SetPartBrowserBg(COLORREF bgColor)				{ m_partBrowser.SetBgColor(bgColor); m_partBrowser.RePaint(); }
	void RePaintPartBrowser()							{ m_partBrowser.RePaint(); }
	void ChangePartBrowserAspect(int ind)				{ m_partBrowser.ChangeAspect(ind); }
	void CyclePartBrowserAspect()						{ m_partBrowser.CycleAspect(); }
	void SetGMEViewMetaModel(CGuiMetaModel* meta);
	void ChangeGMEViewAspect(int ind);
	void CycleGMEViewAspect();
	void GMEViewInvalidate();
	BOOL CMainFrame::VerifyBarState(LPCTSTR lpszProfileName);
	void OnDeleteDCForPanningVindowCtrl(CDC* bCDC);
	void ShowObjectInspector();
	void ShowFindDlg();
	void HideFindDlg();

	void StartAutosaveTimer(int secs);
	void StopAutosaveTimer();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();

	void setGmeOleApp( CGMEOLEApp * the_ole_app);
	void setMgaProj();
	void clearGmeOleApp();
	void clearMgaProj();
	CGMEOLEApp *       mGmeOleApp;

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CGMEPanningWindow	m_panningWindow;
	CGMEConsole			m_console;


protected:  // control bar embedded members
	CMFCStatusBar		m_wndStatusBar;
	CMFCToolBar			m_wndToolBarMain;
	CMFCToolBar			m_wndToolBarWins;
	CMFCMenuBar			m_wndMenuBar;


	CComponentBar		m_wndComponentBar;
//	CDialogBar			m_wndDlgBar;
	CGMEPartBrowser		m_partBrowser;
	CGMEBrowser			m_browser;
	CGMEObjectInspector	m_objectInspector;
	CGMESearch			m_search;

	UINT				m_autosaveTimerID;

// Generated message map functions
protected:
	afx_msg void OnUpdateTime(CCmdUI* pCmdUI);
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	/* @@@afx_msg void OnViewPartbrowser();
	afx_msg void OnViewPannWin();
	afx_msg void OnUpdateViewPannWin(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewPartbrowser(CCmdUI* pCmdUI);
	afx_msg void OnViewBrowser();
	afx_msg void OnUpdateViewBrowser(CCmdUI* pCmdUI);
	afx_msg void OnViewAttributes();
	afx_msg void OnUpdateViewAttributes(CCmdUI* pCmdUI);
	afx_msg void OnViewConsole();
	afx_msg void OnUpdateViewConsole(CCmdUI* pCmdUI);

	*/
	afx_msg void OnViewFullScreen();
	afx_msg void OnEditSearch();
	afx_msg void OnUpdateEditSearch(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnViewMultiUserRefreshSourceControl();
	afx_msg void OnUpdateViewMultiUserRefreshSourceControl(CCmdUI* pCmdUI);
	afx_msg void OnViewMultiUserActiveUsers();
	afx_msg void OnViewMultiUserSubversion();
	afx_msg void OnUpdateViewMultiUserActiveUsers(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewMultiUserSubversion(CCmdUI* pCmdUI);
	afx_msg void OnViewClearConsole();
	afx_msg void OnUpdateViewClearConsole( CCmdUI* pCmdUI);
	afx_msg void CMainFrame::OnClose();
	afx_msg void OnDropFiles(HDROP);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);

	afx_msg void OnBtnBack();
	afx_msg void OnBtnHome();
	afx_msg void OnUpdateBtnBack(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBtnHome(CCmdUI* pCmdUI);

	afx_msg void OnWindowManager();
	afx_msg void OnViewCustomize();

	afx_msg void OnMdiMoveToNextGroup();
	afx_msg void OnMdiMoveToPrevGroup();
	afx_msg void OnMdiNewHorzTabGroup();
	afx_msg void OnMdiNewVertGroup();
	LRESULT OnToolbarCreateNew(WPARAM wp,LPARAM lp);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL InitStatusBar(UINT *pIndicators, int nSize, int nSeconds);
	int CreateToolBars();
	void OnApplicationLook(UINT id);
//	IMgaObject*	modelFindByPath(IMgaModel *model,  const wstring& strPath);
//	IMgaObject*	folderFindByPath(IMgaFolder* folder, const wstring& strPath);

public:
	afx_msg void OnWindowNewhorizontaltabgroup();
	afx_msg void OnWindowNewverticaltabgroup();
	afx_msg void OnWindowMovetoprevioustabgroup();
	afx_msg void OnWindowMovetonexttabgroup();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__BD235B4F_BD3F_11D3_91E2_00104B98EAD9__INCLUDED_)
