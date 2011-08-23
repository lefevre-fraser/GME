
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
    ret.__name__ = f.__name__
    return ret

def register_xmp(xmpfile):
    import os.path
    predef = { 'SF': os.path.join(os.environ['GME_ROOT'], "Paradigms", "SF", "SF.xmp"), 
    'MetaGME': os.path.join(os.environ['GME_ROOT'], "Paradigms", "MetaGME", "Paradigm", "MetaGME.xmp") }
    if not os.path.isfile(xmpfile):
        xmpfile = predef[xmpfile]
    import gme
    gme.register_if_not_registered(xmpfile)
