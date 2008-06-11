// AttachLibDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gmeactivebrowser.h"
#include "AttachLibDlg.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <stdlib.h>
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////
// CAttachLibDlg dialog


CAttachLibDlg::CAttachLibDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAttachLibDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAttachLibDlg)
	m_strConnString = _T("");
	m_bOptimized = FALSE;
	//}}AFX_DATA_INIT
}


void CAttachLibDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAttachLibDlg)
	DDX_Text(pDX, IDC_CONN_STRING, m_strConnString);
	DDX_Check(pDX, IDC_CHECKOPTIMIZED, m_bOptimized);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAttachLibDlg, CDialog)
	//{{AFX_MSG_MAP(CAttachLibDlg)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAttachLibDlg message handlers

void CAttachLibDlg::OnOK() 
{

	if(!UpdateData(TRUE))return;
	CDialog::OnOK();
}

void CAttachLibDlg::OnBrowse() 
{

	static char BASED_CODE szFilter[] = "Binary Project Files (*.mga)|*.mga|Multiuser Project Files (*.mgx)|*.mgx|All Files (*.*)|*.*||";

	CFileDialog dlg(TRUE,"mga",NULL,NULL,szFilter, this);
	if(dlg.DoModal()!=IDOK) return;

	bool is_mga = dlg.GetFileExt().CompareNoCase( "mga") == 0;
	if( is_mga)
		m_strConnString = "MGA=" + dlg.GetPathName();
	else
		m_strConnString = "MGX=\"" + dlg.GetPathName().Left( dlg.GetPathName().ReverseFind( '\\')) + "\"";

	UpdateData(FALSE);
	
}

BOOL CAttachLibDlg::OnInitDialog() 
{
	// convenience for beta-testers
	int pos = m_strConnString.Find( " (optimized)");
	if( pos != -1) // remove if found
	{
		m_bOptimized = TRUE;
		m_strConnString = m_strConnString.Left( pos);
	}
	// end of special section // REMOVE later

	// show the expanded path as a hint
	// when env variable found
	CString hint = m_strConnString;
	pos = hint.Find( "%");
	if( pos != -1) // found
	{
		int npos = hint.Find( "%", pos + 1); //next pos
		if( npos != -1 && npos > pos + 1)
		{
			// get the value of the environment variable between the two %'s
			char *value = getenv( hint.Mid( pos + 1, npos - pos - 1));
			hint.Replace( "%" + hint.Mid( pos + 1, npos - pos - 1) + "%", value);
		}
	}

	// show hint if needed: it differs from m_strConnString
	CWnd *ptr = GetDlgItem( IDC_CONNSTR);
	if( ptr && hint != m_strConnString)
	{
		// replace "Mga Connection String" with expanded path
		ptr->SetWindowText( (LPCTSTR) hint);
	}

	CDialog::OnInitDialog();
	
	SetWindowText(m_strCaption);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
