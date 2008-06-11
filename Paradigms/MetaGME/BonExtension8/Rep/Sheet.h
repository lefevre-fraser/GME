#ifndef SHEET_H
#define SHEET_H

#include "Any.h"
#include "FCO.h"
#include "FolderRep.h"
#include "ModelRep.h"
#include "AtomRep.h"
#include "ConnectionRep.h"
#include "SetRep.h"
#include "ReferenceRep.h"
#include "FcoRep.h"
#include "AttributeRep.h"
#include "RootFolder.h"

#include "list"
#include "vector"
#include "strstream"

class Sheet;

class Sheet 
{

protected:
	static Sheet * m_theOnlyInstance;
	Sheet();

public:
	//static Sheet * getInstance() ; to be implented in Derived classes
	static bool checkInstance() { return m_theOnlyInstance != 0; }
	virtual ~Sheet();
	virtual bool build() = 0;
	virtual bool finalize();
	void setProject( CComPtr<IMgaProject> project );
	std::string getValidName() { return m_validProjName; } 

	FcoRep* createFcoRep( IMgaFCO* ptr, IMgaFCO* resp_ptr);
	AtomRep* createAtomRep( IMgaFCO* ptr, IMgaFCO* resp_ptr);
	ModelRep* createModelRep( IMgaFCO* ptr, IMgaFCO* resp_ptr);
	ConnectionRep* createConnectionRep( IMgaFCO* ptr, IMgaFCO* resp_ptr);
	SetRep* createSetRep( IMgaFCO* ptr, IMgaFCO* resp_ptr);
	ReferenceRep* createReferenceRep( IMgaFCO* ptr, IMgaFCO* resp_ptr);
	FolderRep* createFolderRep( IMgaFCO* ptr, IMgaFCO* resp_ptr);

	AttributeRep* createBoolAttributeRep( IMgaFCO* ptr);
	AttributeRep* createEnumAttributeRep( IMgaFCO* ptr);
	AttributeRep* createFieldAttributeRep( IMgaFCO* ptr);

	FCO* findFCO( IMgaFCO* ptr);
	ReferenceRep* findRef( IMgaFCO* ptr);
	Any* findAny( IMgaFCO* ptr);

	std::string getNamespace() { return m_projNamespace; }

	CComPtr<IMgaFolder> m_BON_Project_Root_Folder2;

	std::set<CComPtr<IMgaModel> > m_setOfParadigmSheets2;

protected:
	std::vector< FCO *> Sheet::sortBasedOnLevels();
	int m_numberOfCliques[FCO::INHERITANCE_TYPE::NUMBER_OF_INHERITANCES]; // stores the number of cliques from inheritance point of view
	                                                                      // this may be different from INTERFACE and IMPLEMENTATION point of view
	typedef std::vector<FCO*>::iterator FCO_Iterator;
	typedef std::vector<Any*>::iterator Any_Iterator;

	typedef std::vector<FcoRep*>::iterator FcoRep_Iterator;
	typedef std::vector<AtomRep*>::iterator AtomRep_Iterator;
	
	typedef std::vector<ModelRep*>::iterator ModelRep_Iterator;
	
	typedef std::vector<ConnectionRep*>::iterator ConnectionRep_Iterator;
	typedef std::vector<ReferenceRep*>::iterator ReferenceRep_Iterator;
	typedef std::vector<SetRep*>::iterator SetRep_Iterator;
	typedef std::vector<FolderRep*>::iterator FolderRep_Iterator;
	typedef std::vector<AttributeRep*>::iterator AttributeRep_Iterator;

	void addAny( Any * ptr);
	void addFcoRep( FcoRep * ptr);
	void addAtomRep( AtomRep * ptr);
	void addModelRep( ModelRep * ptr);
	void addConnectionRep( ConnectionRep * ptr);
	void addReferenceRep( ReferenceRep * ptr);
	void addSetRep( SetRep * ptr);
	void addFolderRep( FolderRep * ptr);
	void addAttributeRep( AttributeRep* ptr);

	std::vector<FcoRep*> m_fcoRepList;
	std::vector<AtomRep*> m_atomList;
	std::vector<ModelRep*> m_modelList;
	std::vector<ConnectionRep*> m_connList;
	std::vector<ReferenceRep*> m_refList;
	std::vector<SetRep*> m_setList;

	std::vector<FolderRep*> m_folderList;

	std::vector<AttributeRep*> m_attributeList;

	std::string m_projName;
	std::string m_validProjName;
	std::string m_projNamespace;
	std::string m_validProjNamespace;
	RootFolder m_rootFolder;

private:
	void init();
	bool isInRootFolder( Any * elem);
	void initRoleNames();
	bool doInheritance( FCO::INHERITANCE_TYPE inh_type);
	bool multipleInheritance();
	
	// these methods deal with the order the fcos should
	// be dumped into the header file
	void order( FCO::INHERITANCE_TYPE type, std::vector<FCO*>& res);
	bool check( FCO::INHERITANCE_TYPE type, std::vector<FCO*>& res);

	typedef std::vector< unsigned int > UI_LIST;
	typedef std::vector< unsigned int > CLIQUE_VECTOR;
	typedef std::vector< FCO *> NODE_VECTOR;
	void gatherNodes( std::vector< FCO *>& nodes);
	void assignCliqueId( CLIQUE_VECTOR & clique, const NODE_VECTOR & nodes);
	bool edge( unsigned int i, unsigned int j, const NODE_VECTOR & nodes, FCO::INHERITANCE_TYPE inh_type);
	void vectorCopy( UI_LIST & target, const UI_LIST & source, UI_LIST & duplicates);
	void getChildren( unsigned int base, const NODE_VECTOR & nodes, UI_LIST & children, FCO::INHERITANCE_TYPE inh_type);
	unsigned int howManyCliques( CLIQUE_VECTOR & clique_id);
	void replaceCliqueId( CLIQUE_VECTOR & clique_id, unsigned int id1, unsigned int id2);
};
#endif //SHEET_H
