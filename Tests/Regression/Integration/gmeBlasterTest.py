#!/usr/bin/python
# Copyright (c) 2004 ISIS, Vanderbilt Univeristy 
#
# Author: Brian Williams
#
# command line args: 1. paradigm 2. output.mga 

import sys
import win32com.client
try:
  gme = win32com.client.Dispatch("GME.Application")
  gme.Visible = 0
  gme.CreateProject(sys.argv[1],"MGA="+sys.argv[2])
  
  gme.SaveProject()
  gme.RunComponent("MGA.Interpreter.Blaster-i")
  gme.SaveProject()
  gme.CloseProject(0)
except:
  gme.CloseProject(0)
  exit(1)