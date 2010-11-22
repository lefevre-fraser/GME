# tests for GME-311 and GME-297

import sys
import os.path
import unittest
import win32com.client

class TestRefportConnectionInvariantUnderMoves(unittest.TestCase):
    def __init__(self, input_file, fco_to_move, destination_model, name=None):
        unittest.TestCase.__init__(self, 'test')
        self.input_file = input_file
        self.fco_to_move = fco_to_move
        self.destination_model = destination_model
        name = name if name else os.path.splitext(self.input_file)[0]
        self.output_file = name + "-output.mga"
        self.correct_file = name + "-correct.mga"

    def test(self):
        '''
        Regression test: given self.input_file, move self.fco_to_move to self.destination_model. Then check self.output_file against self.correct_file
        '''
        # This script depends on late binding. win32com.client.dynamic.Dispatch forces late binding when creating an object,
        # but early-bound objects may be returned from function calls. Disable late binding completely.
        import win32com.client.gencache
        _savedGetClassForCLSID = win32com.client.gencache.GetClassForCLSID
        win32com.client.gencache.GetClassForCLSID = lambda x: None

        self.project = win32com.client.DispatchEx("Mga.MgaProject")
        self.project.Open("MGA=" + self.input_file)
        self.territory = self.project.BeginTransactionInNewTerr()

        fco_to_move = self.project.ObjectByPath(self.fco_to_move)
        OBJTYPE_FOLDER = 6
        if fco_to_move.ObjType == OBJTYPE_FOLDER:
            tomove = win32com.client.DispatchEx("Mga.MgaFolders")
        else:
            tomove = win32com.client.DispatchEx("Mga.MgaFCOs")
        tomove.Append(fco_to_move)

        destination = self.project.ObjectByPath(self.destination_model)
        if destination.ObjType == OBJTYPE_FOLDER:
            destination.MoveFolders(tomove, None)
        else:
            destination.MoveFCOs(tomove, None, None)

        self.project.CommitTransaction()
        self.project.Save("MGA=" + self.output_file)
        self.territory.Destroy()

        win32com.client.gencache.GetClassForCLSID = _savedGetClassForCLSID
        import mgadiff
        if not mgadiff.compare(self.correct_file, self.output_file):
            self.fail("Reference file '%s' does not match output '%s'" % (self.correct_file, self.output_file))
        print "Reference file '%s' matches output '%s'" % (self.correct_file, self.output_file)

def suite():
    suite = unittest.TestSuite()
    suite.addTest(TestRefportConnectionInvariantUnderMoves(input_file="test1.mga", fco_to_move="/Test1/Folder1/A/B", destination_model="/Test1/Folder2/C"))
    suite.addTest(TestRefportConnectionInvariantUnderMoves(input_file="test2.mga", fco_to_move="/Test2/Subtypes/A/BSubtypeRef", destination_model="/Test2/Destination/Destination"))
    suite.addTest(TestRefportConnectionInvariantUnderMoves(input_file="test1.mga", fco_to_move="/Test1/Folder1/A/RefB", destination_model="/Test1/Folder2/C", name="test3"))
    suite.addTest(TestRefportConnectionInvariantUnderMoves(input_file="test4.mga", fco_to_move="/Test4/Folder1/A/RefRefB", destination_model="/Test4/Folder2/C"))
    suite.addTest(TestRefportConnectionInvariantUnderMoves(input_file="test5.mga", fco_to_move="/Test4/Folder2", destination_model="/Test4/Folder3"))
    return suite

if __name__ == "__main__":
    runner = unittest.TextTestRunner()
    runner.run(suite())
