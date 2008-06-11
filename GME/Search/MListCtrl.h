#pragma once


// CMListCtrl

class CMListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CMListCtrl)

public:
	CMListCtrl();
	virtual ~CMListCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
