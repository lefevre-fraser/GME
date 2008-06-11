#include <windows.h>
#include <atlbase.h>
#include "CommonSmart.h"
#include <stdio.h>

#include "Mga.h"
#include "MgaUtil.h"

#define MGACOLL_ITERATE(iftype, collifptr) \
{{{											\
ASSERT( collifptr != NULL );				\
long iter_count = 0;								\
COMTHROW( collifptr->get_Count(&iter_count) );		\
ASSERT( iter_count >= 0 );						\
CComPtr<iftype> *arrptr, *arrend, *array = new CComPtr<iftype>[iter_count]; \
if(iter_count > 0) { \
		unsigned long provided = 0; \
		if(iter_count > 0) COMTHROW( collifptr->GetAll((unsigned long)iter_count, &(*array), &provided) ); \
		ASSERT( (unsigned long)iter_count == provided ); \
} \
arrend = array+iter_count; \
for(arrptr = array; arrptr != arrend; arrptr++)  
#define MGACOLL_ITER (*arrptr)
#define MGACOLL_AT_END (arrptr == arrend)

#define MGACOLL_ITERATE_END delete []array; }}}



#define PRINTANDTHROW(code, string) { \
	fprintf(stderr, "Error %08lX: %s\n", code, string); \
	throw code; \
}
#undef COMTHROW
#define COMTHROW(xx) { \
							HRESULT pp = (xx); \
							if(pp != S_OK) {	\
								PRINTANDTHROW(pp,#xx); \
							} \
					}




long GetArrayLength(const VARIANT &v);
void CopyTo(const VARIANT &v, CComBSTR *start, CComBSTR *end);


bool LocateObject(IMgaProject *p, char * name, IMgaObject **obj) {
	CComPtr<IMgaFolder> f;
	CComPtr<IMgaFCO> fco;
	COMTHROW(p->get_RootFolder(&f));

	char sname[300];
	strncpy(sname, name, 300);
	sname[299] = '\0';
	char *namepart = strtok(sname,"/");

	do {
		if(!namepart) {
			*obj = f.Detach();
			return true;
		}
		
		CComPtr<IMgaFolders> cfs;
		CComPtr<IMgaFCOs> cfcos;
		COMTHROW(f->get_ChildFolders(&cfs));
		COMTHROW(f->get_ChildFCOs(&cfcos));
		f = NULL;
		{
		MGACOLL_ITERATE(IMgaFolder, cfs) {
			CComBSTR name;
			COMTHROW(MGACOLL_ITER->get_Name(&name));
			if(name == namepart) {
				f = MGACOLL_ITER;
				break;
			}
		}
		MGACOLL_ITERATE_END;	
		}
		if(!f) {
		MGACOLL_ITERATE(IMgaFCO, cfcos) {
			CComBSTR name;
			COMTHROW(MGACOLL_ITER->get_Name(&name));
			if(name == namepart) {
				fco = MGACOLL_ITER;
				break;
			}
		}
		MGACOLL_ITERATE_END;	
		}
		if(!fco) return false;
		namepart = strtok(NULL, "/");
	} while(f);

	do {
		if(!namepart) {
			*obj = fco.Detach();
			return true;
		}
		CComQIPtr<IMgaModel> m = fco;
		if(!m) return false;
		CComPtr<IMgaFCOs> cfcos;
		COMTHROW(m->get_ChildFCOs(&cfcos));
		MGACOLL_ITERATE(IMgaFCO, cfcos) {
			CComBSTR name;
			COMTHROW(MGACOLL_ITER->get_Name(&name));
			if(name == namepart) {
				fco = MGACOLL_ITER;
				break;
			}
		}
		MGACOLL_ITERATE_END;	
		namepart = strtok(NULL, "/");
	} while(fco);
	return false;
}	



int main(int argc, char **argv) {
	bool iflag = true, lflag = false, pflag = false;
	long code = 0;
	bool projectopen = false;

	char *pdigm;

	CComBSTR filename;
	char currDir[512];
	GetCurrentDirectory(512,currDir);

	CComPtr<IMgaObjects> objcoll;
	CComPtr<IMgaFCOs> fcocoll;

	CComPtr<IMgaProject> project;
	CComPtr<IMgaTerritory> terr;
	CComPtr<IMgaComponent> component;
	CComPtr<IMgaFCO> context;
  try {
	
    COMTHROW(CoInitialize(NULL));
	COMTHROW(project.CoCreateInstance(CComBSTR("Mga.MgaProject")));

	for(int i = 1; i < argc; i++) {
		char *actarg = argv[i];
		if(actarg[0] == '-') {
			for(int j = 1; actarg[j]; j++) {
				switch(actarg[j]) {
				case 'n':  iflag = false;  
							break;
				case 'c':  code = atol(actarg+j);
							j += strlen(actarg+j) - 1;
							break;
				case 'l': lflag = true;
							break;
				case 'p': pflag = true;
							pdigm = actarg + j + 1;
							j += strlen(actarg+j) - 1;
							break;
				default: goto usage;
				}
			}

		}
		else if(lflag) {
			CComPtr<IMgaObject> o;
			if(!LocateObject(project, actarg, &o)) {
				printf("Cannot find object %s\n", actarg);
				return -1;
			}
			CComQIPtr<IMgaFCO> fo = o;
			if(!fo) {
				printf("Object %s is not an FCO\n", actarg);
				return -1;
			}
			context = fo;
			if(!fcocoll) COMTHROW(fcocoll.CoCreateInstance(CComBSTR("Mga.MgaFCOs")));
			COMTHROW(fcocoll->Append(fo));
			lflag = true;
		}
		else if(!projectopen) {
			CComBSTR projname;
			if(!strchr(actarg, '=')) projname = "MGA=";
			projname.Append(actarg);
			
			filename = projname;

			if(pflag)
			{
				printf("Creating %S\n", projname.m_str);
				COMTHROW(project->Create(projname,CComBSTR(pdigm)));
				COMTHROW(project->CreateTerritory(NULL, &terr));
				COMTHROW(project->BeginTransaction(terr/*, TRANSACTION_READ_ONLY*/));
				COMTHROW(project->put_Name(CComBSTR(actarg)));
				CComPtr<IMgaFolder> rootFdr;
				COMTHROW(project->get_RootFolder(&rootFdr));
				COMTHROW(rootFdr->put_Name(CComBSTR(actarg)));
			}
			else
			{
				printf("Opening %S\n", projname.m_str);
				COMTHROW(project->Open(projname));
				COMTHROW(project->CreateTerritory(NULL, &terr));
				COMTHROW(project->BeginTransaction(terr/*, TRANSACTION_READ_ONLY*/));
			}

			projectopen = true;
		}
		else if(!component) {
			CComPtr<IMgaRegistrar> reg;
			COMTHROW(reg.CoCreateInstance(CComBSTR("Mga.MgaRegistrar")));
			CComBSTR compname;
			if(!strchr(actarg, '.')) {   // just a name without progid
				printf("Looking up progID for %s\n", actarg);
				CComVariant pids;
				COMTHROW(reg->get_Components(REGACCESS_BOTH, &pids));
				int cnt= GetArrayLength(pids);
				CComBSTR *array = new CComBSTR[cnt];
				CopyTo(pids, array, array+cnt);

				for(int i = 0; i < cnt; ++i) {
					CComBSTR desc;
					componenttype_enum ct;
					if(reg->QueryComponent(array[i], &ct, &desc, REGACCESS_PRIORITY) != S_OK) {
						printf("Warning: failed to query component %S\n", (BSTR)array[i]);
					}
					if(desc == actarg) {
						compname = array[i];
						break;
					}
				}		
				delete [] array;
				if(!compname) {
					printf("Error: Could not find component %s\n", actarg);
					return -1;
				}
			}
			else 			compname = actarg;
			CComBSTR desc;
			componenttype_enum ct;
			if(reg->QueryComponent(compname, &ct, &desc, REGACCESS_PRIORITY) != S_OK) {
				printf("Error: could query component %S\n", compname);
				return  -1;
			}
			if(ct & COMPONENTTYPE_ADDON) {
				printf("Warning: Addons can only be partially tested");
			}
			COMTHROW(component.CoCreateInstance(compname));
		}
		else if(!context) {    // in compliance with the current Component interface, 
								// the first object in the FCO collection is the context object
								// (followed by a list of other objects)
			CComPtr<IMgaObject> o;
			if(!LocateObject(project, actarg, &o)) {
				printf("Cannot find object %s\n", actarg);
				return -1;
			}
			CComQIPtr<IMgaFCO> fo = o;
			if(!fo) {
				printf("Object %s is not an FCO\n", actarg);
				return -1;
			}
			context = fo;
			if(!fcocoll) COMTHROW(fcocoll.CoCreateInstance(CComBSTR("Mga.MgaFCOs")));
			COMTHROW(fcocoll->Append(fo));
			lflag = true;
		}
		else goto usage;
	}
	if(!component) {
usage:
			printf("Usage: ComponentTest <projectname> <componentID> [<context>] [-l object...]\n"
					"\tFlags:\t-n : non-interactive\n"
					"\t\t-c<num>: set long argument\n"
					"\t\t-p<paradigm>: create new project using paradigm\n");
			return -1;
	}
	printf("Initializing Component....\n");
	COMTHROW(component->Initialize(project));
	COMTHROW(component->put_InteractiveMode(iflag ?VARIANT_TRUE : VARIANT_FALSE));
	printf("Invoking Component....\n");
	COMTHROW(component->Invoke(project, fcocoll, code));
	printf("Component returned OK....\n");
	COMTHROW(project->CommitTransaction());
//	terr = NULL;
	SetCurrentDirectory(currDir);
	COMTHROW(project->Save(filename));
	COMTHROW(project->Close());
  }
  catch(...) {
	  if(project) 
	  {
		  try
		  {
			  printf("Component aborted with exception...\n");
			  COMTHROW(project->CommitTransaction());
			  SetCurrentDirectory(currDir);
//			  COMTHROW(project->Save(filename));
			  project->Close();
		  }
		  catch(...)
		  {
			  printf("Exception thrown trying to save and close project...\n");
			  project->Close();
		  }
	  }
	  return -1;
  }	
  return 0;
}