import unittest
import os
import GPyUnit.util

def _adjacent_file(file):
    import os.path
    return os.path.join(os.path.dirname(os.path.abspath(__file__)), file)

class TestParser(unittest.TestCase):
    def test_ParseMetaGME(self):
        testdir = os.path.dirname(os.path.abspath(__file__))
        inputfile = os.environ['GME_ROOT'] + r"\Paradigms\MetaGME\MetaGME-model.xme"
        import win32com.client
        xme = win32com.client.DispatchEx("Mga.MgaParser")
        (paradigm, parversion, parguid, basename, ver) = xme.GetXMLInfo(inputfile)
        mga = win32com.client.DispatchEx("Mga.MgaProject")

        mga.Create(self.connstr, paradigm)
        xme.ParseProject(mga, inputfile)
        mga.Save()
        mga.Close()
        del(mga)
        del(xme)
    
    @property
    def connstr(self):
        return "MGA=" + _adjacent_file("tmp.mga")

GPyUnit.util.MUGenerator(globals(), TestParser)

if __name__ == "__main__":
        unittest.main()
