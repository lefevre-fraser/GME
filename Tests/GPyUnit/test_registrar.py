import unittest

class TestRegistrar(unittest.TestCase):
	def test_GetAssociatedParadigmsDisp(self):
		import win32com.client
		x = win32com.client.DispatchEx("MGA.MgaRegistrar")
		self.assertEqual(list(x.GetAssociatedParadigmsDisp("MGA.Interpreter.MetaInterpreter", 1)), [u'MetaGME'])

#suite = (TestRegistrar(),)

if __name__ == "__main__":
        unittest.main()
