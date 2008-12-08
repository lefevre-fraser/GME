using System;
using System.Collections.Generic;
using System.Text;
using METALib;
using System.Runtime.InteropServices;

namespace GME.CSharp
{
    public class Util
    {
        public static IMgaMetaBase GetMetaByName(string name)
        {
            try
            {
                return GME.CSharp.BonExtender.MetaProject.RootFolder.get_DefinedFCOByName(name, false) as IMgaMetaFCO;
            }
            catch (COMException)
            {
                return GME.CSharp.BonExtender.MetaProject.RootFolder.get_DefinedFolderByName(name, false) as IMgaMetaFolder;
            }
        }
    }
}
