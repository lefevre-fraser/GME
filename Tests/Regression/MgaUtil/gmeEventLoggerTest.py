#!/usr/bin/python
# Copyright (c) 2004 ISIS, Vanderbilt Univeristy 
#
# Author: Brian Williams
#
# command line arg: 1. userid this script will run under (e.g. "BrianW.ISIS")

import os
import sys
import win32com.client
import pythoncom

#try:
EventLogger = win32com.client.DispatchEx("Mga.MgaEventLogger")
EventLogger.StartLogging()
EventLogger.LogEvent("Python Test Script")
EventLogger.StopLogging()
EventLogger.StartLogging()
EventLogger.EmergencyEvent()
chdir("C:/Documents and Settings/"+sys.argv[1]+"Application Data/GME")
#except:
 # exit(1)