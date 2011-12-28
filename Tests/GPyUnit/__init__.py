from __future__ import with_statement

import unittest

import platform
if platform.system() == 'Java':
	import os
	import os.path
	import sys
	sys.path.append(os.path.join(os.environ['GME_ROOT'], 'SDK', 'Java'))
	sys.path.append(os.path.join(os.environ['GME_ROOT'], 'SDK', 'Java', 'gme.jar'))
	#sys.registry['java.library.path'] = sys.registry['java.library.path'] + r';C:\Users\ksmyth\git\GMESRC\SDK\Java\native\Jaut\Release'
	#print sys.registry['java.library.path']
	#import java.lang
	#java.lang.System.loadLibrary(r'C:\Users\ksmyth\git\GMESRC\SDK\Java\native\Jaut\Release\jaut.dll')
	import org.isis.jaut
	if not org.isis.jaut.Apartment.currentApartment():
		org.isis.jaut.Apartment.enter(0)

import GPyUnit.test_PIAs

# it is also possible to run tests like this on Python 2.7:
# python -m unittest GPyUnit.Regr.Mga.tc7
_tests = [
 'test_PIAs',
 'test_registrar',
 'test_gmeoleapp',
 'test_parser',
 'test_registry',
 'GME_297.suite',
 'GME_310.suite',
 'GME_371',
]

if platform.system() != 'Java':
    _tests = _tests + [
'Regr.Mga.tc1',
'Regr.Mga.tc2',
'Regr.Mga.tc3',
'Regr.Mga.tc5',
'Regr.Mga.tc6',
]

_tests = unittest.defaultTestLoader.loadTestsFromNames(['GPyUnit.' + test for test in _tests])

