import unittest
import win32com.client
import win32ui
import pythoncom
import os
import utils.Builder
bd = utils.Builder


class TestCase7( unittest.TestCase ):
        """
        avoid if possible the overriding of __init__, yet if you override use the following form:
        def __init__(self, methodName='runTest'):
                unittest.TestCase.__init__(self, methodName)
        """

        def setUp( self ):              ## hook method
                pass

        def tearDown( self ):           ## hook method
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

	def populate7A(self, p):
		pri = bd.newObjInFold( p, p.RootFolder, 'Primitive')
		pri.Name = 'NewPrimitive'
		
		i1 = bd.new( p, pri, 'InputParameters')
		i1.Name = 'NewInputParameters'
		
		i2 = bd.new( p, pri, 'InputSignals')
		i2.Name = 'NewInputSignals'
		
		i3 = bd.new( p, pri, 'OutputParameters')
		i3.Name = 'NewOutputParameters'
		
		i4 = bd.new( p, pri, 'OutputParameters')
		i4.Name = 'NewOutputParameters'
		
		i5 = bd.new( p, pri, 'OutputSignals')
		i5.Name = 'NewOutputSignals'
		
		i6 = bd.new( p, pri, 'Parameters')
		i6.Name = 'NewParameters'
		

        def testA( self ):
                """    testA
                        test properties of IMgaFCO such as
                                Meta
                                MetaRole
                                ParentModel
                                ParentFolder
                """
                
		mganame = "_tc7_A_sf.mga"

		# create the project with the needed kinds
		project = bd.creaP( mganame, "SF")
		if not project:
			self.fail("Create failed")
		try:
			self.populate7A( project)
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

                to_find = "id-0066-00000002"
                fco1 = project.GetFCOByID( to_find )

                to_find = "id-0066-00000003"
                fco3 = project.GetFCOByID( to_find )
                to_find = "id-0066-00000004"
                fco4 = project.GetFCOByID( to_find )
                
                assert fco3.Meta == fco4.Meta
                metafco3 = fco3.Meta            # this line causes win32 exception
                assert metafco3.Name == "OutputParam"
                
                assert fco3.MetaRole == fco4.MetaRole
                metarole3 = fco3.MetaRole       # this line causes win32 exception
                assert metarole3.Name == "OutputParameters"
                
                mod = fco3.ParentModel
                par = mod.ParentFolder
                
                assert par == project.RootFolder

                # commit trans
                project.CommitTransaction()
                

                project.Save()
                project.Close(0)

                pass

	def populate7B(self, p):
		folder1 = bd.newFolder( p, p.RootFolder, 'Folder')
		folder1.Name = 'NewFolder'
		
		folder2 = bd.newFolder( p, folder1, 'Folder')
		folder2.Name = 'NewFolder'

		folder3 = bd.newFolder( p, folder2, 'Folder')
		folder3.Name = 'NewFolder'

		c1 = bd.newObjInFold( p, folder3, 'Compound')
		c1.Name = 'NewCompound'
		
		for i in range(0,7):
		    ci = bd.newObjInFold( p, folder3, 'Compound')
		    ci.Name = 'NewCmp'
		
		c2 = bd.new( p, c1, 'CompoundParts')
		c2.Name = 'NewCompoundParts'
		
		c3 = bd.new( p, c2, 'CompoundParts')
		c3.Name = 'NewCompoundParts'
		
		c4 = bd.new( p, c3, 'CompoundParts')
		c4.Name = 'NewCompoundParts'
		
		c5 = bd.new( p, c4, 'CompoundParts')
		c5.Name = 'NewCompoundParts'
		
		c6 = bd.new( p, c5, 'CompoundParts')
		c6.Name = 'NewCompoundParts'
		
		c7 = bd.new( p, c5, 'PrimitiveParts')
		c7.Name = 'NewPrimitiveParts'
		
		
        def testB( self ):
                """    testB
                        test properties of IMgaFCO such as
                                ParentModel
                                ParentFolder
                """

		mganame = "_tc7_B_sf.mga"

		# create the project with the needed kinds
		project = bd.creaP( mganame, "SF")
		if not project:
			self.fail("Create failed")
		try:
			self.populate7B( project)
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

                to_find = "id-0065-0000000d"
                fco3 = project.GetFCOByID( to_find )
                to_find = "id-0065-0000000e"
                fco4 = project.GetFCOByID( to_find )
                
                last_parent = fco3;
                mod = fco3.ParentModel
                count_model_parents = 0
                while mod != None:
                        count_model_parents = 1 + count_model_parents
                        last_parent = mod
                        mod = mod.ParentModel
                
                assert count_model_parents == 5

                fol = last_parent.ParentFolder
                count_folder_parents = 0
                while fol != None:
                        count_folder_parents = 1 + count_folder_parents
                        last_parent = fol
                        fol = fol.ParentFolder
                
                assert count_folder_parents == 4

                assert last_parent == project.RootFolder

                # commit trans
                project.CommitTransaction()
                
                project.Save()
                project.Close(0)

                pass

	def populate7C(self, p):
		folder1 = bd.newFolder( p, p.RootFolder, 'Folder')
		folder1.Name = 'Samples'
		
		folder2 = bd.newFolder( p, p.RootFolder, 'Folder')
		folder2.Name = 'Universe'

		c1 = bd.newObjInFold( p, folder1, 'Compound')
		c1.Name = 'NewCompound'
		
		c2 = bd.newObjInFold( p, folder1, 'Primitive')
		c2.Name = 'NewPrimitive'
		
		c3 = bd.new( p, c1, 'CompoundParts')
		c3.Name = 'NewCompoundParts'
		
		i1 = bd.new( p, c3, 'InputParameters')
		i1.Name = 'NewInputParameters'
		
		i2 = bd.new( p, c3, 'InputSignals')
		i2.Name = 'NewInputSignals'
		
		c4 = bd.newObjInFold( p, folder2, 'Compound')
		c4.Name = 'NewCompound'
		
		c5 = bd.newObjInFold( p, folder2, 'Primitive')
		c5.Name = 'NewPrimitive'
		
		c6 = bd.new( p, c4, 'CompoundParts')
		c6.Name = 'NewCompoundParts'
		
		c7 = bd.new( p, c4, 'PrimitiveParts')
		c7.Name = 'NewPrimitiveParts'
		
		i3 = bd.new( p, c6, 'InputParameters')
		i3.Name = 'NewInputParameters'
		
		i4 = bd.new( p, c6, 'InputParameters')
		i4.Name = 'NewInputParameters'
		
		i5 = bd.new( p, c6, 'InputSignals')
		i5.Name = 'NewInputSignals'
		
		i6 = bd.new( p, c6, 'InputSignals')
		i6.Name = 'NewInputSignals'
		
		
		i7 = bd.new( p, c7, 'InputParameters')
		i7.Name = 'NewInputParameters'
		
		i8 = bd.new( p, c7, 'InputParameters')
		i8.Name = 'NewInputParameters'
		
		i9 = bd.new( p, c7, 'InputSignals')
		i9.Name = 'NewInputSignals'
		
		ia = bd.new( p, c7, 'InputSignals')
		ia.Name = 'NewInputSignals'		

		ib = bd.new( p, c5, 'InputParameters')
		ib.Name = 'NewInputParameters'
		
		ic = bd.new( p, c5, 'InputSignals')
		ic.Name = 'NewInputSignals'
		
		id = bd.new( p, c5, 'OutputParameters')
		id.Name = 'NewOutputParameters'
		
                
        def testC( self ):
                """    testC
                        test properties of IMgaFCO such as
                                Part
                                Parts
                                PartByMetaPart
                """
                
		mganame = "_tc7_C_sf.mga"

		# create the project with the needed kinds
		project = bd.creaP( mganame, "SF")
		if not project:
			self.fail("Create failed")
		try:
			self.populate7C( project)
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

                to_find = "id-0066-00000001"
                inpar = project.GetFCOByID( to_find )   # inputparameter

                to_find = "id-0066-00000002"
                insig = project.GetFCOByID( to_find )   # inputsignal
                
                to_find = "id-0065-00000003"
                cp = project.GetFCOByID( to_find )      # newcompoundparts
                
                to_find = "id-0065-00000004"
                pp = project.GetFCOByID( to_find )      # newprimitiveparts
                
                aspect_1 = cp.Meta.AspectByName("ParameterAspect")
                aspect_2 = cp.Meta.AspectByName("SignalFlowAspect")
                
                #
                # tests for insig "InputSignal"
                #
                part = insig.Part( aspect_1)
                assert part == None

                part = insig.Part( aspect_2)
                assert part != None
                assert part in insig.Parts
                metapart = part.Meta
                another_part = insig.PartByMetaPart( metapart)
                assert another_part in insig.Parts
                assert another_part == part
                assert another_part.FCO.Name == part.FCO.Name
                
                #
                # tests for inpar "InputParameter"
                #
                part = inpar.Part( aspect_2)
                assert part == None
                
                part = inpar.Part( aspect_1)
                assert part != None

                assert part in inpar.Parts

                metapart = part.Meta
                another_part = inpar.PartByMetaPart( metapart)
                assert another_part in inpar.Parts
                assert another_part == part
                assert another_part.FCO.Name == part.FCO.Name
                
                # commit trans
                project.CommitTransaction()
                

                project.Save()
                project.Close(0)

                pass

	def populate7D(self, p):
		c1 = bd.newObjInFold( p, p.RootFolder, 'Compound')
		c1.Name = 'NewCompound'
		
		p1 = bd.new( p, c1, 'PrimitiveParts')
		p1.Name = 'NewPrimitiveParts'
		
		ip1 = bd.new( p, p1, 'InputParameters')
		ip1.Name = 'NewInputParameters'
		

        def testD( self ):
                """    testD
                        test properties of IMgaFCO such as
                                AttributeByName -get/put
                                StrAttrByName   -get/put
                                IntAttrByName   -get/put
                                
                        first inquire the original values, then modify them
                        inquire once again, revert back to the original ones 
                        then modify and inquire once again using the variant put/getter AttributeByName
                """

		mganame = "_tc7_D_sf.mga"

		# create the project with the needed kinds
		project = bd.creaP( mganame, "SF")
		if not project:
			self.fail("Create failed")
		try:
			self.populate7D( project)
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

                to_find = "id-0066-00000001"
                ip = project.GetFCOByID( to_find )      # inputparameter
                
                to_find = "id-0065-00000002"
                pp = project.GetFCOByID( to_find )      # newprimitiveparts
                
                aspect_1 = pp.Meta.AspectByName("ParameterAspect")
                aspect_2 = pp.Meta.AspectByName("SignalFlowAspect")
                
                assert 1 == ip.GetIntAttrByNameDisp( "Size" )              # default value
                assert "Integer" == ip.GetStrAttrByNameDisp( "DataType" )  # default value
                
                # modify attributes
                ip.SetIntAttrByNameDisp( "Size", 2)
                ip.SetStrAttrByNameDisp( "DataType", "Double")
                
                assert 2 == ip.GetIntAttrByNameDisp( "Size" )
                assert "Double" == ip.GetStrAttrByNameDisp( "DataType" )
                
                # revert changes
                ip.SetIntAttrByNameDisp( "Size", 1)
                ip.SetStrAttrByNameDisp( "DataType", "Integer")

                assert 10 == pp.GetIntAttrByNameDisp( "Priority" )
                assert "" == pp.GetStrAttrByNameDisp( "Script" )
                assert "IFALL" == pp.GetStrAttrByNameDisp( "Firing" )
                
                # modify
                pp.SetIntAttrByNameDisp( "Priority", 5 )
                d_s = "int dummy_script()\n{ return 1; }"
                pp.SetStrAttrByNameDisp( "Script", d_s)
                pp.SetStrAttrByNameDisp( "Firing", "IFANY" )
                
                assert 5 == pp.GetIntAttrByNameDisp( "Priority" )
                assert d_s == pp.GetStrAttrByNameDisp( "Script" )
                assert "IFANY" == pp.GetStrAttrByNameDisp( "Firing" )

                # test whether VARIANTS are returning back the values
                pr = 0 # integer
                pr = pp.GetAttributeByNameDisp( "Priority")
                assert pr == 5
                
                scr = ""
                scr = pp.GetAttributeByNameDisp( "Script" )
                assert scr == d_s

                fir = "IFALL"
                fir = pp.GetAttributeByNameDisp( "Firing" )
                assert "IFANY" == fir

                # revert changes using AttributeByName (test whether VARIANTS are interpreted all right)
                old_pr_val = 10
                pp.SetAttributeByNameDisp( "Priority", old_pr_val )

                old_scr_val = ""
                pp.SetAttributeByNameDisp( "Script", old_scr_val )
                
                old_fir_val = "IFALL"
                pp.SetAttributeByNameDisp( "Firing", old_fir_val )                     
                
                # the values must be the original ones
                assert 10 == pp.GetIntAttrByNameDisp( "Priority")
                assert "" == pp.GetStrAttrByNameDisp( "Script")
                assert "IFALL" == pp.GetStrAttrByNameDisp( "Firing")

                # commit trans
                project.CommitTransaction()
                
                project.Save()
                project.Close(0)

                pass

	def populate7E(self, p):
		f = bd.newFolder( p, p.RootFolder, 'TOSFolder')
		f.Name = 'NewTOSFolder'
		
		cnf = bd.newObjInFold( p, f, 'configuration')
		cnf.Name = 'Newconfiguration'

		int = bd.newObjInFold( p, f, 'interface')
		int.Name = 'Newinterface'
		
		mod = bd.newObjInFold( p, f, 'module')
		mod.Name = 'Newmodule'
		
		e = bd.new( p, cnf, 'FunctionByInterface')
		e.Name = 'NewFunctionByInterface'
		
		e = bd.new( p, cnf, 'PreprocessorSet')
		e.Name = 'NewPreprocessorSet'
		
		e = bd.new( p, cnf, 'State')
		e.Name = 'NewState'
		
		e = bd.new( p, cnf, 'Transition')
		e.Name = 'NewTransition'
		
		e = bd.new( p, cnf, 'configuration_ref')
		e.Name = 'Newconfiguration_ref'
		
		e = bd.new( p, cnf, 'interface_ref')
		e.Name = 'Newinterface_ref'
		
		e = bd.new( p, cnf, 'module_ref')
		e.Name = 'Newmodule_ref'
		
		e = bd.new( p, int, 'State')
		e.Name = 'NewState'
		
		e = bd.new( p, int, 'Transition')
		e.Name = 'NewTransition'
		
		e = bd.new( p, int, 'event')
		e.Name = 'Newevent'
		
		e = bd.new( p, mod, 'FunctionByInterface')
		e.Name = 'NewFunctionByInterface'
		
		f = bd.new( p, e, 'Argument')
		f.Name = 'NewArgument'
		
		e = bd.new( p, mod, 'State')
		e.Name = 'NewState'
		
		e = bd.new( p, mod, 'task')
		e.Name = 'Newtask'
		

        def testE( self ):
                """    testE
                        test properties of IMgaFCO such as
                                AttributeByName -get/put
                                BoolAttrByName  -get/put
                                ClearAttrByName
                                
                        first inquire the original values, then modify them
                        inquire once again, revert back to the original ones 
                        then modify and inquire once again using the variant put/getter AttributeByName
                        and then use ClearAttrByName to revert back to the "unset state"
                """

		mganame = "_tc7_E_gr.mga"

		# create the project with the needed kinds
		project = bd.creaP( mganame, "GRATISII")
		if not project:
			self.fail("Create failed")
		try:
			self.populate7E( project)
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

                to_find = "NewState"
                ns = self.findInProj( project, to_find)

                try:
                        nnnname = ns.Name
                except:
                        print "Caught 1"
                        assert 0
                
                assert False == ns.BoolAttrByName( "IsInitial" )
                try:
                        i = ns.IntAttrByName ( "IsInitial" )    # try if it works
                except:
                        pass
                        #print "Inquiring a bool attribute with IntAttributeByName failed, that should be OK"
                
                
                to_find = "Newevent"
                ne = self.findInProj( project, to_find)

                try:
                        nnnname = ne.Name
                except:
                        print "Caught 2"
                        assert 0
                

                assert False == ne.BoolAttrByName( "Default" )
                assert False == ne.BoolAttrByName( "Async" )
                
                # modify attributes
                ns.SetBoolAttrByNameDisp( "IsInitial", True)
                ne.SetBoolAttrByNameDisp( "Default", True)
                ne.SetBoolAttrByNameDisp( "Async", True)
                
                assert True == ns.BoolAttrByName( "IsInitial" )
                try:
                        assert -1   == ns.GetIntAttrByNameDisp ( "IsInitial" )         # try if it works
                except:
                        pass
                        #print "Inquiring a bool attribute with IntAttributeByName failed, that should be OK"

                assert True == ne.BoolAttrByName( "Default" )
                assert True == ne.BoolAttrByName( "Async" )
                
                # revert changes
                ns.SetBoolAttrByNameDisp( "IsInitial", False)
                ne.SetBoolAttrByNameDisp( "Default", False)
                ne.SetBoolAttrByNameDisp( "Async", False)

                assert False == ns.BoolAttrByName( "IsInitial" )
                assert False == ne.BoolAttrByName( "Default" )
                assert False == ne.BoolAttrByName( "Async" )
                
                
                # modify values using AttributeByName (test whether VARIANTS are interpreted all right)
                
                ns.SetAttributeByNameDisp( "IsInitial", True )
                ne.SetAttributeByNameDisp( "Default", True )
                ne.SetAttributeByNameDisp( "Async", True )


                # test whether VARIANTS are returning back good boolean values

                bVal1 = False       # bool init, so that VARIANTs are converted to bool
                bVal2 = False
                bVal3 = False
                bVal1 = ns.GetAttributeByNameDisp( "IsInitial")
                bVal2 = ne.GetAttributeByNameDisp( "Default")
                bVal3 = ne.GetAttributeByNameDisp( "Async")

                assert bVal1 == True
                assert bVal2 == True
                assert bVal3 == True
                
                # reset the attribute to its default value and to its unset state
                ns.ClearAttrByName( "IsInitial" )
                ne.ClearAttrByName( "Default" )
                ne.ClearAttrByName( "Async" )

                # check once more the values
                assert False == ns.GetBoolAttrByNameDisp( "IsInitial" )
                assert False == ne.GetBoolAttrByNameDisp( "Default" )
                assert False == ne.GetBoolAttrByNameDisp( "Async" )

                # commit trans
                project.CommitTransaction()
                
                project.Save()
                project.Close(0)

                pass

	def populate7F(self, p):
		f = bd.newObjInFold( p, p.RootFolder, 'NewModel')
		f.Name = 'NewNewModel'
		
		a = bd.new( p, f, 'NewAtom')
		a.Name = 'NewNewAtom'

        def testF( self ):
                """    testF
                        test properties of IMgaFCO such as
                                AttributeByName -get/put
                                FloatAttrByName -get/put
                                ClearAttrByName
                                
                        test put/get methods on double type FieldAttributes on a custom (FloatAttr) paradigm
                """

		mganame = "_tc7_F_fl.mga"

		# create the project with the needed kinds
		project = bd.creaP( mganame, "FloatAttr")
		if not project:
			self.fail("Create failed")
		try:
			self.populate7F( project)
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

                to_find = "NewNewAtom"
                at = self.findInProj( project, to_find)

                try:
                        nnnname = at.Name
                except:
                        print "Caught 1"
                        assert 0
                
                
                assert 0.000 == at.GetFloatAttrByNameDisp( "Float1" )          # default value
                assert 1.001 == at.GetFloatAttrByNameDisp( "Float2" )          # default value
                
                at.SetFloatAttrByNameDisp( "Float1", 2.002 )
                at.SetFloatAttrByNameDisp( "Float2", 3.003 )
                
                assert 2.002 == at.GetFloatAttrByNameDisp( "Float1" )
                assert 3.003 == at.GetFloatAttrByNameDisp( "Float2" )

                at.SetAttributeByNameDisp( "Float1", -4.004 )
                at.SetAttributeByNameDisp( "Float2", -5.005 )
                
                # test whether VARIANTS are returning back good values
                assert -4.004 == at.GetAttributeByNameDisp( "Float1" )
                assert -5.005 == at.GetAttributeByNameDisp( "Float2" )

                # reset the attribute to its default value and to its unset state
                at.ClearAttrByName( "Float1" )
                at.ClearAttrByName( "Float2" )

                assert 0.000 == at.GetFloatAttrByNameDisp( "Float1" )          # default value
                assert 1.001 == at.GetFloatAttrByNameDisp( "Float2" )          # default value

                # commit trans
                project.CommitTransaction()
                
                project.Save()
                project.Close(0)

                pass

	def populate7G(self, p):
		f = bd.newFolder( p, p.RootFolder, 'TOSFolder')
		f.Name = 'NewTOSFolder'
		
		cnf = bd.newObjInFold( p, f, 'configuration')
		cnf.Name = 'Newconfiguration'

		int = bd.newObjInFold( p, f, 'interface')
		int.Name = 'Newinterface'
		
		e = bd.new( p, cnf, 'State')
		e.Name = 'NewState'
		
		e = bd.new( p, int, 'event')
		e.Name = 'Newevent'
		

        def testG( self ):
                """    testG

                        test properties of IMgaFCO such as
                                Attributes([out, retval] IMgaAttributes **pVal)
                                Attribute([in] IMgaMetaAttribute *meta, [out, retval] IMgaAttribute **pVal)
                                
                        first inquire the attributes an fco may have based on its meta (using IMgaFCO.Meta.Attributes)
                        then check if these attributes are the expected ones
                        then inquire the value of the attributes using IMgaFCO.Attribute
                        then check the properties of the IMgaAttribute returned like
                                Status
                                Value
                                OrigValue
                                HasChanged
                                Meta
                """

		mganame = "_tc7_G_gr.mga"

		# create the project with the needed kinds
		project = bd.creaP( mganame, "GRATISII")
		if not project:
			self.fail("Create failed")
		try:
			self.populate7G( project)
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

                # a "State" object (empty)
                to_find = "NewState"
                ns = self.findInProj( project, to_find)
                
                # attributes of NewState
                attr_list = ns.Attributes
                
                # attributes defined for NewState in its meta (State) -> this returns all possible attributes of FCO (in contrast to DefinedAttributes which returns those which are locally defined in the FCO itself (between the begin-end xml tags of the fco) [see a tipical .xmp file])
                #attr_meta_list_unknown = list( ns.Meta.Attributes )    -> converting to a list will loose the information what kind of pointer is there
                #attr_meta_list = attr_meta_list_unknown # this is still a IUnknown collection
                attr_meta_list = ns.Meta.Attributes

                assert attr_list.Count == attr_meta_list.Count
                assert attr_list.Count == 1

                names_list = [ "IsInitial" ]    # attribute name
                metarefs_list = [ 1010 ]        # attribute metaref
                
                # for all attributes State may have
                for i in range( 1, attr_meta_list.Count + 1 ):
                        try:
                                a_index = metarefs_list.index( attr_meta_list.Item( i ).MetaRef )       # will not throw
                                assert attr_meta_list.Item( i ).Name in names_list
                                
                                # inquire one specific attribute by providing its meta
                                attr_i = ns.Attribute( attr_meta_list.Item( i ) )
                                
                                # the attribute must be present in the attribute list of ns
                                assert attr_i in attr_list
                                assert True == ( attr_i in attr_list )  # equivalent of the previous
                                
                                if a_index == 0:        # "IsInitial" bool attribute
                                        bval = attr_i.BoolValue
                                        assert False == bval
                                else:
                                        assert 0
                        except:
                                assert 0
                
                # do the same for the following "event" object (empty)
                to_find = "Newevent"
                ne = self.findInProj( project, to_find)
                
                try:
                        nnnname = ne.Name
                except:
                        print "Caught"
                        assert 0
                

                # attributes of Newevent
                attr_list = ne.Attributes
                
                # attributes defined for NewEvent in its meta (Event)
                attr_meta_list = ne.Meta.Attributes
                
                assert attr_list.Count == 5
                assert attr_meta_list.Count == 5

                names_list = [ "Description", "Type", "TypeModifier", "Default", "Async" ]      # attribute names
                metarefs_list = [ 1005, 1015, 1016, 1004, 1001 ]                                # attribute metarefs
                for i in range( 1, attr_meta_list.Count + 1 ):

                        try:
                                a_index = metarefs_list.index( attr_meta_list.Item( i ).MetaRef )       # will not throw
                                assert attr_meta_list.Item( i ).Name in names_list

                                # inquire one specific attribute by providing its meta
                                attr_i = ne.Attribute( attr_meta_list.Item( i ))

                                # the attribute must be present in the attribute list of ne
                                assert attr_i in attr_list
                                assert True == ( attr_i in attr_list )

                                if a_index in [0, 1, 2]:
                                        assert "" == attr_i.StringValue
                                        assert "" == attr_i.Value
                                        assert 0  != attr_i.Status      # 0: here
                                        assert attr_i.OrigValue == attr_i.Value
                                        assert attr_meta_list.Item( i ) == attr_i.Meta
                                        #TODO assert False == attr_i.HasChanged              # RESU: why is true, it is the original unfilled value
                                        #assert not attr_i.HasChanged
                                        
                                elif a_index in [3, 4]:
                                        assert False == attr_i.BoolValue
                                        assert False == attr_i.Value
                                        assert 0  != attr_i.Status      # 0: here
                                        assert attr_i.OrigValue == attr_i.Value
                                        assert attr_meta_list.Item( i ) == attr_i.Meta
                                        #TODO assert False == attr_i.HasChanged              # RESU: why is true?
                                        #assert not attr_i.HasChanged

                                else:
                                        assert 0
                        except:
                                assert 0

                # commit trans
                project.CommitTransaction()
                
                project.Save()
                project.Close(0)

                pass

        def testHfindInProj( self ):
                """    testHfindInProj
                        for testing the findInProj helper method (defined in this file)
                """

                mganame = "_tc7_G_gr.mga"
                self.project = project = win32com.client.Dispatch("Mga.MgaProject")
                try:
                        project.Open( "MGA=" + mganame )
                except:
                        project.Close(0)
                        assert 0
                        
                terr = project.CreateTerritory( None, None, None)
                
                trans = project.BeginTransaction( terr)

                # a "State" object (empty)
                to_find = "NewState"
                ns = self.findInProj( project, to_find)

                try:
                        nnnname = ns.Name
                except:
                        print "Exception Caught. Helper method not working properly. #1"
                        assert 0
                
                # do the same for the following "event" object (empty)
                to_find = "Newevent"
                ne = self.findInProj( project, to_find)
                
                try:
                        nnnname = ne.Name
                except:
                        print "Exception Caught. Helper method not working properly. #2"
                        assert 0

                # commit trans
                project.CommitTransaction()
                
                project.Save()
                project.Close(0)

                pass

	def populate7L(self, p):
		f = bd.newFolder( p, p.RootFolder, 'TOSFolder')
		f.Name = 'NewTOSFolder'
		
		mod = bd.newObjInFold( p, f, 'module')
		mod.Name = 'Newmodule'

		e = bd.new( p, mod, 'State')
		e.Name = 'NewState'
		
        def testL( self ):
                """    testL
                        testing IMgaFCO properties like
                                Registry        get
                                RegistryValue   get/put
                                RegistryNode    get
                        and IMgaRegNode property
                                Value           get/put
                        
                        inquire and modify values, finally commit transaction to preserve changes
                """

		mganame = "_tc7_L_gr.mga"

		# create the project with the needed kinds
		project = bd.creaP( mganame, "GRATISII")
		if not project:
			self.fail("Create failed")
		try:
			self.populate7L( project)
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
                
                # a "State" object (empty)
                to_find = "NewState"
                ns = self.findInProj( project, to_find)
                
                # it should return a collection of nodes
                rgnodesA = ns.Registry                                # virtual nodes too
                rgnodesB = ns.GetRegistryDisp( False )                # just the owned ones
                
                assert rgnodesA.Count == 0                            # initally no nodes exist
                assert rgnodesB.Count == 0
                
                rgnod1 = ns.GetRegistryNodeDisp( "OneNode" )          # this step (though it is a Get) will create the named nodes
                rgnod2 = ns.GetRegistryNodeDisp( "AnoNode" )
                
                rgnod1.Value = '1one'
                rgnod2.Value = '2two'

                # now it should contain > 0 nodes
                rgnodesA = ns.Registry
                rgnodesB = ns.GetRegistryDisp( False)

                # the fresh node must be in the collection
                assert rgnod1 in rgnodesA

                assert rgnod1 in rgnodesA
                assert rgnod2 in rgnodesB
                
                assert "1one" == rgnod1.Value
                assert "2two" == rgnod2.Value

                assert "1one" == ns.GetRegistryValueDisp( "OneNode" )
                assert "2two" == ns.GetRegistryValueDisp( "AnoNode" )

                # modify through the IMgaFCO RegistryValue put-property
                ns.SetRegistryValueDisp( "OneNode", "one1-modified" )
                
                # check it
                assert "one1-modified" == rgnod1.Value
                assert "one1-modified" == ns.GetRegistryValueDisp( "OneNode" )

                # modify through the IMgaRegNode Value put-property
                rgnod2.Value = "two2-modified"
                
                # check it
                assert "two2-modified" == rgnod2.Value
                assert "two2-modified" == ns.GetRegistryValueDisp( "AnoNode" )
                
                project.CommitTransaction()
                
                project.Save()
                project.Close(0)
                
                pass


"""
        Let's produce the test suites
"""
# 1st way
def suites():
        suite = unittest.makeSuite(TestCase7,'test')
        return suite

# 2nd way
def suites2():
        tc = TestCase7()
        #all = tc.my_suite()
        #return all

# 3rd way
def suites3():
        suite = unittest.TestSuite()
        #suite.addTest( TestCase7( "testA"))
        #suite.addTest( TestCase7( "testB"))
        suite.addTest( TestCase7( "testE"))
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
        # unittest.main(defaultTest='TestCase7')
        
        ######## 3rd way
        # all = suites3()
        # runner = unittest.TextTestRunner()
        # runner.run( all )
