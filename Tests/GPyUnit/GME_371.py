import unittest
import os

class TestParser(unittest.TestCase):
    def test_ParseMetaGME(self):
        testdir = os.path.dirname(os.path.abspath(__file__))
        inputfile = os.environ['GME_ROOT'] + r"\Paradigms\MetaGME\MetaGME-model.xme"
        from pythoncom import com_error
        import win32com.client
        xme = win32com.client.DispatchEx("Mga.MgaParser")
        (paradigm, parversion, parguid, basename, ver) = xme.GetXMLInfo(inputfile)
        mga = win32com.client.DispatchEx("Mga.MgaProject")

        mga.Create("MGA=tmp.mga", paradigm)
        terr = mga.BeginTransactionInNewTerr()
        # GME-371: this would crash
        self.assertRaises(com_error, xme.ParseProject, mga, inputfile)
        return
        mga.CommitTransaction()
        terr.Destroy()
        mga.Save()
        mga.Close()
        del(terr)
        del(mga)
        del(xme)

if __name__ == "__main__":
        unittest.main()
