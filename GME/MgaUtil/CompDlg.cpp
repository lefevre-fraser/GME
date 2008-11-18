// CompDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MgaUtil.h"
#include "CompDlg.h"
#include "CompInfoDlg.h"
#include "UACUtils.h"

#include <atlbase.h>
#include <objbase.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCompDlg dialog


CCompDlg::CCompDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCompDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCompDlg)
	m_accessmode = 1;
	m_dispmode = 1;
	//}}AFX_DATA_INIT

	type = COMPONENTTYPE_ALL;
	onOKoper = "Close";
}


void CCompDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCompDlg)
	DDX_Control(pDX, Toggle, m_toggle);
	DDX_Control(pDX, IDC_REMOVE, m_remove);
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Radio(pDX, IDC_RADIOSYS, m_accessmode);
	DDX_Radio(pDX, IDC_ACTIVEDISP, m_dispmode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCompDlg, CDialog)
	//{{AFX_MSG_MAP(CCompDlg)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_INSTALL, OnInstall)
	ON_BN_CLICKED(IDC_ACTIVEDISP, OnActivedisp)
	ON_BN_CLICKED(IDC_ACTIVE_INACTIVE, OnActiveInactive)
	ON_BN_CLICKED(IDC_ALLCOMPS, OnAllcomps)
	ON_BN_CLICKED(Toggle, OnToggle)
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCompDlg message handlers

BOOL CCompDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	MSGTRY
	{
		if( !CUACUtils::isVistaOrLater() ) {
			CComPtr<IMgaRegistrar> registrar;
			COMTHROW( registrar.CoCreateInstance(OLESTR("MGA.MgaRegistrar")) );
			ASSERT( registrar != NULL );

			if(registrar->RegisterComponent(CComBSTR("AAA"), 
				componenttype_enum(COMPONENTTYPE_INTERPRETER+COMPONENTTYPE_PARADIGM_INDEPENDENT), CComBSTR("Dummy"), REGACCESS_TEST) != S_OK) {
				GetDlgItem(IDC_RADIOSYS)->EnableWindow(false);
				GetDlgItem(IDC_RADIOBOTH)->EnableWindow(false);
			}
		}

		SetDlgItemText(IDOK, onOKoper);
		

		LV_COLUMN lvc;
		lvc.mask = LVCF_WIDTH | LVCF_TEXT;

		lvc.pszText = "Name";
		lvc.cx = 150;
		VERIFYTHROW( m_list.InsertColumn(0, &lvc) != -1 );

		lvc.pszText = "Type";
		lvc.cx = 80;
		VERIFYTHROW( m_list.InsertColumn(1, &lvc) != -1 );

		lvc.pszText = "ProgID";
		lvc.cx = 200;
		VERIFYTHROW( m_list.InsertColumn(2, &lvc) != -1 );

		iconlist.Create(IDB_BITMAP1,16,0,15);
		m_list.SetImageList(&iconlist,LVSIL_SMALL);
		if(parameter.vt == VT_BSTR) {
			sticonlist.Create(IDB_BITMAP2,10,0,15);
			m_list.SetImageList(&sticonlist,LVSIL_STATE);
		}
		UpdateData(false);
		ResetItems();
	}
	MSGCATCH("Error while initializing CompDlg",;)
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCompDlg::ResetItems()
{
	CComPtr<IMgaRegistrar> registrar;
	registrar.CoCreateInstance(OLESTR("Mga.MgaRegistrar"));
	ASSERT( registrar != NULL );

	m_remove.EnableWindow(false);
	m_toggle.EnableWindow(false);

	UpdateData();
	VERIFYTHROW( m_list.DeleteAllItems() != 0 );

	CComVariant v;
	if(m_dispmode == 0) {
		COMTHROW( registrar->get_AssociatedComponents(PutInBstr(paradigm), type, REGACCESS_BOTH, PutOut(v)) );
	}
	else {
		COMTHROW( registrar->get_Components(REGACCESS_BOTH, PutOut(v)) );
	}

	CComBstrObjArray progids;
	MoveTo(v, progids);



	for(int i = 0; i < progids.GetSize(); ++i)
	{
		componenttype_enum qtype;
		CComBstrObj desc;

		bool err_ass = false;
		VARIANT_BOOL is_ass, can_ass;
		HRESULT hr = registrar->QueryComponent(progids[i], &qtype, PutOut(desc), REGACCESS_PRIORITY );
		if(hr != S_OK) {
			err_ass = true;
			desc = L"???";
			qtype = COMPONENTTYPE_NONE;
		}
		else {
			if(! (qtype & type) ) continue;
			if(m_dispmode) {
				HRESULT hr = registrar->IsAssociated(progids[i], PutInBstr(paradigm), &is_ass, &can_ass, REGACCESS_PRIORITY );
				if(hr == E_NOTFOUND) {
					err_ass = true;
				}
				else COMTHROW(hr);
				if(m_dispmode == 1 && (is_ass == VARIANT_FALSE && can_ass == VARIANT_FALSE)) continue;
			}
			else is_ass = can_ass = VARIANT_TRUE;
		}

		int index;
		VERIFYTHROW( (index = m_list.InsertItem(i, PutInCString(desc), err_ass ? 3 : is_ass ? 0 : can_ass ? 1 : 2)) != -1 );

		
		CString ctype;
		switch(qtype & COMPONENTTYPE_ALL)
		{
		case COMPONENTTYPE_INTERPRETER:
			ctype = "Interpreter";
			break;

		case COMPONENTTYPE_ADDON:
			ctype = "Add-on";

			if(parameter.vt == VT_BSTR) {
				CComBSTR l = parameter.bstrVal;
				WCHAR * f = wcstok(l,L" ");
				while(f) {
					if(!desc.Compare(CComBSTR(f)) || !progids[i].Compare(CComBSTR(f))) {
						m_list.SetItemState(index, INDEXTOSTATEIMAGEMASK(2), LVIS_STATEIMAGEMASK);
						break;
					}
					f = wcstok(NULL, L" ");
				}
			}
			break;

		case COMPONENTTYPE_PLUGIN:
			ctype = "Plug-in";
			break;

		default:
			ctype = "???";
		}

		VERIFYTHROW( m_list.SetItemText(index, 1, ctype) != 0 );
		VERIFYTHROW( m_list.SetItemText(index, 2, PutInCString(progids[i])) != 0 );
		if(!desc.Compare( PutInBstr(to_select))) {
			m_list.SetItemState(index, LVIS_SELECTED, LVIS_SELECTED);
		}
/*
		LVITEM stat;
		stat.iItem = index;
		stat.iSubItem = 0;
		stat.mask = LVIF_STATE;
		stat.state = INDEXTOSTATEIMAGEMASK(2);
		stat.stateMask = LVIS_STATEIMAGEMASK;
//		stat.iImage = 1;
//		stat.pszText = "Haha";
		VERIFYTHROW( m_list.SetItemState(index, &stat));
*/
	}
}

void CCompDlg::OnOK() 
{
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	if( pos != NULL )
	{
		int i = m_list.GetNextSelectedItem(pos);
		progid = m_list.GetItemText(i, 2);
	}
	else
	{
		progid.Empty();
	}

	CDialog::OnOK();
}

BOOL CCompDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	if( wParam == IDC_LIST && ((NMHDR*)lParam)->code == LVN_ITEMCHANGED )
	{
		POSITION pos = m_list.GetFirstSelectedItemPosition();
		m_remove.EnableWindow(pos != NULL);
		m_toggle.EnableWindow(pos != NULL);
		to_select = m_list.GetItemText(m_list.GetNextSelectedItem(pos),0);
		return TRUE;
	}
	
	return CDialog::OnNotify(wParam, lParam, pResult);
}

void CCompDlg::OnRemove() 
{
	UpdateData();
	MSGTRY
	{
		POSITION pos = m_list.GetFirstSelectedItemPosition();
		if( pos != NULL )
		{
			CString progid = m_list.GetItemText(m_list.GetNextSelectedItem(pos), 2);

			CComPtr<IMgaRegistrar> registrar;
			if (CUACUtils::isVistaOrLater()) {
				CUACUtils::CreateElevatedInstance(CLSID_MgaRegistrar, &registrar);
			}
			else {
				registrar.CoCreateInstance(OLESTR("Mga.MgaRegistrar"));
			}

			if( !registrar ) {
				::AfxMessageBox(_T("Unable to unregister component. Maybe due to insufficient rights."), MB_ICONSTOP | MB_OK);
				return;
			}

			COMTHROW( registrar->UnregisterComponent(PutInBstr(progid), regacc_translate(m_accessmode)) );

			componenttype_enum type;
			ASSERT(E_NOTFOUND == registrar->QueryComponent(PutInBstr(progid), &type, NULL, regacc_translate(m_accessmode)));
			switch(regacc_translate(m_accessmode)) {
				case REGACCESS_USER:
					if(S_OK == registrar->QueryComponent(PutInBstr(progid), &type, NULL, REGACCESS_SYSTEM)) {
						AfxMessageBox("Warning: Component is still present in system registry");
					}
					break;
				case REGACCESS_SYSTEM:
					if(S_OK == registrar->QueryComponent(PutInBstr(progid), &type, NULL, REGACCESS_USER)) {
						AfxMessageBox("Warning: Component is still present in user registry");
					}
					break;
			}
			ResetItems();
		}
	}
	MSGCATCH("Error while removing component",;)
}


void CCompDlg::OnToggle() 
{
	UpdateData();
	MSGTRY
	{
		POSITION pos = m_list.GetFirstSelectedItemPosition();
		if( pos != NULL ) {
			CComBSTR progid = m_list.GetItemText(m_list.GetNextSelectedItem(pos), 2);

			VARIANT_BOOL is_ass, can_ass;
			
			CComPtr<IMgaRegistrar> registrar;
			if (CUACUtils::isVistaOrLater() && (regacc_translate(m_accessmode) != REGACCESS_USER) ) {
				CUACUtils::CreateElevatedInstance(CLSID_MgaRegistrar, &registrar);
			}
			else {
				registrar.CoCreateInstance(OLESTR("Mga.MgaRegistrar"));
			}

			if( !registrar ) {
				::AfxMessageBox(_T("Unable to disable/enable component. Maybe due to insufficient rights."), MB_ICONSTOP | MB_OK);
				return;
			}

			HRESULT hr = registrar->IsAssociated(progid, PutInBstr(paradigm), &is_ass, &can_ass, REGACCESS_PRIORITY);
			if(hr != S_OK) AfxMessageBox("Cannot Activate this component");
			if(is_ass) hr = (registrar->Disassociate(progid, PutInBstr(paradigm), regacc_translate(m_accessmode)) );
			else {
				if(!can_ass) {
					if(AfxMessageBox("This component reports to be incompatible with the paradigm\nAre you sure you want to proceed?", MB_YESNO) != IDYES) return;
				}
				hr = (registrar->Associate(progid, PutInBstr(paradigm), regacc_translate(m_accessmode)) );
			}
			if(hr != S_OK) {
				if(regacc_translate(m_accessmode) == REGACCESS_USER) {
					AfxMessageBox("The toggle operation failed\nCheck if access mode is appropriate");
				}
				else AfxMessageBox("The toggle operation failed");;
			}

			ResetItems();
		}
	}
	MSGCATCH("Error while (dis)associating component",;)
}

static char filter[] = 
	"Component Files (*.dll; *.ocx)|*.dll; *.ocx|"
	"Pattern Files (*.pat)|*.pat|"
	"All Files (*.*)|*.*||";

void CCompDlg::OnInstall() 
{
	UpdateData();
	MSGTRY
	{
		CFileDialog dlg(true, NULL, NULL, 
			OFN_EXPLORER | OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
			filter);

		if( dlg.DoModal() != IDOK )
			return;

		CString ext = dlg.GetFileExt();

		if(ext.CompareNoCase("DLL") == 0) {
				RegisterDll(dlg.GetPathName());
		}
		else if(ext.CompareNoCase("PAT") == 0){
				RegisterPattern(dlg.GetPathName());
		}
		else {
				RegisterUnknownFile(dlg.GetPathName());
		}
		ResetItems();
	}
	MSGCATCH("Error while installing component",;)
}

void CCompDlg::RegisterDll(const CString &path)
{
	CComPtr<IMgaRegistrar> registrar;
	if (CUACUtils::isVistaOrLater()) {
		CUACUtils::CreateElevatedInstance(CLSID_MgaRegistrar, &registrar);
	}
	else {
		registrar.CoCreateInstance(OLESTR("Mga.MgaRegistrar"));
	}

	if( (!registrar) || 
		 FAILED(registrar->RegisterComponentLibrary(PutInBstr(path), regacc_translate(m_accessmode))) ) {
		::AfxMessageBox(_T("Unable to register component. Maybe due to insufficient rights."), MB_ICONSTOP | MB_OK);
	}
}


void CCompDlg::RegisterPattern(const CString &path)
{

	char buf[300];
	{
		std::ifstream fin(path, std::ios::in);//z! ios::nocreate used previously, but if opened for read it won't create in this way
		if(fin.good()) fin.getline(buf, 300);
		if(!fin.good()) {
			AfxMessageBox("Could not open or read the specified file: " + path);
			return;
		}
	}

	regaccessmode_enum acmode = regacc_translate(m_accessmode);
	CComPtr<IMgaRegistrar> registrar;
	if (CUACUtils::isVistaOrLater() && (acmode != REGACCESS_USER) ) {
		CUACUtils::CreateElevatedInstance(CLSID_MgaRegistrar, &registrar);
	}
	else {
		registrar.CoCreateInstance(OLESTR("Mga.MgaRegistrar"));
	}

	if( !registrar ) {
		::AfxMessageBox(_T("Unable to register pattern component. Maybe due to insufficient rights."), MB_ICONSTOP | MB_OK);
		return;
	}

	CCompInfoDlg dlg(registrar);
	dlg.m_filename = path;

	char paren, info[200];
	if(sscanf(buf, " $!COMMENT( %[^)]%c", info, &paren) != 2 || paren != ')') {
nothing_understood:
		AfxMessageBox("Cannot read component info in file " + path);
	}
	else {
	
	
// NAME=nnn, DESCRIPTION=ddd, PROGID=ii, PARADIGM=xx,yy, VERSION=vvv,
		char *p = strtok(info,",");
		bool ready = false;
		bool parsing_paradigm = false;
		bool good = false;
		while(p) {
			CString item(p);
			item.TrimLeft();
			item.TrimRight();
			int k1 = item.Find(';');
			if(ready && !item.IsEmpty()) goto item_err;
			if(k1 > 0) {
				ready = true;
				item = item.Left(k1);
				item.TrimRight();
			}
			k1 = item.Find('=');
			if(k1 > 0) {
				parsing_paradigm = false;
				CString i_name = item.Left(k1);
				i_name.TrimRight();
				CString i_value = item.Mid(k1+1);
				i_value.TrimLeft();
				if(i_name.Compare("NAME") == 0) {
					dlg.m_name = i_value;
				}
				else if(i_name.Compare("DESCRIPTION") == 0 ||
					i_name.Compare("DESC") == 0) {
					dlg.m_description = i_value;
				}
				else if(i_name.Compare("PROGID") == 0) {
					dlg.m_progid = i_value;
				}
				else if(i_name.Compare("PARADIGM") == 0) {
					dlg.m_paradigm = i_value;
					parsing_paradigm  = true;
				}
				else if(i_name.Compare("VERSION") == 0) {
					dlg.m_version = i_value;
				}
				else goto item_err;
				good = true;
			}
			else {
				if(parsing_paradigm) {
					dlg.m_paradigm += "," + item;
				}
				else {
	item_err:
					AfxMessageBox("Syntax error parsing component info: " + item); 
				}
			}
			p = strtok(NULL, ",");
		}
		if(!good) goto nothing_understood;
	}

	if(dlg.m_progid.IsEmpty() && !dlg.m_name.IsEmpty()) {
		dlg.m_progid = "MGA.Pattern." + dlg.m_name;
	}
	if(dlg.m_description.IsEmpty() && !dlg.m_name.IsEmpty()) {
		dlg.m_description = dlg.m_name;
	}
	if(dlg.m_version.IsEmpty()) {
		dlg.m_version = "1.0";
	}

	if(dlg.DoModal() != IDOK) return;


	CComBSTR progid(dlg.m_progid);

	
	COMTHROW(registrar->RegisterComponent(progid, 
				(componenttype_enum)(COMPONENTTYPE_INTERPRETER|COMPONENTTYPE_SCRIPT),
				PutInBstr(dlg.m_description), acmode));
	COMTHROW(registrar->put_ComponentExtraInfo(acmode, progid, CComBSTR("Name"), CComBSTR(dlg.m_name)));
	COMTHROW(registrar->put_ComponentExtraInfo(acmode, progid, CComBSTR("ExecEngine"), CComBSTR(dlg.engine)));
	COMTHROW(registrar->put_ComponentExtraInfo(acmode, progid, CComBSTR("ScriptFile"), CComBSTR(path)));
	COMTHROW(registrar->put_ComponentExtraInfo(acmode, progid, CComBSTR("ScriptVersion"), CComBSTR(dlg.m_version)));

	char *mpardup = (char *)alloca(dlg.m_paradigm.GetLength()+1);
	strcpy(mpardup, dlg.m_paradigm);
	const char *par = strtok(mpardup,"\t ,");
	while(par) {
		COMTHROW(registrar->Associate(progid, CComBSTR(par), acmode));
		par = strtok(NULL, "\t ,");
	}
}

void CCompDlg::RegisterUnknownFile(const CString &path)
{

}

void CCompDlg::OnActivedisp() 
{
	ResetItems();
}

void CCompDlg::OnActiveInactive() 
{
	ResetItems();
}

void CCompDlg::OnAllcomps() 
{
	ResetItems();
}


void CCompDlg::OnSize(UINT nType, int cx, int cy)
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
