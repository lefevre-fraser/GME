#!/usr/bin/python
#
# Copyright (c) 2006 ISIS, Vanderbilt Univeristy 
#
# Author: Peter Volgyesi (peter.volgyesi@vanderbilt.edu)
#
"""GME Build System - tools module"""

import os
import os.path
import win32com.client
from prefs import prefs

#
# Constants
#
ZIP_PRG = os.path.abspath("zip.exe")
WIX_CANDLE_PRG = "candle.exe"
WIX_CANDLE_ARG = ""
WIX_LIGHT_PRG = "light.exe"
WIX_LIGHT_ARG = "-sw1076 -sw1055 -sw1056 -sice:ICE43 -sice:ICE57 -ext WixUIExtension -ext WixUtilExtension" # See comments in GME.wxs

#
# Classes
#
class BuildException(Exception):
    "General Exception Class for all build problems"
    pass

#
# Tools/utilities
#
def toolmsg(str):
    """
    Displays log messages, used by other tool functions
    """
    if prefs['verbose']:
        print "\t" + str + "..."

def test_SVN():
    "Test for SVN client. Raises exception if not found."
    system("svn -v >NUL")


def test_zip():
    "Test for ZIP utility. Raises exception if not found."
    system(ZIP_PRG + " >NUL")
    
    
def zip(dirname, zipname, list=None):
    """
    Build zip archive in the specified directory.
    The optional 'list' argument can specify the name of the file containing the
    include patterns for the archive.
    params
        dirname : the path to the root of the files to be archived
        zipname : the name of the zip archive (will be created in 'dirname')
        list    : name of the list file (see above)
    """
    if list is not None:
        list_arg = "-i@" + list
    else:
        list_arg = ""
    cmd_line = "%s -9 -r %s %s . >NUL" % (ZIP_PRG, list_arg, zipname)
    system(cmd_line, dirname)
    
def collect_and_zip(dirname, zipname, pattern=None):
    """
    Collect files (recursively) and build zip archive in the specified directory.
    params
        dirname : the path to the root of the files to be archived
        zipname : the name of the zip archive (will be created in 'dirname')
        pattern : file name pattern for selecting files to be included
    """
    if list is not None:
        pattern_arg = "-i " + pattern
    else:
        pattern_arg = ""
    cmd_line = "%s -9 -r %s . %s >NUL" % (ZIP_PRG, zipname, pattern_arg)
    system(cmd_line, dirname)


def system(command, dirname=None):
    """
    Executes a system command (throws an exception on error)
    params
        command : command to execute
        dirname : if set, execute the command within this directory
    """
#    if dirname is not None:
#        command = "cd /d %s && %s" % (dirname, command)
    toolmsg("Executing " + command)
    #ret = os.system( command )
    #if ret != 0:
    #    raise BuildException, command + " failed. Exit code: " + str(ret)
    import subprocess
    args = command.split(" ")
    if dirname is not None:
        args[0:0] = 'cd', '/d', '%s', '&&'
    with open(os.devnull, "w") as nulfp:
        # n.b. stderr=subprocess.STDOUT fails mysteriously
        import sys
        subprocess.check_call(args, stdout=(sys.stdout if prefs['verbose'] else nulfp), stderr=None, shell=True)



def test_VS():
    "Test for Microsoft Visual Studio 2010. Raises exception if not found."
    toolmsg("Trying to create VisualStudio.DTE object")
    win32com.client.Dispatch("VisualStudio.DTE.10.0")

def build_VS(sln_path, config_name):
    """
    Builds a Microsoft Visual Studio 2010 project or entire solution.
    It cleans the project/solution before building it if the global 'clean' preference
    is set.
    params
        sln_path     : full path to the solution (.sln) file
        config_name  : name of the build configuration (e.g.: "Release")
    """
    msg = "Cleaning and " * prefs['clean']
    msg += "Compiling " + sln_path + "(" + config_name + ") "
    toolmsg(msg)

    import subprocess
    # , '/fl', '/flp:Verbosity=diagnostic'
    args = ['msbuild', sln_path, '/t:' + ("Clean;" * prefs['clean']) + 'Build', '/p:Configuration=' + config_name]
    with open(os.devnull, "w") as nulfp:
        # n.b. stderr=subprocess.STDOUT fails mysteriously
        import sys
        subprocess.check_call(args, stdout=(sys.stdout if prefs['verbose'] else nulfp), stderr=None, shell=True)

def xme2mga(xml_file, paradigm):
    """
    Generates an .mga file from an .xme file
    params
        xml_file    : full path to the xme file 
        paradigm    : use the specified paradigm to parse the project
        
    The generated .mga file will be created with the same name/path but different
    extension.
    """
    toolmsg("Parsing " + xml_file + " with paradigm " + paradigm)
    parser  = win32com.client.Dispatch( "MGA.MgaParser" )
    project = win32com.client.Dispatch( "MGA.MgaProject" )
    mga_file = os.path.splitext(xml_file)[0] + ".mga"
    project.Create( "MGA="+mga_file, paradigm )
    parser.ParseProject( project, xml_file )
    project.Close()    

    
def xmp2mta(xml_file, paradigm):
    """
    Generates and registers (system-wide) an .mta file from an .xmp file
    params
        xml_file    : full path to the xmp file 
        paradigm    : use the specified paradigm name to parse the paradigm file
        
    The generated .mta file will be created with the same name/path but different
    extension.
    """
    toolmsg("Parsing and registering " + xml_file + " (" + paradigm + ")")
    regsitrar = win32com.client.Dispatch( "MGA.MgaRegistrar" )
    regsitrar.RegisterParadigmFromData( "XML=" + xml_file, paradigm, 2 )


def query_GUID(paradigm ):
    """
    Queries the current GUID of the specified paradigm.
    In order to work properly the paradigm must be registered (system-wide)
    before (see: xmp2mta).
    params
        paradigm    : the name of the paradigm to be queried
    
    returns the GUID as a string
    """ 
    regsitrar = win32com.client.Dispatch( "MGA.MgaRegistrar" )
    return regsitrar.ParadigmGUIDString(2, paradigm)


def test_WiX():
    "Test for WiX. Raises exception if not found."
    toolmsg("Trying to execute WiX tool candle.exe")
    exepath = WIX_CANDLE_PRG
    if os.environ['WIX']:
        exepath = os.path.join(os.environ['WIX'], 'bin', exepath)
    system('"%s" %s' % (exepath, "" if prefs['verbose'] else ">NUL"))
    
def build_WiX(wxs_file):
    """
    Builds a WiX project.
    params
        wxs_file : full path to the WiX source (.wxs)
    """
    fullpath = os.path.normpath(os.path.abspath(wxs_file))
    dirname = os.path.dirname(fullpath)
    filename = os.path.basename(fullpath)
    (projectname, ext) = os.path.splitext(filename)
    
    toolmsg("Building " + filename + " in " + dirname)
    
    exepath = WIX_CANDLE_PRG
    if os.environ['WIX']:
        exepath = os.path.join(os.environ['WIX'], 'bin', exepath)
    cmd_line = '"%s" %s %s %s' % (exepath, WIX_CANDLE_ARG, filename,  ("" if prefs['verbose'] else ">NUL"))
    system(cmd_line, dirname)
    
    exepath = WIX_LIGHT_PRG
    if os.environ['WIX']:
        exepath = os.path.join(os.environ['WIX'], 'bin', exepath)
    cmd_line = '"%s" %s %s.wixobj %s' % (exepath, WIX_LIGHT_ARG, projectname, ("" if prefs['verbose'] else ">NUL"))
    system(cmd_line, dirname)
        
