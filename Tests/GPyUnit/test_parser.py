import unittest
import os

class TestParser(unittest.TestCase):
    def test_ParseMetaGME(self):
        testdir = os.path.dirname(os.path.abspath(__file__))
        inputfile = os.environ['GME_ROOT'] + r"\Paradigms\MetaGME\MetaGME-model.xme"
        import win32com.client
        xme = win32com.client.DispatchEx("Mga.MgaParser")
        (paradigm, parversion, parguid, basename, ver) = xme.GetXMLInfo(inputfile)
        mga = win32com.client.DispatchEx("Mga.MgaProject")

        mga.Create("MGA=tmp.mga", paradigm)
        xme.ParseProject(mga, inputfile)
        mga.Save()
        mga.Close()
        del(mga)
        del(xme)

if __name__ == "__main__":
        unittest.main()
