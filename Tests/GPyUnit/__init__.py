import unittest

import GPyUnit.Regr.Mga.tc1

# it is also possible to run tests like this on Python 2.7:
# python -m unittest GPyUnit.Regr.Mga.tc7
_tests = unittest.defaultTestLoader.loadTestsFromNames(
[ 'GPyUnit.' + test for test in (
 'test_PIAs',
 'test_registrar',
 'test_gmeoleapp',
 'test_parser',
 'GME_297.suite',
 'GME_310.suite',
 'GME_371',
 'Regr.Mga.tc1',
 'Regr.Mga.tc2',
 'Regr.Mga.tc3',
 'Regr.Mga.tc5',
 'Regr.Mga.tc6',
)])

