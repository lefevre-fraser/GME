#!/usr/bin/python
#!/usr/bin/python
# Copyright (c) 2004 ISIS, Vanderbilt Univeristy 
#
# Author: Brian Williams
#
# command line args: 1. input.xme 2. output.mga 3. output.xme

import sys
import win32com.client
import pythoncom

try:
  project = win32com.client.DispatchEx("Mga.MgaProject")
  project.Create("MGA="+sys.argv[2], "MetaGME")
  parser = win32com.client.DispatchEx("Mga.MgaParser")
  parser.ParseProject(project, sys.argv[1])
  project.Save()
  dumper = win32com.client.DispatchEx("Mga.MgaDumper")
  dumper.DumpProject(project, sys.argv[3])
  project.Save()
  project.Close()
except:
  gme.CloseProject(0)
  exit(1)