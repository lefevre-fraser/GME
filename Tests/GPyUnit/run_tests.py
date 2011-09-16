import unittest

# it is also possible to run tests like this on Python 2.7:
# python -m unittest Regr.Mga.tc7
_tests = unittest.defaultTestLoader.loadTestsFromNames((
 'test_registrar',
 'GME_297.suite',
 'GME_310.suite',
 'Regr.Mga.tc1',
 'Regr.Mga.tc2',
 'Regr.Mga.tc3',
 'Regr.Mga.tc5',
 'Regr.Mga.tc6',
))

# For debugging
#import sys
#sys.stdin.readline()

if __name__=='__main__':
    import optparse
    parser = optparse.OptionParser()
    parser.add_option("-x", "--xml", action="store_true", dest="xml")
    parser.add_option("-v", action="store_true", dest="verbose")

    (options, args) = parser.parse_args()
    if options.xml:
        import os.path
        import xmlrunner
        with open("tests.xml", "w") as output:
            output.write("<testsuites>")
            for test in _tests:
                runner = xmlrunner.XMLTestRunner(output)
                runner.run(test)
            output.write("</testsuites>")
    else:
        runner = unittest.TextTestRunner(verbosity=2 if options.verbose else 1)
        runner.run(_tests)

