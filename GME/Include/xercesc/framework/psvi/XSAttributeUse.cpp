/*
 * Copyright 2003,2004 The Apache Software Foundation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * $Id: XSAttributeUse.cpp,v 1.1 2008/02/19 20:16:27 zolmol Exp $
 */

#include <xercesc/framework/psvi/XSAttributeUse.hpp>

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  XSAttributeUse: Constructors and Destructor
// ---------------------------------------------------------------------------
XSAttributeUse::XSAttributeUse(XSAttributeDeclaration* const xsAttDecl,
                               XSModel* const xsModel,
                               MemoryManager* const manager)
    : XSObject(XSConstants::ATTRIBUTE_USE, xsModel, manager)
    , fRequired(false)
    , fConstraintType(XSConstants::VALUE_CONSTRAINT_NONE)
    , fConstraintValue(0)
    , fXSAttributeDeclaration(xsAttDecl)
{
}


XSAttributeUse::~XSAttributeUse() 
{
    // don't delete fXSAttributeDeclaration - deleted by XSModel
}


// ---------------------------------------------------------------------------
//  XSAttributeUse: helper methods
// ---------------------------------------------------------------------------
void XSAttributeUse::set(const bool isRequired,
                         XSConstants::VALUE_CONSTRAINT constraintType,
                         const XMLCh* const constraintValue)
{
    fRequired = isRequired;
    fConstraintType = constraintType;
    fConstraintValue = constraintValue;
}

XERCES_CPP_NAMESPACE_END


