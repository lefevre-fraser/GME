#pragma once


// CDummyEdit

class CDummyEdit : public CEdit
{
	DECLARE_DYNAMIC(CDummyEdit)

public:
	CDummyEdit();
	virtual ~CDummyEdit();
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

protected:
	DECLARE_MESSAGE_MAP()
};


