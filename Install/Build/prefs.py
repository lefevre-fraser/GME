#!/usr/bin/python
#
# Copyright (c) 2006 ISIS, Vanderbilt Univeristy 
#
# Author: Peter Volgyesi (peter.volgyesi@vanderbilt.edu)
#
"""GME Build System - preferences module"""

import time

#
# Preferences & default values (used by other modules)
#
prefs = {
	"clean" : False,
	"verbose" : False,
	"release" : False,
	"version_major" : time.localtime()[0] % 10,
	"version_minor" : time.localtime()[1],
	"version_patch" : time.localtime()[2]
	}