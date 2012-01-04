import unittest
import os
from GPyUnit.util import DispatchEx

class TestParser(unittest.TestCase):
    def test_ParseMetaGME(self):
        testdir = os.path.dirname(os.path.abspath(__file__))
        inputfile = os.environ['GME_ROOT'] + r"\Paradigms\MetaGME\MetaGME-model.xme"
        xme = DispatchEx("Mga.MgaParser")
        (paradigm, parversion, parguid, basename, ver) = xme.GetXMLInfo(inputfile)
        mga = DispatchEx("Mga.MgaProject")

        mga.Create("MGA=tmp.mga", paradigm)
        terr = mga.BeginTransactionInNewTerr()
        import platform
        if platform.system() != 'Java':
            from pythoncom import com_error
            exc_type = com_error
        else:
            import org.isis.jaut.InvokeException
            exc_type = org.isis.jaut.InvokeException
        # GME-371: this would crash
        self.assertRaises(exc_type, xme.ParseProject, mga, inputfile)
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
