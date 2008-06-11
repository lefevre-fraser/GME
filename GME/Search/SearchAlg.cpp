// SearchAlg.cpp: implementation of the CSearch class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "ComHelp.h"
//#include "GMECOM.h"
//#include "ComponentConfig.h"
//#include "RawComponent.h"
#include "Input.h"
#include "SearchAlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSearch::CSearch(CInput inp)
{
	filter = inp;
//	SearchDialog = NULL;
}


CSearch::~CSearch()
{

}

// the main entry point for a search
void CSearch::Search(IMgaFolder *root, IMgaObjects* scopeColl, IMgaFCO *selected, CComPtr<IMgaFCOs> disp, CProgressCtrl *Progress)
{
	results = disp;
	m_pgsSearch = Progress;
	CComPtr<IMgaFolder> pRoot = root;


	if(filter.getReferences && filter.getSplSearch && (selected != NULL))
	{
		SearchReferences(selected);
	}
	else if( filter.doScopedSearch && scopeColl)
	{
		CComPtr<IMgaFCOs> non_container_coll;                  // will store the Atoms, Refs and Sets
		non_container_coll.CoCreateInstance( L"Mga.MgaFCOs");  // which are not Fs and Ms
		long nExtra = 0;                                       // how many are there in the above collection

		MGACOLL_ITERATE(IMgaObject, scopeColl)
		{
			CComPtr<IMgaObject> iter;
			
			objtype_enum type;
			COMTHROW( MGACOLL_ITER->get_ObjType( &type));

			switch( type) {
				case OBJTYPE_FOLDER:   SearchFolderHierarchy( CComQIPtr<IMgaFolder>( MGACOLL_ITER));break;
				case OBJTYPE_MODEL:    SearchModelHierarchy( CComQIPtr<IMgaModel>( MGACOLL_ITER));break;
				case OBJTYPE_SET:
				case OBJTYPE_ATOM:
				case OBJTYPE_REFERENCE: 
					CComQIPtr<IMgaFCO> an_fco( MGACOLL_ITER);
					if( an_fco && non_container_coll) 
					{
						non_container_coll->Append( an_fco);
						++nExtra;
					}
			} // switch
		} MGACOLL_ITERATE_END;

		if( nExtra && non_container_coll) // if coll is non-zero and has elements inside
		{		
			CheckAllReferences( non_container_coll);  // deals with refs only
			CheckAllAtoms( non_container_coll);       // ... atoms only
			CheckAllSets( non_container_coll);        // ... sets only
		}
		non_container_coll.Release();
	}
	else
	{
		SearchFolderHierarchy(pRoot);	
	}
  
	//return results;
}

// get all the atoms that have a matching role name, calling CheckAtom on each
void CSearch::CheckAllAtoms(IMgaFCOs *allObjects)
{

	MGACOLL_ITERATE(IMgaFCO, allObjects)
			{
				CString partName;
				CBstr bstr;
				CComPtr<IMgaMetaRole> rmeta;
				COMTHROW( MGACOLL_ITER->get_MetaRole(&rmeta) );
				if(rmeta) 
				{
					COMTHROW( rmeta->get_Name(bstr) );
					partName = bstr;
				} 
				else 
					partName = "";
				objtype_enum rret;
				COMTHROW( MGACOLL_ITER->get_ObjType( &rret) );

				if( filter.getCaseIgnored) // case ignored, make role lowercase
				{
					partName.MakeLower();
				}

				if((rret == OBJTYPE_ATOM)  && (filter.objRole.Match(partName)) )
				{
					CheckAtom((IMgaAtom *)MGACOLL_ITER.p);
				}

				m_pgsSearch->StepIt();	
			} MGACOLL_ITERATE_END;

}

// get all the references that have a matching role name, calling CheckReference on each
void CSearch::CheckAllReferences(IMgaFCOs *allObjects)
{

	MGACOLL_ITERATE(IMgaFCO, allObjects)
			{
				CString partName;
				CBstr bstr;
				CComPtr<IMgaMetaRole> rmeta;
				COMTHROW( MGACOLL_ITER->get_MetaRole(&rmeta) );
				if(rmeta) 
				{
					COMTHROW( rmeta->get_Name(bstr) );
					partName = bstr;
				} 
				else 
					partName = "";
				objtype_enum rret;
				COMTHROW( MGACOLL_ITER->get_ObjType( &rret) );

				if( filter.getCaseIgnored) // case ignored, make role lowercase
				{
					partName.MakeLower();
				}

				if((rret == OBJTYPE_REFERENCE)  && (filter.objRole.Match(partName)) )
				{
					CheckReference((IMgaReference *)(MGACOLL_ITER.p));
				}

				m_pgsSearch->StepIt();
			} MGACOLL_ITERATE_END;

}

// get all the sets that have a matching role name, calling CheckSet on each
void CSearch::CheckAllSets(IMgaFCOs *allObjects)
{

	MGACOLL_ITERATE(IMgaFCO, allObjects)
			{
				CString partName;
				CBstr bstr;
				CComPtr<IMgaMetaRole> rmeta;
				COMTHROW( MGACOLL_ITER->get_MetaRole(&rmeta) );
				if(rmeta) 
				{
					COMTHROW( rmeta->get_Name(bstr) );
					partName = bstr;
				} 
				else 
					partName = "";
				objtype_enum rret;
				COMTHROW( MGACOLL_ITER->get_ObjType( &rret) );

				if( filter.getCaseIgnored) // case ignored, make role lowercase
				{
					partName.MakeLower();
				}

				if((rret == OBJTYPE_SET)  && (filter.objRole.Match(partName)) )
				{
					CheckSet((IMgaSet *)(MGACOLL_ITER.p));
				}

				m_pgsSearch->StepIt();
			} MGACOLL_ITERATE_END;	
}

// get all the models that have a matching role name, calling CheckModel on each
void CSearch::CheckAllModels(IMgaFCOs *allObjects)
{


	MGACOLL_ITERATE(IMgaFCO, allObjects)
			{
				CString partName;
				CBstr bstr;
				CComPtr<IMgaMetaRole> rmeta;
				COMTHROW( MGACOLL_ITER->get_MetaRole(&rmeta) );
				if(rmeta) 
				{
					COMTHROW( rmeta->get_Name(bstr) );
					partName = bstr;
				} 
				else 
					partName = "";
				objtype_enum rret;
				COMTHROW( MGACOLL_ITER->get_ObjType( &rret) );

				if( filter.getCaseIgnored) // case ignored, make role lowercase
				{
					partName.MakeLower();
				}

				if((rret == OBJTYPE_MODEL)  && (filter.objRole.Match(partName)) )
				{
					CheckModel((IMgaModel *)(MGACOLL_ITER.p));
				}
				m_pgsSearch->StepIt();

			} MGACOLL_ITERATE_END;

}

//searches the folder hierarchy, first searches all the child models and modelhierarchies of the child models
//then does the same with each child folder, then searches the folderhiearchy of each child folder's child folders
//for a Breadth First Search (not quite perfectly BFS)
void CSearch::SearchFolderHierarchy(IMgaFolder *root)
{
	// Search in Root Models & Below
	CComPtrList<IMgaModel> *rootmodlist = new CComPtrList<IMgaModel>; //needed to use new or the addtail below would fail	
	CComPtr<IMgaFCOs> children;
	COMTHROW( root->get_ChildFCOs(&children));
	MGACOLL_ITERATE(IMgaFCO, children) {
		CComPtr<IMgaModel> mm;
		MGACOLL_ITER.QueryInterface(&mm);
		if(mm != NULL) 
		{
			rootmodlist->AddTail( mm );
		}
	} MGACOLL_ITERATE_END;

	if (filter.getModels) 
	{
		CheckAllModels(children);

	}
	
	if (filter.getAtoms)
	{
		CheckAllAtoms(children);
		
	}

	if (filter.getReferences)
	{
		
		CheckAllReferences(children);

	}

	if (filter.getSets)
	{
		CheckAllSets(children);
	} 

	POSITION rmpos = rootmodlist->GetHeadPosition();
	while(rmpos)
	{
		CComPtr<IMgaModel> rootmodel = rootmodlist->GetNext(rmpos);
		SearchModelHierarchy(rootmodel);
	}

	delete rootmodlist; //no longer needed, (used new above)
	
	// Search in Folders & Below
	CComPtr<IMgaFolders> flist;
	COMTHROW( root->get_ChildFolders(&flist));

	MGACOLL_ITERATE(IMgaFolder, flist)
	{
		// Search in Folder-Models & Below

		
		//uncomment next line, and comment out rest of function for more dfs approach
//		SearchFolderHierarchy(MGACOLL_ITER);

		CComPtrList<IMgaModel> *mlist = new CComPtrList<IMgaModel>;	//needed to use new or the addtail below would fail
		CComPtr<IMgaFCOs> subchildren;
		COMTHROW( MGACOLL_ITER->get_ChildFCOs(&subchildren));
		MGACOLL_ITERATE(IMgaFCO, subchildren) {
			CComPtr<IMgaModel> mod;
			MGACOLL_ITER.QueryInterface(&mod);
			if(mod != NULL) 
			{
				mlist->AddTail( mod );
			}
		} MGACOLL_ITERATE_END;
	
		if (filter.getModels) 
		{
			CheckAllModels(subchildren);
		}

		if (filter.getAtoms)
		{
			CheckAllAtoms(subchildren);
		
		}

		if (filter.getReferences)
		{
		
			CheckAllReferences(subchildren);

		}

		if (filter.getSets)
		{
			CheckAllSets(subchildren);
		} 

	

		POSITION mpos = mlist->GetHeadPosition();
		while(mpos)
		{
			CComPtr<IMgaModel> submodel = mlist->GetNext(mpos);
			SearchModelHierarchy(submodel);
		}

		delete mlist; //no longer needed, (used new above)

		// Search in SubFolders & Below
		CComPtr<IMgaFolders> sflist;
		COMTHROW( MGACOLL_ITER->get_ChildFolders(&sflist));
		MGACOLL_ITERATE(IMgaFolder, sflist)
		{
			SearchFolderHierarchy(MGACOLL_ITER);
		} MGACOLL_ITERATE_END; 

	} MGACOLL_ITERATE_END;
}


//checks all the children of the input model, then searches the model hierarchy of all the child models
void CSearch::SearchModelHierarchy(IMgaModel *root)
{
	if(root != NULL)
	{
		CComPtr<IMgaFCOs> modelChildren;
		COMTHROW(root->get_ChildFCOs(&modelChildren));

		if (filter.getAtoms)
		{
			CheckAllAtoms(modelChildren);
		
		}

		if (filter.getReferences)
		{
		
			CheckAllReferences(modelChildren);

		}

		if (filter.getSets)
		{
			CheckAllSets(modelChildren);
		} 
	
		if (filter.getModels)
		{
			CheckAllModels(modelChildren);
		}

		CComPtrList<IMgaModel> *submodellist = new CComPtrList<IMgaModel>;	
		CComPtr<IMgaFCOs> psa;
		COMTHROW( root->get_ChildFCOs(&psa));
		MGACOLL_ITERATE(IMgaFCO, psa) {
			CComPtr<IMgaModel> mm;
			MGACOLL_ITER.QueryInterface(&mm);
			if(mm != NULL) 
			{
				submodellist->AddTail( mm );
			}
		} MGACOLL_ITERATE_END;

		POSITION smpos = submodellist->GetHeadPosition();

		while(smpos)
		{
			CComPtr<IMgaModel> submodel = submodellist->GetNext(smpos);

			SearchModelHierarchy(submodel);
		}
		delete submodellist; //no longer needed (used new above)
	}
}

//checks the name, kindname and attributes, adding all matches to the results
void CSearch::CheckAtom(IMgaAtom *Atom)
{

		CComPtr<IMgaAtom> atom = Atom;

		bool found = false;
		//get the name
		CBstr bstrName;
		COMTHROW(atom->get_Name(bstrName));
		CString name = bstrName;
		//get the KindName
		CBstr bstrKindName;
		CComPtr<IMgaMetaFCO> cmeta;
		COMTHROW( atom->get_Meta(&cmeta) );
		COMTHROW( cmeta->get_Name(bstrKindName) );
		CString kindName = bstrKindName;

		if( filter.getCaseIgnored) // case ignored, make values lowercase
		{
			name.MakeLower();
			kindName.MakeLower();
		}

		if( (filter.objName.Match(name)) && (filter.objKind.Match(kindName))  )		
		{
			if(!filter.objattribName.IsEmpty())
			{
				found = CheckAttributes(atom);
			}
			else
				found = true;
				
			if(found)
			{
				COMTHROW(results->Append(atom));
			}
		}

}

//checks the name, kindname and attributes, adding all matches to the results
//also checks for the special Null reference search
void CSearch::CheckReference(IMgaReference *Reference)
{

		CComPtr<IMgaReference> ref = Reference;

		bool found = false;
		//get the name
		CBstr bstrName;
		COMTHROW(ref->get_Name(bstrName));
		CString name = bstrName;
		//get the KindName
		CBstr bstrKindName;
		CComPtr<IMgaMetaFCO> cmeta;
		COMTHROW( ref->get_Meta(&cmeta) );
		COMTHROW( cmeta->get_Name(bstrKindName) );
		CString kindName = bstrKindName;

		if( filter.getCaseIgnored) // case ignored, make values lowercase
		{
			name.MakeLower();
			kindName.MakeLower();
		}

		if( (filter.objName.Match(name)) && (filter.objKind.Match(kindName))  )		
		{
			if(!filter.objattribName.IsEmpty())
			{
				found = CheckAttributes(ref);
			}
			else
				found = true;
			
			//this is only for the Null reference search, searching for specific refererences handled below
			if(filter.getSplSearch && found)
			{
				CComPtr<IMgaFCO> referred;
				COMTHROW(ref->get_Referred(&referred));
				if(referred != NULL)
					found = false;
			}
			
			if(found)
			{
				COMTHROW(results->Append(ref));
			}
		}

}

//checks the name, kindname and attributes, adding all matches to the results
void CSearch::CheckSet(IMgaSet *Set)
{

		CComPtr<IMgaSet> set = Set;

		bool found = false;
		//get the name
		CBstr bstrName;
		COMTHROW(set->get_Name(bstrName));
		CString name = bstrName;
		//get the KindName
		CBstr bstrKindName;
		CComPtr<IMgaMetaFCO> cmeta;
		COMTHROW( set->get_Meta(&cmeta) );
		COMTHROW( cmeta->get_Name(bstrKindName) );
		CString kindName = bstrKindName;

		if( filter.getCaseIgnored) // case ignored, make values lowercase
		{
			name.MakeLower();
			kindName.MakeLower();
		}

		if( (filter.objName.Match(name)) && (filter.objKind.Match(kindName))  )		
		{
			if(!filter.objattribName.IsEmpty())
			{
				found = CheckAttributes(set);
			}
			else
				found = true;
				
			if(found)
			{
				COMTHROW(results->Append(set));
			}
		}

}

//checks the name, kindname and attributes, adding all matches to the results
void CSearch::CheckModel(IMgaModel *Model)
{

		CComPtr<IMgaModel> model = Model;

		bool found = false;
		//get the name
		CBstr bstrName;
		COMTHROW(model->get_Name(bstrName));
		CString name = bstrName;
		//get the KindName
		CBstr bstrKindName;
		CComPtr<IMgaMetaFCO> cmeta;
		COMTHROW( model->get_Meta(&cmeta) );
		COMTHROW( cmeta->get_Name(bstrKindName) );
		CString kindName = bstrKindName;

		if( filter.getCaseIgnored) // case ignored, make values lowercase
		{
			name.MakeLower();
			kindName.MakeLower();
		}

		if( (filter.objName.Match(name)) && (filter.objKind.Match(kindName))  )		
		{
			if(!filter.objattribName.IsEmpty())
			{
				found = CheckAttributes(model);
			}
			else
				found = true;
				
			if(found)
			{
				COMTHROW(results->Append(model));
			}
		}

}


//special search for references to specific objects
void CSearch::SearchReferences(IMgaFCO *referenced)
{

	CComPtr<IMgaFCOs> objRefByList;
	COMTHROW(referenced->get_ReferencedBy(&objRefByList));

	MGACOLL_ITERATE(IMgaFCO, objRefByList)
	{
		CComPtr<IMgaFCO> refobj = MGACOLL_ITER;
		COMTHROW(results->Append(refobj));
	} MGACOLL_ITERATE_END;

}


bool CSearch::CheckAttributes(IMgaFCO *obj)
{			
	int val_int;
	double val_dbl;
	bool val_b;
	bool found = false;
	CComPtr<IMgaFCO> cObj = obj;

	//first, get the attribute names
	CStringList attriblist;
	attval_enum type;
	attval_enum sectype;

	type = filter.getAttrType;
	if(type == ATTVAL_STRING)
		sectype = ATTVAL_ENUM;
	else
		sectype = ATTVAL_NULL;

	CComPtr<IMgaMetaFCO> cmeta;
	CComPtr<IMgaMetaAttributes> mattrs;
	COMTHROW(cObj->get_Meta(&cmeta));
	COMTHROW(cmeta->get_Attributes(&mattrs));
	MGACOLL_ITERATE(IMgaMetaAttribute, mattrs) {
		attval_enum t;
		COMTHROW(MGACOLL_ITER->get_ValueType(&t) );
		if(t == type || t == sectype) { 
			CBstr n;
			COMTHROW(MGACOLL_ITER->get_Name(n) );
			attriblist.AddTail(n);
		}
		
	} MGACOLL_ITERATE_END;


	//now check the attributes
	POSITION strpos = attriblist.GetHeadPosition();

	while(strpos)
	{
		CString attrib = attriblist.GetNext(strpos);
		CString attrib_altered = attrib;

		if( filter.getCaseIgnored) // case ignored, make attrib name lowercase
		{
			attrib_altered.MakeLower();
		}

		if(filter.objAttrName.Match(attrib_altered))
		{
			if(!filter.objVal.IsEmpty())
			{
				int actval_int;
				double actval_dbl;
				bool actval_b;
				CString actval_str;
				
				CBstr bstrS;
				long l;
				VARIANT_BOOL vb;

				switch(filter.getAttrType)
				{
					case ATTVAL_STRING:		if(! SUCCEEDED( cObj->get_StrAttrByName((CBstrIn)attrib, bstrS) ) ) found = false;
											//COMTHROW( cObj->get_StrAttrByName((CBstrIn)attrib, bstrS) ); 
											actval_str = bstrS;
											if( filter.getCaseIgnored) // case ignored, make attrib value lowercase
											{
												actval_str.MakeLower();
											}

											if(filter.objAttrVal.Match( actval_str))
												found = true;
											// the lines above allow partially specified values to match
											// by Zolmol

											if(filter.objVal == actval_str)
												found = true;
											break;

					case ATTVAL_INTEGER:	if(! SUCCEEDED( cObj->get_IntAttrByName((CBstrIn)attrib, &l) ) ) found = false;
											//COMTHROW( cObj->get_IntAttrByName((CBstrIn)attrib, &l));
											actval_int = l;
											val_int = atoi(filter.objVal);
											if(val_int == actval_int)
												found = true;
											break;
					
					case ATTVAL_DOUBLE:		if( !SUCCEEDED( cObj->get_FloatAttrByName((CBstrIn)attrib, &actval_dbl) ) ) found = false;
											//COMTHROW( cObj->get_FloatAttrByName((CBstrIn)attrib, &actval_dbl));
											val_dbl = atof(filter.objVal);
											if(val_dbl == actval_dbl)
												found = true;
											break;
					
					case ATTVAL_BOOLEAN:	if( !SUCCEEDED( cObj->get_BoolAttrByName((CBstrIn)attrib, &vb) ) ) found = false;
											//COMTHROW( cObj->get_BoolAttrByName((CBstrIn)attrib, &vb));
											actval_b = (vb != 0);			
											val_int = atoi(filter.objVal);
											if(filter.objVal=="false" || filter.objVal=="False" || filter.objVal=="FALSE" || val_int==0)
												val_b = false;
											if(filter.objVal=="true" || filter.objVal=="True" || filter.objVal=="TRUE" || val_int==1)
												val_b = true;

											if(val_b == actval_b)
												found = true;
											break;
					
					case ATTVAL_REFERENCE:	break;
					
					default:				found = true; break;
				}
			}
			else
				found = true;
		}

		if (found)	break;
	}		
	return found; 
}


/*
// COM Functions for Attributes!!...:-((

void CSearch::GetAllAttributes(CBuilderObject *obj)
{
	ASSERT (attrlist->IsEmpty());

	CComPtr<IMgaMetaAttributes> metaAttribs;
	//CComPtr<IMgaMetaFCO> objMeta = obj->GetMeta();

	COMTHROW(obj->GetMeta()->get_Attributes(&mattrs));
	
	MGACOLL_ITERATE(IMgaMetaAttribute, mattrs) 
	{
		attval_enum t;
		COMTHROW(MGACOLL_ITER->get_ValueType(&t) );
		CBstr n;
		COMTHROW(MGACOLL_ITER->get_Name() );


}
*/