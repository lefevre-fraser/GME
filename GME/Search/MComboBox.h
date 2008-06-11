#pragma once


// CMComboBox

class CMComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CMComboBox)

public:
	CMComboBox();
	virtual ~CMComboBox();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
