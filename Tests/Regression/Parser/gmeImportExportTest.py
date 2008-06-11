#!/usr/bin/python
# Copyright (c) 2004 ISIS, Vanderbilt Univeristy 
#
# Author: Brian Williams
#
# command line args: 1. input.xme 2. output.mga 3. output.xme

import sys
import win32com.client
try:
  gme = win32com.client.Dispatch("GME.Application")
  gme.Visible = 0
  gme.CreateProject("MetaGME","MGA="+sys.argv[2])
  
  gme.ImportProject(sys.argv[1])
  gme.SaveProject()
  gme.ExportProject(sys.argv[3])
  gme.SaveProject()
  gme.CloseProject(0)
except:
  gme.CloseProject(0)
  exit(1)