// NewXmlbackendProjDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gme.h"
#include "NewXmlbackendProjDlg.h"
#include <direct.h>
#include "..\XmlBackEnd\svauto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewXmlbackendProjDlg dialog


CNewXmlbackendProjDlg::CNewXmlbackendProjDlg(CWnd* pParent /*=NULL*/)
: CDialog(CNewXmlbackendProjDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewXmlbackendProjDlg)
	m_location = _T("");
	m_projectName = _T("");
	m_svnUrl  = _T("");
	m_sourceControlType = 0;
	m_hashedFileStorage = 0;
	//}}AFX_DATA_INIT
}


void CNewXmlbackendProjDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewXmlbackendProjDlg)
	DDX_Control(pDX, IDC_EDIT_SVNDATABASE, m_svnUrlCtrl);
	DDX_Control(pDX, IDC_STATIC_SUBVERSION_URLLABEL, m_svnUrlLabel);
	DDX_Control(pDX, IDC_STATIC_SVN, m_svnBorder);
	DDX_Control(pDX, IDC_BUTTON_SVNTRY, m_svnTryBtn);
	DDX_Text(pDX, IDC_EDIT_LOCATION, m_location);
	DDX_Text(pDX, IDC_EDIT_PROJNAME, m_projectName);
	DDX_Text(pDX, IDC_EDIT_SVNDATABASE, m_svnUrl);
	DDX_Radio(pDX, IDC_RADIO_SUBVERSION, m_sourceControlType);
	DDX_Check(pDX, IDC_CHECK_SPLITTOSUBDIRS, m_hashedFileStorage);
	DDX_Control(pDX, IDC_COMBO_SPLITALG, m_hashAlgoControl);
	//}}AFX_DATA_MAP
}

void CNewXmlbackendProjDlg::enableSubversionControls( bool enable )
{
	m_svnTryBtn.EnableWindow( enable);
	m_svnBorder.EnableWindow( enable );
	m_svnUrlLabel.EnableWindow( enable );
	m_svnUrlCtrl.EnableWindow( enable );

	//if( GetDlgItem(IDC_STATIC_SVN)          GetDlgItem( IDC_STATIC_SVN)->EnableWindow( enable);
	//if( GetDlgItem(IDC_STATIC_VSSDB2)) GetDlgItem(IDC_STATIC_VSSDB2)->EnableWindow( enable);
	//if( GetDlgItem(IDC_STATIC_VSSDB3)) GetDlgItem(IDC_STATIC_VSSDB3)->EnableWindow( enable);
	if( GetDlgItem(IDC_STATIC_SUBVERSION))  GetDlgItem(IDC_STATIC_SUBVERSION)->EnableWindow( enable);
	if( GetDlgItem(IDC_STATIC_SUBVERSION2)) GetDlgItem(IDC_STATIC_SUBVERSION2)->EnableWindow( enable);
}

BEGIN_MESSAGE_MAP(CNewXmlbackendProjDlg, CDialog)
	//{{AFX_MSG_MAP(CNewXmlbackendProjDlg)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_LOC, OnButtonBrowseLoc)
	ON_BN_CLICKED(IDC_RADIO_SUBVERSION, OnSourceControlChanged)
	ON_BN_CLICKED(IDC_RADIO_NONE, OnSourceControlChanged)
	ON_BN_CLICKED(IDC_CHECK_SPLITTOSUBDIRS, OnBnClickedCheckSplittosubdirs)
	ON_BN_CLICKED(IDC_BUTTON_SVNTRY, OnBnClickedButtonSvnTry)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CNewXmlbackendProjDlg message handlers

void CNewXmlbackendProjDlg::OnButtonBrowseLoc() 
{
	BROWSEINFO bi;

	char szDisplayName[MAX_PATH];
	char szPath[MAX_PATH];

	bi.hwndOwner      = m_hWnd;
	bi.pidlRoot       = NULL;
	bi.lpszTitle      = "Select the project location.";
	bi.pszDisplayName = szDisplayName;
	bi.ulFlags        = BIF_RETURNONLYFSDIRS;
	bi.lpfn           = NULL;
	bi.lParam         = 0;

	LPITEMIDLIST idlist = SHBrowseForFolder(&bi);

	if( idlist && SHGetPathFromIDList(idlist, szPath) )
	{
		UpdateData();
		m_location = szPath;
		UpdateData(FALSE);
	}
}

void CNewXmlbackendProjDlg::OnSourceControlChanged() 
{
	UpdateData();

	enableSubversionControls( m_sourceControlType == 0 );
}

void CNewXmlbackendProjDlg::OnOK()
{
	UpdateData();
	if( m_projectName.Trim().IsEmpty() || m_location.Trim().IsEmpty())
	{
		AfxMessageBox( "Project location and name must not be empty!");
		return;
	}

	WIN32_FILE_ATTRIBUTE_DATA attr;
	if( GetFileAttributesEx( m_location, GetFileExInfoStandard, &attr ) )
	{
		if( FILE_ATTRIBUTE_DIRECTORY != ( attr.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			if( IDOK != AfxMessageBox( m_location + " does not seem to be a directory. Do you still want to use this location for your project?", MB_YESNO))
				return; // if answered NO, return, which means dialog is not closed
	}
	else
		if( IDOK != AfxMessageBox( m_location + " does not seem to exist, but it might be created during the checkout process. Do you want to continue?", MB_YESNO))
			return; // if answered NO, return, which means dialog is not closed

	if( m_sourceControlType == 0 && 
	    (m_svnUrl.Left( 6) != "svn://" 
	    && m_svnUrl.Left(10) != "svn+ssh://"
	    && m_svnUrl.Left(7) != "http://"
	    && m_svnUrl.Left(8) != "https://"))
	{
		AfxMessageBox( "URL must be provided in one of the svn://host[/dir], svn+ssh://[username@]host[/dir] or https://host[/dir] form");
		return;
	}

	m_connectionString = "MGX=\"";
	m_connectionString += m_location.Trim();
	// http://escher.isis.vanderbilt.edu/JIRA/browse/GME-148 : JIRA entry created
	// if m_location contains a tailing '\' then no need for this
	if( m_location.TrimRight().Right(1) != '\\')
		m_connectionString += "\\";
	m_connectionString += m_projectName.Trim();
	m_connectionString += "\"";

	if( m_svnUrl.Right(1) == '/') // cut off tailing '/'
		m_svnUrl = m_svnUrl.Left( m_svnUrl.GetLength() - 1 );

	if( m_sourceControlType == 0 )
	{
		//if( !m_svnUrl.IsEmpty())
		m_connectionString += " svn=\"";
		m_connectionString += m_svnUrl;
		m_connectionString += "\"";
		char gmepath[200];
		if(SHGetSpecialFolderPath( NULL, gmepath, CSIDL_APPDATA, true)) //most likely C:\Documents and Settings\<username>\Application Data
		{
			WIN32_FILE_ATTRIBUTE_DATA attr;
			BOOL res;
			CString path;

			int nb_errs = 0;
			path = CString( gmepath) + "\\Subversion";
			res = GetFileAttributesEx( path, GetFileExInfoStandard, &attr );
			if( res && ( FILE_ATTRIBUTE_DIRECTORY == (attr.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))) { } else
				nb_errs += _mkdir( (LPCTSTR) path);

			path = CString( gmepath) + "\\Subversion\\auth";
			res = GetFileAttributesEx( path, GetFileExInfoStandard, &attr );
			if( res && ( FILE_ATTRIBUTE_DIRECTORY == (attr.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))) { } else
				nb_errs += _mkdir( (LPCTSTR) path);

			if( nb_errs == 0)
			{
				path = CString(gmepath) + "\\Subversion\\auth\\svn.simple";
				res = GetFileAttributesEx( path, GetFileExInfoStandard, &attr );
				if( res && ( FILE_ATTRIBUTE_DIRECTORY == (attr.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))) { } else
				{
					nb_errs += _mkdir((LPCTSTR) path); //in case dir is not there, make it, if it was there will fail
					if( !nb_errs) 
						AfxMessageBox( path + " directory created that the credentials could be stored later.");
				}

				path = CString(gmepath) + "\\Subversion\\auth\\svn.ssl.server";
				res = GetFileAttributesEx( path, GetFileExInfoStandard, &attr );
				if( res && ( FILE_ATTRIBUTE_DIRECTORY == (attr.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))) { } else
				{
					int l_errs = _mkdir((LPCTSTR) path); //in case dir is not there, make it, if it was there will fail
					if( !l_errs)
						AfxMessageBox( path + " directory created that the certificates could be stored later.");

					nb_errs += l_errs;
				}
			}

			if( nb_errs)
				AfxMessageBox( CString( "Could not create the local directories where credentials would be stored: \n") + 
				CString( gmepath) + "\\Subversion\\auth\\svn.simple\n" + 
				CString( gmepath) + "\\Subversion\\auth\\svn.ssl.server");
		}

	}

	if( m_hashedFileStorage == BST_CHECKED)
	{
		m_connectionString += " hash=\"true\"";
		int csel = m_hashAlgoControl.GetCurSel();
		if( csel < m_hashAlgoControl.GetCount() && csel >= 0)
		{
			CString res;
			m_hashAlgoControl.GetLBText( csel, res);

			if(      res == "4096")
				m_connectionString += " hval=\"4096\"";
			else if( res == "256")
				m_connectionString += " hval=\"256\"";
			else if( res == "3")
				m_connectionString += " hval=\"3\"";
			else if( res == "4")
				m_connectionString += " hval=\"4\"";
			else
			{
				AfxMessageBox( "Invalid hash method selected");
				return;
			}
		}
	}

	CDialog::OnOK();
}


BOOL CNewXmlbackendProjDlg::OnInitDialog()
{
	// init m_svnUrl like this while testing to avoid typing too much
	m_svnUrl = "svn+ssh://zolmol@svn.isis.vanderbilt.edu/export/svn/testrepo/gme/zoli";
	m_svnUrl = "https://svn.isis.vanderbilt.edu/testrepo/gme/zoli";
	// init like this when going live
	m_svnUrl = "svn+ssh://<usernamehere>@<hostnamehere>";
	CDialog::OnInitDialog();

	enableSubversionControls( m_sourceControlType == 0 );
	m_hashAlgoControl.SetCurSel( 0);
	m_hashAlgoControl.EnableWindow(  1 == m_hashedFileStorage);

	return TRUE;
}

void CNewXmlbackendProjDlg::OnBnClickedCheckSplittosubdirs()
{
	UpdateData( TRUE);
	m_hashAlgoControl.EnableWindow( 1 == m_hashedFileStorage);
}

void CNewXmlbackendProjDlg::OnBnClickedButtonSvnTry()
{
	UpdateData( TRUE);
	if( m_sourceControlType != 0 || m_svnUrl.IsEmpty()) {
		AfxMessageBox( "Please select Subversion for the Source Control option and provide a URL for the server");
		return;
	}

	CComPtr<ISvnTester> p;
	p.CoCreateInstance( L"Mga.XmlbackEnd.SvnTester");
	if( !p) {
		AfxMessageBox( "Test connection failed because could not create test object.");
		return;
	}

	CComBSTR       url   = m_svnUrl;
	CComBSTR       res;

	if( SUCCEEDED( p->info( url, VARIANT_FALSE, &res)))
	{
		CString r; CopyTo( res, r);
		r.Replace( "\n", "\r\n");

		CComPtr<ISvnWorkBench> wb;
		HRESULT hr = wb.CoCreateInstance( L"Mga.XmlBackEnd.SvnWorkBench");
		if( FAILED( hr) || !wb) {
			AfxMessageBox( "Could not create Svn Work Bench to show the result!");
			return;
		}

		wb->ShowResultDlg( CComBSTR( (LPCTSTR) r));
	}
	else
		AfxMessageBox( "Test connection failed with " + m_svnUrl);
}
