// Options.cpp : implementation file
//

#include "stdafx.h"
#include "Options.h"
#include "EventsDial.h"
#include "MyUtil.h"
#include <afxdlgs.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*static*/ const std::string Options::OptionsRegistrySubNode_str = "MetaGME_Options/GeneratedConstraints";
/*static*/ const std::string Options::RegContMask_str = "RegularContainmentEventMask";
/*static*/ const std::string Options::FolContMask_str = "FolderContainmentEventMask";
/*static*/ const std::string Options::ConnectMask_str = "ConnectionEndEventMask";
/*static*/ const std::string Options::Priority_str = "Priority";
/*static*/ const std::string Options::DontAsk_str = "skip_dialog";

/////////////////////////////////////////////////////////////////////////////
// Options dialog

Options::Options(CWnd* pParent /*=NULL*/)
	: CDialog(Options::IDD, pParent)
	, m_valRegContMask( 0 )
	, m_valFolContMask( 0 )
	, m_valConnectMask( 0 )
	, m_valPriority   ( 1 )

{
	//{{AFX_DATA_INIT(Options)
	m_strRegCont = _T("");
	m_strFolCont = _T("");
	m_strConnect = _T("");
	m_dontask = FALSE;
	m_strPriority = _T("");
	//}}AFX_DATA_INIT
}


void Options::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Options)
	DDX_Control(pDX, IDC_SPIN1, m_spin);
	DDX_Text(pDX, IDC_EDIT1, m_strRegCont);
	DDV_HexNumber(pDX, m_strRegCont);
	DDV_MaxChars(pDX, m_strRegCont, 10);
	DDX_Text(pDX, IDC_EDIT2, m_strFolCont);
	DDV_HexNumber(pDX, m_strFolCont);
	DDV_MaxChars(pDX, m_strFolCont, 10);
	DDX_Text(pDX, IDC_EDIT3, m_strConnect);
	DDV_HexNumber(pDX, m_strConnect);
	DDV_MaxChars(pDX, m_strConnect, 10);
	DDX_Check(pDX, IDC_CHECK1, m_dontask);
	DDX_Text(pDX, IDC_EDIT4, m_strPriority);
	DDV_MaxChars(pDX, m_strPriority, 2);
	DDV_MinMaxInt(pDX, atoi( m_strPriority), 1, 10);
	//}}AFX_DATA_MAP
}

void PASCAL Options::DDV_HexNumber(CDataExchange* pDX, const CString& nmb)
{
	if( !pDX->m_bSaveAndValidate) return;

	CString whitespace = " \t\n";
	CString digits = "0123456789";
	CString hexadigits = "0123456789abcdefABCDEF";
	bool fail = false;
	int i = 0;

	//skip whitespaces
	while( i < nmb.GetLength() && whitespace.Find( nmb.GetAt( i)) != -1) ++i;
	
	if( i == nmb.GetLength()) //empty
	{
		return;//do not fail if empty string, will be considered 0
	}

	bool hex = false;
	if( i + 1 < nmb.GetLength() && nmb.GetAt(i) == '0' && (nmb.GetAt(i + 1) == 'x' || nmb.GetAt(i + 1) == 'X'))
	{
		i += 2;
		hex = true;
		digits = hexadigits;
	}

	while( i < nmb.GetLength() && digits.Find( nmb.GetAt(i)) != -1) ++i;
	
	fail = i < nmb.GetLength();

	if( fail)
	{
		AfxMessageBox("Enter a hexadecimal value please!", MB_ICONERROR);
		pDX->Fail();
	}
}

BEGIN_MESSAGE_MAP(Options, CDialog)
	//{{AFX_MSG_MAP(Options)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_CHECK1, OnDontAskClick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Options message handlers
BOOL Options::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	char buff[32];
	sprintf( buff, "0x%08X", m_valRegContMask);
	m_strRegCont = buff;
	sprintf( buff, "0x%08X", m_valFolContMask);
	m_strFolCont = buff;
	sprintf( buff, "0x%08X", m_valConnectMask);
	m_strConnect = buff;
	sprintf( buff, "%d", m_valPriority);
	m_strPriority = buff;
	
	m_spin.SetRange( 1, 10);
	m_spin.SetPos( m_valPriority);

	UpdateData( FALSE);

	return TRUE;
}

void Options::OnButton1()
{
	UpdateData( TRUE);
	EventsDial d;

	int val = 0;
	if( sscanf( m_strRegCont, "%X", &val) == 1)
		d.m_sumAll = val;

	if( d.DoModal() == IDOK)
	{
		char buff[32];
		sprintf( buff, "0x%08X", d.m_sumAll);
		m_strRegCont = buff;
		m_valRegContMask = d.m_sumAll;
	}

	UpdateData( FALSE);
}

void Options::OnButton2() 
{
	UpdateData( TRUE);
	EventsDial d;

	int val = 0;
	if( sscanf( m_strFolCont, "%X", &val) == 1)
		d.m_sumAll = val;

	if( d.DoModal() == IDOK)
	{
		char buff[32];
		sprintf( buff, "0x%08X", d.m_sumAll);
		m_strFolCont = buff;
		m_valFolContMask = d.m_sumAll;
	}

	UpdateData( FALSE);
}

void Options::OnButton3() 
{
	UpdateData( TRUE);
	EventsDial d;

	int val = 0;
	if( sscanf( m_strConnect, "%X", &val) == 1)
		d.m_sumAll = val;

	if( d.DoModal() == IDOK)
	{
		char buff[32];
		sprintf( buff, "0x%08X", d.m_sumAll);
		m_strConnect = buff;
		m_valConnectMask = d.m_sumAll;
	}

	UpdateData( FALSE);
}

void Options::setDefs( int reg_cont, int fol_cont, int conn_msk, int prior)
{
	m_valRegContMask = reg_cont;
	m_valFolContMask = fol_cont;
	m_valConnectMask = conn_msk;
	m_valPriority    = prior;
}


void Options::getResults( int* v1, int* v2, int* v3, int* vp, bool* dont_ask)
{
	*v1 = m_valRegContMask;
	*v2 = m_valFolContMask;
	*v3 = m_valConnectMask;
	*vp = m_valPriority;

	*dont_ask = m_dontask == TRUE;
}


/*static*/ bool Options::fetchOpts( IMgaProject* proj, int* v1, int* v2, int* v3, int *pr)
{
	CComPtr<IMgaFolder>  rf;
	COMTHROW( proj->get_RootFolder( &rf));

	CComPtr<IMgaRegNode> rn;
	COMTHROW( rf->get_RegistryNode( CComBSTR( OptionsRegistrySubNode_str.c_str()), &rn));

	//BON::RegistryNode rn = proj->getRootFolder()->getRegistry()->getChild( OptionsRegistrySubNode_str);
	if( !rn) return true;

	CComBSTR vl;
	COMTHROW( rn->get_Value( &vl));
	//if( rn->getValue() == DontAsk_str)
	if( Util::Copy( vl) == DontAsk_str)
	{
		return false;
	}
	else
	{
		CComBSTR b_value; std::string value;
		long status = 0; 

		CComPtr<IMgaRegNode> ch1;
		COMTHROW( rn->get_SubNodeByName( Util::Copy( RegContMask_str), &ch1));
		if( ch1) COMTHROW( ch1->get_Status( &status));
		if( ch1) COMTHROW( ch1->get_Value( &b_value));
		value = Util::Copy( b_value);
		if( ch1 && status == 0) // 0: here, -1: in meta, >=1: inherited
			status = sscanf( value.c_str(), "%x", v1); //number stored in hexadecimal format
		
		CComPtr<IMgaRegNode> ch2;
		COMTHROW( rn->get_SubNodeByName( Util::Copy( FolContMask_str), &ch2));
		if( ch2) COMTHROW( ch2->get_Status( &status));
		if( ch2) COMTHROW( ch2->get_Value( &b_value));
		value = Util::Copy( b_value);
		if( ch2 && status == 0)
			status = sscanf( value.c_str(), "%x", v2);
		
		CComPtr<IMgaRegNode> ch3;
		COMTHROW( rn->get_SubNodeByName( Util::Copy( ConnectMask_str), &ch3));
		if( ch3) COMTHROW( ch3->get_Status( &status));
		if( ch3) COMTHROW( ch3->get_Value( &b_value));
		value = Util::Copy( b_value);
		if( ch3 && status == 0)
			status = sscanf( value.c_str(), "%x", v3);

		CComPtr<IMgaRegNode> ch4;
		COMTHROW( rn->get_SubNodeByName( Util::Copy( Priority_str), &ch4));
		if( ch4) COMTHROW( ch4->get_Status( &status));
		if( ch4) COMTHROW( ch4->get_Value( &b_value));
		value = Util::Copy( b_value);
		if( ch4 && status == 0)
		{
			//*pr = ch4->getIntegerValue();
			status = sscanf( value.c_str(), "%d", pr);
		}
	}
	return true;
}


/*static*/ void Options::saveOpts( IMgaProject* proj, int v1, int v2, int v3, int vp, bool dont_ask)
{
	char buff[ 10 + 1 ];

	CComPtr<IMgaFolder>  rf;
	COMTHROW( proj->get_RootFolder( &rf));

	sprintf( buff, "0x%08X", v1);
	COMTHROW( rf->put_RegistryValue( Util::Copy( std::string( OptionsRegistrySubNode_str + "/" + RegContMask_str)), CComBSTR( buff)));

	sprintf( buff, "0x%08X", v2);
	COMTHROW( rf->put_RegistryValue( Util::Copy( std::string( OptionsRegistrySubNode_str + "/" + FolContMask_str)), CComBSTR( buff)));

	sprintf( buff, "0x%08X", v3);
	COMTHROW( rf->put_RegistryValue( Util::Copy( std::string( OptionsRegistrySubNode_str + "/" + ConnectMask_str)), CComBSTR( buff)));

	sprintf( buff, "%d", vp);
	COMTHROW( rf->put_RegistryValue( Util::Copy( std::string( OptionsRegistrySubNode_str + "/" + Priority_str)), CComBSTR( buff)));

	if( dont_ask) COMTHROW( rf->put_RegistryValue( Util::Copy( std::string( OptionsRegistrySubNode_str)), Util::Copy( DontAsk_str)));
}


void Options::OnOK() 
{
	CDialog::OnOK();//UpdateData( TRUE);

	if( m_strRegCont.IsEmpty() || !sscanf( (LPCTSTR) m_strRegCont, "%x", &m_valRegContMask)) m_valRegContMask = 0;
	if( m_strFolCont.IsEmpty() || !sscanf( (LPCTSTR) m_strFolCont, "%x", &m_valFolContMask)) m_valFolContMask = 0;
	if( m_strConnect.IsEmpty() || !sscanf( (LPCTSTR) m_strConnect, "%x", &m_valConnectMask)) m_valConnectMask = 0;

	m_valPriority = atoi( m_strPriority);
	if( !m_valPriority) m_valPriority = 1;

}

void Options::OnDontAskClick() 
{
	if( ((CButton * ) GetDlgItem( IDC_CHECK1))->GetCheck())
		if( IDCANCEL == MessageBox( CString("If you leave this option checked you can access this dialog later only if you modify the \"") + OptionsRegistrySubNode_str.c_str() + "\" value in the RootFolder's registry to something else than \"" + DontAsk_str.c_str() + "\"!", "Warning!", MB_OKCANCEL | MB_ICONWARNING))
			((CButton *) GetDlgItem( IDC_CHECK1))->SetCheck( 0);
	
}
