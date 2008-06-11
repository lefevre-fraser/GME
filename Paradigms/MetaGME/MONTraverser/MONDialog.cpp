//###############################################################################################################################################
//
//	Meta and Builder Object Network V2.0 for GME
//	CMONDialog.cpp
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

#include "stdafx.h"
// #include "component.h"
#include "MONDialog.h"
#include "AfxDlgs.h"
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma warning ( disable : 4101 )

#define FTAB "\t"
#define ETAB "   "

#define ATTR( strName, varValue )	\
	std::string( " " + std::string( strName ) + "=\"" + (std::string) Util::Variant( varValue ) + "\"" )

#define REF( strName, varObject ) 	\
	(												\
		( m_bNameRef ) ?				\
			std::string( " " + std::string( strName ) + "=\"" + (varObject).name() + "\"" )		\
		:			\
			std::string( " " + std::string( strName ) + "=\"" + (std::string) Util::Variant( (varObject).ref() ) + "\"" )		\
	)

#define NEWLINE	\
	PrintLine( strTabs, "" )

#define TAGBEGIN( strTag, attrs )								\
	{ {																\
		std::string strTheTag = strTag;							\
		std::string strTabs2 = strTabs;							\
		std::string strTabs = strTabs2 + ETAB;					\
		PrintLine( strTabs2, "<" + strTheTag + attrs + ">" );

#define TAGEND									 				\
		PrintLine( strTabs2, "</" + strTheTag + ">" );			\
	} }

#define TAG( strTag, attrs )					\
		PrintLine( strTabs, "<" + std::string( strTag ) + attrs + "/>" );

//###############################################################################################################################################
//
// 	C L A S S : CMONDialog
//
//###############################################################################################################################################

	CMONDialog::CMONDialog( const MON::Project& project, CWnd* pParent /*=NULL*/)
		: CDialog( CMONDialog::IDD, pParent ), m_project( project )
	{
		//{{AFX_DATA_INIT(CMONDialog)
		m_bToFile = FALSE;
		m_bNeedRegistry = FALSE;
		m_iContext = -1;
		m_strFile = _T("");
		m_bNameRef = FALSE;
	m_bNeedConstraints = FALSE;
		m_pFile = NULL;
	m_bFCOLinks = FALSE;
	//}}AFX_DATA_INIT
	}


	void CMONDialog::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		//{{AFX_DATA_MAP(CMONDialog)
		DDX_Control(pDX, IDC_BROWSE, m_btnBrowse);
		DDX_Control(pDX, IDC_EDTOUTPUT, m_edtOutput);
		DDX_Control(pDX, IDC_CMBOBJECT, m_cmbObject);
		DDX_Control(pDX, IDC_CMBKIND, m_cmbKind);
		DDX_Check(pDX, IDC_CHKFILE, m_bToFile);
		DDX_Check(pDX, IDC_CHKREGISTRY, m_bNeedRegistry);
		DDX_Radio(pDX, IDC_RDMODEL, m_iContext );
		DDX_Text(pDX, IDC_EDTFILE, m_strFile);
		DDX_Check(pDX, IDC_CHKREFTYPE, m_bNameRef);
	DDX_Check(pDX, IDC_CHKCONSTRAINT, m_bNeedConstraints);
	DDX_Check(pDX, IDC_CHKFCOLINK, m_bFCOLinks);
	//}}AFX_DATA_MAP
	}


	BEGIN_MESSAGE_MAP(CMONDialog, CDialog)
		//{{AFX_MSG_MAP(CMONDialog)
		ON_BN_CLICKED(IDC_BROWSE, OnBrowseClick)
		ON_BN_CLICKED(IDC_CHKFILE, OnFileCheckClick)
		ON_BN_CLICKED(IDC_RDKIND, OnContextEnabling)
		ON_BN_CLICKED(IDC_RDMODEL, OnContextEnabling)
		ON_BN_CLICKED(IDC_RDOBJECT, OnContextEnabling)
		ON_BN_CLICKED(IDOK, OnGenerateClick)
		//}}AFX_MSG_MAP
	END_MESSAGE_MAP()



	BOOL CMONDialog::OnInitDialog()
	{
		CDialog::OnInitDialog();

		m_lstImages.Create( 16, 16, ILC_COLOR24 | ILC_MASK, 12, 12 );
		CBitmap bmp;
		bmp.LoadBitmap( IDB_METAICONS );
		m_lstImages.Add( &bmp, RGB( 128, 158, 8 ) );
		m_cmbObject.SetImageList( &m_lstImages );
		m_cmbKind.SetImageList( &m_lstImages );
		m_iContext = 0;

		UpdateData( FALSE );
		OnContextEnabling();
		OnFileCheckClick();
		FillKindComboBox();
		FillObjectComboBox();

		return TRUE;
	}

	void CMONDialog::OnBrowseClick()
	{
		CFileDialog dlgFile( TRUE, "xml", CString( "MON_" ) + m_project.name().c_str(), OFN_HIDEREADONLY, NULL, this );
		if ( dlgFile.DoModal() == IDOK ) {
			m_strFile = dlgFile.GetPathName();
	 		UpdateData( FALSE );
		}
	}

	void CMONDialog::OnFileCheckClick()
	{
		UpdateData();
		m_btnBrowse.EnableWindow( m_bToFile );
		GetDlgItem( IDC_EDTFILE )->EnableWindow( m_bToFile );
	}

	void CMONDialog::OnContextEnabling()
	{
		UpdateData();
		m_cmbKind.EnableWindow( m_iContext == 1 );
		m_cmbObject.EnableWindow( m_iContext == 2 );
	}

	void CMONDialog::OnGenerateClick()
	{

		UpdateData();

		if ( m_bToFile )
			try {
				m_pFile = new CStdioFile( m_strFile, CFile::modeCreate | CFile::modeWrite );
			}
			catch ( const CFileException *) {
				AfxMessageBox( "File cannot be created!" );
				m_pFile = NULL;
			}

		try {
			m_edtOutput.SetWindowText( "" );
			switch ( m_iContext ) {
				case 0 :
					PrintProject();
					break;
				case 1 :
					switch ( m_cmbKind.GetItemData( m_cmbKind.GetCurSel() ) ) {
						case MON::OT_Folder :
							PrintFolders( "" );
							break;
						case MON::OT_Atom :
							PrintAtoms( "" );
							break;
						case MON::OT_Model :
							PrintModels( "" );
							break;
						case MON::OT_Set :
							PrintSets( "" );
							break;
						case MON::OT_Reference :
							PrintReferences( "" );
							break;
						case MON::OT_Connection :
							PrintConnections( "" );
							break;
						case MON::OT_Attribute :
							PrintAttributes( "" );
							break;
						case MON::OT_Aspect :
							PrintAspects( "" );
							break;
						default :
							AfxMessageBox( "Invalid ComboBoxEx Item" );
					}
					break;
				case 2 :
					PrintLine( "", "" );
					MON::Object object = m_project.findByRef( m_cmbObject.GetItemData( m_cmbObject.GetCurSel() ) );
					switch ( object.type() ) {
						case MON::OT_Folder :
							PrintFolder( "", MON::Folder( object ) );
							break;
						case MON::OT_Atom :
							PrintAtom( "", MON::Atom( object ) );
							break;
						case MON::OT_Model :
							PrintModel( "", MON::Model( object ) );
							break;
						case MON::OT_Set :
							PrintSet( "", MON::Set( object ) );
							break;
						case MON::OT_Reference :
							PrintReference( "", MON::Reference( object ) );
							break;
						case MON::OT_Connection :
							PrintConnection( "", MON::Connection( object ) );
							break;
						case MON::OT_Attribute :
							PrintAttribute( "", MON::Attribute( object ) );
							break;
						case MON::OT_Aspect :
							PrintAspect( "", MON::Aspect( object ) );
							break;
						default :
							AfxMessageBox( "Invalid ComboBoxEx Item" );
					}
					break;
			}
		}
		catch ( const CFileException *) {
			AfxMessageBox( "Error has occured during writing in the file!" );
		}

		if ( m_pFile ) {
			try {
				m_pFile->Close();
				delete m_pFile;
				m_pFile = NULL;
			}
			catch ( const CFileException *) {
				AfxMessageBox( "File cannot be closed!" );
				m_pFile = NULL;
			}
		}
	}

void InsertComboBoxItem( CComboBoxEx& combo, MON::ObjectType eType, const std::string& strName, long lValue )
{
	COMBOBOXEXITEM cbi;
	cbi.mask = CBEIF_INDENT | CBEIF_TEXT | CBEIF_IMAGE | CBEIF_OVERLAY | CBEIF_SELECTEDIMAGE | CBEIF_LPARAM;
	cbi.iItem = combo.GetCount();
	CString cstr( strName.c_str() );
	cbi.pszText = cstr.GetBuffer( cstr.GetLength() );
	cbi.cchTextMax = cstr.GetLength();
	cbi.iImage = eType;
	cbi.iSelectedImage = cbi.iImage;
	cbi.iOverlay = cbi.iImage;
	cbi.iIndent = I_INDENTCALLBACK;
	cbi.lParam = lValue;

	combo.InsertItem( &cbi );
	cstr.ReleaseBuffer();
}

	void CMONDialog::FillKindComboBox()
	{
		InsertComboBoxItem( m_cmbKind, MON::OT_Folder, "Folders", MON::OT_Folder );
		InsertComboBoxItem( m_cmbKind, MON::OT_Model, "Models", MON::OT_Model );
		InsertComboBoxItem( m_cmbKind, MON::OT_Atom, "Atoms", MON::OT_Atom );
		InsertComboBoxItem( m_cmbKind, MON::OT_Reference, "References", MON::OT_Reference );
		InsertComboBoxItem( m_cmbKind, MON::OT_Connection, "Connections", MON::OT_Connection );
		InsertComboBoxItem( m_cmbKind, MON::OT_Set, "Sets", MON::OT_Set );
		InsertComboBoxItem( m_cmbKind, MON::OT_Aspect, "Aspects", MON::OT_Aspect );
		InsertComboBoxItem( m_cmbKind, MON::OT_Attribute, "Attributes", MON::OT_Attribute );
		m_cmbKind.SetCurSel( 0 );
	}

struct LexicoSort
{
	bool operator() ( const MON::MetaObject& o1, const MON::MetaObject& o2 ) const
	{
		return o1.name() < o2.name();
	}
};

template <class T>
void vecSort( const std::set<T>& setT, std::vector<T>& vecT )
{
	vecT.clear();
	for ( std::set<T>::const_iterator it = setT.begin() ; it != setT.end() ; ++it )
		vecT.push_back( *it );
	std::sort( vecT.begin() , vecT.end(), LexicoSort() );
}

template<class T>
void insertVector( CComboBoxEx& combo, const std::set<T>& setT, MON::ObjectType eType )
{
	std::vector<T> objects;
	vecSort<T>( setT, objects );
	for ( int i = 0 ; i  < objects.size() ; i++ )
		InsertComboBoxItem( combo, eType, objects[ i ].name(), objects[ i ].ref() );
}

	void CMONDialog::FillObjectComboBox()
	{
		MON::Object rootFolder = m_project.findByName( "RootFolder" );
		InsertComboBoxItem( m_cmbObject, MON::OT_Null, rootFolder.name(), rootFolder.ref() );

		std::vector<MON::Folder> folders;
		vecSort<MON::Folder>( m_project.folders(), folders );
		for ( int i = 0 ; i  < folders.size() ; i++ )
			if ( folders[ i ].name() != "RootFolder" )
				InsertComboBoxItem( m_cmbObject, MON::OT_Folder, folders[ i ].name(), folders[ i ].ref() );

		insertVector<MON::Model>( m_cmbObject, m_project.models(), MON::OT_Model );
		insertVector<MON::Atom>( m_cmbObject, m_project.atoms(), MON::OT_Atom );
		insertVector<MON::Reference>( m_cmbObject, m_project.references(), MON::OT_Reference );
		insertVector<MON::Connection>( m_cmbObject, m_project.connections(), MON::OT_Connection );
		insertVector<MON::Set>( m_cmbObject, m_project.sets(), MON::OT_Set );
		insertVector<MON::Aspect>( m_cmbObject, m_project.aspects(), MON::OT_Aspect );
		insertVector<MON::Attribute>( m_cmbObject, m_project.attributes(), MON::OT_Attribute );
		if ( m_cmbObject.GetCount() == 0 )
			GetDlgItem( IDC_RDOBJECT )->EnableWindow( FALSE );
		else
			m_cmbObject.SetCurSel( 0 );
	}

	void CMONDialog::PrintLine( const std::string& strTabs, const std::string& strLine )
	{
		m_edtOutput.SetSel( m_edtOutput.LineIndex( m_edtOutput.GetLineCount() - 1 ), -1 );
		m_edtOutput.ReplaceSel( ( strTabs + strLine + "\r\n" ).c_str() );
		if ( m_bToFile && m_pFile )
			m_pFile->WriteString( ( strTabs + strLine + "\n" ).c_str() );
	}

	void CMONDialog::PrintRegistryNode( const std::string& strTabs, const MON::RegistryNode& node )
	{
		TAGBEGIN( "RegistryNode", ATTR( "name", node.name() ) + ATTR( "value", node.value() ) ) {
			std::set<MON::RegistryNode> setNodes = node.children();
			for ( std::set<MON::RegistryNode>::iterator it = setNodes.begin() ; it != setNodes.end() ; ++it ) {
				PrintRegistryNode( strTabs + ETAB, *it );
			}
		} TAGEND;
	}

	void CMONDialog::PrintObject( const std::string& strTabs, const MON::MetaObject& object )
	{
		if ( m_bNeedRegistry ) {
			std::set<MON::RegistryNode> setNodes = object.registry().children();
			for ( std::set<MON::RegistryNode>::iterator it = setNodes.begin() ; it != setNodes.end() ; ++it ) {
				PrintRegistryNode( strTabs, *it );
			}
		}
	}

	void CMONDialog::PrintFCO( const std::string& strTabs, const MON::FCO& fco )
	{
		std::set<MON::Attribute> setAttributes = fco.attributes();
		for ( std::set<MON::Attribute>::iterator it = setAttributes.begin() ; it != setAttributes.end() ; ++it )
			TAG( "Attribute", REF( "ref", *it ) );
		PrintConstraints( strTabs, fco );
	}

	void CMONDialog::PrintAttribute( const std::string& strTabs, const MON::Attribute& attribute )
	{
		std::string strType = "Enumeration";
		switch ( attribute.valueType() ) {
			case MON::AT_String :		strType = "String"; break;
			case MON::AT_Real :		strType = "Real"; break;
			case MON::AT_Boolean :	strType = "Boolean"; break;
			case MON::AT_Integer : 	strType = "Integer"; break;
		}
		TAGBEGIN( "Attribute", ATTR( "name", attribute.name() ) + ATTR( "displayedName", attribute.displayedName() ) + ATTR( "type", strType ) + ATTR( "default", attribute.defaultValue() ) + ATTR( "ref", attribute.ref() ) ) {
			if ( strType == "Enumeration" ) {
				std::vector<MON::Attribute::NameValue> vecItems = attribute.enumItems();
				for ( int i = 0 ; i < vecItems.size() ; i++ )
					TAG( "EnumItem", ATTR( "name", vecItems[ i ].first ) + ATTR( "value", vecItems[ i ].second ) );
			}
			PrintObject( strTabs, attribute );
		} TAGEND;
	}

	void CMONDialog::PrintConstraint( const std::string& strTabs, const MON::Constraint& constraint )
	{
		std::set<MON::ObjectEventType> setEvents = constraint.events();
		std::string strEvents = " ";
		if ( isAll( setEvents ) )
			strEvents = " All ";
		else {
			for ( MON::ObjectEventType eType = MON::OET_None ; eType != MON::OET_All ; eType++ )
				if ( setEvents.find( eType ) != setEvents.end() )
					strEvents += toString( eType ) + " ";
		}
		std::string strDepth;
		switch ( constraint.depth() ) {
			case MON::CD_Zero : strDepth = "0"; break;
			case MON::CD_One : strDepth = "1"; break;
			default : strDepth = "Any";
		}
		TAGBEGIN( "Constraint", ATTR( "name", constraint.name() ) + ATTR( "description", constraint.description() ) + ATTR( "priority", (long) constraint.priority() ) + ATTR( "depth", strDepth ) + ATTR( "events", strEvents ) ) {
			PrintLine( strTabs, "<![CDATA[" );
			std::vector<std::string> vecExpr = constraint.equation();
			for ( int i = 0 ; i < vecExpr.size() ; i ++ ) {
				PrintLine( strTabs, vecExpr[ i ] );
			}
			PrintLine( strTabs, "]]>" );
		} TAGEND;
	}

	void CMONDialog::PrintAspect( const std::string& strTabs, const MON::Aspect& aspect )
	{
		TAGBEGIN( "Aspect", ATTR( "name", aspect.name() ) + ATTR( "displayedName", aspect.displayedName() ) + ATTR( "ref", aspect.ref() ) ) {
			std::set<MON::Model> setModels = aspect.models();
			for ( std::set<MON::Model>::iterator it = setModels.begin() ; it != setModels.end() ; ++it )
				TAG( "Model", REF( "ref", *it ) );
			PrintObject( strTabs, aspect );
		} TAGEND;
	}

	void CMONDialog::PrintContainmentPart( const std::string& strTabs, const MON::ContainmentPart& part )
	{
		TAGBEGIN( "Part", ATTR( "name", part.aspect().name() ) + REF( "aspect", part.aspect() ) + ATTR( "isLinked", part.isLinked() ) + ATTR( "isPrimary", part.isPrimary() ) + ATTR( "ref", part.ref() ) ) {
			PrintObject( strTabs, part );
		} TAGEND;
	}

	void CMONDialog::PrintContainment( const std::string& strTabs, const MON::Containment& cont )
	{
		TAGBEGIN( "Containment", ATTR( "name", cont.name() ) + REF( "fco", cont.child() ) + ATTR( "ref", cont.ref() ) ) {
			std::set<MON::ContainmentPart> setParts = cont.parts();
			for ( std::set<MON::ContainmentPart>::iterator it = setParts.begin() ; it != setParts.end() ; ++it )
				PrintContainmentPart( strTabs, *it );
			PrintObject( strTabs, cont );
		} TAGEND;
	}

	void CMONDialog::PrintAtom( const std::string& strTabs, const MON::Atom& atom )
	{
		TAGBEGIN( "Atom", ATTR( "name", atom.name() ) + ATTR( "displayedName", atom.displayedName() ) + ATTR( "ref", atom.ref() ) ) {
			PrintFCO( strTabs, atom );
			PrintObject( strTabs, atom );
		} TAGEND;
	}

	void CMONDialog::PrintModel( const std::string& strTabs, const MON::Model& model )
	{
		TAGBEGIN( "Model", ATTR( "name", model.name() ) + ATTR( "displayedName", model.displayedName() ) + ATTR( "ref", model.ref() ) ) {
			PrintFCO( strTabs, model );
			std::set<MON::Containment> setContainments = model.childContainments();
			for ( std::set<MON::Containment>::iterator it = setContainments.begin() ; it != setContainments.end() ; ++it )
				PrintContainment( strTabs, *it );
			PrintObject( strTabs, model );
		} TAGEND;
	}

	void CMONDialog::PrintReference( const std::string& strTabs, const MON::Reference& reference )
	{
		TAGBEGIN( "Reference", ATTR( "name", reference.name() ) + ATTR( "displayedName", reference.displayedName() ) + ATTR( "ref", reference.ref() ) ) {
			PrintFCO( strTabs, reference );
			if ( m_bFCOLinks ) {
				std::set<MON::FCO> setFCOs = reference.targetFCOs();
				for ( std::set<MON::FCO>::iterator it = setFCOs.begin() ; it != setFCOs.end() ; ++it )
					TAG( "Target", REF( "ref", *it ) );
			}
			else {
				std::set<MON::FCO> setFCOs = reference.targetFCOs();
				for ( std::set<MON::FCO>::iterator it_fco = setFCOs.begin() ; it_fco != setFCOs.end() ; ++it_fco ) {
					std::set<MON::Containment> setRoles = (*it_fco).parentContainments();
					for ( std::set<MON::Containment>::iterator it = setRoles.begin() ; it != setRoles.end() ; ++it ) {
						if ( m_bNameRef ) {
							TAG( "TargetRole", ATTR( "name", it->name() ) + ATTR( "model", it->parent().name() ) );
						}
						else {
							TAG( "Target", REF( "ref", *it ) );
						}
					}
				}
			}

			PrintObject( strTabs, reference);
		} TAGEND;
	}

	void CMONDialog::PrintSet( const std::string& strTabs, const MON::Set& set )
	{
		TAGBEGIN( "Set", ATTR( "name", set.name() ) + ATTR( "displayedName", set.displayedName() ) + ATTR( "ref", set.ref() ) ) {
			PrintFCO( strTabs, set );
			if ( m_bFCOLinks ) {
				std::set<MON::Containment> setRoles = set.memberRoles();
				std::set<MON::FCO> setFCOs;
				for ( std::set<MON::Containment>::iterator itr = setRoles.begin() ; itr != setRoles.end() ; ++itr )
					setFCOs.insert( itr->child() );
				for ( std::set<MON::FCO>::iterator it = setFCOs.begin() ; it != setFCOs.end() ; ++it )
					TAG( "Member", REF( "ref", *it ) );
			}
			else {
				std::set<MON::Containment> setRoles = set.memberRoles();
				for ( std::set<MON::Containment>::iterator it = setRoles.begin() ; it != setRoles.end() ; ++it )
					if ( m_bNameRef ) {
						TAG( "TargetRole", ATTR( "name", it->name() ) + ATTR( "model", it->parent().name() ) );
					}
					else {
						TAG( "Target", REF( "ref", *it ) );
					}
			}

			PrintObject( strTabs, set );
		} TAGEND;
	}

	void CMONDialog::PrintConnection( const std::string& strTabs, const MON::Connection& connection )
	{
		TAGBEGIN( "Connection", ATTR( "name", connection.name() ) + ATTR( "displayedName", connection.displayedName() ) + ATTR( "ref", connection.ref() ) ) {
			PrintFCO( strTabs, connection );
			std::set<MON::ConnectionSpecification> setSpecs = connection.specifications();
			for ( std::set<MON::ConnectionSpecification>::iterator itS = setSpecs.begin() ; itS != setSpecs.end() ; itS++ ) {
				TAGBEGIN( "ConnectionSpecification", ATTR( "num", (long) itS->number() ) ) {
					std::set<MON::ConnectionRole> setCRoles = itS->roles();
					for ( std::set<MON::ConnectionRole>::iterator itR = setCRoles.begin() ; itR != setCRoles.end() ; itR++ ) {
						TAGBEGIN( "ConnectionRole", ATTR( "name", itR->name() ) ) {
							if ( m_bFCOLinks ) {
								std::set<MON::FCO> setFCOs = itR->targets();
								for ( std::set<MON::FCO>::iterator it = setFCOs.begin() ; it != setFCOs.end() ; ++it )
									TAG( "ConnectionEnd", REF( "ref", *it ) );
							}
							else {
								std::set<MON::Containment> setRoles = itR->targetRoles();
								for ( std::set<MON::Containment>::iterator it = setRoles.begin() ; it != setRoles.end() ; ++it )
									if ( m_bNameRef ) {
										TAG( "ConnectionEndRole", ATTR( "name", it->name() ) + ATTR( "model", it->parent().name() ) );
									}
									else {
										TAG( "ConnectionEndRole", REF( "ref", *it ) );
									}
							}
						} TAGEND;
					}
				} TAGEND;
			}
			PrintObject( strTabs, connection );
		} TAGEND;
	}

	void CMONDialog::PrintFolder( const std::string& strTabs, const MON::Folder& folder )
	{
		TAGBEGIN( "Folder", ATTR( "name", folder.name() ) + ATTR( "displayedName", folder.displayedName() ) + ATTR( "ref", folder.ref() ) ) {
			std::set<MON::Object> setObjects = folder.childObjects();
			for ( std::set<MON::Object>::iterator it = setObjects.begin() ; it != setObjects.end() ; ++it )
				TAG( "Child", REF( "ref", *it ) );
			PrintConstraints( strTabs, folder );
			PrintObject( strTabs, folder );
		} TAGEND;
	}

	void CMONDialog::PrintConstraints( const std::string& strTabs, const MON::MetaObject& object )
	{
		if ( m_bNeedConstraints ) {
			std::set<MON::Constraint> set = ( object.type() == MON::OT_Folder ) ? MON::Folder( object ).constraints() : MON::FCO( object ).constraints();
			for ( std::set<MON::Constraint>::iterator it = set.begin() ; it != set.end() ; ++it ) {
				PrintConstraint( strTabs, *it );
			}
		}
	}

	void CMONDialog::PrintAttributes( const std::string& strTabs )
	{
		std::set<MON::Attribute> set = m_project.attributes();
		for ( std::set<MON::Attribute>::iterator it = set.begin() ; it != set.end() ; ++it ) {
			NEWLINE;
			PrintAttribute( strTabs, *it );
		}
	}

	void CMONDialog::PrintAspects( const std::string& strTabs )
	{
		std::set<MON::Aspect> set = m_project.aspects();
		for ( std::set<MON::Aspect>::iterator it = set.begin() ; it != set.end() ; ++it ) {
			NEWLINE;
			PrintAspect( strTabs, *it );
		}
	}

	void CMONDialog::PrintAtoms( const std::string& strTabs )
	{
		std::set<MON::Atom> set = m_project.atoms();
		for ( std::set<MON::Atom>::iterator it = set.begin() ; it != set.end() ; ++it ) {
			NEWLINE;
			PrintAtom( strTabs, *it );
		}
	}

	void CMONDialog::PrintModels( const std::string& strTabs )
	{
		std::set<MON::Model> set = m_project.models();
		for ( std::set<MON::Model>::iterator it = set.begin() ; it != set.end() ; ++it ) {
			NEWLINE;
			PrintModel( strTabs, *it );
		}
	}

	void CMONDialog::PrintReferences( const std::string& strTabs )
	{
		std::set<MON::Reference> set = m_project.references();
		for ( std::set<MON::Reference>::iterator it = set.begin() ; it != set.end() ; ++it ) {
			NEWLINE;
			PrintReference( strTabs, *it );
		}
	}

	void CMONDialog::PrintSets( const std::string& strTabs )
	{
		std::set<MON::Set> set = m_project.sets();
		for ( std::set<MON::Set>::iterator it = set.begin() ; it != set.end() ; ++it ) {
			NEWLINE;
			PrintSet( strTabs, *it );
		}
	}

	void CMONDialog::PrintConnections( const std::string& strTabs )
	{
		std::set<MON::Connection> set = m_project.connections();
		for ( std::set<MON::Connection>::iterator it = set.begin() ; it != set.end() ; ++it ) {
			NEWLINE;
			PrintConnection( strTabs, *it );
		}
	}

	void CMONDialog::PrintFolders( const std::string& strTabs )
	{
		std::set<MON::Folder> set = m_project.folders();
		for ( std::set<MON::Folder>::iterator it = set.begin() ; it != set.end() ; ++it ) {
			NEWLINE;
			PrintFolder( strTabs, *it );
		}
	}

	void CMONDialog::PrintProject()
	{
		std::string strTabs( "" );
		NEWLINE;
		TAGBEGIN( "Project", ATTR( "name", m_project.name() ) + ATTR( "displayedName", m_project.displayedName() ) + ATTR( "author", m_project.author() ) + ATTR( "comment", m_project.comment() ) + ATTR( "creationTime", m_project.creationTime() ) ) {
			NEWLINE; PrintLine( strTabs, "<!-- ============= Aspects ============= -->" );
			PrintAspects( strTabs );
			NEWLINE; PrintLine( strTabs, "<!-- ============= Attributes ============= -->" );
			PrintAttributes( strTabs );
			NEWLINE; PrintLine( strTabs, "<!-- ============= Folders ============= -->" );
			PrintFolders( strTabs );
			NEWLINE; PrintLine( strTabs, "<!-- ============= Models ============= -->" );
			PrintModels( strTabs );
			NEWLINE; PrintLine( strTabs, "<!-- ============= Atoms ============= -->" );
			PrintAtoms( strTabs );
			NEWLINE; PrintLine( strTabs, "<!-- ============= Sets ============= -->" );
			PrintSets( strTabs );
			NEWLINE; PrintLine( strTabs, "<!-- ============= References ============= -->" );
			PrintReferences( strTabs );
			NEWLINE; PrintLine( strTabs, "<!-- ============= Connections ============= -->" );
			PrintConnections( strTabs );
			NEWLINE;
		} TAGEND;
	}
