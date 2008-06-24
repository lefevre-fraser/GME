//###############################################################################################################################################
//
//	Object Constraint Language Generic Manager
//	GMEViolationDialog.cp
//
//###############################################################################################################################################

#include "stdafx.h"
#include "GMEViolationDialog.h"
#include "OCLCommonEx.h"
#include "OCLGMECMFacade.h"
#include "afximpl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace OclGmeCM {

	struct SortStruct
	{
		CViolationDialog* 	pDialog;
		int					iColumn;
	};



//##############################################################################################################################################
//
//	C L A S S : CViolationDialog <<< + CDialog
//
//##############################################################################################################################################

CViolationDialog::CViolationDialog( bool bExpanded, CWnd* pParent /*=NULL*/, IMgaProject *project)
	: CDialog(CViolationDialog::IDD, pParent), m_bExpanded( bExpanded ), m_bAbort( false ), m_bOK( false ), m_iSelected( 0 ), 
		m_iSelectedConstraint( 0 ), m_iSelectedError( 0 ), m_iSelectedVariable( 0 )
{
	m_spProject = project;

	COMTRY 
	{	
		CComBSTR app("GME.Application");
		CComPtr<IMgaClient> client;
		COMTHROW(m_spProject->GetClientByName((BSTR)app, &client));

		CComPtr<IDispatch> gui;
		COMTHROW(client->get_OLEServer(&gui));
		COMTHROW(gui.QueryInterface(&m_oleapp));
	}
	catch(hresult_exception &)
	{ 
	} 

	//{{AFX_DATA_INIT(CViolationDialog)
	//}}AFX_DATA_INIT
}

void CViolationDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViolationDialog)
	DDX_Control(pDX, CVD_LBLCONSTRAINT, m_lblConstraint);
	DDX_Control(pDX, CVD_FRMMESSAGE, m_frmMessage);
	DDX_Control(pDX, CVD_BTNPREVIOUS, m_btnPrevious);
	DDX_Control(pDX, CVD_BTNNEXT, m_btnNext);
	DDX_Control(pDX, CVD_BTNEXPAND, m_btnExpand);
	DDX_Control(pDX, CVD_TABCONTEXT, m_tabPages);
	DDX_Control(pDX, CVD_LBLGENERALMSG, m_lblGeneralMessage);
	DDX_Control(pDX, CVD_LSTOBJECTS, m_lstObjects);
	DDX_Control(pDX, CVD_BTNABORT, m_btnAbort);
	DDX_Control(pDX, CVD_LSTEXPRESSION, m_lstExpression);
	DDX_Control(pDX, CVD_LSTERRORS, m_lstErrors);
	DDX_Control(pDX, CVD_LSTCONSTRAINTS, m_lstConstraints);
	DDX_Control(pDX, CVD_ICNLARGE, m_imgLarge);
	DDX_Control(pDX, CVD_BTNCLOSE, m_btnClose);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViolationDialog, CDialog)
	//{{AFX_MSG_MAP(CViolationDialog)
	ON_BN_CLICKED(CVD_BTNCLOSE, OnClickClose)
	ON_NOTIFY(LVN_KEYDOWN, CVD_LSTCONSTRAINTS, OnKeyDownConstraints)
	ON_BN_CLICKED(CVD_BTNABORT, OnClickAbort)
	ON_NOTIFY(NM_CLICK, CVD_LSTCONSTRAINTS, OnClickConstraints)
	ON_NOTIFY(NM_CLICK, CVD_LSTERRORS, OnClickErrors)
	ON_NOTIFY(NM_CLICK, CVD_LSTOBJECTS, OnClickVariable)
	ON_NOTIFY(LVN_KEYDOWN, CVD_LSTERRORS, OnKeyDownErrors)
	ON_NOTIFY(TCN_SELCHANGE, CVD_TABCONTEXT, OnSelectionChangedTab)
	ON_BN_CLICKED(CVD_BTNEXPAND, OnClickExpand)
	ON_BN_CLICKED(CVD_BTNNEXT, OnClickNext)
	ON_BN_CLICKED(CVD_BTNPREVIOUS, OnClickPrevious)
	ON_NOTIFY(LVN_COLUMNCLICK, CVD_LSTCONSTRAINTS, OnClickConstraintsColumn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()






BOOL CViolationDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Load ImageLists

	m_lstConstraintImages.Create( 16, 16, ILC_COLOR24 | ILC_MASK, 10, 10 );
	CBitmap bmpTemp1;
	bmpTemp1.LoadBitmap( IDB_CONSTRAINTICONS );
	m_lstConstraintImages.Add( &bmpTemp1, RGB( 255, 0, 255 ) );

	m_lstErrorImages.Create( 16, 16, ILC_COLOR24 | ILC_MASK, 4, 4 );
	CBitmap bmpTemp2;
	bmpTemp2.LoadBitmap( IDB_ERRORICONS );
	m_lstErrorImages.Add( &bmpTemp2, RGB( 255, 0, 255 ) );

	m_lstLineImages.Create( 16, 16, ILC_COLOR24 | ILC_MASK, 2, 2 );
	CBitmap bmpTemp3;
	bmpTemp3.LoadBitmap( IDB_LINEICONS );
	m_lstLineImages.Add( &bmpTemp3, RGB( 255, 0, 255 ) );

	// Set required properties of ListControls

	m_lstConstraints.SetImageList( &m_lstConstraintImages, LVSIL_SMALL );

	int iLength = 3 * m_lstConstraints.GetStringWidth("Type") / 2;
	m_lstConstraints.InsertColumn( 0, "Type", LVCFMT_LEFT, iLength, -1 );
	iLength = 3 * m_lstConstraints.GetStringWidth("Context") / 2;
	m_lstConstraints.InsertColumn( 1, "Context", LVCFMT_LEFT, iLength, 1 );
	iLength = 3 * m_lstConstraints.GetStringWidth("Name") / 2;
	m_lstConstraints.InsertColumn( 2, "Name", LVCFMT_LEFT, iLength, 2 );

	m_lstConstraints.SetExtendedStyle( LVS_EX_FULLROWSELECT );

	m_lstErrors.SetImageList( &m_lstErrorImages, LVSIL_SMALL );

	iLength = 3 * m_lstErrors.GetStringWidth("Line") / 2;
	m_lstErrors.InsertColumn( 0, "Ln.", LVCFMT_LEFT, iLength, -1 );
	/*
	// This column is commented out because this features is not implemented yet
	// Be careful with uncommenting -> column numbers

	iLength = 3 * m_lstErrors.GetStringWidth("Column") / 2;
	m_lstErrors.InsertColumn( 2, "Col.", LVCFMT_LEFT, iLength, 1 );
	*/

	iLength = 3 * m_lstErrors.GetStringWidth("Message") / 2;
	m_lstErrors.InsertColumn( 1, "Message", LVCFMT_LEFT, iLength, 1 );
	iLength = 3 * m_lstErrors.GetStringWidth("Signature") / 2;
	m_lstErrors.InsertColumn( 2, "Signature", LVCFMT_LEFT, iLength, 2 );

	m_lstErrors.SetExtendedStyle( LVS_EX_FULLROWSELECT );

	m_lstExpression.SetImageList( &m_lstLineImages, LVSIL_SMALL );

	iLength = 3 * m_lstExpression.GetStringWidth("Line") / 2;
	m_lstExpression.InsertColumn( 0, "Line", LVCFMT_RIGHT, iLength, -1 );
	iLength = 3 * m_lstExpression.GetStringWidth("Expression") / 2;
	m_lstExpression.InsertColumn( 1, "Expression", LVCFMT_LEFT, iLength, 1 );

	m_lstExpression.SetExtendedStyle( LVS_EX_FULLROWSELECT );

	m_lstObjects.SetImageList( &m_lstLineImages, LVSIL_SMALL );

	iLength = 3 * m_lstObjects.GetStringWidth("Variable") / 2;
	m_lstObjects.InsertColumn( 0, "Variable", LVCFMT_RIGHT, iLength, -1 );
	iLength = 3 * m_lstObjects.GetStringWidth("Object") / 2;
	m_lstObjects.InsertColumn( 1, "Object", LVCFMT_LEFT, iLength, 1 );

	m_lstObjects.SetExtendedStyle( LVS_EX_FULLROWSELECT );

	// Fill Constraint List

	for ( unsigned int i = 0 ; i < m_vecRecords.size() ; i++ ) {
		LVITEM lvItem;
		lvItem.mask = LVIF_IMAGE | LVIF_PARAM;
		if ( i == 0 ) {
			lvItem.mask = lvItem.mask | LVIF_STATE;
			lvItem.state = LVIS_SELECTED;
			lvItem.stateMask = LVIS_SELECTED;
		}
		lvItem.iItem = m_lstConstraints.GetItemCount();
		lvItem.iSubItem = 0;
		lvItem.iImage = m_vecRecords[ i ].spConstraint->GetType();
		lvItem.lParam = i;
		m_lstConstraints.InsertItem( &lvItem );

		lvItem.mask = LVIF_TEXT;
		lvItem.iSubItem = 1;
		CString strText = m_vecRecords[ i ].spConstraint->GetContextType().c_str();// OclCommonEx::Convert( m_vecRecords[ i ].spConstraint->GetContextType() );
		lvItem.pszText = (char*)(LPCTSTR)strText; //.GetBuffer( strText.GetLength() );
		m_lstConstraints.SetItem( &lvItem );
//		strText.ReleaseBuffer();

		lvItem.iSubItem = 2;
		strText = m_vecRecords[ i ].spConstraint->GetName().c_str(); // OclCommonEx::Convert( m_vecRecords[ i ].spConstraint->GetName() );
		lvItem.pszText = (char*)(LPCTSTR)strText; //.GetBuffer( strText.GetLength() );
		m_lstConstraints.SetItem( &lvItem );
//		strText.ReleaseBuffer();
	}

	m_lstConstraints.SetColumnWidth( 0, LVSCW_AUTOSIZE_USEHEADER );
	m_lstConstraints.SetColumnWidth( 1, LVSCW_AUTOSIZE_USEHEADER );
	m_lstConstraints.SetColumnWidth( 2, LVSCW_AUTOSIZE_USEHEADER );

	// Display First Constraint

	SortConstraints( 2 );
	SortConstraints( 1 );
	SortConstraints( 0 );
	RefreshWidgets( true );

	// Enable Buttons

	m_btnAbort.EnableWindow( m_bAbort );
	m_btnClose.EnableWindow( m_bOK );

	m_tabPages.InsertItem(  0, _T("Expression") );
	m_tabPages.InsertItem(  1, _T("Variables") );
	m_lstObjects.ShowWindow( SW_HIDE );

	// Set Expanded vs Collapsed

	if ( ! m_bExpanded ) {
		m_bExpanded = true;
		OnClickExpand();
	}

	return TRUE;
}

void CViolationDialog::OnSelectionChangedTab(NMHDR* pNMHDR, LRESULT* pResult)
{
	m_lstObjects.ShowWindow( ( m_tabPages.GetCurSel() == 1 ) ? SW_SHOW : SW_HIDE );
	m_lstExpression.ShowWindow( ( m_tabPages.GetCurSel() == 0 ) ? SW_SHOW : SW_HIDE );
	*pResult = 0;
}

void CViolationDialog::OnClickClose()
{
	CDialog::OnOK();
}

void CViolationDialog::OnClickAbort()
{
	CDialog::OnCancel();
}

void CViolationDialog::OnClickExpand()
{
	m_bExpanded = ! m_bExpanded;

	m_btnExpand.SetWindowText( ( m_bExpanded ) ? "Collapse" : "Expand" );

	CRect rectEx;
	m_btnExpand.GetWindowRect( rectEx );

	CRect rectObj;
	m_lstObjects.GetWindowRect( rectObj );
	
	CRect rectExp;
	m_lstExpression.GetWindowRect( rectExp );

	CRect rectCon;
	m_lstConstraints.GetWindowRect( rectCon );

	CRect rectMes;
	m_frmMessage.GetWindowRect( rectMes );

	rectObj.TopLeft() = ( m_bExpanded ) ? rectExp.TopLeft() : rectCon.TopLeft();
	if ( m_bExpanded ) 
			rectObj.BottomRight() = rectExp.BottomRight();
	else {
		rectObj.right = rectEx.right;
		rectObj.bottom -= rectObj.Height() / 2;
	}

	m_lstConstraints.ShowWindow( ( m_bExpanded ) ? SW_SHOW : SW_HIDE );
	m_lstErrors.ShowWindow( ( m_bExpanded ) ? SW_SHOW : SW_HIDE );
	m_lstExpression.ShowWindow( ( m_bExpanded && m_tabPages.GetCurSel() == 0 ) ? SW_SHOW : SW_HIDE );
	m_lstObjects.ShowWindow( ( ! m_bExpanded || m_tabPages.GetCurSel() == 1 ) ? SW_SHOW : SW_HIDE );
	m_tabPages.ShowWindow( ( m_bExpanded ) ? SW_SHOW : SW_HIDE );

	int iYGap = rectCon.top - rectMes.bottom;
	int iTop = ( m_bExpanded ) ? rectCon.bottom + iYGap : rectObj.bottom + iYGap;

	ScreenToClient( rectObj );
	m_lstObjects.MoveWindow( rectObj );
	
	std::vector< CButton* > vecButtons;
	vecButtons.push_back( &m_btnNext ); vecButtons.push_back( &m_btnPrevious ); vecButtons.push_back( &m_btnClose ); vecButtons.push_back( &m_btnAbort );
	for ( unsigned int i = 0 ; i < vecButtons.size() ; i++ ) {
		CRect rect; vecButtons[ i ]->GetWindowRect( rect );
		int iHeight = rect.Height();
		rect.top = iTop;
		rect.bottom = iTop + iHeight;
		ScreenToClient( rect );
		vecButtons[ i ]->MoveWindow( rect );
	}

	CRect rectDlg;
	GetWindowRect( rectDlg );
	CRect rectBtn;
	m_btnPrevious.GetWindowRect( rectBtn );
	rectDlg.bottom = rectBtn.bottom + iYGap;
	MoveWindow( rectDlg );



}

void CViolationDialog::OnClickNext()
{
	SelectConstraint( true );
}

void CViolationDialog::OnClickPrevious()
{
	SelectConstraint( false );
}

void CViolationDialog::OnKeyDownConstraints(NMHDR* pNMHDR, LRESULT* pResult)
{
	LV_KEYDOWN* pLVKeyDown = (LV_KEYDOWN*)pNMHDR;
	if ( pLVKeyDown->wVKey == VK_UP )
		SelectConstraint( false );
	else
		if ( pLVKeyDown->wVKey == VK_DOWN )
			SelectConstraint( true );
	*pResult = 0;
}

void CViolationDialog::OnClickConstraints(NMHDR* pNMHDR, LRESULT* pResult)
{
	m_iSelected = min( max( m_lstConstraints.GetSelectionMark(), 0 ), m_lstConstraints.GetItemCount() - 1 );
	RefreshWidgets( true );
	*pResult = 0;
}

void CViolationDialog::OnClickVariable(NMHDR* pNMHDR, LRESULT* pResult)
{
	m_iSelectedVariable = min( max( m_lstObjects.GetSelectionMark(), 0 ), m_lstObjects.GetItemCount() - 1 );
	GotoObject();
}

void CViolationDialog::OnClickErrors(NMHDR* pNMHDR, LRESULT* pResult)
{
	m_iSelectedError = min( max( m_lstErrors.GetSelectionMark(), 0 ), m_lstErrors.GetItemCount() - 1 );
	DisplayErrorItem();
}

void CViolationDialog::OnKeyDownErrors(NMHDR* pNMHDR, LRESULT* pResult)
{
	LV_KEYDOWN* pLVKeyDown = (LV_KEYDOWN*)pNMHDR;
	if ( pLVKeyDown->wVKey == VK_UP )
		SelectError( false );
	else
		if ( pLVKeyDown->wVKey == VK_DOWN )
			SelectError( true );
	*pResult = 0;
}

BOOL CViolationDialog::PreTranslateMessage( MSG* pMsg )
{
	return ( pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE ) ? FALSE : CDialog::PreTranslateMessage( pMsg );
}

void CViolationDialog::OnClickConstraintsColumn(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	SortConstraints( pNMListView->iSubItem );
	*pResult = 0;
}

	void CViolationDialog::RefreshWidgets( bool bNewConstraint )
	{
		m_btnNext.EnableWindow( m_iSelected != m_lstConstraints.GetItemCount() - 1 );
		m_btnPrevious.EnableWindow( m_iSelected != 0 );
		if ( bNewConstraint ) {
			m_iSelectedConstraint = m_lstConstraints.GetItemData( m_iSelected );
			m_lstConstraints.SetItemState( m_iSelected, LVIS_SELECTED, LVIS_SELECTED );
			DisplayConstraintItem();
		}
	}

	void CViolationDialog::SelectConstraint( bool bNext )
	{
		if ( ! bNext ) {
			if ( m_iSelected != 0 ) {
				m_iSelected--;
				RefreshWidgets( true );
			}
		}
		else {
			if ( m_iSelected != m_lstConstraints.GetItemCount() - 1 ) {
				m_iSelected++;
				RefreshWidgets( true );
			}
		}
	}

	void CViolationDialog::SelectError( bool bNext )
	{
		if ( ! bNext ) {
			if ( m_iSelectedError != 0 ) {
				m_iSelectedError--;
				DisplayErrorItem();
			}
		}
		else {
			if ( m_iSelectedError != m_lstErrors.GetItemCount() - 1 ) {
				m_iSelectedError++;
				DisplayErrorItem();
			}
		}
	}

	bool CViolationDialog::IsExpanded() const
	{
		return m_bExpanded;
	}

	void CViolationDialog::AddItem( const EvaluationRecord& item )
	{
		m_vecRecords.push_back( item );
		// ??
		COMTRY 
		{
			OclTree::Violation vi = item.vecViolations[ item.vecViolations.size()-1 ]; // which violation ? 
			CComPtr<IUnknown> logfco = vi.vecObjectsPtr[0]; // self needed
			CComPtr<IMgaFCO> fco;
			COMTRY
			{
				COMTHROW(logfco.QueryInterface(&fco));
				CComBSTR bstr, id, nm;
				COMTHROW( fco->get_ID( &id));
				COMTHROW( fco->get_Name( &nm));
				bstr.Append("Constraint Violation: <A HREF=\"mga:");
				bstr.AppendBSTR( id);
				bstr.Append("\">");
				bstr.AppendBSTR( nm);
				bstr.Append("</A>: ");
				bstr.Append(item.spConstraint.Ptr()->GetMessage().c_str());
				COMTHROW(m_oleapp->ConsoleMessage(bstr, MSG_ERROR));
			}
			catch(hresult_exception &)// in case the constraint is not attached to any fco in the metamodel
			{                         // the constraint becomes project scoped, thus QueryInterface fails
				CComBSTR bstr;
				bstr.Append("Constraint ");
				bstr.Append(item.spConstraint.Ptr()->GetFullName().c_str());
				bstr.Append(" Violated! Description: \"");
				bstr.Append(item.spConstraint.Ptr()->GetMessage().c_str());
				bstr.Append("\".");
				COMTHROW(m_oleapp->ConsoleMessage(bstr, MSG_ERROR));
			}
		}
		catch(hresult_exception &)
		{ 
		}
	}

	void CViolationDialog::EnableAbort()
	{
		m_bAbort = true;
	}

	void CViolationDialog::EnableOK()
	{
		m_bOK = true;
	}

	void CViolationDialog::DisplayErrorItem()
	{
		// Set Line in Expression

		m_lstErrors.SetItemState( m_iSelectedError, LVIS_SELECTED, LVIS_SELECTED );

		OclTree::Violation vi = m_vecRecords[ m_iSelectedConstraint ].vecViolations[ m_iSelectedError ];
		int iLine = vi.position.iLine;

		for ( unsigned int i = 0 ; i < (unsigned int) m_lstExpression.GetItemCount() ; i++ ) {
			LVITEM lvItem;
			DWORD lparam = m_lstExpression.GetItemData(i);
			lvItem.mask = LVIF_IMAGE | LVIF_STATE;
			lvItem.state = ( lparam + 1 == (unsigned int) iLine ) ? LVIS_SELECTED : 0;
			lvItem.stateMask = LVIS_SELECTED;
			lvItem.iItem = i;
			lvItem.iSubItem = 0;
			lvItem.iImage = ( lparam + 1 == (unsigned int) iLine ) ? 1 : 0;
			m_lstExpression.SetItem( &lvItem );
			if ( lparam + 1 == (unsigned int) iLine )
				m_lstExpression.EnsureVisible( i, false );
		}

		// Add Objects

		m_lstObjects.DeleteAllItems();

		for ( unsigned int i = 0 ; i < vi.vecVariables.size() ; i++ ) {

			// Add Variable

			LVITEM lvItem;
			lvItem.mask = /*LVIF_NORECOMPUTE |*/ LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM;
			lvItem.iItem = m_lstObjects.GetItemCount();
			lvItem.iSubItem = 0;
			lvItem.iImage = 0;
			lvItem.lParam = i;
			CString strTemp = vi.vecVariables[ i ].c_str(); // OclCommonEx::Convert( vi.vecVariables[ i ] );
			lvItem.pszText = (char*)(LPCTSTR)strTemp;//.GetBuffer( strTemp.GetLength() );
			m_lstObjects.InsertItem( &lvItem );

//			strTemp.ReleaseBuffer();
			strTemp.Empty();

			// Add Object

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 1;
			strTemp = vi.vecObjects[ i ].c_str(); // OclCommonEx::Convert( vi.vecObjects[ i ] );
			lvItem.pszText = (char*)(LPCTSTR)strTemp; //.GetBuffer( strTemp.GetLength() );
			m_lstObjects.SetItem( &lvItem );

//			strTemp.ReleaseBuffer();
		}

//		m_lstObjects.SetColumnWidth( 0, LVSCW_AUTOSIZE_USEHEADER );
		m_lstObjects.SetColumnWidth( 0, 70);
		m_lstObjects.SetColumnWidth( 1, LVSCW_AUTOSIZE_USEHEADER );
		m_lstObjects.GetParent()->Invalidate();
	}

	void CViolationDialog::addFunctions()
	{
		CStringArray arrText;
		OclGmeCM::FuncDesc::iterator it;
		for (it = m_vecRecords[ m_iSelectedConstraint ].calledFunctions.begin(); 
				it != m_vecRecords[ m_iSelectedConstraint ].calledFunctions.end(); it++)
		{
			arrText.RemoveAll();
			int serial = it->second.serial;
			CString strExpression = it->second.text.c_str(); // OclCommonEx::Convert(it->second.text);
			strExpression.Replace( "\r", "" );
			strExpression.Replace( "\n", "\r\n" );
			strExpression.Replace( "\t", "    " );
			int iFPos = 0;
			do {
				iFPos = strExpression.Find( "\r\n" );
				if ( iFPos == -1 )
					arrText.Add( strExpression );
				else {
					arrText.Add( strExpression.Left( iFPos ) );
					strExpression = strExpression.Right( strExpression.GetLength() - iFPos - 2 );
				}
			} while ( iFPos != -1 );

			// Add Expression

			LVITEM lvItem;
			for ( int i = 0 ; i < arrText.GetSize() ; i++ ) {

				// Add Line

				lvItem.mask = LVIF_PARAM | LVIF_IMAGE | /*LVIF_NORECOMPUTE |*/ LVIF_TEXT;
				lvItem.iItem = m_lstExpression.GetItemCount();
				lvItem.iSubItem = 0;
				lvItem.iImage = 0;
				lvItem.lParam = it->second.serial*1000 +i;
				CString strTemp;
				strTemp.Format( "%d", it->second.serial*1000 + i + 1 );
				lvItem.pszText = (char*)(LPCTSTR)strTemp; //.GetBuffer( strTemp.GetLength() );
				m_lstExpression.InsertItem( &lvItem );

//				strTemp.ReleaseBuffer();
				strTemp.Empty();

				// Add ExpressionPiece

				lvItem.mask = LVIF_TEXT;
				lvItem.iSubItem = 1;
				strTemp = arrText.GetAt( i );
				lvItem.pszText = (char*)(LPCTSTR)strTemp; //.GetBuffer( strTemp.GetLength() );
				m_lstExpression.SetItem( &lvItem );

//				strTemp.ReleaseBuffer();
			}
		}
	}

	void CViolationDialog::DisplayConstraintItem()
	{
		// Set Constraint Name

		m_lblConstraint.SetWindowText( OclCommonEx::Convert( m_vecRecords[ m_iSelectedConstraint ].spConstraint->GetDefinedName() ) );

		// Set Constraint Text

		m_lstExpression.DeleteAllItems();

		CStringArray arrText;
		CString strExpression = m_vecRecords[ m_iSelectedConstraint ].spConstraint->GetText().c_str(); // OclCommonEx::Convert( m_vecRecords[ m_iSelectedConstraint ].spConstraint->GetText() );
		strExpression.Replace( "\r", "" );
		strExpression.Replace( "\n", "\r\n" );
		strExpression.Replace( "\t", "    " );
		int iFPos = 0;
		do {
			iFPos = strExpression.Find( "\r\n" );
			if ( iFPos == -1 )
				arrText.Add( strExpression );
			else {
				arrText.Add( strExpression.Left( iFPos ) );
				strExpression = strExpression.Right( strExpression.GetLength() - iFPos - 2 );
			}
		} while ( iFPos != -1 );

		// Add Expression

		LVITEM lvItem;
		for ( unsigned int i = 0 ; i < (unsigned int) arrText.GetSize() ; i++ ) {

			// Add Line

			lvItem.mask = LVIF_PARAM | LVIF_IMAGE | /*LVIF_NORECOMPUTE |*/ LVIF_TEXT;
			lvItem.iItem = m_lstExpression.GetItemCount();
			lvItem.iSubItem = 0;
			lvItem.iImage = 0;
			lvItem.lParam = i;
			CString strTemp;
			strTemp.Format( "%d", i + 1 );
			lvItem.pszText = (char*)(LPCTSTR)strTemp; // .GetBuffer( strTemp.GetLength() );
			m_lstExpression.InsertItem( &lvItem );

//			strTemp.ReleaseBuffer();
			strTemp.Empty();

			// Add ExpressionPiece

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 1;
			strTemp = arrText.GetAt( i );
			lvItem.pszText = (char*)(LPCTSTR)strTemp; // .GetBuffer( strTemp.GetLength() );
			m_lstExpression.SetItem( &lvItem );

//			strTemp.ReleaseBuffer();
		}

		addFunctions();

//		m_lstExpression.SetColumnWidth( 0, LVSCW_AUTOSIZE_USEHEADER );
		m_lstExpression.SetColumnWidth( 0, 50);
		m_lstExpression.SetColumnWidth( 1, LVSCW_AUTOSIZE_USEHEADER );
		m_lstExpression.SetWindowPos( &wndTop, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE );

		// Add Errors

		m_lstErrors.DeleteAllItems();

		OclTree::ViolationVector vecViolations = m_vecRecords[ m_iSelectedConstraint ].vecViolations;

		for ( unsigned int i = 0 ; i < vecViolations.size() ; i++ ) {
			OclTree::Violation vi = vecViolations[ i ];

			// Add Line

			lvItem.mask = LVIF_IMAGE | /*LVIF_NORECOMPUTE |*/ LVIF_TEXT;
			if ( i == 0 ) {
				lvItem.mask = lvItem.mask | LVIF_STATE;
				lvItem.state = LVIS_SELECTED;
			}
			lvItem.iItem = m_lstErrors.GetItemCount();
			lvItem.iSubItem = 0;
			lvItem.iImage = ( vi.bIsException ) ? 2 : 3;
			lvItem.lParam = i;
			CString strTemp;
			if ( vi.position.iLine < 0 )
				strTemp = "?";
			else
				strTemp.Format( "%d", vi.position.iLine );
			lvItem.pszText = (char*)(LPCTSTR)strTemp; //.GetBuffer( strTemp.GetLength() );
			m_lstErrors.InsertItem( &lvItem );

//			strTemp.ReleaseBuffer();
			strTemp.Empty();

			// Add Column

			/*
			// This column is commented out because this features is not implemented yet
			// Be careful with uncommenting -> column and subitem numbers

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 1;
			strTemp.Format( "%d", vi.position.iColumn );
			lvItem.pszText = (char*)(LPCTSTR)strTemp; //.GetBuffer( strTemp.GetLength() );
			m_lstErrors.SetItem( &lvItem );

//			strTemp.ReleaseBuffer();
			strTemp.Empty();
			*/

			// Add Message

			lvItem.mask = LVIF_TEXT;
			lvItem.iSubItem = 1;
			strTemp = vi.strMessage.c_str(); // OclCommonEx::Convert( vi.strMessage );
			lvItem.pszText = (char*)(LPCTSTR)strTemp; // .GetBuffer( strTemp.GetLength() );
			m_lstErrors.SetItem( &lvItem );

//			strTemp.ReleaseBuffer();
			strTemp.Empty();

			// Add Signature

			lvItem.iSubItem = 2;
			strTemp = vi.strSignature.c_str(); // OclCommonEx::Convert( vi.strSignature );
			lvItem.pszText = (char*)(LPCTSTR)strTemp; // .GetBuffer( strTemp.GetLength() );
			m_lstErrors.SetItem( &lvItem );

//			strTemp.ReleaseBuffer();
		}

		m_lstErrors.SetColumnWidth( 0, LVSCW_AUTOSIZE_USEHEADER );
		m_lstErrors.SetColumnWidth( 1, LVSCW_AUTOSIZE_USEHEADER );
		m_lstErrors.SetColumnWidth( 2, LVSCW_AUTOSIZE_USEHEADER );

		/*
		// This column is commented out because this features is not implemented yet
		// Be careful with uncommenting -> column numbers

		m_lstErrors.SetColumnWidth( 3, LVSCW_AUTOSIZE_USEHEADER );
		*/

		// Add Constraint Message

		m_lblGeneralMessage.SetWindowText( OclCommonEx::Convert( m_vecRecords[ m_iSelectedConstraint ].spConstraint->GetMessage() ) );

		if ( vecViolations.empty() )
			ASSERT( 0 );
		else {
			m_iSelectedError = 0;
			DisplayErrorItem();
		}
	}

	void CViolationDialog::SortConstraints( int iColumn )
	{
		SortStruct sortInfo;
		sortInfo.pDialog = this;
		sortInfo.iColumn = iColumn;
		m_lstConstraints.SortItems( CViolationDialog::CompareConstraint, ( LPARAM ) ( &sortInfo ) );

		for ( int i = 0 ; i < m_lstConstraints.GetItemCount() ; i++ )
			if ( m_lstConstraints.GetItemData( i ) == (unsigned int) m_iSelectedConstraint ) {
				m_iSelected = i;
			 	RefreshWidgets( false );
				return;
			}
	}

	int CALLBACK CViolationDialog::CompareConstraint( LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort )
	{
		SortStruct* pSortInfo = ( SortStruct* ) lParamSort;

		OclGme::SpConstraint spConstraint1 = pSortInfo->pDialog->m_vecRecords[ lParam1 ].spConstraint;
		OclGme::SpConstraint spConstraint2 = pSortInfo->pDialog->m_vecRecords[ lParam2 ].spConstraint;

		if ( pSortInfo->iColumn == 0 ) {
			int iType1 = spConstraint1->GetType();
			int iType2 = spConstraint2->GetType();
			return ( iType1 < iType2 ) ? -1 : ( iType1 > iType2 ) ? 1 : 0;
		}
		CString str1 = ( pSortInfo->iColumn == 1 ) ? spConstraint1->GetContextType().c_str() : spConstraint1->GetName().c_str(); // OclCommonEx::Convert( ( pSortInfo->iColumn == 1 ) ? spConstraint1->GetContextType() : spConstraint1->GetName() );
		CString str2 = ( pSortInfo->iColumn == 1 ) ? spConstraint2->GetContextType().c_str() : spConstraint2->GetName().c_str(); // OclCommonEx::Convert( ( pSortInfo->iColumn == 1 ) ? spConstraint2->GetContextType() : spConstraint2->GetName() );
		return strcmp( str1, str2 );
	}

	void CViolationDialog::GotoObject()
	{
		DWORD lparam = m_lstObjects.GetItemData(m_iSelectedVariable);
		OclTree::Violation vi = m_vecRecords[ m_iSelectedConstraint ].vecViolations[ m_iSelectedError ];
		m_gotopunk = vi.vecObjectsPtr[lparam];
		if (m_gotopunk)
			CDialog::OnOK();
	}


}; // namespace OclGmeCM



