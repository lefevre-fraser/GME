// EmergencySaveDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EmergencySaveDlg.h"


/////////////////////////////////////////////////////////////////////////////
// EmergencySaveDlg dialog

IMPLEMENT_DYNAMIC(EmergencySaveDlg, CDialog)
EmergencySaveDlg::EmergencySaveDlg(CWnd* pParent):
	CDialog(EmergencySaveDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(EmergencySaveDlg)
	m_minidumpChecked = FALSE;
	//}}AFX_DATA_INIT
}

EmergencySaveDlg::~EmergencySaveDlg()
{
}

void EmergencySaveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(EmergencySaveDlg)
	DDX_Control(pDX, IDOK, m_buttonOK);
	DDX_Control(pDX, IDC_MINIDUMP_CHECK, m_checkboxMinidump);
	DDX_Control(pDX, IDC_EMERGENCY_INFO_STATIC, m_staticEmergencySaveInfo);
	DDX_Control(pDX, IDC_MINIDUMP_INFO_STATIC, m_staticMinidumpSaveInfo);
	DDX_Check(pDX, IDC_MINIDUMP_CHECK, m_minidumpChecked);
	DDX_Text(pDX, IDC_EMERGENCY_INFO_STATIC, m_strEmergencySaveInfo);
	DDX_Text(pDX, IDC_MINIDUMP_INFO_STATIC, m_strMinidumpSaveInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(EmergencySaveDlg, CDialog)
	//{{AFX_MSG_MAP(CDialogList)
	ON_BN_CLICKED(IDC_MINIDUMP_CHECK, OnMinidumpCheckboxClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// EmergencySaveDlg message handlers
BOOL EmergencySaveDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_checkboxMinidump.SetCheck((m_minidumpChecked == FALSE) ? 0 : 1);
	m_staticEmergencySaveInfo.SetWindowText(m_strEmergencySaveInfo);
	m_staticMinidumpSaveInfo.SetWindowText(m_strMinidumpSaveInfo);

	return TRUE;
}

void EmergencySaveDlg::OnMinidumpCheckboxClicked()
{
	m_minidumpChecked = (m_checkboxMinidump.GetCheck() == 0 ? FALSE : TRUE);
}

void EmergencySaveDlg::SetStrings(CString emergencySaveInfo, CString minidumpSaveInfo)
{
	m_strEmergencySaveInfo = emergencySaveInfo;
	m_strMinidumpSaveInfo = minidumpSaveInfo;
}

BOOL EmergencySaveDlg::ShouldWriteMiniDump(void)
{
	return m_minidumpChecked;
}

