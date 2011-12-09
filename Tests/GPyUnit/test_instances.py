import unittest
import os
import win32com.client
import GPyUnit.util
from GPyUnit.util import dec_disable_early_binding

def _adjacent_file(file):
    import os.path
    return os.path.join(os.path.dirname(os.path.abspath(__file__)), file)

class TestInstances(unittest.TestCase):
    def __init__(self, name, **kwds):
        super(TestInstances, self).__init__(name, **kwds)

    def tearDown(self):
        if self.project:
            self.project.Close(True)

    @property
    def connstr(self):
        return "MGA=" + _adjacent_file("tmp.mga")
    
    @dec_disable_early_binding
    def test_CreateInstances(self):
        self.project = GPyUnit.util.parse_xme(self.connstr)
        self.project.BeginTransactionInNewTerr()
        for i in range(3): # exponential!
            for model in self.project.RootFolder.ChildFCOs:
                self.project.RootFolder.DeriveRootObject(model, True)
        self.project.CommitTransaction()

GPyUnit.util.MUGenerator(globals(), TestInstances)
