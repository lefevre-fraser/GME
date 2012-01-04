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
GME_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))

paradigms_root = os.path.join(GME_ROOT, "Paradigms")
METAGME_XMP = os.path.join(paradigms_root, "MetaGME", "MetaGME.xmp")
UML_XMP = os.path.join(paradigms_root, "UML", "UML.xmp")
SF_XMP = os.path.join(paradigms_root, "SF", "SF.xmp")
HFSM_XMP = os.path.join(paradigms_root, "HFSM", "HFSM.xmp")
def replace_ext(file, newext):
    import os.path
    return os.path.splitext(file)[0] + "." + newext
def mta_for_xmp(file):
    return replace_ext(file, "mta")

#
# Build steps
#

def check_prerequisites():
    "Check prerequisites (required tools, etc.)"
    
    # Test for GME_ROOT environment variable
    if not os.environ['GME_ROOT']:
        print "GME_ROOT environment variable is not set! (It should point to the GMESRC folder)"
        raise
        
    if not os.environ['JAVA_HOME']:
        print "JAVA_HOME environment variable is not set! (It should point to the JDK root folder)"
        raise
        
    if os.path.normpath(os.path.abspath(os.environ['GME_ROOT'])) != GME_ROOT:
        print "GME_ROOT environment variable is not set to the current dev. source tree!"
        print "GME_ROOT =", os.environ['GME_ROOT']
        print "Current dev. source tree:", GME_ROOT
        raise
    
    # Test for Microsoft Visual Studio 2010
    try:
        tools.test_VS()
    except:
        print "Microsoft Visual Studio 2010 is not installed!"
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
    with file(os.path.join(GME_ROOT, 'GME/Gme/GMEVersion.h.tmpl')) as template:
        template_text = "".join(file.readlines(template))
    with file(os.path.join(GME_ROOT, 'GME/Gme/GMEVersion.h'), 'w') as header:
        header.write(template_text % (prefs["version_major"], prefs["version_minor"], prefs["version_patch"], prefs["version_build"]))

def compile_GME():
    "Compile GME core components"
    sln_file = os.path.join(GME_ROOT, "GME", "GME.sln");
    tools.build_VS( sln_file, "Release" )
    sln_file = os.path.join(GME_ROOT, "GME", "GMEDecorators.sln")
    tools.build_VS( sln_file, "Release" )
    cmd_dir = os.path.join(GME_ROOT, "GME")
    if prefs['arch'] == 'x64':
        # Need x86 Console on x64 to be able to run the tests, since we use 32bit out-of-proc activation for ScriptHost
        tools.build_VS(os.path.join(GME_ROOT, 'GME', 'Console', 'Console.vcxproj'), 'Release', 'Win32')
    tools.system( ['call', 'regrelease.bat'] + (['x64'] if prefs['arch'] == 'x64' else []) + ['<NUL'], cmd_dir)

def _Release_PGO_dir():
    if prefs['arch'] == 'x64':
        return os.path.join(GME_ROOT, 'GME', 'x64', 'Release_PGO')
    else:
        return os.path.join(GME_ROOT, 'GME', 'Release_PGO')
    
def compile_GME_PGO_Instrument():
    "Compile GME core components (PGO Instrument)"
    import shutil
    import errno
    try:
        os.makedirs(_Release_PGO_dir())
    except OSError as exc:
        if exc.errno != errno.EEXIST:
            raise
    if prefs['arch'] == 'x64':
        shutil.copyfile(r"C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\bin\amd64\pgort100.dll", os.path.join(_Release_PGO_dir(), 'pgort100.dll'))
    else:
        shutil.copyfile(r"C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\bin\pgort100.dll", os.path.join(_Release_PGO_dir(), 'pgort100.dll'))
    sln_file = os.path.join(GME_ROOT, "GME", "GME.sln")
    tools.build_VS(sln_file, "Release_PGO_Instrument")
    cmd_dir = os.path.join(GME_ROOT, "GME")
    tools.system( ['call', 'regPGO.bat'] + (['x64'] if prefs['arch'] == 'x64' else []) + ['<NUL'], cmd_dir)

def compile_GME_PGO_Optimize():
    "Compile GME core components (PGO Optimize)"
    sln_file = os.path.join(GME_ROOT, "GME", "GME.sln")
    tools.build_VS( sln_file, "Release_PGO_Optimize" )

def PGO_train():
    "Run tests/Create training data for the PGO binaries"
    import glob
    for file in glob.glob(GME_ROOT + '\\GME' + ('\\x64' if prefs['arch'] == 'x64' else '') + '\\Release_PGO\\*.pgc'):
        os.remove(file)
    import subprocess
    subprocess.check_call([sys.executable, '-m', 'GPyUnit.__main__', '-x'] + (['-a', 'x64'] if prefs['arch'] == 'x64' else []), cwd=os.path.join(GME_ROOT, 'Tests'))

def compile_meta():
    "Compile MetaGME components"
    sln_file = os.path.join(GME_ROOT, "Paradigms", "MetaGME", "MetaGME.sln");
    tools.build_VS( sln_file, "Release" )
    cmd_dir = os.path.join(GME_ROOT, "Paradigms", "MetaGME");
    tools.system( ['call', 'regrelease.bat'] + (['x64'] if prefs['arch'] == 'x64' else []) + ['<NUL'], cmd_dir)

        
def compile_JBON():
    "Compile Java component support (JBON)"
    if prefs['arch'] == 'x64': return
    sln_file = os.path.join(GME_ROOT, "SDK", "Java", "native", "JavaSupport.sln");
    tools.build_VS( sln_file, "Release" )

        
def compile_tools():
    "Compile external tool components"
    
    # Auto Layout
    sln_file = os.path.join(GME_ROOT, "Tools", "AutoLayout", "AutoLayout.sln");
    tools.build_VS( sln_file, "Release" )
    if prefs['arch'] == 'x64': return

    # Table Editor
    sln_file = os.path.join(GME_ROOT, "Tools", "TableEditor", "TableEditor.sln");
    tools.build_VS( sln_file, "Release" )
    
    # GMEplink
    sln_file = os.path.join(GME_ROOT, "Tools", "GMEplink", "GMEplink.sln");
    tools.build_VS( sln_file, "Release" )

    sln_file = os.path.join(GME_ROOT, "SDK", "DotNet", "CSharpComponentWizard", "CSharpComponentWizard.sln");
    tools.build_VS( sln_file, "Release" )

def compile_samples():
    "Compile sample components"
    
    # UML Paradigm
    sln_file = os.path.join(GME_ROOT, "Paradigms", "UML", "decorator", "UMLDecorator.sln");
    tools.build_VS( sln_file, "Release" )

    if prefs['arch'] == 'x64': return

    sln_file = os.path.join(GME_ROOT, "SDK", "PatternProcessor", "PatternProcessor.sln");
    tools.build_VS( sln_file, "Release" )
    
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
    

def zip_decorsamples():
    "Create PlainDecoratorSample.zip"
    zip_dir = os.path.join(GME_ROOT, "SDK", "Decorator Examples", "PlainSample")
    tools.zip(zip_dir, "PlainDecoratorSample.zip", "packagefiles.lst")

    "Create NewDecoratorSample.zip"
    zip_dir = os.path.join(GME_ROOT, "SDK", "Decorator Examples", "NewSample")
    tools.zip(zip_dir, "NewDecoratorSample.zip", "packagefiles.lst")


def zip_scriptSDK():
    "Create ScriptSDK.zip"
    zip_dir = os.path.join(GME_ROOT, "SDK", "ScriptSDK")
    tools.zip(zip_dir, "ScriptSDK.zip", "packagefiles.lst")

def generate_meta_files():
    "Generate meta files (mta/mga)"
    meta_root = os.path.join(GME_ROOT, "Paradigms", "MetaGME")
    tools.xmp2mta(METAGME_XMP, "MetaGME")
    meta_file = os.path.join(meta_root, "MetaGME-model.xme")
    tools.xme2mga(meta_file, "MetaGME")


def generate_sample_files():
    "Generate sample files (mta/mga)"
    samples_root = os.path.join(GME_ROOT, "Paradigms")
    
    # SF Paradigm
    sample_file = os.path.join(samples_root, "SF", "SFMeta.xme")
    tools.xme2mga(sample_file, "MetaGME")
    tools.xmp2mta(SF_XMP, "SF") 
    sample_file = os.path.join(samples_root, "SF", "SFDemo.xme")
    tools.xme2mga(sample_file, "SF")

    # HFSM Paradigm
    sample_file = os.path.join(samples_root, "HFSM", "HFSM-Meta.xme")
    tools.xme2mga(sample_file, "MetaGME")
    tools.xmp2mta(HFSM_XMP, "HFSM") 
    sample_file = os.path.join(samples_root, "HFSM", "HFSM-Demo01.xme")
    tools.xme2mga(sample_file, "HFSM")
    sample_file = os.path.join(samples_root, "HFSM", "HFSM-Demo02.xme")
    tools.xme2mga(sample_file, "HFSM")
    
    # UML Paradigm
    sample_file = os.path.join(samples_root, "UML", "UMLMeta.xme")
    tools.xme2mga(sample_file, "MetaGME")
    tools.xmp2mta(UML_XMP, "UML")


def build_msms():
    "Build WiX merge modules (msm files)"
    
    # Prepare include file with dynamic data
    f = open(os.path.join(GME_ROOT, "Install", "GME_dyn.wxi"), 'w')
    print >> f, "<!-- DO NOT EDIT THIS FILE. WILL BE REGENERATED BY THE BUILD SCRIPTS -->"
    print >> f, "<Include>"
    print >> f, "   <?define GUIDSTRMETAGME='%s' ?>" % (tools.query_GUID(mta_for_xmp(METAGME_XMP)))
    print >> f, "   <?define GUIDSTRHFSM='%s' ?>" % (tools.query_GUID(mta_for_xmp(HFSM_XMP)))
    print >> f, "   <?define GUIDSTRSF='%s' ?>" % (tools.query_GUID(mta_for_xmp(SF_XMP)))
    print >> f, "   <?define GUIDSTRUML='%s' ?>" % (tools.query_GUID(mta_for_xmp(UML_XMP)))
    print >> f, "</Include>" 
    f.close()
   
    import glob
    tools.build_WiX([]
        + [file for file in glob.glob(os.path.join(GME_ROOT, "Install", "*.wxs")) if file.find('GME.wxs') == -1 ]
        + glob.glob(os.path.join(GME_ROOT, "Install", "PIAs", "*.wxi"))
        + glob.glob(os.path.join(GME_ROOT, "Install", "PIAs_1.0.1.0", "*.wxi"))
        )

def build_msi():
    "Build WiX installer (msi file)"

    import glob
    # Build the msi file
    tools.build_WiX([os.path.join(GME_ROOT, "Install", "GME.wxs")])
   

def zip_pdb():
    "Collect and zip all debug information (*.pdb)"
    tools.system(r"call install\symbols_source_server.cmd <NUL".split(), GME_ROOT)
    zipname = os.path.join(GME_ROOT, "Install", "GME-" + prefs['version_string'] + "-symbols.zip")
    tools.collect_and_zip(GME_ROOT, zipname, "*.pdb *.dll *.exe *.ocx")
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
    zip_decorsamples, 
    zip_scriptSDK, 
    generate_meta_files,
    generate_sample_files, 
    compile_GME_PGO_Instrument,
    PGO_train,
    compile_GME_PGO_Optimize,
    build_msms,
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

  -V, --version=MAJOR.MINOR.PATCHLEVEL.BUILD
                      set version (default: %d.%d.%d.%d)
  -b, --build_version=BUILD
                      set only the build version  

  -a, --arch=ARCH     set architecture (x64 or x86)
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
       prefs["version_build"],
       "\n\t".join([str(build_steps.index(s)) + ": " + s.__doc__ + ' (' + s.__name__ + ')' for s in build_steps])
       )

try:
    opts, args = getopt.getopt(sys.argv[1:], 'hvcs:e:i:x:V:b:a:',
                               ["help", "verbose", "clean",
                                "start=", "end=", "include=", "exclude=",
                                "version=", "build_version=", "arch="])
    include_steps = []
    exclude_steps = []
    if args:
        print usage
        sys.exit()
    def get_step(arg):
        try:
            return int(arg)
        except ValueError, e:
            return [step.__name__ for step in build_steps].index(arg)
    for opt, val in opts:
        if opt in ("-h", "--help"):
            print usage
            sys.exit()
        if opt in ("-v", "--verbose"):
            prefs["verbose"] = True
        if opt in ("-c", "--clean"):
            prefs["clean"] = True
        if opt in ("-s", "--start"):
            start_step = get_step(val)
        if opt in ("-e", "--end"):
            end_step = get_step(val)
        if opt in ("-i", "--include"):
            step = get_step(val)
            if val not in include_steps:
                include_steps.append(step)
        if opt in ("-x", "--exclude"):
            step = get_step(val)
            if val not in exclude_steps:
                exclude_steps.append(step)
        if opt in ("-b", "--build_version"):
            prefs["version_build"] = int(val)
        if opt in ("-V", "--version"):
            (M, m, p, b) = val.split(".")
            prefs["version_major"] = int(M)
            prefs["version_minor"] = int(m)
            prefs["version_patch"] = int(p)
            prefs["version_build"] = int(b)
        if opt in ("-a", "--arch"):
            prefs["arch"] = val
            
except (getopt.GetoptError, ValueError, AttributeError), e:
    print e
    print usage
    sys.exit(2)
    
prefs["version_string"] = ".".join([str(prefs["version_major"]),
                                   str(prefs["version_minor"]),
                                   str(prefs["version_patch"])] +
                                   ( [ str(prefs["version_build"]) ] if prefs["version_build"] != 0 else [] ))

print "Building GME version " + prefs["version_string"] + " " + prefs["arch"]

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
