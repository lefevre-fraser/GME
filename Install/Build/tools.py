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

def test_CVS():
    "Test for CVS client. Raises exception if not found."
    system("cvs -v >NUL")


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


def system(command, dirname=None):
    """
    Executes a system command (throws an exception on error)
    params
        command : command to execute
        dirname : if set, execute the command within this directory
    """
    if dirname is not None:
        command = "cd %s && %s" % (dirname, command)
    toolmsg("Executing " + command)
    ret = os.system( command )
    if ret != 0:
        raise BuildException, command + " failed. Exit code: " + str(ret)


def test_VS():
    "Test for Microsoft Visual Studio.NET 2003. Raises exception if not found."
    toolmsg("Trying to create VisualStudio.DTE object")
    win32com.client.Dispatch("VisualStudio.DTE.7.1")


def build_VS(sln_path, project_name, config_name):
    """
    Builds a Microsoft Visual Studio.NET 2003 project.
    It cleans the project before building it if the global 'clean' preference
    is set.
    params
        sln_path     : full path to the solution (.sln) file
	project_name : relative path to the project (.vcproj) file
	config_name  : name of the build configuration (e.g.: "Release")
    """
    msg = "Cleaning and " * prefs['clean']
    msg += "Compiling " + sln_path + " [" + project_name + "] (" + config_name + ") "
    toolmsg(msg)
    DTE = win32com.client.Dispatch("VisualStudio.DTE.7.1")
    DTE.Solution.Open( sln_path )
    builder = DTE.Solution.SolutionBuild
    if prefs['clean']:
        builder.Clean(1)
    builder.BuildProject(config_name, project_name, 1)
    failed = builder.LastBuildInfo
    DTE.Quit()
    if failed > 0:
        raise BuildException, "In solution " + sln_path + ": " + str(failed) + " project(s) failed to compile."

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


def test_IS():
    "Test for InstallShield Developer 8. Raises exception if not found."
    toolmsg("Trying to create ISWiAutomation.ISWiProject object")
    win32com.client.Dispatch("ISWiAutomation.ISWiProject")
    
def build_IS(isv_file, config, release, properties):
    """
    Builds an InstallShield Developer 8 project.
    params
        isv_file : full path to the InstallShield project (.isv)
        config   : name of the configuration to be built
        release  : name of the build configuration (e.g.: "Release")
        properties : dictionary of properties to set for the project at build time
    """
    toolmsg("Building " + isv_file + " - " + config + " - " + release)
    ism_file = os.path.splitext(isv_file)[0] + ".ism"
    ISWiProject = win32com.client.Dispatch( "ISWiAutomation.ISWiProject" )
    ISWiProject.ImportProject(ism_file, isv_file)
    ISWiProject.CloseProject()
    
    ISWiProject.OpenProject(ism_file)
    for property in properties.keys():
        ISProperty = ISWiProject.ISWiProperties.Item(property)
        ISProperty.Value = properties[property]
        toolmsg("\tSet property " + ISProperty.Name + " = " + ISProperty.Value)
        
    ISConfig = ISWiProject.ISWiProductConfigs.Item(config)
    ISRelease = ISConfig.ISWiReleases.Item(release)
    ISRelease.Build()
    ISWiProject.CloseProject()
    
    if ISRelease.BuildWarningCount > 0:
        toolmsg("Warnings found (%d)! Check logfile for details." % (ISRelease.BuildWarningCount))
    if ISRelease.BuildErrorCount > 0:
        raise BuildException, "InstallShield error(s) occured"
        
