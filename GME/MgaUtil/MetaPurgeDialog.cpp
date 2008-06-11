// MetaPurgeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "mgautil.h"
#include "MetaPurgeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMetaPurgeDialog dialog


CMetaPurgeDialog::CMetaPurgeDialog(CString &paradigmname,  IMgaRegistrar *reg, CWnd* pParent /*=NULL*/)
	: CDialog(CMetaPurgeDialog::IDD, pParent), paradigm(paradigmname), registrar(reg)
{
	//{{AFX_DATA_INIT(CMetaPurgeDialog)
	m_delfiles = -1;
	//}}AFX_DATA_INIT
}


void CMetaPurgeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMetaPurgeDialog)
	DDX_Control(pDX, IDC_PURGELIST, m_list);
	DDX_Radio(pDX, IDC_DELFILES, m_delfiles);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMetaPurgeDialog, CDialog)
	//{{AFX_MSG_MAP(CMetaPurgeDialog)
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_PURGE2, OnPurge)
	ON_BN_CLICKED(IDC_SETCURRENT, OnSetcurrent)
	ON_BN_CLICKED(IDCLOSE, OnClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMetaPurgeDialog message handlers


BOOL CMetaPurgeDialog::OnInitDialog() 
{
	m_delfiles = 0;
	CDialog::OnInitDialog();

	CListCtrl* listctrl = (CListCtrl*)GetDlgItem(IDC_PURGELIST);
    DWORD dwStyle = listctrl->SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE,0,0);
    dwStyle |= LVS_EX_FULLROWSELECT;
    listctrl->SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dwStyle);


	MSGTRY
	{
		ASSERT( registrar != NULL );

		LV_COLUMN lvc;
		lvc.mask = LVCF_WIDTH | LVCF_TEXT;

		lvc.pszText = "S";
		lvc.cx = 20;
		VERIFYTHROW( m_list.InsertColumn(0, &lvc) != -1 );

		lvc.pszText = "Version";
		lvc.cx = 50;
		VERIFYTHROW( m_list.InsertColumn(1, &lvc) != -1 );

		lvc.pszText = "GUID";
		lvc.cx = 250;
		VERIFYTHROW( m_list.InsertColumn(2, &lvc) != -1 );


		lvc.pszText = "Connection String";
		lvc.cx = 300;
		VERIFYTHROW( m_list.InsertColumn(3, &lvc) != -1 );

		ResetItems();
	}
	MSGCATCH("Error while initializing MetaPurgeDlg",;)
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMetaPurgeDialog::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
}

void CMetaPurgeDialog::ResetItems()
{
	ASSERT( registrar != NULL );

	VERIFYTHROW( m_list.DeleteAllItems() != 0 );

	CComVariant v;
	COMTHROW( registrar->QueryParadigmAllGUIDs(CComBSTR(paradigm), PutOut(v), REGACCESS_BOTH) );

	CComBstrObjArray guidnames;
	MoveTo(v, guidnames);


	CComBstrObj currentguid;
	{
		CComBSTR dummy;
		CComVariant vv;
		COMTHROW( registrar->QueryParadigm(CComBSTR(paradigm), &dummy, &vv, REGACCESS_PRIORITY ));
		GUID guid;
		CopyTo(vv, guid);
		CopyTo(guid, currentguid);
	}

	for(int i = 0; i < guidnames.GetSize(); ++i)	{
		CString name;
		CopyTo(guidnames[i], name);

		GUID gg;
		CopyTo(guidnames[i],gg);
		CComVariant vv;
		CopyTo(gg, vv);

		CString connstr;
		CString version;
		char statc = 'u';
		HRESULT hr = registrar->QueryParadigm(CComBSTR(paradigm), PutOut(connstr), &vv, REGACCESS_USER);
		if(hr == E_NOTFOUND) {
			statc = 's';
			hr = registrar->QueryParadigm(CComBSTR(paradigm), PutOut(connstr), &vv, REGACCESS_SYSTEM);
		} 
		if(hr != S_OK) {
			statc = ' ';
			connstr = "<<error reading this reg.entry>>";
		}

		hr = registrar->VersionFromGUID(CComBSTR(paradigm), vv, PutOut(version), statc ==  'u' ? REGACCESS_USER : REGACCESS_SYSTEM);
		if (FAILED(hr)) {
			version = "N/A";
		}

		int j;
		VERIFYTHROW( (j = m_list.InsertItem(i, CString(currentguid == guidnames[i] ? "*" : " ") + statc)) != -1 );
		VERIFYTHROW( m_list.SetItemText(j, 1, version) != 0 );
		VERIFYTHROW( m_list.SetItemText(j, 2, PutInCString(guidnames[i])) != 0 );
		VERIFYTHROW( m_list.SetItemText(j, 3, connstr) != 0 );

	}

}

void CMetaPurgeDialog::OnPurge() 
{
	UpdateData();
	MSGTRY
	{
		POSITION pos = m_list.GetFirstSelectedItemPosition();

		while(pos) {
			int i = m_list.GetNextSelectedItem(pos);
			CString cur = m_list.GetItemText(i,0);
			if(cur[0] == '*') continue;
			CString delguid = m_list.GetItemText(i,2);
			GUID gg;
			CopyTo(CComBSTR(delguid),gg);
			CComVariant vv;
			CopyTo(gg, vv);
			COMTHROW( registrar->UnregisterParadigmGUID(CComBSTR(paradigm), vv, cur[1] == 's' ? REGACCESS_SYSTEM : REGACCESS_USER) );
			CString delcstr = m_list.GetItemText(i,3);
			if(m_delfiles != 0 || delcstr.Find("MGA=") != 0) continue;
			DeleteFile(LPCTSTR(delcstr)+4);
		}

		ResetItems();
	}
	MSGCATCH("Error while removing items",;)
}

void CMetaPurgeDialog::OnSetcurrent() 
{
	MSGTRY
	{
		POSITION pos = m_list.GetFirstSelectedItemPosition();

		if(pos) {
			int i = m_list.GetNextSelectedItem(pos);
			CString cur = m_list.GetItemText(i,0);
			if(cur[0] == '*') return;
			CString setver = m_list.GetItemText(i,1);
			CString setguid = m_list.GetItemText(i,2);
			GUID gg;
			CopyTo(CComBSTR(setguid),gg);
			CComVariant vv;
			CopyTo(gg, vv);
			CString setcstr = m_list.GetItemText(i,3);
			COMTHROW( registrar->RegisterParadigm(CComBSTR(paradigm), CComBSTR(setcstr), CComBSTR(setver), vv, 
				cur[1] == 's' ? REGACCESS_SYSTEM : REGACCESS_USER) );
		}

		ResetItems();
	}
	MSGCATCH("Error while setting current version",;)
}

void CMetaPurgeDialog::OnClose() 
{
	CDialog::OnOK();
}
