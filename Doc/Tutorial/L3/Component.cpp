#include "stdafx.h"

#include "Component.h"

#include <fstream.h> 

/* 
// This method is usually no longer in use and does not need to be implemented,
// except when DEPRECATED_BON_INVOKE_IMPLEMENTED is defined in Component.h.
// See the top section of ComponentObj.cpp for details.
void CComponent::Invoke(CBuilder &builder,CBuilderObjectList &selected, long param)
{
	AfxMessageBox("GME Component --- Sample", MB_OK | MB_ICONSTOP);
}
*/

static ofstream outf; 

void CComponent::InvokeEx(CBuilder &builder,CBuilderObject *focus, CBuilderObjectList &selected, long param) 
{ 
	outf.open("netlist.lst"); 
	outf << "Router list for network" << builder.GetRootFolder()->GetName() << endl; 
	const CBuilderModelList *diags = builder.GetRootFolder()->GetRootModels(); 
	POSITION pos = diags->GetHeadPosition(); 
	while(pos) 
	{ 
		CBuilderModel *diagram = diags->GetNext(pos); 
		ProcessDiagram(diagram); 
	} 
	outf.close(); 
} 

void CComponent::ProcessDiagram(CBuilderModel *d) 
{ 
	ASSERT(d->GetKindName() == "NetDiagram"); 
	const CBuilderModelList *diags = d->GetModels("NetDiagram"); 
	POSITION pos = diags->GetHeadPosition(); 
	while(pos) ProcessDiagram(diags->GetNext(pos)); // recursion 

	const CBuilderModelList *routers = d->GetModels("Router"); 
	pos = routers->GetHeadPosition(); 
	while(pos) ProcessRouter(routers->GetNext(pos)); 
} 

void CComponent::ProcessRouter(CBuilderModel *r) 
{ 
	ASSERT(r->GetKindName() == "Router"); 
	CString fam; 
	r->GetAttribute("Family", fam); 
	outf << "\tRouter " << r->GetName() << " (" << fam << ")" << endl; 

	const CBuilderAtomList *ports = r->GetAtoms("Port"); 
	POSITION pos = ports->GetHeadPosition(); 
	while(pos) 
	{ 
		CBuilderAtom *port = ports->GetNext(pos); 
		CString iftype, ipaddr; 
		int ifspeed; 
		port->GetAttribute("IFType", iftype); 
		port->GetAttribute("IFSpeed", ifspeed); 
		port->GetAttribute("IPAddress", ipaddr); 
		outf << "\t\tPort " << port->GetName(); 
		outf << "(" << iftype << "; "<< ifspeed << "Kbps), Addr: " << ipaddr << endl; 
	} 
}