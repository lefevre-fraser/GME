#ifndef RAWCOMPONENT_H
#define RAWCOMPONENT_H


// Declaration of the main RAW COM component interface class


#ifdef BUILDER_OBJECT_NETWORK
#error   This file should only be included in the RAW COM configurations
#endif

#include <string>
#include <list>
#include <map>
#include <algorithm>

#include "entity.h"
#include "relation.h"
#include "Console.h"

#include "FCO.h"
#include "Sheet.h"


class RawComponent {
////////////////////
// Insert your application specific member and method definitions here
public:
	RawComponent() { ; }
private:
	void finalize();
	void invokeEx( IMgaProject *project,  IMgaFCO *currentobj,  IMgaFCOs *selectedobjs,  long param);
	Console m_console;
private:

	typedef std::list< Entity > Entities;
	typedef Entities::iterator Entity_Iterator;
	typedef Entities::const_iterator Entity_Const_Iterator;

	typedef std::list< Relation > Relations;
	typedef Relations::iterator Relation_Iterator;
	typedef Relations::const_iterator Relation_Const_Iterator;

	typedef CComPtr<IMgaFCO> ObjPointer;
	//typedef IMgaFCO* ObjPointer;
	typedef std::map< ObjPointer, ObjPointer> RealMap;
	typedef std::map< ObjPointer, ObjPointer>::iterator RealMap_Iterator;
	typedef std::map< ObjPointer, std::set < ObjPointer > > EquivBag;
	typedef std::map< ObjPointer, std::set < ObjPointer > >::iterator EquivBag_Iterator;

	CComPtr<IMgaObjects>      m_safe;
private: // members
	std::string m_projectName;
	std::string m_dir; // stores the directory names the interpreter has been invoked with

	Entities m_entities;
	//Entities m_toBeDeletedEntities;
	Relations m_relations;
	Relations m_equivRelations;
	RealMap m_realObj;

	EquivBag m_equivBag;

	std::set<CComPtr<IMgaModel> > m_setOfParShs;

private: // methods
	void initMembers( IMgaProject* project);
public:
	void finiMembers();

private:
	void scanProject( IMgaProject* project);
	void scanModels( IMgaModel* model, IMgaFolder* parent);
	void scanSubModels( IMgaModel* model);
	void scanSubFolders( IMgaFolders* folders, CComPtr<IMgaFolders>& result);
	void entityBuilder( IMgaModel* model, IMgaFolder* parent);

	void selectFromSameAspectsFolders();
	void storeEntity( const Entity& p);
	void storeRelation( Relation& p);
	void storeEquivRelation( Relation& p);
	void proxyFinder();
	void equivalenceFinder();
	void removeProxiesAndEquiv();
	bool nameSelector();
	int isProxy( const ObjPointer& ptr);
	void operandSearchAndReplace( const std::vector<ObjPointer>& proxy_obj, const ObjPointer& real_obj);
	void operandSearchAndReplace( const ObjPointer& proxy_obj, const ObjPointer& real_obj);
	void insertIntoEquivBag( const ObjPointer& obj1, const ObjPointer& obj2);
	void markEquivEntities();
	Entity entitySearch( const ObjPointer& p_ptr);
	bool checkForProxies();

	void CHECK();

private:
	Sheet * m_sheet;
	void createSheet(); // TODO: modify this method to create your specific object
	bool populateSheet( IMgaProject* project );
	bool executeSheet();
	void deleteSheet();

	void inheritancesManager( Relation & );
	void refersToManager( Relation & );
	void associationClassManager( Relation & );
	void setMemberManager( Relation & );
	void containmentManager( Relation & );
	void folderContainmentManager( Relation & );
	void hasAspectManager( Relation & );
	void aspectMemberManager( Relation & );
	void hasConstraintManager( Relation & );
	void hasAttributeManager( Relation & );

	
// Try not to modify the code below this line
////////////////////
public:	
#ifdef GME_ADDON
	CComPtr<IMgaProject> project;  // this is set before Initialize() is called
	CComPtr<IMgaAddOn> addon;      // this is set before Initialize() is called
#endif
	bool interactive;
	
	STDMETHODIMP Initialize(struct IMgaProject *);
	STDMETHODIMP Invoke(IMgaProject* gme, IMgaFCOs *models, long param);
	STDMETHODIMP InvokeEx( IMgaProject *project,  IMgaFCO *currentobj,  IMgaFCOs *selectedobjs,  long param);
	STDMETHODIMP ObjectsInvokeEx( IMgaProject *project,  IMgaObject *currentobj,  IMgaObjects *selectedobjs,  long param);
	STDMETHODIMP get_ComponentParameter(BSTR name, VARIANT *pVal);
	STDMETHODIMP put_ComponentParameter(BSTR name, VARIANT newVal);

#ifdef GME_ADDON
	STDMETHODIMP GlobalEvent(globalevent_enum event);
	STDMETHODIMP ObjectEvent(IMgaObject * obj, unsigned long eventmask, VARIANT v);
#endif
};


#endif //RAWCOMPONENT_H