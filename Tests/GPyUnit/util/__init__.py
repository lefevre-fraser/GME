
import unittest

class disable_early_binding(object):
	def __enter__(self):
		import win32com.client.gencache
		self._savedGetClassForCLSID = win32com.client.gencache.GetClassForCLSID
		win32com.client.gencache.GetClassForCLSID = lambda x: None
		return self
	
	def __exit__(self, exc_type, exc_value, traceback):
		import win32com.client
		win32com.client.gencache.GetClassForCLSID = self._savedGetClassForCLSID

def dec_disable_early_binding(f):
    def ret(*args, **kwargs):
        with disable_early_binding():
            f(*args, **kwargs)
    # n.b. unittest reads __name__
    ret.__name__ = f.__name__
    return ret

def register_xmp(xmpfile):
    import os.path
    predef = { 'SF': os.path.join(os.environ['GME_ROOT'], "Paradigms", "SF", "SF.xmp"), 
    # FIXME: doesn't work with GME from installer
    'MetaGME': os.path.join(os.environ['GME_ROOT'], "Paradigms", "MetaGME", "Paradigm", "MetaGME.xmp") }
    if not os.path.isfile(xmpfile):
        xmpfile = predef[xmpfile]
    import gme
    gme.register_if_not_registered(xmpfile)

class MUTestMixin(unittest.TestCase): # need to inherit from TestCase so __mro__ works, since TestCase.__init__ doesn't call super().__init__
    def __init__(self, name, **kwds):
        super(MUTestMixin, self).__init__(name, **kwds)
        import os.path
        self.mgxdir = os.path.abspath(os.path.join(os.path.dirname(__file__), "MUTest"))

    def setUp(self):
        super(MUTestMixin, self).setUp()
        import os.path
        if os.path.isdir(self.mgxdir):
            import shutil
            assert len(self.mgxdir) > 10 # sanity check
            shutil.rmtree(self.mgxdir)
    
    @property
    def connstr(self):
        return "MGX=\"" + self.mgxdir + "\""
