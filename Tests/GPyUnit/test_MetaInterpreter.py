import unittest
import os
import os.path
import GPyUnit.util
from GPyUnit.util import DispatchEx

_filedir = os.path.dirname(os.path.abspath(__file__))
def _adjacent_file(file):
    return os.path.join(_filedir, file)

class TestMetaInterpreter(unittest.TestCase):
    def test_AttributeOrdering(self):
        mga = GPyUnit.util.parse_xme(self.connstr)
        try:
            mga.Save()
            selectedobj = DispatchEx("Mga.MgaFCOs")
            launcher = DispatchEx("Mga.MgaLauncher")
            launcher.RunComponent("Mga.Interpreter.MetaInterpreter", mga, None, selectedobj, 128)
        finally:
            mga.Close()

        with open(os.path.join(self.outdir(), "MetaGME.xmp")) as xmp:
            lines = xmp.readlines()
            atomattributes = "IsAbstract InRootFolder GeneralPreferences DisplayedName IsTypeShown Icon IsNameEnabled PortIcon SubTypeIcon NamePosition InstanceIcon Decorator NameWrapNum IsHotspotEnabled IsResizable AutoRouterPref HelpURL IsGradientFillEnabled GradientFillColor GradientFillDirection IsShadowCastEnabled ShadowColor ShadowThickness ShadowDirection IsRoundRectangleEnabled RoundRectangleRadius"
            self.assertTrue(atomattributes in "".join(lines), filter(lambda x: '<atom name = "Atom"' in x, lines))
        
        metaproj = DispatchEx("Mga.MgaMetaProject")
        metaproj.Open("MGA=" + os.path.join(self.outdir(), "MetaGME.mta"))
        try:
            atomattrs = [attr.Name for attr in metaproj.RootFolder.DefinedFCOByName("Atom", True).Attributes]
            self.assertEqual(atomattrs, list(atomattributes.split()))
        finally:
            metaproj.Close()
        

    def tearDown(self):
        for file in ("MetaGME.xmp", "MetaGME.mta", "MetaGME.xmp.log"):
            if os.path.isfile(os.path.join(self.outdir(), file)):
                os.unlink(os.path.join(self.outdir(), file))
        registrar = DispatchEx("Mga.MgaRegistrar")
        registrar.RegisterParadigmFromData("XML=" + os.path.abspath(os.path.join(os.environ['GME_ROOT'], "Paradigms\\MetaGME\\MetaGME.xmp")), "MetaGME", 1)
    setUp = tearDown

    @property
    def connstr(self):
        return "MGA=" + _adjacent_file("MetaInterpretertest.mga")
    
    def outdir(self):
        return os.path.abspath(_adjacent_file('.'))

GPyUnit.util.MUGenerator(globals(), TestMetaInterpreter)
def _muoutdir(self):
    return os.path.abspath(os.getcwd())
try:
    TestMetaInterpreterMU.outdir = _muoutdir
except NameError:
    pass # MU isn't tested under x64

class TestCSharpDSMLGenerator(unittest.TestCase):
    def test_run(self):
        mga = GPyUnit.util.parse_xme(self.connstr)
        try:
            mga.Save()
            selectedobj = DispatchEx("Mga.MgaFCOs")
            launcher = DispatchEx("Mga.MgaLauncher")
            launcher.RunComponent("Mga.Interpreter.MetaInterpreter", mga, None, selectedobj, 128)
            launcher.RunComponent("Mga.Interpreter.CSharpDSMLGenerator", mga, None, selectedobj, 128)
        finally:
            mga.Close()
        self.assertTrue(os.path.isfile(os.path.join(self.outdir(), "ISIS.GME.Dsml.MetaGME.Classes.cs")))
        self.assertTrue(os.path.isfile(os.path.join(self.outdir(), "ISIS.GME.Dsml.MetaGME.dll")))

            
    def tearDown(self):
        for file in ("MetaGME.xmp", "MetaGME.mta", "MetaGME.xmp.log"):
            if os.path.isfile(os.path.join(self.outdir(), file)):
                os.unlink(os.path.join(self.outdir(), file))
        registrar = DispatchEx("Mga.MgaRegistrar")
        registrar.RegisterParadigmFromData("XML=" + os.path.abspath(os.path.join(os.environ['GME_ROOT'], "Paradigms\\MetaGME\\MetaGME.xmp")), "MetaGME", 1)
        for filename in ("AssemblySignature.snk", "ISIS.GME.Dsml.MetaGME.Classes.cs", "ISIS.GME.Dsml.MetaGME.dll", "ISIS.GME.Dsml.MetaGME.Interfaces.cs", "ISIS.GME.Dsml.MetaGME.xml", "ISIS.GME.Dsml.pdb"):
            path = os.path.join(self.outdir(), filename)
            if os.path.isfile(path):
                os.unlink(path)
    setUp = tearDown

    @property
    def connstr(self):
        return "MGA=" + _adjacent_file("MetaInterpretertest.mga")
    
    def outdir(self):
        return os.path.abspath(_adjacent_file('.'))

if __name__ == "__main__":
    unittest.main()
