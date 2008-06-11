#pragma once


// CMButton

class CMButton : public CButton
{
	DECLARE_DYNAMIC(CMButton)

public:
	CMButton();
	virtual ~CMButton();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
