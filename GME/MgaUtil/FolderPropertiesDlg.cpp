// FolderPropertiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mgautil.h"
#include "FolderPropertiesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFolderPropertiesDlg dialog


CFolderPropertiesDlg::CFolderPropertiesDlg(IMgaFolder *f, CWnd* pParent /*=NULL*/)
	: CDialog(CFolderPropertiesDlg::IDD, pParent), folder(f) {
	//{{AFX_DATA_INIT(CFolderPropertiesDlg)
	name = _T("");
	m_relid = _T("");
	//}}AFX_DATA_INIT
	editflag = false;
}


void CFolderPropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFolderPropertiesDlg)
	DDX_Control(pDX, IDC_NAME, nameBox);
	DDX_Control(pDX, IDC_KIND, kind);
	DDX_Control(pDX, IDC_OBJECTID, objectid);
	DDX_Control(pDX, IDC_LIBRARY, library);
	DDX_Control(pDX, IDC_TYPE, type);
	DDX_Control(pDX, IDC_METAID, metaid);
	DDX_Text(pDX, IDC_NAME, name);
	DDX_Text(pDX, IDC_RELID, m_relid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFolderPropertiesDlg, CDialog)
	//{{AFX_MSG_MAP(CFolderPropertiesDlg)
	ON_BN_CLICKED(IDC_SETRELID, OnSetrelid)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFolderPropertiesDlg message handlers

BOOL CFolderPropertiesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	try {
//		view->BeginTransaction(true);
		{
			COMTHROW(folder->get_RelID(&relid));
			m_relid.Format(_T("0x%08X"), relid);
		}
		UpdateData(FALSE);
		{
			CComBSTR bstr;
			COMTHROW(folder->get_Name(&bstr));
			CopyTo(bstr,name);
			nameBox.SetWindowText(name);

			this->m_sz_pre_edit_name = name;
		}
		{
			CString txt;
			CComPtr<IMgaMetaFolder> metaFolder;
			COMTHROW(folder->get_MetaFolder(&metaFolder));
			ASSERT(metaFolder);
			CComBSTR bstr;
			COMTHROW(metaFolder->get_DisplayedName(&bstr));
			CopyTo(bstr,txt);
			kind.SetWindowText(txt);
			metaref_type mid = 0;
			COMTHROW(metaFolder->get_MetaRef(&mid));
			txt.Format(_T("%ld"),(long)mid);
			metaid.SetWindowText(txt);
		}
		{
			CString txt;
			CComBSTR libid;
 			COMTHROW(folder->get_LibraryName(&libid));
  			CopyTo(libid, txt);
  			objectid.SetWindowText(txt);
		}
		{
			ID_type id = 0;
 			COMTHROW(folder->get_ID(&id));
  			CString txt = CString(_T(""))+id;
  			objectid.SetWindowText(txt);
		}

	}
	catch(hresult_exception e) {
//		view->AbortTransaction(e.hr);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFolderPropertiesDlg::OnSetrelid() {
	GetDlgItem(IDC_RELID)->EnableWindow(editflag = !editflag);
}
