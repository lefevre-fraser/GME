#pragma once

#define USESVN  1

#if(USESVN)
#define USENEON 0
#define USESERF 1

// make sure USESERF and USENEON are mutually exclusive:
#if(USENEON)
	#if(USESERF)
		#error Error: USENEON and USESERF are both true. You should not use both NEON and SERF at the same time!
	#endif
#endif

#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "shfolder.lib")
#pragma comment(lib, "ws2_32.lib")

#pragma comment(lib, "libapr.lib")
#pragma comment(lib, "libaprutil.lib")
#pragma comment(lib, "libapriconv.lib")
#pragma comment(lib, "xml.lib")

#pragma comment(lib, "libeay32.lib")
#pragma comment(lib, "ssleay32.lib")

#pragma comment(lib, "libsvn_client-1.lib")
#pragma comment(lib, "libsvn_delta-1.lib")
#pragma comment(lib, "libsvn_diff-1.lib")
#pragma comment(lib, "libsvn_fs-1.lib")
#pragma comment(lib, "libsvn_fs_fs-1.lib")
#pragma comment(lib, "libsvn_ra-1.lib")
#pragma comment(lib, "libsvn_ra_local-1.lib")
#pragma comment(lib, "libsvn_ra_svn-1.lib")
#pragma comment(lib, "libsvn_repos-1.lib")
#pragma comment(lib, "libsvn_subr-1.lib")
#pragma comment(lib, "libsvn_wc-1.lib")

#ifdef _DEBUG
	#pragma comment(lib, "zlibstatD.lib")
#else
	#pragma comment(lib, "zlibstat.lib")
#endif


#if(USENEON)
	#pragma comment(lib, "libsvn_ra_dav-1.lib")
	#ifdef _DEBUG
		#pragma comment(lib, "libNeonD.lib")
	#else
		#pragma comment(lib, "libNeon.lib")
		#pragma message( "in this case set msvcrtd.lib with the NODEFAULTLIB linker option")
	#endif
#endif

#if(USESERF)
	#pragma comment(lib, "libsvn_ra_serf-1.lib")
	#pragma comment(lib, "serf.lib")
#endif

#endif