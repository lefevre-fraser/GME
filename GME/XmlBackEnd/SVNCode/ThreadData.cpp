/**
 * @copyright
 * ====================================================================
 * Copyright (c) 2003 CollabNet.  All rights reserved.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at http://subversion.tigris.org/license-1.html.
 * If newer versions of this license are posted there, you may use a
 * newer version instead, at your option.
 *
 * This software consists of voluntary contributions made by many
 * individuals.  For exact contribution history, see the revision
 * history and logs, available at http://subversion.tigris.org/.
 * ====================================================================
 * @endcopyright
 *
 */
/**
 * Modified by Zoltan Molnar, Vanderbilt University, 2008
 */


#include "../StdAfx.h"

#if(USESVN)

#include "threaddata.h"

ThreadData::ThreadData(void)
{
}

ThreadData::~ThreadData(void)
{
}

void ThreadData::init()
{
	m_exceptionThrown = false;
	m_requestPool = 0; 
}
#endif