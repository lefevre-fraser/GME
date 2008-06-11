#include "stdafx.h"
#include "BON.h"
#include "BONImpl.h"
#include "AtomRep.h"
#include "logger.h"
#include "ConstraintRep.h"
#include "ConstraintFuncRep.h"

AtomRep::AtomRep( BON::FCO& ptr) : 
    Any(ptr)
	, Constrained( ptr)
	, FCO( ptr)
{ 
}

AtomRep::~AtomRep()
{
}