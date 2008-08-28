using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace GME.CSharp
{
    public class Registrar
    {
        public static string ParadigmName = "MetaGME";
        public static string InterpreterName = "CSharp BonExtension";
        public static string MetaGUID = "GUID";

        public Registrar()
        {
        }

        MGAUTILLib.regaccessmode_enum regacc_translate(int x)
        {
            if (x == 0) return MGAUTILLib.regaccessmode_enum.REGACCESS_SYSTEM;
            if (x == 1) return MGAUTILLib.regaccessmode_enum.REGACCESS_USER;
            if (x == 2) return MGAUTILLib.regaccessmode_enum.REGACCESS_BOTH;

            return MGAUTILLib.regaccessmode_enum.REGACCESS_NONE;
        }

        public void DLLRegisterServer(int regMode)
        {
            //register dll 
            //same as:
            //post build event: C:\WINDOWS\Microsoft.NET\Framework\v2.0.50727\regasm.exe $(TargetDir)Project1.dll /codebase

            Type typeToRegister = typeof(GME.CSharp.BonExtender);

            RegistrationServices regAsm = new RegistrationServices();
            bool bResult = regAsm.RegisterAssembly(
                typeToRegister.Assembly,
                AssemblyRegistrationFlags.SetCodeBase);

            MGAUTILLib.MgaRegistrar reg = new MGAUTILLib.MgaRegistrar();
            reg.RegisterComponent(
                regAsm.GetProgIdForType(typeToRegister),
                MGALib.componenttype_enum.COMPONENTTYPE_INTERPRETER,
                InterpreterName,
                regacc_translate(regMode));

            reg.Associate(
                regAsm.GetProgIdForType(typeToRegister),
                ParadigmName,
                regacc_translate(regMode));
        }
    }
}
