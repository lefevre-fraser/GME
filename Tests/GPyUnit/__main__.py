import GPyUnit
import unittest

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
            for test in GPyUnit._tests:
                runner = xmlrunner.XMLTestRunner(output)
                runner.run(test)
            output.write("</testsuites>")
    else:
        runner = unittest.TextTestRunner(verbosity=2 if options.verbose else 1)
        runner.run(GPyUnit._tests)

