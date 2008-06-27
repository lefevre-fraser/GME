///////////////////////////////////////////////////////////////////////////
// RawComponent.cpp, the main RAW COM component implementation file
// This is the file (along with its header RawComponent.h)
// that the component implementor is expected to modify in the first place
//
///////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "ComHelp.h"
#include "GMECOM.h"
#include <ComponentConfig.h>
#include "RawComponent.h"

#include "logger.h"
#include <string>
#include "Dumper.h"
#include "NameSpecDlg.h"
#include "globals.h"
Globals global_vars;
NameSpecDlg * dlg;

// this method is called after all the generic initialization is done
// this should be empty, unless application-specific initialization is needed
STDMETHODIMP RawComponent::Initialize(struct IMgaProject *) {
	return S_OK;
}

void RawComponent::finalize()
{
	m_entities.clear();
	m_relations.clear();
	m_equivRelations.clear();
	//m_toBeDeletedEntities.clear();
	m_equivBag.clear();
	m_realObj.clear();

	Sheet::m_BON_Project_Root_Folder = NULL; // crucial!!!

	if ( m_sheet != 0)  
	{ 
		TO( "Internal error: Merged Paradigm Sheet object still exists."); 
		delete m_sheet; 
		m_sheet = 0; 
	}
}

void RawComponent::scanSubModels( IMgaModel* model)
{
	CComPtr<IMgaFCOs> children;
	COMTHROW( model->get_ChildFCOs( &children));

	long c = 0;
	if( children) COMTHROW( children->get_Count( &c));

	for( long i = 1; i <= c; ++i)
	{
		CComPtr<IMgaFCO> ch;
		COMTHROW( children->get_Item( i, &ch));

		CComQIPtr<IMgaModel> mch( ch); // model child?
		if( mch) scanSubModels( mch);
	}
}


void RawComponent::scanModels( IMgaModel* model, IMgaFolder* parent)
{
	scanSubModels( model);
	entityBuilder( model, parent);
}


void RawComponent::scanSubFolders( IMgaFolders* subfolders, CComPtr<IMgaFolders>& result)
{
	if( !subfolders) return;
	if( !result) return;

	// result->Append( subfolders);
	long c = 0;
	COMTHROW( subfolders->get_Count( &c));
	CComPtr<IMgaFolder> ch;
	for( long i = 1; i <= c; ++i)
	{
		COMTHROW( subfolders->get_Item( i, &ch));
		result->Append( ch);

		CComPtr<IMgaFolders> childfolders;
		COMTHROW( ch->get_ChildFolders( &childfolders));
		scanSubFolders( childfolders, result);
	}
}


void RawComponent::scanProject( IMgaProject* project)
{
	try
	{
		CComPtr<IMgaFolder> rf;
		COMTHROW( project->get_RootFolder( &rf));
		Sheet::m_BON_Project_Root_Folder = rf;

		CComPtr<IMgaFolders> folders;
		folders.CoCreateInstance( L"Mga.MgaFolders");
		COMTHROW( folders->Append( rf)); // including root folder
		CComPtr<IMgaFolders> subfolders;
		COMTHROW( rf->get_ChildFolders( &subfolders)); // scan folders (libraries are included also)
		// folders->AppendAll( subfolders); 
		long c = 0;
		if( subfolders) COMTHROW( subfolders->get_Count( &c));
		
		for( long i = 1; i <= c; ++i)
		{
			CComPtr<IMgaFolder> ch;
			COMTHROW( subfolders->get_Item( i, &ch));
			COMTHROW( folders->Append( ch));
		}
		
		long d = 0;
		if( folders) COMTHROW( folders->get_Count( &d));
		for( long i = 1; i <= d; ++i)
		{
			CComPtr<IMgaFolder> ch;
			COMTHROW( folders->get_Item( i, &ch));
			CComPtr<IMgaFCOs> chfcos;
			if( ch) COMTHROW( ch->get_ChildFCOs( &chfcos));
			long e = 0;
			if( chfcos) COMTHROW( chfcos->get_Count( &e));
			for( long j = 1; j <= e; ++j)
			{
				CComPtr<IMgaFCO> inner_ch;
				COMTHROW( chfcos->get_Item( j, &inner_ch));
				CComQIPtr<IMgaModel> chmod( inner_ch);
				if( chmod) scanModels( chmod, ch); // scan all root models
			}
		}
	}
	catch(...)
	{
		global_vars.err << MSG_ERROR << "Exception thrown during project scanning.\n";
	}
}


void RawComponent::initMembers( IMgaProject* project)
{
	CComBSTR nm;
	COMTHROW( project->get_Name( &nm));
	m_projectName = Util::Copy( nm);
	m_dir = "";

	if ( global_vars.silent_mode)
	{
		CComBSTR    connString;
		COMTHROW( project->get_ProjectConnStr(&connString));
		std::string path = Util::Copy( connString);
		int e = path.rfind('\\');
		if( e != std::string::npos && path.substr(0, 4) == "MGA=") m_dir = path.substr(4, e-3); // cut leading "MGA=" , preserve tailing '\\'
	}

	m_entities.clear();
	//m_toBeDeletedEntities.clear();
	m_relations.clear();
	m_equivRelations.clear();
	m_realObj.clear();

	m_sheet = 0;
}


void RawComponent::createSheet()
{
	//
	//TODO : create your own Sheet instance (should be a derived class from the Sheet)
	//       store the pointer in the m_sheet member
	m_sheet = Dumper::getInstance();
}	


bool RawComponent::populateSheet( IMgaProject* project )
{
	m_sheet->setProject( project );

	bool error = false;

	Entity_Iterator it_1( m_entities.begin());

	Any * new_elem = 0;

	for( ; it_1 != m_entities.end(); ++it_1 )
	{
		if ( it_1->isDeleted()) continue;

		IMgaFCO* fco( it_1->getPointer());
		IMgaFCO* resp( it_1->getRespPointer());
		IMgaFolder* parent_folder( it_1->getParentFolder());
		IMgaFolder* orig_parent_folder( parent_folder);

		if( Util::islibobj( parent_folder)) // element's parent is in a library?
		{
			// This means we face a nested library, whose rootfolder is also
			// write protected, meaning that it's registry can't be written.
			// We will use the main rootfolder instead
			CComPtr<IMgaFolder> rf;
			COMTHROW( project->get_RootFolder( &rf));
			parent_folder = rf;
		}

		if ( !fco) global_vars.err << MSG_ERROR << "Populate sheet: tries to create Rep with empty FCO.\n";
		else
		{
			new_elem = 0;
			std::string stereotype = Util::kind( fco);

			if ( stereotype == "FCO" )
				new_elem = m_sheet->createFcoRep( fco, resp);
			else if ( stereotype == "Atom" )
				new_elem = m_sheet->createAtomRep( fco, resp);
			else if ( stereotype == "Model" )
				new_elem = m_sheet->createModelRep( fco, resp);
			else if ( stereotype == "Connection" )
				new_elem = m_sheet->createConnectionRep( fco, resp);
			else if ( stereotype == "Set" )
				new_elem = m_sheet->createSetRep( fco, resp);
			else if ( stereotype == "Reference" )
				new_elem = m_sheet->createReferenceRep( fco, resp);
			else if ( stereotype == "Folder" )
				new_elem = m_sheet->createFolderRep( fco, resp);//(resp != BON::FCO())?resp:fco);
			else if ( stereotype == "Aspect" )
				new_elem = m_sheet->createAspectRep( fco, resp);//(resp != BON::FCO())?resp:fco);
			else if ( stereotype == "Constraint" )
				new_elem = m_sheet->createConstraintRep( fco);
			else if ( stereotype == "ConstraintFunc" )
				new_elem = m_sheet->createConstraintFuncRep( fco);
			else if ( stereotype == "BooleanAttribute" )
				new_elem = m_sheet->createBoolAttributeRep( fco);
			else if ( stereotype == "EnumAttribute" )
				new_elem = m_sheet->createEnumAttributeRep( fco);
			else if ( stereotype == "FieldAttribute" )
				new_elem = m_sheet->createFieldAttributeRep( fco);
			else 
			{ 
				global_vars.err << MSG_ERROR << "Not inserted into the sheet: " << fco << " of kind: " << Util::kind( fco) << "\n";
				error = true;
			}
			if (new_elem)
			{
				new_elem->setParentFolder( parent_folder, orig_parent_folder); 
				if ( m_equivBag.find( fco) != m_equivBag.end())
				{
					new_elem->setEquivPeers( m_equivBag[ fco]);
					new_elem->setDisplayedName( it_1->getDispName());
				}
			}
		}
	} // for m_entities

	if (error) 
	{
		global_vars.err << MSG_ERROR << "Internal error during creation of entities. Exiting\n";
		return false;
	}

	Relation_Iterator rel_it = m_relations.begin();
	for( ; rel_it != m_relations.end(); ++rel_it)
	{
		Relation::OPER_TYPE oper = rel_it->getOperation();
		if ( oper == Relation::INHERITANCE_OP ||
				oper == Relation::INT_INHERITANCE_OP ||
				oper == Relation::IMP_INHERITANCE_OP)
			inheritancesManager( *rel_it);
		else if ( oper == Relation::ASSOCIATION_OP)
			associationClassManager( *rel_it);
		else if ( oper == Relation::REFER_TO_OP)
			refersToManager( *rel_it);
		else if ( oper == Relation::SET_MEMBER_OP)
			setMemberManager( *rel_it);
		else if ( oper == Relation::CONTAINMENT_OP)
			containmentManager( *rel_it);
		else if ( oper == Relation::FOLDER_CONTAINMENT_OP)
			folderContainmentManager( *rel_it);
		else if ( oper == Relation::HAS_ASPECT_OP)
			hasAspectManager( *rel_it);
		else if ( oper == Relation::ASPECT_MEMBER_OP)
			aspectMemberManager( *rel_it);
		else if ( oper == Relation::HAS_CONSTRAINT_OP)
			hasConstraintManager( *rel_it);
		else if ( oper == Relation::HAS_ATTRIBUTE_OP)
			hasAttributeManager( *rel_it);
	}

	if (error) 
	{
		global_vars.err << MSG_ERROR << "Internal error during the relation establishment. Exiting\n";
		return false;
	}

	return true;
}


bool RawComponent::executeSheet()
{
	bool success = false;
	try 
	{
		//CRUCIAL step: the role names may be short or long form
		success = m_sheet->finalize();
		
		if (success) 
			success = m_sheet->build();
		else
			global_vars.err << MSG_ERROR << "Internal error: Sheet::finalize() returned with error\n";
	}
	catch( std::string exc_str) 
	{
		global_vars.err << MSG_ERROR << "Something went wrong in executeSheet. Msg: " << exc_str << "\n";
		success = false;
	}
	catch(...) 
	{
		global_vars.err << MSG_ERROR << "Something went wrong in executeSheet\n";
		success = false;
	}
	return success;
}


void RawComponent::deleteSheet()
{
	if ( m_sheet) delete m_sheet;
	m_sheet = 0;
}


// ====================================================
// This is the main component method for Interpereters and Plugins.
// May also be used in case of invokeable Add-Ons
// this is the obsolete component interface
// this present implementation either tries to call InvokeEx, or returns an error;
STDMETHODIMP RawComponent::Invoke(IMgaProject* gme, IMgaFCOs *models, long param) {
#ifdef SUPPORT_OLD_INVOKE
	CComPtr<IMgaFCO> focus;
	CComVariant parval = param;
	return InvokeEx(gme, focus, selected, parvar);
#else
	if(interactive) {
		AfxMessageBox("This component does not support the obsolete invoke mechanism");
	}
	return E_MGA_NOT_SUPPORTED;
#endif
}


// This is the main component method for interpereters and plugins. 
// May als be used in case of invokeable addons
STDMETHODIMP RawComponent::InvokeEx( IMgaProject *project,  IMgaFCO *currentobj, IMgaFCOs *selectedobjs,  long param)
{
	COMTRY {
	  if(interactive) {
		CComBSTR projname;
		CComBSTR focusname = "<nothing>";
		CComPtr<IMgaTerritory> terr;
		COMTHROW(project->CreateTerritory(NULL, &terr));
		COMTHROW(project->BeginTransaction(terr));
		try 
		{
			invokeEx( project, currentobj, selectedobjs, param);
			finalize();
			COMTHROW(project->CommitTransaction());
		}
		catch(...) { 
			finalize();
			project->AbortTransaction(); 
			throw;
		}
		
	  } 
	} COMCATCH(;);
}

void RawComponent::invokeEx( IMgaProject *project,  IMgaFCO *currentobj, IMgaFCOs *selectedobjs,  long param)
{
	// ======================
	// Insert application specific code here
	global_vars.silent_mode = (param == GME_SILENT_MODE);
	//global_vars.silent_mode = true;
	initMembers( project);

	std::string temp;
	if ( !Sheet::makeValidParadigmName( m_projectName, temp))
	{
		if( !global_vars.silent_mode)
		{
			m_console.sendMsg("[MetaInterpreter] Invalid or empty paradigm name (Rootfolder name). Please remove spaces and the special characters, except '.' and '_'. Using: \"" + temp + "\".", MSG_ERROR);
			CString msg = "Invalid or empty paradigm name: \"";
			msg += (m_projectName + "\". Continue using: \"" + temp + "\"?").c_str();
			if( AfxMessageBox( (LPCTSTR)msg, MB_YESNO | MB_ICONWARNING) != IDYES)
			{
				m_console.sendMsg("[MetaInterpreter] Intepretation stopped by the user.", MSG_NORMAL);
				return;
			}
		}
	}
	if ( Dumper::selectOutputFiles( project, m_projectName, m_dir) > 1)
	{
		if( !global_vars.silent_mode) m_console.sendMsg("[MetaInterpreter] Output file name selection cancelled by the user or other file operation failed.", MSG_NORMAL);
		return;
	}

	Dumper::selectOptions( project);

	global_vars.err.m_proj = project;

	CWaitCursor wait;

	CTime theTime = CTime::GetCurrentTime();
	CString s = theTime.Format("%#c");
	s = "METAINTERPRETER LOG STARTED " + s;

	// don't create file output anymore
	//global_vars.err.open( global_vars.err_file_name.c_str(), std::ios_base::out);

	global_vars.err << MSG_NORMAL << std::string( s.GetLength(), '=') << "\n";
	global_vars.err << (LPCTSTR) s << "\n";
	global_vars.err << MSG_NORMAL << std::string( s.GetLength(), '=') << "\n";

	try {
		
		scanProject( project);

		CHECK();

		m_entities.sort();
		m_equivRelations.sort();			// tries to ensure the same order of handling the equivalences

		selectFromSameAspectsFolders();		// selects names for the equivalent objects (designates the nameresp pointers)
		proxyFinder();						// replaces proxies with the real objects
		equivalenceFinder();				// merges the equivalent objects (the relations they are part of)
		removeProxiesAndEquiv();
		bool cont = nameSelector();

		while ( !checkForProxies()) { }
		
		bool do_at_all = true;
		if ( do_at_all)
		{
			if ( Sheet::checkInstance())
				global_vars.err << MSG_ERROR << "Internal error: merged paradigm sheet already exists\n";

			global_vars.dmp.open( global_vars.xmp_file_name.c_str(), std::ios_base::out);

			createSheet();

			bool success = false;
			try 
			{

				success = populateSheet( project );
				if ( success)
					success = executeSheet();
				else
					global_vars.err << MSG_ERROR << "Internal error: PopulateSheet returned with error\n";

			}
			catch( std::string exc_str)
			{
				global_vars.err << MSG_ERROR << "Internal error: Exception caught during populate/execute. Msg: " << exc_str << "\n";
			}
			catch(...)
			{
				global_vars.err << MSG_ERROR << "Internal error: Exception caught during populate/execute.\n";
			}

			if ( !Sheet::checkInstance())
				global_vars.err << MSG_ERROR << "Internal error: Merged Sheet object doesn't exist\n";
			
			deleteSheet();
			
			global_vars.dmp.close();
			if (success)
				Dumper::registerIt( global_vars.xmp_file_name);
		}
		else
			global_vars.err << MSG_ERROR << "Exited before populating the Merged Paradigm Sheet. Proxy or other problem may exist.\n";
		
	}	catch (...)	
	{
		global_vars.err << MSG_ERROR << "Internal error: Exception thrown by Component.\n";
		deleteSheet();
	}

	if ( Sheet::checkInstance())
		global_vars.err << MSG_ERROR << "Internal error: Merged Paradigm Sheet object still exists\n";

	global_vars.err << MSG_NORMAL << "\nEND OF LOG\n";
	// don't create file output anymore
	//global_vars.err.flushit();
	//global_vars.err.close();
	global_vars.err.m_proj = CComPtr<IMgaProject>( 0);

	long r = 0; // remove all items from safe
	if( m_safe) COMTHROW( m_safe->get_Count( &r));
	while( r > 0) COMTHROW( m_safe->Remove( r--));
}

// GME currently does not use this function
// you only need to implement it if other invokation mechanisms are used
STDMETHODIMP RawComponent::ObjectsInvokeEx( IMgaProject *project,  IMgaObject *currentobj,  IMgaObjects *selectedobjs,  long param) {
	if(interactive) {
		AfxMessageBox("Tho ObjectsInvoke method is not implemented");
	}
	return E_MGA_NOT_SUPPORTED;
}


// implement application specific parameter-mechanism in these functions:
STDMETHODIMP RawComponent::get_ComponentParameter(BSTR name, VARIANT *pVal) {
	return S_OK;
}

STDMETHODIMP RawComponent::put_ComponentParameter(BSTR name, VARIANT newVal) {
	return S_OK;
}


#ifdef GME_ADDON

// these two functions are the main 
STDMETHODIMP RawComponent::GlobalEvent(globalevent_enum event) { 
	if(event == GLOBALEVENT_UNDO) {
		AfxMessageBox("UNDO!!");
	}
	return S_OK; 
}

STDMETHODIMP RawComponent::ObjectEvent(IMgaObject * obj, unsigned long eventmask, VARIANT v) {
	if(eventmask & OBJEVENT_CREATED) {
		CComBSTR objID;
		COMTHROW(obj->get_ID(&objID));
		AfxMessageBox( "Object created! ObjID: " + CString(objID)); 
	}		
	return S_OK;
}

#endif
