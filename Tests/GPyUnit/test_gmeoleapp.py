from __future__ import with_statement

import unittest
from GPyUnit.util import DispatchEx

class TestGMEOLEApp(unittest.TestCase):
    def test_Exit(self):
        import win32com.client
        gme = DispatchEx("GME.Application")
        gme.Version
        gme.Exit()
        # under _DEBUG, GME.exe does not exit until Release()ed
        del(gme)
    
    def test_PIAs(self):
        import os.path
        self.assertTrue(os.path.isfile(r"c:\Windows\assembly\GAC_MSIL\GME\1.0.0.0__f240a760fe751c2e\GME.dll"))

    def test_Console(self):
        import win32com.client

        registrar = DispatchEx("Mga.MgaRegistrar")
        registrar.SetScriptEngineDisp(1, "Python.AXScript.2")
        
        def _adjacent_file(file):
            import os.path
            return os.path.join(os.path.dirname(os.path.abspath(__file__)), file)
        self.gme = DispatchEx("GME.Application")
        self.gme.Version
        console = filter(lambda p: p.Name == "Console", self.gme.Panels)[0]
        intf = console.Interface
        # 'intf.Contents =' fails because python calls Invoke(wFlags=3) instead of DISPATCH_PROPERTYPUT=4
        intf.SetContents('magicstring')
        self.assertEqual(intf.Contents, 'magicstring')
        
        pythoncode = 'gme.ConsoleMessage("magic2string", 0)\n'
        with open(_adjacent_file('_console_utf16.py'), 'wb') as file:
           file.write('\xFF\xFE')
           file.write(unicode(pythoncode).encode('utf-16le'))
        intf.LoadScript(_adjacent_file('_console_utf16.py'))
        intf.RunLoadedScript()
        self.assertTrue(intf.Contents.find('magic2string') != -1, 'Console contents: "' + intf.Contents + '"')
        
        with open(_adjacent_file('_console_ansi.py'), 'wb') as file:
            file.write(pythoncode.replace('magic2string', 'magic3string'))
        intf.LoadScript(_adjacent_file('_console_ansi.py'))
        intf.RunLoadedScript()
        self.assertTrue(intf.Contents.find('magic3string') != -1, 'Console contents: "' + intf.Contents + '"')
        
    def setUp(self):
        self.gme = None

    def tearDown(self):
        if self.gme:
            self.gme.Exit()
            del(self.gme)

if __name__ == "__main__":
        unittest.main()
