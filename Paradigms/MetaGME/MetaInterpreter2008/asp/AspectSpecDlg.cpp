// AspectSpecDlg.cpp : implementation file
//

#include "stdafx.h"
#include "aspectspectbl.h"
#include "AspectSpecDlg.h"
#include "logger.h"
#include "ModelRep.h"
#include "ReferenceRep.h"

#include "globals.h"
extern Globals global_vars;

// keep in sync with Dumper.cpp's DUMPER_NOT_SPECIFIED_STR
#define DUMPER_NOT_SPECIFIED_STR      "Not specified"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAspectSpecDlg

//IMPLEMENT_DYNAMIC(CAspectSpecDlg, CPropertySheet)

CAspectSpecDlg::CAspectSpecDlg(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	: CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
	, lastID( 0)
	, countPages( 0)
{
	m_psh.dwFlags |= PSH_NOAPPLYNOW;
}

CAspectSpecDlg::CAspectSpecDlg(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	: CPropertySheet(pszCaption, pParentWnd, iSelectPage)
	, lastID( 0)
	, countPages( 0)
{
	m_psh.dwFlags |= PSH_NOAPPLYNOW;
}

CAspectSpecDlg::~CAspectSpecDlg()
{
	POSITION pos = aspectPages.GetHeadPosition();
	while (pos) 
		delete aspectPages.GetNext(pos);


	aspectPages.RemoveAll();

}


BEGIN_MESSAGE_MAP(CAspectSpecDlg, CPropertySheet)
	ON_WM_CREATE()
	//{{AFX_MSG_MAP(CAspectSpecDlg)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAspectSpecDlg message handlers



int CAspectSpecDlg::AddEntry(CString aspectName, CString roleName, CString kindAspect, CString primaryAsp, const void * ptr)
{
	CAspectPage *aspectPage = NULL;

	POSITION pos = aspectPages.GetHeadPosition();
	while (pos) {
		CAspectPage *page = aspectPages.GetNext(pos);
		CString title = page->GetAspectName();;

		if (title == aspectName)
			aspectPage = page;
	}
	
	if (!aspectPage) {
		aspectPage = new CAspectPage();
		aspectPage->SetAspectName(aspectName);
		aspectNames.AddTail(aspectName);
		AddPage(aspectPage);
		aspectPages.AddTail(aspectPage);
		++countPages;
	}

	aspectPage->AddEntry(lastID, roleName, kindAspect, primaryAsp, ptr);
	return lastID++;
}

void CAspectSpecDlg::GetEntry(int rowID, CString &roleName, CString &kindAspect, CString &isPrimary, const void * &ptr)
{
	POSITION pos = aspectPages.GetHeadPosition();
	while (pos) {
		if (aspectPages.GetNext(pos)->GetEntry(rowID, roleName, kindAspect, isPrimary, ptr))
			break;
	}

}

void CAspectSpecDlg::GetAspects(CStringList &aspects)
{
	aspects.RemoveAll();
	aspects.AddTail(&aspectNames);
}

void CAspectSpecDlg::GetAspects( int rowID, CStringList &aspects)
{
	aspects.RemoveAll();
	CString role_name = "N/A", kind_asp = "N/A", is_prim;
	void * ptr;
	GetEntry( rowID, role_name, kind_asp, is_prim, ptr);
	if ( role_name == "N/A") 
		global_vars.err << MSG_ERROR << "Internal error: GetEntry failed. Empty rolename\n";
	const FCO * fco_ptr = static_cast<const FCO*>( ptr);
	if ( fco_ptr)
	{
		if ( fco_ptr->getMyKind() == Any::MODEL)
		{
			const ModelRep * m_ptr = static_cast<const ModelRep *>(ptr);
			m_ptr->getAspectNames( aspects);
		}
		else if (fco_ptr->getMyKind() == Any::REF)
		{
			aspects.AddTail( DUMPER_NOT_SPECIFIED_STR);
			const ReferenceRep * r_ptr = static_cast< const ReferenceRep *>(ptr);
			std::vector< AspectRep *> asps = r_ptr->getAspectsIntersection();
			std::vector< AspectRep *>::iterator asp_it = asps.begin();
			for( ; asp_it != asps.end(); ++asp_it)
			{
				aspects.AddTail( (*asp_it)->getName().c_str());
			}
		}
		else global_vars.err << MSG_ERROR << "Internal error: why other type than Model and Ref has Kindaspect?\n";
	}
	else global_vars.err << MSG_ERROR << "Internal error: zero pointer\n";
}

BOOL CAspectSpecDlg::OnInitDialog() 
{
	// this will call the OnInitDialog of the first PropertyPage
	BOOL bResult = CPropertySheet::OnInitDialog();

	// this portion may modify the layout of tabs (the number of rows they occupy)
	// since the tabnames may be longer then expected
	// so the first page needs to be resized after this 
	CTabCtrl* tab = GetTabControl();
	int count = tab->GetItemCount();
	POSITION pos = aspectNames.GetHeadPosition();
	for (int i = 0; i < count; i++) {
		TC_ITEM tcItem; 
		tcItem.mask = TCIF_TEXT; 
		tcItem.pszText = aspectNames.GetNext(pos).GetBuffer(255);
		tab->SetItem(i, &tcItem ); 
	}

	SetActivePage(0); // activates the first page, and calls AspectPage::OnSize with the updated size (lower than the previous)

	// resizing of controls on the first page
	CAspectPage *firstpage;
	POSITION pos1 = aspectPages.GetHeadPosition();
	if( pos1){
		firstpage = aspectPages.GetNext(pos1);
		firstpage->resizeTableToFitIn();
	}


	return bResult;
}

int CAspectSpecDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// Set for Scrolling Tabs style if the #of pages exceeds 19
	// otherwise the tabs with long aspect names could occupy the whole window area
	// if 19 aspects with really long names existed still fitted into the window
	// and space left for 3 items
	// that is why we enable the ScrollingTabs in case the number of pages > 19
	// unfortunately the length of the names is not calculated
	EnableStackedTabs( countPages <= 19);

	// Call the base class
	return CPropertySheet::OnCreate(lpCreateStruct);
}
