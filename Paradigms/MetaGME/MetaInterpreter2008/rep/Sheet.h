#ifndef SHEET_H
#define SHEET_H

#include "Any.h"
#include "PartRep.h"
#include "FCO.h"
#include "ConstraintFuncRep.h"
#include "ConstraintRep.h"
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
	void setProject( IMgaProject* project );

	FcoRep* createFcoRep( IMgaFCO* ptr, IMgaFCO* resp_ptr);
	AtomRep* createAtomRep( IMgaFCO* ptr, IMgaFCO* resp_ptr);
	ModelRep* createModelRep( IMgaFCO* ptr, IMgaFCO* resp_ptr);
	ConnectionRep* createConnectionRep( IMgaFCO* ptr, IMgaFCO* resp_ptr);
	SetRep* createSetRep( IMgaFCO* ptr, IMgaFCO* resp_ptr);
	ReferenceRep* createReferenceRep( IMgaFCO* ptr, IMgaFCO* resp_ptr);
	FolderRep* createFolderRep( IMgaFCO* ptr, IMgaFCO* resp_ptr);

	AspectRep* createAspectRep( IMgaFCO* ptr, IMgaFCO* resp_ptr);
	ConstraintRep* createConstraintRep( IMgaFCO* ptr);
	ConstraintFuncRep* createConstraintFuncRep( IMgaFCO* ptr);
	AttributeRep* createBoolAttributeRep( IMgaFCO* ptr);
	AttributeRep* createEnumAttributeRep( IMgaFCO* ptr);
	AttributeRep* createFieldAttributeRep( IMgaFCO* ptr);

	FCO* findFCO( IMgaFCO* ptr);
	ReferenceRep* findRef( IMgaFCO* ptr);
	Any* findAny( IMgaFCO* ptr);

	std::string getNamespace() { return m_projNamespace; }

	static CComPtr<IMgaFolder> m_BON_Project_Root_Folder;
	static bool makeValidParadigmName( const std::string& pInName, std::string& result);
	static bool makeValidNamespace( const std::string& pInName, std::string& result);

protected:
	typedef std::vector<FCO*>::iterator FCO_Iterator;
	typedef std::vector<Any*>::iterator Any_Iterator;

	typedef std::vector<FcoRep*>::iterator FcoRep_Iterator;
	typedef std::vector<AtomRep*>::iterator AtomRep_Iterator;
	
	typedef std::vector<ModelRep*>::iterator ModelRep_Iterator;
	
	typedef std::vector<ConnectionRep*>::iterator ConnectionRep_Iterator;
	typedef std::vector<ReferenceRep*>::iterator ReferenceRep_Iterator;
	typedef std::vector<SetRep*>::iterator SetRep_Iterator;
	typedef std::vector<FolderRep*>::iterator FolderRep_Iterator;
	typedef std::vector<AspectRep*>::iterator AspectRep_Iterator;
	typedef std::vector<ConstraintRep*>::iterator ConstraintRep_Iterator;
	typedef std::vector<ConstraintFuncRep*>::iterator ConstraintFuncRep_Iterator;
	typedef std::vector<AttributeRep*>::iterator AttributeRep_Iterator;

	typedef std::vector<FCO*>::const_iterator FCO_ConstIterator;
	typedef std::vector<FolderRep*>::const_iterator FolderRep_ConstIterator;

	void addAny( Any * ptr);
	void addFcoRep( FcoRep * ptr);
	void addAtomRep( AtomRep * ptr);
	void addModelRep( ModelRep * ptr);
	void addConnectionRep( ConnectionRep * ptr);
	void addReferenceRep( ReferenceRep * ptr);
	void addSetRep( SetRep * ptr);
	void addFolderRep( FolderRep * ptr);
	void addAspectRep( AspectRep * ptr);
	void addConstraintFuncRep( ConstraintFuncRep *ptr);
	void addConstraintRep( ConstraintRep *ptr);
	void addAttributeRep( AttributeRep* ptr);

	std::vector<FcoRep*> m_fcoRepList;
	std::vector<AtomRep*> m_atomList;
	std::vector<ModelRep*> m_modelList;
	std::vector<ConnectionRep*> m_connList;
	std::vector<ReferenceRep*> m_refList;
	std::vector<SetRep*> m_setList;

	std::vector<FolderRep*> m_folderList;

	std::vector<AspectRep*> m_aspectList;
	std::vector<ConstraintRep*> m_constraintList;
	std::vector<ConstraintFuncRep*> m_constraintFuncList;
	std::vector<AttributeRep*> m_attributeList;

	std::string m_projName;
	std::string m_projVersion;
	std::string m_projGUID;
	std::string m_projCreated;
	std::string m_projModified;
	std::string m_projAuthor;
	std::string m_projComment;
	std::string m_projNamespace;

	RootFolder m_rootFolder;

private:
	void init();
	bool isInRootFolder( Any * elem);
	void initRoleNames();
	bool doInheritance( FCO::INHERITANCE_TYPE inh_type);

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
