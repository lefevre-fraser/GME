using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

// new GME registrar
namespace GME.Interpreter
{
    [ComVisible(false)]
    class RegistrationException : ApplicationException
    {
        public RegistrationException(string message) : base(message) { }
    }

    [ComVisible(false)]
    class Registrar
    {
        private Registrar()
        {
        }

        public static void RegisterComponentsInGMERegistry()
        {
            MGAUTILLib.MgaRegistrar registrar = new MGAUTILLib.MgaRegistrar();
            if ((int)GmeLib.MgaInterfaceVersion_enum.MgaInterfaceVersion_Current != (int)((GmeLib.IMgaVersionInfo)registrar).Version)
            {
                throw new RegistrationException("MgaInterfaceVersion mismatch: this assembly is using " +
                    (int)GmeLib.MgaInterfaceVersion_enum.MgaInterfaceVersion_Current +
                    " but the GME interface version is " + (int)((GmeLib.IMgaVersionInfo)registrar).Version +
                    "\n\nPlease install a compatible GME version or update the interop dlls.");
            }

            registrar.RegisterComponent(ComponentConfig.progID, ComponentConfig.componentType, ComponentConfig.componentName, ComponentConfig.registrationMode);
            registrar.set_ComponentExtraInfo(ComponentConfig.registrationMode, ComponentConfig.progID, "Icon", ComponentConfig.iconId);

            if (!ComponentConfig.paradigmName.Equals("*"))
            {
                foreach (String paradigm in ComponentConfig.paradigmName.Split(','))
                {
                    registrar.Associate(ComponentConfig.progID, paradigm, ComponentConfig.registrationMode);
                }
            }
        }

        public static void UnregisterComponentsInGMERegistry()
        {
            MGAUTILLib.MgaRegistrar registrar = new MGAUTILLib.MgaRegistrar();
            if ((int)GmeLib.MgaInterfaceVersion_enum.MgaInterfaceVersion_Current != (int)((GmeLib.IMgaVersionInfo)registrar).Version)
            {
                throw new RegistrationException("MgaInterfaceVersion mismatch: this assembly is using " +
                    (int)GmeLib.MgaInterfaceVersion_enum.MgaInterfaceVersion_Current +
                    " but the GME interface version is " + (int)((GmeLib.IMgaVersionInfo)registrar).Version +
                    "\n\nPlease install a compatible GME version or update the interop dlls.");
            }

            registrar.UnregisterComponent(ComponentConfig.progID, ComponentConfig.registrationMode);
        }

        public void DLLRegisterServer(int regMode)
        {
            //register dll 
            //same as:
            //post build event: C:\WINDOWS\Microsoft.NET\Framework\v2.0.50727\regasm.exe $(TargetPath) /codebase

            RegistrationServices regAsm = new RegistrationServices();
            bool bResult = regAsm.RegisterAssembly(ComponentConfig.typeToRegister.Assembly, AssemblyRegistrationFlags.SetCodeBase);
        }
    }
}

#region Old-GME style registrar
namespace GME.CSharp
{
    [ComVisible(false)]
    public class Registrar
    {
        public Registrar()
        {
        }

        MGAUTILLib.regaccessmode_enum regacc_translate(int x)
        {
            return (MGAUTILLib.regaccessmode_enum)x;
        }

        public void DLLRegisterServer(int regMode)
        {
            //register dll 
            //same as:
            //post build event: C:\WINDOWS\Microsoft.NET\Framework\v2.0.50727\regasm.exe $(TargetPath) /codebase

            RegistrationServices regAsm = new RegistrationServices();
            bool bResult = regAsm.RegisterAssembly(
                ComponentConfig.typeToRegister.Assembly,
                AssemblyRegistrationFlags.SetCodeBase);

            MGAUTILLib.MgaRegistrar reg = new MGAUTILLib.MgaRegistrar();
            if ((int)GmeLib.MgaInterfaceVersion_enum.MgaInterfaceVersion_Current != (int)((GmeLib.IMgaVersionInfo)reg).Version)
            {
                throw new Exception("MgaInterfaceVersion mismatch: this assembly is using " +
                    (int)GmeLib.MgaInterfaceVersion_enum.MgaInterfaceVersion_Current +
                    " but the GME interface version is " + (int)((GmeLib.IMgaVersionInfo)reg).Version +
                    "\n\nPlease install a compatible GME version or update the interop dlls.");
            }
            reg.RegisterComponent(
                ComponentConfig.progID,
                MGALib.componenttype_enum.COMPONENTTYPE_INTERPRETER,
                ComponentConfig.componentName,
                regacc_translate(regMode));

            reg.set_ComponentExtraInfo(regacc_translate(regMode), ComponentConfig.progID, "Icon", ComponentConfig.iconId);

            if (!ComponentConfig.paradigmName.Equals("*"))
            {
                reg.Associate(ComponentConfig.progID, ComponentConfig.paradigmName, (MGAUTILLib.regaccessmode_enum)regMode);
            }

        }
    }
}
#endregion
