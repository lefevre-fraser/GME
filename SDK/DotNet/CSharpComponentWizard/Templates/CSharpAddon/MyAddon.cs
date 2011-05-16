using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using System.IO;
using GME.CSharp;
using MGALib;
using GmeLib;
using MGACoreLib;

namespace MyAddon
{
    [Guid(ComponentConfig.guid),
    ProgId(ComponentConfig.progID),
    ClassInterface(ClassInterfaceType.AutoDual)]
    [ComVisible(true)]
    public class MyAddon : IMgaComponentEx, IGMEVersionInfo, IMgaEventSink
    {

        private MgaAddOn addon;
        private bool componentEnabled = true;

        // Event handlers for addons
        #region MgaEventSink members
        public void GlobalEvent(globalevent_enum @event)
        {
            if (@event == globalevent_enum.GLOBALEVENT_CLOSE_PROJECT)
            {
                Marshal.FinalReleaseComObject(addon);
                addon = null;
            }
            if (!componentEnabled)
            {
                return;
            }

            // TODO: Handle global events
            // MessageBox.Show(@event.ToString());
        }

        /// <summary>
        /// Called when an FCO or folder changes
        /// </summary>
        /// <param name="subject">the object the event(s) happened to</param>
        /// <param name="eventMask">objectevent_enum values ORed together</param>
        /// <param name="param">extra information provided for cetertain event types</param>
        public void ObjectEvent(MgaObject subject, uint eventMask, object param)
        {
            if (!componentEnabled)
            {
                return;
            }

            // TODO: Handle object events (OR eventMask with the members of objectevent_enum)
            // Warning: Only those events are received that you have subscribed for by setting ComponentConfig.eventMask

            // MessageBox.Show(eventMask.ToString());

        }

        #endregion

        #region IMgaComponentEx Members

        public void Initialize(MgaProject p)
        {
            // Creating addon
            p.CreateAddOn(this, out addon);
            // Setting event mask (see ComponentConfig.eventMask)
            unchecked
            {
                addon.EventMask = (uint)ComponentConfig.eventMask;
            }
        }

        public void InvokeEx(MgaProject project, MgaFCO currentobj, MgaFCOs selectedobjs, int param)
        {
            throw new NotImplementedException(); // Not called by addon
        }


        #region Component Information
        public string ComponentName
        {
            get { return GetType().Name; }
        }

        public string ComponentProgID
        {
            get
            {
                return ComponentConfig.progID;
            }
        }

        public componenttype_enum ComponentType
        {
            get { return ComponentConfig.componentType; }
        }
        public string Paradigm
        {
            get { return ComponentConfig.paradigmName; }
        }
        #endregion

        #region Enabling
        bool enabled = true;
        public void Enable(bool newval)
        {
            enabled = newval;
        }
        #endregion

        #region Interactive Mode
        protected bool interactiveMode = true;
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
        #endregion

        #region Custom Parameters
        SortedDictionary<string, object> componentParameters = null;

        public object get_ComponentParameter(string Name)
        {
            if (Name == "type")
                return "csharp";

            if (Name == "path")
                return GetType().Assembly.Location;

            if (Name == "fullname")
                return GetType().FullName;

            object value;
            if (componentParameters != null && componentParameters.TryGetValue(Name, out value))
            {
                return value;
            }

            return null;
        }

        public void set_ComponentParameter(string Name, object pVal)
        {
            if (componentParameters == null)
            {
                componentParameters = new SortedDictionary<string, object>();
            }

            componentParameters[Name] = pVal;
        }
        #endregion

        #region Unused Methods
        // Old interface, it is never called for MgaComponentEx interfaces
        public void Invoke(MgaProject Project, MgaFCOs selectedobjs, int param)
        {
            throw new NotImplementedException();
        }

        // Not used by GME
        public void ObjectsInvokeEx(MgaProject Project, MgaObject currentobj, MgaObjects selectedobjs, int param)
        {
            throw new NotImplementedException();
        }

        #endregion

        #endregion

        #region IMgaVersionInfo Members

        public GMEInterfaceVersion_enum version
        {
            get { return GMEInterfaceVersion_enum.GMEInterfaceVersion_Current; }
        }

        #endregion

        #region Registration Helpers

        [ComRegisterFunctionAttribute]
        public static void GMERegister(Type t)
        {
            Registrar.RegisterComponentsInGMERegistry();
        }

        [ComUnregisterFunctionAttribute]
        public static void GMEUnRegister(Type t)
        {
            Registrar.UnregisterComponentsInGMERegistry();
        }

        #endregion
    }
}
