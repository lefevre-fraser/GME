// XSLTDial.cpp : implementation file
//

#include "stdafx.h"
#include "mgautil.h"
#include "XSLTDial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXSLTDial dialog


CXSLTDial::CXSLTDial(CWnd* pParent /*=NULL*/)
	: CDialog(CXSLTDial::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXSLTDial)
	m_stylesheetFileName = _T("");
	m_inputXmlFileName = _T("");
	m_outputXmlFileName = _T("");
	//}}AFX_DATA_INIT
}


void CXSLTDial::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXSLTDial)
	DDX_Text(pDX, IDC_EDIT1, m_stylesheetFileName);
	DDX_Text(pDX, IDC_EDIT2, m_inputXmlFileName);
	DDX_Text(pDX, IDC_EDIT3, m_outputXmlFileName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CXSLTDial, CDialog)
	//{{AFX_MSG_MAP(CXSLTDial)
	ON_BN_CLICKED(IDC_BUTTON1, OnFileSelection1)
	ON_BN_CLICKED(IDC_BUTTON2, OnFileSelection2)
	ON_BN_CLICKED(IDC_BUTTON3, OnFileSelection3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXSLTDial message handlers

void CXSLTDial::OnFileSelection1() 
{
	CWaitCursor wait;
	CFileDialog dlg(TRUE, "xsl", "",
		OFN_EXPLORER,
		"XSL Stylesheet Files (*.xsl)|*.xsl|All Files (*.*)|*.*||");
	if( dlg.DoModal() == IDOK) 
	{
		this->UpdateData( TRUE);

		m_stylesheetFileName = dlg.GetPathName();
		int idx = m_stylesheetFileName.ReverseFind('\\');
		CString dir;
		if ( idx != -1)
			dir = m_stylesheetFileName.Left( idx + 1);

		if ( m_outputXmlFileName.IsEmpty())
			m_outputXmlFileName = dir;
		if ( m_inputXmlFileName.IsEmpty())
			m_inputXmlFileName = dir;

		this->UpdateData( FALSE);
	}
}

void CXSLTDial::OnFileSelection2() 
{
	CWaitCursor wait;
	CFileDialog dlg(TRUE, "xme", "",
		OFN_EXPLORER,
		"GME Exported Files (*.xme;*.xml)|*.xme; *.xml|All Files (*.*)|*.*||");
	if( dlg.DoModal() == IDOK) 
	{
		this->UpdateData( TRUE);
		m_inputXmlFileName = dlg.GetPathName();
		this->UpdateData( FALSE);
	}
}

void CXSLTDial::OnFileSelection3() 
{
	CWaitCursor wait;
	CFileDialog dlg(FALSE, "xme", "",
		OFN_EXPLORER | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"GME Exported Files (*.xme;*.xml)|*.xme; *.xml|All Files (*.*)|*.*||");
	if( dlg.DoModal() == IDOK) 
	{
		this->UpdateData( TRUE);
		m_outputXmlFileName = dlg.GetPathName();
		this->UpdateData( FALSE);
	}
}

void CXSLTDial::OnOK() 
{
	this->UpdateData( TRUE);

	if ( m_inputXmlFileName == ""
		|| m_stylesheetFileName == ""
		|| m_outputXmlFileName == "" )
	{
		AfxMessageBox("Please select stylesheet, input and output files!", MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	CDialog::OnOK();
}
