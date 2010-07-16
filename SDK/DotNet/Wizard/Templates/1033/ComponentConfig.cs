using System;
using System.Runtime.InteropServices;
using MGAUTILLib;
using MGALib;

namespace GME.Interpreter
{
    abstract class ComponentConfig
    {
        public const string paradigmName = "[!output PARADIGMS]";
        public const string componentName = "[!output COMPONENT_NAME]";
        public const string iconId = "[!output COMPONENT_NAME].dll,IDI_COMPICON";
[!if PARADIGM_INDEPENDENT]
        public static componenttype_enum componentType = componenttype_enum.COMPONENTTYPE_INTERPRETER | componenttype_enum.COMPONENTTYPE_PARADIGM_INDEPENDENT;
[!else]
        public static componenttype_enum componentType = componenttype_enum.COMPONENTTYPE_INTERPRETER;
[!endif]
        public static Type typeToRegister = typeof(GME.Interpreter.[!output COMPONENT_NAME]);
[!if REGISTER_SYSTEMWIDE]
        public const regaccessmode_enum registrationMode = regaccessmode_enum.REGACCESS_SYSTEM;
[!else]
        public const regaccessmode_enum registrationMode = regaccessmode_enum.REGACCESS_USER;
[!endif]
        public const string progID = "[!output COCLASS_PROGID]";
        public const string guid = "[!output COCLASS_UUID]";
    }
}
