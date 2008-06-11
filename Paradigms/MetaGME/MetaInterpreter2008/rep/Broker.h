#ifndef BROKER_H
#define BROKER_H

#include "MyUtil.h"
#include "Common.h"
#include <list>
#include <string>


class Broker
{
public:
	static const int INVALID_METAREF;
	static const int INITIAL_METAREF;
	static const std::string ROOTFOLDER_METAREF_STR;

	class MetaRefNode {
	public:
		MetaRefNode( IMgaObject* o = 0, IMgaFolder* f = 0, const std::string &p = std::string(""), int m = INVALID_METAREF) : obj(o), folder(f), path(p), metaref(m) {};
		CComPtr<IMgaObject> obj;
		CComPtr<IMgaFolder> folder;
		std::string	path;
		int metaref;
	};

	static void reset();
	static void init();
	static int getNextConstraintId();
	static int getNextMetaRefId();

	static std::string getRegistryTokenName( IMgaObject* obj);
	static void initFromObj( IMgaObject* obj, IMgaFolder* folder, const std::string& kind);
	static void initFromAspectObj( IMgaObject* obj, const std::string& name, IMgaFolder* folder);
	static void initFromRegistry( IMgaObject* obj, IMgaFolder* folder, IMgaRegNode* regNode);

	static void checkDuplicates();


private:
	typedef std::list<MetaRefNode> MetaRefDB;
	typedef std::list<MetaRefNode>::iterator MetaRefDB_Iterator;
	static MetaRefDB m_metaRefDB;
	static int m_firstFree;

	static int m_constraintId;
	static int m_metaRefId;
};

#endif