#include "StdAfx.h"
#include "HiClient.h"
#include <fstream>

#if(USESVN)
#include "Pool.h"
#include "svn_wc.h"
#include "svn_dirent_uri.h"

HiClient::HiClient( const std::string& p_userName, const std::string& p_passWord)
	: Client( p_userName, p_passWord)
	, CallLogger()
{
}

HiClient::~HiClient(void)
{
}

void HiClient::replaceUserName( const std::string& p_userName)
{
	m_userName = p_userName;
}

bool HiClient::isItUs( const std::string& p_userName)
{
	log( "isItUs", p_userName);
	return m_userName == p_userName;//strcmp( m_userName.c_str(), ( p_userName?p_userName:"")) == 0; // equal means yes
}

//bool HiClient::isLocked            ( const std::string& p_path)
//{
//	log( "isLocked", p_path);
//	return isLockedByUser( p_path, std::string());
//}
//
//bool HiClient::isLockedByUs        ( const std::string& p_path)
//{
//	bool lkd, l_us, l_else;
//
//	log( "isLockedByUs", p_path);
//	lkd = isLockedByWhom( p_path, &l_us, &l_else);
//
//	return lkd && l_us;
//}
//
bool HiClient::isLockedByOthers    ( const std::string& p_path)
{
	bool lkd, l_us, l_else;

	log( "isLockedByOthers", p_path);
	lkd = isLockedByWhom( p_path, &l_us, &l_else);

	return lkd && l_else;
}

bool HiClient::isLockedByWhom      ( const std::string& p_path, bool * p_us, bool * p_else)
{
	ASSERT( p_us);
	ASSERT( p_else);

	std::string    uname;
	bool           lockd = false;

	log( "isLockedByWhom", p_path);
	lockd = isLockedByUser( p_path, uname);

	*p_us   = isItUs( uname);
	*p_else = !*p_us;

	return lockd;
}

bool HiClient::isLockedByUser      ( const std::string& p_path, std::string& p_username)
{
	Pool reqPool;

	bool res = false;
	ClientUtil::InfoHelp::InfoVec inf;

	log( "isLockedByUser", p_path + p_username);
	bool suc = info2Qck( p_path.c_str(), false, inf);
	ASSERT( suc);
	ASSERT( inf.size() == 1);

	for( ClientUtil::InfoHelp::InfoVecConIter it = inf.begin(), en = inf.end(); suc && it != en; ++it)
	{
#if(USESERF)
		if( it->m_info && it->m_info->lock && it->m_info->lock->token) // it seems that lock->token != 0 means for SERF the locked status
		{ // while for neon the lock != 0 means there is lock
			// locked
			res = true;
			
			// by whom
			ASSERT( it->m_info->lock->owner);
			if( it->m_info->lock->owner)
				p_username = it->m_info->lock->owner;
			else
				p_username = "";
		}
#else // for all other cases: 'svn://', 'svn+ssh://' or 'https://' with USENEON (USENEON could be 1 or 0) this would work:
		if( it->m_info && it->m_info->lock)
		{
			// locked
			res = true;
			
			// by whom
			ASSERT( it->m_info->lock->owner);
			if( it->m_info->lock->owner)
				p_username = it->m_info->lock->owner;
			else
				p_username = "";
		}
#endif
	}

	return res;
}

bool HiClient::isVersioned         ( const std::string& p_path, bool p_isADir /*= false*/, bool p_suppressErrorMsg /*= false*/)
{
	Pool reqPool;

	log( "isVersioned", p_path + (p_isADir?" dir ": " file "));
	ClientUtil::InfoHelp::InfoVec inf;
	// PETER - SVNSPEEDHACK BEGIN
	// bool res = info2Qck( p_path.c_str(), false, inf, p_suppressErrorMsg);
	bool res =  sub_info2( p_path.c_str(), Revision(false, false), Revision(false, false), false, inf, p_suppressErrorMsg);
	// PETER - SVNSPEEDHACK BEGIN
	return res;
}

bool HiClient::info                ( const std::string& p_path, bool p_recursive, bool p_assembleInfoMessage, std::string& p_resultMsg, std::string& p_lastChangingAuthor, std::string& p_lockOwner)
{
	Pool reqPool;

	bool rv = false;
	std::string msg;
	std::string aut;
	std::string own;

	log( "info", p_path);
	ClientUtil::InfoHelp::InfoVec inf;
	if( sub_info2( p_path.c_str(), Revision(), Revision(), p_recursive, inf, true)) // non-recursive info only
	{
		rv = true;

		if( 1)
		{
			msg = "After issuing 'svn info "; msg += ClientUtil::charstar2str( p_path.c_str(), "Url"); msg += "'";
			for( ClientUtil::InfoHelp::InfoVecConIter it = inf.begin(), en = inf.end(); it != en; ++it)
			{
				msg.append( "\nI know about: '");
				msg.append( ClientUtil::charstar2str( it->m_path, "Path"));
				msg.append( "' the following:");
				if( it->m_info)
				{
					if( !aut.empty()) aut.append( ", "); // if multiple entries in inf, then separate authors by ,

					msg.append( "\n\tLast Changed Author: "); 
					aut.append( ClientUtil::charstar2str( it->m_info->last_changed_author, "Author"));
					msg.append( ClientUtil::charstar2str( it->m_info->last_changed_author, "Author"));

					msg.append( "\n\tVersioned as (URL): "); 
					msg.append( ClientUtil::charstar2str( it->m_info->URL, "Url"));
#if(USESERF)
					if( it->m_info->lock && it->m_info->lock->token)
					{
						msg.append( "\n\tLocked by "); 
						if( !own.empty()) own.append( ", "); // if multiple entries in inf, then separate owners by ,

						own.append( ClientUtil::charstar2str( it->m_info->lock->owner, "LockOwner"));
						msg.append( ClientUtil::charstar2str( it->m_info->lock->owner, "LockOwner"));
					}
					else
						msg.append( "\n\tNot Locked");

#else // for all other cases: 'svn://', 'svn+ssh://' or 'https://' with USENEON (USENEON could be 1 or 0) this would work:

					if( it->m_info->lock)
					{
						msg.append( "\n\tLocked by "); 
						if( !own.empty()) own.append( ", "); // if multiple entries in inf, then separate owners by ,

						own.append( ClientUtil::charstar2str( it->m_info->lock->owner, "LockOwner"));
						msg.append( ClientUtil::charstar2str( it->m_info->lock->owner, "LockOwner"));
					}
					else
						msg.append( "\n\tNot Locked");
#endif
				}
				else 
					msg.append( "No detailed info present for item");
			}
		}
	} 
	else 
	{
		rv = false;

		if( p_assembleInfoMessage)
		{
			msg.append( "svn info command failed");
		}
	}

	if( p_assembleInfoMessage)
		p_resultMsg = msg;

	p_lastChangingAuthor = aut;
	p_lockOwner          = own;
	return rv;
}

bool HiClient::tryLock             ( const std::string& p_path)
{
	log( "tryLock", p_path);

	bool res = false;
	if( isLockedByOthers( p_path)) return res;

	Pool reqPool;

	res = sub_lock( Targets( p_path.c_str()), /*comment =*/ "nc" , /*force =*/ false );
	return res;
}

bool HiClient::unLock              ( const std::string& p_path)
{
	log( "unLock", p_path);

	Pool reqPool;

	return sub_unlock( Targets( p_path.c_str()));

}

bool HiClient::unLock              ( const std::vector< std::string> & p_pathVec)
{
	if( p_pathVec.size() == 0) return false;
	log( "unLockVec", p_pathVec.front());

	Pool reqPool;
	Targets tgts( p_pathVec.front().c_str());
	std::vector< std::string>::const_iterator it = p_pathVec.begin();
	std::vector< std::string>::const_iterator en = p_pathVec.end();
	for( ++it; it != en; ++it)      // safe to perform ++it in the initialize phase, since it's not empty
		tgts.add( (*it).c_str());

	return sub_unlock( tgts);
}

bool HiClient::lockableProp        ( const std::string& p_path)
{
	log( "lockableProp", p_path);

	Pool reqPool;

	return sub_propertySet( p_path.c_str(), "svn:needs-lock", /*value =*/ "na", /*recurse =*/ false, /*force =*/ false );
}

bool HiClient::getLatest           ( const std::string& p_path)
{
	log( "getLatest", p_path);

	Pool reqPool;

	UPDATE_RES res;
	bool succ = sub_update( Targets( p_path.c_str()), Revision(), /*recurse =*/ true, /*ignoreExt =*/ false, res);
	return succ;
}

bool HiClient::lightCheckOut( const std::string& p_path, const std::string& p_localDir)
{
	log( "checkOut", p_path);

	Pool reqPool;

	return 0 < sub_checkout( p_path.c_str(), p_localDir.c_str(), Revision(), Revision(), /*recurse =*/ true, /*ignoreExt =*/ false);
}

bool HiClient::commitAll           ( const std::string& p_path, bool p_keepCheckedOut)
{
	log( "commitAll", p_path);

	Pool requestPool;

	Targets tgt( p_path.c_str()); // commit might return -1 if there were no things to commit (diff was 0)
	return 0 < sub_commit( tgt, "no message", /*recurse =*/ true, /*noUnlock =*/ p_keepCheckedOut);
}

bool HiClient::add                 ( const std::string& p_path, bool p_recursive)
{
	log( "add", p_path);

	Pool reqPool;

	return 0 < sub_add( p_path.c_str(), p_recursive);
}

bool HiClient::mkDirOnServer       ( const std::string& p_path)
{
	log( "mkDirOnServer", p_path);

	Pool reqPool;

	return 0 < sub_mkdir2( Targets( p_path.c_str()), "nm");
}

bool HiClient::cleanup( const std::string& p_path)
{
	log( "cleanup", p_path);

	Pool reqPool;
	
	return sub_cleanup( p_path.c_str());
}

bool HiClient::resolve( const std::string& p_path, bool p_recursive)
{
	log( "resolve", p_path);

	Pool reqPool;

	return sub_resolved( p_path.c_str(), p_recursive);
}

bool HiClient::status( const std::string& p_path, bool p_assembleStatusMsg, std::string& p_statMsg)
{
	log( "status", p_path);

	Pool reqPool;

	bool        rv = false;
	std::string msg;

	ClientUtil::StatusExtInfoVec vec;
	vec = sub_extended_status( p_path.c_str(), false /* on_server*/);
	if( !vec.empty())
	{
		rv = true;

		if( p_assembleStatusMsg)
		{
			msg = "Svn status " + p_path + " command resulted in:\n";
			for( ClientUtil::StatusExtInfoVec::iterator it = vec.begin(); it != vec.end(); ++it)
			{
				//const char *                   m_path;
				//svn_wc_status2_t *             m_status;

				if( !it->m_status)
					msg.append( "Null status");
				else
				{
					std::string st;
					switch( it->m_status->text_status) {
					//case items copied from enum svn_wc_status_kind, svn_wc.h
					case svn_wc_status_none:        st += "Not exists "; break; /** does not exist */
					case svn_wc_status_unversioned: st += "Unversioned"; break; /** is not a versioned thing in this wc */
					case svn_wc_status_normal:      st += "Normal     "; break; /** exists, but uninteresting */
					case svn_wc_status_added:       st += "Added      "; break; /** is scheduled for addition */
					case svn_wc_status_missing:     st += "Missing    "; break; /** under v.c., but is missing */
					case svn_wc_status_deleted:     st += "Deleted    "; break; /** scheduled for deletion */
					case svn_wc_status_replaced:    st += "Replaced   "; break; /** was deleted and then re-added */
					case svn_wc_status_modified:    st += "Modified   "; break; /** text or props have been modified */
					case svn_wc_status_merged:      st += "Merged     "; break; /** local mods received repos mods */
					case svn_wc_status_conflicted:  st += "Conflicted "; break; /** local mods received conflicting repos mods */
					case svn_wc_status_ignored:     st += "Ignored    "; break; /** is unversioned but configured to be ignored */
					case svn_wc_status_obstructed:  st += "Obstructed "; break; /** an unversioned resource is in the way of the versioned resource */
					case svn_wc_status_external:    st += "External   "; break; /** an unversioned path populated by an svn:externals property */
					case svn_wc_status_incomplete:  st += "Incomplete "; break; /** a directory doesn't contain a complete entries list */
					default:                        st += "Unknown    ";
					};

					msg.append( st);
				}
				msg.append( " ");
				msg.append( ClientUtil::charstar2str( it->m_path, "Path"));
				if( it->m_status && it->m_status->locked)
					msg.append( " locked");
				if( it->m_status && it->m_status->repos_lock)
					msg.append( std::string( " by ") + ClientUtil::charstar2str( it->m_status->repos_lock->owner, "Owner"));
				msg.append( "\n");
			}
			p_statMsg = msg;
		}
	}
	else // vec.empty()
	{
		if( p_assembleStatusMsg)
			p_statMsg = "svn status command failed";
	}
	return rv;
}


bool HiClient::statusOnServer( const std::string& p_path, bool p_assembleStatusMsg, std::string& p_statMsg, bool* p_outOfDate, bool *p_repoEntryModified)
{
	log( "statusOnServer", p_path);

	Pool reqPool;

	bool        rv = false;
	std::string msg;

	ClientUtil::StatusExtInfoVec vec;
	vec = sub_extended_status( p_path.c_str(), true /* on_server*/);
	if( !vec.empty())
	{
		rv = true;

		msg = "Svn status " + p_path + " command resulted in:\n";
		for( ClientUtil::StatusExtInfoVec::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			//const char *                   m_path;
			//svn_wc_status2_t *             m_status;

			ASSERT( it->m_status);
			if( it->m_status) 
			{

				bool is_repos_text_status_modified = it->m_status->repos_text_status == svn_wc_status_modified;
				bool is_local_copy_out_of_date     = it->m_status->ood_last_cmt_rev != SVN_INVALID_REVNUM && it->m_status->entry->revision < it->m_status->ood_last_cmt_rev;

				if( p_outOfDate)               // valid ptr
					*p_outOfDate = is_local_copy_out_of_date;
				if( p_repoEntryModified)       // valid ptr
					*p_repoEntryModified = is_repos_text_status_modified;

				if( p_assembleStatusMsg)
				{
					if( 1)
					{
						std::string st;
						switch( it->m_status->text_status) {
						//case items copied from enum svn_wc_status_kind, svn_wc.h
						case svn_wc_status_none:        st += "Not exists "; break; /** does not exist */
						case svn_wc_status_unversioned: st += "Unversioned"; break; /** is not a versioned thing in this wc */
						case svn_wc_status_normal:      st += "Normal     "; break; /** exists, but uninteresting */
						case svn_wc_status_added:       st += "Added      "; break; /** is scheduled for addition */
						case svn_wc_status_missing:     st += "Missing    "; break; /** under v.c., but is missing */
						case svn_wc_status_deleted:     st += "Deleted    "; break; /** scheduled for deletion */
						case svn_wc_status_replaced:    st += "Replaced   "; break; /** was deleted and then re-added */
						case svn_wc_status_modified:    st += "Modified   "; break; /** text or props have been modified */
						case svn_wc_status_merged:      st += "Merged     "; break; /** local mods received repos mods */
						case svn_wc_status_conflicted:  st += "Conflicted "; break; /** local mods received conflicting repos mods */
						case svn_wc_status_ignored:     st += "Ignored    "; break; /** is unversioned but configured to be ignored */
						case svn_wc_status_obstructed:  st += "Obstructed "; break; /** an unversioned resource is in the way of the versioned resource */
						case svn_wc_status_external:    st += "External   "; break; /** an unversioned path populated by an svn:externals property */
						case svn_wc_status_incomplete:  st += "Incomplete "; break; /** a directory doesn't contain a complete entries list */
						default:                        st += "Unknown    ";
						};

						msg.append( st);
					}

					if( is_local_copy_out_of_date)
						msg.append( " [Local copy out of date]");

					if( is_repos_text_status_modified)
						msg.append( " [Server copy modified]");

					msg.append( " ");
					msg.append( ClientUtil::charstar2str( it->m_path, "Path"));

					if( it->m_status->locked)
						msg.append( " locked");
					if( it->m_status->repos_lock)
						msg.append( std::string( " by ") + ClientUtil::charstar2str( it->m_status->repos_lock->owner, "Owner"));

					msg.append( "\n");
				}
			}
			else
				msg.append( "Null status");
		}
		if( p_assembleStatusMsg)
			p_statMsg = msg;
	}
	else // vec.empty()
	{
		if( p_assembleStatusMsg)
			p_statMsg = "svn status command failed";
	}
	return rv;
}

bool HiClient::speedLock( const std::vector< std::string> & pathVec, std::string &msg)
{
	if( pathVec.size() == 0) return true;
	log( "speedLock", pathVec.front());

	Pool requestPool;

	svn_error_t *err;
	apr_array_header_t* targets;
	
	targets = apr_array_make( requestPool.pool(), pathVec.size(), sizeof(const char *));
	for( std::vector< std::string>::size_type i = 0; i < pathVec.size(); ++i) {
		const svn_wc_entry_t *entry;
		const char *dirent;
		const char *pathent;
		svn_wc_adm_access_t *adm_access;

		pathent = svn_dirent_internal_style(pathVec[i].c_str(), requestPool.pool());
		dirent = svn_dirent_dirname( pathent, requestPool.pool());
		err = svn_wc_adm_open( &adm_access, NULL, dirent, FALSE, FALSE, requestPool.pool());
		if (err)
		{
			char errbuff[BUFSIZ];
			const char* errbuff2 = svn_err_best_message(err, errbuff, BUFSIZ);
			msg.append(errbuff2 ? errbuff2 : errbuff);
			return false;
		}


		err = svn_wc_entry( &entry, pathent, adm_access, FALSE, requestPool.pool());
		if (err)
		{
			char errbuff[BUFSIZ];
			const char* errbuff2 = svn_err_best_message(err, errbuff, BUFSIZ);
			msg.append(errbuff2 ? errbuff2 : errbuff);
			return false;
		}

		err = svn_wc_adm_close( adm_access);
		if (err)
		{
			char errbuff[BUFSIZ];
			const char* errbuff2 = svn_err_best_message(err, errbuff, BUFSIZ);
			msg.append(errbuff2 ? errbuff2 : errbuff);
			return false;
		}

		if (entry && !entry->lock_token) {
			const char ** ptr = (const char**)apr_array_push(targets);
			*ptr = pathent;
		}
	}

	svn_client_ctx_t *ctx = getContext(NULL);
	if(ctx == NULL)
	{
		msg.append("Unable to create subversion client context");
		return false;
	}

	m_notify2->m_msg.clear();
	m_notify2->m_OK = true;

	err = svn_client_lock(targets, "", FALSE, ctx, requestPool.pool());
  
	if (err)
    {
		char errbuff[BUFSIZ];
		const char* errbuff2 = svn_err_best_message(err, errbuff, BUFSIZ);
		msg.append(errbuff2 ? errbuff2 : errbuff);
		return false;
    }

	if (! m_notify2->m_OK ) {
		msg.append(m_notify2->m_msg);
		return false;
	}
	
	return true;
}

//#if(0)
//			msg = "After issuing 'svn info "; msg += ClientUtil::charstar2str( p_path.c_str(), "Url"); msg += "'";
//			for( ClientUtil::InfoHelp::InfoVecConIter it = inf.begin(), en = inf.end(); it != en; ++it)
//			{
//				msg.append( "\nI know about: '");
//				msg.append( ClientUtil::charstar2str( it->m_path, "Path"));
//				msg.append( "' the following:");
//				if( it->m_info)
//				{
//					if( !aut.empty()) aut.append( ", "); // if multiple entries in inf, then separate authors by ,
//
//					msg.append( "\n\tLast Changed Author: "); 
//					aut.append( ClientUtil::charstar2str( it->m_info->last_changed_author, "Author"));
//					msg.append( ClientUtil::charstar2str( it->m_info->last_changed_author, "Author"));
//
//					msg.append( "\n\tVersioned as (URL): "); 
//					msg.append( ClientUtil::charstar2str( it->m_info->URL, "Url"));
//					
//					if( it->m_info->lock)
//					{
//						msg.append( "\n\tLocked by "); 
//						if( !own.empty()) own.append( ", "); // if multiple entries in inf, then separate owners by ,
//
//						own.append( ClientUtil::charstar2str( it->m_info->lock->owner, "LockOwner"));
//						msg.append( ClientUtil::charstar2str( it->m_info->lock->owner, "LockOwner"));
//					}
//					else
//						msg.append( "\n\tNot Locked");
//				}
//				else 
//					msg.append( "No detailed info present for item");
//			}
//#endif

#endif