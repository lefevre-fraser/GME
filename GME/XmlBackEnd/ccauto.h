/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Apr 28 11:19:27 2004
 */
/* Compiler settings for ccauto.IDL:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __ccauto_h__
#define __ccauto_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IClearCase_FWD_DEFINED__
#define __IClearCase_FWD_DEFINED__
typedef interface IClearCase IClearCase;
#endif 	/* __IClearCase_FWD_DEFINED__ */


#ifndef __ICCVOBObject_FWD_DEFINED__
#define __ICCVOBObject_FWD_DEFINED__
typedef interface ICCVOBObject ICCVOBObject;
#endif 	/* __ICCVOBObject_FWD_DEFINED__ */


#ifndef __ICCActivity_FWD_DEFINED__
#define __ICCActivity_FWD_DEFINED__
typedef interface ICCActivity ICCActivity;
#endif 	/* __ICCActivity_FWD_DEFINED__ */


#ifndef __ICCAttribute_FWD_DEFINED__
#define __ICCAttribute_FWD_DEFINED__
typedef interface ICCAttribute ICCAttribute;
#endif 	/* __ICCAttribute_FWD_DEFINED__ */


#ifndef __ICCAttributeType_FWD_DEFINED__
#define __ICCAttributeType_FWD_DEFINED__
typedef interface ICCAttributeType ICCAttributeType;
#endif 	/* __ICCAttributeType_FWD_DEFINED__ */


#ifndef __ICCLock_FWD_DEFINED__
#define __ICCLock_FWD_DEFINED__
typedef interface ICCLock ICCLock;
#endif 	/* __ICCLock_FWD_DEFINED__ */


#ifndef __ICCHistoryRecord_FWD_DEFINED__
#define __ICCHistoryRecord_FWD_DEFINED__
typedef interface ICCHistoryRecord ICCHistoryRecord;
#endif 	/* __ICCHistoryRecord_FWD_DEFINED__ */


#ifndef __ICCVOB_FWD_DEFINED__
#define __ICCVOB_FWD_DEFINED__
typedef interface ICCVOB ICCVOB;
#endif 	/* __ICCVOB_FWD_DEFINED__ */


#ifndef __ICCAttributeTypes_FWD_DEFINED__
#define __ICCAttributeTypes_FWD_DEFINED__
typedef interface ICCAttributeTypes ICCAttributeTypes;
#endif 	/* __ICCAttributeTypes_FWD_DEFINED__ */


#ifndef __ICCBranchType_FWD_DEFINED__
#define __ICCBranchType_FWD_DEFINED__
typedef interface ICCBranchType ICCBranchType;
#endif 	/* __ICCBranchType_FWD_DEFINED__ */


#ifndef __ICCFile_FWD_DEFINED__
#define __ICCFile_FWD_DEFINED__
typedef interface ICCFile ICCFile;
#endif 	/* __ICCFile_FWD_DEFINED__ */


#ifndef __ICCVersion_FWD_DEFINED__
#define __ICCVersion_FWD_DEFINED__
typedef interface ICCVersion ICCVersion;
#endif 	/* __ICCVersion_FWD_DEFINED__ */


#ifndef __ICCView_FWD_DEFINED__
#define __ICCView_FWD_DEFINED__
typedef interface ICCView ICCView;
#endif 	/* __ICCView_FWD_DEFINED__ */


#ifndef __ICCUCMObject_FWD_DEFINED__
#define __ICCUCMObject_FWD_DEFINED__
typedef interface ICCUCMObject ICCUCMObject;
#endif 	/* __ICCUCMObject_FWD_DEFINED__ */


#ifndef __ICCStream_FWD_DEFINED__
#define __ICCStream_FWD_DEFINED__
typedef interface ICCStream ICCStream;
#endif 	/* __ICCStream_FWD_DEFINED__ */


#ifndef __ICCProjectVOB_FWD_DEFINED__
#define __ICCProjectVOB_FWD_DEFINED__
typedef interface ICCProjectVOB ICCProjectVOB;
#endif 	/* __ICCProjectVOB_FWD_DEFINED__ */


#ifndef __ICCBaseline_FWD_DEFINED__
#define __ICCBaseline_FWD_DEFINED__
typedef interface ICCBaseline ICCBaseline;
#endif 	/* __ICCBaseline_FWD_DEFINED__ */


#ifndef __ICCActivities_FWD_DEFINED__
#define __ICCActivities_FWD_DEFINED__
typedef interface ICCActivities ICCActivities;
#endif 	/* __ICCActivities_FWD_DEFINED__ */


#ifndef __ICCComponent_FWD_DEFINED__
#define __ICCComponent_FWD_DEFINED__
typedef interface ICCComponent ICCComponent;
#endif 	/* __ICCComponent_FWD_DEFINED__ */


#ifndef __ICCElement_FWD_DEFINED__
#define __ICCElement_FWD_DEFINED__
typedef interface ICCElement ICCElement;
#endif 	/* __ICCElement_FWD_DEFINED__ */


#ifndef __ICCCheckedOutFile_FWD_DEFINED__
#define __ICCCheckedOutFile_FWD_DEFINED__
typedef interface ICCCheckedOutFile ICCCheckedOutFile;
#endif 	/* __ICCCheckedOutFile_FWD_DEFINED__ */


#ifndef __ICCTrigger_FWD_DEFINED__
#define __ICCTrigger_FWD_DEFINED__
typedef interface ICCTrigger ICCTrigger;
#endif 	/* __ICCTrigger_FWD_DEFINED__ */


#ifndef __ICCTriggerType_FWD_DEFINED__
#define __ICCTriggerType_FWD_DEFINED__
typedef interface ICCTriggerType ICCTriggerType;
#endif 	/* __ICCTriggerType_FWD_DEFINED__ */


#ifndef __ICCTriggerTypeBuilder_FWD_DEFINED__
#define __ICCTriggerTypeBuilder_FWD_DEFINED__
typedef interface ICCTriggerTypeBuilder ICCTriggerTypeBuilder;
#endif 	/* __ICCTriggerTypeBuilder_FWD_DEFINED__ */


#ifndef __ICCHyperlinkType_FWD_DEFINED__
#define __ICCHyperlinkType_FWD_DEFINED__
typedef interface ICCHyperlinkType ICCHyperlinkType;
#endif 	/* __ICCHyperlinkType_FWD_DEFINED__ */


#ifndef __ICCLabelType_FWD_DEFINED__
#define __ICCLabelType_FWD_DEFINED__
typedef interface ICCLabelType ICCLabelType;
#endif 	/* __ICCLabelType_FWD_DEFINED__ */


#ifndef __ICCTriggers_FWD_DEFINED__
#define __ICCTriggers_FWD_DEFINED__
typedef interface ICCTriggers ICCTriggers;
#endif 	/* __ICCTriggers_FWD_DEFINED__ */


#ifndef __ICCStreams_FWD_DEFINED__
#define __ICCStreams_FWD_DEFINED__
typedef interface ICCStreams ICCStreams;
#endif 	/* __ICCStreams_FWD_DEFINED__ */


#ifndef __ICCComponents_FWD_DEFINED__
#define __ICCComponents_FWD_DEFINED__
typedef interface ICCComponents ICCComponents;
#endif 	/* __ICCComponents_FWD_DEFINED__ */


#ifndef __ICCFolder_FWD_DEFINED__
#define __ICCFolder_FWD_DEFINED__
typedef interface ICCFolder ICCFolder;
#endif 	/* __ICCFolder_FWD_DEFINED__ */


#ifndef __ICCProjects_FWD_DEFINED__
#define __ICCProjects_FWD_DEFINED__
typedef interface ICCProjects ICCProjects;
#endif 	/* __ICCProjects_FWD_DEFINED__ */


#ifndef __ICCProject_FWD_DEFINED__
#define __ICCProject_FWD_DEFINED__
typedef interface ICCProject ICCProject;
#endif 	/* __ICCProject_FWD_DEFINED__ */


#ifndef __ICCProjectPolicy_FWD_DEFINED__
#define __ICCProjectPolicy_FWD_DEFINED__
typedef interface ICCProjectPolicy ICCProjectPolicy;
#endif 	/* __ICCProjectPolicy_FWD_DEFINED__ */


#ifndef __ICCBaselines_FWD_DEFINED__
#define __ICCBaselines_FWD_DEFINED__
typedef interface ICCBaselines ICCBaselines;
#endif 	/* __ICCBaselines_FWD_DEFINED__ */


#ifndef __ICCFolders_FWD_DEFINED__
#define __ICCFolders_FWD_DEFINED__
typedef interface ICCFolders ICCFolders;
#endif 	/* __ICCFolders_FWD_DEFINED__ */


#ifndef __ICCViews_FWD_DEFINED__
#define __ICCViews_FWD_DEFINED__
typedef interface ICCViews ICCViews;
#endif 	/* __ICCViews_FWD_DEFINED__ */


#ifndef __ICCBranch_FWD_DEFINED__
#define __ICCBranch_FWD_DEFINED__
typedef interface ICCBranch ICCBranch;
#endif 	/* __ICCBranch_FWD_DEFINED__ */


#ifndef __ICCVersions_FWD_DEFINED__
#define __ICCVersions_FWD_DEFINED__
typedef interface ICCVersions ICCVersions;
#endif 	/* __ICCVersions_FWD_DEFINED__ */


#ifndef __ICCLabel_FWD_DEFINED__
#define __ICCLabel_FWD_DEFINED__
typedef interface ICCLabel ICCLabel;
#endif 	/* __ICCLabel_FWD_DEFINED__ */


#ifndef __ICCLabels_FWD_DEFINED__
#define __ICCLabels_FWD_DEFINED__
typedef interface ICCLabels ICCLabels;
#endif 	/* __ICCLabels_FWD_DEFINED__ */


#ifndef __ICCBranches_FWD_DEFINED__
#define __ICCBranches_FWD_DEFINED__
typedef interface ICCBranches ICCBranches;
#endif 	/* __ICCBranches_FWD_DEFINED__ */


#ifndef __ICCBranchTypes_FWD_DEFINED__
#define __ICCBranchTypes_FWD_DEFINED__
typedef interface ICCBranchTypes ICCBranchTypes;
#endif 	/* __ICCBranchTypes_FWD_DEFINED__ */


#ifndef __ICCHyperlink_FWD_DEFINED__
#define __ICCHyperlink_FWD_DEFINED__
typedef interface ICCHyperlink ICCHyperlink;
#endif 	/* __ICCHyperlink_FWD_DEFINED__ */


#ifndef __ICCHyperlinkTypes_FWD_DEFINED__
#define __ICCHyperlinkTypes_FWD_DEFINED__
typedef interface ICCHyperlinkTypes ICCHyperlinkTypes;
#endif 	/* __ICCHyperlinkTypes_FWD_DEFINED__ */


#ifndef __ICCLabelTypes_FWD_DEFINED__
#define __ICCLabelTypes_FWD_DEFINED__
typedef interface ICCLabelTypes ICCLabelTypes;
#endif 	/* __ICCLabelTypes_FWD_DEFINED__ */


#ifndef __ICCLocks_FWD_DEFINED__
#define __ICCLocks_FWD_DEFINED__
typedef interface ICCLocks ICCLocks;
#endif 	/* __ICCLocks_FWD_DEFINED__ */


#ifndef __ICCTriggerTypes_FWD_DEFINED__
#define __ICCTriggerTypes_FWD_DEFINED__
typedef interface ICCTriggerTypes ICCTriggerTypes;
#endif 	/* __ICCTriggerTypes_FWD_DEFINED__ */


#ifndef __ICCAttributes_FWD_DEFINED__
#define __ICCAttributes_FWD_DEFINED__
typedef interface ICCAttributes ICCAttributes;
#endif 	/* __ICCAttributes_FWD_DEFINED__ */


#ifndef __ICCHistoryRecords_FWD_DEFINED__
#define __ICCHistoryRecords_FWD_DEFINED__
typedef interface ICCHistoryRecords ICCHistoryRecords;
#endif 	/* __ICCHistoryRecords_FWD_DEFINED__ */


#ifndef __ICCHyperlinks_FWD_DEFINED__
#define __ICCHyperlinks_FWD_DEFINED__
typedef interface ICCHyperlinks ICCHyperlinks;
#endif 	/* __ICCHyperlinks_FWD_DEFINED__ */


#ifndef __ICCCheckedOutFiles_FWD_DEFINED__
#define __ICCCheckedOutFiles_FWD_DEFINED__
typedef interface ICCCheckedOutFiles ICCCheckedOutFiles;
#endif 	/* __ICCCheckedOutFiles_FWD_DEFINED__ */


#ifndef __ICCCheckedOutFileQuery_FWD_DEFINED__
#define __ICCCheckedOutFileQuery_FWD_DEFINED__
typedef interface ICCCheckedOutFileQuery ICCCheckedOutFileQuery;
#endif 	/* __ICCCheckedOutFileQuery_FWD_DEFINED__ */


#ifndef __ICCElements_FWD_DEFINED__
#define __ICCElements_FWD_DEFINED__
typedef interface ICCElements ICCElements;
#endif 	/* __ICCElements_FWD_DEFINED__ */


#ifndef __ICCVOBs_FWD_DEFINED__
#define __ICCVOBs_FWD_DEFINED__
typedef interface ICCVOBs ICCVOBs;
#endif 	/* __ICCVOBs_FWD_DEFINED__ */


#ifndef __ICCBaselineComparison_FWD_DEFINED__
#define __ICCBaselineComparison_FWD_DEFINED__
typedef interface ICCBaselineComparison ICCBaselineComparison;
#endif 	/* __ICCBaselineComparison_FWD_DEFINED__ */


#ifndef __ICCProjectVOBs_FWD_DEFINED__
#define __ICCProjectVOBs_FWD_DEFINED__
typedef interface ICCProjectVOBs ICCProjectVOBs;
#endif 	/* __ICCProjectVOBs_FWD_DEFINED__ */


#ifndef __IClearTool_FWD_DEFINED__
#define __IClearTool_FWD_DEFINED__
typedef interface IClearTool IClearTool;
#endif 	/* __IClearTool_FWD_DEFINED__ */


#ifndef __Application_FWD_DEFINED__
#define __Application_FWD_DEFINED__

#ifdef __cplusplus
typedef class Application Application;
#else
typedef struct Application Application;
#endif /* __cplusplus */

#endif 	/* __Application_FWD_DEFINED__ */


#ifndef __ClearTool_FWD_DEFINED__
#define __ClearTool_FWD_DEFINED__

#ifdef __cplusplus
typedef class ClearTool ClearTool;
#else
typedef struct ClearTool ClearTool;
#endif /* __cplusplus */

#endif 	/* __ClearTool_FWD_DEFINED__ */


#ifndef __CCVOB_FWD_DEFINED__
#define __CCVOB_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCVOB CCVOB;
#else
typedef struct CCVOB CCVOB;
#endif /* __cplusplus */

#endif 	/* __CCVOB_FWD_DEFINED__ */


#ifndef __CCVOBs_FWD_DEFINED__
#define __CCVOBs_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCVOBs CCVOBs;
#else
typedef struct CCVOBs CCVOBs;
#endif /* __cplusplus */

#endif 	/* __CCVOBs_FWD_DEFINED__ */


#ifndef __CCView_FWD_DEFINED__
#define __CCView_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCView CCView;
#else
typedef struct CCView CCView;
#endif /* __cplusplus */

#endif 	/* __CCView_FWD_DEFINED__ */


#ifndef __CCViews_FWD_DEFINED__
#define __CCViews_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCViews CCViews;
#else
typedef struct CCViews CCViews;
#endif /* __cplusplus */

#endif 	/* __CCViews_FWD_DEFINED__ */


#ifndef __CCHistoryRecord_FWD_DEFINED__
#define __CCHistoryRecord_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCHistoryRecord CCHistoryRecord;
#else
typedef struct CCHistoryRecord CCHistoryRecord;
#endif /* __cplusplus */

#endif 	/* __CCHistoryRecord_FWD_DEFINED__ */


#ifndef __CCHistoryRecords_FWD_DEFINED__
#define __CCHistoryRecords_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCHistoryRecords CCHistoryRecords;
#else
typedef struct CCHistoryRecords CCHistoryRecords;
#endif /* __cplusplus */

#endif 	/* __CCHistoryRecords_FWD_DEFINED__ */


#ifndef __CCVOBObject_FWD_DEFINED__
#define __CCVOBObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCVOBObject CCVOBObject;
#else
typedef struct CCVOBObject CCVOBObject;
#endif /* __cplusplus */

#endif 	/* __CCVOBObject_FWD_DEFINED__ */


#ifndef __CCFile_FWD_DEFINED__
#define __CCFile_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCFile CCFile;
#else
typedef struct CCFile CCFile;
#endif /* __cplusplus */

#endif 	/* __CCFile_FWD_DEFINED__ */


#ifndef __CCElement_FWD_DEFINED__
#define __CCElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCElement CCElement;
#else
typedef struct CCElement CCElement;
#endif /* __cplusplus */

#endif 	/* __CCElement_FWD_DEFINED__ */


#ifndef __CCElements_FWD_DEFINED__
#define __CCElements_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCElements CCElements;
#else
typedef struct CCElements CCElements;
#endif /* __cplusplus */

#endif 	/* __CCElements_FWD_DEFINED__ */


#ifndef __CCVersion_FWD_DEFINED__
#define __CCVersion_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCVersion CCVersion;
#else
typedef struct CCVersion CCVersion;
#endif /* __cplusplus */

#endif 	/* __CCVersion_FWD_DEFINED__ */


#ifndef __CCVersions_FWD_DEFINED__
#define __CCVersions_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCVersions CCVersions;
#else
typedef struct CCVersions CCVersions;
#endif /* __cplusplus */

#endif 	/* __CCVersions_FWD_DEFINED__ */


#ifndef __CCCheckedOutFile_FWD_DEFINED__
#define __CCCheckedOutFile_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCCheckedOutFile CCCheckedOutFile;
#else
typedef struct CCCheckedOutFile CCCheckedOutFile;
#endif /* __cplusplus */

#endif 	/* __CCCheckedOutFile_FWD_DEFINED__ */


#ifndef __CCCheckedOutFiles_FWD_DEFINED__
#define __CCCheckedOutFiles_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCCheckedOutFiles CCCheckedOutFiles;
#else
typedef struct CCCheckedOutFiles CCCheckedOutFiles;
#endif /* __cplusplus */

#endif 	/* __CCCheckedOutFiles_FWD_DEFINED__ */


#ifndef __CCCheckedOutFileQuery_FWD_DEFINED__
#define __CCCheckedOutFileQuery_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCCheckedOutFileQuery CCCheckedOutFileQuery;
#else
typedef struct CCCheckedOutFileQuery CCCheckedOutFileQuery;
#endif /* __cplusplus */

#endif 	/* __CCCheckedOutFileQuery_FWD_DEFINED__ */


#ifndef __CCHyperlink_FWD_DEFINED__
#define __CCHyperlink_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCHyperlink CCHyperlink;
#else
typedef struct CCHyperlink CCHyperlink;
#endif /* __cplusplus */

#endif 	/* __CCHyperlink_FWD_DEFINED__ */


#ifndef __CCHyperlinks_FWD_DEFINED__
#define __CCHyperlinks_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCHyperlinks CCHyperlinks;
#else
typedef struct CCHyperlinks CCHyperlinks;
#endif /* __cplusplus */

#endif 	/* __CCHyperlinks_FWD_DEFINED__ */


#ifndef __CCHyperlinkType_FWD_DEFINED__
#define __CCHyperlinkType_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCHyperlinkType CCHyperlinkType;
#else
typedef struct CCHyperlinkType CCHyperlinkType;
#endif /* __cplusplus */

#endif 	/* __CCHyperlinkType_FWD_DEFINED__ */


#ifndef __CCHyperlinkTypes_FWD_DEFINED__
#define __CCHyperlinkTypes_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCHyperlinkTypes CCHyperlinkTypes;
#else
typedef struct CCHyperlinkTypes CCHyperlinkTypes;
#endif /* __cplusplus */

#endif 	/* __CCHyperlinkTypes_FWD_DEFINED__ */


#ifndef __CCLabel_FWD_DEFINED__
#define __CCLabel_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCLabel CCLabel;
#else
typedef struct CCLabel CCLabel;
#endif /* __cplusplus */

#endif 	/* __CCLabel_FWD_DEFINED__ */


#ifndef __CCLabels_FWD_DEFINED__
#define __CCLabels_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCLabels CCLabels;
#else
typedef struct CCLabels CCLabels;
#endif /* __cplusplus */

#endif 	/* __CCLabels_FWD_DEFINED__ */


#ifndef __CCLabelType_FWD_DEFINED__
#define __CCLabelType_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCLabelType CCLabelType;
#else
typedef struct CCLabelType CCLabelType;
#endif /* __cplusplus */

#endif 	/* __CCLabelType_FWD_DEFINED__ */


#ifndef __CCLabelTypes_FWD_DEFINED__
#define __CCLabelTypes_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCLabelTypes CCLabelTypes;
#else
typedef struct CCLabelTypes CCLabelTypes;
#endif /* __cplusplus */

#endif 	/* __CCLabelTypes_FWD_DEFINED__ */


#ifndef __CCBranch_FWD_DEFINED__
#define __CCBranch_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCBranch CCBranch;
#else
typedef struct CCBranch CCBranch;
#endif /* __cplusplus */

#endif 	/* __CCBranch_FWD_DEFINED__ */


#ifndef __CCBranches_FWD_DEFINED__
#define __CCBranches_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCBranches CCBranches;
#else
typedef struct CCBranches CCBranches;
#endif /* __cplusplus */

#endif 	/* __CCBranches_FWD_DEFINED__ */


#ifndef __CCBranchType_FWD_DEFINED__
#define __CCBranchType_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCBranchType CCBranchType;
#else
typedef struct CCBranchType CCBranchType;
#endif /* __cplusplus */

#endif 	/* __CCBranchType_FWD_DEFINED__ */


#ifndef __CCBranchTypes_FWD_DEFINED__
#define __CCBranchTypes_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCBranchTypes CCBranchTypes;
#else
typedef struct CCBranchTypes CCBranchTypes;
#endif /* __cplusplus */

#endif 	/* __CCBranchTypes_FWD_DEFINED__ */


#ifndef __CCAttribute_FWD_DEFINED__
#define __CCAttribute_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCAttribute CCAttribute;
#else
typedef struct CCAttribute CCAttribute;
#endif /* __cplusplus */

#endif 	/* __CCAttribute_FWD_DEFINED__ */


#ifndef __CCAttributes_FWD_DEFINED__
#define __CCAttributes_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCAttributes CCAttributes;
#else
typedef struct CCAttributes CCAttributes;
#endif /* __cplusplus */

#endif 	/* __CCAttributes_FWD_DEFINED__ */


#ifndef __CCAttributeType_FWD_DEFINED__
#define __CCAttributeType_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCAttributeType CCAttributeType;
#else
typedef struct CCAttributeType CCAttributeType;
#endif /* __cplusplus */

#endif 	/* __CCAttributeType_FWD_DEFINED__ */


#ifndef __CCAttributeTypes_FWD_DEFINED__
#define __CCAttributeTypes_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCAttributeTypes CCAttributeTypes;
#else
typedef struct CCAttributeTypes CCAttributeTypes;
#endif /* __cplusplus */

#endif 	/* __CCAttributeTypes_FWD_DEFINED__ */


#ifndef __CCTrigger_FWD_DEFINED__
#define __CCTrigger_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCTrigger CCTrigger;
#else
typedef struct CCTrigger CCTrigger;
#endif /* __cplusplus */

#endif 	/* __CCTrigger_FWD_DEFINED__ */


#ifndef __CCTriggers_FWD_DEFINED__
#define __CCTriggers_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCTriggers CCTriggers;
#else
typedef struct CCTriggers CCTriggers;
#endif /* __cplusplus */

#endif 	/* __CCTriggers_FWD_DEFINED__ */


#ifndef __CCTriggerType_FWD_DEFINED__
#define __CCTriggerType_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCTriggerType CCTriggerType;
#else
typedef struct CCTriggerType CCTriggerType;
#endif /* __cplusplus */

#endif 	/* __CCTriggerType_FWD_DEFINED__ */


#ifndef __CCTriggerTypes_FWD_DEFINED__
#define __CCTriggerTypes_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCTriggerTypes CCTriggerTypes;
#else
typedef struct CCTriggerTypes CCTriggerTypes;
#endif /* __cplusplus */

#endif 	/* __CCTriggerTypes_FWD_DEFINED__ */


#ifndef __CCTriggerTypeBuilder_FWD_DEFINED__
#define __CCTriggerTypeBuilder_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCTriggerTypeBuilder CCTriggerTypeBuilder;
#else
typedef struct CCTriggerTypeBuilder CCTriggerTypeBuilder;
#endif /* __cplusplus */

#endif 	/* __CCTriggerTypeBuilder_FWD_DEFINED__ */


#ifndef __CCLock_FWD_DEFINED__
#define __CCLock_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCLock CCLock;
#else
typedef struct CCLock CCLock;
#endif /* __cplusplus */

#endif 	/* __CCLock_FWD_DEFINED__ */


#ifndef __CCLocks_FWD_DEFINED__
#define __CCLocks_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCLocks CCLocks;
#else
typedef struct CCLocks CCLocks;
#endif /* __cplusplus */

#endif 	/* __CCLocks_FWD_DEFINED__ */


#ifndef __CCActivity_FWD_DEFINED__
#define __CCActivity_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCActivity CCActivity;
#else
typedef struct CCActivity CCActivity;
#endif /* __cplusplus */

#endif 	/* __CCActivity_FWD_DEFINED__ */


#ifndef __CCActivities_FWD_DEFINED__
#define __CCActivities_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCActivities CCActivities;
#else
typedef struct CCActivities CCActivities;
#endif /* __cplusplus */

#endif 	/* __CCActivities_FWD_DEFINED__ */


#ifndef __CCProjectVOB_FWD_DEFINED__
#define __CCProjectVOB_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCProjectVOB CCProjectVOB;
#else
typedef struct CCProjectVOB CCProjectVOB;
#endif /* __cplusplus */

#endif 	/* __CCProjectVOB_FWD_DEFINED__ */


#ifndef __CCProjectVOBs_FWD_DEFINED__
#define __CCProjectVOBs_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCProjectVOBs CCProjectVOBs;
#else
typedef struct CCProjectVOBs CCProjectVOBs;
#endif /* __cplusplus */

#endif 	/* __CCProjectVOBs_FWD_DEFINED__ */


#ifndef __CCUCMObject_FWD_DEFINED__
#define __CCUCMObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCUCMObject CCUCMObject;
#else
typedef struct CCUCMObject CCUCMObject;
#endif /* __cplusplus */

#endif 	/* __CCUCMObject_FWD_DEFINED__ */


#ifndef __CCProject_FWD_DEFINED__
#define __CCProject_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCProject CCProject;
#else
typedef struct CCProject CCProject;
#endif /* __cplusplus */

#endif 	/* __CCProject_FWD_DEFINED__ */


#ifndef __CCProjects_FWD_DEFINED__
#define __CCProjects_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCProjects CCProjects;
#else
typedef struct CCProjects CCProjects;
#endif /* __cplusplus */

#endif 	/* __CCProjects_FWD_DEFINED__ */


#ifndef __CCFolder_FWD_DEFINED__
#define __CCFolder_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCFolder CCFolder;
#else
typedef struct CCFolder CCFolder;
#endif /* __cplusplus */

#endif 	/* __CCFolder_FWD_DEFINED__ */


#ifndef __CCFolders_FWD_DEFINED__
#define __CCFolders_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCFolders CCFolders;
#else
typedef struct CCFolders CCFolders;
#endif /* __cplusplus */

#endif 	/* __CCFolders_FWD_DEFINED__ */


#ifndef __CCComponent_FWD_DEFINED__
#define __CCComponent_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCComponent CCComponent;
#else
typedef struct CCComponent CCComponent;
#endif /* __cplusplus */

#endif 	/* __CCComponent_FWD_DEFINED__ */


#ifndef __CCComponents_FWD_DEFINED__
#define __CCComponents_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCComponents CCComponents;
#else
typedef struct CCComponents CCComponents;
#endif /* __cplusplus */

#endif 	/* __CCComponents_FWD_DEFINED__ */


#ifndef __CCBaseline_FWD_DEFINED__
#define __CCBaseline_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCBaseline CCBaseline;
#else
typedef struct CCBaseline CCBaseline;
#endif /* __cplusplus */

#endif 	/* __CCBaseline_FWD_DEFINED__ */


#ifndef __CCBaselines_FWD_DEFINED__
#define __CCBaselines_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCBaselines CCBaselines;
#else
typedef struct CCBaselines CCBaselines;
#endif /* __cplusplus */

#endif 	/* __CCBaselines_FWD_DEFINED__ */


#ifndef __CCStream_FWD_DEFINED__
#define __CCStream_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCStream CCStream;
#else
typedef struct CCStream CCStream;
#endif /* __cplusplus */

#endif 	/* __CCStream_FWD_DEFINED__ */


#ifndef __CCStreams_FWD_DEFINED__
#define __CCStreams_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCStreams CCStreams;
#else
typedef struct CCStreams CCStreams;
#endif /* __cplusplus */

#endif 	/* __CCStreams_FWD_DEFINED__ */


#ifndef __CCBaselineComparison_FWD_DEFINED__
#define __CCBaselineComparison_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCBaselineComparison CCBaselineComparison;
#else
typedef struct CCBaselineComparison CCBaselineComparison;
#endif /* __cplusplus */

#endif 	/* __CCBaselineComparison_FWD_DEFINED__ */


#ifndef __CCProjectPolicy_FWD_DEFINED__
#define __CCProjectPolicy_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCProjectPolicy CCProjectPolicy;
#else
typedef struct CCProjectPolicy CCProjectPolicy;
#endif /* __cplusplus */

#endif 	/* __CCProjectPolicy_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __ClearCase_LIBRARY_DEFINED__
#define __ClearCase_LIBRARY_DEFINED__

/* library ClearCase */
/* [helpcontext][helpfile][helpstring][version][uuid] */ 


























































typedef /* [helpcontext][helpstring][uuid] */ 
enum __MIDL___MIDL_itf_ccauto_0000_0001
    {	ccConstraint_None	= 0,
	ccConstraint_PerElement	= 1,
	ccConstraint_PerBranch	= 2,
	ccConstraint_PerVersion	= 3
    }	CCTypeConstraint;

typedef /* [helpcontext][helpstring][uuid] */ 
enum __MIDL___MIDL_itf_ccauto_0000_0002
    {	ccScope_Ordinary	= 0,
	ccScope_LocalCopy	= 1,
	ccScope_Global	= 2
    }	CCTypeScope;

typedef /* [helpcontext][helpstring][uuid] */ 
enum __MIDL___MIDL_itf_ccauto_0000_0003
    {	ccReserved	= 0,
	ccUnreserved	= 1,
	ccTryReserved	= 2
    }	CCReservedState;

typedef /* [helpcontext][helpstring][uuid] */ 
enum __MIDL___MIDL_itf_ccauto_0000_0004
    {	ccVersion_Default	= 0,
	ccVersion_SpecificVersion	= 1
    }	CCVersionToCheckOut;

typedef /* [helpcontext][helpstring][uuid] */ 
enum __MIDL___MIDL_itf_ccauto_0000_0005
    {	ccLabelStatus_Unlabeled	= 0,
	ccLabelStatus_Incremental	= 1,
	ccLabelStatus_Full	= 2
    }	CCLabelStatus;

typedef /* [helpcontext][helpstring][uuid] */ 
enum __MIDL___MIDL_itf_ccauto_0000_0006
    {	ccKeep	= 0,
	ccRemove	= 1
    }	CCKeepState;

typedef /* [helpcontext][helpstring][uuid] */ 
enum __MIDL___MIDL_itf_ccauto_0000_0007
    {	ccFiring_PreOp	= 1,
	ccFiring_PostOp	= 2
    }	CCTriggerFiring;

typedef /* [helpcontext][helpstring][uuid] */ 
enum __MIDL___MIDL_itf_ccauto_0000_0008
    {	ccKind_Type	= 0,
	ccKind_Element	= 1,
	ccKind_AllElement	= 2,
	ccKind_UCM	= 3,
	ccKind_AllUCM	= 4
    }	CCKindOfTrigger;

typedef /* [helpcontext][helpstring][uuid] */ 
enum __MIDL___MIDL_itf_ccauto_0000_0009
    {	ccOp_MODIFY_TYPE	= 1,
	ccOp_MODIFY_ELEM	= 2,
	ccOp_MODIFY_DATA	= 3,
	ccOp_MODIFY_MD	= 4,
	ccOp_mktype	= 5,
	ccOp_rmtype	= 6,
	ccOp_rntype	= 7,
	ccOp_lock	= 8,
	ccOp_unlock	= 9,
	ccOp_checkout	= 10,
	ccOp_mkelem	= 11,
	ccOp_mkbranch	= 12,
	ccOp_checkin	= 13,
	ccOp_rmelem	= 14,
	ccOp_rmbranch	= 15,
	ccOp_rmver	= 16,
	ccOp_rmname	= 17,
	ccOp_chtype	= 18,
	ccOp_mklabel	= 19,
	ccOp_mkattr	= 20,
	ccOp_mkhlink	= 21,
	ccOp_mktrigger	= 22,
	ccOp_rmlabel	= 23,
	ccOp_rmattr	= 24,
	ccOp_rmhlink	= 25,
	ccOp_rmtrigger	= 26,
	ccOp_uncheckout	= 27,
	ccOp_protect	= 30,
	ccOp_lnname	= 32,
	ccOp_mkslink	= 33,
	ccOp_reserve	= 37,
	ccOp_unreserve	= 41,
	ccOp_chevent	= 44,
	ccOp_chmaster	= 49,
	ccOp_mkactivity	= 58,
	ccOp_UCM	= 88,
	ccOp_deliver_start	= 89,
	ccOp_deliver_complete	= 90,
	ccOp_deliver_cancel	= 91,
	ccOp_rebase_start	= 92,
	ccOp_rebase_complete	= 93,
	ccOp_rebase_cancel	= 94,
	ccOp_setactivity	= 95,
	ccOp_mkstream	= 96,
	ccOp_mkbl	= 99
    }	CCTriggerOperationKind;

typedef /* [helpcontext][helpstring][uuid] */ 
enum __MIDL___MIDL_itf_ccauto_0000_0010
    {	ccSelection_Path	= 0,
	ccSelection_SubTreeRoot	= 1,
	ccSelection_Directory	= 2,
	ccSelection_AllInVOB	= 3,
	ccSelection_AllVOBs	= 4
    }	CCPath_Selection;

typedef /* [helpcontext][helpstring][uuid] */ 
enum __MIDL___MIDL_itf_ccauto_0150_0001
    {	ccAction_Exec	= 0,
	ccAction_ExecUNIX	= 1,
	ccAction_ExecWin	= 2,
	ccAction_Mklabel	= 3,
	ccAction_Mkattr	= 4,
	ccAction_MkhlinkTo	= 5,
	ccAction_MkhlinkFrom	= 6
    }	CCTriggerActionType;

typedef /* [helpcontext][helpstring][uuid] */ 
enum __MIDL___MIDL_itf_ccauto_0150_0002
    {	ccAll_ElementTypes	= 13,
	ccAll_BranchTypes	= 14,
	ccAll_AttributeTypes	= 15,
	ccAll_HyperlinkTypes	= 16,
	ccAll_TriggerTypes	= 17,
	ccAll_LabelTypes	= 20
    }	CCTriggerTypesAll;

typedef /* [helpcontext][helpstring][uuid] */ 
enum __MIDL___MIDL_itf_ccauto_0150_0003
    {	ccSubset_Both	= 0,
	ccSubset_NotInheritance	= 1,
	ccSubset_NotAttached	= 2
    }	CCTriggerDirectorySubset;


DEFINE_GUID(LIBID_ClearCase,0xB22C7EFA,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);


#ifndef __ICCVOBObject_INTERFACE_DEFINED__
#define __ICCVOBObject_INTERFACE_DEFINED__

/* interface ICCVOBObject */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCVOBObject,0xB22C7EC9,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7EC9-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCVOBObject : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Attribute( 
            /* [in] */ BSTR AttributeType,
            /* [retval][out] */ ICCAttribute __RPC_FAR *__RPC_FAR *pAttribute) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Attributes( 
            /* [retval][out] */ ICCAttributes __RPC_FAR *__RPC_FAR *pAttributes) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Comment( 
            /* [retval][out] */ BSTR __RPC_FAR *pComment) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Comment( 
            /* [in] */ BSTR pComment) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_CreationRecord( 
            /* [retval][out] */ ICCHistoryRecord __RPC_FAR *__RPC_FAR *pHistoryRecord) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_HistoryRecords( 
            /* [in] */ ICCBranchType __RPC_FAR *pICCBranchType,
            /* [defaultvalue][optional][in] */ DATE Since,
            /* [defaultvalue][optional][in] */ BSTR User,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Minor,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL ExcludeCheckOutEvents,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL DirectoryOnly,
            /* [retval][out] */ ICCHistoryRecords __RPC_FAR *__RPC_FAR *pHistoryRecords) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Hyperlinks( 
            /* [defaultvalue][optional][in] */ BSTR HyperlinkType,
            /* [retval][out] */ ICCHyperlinks __RPC_FAR *__RPC_FAR *pHyperlinks) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_OID( 
            /* [retval][out] */ BSTR __RPC_FAR *pOID) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_VOBFamilyUUID( 
            /* [retval][out] */ BSTR __RPC_FAR *pVOBFamilyUUID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCVOBObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCVOBObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCVOBObject __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCVOBObject __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCVOBObject __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCVOBObject __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCVOBObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCVOBObject __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attribute )( 
            ICCVOBObject __RPC_FAR * This,
            /* [in] */ BSTR AttributeType,
            /* [retval][out] */ ICCAttribute __RPC_FAR *__RPC_FAR *pAttribute);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attributes )( 
            ICCVOBObject __RPC_FAR * This,
            /* [retval][out] */ ICCAttributes __RPC_FAR *__RPC_FAR *pAttributes);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Comment )( 
            ICCVOBObject __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pComment);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Comment )( 
            ICCVOBObject __RPC_FAR * This,
            /* [in] */ BSTR pComment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreationRecord )( 
            ICCVOBObject __RPC_FAR * This,
            /* [retval][out] */ ICCHistoryRecord __RPC_FAR *__RPC_FAR *pHistoryRecord);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HistoryRecords )( 
            ICCVOBObject __RPC_FAR * This,
            /* [in] */ ICCBranchType __RPC_FAR *pICCBranchType,
            /* [defaultvalue][optional][in] */ DATE Since,
            /* [defaultvalue][optional][in] */ BSTR User,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Minor,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL ExcludeCheckOutEvents,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL DirectoryOnly,
            /* [retval][out] */ ICCHistoryRecords __RPC_FAR *__RPC_FAR *pHistoryRecords);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hyperlinks )( 
            ICCVOBObject __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR HyperlinkType,
            /* [retval][out] */ ICCHyperlinks __RPC_FAR *__RPC_FAR *pHyperlinks);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OID )( 
            ICCVOBObject __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOBFamilyUUID )( 
            ICCVOBObject __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVOBFamilyUUID);
        
        END_INTERFACE
    } ICCVOBObjectVtbl;

    interface ICCVOBObject
    {
        CONST_VTBL struct ICCVOBObjectVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCVOBObject_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCVOBObject_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCVOBObject_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCVOBObject_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCVOBObject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCVOBObject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCVOBObject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCVOBObject_get_Attribute(This,AttributeType,pAttribute)	\
    (This)->lpVtbl -> get_Attribute(This,AttributeType,pAttribute)

#define ICCVOBObject_get_Attributes(This,pAttributes)	\
    (This)->lpVtbl -> get_Attributes(This,pAttributes)

#define ICCVOBObject_get_Comment(This,pComment)	\
    (This)->lpVtbl -> get_Comment(This,pComment)

#define ICCVOBObject_put_Comment(This,pComment)	\
    (This)->lpVtbl -> put_Comment(This,pComment)

#define ICCVOBObject_get_CreationRecord(This,pHistoryRecord)	\
    (This)->lpVtbl -> get_CreationRecord(This,pHistoryRecord)

#define ICCVOBObject_get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)	\
    (This)->lpVtbl -> get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)

#define ICCVOBObject_get_Hyperlinks(This,HyperlinkType,pHyperlinks)	\
    (This)->lpVtbl -> get_Hyperlinks(This,HyperlinkType,pHyperlinks)

#define ICCVOBObject_get_OID(This,pOID)	\
    (This)->lpVtbl -> get_OID(This,pOID)

#define ICCVOBObject_get_VOBFamilyUUID(This,pVOBFamilyUUID)	\
    (This)->lpVtbl -> get_VOBFamilyUUID(This,pVOBFamilyUUID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOBObject_get_Attribute_Proxy( 
    ICCVOBObject __RPC_FAR * This,
    /* [in] */ BSTR AttributeType,
    /* [retval][out] */ ICCAttribute __RPC_FAR *__RPC_FAR *pAttribute);


void __RPC_STUB ICCVOBObject_get_Attribute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOBObject_get_Attributes_Proxy( 
    ICCVOBObject __RPC_FAR * This,
    /* [retval][out] */ ICCAttributes __RPC_FAR *__RPC_FAR *pAttributes);


void __RPC_STUB ICCVOBObject_get_Attributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOBObject_get_Comment_Proxy( 
    ICCVOBObject __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pComment);


void __RPC_STUB ICCVOBObject_get_Comment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE ICCVOBObject_put_Comment_Proxy( 
    ICCVOBObject __RPC_FAR * This,
    /* [in] */ BSTR pComment);


void __RPC_STUB ICCVOBObject_put_Comment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOBObject_get_CreationRecord_Proxy( 
    ICCVOBObject __RPC_FAR * This,
    /* [retval][out] */ ICCHistoryRecord __RPC_FAR *__RPC_FAR *pHistoryRecord);


void __RPC_STUB ICCVOBObject_get_CreationRecord_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOBObject_get_HistoryRecords_Proxy( 
    ICCVOBObject __RPC_FAR * This,
    /* [in] */ ICCBranchType __RPC_FAR *pICCBranchType,
    /* [defaultvalue][optional][in] */ DATE Since,
    /* [defaultvalue][optional][in] */ BSTR User,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Minor,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL ExcludeCheckOutEvents,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL DirectoryOnly,
    /* [retval][out] */ ICCHistoryRecords __RPC_FAR *__RPC_FAR *pHistoryRecords);


void __RPC_STUB ICCVOBObject_get_HistoryRecords_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOBObject_get_Hyperlinks_Proxy( 
    ICCVOBObject __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR HyperlinkType,
    /* [retval][out] */ ICCHyperlinks __RPC_FAR *__RPC_FAR *pHyperlinks);


void __RPC_STUB ICCVOBObject_get_Hyperlinks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOBObject_get_OID_Proxy( 
    ICCVOBObject __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pOID);


void __RPC_STUB ICCVOBObject_get_OID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOBObject_get_VOBFamilyUUID_Proxy( 
    ICCVOBObject __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVOBFamilyUUID);


void __RPC_STUB ICCVOBObject_get_VOBFamilyUUID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCVOBObject_INTERFACE_DEFINED__ */






#ifndef __IClearCase_INTERFACE_DEFINED__
#define __IClearCase_INTERFACE_DEFINED__

/* interface IClearCase */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_IClearCase,0xB22C7EC6,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7EC6-5A5E-11D3-B1CD-00C04F8ECE2F")
    IClearCase : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Activity( 
            /* [in] */ BSTR Selector,
            /* [retval][out] */ ICCActivity __RPC_FAR *__RPC_FAR *pActivity) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_AttributesEmpty( 
            /* [retval][out] */ ICCAttributes __RPC_FAR *__RPC_FAR *pAttributes) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_AttributeTypesEmpty( 
            /* [retval][out] */ ICCAttributeTypes __RPC_FAR *__RPC_FAR *pAttributeTypes) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_BranchesEmpty( 
            /* [retval][out] */ ICCBranches __RPC_FAR *__RPC_FAR *pBranches) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_BranchTypesEmpty( 
            /* [retval][out] */ ICCBranchTypes __RPC_FAR *__RPC_FAR *pBranchTypes) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_CheckedOutFile( 
            /* [in] */ BSTR Path,
            /* [retval][out] */ ICCCheckedOutFile __RPC_FAR *__RPC_FAR *pCheckedOutFile) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_CheckedOutFilesEmpty( 
            /* [retval][out] */ ICCCheckedOutFiles __RPC_FAR *__RPC_FAR *pCheckedOutFiles) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CheckLicense( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateCheckedOutFileQuery( 
            /* [retval][out] */ ICCCheckedOutFileQuery __RPC_FAR *__RPC_FAR *pCheckedOutFileQuery) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateElement( 
            /* [in] */ BSTR Path,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL SetMaster,
            /* [optional][in] */ VARIANT ElementTypeName,
            /* [retval][out] */ ICCCheckedOutFile __RPC_FAR *__RPC_FAR *pCheckedOutFile) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Element( 
            /* [in] */ BSTR Path,
            /* [retval][out] */ ICCElement __RPC_FAR *__RPC_FAR *pElement) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ElementsEmpty( 
            /* [retval][out] */ ICCElements __RPC_FAR *__RPC_FAR *pElements) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_HistoryRecordsEmpty( 
            /* [retval][out] */ ICCHistoryRecords __RPC_FAR *__RPC_FAR *pHistoryRecords) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Hyperlink( 
            /* [in] */ BSTR Selector,
            /* [retval][out] */ ICCHyperlink __RPC_FAR *__RPC_FAR *pHyperlink) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_HyperlinksEmpty( 
            /* [retval][out] */ ICCHyperlinks __RPC_FAR *__RPC_FAR *pHyperlinks) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_HyperlinkTypesEmpty( 
            /* [retval][out] */ ICCHyperlinkTypes __RPC_FAR *__RPC_FAR *pHyperlinkTypes) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_IsWebGUI( 
            /* [in] */ VARIANT_BOOL rhs) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_LabelsEmpty( 
            /* [retval][out] */ ICCLabels __RPC_FAR *__RPC_FAR *pLabels) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_LabelTypesEmpty( 
            /* [retval][out] */ ICCLabelTypes __RPC_FAR *__RPC_FAR *pLabelTypes) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_LocksEmpty( 
            /* [retval][out] */ ICCLocks __RPC_FAR *__RPC_FAR *pLocks) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetAbortPrompts( void) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_TriggersEmpty( 
            /* [retval][out] */ ICCTriggers __RPC_FAR *__RPC_FAR *pTrigger) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_TriggerTypesEmpty( 
            /* [retval][out] */ ICCTriggerTypes __RPC_FAR *__RPC_FAR *pTriggerTypes) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [in] */ VARIANT Path,
            /* [retval][out] */ ICCVersion __RPC_FAR *__RPC_FAR *pVersion) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_VersionsEmpty( 
            /* [retval][out] */ ICCVersions __RPC_FAR *__RPC_FAR *pVersions) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_View( 
            /* [defaultvalue][optional][in] */ BSTR Identifier,
            /* [retval][out] */ ICCView __RPC_FAR *__RPC_FAR *pView) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Views( 
            /* [defaultvalue][optional][in] */ VARIANT_BOOL FailIfErrors,
            /* [defaultvalue][optional][in] */ BSTR Region,
            /* [retval][out] */ ICCViews __RPC_FAR *__RPC_FAR *pViews) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ViewsEmpty( 
            /* [retval][out] */ ICCViews __RPC_FAR *__RPC_FAR *pViews) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_VOB( 
            /* [in] */ BSTR Identifier,
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_VOBs( 
            /* [defaultvalue][optional][in] */ VARIANT_BOOL FailIfErrors,
            /* [defaultvalue][optional][in] */ BSTR Region,
            /* [retval][out] */ ICCVOBs __RPC_FAR *__RPC_FAR *pVOBs) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_VOBsEmpty( 
            /* [retval][out] */ ICCVOBs __RPC_FAR *__RPC_FAR *pVOBs) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ActivitiesEmpty( 
            /* [retval][out] */ ICCActivities __RPC_FAR *__RPC_FAR *pActivities) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ActivityOfVersion( 
            /* [in] */ ICCVersion __RPC_FAR *pVersion,
            /* [retval][out] */ ICCActivity __RPC_FAR *__RPC_FAR *pActivity) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Baseline( 
            /* [in] */ BSTR Selector,
            /* [retval][out] */ ICCBaseline __RPC_FAR *__RPC_FAR *pBaseline) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_BaselinesEmpty( 
            /* [retval][out] */ ICCBaselines __RPC_FAR *__RPC_FAR *pBaselines) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Component( 
            /* [in] */ BSTR Selector,
            /* [retval][out] */ ICCComponent __RPC_FAR *__RPC_FAR *pComponent) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ComponentsEmpty( 
            /* [retval][out] */ ICCComponents __RPC_FAR *__RPC_FAR *pComponents) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateBaselineComparison( 
            /* [retval][out] */ ICCBaselineComparison __RPC_FAR *__RPC_FAR *pBaselineComparison) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Folder( 
            /* [in] */ BSTR Selector,
            /* [retval][out] */ ICCFolder __RPC_FAR *__RPC_FAR *pFolder) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_FoldersEmpty( 
            /* [retval][out] */ ICCFolders __RPC_FAR *__RPC_FAR *pFolders) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IsClearCaseLT( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsClearCaseLT) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IsClearCaseLTClient( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsClearCaseLTClient) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IsClearCaseLTServer( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsClearCaseLTServer) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Project( 
            /* [in] */ BSTR Selector,
            /* [retval][out] */ ICCProject __RPC_FAR *__RPC_FAR *pProject) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ProjectsEmpty( 
            /* [retval][out] */ ICCProjects __RPC_FAR *__RPC_FAR *pProjects) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ProjectVOB( 
            /* [in] */ BSTR Identifier,
            /* [retval][out] */ ICCProjectVOB __RPC_FAR *__RPC_FAR *pProjectVOB) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ProjectVOBsEmpty( 
            /* [retval][out] */ ICCProjectVOBs __RPC_FAR *__RPC_FAR *pProjectVOBs) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Stream( 
            /* [in] */ BSTR Selector,
            /* [retval][out] */ ICCStream __RPC_FAR *__RPC_FAR *pStream) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_StreamsEmpty( 
            /* [retval][out] */ ICCStreams __RPC_FAR *__RPC_FAR *pStreams) = 0;
        
        virtual /* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get_UniversalSelector( 
            /* [in] */ ICCVOBObject __RPC_FAR *pVOBObject,
            /* [retval][out] */ BSTR __RPC_FAR *pUniversalSelector) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IClearCaseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IClearCase __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IClearCase __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IClearCase __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IClearCase __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IClearCase __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IClearCase __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IClearCase __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Activity )( 
            IClearCase __RPC_FAR * This,
            /* [in] */ BSTR Selector,
            /* [retval][out] */ ICCActivity __RPC_FAR *__RPC_FAR *pActivity);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AttributesEmpty )( 
            IClearCase __RPC_FAR * This,
            /* [retval][out] */ ICCAttributes __RPC_FAR *__RPC_FAR *pAttributes);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AttributeTypesEmpty )( 
            IClearCase __RPC_FAR * This,
            /* [retval][out] */ ICCAttributeTypes __RPC_FAR *__RPC_FAR *pAttributeTypes);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BranchesEmpty )( 
            IClearCase __RPC_FAR * This,
            /* [retval][out] */ ICCBranches __RPC_FAR *__RPC_FAR *pBranches);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BranchTypesEmpty )( 
            IClearCase __RPC_FAR * This,
            /* [retval][out] */ ICCBranchTypes __RPC_FAR *__RPC_FAR *pBranchTypes);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CheckedOutFile )( 
            IClearCase __RPC_FAR * This,
            /* [in] */ BSTR Path,
            /* [retval][out] */ ICCCheckedOutFile __RPC_FAR *__RPC_FAR *pCheckedOutFile);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CheckedOutFilesEmpty )( 
            IClearCase __RPC_FAR * This,
            /* [retval][out] */ ICCCheckedOutFiles __RPC_FAR *__RPC_FAR *pCheckedOutFiles);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CheckLicense )( 
            IClearCase __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateCheckedOutFileQuery )( 
            IClearCase __RPC_FAR * This,
            /* [retval][out] */ ICCCheckedOutFileQuery __RPC_FAR *__RPC_FAR *pCheckedOutFileQuery);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateElement )( 
            IClearCase __RPC_FAR * This,
            /* [in] */ BSTR Path,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL SetMaster,
            /* [optional][in] */ VARIANT ElementTypeName,
            /* [retval][out] */ ICCCheckedOutFile __RPC_FAR *__RPC_FAR *pCheckedOutFile);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Element )( 
            IClearCase __RPC_FAR * This,
            /* [in] */ BSTR Path,
            /* [retval][out] */ ICCElement __RPC_FAR *__RPC_FAR *pElement);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ElementsEmpty )( 
            IClearCase __RPC_FAR * This,
            /* [retval][out] */ ICCElements __RPC_FAR *__RPC_FAR *pElements);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HistoryRecordsEmpty )( 
            IClearCase __RPC_FAR * This,
            /* [retval][out] */ ICCHistoryRecords __RPC_FAR *__RPC_FAR *pHistoryRecords);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hyperlink )( 
            IClearCase __RPC_FAR * This,
            /* [in] */ BSTR Selector,
            /* [retval][out] */ ICCHyperlink __RPC_FAR *__RPC_FAR *pHyperlink);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HyperlinksEmpty )( 
            IClearCase __RPC_FAR * This,
            /* [retval][out] */ ICCHyperlinks __RPC_FAR *__RPC_FAR *pHyperlinks);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HyperlinkTypesEmpty )( 
            IClearCase __RPC_FAR * This,
            /* [retval][out] */ ICCHyperlinkTypes __RPC_FAR *__RPC_FAR *pHyperlinkTypes);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IsWebGUI )( 
            IClearCase __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL rhs);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LabelsEmpty )( 
            IClearCase __RPC_FAR * This,
            /* [retval][out] */ ICCLabels __RPC_FAR *__RPC_FAR *pLabels);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LabelTypesEmpty )( 
            IClearCase __RPC_FAR * This,
            /* [retval][out] */ ICCLabelTypes __RPC_FAR *__RPC_FAR *pLabelTypes);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocksEmpty )( 
            IClearCase __RPC_FAR * This,
            /* [retval][out] */ ICCLocks __RPC_FAR *__RPC_FAR *pLocks);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAbortPrompts )( 
            IClearCase __RPC_FAR * This);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TriggersEmpty )( 
            IClearCase __RPC_FAR * This,
            /* [retval][out] */ ICCTriggers __RPC_FAR *__RPC_FAR *pTrigger);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TriggerTypesEmpty )( 
            IClearCase __RPC_FAR * This,
            /* [retval][out] */ ICCTriggerTypes __RPC_FAR *__RPC_FAR *pTriggerTypes);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            IClearCase __RPC_FAR * This,
            /* [in] */ VARIANT Path,
            /* [retval][out] */ ICCVersion __RPC_FAR *__RPC_FAR *pVersion);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VersionsEmpty )( 
            IClearCase __RPC_FAR * This,
            /* [retval][out] */ ICCVersions __RPC_FAR *__RPC_FAR *pVersions);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_View )( 
            IClearCase __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Identifier,
            /* [retval][out] */ ICCView __RPC_FAR *__RPC_FAR *pView);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Views )( 
            IClearCase __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL FailIfErrors,
            /* [defaultvalue][optional][in] */ BSTR Region,
            /* [retval][out] */ ICCViews __RPC_FAR *__RPC_FAR *pViews);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ViewsEmpty )( 
            IClearCase __RPC_FAR * This,
            /* [retval][out] */ ICCViews __RPC_FAR *__RPC_FAR *pViews);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOB )( 
            IClearCase __RPC_FAR * This,
            /* [in] */ BSTR Identifier,
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOBs )( 
            IClearCase __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL FailIfErrors,
            /* [defaultvalue][optional][in] */ BSTR Region,
            /* [retval][out] */ ICCVOBs __RPC_FAR *__RPC_FAR *pVOBs);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOBsEmpty )( 
            IClearCase __RPC_FAR * This,
            /* [retval][out] */ ICCVOBs __RPC_FAR *__RPC_FAR *pVOBs);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ActivitiesEmpty )( 
            IClearCase __RPC_FAR * This,
            /* [retval][out] */ ICCActivities __RPC_FAR *__RPC_FAR *pActivities);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ActivityOfVersion )( 
            IClearCase __RPC_FAR * This,
            /* [in] */ ICCVersion __RPC_FAR *pVersion,
            /* [retval][out] */ ICCActivity __RPC_FAR *__RPC_FAR *pActivity);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Baseline )( 
            IClearCase __RPC_FAR * This,
            /* [in] */ BSTR Selector,
            /* [retval][out] */ ICCBaseline __RPC_FAR *__RPC_FAR *pBaseline);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BaselinesEmpty )( 
            IClearCase __RPC_FAR * This,
            /* [retval][out] */ ICCBaselines __RPC_FAR *__RPC_FAR *pBaselines);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Component )( 
            IClearCase __RPC_FAR * This,
            /* [in] */ BSTR Selector,
            /* [retval][out] */ ICCComponent __RPC_FAR *__RPC_FAR *pComponent);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ComponentsEmpty )( 
            IClearCase __RPC_FAR * This,
            /* [retval][out] */ ICCComponents __RPC_FAR *__RPC_FAR *pComponents);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateBaselineComparison )( 
            IClearCase __RPC_FAR * This,
            /* [retval][out] */ ICCBaselineComparison __RPC_FAR *__RPC_FAR *pBaselineComparison);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Folder )( 
            IClearCase __RPC_FAR * This,
            /* [in] */ BSTR Selector,
            /* [retval][out] */ ICCFolder __RPC_FAR *__RPC_FAR *pFolder);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FoldersEmpty )( 
            IClearCase __RPC_FAR * This,
            /* [retval][out] */ ICCFolders __RPC_FAR *__RPC_FAR *pFolders);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsClearCaseLT )( 
            IClearCase __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsClearCaseLT);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsClearCaseLTClient )( 
            IClearCase __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsClearCaseLTClient);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsClearCaseLTServer )( 
            IClearCase __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsClearCaseLTServer);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Project )( 
            IClearCase __RPC_FAR * This,
            /* [in] */ BSTR Selector,
            /* [retval][out] */ ICCProject __RPC_FAR *__RPC_FAR *pProject);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProjectsEmpty )( 
            IClearCase __RPC_FAR * This,
            /* [retval][out] */ ICCProjects __RPC_FAR *__RPC_FAR *pProjects);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProjectVOB )( 
            IClearCase __RPC_FAR * This,
            /* [in] */ BSTR Identifier,
            /* [retval][out] */ ICCProjectVOB __RPC_FAR *__RPC_FAR *pProjectVOB);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProjectVOBsEmpty )( 
            IClearCase __RPC_FAR * This,
            /* [retval][out] */ ICCProjectVOBs __RPC_FAR *__RPC_FAR *pProjectVOBs);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Stream )( 
            IClearCase __RPC_FAR * This,
            /* [in] */ BSTR Selector,
            /* [retval][out] */ ICCStream __RPC_FAR *__RPC_FAR *pStream);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StreamsEmpty )( 
            IClearCase __RPC_FAR * This,
            /* [retval][out] */ ICCStreams __RPC_FAR *__RPC_FAR *pStreams);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UniversalSelector )( 
            IClearCase __RPC_FAR * This,
            /* [in] */ ICCVOBObject __RPC_FAR *pVOBObject,
            /* [retval][out] */ BSTR __RPC_FAR *pUniversalSelector);
        
        END_INTERFACE
    } IClearCaseVtbl;

    interface IClearCase
    {
        CONST_VTBL struct IClearCaseVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IClearCase_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IClearCase_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IClearCase_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IClearCase_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IClearCase_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IClearCase_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IClearCase_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IClearCase_get_Activity(This,Selector,pActivity)	\
    (This)->lpVtbl -> get_Activity(This,Selector,pActivity)

#define IClearCase_get_AttributesEmpty(This,pAttributes)	\
    (This)->lpVtbl -> get_AttributesEmpty(This,pAttributes)

#define IClearCase_get_AttributeTypesEmpty(This,pAttributeTypes)	\
    (This)->lpVtbl -> get_AttributeTypesEmpty(This,pAttributeTypes)

#define IClearCase_get_BranchesEmpty(This,pBranches)	\
    (This)->lpVtbl -> get_BranchesEmpty(This,pBranches)

#define IClearCase_get_BranchTypesEmpty(This,pBranchTypes)	\
    (This)->lpVtbl -> get_BranchTypesEmpty(This,pBranchTypes)

#define IClearCase_get_CheckedOutFile(This,Path,pCheckedOutFile)	\
    (This)->lpVtbl -> get_CheckedOutFile(This,Path,pCheckedOutFile)

#define IClearCase_get_CheckedOutFilesEmpty(This,pCheckedOutFiles)	\
    (This)->lpVtbl -> get_CheckedOutFilesEmpty(This,pCheckedOutFiles)

#define IClearCase_CheckLicense(This)	\
    (This)->lpVtbl -> CheckLicense(This)

#define IClearCase_CreateCheckedOutFileQuery(This,pCheckedOutFileQuery)	\
    (This)->lpVtbl -> CreateCheckedOutFileQuery(This,pCheckedOutFileQuery)

#define IClearCase_CreateElement(This,Path,Comment,SetMaster,ElementTypeName,pCheckedOutFile)	\
    (This)->lpVtbl -> CreateElement(This,Path,Comment,SetMaster,ElementTypeName,pCheckedOutFile)

#define IClearCase_get_Element(This,Path,pElement)	\
    (This)->lpVtbl -> get_Element(This,Path,pElement)

#define IClearCase_get_ElementsEmpty(This,pElements)	\
    (This)->lpVtbl -> get_ElementsEmpty(This,pElements)

#define IClearCase_get_HistoryRecordsEmpty(This,pHistoryRecords)	\
    (This)->lpVtbl -> get_HistoryRecordsEmpty(This,pHistoryRecords)

#define IClearCase_get_Hyperlink(This,Selector,pHyperlink)	\
    (This)->lpVtbl -> get_Hyperlink(This,Selector,pHyperlink)

#define IClearCase_get_HyperlinksEmpty(This,pHyperlinks)	\
    (This)->lpVtbl -> get_HyperlinksEmpty(This,pHyperlinks)

#define IClearCase_get_HyperlinkTypesEmpty(This,pHyperlinkTypes)	\
    (This)->lpVtbl -> get_HyperlinkTypesEmpty(This,pHyperlinkTypes)

#define IClearCase_put_IsWebGUI(This,rhs)	\
    (This)->lpVtbl -> put_IsWebGUI(This,rhs)

#define IClearCase_get_LabelsEmpty(This,pLabels)	\
    (This)->lpVtbl -> get_LabelsEmpty(This,pLabels)

#define IClearCase_get_LabelTypesEmpty(This,pLabelTypes)	\
    (This)->lpVtbl -> get_LabelTypesEmpty(This,pLabelTypes)

#define IClearCase_get_LocksEmpty(This,pLocks)	\
    (This)->lpVtbl -> get_LocksEmpty(This,pLocks)

#define IClearCase_SetAbortPrompts(This)	\
    (This)->lpVtbl -> SetAbortPrompts(This)

#define IClearCase_get_TriggersEmpty(This,pTrigger)	\
    (This)->lpVtbl -> get_TriggersEmpty(This,pTrigger)

#define IClearCase_get_TriggerTypesEmpty(This,pTriggerTypes)	\
    (This)->lpVtbl -> get_TriggerTypesEmpty(This,pTriggerTypes)

#define IClearCase_get_Version(This,Path,pVersion)	\
    (This)->lpVtbl -> get_Version(This,Path,pVersion)

#define IClearCase_get_VersionsEmpty(This,pVersions)	\
    (This)->lpVtbl -> get_VersionsEmpty(This,pVersions)

#define IClearCase_get_View(This,Identifier,pView)	\
    (This)->lpVtbl -> get_View(This,Identifier,pView)

#define IClearCase_get_Views(This,FailIfErrors,Region,pViews)	\
    (This)->lpVtbl -> get_Views(This,FailIfErrors,Region,pViews)

#define IClearCase_get_ViewsEmpty(This,pViews)	\
    (This)->lpVtbl -> get_ViewsEmpty(This,pViews)

#define IClearCase_get_VOB(This,Identifier,pVOB)	\
    (This)->lpVtbl -> get_VOB(This,Identifier,pVOB)

#define IClearCase_get_VOBs(This,FailIfErrors,Region,pVOBs)	\
    (This)->lpVtbl -> get_VOBs(This,FailIfErrors,Region,pVOBs)

#define IClearCase_get_VOBsEmpty(This,pVOBs)	\
    (This)->lpVtbl -> get_VOBsEmpty(This,pVOBs)

#define IClearCase_get_ActivitiesEmpty(This,pActivities)	\
    (This)->lpVtbl -> get_ActivitiesEmpty(This,pActivities)

#define IClearCase_get_ActivityOfVersion(This,pVersion,pActivity)	\
    (This)->lpVtbl -> get_ActivityOfVersion(This,pVersion,pActivity)

#define IClearCase_get_Baseline(This,Selector,pBaseline)	\
    (This)->lpVtbl -> get_Baseline(This,Selector,pBaseline)

#define IClearCase_get_BaselinesEmpty(This,pBaselines)	\
    (This)->lpVtbl -> get_BaselinesEmpty(This,pBaselines)

#define IClearCase_get_Component(This,Selector,pComponent)	\
    (This)->lpVtbl -> get_Component(This,Selector,pComponent)

#define IClearCase_get_ComponentsEmpty(This,pComponents)	\
    (This)->lpVtbl -> get_ComponentsEmpty(This,pComponents)

#define IClearCase_CreateBaselineComparison(This,pBaselineComparison)	\
    (This)->lpVtbl -> CreateBaselineComparison(This,pBaselineComparison)

#define IClearCase_get_Folder(This,Selector,pFolder)	\
    (This)->lpVtbl -> get_Folder(This,Selector,pFolder)

#define IClearCase_get_FoldersEmpty(This,pFolders)	\
    (This)->lpVtbl -> get_FoldersEmpty(This,pFolders)

#define IClearCase_get_IsClearCaseLT(This,pIsClearCaseLT)	\
    (This)->lpVtbl -> get_IsClearCaseLT(This,pIsClearCaseLT)

#define IClearCase_get_IsClearCaseLTClient(This,pIsClearCaseLTClient)	\
    (This)->lpVtbl -> get_IsClearCaseLTClient(This,pIsClearCaseLTClient)

#define IClearCase_get_IsClearCaseLTServer(This,pIsClearCaseLTServer)	\
    (This)->lpVtbl -> get_IsClearCaseLTServer(This,pIsClearCaseLTServer)

#define IClearCase_get_Project(This,Selector,pProject)	\
    (This)->lpVtbl -> get_Project(This,Selector,pProject)

#define IClearCase_get_ProjectsEmpty(This,pProjects)	\
    (This)->lpVtbl -> get_ProjectsEmpty(This,pProjects)

#define IClearCase_get_ProjectVOB(This,Identifier,pProjectVOB)	\
    (This)->lpVtbl -> get_ProjectVOB(This,Identifier,pProjectVOB)

#define IClearCase_get_ProjectVOBsEmpty(This,pProjectVOBs)	\
    (This)->lpVtbl -> get_ProjectVOBsEmpty(This,pProjectVOBs)

#define IClearCase_get_Stream(This,Selector,pStream)	\
    (This)->lpVtbl -> get_Stream(This,Selector,pStream)

#define IClearCase_get_StreamsEmpty(This,pStreams)	\
    (This)->lpVtbl -> get_StreamsEmpty(This,pStreams)

#define IClearCase_get_UniversalSelector(This,pVOBObject,pUniversalSelector)	\
    (This)->lpVtbl -> get_UniversalSelector(This,pVOBObject,pUniversalSelector)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_Activity_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [in] */ BSTR Selector,
    /* [retval][out] */ ICCActivity __RPC_FAR *__RPC_FAR *pActivity);


void __RPC_STUB IClearCase_get_Activity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_AttributesEmpty_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [retval][out] */ ICCAttributes __RPC_FAR *__RPC_FAR *pAttributes);


void __RPC_STUB IClearCase_get_AttributesEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_AttributeTypesEmpty_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [retval][out] */ ICCAttributeTypes __RPC_FAR *__RPC_FAR *pAttributeTypes);


void __RPC_STUB IClearCase_get_AttributeTypesEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_BranchesEmpty_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [retval][out] */ ICCBranches __RPC_FAR *__RPC_FAR *pBranches);


void __RPC_STUB IClearCase_get_BranchesEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_BranchTypesEmpty_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [retval][out] */ ICCBranchTypes __RPC_FAR *__RPC_FAR *pBranchTypes);


void __RPC_STUB IClearCase_get_BranchTypesEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_CheckedOutFile_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [in] */ BSTR Path,
    /* [retval][out] */ ICCCheckedOutFile __RPC_FAR *__RPC_FAR *pCheckedOutFile);


void __RPC_STUB IClearCase_get_CheckedOutFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_CheckedOutFilesEmpty_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [retval][out] */ ICCCheckedOutFiles __RPC_FAR *__RPC_FAR *pCheckedOutFiles);


void __RPC_STUB IClearCase_get_CheckedOutFilesEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IClearCase_CheckLicense_Proxy( 
    IClearCase __RPC_FAR * This);


void __RPC_STUB IClearCase_CheckLicense_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IClearCase_CreateCheckedOutFileQuery_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [retval][out] */ ICCCheckedOutFileQuery __RPC_FAR *__RPC_FAR *pCheckedOutFileQuery);


void __RPC_STUB IClearCase_CreateCheckedOutFileQuery_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IClearCase_CreateElement_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [in] */ BSTR Path,
    /* [defaultvalue][optional][in] */ BSTR Comment,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL SetMaster,
    /* [optional][in] */ VARIANT ElementTypeName,
    /* [retval][out] */ ICCCheckedOutFile __RPC_FAR *__RPC_FAR *pCheckedOutFile);


void __RPC_STUB IClearCase_CreateElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_Element_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [in] */ BSTR Path,
    /* [retval][out] */ ICCElement __RPC_FAR *__RPC_FAR *pElement);


void __RPC_STUB IClearCase_get_Element_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_ElementsEmpty_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [retval][out] */ ICCElements __RPC_FAR *__RPC_FAR *pElements);


void __RPC_STUB IClearCase_get_ElementsEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_HistoryRecordsEmpty_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [retval][out] */ ICCHistoryRecords __RPC_FAR *__RPC_FAR *pHistoryRecords);


void __RPC_STUB IClearCase_get_HistoryRecordsEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_Hyperlink_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [in] */ BSTR Selector,
    /* [retval][out] */ ICCHyperlink __RPC_FAR *__RPC_FAR *pHyperlink);


void __RPC_STUB IClearCase_get_Hyperlink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_HyperlinksEmpty_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [retval][out] */ ICCHyperlinks __RPC_FAR *__RPC_FAR *pHyperlinks);


void __RPC_STUB IClearCase_get_HyperlinksEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_HyperlinkTypesEmpty_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [retval][out] */ ICCHyperlinkTypes __RPC_FAR *__RPC_FAR *pHyperlinkTypes);


void __RPC_STUB IClearCase_get_HyperlinkTypesEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IClearCase_put_IsWebGUI_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL rhs);


void __RPC_STUB IClearCase_put_IsWebGUI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_LabelsEmpty_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [retval][out] */ ICCLabels __RPC_FAR *__RPC_FAR *pLabels);


void __RPC_STUB IClearCase_get_LabelsEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_LabelTypesEmpty_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [retval][out] */ ICCLabelTypes __RPC_FAR *__RPC_FAR *pLabelTypes);


void __RPC_STUB IClearCase_get_LabelTypesEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_LocksEmpty_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [retval][out] */ ICCLocks __RPC_FAR *__RPC_FAR *pLocks);


void __RPC_STUB IClearCase_get_LocksEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IClearCase_SetAbortPrompts_Proxy( 
    IClearCase __RPC_FAR * This);


void __RPC_STUB IClearCase_SetAbortPrompts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_TriggersEmpty_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [retval][out] */ ICCTriggers __RPC_FAR *__RPC_FAR *pTrigger);


void __RPC_STUB IClearCase_get_TriggersEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_TriggerTypesEmpty_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [retval][out] */ ICCTriggerTypes __RPC_FAR *__RPC_FAR *pTriggerTypes);


void __RPC_STUB IClearCase_get_TriggerTypesEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_Version_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [in] */ VARIANT Path,
    /* [retval][out] */ ICCVersion __RPC_FAR *__RPC_FAR *pVersion);


void __RPC_STUB IClearCase_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_VersionsEmpty_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [retval][out] */ ICCVersions __RPC_FAR *__RPC_FAR *pVersions);


void __RPC_STUB IClearCase_get_VersionsEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_View_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Identifier,
    /* [retval][out] */ ICCView __RPC_FAR *__RPC_FAR *pView);


void __RPC_STUB IClearCase_get_View_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_Views_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL FailIfErrors,
    /* [defaultvalue][optional][in] */ BSTR Region,
    /* [retval][out] */ ICCViews __RPC_FAR *__RPC_FAR *pViews);


void __RPC_STUB IClearCase_get_Views_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_ViewsEmpty_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [retval][out] */ ICCViews __RPC_FAR *__RPC_FAR *pViews);


void __RPC_STUB IClearCase_get_ViewsEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_VOB_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [in] */ BSTR Identifier,
    /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);


void __RPC_STUB IClearCase_get_VOB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_VOBs_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL FailIfErrors,
    /* [defaultvalue][optional][in] */ BSTR Region,
    /* [retval][out] */ ICCVOBs __RPC_FAR *__RPC_FAR *pVOBs);


void __RPC_STUB IClearCase_get_VOBs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_VOBsEmpty_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [retval][out] */ ICCVOBs __RPC_FAR *__RPC_FAR *pVOBs);


void __RPC_STUB IClearCase_get_VOBsEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_ActivitiesEmpty_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [retval][out] */ ICCActivities __RPC_FAR *__RPC_FAR *pActivities);


void __RPC_STUB IClearCase_get_ActivitiesEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_ActivityOfVersion_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [in] */ ICCVersion __RPC_FAR *pVersion,
    /* [retval][out] */ ICCActivity __RPC_FAR *__RPC_FAR *pActivity);


void __RPC_STUB IClearCase_get_ActivityOfVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_Baseline_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [in] */ BSTR Selector,
    /* [retval][out] */ ICCBaseline __RPC_FAR *__RPC_FAR *pBaseline);


void __RPC_STUB IClearCase_get_Baseline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_BaselinesEmpty_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [retval][out] */ ICCBaselines __RPC_FAR *__RPC_FAR *pBaselines);


void __RPC_STUB IClearCase_get_BaselinesEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_Component_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [in] */ BSTR Selector,
    /* [retval][out] */ ICCComponent __RPC_FAR *__RPC_FAR *pComponent);


void __RPC_STUB IClearCase_get_Component_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_ComponentsEmpty_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [retval][out] */ ICCComponents __RPC_FAR *__RPC_FAR *pComponents);


void __RPC_STUB IClearCase_get_ComponentsEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IClearCase_CreateBaselineComparison_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [retval][out] */ ICCBaselineComparison __RPC_FAR *__RPC_FAR *pBaselineComparison);


void __RPC_STUB IClearCase_CreateBaselineComparison_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_Folder_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [in] */ BSTR Selector,
    /* [retval][out] */ ICCFolder __RPC_FAR *__RPC_FAR *pFolder);


void __RPC_STUB IClearCase_get_Folder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_FoldersEmpty_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [retval][out] */ ICCFolders __RPC_FAR *__RPC_FAR *pFolders);


void __RPC_STUB IClearCase_get_FoldersEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_IsClearCaseLT_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsClearCaseLT);


void __RPC_STUB IClearCase_get_IsClearCaseLT_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_IsClearCaseLTClient_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsClearCaseLTClient);


void __RPC_STUB IClearCase_get_IsClearCaseLTClient_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_IsClearCaseLTServer_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsClearCaseLTServer);


void __RPC_STUB IClearCase_get_IsClearCaseLTServer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_Project_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [in] */ BSTR Selector,
    /* [retval][out] */ ICCProject __RPC_FAR *__RPC_FAR *pProject);


void __RPC_STUB IClearCase_get_Project_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_ProjectsEmpty_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [retval][out] */ ICCProjects __RPC_FAR *__RPC_FAR *pProjects);


void __RPC_STUB IClearCase_get_ProjectsEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_ProjectVOB_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [in] */ BSTR Identifier,
    /* [retval][out] */ ICCProjectVOB __RPC_FAR *__RPC_FAR *pProjectVOB);


void __RPC_STUB IClearCase_get_ProjectVOB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_ProjectVOBsEmpty_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [retval][out] */ ICCProjectVOBs __RPC_FAR *__RPC_FAR *pProjectVOBs);


void __RPC_STUB IClearCase_get_ProjectVOBsEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_Stream_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [in] */ BSTR Selector,
    /* [retval][out] */ ICCStream __RPC_FAR *__RPC_FAR *pStream);


void __RPC_STUB IClearCase_get_Stream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_StreamsEmpty_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [retval][out] */ ICCStreams __RPC_FAR *__RPC_FAR *pStreams);


void __RPC_STUB IClearCase_get_StreamsEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE IClearCase_get_UniversalSelector_Proxy( 
    IClearCase __RPC_FAR * This,
    /* [in] */ ICCVOBObject __RPC_FAR *pVOBObject,
    /* [retval][out] */ BSTR __RPC_FAR *pUniversalSelector);


void __RPC_STUB IClearCase_get_UniversalSelector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IClearCase_INTERFACE_DEFINED__ */


#ifndef __ICCActivity_INTERFACE_DEFINED__
#define __ICCActivity_INTERFACE_DEFINED__

/* interface ICCActivity */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCActivity,0xB22C7EF9,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7EF9-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCActivity : public ICCVOBObject
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pName) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ChangeSet( 
            /* [in] */ ICCView __RPC_FAR *pNameResolverView,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL FailIfErrors,
            /* [retval][out] */ ICCVersions __RPC_FAR *__RPC_FAR *pVersions) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateLock( 
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
            /* [optional][in] */ VARIANT ExemptUsersStringArray) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Headline( 
            /* [retval][out] */ BSTR __RPC_FAR *pHeadline) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Lock( 
            /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Master( 
            /* [retval][out] */ BSTR __RPC_FAR *pReplica) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_NameResolverView( 
            /* [retval][out] */ ICCView __RPC_FAR *__RPC_FAR *pNameResolverView) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMaster( 
            /* [in] */ BSTR Replica,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_VOB( 
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ClearQuestRecordID( 
            /* [retval][out] */ BSTR __RPC_FAR *pClearQuestRecordID) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Group( 
            /* [retval][out] */ BSTR __RPC_FAR *pGroup) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_HasChangeSet( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pHasChangeSet) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Owner( 
            /* [retval][out] */ BSTR __RPC_FAR *pOwner) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetGroup( 
            /* [in] */ BSTR NewGroup,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetHeadline( 
            /* [in] */ BSTR NewHeadline,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetName( 
            /* [in] */ BSTR NewName,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetOwner( 
            /* [in] */ BSTR NewOwner,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Stream( 
            /* [retval][out] */ ICCStream __RPC_FAR *__RPC_FAR *pStream) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCActivityVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCActivity __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCActivity __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCActivity __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCActivity __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCActivity __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCActivity __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCActivity __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attribute )( 
            ICCActivity __RPC_FAR * This,
            /* [in] */ BSTR AttributeType,
            /* [retval][out] */ ICCAttribute __RPC_FAR *__RPC_FAR *pAttribute);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attributes )( 
            ICCActivity __RPC_FAR * This,
            /* [retval][out] */ ICCAttributes __RPC_FAR *__RPC_FAR *pAttributes);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Comment )( 
            ICCActivity __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pComment);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Comment )( 
            ICCActivity __RPC_FAR * This,
            /* [in] */ BSTR pComment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreationRecord )( 
            ICCActivity __RPC_FAR * This,
            /* [retval][out] */ ICCHistoryRecord __RPC_FAR *__RPC_FAR *pHistoryRecord);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HistoryRecords )( 
            ICCActivity __RPC_FAR * This,
            /* [in] */ ICCBranchType __RPC_FAR *pICCBranchType,
            /* [defaultvalue][optional][in] */ DATE Since,
            /* [defaultvalue][optional][in] */ BSTR User,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Minor,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL ExcludeCheckOutEvents,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL DirectoryOnly,
            /* [retval][out] */ ICCHistoryRecords __RPC_FAR *__RPC_FAR *pHistoryRecords);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hyperlinks )( 
            ICCActivity __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR HyperlinkType,
            /* [retval][out] */ ICCHyperlinks __RPC_FAR *__RPC_FAR *pHyperlinks);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OID )( 
            ICCActivity __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOBFamilyUUID )( 
            ICCActivity __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVOBFamilyUUID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ICCActivity __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pName);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ChangeSet )( 
            ICCActivity __RPC_FAR * This,
            /* [in] */ ICCView __RPC_FAR *pNameResolverView,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL FailIfErrors,
            /* [retval][out] */ ICCVersions __RPC_FAR *__RPC_FAR *pVersions);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateLock )( 
            ICCActivity __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
            /* [optional][in] */ VARIANT ExemptUsersStringArray);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Headline )( 
            ICCActivity __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pHeadline);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Lock )( 
            ICCActivity __RPC_FAR * This,
            /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Master )( 
            ICCActivity __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pReplica);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NameResolverView )( 
            ICCActivity __RPC_FAR * This,
            /* [retval][out] */ ICCView __RPC_FAR *__RPC_FAR *pNameResolverView);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMaster )( 
            ICCActivity __RPC_FAR * This,
            /* [in] */ BSTR Replica,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOB )( 
            ICCActivity __RPC_FAR * This,
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClearQuestRecordID )( 
            ICCActivity __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pClearQuestRecordID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Group )( 
            ICCActivity __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pGroup);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HasChangeSet )( 
            ICCActivity __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pHasChangeSet);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Owner )( 
            ICCActivity __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOwner);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGroup )( 
            ICCActivity __RPC_FAR * This,
            /* [in] */ BSTR NewGroup,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetHeadline )( 
            ICCActivity __RPC_FAR * This,
            /* [in] */ BSTR NewHeadline,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetName )( 
            ICCActivity __RPC_FAR * This,
            /* [in] */ BSTR NewName,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOwner )( 
            ICCActivity __RPC_FAR * This,
            /* [in] */ BSTR NewOwner,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Stream )( 
            ICCActivity __RPC_FAR * This,
            /* [retval][out] */ ICCStream __RPC_FAR *__RPC_FAR *pStream);
        
        END_INTERFACE
    } ICCActivityVtbl;

    interface ICCActivity
    {
        CONST_VTBL struct ICCActivityVtbl __RPC_FAR *lpVtbl;
    };

    
#ifdef COBJMACROS


#define ICCActivity_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCActivity_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCActivity_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCActivity_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCActivity_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCActivity_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCActivity_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCActivity_get_Attribute(This,AttributeType,pAttribute)	\
    (This)->lpVtbl -> get_Attribute(This,AttributeType,pAttribute)

#define ICCActivity_get_Attributes(This,pAttributes)	\
    (This)->lpVtbl -> get_Attributes(This,pAttributes)

#define ICCActivity_get_Comment(This,pComment)	\
    (This)->lpVtbl -> get_Comment(This,pComment)

#define ICCActivity_put_Comment(This,pComment)	\
    (This)->lpVtbl -> put_Comment(This,pComment)

#define ICCActivity_get_CreationRecord(This,pHistoryRecord)	\
    (This)->lpVtbl -> get_CreationRecord(This,pHistoryRecord)

#define ICCActivity_get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)	\
    (This)->lpVtbl -> get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)

#define ICCActivity_get_Hyperlinks(This,HyperlinkType,pHyperlinks)	\
    (This)->lpVtbl -> get_Hyperlinks(This,HyperlinkType,pHyperlinks)

#define ICCActivity_get_OID(This,pOID)	\
    (This)->lpVtbl -> get_OID(This,pOID)

#define ICCActivity_get_VOBFamilyUUID(This,pVOBFamilyUUID)	\
    (This)->lpVtbl -> get_VOBFamilyUUID(This,pVOBFamilyUUID)


#define ICCActivity_get_Name(This,pName)	\
    (This)->lpVtbl -> get_Name(This,pName)

#define ICCActivity_get_ChangeSet(This,pNameResolverView,FailIfErrors,pVersions)	\
    (This)->lpVtbl -> get_ChangeSet(This,pNameResolverView,FailIfErrors,pVersions)

#define ICCActivity_CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)	\
    (This)->lpVtbl -> CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)

#define ICCActivity_get_Headline(This,pHeadline)	\
    (This)->lpVtbl -> get_Headline(This,pHeadline)

#define ICCActivity_get_Lock(This,pLock)	\
    (This)->lpVtbl -> get_Lock(This,pLock)

#define ICCActivity_get_Master(This,pReplica)	\
    (This)->lpVtbl -> get_Master(This,pReplica)

#define ICCActivity_get_NameResolverView(This,pNameResolverView)	\
    (This)->lpVtbl -> get_NameResolverView(This,pNameResolverView)

#define ICCActivity_SetMaster(This,Replica,Comment)	\
    (This)->lpVtbl -> SetMaster(This,Replica,Comment)

#define ICCActivity_get_VOB(This,pVOB)	\
    (This)->lpVtbl -> get_VOB(This,pVOB)

#define ICCActivity_get_ClearQuestRecordID(This,pClearQuestRecordID)	\
    (This)->lpVtbl -> get_ClearQuestRecordID(This,pClearQuestRecordID)

#define ICCActivity_get_Group(This,pGroup)	\
    (This)->lpVtbl -> get_Group(This,pGroup)

#define ICCActivity_get_HasChangeSet(This,pHasChangeSet)	\
    (This)->lpVtbl -> get_HasChangeSet(This,pHasChangeSet)

#define ICCActivity_get_Owner(This,pOwner)	\
    (This)->lpVtbl -> get_Owner(This,pOwner)

#define ICCActivity_SetGroup(This,NewGroup,Comment)	\
    (This)->lpVtbl -> SetGroup(This,NewGroup,Comment)

#define ICCActivity_SetHeadline(This,NewHeadline,Comment)	\
    (This)->lpVtbl -> SetHeadline(This,NewHeadline,Comment)

#define ICCActivity_SetName(This,NewName,Comment)	\
    (This)->lpVtbl -> SetName(This,NewName,Comment)

#define ICCActivity_SetOwner(This,NewOwner,Comment)	\
    (This)->lpVtbl -> SetOwner(This,NewOwner,Comment)

#define ICCActivity_get_Stream(This,pStream)	\
    (This)->lpVtbl -> get_Stream(This,pStream)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCActivity_get_Name_Proxy( 
    ICCActivity __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pName);


void __RPC_STUB ICCActivity_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCActivity_get_ChangeSet_Proxy( 
    ICCActivity __RPC_FAR * This,
    /* [in] */ ICCView __RPC_FAR *pNameResolverView,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL FailIfErrors,
    /* [retval][out] */ ICCVersions __RPC_FAR *__RPC_FAR *pVersions);


void __RPC_STUB ICCActivity_get_ChangeSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCActivity_CreateLock_Proxy( 
    ICCActivity __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Comment,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
    /* [optional][in] */ VARIANT ExemptUsersStringArray);


void __RPC_STUB ICCActivity_CreateLock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCActivity_get_Headline_Proxy( 
    ICCActivity __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pHeadline);


void __RPC_STUB ICCActivity_get_Headline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCActivity_get_Lock_Proxy( 
    ICCActivity __RPC_FAR * This,
    /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock);


void __RPC_STUB ICCActivity_get_Lock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCActivity_get_Master_Proxy( 
    ICCActivity __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pReplica);


void __RPC_STUB ICCActivity_get_Master_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCActivity_get_NameResolverView_Proxy( 
    ICCActivity __RPC_FAR * This,
    /* [retval][out] */ ICCView __RPC_FAR *__RPC_FAR *pNameResolverView);


void __RPC_STUB ICCActivity_get_NameResolverView_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCActivity_SetMaster_Proxy( 
    ICCActivity __RPC_FAR * This,
    /* [in] */ BSTR Replica,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCActivity_SetMaster_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCActivity_get_VOB_Proxy( 
    ICCActivity __RPC_FAR * This,
    /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);


void __RPC_STUB ICCActivity_get_VOB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCActivity_get_ClearQuestRecordID_Proxy( 
    ICCActivity __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pClearQuestRecordID);


void __RPC_STUB ICCActivity_get_ClearQuestRecordID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCActivity_get_Group_Proxy( 
    ICCActivity __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pGroup);


void __RPC_STUB ICCActivity_get_Group_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCActivity_get_HasChangeSet_Proxy( 
    ICCActivity __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pHasChangeSet);


void __RPC_STUB ICCActivity_get_HasChangeSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCActivity_get_Owner_Proxy( 
    ICCActivity __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pOwner);


void __RPC_STUB ICCActivity_get_Owner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCActivity_SetGroup_Proxy( 
    ICCActivity __RPC_FAR * This,
    /* [in] */ BSTR NewGroup,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCActivity_SetGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCActivity_SetHeadline_Proxy( 
    ICCActivity __RPC_FAR * This,
    /* [in] */ BSTR NewHeadline,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCActivity_SetHeadline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCActivity_SetName_Proxy( 
    ICCActivity __RPC_FAR * This,
    /* [in] */ BSTR NewName,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCActivity_SetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCActivity_SetOwner_Proxy( 
    ICCActivity __RPC_FAR * This,
    /* [in] */ BSTR NewOwner,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCActivity_SetOwner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCActivity_get_Stream_Proxy( 
    ICCActivity __RPC_FAR * This,
    /* [retval][out] */ ICCStream __RPC_FAR *__RPC_FAR *pStream);


void __RPC_STUB ICCActivity_get_Stream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCActivity_INTERFACE_DEFINED__ */

#ifndef __ICCAttribute_INTERFACE_DEFINED__
#define __ICCAttribute_INTERFACE_DEFINED__

/* interface ICCAttribute */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCAttribute,0xB22C7EED,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7EED-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCAttribute : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetValue( 
            /* [in] */ VARIANT Value,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ ICCAttributeType __RPC_FAR *__RPC_FAR *pType) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ VARIANT __RPC_FAR *pValue) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_VOB( 
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCAttributeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCAttribute __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCAttribute __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCAttribute __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCAttribute __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCAttribute __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCAttribute __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCAttribute __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ICCAttribute __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetValue )( 
            ICCAttribute __RPC_FAR * This,
            /* [in] */ VARIANT Value,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            ICCAttribute __RPC_FAR * This,
            /* [retval][out] */ ICCAttributeType __RPC_FAR *__RPC_FAR *pType);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Value )( 
            ICCAttribute __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pValue);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOB )( 
            ICCAttribute __RPC_FAR * This,
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);
        
        END_INTERFACE
    } ICCAttributeVtbl;

    interface ICCAttribute
    {
        CONST_VTBL struct ICCAttributeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCAttribute_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCAttribute_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCAttribute_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCAttribute_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCAttribute_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCAttribute_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCAttribute_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCAttribute_Remove(This,Comment)	\
    (This)->lpVtbl -> Remove(This,Comment)

#define ICCAttribute_SetValue(This,Value,Comment)	\
    (This)->lpVtbl -> SetValue(This,Value,Comment)

#define ICCAttribute_get_Type(This,pType)	\
    (This)->lpVtbl -> get_Type(This,pType)

#define ICCAttribute_get_Value(This,pValue)	\
    (This)->lpVtbl -> get_Value(This,pValue)

#define ICCAttribute_get_VOB(This,pVOB)	\
    (This)->lpVtbl -> get_VOB(This,pVOB)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCAttribute_Remove_Proxy( 
    ICCAttribute __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCAttribute_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCAttribute_SetValue_Proxy( 
    ICCAttribute __RPC_FAR * This,
    /* [in] */ VARIANT Value,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCAttribute_SetValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCAttribute_get_Type_Proxy( 
    ICCAttribute __RPC_FAR * This,
    /* [retval][out] */ ICCAttributeType __RPC_FAR *__RPC_FAR *pType);


void __RPC_STUB ICCAttribute_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCAttribute_get_Value_Proxy( 
    ICCAttribute __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pValue);


void __RPC_STUB ICCAttribute_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCAttribute_get_VOB_Proxy( 
    ICCAttribute __RPC_FAR * This,
    /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);


void __RPC_STUB ICCAttribute_get_VOB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCAttribute_INTERFACE_DEFINED__ */


#ifndef __ICCAttributeType_INTERFACE_DEFINED__
#define __ICCAttributeType_INTERFACE_DEFINED__

/* interface ICCAttributeType */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCAttributeType,0xB22C7EEB,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7EEB-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCAttributeType : public ICCVOBObject
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pName) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Apply( 
            /* [in] */ ICCVOBObject __RPC_FAR *pVOBObject,
            /* [optional][in] */ VARIANT Value,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"",
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Replace = 0,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse = 0) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Constraint( 
            /* [retval][out] */ CCTypeConstraint __RPC_FAR *pConstraint) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateLock( 
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
            /* [optional][in] */ VARIANT ExemptUsersStringArray) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_DefaultValue( 
            /* [retval][out] */ VARIANT __RPC_FAR *pDefaultValue) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_EnumValuesArray( 
            /* [retval][out] */ VARIANT __RPC_FAR *pEnumValuesArray) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Group( 
            /* [retval][out] */ BSTR __RPC_FAR *pGroup) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_HasSharedMastership( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pHasShared) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Lock( 
            /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_LowerIsInRange( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pLowerIsInRange) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_LowerValue( 
            /* [retval][out] */ VARIANT __RPC_FAR *pLowerValue) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Master( 
            /* [retval][out] */ BSTR __RPC_FAR *pReplica) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_NumberOfEnumValues( 
            /* [retval][out] */ long __RPC_FAR *pNumberOfEnumValues) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Owner( 
            /* [retval][out] */ BSTR __RPC_FAR *pOwner) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveType( 
            /* [defaultvalue][optional][in] */ VARIANT_BOOL RemoveAllInstances = 0,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Scope( 
            /* [retval][out] */ CCTypeScope __RPC_FAR *pScope) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetConstraint( 
            /* [in] */ CCTypeConstraint NewConstraint,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDefaultValue( 
            /* [optional][in] */ VARIANT DefaultValue,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEnumValuesArray( 
            /* [optional][in] */ VARIANT EnumValuesArray,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetGroup( 
            /* [in] */ BSTR NewGroup,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetLowerValue( 
            /* [optional][in] */ VARIANT LowerValue,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL LowerIsInRange = 0,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMaster( 
            /* [in] */ BSTR Replica,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetName( 
            /* [in] */ BSTR NewName,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetOwner( 
            /* [in] */ BSTR NewOwner,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetScope( 
            /* [in] */ VARIANT_BOOL Global,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Acquire = 0,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetUpperValue( 
            /* [optional][in] */ VARIANT UpperValue,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL UpperIsInRange = 0,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetValueType( 
            /* [in] */ long ValueType,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ShareMastership( 
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_UpperIsInRange( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pUpperIsInRange) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_UpperValue( 
            /* [retval][out] */ VARIANT __RPC_FAR *pUpperValue) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ValueType( 
            /* [retval][out] */ long __RPC_FAR *pValueType) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_VOB( 
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCAttributeTypeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCAttributeType __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCAttributeType __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCAttributeType __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCAttributeType __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCAttributeType __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCAttributeType __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCAttributeType __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attribute )( 
            ICCAttributeType __RPC_FAR * This,
            /* [in] */ BSTR AttributeType,
            /* [retval][out] */ ICCAttribute __RPC_FAR *__RPC_FAR *pAttribute);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attributes )( 
            ICCAttributeType __RPC_FAR * This,
            /* [retval][out] */ ICCAttributes __RPC_FAR *__RPC_FAR *pAttributes);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Comment )( 
            ICCAttributeType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pComment);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Comment )( 
            ICCAttributeType __RPC_FAR * This,
            /* [in] */ BSTR pComment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreationRecord )( 
            ICCAttributeType __RPC_FAR * This,
            /* [retval][out] */ ICCHistoryRecord __RPC_FAR *__RPC_FAR *pHistoryRecord);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HistoryRecords )( 
            ICCAttributeType __RPC_FAR * This,
            /* [in] */ ICCBranchType __RPC_FAR *pICCBranchType,
            /* [defaultvalue][optional][in] */ DATE Since,
            /* [defaultvalue][optional][in] */ BSTR User,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Minor,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL ExcludeCheckOutEvents,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL DirectoryOnly,
            /* [retval][out] */ ICCHistoryRecords __RPC_FAR *__RPC_FAR *pHistoryRecords);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hyperlinks )( 
            ICCAttributeType __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR HyperlinkType,
            /* [retval][out] */ ICCHyperlinks __RPC_FAR *__RPC_FAR *pHyperlinks);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OID )( 
            ICCAttributeType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOBFamilyUUID )( 
            ICCAttributeType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVOBFamilyUUID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ICCAttributeType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Apply )( 
            ICCAttributeType __RPC_FAR * This,
            /* [in] */ ICCVOBObject __RPC_FAR *pVOBObject,
            /* [optional][in] */ VARIANT Value,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Replace,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Constraint )( 
            ICCAttributeType __RPC_FAR * This,
            /* [retval][out] */ CCTypeConstraint __RPC_FAR *pConstraint);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateLock )( 
            ICCAttributeType __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
            /* [optional][in] */ VARIANT ExemptUsersStringArray);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DefaultValue )( 
            ICCAttributeType __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pDefaultValue);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EnumValuesArray )( 
            ICCAttributeType __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pEnumValuesArray);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Group )( 
            ICCAttributeType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pGroup);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HasSharedMastership )( 
            ICCAttributeType __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pHasShared);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Lock )( 
            ICCAttributeType __RPC_FAR * This,
            /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LowerIsInRange )( 
            ICCAttributeType __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pLowerIsInRange);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LowerValue )( 
            ICCAttributeType __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pLowerValue);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Master )( 
            ICCAttributeType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pReplica);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumberOfEnumValues )( 
            ICCAttributeType __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pNumberOfEnumValues);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Owner )( 
            ICCAttributeType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOwner);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveType )( 
            ICCAttributeType __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL RemoveAllInstances,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Scope )( 
            ICCAttributeType __RPC_FAR * This,
            /* [retval][out] */ CCTypeScope __RPC_FAR *pScope);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConstraint )( 
            ICCAttributeType __RPC_FAR * This,
            /* [in] */ CCTypeConstraint NewConstraint,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDefaultValue )( 
            ICCAttributeType __RPC_FAR * This,
            /* [optional][in] */ VARIANT DefaultValue,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetEnumValuesArray )( 
            ICCAttributeType __RPC_FAR * This,
            /* [optional][in] */ VARIANT EnumValuesArray,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGroup )( 
            ICCAttributeType __RPC_FAR * This,
            /* [in] */ BSTR NewGroup,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetLowerValue )( 
            ICCAttributeType __RPC_FAR * This,
            /* [optional][in] */ VARIANT LowerValue,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL LowerIsInRange,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMaster )( 
            ICCAttributeType __RPC_FAR * This,
            /* [in] */ BSTR Replica,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetName )( 
            ICCAttributeType __RPC_FAR * This,
            /* [in] */ BSTR NewName,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOwner )( 
            ICCAttributeType __RPC_FAR * This,
            /* [in] */ BSTR NewOwner,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetScope )( 
            ICCAttributeType __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Global,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Acquire,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetUpperValue )( 
            ICCAttributeType __RPC_FAR * This,
            /* [optional][in] */ VARIANT UpperValue,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL UpperIsInRange,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetValueType )( 
            ICCAttributeType __RPC_FAR * This,
            /* [in] */ long ValueType,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShareMastership )( 
            ICCAttributeType __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UpperIsInRange )( 
            ICCAttributeType __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pUpperIsInRange);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UpperValue )( 
            ICCAttributeType __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pUpperValue);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ValueType )( 
            ICCAttributeType __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pValueType);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOB )( 
            ICCAttributeType __RPC_FAR * This,
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);
        
        END_INTERFACE
    } ICCAttributeTypeVtbl;

    interface ICCAttributeType
    {
        CONST_VTBL struct ICCAttributeTypeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCAttributeType_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCAttributeType_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCAttributeType_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCAttributeType_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCAttributeType_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCAttributeType_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCAttributeType_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCAttributeType_get_Attribute(This,AttributeType,pAttribute)	\
    (This)->lpVtbl -> get_Attribute(This,AttributeType,pAttribute)

#define ICCAttributeType_get_Attributes(This,pAttributes)	\
    (This)->lpVtbl -> get_Attributes(This,pAttributes)

#define ICCAttributeType_get_Comment(This,pComment)	\
    (This)->lpVtbl -> get_Comment(This,pComment)

#define ICCAttributeType_put_Comment(This,pComment)	\
    (This)->lpVtbl -> put_Comment(This,pComment)

#define ICCAttributeType_get_CreationRecord(This,pHistoryRecord)	\
    (This)->lpVtbl -> get_CreationRecord(This,pHistoryRecord)

#define ICCAttributeType_get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)	\
    (This)->lpVtbl -> get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)

#define ICCAttributeType_get_Hyperlinks(This,HyperlinkType,pHyperlinks)	\
    (This)->lpVtbl -> get_Hyperlinks(This,HyperlinkType,pHyperlinks)

#define ICCAttributeType_get_OID(This,pOID)	\
    (This)->lpVtbl -> get_OID(This,pOID)

#define ICCAttributeType_get_VOBFamilyUUID(This,pVOBFamilyUUID)	\
    (This)->lpVtbl -> get_VOBFamilyUUID(This,pVOBFamilyUUID)


#define ICCAttributeType_get_Name(This,pName)	\
    (This)->lpVtbl -> get_Name(This,pName)

#define ICCAttributeType_Apply(This,pVOBObject,Value,Comment,Replace,Recurse)	\
    (This)->lpVtbl -> Apply(This,pVOBObject,Value,Comment,Replace,Recurse)

#define ICCAttributeType_get_Constraint(This,pConstraint)	\
    (This)->lpVtbl -> get_Constraint(This,pConstraint)

#define ICCAttributeType_CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)	\
    (This)->lpVtbl -> CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)

#define ICCAttributeType_get_DefaultValue(This,pDefaultValue)	\
    (This)->lpVtbl -> get_DefaultValue(This,pDefaultValue)

#define ICCAttributeType_get_EnumValuesArray(This,pEnumValuesArray)	\
    (This)->lpVtbl -> get_EnumValuesArray(This,pEnumValuesArray)

#define ICCAttributeType_get_Group(This,pGroup)	\
    (This)->lpVtbl -> get_Group(This,pGroup)

#define ICCAttributeType_get_HasSharedMastership(This,pHasShared)	\
    (This)->lpVtbl -> get_HasSharedMastership(This,pHasShared)

#define ICCAttributeType_get_Lock(This,pLock)	\
    (This)->lpVtbl -> get_Lock(This,pLock)

#define ICCAttributeType_get_LowerIsInRange(This,pLowerIsInRange)	\
    (This)->lpVtbl -> get_LowerIsInRange(This,pLowerIsInRange)

#define ICCAttributeType_get_LowerValue(This,pLowerValue)	\
    (This)->lpVtbl -> get_LowerValue(This,pLowerValue)

#define ICCAttributeType_get_Master(This,pReplica)	\
    (This)->lpVtbl -> get_Master(This,pReplica)

#define ICCAttributeType_get_NumberOfEnumValues(This,pNumberOfEnumValues)	\
    (This)->lpVtbl -> get_NumberOfEnumValues(This,pNumberOfEnumValues)

#define ICCAttributeType_get_Owner(This,pOwner)	\
    (This)->lpVtbl -> get_Owner(This,pOwner)

#define ICCAttributeType_RemoveType(This,RemoveAllInstances,Comment)	\
    (This)->lpVtbl -> RemoveType(This,RemoveAllInstances,Comment)

#define ICCAttributeType_get_Scope(This,pScope)	\
    (This)->lpVtbl -> get_Scope(This,pScope)

#define ICCAttributeType_SetConstraint(This,NewConstraint,Comment)	\
    (This)->lpVtbl -> SetConstraint(This,NewConstraint,Comment)

#define ICCAttributeType_SetDefaultValue(This,DefaultValue,Comment)	\
    (This)->lpVtbl -> SetDefaultValue(This,DefaultValue,Comment)

#define ICCAttributeType_SetEnumValuesArray(This,EnumValuesArray,Comment)	\
    (This)->lpVtbl -> SetEnumValuesArray(This,EnumValuesArray,Comment)

#define ICCAttributeType_SetGroup(This,NewGroup,Comment)	\
    (This)->lpVtbl -> SetGroup(This,NewGroup,Comment)

#define ICCAttributeType_SetLowerValue(This,LowerValue,LowerIsInRange,Comment)	\
    (This)->lpVtbl -> SetLowerValue(This,LowerValue,LowerIsInRange,Comment)

#define ICCAttributeType_SetMaster(This,Replica,Comment)	\
    (This)->lpVtbl -> SetMaster(This,Replica,Comment)

#define ICCAttributeType_SetName(This,NewName,Comment)	\
    (This)->lpVtbl -> SetName(This,NewName,Comment)

#define ICCAttributeType_SetOwner(This,NewOwner,Comment)	\
    (This)->lpVtbl -> SetOwner(This,NewOwner,Comment)

#define ICCAttributeType_SetScope(This,Global,Acquire,Comment)	\
    (This)->lpVtbl -> SetScope(This,Global,Acquire,Comment)

#define ICCAttributeType_SetUpperValue(This,UpperValue,UpperIsInRange,Comment)	\
    (This)->lpVtbl -> SetUpperValue(This,UpperValue,UpperIsInRange,Comment)

#define ICCAttributeType_SetValueType(This,ValueType,Comment)	\
    (This)->lpVtbl -> SetValueType(This,ValueType,Comment)

#define ICCAttributeType_ShareMastership(This,Comment)	\
    (This)->lpVtbl -> ShareMastership(This,Comment)

#define ICCAttributeType_get_UpperIsInRange(This,pUpperIsInRange)	\
    (This)->lpVtbl -> get_UpperIsInRange(This,pUpperIsInRange)

#define ICCAttributeType_get_UpperValue(This,pUpperValue)	\
    (This)->lpVtbl -> get_UpperValue(This,pUpperValue)

#define ICCAttributeType_get_ValueType(This,pValueType)	\
    (This)->lpVtbl -> get_ValueType(This,pValueType)

#define ICCAttributeType_get_VOB(This,pVOB)	\
    (This)->lpVtbl -> get_VOB(This,pVOB)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_get_Name_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pName);


void __RPC_STUB ICCAttributeType_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_Apply_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [in] */ ICCVOBObject __RPC_FAR *pVOBObject,
    /* [optional][in] */ VARIANT Value,
    /* [defaultvalue][optional][in] */ BSTR Comment,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Replace,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse);


void __RPC_STUB ICCAttributeType_Apply_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_get_Constraint_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [retval][out] */ CCTypeConstraint __RPC_FAR *pConstraint);


void __RPC_STUB ICCAttributeType_get_Constraint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_CreateLock_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Comment,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
    /* [optional][in] */ VARIANT ExemptUsersStringArray);


void __RPC_STUB ICCAttributeType_CreateLock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_get_DefaultValue_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pDefaultValue);


void __RPC_STUB ICCAttributeType_get_DefaultValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_get_EnumValuesArray_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pEnumValuesArray);


void __RPC_STUB ICCAttributeType_get_EnumValuesArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_get_Group_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pGroup);


void __RPC_STUB ICCAttributeType_get_Group_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_get_HasSharedMastership_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pHasShared);


void __RPC_STUB ICCAttributeType_get_HasSharedMastership_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_get_Lock_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock);


void __RPC_STUB ICCAttributeType_get_Lock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_get_LowerIsInRange_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pLowerIsInRange);


void __RPC_STUB ICCAttributeType_get_LowerIsInRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_get_LowerValue_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pLowerValue);


void __RPC_STUB ICCAttributeType_get_LowerValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_get_Master_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pReplica);


void __RPC_STUB ICCAttributeType_get_Master_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_get_NumberOfEnumValues_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pNumberOfEnumValues);


void __RPC_STUB ICCAttributeType_get_NumberOfEnumValues_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_get_Owner_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pOwner);


void __RPC_STUB ICCAttributeType_get_Owner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_RemoveType_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL RemoveAllInstances,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCAttributeType_RemoveType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_get_Scope_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [retval][out] */ CCTypeScope __RPC_FAR *pScope);


void __RPC_STUB ICCAttributeType_get_Scope_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_SetConstraint_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [in] */ CCTypeConstraint NewConstraint,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCAttributeType_SetConstraint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_SetDefaultValue_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [optional][in] */ VARIANT DefaultValue,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCAttributeType_SetDefaultValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_SetEnumValuesArray_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [optional][in] */ VARIANT EnumValuesArray,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCAttributeType_SetEnumValuesArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_SetGroup_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [in] */ BSTR NewGroup,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCAttributeType_SetGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_SetLowerValue_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [optional][in] */ VARIANT LowerValue,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL LowerIsInRange,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCAttributeType_SetLowerValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_SetMaster_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [in] */ BSTR Replica,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCAttributeType_SetMaster_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_SetName_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [in] */ BSTR NewName,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCAttributeType_SetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_SetOwner_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [in] */ BSTR NewOwner,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCAttributeType_SetOwner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_SetScope_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Global,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Acquire,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCAttributeType_SetScope_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_SetUpperValue_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [optional][in] */ VARIANT UpperValue,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL UpperIsInRange,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCAttributeType_SetUpperValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_SetValueType_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [in] */ long ValueType,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCAttributeType_SetValueType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_ShareMastership_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCAttributeType_ShareMastership_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_get_UpperIsInRange_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pUpperIsInRange);


void __RPC_STUB ICCAttributeType_get_UpperIsInRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_get_UpperValue_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pUpperValue);


void __RPC_STUB ICCAttributeType_get_UpperValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_get_ValueType_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pValueType);


void __RPC_STUB ICCAttributeType_get_ValueType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeType_get_VOB_Proxy( 
    ICCAttributeType __RPC_FAR * This,
    /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);


void __RPC_STUB ICCAttributeType_get_VOB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCAttributeType_INTERFACE_DEFINED__ */


#ifndef __ICCLock_INTERFACE_DEFINED__
#define __ICCLock_INTERFACE_DEFINED__

/* interface ICCLock */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCLock,0xB22C7EF7,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7EF7-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCLock : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_CreationRecord( 
            /* [retval][out] */ ICCHistoryRecord __RPC_FAR *__RPC_FAR *pHistoryRecord) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ExemptUsersStringArray( 
            /* [retval][out] */ VARIANT __RPC_FAR *pExemptUsersStringArray) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IsObsolete( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsObsolete) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_LockedObject( 
            /* [retval][out] */ ICCVOBObject __RPC_FAR *__RPC_FAR *pLockedObject) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_NumberOfExemptUsers( 
            /* [retval][out] */ long __RPC_FAR *pNumberOfExemptUsers) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetExemptUsersStringArray( 
            /* [optional][in] */ VARIANT ExemptUsersStringArray,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetObsolete( 
            /* [in] */ VARIANT_BOOL IsObsolete,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_VOB( 
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCLockVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCLock __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCLock __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCLock __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCLock __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCLock __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCLock __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCLock __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreationRecord )( 
            ICCLock __RPC_FAR * This,
            /* [retval][out] */ ICCHistoryRecord __RPC_FAR *__RPC_FAR *pHistoryRecord);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExemptUsersStringArray )( 
            ICCLock __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pExemptUsersStringArray);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsObsolete )( 
            ICCLock __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsObsolete);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LockedObject )( 
            ICCLock __RPC_FAR * This,
            /* [retval][out] */ ICCVOBObject __RPC_FAR *__RPC_FAR *pLockedObject);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumberOfExemptUsers )( 
            ICCLock __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pNumberOfExemptUsers);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ICCLock __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetExemptUsersStringArray )( 
            ICCLock __RPC_FAR * This,
            /* [optional][in] */ VARIANT ExemptUsersStringArray,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetObsolete )( 
            ICCLock __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL IsObsolete,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOB )( 
            ICCLock __RPC_FAR * This,
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);
        
        END_INTERFACE
    } ICCLockVtbl;

    interface ICCLock
    {
        CONST_VTBL struct ICCLockVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCLock_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCLock_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCLock_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCLock_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCLock_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCLock_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCLock_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCLock_get_CreationRecord(This,pHistoryRecord)	\
    (This)->lpVtbl -> get_CreationRecord(This,pHistoryRecord)

#define ICCLock_get_ExemptUsersStringArray(This,pExemptUsersStringArray)	\
    (This)->lpVtbl -> get_ExemptUsersStringArray(This,pExemptUsersStringArray)

#define ICCLock_get_IsObsolete(This,pIsObsolete)	\
    (This)->lpVtbl -> get_IsObsolete(This,pIsObsolete)

#define ICCLock_get_LockedObject(This,pLockedObject)	\
    (This)->lpVtbl -> get_LockedObject(This,pLockedObject)

#define ICCLock_get_NumberOfExemptUsers(This,pNumberOfExemptUsers)	\
    (This)->lpVtbl -> get_NumberOfExemptUsers(This,pNumberOfExemptUsers)

#define ICCLock_Remove(This,Comment)	\
    (This)->lpVtbl -> Remove(This,Comment)

#define ICCLock_SetExemptUsersStringArray(This,ExemptUsersStringArray,Comment)	\
    (This)->lpVtbl -> SetExemptUsersStringArray(This,ExemptUsersStringArray,Comment)

#define ICCLock_SetObsolete(This,IsObsolete,Comment)	\
    (This)->lpVtbl -> SetObsolete(This,IsObsolete,Comment)

#define ICCLock_get_VOB(This,pVOB)	\
    (This)->lpVtbl -> get_VOB(This,pVOB)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCLock_get_CreationRecord_Proxy( 
    ICCLock __RPC_FAR * This,
    /* [retval][out] */ ICCHistoryRecord __RPC_FAR *__RPC_FAR *pHistoryRecord);


void __RPC_STUB ICCLock_get_CreationRecord_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCLock_get_ExemptUsersStringArray_Proxy( 
    ICCLock __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pExemptUsersStringArray);


void __RPC_STUB ICCLock_get_ExemptUsersStringArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCLock_get_IsObsolete_Proxy( 
    ICCLock __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsObsolete);


void __RPC_STUB ICCLock_get_IsObsolete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCLock_get_LockedObject_Proxy( 
    ICCLock __RPC_FAR * This,
    /* [retval][out] */ ICCVOBObject __RPC_FAR *__RPC_FAR *pLockedObject);


void __RPC_STUB ICCLock_get_LockedObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCLock_get_NumberOfExemptUsers_Proxy( 
    ICCLock __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pNumberOfExemptUsers);


void __RPC_STUB ICCLock_get_NumberOfExemptUsers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCLock_Remove_Proxy( 
    ICCLock __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCLock_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCLock_SetExemptUsersStringArray_Proxy( 
    ICCLock __RPC_FAR * This,
    /* [optional][in] */ VARIANT ExemptUsersStringArray,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCLock_SetExemptUsersStringArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCLock_SetObsolete_Proxy( 
    ICCLock __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL IsObsolete,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCLock_SetObsolete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCLock_get_VOB_Proxy( 
    ICCLock __RPC_FAR * This,
    /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);


void __RPC_STUB ICCLock_get_VOB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCLock_INTERFACE_DEFINED__ */


#ifndef __ICCHistoryRecord_INTERFACE_DEFINED__
#define __ICCHistoryRecord_INTERFACE_DEFINED__

/* interface ICCHistoryRecord */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCHistoryRecord,0xB22C7ECF,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7ECF-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCHistoryRecord : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_UserLoginName( 
            /* [retval][out] */ BSTR __RPC_FAR *pUserLoginName) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_UserFullName( 
            /* [retval][out] */ BSTR __RPC_FAR *pUserFullName) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Group( 
            /* [retval][out] */ BSTR __RPC_FAR *pGroup) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Comment( 
            /* [retval][out] */ BSTR __RPC_FAR *pComment) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Comment( 
            /* [in] */ BSTR pComment) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Host( 
            /* [retval][out] */ BSTR __RPC_FAR *pHost) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_EventKind( 
            /* [retval][out] */ BSTR __RPC_FAR *pEventKind) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Date( 
            /* [retval][out] */ DATE __RPC_FAR *pDate) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_VOB( 
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCHistoryRecordVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCHistoryRecord __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCHistoryRecord __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCHistoryRecord __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCHistoryRecord __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCHistoryRecord __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCHistoryRecord __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCHistoryRecord __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UserLoginName )( 
            ICCHistoryRecord __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pUserLoginName);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UserFullName )( 
            ICCHistoryRecord __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pUserFullName);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Group )( 
            ICCHistoryRecord __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pGroup);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Comment )( 
            ICCHistoryRecord __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pComment);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Comment )( 
            ICCHistoryRecord __RPC_FAR * This,
            /* [in] */ BSTR pComment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Host )( 
            ICCHistoryRecord __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pHost);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EventKind )( 
            ICCHistoryRecord __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pEventKind);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Date )( 
            ICCHistoryRecord __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *pDate);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOB )( 
            ICCHistoryRecord __RPC_FAR * This,
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);
        
        END_INTERFACE
    } ICCHistoryRecordVtbl;

    interface ICCHistoryRecord
    {
        CONST_VTBL struct ICCHistoryRecordVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCHistoryRecord_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCHistoryRecord_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCHistoryRecord_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCHistoryRecord_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCHistoryRecord_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCHistoryRecord_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCHistoryRecord_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCHistoryRecord_get_UserLoginName(This,pUserLoginName)	\
    (This)->lpVtbl -> get_UserLoginName(This,pUserLoginName)

#define ICCHistoryRecord_get_UserFullName(This,pUserFullName)	\
    (This)->lpVtbl -> get_UserFullName(This,pUserFullName)

#define ICCHistoryRecord_get_Group(This,pGroup)	\
    (This)->lpVtbl -> get_Group(This,pGroup)

#define ICCHistoryRecord_get_Comment(This,pComment)	\
    (This)->lpVtbl -> get_Comment(This,pComment)

#define ICCHistoryRecord_put_Comment(This,pComment)	\
    (This)->lpVtbl -> put_Comment(This,pComment)

#define ICCHistoryRecord_get_Host(This,pHost)	\
    (This)->lpVtbl -> get_Host(This,pHost)

#define ICCHistoryRecord_get_EventKind(This,pEventKind)	\
    (This)->lpVtbl -> get_EventKind(This,pEventKind)

#define ICCHistoryRecord_get_Date(This,pDate)	\
    (This)->lpVtbl -> get_Date(This,pDate)

#define ICCHistoryRecord_get_VOB(This,pVOB)	\
    (This)->lpVtbl -> get_VOB(This,pVOB)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHistoryRecord_get_UserLoginName_Proxy( 
    ICCHistoryRecord __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pUserLoginName);


void __RPC_STUB ICCHistoryRecord_get_UserLoginName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHistoryRecord_get_UserFullName_Proxy( 
    ICCHistoryRecord __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pUserFullName);


void __RPC_STUB ICCHistoryRecord_get_UserFullName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHistoryRecord_get_Group_Proxy( 
    ICCHistoryRecord __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pGroup);


void __RPC_STUB ICCHistoryRecord_get_Group_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHistoryRecord_get_Comment_Proxy( 
    ICCHistoryRecord __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pComment);


void __RPC_STUB ICCHistoryRecord_get_Comment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE ICCHistoryRecord_put_Comment_Proxy( 
    ICCHistoryRecord __RPC_FAR * This,
    /* [in] */ BSTR pComment);


void __RPC_STUB ICCHistoryRecord_put_Comment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHistoryRecord_get_Host_Proxy( 
    ICCHistoryRecord __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pHost);


void __RPC_STUB ICCHistoryRecord_get_Host_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHistoryRecord_get_EventKind_Proxy( 
    ICCHistoryRecord __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pEventKind);


void __RPC_STUB ICCHistoryRecord_get_EventKind_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHistoryRecord_get_Date_Proxy( 
    ICCHistoryRecord __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *pDate);


void __RPC_STUB ICCHistoryRecord_get_Date_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHistoryRecord_get_VOB_Proxy( 
    ICCHistoryRecord __RPC_FAR * This,
    /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);


void __RPC_STUB ICCHistoryRecord_get_VOB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCHistoryRecord_INTERFACE_DEFINED__ */


#ifndef __ICCVOB_INTERFACE_DEFINED__
#define __ICCVOB_INTERFACE_DEFINED__

/* interface ICCVOB */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCVOB,0xB22C7ECB,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7ECB-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCVOB : public ICCVOBObject
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_TagName( 
            /* [retval][out] */ BSTR __RPC_FAR *pTagName) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Activity( 
            /* [in] */ BSTR Selector,
            /* [retval][out] */ ICCActivity __RPC_FAR *__RPC_FAR *pActivity) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_AdditionalGroupsStringArray( 
            /* [retval][out] */ VARIANT __RPC_FAR *pAdditionalGroupsStringArray) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_AttributeType( 
            /* [in] */ BSTR Name,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
            /* [retval][out] */ ICCAttributeType __RPC_FAR *__RPC_FAR *pType) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_AttributeTypes( 
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL IncludeObsoletes,
            /* [retval][out] */ ICCAttributeTypes __RPC_FAR *__RPC_FAR *pEnum) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_BranchType( 
            /* [in] */ BSTR Name,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
            /* [retval][out] */ ICCBranchType __RPC_FAR *__RPC_FAR *pType) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_BranchTypes( 
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL IncludeObsoletes,
            /* [retval][out] */ ICCBranchTypes __RPC_FAR *__RPC_FAR *pEnum) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateAttributeType( 
            /* [in] */ BSTR Name,
            /* [defaultvalue][optional][in] */ long ValueType,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Shared,
            /* [defaultvalue][optional][in] */ CCTypeConstraint Constraint,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Global,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Acquire,
            /* [retval][out] */ ICCAttributeType __RPC_FAR *__RPC_FAR *pType) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateBranchType( 
            /* [in] */ BSTR Name,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ CCTypeConstraint Constraint,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Global,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Acquire,
            /* [retval][out] */ ICCBranchType __RPC_FAR *__RPC_FAR *pType) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateHyperlinkType( 
            /* [in] */ BSTR Name,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Shared,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Global,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Acquire,
            /* [retval][out] */ ICCHyperlinkType __RPC_FAR *__RPC_FAR *pType) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateLabelType( 
            /* [in] */ BSTR Name,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Shared,
            /* [defaultvalue][optional][in] */ CCTypeConstraint Constraint,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Global,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Acquire,
            /* [retval][out] */ ICCLabelType __RPC_FAR *__RPC_FAR *pType) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateLock( 
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
            /* [optional][in] */ VARIANT ExemptUsersStringArray) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateTriggerTypeBuilder( 
            /* [retval][out] */ ICCTriggerTypeBuilder __RPC_FAR *__RPC_FAR *pTriggerTypeBuilder) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Group( 
            /* [retval][out] */ BSTR __RPC_FAR *pGroup) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_HasMSDOSTextMode( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pHasMSDOSTextMode) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Host( 
            /* [retval][out] */ BSTR __RPC_FAR *pHost) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Hyperlink( 
            /* [in] */ BSTR IDString,
            /* [retval][out] */ ICCHyperlink __RPC_FAR *__RPC_FAR *pHyperlink) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_HyperlinkType( 
            /* [in] */ BSTR Name,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
            /* [retval][out] */ ICCHyperlinkType __RPC_FAR *__RPC_FAR *pType) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_HyperlinkTypes( 
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL IncludeObsoletes,
            /* [retval][out] */ ICCHyperlinkTypes __RPC_FAR *__RPC_FAR *pEnum) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IsMounted( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsMounted) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_IsMounted( 
            /* [in] */ VARIANT_BOOL pIsMounted) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_IsPersistent( 
            /* [in] */ VARIANT_BOOL rhs) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IsReplicated( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsReplicated) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_LabelType( 
            /* [in] */ BSTR Name,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
            /* [retval][out] */ ICCLabelType __RPC_FAR *__RPC_FAR *pType) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_LabelTypes( 
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL IncludeObsoletes,
            /* [retval][out] */ ICCLabelTypes __RPC_FAR *__RPC_FAR *pEnum) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Lock( 
            /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Locks( 
            /* [defaultvalue][optional][in] */ VARIANT_BOOL IncludeObsoletes,
            /* [retval][out] */ ICCLocks __RPC_FAR *__RPC_FAR *pLocks) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Master( 
            /* [retval][out] */ BSTR __RPC_FAR *pReplica) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_NumberOfAdditionalGroups( 
            /* [retval][out] */ long __RPC_FAR *pNumberOfAdditionalGroups) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_NumberOfReplicas( 
            /* [retval][out] */ long __RPC_FAR *pNumberOfReplicas) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Owner( 
            /* [retval][out] */ BSTR __RPC_FAR *pOwner) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Protect( 
            /* [defaultvalue][optional][in] */ BSTR NewOwner,
            /* [defaultvalue][optional][in] */ BSTR NewGroup,
            /* [optional][in] */ VARIANT GroupsToAddStringArray,
            /* [optional][in] */ VARIANT GroupsToRemoveStringArray) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ReplicasStringArray( 
            /* [retval][out] */ VARIANT __RPC_FAR *pReplicasStringArray) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMaster( 
            /* [in] */ BSTR Replica,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ThisReplica( 
            /* [retval][out] */ BSTR __RPC_FAR *pReplica) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_TriggerType( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ ICCTriggerType __RPC_FAR *__RPC_FAR *pType) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_TriggerTypes( 
            /* [defaultvalue][optional][in] */ VARIANT_BOOL IncludeObsoletes,
            /* [retval][out] */ ICCTriggerTypes __RPC_FAR *__RPC_FAR *pEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCVOBVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCVOB __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCVOB __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCVOB __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCVOB __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCVOB __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCVOB __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCVOB __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attribute )( 
            ICCVOB __RPC_FAR * This,
            /* [in] */ BSTR AttributeType,
            /* [retval][out] */ ICCAttribute __RPC_FAR *__RPC_FAR *pAttribute);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attributes )( 
            ICCVOB __RPC_FAR * This,
            /* [retval][out] */ ICCAttributes __RPC_FAR *__RPC_FAR *pAttributes);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Comment )( 
            ICCVOB __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pComment);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Comment )( 
            ICCVOB __RPC_FAR * This,
            /* [in] */ BSTR pComment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreationRecord )( 
            ICCVOB __RPC_FAR * This,
            /* [retval][out] */ ICCHistoryRecord __RPC_FAR *__RPC_FAR *pHistoryRecord);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HistoryRecords )( 
            ICCVOB __RPC_FAR * This,
            /* [in] */ ICCBranchType __RPC_FAR *pICCBranchType,
            /* [defaultvalue][optional][in] */ DATE Since,
            /* [defaultvalue][optional][in] */ BSTR User,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Minor,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL ExcludeCheckOutEvents,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL DirectoryOnly,
            /* [retval][out] */ ICCHistoryRecords __RPC_FAR *__RPC_FAR *pHistoryRecords);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hyperlinks )( 
            ICCVOB __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR HyperlinkType,
            /* [retval][out] */ ICCHyperlinks __RPC_FAR *__RPC_FAR *pHyperlinks);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OID )( 
            ICCVOB __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOBFamilyUUID )( 
            ICCVOB __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVOBFamilyUUID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TagName )( 
            ICCVOB __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pTagName);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Activity )( 
            ICCVOB __RPC_FAR * This,
            /* [in] */ BSTR Selector,
            /* [retval][out] */ ICCActivity __RPC_FAR *__RPC_FAR *pActivity);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AdditionalGroupsStringArray )( 
            ICCVOB __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pAdditionalGroupsStringArray);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AttributeType )( 
            ICCVOB __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
            /* [retval][out] */ ICCAttributeType __RPC_FAR *__RPC_FAR *pType);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AttributeTypes )( 
            ICCVOB __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL IncludeObsoletes,
            /* [retval][out] */ ICCAttributeTypes __RPC_FAR *__RPC_FAR *pEnum);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BranchType )( 
            ICCVOB __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
            /* [retval][out] */ ICCBranchType __RPC_FAR *__RPC_FAR *pType);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BranchTypes )( 
            ICCVOB __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL IncludeObsoletes,
            /* [retval][out] */ ICCBranchTypes __RPC_FAR *__RPC_FAR *pEnum);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateAttributeType )( 
            ICCVOB __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [defaultvalue][optional][in] */ long ValueType,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Shared,
            /* [defaultvalue][optional][in] */ CCTypeConstraint Constraint,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Global,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Acquire,
            /* [retval][out] */ ICCAttributeType __RPC_FAR *__RPC_FAR *pType);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateBranchType )( 
            ICCVOB __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ CCTypeConstraint Constraint,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Global,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Acquire,
            /* [retval][out] */ ICCBranchType __RPC_FAR *__RPC_FAR *pType);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateHyperlinkType )( 
            ICCVOB __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Shared,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Global,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Acquire,
            /* [retval][out] */ ICCHyperlinkType __RPC_FAR *__RPC_FAR *pType);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateLabelType )( 
            ICCVOB __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Shared,
            /* [defaultvalue][optional][in] */ CCTypeConstraint Constraint,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Global,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Acquire,
            /* [retval][out] */ ICCLabelType __RPC_FAR *__RPC_FAR *pType);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateLock )( 
            ICCVOB __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
            /* [optional][in] */ VARIANT ExemptUsersStringArray);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateTriggerTypeBuilder )( 
            ICCVOB __RPC_FAR * This,
            /* [retval][out] */ ICCTriggerTypeBuilder __RPC_FAR *__RPC_FAR *pTriggerTypeBuilder);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Group )( 
            ICCVOB __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pGroup);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HasMSDOSTextMode )( 
            ICCVOB __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pHasMSDOSTextMode);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Host )( 
            ICCVOB __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pHost);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hyperlink )( 
            ICCVOB __RPC_FAR * This,
            /* [in] */ BSTR IDString,
            /* [retval][out] */ ICCHyperlink __RPC_FAR *__RPC_FAR *pHyperlink);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HyperlinkType )( 
            ICCVOB __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
            /* [retval][out] */ ICCHyperlinkType __RPC_FAR *__RPC_FAR *pType);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HyperlinkTypes )( 
            ICCVOB __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL IncludeObsoletes,
            /* [retval][out] */ ICCHyperlinkTypes __RPC_FAR *__RPC_FAR *pEnum);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsMounted )( 
            ICCVOB __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsMounted);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IsMounted )( 
            ICCVOB __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pIsMounted);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IsPersistent )( 
            ICCVOB __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL rhs);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsReplicated )( 
            ICCVOB __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsReplicated);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LabelType )( 
            ICCVOB __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
            /* [retval][out] */ ICCLabelType __RPC_FAR *__RPC_FAR *pType);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LabelTypes )( 
            ICCVOB __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL IncludeObsoletes,
            /* [retval][out] */ ICCLabelTypes __RPC_FAR *__RPC_FAR *pEnum);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Lock )( 
            ICCVOB __RPC_FAR * This,
            /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Locks )( 
            ICCVOB __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL IncludeObsoletes,
            /* [retval][out] */ ICCLocks __RPC_FAR *__RPC_FAR *pLocks);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Master )( 
            ICCVOB __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pReplica);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumberOfAdditionalGroups )( 
            ICCVOB __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pNumberOfAdditionalGroups);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumberOfReplicas )( 
            ICCVOB __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pNumberOfReplicas);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Owner )( 
            ICCVOB __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOwner);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Protect )( 
            ICCVOB __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR NewOwner,
            /* [defaultvalue][optional][in] */ BSTR NewGroup,
            /* [optional][in] */ VARIANT GroupsToAddStringArray,
            /* [optional][in] */ VARIANT GroupsToRemoveStringArray);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReplicasStringArray )( 
            ICCVOB __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pReplicasStringArray);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMaster )( 
            ICCVOB __RPC_FAR * This,
            /* [in] */ BSTR Replica,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ThisReplica )( 
            ICCVOB __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pReplica);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TriggerType )( 
            ICCVOB __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ ICCTriggerType __RPC_FAR *__RPC_FAR *pType);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TriggerTypes )( 
            ICCVOB __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL IncludeObsoletes,
            /* [retval][out] */ ICCTriggerTypes __RPC_FAR *__RPC_FAR *pEnum);
        
        END_INTERFACE
    } ICCVOBVtbl;

    interface ICCVOB
    {
        CONST_VTBL struct ICCVOBVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCVOB_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCVOB_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCVOB_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCVOB_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCVOB_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCVOB_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCVOB_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCVOB_get_Attribute(This,AttributeType,pAttribute)	\
    (This)->lpVtbl -> get_Attribute(This,AttributeType,pAttribute)

#define ICCVOB_get_Attributes(This,pAttributes)	\
    (This)->lpVtbl -> get_Attributes(This,pAttributes)

#define ICCVOB_get_Comment(This,pComment)	\
    (This)->lpVtbl -> get_Comment(This,pComment)

#define ICCVOB_put_Comment(This,pComment)	\
    (This)->lpVtbl -> put_Comment(This,pComment)

#define ICCVOB_get_CreationRecord(This,pHistoryRecord)	\
    (This)->lpVtbl -> get_CreationRecord(This,pHistoryRecord)

#define ICCVOB_get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)	\
    (This)->lpVtbl -> get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)

#define ICCVOB_get_Hyperlinks(This,HyperlinkType,pHyperlinks)	\
    (This)->lpVtbl -> get_Hyperlinks(This,HyperlinkType,pHyperlinks)

#define ICCVOB_get_OID(This,pOID)	\
    (This)->lpVtbl -> get_OID(This,pOID)

#define ICCVOB_get_VOBFamilyUUID(This,pVOBFamilyUUID)	\
    (This)->lpVtbl -> get_VOBFamilyUUID(This,pVOBFamilyUUID)


#define ICCVOB_get_TagName(This,pTagName)	\
    (This)->lpVtbl -> get_TagName(This,pTagName)

#define ICCVOB_get_Activity(This,Selector,pActivity)	\
    (This)->lpVtbl -> get_Activity(This,Selector,pActivity)

#define ICCVOB_get_AdditionalGroupsStringArray(This,pAdditionalGroupsStringArray)	\
    (This)->lpVtbl -> get_AdditionalGroupsStringArray(This,pAdditionalGroupsStringArray)

#define ICCVOB_get_AttributeType(This,Name,Local,pType)	\
    (This)->lpVtbl -> get_AttributeType(This,Name,Local,pType)

#define ICCVOB_get_AttributeTypes(This,Local,IncludeObsoletes,pEnum)	\
    (This)->lpVtbl -> get_AttributeTypes(This,Local,IncludeObsoletes,pEnum)

#define ICCVOB_get_BranchType(This,Name,Local,pType)	\
    (This)->lpVtbl -> get_BranchType(This,Name,Local,pType)

#define ICCVOB_get_BranchTypes(This,Local,IncludeObsoletes,pEnum)	\
    (This)->lpVtbl -> get_BranchTypes(This,Local,IncludeObsoletes,pEnum)

#define ICCVOB_CreateAttributeType(This,Name,ValueType,Comment,Shared,Constraint,Global,Acquire,pType)	\
    (This)->lpVtbl -> CreateAttributeType(This,Name,ValueType,Comment,Shared,Constraint,Global,Acquire,pType)

#define ICCVOB_CreateBranchType(This,Name,Comment,Constraint,Global,Acquire,pType)	\
    (This)->lpVtbl -> CreateBranchType(This,Name,Comment,Constraint,Global,Acquire,pType)

#define ICCVOB_CreateHyperlinkType(This,Name,Comment,Shared,Global,Acquire,pType)	\
    (This)->lpVtbl -> CreateHyperlinkType(This,Name,Comment,Shared,Global,Acquire,pType)

#define ICCVOB_CreateLabelType(This,Name,Comment,Shared,Constraint,Global,Acquire,pType)	\
    (This)->lpVtbl -> CreateLabelType(This,Name,Comment,Shared,Constraint,Global,Acquire,pType)

#define ICCVOB_CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)	\
    (This)->lpVtbl -> CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)

#define ICCVOB_CreateTriggerTypeBuilder(This,pTriggerTypeBuilder)	\
    (This)->lpVtbl -> CreateTriggerTypeBuilder(This,pTriggerTypeBuilder)

#define ICCVOB_get_Group(This,pGroup)	\
    (This)->lpVtbl -> get_Group(This,pGroup)

#define ICCVOB_get_HasMSDOSTextMode(This,pHasMSDOSTextMode)	\
    (This)->lpVtbl -> get_HasMSDOSTextMode(This,pHasMSDOSTextMode)

#define ICCVOB_get_Host(This,pHost)	\
    (This)->lpVtbl -> get_Host(This,pHost)

#define ICCVOB_get_Hyperlink(This,IDString,pHyperlink)	\
    (This)->lpVtbl -> get_Hyperlink(This,IDString,pHyperlink)

#define ICCVOB_get_HyperlinkType(This,Name,Local,pType)	\
    (This)->lpVtbl -> get_HyperlinkType(This,Name,Local,pType)

#define ICCVOB_get_HyperlinkTypes(This,Local,IncludeObsoletes,pEnum)	\
    (This)->lpVtbl -> get_HyperlinkTypes(This,Local,IncludeObsoletes,pEnum)

#define ICCVOB_get_IsMounted(This,pIsMounted)	\
    (This)->lpVtbl -> get_IsMounted(This,pIsMounted)

#define ICCVOB_put_IsMounted(This,pIsMounted)	\
    (This)->lpVtbl -> put_IsMounted(This,pIsMounted)

#define ICCVOB_put_IsPersistent(This,rhs)	\
    (This)->lpVtbl -> put_IsPersistent(This,rhs)

#define ICCVOB_get_IsReplicated(This,pIsReplicated)	\
    (This)->lpVtbl -> get_IsReplicated(This,pIsReplicated)

#define ICCVOB_get_LabelType(This,Name,Local,pType)	\
    (This)->lpVtbl -> get_LabelType(This,Name,Local,pType)

#define ICCVOB_get_LabelTypes(This,Local,IncludeObsoletes,pEnum)	\
    (This)->lpVtbl -> get_LabelTypes(This,Local,IncludeObsoletes,pEnum)

#define ICCVOB_get_Lock(This,pLock)	\
    (This)->lpVtbl -> get_Lock(This,pLock)

#define ICCVOB_get_Locks(This,IncludeObsoletes,pLocks)	\
    (This)->lpVtbl -> get_Locks(This,IncludeObsoletes,pLocks)

#define ICCVOB_get_Master(This,pReplica)	\
    (This)->lpVtbl -> get_Master(This,pReplica)

#define ICCVOB_get_NumberOfAdditionalGroups(This,pNumberOfAdditionalGroups)	\
    (This)->lpVtbl -> get_NumberOfAdditionalGroups(This,pNumberOfAdditionalGroups)

#define ICCVOB_get_NumberOfReplicas(This,pNumberOfReplicas)	\
    (This)->lpVtbl -> get_NumberOfReplicas(This,pNumberOfReplicas)

#define ICCVOB_get_Owner(This,pOwner)	\
    (This)->lpVtbl -> get_Owner(This,pOwner)

#define ICCVOB_Protect(This,NewOwner,NewGroup,GroupsToAddStringArray,GroupsToRemoveStringArray)	\
    (This)->lpVtbl -> Protect(This,NewOwner,NewGroup,GroupsToAddStringArray,GroupsToRemoveStringArray)

#define ICCVOB_get_ReplicasStringArray(This,pReplicasStringArray)	\
    (This)->lpVtbl -> get_ReplicasStringArray(This,pReplicasStringArray)

#define ICCVOB_SetMaster(This,Replica,Comment)	\
    (This)->lpVtbl -> SetMaster(This,Replica,Comment)

#define ICCVOB_get_ThisReplica(This,pReplica)	\
    (This)->lpVtbl -> get_ThisReplica(This,pReplica)

#define ICCVOB_get_TriggerType(This,Name,pType)	\
    (This)->lpVtbl -> get_TriggerType(This,Name,pType)

#define ICCVOB_get_TriggerTypes(This,IncludeObsoletes,pEnum)	\
    (This)->lpVtbl -> get_TriggerTypes(This,IncludeObsoletes,pEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_get_TagName_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pTagName);


void __RPC_STUB ICCVOB_get_TagName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_get_Activity_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [in] */ BSTR Selector,
    /* [retval][out] */ ICCActivity __RPC_FAR *__RPC_FAR *pActivity);


void __RPC_STUB ICCVOB_get_Activity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_get_AdditionalGroupsStringArray_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pAdditionalGroupsStringArray);


void __RPC_STUB ICCVOB_get_AdditionalGroupsStringArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_get_AttributeType_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
    /* [retval][out] */ ICCAttributeType __RPC_FAR *__RPC_FAR *pType);


void __RPC_STUB ICCVOB_get_AttributeType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_get_AttributeTypes_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL IncludeObsoletes,
    /* [retval][out] */ ICCAttributeTypes __RPC_FAR *__RPC_FAR *pEnum);


void __RPC_STUB ICCVOB_get_AttributeTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_get_BranchType_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
    /* [retval][out] */ ICCBranchType __RPC_FAR *__RPC_FAR *pType);


void __RPC_STUB ICCVOB_get_BranchType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_get_BranchTypes_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL IncludeObsoletes,
    /* [retval][out] */ ICCBranchTypes __RPC_FAR *__RPC_FAR *pEnum);


void __RPC_STUB ICCVOB_get_BranchTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_CreateAttributeType_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [defaultvalue][optional][in] */ long ValueType,
    /* [defaultvalue][optional][in] */ BSTR Comment,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Shared,
    /* [defaultvalue][optional][in] */ CCTypeConstraint Constraint,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Global,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Acquire,
    /* [retval][out] */ ICCAttributeType __RPC_FAR *__RPC_FAR *pType);


void __RPC_STUB ICCVOB_CreateAttributeType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_CreateBranchType_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [defaultvalue][optional][in] */ BSTR Comment,
    /* [defaultvalue][optional][in] */ CCTypeConstraint Constraint,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Global,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Acquire,
    /* [retval][out] */ ICCBranchType __RPC_FAR *__RPC_FAR *pType);


void __RPC_STUB ICCVOB_CreateBranchType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_CreateHyperlinkType_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [defaultvalue][optional][in] */ BSTR Comment,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Shared,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Global,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Acquire,
    /* [retval][out] */ ICCHyperlinkType __RPC_FAR *__RPC_FAR *pType);


void __RPC_STUB ICCVOB_CreateHyperlinkType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_CreateLabelType_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [defaultvalue][optional][in] */ BSTR Comment,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Shared,
    /* [defaultvalue][optional][in] */ CCTypeConstraint Constraint,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Global,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Acquire,
    /* [retval][out] */ ICCLabelType __RPC_FAR *__RPC_FAR *pType);


void __RPC_STUB ICCVOB_CreateLabelType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_CreateLock_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Comment,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
    /* [optional][in] */ VARIANT ExemptUsersStringArray);


void __RPC_STUB ICCVOB_CreateLock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_CreateTriggerTypeBuilder_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [retval][out] */ ICCTriggerTypeBuilder __RPC_FAR *__RPC_FAR *pTriggerTypeBuilder);


void __RPC_STUB ICCVOB_CreateTriggerTypeBuilder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_get_Group_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pGroup);


void __RPC_STUB ICCVOB_get_Group_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_get_HasMSDOSTextMode_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pHasMSDOSTextMode);


void __RPC_STUB ICCVOB_get_HasMSDOSTextMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_get_Host_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pHost);


void __RPC_STUB ICCVOB_get_Host_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_get_Hyperlink_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [in] */ BSTR IDString,
    /* [retval][out] */ ICCHyperlink __RPC_FAR *__RPC_FAR *pHyperlink);


void __RPC_STUB ICCVOB_get_Hyperlink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_get_HyperlinkType_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
    /* [retval][out] */ ICCHyperlinkType __RPC_FAR *__RPC_FAR *pType);


void __RPC_STUB ICCVOB_get_HyperlinkType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_get_HyperlinkTypes_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL IncludeObsoletes,
    /* [retval][out] */ ICCHyperlinkTypes __RPC_FAR *__RPC_FAR *pEnum);


void __RPC_STUB ICCVOB_get_HyperlinkTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_get_IsMounted_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsMounted);


void __RPC_STUB ICCVOB_get_IsMounted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_put_IsMounted_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL pIsMounted);


void __RPC_STUB ICCVOB_put_IsMounted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_put_IsPersistent_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL rhs);


void __RPC_STUB ICCVOB_put_IsPersistent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_get_IsReplicated_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsReplicated);


void __RPC_STUB ICCVOB_get_IsReplicated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_get_LabelType_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
    /* [retval][out] */ ICCLabelType __RPC_FAR *__RPC_FAR *pType);


void __RPC_STUB ICCVOB_get_LabelType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_get_LabelTypes_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL IncludeObsoletes,
    /* [retval][out] */ ICCLabelTypes __RPC_FAR *__RPC_FAR *pEnum);


void __RPC_STUB ICCVOB_get_LabelTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_get_Lock_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock);


void __RPC_STUB ICCVOB_get_Lock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_get_Locks_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL IncludeObsoletes,
    /* [retval][out] */ ICCLocks __RPC_FAR *__RPC_FAR *pLocks);


void __RPC_STUB ICCVOB_get_Locks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_get_Master_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pReplica);


void __RPC_STUB ICCVOB_get_Master_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_get_NumberOfAdditionalGroups_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pNumberOfAdditionalGroups);


void __RPC_STUB ICCVOB_get_NumberOfAdditionalGroups_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_get_NumberOfReplicas_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pNumberOfReplicas);


void __RPC_STUB ICCVOB_get_NumberOfReplicas_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_get_Owner_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pOwner);


void __RPC_STUB ICCVOB_get_Owner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_Protect_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR NewOwner,
    /* [defaultvalue][optional][in] */ BSTR NewGroup,
    /* [optional][in] */ VARIANT GroupsToAddStringArray,
    /* [optional][in] */ VARIANT GroupsToRemoveStringArray);


void __RPC_STUB ICCVOB_Protect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_get_ReplicasStringArray_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pReplicasStringArray);


void __RPC_STUB ICCVOB_get_ReplicasStringArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_SetMaster_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [in] */ BSTR Replica,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCVOB_SetMaster_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_get_ThisReplica_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pReplica);


void __RPC_STUB ICCVOB_get_ThisReplica_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_get_TriggerType_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [retval][out] */ ICCTriggerType __RPC_FAR *__RPC_FAR *pType);


void __RPC_STUB ICCVOB_get_TriggerType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOB_get_TriggerTypes_Proxy( 
    ICCVOB __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL IncludeObsoletes,
    /* [retval][out] */ ICCTriggerTypes __RPC_FAR *__RPC_FAR *pEnum);


void __RPC_STUB ICCVOB_get_TriggerTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCVOB_INTERFACE_DEFINED__ */


#ifndef __ICCAttributeTypes_INTERFACE_DEFINED__
#define __ICCAttributeTypes_INTERFACE_DEFINED__

/* interface ICCAttributeTypes */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCAttributeTypes,0xB22C7EEC,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7EEC-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCAttributeTypes : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long index,
            /* [retval][out] */ ICCAttributeType __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ICCAttributeType __RPC_FAR *pAttributeType) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long index) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCAttributeTypesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCAttributeTypes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCAttributeTypes __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCAttributeTypes __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCAttributeTypes __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCAttributeTypes __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCAttributeTypes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCAttributeTypes __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ICCAttributeTypes __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ ICCAttributeType __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            ICCAttributeTypes __RPC_FAR * This,
            /* [in] */ ICCAttributeType __RPC_FAR *pAttributeType);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ICCAttributeTypes __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ICCAttributeTypes __RPC_FAR * This,
            /* [in] */ long index);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ICCAttributeTypes __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);
        
        END_INTERFACE
    } ICCAttributeTypesVtbl;

    interface ICCAttributeTypes
    {
        CONST_VTBL struct ICCAttributeTypesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCAttributeTypes_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCAttributeTypes_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCAttributeTypes_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCAttributeTypes_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCAttributeTypes_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCAttributeTypes_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCAttributeTypes_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCAttributeTypes_get_Item(This,index,pItem)	\
    (This)->lpVtbl -> get_Item(This,index,pItem)

#define ICCAttributeTypes_Add(This,pAttributeType)	\
    (This)->lpVtbl -> Add(This,pAttributeType)

#define ICCAttributeTypes_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define ICCAttributeTypes_Remove(This,index)	\
    (This)->lpVtbl -> Remove(This,index)

#define ICCAttributeTypes_get__NewEnum(This,pEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,pEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeTypes_get_Item_Proxy( 
    ICCAttributeTypes __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ ICCAttributeType __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB ICCAttributeTypes_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeTypes_Add_Proxy( 
    ICCAttributeTypes __RPC_FAR * This,
    /* [in] */ ICCAttributeType __RPC_FAR *pAttributeType);


void __RPC_STUB ICCAttributeTypes_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeTypes_get_Count_Proxy( 
    ICCAttributeTypes __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB ICCAttributeTypes_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeTypes_Remove_Proxy( 
    ICCAttributeTypes __RPC_FAR * This,
    /* [in] */ long index);


void __RPC_STUB ICCAttributeTypes_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICCAttributeTypes_get__NewEnum_Proxy( 
    ICCAttributeTypes __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);


void __RPC_STUB ICCAttributeTypes_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCAttributeTypes_INTERFACE_DEFINED__ */


#ifndef __ICCBranchType_INTERFACE_DEFINED__
#define __ICCBranchType_INTERFACE_DEFINED__

/* interface ICCBranchType */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCBranchType,0xB22C7EE7,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7EE7-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCBranchType : public ICCVOBObject
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pName) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Apply( 
            /* [in] */ ICCVersion __RPC_FAR *pVersion,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [retval][out] */ ICCCheckedOutFile __RPC_FAR *__RPC_FAR *pCheckedOutFile) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ApplyNoCheckOut( 
            /* [in] */ ICCVersion __RPC_FAR *pVersion,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Constraint( 
            /* [retval][out] */ CCTypeConstraint __RPC_FAR *pConstraint) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateLock( 
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
            /* [optional][in] */ VARIANT ExemptUsersStringArray) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Group( 
            /* [retval][out] */ BSTR __RPC_FAR *pGroup) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Lock( 
            /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Master( 
            /* [retval][out] */ BSTR __RPC_FAR *pReplica) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Owner( 
            /* [retval][out] */ BSTR __RPC_FAR *pOwner) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveType( 
            /* [defaultvalue][optional][in] */ VARIANT_BOOL RemoveAllInstances = 0,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Scope( 
            /* [retval][out] */ CCTypeScope __RPC_FAR *pScope) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetConstraint( 
            /* [in] */ CCTypeConstraint NewConstraint,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetGroup( 
            /* [in] */ BSTR NewGroup,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMaster( 
            /* [in] */ BSTR Replica,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetName( 
            /* [in] */ BSTR NewName,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetOwner( 
            /* [in] */ BSTR NewOwner,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetScope( 
            /* [in] */ VARIANT_BOOL Global,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Acquire = 0,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_VOB( 
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCBranchTypeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCBranchType __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCBranchType __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCBranchType __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCBranchType __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCBranchType __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCBranchType __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCBranchType __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attribute )( 
            ICCBranchType __RPC_FAR * This,
            /* [in] */ BSTR AttributeType,
            /* [retval][out] */ ICCAttribute __RPC_FAR *__RPC_FAR *pAttribute);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attributes )( 
            ICCBranchType __RPC_FAR * This,
            /* [retval][out] */ ICCAttributes __RPC_FAR *__RPC_FAR *pAttributes);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Comment )( 
            ICCBranchType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pComment);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Comment )( 
            ICCBranchType __RPC_FAR * This,
            /* [in] */ BSTR pComment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreationRecord )( 
            ICCBranchType __RPC_FAR * This,
            /* [retval][out] */ ICCHistoryRecord __RPC_FAR *__RPC_FAR *pHistoryRecord);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HistoryRecords )( 
            ICCBranchType __RPC_FAR * This,
            /* [in] */ ICCBranchType __RPC_FAR *pICCBranchType,
            /* [defaultvalue][optional][in] */ DATE Since,
            /* [defaultvalue][optional][in] */ BSTR User,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Minor,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL ExcludeCheckOutEvents,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL DirectoryOnly,
            /* [retval][out] */ ICCHistoryRecords __RPC_FAR *__RPC_FAR *pHistoryRecords);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hyperlinks )( 
            ICCBranchType __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR HyperlinkType,
            /* [retval][out] */ ICCHyperlinks __RPC_FAR *__RPC_FAR *pHyperlinks);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OID )( 
            ICCBranchType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOBFamilyUUID )( 
            ICCBranchType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVOBFamilyUUID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ICCBranchType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Apply )( 
            ICCBranchType __RPC_FAR * This,
            /* [in] */ ICCVersion __RPC_FAR *pVersion,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [retval][out] */ ICCCheckedOutFile __RPC_FAR *__RPC_FAR *pCheckedOutFile);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ApplyNoCheckOut )( 
            ICCBranchType __RPC_FAR * This,
            /* [in] */ ICCVersion __RPC_FAR *pVersion,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Constraint )( 
            ICCBranchType __RPC_FAR * This,
            /* [retval][out] */ CCTypeConstraint __RPC_FAR *pConstraint);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateLock )( 
            ICCBranchType __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
            /* [optional][in] */ VARIANT ExemptUsersStringArray);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Group )( 
            ICCBranchType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pGroup);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Lock )( 
            ICCBranchType __RPC_FAR * This,
            /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Master )( 
            ICCBranchType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pReplica);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Owner )( 
            ICCBranchType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOwner);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveType )( 
            ICCBranchType __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL RemoveAllInstances,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Scope )( 
            ICCBranchType __RPC_FAR * This,
            /* [retval][out] */ CCTypeScope __RPC_FAR *pScope);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConstraint )( 
            ICCBranchType __RPC_FAR * This,
            /* [in] */ CCTypeConstraint NewConstraint,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGroup )( 
            ICCBranchType __RPC_FAR * This,
            /* [in] */ BSTR NewGroup,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMaster )( 
            ICCBranchType __RPC_FAR * This,
            /* [in] */ BSTR Replica,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetName )( 
            ICCBranchType __RPC_FAR * This,
            /* [in] */ BSTR NewName,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOwner )( 
            ICCBranchType __RPC_FAR * This,
            /* [in] */ BSTR NewOwner,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetScope )( 
            ICCBranchType __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Global,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Acquire,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOB )( 
            ICCBranchType __RPC_FAR * This,
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);
        
        END_INTERFACE
    } ICCBranchTypeVtbl;

    interface ICCBranchType
    {
        CONST_VTBL struct ICCBranchTypeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCBranchType_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCBranchType_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCBranchType_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCBranchType_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCBranchType_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCBranchType_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCBranchType_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCBranchType_get_Attribute(This,AttributeType,pAttribute)	\
    (This)->lpVtbl -> get_Attribute(This,AttributeType,pAttribute)

#define ICCBranchType_get_Attributes(This,pAttributes)	\
    (This)->lpVtbl -> get_Attributes(This,pAttributes)

#define ICCBranchType_get_Comment(This,pComment)	\
    (This)->lpVtbl -> get_Comment(This,pComment)

#define ICCBranchType_put_Comment(This,pComment)	\
    (This)->lpVtbl -> put_Comment(This,pComment)

#define ICCBranchType_get_CreationRecord(This,pHistoryRecord)	\
    (This)->lpVtbl -> get_CreationRecord(This,pHistoryRecord)

#define ICCBranchType_get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)	\
    (This)->lpVtbl -> get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)

#define ICCBranchType_get_Hyperlinks(This,HyperlinkType,pHyperlinks)	\
    (This)->lpVtbl -> get_Hyperlinks(This,HyperlinkType,pHyperlinks)

#define ICCBranchType_get_OID(This,pOID)	\
    (This)->lpVtbl -> get_OID(This,pOID)

#define ICCBranchType_get_VOBFamilyUUID(This,pVOBFamilyUUID)	\
    (This)->lpVtbl -> get_VOBFamilyUUID(This,pVOBFamilyUUID)


#define ICCBranchType_get_Name(This,pName)	\
    (This)->lpVtbl -> get_Name(This,pName)

#define ICCBranchType_Apply(This,pVersion,Comment,pCheckedOutFile)	\
    (This)->lpVtbl -> Apply(This,pVersion,Comment,pCheckedOutFile)

#define ICCBranchType_ApplyNoCheckOut(This,pVersion,Comment)	\
    (This)->lpVtbl -> ApplyNoCheckOut(This,pVersion,Comment)

#define ICCBranchType_get_Constraint(This,pConstraint)	\
    (This)->lpVtbl -> get_Constraint(This,pConstraint)

#define ICCBranchType_CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)	\
    (This)->lpVtbl -> CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)

#define ICCBranchType_get_Group(This,pGroup)	\
    (This)->lpVtbl -> get_Group(This,pGroup)

#define ICCBranchType_get_Lock(This,pLock)	\
    (This)->lpVtbl -> get_Lock(This,pLock)

#define ICCBranchType_get_Master(This,pReplica)	\
    (This)->lpVtbl -> get_Master(This,pReplica)

#define ICCBranchType_get_Owner(This,pOwner)	\
    (This)->lpVtbl -> get_Owner(This,pOwner)

#define ICCBranchType_RemoveType(This,RemoveAllInstances,Comment)	\
    (This)->lpVtbl -> RemoveType(This,RemoveAllInstances,Comment)

#define ICCBranchType_get_Scope(This,pScope)	\
    (This)->lpVtbl -> get_Scope(This,pScope)

#define ICCBranchType_SetConstraint(This,NewConstraint,Comment)	\
    (This)->lpVtbl -> SetConstraint(This,NewConstraint,Comment)

#define ICCBranchType_SetGroup(This,NewGroup,Comment)	\
    (This)->lpVtbl -> SetGroup(This,NewGroup,Comment)

#define ICCBranchType_SetMaster(This,Replica,Comment)	\
    (This)->lpVtbl -> SetMaster(This,Replica,Comment)

#define ICCBranchType_SetName(This,NewName,Comment)	\
    (This)->lpVtbl -> SetName(This,NewName,Comment)

#define ICCBranchType_SetOwner(This,NewOwner,Comment)	\
    (This)->lpVtbl -> SetOwner(This,NewOwner,Comment)

#define ICCBranchType_SetScope(This,Global,Acquire,Comment)	\
    (This)->lpVtbl -> SetScope(This,Global,Acquire,Comment)

#define ICCBranchType_get_VOB(This,pVOB)	\
    (This)->lpVtbl -> get_VOB(This,pVOB)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBranchType_get_Name_Proxy( 
    ICCBranchType __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pName);


void __RPC_STUB ICCBranchType_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCBranchType_Apply_Proxy( 
    ICCBranchType __RPC_FAR * This,
    /* [in] */ ICCVersion __RPC_FAR *pVersion,
    /* [defaultvalue][optional][in] */ BSTR Comment,
    /* [retval][out] */ ICCCheckedOutFile __RPC_FAR *__RPC_FAR *pCheckedOutFile);


void __RPC_STUB ICCBranchType_Apply_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCBranchType_ApplyNoCheckOut_Proxy( 
    ICCBranchType __RPC_FAR * This,
    /* [in] */ ICCVersion __RPC_FAR *pVersion,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCBranchType_ApplyNoCheckOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBranchType_get_Constraint_Proxy( 
    ICCBranchType __RPC_FAR * This,
    /* [retval][out] */ CCTypeConstraint __RPC_FAR *pConstraint);


void __RPC_STUB ICCBranchType_get_Constraint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCBranchType_CreateLock_Proxy( 
    ICCBranchType __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Comment,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
    /* [optional][in] */ VARIANT ExemptUsersStringArray);


void __RPC_STUB ICCBranchType_CreateLock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBranchType_get_Group_Proxy( 
    ICCBranchType __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pGroup);


void __RPC_STUB ICCBranchType_get_Group_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBranchType_get_Lock_Proxy( 
    ICCBranchType __RPC_FAR * This,
    /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock);


void __RPC_STUB ICCBranchType_get_Lock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBranchType_get_Master_Proxy( 
    ICCBranchType __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pReplica);


void __RPC_STUB ICCBranchType_get_Master_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBranchType_get_Owner_Proxy( 
    ICCBranchType __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pOwner);


void __RPC_STUB ICCBranchType_get_Owner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCBranchType_RemoveType_Proxy( 
    ICCBranchType __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL RemoveAllInstances,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCBranchType_RemoveType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBranchType_get_Scope_Proxy( 
    ICCBranchType __RPC_FAR * This,
    /* [retval][out] */ CCTypeScope __RPC_FAR *pScope);


void __RPC_STUB ICCBranchType_get_Scope_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCBranchType_SetConstraint_Proxy( 
    ICCBranchType __RPC_FAR * This,
    /* [in] */ CCTypeConstraint NewConstraint,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCBranchType_SetConstraint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCBranchType_SetGroup_Proxy( 
    ICCBranchType __RPC_FAR * This,
    /* [in] */ BSTR NewGroup,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCBranchType_SetGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCBranchType_SetMaster_Proxy( 
    ICCBranchType __RPC_FAR * This,
    /* [in] */ BSTR Replica,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCBranchType_SetMaster_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCBranchType_SetName_Proxy( 
    ICCBranchType __RPC_FAR * This,
    /* [in] */ BSTR NewName,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCBranchType_SetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCBranchType_SetOwner_Proxy( 
    ICCBranchType __RPC_FAR * This,
    /* [in] */ BSTR NewOwner,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCBranchType_SetOwner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCBranchType_SetScope_Proxy( 
    ICCBranchType __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Global,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Acquire,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCBranchType_SetScope_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBranchType_get_VOB_Proxy( 
    ICCBranchType __RPC_FAR * This,
    /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);


void __RPC_STUB ICCBranchType_get_VOB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCBranchType_INTERFACE_DEFINED__ */


#ifndef __ICCFile_INTERFACE_DEFINED__
#define __ICCFile_INTERFACE_DEFINED__

/* interface ICCFile */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCFile,0xB22C7ED1,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7ED1-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCFile : public ICCVOBObject
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Path( 
            /* [retval][out] */ BSTR __RPC_FAR *pPath) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ExtendedPath( 
            /* [retval][out] */ BSTR __RPC_FAR *pExtendedPath) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ExtendedPathInView( 
            /* [in] */ ICCView __RPC_FAR *pView,
            /* [retval][out] */ BSTR __RPC_FAR *pExtendedPath) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IsDirectory( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsDirectory) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_PathInView( 
            /* [in] */ ICCView __RPC_FAR *pView,
            /* [retval][out] */ BSTR __RPC_FAR *pPath) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_View( 
            /* [retval][out] */ ICCView __RPC_FAR *__RPC_FAR *pView) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_VOB( 
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCFileVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCFile __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCFile __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCFile __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCFile __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCFile __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCFile __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCFile __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attribute )( 
            ICCFile __RPC_FAR * This,
            /* [in] */ BSTR AttributeType,
            /* [retval][out] */ ICCAttribute __RPC_FAR *__RPC_FAR *pAttribute);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attributes )( 
            ICCFile __RPC_FAR * This,
            /* [retval][out] */ ICCAttributes __RPC_FAR *__RPC_FAR *pAttributes);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Comment )( 
            ICCFile __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pComment);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Comment )( 
            ICCFile __RPC_FAR * This,
            /* [in] */ BSTR pComment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreationRecord )( 
            ICCFile __RPC_FAR * This,
            /* [retval][out] */ ICCHistoryRecord __RPC_FAR *__RPC_FAR *pHistoryRecord);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HistoryRecords )( 
            ICCFile __RPC_FAR * This,
            /* [in] */ ICCBranchType __RPC_FAR *pICCBranchType,
            /* [defaultvalue][optional][in] */ DATE Since,
            /* [defaultvalue][optional][in] */ BSTR User,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Minor,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL ExcludeCheckOutEvents,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL DirectoryOnly,
            /* [retval][out] */ ICCHistoryRecords __RPC_FAR *__RPC_FAR *pHistoryRecords);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hyperlinks )( 
            ICCFile __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR HyperlinkType,
            /* [retval][out] */ ICCHyperlinks __RPC_FAR *__RPC_FAR *pHyperlinks);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OID )( 
            ICCFile __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOBFamilyUUID )( 
            ICCFile __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVOBFamilyUUID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Path )( 
            ICCFile __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pPath);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExtendedPath )( 
            ICCFile __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pExtendedPath);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExtendedPathInView )( 
            ICCFile __RPC_FAR * This,
            /* [in] */ ICCView __RPC_FAR *pView,
            /* [retval][out] */ BSTR __RPC_FAR *pExtendedPath);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsDirectory )( 
            ICCFile __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsDirectory);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PathInView )( 
            ICCFile __RPC_FAR * This,
            /* [in] */ ICCView __RPC_FAR *pView,
            /* [retval][out] */ BSTR __RPC_FAR *pPath);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_View )( 
            ICCFile __RPC_FAR * This,
            /* [retval][out] */ ICCView __RPC_FAR *__RPC_FAR *pView);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOB )( 
            ICCFile __RPC_FAR * This,
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);
        
        END_INTERFACE
    } ICCFileVtbl;

    interface ICCFile
    {
        CONST_VTBL struct ICCFileVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCFile_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCFile_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCFile_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCFile_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCFile_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCFile_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCFile_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCFile_get_Attribute(This,AttributeType,pAttribute)	\
    (This)->lpVtbl -> get_Attribute(This,AttributeType,pAttribute)

#define ICCFile_get_Attributes(This,pAttributes)	\
    (This)->lpVtbl -> get_Attributes(This,pAttributes)

#define ICCFile_get_Comment(This,pComment)	\
    (This)->lpVtbl -> get_Comment(This,pComment)

#define ICCFile_put_Comment(This,pComment)	\
    (This)->lpVtbl -> put_Comment(This,pComment)

#define ICCFile_get_CreationRecord(This,pHistoryRecord)	\
    (This)->lpVtbl -> get_CreationRecord(This,pHistoryRecord)

#define ICCFile_get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)	\
    (This)->lpVtbl -> get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)

#define ICCFile_get_Hyperlinks(This,HyperlinkType,pHyperlinks)	\
    (This)->lpVtbl -> get_Hyperlinks(This,HyperlinkType,pHyperlinks)

#define ICCFile_get_OID(This,pOID)	\
    (This)->lpVtbl -> get_OID(This,pOID)

#define ICCFile_get_VOBFamilyUUID(This,pVOBFamilyUUID)	\
    (This)->lpVtbl -> get_VOBFamilyUUID(This,pVOBFamilyUUID)


#define ICCFile_get_Path(This,pPath)	\
    (This)->lpVtbl -> get_Path(This,pPath)

#define ICCFile_get_ExtendedPath(This,pExtendedPath)	\
    (This)->lpVtbl -> get_ExtendedPath(This,pExtendedPath)

#define ICCFile_get_ExtendedPathInView(This,pView,pExtendedPath)	\
    (This)->lpVtbl -> get_ExtendedPathInView(This,pView,pExtendedPath)

#define ICCFile_get_IsDirectory(This,pIsDirectory)	\
    (This)->lpVtbl -> get_IsDirectory(This,pIsDirectory)

#define ICCFile_get_PathInView(This,pView,pPath)	\
    (This)->lpVtbl -> get_PathInView(This,pView,pPath)

#define ICCFile_get_View(This,pView)	\
    (This)->lpVtbl -> get_View(This,pView)

#define ICCFile_get_VOB(This,pVOB)	\
    (This)->lpVtbl -> get_VOB(This,pVOB)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCFile_get_Path_Proxy( 
    ICCFile __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pPath);


void __RPC_STUB ICCFile_get_Path_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCFile_get_ExtendedPath_Proxy( 
    ICCFile __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pExtendedPath);


void __RPC_STUB ICCFile_get_ExtendedPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCFile_get_ExtendedPathInView_Proxy( 
    ICCFile __RPC_FAR * This,
    /* [in] */ ICCView __RPC_FAR *pView,
    /* [retval][out] */ BSTR __RPC_FAR *pExtendedPath);


void __RPC_STUB ICCFile_get_ExtendedPathInView_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCFile_get_IsDirectory_Proxy( 
    ICCFile __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsDirectory);


void __RPC_STUB ICCFile_get_IsDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCFile_get_PathInView_Proxy( 
    ICCFile __RPC_FAR * This,
    /* [in] */ ICCView __RPC_FAR *pView,
    /* [retval][out] */ BSTR __RPC_FAR *pPath);


void __RPC_STUB ICCFile_get_PathInView_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCFile_get_View_Proxy( 
    ICCFile __RPC_FAR * This,
    /* [retval][out] */ ICCView __RPC_FAR *__RPC_FAR *pView);


void __RPC_STUB ICCFile_get_View_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCFile_get_VOB_Proxy( 
    ICCFile __RPC_FAR * This,
    /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);


void __RPC_STUB ICCFile_get_VOB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCFile_INTERFACE_DEFINED__ */


#ifndef __ICCVersion_INTERFACE_DEFINED__
#define __ICCVersion_INTERFACE_DEFINED__

/* interface ICCVersion */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCVersion,0xB22C7ED6,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7ED6-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCVersion : public ICCFile
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Branch( 
            /* [retval][out] */ ICCBranch __RPC_FAR *__RPC_FAR *pBranch) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CheckOut( 
            /* [in] */ CCReservedState ReservedState,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL UseHijacked,
            /* [defaultvalue][optional][in] */ CCVersionToCheckOut Version,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL MustBeLatest,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL PreserveTime,
            /* [retval][out] */ ICCCheckedOutFile __RPC_FAR *__RPC_FAR *pCheckedOutFile) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Element( 
            /* [retval][out] */ ICCElement __RPC_FAR *__RPC_FAR *pElement) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Identifier( 
            /* [retval][out] */ BSTR __RPC_FAR *pIdentifier) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IsCheckedOut( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsCheckedOut) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IsDifferent( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsDifferent) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IsHijacked( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsHijacked) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IsLatest( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsLatest) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Label( 
            /* [in] */ BSTR LabelType,
            /* [retval][out] */ ICCLabel __RPC_FAR *__RPC_FAR *pLabel) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Labels( 
            /* [retval][out] */ ICCLabels __RPC_FAR *__RPC_FAR *pLabels) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ ICCVersion __RPC_FAR *__RPC_FAR *pParent) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Predecessor( 
            /* [retval][out] */ ICCVersion __RPC_FAR *__RPC_FAR *pPredecessor) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveVersion( 
            /* [defaultvalue][optional][in] */ BSTR Comment = L"",
            /* [defaultvalue][optional][in] */ VARIANT_BOOL DataOnly = 0,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL EvenIfBranches = 0,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL EvenIfLabels = 0,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL EvenIfAttributes = 0,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL EvenIfHyperlinks = 0) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SubBranches( 
            /* [retval][out] */ ICCBranches __RPC_FAR *__RPC_FAR *pBranches) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_VersionNumber( 
            /* [retval][out] */ long __RPC_FAR *pVersionNumber) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCVersionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCVersion __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCVersion __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCVersion __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCVersion __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCVersion __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCVersion __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCVersion __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attribute )( 
            ICCVersion __RPC_FAR * This,
            /* [in] */ BSTR AttributeType,
            /* [retval][out] */ ICCAttribute __RPC_FAR *__RPC_FAR *pAttribute);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attributes )( 
            ICCVersion __RPC_FAR * This,
            /* [retval][out] */ ICCAttributes __RPC_FAR *__RPC_FAR *pAttributes);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Comment )( 
            ICCVersion __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pComment);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Comment )( 
            ICCVersion __RPC_FAR * This,
            /* [in] */ BSTR pComment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreationRecord )( 
            ICCVersion __RPC_FAR * This,
            /* [retval][out] */ ICCHistoryRecord __RPC_FAR *__RPC_FAR *pHistoryRecord);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HistoryRecords )( 
            ICCVersion __RPC_FAR * This,
            /* [in] */ ICCBranchType __RPC_FAR *pICCBranchType,
            /* [defaultvalue][optional][in] */ DATE Since,
            /* [defaultvalue][optional][in] */ BSTR User,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Minor,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL ExcludeCheckOutEvents,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL DirectoryOnly,
            /* [retval][out] */ ICCHistoryRecords __RPC_FAR *__RPC_FAR *pHistoryRecords);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hyperlinks )( 
            ICCVersion __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR HyperlinkType,
            /* [retval][out] */ ICCHyperlinks __RPC_FAR *__RPC_FAR *pHyperlinks);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OID )( 
            ICCVersion __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOBFamilyUUID )( 
            ICCVersion __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVOBFamilyUUID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Path )( 
            ICCVersion __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pPath);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExtendedPath )( 
            ICCVersion __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pExtendedPath);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExtendedPathInView )( 
            ICCVersion __RPC_FAR * This,
            /* [in] */ ICCView __RPC_FAR *pView,
            /* [retval][out] */ BSTR __RPC_FAR *pExtendedPath);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsDirectory )( 
            ICCVersion __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsDirectory);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PathInView )( 
            ICCVersion __RPC_FAR * This,
            /* [in] */ ICCView __RPC_FAR *pView,
            /* [retval][out] */ BSTR __RPC_FAR *pPath);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_View )( 
            ICCVersion __RPC_FAR * This,
            /* [retval][out] */ ICCView __RPC_FAR *__RPC_FAR *pView);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOB )( 
            ICCVersion __RPC_FAR * This,
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Branch )( 
            ICCVersion __RPC_FAR * This,
            /* [retval][out] */ ICCBranch __RPC_FAR *__RPC_FAR *pBranch);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CheckOut )( 
            ICCVersion __RPC_FAR * This,
            /* [in] */ CCReservedState ReservedState,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL UseHijacked,
            /* [defaultvalue][optional][in] */ CCVersionToCheckOut Version,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL MustBeLatest,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL PreserveTime,
            /* [retval][out] */ ICCCheckedOutFile __RPC_FAR *__RPC_FAR *pCheckedOutFile);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Element )( 
            ICCVersion __RPC_FAR * This,
            /* [retval][out] */ ICCElement __RPC_FAR *__RPC_FAR *pElement);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Identifier )( 
            ICCVersion __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pIdentifier);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsCheckedOut )( 
            ICCVersion __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsCheckedOut);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsDifferent )( 
            ICCVersion __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsDifferent);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsHijacked )( 
            ICCVersion __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsHijacked);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsLatest )( 
            ICCVersion __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsLatest);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Label )( 
            ICCVersion __RPC_FAR * This,
            /* [in] */ BSTR LabelType,
            /* [retval][out] */ ICCLabel __RPC_FAR *__RPC_FAR *pLabel);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Labels )( 
            ICCVersion __RPC_FAR * This,
            /* [retval][out] */ ICCLabels __RPC_FAR *__RPC_FAR *pLabels);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            ICCVersion __RPC_FAR * This,
            /* [retval][out] */ ICCVersion __RPC_FAR *__RPC_FAR *pParent);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Predecessor )( 
            ICCVersion __RPC_FAR * This,
            /* [retval][out] */ ICCVersion __RPC_FAR *__RPC_FAR *pPredecessor);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveVersion )( 
            ICCVersion __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL DataOnly,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL EvenIfBranches,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL EvenIfLabels,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL EvenIfAttributes,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL EvenIfHyperlinks);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SubBranches )( 
            ICCVersion __RPC_FAR * This,
            /* [retval][out] */ ICCBranches __RPC_FAR *__RPC_FAR *pBranches);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VersionNumber )( 
            ICCVersion __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVersionNumber);
        
        END_INTERFACE
    } ICCVersionVtbl;

    interface ICCVersion
    {
        CONST_VTBL struct ICCVersionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCVersion_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCVersion_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCVersion_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCVersion_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCVersion_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCVersion_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCVersion_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCVersion_get_Attribute(This,AttributeType,pAttribute)	\
    (This)->lpVtbl -> get_Attribute(This,AttributeType,pAttribute)

#define ICCVersion_get_Attributes(This,pAttributes)	\
    (This)->lpVtbl -> get_Attributes(This,pAttributes)

#define ICCVersion_get_Comment(This,pComment)	\
    (This)->lpVtbl -> get_Comment(This,pComment)

#define ICCVersion_put_Comment(This,pComment)	\
    (This)->lpVtbl -> put_Comment(This,pComment)

#define ICCVersion_get_CreationRecord(This,pHistoryRecord)	\
    (This)->lpVtbl -> get_CreationRecord(This,pHistoryRecord)

#define ICCVersion_get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)	\
    (This)->lpVtbl -> get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)

#define ICCVersion_get_Hyperlinks(This,HyperlinkType,pHyperlinks)	\
    (This)->lpVtbl -> get_Hyperlinks(This,HyperlinkType,pHyperlinks)

#define ICCVersion_get_OID(This,pOID)	\
    (This)->lpVtbl -> get_OID(This,pOID)

#define ICCVersion_get_VOBFamilyUUID(This,pVOBFamilyUUID)	\
    (This)->lpVtbl -> get_VOBFamilyUUID(This,pVOBFamilyUUID)


#define ICCVersion_get_Path(This,pPath)	\
    (This)->lpVtbl -> get_Path(This,pPath)

#define ICCVersion_get_ExtendedPath(This,pExtendedPath)	\
    (This)->lpVtbl -> get_ExtendedPath(This,pExtendedPath)

#define ICCVersion_get_ExtendedPathInView(This,pView,pExtendedPath)	\
    (This)->lpVtbl -> get_ExtendedPathInView(This,pView,pExtendedPath)

#define ICCVersion_get_IsDirectory(This,pIsDirectory)	\
    (This)->lpVtbl -> get_IsDirectory(This,pIsDirectory)

#define ICCVersion_get_PathInView(This,pView,pPath)	\
    (This)->lpVtbl -> get_PathInView(This,pView,pPath)

#define ICCVersion_get_View(This,pView)	\
    (This)->lpVtbl -> get_View(This,pView)

#define ICCVersion_get_VOB(This,pVOB)	\
    (This)->lpVtbl -> get_VOB(This,pVOB)


#define ICCVersion_get_Branch(This,pBranch)	\
    (This)->lpVtbl -> get_Branch(This,pBranch)

#define ICCVersion_CheckOut(This,ReservedState,Comment,UseHijacked,Version,MustBeLatest,PreserveTime,pCheckedOutFile)	\
    (This)->lpVtbl -> CheckOut(This,ReservedState,Comment,UseHijacked,Version,MustBeLatest,PreserveTime,pCheckedOutFile)

#define ICCVersion_get_Element(This,pElement)	\
    (This)->lpVtbl -> get_Element(This,pElement)

#define ICCVersion_get_Identifier(This,pIdentifier)	\
    (This)->lpVtbl -> get_Identifier(This,pIdentifier)

#define ICCVersion_get_IsCheckedOut(This,pIsCheckedOut)	\
    (This)->lpVtbl -> get_IsCheckedOut(This,pIsCheckedOut)

#define ICCVersion_get_IsDifferent(This,pIsDifferent)	\
    (This)->lpVtbl -> get_IsDifferent(This,pIsDifferent)

#define ICCVersion_get_IsHijacked(This,pIsHijacked)	\
    (This)->lpVtbl -> get_IsHijacked(This,pIsHijacked)

#define ICCVersion_get_IsLatest(This,pIsLatest)	\
    (This)->lpVtbl -> get_IsLatest(This,pIsLatest)

#define ICCVersion_get_Label(This,LabelType,pLabel)	\
    (This)->lpVtbl -> get_Label(This,LabelType,pLabel)

#define ICCVersion_get_Labels(This,pLabels)	\
    (This)->lpVtbl -> get_Labels(This,pLabels)

#define ICCVersion_get_Parent(This,pParent)	\
    (This)->lpVtbl -> get_Parent(This,pParent)

#define ICCVersion_get_Predecessor(This,pPredecessor)	\
    (This)->lpVtbl -> get_Predecessor(This,pPredecessor)

#define ICCVersion_RemoveVersion(This,Comment,DataOnly,EvenIfBranches,EvenIfLabels,EvenIfAttributes,EvenIfHyperlinks)	\
    (This)->lpVtbl -> RemoveVersion(This,Comment,DataOnly,EvenIfBranches,EvenIfLabels,EvenIfAttributes,EvenIfHyperlinks)

#define ICCVersion_get_SubBranches(This,pBranches)	\
    (This)->lpVtbl -> get_SubBranches(This,pBranches)

#define ICCVersion_get_VersionNumber(This,pVersionNumber)	\
    (This)->lpVtbl -> get_VersionNumber(This,pVersionNumber)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVersion_get_Branch_Proxy( 
    ICCVersion __RPC_FAR * This,
    /* [retval][out] */ ICCBranch __RPC_FAR *__RPC_FAR *pBranch);


void __RPC_STUB ICCVersion_get_Branch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCVersion_CheckOut_Proxy( 
    ICCVersion __RPC_FAR * This,
    /* [in] */ CCReservedState ReservedState,
    /* [defaultvalue][optional][in] */ BSTR Comment,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL UseHijacked,
    /* [defaultvalue][optional][in] */ CCVersionToCheckOut Version,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL MustBeLatest,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL PreserveTime,
    /* [retval][out] */ ICCCheckedOutFile __RPC_FAR *__RPC_FAR *pCheckedOutFile);


void __RPC_STUB ICCVersion_CheckOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVersion_get_Element_Proxy( 
    ICCVersion __RPC_FAR * This,
    /* [retval][out] */ ICCElement __RPC_FAR *__RPC_FAR *pElement);


void __RPC_STUB ICCVersion_get_Element_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVersion_get_Identifier_Proxy( 
    ICCVersion __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pIdentifier);


void __RPC_STUB ICCVersion_get_Identifier_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVersion_get_IsCheckedOut_Proxy( 
    ICCVersion __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsCheckedOut);


void __RPC_STUB ICCVersion_get_IsCheckedOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVersion_get_IsDifferent_Proxy( 
    ICCVersion __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsDifferent);


void __RPC_STUB ICCVersion_get_IsDifferent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVersion_get_IsHijacked_Proxy( 
    ICCVersion __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsHijacked);


void __RPC_STUB ICCVersion_get_IsHijacked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVersion_get_IsLatest_Proxy( 
    ICCVersion __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsLatest);


void __RPC_STUB ICCVersion_get_IsLatest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVersion_get_Label_Proxy( 
    ICCVersion __RPC_FAR * This,
    /* [in] */ BSTR LabelType,
    /* [retval][out] */ ICCLabel __RPC_FAR *__RPC_FAR *pLabel);


void __RPC_STUB ICCVersion_get_Label_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVersion_get_Labels_Proxy( 
    ICCVersion __RPC_FAR * This,
    /* [retval][out] */ ICCLabels __RPC_FAR *__RPC_FAR *pLabels);


void __RPC_STUB ICCVersion_get_Labels_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVersion_get_Parent_Proxy( 
    ICCVersion __RPC_FAR * This,
    /* [retval][out] */ ICCVersion __RPC_FAR *__RPC_FAR *pParent);


void __RPC_STUB ICCVersion_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVersion_get_Predecessor_Proxy( 
    ICCVersion __RPC_FAR * This,
    /* [retval][out] */ ICCVersion __RPC_FAR *__RPC_FAR *pPredecessor);


void __RPC_STUB ICCVersion_get_Predecessor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCVersion_RemoveVersion_Proxy( 
    ICCVersion __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Comment,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL DataOnly,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL EvenIfBranches,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL EvenIfLabels,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL EvenIfAttributes,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL EvenIfHyperlinks);


void __RPC_STUB ICCVersion_RemoveVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVersion_get_SubBranches_Proxy( 
    ICCVersion __RPC_FAR * This,
    /* [retval][out] */ ICCBranches __RPC_FAR *__RPC_FAR *pBranches);


void __RPC_STUB ICCVersion_get_SubBranches_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVersion_get_VersionNumber_Proxy( 
    ICCVersion __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVersionNumber);


void __RPC_STUB ICCVersion_get_VersionNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCVersion_INTERFACE_DEFINED__ */



#ifndef __ICCView_INTERFACE_DEFINED__
#define __ICCView_INTERFACE_DEFINED__

/* interface ICCView */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCView,0xB22C7ECD,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7ECD-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCView : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_TagName( 
            /* [retval][out] */ BSTR __RPC_FAR *pTagName) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_BuildsNonShareableDOs( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pBuildsNonShareableDOs) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_BuildsNonShareableDOs( 
            /* [in] */ VARIANT_BOOL pBuildsNonShareableDOs) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ConfigSpec( 
            /* [retval][out] */ BSTR __RPC_FAR *pConfigSpec) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_ConfigSpec( 
            /* [in] */ BSTR pConfigSpec) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_DisplayableConfigSpec( 
            /* [retval][out] */ BSTR __RPC_FAR *pConfigSpec) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Host( 
            /* [retval][out] */ BSTR __RPC_FAR *pHost) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IsActive( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsActive) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_IsActive( 
            /* [in] */ VARIANT_BOOL pIsActive) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IsSnapShot( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsSnapShot) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_CurrentActivity( 
            /* [retval][out] */ ICCActivity __RPC_FAR *__RPC_FAR *pActivity) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IsUCMView( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsUCMView) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetActivity( 
            /* [in] */ ICCActivity __RPC_FAR *NewActivity,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Stream( 
            /* [retval][out] */ ICCStream __RPC_FAR *__RPC_FAR *pStream) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCViewVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCView __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCView __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCView __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCView __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCView __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCView __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCView __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TagName )( 
            ICCView __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pTagName);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BuildsNonShareableDOs )( 
            ICCView __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pBuildsNonShareableDOs);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BuildsNonShareableDOs )( 
            ICCView __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pBuildsNonShareableDOs);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConfigSpec )( 
            ICCView __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pConfigSpec);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConfigSpec )( 
            ICCView __RPC_FAR * This,
            /* [in] */ BSTR pConfigSpec);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisplayableConfigSpec )( 
            ICCView __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pConfigSpec);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Host )( 
            ICCView __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pHost);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsActive )( 
            ICCView __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsActive);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IsActive )( 
            ICCView __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pIsActive);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsSnapShot )( 
            ICCView __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsSnapShot);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentActivity )( 
            ICCView __RPC_FAR * This,
            /* [retval][out] */ ICCActivity __RPC_FAR *__RPC_FAR *pActivity);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsUCMView )( 
            ICCView __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsUCMView);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetActivity )( 
            ICCView __RPC_FAR * This,
            /* [in] */ ICCActivity __RPC_FAR *NewActivity,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Stream )( 
            ICCView __RPC_FAR * This,
            /* [retval][out] */ ICCStream __RPC_FAR *__RPC_FAR *pStream);
        
        END_INTERFACE
    } ICCViewVtbl;

    interface ICCView
    {
        CONST_VTBL struct ICCViewVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCView_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCView_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCView_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCView_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCView_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCView_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCView_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCView_get_TagName(This,pTagName)	\
    (This)->lpVtbl -> get_TagName(This,pTagName)

#define ICCView_get_BuildsNonShareableDOs(This,pBuildsNonShareableDOs)	\
    (This)->lpVtbl -> get_BuildsNonShareableDOs(This,pBuildsNonShareableDOs)

#define ICCView_put_BuildsNonShareableDOs(This,pBuildsNonShareableDOs)	\
    (This)->lpVtbl -> put_BuildsNonShareableDOs(This,pBuildsNonShareableDOs)

#define ICCView_get_ConfigSpec(This,pConfigSpec)	\
    (This)->lpVtbl -> get_ConfigSpec(This,pConfigSpec)

#define ICCView_put_ConfigSpec(This,pConfigSpec)	\
    (This)->lpVtbl -> put_ConfigSpec(This,pConfigSpec)

#define ICCView_get_DisplayableConfigSpec(This,pConfigSpec)	\
    (This)->lpVtbl -> get_DisplayableConfigSpec(This,pConfigSpec)

#define ICCView_get_Host(This,pHost)	\
    (This)->lpVtbl -> get_Host(This,pHost)

#define ICCView_get_IsActive(This,pIsActive)	\
    (This)->lpVtbl -> get_IsActive(This,pIsActive)

#define ICCView_put_IsActive(This,pIsActive)	\
    (This)->lpVtbl -> put_IsActive(This,pIsActive)

#define ICCView_get_IsSnapShot(This,pIsSnapShot)	\
    (This)->lpVtbl -> get_IsSnapShot(This,pIsSnapShot)

#define ICCView_get_CurrentActivity(This,pActivity)	\
    (This)->lpVtbl -> get_CurrentActivity(This,pActivity)

#define ICCView_get_IsUCMView(This,pIsUCMView)	\
    (This)->lpVtbl -> get_IsUCMView(This,pIsUCMView)

#define ICCView_SetActivity(This,NewActivity,Comment)	\
    (This)->lpVtbl -> SetActivity(This,NewActivity,Comment)

#define ICCView_get_Stream(This,pStream)	\
    (This)->lpVtbl -> get_Stream(This,pStream)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCView_get_TagName_Proxy( 
    ICCView __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pTagName);


void __RPC_STUB ICCView_get_TagName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCView_get_BuildsNonShareableDOs_Proxy( 
    ICCView __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pBuildsNonShareableDOs);


void __RPC_STUB ICCView_get_BuildsNonShareableDOs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE ICCView_put_BuildsNonShareableDOs_Proxy( 
    ICCView __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL pBuildsNonShareableDOs);


void __RPC_STUB ICCView_put_BuildsNonShareableDOs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCView_get_ConfigSpec_Proxy( 
    ICCView __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pConfigSpec);


void __RPC_STUB ICCView_get_ConfigSpec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE ICCView_put_ConfigSpec_Proxy( 
    ICCView __RPC_FAR * This,
    /* [in] */ BSTR pConfigSpec);


void __RPC_STUB ICCView_put_ConfigSpec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCView_get_DisplayableConfigSpec_Proxy( 
    ICCView __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pConfigSpec);


void __RPC_STUB ICCView_get_DisplayableConfigSpec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCView_get_Host_Proxy( 
    ICCView __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pHost);


void __RPC_STUB ICCView_get_Host_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCView_get_IsActive_Proxy( 
    ICCView __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsActive);


void __RPC_STUB ICCView_get_IsActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE ICCView_put_IsActive_Proxy( 
    ICCView __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL pIsActive);


void __RPC_STUB ICCView_put_IsActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCView_get_IsSnapShot_Proxy( 
    ICCView __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsSnapShot);


void __RPC_STUB ICCView_get_IsSnapShot_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCView_get_CurrentActivity_Proxy( 
    ICCView __RPC_FAR * This,
    /* [retval][out] */ ICCActivity __RPC_FAR *__RPC_FAR *pActivity);


void __RPC_STUB ICCView_get_CurrentActivity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCView_get_IsUCMView_Proxy( 
    ICCView __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsUCMView);


void __RPC_STUB ICCView_get_IsUCMView_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCView_SetActivity_Proxy( 
    ICCView __RPC_FAR * This,
    /* [in] */ ICCActivity __RPC_FAR *NewActivity,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCView_SetActivity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCView_get_Stream_Proxy( 
    ICCView __RPC_FAR * This,
    /* [retval][out] */ ICCStream __RPC_FAR *__RPC_FAR *pStream);


void __RPC_STUB ICCView_get_Stream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCView_INTERFACE_DEFINED__ */

#ifndef __ICCUCMObject_INTERFACE_DEFINED__
#define __ICCUCMObject_INTERFACE_DEFINED__

/* interface ICCUCMObject */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCUCMObject,0xB22C7F31,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7F31-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCUCMObject : public ICCVOBObject
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pName) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateLock( 
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
            /* [optional][in] */ VARIANT ExemptUsersStringArray) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Group( 
            /* [retval][out] */ BSTR __RPC_FAR *pGroup) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Lock( 
            /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Master( 
            /* [retval][out] */ BSTR __RPC_FAR *pReplica) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Owner( 
            /* [retval][out] */ BSTR __RPC_FAR *pOwner) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ProjectVOB( 
            /* [retval][out] */ ICCProjectVOB __RPC_FAR *__RPC_FAR *pProjectVOB) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetGroup( 
            /* [in] */ BSTR NewGroup,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMaster( 
            /* [in] */ BSTR Replica,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetOwner( 
            /* [in] */ BSTR NewOwner,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Title( 
            /* [retval][out] */ BSTR __RPC_FAR *pTitle) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCUCMObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCUCMObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCUCMObject __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCUCMObject __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCUCMObject __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCUCMObject __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCUCMObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCUCMObject __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attribute )( 
            ICCUCMObject __RPC_FAR * This,
            /* [in] */ BSTR AttributeType,
            /* [retval][out] */ ICCAttribute __RPC_FAR *__RPC_FAR *pAttribute);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attributes )( 
            ICCUCMObject __RPC_FAR * This,
            /* [retval][out] */ ICCAttributes __RPC_FAR *__RPC_FAR *pAttributes);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Comment )( 
            ICCUCMObject __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pComment);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Comment )( 
            ICCUCMObject __RPC_FAR * This,
            /* [in] */ BSTR pComment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreationRecord )( 
            ICCUCMObject __RPC_FAR * This,
            /* [retval][out] */ ICCHistoryRecord __RPC_FAR *__RPC_FAR *pHistoryRecord);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HistoryRecords )( 
            ICCUCMObject __RPC_FAR * This,
            /* [in] */ ICCBranchType __RPC_FAR *pICCBranchType,
            /* [defaultvalue][optional][in] */ DATE Since,
            /* [defaultvalue][optional][in] */ BSTR User,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Minor,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL ExcludeCheckOutEvents,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL DirectoryOnly,
            /* [retval][out] */ ICCHistoryRecords __RPC_FAR *__RPC_FAR *pHistoryRecords);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hyperlinks )( 
            ICCUCMObject __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR HyperlinkType,
            /* [retval][out] */ ICCHyperlinks __RPC_FAR *__RPC_FAR *pHyperlinks);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OID )( 
            ICCUCMObject __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOBFamilyUUID )( 
            ICCUCMObject __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVOBFamilyUUID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ICCUCMObject __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateLock )( 
            ICCUCMObject __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
            /* [optional][in] */ VARIANT ExemptUsersStringArray);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Group )( 
            ICCUCMObject __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pGroup);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Lock )( 
            ICCUCMObject __RPC_FAR * This,
            /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Master )( 
            ICCUCMObject __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pReplica);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Owner )( 
            ICCUCMObject __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOwner);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProjectVOB )( 
            ICCUCMObject __RPC_FAR * This,
            /* [retval][out] */ ICCProjectVOB __RPC_FAR *__RPC_FAR *pProjectVOB);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGroup )( 
            ICCUCMObject __RPC_FAR * This,
            /* [in] */ BSTR NewGroup,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMaster )( 
            ICCUCMObject __RPC_FAR * This,
            /* [in] */ BSTR Replica,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOwner )( 
            ICCUCMObject __RPC_FAR * This,
            /* [in] */ BSTR NewOwner,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Title )( 
            ICCUCMObject __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pTitle);
        
        END_INTERFACE
    } ICCUCMObjectVtbl;

    interface ICCUCMObject
    {
        CONST_VTBL struct ICCUCMObjectVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCUCMObject_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCUCMObject_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCUCMObject_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCUCMObject_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCUCMObject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCUCMObject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCUCMObject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCUCMObject_get_Attribute(This,AttributeType,pAttribute)	\
    (This)->lpVtbl -> get_Attribute(This,AttributeType,pAttribute)

#define ICCUCMObject_get_Attributes(This,pAttributes)	\
    (This)->lpVtbl -> get_Attributes(This,pAttributes)

#define ICCUCMObject_get_Comment(This,pComment)	\
    (This)->lpVtbl -> get_Comment(This,pComment)

#define ICCUCMObject_put_Comment(This,pComment)	\
    (This)->lpVtbl -> put_Comment(This,pComment)

#define ICCUCMObject_get_CreationRecord(This,pHistoryRecord)	\
    (This)->lpVtbl -> get_CreationRecord(This,pHistoryRecord)

#define ICCUCMObject_get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)	\
    (This)->lpVtbl -> get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)

#define ICCUCMObject_get_Hyperlinks(This,HyperlinkType,pHyperlinks)	\
    (This)->lpVtbl -> get_Hyperlinks(This,HyperlinkType,pHyperlinks)

#define ICCUCMObject_get_OID(This,pOID)	\
    (This)->lpVtbl -> get_OID(This,pOID)

#define ICCUCMObject_get_VOBFamilyUUID(This,pVOBFamilyUUID)	\
    (This)->lpVtbl -> get_VOBFamilyUUID(This,pVOBFamilyUUID)


#define ICCUCMObject_get_Name(This,pName)	\
    (This)->lpVtbl -> get_Name(This,pName)

#define ICCUCMObject_CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)	\
    (This)->lpVtbl -> CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)

#define ICCUCMObject_get_Group(This,pGroup)	\
    (This)->lpVtbl -> get_Group(This,pGroup)

#define ICCUCMObject_get_Lock(This,pLock)	\
    (This)->lpVtbl -> get_Lock(This,pLock)

#define ICCUCMObject_get_Master(This,pReplica)	\
    (This)->lpVtbl -> get_Master(This,pReplica)

#define ICCUCMObject_get_Owner(This,pOwner)	\
    (This)->lpVtbl -> get_Owner(This,pOwner)

#define ICCUCMObject_get_ProjectVOB(This,pProjectVOB)	\
    (This)->lpVtbl -> get_ProjectVOB(This,pProjectVOB)

#define ICCUCMObject_SetGroup(This,NewGroup,Comment)	\
    (This)->lpVtbl -> SetGroup(This,NewGroup,Comment)

#define ICCUCMObject_SetMaster(This,Replica,Comment)	\
    (This)->lpVtbl -> SetMaster(This,Replica,Comment)

#define ICCUCMObject_SetOwner(This,NewOwner,Comment)	\
    (This)->lpVtbl -> SetOwner(This,NewOwner,Comment)

#define ICCUCMObject_get_Title(This,pTitle)	\
    (This)->lpVtbl -> get_Title(This,pTitle)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCUCMObject_get_Name_Proxy( 
    ICCUCMObject __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pName);


void __RPC_STUB ICCUCMObject_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCUCMObject_CreateLock_Proxy( 
    ICCUCMObject __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Comment,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
    /* [optional][in] */ VARIANT ExemptUsersStringArray);


void __RPC_STUB ICCUCMObject_CreateLock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCUCMObject_get_Group_Proxy( 
    ICCUCMObject __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pGroup);


void __RPC_STUB ICCUCMObject_get_Group_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCUCMObject_get_Lock_Proxy( 
    ICCUCMObject __RPC_FAR * This,
    /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock);


void __RPC_STUB ICCUCMObject_get_Lock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCUCMObject_get_Master_Proxy( 
    ICCUCMObject __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pReplica);


void __RPC_STUB ICCUCMObject_get_Master_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCUCMObject_get_Owner_Proxy( 
    ICCUCMObject __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pOwner);


void __RPC_STUB ICCUCMObject_get_Owner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCUCMObject_get_ProjectVOB_Proxy( 
    ICCUCMObject __RPC_FAR * This,
    /* [retval][out] */ ICCProjectVOB __RPC_FAR *__RPC_FAR *pProjectVOB);


void __RPC_STUB ICCUCMObject_get_ProjectVOB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCUCMObject_SetGroup_Proxy( 
    ICCUCMObject __RPC_FAR * This,
    /* [in] */ BSTR NewGroup,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCUCMObject_SetGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCUCMObject_SetMaster_Proxy( 
    ICCUCMObject __RPC_FAR * This,
    /* [in] */ BSTR Replica,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCUCMObject_SetMaster_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCUCMObject_SetOwner_Proxy( 
    ICCUCMObject __RPC_FAR * This,
    /* [in] */ BSTR NewOwner,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCUCMObject_SetOwner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCUCMObject_get_Title_Proxy( 
    ICCUCMObject __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pTitle);


void __RPC_STUB ICCUCMObject_get_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCUCMObject_INTERFACE_DEFINED__ */



#ifndef __ICCStream_INTERFACE_DEFINED__
#define __ICCStream_INTERFACE_DEFINED__

/* interface ICCStream */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCStream,0xB22C7F2D,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7F2D-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCStream : public ICCUCMObject
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Activities( 
            /* [retval][out] */ ICCActivities __RPC_FAR *__RPC_FAR *pActivities) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Baselines( 
            /* [in] */ ICCComponent __RPC_FAR *Component,
            /* [retval][out] */ ICCBaselines __RPC_FAR *__RPC_FAR *pBaselines) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateActivity( 
            /* [defaultvalue][optional][in] */ BSTR Headline,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ BSTR Name,
            /* [retval][out] */ ICCActivity __RPC_FAR *__RPC_FAR *pActivity) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_FoundationBaseline( 
            /* [in] */ ICCComponent __RPC_FAR *Component,
            /* [retval][out] */ ICCBaseline __RPC_FAR *__RPC_FAR *pFoundationBaseline) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_FoundationBaselines( 
            /* [retval][out] */ ICCBaselines __RPC_FAR *__RPC_FAR *pFoundationBaselines) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_HasActivities( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pHasActivities) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IsIntegrationStream( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsIntegrationStream) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_LatestBaseline( 
            /* [in] */ ICCComponent __RPC_FAR *Component,
            /* [retval][out] */ ICCBaseline __RPC_FAR *__RPC_FAR *pLatestBaseline) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_LatestBaselines( 
            /* [retval][out] */ ICCBaselines __RPC_FAR *__RPC_FAR *pLatestBaselines) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Project( 
            /* [retval][out] */ ICCProject __RPC_FAR *__RPC_FAR *pProject) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Views( 
            /* [defaultvalue][optional][in] */ BSTR Owner,
            /* [retval][out] */ ICCViews __RPC_FAR *__RPC_FAR *pViews) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCStreamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCStream __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCStream __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCStream __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCStream __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCStream __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCStream __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCStream __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attribute )( 
            ICCStream __RPC_FAR * This,
            /* [in] */ BSTR AttributeType,
            /* [retval][out] */ ICCAttribute __RPC_FAR *__RPC_FAR *pAttribute);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attributes )( 
            ICCStream __RPC_FAR * This,
            /* [retval][out] */ ICCAttributes __RPC_FAR *__RPC_FAR *pAttributes);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Comment )( 
            ICCStream __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pComment);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Comment )( 
            ICCStream __RPC_FAR * This,
            /* [in] */ BSTR pComment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreationRecord )( 
            ICCStream __RPC_FAR * This,
            /* [retval][out] */ ICCHistoryRecord __RPC_FAR *__RPC_FAR *pHistoryRecord);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HistoryRecords )( 
            ICCStream __RPC_FAR * This,
            /* [in] */ ICCBranchType __RPC_FAR *pICCBranchType,
            /* [defaultvalue][optional][in] */ DATE Since,
            /* [defaultvalue][optional][in] */ BSTR User,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Minor,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL ExcludeCheckOutEvents,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL DirectoryOnly,
            /* [retval][out] */ ICCHistoryRecords __RPC_FAR *__RPC_FAR *pHistoryRecords);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hyperlinks )( 
            ICCStream __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR HyperlinkType,
            /* [retval][out] */ ICCHyperlinks __RPC_FAR *__RPC_FAR *pHyperlinks);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OID )( 
            ICCStream __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOBFamilyUUID )( 
            ICCStream __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVOBFamilyUUID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ICCStream __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateLock )( 
            ICCStream __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
            /* [optional][in] */ VARIANT ExemptUsersStringArray);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Group )( 
            ICCStream __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pGroup);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Lock )( 
            ICCStream __RPC_FAR * This,
            /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Master )( 
            ICCStream __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pReplica);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Owner )( 
            ICCStream __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOwner);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProjectVOB )( 
            ICCStream __RPC_FAR * This,
            /* [retval][out] */ ICCProjectVOB __RPC_FAR *__RPC_FAR *pProjectVOB);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGroup )( 
            ICCStream __RPC_FAR * This,
            /* [in] */ BSTR NewGroup,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMaster )( 
            ICCStream __RPC_FAR * This,
            /* [in] */ BSTR Replica,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOwner )( 
            ICCStream __RPC_FAR * This,
            /* [in] */ BSTR NewOwner,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Title )( 
            ICCStream __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pTitle);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Activities )( 
            ICCStream __RPC_FAR * This,
            /* [retval][out] */ ICCActivities __RPC_FAR *__RPC_FAR *pActivities);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Baselines )( 
            ICCStream __RPC_FAR * This,
            /* [in] */ ICCComponent __RPC_FAR *Component,
            /* [retval][out] */ ICCBaselines __RPC_FAR *__RPC_FAR *pBaselines);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateActivity )( 
            ICCStream __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Headline,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ BSTR Name,
            /* [retval][out] */ ICCActivity __RPC_FAR *__RPC_FAR *pActivity);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FoundationBaseline )( 
            ICCStream __RPC_FAR * This,
            /* [in] */ ICCComponent __RPC_FAR *Component,
            /* [retval][out] */ ICCBaseline __RPC_FAR *__RPC_FAR *pFoundationBaseline);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FoundationBaselines )( 
            ICCStream __RPC_FAR * This,
            /* [retval][out] */ ICCBaselines __RPC_FAR *__RPC_FAR *pFoundationBaselines);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HasActivities )( 
            ICCStream __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pHasActivities);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsIntegrationStream )( 
            ICCStream __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsIntegrationStream);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LatestBaseline )( 
            ICCStream __RPC_FAR * This,
            /* [in] */ ICCComponent __RPC_FAR *Component,
            /* [retval][out] */ ICCBaseline __RPC_FAR *__RPC_FAR *pLatestBaseline);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LatestBaselines )( 
            ICCStream __RPC_FAR * This,
            /* [retval][out] */ ICCBaselines __RPC_FAR *__RPC_FAR *pLatestBaselines);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Project )( 
            ICCStream __RPC_FAR * This,
            /* [retval][out] */ ICCProject __RPC_FAR *__RPC_FAR *pProject);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Views )( 
            ICCStream __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Owner,
            /* [retval][out] */ ICCViews __RPC_FAR *__RPC_FAR *pViews);
        
        END_INTERFACE
    } ICCStreamVtbl;

    interface ICCStream
    {
        CONST_VTBL struct ICCStreamVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCStream_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCStream_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCStream_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCStream_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCStream_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCStream_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCStream_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCStream_get_Attribute(This,AttributeType,pAttribute)	\
    (This)->lpVtbl -> get_Attribute(This,AttributeType,pAttribute)

#define ICCStream_get_Attributes(This,pAttributes)	\
    (This)->lpVtbl -> get_Attributes(This,pAttributes)

#define ICCStream_get_Comment(This,pComment)	\
    (This)->lpVtbl -> get_Comment(This,pComment)

#define ICCStream_put_Comment(This,pComment)	\
    (This)->lpVtbl -> put_Comment(This,pComment)

#define ICCStream_get_CreationRecord(This,pHistoryRecord)	\
    (This)->lpVtbl -> get_CreationRecord(This,pHistoryRecord)

#define ICCStream_get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)	\
    (This)->lpVtbl -> get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)

#define ICCStream_get_Hyperlinks(This,HyperlinkType,pHyperlinks)	\
    (This)->lpVtbl -> get_Hyperlinks(This,HyperlinkType,pHyperlinks)

#define ICCStream_get_OID(This,pOID)	\
    (This)->lpVtbl -> get_OID(This,pOID)

#define ICCStream_get_VOBFamilyUUID(This,pVOBFamilyUUID)	\
    (This)->lpVtbl -> get_VOBFamilyUUID(This,pVOBFamilyUUID)


#define ICCStream_get_Name(This,pName)	\
    (This)->lpVtbl -> get_Name(This,pName)

#define ICCStream_CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)	\
    (This)->lpVtbl -> CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)

#define ICCStream_get_Group(This,pGroup)	\
    (This)->lpVtbl -> get_Group(This,pGroup)

#define ICCStream_get_Lock(This,pLock)	\
    (This)->lpVtbl -> get_Lock(This,pLock)

#define ICCStream_get_Master(This,pReplica)	\
    (This)->lpVtbl -> get_Master(This,pReplica)

#define ICCStream_get_Owner(This,pOwner)	\
    (This)->lpVtbl -> get_Owner(This,pOwner)

#define ICCStream_get_ProjectVOB(This,pProjectVOB)	\
    (This)->lpVtbl -> get_ProjectVOB(This,pProjectVOB)

#define ICCStream_SetGroup(This,NewGroup,Comment)	\
    (This)->lpVtbl -> SetGroup(This,NewGroup,Comment)

#define ICCStream_SetMaster(This,Replica,Comment)	\
    (This)->lpVtbl -> SetMaster(This,Replica,Comment)

#define ICCStream_SetOwner(This,NewOwner,Comment)	\
    (This)->lpVtbl -> SetOwner(This,NewOwner,Comment)

#define ICCStream_get_Title(This,pTitle)	\
    (This)->lpVtbl -> get_Title(This,pTitle)


#define ICCStream_get_Activities(This,pActivities)	\
    (This)->lpVtbl -> get_Activities(This,pActivities)

#define ICCStream_get_Baselines(This,Component,pBaselines)	\
    (This)->lpVtbl -> get_Baselines(This,Component,pBaselines)

#define ICCStream_CreateActivity(This,Headline,Comment,Name,pActivity)	\
    (This)->lpVtbl -> CreateActivity(This,Headline,Comment,Name,pActivity)

#define ICCStream_get_FoundationBaseline(This,Component,pFoundationBaseline)	\
    (This)->lpVtbl -> get_FoundationBaseline(This,Component,pFoundationBaseline)

#define ICCStream_get_FoundationBaselines(This,pFoundationBaselines)	\
    (This)->lpVtbl -> get_FoundationBaselines(This,pFoundationBaselines)

#define ICCStream_get_HasActivities(This,pHasActivities)	\
    (This)->lpVtbl -> get_HasActivities(This,pHasActivities)

#define ICCStream_get_IsIntegrationStream(This,pIsIntegrationStream)	\
    (This)->lpVtbl -> get_IsIntegrationStream(This,pIsIntegrationStream)

#define ICCStream_get_LatestBaseline(This,Component,pLatestBaseline)	\
    (This)->lpVtbl -> get_LatestBaseline(This,Component,pLatestBaseline)

#define ICCStream_get_LatestBaselines(This,pLatestBaselines)	\
    (This)->lpVtbl -> get_LatestBaselines(This,pLatestBaselines)

#define ICCStream_get_Project(This,pProject)	\
    (This)->lpVtbl -> get_Project(This,pProject)

#define ICCStream_get_Views(This,Owner,pViews)	\
    (This)->lpVtbl -> get_Views(This,Owner,pViews)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCStream_get_Activities_Proxy( 
    ICCStream __RPC_FAR * This,
    /* [retval][out] */ ICCActivities __RPC_FAR *__RPC_FAR *pActivities);


void __RPC_STUB ICCStream_get_Activities_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCStream_get_Baselines_Proxy( 
    ICCStream __RPC_FAR * This,
    /* [in] */ ICCComponent __RPC_FAR *Component,
    /* [retval][out] */ ICCBaselines __RPC_FAR *__RPC_FAR *pBaselines);


void __RPC_STUB ICCStream_get_Baselines_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCStream_CreateActivity_Proxy( 
    ICCStream __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Headline,
    /* [defaultvalue][optional][in] */ BSTR Comment,
    /* [defaultvalue][optional][in] */ BSTR Name,
    /* [retval][out] */ ICCActivity __RPC_FAR *__RPC_FAR *pActivity);


void __RPC_STUB ICCStream_CreateActivity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCStream_get_FoundationBaseline_Proxy( 
    ICCStream __RPC_FAR * This,
    /* [in] */ ICCComponent __RPC_FAR *Component,
    /* [retval][out] */ ICCBaseline __RPC_FAR *__RPC_FAR *pFoundationBaseline);


void __RPC_STUB ICCStream_get_FoundationBaseline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCStream_get_FoundationBaselines_Proxy( 
    ICCStream __RPC_FAR * This,
    /* [retval][out] */ ICCBaselines __RPC_FAR *__RPC_FAR *pFoundationBaselines);


void __RPC_STUB ICCStream_get_FoundationBaselines_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCStream_get_HasActivities_Proxy( 
    ICCStream __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pHasActivities);


void __RPC_STUB ICCStream_get_HasActivities_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCStream_get_IsIntegrationStream_Proxy( 
    ICCStream __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsIntegrationStream);


void __RPC_STUB ICCStream_get_IsIntegrationStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCStream_get_LatestBaseline_Proxy( 
    ICCStream __RPC_FAR * This,
    /* [in] */ ICCComponent __RPC_FAR *Component,
    /* [retval][out] */ ICCBaseline __RPC_FAR *__RPC_FAR *pLatestBaseline);


void __RPC_STUB ICCStream_get_LatestBaseline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCStream_get_LatestBaselines_Proxy( 
    ICCStream __RPC_FAR * This,
    /* [retval][out] */ ICCBaselines __RPC_FAR *__RPC_FAR *pLatestBaselines);


void __RPC_STUB ICCStream_get_LatestBaselines_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCStream_get_Project_Proxy( 
    ICCStream __RPC_FAR * This,
    /* [retval][out] */ ICCProject __RPC_FAR *__RPC_FAR *pProject);


void __RPC_STUB ICCStream_get_Project_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCStream_get_Views_Proxy( 
    ICCStream __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Owner,
    /* [retval][out] */ ICCViews __RPC_FAR *__RPC_FAR *pViews);


void __RPC_STUB ICCStream_get_Views_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCStream_INTERFACE_DEFINED__ */


#ifndef __ICCProjectVOB_INTERFACE_DEFINED__
#define __ICCProjectVOB_INTERFACE_DEFINED__

/* interface ICCProjectVOB */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCProjectVOB,0xB22C7F27,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7F27-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCProjectVOB : public ICCVOB
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Baseline( 
            /* [in] */ BSTR Selector,
            /* [retval][out] */ ICCBaseline __RPC_FAR *__RPC_FAR *pBaseline) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Component( 
            /* [in] */ BSTR Selector,
            /* [retval][out] */ ICCComponent __RPC_FAR *__RPC_FAR *pComponent) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Components( 
            /* [retval][out] */ ICCComponents __RPC_FAR *__RPC_FAR *pComponents) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_DefaultPromotionLevel( 
            /* [retval][out] */ BSTR __RPC_FAR *pDefaultPromotionLevel) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Folder( 
            /* [in] */ BSTR Selector,
            /* [retval][out] */ ICCFolder __RPC_FAR *__RPC_FAR *pFolder) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_NumberOfPromotionLevels( 
            /* [retval][out] */ long __RPC_FAR *pNumberOfPromotionLevels) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Project( 
            /* [in] */ BSTR Selector,
            /* [retval][out] */ ICCProject __RPC_FAR *__RPC_FAR *pProject) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Projects( 
            /* [retval][out] */ ICCProjects __RPC_FAR *__RPC_FAR *pProjects) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_PromotionLevelsStringArray( 
            /* [retval][out] */ VARIANT __RPC_FAR *pPromotionLevelsStringArray) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_RootFolder( 
            /* [retval][out] */ ICCFolder __RPC_FAR *__RPC_FAR *pRootFolder) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Stream( 
            /* [in] */ BSTR Selector,
            /* [retval][out] */ ICCStream __RPC_FAR *__RPC_FAR *pStream) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCProjectVOBVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCProjectVOB __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCProjectVOB __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attribute )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [in] */ BSTR AttributeType,
            /* [retval][out] */ ICCAttribute __RPC_FAR *__RPC_FAR *pAttribute);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attributes )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [retval][out] */ ICCAttributes __RPC_FAR *__RPC_FAR *pAttributes);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Comment )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pComment);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Comment )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [in] */ BSTR pComment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreationRecord )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [retval][out] */ ICCHistoryRecord __RPC_FAR *__RPC_FAR *pHistoryRecord);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HistoryRecords )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [in] */ ICCBranchType __RPC_FAR *pICCBranchType,
            /* [defaultvalue][optional][in] */ DATE Since,
            /* [defaultvalue][optional][in] */ BSTR User,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Minor,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL ExcludeCheckOutEvents,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL DirectoryOnly,
            /* [retval][out] */ ICCHistoryRecords __RPC_FAR *__RPC_FAR *pHistoryRecords);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hyperlinks )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR HyperlinkType,
            /* [retval][out] */ ICCHyperlinks __RPC_FAR *__RPC_FAR *pHyperlinks);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OID )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOBFamilyUUID )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVOBFamilyUUID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TagName )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pTagName);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Activity )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [in] */ BSTR Selector,
            /* [retval][out] */ ICCActivity __RPC_FAR *__RPC_FAR *pActivity);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AdditionalGroupsStringArray )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pAdditionalGroupsStringArray);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AttributeType )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
            /* [retval][out] */ ICCAttributeType __RPC_FAR *__RPC_FAR *pType);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AttributeTypes )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL IncludeObsoletes,
            /* [retval][out] */ ICCAttributeTypes __RPC_FAR *__RPC_FAR *pEnum);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BranchType )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
            /* [retval][out] */ ICCBranchType __RPC_FAR *__RPC_FAR *pType);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BranchTypes )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL IncludeObsoletes,
            /* [retval][out] */ ICCBranchTypes __RPC_FAR *__RPC_FAR *pEnum);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateAttributeType )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [defaultvalue][optional][in] */ long ValueType,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Shared,
            /* [defaultvalue][optional][in] */ CCTypeConstraint Constraint,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Global,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Acquire,
            /* [retval][out] */ ICCAttributeType __RPC_FAR *__RPC_FAR *pType);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateBranchType )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ CCTypeConstraint Constraint,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Global,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Acquire,
            /* [retval][out] */ ICCBranchType __RPC_FAR *__RPC_FAR *pType);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateHyperlinkType )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Shared,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Global,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Acquire,
            /* [retval][out] */ ICCHyperlinkType __RPC_FAR *__RPC_FAR *pType);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateLabelType )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Shared,
            /* [defaultvalue][optional][in] */ CCTypeConstraint Constraint,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Global,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Acquire,
            /* [retval][out] */ ICCLabelType __RPC_FAR *__RPC_FAR *pType);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateLock )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
            /* [optional][in] */ VARIANT ExemptUsersStringArray);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateTriggerTypeBuilder )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [retval][out] */ ICCTriggerTypeBuilder __RPC_FAR *__RPC_FAR *pTriggerTypeBuilder);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Group )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pGroup);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HasMSDOSTextMode )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pHasMSDOSTextMode);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Host )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pHost);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hyperlink )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [in] */ BSTR IDString,
            /* [retval][out] */ ICCHyperlink __RPC_FAR *__RPC_FAR *pHyperlink);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HyperlinkType )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
            /* [retval][out] */ ICCHyperlinkType __RPC_FAR *__RPC_FAR *pType);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HyperlinkTypes )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL IncludeObsoletes,
            /* [retval][out] */ ICCHyperlinkTypes __RPC_FAR *__RPC_FAR *pEnum);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsMounted )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsMounted);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IsMounted )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pIsMounted);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IsPersistent )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL rhs);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsReplicated )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsReplicated);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LabelType )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
            /* [retval][out] */ ICCLabelType __RPC_FAR *__RPC_FAR *pType);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LabelTypes )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Local,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL IncludeObsoletes,
            /* [retval][out] */ ICCLabelTypes __RPC_FAR *__RPC_FAR *pEnum);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Lock )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Locks )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL IncludeObsoletes,
            /* [retval][out] */ ICCLocks __RPC_FAR *__RPC_FAR *pLocks);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Master )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pReplica);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumberOfAdditionalGroups )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pNumberOfAdditionalGroups);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumberOfReplicas )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pNumberOfReplicas);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Owner )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOwner);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Protect )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR NewOwner,
            /* [defaultvalue][optional][in] */ BSTR NewGroup,
            /* [optional][in] */ VARIANT GroupsToAddStringArray,
            /* [optional][in] */ VARIANT GroupsToRemoveStringArray);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReplicasStringArray )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pReplicasStringArray);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMaster )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [in] */ BSTR Replica,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ThisReplica )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pReplica);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TriggerType )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ ICCTriggerType __RPC_FAR *__RPC_FAR *pType);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TriggerTypes )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL IncludeObsoletes,
            /* [retval][out] */ ICCTriggerTypes __RPC_FAR *__RPC_FAR *pEnum);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Baseline )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [in] */ BSTR Selector,
            /* [retval][out] */ ICCBaseline __RPC_FAR *__RPC_FAR *pBaseline);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Component )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [in] */ BSTR Selector,
            /* [retval][out] */ ICCComponent __RPC_FAR *__RPC_FAR *pComponent);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Components )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [retval][out] */ ICCComponents __RPC_FAR *__RPC_FAR *pComponents);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DefaultPromotionLevel )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pDefaultPromotionLevel);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Folder )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [in] */ BSTR Selector,
            /* [retval][out] */ ICCFolder __RPC_FAR *__RPC_FAR *pFolder);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumberOfPromotionLevels )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pNumberOfPromotionLevels);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Project )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [in] */ BSTR Selector,
            /* [retval][out] */ ICCProject __RPC_FAR *__RPC_FAR *pProject);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Projects )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [retval][out] */ ICCProjects __RPC_FAR *__RPC_FAR *pProjects);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PromotionLevelsStringArray )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pPromotionLevelsStringArray);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RootFolder )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [retval][out] */ ICCFolder __RPC_FAR *__RPC_FAR *pRootFolder);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Stream )( 
            ICCProjectVOB __RPC_FAR * This,
            /* [in] */ BSTR Selector,
            /* [retval][out] */ ICCStream __RPC_FAR *__RPC_FAR *pStream);
        
        END_INTERFACE
    } ICCProjectVOBVtbl;

    interface ICCProjectVOB
    {
        CONST_VTBL struct ICCProjectVOBVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCProjectVOB_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCProjectVOB_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCProjectVOB_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCProjectVOB_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCProjectVOB_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCProjectVOB_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCProjectVOB_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCProjectVOB_get_Attribute(This,AttributeType,pAttribute)	\
    (This)->lpVtbl -> get_Attribute(This,AttributeType,pAttribute)

#define ICCProjectVOB_get_Attributes(This,pAttributes)	\
    (This)->lpVtbl -> get_Attributes(This,pAttributes)

#define ICCProjectVOB_get_Comment(This,pComment)	\
    (This)->lpVtbl -> get_Comment(This,pComment)

#define ICCProjectVOB_put_Comment(This,pComment)	\
    (This)->lpVtbl -> put_Comment(This,pComment)

#define ICCProjectVOB_get_CreationRecord(This,pHistoryRecord)	\
    (This)->lpVtbl -> get_CreationRecord(This,pHistoryRecord)

#define ICCProjectVOB_get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)	\
    (This)->lpVtbl -> get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)

#define ICCProjectVOB_get_Hyperlinks(This,HyperlinkType,pHyperlinks)	\
    (This)->lpVtbl -> get_Hyperlinks(This,HyperlinkType,pHyperlinks)

#define ICCProjectVOB_get_OID(This,pOID)	\
    (This)->lpVtbl -> get_OID(This,pOID)

#define ICCProjectVOB_get_VOBFamilyUUID(This,pVOBFamilyUUID)	\
    (This)->lpVtbl -> get_VOBFamilyUUID(This,pVOBFamilyUUID)


#define ICCProjectVOB_get_TagName(This,pTagName)	\
    (This)->lpVtbl -> get_TagName(This,pTagName)

#define ICCProjectVOB_get_Activity(This,Selector,pActivity)	\
    (This)->lpVtbl -> get_Activity(This,Selector,pActivity)

#define ICCProjectVOB_get_AdditionalGroupsStringArray(This,pAdditionalGroupsStringArray)	\
    (This)->lpVtbl -> get_AdditionalGroupsStringArray(This,pAdditionalGroupsStringArray)

#define ICCProjectVOB_get_AttributeType(This,Name,Local,pType)	\
    (This)->lpVtbl -> get_AttributeType(This,Name,Local,pType)

#define ICCProjectVOB_get_AttributeTypes(This,Local,IncludeObsoletes,pEnum)	\
    (This)->lpVtbl -> get_AttributeTypes(This,Local,IncludeObsoletes,pEnum)

#define ICCProjectVOB_get_BranchType(This,Name,Local,pType)	\
    (This)->lpVtbl -> get_BranchType(This,Name,Local,pType)

#define ICCProjectVOB_get_BranchTypes(This,Local,IncludeObsoletes,pEnum)	\
    (This)->lpVtbl -> get_BranchTypes(This,Local,IncludeObsoletes,pEnum)

#define ICCProjectVOB_CreateAttributeType(This,Name,ValueType,Comment,Shared,Constraint,Global,Acquire,pType)	\
    (This)->lpVtbl -> CreateAttributeType(This,Name,ValueType,Comment,Shared,Constraint,Global,Acquire,pType)

#define ICCProjectVOB_CreateBranchType(This,Name,Comment,Constraint,Global,Acquire,pType)	\
    (This)->lpVtbl -> CreateBranchType(This,Name,Comment,Constraint,Global,Acquire,pType)

#define ICCProjectVOB_CreateHyperlinkType(This,Name,Comment,Shared,Global,Acquire,pType)	\
    (This)->lpVtbl -> CreateHyperlinkType(This,Name,Comment,Shared,Global,Acquire,pType)

#define ICCProjectVOB_CreateLabelType(This,Name,Comment,Shared,Constraint,Global,Acquire,pType)	\
    (This)->lpVtbl -> CreateLabelType(This,Name,Comment,Shared,Constraint,Global,Acquire,pType)

#define ICCProjectVOB_CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)	\
    (This)->lpVtbl -> CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)

#define ICCProjectVOB_CreateTriggerTypeBuilder(This,pTriggerTypeBuilder)	\
    (This)->lpVtbl -> CreateTriggerTypeBuilder(This,pTriggerTypeBuilder)

#define ICCProjectVOB_get_Group(This,pGroup)	\
    (This)->lpVtbl -> get_Group(This,pGroup)

#define ICCProjectVOB_get_HasMSDOSTextMode(This,pHasMSDOSTextMode)	\
    (This)->lpVtbl -> get_HasMSDOSTextMode(This,pHasMSDOSTextMode)

#define ICCProjectVOB_get_Host(This,pHost)	\
    (This)->lpVtbl -> get_Host(This,pHost)

#define ICCProjectVOB_get_Hyperlink(This,IDString,pHyperlink)	\
    (This)->lpVtbl -> get_Hyperlink(This,IDString,pHyperlink)

#define ICCProjectVOB_get_HyperlinkType(This,Name,Local,pType)	\
    (This)->lpVtbl -> get_HyperlinkType(This,Name,Local,pType)

#define ICCProjectVOB_get_HyperlinkTypes(This,Local,IncludeObsoletes,pEnum)	\
    (This)->lpVtbl -> get_HyperlinkTypes(This,Local,IncludeObsoletes,pEnum)

#define ICCProjectVOB_get_IsMounted(This,pIsMounted)	\
    (This)->lpVtbl -> get_IsMounted(This,pIsMounted)

#define ICCProjectVOB_put_IsMounted(This,pIsMounted)	\
    (This)->lpVtbl -> put_IsMounted(This,pIsMounted)

#define ICCProjectVOB_put_IsPersistent(This,rhs)	\
    (This)->lpVtbl -> put_IsPersistent(This,rhs)

#define ICCProjectVOB_get_IsReplicated(This,pIsReplicated)	\
    (This)->lpVtbl -> get_IsReplicated(This,pIsReplicated)

#define ICCProjectVOB_get_LabelType(This,Name,Local,pType)	\
    (This)->lpVtbl -> get_LabelType(This,Name,Local,pType)

#define ICCProjectVOB_get_LabelTypes(This,Local,IncludeObsoletes,pEnum)	\
    (This)->lpVtbl -> get_LabelTypes(This,Local,IncludeObsoletes,pEnum)

#define ICCProjectVOB_get_Lock(This,pLock)	\
    (This)->lpVtbl -> get_Lock(This,pLock)

#define ICCProjectVOB_get_Locks(This,IncludeObsoletes,pLocks)	\
    (This)->lpVtbl -> get_Locks(This,IncludeObsoletes,pLocks)

#define ICCProjectVOB_get_Master(This,pReplica)	\
    (This)->lpVtbl -> get_Master(This,pReplica)

#define ICCProjectVOB_get_NumberOfAdditionalGroups(This,pNumberOfAdditionalGroups)	\
    (This)->lpVtbl -> get_NumberOfAdditionalGroups(This,pNumberOfAdditionalGroups)

#define ICCProjectVOB_get_NumberOfReplicas(This,pNumberOfReplicas)	\
    (This)->lpVtbl -> get_NumberOfReplicas(This,pNumberOfReplicas)

#define ICCProjectVOB_get_Owner(This,pOwner)	\
    (This)->lpVtbl -> get_Owner(This,pOwner)

#define ICCProjectVOB_Protect(This,NewOwner,NewGroup,GroupsToAddStringArray,GroupsToRemoveStringArray)	\
    (This)->lpVtbl -> Protect(This,NewOwner,NewGroup,GroupsToAddStringArray,GroupsToRemoveStringArray)

#define ICCProjectVOB_get_ReplicasStringArray(This,pReplicasStringArray)	\
    (This)->lpVtbl -> get_ReplicasStringArray(This,pReplicasStringArray)

#define ICCProjectVOB_SetMaster(This,Replica,Comment)	\
    (This)->lpVtbl -> SetMaster(This,Replica,Comment)

#define ICCProjectVOB_get_ThisReplica(This,pReplica)	\
    (This)->lpVtbl -> get_ThisReplica(This,pReplica)

#define ICCProjectVOB_get_TriggerType(This,Name,pType)	\
    (This)->lpVtbl -> get_TriggerType(This,Name,pType)

#define ICCProjectVOB_get_TriggerTypes(This,IncludeObsoletes,pEnum)	\
    (This)->lpVtbl -> get_TriggerTypes(This,IncludeObsoletes,pEnum)


#define ICCProjectVOB_get_Baseline(This,Selector,pBaseline)	\
    (This)->lpVtbl -> get_Baseline(This,Selector,pBaseline)

#define ICCProjectVOB_get_Component(This,Selector,pComponent)	\
    (This)->lpVtbl -> get_Component(This,Selector,pComponent)

#define ICCProjectVOB_get_Components(This,pComponents)	\
    (This)->lpVtbl -> get_Components(This,pComponents)

#define ICCProjectVOB_get_DefaultPromotionLevel(This,pDefaultPromotionLevel)	\
    (This)->lpVtbl -> get_DefaultPromotionLevel(This,pDefaultPromotionLevel)

#define ICCProjectVOB_get_Folder(This,Selector,pFolder)	\
    (This)->lpVtbl -> get_Folder(This,Selector,pFolder)

#define ICCProjectVOB_get_NumberOfPromotionLevels(This,pNumberOfPromotionLevels)	\
    (This)->lpVtbl -> get_NumberOfPromotionLevels(This,pNumberOfPromotionLevels)

#define ICCProjectVOB_get_Project(This,Selector,pProject)	\
    (This)->lpVtbl -> get_Project(This,Selector,pProject)

#define ICCProjectVOB_get_Projects(This,pProjects)	\
    (This)->lpVtbl -> get_Projects(This,pProjects)

#define ICCProjectVOB_get_PromotionLevelsStringArray(This,pPromotionLevelsStringArray)	\
    (This)->lpVtbl -> get_PromotionLevelsStringArray(This,pPromotionLevelsStringArray)

#define ICCProjectVOB_get_RootFolder(This,pRootFolder)	\
    (This)->lpVtbl -> get_RootFolder(This,pRootFolder)

#define ICCProjectVOB_get_Stream(This,Selector,pStream)	\
    (This)->lpVtbl -> get_Stream(This,Selector,pStream)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProjectVOB_get_Baseline_Proxy( 
    ICCProjectVOB __RPC_FAR * This,
    /* [in] */ BSTR Selector,
    /* [retval][out] */ ICCBaseline __RPC_FAR *__RPC_FAR *pBaseline);


void __RPC_STUB ICCProjectVOB_get_Baseline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProjectVOB_get_Component_Proxy( 
    ICCProjectVOB __RPC_FAR * This,
    /* [in] */ BSTR Selector,
    /* [retval][out] */ ICCComponent __RPC_FAR *__RPC_FAR *pComponent);


void __RPC_STUB ICCProjectVOB_get_Component_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProjectVOB_get_Components_Proxy( 
    ICCProjectVOB __RPC_FAR * This,
    /* [retval][out] */ ICCComponents __RPC_FAR *__RPC_FAR *pComponents);


void __RPC_STUB ICCProjectVOB_get_Components_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProjectVOB_get_DefaultPromotionLevel_Proxy( 
    ICCProjectVOB __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pDefaultPromotionLevel);


void __RPC_STUB ICCProjectVOB_get_DefaultPromotionLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProjectVOB_get_Folder_Proxy( 
    ICCProjectVOB __RPC_FAR * This,
    /* [in] */ BSTR Selector,
    /* [retval][out] */ ICCFolder __RPC_FAR *__RPC_FAR *pFolder);


void __RPC_STUB ICCProjectVOB_get_Folder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProjectVOB_get_NumberOfPromotionLevels_Proxy( 
    ICCProjectVOB __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pNumberOfPromotionLevels);


void __RPC_STUB ICCProjectVOB_get_NumberOfPromotionLevels_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProjectVOB_get_Project_Proxy( 
    ICCProjectVOB __RPC_FAR * This,
    /* [in] */ BSTR Selector,
    /* [retval][out] */ ICCProject __RPC_FAR *__RPC_FAR *pProject);


void __RPC_STUB ICCProjectVOB_get_Project_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProjectVOB_get_Projects_Proxy( 
    ICCProjectVOB __RPC_FAR * This,
    /* [retval][out] */ ICCProjects __RPC_FAR *__RPC_FAR *pProjects);


void __RPC_STUB ICCProjectVOB_get_Projects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProjectVOB_get_PromotionLevelsStringArray_Proxy( 
    ICCProjectVOB __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pPromotionLevelsStringArray);


void __RPC_STUB ICCProjectVOB_get_PromotionLevelsStringArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProjectVOB_get_RootFolder_Proxy( 
    ICCProjectVOB __RPC_FAR * This,
    /* [retval][out] */ ICCFolder __RPC_FAR *__RPC_FAR *pRootFolder);


void __RPC_STUB ICCProjectVOB_get_RootFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProjectVOB_get_Stream_Proxy( 
    ICCProjectVOB __RPC_FAR * This,
    /* [in] */ BSTR Selector,
    /* [retval][out] */ ICCStream __RPC_FAR *__RPC_FAR *pStream);


void __RPC_STUB ICCProjectVOB_get_Stream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCProjectVOB_INTERFACE_DEFINED__ */


#ifndef __ICCBaseline_INTERFACE_DEFINED__
#define __ICCBaseline_INTERFACE_DEFINED__

/* interface ICCBaseline */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCBaseline,0xB22C7F2C,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7F2C-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCBaseline : public ICCUCMObject
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Activities( 
            /* [retval][out] */ ICCActivities __RPC_FAR *__RPC_FAR *pActivities) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Component( 
            /* [retval][out] */ ICCComponent __RPC_FAR *__RPC_FAR *pComponent) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_LabelStatus( 
            /* [retval][out] */ CCLabelStatus __RPC_FAR *pLabelStatus) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_PromotionLevel( 
            /* [retval][out] */ BSTR __RPC_FAR *pPromotionLevel) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Stream( 
            /* [retval][out] */ ICCStream __RPC_FAR *__RPC_FAR *pStream) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_UsedByStreams( 
            /* [retval][out] */ ICCStreams __RPC_FAR *__RPC_FAR *pUsedByStreams) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCBaselineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCBaseline __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCBaseline __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCBaseline __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCBaseline __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCBaseline __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCBaseline __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCBaseline __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attribute )( 
            ICCBaseline __RPC_FAR * This,
            /* [in] */ BSTR AttributeType,
            /* [retval][out] */ ICCAttribute __RPC_FAR *__RPC_FAR *pAttribute);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attributes )( 
            ICCBaseline __RPC_FAR * This,
            /* [retval][out] */ ICCAttributes __RPC_FAR *__RPC_FAR *pAttributes);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Comment )( 
            ICCBaseline __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pComment);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Comment )( 
            ICCBaseline __RPC_FAR * This,
            /* [in] */ BSTR pComment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreationRecord )( 
            ICCBaseline __RPC_FAR * This,
            /* [retval][out] */ ICCHistoryRecord __RPC_FAR *__RPC_FAR *pHistoryRecord);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HistoryRecords )( 
            ICCBaseline __RPC_FAR * This,
            /* [in] */ ICCBranchType __RPC_FAR *pICCBranchType,
            /* [defaultvalue][optional][in] */ DATE Since,
            /* [defaultvalue][optional][in] */ BSTR User,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Minor,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL ExcludeCheckOutEvents,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL DirectoryOnly,
            /* [retval][out] */ ICCHistoryRecords __RPC_FAR *__RPC_FAR *pHistoryRecords);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hyperlinks )( 
            ICCBaseline __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR HyperlinkType,
            /* [retval][out] */ ICCHyperlinks __RPC_FAR *__RPC_FAR *pHyperlinks);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OID )( 
            ICCBaseline __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOBFamilyUUID )( 
            ICCBaseline __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVOBFamilyUUID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ICCBaseline __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateLock )( 
            ICCBaseline __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
            /* [optional][in] */ VARIANT ExemptUsersStringArray);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Group )( 
            ICCBaseline __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pGroup);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Lock )( 
            ICCBaseline __RPC_FAR * This,
            /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Master )( 
            ICCBaseline __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pReplica);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Owner )( 
            ICCBaseline __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOwner);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProjectVOB )( 
            ICCBaseline __RPC_FAR * This,
            /* [retval][out] */ ICCProjectVOB __RPC_FAR *__RPC_FAR *pProjectVOB);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGroup )( 
            ICCBaseline __RPC_FAR * This,
            /* [in] */ BSTR NewGroup,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMaster )( 
            ICCBaseline __RPC_FAR * This,
            /* [in] */ BSTR Replica,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOwner )( 
            ICCBaseline __RPC_FAR * This,
            /* [in] */ BSTR NewOwner,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Title )( 
            ICCBaseline __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pTitle);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Activities )( 
            ICCBaseline __RPC_FAR * This,
            /* [retval][out] */ ICCActivities __RPC_FAR *__RPC_FAR *pActivities);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Component )( 
            ICCBaseline __RPC_FAR * This,
            /* [retval][out] */ ICCComponent __RPC_FAR *__RPC_FAR *pComponent);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LabelStatus )( 
            ICCBaseline __RPC_FAR * This,
            /* [retval][out] */ CCLabelStatus __RPC_FAR *pLabelStatus);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PromotionLevel )( 
            ICCBaseline __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pPromotionLevel);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Stream )( 
            ICCBaseline __RPC_FAR * This,
            /* [retval][out] */ ICCStream __RPC_FAR *__RPC_FAR *pStream);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UsedByStreams )( 
            ICCBaseline __RPC_FAR * This,
            /* [retval][out] */ ICCStreams __RPC_FAR *__RPC_FAR *pUsedByStreams);
        
        END_INTERFACE
    } ICCBaselineVtbl;

    interface ICCBaseline
    {
        CONST_VTBL struct ICCBaselineVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCBaseline_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCBaseline_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCBaseline_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCBaseline_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCBaseline_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCBaseline_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCBaseline_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCBaseline_get_Attribute(This,AttributeType,pAttribute)	\
    (This)->lpVtbl -> get_Attribute(This,AttributeType,pAttribute)

#define ICCBaseline_get_Attributes(This,pAttributes)	\
    (This)->lpVtbl -> get_Attributes(This,pAttributes)

#define ICCBaseline_get_Comment(This,pComment)	\
    (This)->lpVtbl -> get_Comment(This,pComment)

#define ICCBaseline_put_Comment(This,pComment)	\
    (This)->lpVtbl -> put_Comment(This,pComment)

#define ICCBaseline_get_CreationRecord(This,pHistoryRecord)	\
    (This)->lpVtbl -> get_CreationRecord(This,pHistoryRecord)

#define ICCBaseline_get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)	\
    (This)->lpVtbl -> get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)

#define ICCBaseline_get_Hyperlinks(This,HyperlinkType,pHyperlinks)	\
    (This)->lpVtbl -> get_Hyperlinks(This,HyperlinkType,pHyperlinks)

#define ICCBaseline_get_OID(This,pOID)	\
    (This)->lpVtbl -> get_OID(This,pOID)

#define ICCBaseline_get_VOBFamilyUUID(This,pVOBFamilyUUID)	\
    (This)->lpVtbl -> get_VOBFamilyUUID(This,pVOBFamilyUUID)


#define ICCBaseline_get_Name(This,pName)	\
    (This)->lpVtbl -> get_Name(This,pName)

#define ICCBaseline_CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)	\
    (This)->lpVtbl -> CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)

#define ICCBaseline_get_Group(This,pGroup)	\
    (This)->lpVtbl -> get_Group(This,pGroup)

#define ICCBaseline_get_Lock(This,pLock)	\
    (This)->lpVtbl -> get_Lock(This,pLock)

#define ICCBaseline_get_Master(This,pReplica)	\
    (This)->lpVtbl -> get_Master(This,pReplica)

#define ICCBaseline_get_Owner(This,pOwner)	\
    (This)->lpVtbl -> get_Owner(This,pOwner)

#define ICCBaseline_get_ProjectVOB(This,pProjectVOB)	\
    (This)->lpVtbl -> get_ProjectVOB(This,pProjectVOB)

#define ICCBaseline_SetGroup(This,NewGroup,Comment)	\
    (This)->lpVtbl -> SetGroup(This,NewGroup,Comment)

#define ICCBaseline_SetMaster(This,Replica,Comment)	\
    (This)->lpVtbl -> SetMaster(This,Replica,Comment)

#define ICCBaseline_SetOwner(This,NewOwner,Comment)	\
    (This)->lpVtbl -> SetOwner(This,NewOwner,Comment)

#define ICCBaseline_get_Title(This,pTitle)	\
    (This)->lpVtbl -> get_Title(This,pTitle)


#define ICCBaseline_get_Activities(This,pActivities)	\
    (This)->lpVtbl -> get_Activities(This,pActivities)

#define ICCBaseline_get_Component(This,pComponent)	\
    (This)->lpVtbl -> get_Component(This,pComponent)

#define ICCBaseline_get_LabelStatus(This,pLabelStatus)	\
    (This)->lpVtbl -> get_LabelStatus(This,pLabelStatus)

#define ICCBaseline_get_PromotionLevel(This,pPromotionLevel)	\
    (This)->lpVtbl -> get_PromotionLevel(This,pPromotionLevel)

#define ICCBaseline_get_Stream(This,pStream)	\
    (This)->lpVtbl -> get_Stream(This,pStream)

#define ICCBaseline_get_UsedByStreams(This,pUsedByStreams)	\
    (This)->lpVtbl -> get_UsedByStreams(This,pUsedByStreams)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBaseline_get_Activities_Proxy( 
    ICCBaseline __RPC_FAR * This,
    /* [retval][out] */ ICCActivities __RPC_FAR *__RPC_FAR *pActivities);


void __RPC_STUB ICCBaseline_get_Activities_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBaseline_get_Component_Proxy( 
    ICCBaseline __RPC_FAR * This,
    /* [retval][out] */ ICCComponent __RPC_FAR *__RPC_FAR *pComponent);


void __RPC_STUB ICCBaseline_get_Component_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBaseline_get_LabelStatus_Proxy( 
    ICCBaseline __RPC_FAR * This,
    /* [retval][out] */ CCLabelStatus __RPC_FAR *pLabelStatus);


void __RPC_STUB ICCBaseline_get_LabelStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBaseline_get_PromotionLevel_Proxy( 
    ICCBaseline __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pPromotionLevel);


void __RPC_STUB ICCBaseline_get_PromotionLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBaseline_get_Stream_Proxy( 
    ICCBaseline __RPC_FAR * This,
    /* [retval][out] */ ICCStream __RPC_FAR *__RPC_FAR *pStream);


void __RPC_STUB ICCBaseline_get_Stream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBaseline_get_UsedByStreams_Proxy( 
    ICCBaseline __RPC_FAR * This,
    /* [retval][out] */ ICCStreams __RPC_FAR *__RPC_FAR *pUsedByStreams);


void __RPC_STUB ICCBaseline_get_UsedByStreams_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCBaseline_INTERFACE_DEFINED__ */


#ifndef __ICCActivities_INTERFACE_DEFINED__
#define __ICCActivities_INTERFACE_DEFINED__

/* interface ICCActivities */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCActivities,0xB22C7F30,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7F30-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCActivities : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long index,
            /* [retval][out] */ ICCActivity __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ICCActivity __RPC_FAR *pActivity) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long index) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCActivitiesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCActivities __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCActivities __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCActivities __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCActivities __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCActivities __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCActivities __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCActivities __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ICCActivities __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ ICCActivity __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            ICCActivities __RPC_FAR * This,
            /* [in] */ ICCActivity __RPC_FAR *pActivity);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ICCActivities __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ICCActivities __RPC_FAR * This,
            /* [in] */ long index);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ICCActivities __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);
        
        END_INTERFACE
    } ICCActivitiesVtbl;

    interface ICCActivities
    {
        CONST_VTBL struct ICCActivitiesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCActivities_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCActivities_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCActivities_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCActivities_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCActivities_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCActivities_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCActivities_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCActivities_get_Item(This,index,pItem)	\
    (This)->lpVtbl -> get_Item(This,index,pItem)

#define ICCActivities_Add(This,pActivity)	\
    (This)->lpVtbl -> Add(This,pActivity)

#define ICCActivities_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define ICCActivities_Remove(This,index)	\
    (This)->lpVtbl -> Remove(This,index)

#define ICCActivities_get__NewEnum(This,pEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,pEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCActivities_get_Item_Proxy( 
    ICCActivities __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ ICCActivity __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB ICCActivities_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCActivities_Add_Proxy( 
    ICCActivities __RPC_FAR * This,
    /* [in] */ ICCActivity __RPC_FAR *pActivity);


void __RPC_STUB ICCActivities_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCActivities_get_Count_Proxy( 
    ICCActivities __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB ICCActivities_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCActivities_Remove_Proxy( 
    ICCActivities __RPC_FAR * This,
    /* [in] */ long index);


void __RPC_STUB ICCActivities_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICCActivities_get__NewEnum_Proxy( 
    ICCActivities __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);


void __RPC_STUB ICCActivities_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCActivities_INTERFACE_DEFINED__ */


#ifndef __ICCComponent_INTERFACE_DEFINED__
#define __ICCComponent_INTERFACE_DEFINED__

/* interface ICCComponent */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCComponent,0xB22C7F2B,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7F2B-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCComponent : public ICCUCMObject
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_RootDirectoryElement( 
            /* [retval][out] */ ICCElement __RPC_FAR *__RPC_FAR *pElement) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCComponentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCComponent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCComponent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCComponent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCComponent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCComponent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCComponent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCComponent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attribute )( 
            ICCComponent __RPC_FAR * This,
            /* [in] */ BSTR AttributeType,
            /* [retval][out] */ ICCAttribute __RPC_FAR *__RPC_FAR *pAttribute);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attributes )( 
            ICCComponent __RPC_FAR * This,
            /* [retval][out] */ ICCAttributes __RPC_FAR *__RPC_FAR *pAttributes);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Comment )( 
            ICCComponent __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pComment);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Comment )( 
            ICCComponent __RPC_FAR * This,
            /* [in] */ BSTR pComment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreationRecord )( 
            ICCComponent __RPC_FAR * This,
            /* [retval][out] */ ICCHistoryRecord __RPC_FAR *__RPC_FAR *pHistoryRecord);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HistoryRecords )( 
            ICCComponent __RPC_FAR * This,
            /* [in] */ ICCBranchType __RPC_FAR *pICCBranchType,
            /* [defaultvalue][optional][in] */ DATE Since,
            /* [defaultvalue][optional][in] */ BSTR User,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Minor,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL ExcludeCheckOutEvents,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL DirectoryOnly,
            /* [retval][out] */ ICCHistoryRecords __RPC_FAR *__RPC_FAR *pHistoryRecords);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hyperlinks )( 
            ICCComponent __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR HyperlinkType,
            /* [retval][out] */ ICCHyperlinks __RPC_FAR *__RPC_FAR *pHyperlinks);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OID )( 
            ICCComponent __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOBFamilyUUID )( 
            ICCComponent __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVOBFamilyUUID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ICCComponent __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateLock )( 
            ICCComponent __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
            /* [optional][in] */ VARIANT ExemptUsersStringArray);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Group )( 
            ICCComponent __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pGroup);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Lock )( 
            ICCComponent __RPC_FAR * This,
            /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Master )( 
            ICCComponent __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pReplica);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Owner )( 
            ICCComponent __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOwner);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProjectVOB )( 
            ICCComponent __RPC_FAR * This,
            /* [retval][out] */ ICCProjectVOB __RPC_FAR *__RPC_FAR *pProjectVOB);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGroup )( 
            ICCComponent __RPC_FAR * This,
            /* [in] */ BSTR NewGroup,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMaster )( 
            ICCComponent __RPC_FAR * This,
            /* [in] */ BSTR Replica,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOwner )( 
            ICCComponent __RPC_FAR * This,
            /* [in] */ BSTR NewOwner,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Title )( 
            ICCComponent __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pTitle);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RootDirectoryElement )( 
            ICCComponent __RPC_FAR * This,
            /* [retval][out] */ ICCElement __RPC_FAR *__RPC_FAR *pElement);
        
        END_INTERFACE
    } ICCComponentVtbl;

    interface ICCComponent
    {
        CONST_VTBL struct ICCComponentVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCComponent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCComponent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCComponent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCComponent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCComponent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCComponent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCComponent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCComponent_get_Attribute(This,AttributeType,pAttribute)	\
    (This)->lpVtbl -> get_Attribute(This,AttributeType,pAttribute)

#define ICCComponent_get_Attributes(This,pAttributes)	\
    (This)->lpVtbl -> get_Attributes(This,pAttributes)

#define ICCComponent_get_Comment(This,pComment)	\
    (This)->lpVtbl -> get_Comment(This,pComment)

#define ICCComponent_put_Comment(This,pComment)	\
    (This)->lpVtbl -> put_Comment(This,pComment)

#define ICCComponent_get_CreationRecord(This,pHistoryRecord)	\
    (This)->lpVtbl -> get_CreationRecord(This,pHistoryRecord)

#define ICCComponent_get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)	\
    (This)->lpVtbl -> get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)

#define ICCComponent_get_Hyperlinks(This,HyperlinkType,pHyperlinks)	\
    (This)->lpVtbl -> get_Hyperlinks(This,HyperlinkType,pHyperlinks)

#define ICCComponent_get_OID(This,pOID)	\
    (This)->lpVtbl -> get_OID(This,pOID)

#define ICCComponent_get_VOBFamilyUUID(This,pVOBFamilyUUID)	\
    (This)->lpVtbl -> get_VOBFamilyUUID(This,pVOBFamilyUUID)


#define ICCComponent_get_Name(This,pName)	\
    (This)->lpVtbl -> get_Name(This,pName)

#define ICCComponent_CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)	\
    (This)->lpVtbl -> CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)

#define ICCComponent_get_Group(This,pGroup)	\
    (This)->lpVtbl -> get_Group(This,pGroup)

#define ICCComponent_get_Lock(This,pLock)	\
    (This)->lpVtbl -> get_Lock(This,pLock)

#define ICCComponent_get_Master(This,pReplica)	\
    (This)->lpVtbl -> get_Master(This,pReplica)

#define ICCComponent_get_Owner(This,pOwner)	\
    (This)->lpVtbl -> get_Owner(This,pOwner)

#define ICCComponent_get_ProjectVOB(This,pProjectVOB)	\
    (This)->lpVtbl -> get_ProjectVOB(This,pProjectVOB)

#define ICCComponent_SetGroup(This,NewGroup,Comment)	\
    (This)->lpVtbl -> SetGroup(This,NewGroup,Comment)

#define ICCComponent_SetMaster(This,Replica,Comment)	\
    (This)->lpVtbl -> SetMaster(This,Replica,Comment)

#define ICCComponent_SetOwner(This,NewOwner,Comment)	\
    (This)->lpVtbl -> SetOwner(This,NewOwner,Comment)

#define ICCComponent_get_Title(This,pTitle)	\
    (This)->lpVtbl -> get_Title(This,pTitle)


#define ICCComponent_get_RootDirectoryElement(This,pElement)	\
    (This)->lpVtbl -> get_RootDirectoryElement(This,pElement)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCComponent_get_RootDirectoryElement_Proxy( 
    ICCComponent __RPC_FAR * This,
    /* [retval][out] */ ICCElement __RPC_FAR *__RPC_FAR *pElement);


void __RPC_STUB ICCComponent_get_RootDirectoryElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCComponent_INTERFACE_DEFINED__ */


#ifndef __ICCElement_INTERFACE_DEFINED__
#define __ICCElement_INTERFACE_DEFINED__

/* interface ICCElement */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCElement,0xB22C7ED2,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7ED2-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCElement : public ICCFile
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_CheckedOutFile( 
            /* [retval][out] */ ICCCheckedOutFile __RPC_FAR *__RPC_FAR *pCheckedOutFile) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateLock( 
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
            /* [optional][in] */ VARIANT ExemptUsersStringArray) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ElementType( 
            /* [retval][out] */ BSTR __RPC_FAR *pElementType) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Group( 
            /* [retval][out] */ BSTR __RPC_FAR *pGroup) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Lock( 
            /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Master( 
            /* [retval][out] */ BSTR __RPC_FAR *pReplica) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ ICCElement __RPC_FAR *pNewParent,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Owner( 
            /* [retval][out] */ BSTR __RPC_FAR *pOwner) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ ICCElement __RPC_FAR *__RPC_FAR *pParent) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Permissions( 
            /* [retval][out] */ long __RPC_FAR *pPermissions) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveElement( 
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveName( 
            /* [defaultvalue][optional][in] */ BSTR Comment = L"",
            /* [defaultvalue][optional][in] */ VARIANT_BOOL DirectoryMustBeCheckedOut = -1) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Rename( 
            /* [in] */ BSTR NewName,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetGroup( 
            /* [in] */ BSTR NewGroup,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMaster( 
            /* [in] */ BSTR Replica,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetOwner( 
            /* [in] */ BSTR NewOwner,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPermissions( 
            /* [in] */ long NewPermissions,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Trigger( 
            /* [in] */ BSTR TriggerType,
            /* [retval][out] */ ICCTrigger __RPC_FAR *__RPC_FAR *pTrigger) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Triggers( 
            /* [retval][out] */ ICCTriggers __RPC_FAR *__RPC_FAR *pTriggers) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [defaultvalue][optional][in] */ BSTR Selector,
            /* [retval][out] */ ICCVersion __RPC_FAR *__RPC_FAR *pVersion) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCElement __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCElement __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCElement __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCElement __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attribute )( 
            ICCElement __RPC_FAR * This,
            /* [in] */ BSTR AttributeType,
            /* [retval][out] */ ICCAttribute __RPC_FAR *__RPC_FAR *pAttribute);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attributes )( 
            ICCElement __RPC_FAR * This,
            /* [retval][out] */ ICCAttributes __RPC_FAR *__RPC_FAR *pAttributes);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Comment )( 
            ICCElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pComment);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Comment )( 
            ICCElement __RPC_FAR * This,
            /* [in] */ BSTR pComment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreationRecord )( 
            ICCElement __RPC_FAR * This,
            /* [retval][out] */ ICCHistoryRecord __RPC_FAR *__RPC_FAR *pHistoryRecord);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HistoryRecords )( 
            ICCElement __RPC_FAR * This,
            /* [in] */ ICCBranchType __RPC_FAR *pICCBranchType,
            /* [defaultvalue][optional][in] */ DATE Since,
            /* [defaultvalue][optional][in] */ BSTR User,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Minor,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL ExcludeCheckOutEvents,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL DirectoryOnly,
            /* [retval][out] */ ICCHistoryRecords __RPC_FAR *__RPC_FAR *pHistoryRecords);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hyperlinks )( 
            ICCElement __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR HyperlinkType,
            /* [retval][out] */ ICCHyperlinks __RPC_FAR *__RPC_FAR *pHyperlinks);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OID )( 
            ICCElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOBFamilyUUID )( 
            ICCElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVOBFamilyUUID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Path )( 
            ICCElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pPath);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExtendedPath )( 
            ICCElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pExtendedPath);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExtendedPathInView )( 
            ICCElement __RPC_FAR * This,
            /* [in] */ ICCView __RPC_FAR *pView,
            /* [retval][out] */ BSTR __RPC_FAR *pExtendedPath);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsDirectory )( 
            ICCElement __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsDirectory);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PathInView )( 
            ICCElement __RPC_FAR * This,
            /* [in] */ ICCView __RPC_FAR *pView,
            /* [retval][out] */ BSTR __RPC_FAR *pPath);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_View )( 
            ICCElement __RPC_FAR * This,
            /* [retval][out] */ ICCView __RPC_FAR *__RPC_FAR *pView);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOB )( 
            ICCElement __RPC_FAR * This,
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CheckedOutFile )( 
            ICCElement __RPC_FAR * This,
            /* [retval][out] */ ICCCheckedOutFile __RPC_FAR *__RPC_FAR *pCheckedOutFile);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateLock )( 
            ICCElement __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
            /* [optional][in] */ VARIANT ExemptUsersStringArray);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ElementType )( 
            ICCElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pElementType);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Group )( 
            ICCElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pGroup);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Lock )( 
            ICCElement __RPC_FAR * This,
            /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Master )( 
            ICCElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pReplica);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Move )( 
            ICCElement __RPC_FAR * This,
            /* [in] */ ICCElement __RPC_FAR *pNewParent,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Owner )( 
            ICCElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOwner);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            ICCElement __RPC_FAR * This,
            /* [retval][out] */ ICCElement __RPC_FAR *__RPC_FAR *pParent);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Permissions )( 
            ICCElement __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pPermissions);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveElement )( 
            ICCElement __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveName )( 
            ICCElement __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL DirectoryMustBeCheckedOut);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Rename )( 
            ICCElement __RPC_FAR * This,
            /* [in] */ BSTR NewName,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGroup )( 
            ICCElement __RPC_FAR * This,
            /* [in] */ BSTR NewGroup,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMaster )( 
            ICCElement __RPC_FAR * This,
            /* [in] */ BSTR Replica,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOwner )( 
            ICCElement __RPC_FAR * This,
            /* [in] */ BSTR NewOwner,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPermissions )( 
            ICCElement __RPC_FAR * This,
            /* [in] */ long NewPermissions,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Trigger )( 
            ICCElement __RPC_FAR * This,
            /* [in] */ BSTR TriggerType,
            /* [retval][out] */ ICCTrigger __RPC_FAR *__RPC_FAR *pTrigger);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Triggers )( 
            ICCElement __RPC_FAR * This,
            /* [retval][out] */ ICCTriggers __RPC_FAR *__RPC_FAR *pTriggers);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            ICCElement __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Selector,
            /* [retval][out] */ ICCVersion __RPC_FAR *__RPC_FAR *pVersion);
        
        END_INTERFACE
    } ICCElementVtbl;

    interface ICCElement
    {
        CONST_VTBL struct ICCElementVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCElement_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCElement_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCElement_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCElement_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCElement_get_Attribute(This,AttributeType,pAttribute)	\
    (This)->lpVtbl -> get_Attribute(This,AttributeType,pAttribute)

#define ICCElement_get_Attributes(This,pAttributes)	\
    (This)->lpVtbl -> get_Attributes(This,pAttributes)

#define ICCElement_get_Comment(This,pComment)	\
    (This)->lpVtbl -> get_Comment(This,pComment)

#define ICCElement_put_Comment(This,pComment)	\
    (This)->lpVtbl -> put_Comment(This,pComment)

#define ICCElement_get_CreationRecord(This,pHistoryRecord)	\
    (This)->lpVtbl -> get_CreationRecord(This,pHistoryRecord)

#define ICCElement_get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)	\
    (This)->lpVtbl -> get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)

#define ICCElement_get_Hyperlinks(This,HyperlinkType,pHyperlinks)	\
    (This)->lpVtbl -> get_Hyperlinks(This,HyperlinkType,pHyperlinks)

#define ICCElement_get_OID(This,pOID)	\
    (This)->lpVtbl -> get_OID(This,pOID)

#define ICCElement_get_VOBFamilyUUID(This,pVOBFamilyUUID)	\
    (This)->lpVtbl -> get_VOBFamilyUUID(This,pVOBFamilyUUID)


#define ICCElement_get_Path(This,pPath)	\
    (This)->lpVtbl -> get_Path(This,pPath)

#define ICCElement_get_ExtendedPath(This,pExtendedPath)	\
    (This)->lpVtbl -> get_ExtendedPath(This,pExtendedPath)

#define ICCElement_get_ExtendedPathInView(This,pView,pExtendedPath)	\
    (This)->lpVtbl -> get_ExtendedPathInView(This,pView,pExtendedPath)

#define ICCElement_get_IsDirectory(This,pIsDirectory)	\
    (This)->lpVtbl -> get_IsDirectory(This,pIsDirectory)

#define ICCElement_get_PathInView(This,pView,pPath)	\
    (This)->lpVtbl -> get_PathInView(This,pView,pPath)

#define ICCElement_get_View(This,pView)	\
    (This)->lpVtbl -> get_View(This,pView)

#define ICCElement_get_VOB(This,pVOB)	\
    (This)->lpVtbl -> get_VOB(This,pVOB)


#define ICCElement_get_CheckedOutFile(This,pCheckedOutFile)	\
    (This)->lpVtbl -> get_CheckedOutFile(This,pCheckedOutFile)

#define ICCElement_CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)	\
    (This)->lpVtbl -> CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)

#define ICCElement_get_ElementType(This,pElementType)	\
    (This)->lpVtbl -> get_ElementType(This,pElementType)

#define ICCElement_get_Group(This,pGroup)	\
    (This)->lpVtbl -> get_Group(This,pGroup)

#define ICCElement_get_Lock(This,pLock)	\
    (This)->lpVtbl -> get_Lock(This,pLock)

#define ICCElement_get_Master(This,pReplica)	\
    (This)->lpVtbl -> get_Master(This,pReplica)

#define ICCElement_Move(This,pNewParent,Comment)	\
    (This)->lpVtbl -> Move(This,pNewParent,Comment)

#define ICCElement_get_Owner(This,pOwner)	\
    (This)->lpVtbl -> get_Owner(This,pOwner)

#define ICCElement_get_Parent(This,pParent)	\
    (This)->lpVtbl -> get_Parent(This,pParent)

#define ICCElement_get_Permissions(This,pPermissions)	\
    (This)->lpVtbl -> get_Permissions(This,pPermissions)

#define ICCElement_RemoveElement(This,Comment)	\
    (This)->lpVtbl -> RemoveElement(This,Comment)

#define ICCElement_RemoveName(This,Comment,DirectoryMustBeCheckedOut)	\
    (This)->lpVtbl -> RemoveName(This,Comment,DirectoryMustBeCheckedOut)

#define ICCElement_Rename(This,NewName,Comment)	\
    (This)->lpVtbl -> Rename(This,NewName,Comment)

#define ICCElement_SetGroup(This,NewGroup,Comment)	\
    (This)->lpVtbl -> SetGroup(This,NewGroup,Comment)

#define ICCElement_SetMaster(This,Replica,Comment)	\
    (This)->lpVtbl -> SetMaster(This,Replica,Comment)

#define ICCElement_SetOwner(This,NewOwner,Comment)	\
    (This)->lpVtbl -> SetOwner(This,NewOwner,Comment)

#define ICCElement_SetPermissions(This,NewPermissions,Comment)	\
    (This)->lpVtbl -> SetPermissions(This,NewPermissions,Comment)

#define ICCElement_get_Trigger(This,TriggerType,pTrigger)	\
    (This)->lpVtbl -> get_Trigger(This,TriggerType,pTrigger)

#define ICCElement_get_Triggers(This,pTriggers)	\
    (This)->lpVtbl -> get_Triggers(This,pTriggers)

#define ICCElement_get_Version(This,Selector,pVersion)	\
    (This)->lpVtbl -> get_Version(This,Selector,pVersion)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCElement_get_CheckedOutFile_Proxy( 
    ICCElement __RPC_FAR * This,
    /* [retval][out] */ ICCCheckedOutFile __RPC_FAR *__RPC_FAR *pCheckedOutFile);


void __RPC_STUB ICCElement_get_CheckedOutFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCElement_CreateLock_Proxy( 
    ICCElement __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Comment,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
    /* [optional][in] */ VARIANT ExemptUsersStringArray);


void __RPC_STUB ICCElement_CreateLock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCElement_get_ElementType_Proxy( 
    ICCElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pElementType);


void __RPC_STUB ICCElement_get_ElementType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCElement_get_Group_Proxy( 
    ICCElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pGroup);


void __RPC_STUB ICCElement_get_Group_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCElement_get_Lock_Proxy( 
    ICCElement __RPC_FAR * This,
    /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock);


void __RPC_STUB ICCElement_get_Lock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCElement_get_Master_Proxy( 
    ICCElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pReplica);


void __RPC_STUB ICCElement_get_Master_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCElement_Move_Proxy( 
    ICCElement __RPC_FAR * This,
    /* [in] */ ICCElement __RPC_FAR *pNewParent,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCElement_Move_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCElement_get_Owner_Proxy( 
    ICCElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pOwner);


void __RPC_STUB ICCElement_get_Owner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCElement_get_Parent_Proxy( 
    ICCElement __RPC_FAR * This,
    /* [retval][out] */ ICCElement __RPC_FAR *__RPC_FAR *pParent);


void __RPC_STUB ICCElement_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCElement_get_Permissions_Proxy( 
    ICCElement __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pPermissions);


void __RPC_STUB ICCElement_get_Permissions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCElement_RemoveElement_Proxy( 
    ICCElement __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCElement_RemoveElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCElement_RemoveName_Proxy( 
    ICCElement __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Comment,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL DirectoryMustBeCheckedOut);


void __RPC_STUB ICCElement_RemoveName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCElement_Rename_Proxy( 
    ICCElement __RPC_FAR * This,
    /* [in] */ BSTR NewName,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCElement_Rename_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCElement_SetGroup_Proxy( 
    ICCElement __RPC_FAR * This,
    /* [in] */ BSTR NewGroup,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCElement_SetGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCElement_SetMaster_Proxy( 
    ICCElement __RPC_FAR * This,
    /* [in] */ BSTR Replica,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCElement_SetMaster_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCElement_SetOwner_Proxy( 
    ICCElement __RPC_FAR * This,
    /* [in] */ BSTR NewOwner,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCElement_SetOwner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCElement_SetPermissions_Proxy( 
    ICCElement __RPC_FAR * This,
    /* [in] */ long NewPermissions,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCElement_SetPermissions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCElement_get_Trigger_Proxy( 
    ICCElement __RPC_FAR * This,
    /* [in] */ BSTR TriggerType,
    /* [retval][out] */ ICCTrigger __RPC_FAR *__RPC_FAR *pTrigger);


void __RPC_STUB ICCElement_get_Trigger_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCElement_get_Triggers_Proxy( 
    ICCElement __RPC_FAR * This,
    /* [retval][out] */ ICCTriggers __RPC_FAR *__RPC_FAR *pTriggers);


void __RPC_STUB ICCElement_get_Triggers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCElement_get_Version_Proxy( 
    ICCElement __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Selector,
    /* [retval][out] */ ICCVersion __RPC_FAR *__RPC_FAR *pVersion);


void __RPC_STUB ICCElement_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCElement_INTERFACE_DEFINED__ */


#ifndef __ICCCheckedOutFile_INTERFACE_DEFINED__
#define __ICCCheckedOutFile_INTERFACE_DEFINED__

/* interface ICCCheckedOutFile */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCCheckedOutFile,0xB22C7ED9,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7ED9-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCCheckedOutFile : public ICCVersion
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ByView( 
            /* [retval][out] */ ICCView __RPC_FAR *__RPC_FAR *pByView) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CheckIn( 
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL EvenIfIdentical,
            /* [defaultvalue][optional][in] */ BSTR FromPath,
            /* [defaultvalue][optional][in] */ CCKeepState KeepState,
            /* [retval][out] */ ICCVersion __RPC_FAR *__RPC_FAR *pNewVersion) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IsReserved( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsReserved) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Reserve( 
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE UnCheckOut( 
            /* [in] */ CCKeepState KeepState,
            /* [retval][out] */ ICCVersion __RPC_FAR *__RPC_FAR *pPredVersion) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE UnReserve( 
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCCheckedOutFileVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCCheckedOutFile __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCCheckedOutFile __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attribute )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [in] */ BSTR AttributeType,
            /* [retval][out] */ ICCAttribute __RPC_FAR *__RPC_FAR *pAttribute);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attributes )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [retval][out] */ ICCAttributes __RPC_FAR *__RPC_FAR *pAttributes);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Comment )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pComment);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Comment )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [in] */ BSTR pComment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreationRecord )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [retval][out] */ ICCHistoryRecord __RPC_FAR *__RPC_FAR *pHistoryRecord);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HistoryRecords )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [in] */ ICCBranchType __RPC_FAR *pICCBranchType,
            /* [defaultvalue][optional][in] */ DATE Since,
            /* [defaultvalue][optional][in] */ BSTR User,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Minor,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL ExcludeCheckOutEvents,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL DirectoryOnly,
            /* [retval][out] */ ICCHistoryRecords __RPC_FAR *__RPC_FAR *pHistoryRecords);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hyperlinks )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR HyperlinkType,
            /* [retval][out] */ ICCHyperlinks __RPC_FAR *__RPC_FAR *pHyperlinks);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OID )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOBFamilyUUID )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVOBFamilyUUID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Path )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pPath);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExtendedPath )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pExtendedPath);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExtendedPathInView )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [in] */ ICCView __RPC_FAR *pView,
            /* [retval][out] */ BSTR __RPC_FAR *pExtendedPath);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsDirectory )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsDirectory);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PathInView )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [in] */ ICCView __RPC_FAR *pView,
            /* [retval][out] */ BSTR __RPC_FAR *pPath);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_View )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [retval][out] */ ICCView __RPC_FAR *__RPC_FAR *pView);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOB )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Branch )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [retval][out] */ ICCBranch __RPC_FAR *__RPC_FAR *pBranch);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CheckOut )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [in] */ CCReservedState ReservedState,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL UseHijacked,
            /* [defaultvalue][optional][in] */ CCVersionToCheckOut Version,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL MustBeLatest,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL PreserveTime,
            /* [retval][out] */ ICCCheckedOutFile __RPC_FAR *__RPC_FAR *pCheckedOutFile);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Element )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [retval][out] */ ICCElement __RPC_FAR *__RPC_FAR *pElement);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Identifier )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pIdentifier);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsCheckedOut )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsCheckedOut);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsDifferent )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsDifferent);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsHijacked )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsHijacked);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsLatest )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsLatest);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Label )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [in] */ BSTR LabelType,
            /* [retval][out] */ ICCLabel __RPC_FAR *__RPC_FAR *pLabel);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Labels )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [retval][out] */ ICCLabels __RPC_FAR *__RPC_FAR *pLabels);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [retval][out] */ ICCVersion __RPC_FAR *__RPC_FAR *pParent);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Predecessor )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [retval][out] */ ICCVersion __RPC_FAR *__RPC_FAR *pPredecessor);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveVersion )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL DataOnly,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL EvenIfBranches,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL EvenIfLabels,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL EvenIfAttributes,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL EvenIfHyperlinks);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SubBranches )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [retval][out] */ ICCBranches __RPC_FAR *__RPC_FAR *pBranches);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VersionNumber )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVersionNumber);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ByView )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [retval][out] */ ICCView __RPC_FAR *__RPC_FAR *pByView);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CheckIn )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL EvenIfIdentical,
            /* [defaultvalue][optional][in] */ BSTR FromPath,
            /* [defaultvalue][optional][in] */ CCKeepState KeepState,
            /* [retval][out] */ ICCVersion __RPC_FAR *__RPC_FAR *pNewVersion);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsReserved )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsReserved);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserve )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnCheckOut )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [in] */ CCKeepState KeepState,
            /* [retval][out] */ ICCVersion __RPC_FAR *__RPC_FAR *pPredVersion);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnReserve )( 
            ICCCheckedOutFile __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        END_INTERFACE
    } ICCCheckedOutFileVtbl;

    interface ICCCheckedOutFile
    {
        CONST_VTBL struct ICCCheckedOutFileVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCCheckedOutFile_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCCheckedOutFile_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCCheckedOutFile_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCCheckedOutFile_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCCheckedOutFile_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCCheckedOutFile_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCCheckedOutFile_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCCheckedOutFile_get_Attribute(This,AttributeType,pAttribute)	\
    (This)->lpVtbl -> get_Attribute(This,AttributeType,pAttribute)

#define ICCCheckedOutFile_get_Attributes(This,pAttributes)	\
    (This)->lpVtbl -> get_Attributes(This,pAttributes)

#define ICCCheckedOutFile_get_Comment(This,pComment)	\
    (This)->lpVtbl -> get_Comment(This,pComment)

#define ICCCheckedOutFile_put_Comment(This,pComment)	\
    (This)->lpVtbl -> put_Comment(This,pComment)

#define ICCCheckedOutFile_get_CreationRecord(This,pHistoryRecord)	\
    (This)->lpVtbl -> get_CreationRecord(This,pHistoryRecord)

#define ICCCheckedOutFile_get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)	\
    (This)->lpVtbl -> get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)

#define ICCCheckedOutFile_get_Hyperlinks(This,HyperlinkType,pHyperlinks)	\
    (This)->lpVtbl -> get_Hyperlinks(This,HyperlinkType,pHyperlinks)

#define ICCCheckedOutFile_get_OID(This,pOID)	\
    (This)->lpVtbl -> get_OID(This,pOID)

#define ICCCheckedOutFile_get_VOBFamilyUUID(This,pVOBFamilyUUID)	\
    (This)->lpVtbl -> get_VOBFamilyUUID(This,pVOBFamilyUUID)


#define ICCCheckedOutFile_get_Path(This,pPath)	\
    (This)->lpVtbl -> get_Path(This,pPath)

#define ICCCheckedOutFile_get_ExtendedPath(This,pExtendedPath)	\
    (This)->lpVtbl -> get_ExtendedPath(This,pExtendedPath)

#define ICCCheckedOutFile_get_ExtendedPathInView(This,pView,pExtendedPath)	\
    (This)->lpVtbl -> get_ExtendedPathInView(This,pView,pExtendedPath)

#define ICCCheckedOutFile_get_IsDirectory(This,pIsDirectory)	\
    (This)->lpVtbl -> get_IsDirectory(This,pIsDirectory)

#define ICCCheckedOutFile_get_PathInView(This,pView,pPath)	\
    (This)->lpVtbl -> get_PathInView(This,pView,pPath)

#define ICCCheckedOutFile_get_View(This,pView)	\
    (This)->lpVtbl -> get_View(This,pView)

#define ICCCheckedOutFile_get_VOB(This,pVOB)	\
    (This)->lpVtbl -> get_VOB(This,pVOB)


#define ICCCheckedOutFile_get_Branch(This,pBranch)	\
    (This)->lpVtbl -> get_Branch(This,pBranch)

#define ICCCheckedOutFile_CheckOut(This,ReservedState,Comment,UseHijacked,Version,MustBeLatest,PreserveTime,pCheckedOutFile)	\
    (This)->lpVtbl -> CheckOut(This,ReservedState,Comment,UseHijacked,Version,MustBeLatest,PreserveTime,pCheckedOutFile)

#define ICCCheckedOutFile_get_Element(This,pElement)	\
    (This)->lpVtbl -> get_Element(This,pElement)

#define ICCCheckedOutFile_get_Identifier(This,pIdentifier)	\
    (This)->lpVtbl -> get_Identifier(This,pIdentifier)

#define ICCCheckedOutFile_get_IsCheckedOut(This,pIsCheckedOut)	\
    (This)->lpVtbl -> get_IsCheckedOut(This,pIsCheckedOut)

#define ICCCheckedOutFile_get_IsDifferent(This,pIsDifferent)	\
    (This)->lpVtbl -> get_IsDifferent(This,pIsDifferent)

#define ICCCheckedOutFile_get_IsHijacked(This,pIsHijacked)	\
    (This)->lpVtbl -> get_IsHijacked(This,pIsHijacked)

#define ICCCheckedOutFile_get_IsLatest(This,pIsLatest)	\
    (This)->lpVtbl -> get_IsLatest(This,pIsLatest)

#define ICCCheckedOutFile_get_Label(This,LabelType,pLabel)	\
    (This)->lpVtbl -> get_Label(This,LabelType,pLabel)

#define ICCCheckedOutFile_get_Labels(This,pLabels)	\
    (This)->lpVtbl -> get_Labels(This,pLabels)

#define ICCCheckedOutFile_get_Parent(This,pParent)	\
    (This)->lpVtbl -> get_Parent(This,pParent)

#define ICCCheckedOutFile_get_Predecessor(This,pPredecessor)	\
    (This)->lpVtbl -> get_Predecessor(This,pPredecessor)

#define ICCCheckedOutFile_RemoveVersion(This,Comment,DataOnly,EvenIfBranches,EvenIfLabels,EvenIfAttributes,EvenIfHyperlinks)	\
    (This)->lpVtbl -> RemoveVersion(This,Comment,DataOnly,EvenIfBranches,EvenIfLabels,EvenIfAttributes,EvenIfHyperlinks)

#define ICCCheckedOutFile_get_SubBranches(This,pBranches)	\
    (This)->lpVtbl -> get_SubBranches(This,pBranches)

#define ICCCheckedOutFile_get_VersionNumber(This,pVersionNumber)	\
    (This)->lpVtbl -> get_VersionNumber(This,pVersionNumber)


#define ICCCheckedOutFile_get_ByView(This,pByView)	\
    (This)->lpVtbl -> get_ByView(This,pByView)

#define ICCCheckedOutFile_CheckIn(This,Comment,EvenIfIdentical,FromPath,KeepState,pNewVersion)	\
    (This)->lpVtbl -> CheckIn(This,Comment,EvenIfIdentical,FromPath,KeepState,pNewVersion)

#define ICCCheckedOutFile_get_IsReserved(This,pIsReserved)	\
    (This)->lpVtbl -> get_IsReserved(This,pIsReserved)

#define ICCCheckedOutFile_Reserve(This,Comment)	\
    (This)->lpVtbl -> Reserve(This,Comment)

#define ICCCheckedOutFile_UnCheckOut(This,KeepState,pPredVersion)	\
    (This)->lpVtbl -> UnCheckOut(This,KeepState,pPredVersion)

#define ICCCheckedOutFile_UnReserve(This,Comment)	\
    (This)->lpVtbl -> UnReserve(This,Comment)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCCheckedOutFile_get_ByView_Proxy( 
    ICCCheckedOutFile __RPC_FAR * This,
    /* [retval][out] */ ICCView __RPC_FAR *__RPC_FAR *pByView);


void __RPC_STUB ICCCheckedOutFile_get_ByView_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCCheckedOutFile_CheckIn_Proxy( 
    ICCCheckedOutFile __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Comment,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL EvenIfIdentical,
    /* [defaultvalue][optional][in] */ BSTR FromPath,
    /* [defaultvalue][optional][in] */ CCKeepState KeepState,
    /* [retval][out] */ ICCVersion __RPC_FAR *__RPC_FAR *pNewVersion);


void __RPC_STUB ICCCheckedOutFile_CheckIn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCCheckedOutFile_get_IsReserved_Proxy( 
    ICCCheckedOutFile __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsReserved);


void __RPC_STUB ICCCheckedOutFile_get_IsReserved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCCheckedOutFile_Reserve_Proxy( 
    ICCCheckedOutFile __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCCheckedOutFile_Reserve_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCCheckedOutFile_UnCheckOut_Proxy( 
    ICCCheckedOutFile __RPC_FAR * This,
    /* [in] */ CCKeepState KeepState,
    /* [retval][out] */ ICCVersion __RPC_FAR *__RPC_FAR *pPredVersion);


void __RPC_STUB ICCCheckedOutFile_UnCheckOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCCheckedOutFile_UnReserve_Proxy( 
    ICCCheckedOutFile __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCCheckedOutFile_UnReserve_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCCheckedOutFile_INTERFACE_DEFINED__ */


#ifndef __ICCTrigger_INTERFACE_DEFINED__
#define __ICCTrigger_INTERFACE_DEFINED__

/* interface ICCTrigger */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCTrigger,0xB22C7EF5,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7EF5-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCTrigger : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IsOnAttachedList( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsOnAttachedList) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IsOnInheritanceList( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsOnInheritanceList) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse,
            /* [optional][in] */ VARIANT DirectoryListsSubset) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ ICCTriggerType __RPC_FAR *__RPC_FAR *pType) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_VOB( 
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCTriggerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCTrigger __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCTrigger __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCTrigger __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCTrigger __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCTrigger __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCTrigger __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCTrigger __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsOnAttachedList )( 
            ICCTrigger __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsOnAttachedList);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsOnInheritanceList )( 
            ICCTrigger __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsOnInheritanceList);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ICCTrigger __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse,
            /* [optional][in] */ VARIANT DirectoryListsSubset);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            ICCTrigger __RPC_FAR * This,
            /* [retval][out] */ ICCTriggerType __RPC_FAR *__RPC_FAR *pType);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOB )( 
            ICCTrigger __RPC_FAR * This,
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);
        
        END_INTERFACE
    } ICCTriggerVtbl;

    interface ICCTrigger
    {
        CONST_VTBL struct ICCTriggerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCTrigger_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCTrigger_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCTrigger_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCTrigger_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCTrigger_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCTrigger_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCTrigger_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCTrigger_get_IsOnAttachedList(This,pIsOnAttachedList)	\
    (This)->lpVtbl -> get_IsOnAttachedList(This,pIsOnAttachedList)

#define ICCTrigger_get_IsOnInheritanceList(This,pIsOnInheritanceList)	\
    (This)->lpVtbl -> get_IsOnInheritanceList(This,pIsOnInheritanceList)

#define ICCTrigger_Remove(This,Comment,Recurse,DirectoryListsSubset)	\
    (This)->lpVtbl -> Remove(This,Comment,Recurse,DirectoryListsSubset)

#define ICCTrigger_get_Type(This,pType)	\
    (This)->lpVtbl -> get_Type(This,pType)

#define ICCTrigger_get_VOB(This,pVOB)	\
    (This)->lpVtbl -> get_VOB(This,pVOB)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTrigger_get_IsOnAttachedList_Proxy( 
    ICCTrigger __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsOnAttachedList);


void __RPC_STUB ICCTrigger_get_IsOnAttachedList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTrigger_get_IsOnInheritanceList_Proxy( 
    ICCTrigger __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsOnInheritanceList);


void __RPC_STUB ICCTrigger_get_IsOnInheritanceList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCTrigger_Remove_Proxy( 
    ICCTrigger __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Comment,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse,
    /* [optional][in] */ VARIANT DirectoryListsSubset);


void __RPC_STUB ICCTrigger_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTrigger_get_Type_Proxy( 
    ICCTrigger __RPC_FAR * This,
    /* [retval][out] */ ICCTriggerType __RPC_FAR *__RPC_FAR *pType);


void __RPC_STUB ICCTrigger_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTrigger_get_VOB_Proxy( 
    ICCTrigger __RPC_FAR * This,
    /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);


void __RPC_STUB ICCTrigger_get_VOB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCTrigger_INTERFACE_DEFINED__ */


#ifndef __ICCTriggerType_INTERFACE_DEFINED__
#define __ICCTriggerType_INTERFACE_DEFINED__

/* interface ICCTriggerType */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCTriggerType,0xB22C7EF3,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7EF3-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCTriggerType : public ICCVOBObject
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pName) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ActionsArray( 
            /* [retval][out] */ VARIANT __RPC_FAR *pActionsArray) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Apply( 
            /* [in] */ ICCElement __RPC_FAR *pElement,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Force,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse,
            /* [optional][in] */ VARIANT DirectoryListsSubset) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateBuilderFromType( 
            /* [retval][out] */ ICCTriggerTypeBuilder __RPC_FAR *__RPC_FAR *pTriggerTypeBuilder) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateLock( 
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
            /* [optional][in] */ VARIANT ExemptUsersStringArray) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ExemptUsersStringArray( 
            /* [retval][out] */ VARIANT __RPC_FAR *pExemptUsersStringArray) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Firing( 
            /* [retval][out] */ CCTriggerFiring __RPC_FAR *pFiring) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Group( 
            /* [retval][out] */ BSTR __RPC_FAR *pGroup) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_InclusionsArray( 
            /* [retval][out] */ VARIANT __RPC_FAR *pInclusionsArray) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_KindOfTrigger( 
            /* [retval][out] */ CCKindOfTrigger __RPC_FAR *pKind) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Lock( 
            /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_NumberOfActions( 
            /* [retval][out] */ long __RPC_FAR *pNumberOfActions) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_NumberOfExemptUsers( 
            /* [retval][out] */ long __RPC_FAR *pNumberOfExemptUsers) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_NumberOfInclusions( 
            /* [retval][out] */ long __RPC_FAR *pNumberOfInclusions) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_NumberOfOperationKinds( 
            /* [retval][out] */ long __RPC_FAR *pNumberOfOperationKinds) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_NumberOfRestrictions( 
            /* [retval][out] */ long __RPC_FAR *pNumberOfRestrictions) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_OperationKindsArray( 
            /* [retval][out] */ VARIANT __RPC_FAR *pOperationKindsArray) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Owner( 
            /* [retval][out] */ BSTR __RPC_FAR *pOwner) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_DebugPrinting( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pDebugPrinting) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveType( 
            /* [defaultvalue][optional][in] */ VARIANT_BOOL RemoveAllInstances = 0,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL IgnorePreopTriggers = 0,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_RestrictionsArray( 
            /* [retval][out] */ VARIANT __RPC_FAR *pRestrictionsArray) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetExemptUsersStringArray( 
            /* [optional][in] */ VARIANT ExemptUsersStringArray,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetGroup( 
            /* [in] */ BSTR NewGroup,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetName( 
            /* [in] */ BSTR NewName,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetOwner( 
            /* [in] */ BSTR NewOwner,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDebugPrinting( 
            /* [in] */ VARIANT_BOOL NewDebugPrinting,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_VOB( 
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCTriggerTypeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCTriggerType __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCTriggerType __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCTriggerType __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCTriggerType __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCTriggerType __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCTriggerType __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCTriggerType __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attribute )( 
            ICCTriggerType __RPC_FAR * This,
            /* [in] */ BSTR AttributeType,
            /* [retval][out] */ ICCAttribute __RPC_FAR *__RPC_FAR *pAttribute);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attributes )( 
            ICCTriggerType __RPC_FAR * This,
            /* [retval][out] */ ICCAttributes __RPC_FAR *__RPC_FAR *pAttributes);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Comment )( 
            ICCTriggerType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pComment);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Comment )( 
            ICCTriggerType __RPC_FAR * This,
            /* [in] */ BSTR pComment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreationRecord )( 
            ICCTriggerType __RPC_FAR * This,
            /* [retval][out] */ ICCHistoryRecord __RPC_FAR *__RPC_FAR *pHistoryRecord);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HistoryRecords )( 
            ICCTriggerType __RPC_FAR * This,
            /* [in] */ ICCBranchType __RPC_FAR *pICCBranchType,
            /* [defaultvalue][optional][in] */ DATE Since,
            /* [defaultvalue][optional][in] */ BSTR User,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Minor,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL ExcludeCheckOutEvents,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL DirectoryOnly,
            /* [retval][out] */ ICCHistoryRecords __RPC_FAR *__RPC_FAR *pHistoryRecords);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hyperlinks )( 
            ICCTriggerType __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR HyperlinkType,
            /* [retval][out] */ ICCHyperlinks __RPC_FAR *__RPC_FAR *pHyperlinks);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OID )( 
            ICCTriggerType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOBFamilyUUID )( 
            ICCTriggerType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVOBFamilyUUID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ICCTriggerType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pName);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ActionsArray )( 
            ICCTriggerType __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pActionsArray);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Apply )( 
            ICCTriggerType __RPC_FAR * This,
            /* [in] */ ICCElement __RPC_FAR *pElement,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Force,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse,
            /* [optional][in] */ VARIANT DirectoryListsSubset);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateBuilderFromType )( 
            ICCTriggerType __RPC_FAR * This,
            /* [retval][out] */ ICCTriggerTypeBuilder __RPC_FAR *__RPC_FAR *pTriggerTypeBuilder);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateLock )( 
            ICCTriggerType __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
            /* [optional][in] */ VARIANT ExemptUsersStringArray);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExemptUsersStringArray )( 
            ICCTriggerType __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pExemptUsersStringArray);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Firing )( 
            ICCTriggerType __RPC_FAR * This,
            /* [retval][out] */ CCTriggerFiring __RPC_FAR *pFiring);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Group )( 
            ICCTriggerType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pGroup);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InclusionsArray )( 
            ICCTriggerType __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pInclusionsArray);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_KindOfTrigger )( 
            ICCTriggerType __RPC_FAR * This,
            /* [retval][out] */ CCKindOfTrigger __RPC_FAR *pKind);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Lock )( 
            ICCTriggerType __RPC_FAR * This,
            /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumberOfActions )( 
            ICCTriggerType __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pNumberOfActions);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumberOfExemptUsers )( 
            ICCTriggerType __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pNumberOfExemptUsers);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumberOfInclusions )( 
            ICCTriggerType __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pNumberOfInclusions);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumberOfOperationKinds )( 
            ICCTriggerType __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pNumberOfOperationKinds);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumberOfRestrictions )( 
            ICCTriggerType __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pNumberOfRestrictions);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OperationKindsArray )( 
            ICCTriggerType __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pOperationKindsArray);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Owner )( 
            ICCTriggerType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOwner);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DebugPrinting )( 
            ICCTriggerType __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pDebugPrinting);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveType )( 
            ICCTriggerType __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL RemoveAllInstances,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL IgnorePreopTriggers,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RestrictionsArray )( 
            ICCTriggerType __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pRestrictionsArray);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetExemptUsersStringArray )( 
            ICCTriggerType __RPC_FAR * This,
            /* [optional][in] */ VARIANT ExemptUsersStringArray,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGroup )( 
            ICCTriggerType __RPC_FAR * This,
            /* [in] */ BSTR NewGroup,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetName )( 
            ICCTriggerType __RPC_FAR * This,
            /* [in] */ BSTR NewName,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOwner )( 
            ICCTriggerType __RPC_FAR * This,
            /* [in] */ BSTR NewOwner,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDebugPrinting )( 
            ICCTriggerType __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL NewDebugPrinting,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOB )( 
            ICCTriggerType __RPC_FAR * This,
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);
        
        END_INTERFACE
    } ICCTriggerTypeVtbl;

    interface ICCTriggerType
    {
        CONST_VTBL struct ICCTriggerTypeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCTriggerType_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCTriggerType_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCTriggerType_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCTriggerType_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCTriggerType_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCTriggerType_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCTriggerType_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCTriggerType_get_Attribute(This,AttributeType,pAttribute)	\
    (This)->lpVtbl -> get_Attribute(This,AttributeType,pAttribute)

#define ICCTriggerType_get_Attributes(This,pAttributes)	\
    (This)->lpVtbl -> get_Attributes(This,pAttributes)

#define ICCTriggerType_get_Comment(This,pComment)	\
    (This)->lpVtbl -> get_Comment(This,pComment)

#define ICCTriggerType_put_Comment(This,pComment)	\
    (This)->lpVtbl -> put_Comment(This,pComment)

#define ICCTriggerType_get_CreationRecord(This,pHistoryRecord)	\
    (This)->lpVtbl -> get_CreationRecord(This,pHistoryRecord)

#define ICCTriggerType_get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)	\
    (This)->lpVtbl -> get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)

#define ICCTriggerType_get_Hyperlinks(This,HyperlinkType,pHyperlinks)	\
    (This)->lpVtbl -> get_Hyperlinks(This,HyperlinkType,pHyperlinks)

#define ICCTriggerType_get_OID(This,pOID)	\
    (This)->lpVtbl -> get_OID(This,pOID)

#define ICCTriggerType_get_VOBFamilyUUID(This,pVOBFamilyUUID)	\
    (This)->lpVtbl -> get_VOBFamilyUUID(This,pVOBFamilyUUID)


#define ICCTriggerType_get_Name(This,pName)	\
    (This)->lpVtbl -> get_Name(This,pName)

#define ICCTriggerType_get_ActionsArray(This,pActionsArray)	\
    (This)->lpVtbl -> get_ActionsArray(This,pActionsArray)

#define ICCTriggerType_Apply(This,pElement,Comment,Force,Recurse,DirectoryListsSubset)	\
    (This)->lpVtbl -> Apply(This,pElement,Comment,Force,Recurse,DirectoryListsSubset)

#define ICCTriggerType_CreateBuilderFromType(This,pTriggerTypeBuilder)	\
    (This)->lpVtbl -> CreateBuilderFromType(This,pTriggerTypeBuilder)

#define ICCTriggerType_CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)	\
    (This)->lpVtbl -> CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)

#define ICCTriggerType_get_ExemptUsersStringArray(This,pExemptUsersStringArray)	\
    (This)->lpVtbl -> get_ExemptUsersStringArray(This,pExemptUsersStringArray)

#define ICCTriggerType_get_Firing(This,pFiring)	\
    (This)->lpVtbl -> get_Firing(This,pFiring)

#define ICCTriggerType_get_Group(This,pGroup)	\
    (This)->lpVtbl -> get_Group(This,pGroup)

#define ICCTriggerType_get_InclusionsArray(This,pInclusionsArray)	\
    (This)->lpVtbl -> get_InclusionsArray(This,pInclusionsArray)

#define ICCTriggerType_get_KindOfTrigger(This,pKind)	\
    (This)->lpVtbl -> get_KindOfTrigger(This,pKind)

#define ICCTriggerType_get_Lock(This,pLock)	\
    (This)->lpVtbl -> get_Lock(This,pLock)

#define ICCTriggerType_get_NumberOfActions(This,pNumberOfActions)	\
    (This)->lpVtbl -> get_NumberOfActions(This,pNumberOfActions)

#define ICCTriggerType_get_NumberOfExemptUsers(This,pNumberOfExemptUsers)	\
    (This)->lpVtbl -> get_NumberOfExemptUsers(This,pNumberOfExemptUsers)

#define ICCTriggerType_get_NumberOfInclusions(This,pNumberOfInclusions)	\
    (This)->lpVtbl -> get_NumberOfInclusions(This,pNumberOfInclusions)

#define ICCTriggerType_get_NumberOfOperationKinds(This,pNumberOfOperationKinds)	\
    (This)->lpVtbl -> get_NumberOfOperationKinds(This,pNumberOfOperationKinds)

#define ICCTriggerType_get_NumberOfRestrictions(This,pNumberOfRestrictions)	\
    (This)->lpVtbl -> get_NumberOfRestrictions(This,pNumberOfRestrictions)

#define ICCTriggerType_get_OperationKindsArray(This,pOperationKindsArray)	\
    (This)->lpVtbl -> get_OperationKindsArray(This,pOperationKindsArray)

#define ICCTriggerType_get_Owner(This,pOwner)	\
    (This)->lpVtbl -> get_Owner(This,pOwner)

#define ICCTriggerType_get_DebugPrinting(This,pDebugPrinting)	\
    (This)->lpVtbl -> get_DebugPrinting(This,pDebugPrinting)

#define ICCTriggerType_RemoveType(This,RemoveAllInstances,IgnorePreopTriggers,Comment)	\
    (This)->lpVtbl -> RemoveType(This,RemoveAllInstances,IgnorePreopTriggers,Comment)

#define ICCTriggerType_get_RestrictionsArray(This,pRestrictionsArray)	\
    (This)->lpVtbl -> get_RestrictionsArray(This,pRestrictionsArray)

#define ICCTriggerType_SetExemptUsersStringArray(This,ExemptUsersStringArray,Comment)	\
    (This)->lpVtbl -> SetExemptUsersStringArray(This,ExemptUsersStringArray,Comment)

#define ICCTriggerType_SetGroup(This,NewGroup,Comment)	\
    (This)->lpVtbl -> SetGroup(This,NewGroup,Comment)

#define ICCTriggerType_SetName(This,NewName,Comment)	\
    (This)->lpVtbl -> SetName(This,NewName,Comment)

#define ICCTriggerType_SetOwner(This,NewOwner,Comment)	\
    (This)->lpVtbl -> SetOwner(This,NewOwner,Comment)

#define ICCTriggerType_SetDebugPrinting(This,NewDebugPrinting,Comment)	\
    (This)->lpVtbl -> SetDebugPrinting(This,NewDebugPrinting,Comment)

#define ICCTriggerType_get_VOB(This,pVOB)	\
    (This)->lpVtbl -> get_VOB(This,pVOB)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerType_get_Name_Proxy( 
    ICCTriggerType __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pName);


void __RPC_STUB ICCTriggerType_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerType_get_ActionsArray_Proxy( 
    ICCTriggerType __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pActionsArray);


void __RPC_STUB ICCTriggerType_get_ActionsArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerType_Apply_Proxy( 
    ICCTriggerType __RPC_FAR * This,
    /* [in] */ ICCElement __RPC_FAR *pElement,
    /* [defaultvalue][optional][in] */ BSTR Comment,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Force,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse,
    /* [optional][in] */ VARIANT DirectoryListsSubset);


void __RPC_STUB ICCTriggerType_Apply_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerType_CreateBuilderFromType_Proxy( 
    ICCTriggerType __RPC_FAR * This,
    /* [retval][out] */ ICCTriggerTypeBuilder __RPC_FAR *__RPC_FAR *pTriggerTypeBuilder);


void __RPC_STUB ICCTriggerType_CreateBuilderFromType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerType_CreateLock_Proxy( 
    ICCTriggerType __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Comment,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
    /* [optional][in] */ VARIANT ExemptUsersStringArray);


void __RPC_STUB ICCTriggerType_CreateLock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerType_get_ExemptUsersStringArray_Proxy( 
    ICCTriggerType __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pExemptUsersStringArray);


void __RPC_STUB ICCTriggerType_get_ExemptUsersStringArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerType_get_Firing_Proxy( 
    ICCTriggerType __RPC_FAR * This,
    /* [retval][out] */ CCTriggerFiring __RPC_FAR *pFiring);


void __RPC_STUB ICCTriggerType_get_Firing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerType_get_Group_Proxy( 
    ICCTriggerType __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pGroup);


void __RPC_STUB ICCTriggerType_get_Group_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerType_get_InclusionsArray_Proxy( 
    ICCTriggerType __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pInclusionsArray);


void __RPC_STUB ICCTriggerType_get_InclusionsArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerType_get_KindOfTrigger_Proxy( 
    ICCTriggerType __RPC_FAR * This,
    /* [retval][out] */ CCKindOfTrigger __RPC_FAR *pKind);


void __RPC_STUB ICCTriggerType_get_KindOfTrigger_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerType_get_Lock_Proxy( 
    ICCTriggerType __RPC_FAR * This,
    /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock);


void __RPC_STUB ICCTriggerType_get_Lock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerType_get_NumberOfActions_Proxy( 
    ICCTriggerType __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pNumberOfActions);


void __RPC_STUB ICCTriggerType_get_NumberOfActions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerType_get_NumberOfExemptUsers_Proxy( 
    ICCTriggerType __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pNumberOfExemptUsers);


void __RPC_STUB ICCTriggerType_get_NumberOfExemptUsers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerType_get_NumberOfInclusions_Proxy( 
    ICCTriggerType __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pNumberOfInclusions);


void __RPC_STUB ICCTriggerType_get_NumberOfInclusions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerType_get_NumberOfOperationKinds_Proxy( 
    ICCTriggerType __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pNumberOfOperationKinds);


void __RPC_STUB ICCTriggerType_get_NumberOfOperationKinds_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerType_get_NumberOfRestrictions_Proxy( 
    ICCTriggerType __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pNumberOfRestrictions);


void __RPC_STUB ICCTriggerType_get_NumberOfRestrictions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerType_get_OperationKindsArray_Proxy( 
    ICCTriggerType __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pOperationKindsArray);


void __RPC_STUB ICCTriggerType_get_OperationKindsArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerType_get_Owner_Proxy( 
    ICCTriggerType __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pOwner);


void __RPC_STUB ICCTriggerType_get_Owner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerType_get_DebugPrinting_Proxy( 
    ICCTriggerType __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pDebugPrinting);


void __RPC_STUB ICCTriggerType_get_DebugPrinting_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerType_RemoveType_Proxy( 
    ICCTriggerType __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL RemoveAllInstances,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL IgnorePreopTriggers,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCTriggerType_RemoveType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerType_get_RestrictionsArray_Proxy( 
    ICCTriggerType __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pRestrictionsArray);


void __RPC_STUB ICCTriggerType_get_RestrictionsArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerType_SetExemptUsersStringArray_Proxy( 
    ICCTriggerType __RPC_FAR * This,
    /* [optional][in] */ VARIANT ExemptUsersStringArray,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCTriggerType_SetExemptUsersStringArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerType_SetGroup_Proxy( 
    ICCTriggerType __RPC_FAR * This,
    /* [in] */ BSTR NewGroup,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCTriggerType_SetGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerType_SetName_Proxy( 
    ICCTriggerType __RPC_FAR * This,
    /* [in] */ BSTR NewName,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCTriggerType_SetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerType_SetOwner_Proxy( 
    ICCTriggerType __RPC_FAR * This,
    /* [in] */ BSTR NewOwner,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCTriggerType_SetOwner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerType_SetDebugPrinting_Proxy( 
    ICCTriggerType __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL NewDebugPrinting,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCTriggerType_SetDebugPrinting_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerType_get_VOB_Proxy( 
    ICCTriggerType __RPC_FAR * This,
    /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);


void __RPC_STUB ICCTriggerType_get_VOB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCTriggerType_INTERFACE_DEFINED__ */


#ifndef __ICCTriggerTypeBuilder_INTERFACE_DEFINED__
#define __ICCTriggerTypeBuilder_INTERFACE_DEFINED__

/* interface ICCTriggerTypeBuilder */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCTriggerTypeBuilder,0xB22C7EF2,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7EF2-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCTriggerTypeBuilder : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pName) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR pName) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ActionsArray( 
            /* [retval][out] */ VARIANT __RPC_FAR *pActionsArray) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE AddExecAction( 
            /* [in] */ BSTR Action) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE AddExecUNIXAction( 
            /* [in] */ BSTR Action) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE AddExecWinAction( 
            /* [in] */ BSTR Action) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE AddMkattrAction( 
            /* [in] */ ICCAttributeType __RPC_FAR *pAttributeType,
            /* [in] */ VARIANT Value) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE AddMkhlinkFromAction( 
            /* [in] */ ICCHyperlinkType __RPC_FAR *pHyperlinkType,
            /* [in] */ BSTR FromPath) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE AddMkhlinkToAction( 
            /* [in] */ ICCHyperlinkType __RPC_FAR *pHyperlinkType,
            /* [in] */ BSTR ToPath) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE AddMklabelAction( 
            /* [in] */ ICCLabelType __RPC_FAR *pLabelType) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Create( 
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [retval][out] */ ICCTriggerType __RPC_FAR *__RPC_FAR *pTriggerType) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_DebugPrinting( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pDebugPrinting) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_DebugPrinting( 
            /* [in] */ VARIANT_BOOL pDebugPrinting) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ExemptUsersStringArray( 
            /* [retval][out] */ VARIANT __RPC_FAR *pExemptUsersStringArray) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_ExemptUsersStringArray( 
            /* [in] */ VARIANT pExemptUsersStringArray) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE FireOn( 
            /* [in] */ CCTriggerOperationKind OperationKind) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Firing( 
            /* [retval][out] */ CCTriggerFiring __RPC_FAR *pFiring) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Firing( 
            /* [in] */ CCTriggerFiring pFiring) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IncludeOn( 
            /* [in] */ VARIANT InclusionType) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_InclusionsArray( 
            /* [retval][out] */ VARIANT __RPC_FAR *pInclusionsArray) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_KindOfTrigger( 
            /* [retval][out] */ CCKindOfTrigger __RPC_FAR *pKind) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_KindOfTrigger( 
            /* [in] */ CCKindOfTrigger pKind) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_NumberOfActions( 
            /* [retval][out] */ long __RPC_FAR *pNumberOfActions) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_NumberOfExemptUsers( 
            /* [retval][out] */ long __RPC_FAR *pNumberOfExemptUsers) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_NumberOfInclusions( 
            /* [retval][out] */ long __RPC_FAR *pNumberOfInclusions) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_NumberOfOperationKinds( 
            /* [retval][out] */ long __RPC_FAR *pNumberOfOperationKinds) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_NumberOfRestrictions( 
            /* [retval][out] */ long __RPC_FAR *pNumberOfRestrictions) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_OperationKindsArray( 
            /* [retval][out] */ VARIANT __RPC_FAR *pOperationKindsArray) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAction( 
            /* [in] */ long index) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveInclusion( 
            /* [in] */ VARIANT InclusionType) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveOperationKind( 
            /* [in] */ CCTriggerOperationKind OperationKind) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveRestriction( 
            /* [in] */ VARIANT RestrictionType) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Replace( 
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [retval][out] */ ICCTriggerType __RPC_FAR *__RPC_FAR *pTriggerType) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE RestrictBy( 
            /* [in] */ VARIANT RestrictionType) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_RestrictionsArray( 
            /* [retval][out] */ VARIANT __RPC_FAR *pRestrictionsArray) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_VOB( 
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCTriggerTypeBuilderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCTriggerTypeBuilder __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCTriggerTypeBuilder __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pName);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [in] */ BSTR pName);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ActionsArray )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pActionsArray);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddExecAction )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [in] */ BSTR Action);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddExecUNIXAction )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [in] */ BSTR Action);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddExecWinAction )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [in] */ BSTR Action);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddMkattrAction )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [in] */ ICCAttributeType __RPC_FAR *pAttributeType,
            /* [in] */ VARIANT Value);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddMkhlinkFromAction )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [in] */ ICCHyperlinkType __RPC_FAR *pHyperlinkType,
            /* [in] */ BSTR FromPath);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddMkhlinkToAction )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [in] */ ICCHyperlinkType __RPC_FAR *pHyperlinkType,
            /* [in] */ BSTR ToPath);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddMklabelAction )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [in] */ ICCLabelType __RPC_FAR *pLabelType);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Create )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [retval][out] */ ICCTriggerType __RPC_FAR *__RPC_FAR *pTriggerType);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DebugPrinting )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pDebugPrinting);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DebugPrinting )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pDebugPrinting);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExemptUsersStringArray )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pExemptUsersStringArray);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ExemptUsersStringArray )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [in] */ VARIANT pExemptUsersStringArray);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FireOn )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [in] */ CCTriggerOperationKind OperationKind);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Firing )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [retval][out] */ CCTriggerFiring __RPC_FAR *pFiring);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Firing )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [in] */ CCTriggerFiring pFiring);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IncludeOn )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [in] */ VARIANT InclusionType);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InclusionsArray )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pInclusionsArray);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_KindOfTrigger )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [retval][out] */ CCKindOfTrigger __RPC_FAR *pKind);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KindOfTrigger )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [in] */ CCKindOfTrigger pKind);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumberOfActions )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pNumberOfActions);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumberOfExemptUsers )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pNumberOfExemptUsers);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumberOfInclusions )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pNumberOfInclusions);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumberOfOperationKinds )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pNumberOfOperationKinds);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumberOfRestrictions )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pNumberOfRestrictions);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OperationKindsArray )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pOperationKindsArray);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveAction )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [in] */ long index);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveInclusion )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [in] */ VARIANT InclusionType);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveOperationKind )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [in] */ CCTriggerOperationKind OperationKind);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveRestriction )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [in] */ VARIANT RestrictionType);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Replace )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [retval][out] */ ICCTriggerType __RPC_FAR *__RPC_FAR *pTriggerType);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RestrictBy )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [in] */ VARIANT RestrictionType);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RestrictionsArray )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pRestrictionsArray);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOB )( 
            ICCTriggerTypeBuilder __RPC_FAR * This,
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);
        
        END_INTERFACE
    } ICCTriggerTypeBuilderVtbl;

    interface ICCTriggerTypeBuilder
    {
        CONST_VTBL struct ICCTriggerTypeBuilderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCTriggerTypeBuilder_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCTriggerTypeBuilder_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCTriggerTypeBuilder_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCTriggerTypeBuilder_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCTriggerTypeBuilder_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCTriggerTypeBuilder_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCTriggerTypeBuilder_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCTriggerTypeBuilder_get_Name(This,pName)	\
    (This)->lpVtbl -> get_Name(This,pName)

#define ICCTriggerTypeBuilder_put_Name(This,pName)	\
    (This)->lpVtbl -> put_Name(This,pName)

#define ICCTriggerTypeBuilder_get_ActionsArray(This,pActionsArray)	\
    (This)->lpVtbl -> get_ActionsArray(This,pActionsArray)

#define ICCTriggerTypeBuilder_AddExecAction(This,Action)	\
    (This)->lpVtbl -> AddExecAction(This,Action)

#define ICCTriggerTypeBuilder_AddExecUNIXAction(This,Action)	\
    (This)->lpVtbl -> AddExecUNIXAction(This,Action)

#define ICCTriggerTypeBuilder_AddExecWinAction(This,Action)	\
    (This)->lpVtbl -> AddExecWinAction(This,Action)

#define ICCTriggerTypeBuilder_AddMkattrAction(This,pAttributeType,Value)	\
    (This)->lpVtbl -> AddMkattrAction(This,pAttributeType,Value)

#define ICCTriggerTypeBuilder_AddMkhlinkFromAction(This,pHyperlinkType,FromPath)	\
    (This)->lpVtbl -> AddMkhlinkFromAction(This,pHyperlinkType,FromPath)

#define ICCTriggerTypeBuilder_AddMkhlinkToAction(This,pHyperlinkType,ToPath)	\
    (This)->lpVtbl -> AddMkhlinkToAction(This,pHyperlinkType,ToPath)

#define ICCTriggerTypeBuilder_AddMklabelAction(This,pLabelType)	\
    (This)->lpVtbl -> AddMklabelAction(This,pLabelType)

#define ICCTriggerTypeBuilder_Create(This,Comment,pTriggerType)	\
    (This)->lpVtbl -> Create(This,Comment,pTriggerType)

#define ICCTriggerTypeBuilder_get_DebugPrinting(This,pDebugPrinting)	\
    (This)->lpVtbl -> get_DebugPrinting(This,pDebugPrinting)

#define ICCTriggerTypeBuilder_put_DebugPrinting(This,pDebugPrinting)	\
    (This)->lpVtbl -> put_DebugPrinting(This,pDebugPrinting)

#define ICCTriggerTypeBuilder_get_ExemptUsersStringArray(This,pExemptUsersStringArray)	\
    (This)->lpVtbl -> get_ExemptUsersStringArray(This,pExemptUsersStringArray)

#define ICCTriggerTypeBuilder_put_ExemptUsersStringArray(This,pExemptUsersStringArray)	\
    (This)->lpVtbl -> put_ExemptUsersStringArray(This,pExemptUsersStringArray)

#define ICCTriggerTypeBuilder_FireOn(This,OperationKind)	\
    (This)->lpVtbl -> FireOn(This,OperationKind)

#define ICCTriggerTypeBuilder_get_Firing(This,pFiring)	\
    (This)->lpVtbl -> get_Firing(This,pFiring)

#define ICCTriggerTypeBuilder_put_Firing(This,pFiring)	\
    (This)->lpVtbl -> put_Firing(This,pFiring)

#define ICCTriggerTypeBuilder_IncludeOn(This,InclusionType)	\
    (This)->lpVtbl -> IncludeOn(This,InclusionType)

#define ICCTriggerTypeBuilder_get_InclusionsArray(This,pInclusionsArray)	\
    (This)->lpVtbl -> get_InclusionsArray(This,pInclusionsArray)

#define ICCTriggerTypeBuilder_get_KindOfTrigger(This,pKind)	\
    (This)->lpVtbl -> get_KindOfTrigger(This,pKind)

#define ICCTriggerTypeBuilder_put_KindOfTrigger(This,pKind)	\
    (This)->lpVtbl -> put_KindOfTrigger(This,pKind)

#define ICCTriggerTypeBuilder_get_NumberOfActions(This,pNumberOfActions)	\
    (This)->lpVtbl -> get_NumberOfActions(This,pNumberOfActions)

#define ICCTriggerTypeBuilder_get_NumberOfExemptUsers(This,pNumberOfExemptUsers)	\
    (This)->lpVtbl -> get_NumberOfExemptUsers(This,pNumberOfExemptUsers)

#define ICCTriggerTypeBuilder_get_NumberOfInclusions(This,pNumberOfInclusions)	\
    (This)->lpVtbl -> get_NumberOfInclusions(This,pNumberOfInclusions)

#define ICCTriggerTypeBuilder_get_NumberOfOperationKinds(This,pNumberOfOperationKinds)	\
    (This)->lpVtbl -> get_NumberOfOperationKinds(This,pNumberOfOperationKinds)

#define ICCTriggerTypeBuilder_get_NumberOfRestrictions(This,pNumberOfRestrictions)	\
    (This)->lpVtbl -> get_NumberOfRestrictions(This,pNumberOfRestrictions)

#define ICCTriggerTypeBuilder_get_OperationKindsArray(This,pOperationKindsArray)	\
    (This)->lpVtbl -> get_OperationKindsArray(This,pOperationKindsArray)

#define ICCTriggerTypeBuilder_RemoveAction(This,index)	\
    (This)->lpVtbl -> RemoveAction(This,index)

#define ICCTriggerTypeBuilder_RemoveInclusion(This,InclusionType)	\
    (This)->lpVtbl -> RemoveInclusion(This,InclusionType)

#define ICCTriggerTypeBuilder_RemoveOperationKind(This,OperationKind)	\
    (This)->lpVtbl -> RemoveOperationKind(This,OperationKind)

#define ICCTriggerTypeBuilder_RemoveRestriction(This,RestrictionType)	\
    (This)->lpVtbl -> RemoveRestriction(This,RestrictionType)

#define ICCTriggerTypeBuilder_Replace(This,Comment,pTriggerType)	\
    (This)->lpVtbl -> Replace(This,Comment,pTriggerType)

#define ICCTriggerTypeBuilder_RestrictBy(This,RestrictionType)	\
    (This)->lpVtbl -> RestrictBy(This,RestrictionType)

#define ICCTriggerTypeBuilder_get_RestrictionsArray(This,pRestrictionsArray)	\
    (This)->lpVtbl -> get_RestrictionsArray(This,pRestrictionsArray)

#define ICCTriggerTypeBuilder_get_VOB(This,pVOB)	\
    (This)->lpVtbl -> get_VOB(This,pVOB)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_get_Name_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pName);


void __RPC_STUB ICCTriggerTypeBuilder_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_put_Name_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [in] */ BSTR pName);


void __RPC_STUB ICCTriggerTypeBuilder_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_get_ActionsArray_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pActionsArray);


void __RPC_STUB ICCTriggerTypeBuilder_get_ActionsArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_AddExecAction_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [in] */ BSTR Action);


void __RPC_STUB ICCTriggerTypeBuilder_AddExecAction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_AddExecUNIXAction_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [in] */ BSTR Action);


void __RPC_STUB ICCTriggerTypeBuilder_AddExecUNIXAction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_AddExecWinAction_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [in] */ BSTR Action);


void __RPC_STUB ICCTriggerTypeBuilder_AddExecWinAction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_AddMkattrAction_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [in] */ ICCAttributeType __RPC_FAR *pAttributeType,
    /* [in] */ VARIANT Value);


void __RPC_STUB ICCTriggerTypeBuilder_AddMkattrAction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_AddMkhlinkFromAction_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [in] */ ICCHyperlinkType __RPC_FAR *pHyperlinkType,
    /* [in] */ BSTR FromPath);


void __RPC_STUB ICCTriggerTypeBuilder_AddMkhlinkFromAction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_AddMkhlinkToAction_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [in] */ ICCHyperlinkType __RPC_FAR *pHyperlinkType,
    /* [in] */ BSTR ToPath);


void __RPC_STUB ICCTriggerTypeBuilder_AddMkhlinkToAction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_AddMklabelAction_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [in] */ ICCLabelType __RPC_FAR *pLabelType);


void __RPC_STUB ICCTriggerTypeBuilder_AddMklabelAction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_Create_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Comment,
    /* [retval][out] */ ICCTriggerType __RPC_FAR *__RPC_FAR *pTriggerType);


void __RPC_STUB ICCTriggerTypeBuilder_Create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_get_DebugPrinting_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pDebugPrinting);


void __RPC_STUB ICCTriggerTypeBuilder_get_DebugPrinting_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_put_DebugPrinting_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL pDebugPrinting);


void __RPC_STUB ICCTriggerTypeBuilder_put_DebugPrinting_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_get_ExemptUsersStringArray_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pExemptUsersStringArray);


void __RPC_STUB ICCTriggerTypeBuilder_get_ExemptUsersStringArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_put_ExemptUsersStringArray_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [in] */ VARIANT pExemptUsersStringArray);


void __RPC_STUB ICCTriggerTypeBuilder_put_ExemptUsersStringArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_FireOn_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [in] */ CCTriggerOperationKind OperationKind);


void __RPC_STUB ICCTriggerTypeBuilder_FireOn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_get_Firing_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [retval][out] */ CCTriggerFiring __RPC_FAR *pFiring);


void __RPC_STUB ICCTriggerTypeBuilder_get_Firing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_put_Firing_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [in] */ CCTriggerFiring pFiring);


void __RPC_STUB ICCTriggerTypeBuilder_put_Firing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_IncludeOn_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [in] */ VARIANT InclusionType);


void __RPC_STUB ICCTriggerTypeBuilder_IncludeOn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_get_InclusionsArray_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pInclusionsArray);


void __RPC_STUB ICCTriggerTypeBuilder_get_InclusionsArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_get_KindOfTrigger_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [retval][out] */ CCKindOfTrigger __RPC_FAR *pKind);


void __RPC_STUB ICCTriggerTypeBuilder_get_KindOfTrigger_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_put_KindOfTrigger_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [in] */ CCKindOfTrigger pKind);


void __RPC_STUB ICCTriggerTypeBuilder_put_KindOfTrigger_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_get_NumberOfActions_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pNumberOfActions);


void __RPC_STUB ICCTriggerTypeBuilder_get_NumberOfActions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_get_NumberOfExemptUsers_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pNumberOfExemptUsers);


void __RPC_STUB ICCTriggerTypeBuilder_get_NumberOfExemptUsers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_get_NumberOfInclusions_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pNumberOfInclusions);


void __RPC_STUB ICCTriggerTypeBuilder_get_NumberOfInclusions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_get_NumberOfOperationKinds_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pNumberOfOperationKinds);


void __RPC_STUB ICCTriggerTypeBuilder_get_NumberOfOperationKinds_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_get_NumberOfRestrictions_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pNumberOfRestrictions);


void __RPC_STUB ICCTriggerTypeBuilder_get_NumberOfRestrictions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_get_OperationKindsArray_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pOperationKindsArray);


void __RPC_STUB ICCTriggerTypeBuilder_get_OperationKindsArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_RemoveAction_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [in] */ long index);


void __RPC_STUB ICCTriggerTypeBuilder_RemoveAction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_RemoveInclusion_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [in] */ VARIANT InclusionType);


void __RPC_STUB ICCTriggerTypeBuilder_RemoveInclusion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_RemoveOperationKind_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [in] */ CCTriggerOperationKind OperationKind);


void __RPC_STUB ICCTriggerTypeBuilder_RemoveOperationKind_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_RemoveRestriction_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [in] */ VARIANT RestrictionType);


void __RPC_STUB ICCTriggerTypeBuilder_RemoveRestriction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_Replace_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Comment,
    /* [retval][out] */ ICCTriggerType __RPC_FAR *__RPC_FAR *pTriggerType);


void __RPC_STUB ICCTriggerTypeBuilder_Replace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_RestrictBy_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [in] */ VARIANT RestrictionType);


void __RPC_STUB ICCTriggerTypeBuilder_RestrictBy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_get_RestrictionsArray_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pRestrictionsArray);


void __RPC_STUB ICCTriggerTypeBuilder_get_RestrictionsArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypeBuilder_get_VOB_Proxy( 
    ICCTriggerTypeBuilder __RPC_FAR * This,
    /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);


void __RPC_STUB ICCTriggerTypeBuilder_get_VOB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCTriggerTypeBuilder_INTERFACE_DEFINED__ */


#ifndef __ICCHyperlinkType_INTERFACE_DEFINED__
#define __ICCHyperlinkType_INTERFACE_DEFINED__

/* interface ICCHyperlinkType */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCHyperlinkType,0xB22C7EDF,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7EDF-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCHyperlinkType : public ICCVOBObject
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pName) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Apply( 
            /* [in] */ ICCVOBObject __RPC_FAR *pFromObject,
            /* [in] */ BSTR FromText,
            /* [in] */ ICCVOBObject __RPC_FAR *pToObject,
            /* [defaultvalue][optional][in] */ BSTR ToText = L"",
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Unidirectional = 0,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateLock( 
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
            /* [optional][in] */ VARIANT ExemptUsersStringArray) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Group( 
            /* [retval][out] */ BSTR __RPC_FAR *pGroup) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_HasSharedMastership( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pHasShared) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Lock( 
            /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Master( 
            /* [retval][out] */ BSTR __RPC_FAR *pReplica) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Owner( 
            /* [retval][out] */ BSTR __RPC_FAR *pOwner) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveType( 
            /* [defaultvalue][optional][in] */ VARIANT_BOOL RemoveAllInstances = 0,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Scope( 
            /* [retval][out] */ CCTypeScope __RPC_FAR *pScope) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetGroup( 
            /* [in] */ BSTR NewGroup,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMaster( 
            /* [in] */ BSTR Replica,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetName( 
            /* [in] */ BSTR NewName,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetOwner( 
            /* [in] */ BSTR NewOwner,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetScope( 
            /* [in] */ VARIANT_BOOL Global,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Acquire = 0,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ShareMastership( 
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_VOB( 
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB) = 0;
        
        virtual /* [helpstring][hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get__AttributeTypesObjectArray( 
            /* [retval][out] */ VARIANT __RPC_FAR *pAttributeTypesObjectArray) = 0;
        
        virtual /* [helpstring][hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get__NumberOfAttributeTypes( 
            /* [retval][out] */ long __RPC_FAR *pNumberOfAttributeTypes) = 0;
        
        virtual /* [helpstring][hidden][id] */ HRESULT STDMETHODCALLTYPE _SetAttributeTypesObjectArray( 
            /* [optional][in] */ VARIANT AttributeTypesObjectArray,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCHyperlinkTypeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCHyperlinkType __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCHyperlinkType __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attribute )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [in] */ BSTR AttributeType,
            /* [retval][out] */ ICCAttribute __RPC_FAR *__RPC_FAR *pAttribute);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attributes )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [retval][out] */ ICCAttributes __RPC_FAR *__RPC_FAR *pAttributes);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Comment )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pComment);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Comment )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [in] */ BSTR pComment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreationRecord )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [retval][out] */ ICCHistoryRecord __RPC_FAR *__RPC_FAR *pHistoryRecord);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HistoryRecords )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [in] */ ICCBranchType __RPC_FAR *pICCBranchType,
            /* [defaultvalue][optional][in] */ DATE Since,
            /* [defaultvalue][optional][in] */ BSTR User,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Minor,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL ExcludeCheckOutEvents,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL DirectoryOnly,
            /* [retval][out] */ ICCHistoryRecords __RPC_FAR *__RPC_FAR *pHistoryRecords);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hyperlinks )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR HyperlinkType,
            /* [retval][out] */ ICCHyperlinks __RPC_FAR *__RPC_FAR *pHyperlinks);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OID )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOBFamilyUUID )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVOBFamilyUUID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Apply )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [in] */ ICCVOBObject __RPC_FAR *pFromObject,
            /* [in] */ BSTR FromText,
            /* [in] */ ICCVOBObject __RPC_FAR *pToObject,
            /* [defaultvalue][optional][in] */ BSTR ToText,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Unidirectional,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateLock )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
            /* [optional][in] */ VARIANT ExemptUsersStringArray);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Group )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pGroup);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HasSharedMastership )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pHasShared);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Lock )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Master )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pReplica);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Owner )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOwner);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveType )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL RemoveAllInstances,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Scope )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [retval][out] */ CCTypeScope __RPC_FAR *pScope);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGroup )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [in] */ BSTR NewGroup,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMaster )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [in] */ BSTR Replica,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetName )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [in] */ BSTR NewName,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOwner )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [in] */ BSTR NewOwner,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetScope )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Global,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Acquire,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShareMastership )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOB )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);
        
        /* [helpstring][hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__AttributeTypesObjectArray )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pAttributeTypesObjectArray);
        
        /* [helpstring][hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NumberOfAttributeTypes )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pNumberOfAttributeTypes);
        
        /* [helpstring][hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_SetAttributeTypesObjectArray )( 
            ICCHyperlinkType __RPC_FAR * This,
            /* [optional][in] */ VARIANT AttributeTypesObjectArray,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        END_INTERFACE
    } ICCHyperlinkTypeVtbl;

    interface ICCHyperlinkType
    {
        CONST_VTBL struct ICCHyperlinkTypeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCHyperlinkType_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCHyperlinkType_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCHyperlinkType_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCHyperlinkType_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCHyperlinkType_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCHyperlinkType_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCHyperlinkType_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCHyperlinkType_get_Attribute(This,AttributeType,pAttribute)	\
    (This)->lpVtbl -> get_Attribute(This,AttributeType,pAttribute)

#define ICCHyperlinkType_get_Attributes(This,pAttributes)	\
    (This)->lpVtbl -> get_Attributes(This,pAttributes)

#define ICCHyperlinkType_get_Comment(This,pComment)	\
    (This)->lpVtbl -> get_Comment(This,pComment)

#define ICCHyperlinkType_put_Comment(This,pComment)	\
    (This)->lpVtbl -> put_Comment(This,pComment)

#define ICCHyperlinkType_get_CreationRecord(This,pHistoryRecord)	\
    (This)->lpVtbl -> get_CreationRecord(This,pHistoryRecord)

#define ICCHyperlinkType_get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)	\
    (This)->lpVtbl -> get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)

#define ICCHyperlinkType_get_Hyperlinks(This,HyperlinkType,pHyperlinks)	\
    (This)->lpVtbl -> get_Hyperlinks(This,HyperlinkType,pHyperlinks)

#define ICCHyperlinkType_get_OID(This,pOID)	\
    (This)->lpVtbl -> get_OID(This,pOID)

#define ICCHyperlinkType_get_VOBFamilyUUID(This,pVOBFamilyUUID)	\
    (This)->lpVtbl -> get_VOBFamilyUUID(This,pVOBFamilyUUID)


#define ICCHyperlinkType_get_Name(This,pName)	\
    (This)->lpVtbl -> get_Name(This,pName)

#define ICCHyperlinkType_Apply(This,pFromObject,FromText,pToObject,ToText,Unidirectional,Comment)	\
    (This)->lpVtbl -> Apply(This,pFromObject,FromText,pToObject,ToText,Unidirectional,Comment)

#define ICCHyperlinkType_CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)	\
    (This)->lpVtbl -> CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)

#define ICCHyperlinkType_get_Group(This,pGroup)	\
    (This)->lpVtbl -> get_Group(This,pGroup)

#define ICCHyperlinkType_get_HasSharedMastership(This,pHasShared)	\
    (This)->lpVtbl -> get_HasSharedMastership(This,pHasShared)

#define ICCHyperlinkType_get_Lock(This,pLock)	\
    (This)->lpVtbl -> get_Lock(This,pLock)

#define ICCHyperlinkType_get_Master(This,pReplica)	\
    (This)->lpVtbl -> get_Master(This,pReplica)

#define ICCHyperlinkType_get_Owner(This,pOwner)	\
    (This)->lpVtbl -> get_Owner(This,pOwner)

#define ICCHyperlinkType_RemoveType(This,RemoveAllInstances,Comment)	\
    (This)->lpVtbl -> RemoveType(This,RemoveAllInstances,Comment)

#define ICCHyperlinkType_get_Scope(This,pScope)	\
    (This)->lpVtbl -> get_Scope(This,pScope)

#define ICCHyperlinkType_SetGroup(This,NewGroup,Comment)	\
    (This)->lpVtbl -> SetGroup(This,NewGroup,Comment)

#define ICCHyperlinkType_SetMaster(This,Replica,Comment)	\
    (This)->lpVtbl -> SetMaster(This,Replica,Comment)

#define ICCHyperlinkType_SetName(This,NewName,Comment)	\
    (This)->lpVtbl -> SetName(This,NewName,Comment)

#define ICCHyperlinkType_SetOwner(This,NewOwner,Comment)	\
    (This)->lpVtbl -> SetOwner(This,NewOwner,Comment)

#define ICCHyperlinkType_SetScope(This,Global,Acquire,Comment)	\
    (This)->lpVtbl -> SetScope(This,Global,Acquire,Comment)

#define ICCHyperlinkType_ShareMastership(This,Comment)	\
    (This)->lpVtbl -> ShareMastership(This,Comment)

#define ICCHyperlinkType_get_VOB(This,pVOB)	\
    (This)->lpVtbl -> get_VOB(This,pVOB)

#define ICCHyperlinkType_get__AttributeTypesObjectArray(This,pAttributeTypesObjectArray)	\
    (This)->lpVtbl -> get__AttributeTypesObjectArray(This,pAttributeTypesObjectArray)

#define ICCHyperlinkType_get__NumberOfAttributeTypes(This,pNumberOfAttributeTypes)	\
    (This)->lpVtbl -> get__NumberOfAttributeTypes(This,pNumberOfAttributeTypes)

#define ICCHyperlinkType__SetAttributeTypesObjectArray(This,AttributeTypesObjectArray,Comment)	\
    (This)->lpVtbl -> _SetAttributeTypesObjectArray(This,AttributeTypesObjectArray,Comment)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlinkType_get_Name_Proxy( 
    ICCHyperlinkType __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pName);


void __RPC_STUB ICCHyperlinkType_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlinkType_Apply_Proxy( 
    ICCHyperlinkType __RPC_FAR * This,
    /* [in] */ ICCVOBObject __RPC_FAR *pFromObject,
    /* [in] */ BSTR FromText,
    /* [in] */ ICCVOBObject __RPC_FAR *pToObject,
    /* [defaultvalue][optional][in] */ BSTR ToText,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Unidirectional,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCHyperlinkType_Apply_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlinkType_CreateLock_Proxy( 
    ICCHyperlinkType __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Comment,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
    /* [optional][in] */ VARIANT ExemptUsersStringArray);


void __RPC_STUB ICCHyperlinkType_CreateLock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlinkType_get_Group_Proxy( 
    ICCHyperlinkType __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pGroup);


void __RPC_STUB ICCHyperlinkType_get_Group_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlinkType_get_HasSharedMastership_Proxy( 
    ICCHyperlinkType __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pHasShared);


void __RPC_STUB ICCHyperlinkType_get_HasSharedMastership_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlinkType_get_Lock_Proxy( 
    ICCHyperlinkType __RPC_FAR * This,
    /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock);


void __RPC_STUB ICCHyperlinkType_get_Lock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlinkType_get_Master_Proxy( 
    ICCHyperlinkType __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pReplica);


void __RPC_STUB ICCHyperlinkType_get_Master_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlinkType_get_Owner_Proxy( 
    ICCHyperlinkType __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pOwner);


void __RPC_STUB ICCHyperlinkType_get_Owner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlinkType_RemoveType_Proxy( 
    ICCHyperlinkType __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL RemoveAllInstances,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCHyperlinkType_RemoveType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlinkType_get_Scope_Proxy( 
    ICCHyperlinkType __RPC_FAR * This,
    /* [retval][out] */ CCTypeScope __RPC_FAR *pScope);


void __RPC_STUB ICCHyperlinkType_get_Scope_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlinkType_SetGroup_Proxy( 
    ICCHyperlinkType __RPC_FAR * This,
    /* [in] */ BSTR NewGroup,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCHyperlinkType_SetGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlinkType_SetMaster_Proxy( 
    ICCHyperlinkType __RPC_FAR * This,
    /* [in] */ BSTR Replica,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCHyperlinkType_SetMaster_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlinkType_SetName_Proxy( 
    ICCHyperlinkType __RPC_FAR * This,
    /* [in] */ BSTR NewName,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCHyperlinkType_SetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlinkType_SetOwner_Proxy( 
    ICCHyperlinkType __RPC_FAR * This,
    /* [in] */ BSTR NewOwner,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCHyperlinkType_SetOwner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlinkType_SetScope_Proxy( 
    ICCHyperlinkType __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Global,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Acquire,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCHyperlinkType_SetScope_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlinkType_ShareMastership_Proxy( 
    ICCHyperlinkType __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCHyperlinkType_ShareMastership_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlinkType_get_VOB_Proxy( 
    ICCHyperlinkType __RPC_FAR * This,
    /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);


void __RPC_STUB ICCHyperlinkType_get_VOB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][hidden][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlinkType_get__AttributeTypesObjectArray_Proxy( 
    ICCHyperlinkType __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pAttributeTypesObjectArray);


void __RPC_STUB ICCHyperlinkType_get__AttributeTypesObjectArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][hidden][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlinkType_get__NumberOfAttributeTypes_Proxy( 
    ICCHyperlinkType __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pNumberOfAttributeTypes);


void __RPC_STUB ICCHyperlinkType_get__NumberOfAttributeTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][hidden][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlinkType__SetAttributeTypesObjectArray_Proxy( 
    ICCHyperlinkType __RPC_FAR * This,
    /* [optional][in] */ VARIANT AttributeTypesObjectArray,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCHyperlinkType__SetAttributeTypesObjectArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCHyperlinkType_INTERFACE_DEFINED__ */


#ifndef __ICCLabelType_INTERFACE_DEFINED__
#define __ICCLabelType_INTERFACE_DEFINED__

/* interface ICCLabelType */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCLabelType,0xB22C7EE3,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7EE3-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCLabelType : public ICCVOBObject
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pName) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Apply( 
            /* [in] */ ICCVersion __RPC_FAR *pVersion,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"",
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Replace = 0,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse = 0) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Constraint( 
            /* [retval][out] */ CCTypeConstraint __RPC_FAR *pConstraint) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateLock( 
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
            /* [optional][in] */ VARIANT ExemptUsersStringArray) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Group( 
            /* [retval][out] */ BSTR __RPC_FAR *pGroup) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_HasSharedMastership( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pHasShared) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Lock( 
            /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Master( 
            /* [retval][out] */ BSTR __RPC_FAR *pReplica) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Owner( 
            /* [retval][out] */ BSTR __RPC_FAR *pOwner) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveType( 
            /* [defaultvalue][optional][in] */ VARIANT_BOOL RemoveAllInstances = 0,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Scope( 
            /* [retval][out] */ CCTypeScope __RPC_FAR *pScope) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetConstraint( 
            /* [in] */ CCTypeConstraint NewConstraint,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetGroup( 
            /* [in] */ BSTR NewGroup,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMaster( 
            /* [in] */ BSTR Replica,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetName( 
            /* [in] */ BSTR NewName,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetOwner( 
            /* [in] */ BSTR NewOwner,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetScope( 
            /* [in] */ VARIANT_BOOL Global,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Acquire = 0,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ShareMastership( 
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_VOB( 
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCLabelTypeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCLabelType __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCLabelType __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCLabelType __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCLabelType __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCLabelType __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCLabelType __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCLabelType __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attribute )( 
            ICCLabelType __RPC_FAR * This,
            /* [in] */ BSTR AttributeType,
            /* [retval][out] */ ICCAttribute __RPC_FAR *__RPC_FAR *pAttribute);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attributes )( 
            ICCLabelType __RPC_FAR * This,
            /* [retval][out] */ ICCAttributes __RPC_FAR *__RPC_FAR *pAttributes);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Comment )( 
            ICCLabelType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pComment);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Comment )( 
            ICCLabelType __RPC_FAR * This,
            /* [in] */ BSTR pComment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreationRecord )( 
            ICCLabelType __RPC_FAR * This,
            /* [retval][out] */ ICCHistoryRecord __RPC_FAR *__RPC_FAR *pHistoryRecord);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HistoryRecords )( 
            ICCLabelType __RPC_FAR * This,
            /* [in] */ ICCBranchType __RPC_FAR *pICCBranchType,
            /* [defaultvalue][optional][in] */ DATE Since,
            /* [defaultvalue][optional][in] */ BSTR User,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Minor,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL ExcludeCheckOutEvents,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL DirectoryOnly,
            /* [retval][out] */ ICCHistoryRecords __RPC_FAR *__RPC_FAR *pHistoryRecords);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hyperlinks )( 
            ICCLabelType __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR HyperlinkType,
            /* [retval][out] */ ICCHyperlinks __RPC_FAR *__RPC_FAR *pHyperlinks);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OID )( 
            ICCLabelType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOBFamilyUUID )( 
            ICCLabelType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVOBFamilyUUID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ICCLabelType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Apply )( 
            ICCLabelType __RPC_FAR * This,
            /* [in] */ ICCVersion __RPC_FAR *pVersion,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Replace,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Constraint )( 
            ICCLabelType __RPC_FAR * This,
            /* [retval][out] */ CCTypeConstraint __RPC_FAR *pConstraint);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateLock )( 
            ICCLabelType __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
            /* [optional][in] */ VARIANT ExemptUsersStringArray);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Group )( 
            ICCLabelType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pGroup);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HasSharedMastership )( 
            ICCLabelType __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pHasShared);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Lock )( 
            ICCLabelType __RPC_FAR * This,
            /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Master )( 
            ICCLabelType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pReplica);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Owner )( 
            ICCLabelType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOwner);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveType )( 
            ICCLabelType __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL RemoveAllInstances,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Scope )( 
            ICCLabelType __RPC_FAR * This,
            /* [retval][out] */ CCTypeScope __RPC_FAR *pScope);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConstraint )( 
            ICCLabelType __RPC_FAR * This,
            /* [in] */ CCTypeConstraint NewConstraint,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGroup )( 
            ICCLabelType __RPC_FAR * This,
            /* [in] */ BSTR NewGroup,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMaster )( 
            ICCLabelType __RPC_FAR * This,
            /* [in] */ BSTR Replica,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetName )( 
            ICCLabelType __RPC_FAR * This,
            /* [in] */ BSTR NewName,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOwner )( 
            ICCLabelType __RPC_FAR * This,
            /* [in] */ BSTR NewOwner,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetScope )( 
            ICCLabelType __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Global,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Acquire,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShareMastership )( 
            ICCLabelType __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOB )( 
            ICCLabelType __RPC_FAR * This,
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);
        
        END_INTERFACE
    } ICCLabelTypeVtbl;

    interface ICCLabelType
    {
        CONST_VTBL struct ICCLabelTypeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCLabelType_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCLabelType_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCLabelType_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCLabelType_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCLabelType_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCLabelType_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCLabelType_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCLabelType_get_Attribute(This,AttributeType,pAttribute)	\
    (This)->lpVtbl -> get_Attribute(This,AttributeType,pAttribute)

#define ICCLabelType_get_Attributes(This,pAttributes)	\
    (This)->lpVtbl -> get_Attributes(This,pAttributes)

#define ICCLabelType_get_Comment(This,pComment)	\
    (This)->lpVtbl -> get_Comment(This,pComment)

#define ICCLabelType_put_Comment(This,pComment)	\
    (This)->lpVtbl -> put_Comment(This,pComment)

#define ICCLabelType_get_CreationRecord(This,pHistoryRecord)	\
    (This)->lpVtbl -> get_CreationRecord(This,pHistoryRecord)

#define ICCLabelType_get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)	\
    (This)->lpVtbl -> get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)

#define ICCLabelType_get_Hyperlinks(This,HyperlinkType,pHyperlinks)	\
    (This)->lpVtbl -> get_Hyperlinks(This,HyperlinkType,pHyperlinks)

#define ICCLabelType_get_OID(This,pOID)	\
    (This)->lpVtbl -> get_OID(This,pOID)

#define ICCLabelType_get_VOBFamilyUUID(This,pVOBFamilyUUID)	\
    (This)->lpVtbl -> get_VOBFamilyUUID(This,pVOBFamilyUUID)


#define ICCLabelType_get_Name(This,pName)	\
    (This)->lpVtbl -> get_Name(This,pName)

#define ICCLabelType_Apply(This,pVersion,Comment,Replace,Recurse)	\
    (This)->lpVtbl -> Apply(This,pVersion,Comment,Replace,Recurse)

#define ICCLabelType_get_Constraint(This,pConstraint)	\
    (This)->lpVtbl -> get_Constraint(This,pConstraint)

#define ICCLabelType_CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)	\
    (This)->lpVtbl -> CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)

#define ICCLabelType_get_Group(This,pGroup)	\
    (This)->lpVtbl -> get_Group(This,pGroup)

#define ICCLabelType_get_HasSharedMastership(This,pHasShared)	\
    (This)->lpVtbl -> get_HasSharedMastership(This,pHasShared)

#define ICCLabelType_get_Lock(This,pLock)	\
    (This)->lpVtbl -> get_Lock(This,pLock)

#define ICCLabelType_get_Master(This,pReplica)	\
    (This)->lpVtbl -> get_Master(This,pReplica)

#define ICCLabelType_get_Owner(This,pOwner)	\
    (This)->lpVtbl -> get_Owner(This,pOwner)

#define ICCLabelType_RemoveType(This,RemoveAllInstances,Comment)	\
    (This)->lpVtbl -> RemoveType(This,RemoveAllInstances,Comment)

#define ICCLabelType_get_Scope(This,pScope)	\
    (This)->lpVtbl -> get_Scope(This,pScope)

#define ICCLabelType_SetConstraint(This,NewConstraint,Comment)	\
    (This)->lpVtbl -> SetConstraint(This,NewConstraint,Comment)

#define ICCLabelType_SetGroup(This,NewGroup,Comment)	\
    (This)->lpVtbl -> SetGroup(This,NewGroup,Comment)

#define ICCLabelType_SetMaster(This,Replica,Comment)	\
    (This)->lpVtbl -> SetMaster(This,Replica,Comment)

#define ICCLabelType_SetName(This,NewName,Comment)	\
    (This)->lpVtbl -> SetName(This,NewName,Comment)

#define ICCLabelType_SetOwner(This,NewOwner,Comment)	\
    (This)->lpVtbl -> SetOwner(This,NewOwner,Comment)

#define ICCLabelType_SetScope(This,Global,Acquire,Comment)	\
    (This)->lpVtbl -> SetScope(This,Global,Acquire,Comment)

#define ICCLabelType_ShareMastership(This,Comment)	\
    (This)->lpVtbl -> ShareMastership(This,Comment)

#define ICCLabelType_get_VOB(This,pVOB)	\
    (This)->lpVtbl -> get_VOB(This,pVOB)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCLabelType_get_Name_Proxy( 
    ICCLabelType __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pName);


void __RPC_STUB ICCLabelType_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCLabelType_Apply_Proxy( 
    ICCLabelType __RPC_FAR * This,
    /* [in] */ ICCVersion __RPC_FAR *pVersion,
    /* [defaultvalue][optional][in] */ BSTR Comment,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Replace,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse);


void __RPC_STUB ICCLabelType_Apply_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCLabelType_get_Constraint_Proxy( 
    ICCLabelType __RPC_FAR * This,
    /* [retval][out] */ CCTypeConstraint __RPC_FAR *pConstraint);


void __RPC_STUB ICCLabelType_get_Constraint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCLabelType_CreateLock_Proxy( 
    ICCLabelType __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Comment,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
    /* [optional][in] */ VARIANT ExemptUsersStringArray);


void __RPC_STUB ICCLabelType_CreateLock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCLabelType_get_Group_Proxy( 
    ICCLabelType __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pGroup);


void __RPC_STUB ICCLabelType_get_Group_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCLabelType_get_HasSharedMastership_Proxy( 
    ICCLabelType __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pHasShared);


void __RPC_STUB ICCLabelType_get_HasSharedMastership_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCLabelType_get_Lock_Proxy( 
    ICCLabelType __RPC_FAR * This,
    /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock);


void __RPC_STUB ICCLabelType_get_Lock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCLabelType_get_Master_Proxy( 
    ICCLabelType __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pReplica);


void __RPC_STUB ICCLabelType_get_Master_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCLabelType_get_Owner_Proxy( 
    ICCLabelType __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pOwner);


void __RPC_STUB ICCLabelType_get_Owner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCLabelType_RemoveType_Proxy( 
    ICCLabelType __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL RemoveAllInstances,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCLabelType_RemoveType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCLabelType_get_Scope_Proxy( 
    ICCLabelType __RPC_FAR * This,
    /* [retval][out] */ CCTypeScope __RPC_FAR *pScope);


void __RPC_STUB ICCLabelType_get_Scope_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCLabelType_SetConstraint_Proxy( 
    ICCLabelType __RPC_FAR * This,
    /* [in] */ CCTypeConstraint NewConstraint,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCLabelType_SetConstraint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCLabelType_SetGroup_Proxy( 
    ICCLabelType __RPC_FAR * This,
    /* [in] */ BSTR NewGroup,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCLabelType_SetGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCLabelType_SetMaster_Proxy( 
    ICCLabelType __RPC_FAR * This,
    /* [in] */ BSTR Replica,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCLabelType_SetMaster_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCLabelType_SetName_Proxy( 
    ICCLabelType __RPC_FAR * This,
    /* [in] */ BSTR NewName,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCLabelType_SetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCLabelType_SetOwner_Proxy( 
    ICCLabelType __RPC_FAR * This,
    /* [in] */ BSTR NewOwner,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCLabelType_SetOwner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCLabelType_SetScope_Proxy( 
    ICCLabelType __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Global,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Acquire,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCLabelType_SetScope_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCLabelType_ShareMastership_Proxy( 
    ICCLabelType __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCLabelType_ShareMastership_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCLabelType_get_VOB_Proxy( 
    ICCLabelType __RPC_FAR * This,
    /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);


void __RPC_STUB ICCLabelType_get_VOB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCLabelType_INTERFACE_DEFINED__ */


#ifndef __ICCTriggers_INTERFACE_DEFINED__
#define __ICCTriggers_INTERFACE_DEFINED__

/* interface ICCTriggers */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCTriggers,0xB22C7EF6,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7EF6-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCTriggers : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long index,
            /* [retval][out] */ ICCTrigger __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ICCTrigger __RPC_FAR *pTrigger) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long index) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCTriggersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCTriggers __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCTriggers __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCTriggers __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCTriggers __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCTriggers __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCTriggers __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCTriggers __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ICCTriggers __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ ICCTrigger __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            ICCTriggers __RPC_FAR * This,
            /* [in] */ ICCTrigger __RPC_FAR *pTrigger);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ICCTriggers __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ICCTriggers __RPC_FAR * This,
            /* [in] */ long index);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ICCTriggers __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);
        
        END_INTERFACE
    } ICCTriggersVtbl;

    interface ICCTriggers
    {
        CONST_VTBL struct ICCTriggersVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCTriggers_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCTriggers_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCTriggers_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCTriggers_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCTriggers_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCTriggers_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCTriggers_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCTriggers_get_Item(This,index,pItem)	\
    (This)->lpVtbl -> get_Item(This,index,pItem)

#define ICCTriggers_Add(This,pTrigger)	\
    (This)->lpVtbl -> Add(This,pTrigger)

#define ICCTriggers_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define ICCTriggers_Remove(This,index)	\
    (This)->lpVtbl -> Remove(This,index)

#define ICCTriggers_get__NewEnum(This,pEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,pEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggers_get_Item_Proxy( 
    ICCTriggers __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ ICCTrigger __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB ICCTriggers_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCTriggers_Add_Proxy( 
    ICCTriggers __RPC_FAR * This,
    /* [in] */ ICCTrigger __RPC_FAR *pTrigger);


void __RPC_STUB ICCTriggers_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggers_get_Count_Proxy( 
    ICCTriggers __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB ICCTriggers_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCTriggers_Remove_Proxy( 
    ICCTriggers __RPC_FAR * This,
    /* [in] */ long index);


void __RPC_STUB ICCTriggers_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggers_get__NewEnum_Proxy( 
    ICCTriggers __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);


void __RPC_STUB ICCTriggers_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCTriggers_INTERFACE_DEFINED__ */


#ifndef __ICCStreams_INTERFACE_DEFINED__
#define __ICCStreams_INTERFACE_DEFINED__

/* interface ICCStreams */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCStreams,0xB22C7F45,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7F45-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCStreams : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long index,
            /* [retval][out] */ ICCStream __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ICCStream __RPC_FAR *pStream) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long index) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_InitErrors( 
            /* [retval][out] */ BSTR __RPC_FAR *pInitErrors) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCStreamsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCStreams __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCStreams __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCStreams __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCStreams __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCStreams __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCStreams __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCStreams __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ICCStreams __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ ICCStream __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            ICCStreams __RPC_FAR * This,
            /* [in] */ ICCStream __RPC_FAR *pStream);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ICCStreams __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ICCStreams __RPC_FAR * This,
            /* [in] */ long index);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InitErrors )( 
            ICCStreams __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pInitErrors);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ICCStreams __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);
        
        END_INTERFACE
    } ICCStreamsVtbl;

    interface ICCStreams
    {
        CONST_VTBL struct ICCStreamsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCStreams_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCStreams_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCStreams_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCStreams_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCStreams_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCStreams_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCStreams_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCStreams_get_Item(This,index,pItem)	\
    (This)->lpVtbl -> get_Item(This,index,pItem)

#define ICCStreams_Add(This,pStream)	\
    (This)->lpVtbl -> Add(This,pStream)

#define ICCStreams_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define ICCStreams_Remove(This,index)	\
    (This)->lpVtbl -> Remove(This,index)

#define ICCStreams_get_InitErrors(This,pInitErrors)	\
    (This)->lpVtbl -> get_InitErrors(This,pInitErrors)

#define ICCStreams_get__NewEnum(This,pEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,pEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCStreams_get_Item_Proxy( 
    ICCStreams __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ ICCStream __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB ICCStreams_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCStreams_Add_Proxy( 
    ICCStreams __RPC_FAR * This,
    /* [in] */ ICCStream __RPC_FAR *pStream);


void __RPC_STUB ICCStreams_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCStreams_get_Count_Proxy( 
    ICCStreams __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB ICCStreams_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCStreams_Remove_Proxy( 
    ICCStreams __RPC_FAR * This,
    /* [in] */ long index);


void __RPC_STUB ICCStreams_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCStreams_get_InitErrors_Proxy( 
    ICCStreams __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pInitErrors);


void __RPC_STUB ICCStreams_get_InitErrors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICCStreams_get__NewEnum_Proxy( 
    ICCStreams __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);


void __RPC_STUB ICCStreams_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCStreams_INTERFACE_DEFINED__ */


#ifndef __ICCComponents_INTERFACE_DEFINED__
#define __ICCComponents_INTERFACE_DEFINED__

/* interface ICCComponents */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCComponents,0xB22C7F43,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7F43-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCComponents : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long index,
            /* [retval][out] */ ICCComponent __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ICCComponent __RPC_FAR *pComponent) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long index) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_InitErrors( 
            /* [retval][out] */ BSTR __RPC_FAR *pInitErrors) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCComponentsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCComponents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCComponents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCComponents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCComponents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCComponents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCComponents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCComponents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ICCComponents __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ ICCComponent __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            ICCComponents __RPC_FAR * This,
            /* [in] */ ICCComponent __RPC_FAR *pComponent);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ICCComponents __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ICCComponents __RPC_FAR * This,
            /* [in] */ long index);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InitErrors )( 
            ICCComponents __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pInitErrors);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ICCComponents __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);
        
        END_INTERFACE
    } ICCComponentsVtbl;

    interface ICCComponents
    {
        CONST_VTBL struct ICCComponentsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCComponents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCComponents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCComponents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCComponents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCComponents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCComponents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCComponents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCComponents_get_Item(This,index,pItem)	\
    (This)->lpVtbl -> get_Item(This,index,pItem)

#define ICCComponents_Add(This,pComponent)	\
    (This)->lpVtbl -> Add(This,pComponent)

#define ICCComponents_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define ICCComponents_Remove(This,index)	\
    (This)->lpVtbl -> Remove(This,index)

#define ICCComponents_get_InitErrors(This,pInitErrors)	\
    (This)->lpVtbl -> get_InitErrors(This,pInitErrors)

#define ICCComponents_get__NewEnum(This,pEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,pEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCComponents_get_Item_Proxy( 
    ICCComponents __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ ICCComponent __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB ICCComponents_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCComponents_Add_Proxy( 
    ICCComponents __RPC_FAR * This,
    /* [in] */ ICCComponent __RPC_FAR *pComponent);


void __RPC_STUB ICCComponents_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCComponents_get_Count_Proxy( 
    ICCComponents __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB ICCComponents_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCComponents_Remove_Proxy( 
    ICCComponents __RPC_FAR * This,
    /* [in] */ long index);


void __RPC_STUB ICCComponents_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCComponents_get_InitErrors_Proxy( 
    ICCComponents __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pInitErrors);


void __RPC_STUB ICCComponents_get_InitErrors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICCComponents_get__NewEnum_Proxy( 
    ICCComponents __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);


void __RPC_STUB ICCComponents_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCComponents_INTERFACE_DEFINED__ */


#ifndef __ICCFolder_INTERFACE_DEFINED__
#define __ICCFolder_INTERFACE_DEFINED__

/* interface ICCFolder */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCFolder,0xB22C7F2A,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7F2A-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCFolder : public ICCUCMObject
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IsRootFolder( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsRootFolder) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ParentFolder( 
            /* [retval][out] */ ICCFolder __RPC_FAR *__RPC_FAR *pParentFolder) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Projects( 
            /* [retval][out] */ ICCProjects __RPC_FAR *__RPC_FAR *pProjects) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SubFolders( 
            /* [retval][out] */ ICCFolders __RPC_FAR *__RPC_FAR *pSubFolders) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCFolderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCFolder __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCFolder __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCFolder __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCFolder __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCFolder __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCFolder __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCFolder __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attribute )( 
            ICCFolder __RPC_FAR * This,
            /* [in] */ BSTR AttributeType,
            /* [retval][out] */ ICCAttribute __RPC_FAR *__RPC_FAR *pAttribute);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attributes )( 
            ICCFolder __RPC_FAR * This,
            /* [retval][out] */ ICCAttributes __RPC_FAR *__RPC_FAR *pAttributes);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Comment )( 
            ICCFolder __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pComment);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Comment )( 
            ICCFolder __RPC_FAR * This,
            /* [in] */ BSTR pComment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreationRecord )( 
            ICCFolder __RPC_FAR * This,
            /* [retval][out] */ ICCHistoryRecord __RPC_FAR *__RPC_FAR *pHistoryRecord);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HistoryRecords )( 
            ICCFolder __RPC_FAR * This,
            /* [in] */ ICCBranchType __RPC_FAR *pICCBranchType,
            /* [defaultvalue][optional][in] */ DATE Since,
            /* [defaultvalue][optional][in] */ BSTR User,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Minor,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL ExcludeCheckOutEvents,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL DirectoryOnly,
            /* [retval][out] */ ICCHistoryRecords __RPC_FAR *__RPC_FAR *pHistoryRecords);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hyperlinks )( 
            ICCFolder __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR HyperlinkType,
            /* [retval][out] */ ICCHyperlinks __RPC_FAR *__RPC_FAR *pHyperlinks);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OID )( 
            ICCFolder __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOBFamilyUUID )( 
            ICCFolder __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVOBFamilyUUID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ICCFolder __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateLock )( 
            ICCFolder __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
            /* [optional][in] */ VARIANT ExemptUsersStringArray);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Group )( 
            ICCFolder __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pGroup);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Lock )( 
            ICCFolder __RPC_FAR * This,
            /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Master )( 
            ICCFolder __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pReplica);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Owner )( 
            ICCFolder __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOwner);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProjectVOB )( 
            ICCFolder __RPC_FAR * This,
            /* [retval][out] */ ICCProjectVOB __RPC_FAR *__RPC_FAR *pProjectVOB);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGroup )( 
            ICCFolder __RPC_FAR * This,
            /* [in] */ BSTR NewGroup,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMaster )( 
            ICCFolder __RPC_FAR * This,
            /* [in] */ BSTR Replica,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOwner )( 
            ICCFolder __RPC_FAR * This,
            /* [in] */ BSTR NewOwner,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Title )( 
            ICCFolder __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pTitle);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsRootFolder )( 
            ICCFolder __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsRootFolder);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ParentFolder )( 
            ICCFolder __RPC_FAR * This,
            /* [retval][out] */ ICCFolder __RPC_FAR *__RPC_FAR *pParentFolder);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Projects )( 
            ICCFolder __RPC_FAR * This,
            /* [retval][out] */ ICCProjects __RPC_FAR *__RPC_FAR *pProjects);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SubFolders )( 
            ICCFolder __RPC_FAR * This,
            /* [retval][out] */ ICCFolders __RPC_FAR *__RPC_FAR *pSubFolders);
        
        END_INTERFACE
    } ICCFolderVtbl;

    interface ICCFolder
    {
        CONST_VTBL struct ICCFolderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCFolder_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCFolder_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCFolder_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCFolder_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCFolder_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCFolder_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCFolder_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCFolder_get_Attribute(This,AttributeType,pAttribute)	\
    (This)->lpVtbl -> get_Attribute(This,AttributeType,pAttribute)

#define ICCFolder_get_Attributes(This,pAttributes)	\
    (This)->lpVtbl -> get_Attributes(This,pAttributes)

#define ICCFolder_get_Comment(This,pComment)	\
    (This)->lpVtbl -> get_Comment(This,pComment)

#define ICCFolder_put_Comment(This,pComment)	\
    (This)->lpVtbl -> put_Comment(This,pComment)

#define ICCFolder_get_CreationRecord(This,pHistoryRecord)	\
    (This)->lpVtbl -> get_CreationRecord(This,pHistoryRecord)

#define ICCFolder_get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)	\
    (This)->lpVtbl -> get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)

#define ICCFolder_get_Hyperlinks(This,HyperlinkType,pHyperlinks)	\
    (This)->lpVtbl -> get_Hyperlinks(This,HyperlinkType,pHyperlinks)

#define ICCFolder_get_OID(This,pOID)	\
    (This)->lpVtbl -> get_OID(This,pOID)

#define ICCFolder_get_VOBFamilyUUID(This,pVOBFamilyUUID)	\
    (This)->lpVtbl -> get_VOBFamilyUUID(This,pVOBFamilyUUID)


#define ICCFolder_get_Name(This,pName)	\
    (This)->lpVtbl -> get_Name(This,pName)

#define ICCFolder_CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)	\
    (This)->lpVtbl -> CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)

#define ICCFolder_get_Group(This,pGroup)	\
    (This)->lpVtbl -> get_Group(This,pGroup)

#define ICCFolder_get_Lock(This,pLock)	\
    (This)->lpVtbl -> get_Lock(This,pLock)

#define ICCFolder_get_Master(This,pReplica)	\
    (This)->lpVtbl -> get_Master(This,pReplica)

#define ICCFolder_get_Owner(This,pOwner)	\
    (This)->lpVtbl -> get_Owner(This,pOwner)

#define ICCFolder_get_ProjectVOB(This,pProjectVOB)	\
    (This)->lpVtbl -> get_ProjectVOB(This,pProjectVOB)

#define ICCFolder_SetGroup(This,NewGroup,Comment)	\
    (This)->lpVtbl -> SetGroup(This,NewGroup,Comment)

#define ICCFolder_SetMaster(This,Replica,Comment)	\
    (This)->lpVtbl -> SetMaster(This,Replica,Comment)

#define ICCFolder_SetOwner(This,NewOwner,Comment)	\
    (This)->lpVtbl -> SetOwner(This,NewOwner,Comment)

#define ICCFolder_get_Title(This,pTitle)	\
    (This)->lpVtbl -> get_Title(This,pTitle)


#define ICCFolder_get_IsRootFolder(This,pIsRootFolder)	\
    (This)->lpVtbl -> get_IsRootFolder(This,pIsRootFolder)

#define ICCFolder_get_ParentFolder(This,pParentFolder)	\
    (This)->lpVtbl -> get_ParentFolder(This,pParentFolder)

#define ICCFolder_get_Projects(This,pProjects)	\
    (This)->lpVtbl -> get_Projects(This,pProjects)

#define ICCFolder_get_SubFolders(This,pSubFolders)	\
    (This)->lpVtbl -> get_SubFolders(This,pSubFolders)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCFolder_get_IsRootFolder_Proxy( 
    ICCFolder __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsRootFolder);


void __RPC_STUB ICCFolder_get_IsRootFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCFolder_get_ParentFolder_Proxy( 
    ICCFolder __RPC_FAR * This,
    /* [retval][out] */ ICCFolder __RPC_FAR *__RPC_FAR *pParentFolder);


void __RPC_STUB ICCFolder_get_ParentFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCFolder_get_Projects_Proxy( 
    ICCFolder __RPC_FAR * This,
    /* [retval][out] */ ICCProjects __RPC_FAR *__RPC_FAR *pProjects);


void __RPC_STUB ICCFolder_get_Projects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCFolder_get_SubFolders_Proxy( 
    ICCFolder __RPC_FAR * This,
    /* [retval][out] */ ICCFolders __RPC_FAR *__RPC_FAR *pSubFolders);


void __RPC_STUB ICCFolder_get_SubFolders_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCFolder_INTERFACE_DEFINED__ */


#ifndef __ICCProjects_INTERFACE_DEFINED__
#define __ICCProjects_INTERFACE_DEFINED__

/* interface ICCProjects */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCProjects,0xB22C7F41,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7F41-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCProjects : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long index,
            /* [retval][out] */ ICCProject __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ICCProject __RPC_FAR *pProject) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long index) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_InitErrors( 
            /* [retval][out] */ BSTR __RPC_FAR *pInitErrors) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCProjectsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCProjects __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCProjects __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCProjects __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCProjects __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCProjects __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCProjects __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCProjects __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ICCProjects __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ ICCProject __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            ICCProjects __RPC_FAR * This,
            /* [in] */ ICCProject __RPC_FAR *pProject);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ICCProjects __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ICCProjects __RPC_FAR * This,
            /* [in] */ long index);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InitErrors )( 
            ICCProjects __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pInitErrors);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ICCProjects __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);
        
        END_INTERFACE
    } ICCProjectsVtbl;

    interface ICCProjects
    {
        CONST_VTBL struct ICCProjectsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCProjects_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCProjects_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCProjects_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCProjects_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCProjects_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCProjects_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCProjects_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCProjects_get_Item(This,index,pItem)	\
    (This)->lpVtbl -> get_Item(This,index,pItem)

#define ICCProjects_Add(This,pProject)	\
    (This)->lpVtbl -> Add(This,pProject)

#define ICCProjects_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define ICCProjects_Remove(This,index)	\
    (This)->lpVtbl -> Remove(This,index)

#define ICCProjects_get_InitErrors(This,pInitErrors)	\
    (This)->lpVtbl -> get_InitErrors(This,pInitErrors)

#define ICCProjects_get__NewEnum(This,pEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,pEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProjects_get_Item_Proxy( 
    ICCProjects __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ ICCProject __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB ICCProjects_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCProjects_Add_Proxy( 
    ICCProjects __RPC_FAR * This,
    /* [in] */ ICCProject __RPC_FAR *pProject);


void __RPC_STUB ICCProjects_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProjects_get_Count_Proxy( 
    ICCProjects __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB ICCProjects_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCProjects_Remove_Proxy( 
    ICCProjects __RPC_FAR * This,
    /* [in] */ long index);


void __RPC_STUB ICCProjects_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProjects_get_InitErrors_Proxy( 
    ICCProjects __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pInitErrors);


void __RPC_STUB ICCProjects_get_InitErrors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICCProjects_get__NewEnum_Proxy( 
    ICCProjects __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);


void __RPC_STUB ICCProjects_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCProjects_INTERFACE_DEFINED__ */


#ifndef __ICCProject_INTERFACE_DEFINED__
#define __ICCProject_INTERFACE_DEFINED__

/* interface ICCProject */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCProject,0xB22C7F29,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7F29-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCProject : public ICCUCMObject
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ClearQuestDatabaseName( 
            /* [retval][out] */ BSTR __RPC_FAR *pDatabaseName) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_DevelopmentStreams( 
            /* [defaultvalue][optional][in] */ BSTR Owner,
            /* [retval][out] */ ICCStreams __RPC_FAR *__RPC_FAR *pDevelopmentStreams) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_HasStreams( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pHasStreams) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IntegrationStream( 
            /* [retval][out] */ ICCStream __RPC_FAR *__RPC_FAR *pIntegrationStream) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IsCRMEnabled( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsCRMEnabled) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ModifiableComponents( 
            /* [retval][out] */ ICCComponents __RPC_FAR *__RPC_FAR *pComponents) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ParentFolder( 
            /* [retval][out] */ ICCFolder __RPC_FAR *__RPC_FAR *pParentFolder) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Policy( 
            /* [retval][out] */ ICCProjectPolicy __RPC_FAR *__RPC_FAR *pPolicy) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_RecommendedBaselines( 
            /* [retval][out] */ ICCBaselines __RPC_FAR *__RPC_FAR *pBaselines) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_RequiredPromotionLevel( 
            /* [retval][out] */ BSTR __RPC_FAR *pRequiredPromotionLevel) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Streams( 
            /* [defaultvalue][optional][in] */ BSTR Owner,
            /* [retval][out] */ ICCStreams __RPC_FAR *__RPC_FAR *pStreams) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCProjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCProject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCProject __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCProject __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCProject __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCProject __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCProject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCProject __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attribute )( 
            ICCProject __RPC_FAR * This,
            /* [in] */ BSTR AttributeType,
            /* [retval][out] */ ICCAttribute __RPC_FAR *__RPC_FAR *pAttribute);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attributes )( 
            ICCProject __RPC_FAR * This,
            /* [retval][out] */ ICCAttributes __RPC_FAR *__RPC_FAR *pAttributes);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Comment )( 
            ICCProject __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pComment);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Comment )( 
            ICCProject __RPC_FAR * This,
            /* [in] */ BSTR pComment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreationRecord )( 
            ICCProject __RPC_FAR * This,
            /* [retval][out] */ ICCHistoryRecord __RPC_FAR *__RPC_FAR *pHistoryRecord);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HistoryRecords )( 
            ICCProject __RPC_FAR * This,
            /* [in] */ ICCBranchType __RPC_FAR *pICCBranchType,
            /* [defaultvalue][optional][in] */ DATE Since,
            /* [defaultvalue][optional][in] */ BSTR User,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Minor,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL ExcludeCheckOutEvents,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL DirectoryOnly,
            /* [retval][out] */ ICCHistoryRecords __RPC_FAR *__RPC_FAR *pHistoryRecords);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hyperlinks )( 
            ICCProject __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR HyperlinkType,
            /* [retval][out] */ ICCHyperlinks __RPC_FAR *__RPC_FAR *pHyperlinks);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OID )( 
            ICCProject __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOBFamilyUUID )( 
            ICCProject __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVOBFamilyUUID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ICCProject __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateLock )( 
            ICCProject __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
            /* [optional][in] */ VARIANT ExemptUsersStringArray);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Group )( 
            ICCProject __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pGroup);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Lock )( 
            ICCProject __RPC_FAR * This,
            /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Master )( 
            ICCProject __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pReplica);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Owner )( 
            ICCProject __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOwner);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProjectVOB )( 
            ICCProject __RPC_FAR * This,
            /* [retval][out] */ ICCProjectVOB __RPC_FAR *__RPC_FAR *pProjectVOB);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGroup )( 
            ICCProject __RPC_FAR * This,
            /* [in] */ BSTR NewGroup,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMaster )( 
            ICCProject __RPC_FAR * This,
            /* [in] */ BSTR Replica,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOwner )( 
            ICCProject __RPC_FAR * This,
            /* [in] */ BSTR NewOwner,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Title )( 
            ICCProject __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pTitle);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClearQuestDatabaseName )( 
            ICCProject __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pDatabaseName);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DevelopmentStreams )( 
            ICCProject __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Owner,
            /* [retval][out] */ ICCStreams __RPC_FAR *__RPC_FAR *pDevelopmentStreams);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HasStreams )( 
            ICCProject __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pHasStreams);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IntegrationStream )( 
            ICCProject __RPC_FAR * This,
            /* [retval][out] */ ICCStream __RPC_FAR *__RPC_FAR *pIntegrationStream);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsCRMEnabled )( 
            ICCProject __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsCRMEnabled);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ModifiableComponents )( 
            ICCProject __RPC_FAR * This,
            /* [retval][out] */ ICCComponents __RPC_FAR *__RPC_FAR *pComponents);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ParentFolder )( 
            ICCProject __RPC_FAR * This,
            /* [retval][out] */ ICCFolder __RPC_FAR *__RPC_FAR *pParentFolder);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Policy )( 
            ICCProject __RPC_FAR * This,
            /* [retval][out] */ ICCProjectPolicy __RPC_FAR *__RPC_FAR *pPolicy);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RecommendedBaselines )( 
            ICCProject __RPC_FAR * This,
            /* [retval][out] */ ICCBaselines __RPC_FAR *__RPC_FAR *pBaselines);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RequiredPromotionLevel )( 
            ICCProject __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pRequiredPromotionLevel);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Streams )( 
            ICCProject __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Owner,
            /* [retval][out] */ ICCStreams __RPC_FAR *__RPC_FAR *pStreams);
        
        END_INTERFACE
    } ICCProjectVtbl;

    interface ICCProject
    {
        CONST_VTBL struct ICCProjectVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCProject_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCProject_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCProject_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCProject_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCProject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCProject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCProject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCProject_get_Attribute(This,AttributeType,pAttribute)	\
    (This)->lpVtbl -> get_Attribute(This,AttributeType,pAttribute)

#define ICCProject_get_Attributes(This,pAttributes)	\
    (This)->lpVtbl -> get_Attributes(This,pAttributes)

#define ICCProject_get_Comment(This,pComment)	\
    (This)->lpVtbl -> get_Comment(This,pComment)

#define ICCProject_put_Comment(This,pComment)	\
    (This)->lpVtbl -> put_Comment(This,pComment)

#define ICCProject_get_CreationRecord(This,pHistoryRecord)	\
    (This)->lpVtbl -> get_CreationRecord(This,pHistoryRecord)

#define ICCProject_get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)	\
    (This)->lpVtbl -> get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)

#define ICCProject_get_Hyperlinks(This,HyperlinkType,pHyperlinks)	\
    (This)->lpVtbl -> get_Hyperlinks(This,HyperlinkType,pHyperlinks)

#define ICCProject_get_OID(This,pOID)	\
    (This)->lpVtbl -> get_OID(This,pOID)

#define ICCProject_get_VOBFamilyUUID(This,pVOBFamilyUUID)	\
    (This)->lpVtbl -> get_VOBFamilyUUID(This,pVOBFamilyUUID)


#define ICCProject_get_Name(This,pName)	\
    (This)->lpVtbl -> get_Name(This,pName)

#define ICCProject_CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)	\
    (This)->lpVtbl -> CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)

#define ICCProject_get_Group(This,pGroup)	\
    (This)->lpVtbl -> get_Group(This,pGroup)

#define ICCProject_get_Lock(This,pLock)	\
    (This)->lpVtbl -> get_Lock(This,pLock)

#define ICCProject_get_Master(This,pReplica)	\
    (This)->lpVtbl -> get_Master(This,pReplica)

#define ICCProject_get_Owner(This,pOwner)	\
    (This)->lpVtbl -> get_Owner(This,pOwner)

#define ICCProject_get_ProjectVOB(This,pProjectVOB)	\
    (This)->lpVtbl -> get_ProjectVOB(This,pProjectVOB)

#define ICCProject_SetGroup(This,NewGroup,Comment)	\
    (This)->lpVtbl -> SetGroup(This,NewGroup,Comment)

#define ICCProject_SetMaster(This,Replica,Comment)	\
    (This)->lpVtbl -> SetMaster(This,Replica,Comment)

#define ICCProject_SetOwner(This,NewOwner,Comment)	\
    (This)->lpVtbl -> SetOwner(This,NewOwner,Comment)

#define ICCProject_get_Title(This,pTitle)	\
    (This)->lpVtbl -> get_Title(This,pTitle)


#define ICCProject_get_ClearQuestDatabaseName(This,pDatabaseName)	\
    (This)->lpVtbl -> get_ClearQuestDatabaseName(This,pDatabaseName)

#define ICCProject_get_DevelopmentStreams(This,Owner,pDevelopmentStreams)	\
    (This)->lpVtbl -> get_DevelopmentStreams(This,Owner,pDevelopmentStreams)

#define ICCProject_get_HasStreams(This,pHasStreams)	\
    (This)->lpVtbl -> get_HasStreams(This,pHasStreams)

#define ICCProject_get_IntegrationStream(This,pIntegrationStream)	\
    (This)->lpVtbl -> get_IntegrationStream(This,pIntegrationStream)

#define ICCProject_get_IsCRMEnabled(This,pIsCRMEnabled)	\
    (This)->lpVtbl -> get_IsCRMEnabled(This,pIsCRMEnabled)

#define ICCProject_get_ModifiableComponents(This,pComponents)	\
    (This)->lpVtbl -> get_ModifiableComponents(This,pComponents)

#define ICCProject_get_ParentFolder(This,pParentFolder)	\
    (This)->lpVtbl -> get_ParentFolder(This,pParentFolder)

#define ICCProject_get_Policy(This,pPolicy)	\
    (This)->lpVtbl -> get_Policy(This,pPolicy)

#define ICCProject_get_RecommendedBaselines(This,pBaselines)	\
    (This)->lpVtbl -> get_RecommendedBaselines(This,pBaselines)

#define ICCProject_get_RequiredPromotionLevel(This,pRequiredPromotionLevel)	\
    (This)->lpVtbl -> get_RequiredPromotionLevel(This,pRequiredPromotionLevel)

#define ICCProject_get_Streams(This,Owner,pStreams)	\
    (This)->lpVtbl -> get_Streams(This,Owner,pStreams)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProject_get_ClearQuestDatabaseName_Proxy( 
    ICCProject __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pDatabaseName);


void __RPC_STUB ICCProject_get_ClearQuestDatabaseName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProject_get_DevelopmentStreams_Proxy( 
    ICCProject __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Owner,
    /* [retval][out] */ ICCStreams __RPC_FAR *__RPC_FAR *pDevelopmentStreams);


void __RPC_STUB ICCProject_get_DevelopmentStreams_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProject_get_HasStreams_Proxy( 
    ICCProject __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pHasStreams);


void __RPC_STUB ICCProject_get_HasStreams_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProject_get_IntegrationStream_Proxy( 
    ICCProject __RPC_FAR * This,
    /* [retval][out] */ ICCStream __RPC_FAR *__RPC_FAR *pIntegrationStream);


void __RPC_STUB ICCProject_get_IntegrationStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProject_get_IsCRMEnabled_Proxy( 
    ICCProject __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pIsCRMEnabled);


void __RPC_STUB ICCProject_get_IsCRMEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProject_get_ModifiableComponents_Proxy( 
    ICCProject __RPC_FAR * This,
    /* [retval][out] */ ICCComponents __RPC_FAR *__RPC_FAR *pComponents);


void __RPC_STUB ICCProject_get_ModifiableComponents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProject_get_ParentFolder_Proxy( 
    ICCProject __RPC_FAR * This,
    /* [retval][out] */ ICCFolder __RPC_FAR *__RPC_FAR *pParentFolder);


void __RPC_STUB ICCProject_get_ParentFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProject_get_Policy_Proxy( 
    ICCProject __RPC_FAR * This,
    /* [retval][out] */ ICCProjectPolicy __RPC_FAR *__RPC_FAR *pPolicy);


void __RPC_STUB ICCProject_get_Policy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProject_get_RecommendedBaselines_Proxy( 
    ICCProject __RPC_FAR * This,
    /* [retval][out] */ ICCBaselines __RPC_FAR *__RPC_FAR *pBaselines);


void __RPC_STUB ICCProject_get_RecommendedBaselines_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProject_get_RequiredPromotionLevel_Proxy( 
    ICCProject __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pRequiredPromotionLevel);


void __RPC_STUB ICCProject_get_RequiredPromotionLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProject_get_Streams_Proxy( 
    ICCProject __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Owner,
    /* [retval][out] */ ICCStreams __RPC_FAR *__RPC_FAR *pStreams);


void __RPC_STUB ICCProject_get_Streams_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCProject_INTERFACE_DEFINED__ */


#ifndef __ICCProjectPolicy_INTERFACE_DEFINED__
#define __ICCProjectPolicy_INTERFACE_DEFINED__

/* interface ICCProjectPolicy */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCProjectPolicy,0xB22C7F28,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7F28-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCProjectPolicy : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_DeliverRequireCheckin( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pDeliverRequireCheckin) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_DeliverRequireCheckin( 
            /* [in] */ VARIANT_BOOL pDeliverRequireCheckin) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_DeliverRequireRebase( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pDeliverRequireRebase) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_DeliverRequireRebase( 
            /* [in] */ VARIANT_BOOL pDeliverRequireRebase) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_UNIXDevelopmentSnapshot( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pUNIXDevelopmentSnapshot) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_UNIXDevelopmentSnapshot( 
            /* [in] */ VARIANT_BOOL pUNIXDevelopmentSnapshot) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_UNIXIntegrationSnapshot( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pUNIXIntegrationSnapshot) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_UNIXIntegrationSnapshot( 
            /* [in] */ VARIANT_BOOL pUNIXIntegrationSnapshot) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_WinDevelopmentSnapshot( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pWinDevelopmentSnapshot) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_WinDevelopmentSnapshot( 
            /* [in] */ VARIANT_BOOL pWinDevelopmentSnapshot) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_WinIntegrationSnapshot( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pWinIntegrationSnapshot) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_WinIntegrationSnapshot( 
            /* [in] */ VARIANT_BOOL pWinIntegrationSnapshot) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCProjectPolicyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCProjectPolicy __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCProjectPolicy __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCProjectPolicy __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCProjectPolicy __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCProjectPolicy __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCProjectPolicy __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCProjectPolicy __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DeliverRequireCheckin )( 
            ICCProjectPolicy __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pDeliverRequireCheckin);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DeliverRequireCheckin )( 
            ICCProjectPolicy __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pDeliverRequireCheckin);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DeliverRequireRebase )( 
            ICCProjectPolicy __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pDeliverRequireRebase);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DeliverRequireRebase )( 
            ICCProjectPolicy __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pDeliverRequireRebase);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UNIXDevelopmentSnapshot )( 
            ICCProjectPolicy __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pUNIXDevelopmentSnapshot);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UNIXDevelopmentSnapshot )( 
            ICCProjectPolicy __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pUNIXDevelopmentSnapshot);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UNIXIntegrationSnapshot )( 
            ICCProjectPolicy __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pUNIXIntegrationSnapshot);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UNIXIntegrationSnapshot )( 
            ICCProjectPolicy __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pUNIXIntegrationSnapshot);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WinDevelopmentSnapshot )( 
            ICCProjectPolicy __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pWinDevelopmentSnapshot);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WinDevelopmentSnapshot )( 
            ICCProjectPolicy __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pWinDevelopmentSnapshot);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WinIntegrationSnapshot )( 
            ICCProjectPolicy __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pWinIntegrationSnapshot);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WinIntegrationSnapshot )( 
            ICCProjectPolicy __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pWinIntegrationSnapshot);
        
        END_INTERFACE
    } ICCProjectPolicyVtbl;

    interface ICCProjectPolicy
    {
        CONST_VTBL struct ICCProjectPolicyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCProjectPolicy_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCProjectPolicy_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCProjectPolicy_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCProjectPolicy_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCProjectPolicy_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCProjectPolicy_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCProjectPolicy_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCProjectPolicy_get_DeliverRequireCheckin(This,pDeliverRequireCheckin)	\
    (This)->lpVtbl -> get_DeliverRequireCheckin(This,pDeliverRequireCheckin)

#define ICCProjectPolicy_put_DeliverRequireCheckin(This,pDeliverRequireCheckin)	\
    (This)->lpVtbl -> put_DeliverRequireCheckin(This,pDeliverRequireCheckin)

#define ICCProjectPolicy_get_DeliverRequireRebase(This,pDeliverRequireRebase)	\
    (This)->lpVtbl -> get_DeliverRequireRebase(This,pDeliverRequireRebase)

#define ICCProjectPolicy_put_DeliverRequireRebase(This,pDeliverRequireRebase)	\
    (This)->lpVtbl -> put_DeliverRequireRebase(This,pDeliverRequireRebase)

#define ICCProjectPolicy_get_UNIXDevelopmentSnapshot(This,pUNIXDevelopmentSnapshot)	\
    (This)->lpVtbl -> get_UNIXDevelopmentSnapshot(This,pUNIXDevelopmentSnapshot)

#define ICCProjectPolicy_put_UNIXDevelopmentSnapshot(This,pUNIXDevelopmentSnapshot)	\
    (This)->lpVtbl -> put_UNIXDevelopmentSnapshot(This,pUNIXDevelopmentSnapshot)

#define ICCProjectPolicy_get_UNIXIntegrationSnapshot(This,pUNIXIntegrationSnapshot)	\
    (This)->lpVtbl -> get_UNIXIntegrationSnapshot(This,pUNIXIntegrationSnapshot)

#define ICCProjectPolicy_put_UNIXIntegrationSnapshot(This,pUNIXIntegrationSnapshot)	\
    (This)->lpVtbl -> put_UNIXIntegrationSnapshot(This,pUNIXIntegrationSnapshot)

#define ICCProjectPolicy_get_WinDevelopmentSnapshot(This,pWinDevelopmentSnapshot)	\
    (This)->lpVtbl -> get_WinDevelopmentSnapshot(This,pWinDevelopmentSnapshot)

#define ICCProjectPolicy_put_WinDevelopmentSnapshot(This,pWinDevelopmentSnapshot)	\
    (This)->lpVtbl -> put_WinDevelopmentSnapshot(This,pWinDevelopmentSnapshot)

#define ICCProjectPolicy_get_WinIntegrationSnapshot(This,pWinIntegrationSnapshot)	\
    (This)->lpVtbl -> get_WinIntegrationSnapshot(This,pWinIntegrationSnapshot)

#define ICCProjectPolicy_put_WinIntegrationSnapshot(This,pWinIntegrationSnapshot)	\
    (This)->lpVtbl -> put_WinIntegrationSnapshot(This,pWinIntegrationSnapshot)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProjectPolicy_get_DeliverRequireCheckin_Proxy( 
    ICCProjectPolicy __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pDeliverRequireCheckin);


void __RPC_STUB ICCProjectPolicy_get_DeliverRequireCheckin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE ICCProjectPolicy_put_DeliverRequireCheckin_Proxy( 
    ICCProjectPolicy __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL pDeliverRequireCheckin);


void __RPC_STUB ICCProjectPolicy_put_DeliverRequireCheckin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProjectPolicy_get_DeliverRequireRebase_Proxy( 
    ICCProjectPolicy __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pDeliverRequireRebase);


void __RPC_STUB ICCProjectPolicy_get_DeliverRequireRebase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE ICCProjectPolicy_put_DeliverRequireRebase_Proxy( 
    ICCProjectPolicy __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL pDeliverRequireRebase);


void __RPC_STUB ICCProjectPolicy_put_DeliverRequireRebase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProjectPolicy_get_UNIXDevelopmentSnapshot_Proxy( 
    ICCProjectPolicy __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pUNIXDevelopmentSnapshot);


void __RPC_STUB ICCProjectPolicy_get_UNIXDevelopmentSnapshot_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE ICCProjectPolicy_put_UNIXDevelopmentSnapshot_Proxy( 
    ICCProjectPolicy __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL pUNIXDevelopmentSnapshot);


void __RPC_STUB ICCProjectPolicy_put_UNIXDevelopmentSnapshot_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProjectPolicy_get_UNIXIntegrationSnapshot_Proxy( 
    ICCProjectPolicy __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pUNIXIntegrationSnapshot);


void __RPC_STUB ICCProjectPolicy_get_UNIXIntegrationSnapshot_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE ICCProjectPolicy_put_UNIXIntegrationSnapshot_Proxy( 
    ICCProjectPolicy __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL pUNIXIntegrationSnapshot);


void __RPC_STUB ICCProjectPolicy_put_UNIXIntegrationSnapshot_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProjectPolicy_get_WinDevelopmentSnapshot_Proxy( 
    ICCProjectPolicy __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pWinDevelopmentSnapshot);


void __RPC_STUB ICCProjectPolicy_get_WinDevelopmentSnapshot_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE ICCProjectPolicy_put_WinDevelopmentSnapshot_Proxy( 
    ICCProjectPolicy __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL pWinDevelopmentSnapshot);


void __RPC_STUB ICCProjectPolicy_put_WinDevelopmentSnapshot_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProjectPolicy_get_WinIntegrationSnapshot_Proxy( 
    ICCProjectPolicy __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pWinIntegrationSnapshot);


void __RPC_STUB ICCProjectPolicy_get_WinIntegrationSnapshot_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE ICCProjectPolicy_put_WinIntegrationSnapshot_Proxy( 
    ICCProjectPolicy __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL pWinIntegrationSnapshot);


void __RPC_STUB ICCProjectPolicy_put_WinIntegrationSnapshot_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCProjectPolicy_INTERFACE_DEFINED__ */


#ifndef __ICCBaselines_INTERFACE_DEFINED__
#define __ICCBaselines_INTERFACE_DEFINED__

/* interface ICCBaselines */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCBaselines,0xB22C7F44,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7F44-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCBaselines : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long index,
            /* [retval][out] */ ICCBaseline __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ICCBaseline __RPC_FAR *pBaseline) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long index) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_InitErrors( 
            /* [retval][out] */ BSTR __RPC_FAR *pInitErrors) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCBaselinesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCBaselines __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCBaselines __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCBaselines __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCBaselines __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCBaselines __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCBaselines __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCBaselines __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ICCBaselines __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ ICCBaseline __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            ICCBaselines __RPC_FAR * This,
            /* [in] */ ICCBaseline __RPC_FAR *pBaseline);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ICCBaselines __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ICCBaselines __RPC_FAR * This,
            /* [in] */ long index);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InitErrors )( 
            ICCBaselines __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pInitErrors);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ICCBaselines __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);
        
        END_INTERFACE
    } ICCBaselinesVtbl;

    interface ICCBaselines
    {
        CONST_VTBL struct ICCBaselinesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCBaselines_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCBaselines_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCBaselines_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCBaselines_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCBaselines_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCBaselines_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCBaselines_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCBaselines_get_Item(This,index,pItem)	\
    (This)->lpVtbl -> get_Item(This,index,pItem)

#define ICCBaselines_Add(This,pBaseline)	\
    (This)->lpVtbl -> Add(This,pBaseline)

#define ICCBaselines_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define ICCBaselines_Remove(This,index)	\
    (This)->lpVtbl -> Remove(This,index)

#define ICCBaselines_get_InitErrors(This,pInitErrors)	\
    (This)->lpVtbl -> get_InitErrors(This,pInitErrors)

#define ICCBaselines_get__NewEnum(This,pEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,pEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBaselines_get_Item_Proxy( 
    ICCBaselines __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ ICCBaseline __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB ICCBaselines_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCBaselines_Add_Proxy( 
    ICCBaselines __RPC_FAR * This,
    /* [in] */ ICCBaseline __RPC_FAR *pBaseline);


void __RPC_STUB ICCBaselines_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBaselines_get_Count_Proxy( 
    ICCBaselines __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB ICCBaselines_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCBaselines_Remove_Proxy( 
    ICCBaselines __RPC_FAR * This,
    /* [in] */ long index);


void __RPC_STUB ICCBaselines_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBaselines_get_InitErrors_Proxy( 
    ICCBaselines __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pInitErrors);


void __RPC_STUB ICCBaselines_get_InitErrors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICCBaselines_get__NewEnum_Proxy( 
    ICCBaselines __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);


void __RPC_STUB ICCBaselines_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCBaselines_INTERFACE_DEFINED__ */


#ifndef __ICCFolders_INTERFACE_DEFINED__
#define __ICCFolders_INTERFACE_DEFINED__

/* interface ICCFolders */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCFolders,0xB22C7F42,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7F42-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCFolders : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long index,
            /* [retval][out] */ ICCFolder __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ICCFolder __RPC_FAR *pFolder) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long index) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_InitErrors( 
            /* [retval][out] */ BSTR __RPC_FAR *pInitErrors) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCFoldersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCFolders __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCFolders __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCFolders __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCFolders __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCFolders __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCFolders __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCFolders __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ICCFolders __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ ICCFolder __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            ICCFolders __RPC_FAR * This,
            /* [in] */ ICCFolder __RPC_FAR *pFolder);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ICCFolders __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ICCFolders __RPC_FAR * This,
            /* [in] */ long index);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InitErrors )( 
            ICCFolders __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pInitErrors);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ICCFolders __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);
        
        END_INTERFACE
    } ICCFoldersVtbl;

    interface ICCFolders
    {
        CONST_VTBL struct ICCFoldersVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCFolders_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCFolders_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCFolders_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCFolders_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCFolders_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCFolders_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCFolders_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCFolders_get_Item(This,index,pItem)	\
    (This)->lpVtbl -> get_Item(This,index,pItem)

#define ICCFolders_Add(This,pFolder)	\
    (This)->lpVtbl -> Add(This,pFolder)

#define ICCFolders_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define ICCFolders_Remove(This,index)	\
    (This)->lpVtbl -> Remove(This,index)

#define ICCFolders_get_InitErrors(This,pInitErrors)	\
    (This)->lpVtbl -> get_InitErrors(This,pInitErrors)

#define ICCFolders_get__NewEnum(This,pEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,pEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCFolders_get_Item_Proxy( 
    ICCFolders __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ ICCFolder __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB ICCFolders_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCFolders_Add_Proxy( 
    ICCFolders __RPC_FAR * This,
    /* [in] */ ICCFolder __RPC_FAR *pFolder);


void __RPC_STUB ICCFolders_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCFolders_get_Count_Proxy( 
    ICCFolders __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB ICCFolders_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCFolders_Remove_Proxy( 
    ICCFolders __RPC_FAR * This,
    /* [in] */ long index);


void __RPC_STUB ICCFolders_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCFolders_get_InitErrors_Proxy( 
    ICCFolders __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pInitErrors);


void __RPC_STUB ICCFolders_get_InitErrors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICCFolders_get__NewEnum_Proxy( 
    ICCFolders __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);


void __RPC_STUB ICCFolders_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCFolders_INTERFACE_DEFINED__ */


#ifndef __ICCViews_INTERFACE_DEFINED__
#define __ICCViews_INTERFACE_DEFINED__

/* interface ICCViews */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCViews,0xB22C7ECE,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7ECE-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCViews : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long index,
            /* [retval][out] */ ICCView __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ICCView __RPC_FAR *pView) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long index) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_InitErrors( 
            /* [retval][out] */ BSTR __RPC_FAR *pInitErrors) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCViewsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCViews __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCViews __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCViews __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCViews __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCViews __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCViews __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCViews __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ICCViews __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ ICCView __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            ICCViews __RPC_FAR * This,
            /* [in] */ ICCView __RPC_FAR *pView);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ICCViews __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ICCViews __RPC_FAR * This,
            /* [in] */ long index);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InitErrors )( 
            ICCViews __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pInitErrors);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ICCViews __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);
        
        END_INTERFACE
    } ICCViewsVtbl;

    interface ICCViews
    {
        CONST_VTBL struct ICCViewsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCViews_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCViews_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCViews_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCViews_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCViews_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCViews_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCViews_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCViews_get_Item(This,index,pItem)	\
    (This)->lpVtbl -> get_Item(This,index,pItem)

#define ICCViews_Add(This,pView)	\
    (This)->lpVtbl -> Add(This,pView)

#define ICCViews_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define ICCViews_Remove(This,index)	\
    (This)->lpVtbl -> Remove(This,index)

#define ICCViews_get_InitErrors(This,pInitErrors)	\
    (This)->lpVtbl -> get_InitErrors(This,pInitErrors)

#define ICCViews_get__NewEnum(This,pEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,pEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCViews_get_Item_Proxy( 
    ICCViews __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ ICCView __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB ICCViews_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCViews_Add_Proxy( 
    ICCViews __RPC_FAR * This,
    /* [in] */ ICCView __RPC_FAR *pView);


void __RPC_STUB ICCViews_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCViews_get_Count_Proxy( 
    ICCViews __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB ICCViews_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCViews_Remove_Proxy( 
    ICCViews __RPC_FAR * This,
    /* [in] */ long index);


void __RPC_STUB ICCViews_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCViews_get_InitErrors_Proxy( 
    ICCViews __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pInitErrors);


void __RPC_STUB ICCViews_get_InitErrors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICCViews_get__NewEnum_Proxy( 
    ICCViews __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);


void __RPC_STUB ICCViews_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCViews_INTERFACE_DEFINED__ */


#ifndef __ICCBranch_INTERFACE_DEFINED__
#define __ICCBranch_INTERFACE_DEFINED__

/* interface ICCBranch */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCBranch,0xB22C7EE9,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7EE9-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCBranch : public ICCVOBObject
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Path( 
            /* [retval][out] */ BSTR __RPC_FAR *pPath) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_BranchPointVersion( 
            /* [retval][out] */ ICCVersion __RPC_FAR *__RPC_FAR *pVersion) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateLock( 
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
            /* [optional][in] */ VARIANT ExemptUsersStringArray) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Element( 
            /* [retval][out] */ ICCElement __RPC_FAR *__RPC_FAR *pElement) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_LatestVersion( 
            /* [retval][out] */ ICCVersion __RPC_FAR *__RPC_FAR *pVersion) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Lock( 
            /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Master( 
            /* [retval][out] */ BSTR __RPC_FAR *pReplica) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE RequestMaster( 
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMaster( 
            /* [in] */ BSTR Replica,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ ICCBranchType __RPC_FAR *__RPC_FAR *pType) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Versions( 
            /* [retval][out] */ ICCVersions __RPC_FAR *__RPC_FAR *pVersions) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_VOB( 
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCBranchVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCBranch __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCBranch __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCBranch __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCBranch __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCBranch __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCBranch __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCBranch __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attribute )( 
            ICCBranch __RPC_FAR * This,
            /* [in] */ BSTR AttributeType,
            /* [retval][out] */ ICCAttribute __RPC_FAR *__RPC_FAR *pAttribute);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attributes )( 
            ICCBranch __RPC_FAR * This,
            /* [retval][out] */ ICCAttributes __RPC_FAR *__RPC_FAR *pAttributes);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Comment )( 
            ICCBranch __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pComment);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Comment )( 
            ICCBranch __RPC_FAR * This,
            /* [in] */ BSTR pComment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreationRecord )( 
            ICCBranch __RPC_FAR * This,
            /* [retval][out] */ ICCHistoryRecord __RPC_FAR *__RPC_FAR *pHistoryRecord);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HistoryRecords )( 
            ICCBranch __RPC_FAR * This,
            /* [in] */ ICCBranchType __RPC_FAR *pICCBranchType,
            /* [defaultvalue][optional][in] */ DATE Since,
            /* [defaultvalue][optional][in] */ BSTR User,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Minor,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL ExcludeCheckOutEvents,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL DirectoryOnly,
            /* [retval][out] */ ICCHistoryRecords __RPC_FAR *__RPC_FAR *pHistoryRecords);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hyperlinks )( 
            ICCBranch __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR HyperlinkType,
            /* [retval][out] */ ICCHyperlinks __RPC_FAR *__RPC_FAR *pHyperlinks);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OID )( 
            ICCBranch __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOBFamilyUUID )( 
            ICCBranch __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVOBFamilyUUID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Path )( 
            ICCBranch __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pPath);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BranchPointVersion )( 
            ICCBranch __RPC_FAR * This,
            /* [retval][out] */ ICCVersion __RPC_FAR *__RPC_FAR *pVersion);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateLock )( 
            ICCBranch __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
            /* [optional][in] */ VARIANT ExemptUsersStringArray);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Element )( 
            ICCBranch __RPC_FAR * This,
            /* [retval][out] */ ICCElement __RPC_FAR *__RPC_FAR *pElement);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LatestVersion )( 
            ICCBranch __RPC_FAR * This,
            /* [retval][out] */ ICCVersion __RPC_FAR *__RPC_FAR *pVersion);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Lock )( 
            ICCBranch __RPC_FAR * This,
            /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Master )( 
            ICCBranch __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pReplica);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ICCBranch __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RequestMaster )( 
            ICCBranch __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMaster )( 
            ICCBranch __RPC_FAR * This,
            /* [in] */ BSTR Replica,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            ICCBranch __RPC_FAR * This,
            /* [retval][out] */ ICCBranchType __RPC_FAR *__RPC_FAR *pType);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Versions )( 
            ICCBranch __RPC_FAR * This,
            /* [retval][out] */ ICCVersions __RPC_FAR *__RPC_FAR *pVersions);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOB )( 
            ICCBranch __RPC_FAR * This,
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);
        
        END_INTERFACE
    } ICCBranchVtbl;

    interface ICCBranch
    {
        CONST_VTBL struct ICCBranchVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCBranch_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCBranch_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCBranch_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCBranch_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCBranch_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCBranch_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCBranch_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCBranch_get_Attribute(This,AttributeType,pAttribute)	\
    (This)->lpVtbl -> get_Attribute(This,AttributeType,pAttribute)

#define ICCBranch_get_Attributes(This,pAttributes)	\
    (This)->lpVtbl -> get_Attributes(This,pAttributes)

#define ICCBranch_get_Comment(This,pComment)	\
    (This)->lpVtbl -> get_Comment(This,pComment)

#define ICCBranch_put_Comment(This,pComment)	\
    (This)->lpVtbl -> put_Comment(This,pComment)

#define ICCBranch_get_CreationRecord(This,pHistoryRecord)	\
    (This)->lpVtbl -> get_CreationRecord(This,pHistoryRecord)

#define ICCBranch_get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)	\
    (This)->lpVtbl -> get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)

#define ICCBranch_get_Hyperlinks(This,HyperlinkType,pHyperlinks)	\
    (This)->lpVtbl -> get_Hyperlinks(This,HyperlinkType,pHyperlinks)

#define ICCBranch_get_OID(This,pOID)	\
    (This)->lpVtbl -> get_OID(This,pOID)

#define ICCBranch_get_VOBFamilyUUID(This,pVOBFamilyUUID)	\
    (This)->lpVtbl -> get_VOBFamilyUUID(This,pVOBFamilyUUID)


#define ICCBranch_get_Path(This,pPath)	\
    (This)->lpVtbl -> get_Path(This,pPath)

#define ICCBranch_get_BranchPointVersion(This,pVersion)	\
    (This)->lpVtbl -> get_BranchPointVersion(This,pVersion)

#define ICCBranch_CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)	\
    (This)->lpVtbl -> CreateLock(This,Comment,Obsolete,ExemptUsersStringArray)

#define ICCBranch_get_Element(This,pElement)	\
    (This)->lpVtbl -> get_Element(This,pElement)

#define ICCBranch_get_LatestVersion(This,pVersion)	\
    (This)->lpVtbl -> get_LatestVersion(This,pVersion)

#define ICCBranch_get_Lock(This,pLock)	\
    (This)->lpVtbl -> get_Lock(This,pLock)

#define ICCBranch_get_Master(This,pReplica)	\
    (This)->lpVtbl -> get_Master(This,pReplica)

#define ICCBranch_Remove(This,Comment)	\
    (This)->lpVtbl -> Remove(This,Comment)

#define ICCBranch_RequestMaster(This,Comment)	\
    (This)->lpVtbl -> RequestMaster(This,Comment)

#define ICCBranch_SetMaster(This,Replica,Comment)	\
    (This)->lpVtbl -> SetMaster(This,Replica,Comment)

#define ICCBranch_get_Type(This,pType)	\
    (This)->lpVtbl -> get_Type(This,pType)

#define ICCBranch_get_Versions(This,pVersions)	\
    (This)->lpVtbl -> get_Versions(This,pVersions)

#define ICCBranch_get_VOB(This,pVOB)	\
    (This)->lpVtbl -> get_VOB(This,pVOB)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBranch_get_Path_Proxy( 
    ICCBranch __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pPath);


void __RPC_STUB ICCBranch_get_Path_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBranch_get_BranchPointVersion_Proxy( 
    ICCBranch __RPC_FAR * This,
    /* [retval][out] */ ICCVersion __RPC_FAR *__RPC_FAR *pVersion);


void __RPC_STUB ICCBranch_get_BranchPointVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCBranch_CreateLock_Proxy( 
    ICCBranch __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Comment,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Obsolete,
    /* [optional][in] */ VARIANT ExemptUsersStringArray);


void __RPC_STUB ICCBranch_CreateLock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBranch_get_Element_Proxy( 
    ICCBranch __RPC_FAR * This,
    /* [retval][out] */ ICCElement __RPC_FAR *__RPC_FAR *pElement);


void __RPC_STUB ICCBranch_get_Element_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBranch_get_LatestVersion_Proxy( 
    ICCBranch __RPC_FAR * This,
    /* [retval][out] */ ICCVersion __RPC_FAR *__RPC_FAR *pVersion);


void __RPC_STUB ICCBranch_get_LatestVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBranch_get_Lock_Proxy( 
    ICCBranch __RPC_FAR * This,
    /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pLock);


void __RPC_STUB ICCBranch_get_Lock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBranch_get_Master_Proxy( 
    ICCBranch __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pReplica);


void __RPC_STUB ICCBranch_get_Master_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCBranch_Remove_Proxy( 
    ICCBranch __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCBranch_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCBranch_RequestMaster_Proxy( 
    ICCBranch __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCBranch_RequestMaster_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCBranch_SetMaster_Proxy( 
    ICCBranch __RPC_FAR * This,
    /* [in] */ BSTR Replica,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCBranch_SetMaster_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBranch_get_Type_Proxy( 
    ICCBranch __RPC_FAR * This,
    /* [retval][out] */ ICCBranchType __RPC_FAR *__RPC_FAR *pType);


void __RPC_STUB ICCBranch_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBranch_get_Versions_Proxy( 
    ICCBranch __RPC_FAR * This,
    /* [retval][out] */ ICCVersions __RPC_FAR *__RPC_FAR *pVersions);


void __RPC_STUB ICCBranch_get_Versions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBranch_get_VOB_Proxy( 
    ICCBranch __RPC_FAR * This,
    /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);


void __RPC_STUB ICCBranch_get_VOB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCBranch_INTERFACE_DEFINED__ */


#ifndef __ICCVersions_INTERFACE_DEFINED__
#define __ICCVersions_INTERFACE_DEFINED__

/* interface ICCVersions */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCVersions,0xB22C7ED7,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7ED7-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCVersions : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long index,
            /* [retval][out] */ ICCVersion __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ICCVersion __RPC_FAR *pVersion) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long index) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_InitErrors( 
            /* [retval][out] */ BSTR __RPC_FAR *pInitErrors) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCVersionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCVersions __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCVersions __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCVersions __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCVersions __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCVersions __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCVersions __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCVersions __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ICCVersions __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ ICCVersion __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            ICCVersions __RPC_FAR * This,
            /* [in] */ ICCVersion __RPC_FAR *pVersion);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ICCVersions __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ICCVersions __RPC_FAR * This,
            /* [in] */ long index);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InitErrors )( 
            ICCVersions __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pInitErrors);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ICCVersions __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);
        
        END_INTERFACE
    } ICCVersionsVtbl;

    interface ICCVersions
    {
        CONST_VTBL struct ICCVersionsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCVersions_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCVersions_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCVersions_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCVersions_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCVersions_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCVersions_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCVersions_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCVersions_get_Item(This,index,pItem)	\
    (This)->lpVtbl -> get_Item(This,index,pItem)

#define ICCVersions_Add(This,pVersion)	\
    (This)->lpVtbl -> Add(This,pVersion)

#define ICCVersions_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define ICCVersions_Remove(This,index)	\
    (This)->lpVtbl -> Remove(This,index)

#define ICCVersions_get_InitErrors(This,pInitErrors)	\
    (This)->lpVtbl -> get_InitErrors(This,pInitErrors)

#define ICCVersions_get__NewEnum(This,pEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,pEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVersions_get_Item_Proxy( 
    ICCVersions __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ ICCVersion __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB ICCVersions_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCVersions_Add_Proxy( 
    ICCVersions __RPC_FAR * This,
    /* [in] */ ICCVersion __RPC_FAR *pVersion);


void __RPC_STUB ICCVersions_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVersions_get_Count_Proxy( 
    ICCVersions __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB ICCVersions_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCVersions_Remove_Proxy( 
    ICCVersions __RPC_FAR * This,
    /* [in] */ long index);


void __RPC_STUB ICCVersions_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVersions_get_InitErrors_Proxy( 
    ICCVersions __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pInitErrors);


void __RPC_STUB ICCVersions_get_InitErrors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICCVersions_get__NewEnum_Proxy( 
    ICCVersions __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);


void __RPC_STUB ICCVersions_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCVersions_INTERFACE_DEFINED__ */


#ifndef __ICCLabel_INTERFACE_DEFINED__
#define __ICCLabel_INTERFACE_DEFINED__

/* interface ICCLabel */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCLabel,0xB22C7EE5,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7EE5-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCLabel : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ ICCLabelType __RPC_FAR *__RPC_FAR *pType) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_VOB( 
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCLabelVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCLabel __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCLabel __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCLabel __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCLabel __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCLabel __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCLabel __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCLabel __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ICCLabel __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            ICCLabel __RPC_FAR * This,
            /* [retval][out] */ ICCLabelType __RPC_FAR *__RPC_FAR *pType);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOB )( 
            ICCLabel __RPC_FAR * This,
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);
        
        END_INTERFACE
    } ICCLabelVtbl;

    interface ICCLabel
    {
        CONST_VTBL struct ICCLabelVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCLabel_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCLabel_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCLabel_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCLabel_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCLabel_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCLabel_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCLabel_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCLabel_Remove(This,Comment)	\
    (This)->lpVtbl -> Remove(This,Comment)

#define ICCLabel_get_Type(This,pType)	\
    (This)->lpVtbl -> get_Type(This,pType)

#define ICCLabel_get_VOB(This,pVOB)	\
    (This)->lpVtbl -> get_VOB(This,pVOB)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCLabel_Remove_Proxy( 
    ICCLabel __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCLabel_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCLabel_get_Type_Proxy( 
    ICCLabel __RPC_FAR * This,
    /* [retval][out] */ ICCLabelType __RPC_FAR *__RPC_FAR *pType);


void __RPC_STUB ICCLabel_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCLabel_get_VOB_Proxy( 
    ICCLabel __RPC_FAR * This,
    /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);


void __RPC_STUB ICCLabel_get_VOB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCLabel_INTERFACE_DEFINED__ */


#ifndef __ICCLabels_INTERFACE_DEFINED__
#define __ICCLabels_INTERFACE_DEFINED__

/* interface ICCLabels */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCLabels,0xB22C7EE6,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7EE6-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCLabels : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long index,
            /* [retval][out] */ ICCLabel __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ICCLabel __RPC_FAR *pLabel) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long index) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCLabelsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCLabels __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCLabels __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCLabels __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCLabels __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCLabels __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCLabels __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCLabels __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ICCLabels __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ ICCLabel __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            ICCLabels __RPC_FAR * This,
            /* [in] */ ICCLabel __RPC_FAR *pLabel);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ICCLabels __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ICCLabels __RPC_FAR * This,
            /* [in] */ long index);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ICCLabels __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);
        
        END_INTERFACE
    } ICCLabelsVtbl;

    interface ICCLabels
    {
        CONST_VTBL struct ICCLabelsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCLabels_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCLabels_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCLabels_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCLabels_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCLabels_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCLabels_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCLabels_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCLabels_get_Item(This,index,pItem)	\
    (This)->lpVtbl -> get_Item(This,index,pItem)

#define ICCLabels_Add(This,pLabel)	\
    (This)->lpVtbl -> Add(This,pLabel)

#define ICCLabels_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define ICCLabels_Remove(This,index)	\
    (This)->lpVtbl -> Remove(This,index)

#define ICCLabels_get__NewEnum(This,pEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,pEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCLabels_get_Item_Proxy( 
    ICCLabels __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ ICCLabel __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB ICCLabels_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCLabels_Add_Proxy( 
    ICCLabels __RPC_FAR * This,
    /* [in] */ ICCLabel __RPC_FAR *pLabel);


void __RPC_STUB ICCLabels_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCLabels_get_Count_Proxy( 
    ICCLabels __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB ICCLabels_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCLabels_Remove_Proxy( 
    ICCLabels __RPC_FAR * This,
    /* [in] */ long index);


void __RPC_STUB ICCLabels_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICCLabels_get__NewEnum_Proxy( 
    ICCLabels __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);


void __RPC_STUB ICCLabels_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCLabels_INTERFACE_DEFINED__ */


#ifndef __ICCBranches_INTERFACE_DEFINED__
#define __ICCBranches_INTERFACE_DEFINED__

/* interface ICCBranches */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCBranches,0xB22C7EEA,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7EEA-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCBranches : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long index,
            /* [retval][out] */ ICCBranch __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ICCBranch __RPC_FAR *pBranch) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long index) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCBranchesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCBranches __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCBranches __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCBranches __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCBranches __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCBranches __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCBranches __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCBranches __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ICCBranches __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ ICCBranch __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            ICCBranches __RPC_FAR * This,
            /* [in] */ ICCBranch __RPC_FAR *pBranch);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ICCBranches __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ICCBranches __RPC_FAR * This,
            /* [in] */ long index);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ICCBranches __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);
        
        END_INTERFACE
    } ICCBranchesVtbl;

    interface ICCBranches
    {
        CONST_VTBL struct ICCBranchesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCBranches_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCBranches_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCBranches_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCBranches_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCBranches_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCBranches_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCBranches_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCBranches_get_Item(This,index,pItem)	\
    (This)->lpVtbl -> get_Item(This,index,pItem)

#define ICCBranches_Add(This,pBranch)	\
    (This)->lpVtbl -> Add(This,pBranch)

#define ICCBranches_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define ICCBranches_Remove(This,index)	\
    (This)->lpVtbl -> Remove(This,index)

#define ICCBranches_get__NewEnum(This,pEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,pEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBranches_get_Item_Proxy( 
    ICCBranches __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ ICCBranch __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB ICCBranches_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCBranches_Add_Proxy( 
    ICCBranches __RPC_FAR * This,
    /* [in] */ ICCBranch __RPC_FAR *pBranch);


void __RPC_STUB ICCBranches_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBranches_get_Count_Proxy( 
    ICCBranches __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB ICCBranches_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCBranches_Remove_Proxy( 
    ICCBranches __RPC_FAR * This,
    /* [in] */ long index);


void __RPC_STUB ICCBranches_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICCBranches_get__NewEnum_Proxy( 
    ICCBranches __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);


void __RPC_STUB ICCBranches_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCBranches_INTERFACE_DEFINED__ */


#ifndef __ICCBranchTypes_INTERFACE_DEFINED__
#define __ICCBranchTypes_INTERFACE_DEFINED__

/* interface ICCBranchTypes */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCBranchTypes,0xB22C7EE8,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7EE8-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCBranchTypes : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long index,
            /* [retval][out] */ ICCBranchType __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ICCBranchType __RPC_FAR *pBranchType) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long index) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCBranchTypesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCBranchTypes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCBranchTypes __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCBranchTypes __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCBranchTypes __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCBranchTypes __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCBranchTypes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCBranchTypes __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ICCBranchTypes __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ ICCBranchType __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            ICCBranchTypes __RPC_FAR * This,
            /* [in] */ ICCBranchType __RPC_FAR *pBranchType);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ICCBranchTypes __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ICCBranchTypes __RPC_FAR * This,
            /* [in] */ long index);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ICCBranchTypes __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);
        
        END_INTERFACE
    } ICCBranchTypesVtbl;

    interface ICCBranchTypes
    {
        CONST_VTBL struct ICCBranchTypesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCBranchTypes_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCBranchTypes_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCBranchTypes_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCBranchTypes_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCBranchTypes_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCBranchTypes_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCBranchTypes_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCBranchTypes_get_Item(This,index,pItem)	\
    (This)->lpVtbl -> get_Item(This,index,pItem)

#define ICCBranchTypes_Add(This,pBranchType)	\
    (This)->lpVtbl -> Add(This,pBranchType)

#define ICCBranchTypes_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define ICCBranchTypes_Remove(This,index)	\
    (This)->lpVtbl -> Remove(This,index)

#define ICCBranchTypes_get__NewEnum(This,pEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,pEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBranchTypes_get_Item_Proxy( 
    ICCBranchTypes __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ ICCBranchType __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB ICCBranchTypes_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCBranchTypes_Add_Proxy( 
    ICCBranchTypes __RPC_FAR * This,
    /* [in] */ ICCBranchType __RPC_FAR *pBranchType);


void __RPC_STUB ICCBranchTypes_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBranchTypes_get_Count_Proxy( 
    ICCBranchTypes __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB ICCBranchTypes_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCBranchTypes_Remove_Proxy( 
    ICCBranchTypes __RPC_FAR * This,
    /* [in] */ long index);


void __RPC_STUB ICCBranchTypes_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICCBranchTypes_get__NewEnum_Proxy( 
    ICCBranchTypes __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);


void __RPC_STUB ICCBranchTypes_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCBranchTypes_INTERFACE_DEFINED__ */


#ifndef __ICCHyperlink_INTERFACE_DEFINED__
#define __ICCHyperlink_INTERFACE_DEFINED__

/* interface ICCHyperlink */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCHyperlink,0xB22C7EE1,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7EE1-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCHyperlink : public ICCVOBObject
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IDString( 
            /* [retval][out] */ BSTR __RPC_FAR *pIDString) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_FromObject( 
            /* [retval][out] */ ICCVOBObject __RPC_FAR *__RPC_FAR *pFromObject) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_FromText( 
            /* [retval][out] */ BSTR __RPC_FAR *pFromText) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Group( 
            /* [retval][out] */ BSTR __RPC_FAR *pGroup) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Master( 
            /* [retval][out] */ BSTR __RPC_FAR *pReplica) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Owner( 
            /* [retval][out] */ BSTR __RPC_FAR *pOwner) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetGroup( 
            /* [in] */ BSTR NewGroup,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMaster( 
            /* [in] */ BSTR Replica,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetOwner( 
            /* [in] */ BSTR NewOwner,
            /* [defaultvalue][optional][in] */ BSTR Comment = L"") = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ToObject( 
            /* [retval][out] */ ICCVOBObject __RPC_FAR *__RPC_FAR *pToObject) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ToText( 
            /* [retval][out] */ BSTR __RPC_FAR *pToText) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ ICCHyperlinkType __RPC_FAR *__RPC_FAR *pType) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Unidirectional( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pUnidirectional) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_VOB( 
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCHyperlinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCHyperlink __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCHyperlink __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCHyperlink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCHyperlink __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCHyperlink __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCHyperlink __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCHyperlink __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attribute )( 
            ICCHyperlink __RPC_FAR * This,
            /* [in] */ BSTR AttributeType,
            /* [retval][out] */ ICCAttribute __RPC_FAR *__RPC_FAR *pAttribute);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attributes )( 
            ICCHyperlink __RPC_FAR * This,
            /* [retval][out] */ ICCAttributes __RPC_FAR *__RPC_FAR *pAttributes);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Comment )( 
            ICCHyperlink __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pComment);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Comment )( 
            ICCHyperlink __RPC_FAR * This,
            /* [in] */ BSTR pComment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreationRecord )( 
            ICCHyperlink __RPC_FAR * This,
            /* [retval][out] */ ICCHistoryRecord __RPC_FAR *__RPC_FAR *pHistoryRecord);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HistoryRecords )( 
            ICCHyperlink __RPC_FAR * This,
            /* [in] */ ICCBranchType __RPC_FAR *pICCBranchType,
            /* [defaultvalue][optional][in] */ DATE Since,
            /* [defaultvalue][optional][in] */ BSTR User,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Minor,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL ExcludeCheckOutEvents,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Recurse,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL DirectoryOnly,
            /* [retval][out] */ ICCHistoryRecords __RPC_FAR *__RPC_FAR *pHistoryRecords);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hyperlinks )( 
            ICCHyperlink __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR HyperlinkType,
            /* [retval][out] */ ICCHyperlinks __RPC_FAR *__RPC_FAR *pHyperlinks);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OID )( 
            ICCHyperlink __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOBFamilyUUID )( 
            ICCHyperlink __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVOBFamilyUUID);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IDString )( 
            ICCHyperlink __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pIDString);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FromObject )( 
            ICCHyperlink __RPC_FAR * This,
            /* [retval][out] */ ICCVOBObject __RPC_FAR *__RPC_FAR *pFromObject);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FromText )( 
            ICCHyperlink __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pFromText);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Group )( 
            ICCHyperlink __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pGroup);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Master )( 
            ICCHyperlink __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pReplica);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Owner )( 
            ICCHyperlink __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pOwner);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ICCHyperlink __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGroup )( 
            ICCHyperlink __RPC_FAR * This,
            /* [in] */ BSTR NewGroup,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMaster )( 
            ICCHyperlink __RPC_FAR * This,
            /* [in] */ BSTR Replica,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOwner )( 
            ICCHyperlink __RPC_FAR * This,
            /* [in] */ BSTR NewOwner,
            /* [defaultvalue][optional][in] */ BSTR Comment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ToObject )( 
            ICCHyperlink __RPC_FAR * This,
            /* [retval][out] */ ICCVOBObject __RPC_FAR *__RPC_FAR *pToObject);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ToText )( 
            ICCHyperlink __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pToText);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            ICCHyperlink __RPC_FAR * This,
            /* [retval][out] */ ICCHyperlinkType __RPC_FAR *__RPC_FAR *pType);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Unidirectional )( 
            ICCHyperlink __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pUnidirectional);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VOB )( 
            ICCHyperlink __RPC_FAR * This,
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);
        
        END_INTERFACE
    } ICCHyperlinkVtbl;

    interface ICCHyperlink
    {
        CONST_VTBL struct ICCHyperlinkVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCHyperlink_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCHyperlink_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCHyperlink_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCHyperlink_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCHyperlink_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCHyperlink_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCHyperlink_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCHyperlink_get_Attribute(This,AttributeType,pAttribute)	\
    (This)->lpVtbl -> get_Attribute(This,AttributeType,pAttribute)

#define ICCHyperlink_get_Attributes(This,pAttributes)	\
    (This)->lpVtbl -> get_Attributes(This,pAttributes)

#define ICCHyperlink_get_Comment(This,pComment)	\
    (This)->lpVtbl -> get_Comment(This,pComment)

#define ICCHyperlink_put_Comment(This,pComment)	\
    (This)->lpVtbl -> put_Comment(This,pComment)

#define ICCHyperlink_get_CreationRecord(This,pHistoryRecord)	\
    (This)->lpVtbl -> get_CreationRecord(This,pHistoryRecord)

#define ICCHyperlink_get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)	\
    (This)->lpVtbl -> get_HistoryRecords(This,pICCBranchType,Since,User,Minor,ExcludeCheckOutEvents,Recurse,DirectoryOnly,pHistoryRecords)

#define ICCHyperlink_get_Hyperlinks(This,HyperlinkType,pHyperlinks)	\
    (This)->lpVtbl -> get_Hyperlinks(This,HyperlinkType,pHyperlinks)

#define ICCHyperlink_get_OID(This,pOID)	\
    (This)->lpVtbl -> get_OID(This,pOID)

#define ICCHyperlink_get_VOBFamilyUUID(This,pVOBFamilyUUID)	\
    (This)->lpVtbl -> get_VOBFamilyUUID(This,pVOBFamilyUUID)


#define ICCHyperlink_get_IDString(This,pIDString)	\
    (This)->lpVtbl -> get_IDString(This,pIDString)

#define ICCHyperlink_get_FromObject(This,pFromObject)	\
    (This)->lpVtbl -> get_FromObject(This,pFromObject)

#define ICCHyperlink_get_FromText(This,pFromText)	\
    (This)->lpVtbl -> get_FromText(This,pFromText)

#define ICCHyperlink_get_Group(This,pGroup)	\
    (This)->lpVtbl -> get_Group(This,pGroup)

#define ICCHyperlink_get_Master(This,pReplica)	\
    (This)->lpVtbl -> get_Master(This,pReplica)

#define ICCHyperlink_get_Owner(This,pOwner)	\
    (This)->lpVtbl -> get_Owner(This,pOwner)

#define ICCHyperlink_Remove(This,Comment)	\
    (This)->lpVtbl -> Remove(This,Comment)

#define ICCHyperlink_SetGroup(This,NewGroup,Comment)	\
    (This)->lpVtbl -> SetGroup(This,NewGroup,Comment)

#define ICCHyperlink_SetMaster(This,Replica,Comment)	\
    (This)->lpVtbl -> SetMaster(This,Replica,Comment)

#define ICCHyperlink_SetOwner(This,NewOwner,Comment)	\
    (This)->lpVtbl -> SetOwner(This,NewOwner,Comment)

#define ICCHyperlink_get_ToObject(This,pToObject)	\
    (This)->lpVtbl -> get_ToObject(This,pToObject)

#define ICCHyperlink_get_ToText(This,pToText)	\
    (This)->lpVtbl -> get_ToText(This,pToText)

#define ICCHyperlink_get_Type(This,pType)	\
    (This)->lpVtbl -> get_Type(This,pType)

#define ICCHyperlink_get_Unidirectional(This,pUnidirectional)	\
    (This)->lpVtbl -> get_Unidirectional(This,pUnidirectional)

#define ICCHyperlink_get_VOB(This,pVOB)	\
    (This)->lpVtbl -> get_VOB(This,pVOB)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlink_get_IDString_Proxy( 
    ICCHyperlink __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pIDString);


void __RPC_STUB ICCHyperlink_get_IDString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlink_get_FromObject_Proxy( 
    ICCHyperlink __RPC_FAR * This,
    /* [retval][out] */ ICCVOBObject __RPC_FAR *__RPC_FAR *pFromObject);


void __RPC_STUB ICCHyperlink_get_FromObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlink_get_FromText_Proxy( 
    ICCHyperlink __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pFromText);


void __RPC_STUB ICCHyperlink_get_FromText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlink_get_Group_Proxy( 
    ICCHyperlink __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pGroup);


void __RPC_STUB ICCHyperlink_get_Group_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlink_get_Master_Proxy( 
    ICCHyperlink __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pReplica);


void __RPC_STUB ICCHyperlink_get_Master_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlink_get_Owner_Proxy( 
    ICCHyperlink __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pOwner);


void __RPC_STUB ICCHyperlink_get_Owner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlink_Remove_Proxy( 
    ICCHyperlink __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCHyperlink_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlink_SetGroup_Proxy( 
    ICCHyperlink __RPC_FAR * This,
    /* [in] */ BSTR NewGroup,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCHyperlink_SetGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlink_SetMaster_Proxy( 
    ICCHyperlink __RPC_FAR * This,
    /* [in] */ BSTR Replica,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCHyperlink_SetMaster_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlink_SetOwner_Proxy( 
    ICCHyperlink __RPC_FAR * This,
    /* [in] */ BSTR NewOwner,
    /* [defaultvalue][optional][in] */ BSTR Comment);


void __RPC_STUB ICCHyperlink_SetOwner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlink_get_ToObject_Proxy( 
    ICCHyperlink __RPC_FAR * This,
    /* [retval][out] */ ICCVOBObject __RPC_FAR *__RPC_FAR *pToObject);


void __RPC_STUB ICCHyperlink_get_ToObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlink_get_ToText_Proxy( 
    ICCHyperlink __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pToText);


void __RPC_STUB ICCHyperlink_get_ToText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlink_get_Type_Proxy( 
    ICCHyperlink __RPC_FAR * This,
    /* [retval][out] */ ICCHyperlinkType __RPC_FAR *__RPC_FAR *pType);


void __RPC_STUB ICCHyperlink_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlink_get_Unidirectional_Proxy( 
    ICCHyperlink __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pUnidirectional);


void __RPC_STUB ICCHyperlink_get_Unidirectional_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlink_get_VOB_Proxy( 
    ICCHyperlink __RPC_FAR * This,
    /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pVOB);


void __RPC_STUB ICCHyperlink_get_VOB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCHyperlink_INTERFACE_DEFINED__ */


#ifndef __ICCHyperlinkTypes_INTERFACE_DEFINED__
#define __ICCHyperlinkTypes_INTERFACE_DEFINED__

/* interface ICCHyperlinkTypes */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCHyperlinkTypes,0xB22C7EE0,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7EE0-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCHyperlinkTypes : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long index,
            /* [retval][out] */ ICCHyperlinkType __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ICCHyperlinkType __RPC_FAR *pHyperlinkType) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long index) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCHyperlinkTypesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCHyperlinkTypes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCHyperlinkTypes __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCHyperlinkTypes __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCHyperlinkTypes __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCHyperlinkTypes __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCHyperlinkTypes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCHyperlinkTypes __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ICCHyperlinkTypes __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ ICCHyperlinkType __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            ICCHyperlinkTypes __RPC_FAR * This,
            /* [in] */ ICCHyperlinkType __RPC_FAR *pHyperlinkType);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ICCHyperlinkTypes __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ICCHyperlinkTypes __RPC_FAR * This,
            /* [in] */ long index);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ICCHyperlinkTypes __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);
        
        END_INTERFACE
    } ICCHyperlinkTypesVtbl;

    interface ICCHyperlinkTypes
    {
        CONST_VTBL struct ICCHyperlinkTypesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCHyperlinkTypes_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCHyperlinkTypes_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCHyperlinkTypes_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCHyperlinkTypes_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCHyperlinkTypes_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCHyperlinkTypes_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCHyperlinkTypes_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCHyperlinkTypes_get_Item(This,index,pItem)	\
    (This)->lpVtbl -> get_Item(This,index,pItem)

#define ICCHyperlinkTypes_Add(This,pHyperlinkType)	\
    (This)->lpVtbl -> Add(This,pHyperlinkType)

#define ICCHyperlinkTypes_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define ICCHyperlinkTypes_Remove(This,index)	\
    (This)->lpVtbl -> Remove(This,index)

#define ICCHyperlinkTypes_get__NewEnum(This,pEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,pEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlinkTypes_get_Item_Proxy( 
    ICCHyperlinkTypes __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ ICCHyperlinkType __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB ICCHyperlinkTypes_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlinkTypes_Add_Proxy( 
    ICCHyperlinkTypes __RPC_FAR * This,
    /* [in] */ ICCHyperlinkType __RPC_FAR *pHyperlinkType);


void __RPC_STUB ICCHyperlinkTypes_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlinkTypes_get_Count_Proxy( 
    ICCHyperlinkTypes __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB ICCHyperlinkTypes_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlinkTypes_Remove_Proxy( 
    ICCHyperlinkTypes __RPC_FAR * This,
    /* [in] */ long index);


void __RPC_STUB ICCHyperlinkTypes_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlinkTypes_get__NewEnum_Proxy( 
    ICCHyperlinkTypes __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);


void __RPC_STUB ICCHyperlinkTypes_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCHyperlinkTypes_INTERFACE_DEFINED__ */


#ifndef __ICCLabelTypes_INTERFACE_DEFINED__
#define __ICCLabelTypes_INTERFACE_DEFINED__

/* interface ICCLabelTypes */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCLabelTypes,0xB22C7EE4,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7EE4-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCLabelTypes : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long index,
            /* [retval][out] */ ICCLabelType __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ICCLabelType __RPC_FAR *pLabelType) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long index) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCLabelTypesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCLabelTypes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCLabelTypes __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCLabelTypes __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCLabelTypes __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCLabelTypes __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCLabelTypes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCLabelTypes __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ICCLabelTypes __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ ICCLabelType __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            ICCLabelTypes __RPC_FAR * This,
            /* [in] */ ICCLabelType __RPC_FAR *pLabelType);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ICCLabelTypes __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ICCLabelTypes __RPC_FAR * This,
            /* [in] */ long index);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ICCLabelTypes __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);
        
        END_INTERFACE
    } ICCLabelTypesVtbl;

    interface ICCLabelTypes
    {
        CONST_VTBL struct ICCLabelTypesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCLabelTypes_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCLabelTypes_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCLabelTypes_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCLabelTypes_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCLabelTypes_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCLabelTypes_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCLabelTypes_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCLabelTypes_get_Item(This,index,pItem)	\
    (This)->lpVtbl -> get_Item(This,index,pItem)

#define ICCLabelTypes_Add(This,pLabelType)	\
    (This)->lpVtbl -> Add(This,pLabelType)

#define ICCLabelTypes_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define ICCLabelTypes_Remove(This,index)	\
    (This)->lpVtbl -> Remove(This,index)

#define ICCLabelTypes_get__NewEnum(This,pEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,pEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCLabelTypes_get_Item_Proxy( 
    ICCLabelTypes __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ ICCLabelType __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB ICCLabelTypes_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCLabelTypes_Add_Proxy( 
    ICCLabelTypes __RPC_FAR * This,
    /* [in] */ ICCLabelType __RPC_FAR *pLabelType);


void __RPC_STUB ICCLabelTypes_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCLabelTypes_get_Count_Proxy( 
    ICCLabelTypes __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB ICCLabelTypes_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCLabelTypes_Remove_Proxy( 
    ICCLabelTypes __RPC_FAR * This,
    /* [in] */ long index);


void __RPC_STUB ICCLabelTypes_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICCLabelTypes_get__NewEnum_Proxy( 
    ICCLabelTypes __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);


void __RPC_STUB ICCLabelTypes_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCLabelTypes_INTERFACE_DEFINED__ */


#ifndef __ICCLocks_INTERFACE_DEFINED__
#define __ICCLocks_INTERFACE_DEFINED__

/* interface ICCLocks */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCLocks,0xB22C7EF8,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7EF8-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCLocks : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long index,
            /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ICCLock __RPC_FAR *pLock) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long index) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCLocksVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCLocks __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCLocks __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCLocks __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCLocks __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCLocks __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCLocks __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCLocks __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ICCLocks __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            ICCLocks __RPC_FAR * This,
            /* [in] */ ICCLock __RPC_FAR *pLock);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ICCLocks __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ICCLocks __RPC_FAR * This,
            /* [in] */ long index);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ICCLocks __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);
        
        END_INTERFACE
    } ICCLocksVtbl;

    interface ICCLocks
    {
        CONST_VTBL struct ICCLocksVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCLocks_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCLocks_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCLocks_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCLocks_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCLocks_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCLocks_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCLocks_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCLocks_get_Item(This,index,pItem)	\
    (This)->lpVtbl -> get_Item(This,index,pItem)

#define ICCLocks_Add(This,pLock)	\
    (This)->lpVtbl -> Add(This,pLock)

#define ICCLocks_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define ICCLocks_Remove(This,index)	\
    (This)->lpVtbl -> Remove(This,index)

#define ICCLocks_get__NewEnum(This,pEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,pEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCLocks_get_Item_Proxy( 
    ICCLocks __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ ICCLock __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB ICCLocks_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCLocks_Add_Proxy( 
    ICCLocks __RPC_FAR * This,
    /* [in] */ ICCLock __RPC_FAR *pLock);


void __RPC_STUB ICCLocks_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCLocks_get_Count_Proxy( 
    ICCLocks __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB ICCLocks_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCLocks_Remove_Proxy( 
    ICCLocks __RPC_FAR * This,
    /* [in] */ long index);


void __RPC_STUB ICCLocks_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICCLocks_get__NewEnum_Proxy( 
    ICCLocks __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);


void __RPC_STUB ICCLocks_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCLocks_INTERFACE_DEFINED__ */


#ifndef __ICCTriggerTypes_INTERFACE_DEFINED__
#define __ICCTriggerTypes_INTERFACE_DEFINED__

/* interface ICCTriggerTypes */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCTriggerTypes,0xB22C7EF4,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7EF4-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCTriggerTypes : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long index,
            /* [retval][out] */ ICCTriggerType __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ICCTriggerType __RPC_FAR *pTriggerType) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long index) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCTriggerTypesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCTriggerTypes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCTriggerTypes __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCTriggerTypes __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCTriggerTypes __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCTriggerTypes __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCTriggerTypes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCTriggerTypes __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ICCTriggerTypes __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ ICCTriggerType __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            ICCTriggerTypes __RPC_FAR * This,
            /* [in] */ ICCTriggerType __RPC_FAR *pTriggerType);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ICCTriggerTypes __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ICCTriggerTypes __RPC_FAR * This,
            /* [in] */ long index);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ICCTriggerTypes __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);
        
        END_INTERFACE
    } ICCTriggerTypesVtbl;

    interface ICCTriggerTypes
    {
        CONST_VTBL struct ICCTriggerTypesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCTriggerTypes_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCTriggerTypes_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCTriggerTypes_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCTriggerTypes_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCTriggerTypes_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCTriggerTypes_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCTriggerTypes_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCTriggerTypes_get_Item(This,index,pItem)	\
    (This)->lpVtbl -> get_Item(This,index,pItem)

#define ICCTriggerTypes_Add(This,pTriggerType)	\
    (This)->lpVtbl -> Add(This,pTriggerType)

#define ICCTriggerTypes_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define ICCTriggerTypes_Remove(This,index)	\
    (This)->lpVtbl -> Remove(This,index)

#define ICCTriggerTypes_get__NewEnum(This,pEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,pEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypes_get_Item_Proxy( 
    ICCTriggerTypes __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ ICCTriggerType __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB ICCTriggerTypes_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypes_Add_Proxy( 
    ICCTriggerTypes __RPC_FAR * This,
    /* [in] */ ICCTriggerType __RPC_FAR *pTriggerType);


void __RPC_STUB ICCTriggerTypes_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypes_get_Count_Proxy( 
    ICCTriggerTypes __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB ICCTriggerTypes_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypes_Remove_Proxy( 
    ICCTriggerTypes __RPC_FAR * This,
    /* [in] */ long index);


void __RPC_STUB ICCTriggerTypes_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICCTriggerTypes_get__NewEnum_Proxy( 
    ICCTriggerTypes __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);


void __RPC_STUB ICCTriggerTypes_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCTriggerTypes_INTERFACE_DEFINED__ */


#ifndef __ICCAttributes_INTERFACE_DEFINED__
#define __ICCAttributes_INTERFACE_DEFINED__

/* interface ICCAttributes */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCAttributes,0xB22C7EEE,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7EEE-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCAttributes : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long index,
            /* [retval][out] */ ICCAttribute __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ICCAttribute __RPC_FAR *pAttribute) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long index) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCAttributesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCAttributes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCAttributes __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCAttributes __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCAttributes __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCAttributes __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCAttributes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCAttributes __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ICCAttributes __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ ICCAttribute __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            ICCAttributes __RPC_FAR * This,
            /* [in] */ ICCAttribute __RPC_FAR *pAttribute);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ICCAttributes __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ICCAttributes __RPC_FAR * This,
            /* [in] */ long index);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ICCAttributes __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);
        
        END_INTERFACE
    } ICCAttributesVtbl;

    interface ICCAttributes
    {
        CONST_VTBL struct ICCAttributesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCAttributes_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCAttributes_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCAttributes_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCAttributes_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCAttributes_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCAttributes_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCAttributes_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCAttributes_get_Item(This,index,pItem)	\
    (This)->lpVtbl -> get_Item(This,index,pItem)

#define ICCAttributes_Add(This,pAttribute)	\
    (This)->lpVtbl -> Add(This,pAttribute)

#define ICCAttributes_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define ICCAttributes_Remove(This,index)	\
    (This)->lpVtbl -> Remove(This,index)

#define ICCAttributes_get__NewEnum(This,pEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,pEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCAttributes_get_Item_Proxy( 
    ICCAttributes __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ ICCAttribute __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB ICCAttributes_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCAttributes_Add_Proxy( 
    ICCAttributes __RPC_FAR * This,
    /* [in] */ ICCAttribute __RPC_FAR *pAttribute);


void __RPC_STUB ICCAttributes_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCAttributes_get_Count_Proxy( 
    ICCAttributes __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB ICCAttributes_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCAttributes_Remove_Proxy( 
    ICCAttributes __RPC_FAR * This,
    /* [in] */ long index);


void __RPC_STUB ICCAttributes_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICCAttributes_get__NewEnum_Proxy( 
    ICCAttributes __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);


void __RPC_STUB ICCAttributes_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCAttributes_INTERFACE_DEFINED__ */


#ifndef __ICCHistoryRecords_INTERFACE_DEFINED__
#define __ICCHistoryRecords_INTERFACE_DEFINED__

/* interface ICCHistoryRecords */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCHistoryRecords,0xB22C7ED0,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7ED0-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCHistoryRecords : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long index,
            /* [retval][out] */ ICCHistoryRecord __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ICCHistoryRecord __RPC_FAR *pHistoryRecord) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long index) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCHistoryRecordsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCHistoryRecords __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCHistoryRecords __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCHistoryRecords __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCHistoryRecords __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCHistoryRecords __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCHistoryRecords __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCHistoryRecords __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ICCHistoryRecords __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ ICCHistoryRecord __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            ICCHistoryRecords __RPC_FAR * This,
            /* [in] */ ICCHistoryRecord __RPC_FAR *pHistoryRecord);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ICCHistoryRecords __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ICCHistoryRecords __RPC_FAR * This,
            /* [in] */ long index);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ICCHistoryRecords __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);
        
        END_INTERFACE
    } ICCHistoryRecordsVtbl;

    interface ICCHistoryRecords
    {
        CONST_VTBL struct ICCHistoryRecordsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCHistoryRecords_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCHistoryRecords_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCHistoryRecords_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCHistoryRecords_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCHistoryRecords_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCHistoryRecords_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCHistoryRecords_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCHistoryRecords_get_Item(This,index,pItem)	\
    (This)->lpVtbl -> get_Item(This,index,pItem)

#define ICCHistoryRecords_Add(This,pHistoryRecord)	\
    (This)->lpVtbl -> Add(This,pHistoryRecord)

#define ICCHistoryRecords_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define ICCHistoryRecords_Remove(This,index)	\
    (This)->lpVtbl -> Remove(This,index)

#define ICCHistoryRecords_get__NewEnum(This,pEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,pEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHistoryRecords_get_Item_Proxy( 
    ICCHistoryRecords __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ ICCHistoryRecord __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB ICCHistoryRecords_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCHistoryRecords_Add_Proxy( 
    ICCHistoryRecords __RPC_FAR * This,
    /* [in] */ ICCHistoryRecord __RPC_FAR *pHistoryRecord);


void __RPC_STUB ICCHistoryRecords_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHistoryRecords_get_Count_Proxy( 
    ICCHistoryRecords __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB ICCHistoryRecords_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCHistoryRecords_Remove_Proxy( 
    ICCHistoryRecords __RPC_FAR * This,
    /* [in] */ long index);


void __RPC_STUB ICCHistoryRecords_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICCHistoryRecords_get__NewEnum_Proxy( 
    ICCHistoryRecords __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);


void __RPC_STUB ICCHistoryRecords_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCHistoryRecords_INTERFACE_DEFINED__ */


#ifndef __ICCHyperlinks_INTERFACE_DEFINED__
#define __ICCHyperlinks_INTERFACE_DEFINED__

/* interface ICCHyperlinks */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCHyperlinks,0xB22C7EE2,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7EE2-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCHyperlinks : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long index,
            /* [retval][out] */ ICCHyperlink __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ICCHyperlink __RPC_FAR *pHyperlink) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long index) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCHyperlinksVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCHyperlinks __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCHyperlinks __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCHyperlinks __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCHyperlinks __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCHyperlinks __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCHyperlinks __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCHyperlinks __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ICCHyperlinks __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ ICCHyperlink __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            ICCHyperlinks __RPC_FAR * This,
            /* [in] */ ICCHyperlink __RPC_FAR *pHyperlink);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ICCHyperlinks __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ICCHyperlinks __RPC_FAR * This,
            /* [in] */ long index);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ICCHyperlinks __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);
        
        END_INTERFACE
    } ICCHyperlinksVtbl;

    interface ICCHyperlinks
    {
        CONST_VTBL struct ICCHyperlinksVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCHyperlinks_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCHyperlinks_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCHyperlinks_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCHyperlinks_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCHyperlinks_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCHyperlinks_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCHyperlinks_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCHyperlinks_get_Item(This,index,pItem)	\
    (This)->lpVtbl -> get_Item(This,index,pItem)

#define ICCHyperlinks_Add(This,pHyperlink)	\
    (This)->lpVtbl -> Add(This,pHyperlink)

#define ICCHyperlinks_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define ICCHyperlinks_Remove(This,index)	\
    (This)->lpVtbl -> Remove(This,index)

#define ICCHyperlinks_get__NewEnum(This,pEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,pEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlinks_get_Item_Proxy( 
    ICCHyperlinks __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ ICCHyperlink __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB ICCHyperlinks_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlinks_Add_Proxy( 
    ICCHyperlinks __RPC_FAR * This,
    /* [in] */ ICCHyperlink __RPC_FAR *pHyperlink);


void __RPC_STUB ICCHyperlinks_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlinks_get_Count_Proxy( 
    ICCHyperlinks __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB ICCHyperlinks_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlinks_Remove_Proxy( 
    ICCHyperlinks __RPC_FAR * This,
    /* [in] */ long index);


void __RPC_STUB ICCHyperlinks_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICCHyperlinks_get__NewEnum_Proxy( 
    ICCHyperlinks __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);


void __RPC_STUB ICCHyperlinks_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCHyperlinks_INTERFACE_DEFINED__ */


#ifndef __ICCCheckedOutFiles_INTERFACE_DEFINED__
#define __ICCCheckedOutFiles_INTERFACE_DEFINED__

/* interface ICCCheckedOutFiles */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCCheckedOutFiles,0xB22C7EDA,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7EDA-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCCheckedOutFiles : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long index,
            /* [retval][out] */ ICCCheckedOutFile __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ICCCheckedOutFile __RPC_FAR *pCheckedOutFile) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long index) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCCheckedOutFilesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCCheckedOutFiles __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCCheckedOutFiles __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCCheckedOutFiles __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCCheckedOutFiles __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCCheckedOutFiles __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCCheckedOutFiles __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCCheckedOutFiles __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ICCCheckedOutFiles __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ ICCCheckedOutFile __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            ICCCheckedOutFiles __RPC_FAR * This,
            /* [in] */ ICCCheckedOutFile __RPC_FAR *pCheckedOutFile);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ICCCheckedOutFiles __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ICCCheckedOutFiles __RPC_FAR * This,
            /* [in] */ long index);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ICCCheckedOutFiles __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);
        
        END_INTERFACE
    } ICCCheckedOutFilesVtbl;

    interface ICCCheckedOutFiles
    {
        CONST_VTBL struct ICCCheckedOutFilesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCCheckedOutFiles_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCCheckedOutFiles_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCCheckedOutFiles_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCCheckedOutFiles_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCCheckedOutFiles_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCCheckedOutFiles_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCCheckedOutFiles_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCCheckedOutFiles_get_Item(This,index,pItem)	\
    (This)->lpVtbl -> get_Item(This,index,pItem)

#define ICCCheckedOutFiles_Add(This,pCheckedOutFile)	\
    (This)->lpVtbl -> Add(This,pCheckedOutFile)

#define ICCCheckedOutFiles_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define ICCCheckedOutFiles_Remove(This,index)	\
    (This)->lpVtbl -> Remove(This,index)

#define ICCCheckedOutFiles_get__NewEnum(This,pEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,pEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCCheckedOutFiles_get_Item_Proxy( 
    ICCCheckedOutFiles __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ ICCCheckedOutFile __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB ICCCheckedOutFiles_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCCheckedOutFiles_Add_Proxy( 
    ICCCheckedOutFiles __RPC_FAR * This,
    /* [in] */ ICCCheckedOutFile __RPC_FAR *pCheckedOutFile);


void __RPC_STUB ICCCheckedOutFiles_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCCheckedOutFiles_get_Count_Proxy( 
    ICCCheckedOutFiles __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB ICCCheckedOutFiles_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCCheckedOutFiles_Remove_Proxy( 
    ICCCheckedOutFiles __RPC_FAR * This,
    /* [in] */ long index);


void __RPC_STUB ICCCheckedOutFiles_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICCCheckedOutFiles_get__NewEnum_Proxy( 
    ICCCheckedOutFiles __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);


void __RPC_STUB ICCCheckedOutFiles_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCCheckedOutFiles_INTERFACE_DEFINED__ */


#ifndef __ICCCheckedOutFileQuery_INTERFACE_DEFINED__
#define __ICCCheckedOutFileQuery_INTERFACE_DEFINED__

/* interface ICCCheckedOutFileQuery */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCCheckedOutFileQuery,0xB22C7EDC,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7EDC-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCCheckedOutFileQuery : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Apply( 
            /* [retval][out] */ ICCCheckedOutFiles __RPC_FAR *__RPC_FAR *pCheckedOutFiles) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_BranchType( 
            /* [retval][out] */ BSTR __RPC_FAR *pBranchType) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_BranchType( 
            /* [in] */ BSTR pBranchType) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ExamineAllReplicas( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pExamineAllReplicas) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_ExamineAllReplicas( 
            /* [in] */ VARIANT_BOOL pExamineAllReplicas) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_PathArray( 
            /* [retval][out] */ VARIANT __RPC_FAR *PathArray) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_PathArray( 
            /* [in] */ VARIANT PathArray) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_PathSelects( 
            /* [retval][out] */ CCPath_Selection __RPC_FAR *pSelection) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_PathSelects( 
            /* [in] */ CCPath_Selection pSelection) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_UseCurrentView( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pUseCurrentView) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_UseCurrentView( 
            /* [in] */ VARIANT_BOOL pUseCurrentView) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_User( 
            /* [retval][out] */ BSTR __RPC_FAR *pUser) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_User( 
            /* [in] */ BSTR pUser) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCCheckedOutFileQueryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCCheckedOutFileQuery __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCCheckedOutFileQuery __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCCheckedOutFileQuery __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCCheckedOutFileQuery __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCCheckedOutFileQuery __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCCheckedOutFileQuery __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCCheckedOutFileQuery __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Apply )( 
            ICCCheckedOutFileQuery __RPC_FAR * This,
            /* [retval][out] */ ICCCheckedOutFiles __RPC_FAR *__RPC_FAR *pCheckedOutFiles);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BranchType )( 
            ICCCheckedOutFileQuery __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pBranchType);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BranchType )( 
            ICCCheckedOutFileQuery __RPC_FAR * This,
            /* [in] */ BSTR pBranchType);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExamineAllReplicas )( 
            ICCCheckedOutFileQuery __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pExamineAllReplicas);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ExamineAllReplicas )( 
            ICCCheckedOutFileQuery __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pExamineAllReplicas);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PathArray )( 
            ICCCheckedOutFileQuery __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *PathArray);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PathArray )( 
            ICCCheckedOutFileQuery __RPC_FAR * This,
            /* [in] */ VARIANT PathArray);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PathSelects )( 
            ICCCheckedOutFileQuery __RPC_FAR * This,
            /* [retval][out] */ CCPath_Selection __RPC_FAR *pSelection);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PathSelects )( 
            ICCCheckedOutFileQuery __RPC_FAR * This,
            /* [in] */ CCPath_Selection pSelection);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UseCurrentView )( 
            ICCCheckedOutFileQuery __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pUseCurrentView);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UseCurrentView )( 
            ICCCheckedOutFileQuery __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pUseCurrentView);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_User )( 
            ICCCheckedOutFileQuery __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pUser);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_User )( 
            ICCCheckedOutFileQuery __RPC_FAR * This,
            /* [in] */ BSTR pUser);
        
        END_INTERFACE
    } ICCCheckedOutFileQueryVtbl;

    interface ICCCheckedOutFileQuery
    {
        CONST_VTBL struct ICCCheckedOutFileQueryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCCheckedOutFileQuery_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCCheckedOutFileQuery_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCCheckedOutFileQuery_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCCheckedOutFileQuery_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCCheckedOutFileQuery_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCCheckedOutFileQuery_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCCheckedOutFileQuery_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCCheckedOutFileQuery_Apply(This,pCheckedOutFiles)	\
    (This)->lpVtbl -> Apply(This,pCheckedOutFiles)

#define ICCCheckedOutFileQuery_get_BranchType(This,pBranchType)	\
    (This)->lpVtbl -> get_BranchType(This,pBranchType)

#define ICCCheckedOutFileQuery_put_BranchType(This,pBranchType)	\
    (This)->lpVtbl -> put_BranchType(This,pBranchType)

#define ICCCheckedOutFileQuery_get_ExamineAllReplicas(This,pExamineAllReplicas)	\
    (This)->lpVtbl -> get_ExamineAllReplicas(This,pExamineAllReplicas)

#define ICCCheckedOutFileQuery_put_ExamineAllReplicas(This,pExamineAllReplicas)	\
    (This)->lpVtbl -> put_ExamineAllReplicas(This,pExamineAllReplicas)

#define ICCCheckedOutFileQuery_get_PathArray(This,PathArray)	\
    (This)->lpVtbl -> get_PathArray(This,PathArray)

#define ICCCheckedOutFileQuery_put_PathArray(This,PathArray)	\
    (This)->lpVtbl -> put_PathArray(This,PathArray)

#define ICCCheckedOutFileQuery_get_PathSelects(This,pSelection)	\
    (This)->lpVtbl -> get_PathSelects(This,pSelection)

#define ICCCheckedOutFileQuery_put_PathSelects(This,pSelection)	\
    (This)->lpVtbl -> put_PathSelects(This,pSelection)

#define ICCCheckedOutFileQuery_get_UseCurrentView(This,pUseCurrentView)	\
    (This)->lpVtbl -> get_UseCurrentView(This,pUseCurrentView)

#define ICCCheckedOutFileQuery_put_UseCurrentView(This,pUseCurrentView)	\
    (This)->lpVtbl -> put_UseCurrentView(This,pUseCurrentView)

#define ICCCheckedOutFileQuery_get_User(This,pUser)	\
    (This)->lpVtbl -> get_User(This,pUser)

#define ICCCheckedOutFileQuery_put_User(This,pUser)	\
    (This)->lpVtbl -> put_User(This,pUser)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCCheckedOutFileQuery_Apply_Proxy( 
    ICCCheckedOutFileQuery __RPC_FAR * This,
    /* [retval][out] */ ICCCheckedOutFiles __RPC_FAR *__RPC_FAR *pCheckedOutFiles);


void __RPC_STUB ICCCheckedOutFileQuery_Apply_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCCheckedOutFileQuery_get_BranchType_Proxy( 
    ICCCheckedOutFileQuery __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pBranchType);


void __RPC_STUB ICCCheckedOutFileQuery_get_BranchType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE ICCCheckedOutFileQuery_put_BranchType_Proxy( 
    ICCCheckedOutFileQuery __RPC_FAR * This,
    /* [in] */ BSTR pBranchType);


void __RPC_STUB ICCCheckedOutFileQuery_put_BranchType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCCheckedOutFileQuery_get_ExamineAllReplicas_Proxy( 
    ICCCheckedOutFileQuery __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pExamineAllReplicas);


void __RPC_STUB ICCCheckedOutFileQuery_get_ExamineAllReplicas_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE ICCCheckedOutFileQuery_put_ExamineAllReplicas_Proxy( 
    ICCCheckedOutFileQuery __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL pExamineAllReplicas);


void __RPC_STUB ICCCheckedOutFileQuery_put_ExamineAllReplicas_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCCheckedOutFileQuery_get_PathArray_Proxy( 
    ICCCheckedOutFileQuery __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *PathArray);


void __RPC_STUB ICCCheckedOutFileQuery_get_PathArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE ICCCheckedOutFileQuery_put_PathArray_Proxy( 
    ICCCheckedOutFileQuery __RPC_FAR * This,
    /* [in] */ VARIANT PathArray);


void __RPC_STUB ICCCheckedOutFileQuery_put_PathArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCCheckedOutFileQuery_get_PathSelects_Proxy( 
    ICCCheckedOutFileQuery __RPC_FAR * This,
    /* [retval][out] */ CCPath_Selection __RPC_FAR *pSelection);


void __RPC_STUB ICCCheckedOutFileQuery_get_PathSelects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE ICCCheckedOutFileQuery_put_PathSelects_Proxy( 
    ICCCheckedOutFileQuery __RPC_FAR * This,
    /* [in] */ CCPath_Selection pSelection);


void __RPC_STUB ICCCheckedOutFileQuery_put_PathSelects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCCheckedOutFileQuery_get_UseCurrentView_Proxy( 
    ICCCheckedOutFileQuery __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pUseCurrentView);


void __RPC_STUB ICCCheckedOutFileQuery_get_UseCurrentView_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE ICCCheckedOutFileQuery_put_UseCurrentView_Proxy( 
    ICCCheckedOutFileQuery __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL pUseCurrentView);


void __RPC_STUB ICCCheckedOutFileQuery_put_UseCurrentView_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCCheckedOutFileQuery_get_User_Proxy( 
    ICCCheckedOutFileQuery __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pUser);


void __RPC_STUB ICCCheckedOutFileQuery_get_User_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE ICCCheckedOutFileQuery_put_User_Proxy( 
    ICCCheckedOutFileQuery __RPC_FAR * This,
    /* [in] */ BSTR pUser);


void __RPC_STUB ICCCheckedOutFileQuery_put_User_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCCheckedOutFileQuery_INTERFACE_DEFINED__ */


#ifndef __ICCElements_INTERFACE_DEFINED__
#define __ICCElements_INTERFACE_DEFINED__

/* interface ICCElements */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCElements,0xB22C7ED3,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7ED3-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCElements : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long index,
            /* [retval][out] */ ICCElement __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ICCElement __RPC_FAR *pElement) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long index) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCElementsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCElements __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCElements __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCElements __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCElements __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCElements __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCElements __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCElements __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ICCElements __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ ICCElement __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            ICCElements __RPC_FAR * This,
            /* [in] */ ICCElement __RPC_FAR *pElement);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ICCElements __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ICCElements __RPC_FAR * This,
            /* [in] */ long index);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ICCElements __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);
        
        END_INTERFACE
    } ICCElementsVtbl;

    interface ICCElements
    {
        CONST_VTBL struct ICCElementsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCElements_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCElements_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCElements_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCElements_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCElements_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCElements_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCElements_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCElements_get_Item(This,index,pItem)	\
    (This)->lpVtbl -> get_Item(This,index,pItem)

#define ICCElements_Add(This,pElement)	\
    (This)->lpVtbl -> Add(This,pElement)

#define ICCElements_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define ICCElements_Remove(This,index)	\
    (This)->lpVtbl -> Remove(This,index)

#define ICCElements_get__NewEnum(This,pEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,pEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCElements_get_Item_Proxy( 
    ICCElements __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ ICCElement __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB ICCElements_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCElements_Add_Proxy( 
    ICCElements __RPC_FAR * This,
    /* [in] */ ICCElement __RPC_FAR *pElement);


void __RPC_STUB ICCElements_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCElements_get_Count_Proxy( 
    ICCElements __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB ICCElements_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCElements_Remove_Proxy( 
    ICCElements __RPC_FAR * This,
    /* [in] */ long index);


void __RPC_STUB ICCElements_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICCElements_get__NewEnum_Proxy( 
    ICCElements __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);


void __RPC_STUB ICCElements_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCElements_INTERFACE_DEFINED__ */


#ifndef __ICCVOBs_INTERFACE_DEFINED__
#define __ICCVOBs_INTERFACE_DEFINED__

/* interface ICCVOBs */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCVOBs,0xB22C7ECC,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7ECC-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCVOBs : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long index,
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ICCVOB __RPC_FAR *pVOB) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long index) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_InitErrors( 
            /* [retval][out] */ BSTR __RPC_FAR *pInitErrors) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCVOBsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCVOBs __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCVOBs __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCVOBs __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCVOBs __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCVOBs __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCVOBs __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCVOBs __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ICCVOBs __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            ICCVOBs __RPC_FAR * This,
            /* [in] */ ICCVOB __RPC_FAR *pVOB);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ICCVOBs __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ICCVOBs __RPC_FAR * This,
            /* [in] */ long index);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InitErrors )( 
            ICCVOBs __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pInitErrors);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ICCVOBs __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);
        
        END_INTERFACE
    } ICCVOBsVtbl;

    interface ICCVOBs
    {
        CONST_VTBL struct ICCVOBsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCVOBs_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCVOBs_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCVOBs_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCVOBs_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCVOBs_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCVOBs_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCVOBs_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCVOBs_get_Item(This,index,pItem)	\
    (This)->lpVtbl -> get_Item(This,index,pItem)

#define ICCVOBs_Add(This,pVOB)	\
    (This)->lpVtbl -> Add(This,pVOB)

#define ICCVOBs_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define ICCVOBs_Remove(This,index)	\
    (This)->lpVtbl -> Remove(This,index)

#define ICCVOBs_get_InitErrors(This,pInitErrors)	\
    (This)->lpVtbl -> get_InitErrors(This,pInitErrors)

#define ICCVOBs_get__NewEnum(This,pEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,pEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOBs_get_Item_Proxy( 
    ICCVOBs __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ ICCVOB __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB ICCVOBs_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCVOBs_Add_Proxy( 
    ICCVOBs __RPC_FAR * This,
    /* [in] */ ICCVOB __RPC_FAR *pVOB);


void __RPC_STUB ICCVOBs_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOBs_get_Count_Proxy( 
    ICCVOBs __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB ICCVOBs_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCVOBs_Remove_Proxy( 
    ICCVOBs __RPC_FAR * This,
    /* [in] */ long index);


void __RPC_STUB ICCVOBs_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOBs_get_InitErrors_Proxy( 
    ICCVOBs __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pInitErrors);


void __RPC_STUB ICCVOBs_get_InitErrors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICCVOBs_get__NewEnum_Proxy( 
    ICCVOBs __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);


void __RPC_STUB ICCVOBs_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCVOBs_INTERFACE_DEFINED__ */


#ifndef __ICCBaselineComparison_INTERFACE_DEFINED__
#define __ICCBaselineComparison_INTERFACE_DEFINED__

/* interface ICCBaselineComparison */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCBaselineComparison,0xB22C7F2E,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7F2E-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCBaselineComparison : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ActivitiesInOneButNotTwo( 
            /* [retval][out] */ ICCActivities __RPC_FAR *__RPC_FAR *pActivities) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ActivitiesInTwoButNotOne( 
            /* [retval][out] */ ICCActivities __RPC_FAR *__RPC_FAR *pActivities) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_BaselineOne( 
            /* [retval][out] */ ICCBaseline __RPC_FAR *__RPC_FAR *pBaselineOne) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_BaselineOne( 
            /* [in] */ ICCBaseline __RPC_FAR *pBaselineOne) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_BaselineTwo( 
            /* [retval][out] */ ICCBaseline __RPC_FAR *__RPC_FAR *pBaselineTwo) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_BaselineTwo( 
            /* [in] */ ICCBaseline __RPC_FAR *pBaselineTwo) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ChangedActivities( 
            /* [retval][out] */ ICCActivities __RPC_FAR *__RPC_FAR *pActivities) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Compare( void) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_StreamOne( 
            /* [retval][out] */ ICCStream __RPC_FAR *__RPC_FAR *pStreamOne) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_StreamOne( 
            /* [in] */ ICCStream __RPC_FAR *pStreamOne) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_StreamTwo( 
            /* [retval][out] */ ICCStream __RPC_FAR *__RPC_FAR *pStreamTwo) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_StreamTwo( 
            /* [in] */ ICCStream __RPC_FAR *pStreamTwo) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_VersionsInOneButNotTwo( 
            /* [retval][out] */ ICCVersions __RPC_FAR *__RPC_FAR *pVersions) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_VersionsInTwoButNotOne( 
            /* [retval][out] */ ICCVersions __RPC_FAR *__RPC_FAR *pVersions) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCBaselineComparisonVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCBaselineComparison __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCBaselineComparison __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCBaselineComparison __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCBaselineComparison __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCBaselineComparison __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCBaselineComparison __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCBaselineComparison __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ActivitiesInOneButNotTwo )( 
            ICCBaselineComparison __RPC_FAR * This,
            /* [retval][out] */ ICCActivities __RPC_FAR *__RPC_FAR *pActivities);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ActivitiesInTwoButNotOne )( 
            ICCBaselineComparison __RPC_FAR * This,
            /* [retval][out] */ ICCActivities __RPC_FAR *__RPC_FAR *pActivities);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BaselineOne )( 
            ICCBaselineComparison __RPC_FAR * This,
            /* [retval][out] */ ICCBaseline __RPC_FAR *__RPC_FAR *pBaselineOne);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BaselineOne )( 
            ICCBaselineComparison __RPC_FAR * This,
            /* [in] */ ICCBaseline __RPC_FAR *pBaselineOne);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BaselineTwo )( 
            ICCBaselineComparison __RPC_FAR * This,
            /* [retval][out] */ ICCBaseline __RPC_FAR *__RPC_FAR *pBaselineTwo);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BaselineTwo )( 
            ICCBaselineComparison __RPC_FAR * This,
            /* [in] */ ICCBaseline __RPC_FAR *pBaselineTwo);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ChangedActivities )( 
            ICCBaselineComparison __RPC_FAR * This,
            /* [retval][out] */ ICCActivities __RPC_FAR *__RPC_FAR *pActivities);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Compare )( 
            ICCBaselineComparison __RPC_FAR * This);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StreamOne )( 
            ICCBaselineComparison __RPC_FAR * This,
            /* [retval][out] */ ICCStream __RPC_FAR *__RPC_FAR *pStreamOne);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StreamOne )( 
            ICCBaselineComparison __RPC_FAR * This,
            /* [in] */ ICCStream __RPC_FAR *pStreamOne);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StreamTwo )( 
            ICCBaselineComparison __RPC_FAR * This,
            /* [retval][out] */ ICCStream __RPC_FAR *__RPC_FAR *pStreamTwo);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StreamTwo )( 
            ICCBaselineComparison __RPC_FAR * This,
            /* [in] */ ICCStream __RPC_FAR *pStreamTwo);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VersionsInOneButNotTwo )( 
            ICCBaselineComparison __RPC_FAR * This,
            /* [retval][out] */ ICCVersions __RPC_FAR *__RPC_FAR *pVersions);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VersionsInTwoButNotOne )( 
            ICCBaselineComparison __RPC_FAR * This,
            /* [retval][out] */ ICCVersions __RPC_FAR *__RPC_FAR *pVersions);
        
        END_INTERFACE
    } ICCBaselineComparisonVtbl;

    interface ICCBaselineComparison
    {
        CONST_VTBL struct ICCBaselineComparisonVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCBaselineComparison_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCBaselineComparison_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCBaselineComparison_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCBaselineComparison_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCBaselineComparison_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCBaselineComparison_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCBaselineComparison_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCBaselineComparison_get_ActivitiesInOneButNotTwo(This,pActivities)	\
    (This)->lpVtbl -> get_ActivitiesInOneButNotTwo(This,pActivities)

#define ICCBaselineComparison_get_ActivitiesInTwoButNotOne(This,pActivities)	\
    (This)->lpVtbl -> get_ActivitiesInTwoButNotOne(This,pActivities)

#define ICCBaselineComparison_get_BaselineOne(This,pBaselineOne)	\
    (This)->lpVtbl -> get_BaselineOne(This,pBaselineOne)

#define ICCBaselineComparison_put_BaselineOne(This,pBaselineOne)	\
    (This)->lpVtbl -> put_BaselineOne(This,pBaselineOne)

#define ICCBaselineComparison_get_BaselineTwo(This,pBaselineTwo)	\
    (This)->lpVtbl -> get_BaselineTwo(This,pBaselineTwo)

#define ICCBaselineComparison_put_BaselineTwo(This,pBaselineTwo)	\
    (This)->lpVtbl -> put_BaselineTwo(This,pBaselineTwo)

#define ICCBaselineComparison_get_ChangedActivities(This,pActivities)	\
    (This)->lpVtbl -> get_ChangedActivities(This,pActivities)

#define ICCBaselineComparison_Compare(This)	\
    (This)->lpVtbl -> Compare(This)

#define ICCBaselineComparison_get_StreamOne(This,pStreamOne)	\
    (This)->lpVtbl -> get_StreamOne(This,pStreamOne)

#define ICCBaselineComparison_put_StreamOne(This,pStreamOne)	\
    (This)->lpVtbl -> put_StreamOne(This,pStreamOne)

#define ICCBaselineComparison_get_StreamTwo(This,pStreamTwo)	\
    (This)->lpVtbl -> get_StreamTwo(This,pStreamTwo)

#define ICCBaselineComparison_put_StreamTwo(This,pStreamTwo)	\
    (This)->lpVtbl -> put_StreamTwo(This,pStreamTwo)

#define ICCBaselineComparison_get_VersionsInOneButNotTwo(This,pVersions)	\
    (This)->lpVtbl -> get_VersionsInOneButNotTwo(This,pVersions)

#define ICCBaselineComparison_get_VersionsInTwoButNotOne(This,pVersions)	\
    (This)->lpVtbl -> get_VersionsInTwoButNotOne(This,pVersions)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBaselineComparison_get_ActivitiesInOneButNotTwo_Proxy( 
    ICCBaselineComparison __RPC_FAR * This,
    /* [retval][out] */ ICCActivities __RPC_FAR *__RPC_FAR *pActivities);


void __RPC_STUB ICCBaselineComparison_get_ActivitiesInOneButNotTwo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBaselineComparison_get_ActivitiesInTwoButNotOne_Proxy( 
    ICCBaselineComparison __RPC_FAR * This,
    /* [retval][out] */ ICCActivities __RPC_FAR *__RPC_FAR *pActivities);


void __RPC_STUB ICCBaselineComparison_get_ActivitiesInTwoButNotOne_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBaselineComparison_get_BaselineOne_Proxy( 
    ICCBaselineComparison __RPC_FAR * This,
    /* [retval][out] */ ICCBaseline __RPC_FAR *__RPC_FAR *pBaselineOne);


void __RPC_STUB ICCBaselineComparison_get_BaselineOne_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE ICCBaselineComparison_put_BaselineOne_Proxy( 
    ICCBaselineComparison __RPC_FAR * This,
    /* [in] */ ICCBaseline __RPC_FAR *pBaselineOne);


void __RPC_STUB ICCBaselineComparison_put_BaselineOne_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBaselineComparison_get_BaselineTwo_Proxy( 
    ICCBaselineComparison __RPC_FAR * This,
    /* [retval][out] */ ICCBaseline __RPC_FAR *__RPC_FAR *pBaselineTwo);


void __RPC_STUB ICCBaselineComparison_get_BaselineTwo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE ICCBaselineComparison_put_BaselineTwo_Proxy( 
    ICCBaselineComparison __RPC_FAR * This,
    /* [in] */ ICCBaseline __RPC_FAR *pBaselineTwo);


void __RPC_STUB ICCBaselineComparison_put_BaselineTwo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBaselineComparison_get_ChangedActivities_Proxy( 
    ICCBaselineComparison __RPC_FAR * This,
    /* [retval][out] */ ICCActivities __RPC_FAR *__RPC_FAR *pActivities);


void __RPC_STUB ICCBaselineComparison_get_ChangedActivities_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCBaselineComparison_Compare_Proxy( 
    ICCBaselineComparison __RPC_FAR * This);


void __RPC_STUB ICCBaselineComparison_Compare_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBaselineComparison_get_StreamOne_Proxy( 
    ICCBaselineComparison __RPC_FAR * This,
    /* [retval][out] */ ICCStream __RPC_FAR *__RPC_FAR *pStreamOne);


void __RPC_STUB ICCBaselineComparison_get_StreamOne_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE ICCBaselineComparison_put_StreamOne_Proxy( 
    ICCBaselineComparison __RPC_FAR * This,
    /* [in] */ ICCStream __RPC_FAR *pStreamOne);


void __RPC_STUB ICCBaselineComparison_put_StreamOne_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBaselineComparison_get_StreamTwo_Proxy( 
    ICCBaselineComparison __RPC_FAR * This,
    /* [retval][out] */ ICCStream __RPC_FAR *__RPC_FAR *pStreamTwo);


void __RPC_STUB ICCBaselineComparison_get_StreamTwo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE ICCBaselineComparison_put_StreamTwo_Proxy( 
    ICCBaselineComparison __RPC_FAR * This,
    /* [in] */ ICCStream __RPC_FAR *pStreamTwo);


void __RPC_STUB ICCBaselineComparison_put_StreamTwo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBaselineComparison_get_VersionsInOneButNotTwo_Proxy( 
    ICCBaselineComparison __RPC_FAR * This,
    /* [retval][out] */ ICCVersions __RPC_FAR *__RPC_FAR *pVersions);


void __RPC_STUB ICCBaselineComparison_get_VersionsInOneButNotTwo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCBaselineComparison_get_VersionsInTwoButNotOne_Proxy( 
    ICCBaselineComparison __RPC_FAR * This,
    /* [retval][out] */ ICCVersions __RPC_FAR *__RPC_FAR *pVersions);


void __RPC_STUB ICCBaselineComparison_get_VersionsInTwoButNotOne_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCBaselineComparison_INTERFACE_DEFINED__ */


#ifndef __ICCProjectVOBs_INTERFACE_DEFINED__
#define __ICCProjectVOBs_INTERFACE_DEFINED__

/* interface ICCProjectVOBs */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_ICCProjectVOBs,0xB22C7F40,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7F40-5A5E-11D3-B1CD-00C04F8ECE2F")
    ICCProjectVOBs : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long index,
            /* [retval][out] */ ICCProjectVOB __RPC_FAR *__RPC_FAR *pItem) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ICCProjectVOB __RPC_FAR *pProjectVOB) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long index) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCProjectVOBsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCProjectVOBs __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCProjectVOBs __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCProjectVOBs __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICCProjectVOBs __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICCProjectVOBs __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICCProjectVOBs __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICCProjectVOBs __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ICCProjectVOBs __RPC_FAR * This,
            /* [in] */ long index,
            /* [retval][out] */ ICCProjectVOB __RPC_FAR *__RPC_FAR *pItem);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            ICCProjectVOBs __RPC_FAR * This,
            /* [in] */ ICCProjectVOB __RPC_FAR *pProjectVOB);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ICCProjectVOBs __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            ICCProjectVOBs __RPC_FAR * This,
            /* [in] */ long index);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ICCProjectVOBs __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);
        
        END_INTERFACE
    } ICCProjectVOBsVtbl;

    interface ICCProjectVOBs
    {
        CONST_VTBL struct ICCProjectVOBsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCProjectVOBs_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCProjectVOBs_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCProjectVOBs_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCProjectVOBs_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICCProjectVOBs_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICCProjectVOBs_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICCProjectVOBs_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICCProjectVOBs_get_Item(This,index,pItem)	\
    (This)->lpVtbl -> get_Item(This,index,pItem)

#define ICCProjectVOBs_Add(This,pProjectVOB)	\
    (This)->lpVtbl -> Add(This,pProjectVOB)

#define ICCProjectVOBs_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define ICCProjectVOBs_Remove(This,index)	\
    (This)->lpVtbl -> Remove(This,index)

#define ICCProjectVOBs_get__NewEnum(This,pEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,pEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProjectVOBs_get_Item_Proxy( 
    ICCProjectVOBs __RPC_FAR * This,
    /* [in] */ long index,
    /* [retval][out] */ ICCProjectVOB __RPC_FAR *__RPC_FAR *pItem);


void __RPC_STUB ICCProjectVOBs_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCProjectVOBs_Add_Proxy( 
    ICCProjectVOBs __RPC_FAR * This,
    /* [in] */ ICCProjectVOB __RPC_FAR *pProjectVOB);


void __RPC_STUB ICCProjectVOBs_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ICCProjectVOBs_get_Count_Proxy( 
    ICCProjectVOBs __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB ICCProjectVOBs_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ICCProjectVOBs_Remove_Proxy( 
    ICCProjectVOBs __RPC_FAR * This,
    /* [in] */ long index);


void __RPC_STUB ICCProjectVOBs_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICCProjectVOBs_get__NewEnum_Proxy( 
    ICCProjectVOBs __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pEnum);


void __RPC_STUB ICCProjectVOBs_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCProjectVOBs_INTERFACE_DEFINED__ */


#ifndef __IClearTool_INTERFACE_DEFINED__
#define __IClearTool_INTERFACE_DEFINED__

/* interface IClearTool */
/* [object][oleautomation][nonextensible][dual][hidden][helpcontext][helpstring][uuid] */ 


DEFINE_GUID(IID_IClearTool,0xB22C7EC7,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B22C7EC7-5A5E-11D3-B1CD-00C04F8ECE2F")
    IClearTool : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CmdExec( 
            /* [in] */ BSTR CommandString,
            /* [retval][out] */ BSTR __RPC_FAR *CommandOutput) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE CmdExecOld( 
            /* [in] */ BSTR CommandString,
            /* [retval][out] */ BSTR __RPC_FAR *CommandOutput) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IClearToolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IClearTool __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IClearTool __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IClearTool __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IClearTool __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IClearTool __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IClearTool __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IClearTool __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CmdExec )( 
            IClearTool __RPC_FAR * This,
            /* [in] */ BSTR CommandString,
            /* [retval][out] */ BSTR __RPC_FAR *CommandOutput);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CmdExecOld )( 
            IClearTool __RPC_FAR * This,
            /* [in] */ BSTR CommandString,
            /* [retval][out] */ BSTR __RPC_FAR *CommandOutput);
        
        END_INTERFACE
    } IClearToolVtbl;

    interface IClearTool
    {
        CONST_VTBL struct IClearToolVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IClearTool_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IClearTool_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IClearTool_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IClearTool_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IClearTool_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IClearTool_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IClearTool_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IClearTool_CmdExec(This,CommandString,CommandOutput)	\
    (This)->lpVtbl -> CmdExec(This,CommandString,CommandOutput)

#define IClearTool_CmdExecOld(This,CommandString,CommandOutput)	\
    (This)->lpVtbl -> CmdExecOld(This,CommandString,CommandOutput)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IClearTool_CmdExec_Proxy( 
    IClearTool __RPC_FAR * This,
    /* [in] */ BSTR CommandString,
    /* [retval][out] */ BSTR __RPC_FAR *CommandOutput);


void __RPC_STUB IClearTool_CmdExec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE IClearTool_CmdExecOld_Proxy( 
    IClearTool __RPC_FAR * This,
    /* [in] */ BSTR CommandString,
    /* [retval][out] */ BSTR __RPC_FAR *CommandOutput);


void __RPC_STUB IClearTool_CmdExecOld_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IClearTool_INTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_Application,0xB22C7EFB,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7EFB-5A5E-11D3-B1CD-00C04F8ECE2F")
Application;
#endif

DEFINE_GUID(CLSID_ClearTool,0xB22C7EFC,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7EFC-5A5E-11D3-B1CD-00C04F8ECE2F")
ClearTool;
#endif

DEFINE_GUID(CLSID_CCVOB,0xB22C7EFD,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7EFD-5A5E-11D3-B1CD-00C04F8ECE2F")
CCVOB;
#endif

DEFINE_GUID(CLSID_CCVOBs,0xB22C7EFE,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7EFE-5A5E-11D3-B1CD-00C04F8ECE2F")
CCVOBs;
#endif

DEFINE_GUID(CLSID_CCView,0xB22C7EFF,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7EFF-5A5E-11D3-B1CD-00C04F8ECE2F")
CCView;
#endif

DEFINE_GUID(CLSID_CCViews,0xB22C7F00,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F00-5A5E-11D3-B1CD-00C04F8ECE2F")
CCViews;
#endif

DEFINE_GUID(CLSID_CCHistoryRecord,0xB22C7F01,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F01-5A5E-11D3-B1CD-00C04F8ECE2F")
CCHistoryRecord;
#endif

DEFINE_GUID(CLSID_CCHistoryRecords,0xB22C7F02,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F02-5A5E-11D3-B1CD-00C04F8ECE2F")
CCHistoryRecords;
#endif

DEFINE_GUID(CLSID_CCVOBObject,0xB22C7F03,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F03-5A5E-11D3-B1CD-00C04F8ECE2F")
CCVOBObject;
#endif

DEFINE_GUID(CLSID_CCFile,0xB22C7F04,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F04-5A5E-11D3-B1CD-00C04F8ECE2F")
CCFile;
#endif

DEFINE_GUID(CLSID_CCElement,0xB22C7F05,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F05-5A5E-11D3-B1CD-00C04F8ECE2F")
CCElement;
#endif

DEFINE_GUID(CLSID_CCElements,0xB22C7F06,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F06-5A5E-11D3-B1CD-00C04F8ECE2F")
CCElements;
#endif

DEFINE_GUID(CLSID_CCVersion,0xB22C7F07,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F07-5A5E-11D3-B1CD-00C04F8ECE2F")
CCVersion;
#endif

DEFINE_GUID(CLSID_CCVersions,0xB22C7F08,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F08-5A5E-11D3-B1CD-00C04F8ECE2F")
CCVersions;
#endif

DEFINE_GUID(CLSID_CCCheckedOutFile,0xB22C7F09,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F09-5A5E-11D3-B1CD-00C04F8ECE2F")
CCCheckedOutFile;
#endif

DEFINE_GUID(CLSID_CCCheckedOutFiles,0xB22C7F0A,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F0A-5A5E-11D3-B1CD-00C04F8ECE2F")
CCCheckedOutFiles;
#endif

DEFINE_GUID(CLSID_CCCheckedOutFileQuery,0xB22C7F0B,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F0B-5A5E-11D3-B1CD-00C04F8ECE2F")
CCCheckedOutFileQuery;
#endif

DEFINE_GUID(CLSID_CCHyperlink,0xB22C7F0C,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F0C-5A5E-11D3-B1CD-00C04F8ECE2F")
CCHyperlink;
#endif

DEFINE_GUID(CLSID_CCHyperlinks,0xB22C7F0D,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F0D-5A5E-11D3-B1CD-00C04F8ECE2F")
CCHyperlinks;
#endif

DEFINE_GUID(CLSID_CCHyperlinkType,0xB22C7F0E,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F0E-5A5E-11D3-B1CD-00C04F8ECE2F")
CCHyperlinkType;
#endif

DEFINE_GUID(CLSID_CCHyperlinkTypes,0xB22C7F0F,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F0F-5A5E-11D3-B1CD-00C04F8ECE2F")
CCHyperlinkTypes;
#endif

DEFINE_GUID(CLSID_CCLabel,0xB22C7F10,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F10-5A5E-11D3-B1CD-00C04F8ECE2F")
CCLabel;
#endif

DEFINE_GUID(CLSID_CCLabels,0xB22C7F11,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F11-5A5E-11D3-B1CD-00C04F8ECE2F")
CCLabels;
#endif

DEFINE_GUID(CLSID_CCLabelType,0xB22C7F12,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F12-5A5E-11D3-B1CD-00C04F8ECE2F")
CCLabelType;
#endif

DEFINE_GUID(CLSID_CCLabelTypes,0xB22C7F13,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F13-5A5E-11D3-B1CD-00C04F8ECE2F")
CCLabelTypes;
#endif

DEFINE_GUID(CLSID_CCBranch,0xB22C7F14,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F14-5A5E-11D3-B1CD-00C04F8ECE2F")
CCBranch;
#endif

DEFINE_GUID(CLSID_CCBranches,0xB22C7F15,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F15-5A5E-11D3-B1CD-00C04F8ECE2F")
CCBranches;
#endif

DEFINE_GUID(CLSID_CCBranchType,0xB22C7F16,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F16-5A5E-11D3-B1CD-00C04F8ECE2F")
CCBranchType;
#endif

DEFINE_GUID(CLSID_CCBranchTypes,0xB22C7F17,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F17-5A5E-11D3-B1CD-00C04F8ECE2F")
CCBranchTypes;
#endif

DEFINE_GUID(CLSID_CCAttribute,0xB22C7F18,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F18-5A5E-11D3-B1CD-00C04F8ECE2F")
CCAttribute;
#endif

DEFINE_GUID(CLSID_CCAttributes,0xB22C7F19,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F19-5A5E-11D3-B1CD-00C04F8ECE2F")
CCAttributes;
#endif

DEFINE_GUID(CLSID_CCAttributeType,0xB22C7F1A,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F1A-5A5E-11D3-B1CD-00C04F8ECE2F")
CCAttributeType;
#endif

DEFINE_GUID(CLSID_CCAttributeTypes,0xB22C7F1B,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F1B-5A5E-11D3-B1CD-00C04F8ECE2F")
CCAttributeTypes;
#endif

DEFINE_GUID(CLSID_CCTrigger,0xB22C7F1C,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F1C-5A5E-11D3-B1CD-00C04F8ECE2F")
CCTrigger;
#endif

DEFINE_GUID(CLSID_CCTriggers,0xB22C7F1D,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F1D-5A5E-11D3-B1CD-00C04F8ECE2F")
CCTriggers;
#endif

DEFINE_GUID(CLSID_CCTriggerType,0xB22C7F1E,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F1E-5A5E-11D3-B1CD-00C04F8ECE2F")
CCTriggerType;
#endif

DEFINE_GUID(CLSID_CCTriggerTypes,0xB22C7F1F,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F1F-5A5E-11D3-B1CD-00C04F8ECE2F")
CCTriggerTypes;
#endif

DEFINE_GUID(CLSID_CCTriggerTypeBuilder,0xB22C7F20,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F20-5A5E-11D3-B1CD-00C04F8ECE2F")
CCTriggerTypeBuilder;
#endif

DEFINE_GUID(CLSID_CCLock,0xB22C7F21,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F21-5A5E-11D3-B1CD-00C04F8ECE2F")
CCLock;
#endif

DEFINE_GUID(CLSID_CCLocks,0xB22C7F22,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F22-5A5E-11D3-B1CD-00C04F8ECE2F")
CCLocks;
#endif

DEFINE_GUID(CLSID_CCActivity,0xB22C7F23,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F23-5A5E-11D3-B1CD-00C04F8ECE2F")
CCActivity;
#endif

DEFINE_GUID(CLSID_CCActivities,0xB22C7F47,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F47-5A5E-11D3-B1CD-00C04F8ECE2F")
CCActivities;
#endif

DEFINE_GUID(CLSID_CCProjectVOB,0xB22C7F32,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F32-5A5E-11D3-B1CD-00C04F8ECE2F")
CCProjectVOB;
#endif

DEFINE_GUID(CLSID_CCProjectVOBs,0xB22C7F33,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F33-5A5E-11D3-B1CD-00C04F8ECE2F")
CCProjectVOBs;
#endif

DEFINE_GUID(CLSID_CCUCMObject,0xB22C7F48,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F48-5A5E-11D3-B1CD-00C04F8ECE2F")
CCUCMObject;
#endif

DEFINE_GUID(CLSID_CCProject,0xB22C7F34,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F34-5A5E-11D3-B1CD-00C04F8ECE2F")
CCProject;
#endif

DEFINE_GUID(CLSID_CCProjects,0xB22C7F35,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F35-5A5E-11D3-B1CD-00C04F8ECE2F")
CCProjects;
#endif

DEFINE_GUID(CLSID_CCFolder,0xB22C7F37,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F37-5A5E-11D3-B1CD-00C04F8ECE2F")
CCFolder;
#endif

DEFINE_GUID(CLSID_CCFolders,0xB22C7F38,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F38-5A5E-11D3-B1CD-00C04F8ECE2F")
CCFolders;
#endif

DEFINE_GUID(CLSID_CCComponent,0xB22C7F39,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F39-5A5E-11D3-B1CD-00C04F8ECE2F")
CCComponent;
#endif

DEFINE_GUID(CLSID_CCComponents,0xB22C7F3A,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F3A-5A5E-11D3-B1CD-00C04F8ECE2F")
CCComponents;
#endif

DEFINE_GUID(CLSID_CCBaseline,0xB22C7F3B,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F3B-5A5E-11D3-B1CD-00C04F8ECE2F")
CCBaseline;
#endif

DEFINE_GUID(CLSID_CCBaselines,0xB22C7F3C,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F3C-5A5E-11D3-B1CD-00C04F8ECE2F")
CCBaselines;
#endif

DEFINE_GUID(CLSID_CCStream,0xB22C7F3D,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F3D-5A5E-11D3-B1CD-00C04F8ECE2F")
CCStream;
#endif

DEFINE_GUID(CLSID_CCStreams,0xB22C7F3E,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F3E-5A5E-11D3-B1CD-00C04F8ECE2F")
CCStreams;
#endif

DEFINE_GUID(CLSID_CCBaselineComparison,0xB22C7F3F,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F3F-5A5E-11D3-B1CD-00C04F8ECE2F")
CCBaselineComparison;
#endif

DEFINE_GUID(CLSID_CCProjectPolicy,0xB22C7F46,0x5A5E,0x11D3,0xB1,0xCD,0x00,0xC0,0x4F,0x8E,0xCE,0x2F);

#ifdef __cplusplus

class DECLSPEC_UUID("B22C7F46-5A5E-11D3-B1CD-00C04F8ECE2F")
CCProjectPolicy;
#endif
#endif /* __ClearCase_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
