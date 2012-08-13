import unittest
import os
import GPyUnit.util
from GPyUnit.util import DispatchEx

def _adjacent_file(file):
    import os.path
    return os.path.join(os.path.dirname(os.path.abspath(__file__)), file)

class TestParser(unittest.TestCase):
    def test_ParseMetaGME(self):
        mga = GPyUnit.util.parse_xme(self.connstr)
        mga.Save()
        mga.Close()
        if type(self) == TestParser:
            self.assertTrue(os.path.isfile(_adjacent_file("parsertest.mga")))
    
    def test_ParseInTx(self):
        project = GPyUnit.util.DispatchEx("Mga.MgaProject")
        project.Create(self.connstr, "MetaGME")
        project.BeginTransactionInNewTerr()
        try:
            mga = GPyUnit.util.parse_xme(self.connstr, project=project)
        except Exception, e:
            self.assertTrue(str(e).find("already in transaction") != -1)
        project.Close(True)
    
    @property
    def connstr(self):
        return "MGA=" + _adjacent_file("parsertest.mga")

    def test_GetXMLParadigm(self):
        parser = DispatchEx("Mga.MgaParser")
        paradigm = parser.GetXMLParadigm(os.environ['GME_ROOT'] + r"\Paradigms\MetaGME\MetaGME-model.xme")
        assert paradigm == "MetaGME"
       
    def test_GetXMLInfo(self):
        parser = DispatchEx("Mga.MgaParser")
        xme = os.environ['GME_ROOT'] + r"\Paradigms\MetaGME\MetaGME-model.xme"
        (paradigm, parversion, parguid, basename, ver) = parser.GetXMLInfo(xme)
        assert paradigm == "MetaGME"
    
GPyUnit.util.MUGenerator(globals(), TestParser)

if __name__ == "__main__":
        unittest.main()
