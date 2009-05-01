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


    if(filter.scope==1)
    {
        //SearchReferences(selected);
    }
    else if( filter.scope==2 && scopeColl)
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
    else if(filter.scope==0)
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
        /*CString partName;
        CBstr bstr;
        CComPtr<IMgaMetaRole> rmeta;
        COMTHROW( MGACOLL_ITER->get_MetaRole(&rmeta) );
        if(rmeta) 
        {
        COMTHROW( rmeta->get_Name(bstr) );
        partName = bstr;
        } 
        else 
        partName = "";*/
        objtype_enum rret;
        COMTHROW( MGACOLL_ITER->get_ObjType( &rret) );

        /*if( filter.getCaseIgnored) // case ignored, make role lowercase
        {
        partName.MakeLower();
        }*/

        if(rret == OBJTYPE_ATOM)  
        {
            // if(Check(MGACOLL_ITER.p,0)) COMTHROW(results->Append((IMgaAtom *)MGACOLL_ITER.p));
            if (CheckAtom((IMgaAtom*)(MGACOLL_ITER.p))) COMTHROW(results->Append((IMgaAtom*)(MGACOLL_ITER.p)));
        }
        /*if((rret == OBJTYPE_ATOM) && filter.or&& filter.doSecond && (filter.objRole2.Match(partName)) )
        {
        CheckAtom((IMgaAtom *)MGACOLL_ITER.p,FALSE);
        }*/

        m_pgsSearch->StepIt();	
    } MGACOLL_ITERATE_END;

}

// get all the references that have a matching role name, calling CheckReference on each
void CSearch::CheckAllReferences(IMgaFCOs *allObjects)
{

    MGACOLL_ITERATE(IMgaFCO, allObjects)
    {
        /*CString partName;
        CBstr bstr;
        CComPtr<IMgaMetaRole> rmeta;
        COMTHROW( MGACOLL_ITER->get_MetaRole(&rmeta) );
        if(rmeta) 
        {
        COMTHROW( rmeta->get_Name(bstr) );
        partName = bstr;
        } 
        else 
        partName = "";*/
        objtype_enum rret;
        COMTHROW( MGACOLL_ITER->get_ObjType( &rret) );

        /*if( filter.getCaseIgnored) // case ignored, make role lowercase
        {
        partName.MakeLower();
        }*/

        if(rret == OBJTYPE_REFERENCE )
        {
            //if(Check(MGACOLL_ITER.p,2)) COMTHROW(results->Append((IMgaReference *)(MGACOLL_ITER.p)));
            if (CheckAtom((IMgaAtom*)(MGACOLL_ITER.p))) COMTHROW(results->Append((IMgaReference*)(MGACOLL_ITER.p)));
        }
        /*if((rret == OBJTYPE_REFERENCE) && filter.or && filter.doSecond && (filter.objRole2.Match(partName)) )
        {
        CheckReference((IMgaReference *)(MGACOLL_ITER.p),FALSE);
        }*/


        m_pgsSearch->StepIt();
    } MGACOLL_ITERATE_END;

}

// get all the sets that have a matching role name, calling CheckSet on each
void CSearch::CheckAllSets(IMgaFCOs *allObjects)
{

    MGACOLL_ITERATE(IMgaFCO, allObjects)
    {
        /*CString partName;
        CBstr bstr;
        CComPtr<IMgaMetaRole> rmeta;
        COMTHROW( MGACOLL_ITER->get_MetaRole(&rmeta) );
        if(rmeta) 
        {
        COMTHROW( rmeta->get_Name(bstr) );
        partName = bstr;
        } 
        else 
        partName = "";*/
        objtype_enum rret;
        COMTHROW( MGACOLL_ITER->get_ObjType( &rret) );

        /*if( filter.getCaseIgnored) // case ignored, make role lowercase
        {
        partName.MakeLower();
        }*/

        if(rret == OBJTYPE_SET)
        {
            //if(Check(MGACOLL_ITER.p,3)) COMTHROW(results->Append((IMgaSet *)(MGACOLL_ITER.p)));
            if(CheckSet((IMgaSet*)(MGACOLL_ITER.p)))COMTHROW(results->Append((IMgaSet*)(MGACOLL_ITER.p)));
        }
        /*if((rret == OBJTYPE_SET)&& filter.or && filter.doSecond && (filter.objRole2.Match(partName)) )
        {
        CheckSet((IMgaSet *)(MGACOLL_ITER.p),FALSE);
        }*/

        m_pgsSearch->StepIt();
    } MGACOLL_ITERATE_END;	
}

// get all the models that have a matching role name, calling CheckModel on each
void CSearch::CheckAllModels(IMgaFCOs *allObjects)
{


    MGACOLL_ITERATE(IMgaFCO, allObjects)
    {
        /*CString partName;
        CBstr bstr;
        CComPtr<IMgaMetaRole> rmeta;
        COMTHROW( MGACOLL_ITER->get_MetaRole(&rmeta) );
        if(rmeta) 
        {
        COMTHROW( rmeta->get_Name(bstr) );
        partName = bstr;
        } 
        else 
        partName = "";*/
        objtype_enum rret;
        COMTHROW( MGACOLL_ITER->get_ObjType( &rret) );

        /*if( filter.getCaseIgnored) // case ignored, make role lowercase
        {
        partName.MakeLower();
        }*/

        if(rret == OBJTYPE_MODEL) 
        {
            //if(Check(MGACOLL_ITER.p,1)) COMTHROW(results->Append((IMgaModel *)(MGACOLL_ITER.p)));

            if(CheckModel((IMgaModel *)(MGACOLL_ITER.p))) COMTHROW(results->Append((IMgaModel*)(MGACOLL_ITER.p)));;
        }

        //added
        /* if((rret == OBJTYPE_MODEL)  && filter.or&& filter.doSecond &&(filter.objRole2.Match(partName))) {
        CheckModel((IMgaModel *)(MGACOLL_ITER.p),FALSE);
        }*/

        //end added
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
bool CSearch::CheckAtom(IMgaFCO *Atom)
{

    int x=Matches(Atom,true);
    int y=Matches(Atom,false);

    return PerformLogical(x,y);

}

//checks the name, kindname and attributes, adding all matches to the results
bool CSearch::CheckReference(IMgaFCO *Reference)
{

    int x=Matches(Reference,true);
    int y=Matches(Reference,false);

    return PerformLogical(x,y);
}

//checks the name, kindname and attributes, adding all matches to the results
bool CSearch::CheckSet(IMgaFCO *Set)
{

    int x=Matches(Set,true);
    int y=Matches(Set,false);

    return PerformLogical(x,y);
}

//checks the name, kindname and attributes, adding all matches to the results
bool CSearch::CheckModel(IMgaFCO *Model) //BOOL first added to check if it matches first or second
{

    int x=Matches(Model,true);
    int y=Matches(Model,false);

    return PerformLogical(x,y);

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

/*bool CSearch::CheckAttributes(IMgaFCO *obj,BOOL first)
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

type =first? filter.getAttrType:filter.getAttrType2;
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

switch(type)
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
*/

bool CSearch::CheckAttributes(IMgaFCO *obj,bool first)
{	
    int index=0;
    int val_int;
    double val_dbl;
    bool val_b;		
    bool found = false;
    CComPtr<IMgaFCO> cObj = obj;

    //first, get the attribute names
    CStringList attriblist;
    std::vector<attval_enum> typeList;
    std::vector<int> indices;
    std::vector<Attrib> expr=first?filter.expr1:filter.expr2;
    CComPtr<IMgaMetaFCO> cmeta;
    CComPtr<IMgaMetaAttributes> mattrs;
    COMTHROW(cObj->get_Meta(&cmeta));
    COMTHROW(cmeta->get_Attributes(&mattrs));
    index=0;
    MGACOLL_ITERATE(IMgaMetaAttribute, mattrs) {
        attval_enum t;
		CComBSTR n;
        COMTHROW(MGACOLL_ITER->get_DisplayedName(&n) );
		CComBSTR n2;
		COMTHROW(MGACOLL_ITER->get_Name(&n2) );
        index=0; 
        for(std::vector<Attrib>::iterator it=expr.begin();it!=expr.end();++it)
        {
            Attrib attr=*it;
            CString name=(CString) n;
            if (filter.getCaseIgnored) name.MakeLower();
			if(attr.GetRegExp(attr.name,filter.full).Match(name))
            {
                COMTHROW(MGACOLL_ITER->get_ValueType(&t) );
                attriblist.AddTail(CString(n2));
                typeList.push_back(t);
                indices.push_back(index);
            }
            index++;
        }



    } MGACOLL_ITERATE_END;


    //now check the attributes
    POSITION strpos = attriblist.GetHeadPosition();
    index=0;
    int temp_index=0;

    while(strpos)
    {
        CString attrib = attriblist.GetNext(strpos);
        CString attrib_altered = attrib;
        Attrib& attrib_name=expr[indices[index]];

        /* while(indices[index]>temp_index)
        {
        if(!expr[temp_index].IsOperator())
        {
        expr[temp_index].eval=FALSE;
        }
        temp_index++;
        }*/

        if( filter.getCaseIgnored) // case ignored, make attrib name lowercase
        {
            attrib_altered.MakeLower();
        }

        //this check is useless reduce it

        //if(attrib_name.GetRegExp(attrib_name.name,filter.full).Match(attrib_altered))
        {
            CString objVal=expr[indices[index]].value;
            if(!objVal.IsEmpty())
            {
                int actval_int;
                double actval_dbl;
                bool actval_b;
                CString actval_str;

                CBstr bstrS;
                long l;
                VARIANT_BOOL vb;

                switch(typeList[index])
                {
                case ATTVAL_STRING:		if(! SUCCEEDED( cObj->get_StrAttrByName((CBstrIn)attrib, bstrS) ) ) attrib_name.eval=FALSE;
                    //COMTHROW( cObj->get_StrAttrByName((CBstrIn)attrib, bstrS) ); 
                    actval_str = bstrS;
                    if( filter.getCaseIgnored) // case ignored, make attrib value lowercase
                    {
                        actval_str.MakeLower();
                    }

                    if(attrib_name.CheckString(attrib_name.GetRegExp(objVal,filter.full).Match( actval_str)))
                        attrib_name.eval=TRUE;
                    break;

                case ATTVAL_INTEGER:	if(! SUCCEEDED( cObj->get_IntAttrByName((CBstrIn)attrib, &l) ) ) attrib_name.eval=FALSE;
                    //COMTHROW( cObj->get_IntAttrByName((CBstrIn)attrib, &l));
                    actval_int = l;
                    //val_int = atoi(filter.objVal);
                    val_int = atoi(attrib_name.value);
                    if(attrib_name.CheckInteger(actval_int,val_int))
                        attrib_name.eval=TRUE;
                    break;

                case ATTVAL_DOUBLE:		if( !SUCCEEDED( cObj->get_FloatAttrByName((CBstrIn)attrib, &actval_dbl) ) ) attrib_name.eval=FALSE;
                    //COMTHROW( cObj->get_FloatAttrByName((CBstrIn)attrib, &actval_dbl));
                    val_dbl = atof(attrib_name.value);
                    if(attrib_name.CheckDouble(actval_dbl,val_dbl))
                        attrib_name.eval=TRUE ;
                    break;

                case ATTVAL_BOOLEAN:	if( !SUCCEEDED( cObj->get_BoolAttrByName((CBstrIn)attrib, &vb) ) ) attrib_name.eval=FALSE;
                    //COMTHROW( cObj->get_BoolAttrByName((CBstrIn)attrib, &vb));
                    actval_b = (vb != 0);			
                    val_int = atoi(attrib_name.value);
                    if(attrib_name.value=="false" || attrib_name.value=="False" || attrib_name.value=="FALSE" || val_int==0)
                        val_b = false;
                    if(attrib_name.value=="true" || attrib_name.value=="True" || attrib_name.value=="TRUE" || val_int==1)
                        val_b = true;

                    if(attrib_name.CheckBool(actval_b,val_b))
                        attrib_name.eval=TRUE;
                    break;

                case ATTVAL_REFERENCE:	break;

                default:				attrib_name.eval = TRUE; break;
                }
            }
            else
                attrib_name.eval = TRUE;

        }

        ++index;
        //if (found)	break;
    }		
    return EvaluateResult(expr); 
}

//Evaluate the logical combination result

bool CSearch::EvaluateResult(std::vector<Attrib>& attrs)
{
    if(attrs.size()==0)
        return true;
    else if (attrs.size()==1)
        return (attrs[0].eval==TRUE);

    while(attrs.size()!=1)
    {
        Attrib attr=attrs.back();
        attrs.pop_back();
        Attrib oper=attrs.back();
        attrs.pop_back();
        Attrib attr2=attrs.back();
        attrs.pop_back();
        attr.eval=oper.LogicalCompare(attr.eval,oper,attr2.eval);
        attrs.push_back(attr);
    }
    return (attrs[0].eval == TRUE);
}


void CSearch::SearchResults(CComPtr<IMgaFCOs> old_results,CComPtr<IMgaFCOs> disp, CProgressCtrl *Progress)
{
    //CComPtr<IMgaFCO> fco;
    results=disp;
    m_pgsSearch=Progress;


    MGACOLL_ITERATE(IMgaFCO, old_results)
    {
        objtype_enum rret;
        COMTHROW( MGACOLL_ITER->get_ObjType( &rret) );
        if (rret == OBJTYPE_ATOM  && filter.getAtoms)
        {
            //if(Check(MGACOLL_ITER.p,0)) COMTHROW(results->Append((IMgaAtom*)(MGACOLL_ITER.p)));
            if (CheckAtom((IMgaAtom*)(MGACOLL_ITER.p))) COMTHROW(results->Append((IMgaAtom*)(MGACOLL_ITER.p)));
        }
        else if (rret == OBJTYPE_MODEL && filter.getModels)
        {
            //type = "MODEL";
            //if(Check((MGACOLL_ITER.p),1)) COMTHROW(results->Append((IMgaModel*)(MGACOLL_ITER.p)));
            if(CheckModel((IMgaModel *)(MGACOLL_ITER.p))) COMTHROW(results->Append((IMgaModel*)(MGACOLL_ITER.p)));;
        }
        else if (rret == OBJTYPE_REFERENCE && filter.getReferences)
        {
            //type = "REFERENCE";
            //if(Check((MGACOLL_ITER.p),2)) COMTHROW(results->Append((IMgaReference*)(MGACOLL_ITER.p)));
            if (CheckAtom((IMgaAtom*)(MGACOLL_ITER.p))) COMTHROW(results->Append((IMgaReference*)(MGACOLL_ITER.p)));
        }
        else if (rret == OBJTYPE_SET && filter.getSets)
        {
            //if(Check((MGACOLL_ITER.p),3)) COMTHROW(results->Append((IMgaSet*)(MGACOLL_ITER.p)));
            if(CheckSet((IMgaSet*)(MGACOLL_ITER.p)))COMTHROW(results->Append((IMgaSet*)(MGACOLL_ITER.p)));
            //type = "SET";
        }
    } MGACOLL_ITERATE_END;
}


/*bool CSearch::Check(IMgaFCO* fco,int type) //0-atom,1-model,2-ref,3-set
{

switch(type)
{
case 0:
return CheckLogicalCombination(fco,&CSearch::CheckAtom);

case 1:
return CheckLogicalCombination(fco,&CSearch::CheckModel);

case 2:
return CheckLogicalCombination(fco,&CSearch::CheckReference);

case 3:
return CheckLogicalCombination(fco,&CSearch::CheckSet);
case 4:
return CheckLogicalCombination(fco,&CSearch::CheckAttributes);
}
return false;
}

bool CSearch::CheckLogicalCombination(IMgaFCO* fco,bool (CSearch::*Chk)(IMgaFCO* fco,bool first))
{
BSTR n;
COMTHROW(fco->get_Name(&n));
switch(filter.logical)
{
case 0://AND
return (this->*Chk)(fco,true) && (this->*Chk)(fco,false);
case 1://OR
return (this->*Chk)(fco,true) || (this->*Chk)(fco,false);
case 2://XOR
bool b1=(this->*Chk)(fco,true);
bool b2=!(this->*Chk)(fco,false);
bool b3=(!(this->*Chk)(fco,true));
bool b4=(this->*Chk)(fco,false);
return (b1 && b2) || (b3&& b4);
// return (((this->*Chk)(fco,true) && (!(this->*Chk)(fco,false))) || (((!(this->*Chk)(fco,true)) && (this->*Chk)(fco,false))));
}
return false;
}*/

bool CSearch::PerformLogical(int x,int y)
{
    switch (filter.logical)
    {
    case 0:
        return (x==-1 && y==1)||(x==1 && y==-1) ||(x==1&&y==1);
    case 1:
        return x==1 || y==1;
    case 2:
        return (x==-1 && y==1)||(x==1 && y==-1)||(x==1 && y==0);
    }

    return false;
}

int CSearch::Matches(IMgaFCO* fco,bool first)
{
    CString partName;
    CBstr bstr;
    CComPtr<IMgaMetaRole> rmeta;
    COMTHROW( fco->get_MetaRole(&rmeta) );
    if(rmeta) 
    {
        COMTHROW( rmeta->get_Name(bstr) );
        partName = bstr;
    } 
    else 
        partName = "";
    CRegExp role=first?filter.objRole:filter.objRole2;


    //if(!role.Match(partName)) return false;


    //get the name
    CBstr bstrName;
    COMTHROW(fco->get_Name(bstrName));
    CString name = bstrName;
    //get the KindName
    CBstr bstrKindName;
    CComPtr<IMgaMetaFCO> cmeta;
    COMTHROW( fco->get_Meta(&cmeta) );
    COMTHROW( fco->get_Name(bstrKindName) );
    CString kindName = bstrKindName;

    if( filter.getCaseIgnored) // case ignored, make values lowercase
    {
        name.MakeLower();
        kindName.MakeLower();
        partName.MakeLower();
    }
    bool found = true;
    int result=-1;
    if(first)
    {
        if(!filter.role.IsEmpty())
        {
            result=filter.objRole.Match(partName)?1:0;

        }
        if(!filter.kind.IsEmpty() && result!=0)
            result=filter.objRole.Match(kindName)?1:0;

        if(!filter.name.IsEmpty() &&result!=0)
            result=filter.objName.Match(name)?1:0;
        if(!filter.objattrib.IsEmpty() &&result!=0)
            result=CheckAttributes(fco,first)?1:0;

    }
    else
    {
        if(!filter.role2.IsEmpty())
        {
            result=filter.objRole2.Match(partName)?1:0;

        }
        if(!filter.kind2.IsEmpty()&& result!=0)
            result=filter.objRole2.Match(kindName)?1:0;

        if(!filter.name2.IsEmpty() &&result!=0)
            result=filter.objName2.Match(name)?1:0;
        if(!filter.objAttrib2.IsEmpty() && result!=0)
            result=CheckAttributes(fco,first)?1:0;
    }

    return result;
    //if(filter.objRole.Is
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