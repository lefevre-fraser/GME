#!/bin/python

from __future__ import with_statement

import re
import sys
import os.path
import win32com.client
import StringIO
import platform

# For py2exe support
# To generate the exe, be sure to rename or delete .../Python/lib/site-packages/win32com/gen_py
# See http://www.py2exe.org/index.cgi/UsingEnsureDispatch
if hasattr(win32com.client, "gencache") and win32com.client.gencache.is_readonly == True:
	#allow gencache to create the cached wrapper objects
	win32com.client.gencache.is_readonly = False
	# under p2exe the call in gencache to __init__() does not happen
	# so we use Rebuild() to force the creation of the gen_py folder
	try:
		saveout = sys.stdout
		try:
			sys.stdout = output = StringIO.StringIO()
			win32com.client.gencache.Rebuild()
		finally:
			sys.stdout = saveout
	except:
		print output.getvalue()
		raise

import subprocess
import itertools

# Elevation helpers
def execute_elevated(*args):
	# FIXME: support **kwargs
	from win32com.shell.shell import ShellExecuteEx
	from win32com.shell import shellcon
	import win32process, win32event
	import winxpgui
	import win32api
	import win32con
	try:
		hwnd = winxpgui.GetConsoleWindow()
	except winxpgui.error:
		hwnd = 0
	parameters = ""
	if not hasattr(sys, "frozen"):
		# Not running under py2exe exe
		parameters += "\"" + sys.argv[0] + "\" "
	parameters += " ".join(map(lambda x: "\"" + str(x) + "\"", args))
	print "Executing elevated with parameters " + parameters
	# TODO: capture output (maybe via named pipe)
	rc = ShellExecuteEx(hwnd=hwnd, fMask=shellcon.SEE_MASK_NOCLOSEPROCESS, lpVerb="runas", lpFile=sys.executable, 
		lpParameters=parameters, nShow=win32con.SW_SHOW)
	hproc = rc['hProcess']
	win32event.WaitForSingleObject(hproc, win32event.INFINITE)
	exit_code = win32process.GetExitCodeProcess(hproc)
	if exit_code:
		raise Exception("Error: subprocess failed (exit code %s)." % exit_code)

def is_elevated():
	import win32security
	import win32api
	hToken = win32security.OpenProcessToken(win32api.GetCurrentProcess(), win32security.TOKEN_QUERY)
	return win32security.GetTokenInformation(hToken, win32security.TokenElevation) != 0


def maybe_elevate():
	def decorator(func):
		if not hasattr(sys, "getwindowsversion") or sys.getwindowsversion()[0] < 6:
			wrap = func
		else:
			def wrap(*args, **kwargs):
				if not is_elevated():
					execute_elevated(func.__name__, *args, **kwargs)
				else:
					func(*args, **kwargs)
		setattr(sys.modules[__name__], func.__name__, wrap)
		return wrap
	return decorator

@maybe_elevate()
def elevated_check_call(*args):
	return subprocess.check_call(args)

# GME functions
def create_project(project, connection, paradigm):
	return project.Create(connection, paradigm)

# aka CreateMga.vbs
def xme2mga(xmefile, mgafile=None):
	if not mgafile:
		mgafile = os.path.splitext(xmefile)[0] + ".mga"
	with Project.open(xmefile, mgafile) as project:
		project.save(project.mgafile)
		return project.mgafile

def run_interpreter(interpreter, file, focusobj=None, selectedobj=None, param=0, mga_to_save=None):
	with Project.open(file, mga_to_save=mga_to_save) as project:
		project.run_interpreter(interpreter, focusobj, selectedobj, param)

# MGAUTILLib.regaccessmode_enum.REGACCESS_BOTH = 3
def get_paradigm_file(paradigm, regaccess=3):
	"Returns the .mta file for a given registered paradigm"
	registrar = win32com.client.DispatchEx("Mga.MgaRegistrar")
	guid = registrar.GetParadigmGUIDStringDisp(regaccess, paradigm)
	import uuid
	if platform.system() != 'Java':
		buf = buffer(uuid.UUID(guid).bytes_le, 0, 16)
	else:
		buf = str(uuid.UUID(guid).bytes_le[0:16])
	(connstr, guid) = registrar.QueryParadigm(paradigm, None, buf, regaccess)
	# >>> constr
	# "MGA=....mta"
	return connstr[4:]


def _associate(progid, paradigm, regaccess):
	registrar = win32com.client.DispatchEx("Mga.MgaRegistrar")
	registrar.Associate(progid, paradigm, regaccess)

@maybe_elevate()
def _associate_elevated(*args):
	_associate(*args)

def associate(progid, paradigm, regaccess=1):
	"Associate a component with a paradigm"
	regaccess = int(regaccess)
	if regaccess != 1:
		_associate_elevated(progid, paradigm, regaccess)
	else:
		_associate(progid, paradigm, regaccess)


def is_registered(paradigm):
	registrar = win32com.client.DispatchEx("Mga.MgaRegistrar")
	paradigms = []
	# REGACCESS_USER = 1
	paradigms.extend(registrar.GetParadigmsDisp(1))
	# REGACCESS_SYSTEM = 2
	paradigms.extend(registrar.GetParadigmsDisp(2))
	return filter(lambda p: p == paradigm, paradigms)

REGISTER = 128
DONT_REGISTER = 0
def register_if_not_registered(file):
	"Register an xme or mga if it has not already been registered"
	if os.path.splitext(file)[1] == ".xmp":
		if not is_registered(os.path.basename(os.path.splitext(file)[0])) or (platform.system() != 'Java' and not os.path.isfile(get_paradigm_file(os.path.splitext(os.path.basename(file))[0]))):
			regxmp(file)
		return
	
	# if we don't give GME an absolute path, it registers the mta with a relative path (which is bad)
	with Project.open(os.path.abspath(file), mga_to_save=True) as project:
		paradigm = project.project.RootFolder.Name
		if not is_registered(paradigm):
			project.run_interpreter("MGA.Interpreter.MetaInterpreter", param=REGISTER)
			print "Paradigm '%s' is now registered" % paradigm
		elif not os.path.isfile(get_paradigm_file(paradigm)):
			#FIXME: should we look for the .xmp?
			project.run_interpreter("MGA.Interpreter.MetaInterpreter", param=REGISTER)
			print "Paradigm '%s' had nonexistant .mta; it is now reregistered" % paradigm
		# TODO: can we check if it is up-to-date?
		# or os.path.getmtime(get_paradigm_file(paradigm)) < os.path.getmtime(file):
		else:
			print "Paradigm '%s' is already registered" % paradigm

def mga2xmp(mgafile, register=REGISTER):
	# if we don't give GME an absolute path, it registers the mta with a relative path (which is bad)
	run_interpreter("MGA.Interpreter.MetaInterpreter", os.path.abspath(mgafile), param=register, mga_to_save=True)

def xme2xmp(xmefile, register=REGISTER):
	mgafile = xme2mga(xmefile)
	mga2xmp(mgafile, register)
	return mgafile

def _regxmp(xmpfile, regaccess):
	REG_USER = 1
	REG_SYSTEM = 2
	REG_BOTH = 3
	registrar = win32com.client.DispatchEx("Mga.MgaRegistrar")
	registrar.RegisterParadigmFromData("XML=" + os.path.abspath(xmpfile), "", regaccess)

@maybe_elevate()
def _regxmp_elevated(xmpfile, regaccess):
	_regxmp(xmpfile, regaccess)

def regxmp(xmpfile, regaccess=1):
	regaccess = int(regaccess)
	if regaccess != 1:
		_regxmp_elevated(xmpfile, regaccess)
	else:
		_regxmp(xmpfile, regaccess)

def _reggmexmps(regaccess):
	regaccess = int(regaccess)
	for file in [ 'HFSM/HFSM.xmp', 'MetaGME/Paradigm/MetaGME.xmp', 'SF/SF.xmp', 'UML/UML.xmp' ]:
		regxmp(os.path.join(os.path.join(os.environ['GME_ROOT'], 'Paradigms'), file), regaccess)

@maybe_elevate()
def _reggmexmps_elevated(regaccess):
	_reggmexmps(regaccess)

def reggmexmps(regaccess=1):
	regaccess = int(regaccess)
	if regaccess != 1:
		_reggmexmps_elevated(regaccess)
	else:
		_reggmexmps(regaccess)

def mga2xme(mgafile, xmefile=None):
	if not xmefile:
		xmefile = os.path.splitext(mgafile)[0] + ".xme"

	with Project.open(mgafile) as project:
		project.save(xmefile)
	return xmefile

def register_component(file, warn_on_tlb_error=None):
# TODO: on Vista or 7 we need to start an elevated registrar
	registrar = win32com.client.DispatchEx("Mga.MgaRegistrar")
	# REGACCESS_BOTH	= 3,
	registrar.RegisterComponentLibrary(file, 3)


# UDM functions
def meta2uml(mgafile, umlfile=None):
	if not os.path.isfile(mgafile):
		raise Exception("'" + mgafile + "' not found")
	
	if not umlfile:
		umlfile = os.path.splitext(mgafile)[0] + "_uml.mga"
	subprocess.check_call(["MetaGME2UML.exe", mgafile, umlfile])

# aka CreateUdmXml.vbs
def mga2udmxml(mgafile):
	run_interpreter("MGA.Interpreter.UML2XML", mgafile, None, None, 128)

# GReAT functions
def RunGreatMasterInt(file):
	file = os.path.abspath(file)
	with Project.open(file) as project:
		project.run_interpreter("MGA.Interpreter.GReAT Master Interpreter", param=128)
# touch(1) the generated .udm file so incremental build works
		configurations = (cast(fco) for fco in project.project.RootFolder.children() if fco.kind() == "Configurations").next()
		configuration = (cast(fco) for fco in configurations.children() if fco.kind() == "Configuration").next()
		metainformation = (cast(fco) for fco in configuration.children() if fco.kind() == "MetaInformation").next()
		udmfile = os.path.dirname(file) + "/" + metainformation.AttributeByName("UdmProjectFile")
		mtime = os.stat(udmfile).st_mtime
	os.utime(file, (mtime, mtime))

# Explorer context menu
def context_menu_reg():
	"""Register explorer context menu options"""
	import _winreg
	if hasattr(sys, "frozen"):
		# Running under py2exe exe
		gmepydir = os.path.dirname(unicode(sys.executable, sys.getfilesystemencoding( )))
	else:
		gmepydir = os.path.dirname(__file__)
	# Windows won't let us start gme.py from the context menu, so use the exe
	gmepy = gmepydir + "\\gmepy.exe"

	mga = "mga"
	xme = "xme"
	xmp = "xmp"
	menus = [ (mga, "mga2xme"),
			(mga, "mga2xmp"),
			(mga, "mga2udmxml"),
			(xme, "xme2mga"),
			(xmp, "regxmp"),
			]
	regname = gmepydir + "\\gmepy_context_menu.reg"
	with open(regname, "w") as reg:
		reg.write("Windows Registry Editor Version 5.00\n")
		for p in menus:
			try:
				key = _winreg.OpenKey(_winreg.ConnectRegistry(None, _winreg.HKEY_CLASSES_ROOT), "."+p[0])
				n,v,t = _winreg.EnumValue(key, 0)
				ext = v
				_winreg.CloseKey(key)
			except WindowsError:
				ext = "."+p[0]
			str = """[HKEY_CLASSES_ROOT\{ext}\shell]

[HKEY_CLASSES_ROOT\{ext}\shell\{name}]

[HKEY_CLASSES_ROOT\{ext}\shell\{name}\command]
@="\\"{gmepy}\\" {name} \\\"%1\\\""

""".format(ext=ext, name=p[1], gmepy=gmepy.replace("\\", "\\\\"))
			reg.write(str)
	elevated_check_call("regedit", regname)

if platform.system() != 'Java':
	# GME Project functions
	import win32com.client.gencache
	# Generate .py's for GME Type Library
	# n.b. we don't use EnsureModule here because we don't properly version the typelib
	#   A change in the typelib may invalidate the cache, but gencache doesn't know it, e.g. GMESRC r947
	meta_module = win32com.client.gencache.MakeModuleForTypelib('{0ADEEC71-D83A-11D3-B36B-005004D38590}', 0, 1, 0)
	mga_module = win32com.client.gencache.MakeModuleForTypelib('{270B4F86-B17C-11D3-9AD1-00AA00B6FE26}', 0, 1, 0)

	gme_constants = getattr(meta_module, "constants")

	OBJTYPE_INTERFACE_MAP = {
		gme_constants.OBJTYPE_MODEL: "IMgaModel",
		# Seems IMgaAtom isn't generated because it defines no new methods
	#	2: "IMgaAtom",
		gme_constants.OBJTYPE_ATOM: "IMgaFCO",
		gme_constants.OBJTYPE_REFERENCE: "IMgaReference",
		gme_constants.OBJTYPE_CONNECTION: "IMgaConnection",
		gme_constants.OBJTYPE_SET: "IMgaSet",
		gme_constants.OBJTYPE_FOLDER: "IMgaFolder",
	#	gme_constants.OBJTYPE_ASPECT: "IMgaAspect",
	#	gme_constants.OBJTYPE_ROLE: "IMgaRole",
		gme_constants.OBJTYPE_ATTRIBUTE: "IMgaAttribute",
		gme_constants.OBJTYPE_PART: "IMgaPart",
	}

	def cast(fco):
		return win32com.client.CastTo(fco, OBJTYPE_INTERFACE_MAP.get(fco.ObjType))

	# KMS I'm not sure why gen_py lowercases these (for GME<VS2010). Create aliases:
	if mga_module.IMgaReference._prop_map_get_.has_key("referred"):
	    mga_module.IMgaReference._prop_map_get_["Referred"] = mga_module.IMgaReference._prop_map_get_["referred"]
	#mga_module.IMgaConnPoint._prop_map_get_["Target"] = mga_module.IMgaConnPoint._prop_map_get_["target"]
	# Make IMgaFolder behave more like IMgaFCO
	mga_module.IMgaFolder._prop_map_get_["Meta"] = mga_module.IMgaFolder._prop_map_get_["MetaFolder"]


	def monkeypatch_method(classes):
	    def decorator(func):
	    	for name in classes:
	        	setattr(getattr(mga_module, name), func.__name__, func)
	        return func
	    return decorator

	# ConnPoints([out, retval] IMgaConnPoints **pVal);
	@monkeypatch_method(["IMgaConnection"])
	def get_end(self, role):
		ends = filter(lambda cp: cp.ConnRole == role, self.ConnPoints)
		if ends:
			return ends[0].Target
		else:
			raise Exception(self.Name + " has no connection point " + role)

	@monkeypatch_method(itertools.chain(["IMgaFCO"], OBJTYPE_INTERFACE_MAP.itervalues()))
	def kind(self):
	    return self.Meta.Name

	OBJTYPE_MAP = {
		gme_constants.OBJTYPE_MODEL: "Model",
		gme_constants.OBJTYPE_ATOM: "Atom",
		gme_constants.OBJTYPE_REFERENCE: "Reference",
		gme_constants.OBJTYPE_CONNECTION: "Connection",
		gme_constants.OBJTYPE_SET: "Set",
		gme_constants.OBJTYPE_FOLDER: "Folder",
		gme_constants.OBJTYPE_ASPECT: "Aspect",
		gme_constants.OBJTYPE_ROLE: "Role",
		gme_constants.OBJTYPE_ATTRIBUTE: "Attribute",
		gme_constants.OBJTYPE_PART: "Part",
	}

	@monkeypatch_method(itertools.chain(["IMgaFCO"], OBJTYPE_INTERFACE_MAP.itervalues()))
	def mga_type(self):
		return OBJTYPE_MAP.get(self.ObjType)

	@monkeypatch_method(itertools.chain(["IMgaFCO"], OBJTYPE_INTERFACE_MAP.itervalues()))
	def parent(self):
		if self.mga_type() == "Folder":
			return self.ParentFolder
		parent = self.ParentFolder
		if not parent:
			parent = self.ParentModel
		return parent

	@monkeypatch_method(itertools.chain(["IMgaFCO"], OBJTYPE_INTERFACE_MAP.itervalues()))
	def parents(self):
		parents = []
		current = self
		while True:
			parent = current.parent()
			if not parent:
				return parents
			else:
				current = parent
				parents.append(parent)

	@monkeypatch_method(itertools.chain(["IMgaFCO"], OBJTYPE_INTERFACE_MAP.itervalues()))
	def in_library(self):
		return filter(lambda x: x.mga_type() == "Folder" and x.LibraryName != "", self.parents())

	@monkeypatch_method(["IMgaFolder"])
	def children(self):
		children = []
		children.extend(self.ChildFolders)
		children.extend(self.ChildFCOs)
		return children

	@monkeypatch_method(["IMgaModel"])
	def children(self):
		return self.ChildFCOs

	def is_container(fco):
		return fco.ObjType == gme_constants.OBJTYPE_MODEL or fco.ObjType == gme_constants.OBJTYPE_FOLDER
else:
	def cast(fco):
		return fco

import tempfile
class Project():
	def __init__(self, com_project):
		self.project = com_project

	def __enter__(self):
		self.begin_transaction()
		return self

	def __exit__(self, exc_type, exc_value, traceback):
		if self.project.ProjectStatus == 3 or self.project.ProjectStatus == 4:
			if exc_type:
				self.project.AbortTransaction()
			else:
				self.project.CommitTransaction()
			if self.territory:
				self.territory.Destroy()
				self.territory = None
		self.project.Close()

	def get_fco(self, path):
		path_a = path.split("/")
		current = self.project.RootFolder
		for name in path_a[0:-1]:
			containers = filter(is_container, current.children())
			matches = filter(lambda x: x.Name == name, containers)
			if matches:
				current = cast(matches[0])
			else:
				raise Exception("Cant find %s in path %s" % (name, path))
		matches = filter(lambda x: x.Name == path_a[-1], current.children())
		if matches:
			return cast(matches[0])
		else:
			raise Exception("Cant find %s in path %s" % (path_a[-1], path))

	def save(self, filename=None):
		if not filename:
			filename = self.file
		self.project.CommitTransaction()
		if self.territory:
			self.territory.Destroy()
			self.territory = None

		extension = os.path.splitext(filename)[1]
		if extension == ".mga":
			self.project.Save("MGA=" + filename)
		elif extension == ".xme":
			dumper = win32com.client.DispatchEx("Mga.MgaDumper")
			dumper.DumpProject(self.project, filename)
		else:
			raise Exception("Don't know how to save '%s'" % filename)
		self.territory = self.project.BeginTransactionInNewTerr()
	
	def begin_transaction(self):
		self.territory = self.project.BeginTransactionInNewTerr()

	def commit_transaction(self):
		self.project.CommitTransaction()
		if self.territory:
			self.territory.Destroy()
			self.territory = None
	
	def run_interpreter_raw(self, interpreter, focusobj=None, selectedobj=None, param=0):
		import ctypes
		import comtypes.client
		import comtypes.automation
		import _ctypes
		comtypes.client.GetModule(['{270B4F86-B17C-11D3-9AD1-00AA00B6FE26}', 1, 0]) # Mga Mga
		comtypes.client.GetModule(["{461F30AE-3BF0-11D4-B3F0-005004D38590}", 1, 0]) # MgaUtil
		#TODO: check for GME version compatibility
		#TODO: CreateMgaComponent supports IDispatch wrapper ComponentProxy. do the same here
		comp = comtypes.client.CreateObject(interpreter, interface=comtypes.gen.MGAUTILLib.IMgaComponentEx)
		if interpreter == "MGA.Interpreter.MetaInterpreter":
			# http://escher.isis.vanderbilt.edu/JIRA/browse/GME-252
			comp.AddRef()

		comp.InteractiveMode = False
		p = get_ctypes_dispatch_from_win32com(self.project)

		#TODO: convert and use focusobj and selectedobj
		fcos = comtypes.client.CreateObject("Mga.MgaFCOs")
		self.commit_transaction()
		try:
			# FIXME: does this leak p ?
			comp.InvokeEx(p.QueryInterface(comtypes.gen.MGALib.IMgaProject), None, fcos, 128)
		finally:
			self.begin_transaction()

	
	def run_interpreter(self, interpreter, focusobj=None, selectedobj=None, param=0):
		if not selectedobj:
			selectedobj=win32com.client.DispatchEx("Mga.MgaFCOs")
		try:
			self.run_interpreter_raw(interpreter, focusobj, selectedobj, param)
		except ImportError:
			print "Warning: no comtypes library. Running interpreter through MgaLauncher; interpreter return code will be lost"
			self.commit_transaction()
			try:
				launcher = win32com.client.DispatchEx("Mga.MgaLauncher")
				launcher.RunComponent(interpreter, self.project, focusobj, selectedobj, param)
			finally:
				self.begin_transaction()

	@staticmethod
	def create(mgafile, paradigm):
		project = win32com.client.DispatchEx("Mga.MgaProject")
		create_project(project, "MGA=" + mgafile, paradigm)
		p = Project(project)
		p.filename = mgafile
		p.mgafile = mgafile
		return p

	@staticmethod
	def open(file, mga_to_save=None):
		if not os.path.isfile(file):
			raise Exception("'" + file + "' not found")
		extension = os.path.splitext(file)[1]
		mga = None
		if extension == ".mga":
			mga = win32com.client.DispatchEx("Mga.MgaProject")
			mga.Open("MGA=" + file)
			mga_to_save = file
		elif extension == ".xme":
			xme = win32com.client.DispatchEx("Mga.MgaParser")
			(paradigm, parversion, parguid, basename, ver) = xme.GetXMLInfo(file)

			mga = win32com.client.DispatchEx("Mga.MgaProject")
			xme = win32com.client.DispatchEx("Mga.MgaParser")
			if mga_to_save == True:
				mga_to_save = os.path.splitext(file)[0] + ".mga"
			elif not mga_to_save:
				mga_to_save = tempfile.gettempdir() + "gmepy-%s.mga" % os.getpid()
			create_project(mga, "MGA=" + mga_to_save, paradigm)
			xme.ParseProject(mga, file)
		else:
			raise Exception("Don't know how to open '%s'" % file)
		p = Project(mga)
		p.filename = file
		p.mgafile = mga_to_save
		return p

def get_ctypes_dispatch_from_win32com(disp):
	# http://mail.python.org/pipermail/python-win32/2008-April/007302.html
	import win32com.client.dynamic
	import ctypes
	import comtypes
	disp = win32com.client.dynamic.DumbDispatch(disp)
	x = disp._oleobj_
	addr = int(repr(x).split()[-1][2:-1], 16)
	#print hex(addr)
	
	pnt = ctypes.POINTER(comtypes.automation.IDispatch)()
	ctypes.cast(ctypes.byref(pnt), ctypes.POINTER(ctypes.c_void_p))[0] = addr
	pnt.AddRef()
	return pnt


def print_paradigm(xmefile):
	"Print the input file and paradigm of a given xme"
	xme = win32com.client.DispatchEx("Mga.MgaParser")
	(paradigm, parversion, parguid, basename, ver) = xme.GetXMLInfo(xmefile)
	print xmefile
	print paradigm

import traceback
if __name__ == '__main__':
	try:
		if sys.argv[1] not in dir():
			gme_dict = sys.modules[__name__].__dict__
			names = []
			names.extend(gme_dict.keys())
			for name in filter(lambda name: type(gme_dict[name]) == type(print_paradigm), names):
				if gme_dict[name].__doc__:
					print name
					print "\t" + gme_dict[name].__doc__
			sys.exit(1)
		else:
			# TRY:
			# sys.modules[__name__].__getattribute__(sys.argv[1]).__call__(*sys.argv[2:])
			eval("%s(*sys.argv[2:])" % sys.argv[1])
	except:
		traceback.print_exc(file=sys.stderr)
		sys.stdin.readline()
		sys.exit(1)
