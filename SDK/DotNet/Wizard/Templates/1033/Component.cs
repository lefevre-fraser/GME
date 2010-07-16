using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.IO;


using GME.CSharp;
using GmeLib;


namespace GME.Interpreter
{
    [Guid(ComponentConfig.guid),
    ProgId(ComponentConfig.progID),
    ClassInterface(ClassInterfaceType.AutoDual)]
    [ComVisible(true)]
    public class [!output COMPONENT_NAME] : GmeLib.IMgaComponentEx, GmeLib.IMgaVersionInfo
    {
        public void InvokeEx2(IMgaProject project, IMgaFCO currentobj, IMgaFCOs selectedobjs, int param)
        {
            IGMEOLEApp gme = null;
            try
            {
                gme = (IGMEOLEApp)project.GetClientByName("GME.Application").OLEServer;
            }
            catch { }
            gme.ConsoleMessage("Interpreting...", msgtype_enum.MSG_INFO);

            GmeLib.IMgaTerritory territory = project.BeginTransactionInNewTerr(transactiontype_enum.TRANSACTION_READ_ONLY);
            try
            {
            	// TODO: interpreter code goes here
                IMgaFolder rootFolder = project.RootFolder;
                gme.ConsoleMessage(rootFolder.Name, msgtype_enum.MSG_INFO);
            }
            finally
            {
                try
                {
                    project.AbortTransaction();
                }
                catch { }
                try
                {
                    territory.Destroy();
                }
                catch { }
                System.Runtime.InteropServices.Marshal.ReleaseComObject(project);
                System.Runtime.InteropServices.Marshal.ReleaseComObject(territory);
                System.Runtime.InteropServices.Marshal.ReleaseComObject(selectedobjs);
                System.Runtime.InteropServices.Marshal.ReleaseComObject(gme);
            }
        }

        #region IMgaComponentEx Members

        public void InvokeEx(IMgaProject project, IMgaFCO currentobj, IMgaFCOs selectedobjs, int param)
        {
            try
            {
                InvokeEx2(project, currentobj, selectedobjs, param);
            }
            finally
            {
                project = null;
                currentobj = null;
                selectedobjs = null;
                GC.Collect();
                GC.WaitForPendingFinalizers();
            }
        }

        public string ComponentName
        {
            get { return GetType().Name; }
        }

        public string ComponentProgID
        {
            get
            {
                RegistrationServices regService = new RegistrationServices();
                return regService.GetProgIdForType(GetType());
            }
        }

        public componenttype_enum ComponentType
        {
            get { return GmeLib.componenttype_enum.COMPONENTTYPE_INTERPRETER; }
        }

        public void Enable(bool newval)
        {
        }

        public void Initialize(IMgaProject p)
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

        public void Invoke(IMgaProject Project, IMgaFCOs selectedobjs, int param)
        {
            InvokeEx(Project, null, selectedobjs, 0);
        }

        public void ObjectsInvokeEx(IMgaProject Project, IMgaObject currentobj, IMgaObjects selectedobjs, int param)
        {
            throw new NotImplementedException();
        }

        public string Paradigm
        {
            get { return ComponentConfig.paradigmName; }
        }

        public object get_ComponentParameter(string Name)
        {
            if (Name == "type")
                return "csharp";

            if (Name == "path")
                return GetType().Assembly.Location;

            if (Name == "fullname")
                return GetType().FullName;

            return null;
        }

        public void set_ComponentParameter(string Name, object pVal)
        {
        }

        #endregion

        #region IMgaVersionInfo Members

        public MgaInterfaceVersion_enum Version
        {
            get { return GmeLib.MgaInterfaceVersion_enum.MgaInterfaceVersion_Current; }
        }

        #endregion
    
        [ComRegisterFunctionAttribute]
        public static void GMERegister(Type t)
        {
            Registrar.RegisterComponentsInGMERegistry();
          
        }

        [ComUnregisterFunctionAttribute]
        public static void GMEUnRegister(Type t)
        {
            Registrar.UnRegisterComponentsInGMERegistry();

        }
    }
}
