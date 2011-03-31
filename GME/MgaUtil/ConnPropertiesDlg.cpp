// ConnPropertiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ConnPropertiesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConnPropertiesDlg dialog


CConnPropertiesDlg::CConnPropertiesDlg(
									   CString s,
									   CString sp,
									   CString d,
									   CString dp,
									   CString rol,
									   CString iden,
									   CString nm,
									   bool typ,
									   CString metaid,
									   CString kind,
									   CString aspect,
									   long relid,
									   CWnd* pParent /*=NULL*/)
	: CDialog(CConnPropertiesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConnPropertiesDlg)
	dst = d;
	dstPort = dp;
	id = iden;
	name = nm;
	src = s;
	srcPort = sp;
	m_objectid = iden;
	m_metaid = metaid;
	m_aspect = aspect;
	m_kind = kind;
	m_role = rol;
	m_relid = _T("");
	//}}AFX_DATA_INIT
	isType = typ;
	editflag = false;
	m_relid.Format(_T("0x%08X"), relid);
}


void CConnPropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConnPropertiesDlg)
	DDX_Control(pDX, IDC_CONNNAME, nameBox);
	DDX_Text(pDX, IDC_CONNDST, dst);
	DDX_Text(pDX, IDC_CONNDSTPORT, dstPort);
	DDX_Text(pDX, IDC_CONNID, id);
	DDX_Text(pDX, IDC_CONNNAME, name);
	DDX_Text(pDX, IDC_CONNSRC, src);
	DDX_Text(pDX, IDC_CONNSRCPORT, srcPort);
	DDX_Text(pDX, IDC_CONNOBJID, m_objectid);
	DDX_Text(pDX, IDC_METAID, m_metaid);
	DDX_Text(pDX, IDC_ASPECT, m_aspect);
	DDX_Text(pDX, IDC_CONNTYPE, m_kind);
	DDX_Text(pDX, IDC_CONNROLE, m_role);
	DDX_Text(pDX, IDC_RELID, m_relid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConnPropertiesDlg, CDialog)
	//{{AFX_MSG_MAP(CConnPropertiesDlg)
	ON_BN_CLICKED(IDC_SETRELID, OnSetrelid)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConnPropertiesDlg message handlers

BOOL CConnPropertiesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	nameBox.SetReadOnly(!isType);
	
	this->m_sz_pre_edit_name = name;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConnPropertiesDlg::OnSetrelid() 
{
	GetDlgItem(IDC_RELID)->EnableWindow(editflag = !editflag);
}

