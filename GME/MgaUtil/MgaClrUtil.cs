

using System;
using System.Runtime.InteropServices;
using System.Runtime.Remoting;
using System.Reflection;

namespace GME.MgaUtil
{
    class RegistrationHelper
    {

        [DllImport("MgaUtil.dll", EntryPoint = "ManagedExceptionCallback")]
        public static extern void ManagedExceptionCallback(IntPtr pBSTR,
            [MarshalAs(UnmanagedType.BStr)] string exception);
        // void ManagedExceptionCallback(void * pBSTR, BSTR exception)

        public RegistrationHelper(int pBSTR, string assemblyFile, string typeName, string methodName, int mode)
        {
            try
            {
                object obj = AppDomain.CurrentDomain.CreateInstanceFrom(assemblyFile, typeName).Unwrap();
                obj.GetType().InvokeMember(methodName, System.Reflection.BindingFlags.InvokeMethod,
                    null, obj, new object[] { mode });
            }
            catch (TargetInvocationException e)
            {
                ManagedExceptionCallback(new IntPtr(pBSTR), e.InnerException.ToString());
                throw;
            }
        }
    }

}