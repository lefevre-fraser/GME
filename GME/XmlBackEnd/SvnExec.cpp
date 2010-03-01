// SvnExec.cpp : Implementation of CSvnExec

#include "stdafx.h"
#include "SvnExec.h"
#include "svauto_i.c" // this includes the IID_ISvnExec, IID_ISvnTester, IID_ISvnWorkBench

// CSvnExec
VARIANT_BOOL CSvnExec::b2vb( bool p_val)
{
	return p_val? VARIANT_TRUE: VARIANT_FALSE;
}

bool CSvnExec::vb2b( VARIANT_BOOL p_val)
{
	return p_val == VARIANT_TRUE;
}

STDMETHODIMP CSvnExec::TryLock(BSTR p_path, VARIANT_BOOL* p_ptrSuccess)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

#if(USESVN)
	std::string ph;
	CopyTo( p_path, ph);
	
	bool succ = m_impl->tryLock( ph);
	if( p_ptrSuccess)
		*p_ptrSuccess = b2vb( succ);

	return S_OK;
#else
	return E_NOTIMPL;
#endif
}

STDMETHODIMP CSvnExec::UnLock(BSTR p_path, VARIANT_BOOL* p_ptrSuccess)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

#if(USESVN)
	std::string ph;
	CopyTo( p_path, ph);
	
	bool succ = m_impl->unLock( ph);
	if( p_ptrSuccess)
		*p_ptrSuccess = b2vb( succ);

	return S_OK;
#else
	return E_NOTIMPL;
#endif
}

STDMETHODIMP CSvnExec::AddLockableProperty(BSTR p_path)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

#if(USESVN)
	std::string ph;
	CopyTo( p_path, ph);
	
	bool res = m_impl->lockableProp( ph);

	return res? S_OK: E_FAIL;
#else
	return E_NOTIMPL;
#endif
}

STDMETHODIMP CSvnExec::GetLatest(BSTR p_path)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

#if(USESVN)
	std::string ph;
	CopyTo( p_path, ph);
	
	bool res = m_impl->getLatest( ph);

	return res? S_OK: E_FAIL;
#else
	return E_NOTIMPL;
#endif
}

STDMETHODIMP CSvnExec::LightCheckOut(BSTR p_path, BSTR p_localDir)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

#if(USESVN)
	std::string ph;
	std::string ldir;
	CopyTo( p_path, ph);
	CopyTo( p_localDir, ldir);
	
	bool res = m_impl->lightCheckOut( ph, ldir);

	return res? S_OK: E_FAIL;
#else
	return E_NOTIMPL;
#endif
}

STDMETHODIMP CSvnExec::Commit(BSTR p_path, BSTR p_comment, VARIANT_BOOL p_keepLocked)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

#if(USESVN)
	std::string ph;
	CopyTo( p_path, ph);
	std::string comment;
	CopyTo( p_comment, comment);

	bool res = m_impl->commitAll( ph, comment, vb2b( p_keepLocked));

	return res? S_OK: E_FAIL;
#else
	return E_NOTIMPL;
#endif
}

STDMETHODIMP CSvnExec::Add(BSTR p_path, VARIANT_BOOL p_recursive)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

#if(USESVN)
	std::string ph;
	CopyTo( p_path, ph);
	
	bool res = m_impl->add( ph, vb2b( p_recursive));

	return res? S_OK: E_FAIL;
#else
	return E_NOTIMPL;
#endif
}

STDMETHODIMP CSvnExec::SrvMkDir(BSTR p_path)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

#if(USESVN)
	std::string ph;
	CopyTo( p_path, ph);
	
	bool res = m_impl->mkDirOnServer( ph);

	return res? S_OK: E_FAIL;
#else
	return E_NOTIMPL;
#endif
}

STDMETHODIMP CSvnExec::Resolve(BSTR p_path, VARIANT_BOOL p_recursive)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

#if(USESVN)
	std::string ph;
	CopyTo( p_path, ph);
	
	bool res = m_impl->resolve( ph, vb2b( p_recursive));

	return res? S_OK: E_FAIL;
#else
	return E_NOTIMPL;
#endif
}

STDMETHODIMP CSvnExec::CleanUp(BSTR p_path)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

#if(USESVN)
	std::string ph;
	CopyTo( p_path, ph);
	
	bool res = m_impl->cleanup( ph);

	return res? S_OK: E_FAIL;
#else
	return E_NOTIMPL;
#endif
}

STDMETHODIMP CSvnExec::Status(BSTR p_path, VARIANT_BOOL p_provideStatusMessage, BSTR* p_ptrStatusMessage)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

#if(USESVN)
	std::string ph;
	CopyTo( p_path, ph);
	
	std::string status_msg;
	bool res = m_impl->status( ph, vb2b( p_provideStatusMessage), status_msg);
	CopyTo( status_msg, p_ptrStatusMessage);

	return res? S_OK: E_FAIL;
#else
	return E_NOTIMPL;
#endif
}

STDMETHODIMP CSvnExec::Info(BSTR p_url, VARIANT_BOOL p_recursive, VARIANT_BOOL p_provideInfoMessage, BSTR* p_ptrInfoMsg, BSTR* p_ptrAuthor, BSTR* p_ptrLockOwner)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

#if(USESVN)
	std::string url;
	CopyTo( p_url, url);
	std::string info_msg, author, lock_owner;

	bool res = m_impl->info( url, vb2b( p_recursive), vb2b( p_provideInfoMessage), info_msg, author, lock_owner);
	CopyTo( info_msg  , p_ptrInfoMsg);
	CopyTo( author    , p_ptrAuthor);
	CopyTo( lock_owner, p_ptrLockOwner);
	
	return res? S_OK: E_FAIL;
#else
	return E_NOTIMPL;
#endif
}

STDMETHODIMP CSvnExec::IsVersioned(BSTR p_path, VARIANT_BOOL p_isDir, VARIANT_BOOL p_suppressErrorMsg, VARIANT_BOOL* p_ptrIsVersioned)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

#if(USESVN)
	std::string ph;
	CopyTo( p_path, ph);
	bool versioned = m_impl->isVersioned( ph, vb2b( p_isDir), vb2b( p_suppressErrorMsg));
	if( p_ptrIsVersioned)
		*p_ptrIsVersioned = b2vb( versioned);

	return S_OK;
#else
	return E_NOTIMPL;
#endif
}

STDMETHODIMP CSvnExec::IsLocked(BSTR p_path, VARIANT_BOOL* p_ptrIsLocked, BSTR* p_ptrLockHolder)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

#if(USESVN)
	std::string ph, holder;
	CopyTo( p_path, ph);
	bool locked = m_impl->isLockedByUser( ph, holder);// TODO: Add your implementation code here

	if( p_ptrIsLocked)  // valid pointer
		*p_ptrIsLocked = b2vb( locked);

	if( p_ptrLockHolder && locked) // if it is locked, there is a holder
		CopyTo( holder, p_ptrLockHolder);

	return S_OK;
#else
	return E_NOTIMPL;
#endif
}

STDMETHODIMP CSvnExec::Init(BSTR p_username, BSTR p_password)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

#if(USESVN)
	std::string un, pw;
	CopyTo( p_username, un);
	CopyTo( p_password, pw);
	m_impl = new HiClient( un, pw);

	return m_impl? S_OK: E_FAIL;
#else
	return E_NOTIMPL;
#endif
}

STDMETHODIMP CSvnExec::ReplaceUserName(BSTR p_userName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

#if(USESVN)
	std::string un;
	CopyTo( p_userName, un);
	m_impl->replaceUserName( un);

	return S_OK;
#else
	return E_NOTIMPL;
#endif
}

STDMETHODIMP CSvnExec::Logging(VARIANT_BOOL p_onoff, BSTR p_logFile)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

#if(USESVN)
	std::string logfile;
	CopyTo( p_logFile, logfile);
	m_impl->setLog( vb2b( p_onoff), logfile);

	return S_OK;
#else
	return E_NOTIMPL;
#endif
}

STDMETHODIMP CSvnExec::IsUpToDate(BSTR p_path, VARIANT_BOOL* p_upToDate)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

#if(USESVN)
	bool        out_of_date           = false;
	bool        repo_entry_modified   = false;

	std::string ph;
	CopyTo( p_path, ph);
	bool succ = m_impl->statusOnServer( ph, false, std::string(), &out_of_date, &repo_entry_modified);
	ASSERT( succ);

	if( p_upToDate)
		*p_upToDate = b2vb( out_of_date);

	return S_OK;
#else
	return E_NOTIMPL;
#endif
}

STDMETHODIMP CSvnExec::BulkUnLock( VARIANT p_pathVec, VARIANT_BOOL* p_ptrSuccess)
{
	std::vector< std::string> vec;
	BSTR HUGEP *pBSTR;
	HRESULT hr;

	SAFEARRAY* p_pathVecSA = p_pathVec.parray;
	// Get a pointer to the elements of the array.
	hr = SafeArrayAccessData( p_pathVecSA, (void HUGEP* FAR*)&pBSTR);
	if( SUCCEEDED(hr))
	{
		char buff[ _MAX_PATH];

		long lbound = 0;
		long ubound = 0;

		HRESULT hr0 = SafeArrayGetDim( p_pathVecSA) == 1 ? S_OK: E_FAIL;
		HRESULT hr1 = SafeArrayGetLBound( p_pathVecSA, 1, &lbound);
		HRESULT hr2 = SafeArrayGetUBound( p_pathVecSA, 1, &ubound);

		if( SUCCEEDED( hr0) && SUCCEEDED( hr1) && SUCCEEDED( hr2))
		{
			long cElements = ubound - lbound + 1;
			for( long i = 0; i < cElements; ++i)
			{
				size_t sz = wcstombs( buff, pBSTR[i], _MAX_PATH);
				if( sz != std::string::npos)
				{
					buff[ sz] = 0; // terminating null char
					vec.push_back( buff);
				}
			}
		}
		SafeArrayUnaccessData( p_pathVecSA);
		SafeArrayDestroy( p_pathVec.parray);
	}

#if(USESVN)
	bool succ = m_impl->unLock( vec);
	if( p_ptrSuccess)
		*p_ptrSuccess = b2vb( succ);

	return S_OK;
#else
	return E_NOTIMPL;
#endif

}

STDMETHODIMP CSvnExec::SpeedLock( VARIANT targets, VARIANT_BOOL* success, BSTR* succ_msg)
{
	std::vector< std::string> vec;
	BSTR HUGEP *pBSTR;
	HRESULT hr;

	SAFEARRAY* p_pathVecSA = targets.parray;
	// Get a pointer to the elements of the array.
	hr = SafeArrayAccessData( p_pathVecSA, (void HUGEP* FAR*)&pBSTR);
	if( SUCCEEDED(hr))
	{
		char buff[ _MAX_PATH];

		long lbound = 0;
		long ubound = 0;

		HRESULT hr0 = SafeArrayGetDim( p_pathVecSA) == 1 ? S_OK: E_FAIL;
		HRESULT hr1 = SafeArrayGetLBound( p_pathVecSA, 1, &lbound);
		HRESULT hr2 = SafeArrayGetUBound( p_pathVecSA, 1, &ubound);

		if( SUCCEEDED( hr0) && SUCCEEDED( hr1) && SUCCEEDED( hr2))
		{
			long cElements = ubound - lbound + 1;
			for( long i = 0; i < cElements; ++i)
			{
				size_t sz = wcstombs( buff, pBSTR[i], _MAX_PATH);
				if( sz != std::string::npos)
				{
					buff[ sz] = 0; // terminating null char
					vec.push_back( buff);
				}
			}
		}
		SafeArrayUnaccessData( p_pathVecSA);
		SafeArrayDestroy( targets.parray);
	}

#if(USESVN)
	std::string msg;
	bool succ = m_impl->speedLock( vec, msg);
	if( success)
		*success = b2vb( succ);
	CopyTo( msg, succ_msg);

	return S_OK;
#else
	return E_NOTIMPL;
#endif

}
