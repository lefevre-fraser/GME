import unittest
import win32com.client
import win32ui
import pythoncom
import os
import utils.Builder
bd = utils.Builder


class TestCase8( unittest.TestCase ):
	"""
	avoid if possible the overriding of __init__, yet if you override use the following form:
	def __init__(self, methodName='runTest'):
		unittest.TestCase.__init__(self, methodName)
	"""

	def setUp( self ):		## hook method
		pass

	def tearDown( self ):		## hook method
		self.project.Close( 0 )
		pass

	def findInProj( self, project, obj_name = "", obj_kind = ""):

		# create a filter
		filter = project.CreateFilter()
		
		# use Name filter
		filter.Name = obj_name
		filter.Kind = obj_kind

		try:
			some_fcos = project.AllFCOs( filter )
			if some_fcos.Count > 0:
				return some_fcos.Item( 1 )
			else:
				print "findInProj >> Object not found : name = '" + obj_name + "' kind = '" + obj_kind + "'"
				assert 0
		except:
			print "findInProj >> Exception : name = '" + obj_name + "' kind = '" + obj_kind + "'"
			assert 0

		pass

	def populate8A(self, p):
		fff = bd.newFolder( p, p.RootFolder, 'TOSFolder')
		fff.Name = 'NewTOSFolder'
		
		md = bd.newObjInFold( p, fff, 'module')
		md.Name = 'Newmodule'
		
		st = bd.new( p, md, 'State')
		st.Name = 'NewState'
		
	def testA( self ):
		"""    testA
			
			testing methods of IMgaFCO
				Constraints([in] VARIANT_BOOL includemeta, [out, retval] IMgaConstraints **pVal);
				AddConstraint([in] IMgaConstraint *constraint);
				DefineConstraint([in] BSTR name, [in] long mask, [in] BSTR expr, [out] IMgaConstraint **nconstraint);
			and methods of IMgaObject
				Check
		"""

		mganame = "_tc8_A_gr.mga"

		# create the project with the needed kinds
		project = bd.creaP( mganame, "GRATISII")
		if not project:
			self.fail("Create failed")
		try:
			self.populate8A( project)
		except:
			bd.saveP( project)
			raise
		bd.saveP( project)
		
                        
		# open the created project
		self.project = project
		try:
			project.Open( "MGA=" + mganame )
		except:
			project.Close(0)
			raise
			
		terr = project.CreateTerritory( None, None, None)
			
		trans = project.BeginTransaction( terr)
		
		to_find = "Newmodule"
		obj = self.findInProj( project, to_find)
		
		try:
			nnnname = obj.Name
		except:
			print "Caught 1"
			assert 0

		print 'a1'
		expr = "let modules = project.allInstancesOf( module ) in modules->select( n | n.name.trim() = name )->size <= 1"
		print 'a2'
		newconstraint = obj.DefineConstraint( "new_constraint_defined", 0, expr)
		
		print 'a3'
		obj.AddConstraint( newconstraint )
		print 'a4'
		
		obj.Check()
		print 'a5'
		obj.CheckTree()
		print 'a6'
		
		# commit trans
		project.CommitTransaction()
		print 'a7'
		
		project.Save()
		project.Close(0)
		
		pass

	def populate8B(self, p):
		fff = bd.newFolder( p, p.RootFolder, 'TOSFolder')
		fff.Name = 'NewTOSFolder'
		
		cnf = bd.newObjInFold( p, fff, 'configuration')
		cnf.Name = 'NewconfigurationB'
		
		cnS = bd.subtypeInFold( p, fff, cnf)
		cnS.Name = 'NewconfigurationS'
		
		cnI = bd.instantiateInFold( p, fff, cnf)
		cnI.Name = 'NewconfigurationI'
		

	def testB( self ):

		"""    testB
			test methods of IMgaFCO
				DerivedObjects
				DerivedFrom
				IsInstance
				Type
				BaseType
				ArcheType
				IsPrimaryDerived
		"""
		
		mganame = "_tc8_B_gr.mga"
		# create the project with the needed kinds
		project = bd.creaP( mganame, "GRATISII")
		if not project:
			self.fail("Create failed")
		try:
			self.populate8B( project)
		except:
			bd.saveP( project)
			raise
		bd.saveP( project)
		
                        
		# open the created project
		self.project = project
		try:
			project.Open( "MGA=" + mganame )
		except:
			project.Close(0)
			raise


		terr = project.CreateTerritory( None, None, None)
		
		trans = project.BeginTransaction( terr)
		
		to_find = "NewconfigurationB"
		obj = self.findInProj( project, to_find)
		
		ders = obj.DerivedObjects
		for i in range( 1, ders.Count + 1):
			one_der = ders.Item( i )
			assert obj == one_der.DerivedFrom
			
			if one_der.IsInstance:
				inst = one_der
				base = one_der.Type
				assert inst.Name == "NewconfigurationI"
				assert base.Name == "NewconfigurationB"
				assert base == inst.ArcheType
				assert inst.IsPrimaryDerived
			else:
				subt = one_der
				base = one_der.BaseType
				assert subt.Name == "NewconfigurationS"
				assert base.Name == "NewconfigurationB"
				assert base == subt.ArcheType
				assert subt.IsPrimaryDerived

		# commit trans
		project.CommitTransaction()
		
		project.Save()
		project.Close(0)

		
		pass

	def populate8C(self, p):
		fff = bd.newFolder( p, p.RootFolder, 'TOSFolder')
		fff.Name = 'NewTOSFolder'
		
		int = bd.newObjInFold( p, fff, 'interface')
		int.Name = 'NewinterfaceB'
		
		pps = bd.new( p, int, 'PreprocessorSet')
		pps.Name = 'NewPreprocessorSet'
		
		sta = bd.new( p, int, 'State')
		sta.Name = 'NewStateB'
		
		eve = bd.new( p, int, 'event')
		eve.Name = 'Newevent'
		
		# subtype int 
		inS = bd.subtypeInFold( p, fff, int)
		inS.Name = 'NewinterfaceS'

		# rename its child
		inS.ChildFCO('NewStateB').Name = 'NewStateS'
		
		# instantiate int
		inI = bd.instantiateInFold( p, fff, int)
		inI.Name = 'NewinterfaceI'
		
		# rename its child
		inI.ChildFCO('NewStateB').Name = 'NewStateI'
		
		# subtype inS (the subtype of int)
		inSS = bd.subtypeInFold( p, fff, inS)
		inSS.Name = 'NewinterfaceSS'

		# rename its child
		inSS.ChildFCO('NewStateS').Name = 'NewStateSS'
		
	def testC( self ):
		"""    testC
			test methods of IMgaFCO
				DerivedFrom
				BaseType
				ArcheType
				IsPrimaryDerived
			
			test objects which are derived along with their parents (not on their own) -> these are the nonprimaryderived ones
			test subtypes of subtypes
		"""
		
		mganame = "_tc8_C_gr.mga"
		# create the project with the needed kinds
		project = bd.creaP( mganame, "GRATISII")
		if not project:
			self.fail("Create failed")
		try:
			self.populate8C( project)
		except:
			bd.saveP( project)
			raise
		bd.saveP( project)
		
                        
		# open the created project
		self.project = project
		try:
			project.Open( "MGA=" + mganame )
		except:
			project.Close(0)
			raise

						
		terr = project.CreateTerritory( None, None, None)
		
		trans = project.BeginTransaction( terr)
		
		to_find = "NewStateB" 		# not a primary derived obj (derived along with a Newinterface)
		statB = self.findInProj( project, to_find)
		
		to_find = "NewStateI"
		statI = self.findInProj( project, to_find)
		to_find = "NewStateS"
		statS = self.findInProj( project, to_find)
		
		assert not statI.IsPrimaryDerived
		assert statI.Type == statB
		
		assert not statS.IsPrimaryDerived
		assert statS.BaseType == statB
		
		to_find = "NewinterfaceB"
		arch = self.findInProj( project, to_find)
		
		to_find = "NewinterfaceS" 	# a subtype of "arch"
		subt = self.findInProj( project, to_find)
		
		to_find = "NewinterfaceSS"	# a subtype of "subt"
		subt_two = self.findInProj( project, to_find)
		
		assert subt_two.BaseType == subt
		assert subt_two.DerivedFrom == subt
		assert subt.BaseType == arch
		assert subt.DerivedFrom == arch
		
		assert subt_two.ArcheType == arch
		assert subt.ArcheType == arch
		
		# commit trans
		project.CommitTransaction()
		
		project.Save()
		project.Close(0)
		
		pass

	def populate8D(self, p):
		fff = bd.newFolder( p, p.RootFolder, 'TOSFolder')
		fff.Name = 'NewTOSFolder'
		
		md = bd.newObjInFold( p, fff, 'module')
		md.Name = 'Newmodule'
		
		tr = bd.new( p, md, 'Transition')
		tr.Name = 'NewTransition'
		
		# instantiate md
		mdI = bd.instantiateInFold( p, fff, md)
		mdI.Name = 'Newmodule_in'
		
		# subtype md
		mdS = bd.subtypeInFold( p, fff, md)
		mdS.Name = 'Newmodule_st'
		
		# create a new child in mdS (a subtype of md)
		pps = bd.new( p, mdS, 'PreprocessorSet')
		
		# instantiate mdS
		mdSI = bd.instantiateInFold( p, fff, mdS)
		mdSI.Name = 'Newmodule_st_in'
		

	def testD( self ):
		"""    testD
			test instances of subtypes
		"""
		
		mganame = "_tc8_D_gr.mga"
		# create the project with the needed kinds
		project = bd.creaP( mganame, "GRATISII")
		if not project:
			self.fail("Create failed")
		try:
			self.populate8D( project)
		except:
			bd.saveP( project)
			raise
		bd.saveP( project)
		
                        
		# open the created project
		self.project = project
		try:
			project.Open( "MGA=" + mganame )
		except:
			project.Close(0)
			raise

						
		terr = project.CreateTerritory( None, None, None)
		
		trans = project.BeginTransaction( terr)
		
		to_find = "Newmodule"
		modB = self.findInProj( project, to_find)

		to_find = "Newmodule_st"			# subtype of modB
		modS = self.findInProj( project, to_find)
		
		to_find = "Newmodule_st_in"			# instance of the modS subtype
		modIofS = self.findInProj( project, to_find)
		
		assert modS.IsPrimaryDerived
		assert modIofS.IsPrimaryDerived
		
		assert modIofS.IsInstance
		
		assert modS.BaseType == modB
		assert modIofS.Type == modS			# RESU: modIofS (instance of subtype) is derived from modB according to the tests
		
		assert modS.DerivedFrom == modB
		assert modIofS.DerivedFrom == modS		# RESU: see above
		
		assert modS.ArcheType == modB
		assert modIofS.ArcheType == modS		# archetype of modIofS is the subtype # RESU: see above
		
		# commit trans
		project.CommitTransaction()
		
		project.Save()
		project.Close(0)

		
		pass

	def populate8E(self, p):
		fff = bd.newFolder( p, p.RootFolder, 'TOSFolder')
		fff.Name = 'NewTOSFolder'
		
		cnf = bd.newObjInFold( p, fff, 'configuration')
		cnf.Name = 'NewconfigurationB'
		
		sta = bd.new( p, cnf, 'State')
		sta.Name = 'NewStateB'
		sta.SetBoolAttrByNameDisp( 'IsInitial', True)
		
		# subtype cnf
		cnS = bd.subtypeInFold( p, fff, cnf)
		cnS.Name = 'NewconfigurationS'
		
		# rename its child
		staS = cnS.ChildFCO('NewStateB')
		staS.Name = 'NewStateS'

		# set its attribute to a different value from its inherited
		# thus, this attribute will be detached from the archetype's attr
		staS.SetBoolAttrByNameDisp( 'IsInitial', False)

	def testE( self ):
		"""    testE
			open a project where the subtype has been detached manually already
			modify attribute (when available) and test whether the modification is 
			propagated down the hierarchy (the subtype is detached already)
		"""
		
		mganame = "_tc8_E_gr.mga"
		# create the project with the needed kinds
		project = bd.creaP( mganame, "GRATISII")
		if not project:
			self.fail("Create failed")
		try:
			self.populate8E( project)
		except:
			bd.saveP( project)
			raise
		bd.saveP( project)
		
                        
		# open the created project
		self.project = project
		try:
			project.Open( "MGA=" + mganame )
		except:
			project.Close(0)
			raise

		
		terr = project.CreateTerritory( None, None, None)
		
		trans = project.BeginTransaction( terr)
		
		to_find = "NewStateB"
		statB = self.findInProj( project, to_find)
		
		to_find = "NewStateS"
		statS = self.findInProj( project, to_find)
		
		# inquiring the "IsInitial" attribute of the two objects
		statB_bval = statB.GetBoolAttrByNameDisp( "IsInitial" )
		statS_bval = statS.GetBoolAttrByNameDisp( "IsInitial" )
		
		assert statB_bval
		assert not statS_bval
		
		# modify attribute and test whether the modification is propagated down the hierarchy
		# really is not a modification
		statB.SetBoolAttrByNameDisp( "IsInitial", True )
		
		# is propagated down?
		statS_bval = statS.GetBoolAttrByNameDisp( "IsInitial" )
		assert not statS_bval
		
		# commit trans
		project.CommitTransaction()
		
		project.Save()
		project.Close(0)

		pass

	def populate8F(self, p):
		fff = bd.newFolder( p, p.RootFolder, 'TOSFolder')
		fff.Name = 'NewTOSFolder'
		
		cnf = bd.newObjInFold( p, fff, 'configuration')
		cnf.Name = 'Newconfiguration'
		
		staB = bd.new( p, cnf, 'State')
		staB.Name = 'NewStateB'
		
		# subtype staB
		staS = bd.subtype( p, cnf, staB)
		staS.Name = 'NewStateS'

	def testF( self ):
		"""    testF
			test methods of IMgaFCO
				DetachFromArcheType()
			
			detach a subtype programatically and 
			modify attribute (when available) and test whether the modification is 
			propagated down the hierarchy (the subtype is detached already)
			
		[ helpstring("method AttachToArcheType")] 
					HRESULT AttachToArcheType([in] IMgaFCO *newtype, [in] VARIANT_BOOL instance);
		[ helpstring("method DetachFromArcheType")] 
					HRESULT DetachFromArcheType();
		"""
		
		mganame = "_tc8_F_gr.mga"
		# create the project with the needed kinds
		project = bd.creaP( mganame, "GRATISII")
		if not project:
			self.fail("Create failed")
		try:
			self.populate8F( project)
		except:
			bd.saveP( project)
			raise
		bd.saveP( project)
		
                        
		# open the created project
		self.project = project
		try:
			project.Open( "MGA=" + mganame )
		except:
			project.Close(0)
			raise

		
		terr = project.CreateTerritory( None, None, None)
		
		trans = project.BeginTransaction( terr)
		
		to_find = "NewStateB"
		statB = self.findInProj( project, to_find)
		
		to_find = "NewStateS"
		statS = self.findInProj( project, to_find)
		
		# inquiring the "IsInitial" attribute of the two objects
		statB_bval = statB.GetBoolAttrByNameDisp( "IsInitial" )
		statS_bval = statS.GetBoolAttrByNameDisp( "IsInitial" )
		
		assert not statB_bval
		assert not statS_bval
		
		# detach the subtype
		statS.DetachFromArcheType()
		
		# modify attribute and test whether the modification is propagated down the hierarchy
		statB.SetBoolAttrByNameDisp( "IsInitial", True )
		
		# is propagated down?
		statS_bval = statS.GetBoolAttrByNameDisp( "IsInitial" )
		assert not statS_bval
		
		# commit trans
		project.CommitTransaction()
		
		project.Save()
		project.Close(0)
		
		pass

	def populate8G(self, p):
		fff = bd.newFolder( p, p.RootFolder, 'TOSFolder')
		fff.Name = 'NewTOSFolder'
		
		cnf = bd.newObjInFold( p, fff, 'configuration')
		cnf.Name = 'Newconfiguration'
		
		staB = bd.new( p, cnf, 'State')
		staB.Name = 'NewStateB'
		
		# subtype staB
		staS = bd.subtype( p, cnf, staB)
		staS.Name = 'NewStateS'

		# instantiate staB
		staI = bd.instantiate( p, cnf, staB)
		staI.Name = 'NewStateI'

	def testG( self ):
		"""    testG
			test methods of IMgaFCO
				DetachFromArcheType
				AttachToArcheType
		"""
		
		mganame = "_tc8_G_gr.mga"
		# create the project with the needed kinds
		project = bd.creaP( mganame, "GRATISII")
		if not project:
			self.fail("Create failed")
		try:
			self.populate8G( project)
		except:
			bd.saveP( project)
			raise
		bd.saveP( project)
		
                        
		# open the created project
		self.project = project
		try:
			project.Open( "MGA=" + mganame )
		except:
			project.Close(0)
			raise

					
		terr = project.CreateTerritory( None, None, None)
		
		trans = project.BeginTransaction( terr)
		
		to_find = "NewStateB"
		statB = self.findInProj( project, to_find)
		
		to_find = "NewStateS"
		statS = self.findInProj( project, to_find)

		to_find = "NewStateI"
		statI = self.findInProj( project, to_find)
		
		# inquiring the "IsInitial" attribute of the two objects
		statB_bval = statB.GetBoolAttrByNameDisp( "IsInitial" )
		statS_bval = statS.GetBoolAttrByNameDisp( "IsInitial" )
		statI_bval = statI.GetBoolAttrByNameDisp( "IsInitial" )
		
		assert not statB_bval
		assert not statS_bval
		assert not statI_bval
		
		# detach the subtype and instance
		statS.DetachFromArcheType()
		statI.DetachFromArcheType()
		
		# modify attribute when available and test whether the modification is propagated down the hierarchy
		statB.SetBoolAttrByNameDisp( "IsInitial", True )
		
		# is propagated down? It should not
		statS_bval = statS.GetBoolAttrByNameDisp( "IsInitial" )
		statI_bval = statI.GetBoolAttrByNameDisp( "IsInitial" )
		assert not statS_bval
		assert not statI_bval
		
		# attach again
		statS.AttachToArcheType( statB, False)		# isinstance: false
		statI.AttachToArcheType( statB, True)		# isinstance: true
		
		# modify attribute and test ...
		# really is not a modification
		statB.SetBoolAttrByNameDisp( "IsInitial", True )
		
		# is propagated down? It should
		statS_bval = statS.GetBoolAttrByNameDisp( "IsInitial" )
		statI_bval = statI.GetBoolAttrByNameDisp( "IsInitial" )
		assert statS_bval
		assert statI_bval
		
		# commit trans
		project.CommitTransaction()
		
		project.Save()
		project.Close(0)
		
		pass

"""
	Let's produce the test suites
"""
# 1st way
def suites():
	suite = unittest.makeSuite(TestCase8,'test')
	return suite

# 2nd way
def suites2():
	tc = TestCase8()
	#all = tc.my_suite()
	#return all

# 3rd way
def suites3():
	suite = unittest.TestSuite()
	suite.addTest( TestCase8( "testA"))
	#suite.addTest( TestCase8( "testB"))
	#suite.addTest( TestCase8( "testC"))
	return suite

########
# main
########
if __name__ == "__main__":
	print "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	print "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	print "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	print "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	print "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	print "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ TEST BEGINS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	print "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	print "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	print "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	print "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	print "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	
	######## 1st way
	unittest.main()

	######## 2nd way
	# unittest.main(defaultTest='TestCase8')
	
	######## 3rd way
	# all = suites3()
	# runner = unittest.TextTestRunner()
	# runner.run( all )
