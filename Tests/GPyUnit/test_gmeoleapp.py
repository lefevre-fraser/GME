import unittest

class TestGMEOLEApp(unittest.TestCase):
    def test_Exit(self):
        import win32com.client
        gme = win32com.client.DispatchEx("GME.Application")
        gme.Exit()
        # under _DEBUG, GME.exe does not exist until Release()ed
        del(gme)

if __name__ == "__main__":
        unittest.main()
