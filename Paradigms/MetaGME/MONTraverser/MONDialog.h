//###############################################################################################################################################
//
//	Meta and Builder Object Network V2.0 for GME
//	CMONDialog.h
//
//###############################################################################################################################################

/*
	Copyright (c) Vanderbilt University, 2000-2004
	ALL RIGHTS RESERVED

	Vanderbilt University disclaims all warranties with regard to this
	software, including all implied warranties of merchantability
	and fitness.  In no event shall Vanderbilt University be liable for
	any special, indirect or consequential damages or any damages
	whatsoever resulting from loss of use, data or profits, whether
	in an action of contract, negligence or other tortious action,
	arising out of or in connection with the use or performance of
	this software.
*/

#if !defined(AFX_MONDIALOG_H__CAD57B83_27EF_46F2_B733_CB511C3F2239__INCLUDED_)
#define AFX_MONDIALOG_H__CAD57B83_27EF_46F2_B733_CB511C3F2239__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Resource.h"
#include "AfxCmn.h"
#include "MON.h"

//###############################################################################################################################################
//
// 	C L A S S : CMONDialog
//
//###############################################################################################################################################

class CMONDialog : public CDialog
{
// Construction
public:
	CMONDialog( const MON::Project& project, CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(CMONDialog)
	enum { IDD = IDD_MONTRAVERSER };
	CButton			m_btnBrowse;
	CEdit				m_edtOutput;
	CComboBoxEx		m_cmbObject;
	CComboBoxEx		m_cmbKind;
	BOOL				m_bToFile;
	BOOL				m_bNeedRegistry;
	int					m_iContext;
	CString				m_strFile;
	BOOL				m_bNameRef;
	BOOL	m_bNeedConstraints;
	BOOL	m_bFCOLinks;
	//}}AFX_DATA

	CImageList			m_lstImages;
	MON::Project		m_project;
	CStdioFile*			m_pFile;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMONDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void 	FillKindComboBox();
	void 	FillObjectComboBox();

	void 	PrintLine( const std::string& strTabs, const std::string& strLine );

	void 	PrintRegistryNode( const std::string& strTabs, const MON::RegistryNode& node );

	void 	PrintObject( const std::string& strTabs, const MON::MetaObject& object );
	void 	PrintFCO( const std::string& strTabs, const MON::FCO& object );

	void 	PrintContainment( const std::string& strTabs, const MON::Containment& cont );
	void 	PrintContainmentPart( const std::string& strTabs, const MON::ContainmentPart& part );

	void 	PrintAspect( const std::string& strTabs, const MON::Aspect& aspect );
	void 	PrintAttribute( const std::string& strTabs, const MON::Attribute& attribute );
	void 	PrintConstraint( const std::string& strTabs, const MON::Constraint& constraint );

	void 	PrintFolder( const std::string& strTabs, const MON::Folder& folder );
	void 	PrintAtom( const std::string& strTabs, const MON::Atom& atom );
	void 	PrintModel( const std::string& strTabs, const MON::Model& model );
	void 	PrintReference( const std::string& strTabs, const MON::Reference& reference );
	void 	PrintSet( const std::string& strTabs, const MON::Set& set );
	void	PrintConnection( const std::string& strTabs, const MON::Connection& connection );

	void 	PrintConstraints( const std::string& strTabs, const MON::MetaObject& object );
	void 	PrintAttributes( const std::string& strTabs );
	void 	PrintAspects( const std::string& strTabs );
	void 	PrintAtoms( const std::string& strTabs );
	void 	PrintModels( const std::string& strTabs );
	void 	PrintReferences( const std::string& strTabs );
	void 	PrintSets( const std::string& strTabs );
	void	PrintConnections( const std::string& strTabs );
	void 	PrintFolders( const std::string& strTabs );
	void 	PrintProject();


	// Generated message map functions
	//{{AFX_MSG(CMONDialog)
	afx_msg void OnBrowseClick();
	virtual BOOL OnInitDialog();
	afx_msg void OnFileCheckClick();
	afx_msg void OnContextEnabling();
	afx_msg void OnGenerateClick();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONDIALOG_H__CAD57B83_27EF_46F2_B733_CB511C3F2239__INCLUDED_)
