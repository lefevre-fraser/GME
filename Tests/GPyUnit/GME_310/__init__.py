# tests for GME-310

import sys
import os.path
import unittest
import win32com.client

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
            return os.path.join(os.path.dirname(__file__), file)
        from GPyUnit import util
        util.register_xmp(_adjacent_file('GME310ModelRefportTest.xmp'))

        with util.disable_early_binding():
            self.project = win32com.client.DispatchEx("Mga.MgaProject")
            self.project.Open("MGA=" + _adjacent_file(self.input_file))
            self.territory = self.project.BeginTransactionInNewTerr()

            modelb = self.project.ObjectByPath(self.folder_to_copy)
            modelb.Name
            tomove = win32com.client.DispatchEx("Mga.MgaFolders")
            tomove.Append(modelb)
            #self.project.ObjectByPath(self.destination_folder).CopyFolders(tomove, None)
            self.project.RootFolder.CopyFolders(tomove, None)

            self.project.CommitTransaction()
            self.project.Save("MGA=" + _adjacent_file(self.output_file))
            self.territory.Destroy()
            self.project.Close()

        import GPyUnit.util.mgadiff as mgadiff
        if not mgadiff.compare(_adjacent_file(self.correct_file), _adjacent_file(self.output_file)):
            self.fail("Reference file '%s' does not match output '%s'" % (self.correct_file, self.output_file))
        #print "Reference file '%s' matches output '%s'" % (self.correct_file, self.output_file)

def suite():
    suite = unittest.TestSuite()
    suite.addTest(TestFolderCopy(input_file="test1.mga", folder_to_copy="/Test1", destination_folder=""))
    return suite

if __name__ == "__main__":
    runner = unittest.TextTestRunner()
    runner.run(suite())
