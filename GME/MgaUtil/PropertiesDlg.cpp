// PropertiesDlg.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertiesDlg dialog


CPropertiesDlg::CPropertiesDlg(IMgaFCO *fcopt, CWnd* pParent /*=NULL*/)
	: CDialog(CPropertiesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPropertiesDlg)
	name = _T("");
	m_relid = _T("");
	//}}AFX_DATA_INIT
	fco = fcopt;
	editflag = false;
//	view = vw;
}

void CPropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertiesDlg)
	DDX_Control(pDX, IDC_DEPENDENCY, dep);
	DDX_Control(pDX, IDC_NAME, nameBox);
	DDX_Control(pDX, IDC_KIND, kind);
	DDX_Control(pDX, IDC_OBJECTID, objectid);
	DDX_Control(pDX, IDC_MODELETC, etc);
	DDX_Control(pDX, IDC_ASPECT, aspect);
	DDX_Control(pDX, IDC_ROLENAME, role);
	DDX_Control(pDX, IDC_TYPE, type);
	DDX_Control(pDX, IDC_METAID, metaid);
	DDX_Text(pDX, IDC_NAME, name);
	DDX_Text(pDX, IDC_RELID, m_relid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropertiesDlg, CDialog)
	//{{AFX_MSG_MAP(CPropertiesDlg)
	ON_BN_CLICKED(IDC_SETRELID, OnSetrelid)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertiesDlg message handlers

BOOL CPropertiesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	try {
//		view->BeginTransaction(true);
		{
			COMTHROW(fco->get_RelID(&relid));
			m_relid.Format(_T("0x%08X"), relid);
		}
		UpdateData(FALSE);
		{
			CComBSTR bstr;
			COMTHROW(fco->get_Name(&bstr));
			CopyTo(bstr,name);
			nameBox.SetWindowText(name);

			this->m_sz_pre_edit_name = name;
		}
		{
			objtype_enum otype;
			COMTHROW(fco->get_ObjType(&otype));
			CString names[] = { _T("Invalid"), _T("Model"), _T("Atom"), _T("Reference"), _T("Connection"), _T("Set"), _T("Folder") };

			CString nm;
			
			nm.Format(_T("%s Properties"), names[otype]);

			this->SetWindowText(nm);

			if(otype == OBJTYPE_MODEL) {
				CComPtr<IMgaFCO> type;
				COMTHROW(fco->get_DerivedFrom(&type));
				if(type != 0) {
					CComBSTR nmb;
					COMTHROW(type->get_Name(&nmb));
					CString tnm;
					CopyTo(nmb,tnm);
	
					VARIANT_BOOL b;
					COMTHROW(fco->get_IsInstance(&b));
					if(b != VARIANT_FALSE) {
						nm.Format(_T("%s (instance of %s)"),names[otype],tnm);
#pragma bookmark (allow name changes for now__ it is allowed in propbar anyways)
//						nameBox.SetReadOnly(true);
					}
					else
						nm.Format(_T("%s (subtype of %s)"),names[otype],tnm);
				}
				else
					nm.Format(_T("%s (archetype)"),names[otype]);
			}
			type.SetWindowText(nm);
		}
		{
			CComPtr<IMgaMetaFCO> metaFco;
			COMTHROW(fco->get_Meta(&metaFco));
			CString txt = _T("N/A");
			if(metaFco != 0) {
				CComBSTR bstr;
				COMTHROW(metaFco->get_DisplayedName(&bstr));
				CopyTo(bstr,txt);
			}
			kind.SetWindowText(txt);
			metaref_type mid = 0;
			COMTHROW(metaFco->get_MetaRef(&mid));
			txt.Format(_T("%ld"),(long)mid);
			metaid.SetWindowText(txt);
		}
		{
			CComPtr<IMgaMetaRole> metaRole;
			COMTHROW(fco->get_MetaRole(&metaRole));
			CString txt = _T("N/A");
			if(metaRole != 0) {
				CComBSTR bstr;
				COMTHROW(metaRole->get_DisplayedName(&bstr));
				CopyTo(bstr,txt);
			}
			role.SetWindowText(txt);
		}
		{
			ID_type id = 0;
 			COMTHROW(fco->get_ID(&id));
  			CString txt = CString(_T(""))+id;
  			objectid.SetWindowText(txt);
		}
		{
			etc.SetWindowText(_T("N/A"));
			CComPtr<IMgaReference> ref;
			if(fco.QueryInterface(&ref) == S_OK) {
				CComPtr<IMgaFCO> refd;
	 			COMTHROW(ref->get_Referred(&refd));
				if(refd != 0) {
					CString name;
					CString kindDisplayedName;
					{
						CComBSTR bstr;
						COMTHROW(refd->get_Name(&bstr));
						CopyTo(bstr,name);
					}
					{
						CComPtr<IMgaMetaFCO> meta;
						COMTHROW(refd->get_Meta(&meta));
						CComBSTR bstr;
						COMTHROW(meta->get_DisplayedName(&bstr));
						CopyTo(bstr,kindDisplayedName);
					}
					CString txt;
					txt.Format(_T("-> %s (%s)"),name,kindDisplayedName);
					etc.SetWindowText(txt);
				}
				else
					etc.SetWindowText(_T("-> null"));
			}
		}
		{
			CString txt = _T("N/A");
			CComPtr<IMgaFCO> asc;
			COMTHROW(fco->get_DerivedFrom(&asc));
			if(asc) {
				CComPtr<IMgaReference> ref;
				short depends;
				if(fco.QueryInterface(&ref) == S_OK) {
		 			COMTHROW(ref->CompareToBase(&depends));
					if(depends > 0)
						txt = _T("Not a dependent");
					else 
						txt = _T("Dependent");
				}
				else {
					CComPtr<IMgaSet> set;
					if(fco.QueryInterface(&set) == S_OK) {
			 			COMTHROW(set->CompareToBase(&depends));
						if(depends > 0)
							txt = _T("Not a Dependent");
						else 
							txt = _T("Dependent");
					}
				}
			}
			dep.SetWindowText(txt);
		}
//		view->CommitTransaction();

		{ // aspects: multiple possible and one may be primary

			bool first = true;

			CString txt = _T("-");

			objtype_enum objtype;

			{ 	CComPtr<IMgaObject> obj_par;
				COMTHROW( fco->GetParent(&obj_par, &objtype) ); }

			CComPtr<IMgaParts> parts;
	
			if (objtype != OBJTYPE_FOLDER) {

				COMTHROW(fco->get_Parts(&parts));
			}

			CComPtr<IMgaPart> impart_ix;

			if((parts != NULL)) {

				txt = _T("");

				MGACOLL_ITERATE(IMgaPart,parts) {

					impart_ix = MGACOLL_ITER;

					ASSERT(impart_ix != NULL);

					CComPtr<IMgaMetaAspect> asp;
					CComBSTR aspname;
					COMTHROW( impart_ix->get_MetaAspect(&asp) );
					COMTHROW( asp->get_Name(&aspname) );

					if (!first) { txt += _T("; "); } 
					else { first = false; }

					txt += CString(aspname);

#pragma bookmark ( simplify here when IMgaPart::get_AccessMask() is available )

					CComPtr<IMgaMetaPart> mpart;
					COMTHROW( impart_ix->get_Meta(&mpart) );
					ASSERT( mpart != NULL );

					VARIANT_BOOL vb_pri_asp = VARIANT_FALSE;
					COMTHROW( mpart->get_IsPrimary(&vb_pri_asp) );

					if (vb_pri_asp != VARIANT_FALSE) {

						txt += _T(" (primary)");
					}
				}
				MGACOLL_ITERATE_END;
				
			}
			aspect.SetWindowText(txt);
		}

	}
	catch(hresult_exception e) {
//		view->AbortTransaction(e.hr);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CPropertiesDlg::OnSetrelid() 
{
	GetDlgItem(IDC_RELID)->EnableWindow(editflag = !editflag);
}
