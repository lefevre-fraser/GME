#!/usr/bin/python
#
# Copyright (c) 2006-2008 ISIS, Vanderbilt Univeristy 
#
# Author: Peter Volgyesi (peter.volgyesi@vanderbilt.edu)
#
"""GME Build System - central module"""

import sys
import os, os.path
import getopt
from prefs import prefs
import tools
import win32com


#
# Constants
#
GME_ROOT = os.path.normpath(os.path.abspath("../.."))

#
# Build steps
#

def check_prerequisites():
    "Check prerequisites (required tools, etc.)"
    
    # Test for GME_ROOT environment variable
    if not os.environ['GME_ROOT']:
        print "GME_ROOT environment variable is not set!"
        raise
        
    if os.path.normpath(os.path.abspath(os.environ['GME_ROOT'])) != GME_ROOT:
        print "GME_ROOT environment variable is not set to the current dev. source tree!"
        print "GME_ROOT =", os.environ['GME_ROOT']
        print "Current dev. source tree:", GME_ROOT
        raise
    
    # Test for Microsoft Visual Studio 2008
    try:
        tools.test_VS()
    except:
        print "Microsoft Visual Studio 2008 is not installed!"
        raise
    
    # Test for zip utility
    try:
        tools.test_zip()
    except:
        print "ZIP utility cannot be found!"
        raise
    
    # Test for InstallShield
    try:
        tools.test_WiX()
    except:
        print "WiX toolset cannot be found in your path!"
        raise
    
    # Test for SVN
    try:
        tools.test_SVN()
    except:
        print "Warning: SVN client cannot be found! You won't be able to check in & tag releases"


def update_version_str():
    "Update version strings in source files"
    pass

def compile_GME():
    "Compile GME core components"
    sln_file = os.path.join(GME_ROOT, "GME", "GME.sln");
    tools.build_VS( sln_file, "Release" )
    cmd_dir = os.path.join(GME_ROOT, "GME");
    tools.system( "regrelease.bat >NUL", cmd_dir)


def compile_meta():
    "Compile MetaGME components"
    sln_file = os.path.join(GME_ROOT, "Paradigms", "MetaGME", "MetaGME.sln");
    tools.build_VS( sln_file, "Release" )
    cmd_dir = os.path.join(GME_ROOT, "Paradigms", "MetaGME");
    tools.system( "regrelease.bat >NUL", cmd_dir)

        
def compile_JBON():
    "Compile Java component support (JBON)"
    sln_file = os.path.join(GME_ROOT, "SDK", "Java", "native", "JavaSupport.sln");
    tools.build_VS( sln_file, "Release" )

        
def compile_tools():
    "Compile external tool components"
    
    # Table Editor
    sln_file = os.path.join(GME_ROOT, "Tools", "TableEditor", "TableEditor.sln");
    tools.build_VS( sln_file, "Release" )
    
    # Auto Layout
    sln_file = os.path.join(GME_ROOT, "Tools", "AutoLayout", "AutoLayout.sln");
    tools.build_VS( sln_file, "Release" )
    
    # Model Migrate - Does not compile currently
    #sln_file = os.path.join(GME_ROOT, "Tools", "ModelMigrate", "ModelMigrate.sln");
    #tools.build_VS( sln_file, "Release" )
    
    # GME Merge
    sln_file = os.path.join(GME_ROOT, "Tools", "GMEMerge", "GMEMerge.sln");
    tools.build_VS( sln_file, "Release" )
    
    # Pattern Processor
    sln_file = os.path.join(GME_ROOT, "SDK", "PatternProcessor", "PatternProcessor.sln");
    tools.build_VS( sln_file, "Release" )
    
    # ExtractCrashDumpXML 
    sln_file = os.path.join(GME_ROOT, "Tools", "ExtractCrashDumpXML", "ExtractCrashDumpXML.sln");
    tools.build_VS( sln_file, "Release" )
    

def compile_samples():
    "Compile sample components"
    
    # SF Paradigm
    sln_file = os.path.join(GME_ROOT, "Paradigms", "SF", "SFInterpreter", "SFInterpreter.sln");
    tools.build_VS( sln_file, "Release" )
    sln_file = os.path.join(GME_ROOT, "Paradigms", "SF", "BON2SFSample", "BON2SFSample.sln");
    tools.build_VS( sln_file, "Release" )
    sln_file = os.path.join(GME_ROOT, "Paradigms", "SF", "BON2SFInterpreter", "BON2SFInterpreter.sln");
    tools.build_VS( sln_file, "Release" )
    
    # HFSM Paradigm
    sln_file = os.path.join(GME_ROOT, "Paradigms", "HFSM", "HFSMSimulator", "HFSMSimulator.sln");
    tools.build_VS( sln_file, "Release" )
    
    # UML Paradigm
    sln_file = os.path.join(GME_ROOT, "Paradigms", "UML", "decorator", "UMLDecorator.sln");
    tools.build_VS( sln_file, "Release" )
    

def zip_decorkit():
    "Create DecoratorKit.zip"
    zip_dir = os.path.join(GME_ROOT, "SDK", "DecorKit")
    tools.zip(zip_dir, "DecoratorKit.zip", "packagefiles.lst")


def zip_scriptSDK():
    "Create ScriptSDK.zip"
    zip_dir = os.path.join(GME_ROOT, "SDK", "ScriptSDK")
    tools.zip(zip_dir, "ScriptSDK.zip", "packagefiles.lst")

def generate_meta_files():
    "Generate meta files (mta/mga)"
    meta_root = os.path.join(GME_ROOT, "Paradigms", "MetaGME", "Paradigm")
    meta_file = os.path.join(meta_root, "MetaGME.xmp")
    tools.xmp2mta(meta_file, "MetaGME")
    meta_file = os.path.join(meta_root, "MetaGME-model.xme")
    tools.xme2mga(meta_file, "MetaGME")


def generate_sample_files():
    "Generate sample files (mta/mga)"
    samples_root = os.path.join(GME_ROOT, "Paradigms")
    
    # SF Paradigm
    sample_file = os.path.join(samples_root, "SF", "SFMeta.xme")
    tools.xme2mga(sample_file, "MetaGME")
    sample_file = os.path.join(samples_root, "SF", "SF.xmp")
    tools.xmp2mta(sample_file, "SF") 
    sample_file = os.path.join(samples_root, "SF", "SFDemo.xme")
    tools.xme2mga(sample_file, "SF")

    # HFSM Paradigm
    sample_file = os.path.join(samples_root, "HFSM", "HFSM-Meta.xme")
    tools.xme2mga(sample_file, "MetaGME")
    sample_file = os.path.join(samples_root, "HFSM", "HFSM.xmp")
    tools.xmp2mta(sample_file, "HFSM") 
    sample_file = os.path.join(samples_root, "HFSM", "HFSM-Demo01.xme")
    tools.xme2mga(sample_file, "HFSM")
    sample_file = os.path.join(samples_root, "HFSM", "HFSM-Demo02.xme")
    tools.xme2mga(sample_file, "HFSM")
    
    # UML Paradigm
    sample_file = os.path.join(samples_root, "UML", "UMLMeta.xme")
    tools.xme2mga(sample_file, "MetaGME")
    sample_file = os.path.join(samples_root, "UML", "UML.xmp")
    tools.xmp2mta(sample_file, "UML")


def build_msi():
    "Build WiX installer (msi file)"
    
    # Prepare include file with dynamic data
    f = open(os.path.join(GME_ROOT, "Install", "GME_dyn.wxi"), 'w')
    print >> f, "<!-- DO NOT EDIT THIS FILE. WILL BE REGENERATED BY THE BUILD SCRIPTS -->"
    print >> f, "<Include>"
    print >> f, "   <?define VERSIONSTR='%s' ?>" % (prefs["version_string"])
    print >> f, "   <?define GUIDSTRMETAGME='%s' ?>" % (tools.query_GUID("MetaGME"))
    print >> f, "   <?define GUIDSTRHFSM='%s' ?>" % (tools.query_GUID("SF")) 
    print >> f, "   <?define GUIDSTRSF='%s' ?>" % (tools.query_GUID("UML"))
    print >> f, "   <?define GUIDSTRUML='%sf' ?>" % (tools.query_GUID("HFSM"))
    print >> f, "</Include>" 
    f.close()
   
    # Build the msi file
    tools.build_WiX(os.path.join(GME_ROOT, "Install", "GME.wxs"))

def zip_pdb():
    "Collect and zip all debug information (*.pdb)"
    zipname = os.path.join(GME_ROOT, "Install", "GME-" + prefs['version_string'] + "-symbols.zip")
    tools.collect_and_zip(GME_ROOT, zipname, "*.pdb")
    pass

def publish():
    "Publish and archive the install image and debug info"
    pass


def tag_repository():
    "Check in and Tag SVN repository (only for releases)"
    pass


def do_step(num, step):
    "Executing one building step given in param 'step'"
    print str(num) + ".", step.__doc__, "..."
    step()


#
# Main entry point
#

build_steps = [
    check_prerequisites,
    update_version_str,
    compile_GME,
    compile_meta,
    compile_JBON,
    compile_tools,
    compile_samples, 
    zip_decorkit, 
    zip_scriptSDK, 
    generate_meta_files,
    generate_sample_files, 
    build_msi,
    zip_pdb,
    publish,
    tag_repository
    ]

start_step = 0
end_step = len(build_steps)-1

usage = """
usage: %s [OPTION]...
Build an installation image (msi) for GME.

  -h, --help          display help (this message) and exit
  -v, --verbose       verbose output (default: %s)
  -c, --clean         clean projects before building them (default: %s)
  -s, --start=NUM     start at build step 'NUM' (default: %d)
  -e, --end=NUM       stop at build step 'NUM' (default: %d)
  -i, --include=NUM   include build step 'NUM' explicitly
  -x, --exclude=NUM   exclude build step 'NUM' explicitly
  
  -V, --version=MAJOR.MINOR.PATCHLEVEL
                      set build version (default: %d.%d.%d)

\tBuild steps:

\t%s
""" % (sys.argv[0],
       prefs["verbose"],
       prefs["clean"],
       start_step,
       end_step,
       prefs["version_major"],
       prefs["version_minor"],
       prefs["version_patch"],
       "\n\t".join([str(build_steps.index(s)) + ": " + s.__doc__ for s in build_steps])
       )

try:
    opts, args = getopt.getopt(sys.argv[1:], 'hvcs:e:i:x:V:',
                               ["help", "verbose", "clean",
                                "start=", "end=", "include=", "exclude=",
                                "version="])
    include_steps = []
    exclude_steps = []
    for opt, val in opts:
        if opt in ("-h", "--help"):
            print usage
            sys.exit()
        if opt in ("-v", "--verbose"):
            prefs["verbose"] = True
        if opt in ("-c", "--clean"):
            prefs["clean"] = True
        if opt in ("-s", "--start"):
            start_step = int(val)
        if opt in ("-e", "--end"):
            end_step = int(val)
        if opt in ("-i", "--include"):
            step = int(val)
            if val not in include_steps:
                include_steps.append(step)
        if opt in ("-x", "--exclude"):
            step = int(val)
            if val not in exclude_steps:
                exclude_steps.append(step)
        if opt in ("-V", "--version"):
            (M, m, p) = val.split(".")
            prefs["version_major"] = int(M)
            prefs["version_minor"] = int(m)
            prefs["version_patch"] = int(p)
            
except (getopt.GetoptError, ValueError, AttributeError), e:
    print e
    print usage
    sys.exit(2)
    
prefs["version_string"] = ".".join([str(prefs["version_major"]),
                                   str(prefs["version_minor"]),
                                   str(prefs["version_patch"])])

print "Building GME version " + prefs["version_string"]

try:
    for i in range(len(build_steps)):
        if i in include_steps:
            do_step(i, build_steps[i])
            continue
        if i in exclude_steps:
            continue
        if start_step <= i and i <= end_step:
            do_step(i, build_steps[i])

    print "Build SUCCEEDED."
except:
    print "!!! Build FAILED !!!"
    raise
