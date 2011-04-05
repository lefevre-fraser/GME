// MetaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MgaUtil.h"
#include "MetaDlg.h"
#include "MetaPurgeDialog.h"
#include "MgaLauncher.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMetaDlg dialog


CMetaDlg::CMetaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMetaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMetaDlg)
	m_accessmode = 1;
	//}}AFX_DATA_INIT
}


void CMetaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMetaDlg)
	DDX_Control(pDX, IDC_PURGE, m_purge);
	DDX_Control(pDX, IDC_REMOVE, m_remove);
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Radio(pDX, IDC_RADIOSYS, m_accessmode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMetaDlg, CDialog)
	//{{AFX_MSG_MAP(CMetaDlg)
	ON_BN_CLICKED(IDC_ADDFILE, OnAddfile)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_ADDDB, OnAddDB)
	ON_BN_CLICKED(IDC_PURGE, OnPurge)
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMetaDlg message handlers

BOOL CMetaDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CListCtrl* listctrl = (CListCtrl*)GetDlgItem(IDC_LIST);
    DWORD dwStyle = listctrl->SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE,0,0);
    dwStyle |= LVS_EX_FULLROWSELECT;
    listctrl->SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dwStyle);



	MSGTRY
	{
		ASSERT( registrar == NULL );
		// Invoke IMgaregistrar through a COM surrogate (to support COM elevation under Vista)
		HRESULT hr = registrar.CoCreateInstance(OLESTR("MGA.MgaRegistrar"));

		ASSERT( registrar != NULL );

		if (flags == METADLG_PARREG) {
			GetDlgItem(IDOK)->SetWindowText(_T("Components..."));
		} else if (flags == METADLG_NONE) {
			GetDlgItem(IDOK)->SetWindowText(_T("Open"));
		} else if (flags == METADLG_NEWFILE) {
			GetDlgItem(IDOK)->SetWindowText(_T("Create New"));
		}

		{
			CRegKey accessTest;
			if (accessTest.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\GME"), KEY_READ | KEY_WRITE) == ERROR_ACCESS_DENIED) {
				GetDlgItem(IDC_RADIOSYS)->EnableWindow(false);
				GetDlgItem(IDC_RADIOUSER)->EnableWindow(false);
				GetDlgItem(IDC_RADIOBOTH)->EnableWindow(false);
			}
		}

		LV_COLUMN lvc;
		lvc.mask = LVCF_WIDTH | LVCF_TEXT;

		lvc.pszText = _T("Paradigm");
		lvc.cx = 100;
		VERIFYTHROW( m_list.InsertColumn(0, &lvc) != -1 );

		lvc.pszText = _T("S");
		lvc.cx = 20;
		VERIFYTHROW( m_list.InsertColumn(1, &lvc) != -1 );

		lvc.pszText = _T("Version");
		lvc.cx = 50;
		VERIFYTHROW( m_list.InsertColumn(2, &lvc) != -1 );

		lvc.pszText = _T("Connection string");
		lvc.cx = 500;
		VERIFYTHROW( m_list.InsertColumn(3, &lvc) != -1 );

		lvc.pszText = _T("GUID");
		lvc.cx = 300;
		VERIFYTHROW( m_list.InsertColumn(4, &lvc) != -1 );

		ResetItems();
	}
	MSGCATCH(_T("Error while initializing MetaDlg"),;)
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMetaDlg::ResetItems()
{
	m_remove.EnableWindow(false);
	GetDlgItem(IDOK)->EnableWindow(false);
	m_purge.EnableWindow(false);
	ASSERT( registrar != NULL );

	VERIFYTHROW( m_list.DeleteAllItems() != 0 );

	
	CComVariant vpars;
	COMTHROW( registrar->get_Paradigms(REGACCESS_BOTH, PutOut(vpars)) );

	CComBstrObjArray paradigms;
	MoveTo(vpars, paradigms);

	for(int i = 0; i < paradigms.GetSize(); ++i)
	{
		CString name;
		CString cstr;
		CString version;
		CComBstrObj guid2;

		CopyTo(paradigms[i], name);
		CComVariant v;

		CString mode = _T("u");
		if( registrar->QueryParadigm(paradigms[i], PutOut(cstr), PutOut(v), REGACCESS_USER) != S_OK) {
			mode = _T("s");
			if( registrar->QueryParadigm(paradigms[i], PutOut(cstr), PutOut(v), REGACCESS_SYSTEM) != S_OK) {
				AfxMessageBox(_T("Error reading registry data for paradigm ") + name);
				mode = _T("?");
				cstr = _T("????");
			}
		}
		if(v.vt != VT_EMPTY) {
			GUID guid;
			CopyTo(v, guid);

			CopyTo(guid, guid2);
		}
		
		HRESULT hr = registrar->VersionFromGUID(paradigms[i], v, PutOut(version), mode ==  'u' ? REGACCESS_USER : REGACCESS_SYSTEM);
		if (FAILED(hr)) {
			version = _T("N/A");
		}

		int j = m_list.InsertItem(i, name);
		VERIFYTHROW( j != -1 );
		VERIFYTHROW( m_list.SetItemText(j, 1, mode) != 0 );

		VERIFYTHROW( m_list.SetItemText(j, 2, version) != 0 );

		VERIFYTHROW( m_list.SetItemText(j, 3, cstr) != 0 );


		VERIFYTHROW( m_list.SetItemText(j, 4, PutInCString(guid2)) != 0 );
		if(name == to_select) m_list.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
	}
}

static TCHAR filter[] = 
	_T("Paradigm Files (*.xmp)|*.xmp|")
	_T("Exported Files (*.xme;*.xml)|*.xme; *.xml|")
	_T("MGA Meta Files (*.mta)|*.mta|")
	_T("Microsoft Access Files (*.mdb)|*.mdb|")
	_T("All Files (*.*)|*.*||");


void CMetaDlg::OnAddfile() 
{
	UpdateData();
	MSGTRY
	{
		CFileDialog dlg(true, NULL, NULL, 
			OFN_EXPLORER | OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
			filter);

		if( dlg.DoModal() != IDOK )
			return;

		CString conn;

		CString ext = dlg.GetFileExt();
		ext.MakeLower();

		if( ext == _T("") )
		{
			switch( dlg.m_ofn.nFilterIndex )
			{
			case 1:
				conn = CString(_T("XML=")) + dlg.GetPathName() + _T(".xmp");
				break;

			case 2:
				conn = CString(_T("MGA=")) + dlg.GetPathName() + _T(".mta");
				break;

			case 3:
				conn = CString(_T("DBQ=")) + dlg.GetPathName() + _T(".mdb");
				break;
			}

		}
		else if( ext == _T("xmp") || ext == _T("xml") )
			conn = CString(_T("XML=")) + dlg.GetPathName();
		else if( ext == _T("mta") )
			conn = CString(_T("MGA=")) + dlg.GetPathName();
		else if( ext == _T("mdb") )
			conn = CString(_T("DBQ=")) + dlg.GetPathName();
		else
		{
			switch( dlg.m_ofn.nFilterIndex )
			{
			case 1:
			case 2:
				conn = CString(_T("XML=")) + dlg.GetPathName();
				break;

			case 3:
				conn = CString(_T("MGA=")) + dlg.GetPathName();
				break;

			case 4:
				conn = CString(_T("DBQ=")) + dlg.GetPathName();
				break;
			}
		}

		// TODO: error message
		if( conn.IsEmpty() )
			return;

		CWaitCursor wait;


		CComBSTR newname;
		COMTHROW(registrar->RegisterParadigmFromData(PutInBstr(conn), &newname, regacc_translate(m_accessmode)));
		
		to_select = newname;
		ResetItems();
	}
	MSGCATCH(_T("Error while registering paradigm"),;)
}

void CMetaDlg::OnRemove() 
{
	UpdateData();
	MSGTRY
	{
		POSITION pos = m_list.GetFirstSelectedItemPosition();
		if( pos != NULL )
		{
			CString name = m_list.GetItemText(m_list.GetNextSelectedItem(pos), 0);

			ASSERT( registrar != NULL );
			COMTHROW( registrar->UnregisterParadigm(PutInBstr(name), regacc_translate(m_accessmode)) );

			CComBSTR dummyc;
			CComVariant dummyg;
			switch(regacc_translate(m_accessmode)) {
			case REGACCESS_USER: 
				if(S_OK == registrar->QueryParadigm(PutInBstr(name), &dummyc, &dummyg, REGACCESS_SYSTEM)) {
					AfxMessageBox(_T("Warning: Paradigm is still present in system registry"));
				}
				break;
			case REGACCESS_SYSTEM: 
				if(S_OK == registrar->QueryParadigm(PutInBstr(name), &dummyc, &dummyg, REGACCESS_USER)) {
					AfxMessageBox(_T("Warning: Paradigm is still present in user registry"));
				}
				break;
			}
			ResetItems();
		}
	}
	MSGCATCH(_T("Error while removing paradigm"),;)
}

void CMetaDlg::OnAddDB() 
{
	UpdateData();
	MSGTRY
	{
		CDatabase db;
		if( db.OpenEx(NULL) )
		{
			CString conn = CMgaLauncher::PruneConnectionString(db.GetConnect());

			CComObjPtr<IMgaMetaProject> paradigm;
			COMTHROW( paradigm.CoCreateInstance(OLESTR("MGA.MgaMetaProject")) );
			ASSERT( paradigm != NULL );

			COMTHROW( paradigm->Open(PutInBstr(conn)) );

			CComBstrObj name;
			COMTHROW( paradigm->get_Name(PutOut(name)) );

			CComBstrObj version;
			COMTHROW( paradigm->get_Version(PutOut(version)) );

			CComVariant guid;
			COMTHROW( paradigm->get_GUID(PutOut(guid)) );

			COMTHROW( paradigm->Close() );

			ASSERT( registrar != NULL );
			COMTHROW( registrar->RegisterParadigm(name, PutInBstr(conn), PutInBstr(version), guid, regacc_translate(m_accessmode)) );

			to_select = PutInBstr(name);
			ResetItems();
		}
		db.Close();
	}
	MSGCATCH(_T("Error while registering paradigm"),;)
	catch(...)
	{
		DisplayError(_T("Error while registering paradigm"), E_EXCEPTION);
	}
}

BOOL CMetaDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	if( wParam == IDC_LIST && ((NMHDR*)lParam)->code == LVN_ITEMCHANGED )
	{
		POSITION pos = m_list.GetFirstSelectedItemPosition();
		m_remove.EnableWindow(pos != NULL);
		GetDlgItem(IDOK)->EnableWindow(pos != NULL);
		m_purge.EnableWindow(pos != NULL);
		to_select = pos ? m_list.GetItemText(m_list.GetNextSelectedItem(pos),0) : _T("");
		if (pos != NULL)
			::SendMessage(GetDlgItem(IDOK)->GetSafeHwnd(), BM_SETSTATE, BST_PUSHED, 0);
		return TRUE;
	}
	else if( wParam == IDC_LIST && ((NMHDR*)lParam)->code == NM_DBLCLK )
	{
		if( !(flags & METADLG_PARREG) && m_list.GetFirstSelectedItemPosition() != NULL )
			OnOK();

		return TRUE;
	}
	
	return CDialog::OnNotify(wParam, lParam, pResult);
}

void CMetaDlg::OnOK() 
{
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	if( pos != NULL )
	{
		int i = m_list.GetNextSelectedItem(pos);
		connstr = m_list.GetItemText(i, 3);
		if(connstr[0] == '?') {
			AfxMessageBox(_T("Error with selected paradigm"));
			return;
		}
		name = m_list.GetItemText(i, 0);
	}
	CDialog::OnOK();
}

void CMetaDlg::OnPurge() 
{
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	if( pos == NULL ) return;
	CMetaPurgeDialog dlg(m_list.GetItemText(m_list.GetNextSelectedItem(pos), 0), registrar);
	dlg.DoModal();
	ResetItems();
}

void CMetaDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CRect list_rect;
	if( m_list.GetSafeHwnd()) {
		m_list.GetWindowRect( &list_rect);
		ScreenToClient( &list_rect);
		int width = cx - 2 * list_rect.left;

		m_list.SetWindowPos( NULL, list_rect.left, list_rect.top, width > 20? width: 20, list_rect.Height(), SWP_NOZORDER);
	}
}
