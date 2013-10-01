import unittest
import os
import win32com.client
import GPyUnit.util
from GPyUnit.util import dec_disable_early_binding

def _adjacent_file(file):
    import os.path
    return os.path.join(os.path.dirname(os.path.abspath(__file__)), file)

class TestInstances(unittest.TestCase):
    project = None
    def __init__(self, name, **kwds):
        super(TestInstances, self).__init__(name, **kwds)

    def tearDown(self):
        if self.project:
            self.project.Close(True)

    @property
    def connstr(self):
        return "MGA=" + _adjacent_file("tmp.mga")
    
    @dec_disable_early_binding
    def test_CreateInstances(self):
        self.project = GPyUnit.util.parse_xme(self.connstr)
        self.project.BeginTransactionInNewTerr()
        for i in range(3): # exponential!
            for model in self.project.RootFolder.ChildFCOs:
                self.project.RootFolder.DeriveRootObject(model, True)
        self.project.CommitTransaction()

    @dec_disable_early_binding
    def test_RedirectBaseReference(self):
        self.project = GPyUnit.util.parse_xme(self.connstr)
        self.project.BeginTransactionInNewTerr()
        aspects = self.project.RootFolder.GetObjectByPathDisp("/@Aspects")
        allproxy = self.project.RootFolder.GetObjectByPathDisp("/@Aspects/@AllRef")
        aspects_instance = self.project.RootFolder.DeriveRootObject(aspects, True)
        aspects_subtype = self.project.RootFolder.DeriveRootObject(aspects, False)
        attributes = self.project.RootFolder.GetObjectByPathDisp("/@Stereotypes/@Attributes")
        allproxy.Referred = attributes
        for asp in (aspects_instance, aspects_subtype):
            self.assertEqual(asp.GetObjectByPathDisp("/@AllRef").Referred.Name, attributes.Name)
            self.assertEqual(asp.GetObjectByPathDisp("/@AllRef").Referred.ID, attributes.ID)
        self.project.CommitTransaction()

    @dec_disable_early_binding
    def test_RedirectBaseReference2(self):
        self.project = GPyUnit.util.parse_xme(self.connstr)
        self.project.BeginTransactionInNewTerr()
        aspects = self.project.RootFolder.GetObjectByPathDisp("/@Aspects")
        allproxy = self.project.RootFolder.GetObjectByPathDisp("/@Aspects/@AllRef")
        instances = []
        for inst_flag in (True, False, True, False):
            instances.append(aspects.DeriveChildObject(allproxy, allproxy.MetaRole, inst_flag))
        attributes = self.project.RootFolder.GetObjectByPathDisp("/@Stereotypes/@Attributes")
        allproxy.Referred = attributes
        try:
            instances[0].Referred = self.project.RootFolder.GetObjectByPathDisp("/@Constraints/@Constraints|kind=Aspect")
        except Exception, e:
            pass
        else:
            self.fail()
        for asp in instances:
            self.assertEqual(asp.Referred.Name, attributes.Name)
            self.assertEqual(asp.Referred.ID, attributes.ID)
        self.project.CommitTransaction()

    @dec_disable_early_binding
    def test_RedirectBaseReference3(self):
        self.project = GPyUnit.util.parse_xme(self.connstr)
        self.project.BeginTransactionInNewTerr()
        aspects = self.project.RootFolder.GetObjectByPathDisp("/@Aspects")
        allproxy = self.project.RootFolder.GetObjectByPathDisp("/@Aspects/@AllRef")
        instances = []
        for inst_flag in (True, False, True, False):
            instances.append(aspects.DeriveChildObject(allproxy, allproxy.MetaRole, inst_flag))
        self.assertFalse(instances[3].CompareToBase())
        instances[3].Referred = instances[3].Referred
        self.assertTrue(instances[3].CompareToBase())
        attributes = self.project.RootFolder.GetObjectByPathDisp("/@Stereotypes/@Attributes")
        try:
            allproxy.Referred = attributes
        except Exception, e:
            pass
        else:
            self.fail()
        instances[3].RevertToBase()
        self.assertFalse(instances[3].CompareToBase())
        allproxy.Referred = attributes
        for asp in instances:
            self.assertEqual(asp.Referred.Name, attributes.Name)
            self.assertEqual(asp.Referred.ID, attributes.ID)
        self.project.CommitTransaction()

    @dec_disable_early_binding
    def test_DetachFromArcheType_RelIDs(self):
        self.project = GPyUnit.util.parse_xme(self.connstr)
        self.project.BeginTransactionInNewTerr()
        aspects = self.project.RootFolder.GetObjectByPathDisp("/@Aspects")
        allproxy = self.project.RootFolder.GetObjectByPathDisp("/@Aspects/@AllRef")
        subtype = self.project.RootFolder.DeriveRootObject(aspects, False)
        allrefNew = subtype.CreateChildObject(allproxy.MetaRole)
        setMembership = subtype.GetObjectByPathDisp("@SetMembership")
        self.assertEquals(0x8000001, setMembership.RelID)
        
        subtype.DetachFromArcheType() # this changes RelIDs so there are no dups
        self.assertEquals(list(range(1,50+1)), sorted([fco.RelID for fco in subtype.ChildFCOs]))
        self.project.CommitTransaction()

#GPyUnit.util.MUGenerator(globals(), TestInstances)
