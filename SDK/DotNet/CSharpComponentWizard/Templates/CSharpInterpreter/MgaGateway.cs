using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using MGALib;
using GmeLib;
using MGAMetaLib;
using MGACoreLib;

namespace GME.CSharp
{
    static class MgaGateway
    {
        public static IMgaProject project = null;
        public static IMgaTerritory territory = null;
		// TODO: Add your static variables here. 
        // Never forget to initialize static variables in each invocation of the component.
        // Static variables preserves their values across the invocations from the same GME process.


        // TODO: Add your generic MGA access functions here
#region TRANSACTION HANDLING
        public static void BeginTransaction(transactiontype_enum mode = transactiontype_enum.TRANSACTION_GENERAL)
        {
            project.BeginTransaction(territory, mode);
        }

        public static void CommitTransaction()
        {
            project.CommitTransaction();
        }

        public static void AbortTransaction()
        {
            project.AbortTransaction();
        }
#endregion
#region UTILITIES
	public static IMgaMetaBase GetMetaByName(string name)
        {
            try
            {
                return project.RootMeta.RootFolder.get_DefinedFCOByName(name, false) as MgaMetaFCO;
            }
#pragma warning disable 0168
            catch (System.Runtime.InteropServices.COMException e)
            {
                return project.RootMeta.RootFolder.get_DefinedFolderByName(name, false) as MgaMetaFolder;
            }
#pragma warning restore 0168
        }

#endregion


    }
}
