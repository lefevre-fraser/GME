#ifndef ANY_H
#define ANY_H

#include "MyUtil.h"
#include "Any.h"
#include <string>
#include <vector>
#include <set>
#include "logger.h"

/** This class is the abstract base of all kinds of parts/FCOs that can occur during a modeling process. */
class Any;
class ConstraintRep;

class AnyLexicographicSort
{
public:
  bool operator()( Any * op1, Any * op2) const;
};

class Any 
{
public: // constant strings
	static const std::string NamespaceDelimiter_str;//"::"
	static const std::string InRootFolder_str;//"InRootFolder"
	static const std::string DisplayedName_str;//"DisplayedName"

	static const std::string NameSelectorNode_str;
	static const std::string DisplayedNameSelectorNode_str;
public: // types
	typedef enum
	{
		ATOM,
		MODEL,
		CONN,
		SET,
		REF,
		FCO_REP, // abstract term only
		ASPECT,
		FOLDER,
		CONSTRAINT,
		CONSTRAINTFUNC,
		ATTRIBUTE
	} KIND_TYPE;

	const static std::string KIND_TYPE_STR[];/* =
		{
		"ATOM",	// defined in Any.cpp If the order changes update there please
		"MODEL",
		"CONN",
		"SET",
		"REF",
		"FCO",
		"ASPECT",
		"FOLDER",
		"CONSTRAINT",
		"CONSTRAINFUNC",
		"ATTRIBUTE"
		};*/

	typedef std::vector< ConstraintRep* > ConstraintRepPtrList;
	typedef std::vector< ConstraintRep* >::const_iterator ConstraintRepPtrList_ConstIterator;

	typedef std::set< CComPtr<IMgaFCO> > EquivSet;
	typedef std::set< CComPtr<IMgaFCO> >::const_iterator EquivSet_ConstIterator;

public:
	Any( IMgaFCO* ptr);
	virtual ~Any();

public:	
	virtual void initAttributes();
	void initNamespace();
	void resetNamespace();
	std::string getNamespace() const;

	virtual KIND_TYPE getMyKind() const = 0;
	std::string getMyKindStr() const;
	virtual std::string doDump() = 0;
	virtual std::string getName() const;
	virtual std::string getDispName() const;
	virtual std::string dumpDispName() const;

	std::string dumpConstraints();

	IMgaFCO* getPtr() const { return m_ptr; }

	bool isInRootFolder();

	IMgaFolder* getParentFolder() const { return m_parentFolder; }
	void setParentFolder( IMgaFolder* writableRegFolder, IMgaFolder* nmspHolderFolder) { m_parentFolder = writableRegFolder; m_nmspRootFolder = nmspHolderFolder;}
	void setEquivPeers( EquivSet& ps) { m_equivs = ps; }
	void setDisplayedName( const std::string& dispnm) { m_userSelectedDisplayName = dispnm; }

	virtual std::string getMyPrefix() const;
	virtual CComPtr<IMgaRegNode> getMyRegistry() const;
	CComPtr<IMgaRegNode> getMyRegistryOld() const;

	static std::string getMyPrefix( IMgaFCO* fco, IMgaFolder* f);
	static CComPtr<IMgaRegNode> getMyRegistry( IMgaFCO* fco, IMgaFolder* f);

	bool isFCO() const;
	std::string askMetaRef(const std::string & tok = "") const;

	// constraints
	void addInitialConstraintRep( ConstraintRep * );
	const ConstraintRepPtrList& getInitialConstraintRepPtrList() const;
	void addFinalConstraint( ConstraintRep * constraint);
	void addFinalConstraintList( const ConstraintRepPtrList & list);

protected:
	// pointer of the BON object
	CComPtr<IMgaFCO> m_ptr;

	// pointer of the parent folder
	// this must be writable because
	// the registry write operations
	// work through this ptr
	CComPtr<IMgaFolder> m_parentFolder;

	// namespace info taken from this folder
	// typically same with m_parentFolder
	CComPtr<IMgaFolder> m_nmspRootFolder;

	// equivalent peers
	EquivSet m_equivs;
	bool	m_isInRootFolder;

	// displayed name (if name selection dialog used) 
	std::string m_userSelectedDisplayName;

	// initial and final constraints
	ConstraintRepPtrList m_initialConstraintList;
	ConstraintRepPtrList m_finalConstraintList;

	// part of this namespace:
	std::string m_namespace;

private: // forbiding copy
	Any( const Any&);
	const Any& operator=( const Any&);
};

#endif //ANY_H
