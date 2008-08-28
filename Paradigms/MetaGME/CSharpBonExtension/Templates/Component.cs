using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using System.IO;


namespace ##1##
{
    [ClassInterface(ClassInterfaceType.AutoDual)]
    public class ##2## : GmeLib.IMgaComponentEx, GmeLib.IMgaVersionInfo
    {
        public static GmeLib.IMgaProject Project;
        public static GmeLib.IMgaMetaProject MetaProject;

        public ##2##()
        { }

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
            throw new NotImplementedException();
        }

        public void InvokeEx(GmeLib.IMgaProject project)
        {
            InvokeEx(project, null, null, 0);
        }

        public void InvokeEx(GmeLib.IMgaProject project, GmeLib.IMgaFCO currentobj, GmeLib.IMgaFCOs selectedobjs, int param)
        {
            GmeLib.IMgaTerritory territory = null;
            ##2##.Project = project;
            ##2##.MetaProject = project.RootMeta;

            project.CreateTerritory(null, out territory, null);

            try
            {
                project.BeginTransaction(territory, GmeLib.transactiontype_enum.TRANSACTION_GENERAL);
                MGALib.IMgaFolder root = project.RootFolder as MGALib.IMgaFolder;
                RootFolder rf = new RootFolder(root);
                /////////////////////////////////////////////////////////////////////////////////////////////

                //Add implementation code here

                /////////////////////////////////////////////////////////////////////////////////////////////

                project.CommitTransaction();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);

                project.AbortTransaction();
            }

            finally
            {
                territory.Destroy();

                GC.Collect();
                GC.WaitForPendingFinalizers();
            }
        }


        public void ObjectsInvokeEx(GmeLib.IMgaProject Project, GmeLib.IMgaObject currentobj, GmeLib.IMgaObjects selectedobjs, int param)
        {
            //throw new NotSupportedException();
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
                return typeof(##2##).Assembly.Location;

            if (Name == "fullname")
                return typeof(##2##).FullName;

            return null;
            //throw new NotSupportedException();
        }

        public void set_ComponentParameter(string Name, object pVal)
        {
            //throw new NotSupportedException();
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


