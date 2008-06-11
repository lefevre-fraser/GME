// SearchAlg.h: interface for the CSearch class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_SEARCHALG_H
#define AFX_SEARCHALG_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ComHelp.h"
#include "Input.h"
#include <afxcmn.h>
//#include "GMESearchDialog.h"

/**
* \brief The Search Class
*
* Performs the search algorithm. The input is validated and the output list empty when
* this class is instantiated. Any match found will be added to the tail of the output list.
*/
class CSearch  
{
public:
	CSearch(CInput inp);
//	CSearch(CInput inp, CGMESearchDialog *Searcher);
	virtual ~CSearch();
/**
* \brief Function to execute the correct input-based search.
*
* \param root : The project root folder, for a global search.
* \param scope : The collection of containers (if any) where local search should be performed 
* \param selected : The selected object, for a reference search.
* \param disp : An empty list that will be used to store the results.
* \param Progress : A Progress Control to keep the user aware that the search is progressing.
* \return Returns void, however, the actions of Search will fill the parameter disp with all matches found during the search.
*
*/
	void Search(IMgaFolder *root, IMgaObjects* scope, IMgaFCO *selected, CComPtr<IMgaFCOs> disp, CProgressCtrl *Progress);

	
private:

/**
* \brief Recursively search the current Folder and below	
*
* \param root : The current Folder we are on
*/
	void SearchFolderHierarchy(IMgaFolder *root);
/**
* \brief Recursively search the current Model and below	
*
* \param root : The current Model we are on
*/
	void SearchModelHierarchy(IMgaModel *root);
/**
* \brief Search through all the references to objects in the list.
*
* \param referenced : Object whose references will be searched
*/
	void SearchReferences(IMgaFCO *referenced);

/**
* \brief Check all the atoms for search matches.
*
* \param allObjects : list of objects currently being searched.
*/
	void CheckAllAtoms(IMgaFCOs *allObjects);
/**
* \brief Check all the references for search matches.
*
* \param allObjects : list of objects currently being searched.
*/
	void CheckAllReferences(IMgaFCOs *allObjects);
/**
* \brief Check all the sets for search matches.
*
* \param rootObjects : Model from which child objects will be searched.
*/
	void CheckAllSets(IMgaFCOs *allObjects);
/**
* \brief Check all the models for search matches.
*
* \param allObjects : list of objects currently being searched.
*/
	void CheckAllModels(IMgaFCOs *allObjects);

/**
* \brief Check this model against the search criteria.
*/
	void CheckModel(IMgaModel *Model);
/**
* \brief Check this atom against the search criteria.
*/
	void CheckAtom(IMgaAtom *Atom);
/**
* \brief Check this reference against the search criteria.
*/
	void CheckReference(IMgaReference *Reference);
/**
* \brief Check this set against the search criteria.
*/
	void CheckSet(IMgaSet *Set);

/**
* \brief Check the object's attributes against the search criteria.
*/
	bool CheckAttributes(IMgaFCO *obj);


	/// Where to store the results
	CComPtr<IMgaFCOs> results;
	// Progress bar
	CProgressCtrl *m_pgsSearch;
	
	/// The input criteria.
	CInput filter;

//	CGMESearchDialog *SearchDialog;
};

#endif
