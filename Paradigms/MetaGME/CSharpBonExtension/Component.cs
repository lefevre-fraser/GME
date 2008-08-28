using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using System.IO;
using BonExtension.Generators;
using System.Windows.Forms;


namespace GME.CSharp
{
    [ClassInterface(ClassInterfaceType.AutoDual)]
    public class BonExtender : GmeLib.IMgaComponentEx, GmeLib.IMgaVersionInfo
    {
        public BonExtender()
        { }

        public static GmeLib.IMgaProject Project;
        public static GmeLib.IMgaMetaProject MetaProject;

        public static List<string> Errors = new List<string>();

        #region IMgaComponentEx Members

        public string ComponentName
        {
            get
            {
                return GetType().Name;
            }
        }

        public string ComponentProgID
        {
            get
            {
                RegistrationServices regService = new RegistrationServices();
                return regService.GetProgIdForType(GetType());
            }
        }

        public GmeLib.componenttype_enum ComponentType
        {
            get
            {
                return GmeLib.componenttype_enum.COMPONENTTYPE_INTERPRETER;
            }
        }

        public void Enable(bool newval)
        {

        }

        public void Initialize(GmeLib.IMgaProject p)
        {

        }

        protected bool interactiveMode = false;
        public bool InteractiveMode
        {
            get
            {
                return interactiveMode;
            }
            set
            {
                interactiveMode = value;
            }
        }

        public void Invoke(GmeLib.IMgaProject Project, GmeLib.IMgaFCOs selectedobjs, int param)
        {
            //throw new NotImplementedException();
        }

        private void clear()
        {
            BonExtension.Generators.Object.ElementsByName.Clear();
            BonExtension.Generators.Object.ProxyObjects.Clear();
            BonExtension.Generators.Object.ProxyCache.Clear();
            BonExtension.Generators.Enum.Clear();
            BonExtension.Generators.RootFolder.RootObject.Clear();
            Errors.Clear();
        }

        private void processParadigmSheet(MGALib.IMgaFCO fco)
        {
            if (fco.Meta.Name != "ParadigmSheet")
            {
                //handle error
            }

            MGALib.IMgaModel model = fco as MGALib.IMgaModel;

            foreach (MGALib.IMgaObject obj in model.ChildObjects)
            {
                BonExtension.Generators.Object object1;
                if (obj is MGALib.IMgaAtom)
                {
                    MGALib.IMgaAtom o = obj as MGALib.IMgaAtom;
                    switch (o.Meta.Name)
                    {
                        case "Folder":
                            object1 = new Folder(o);
                            break;
                        case "Model":
                            object1 = new Model(o);
                            break;
                        case "FCO":
                            object1 = new FCO(o);
                            break;
                        case "Atom":
                            object1 = new Atom(o);
                            break;
                        case "Reference":
                            object1 = new Reference(o);
                            break;
                        case "Set":
                            object1 = new Set(o);
                            break;
                        case "Connection":
                            object1 = new Connection(o);
                            break;
                        default:

                            //not supported
                            break;
                    }
                }
                else
                {
                    if (obj.MetaBase.Name.Contains("Proxy"))
                    {
                        MGALib.IMgaReference proxy = obj as MGALib.IMgaReference;

                        string referred = proxy.Referred.Name;

                        if (BonExtension.Generators.Object.ProxyCache.ContainsKey(proxy.Name) &&
                            BonExtension.Generators.Object.ProxyCache[proxy.Name] != referred)
                        {
                            Errors.Add(string.Format("Proxies with name '{0}' refer different objects", proxy.Name));
                        }
                        else
                        {
                            BonExtension.Generators.Object.ProxyCache[proxy.Name] = referred;
                            BonExtension.Generators.Object.ProxyObjects[proxy.Name] = proxy;
                        }
                    }
                }
            }  
        }

        public void InvokeEx(GmeLib.IMgaProject project)
        {
            InvokeEx(project, null, null, 0);
        }

        public void InvokeEx(GmeLib.IMgaProject project, GmeLib.IMgaFCO currentobj, GmeLib.IMgaFCOs selectedobjs, int param)
        {
            GmeLib.IMgaTerritory territory = null;
            BonExtender.Project = project;
            BonExtender.MetaProject = project.RootMeta;
            
            project.CreateTerritory(null, out territory, null);

            try
            {
                project.BeginTransaction(territory, GmeLib.transactiontype_enum.TRANSACTION_GENERAL);
                MGALib.IMgaFolder root = project.RootFolder as MGALib.IMgaFolder;
                /////////////////////////////////////////////////////////////////////////////////////////////

                clear();
                

                General.InterpreterName = root.Name + " Interpreter";
                General.ClassName = root.Name;
                General.NamespaceName = "MGA.CSharp";
                General.ParadigmName = root.Name;

                BonExtension.Setup f1 = new BonExtension.Setup();
                if (DialogResult.OK == f1.ShowDialog())
                {
                    //todo: flatten meta, proxies

                    foreach (MGALib.IMgaFCO fco in root.ChildFCOs)
                    {
                        processParadigmSheet(fco);                                              
                    }

                    foreach (MGALib.IMgaFolder fol in root.ChildFolders)
                    {
                        foreach (MGALib.IMgaFCO fco in fol.ChildFCOs)
                        {
                            processParadigmSheet(fco);
                        }
                    }

                }

                RootFolder rootF = new RootFolder();
                rootF.Save();

                foreach (BonExtension.Generators.Object elem in BonExtension.Generators.Object.ElementsByName.Values)
                {
                    elem.Save();
                }

                BonExtension.Generators.Enum.Save();
                BonExtension.Generators.General.Save();

                if (Errors.Count > 0)
                {
                    StringBuilder sb = new StringBuilder();
                    sb.AppendLine("Errors during generation process:");
                    foreach (string item in Errors)
                    {
                        sb.AppendLine(item);
                    }

                    MessageBox.Show(sb.ToString(), "Errors during generation process", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }

                /////////////////////////////////////////////////////////////////////////////////////////////
                project.CommitTransaction();                
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
                MessageBox.Show(e.Message, "Fatal error in interpreter", MessageBoxButtons.OK, MessageBoxIcon.Error);

                project.AbortTransaction();
            }

            finally
            {
                territory.Destroy();

                GC.Collect();
                GC.WaitForPendingFinalizers();
            }
        }

        private void cleanUp(object o)
        {
            if (o != null)
            {
                int refCount = Marshal.ReleaseComObject(o);
                while (refCount != 0)
                {
                    refCount = Marshal.ReleaseComObject(o);
                }
            }
        }

        public void ObjectsInvokeEx(GmeLib.IMgaProject Project, GmeLib.IMgaObject currentobj, GmeLib.IMgaObjects selectedobjs, int param)
        {
            throw new NotSupportedException();
        }

        public string Paradigm
        {
            get
            {
                return GME.CSharp.Registrar.ParadigmName;
            }
        }

        public object get_ComponentParameter(string Name)
        {
            if (Name == "type")
                return "csharp";

            if (Name == "path")
                return typeof(BonExtender).Assembly.Location;

            if (Name == "fullname")
                return typeof(BonExtender).FullName;

            return null;
        }

        public void set_ComponentParameter(string Name, object pVal)
        {
            
        }

        #endregion

        #region IMgaVersionInfo Members

        public GmeLib.MgaInterfaceVersion_enum Version
        {
            get
            {
                return GmeLib.MgaInterfaceVersion_enum.MgaInterfaceVersion_Current;
            }
        }

        #endregion
    }
}


