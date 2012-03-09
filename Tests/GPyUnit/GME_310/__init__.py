# tests for GME-310
from __future__ import with_statement

import sys
import os.path
import unittest
from GPyUnit.util import DispatchEx

class TestFolderCopy(unittest.TestCase):
    def __init__(self, input_file, folder_to_copy, destination_folder, name=None, **kwds):
        super(TestFolderCopy, self).__init__('test', **kwds)
        self.input_file = input_file
        self.folder_to_copy = folder_to_copy
        self.destination_folder = destination_folder
        name = name if name else os.path.splitext(self.input_file)[0]
        self._testMethodDoc = name
        self.output_file = name + "-output.mga"
        self.correct_file = name + "-correct.mga"

    def test(self):
        """
        Regression test: given self.input_file, move self.folder_to_copy to self.destination_folder. Then check self.output_file against self.correct_file
        """
        def _adjacent_file(file):
            import os.path
            return os.path.join(os.path.dirname(os.path.abspath(__file__)), file)
        from GPyUnit import util
        util.register_xmp(_adjacent_file('GME310ModelRefportTest.xmp'))

        with util.disable_early_binding():
            self.project = DispatchEx("Mga.MgaProject")
            self.project.Open("MGA=" + _adjacent_file(self.input_file))
            self.territory = self.project.BeginTransactionInNewTerr()

            modelb = self.project.ObjectByPath(self.folder_to_copy)
            modelb.Name
            tomove = DispatchEx("Mga.MgaFolders")
            tomove.Append(modelb)
            #self.project.ObjectByPath(self.destination_folder).CopyFolders(tomove, None)
            self.project.RootFolder.CopyFolderDisp(modelb)

            self.project.CommitTransaction()
            self.project.Save("MGA=" + _adjacent_file(self.output_file))
            self.territory.Destroy()
            self.project.Close()

        import GPyUnit.util.mgadiff as mgadiff
        if not mgadiff.compare(_adjacent_file(self.correct_file), _adjacent_file(self.output_file)):
            self.fail("Reference file '%s' does not match output '%s'" % (self.correct_file, self.output_file))
        #print "Reference file '%s' matches output '%s'" % (self.correct_file, self.output_file)

class TestRefportAPI(unittest.TestCase):
    def __init__(self, *kargs, **kwds):
        super(TestRefportAPI, self).__init__(*kargs, **kwds)

    def test(self):
        def _adjacent_file(file):
            import os.path
            return os.path.join(os.path.dirname(os.path.abspath(__file__)), file)
        from GPyUnit import util
        util.register_xmp(_adjacent_file('GME310ModelRefportTest.xmp'))

        with util.disable_early_binding():
            self.project = DispatchEx("Mga.MgaProject")
            self.project.Open("MGA=" + _adjacent_file("test1.mga"))
            self.territory = self.project.BeginTransactionInNewTerr()

            a = self.project.ObjectByPath("/Test1/Folder1/A")
            b = self.project.ObjectByPath("/Test1/Folder1/A/B")
            kindAtom = self.project.ObjectByPath("/Test1/Folder1/A/B/KindAtom")
            self.assertTrue(kindAtom)
            bref = self.project.ObjectByPath("/Test1/Folder1/A/BRef")
            brefref = self.project.ObjectByPath("/Test1/Folder1/A/BRefRef")
            kindConnection = [c for c in a.ChildFCOs if c.Name == "KindConnection"][0]
            c = a.CreateSimpleConnDisp(kindConnection.MetaRole, kindAtom, kindAtom, None, None)
            c = a.CreateSimpleConnDisp(kindConnection.MetaRole, kindAtom, kindAtom, bref, brefref)

            self.project.CommitTransaction()
            self.project.Save("MGA=" + _adjacent_file("TestRefportAPI.mga"))
            self.territory.Destroy()
            self.project.Close()

def suite():
    suite = unittest.TestSuite()
    suite.addTest(TestFolderCopy(input_file="test1.mga", folder_to_copy="/Test1", destination_folder=""))
    suite.addTest(TestRefportAPI("test"))
    return suite

if __name__ == "__main__":
    runner = unittest.TextTestRunner()
    runner.run(suite())
