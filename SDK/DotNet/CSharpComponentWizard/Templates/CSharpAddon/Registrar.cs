using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using MGAUtilLib;
using MGALib;
using GmeLib;
using MGACoreLib;
using Microsoft.Win32;

namespace GME.CSharp
{
    [ComVisible(false)]
    public class RegistrationException : ApplicationException
    {
        public RegistrationException(string message):base(message){}
    }

    [ComVisible(false)]
    public class Registrar
    {
       
        public Registrar()
        {
        }


        public static void RegisterComponentsInGMERegistry()
        {
            try
            {
                MgaRegistrar registrar = new MgaRegistrar();
                if ((int)GMEInterfaceVersion_enum.GMEInterfaceVersion_Current != (int)((IGMEVersionInfo)registrar).version)
                {
                    throw new RegistrationException("GMEInterfaceVersion mismatch: this assembly is using " +
                        (int)GMEInterfaceVersion_enum.GMEInterfaceVersion_Current +
                        " but the GME interface version is " + (int)((IGMEVersionInfo)registrar).version +
                        "\n\nPlease install a compatible GME version or update the interop dlls.");
                }
             
                registrar.RegisterComponent(ComponentConfig.progID, ComponentConfig.componentType, ComponentConfig.componentName, ComponentConfig.registrationMode);
              
                if (!ComponentConfig.paradigmName.Equals("*"))
                {
                    registrar.Associate(
                       ComponentConfig.progID,
                        ComponentConfig.paradigmName,
                        ComponentConfig.registrationMode);
                }
            }
            catch (Exception e)
            {
                System.Windows.Forms.MessageBox.Show(e.Message);
            }

        }


        public static void UnregisterComponentsInGMERegistry()
        {
            try
            {

                MgaRegistrar registrar = new MgaRegistrar();
                if ((int)GMEInterfaceVersion_enum.GMEInterfaceVersion_Current != (int)((IGMEVersionInfo)registrar).version)
                {
                    throw new RegistrationException("GMEInterfaceVersion mismatch: this assembly is using " +
                        (int)GMEInterfaceVersion_enum.GMEInterfaceVersion_Current +
                        " but the GME interface version is " + (int)((IGMEVersionInfo)registrar).version +
                        "\n\nPlease install a compatible GME version or update the interop dlls.");
                }

                registrar.UnregisterComponent(ComponentConfig.progID, ComponentConfig.registrationMode);

            }
            catch (Exception e)
            {
                System.Windows.Forms.MessageBox.Show(e.Message);
            }

        }
    }
}
