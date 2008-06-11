// EventMaskDialog.cpp : implementation file
//

#include "stdafx.h"
#include "interpreterconfig.h"
#include "EventMaskDialog.h"
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEventMaskDialog dialog


CEventMaskDialog::CEventMaskDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEventMaskDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEventMaskDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CEventMaskDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEventMaskDialog)
	DDX_Control(pDX, IDC_EVLIST, m_evlist);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEventMaskDialog, CDialog)
	//{{AFX_MSG_MAP(CEventMaskDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventMaskDialog message handlers

void CEventMaskDialog::OnOK() 
{

	POSITION pos = m_evlist.GetFirstSelectedItemPosition();
	mask = 0;
	while(pos) {
		int k = m_evlist.GetNextSelectedItem(pos);

		CString maskstr = m_evlist.GetItemText(k,1);
		ULONG mm;
		sscanf(maskstr,"%lx", &mm);
		mask |= mm;
	}		
	
	for(int i = 0; i < m_evlist.GetItemCount(); i++) {
	}
	CDialog::OnOK();
}

BOOL CEventMaskDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	LV_COLUMN lvc;
	lvc.mask = LVCF_WIDTH | LVCF_TEXT;

	lvc.pszText = "Event";
	lvc.cx = 150;
	if( m_evlist.InsertColumn(0, &lvc) == -1) return false;

	lvc.pszText = "Mask";
	lvc.cx = 80;
	if( m_evlist.InsertColumn(1, &lvc) == -1 ) return false;

	int pos = 0;
	if(fin.rdstate() == ios::goodbit) {
	  while(!fin.eof()) {
		char buf[250]; //buffer enlarged from 100
		fin.getline(buf, 250);
		if(!fin.eof()) {
			unsigned long mmask;
			char evname[31];
			if(sscanf(buf, "%*[^A-Za-z]OBJEVENT_%30s = %Lx",evname, &mmask) == 2) {
				int index;
				int p = (mmask & mask) == mmask ? LVIS_SELECTED : 0;
				index = m_evlist.InsertItem(LVIF_STATE|LVIF_TEXT,
					pos++, evname, p,LVIS_SELECTED,0,0);
				char ct[15]; sprintf(ct,"0x%08LX", mmask);
				m_evlist.SetItemText(index, 1, ct);
			}
		}
	  }
	}
	if(pos == 0) {
		AfxMessageBox("Error reading/parsing event definitions. Mnemonics will not be available");
		for(unsigned long i = 1; i; i <<= 1) {
				char ct[15]; sprintf(ct,"0x%08LX", i);
				int p = i & mask ? LVIS_SELECTED : 0;
				int index = m_evlist.InsertItem(LVIF_STATE|LVIF_TEXT, 
					pos++, ct, p,LVIS_SELECTED,0,0);
				m_evlist.SetItemText(index, 1, ct);
		}	
	}

	m_evlist.SetFocus();
	return TRUE;
}
