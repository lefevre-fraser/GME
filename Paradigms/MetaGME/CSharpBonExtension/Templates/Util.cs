using System;
using System.Collections.Generic;
using System.Text;
using METALib;
using System.Runtime.InteropServices;

namespace ##1##
{
    public class Util
    {
        public static IMgaMetaBase GetMetaByName(string name)
        {
            try
            {
                return ##1##.##2##.MetaProject.RootFolder.get_DefinedFCOByName(name, false) as IMgaMetaFCO;
            }
            catch (COMException e)
            {
                return ##1##.##2##.MetaProject.RootFolder.get_DefinedFolderByName(name, false) as IMgaMetaFolder;
            }
        }
    }
}