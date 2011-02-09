using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using GmeLib;

namespace GME.CSharp
{
    /// <summary>
    /// Automatically redirects console messages to the GME console output, if GME is available.
    /// Otherwise prints the output to System console.
    /// </summary>
    public static class GMEConsole
    {

        /// <summary>
        /// The GME application variable
        /// </summary>
        static public IGMEOLEApp gme = null;
        private static GMETextWriter error = new GMETextWriter(msgtype_enum.MSG_ERROR);
        private static GMETextWriter warning = new GMETextWriter(msgtype_enum.MSG_WARNING);
        private static GMETextWriter info = new GMETextWriter(msgtype_enum.MSG_INFO);
        private static GMETextWriter normal = new GMETextWriter(msgtype_enum.MSG_NORMAL);

        /// <summary>
        /// Handles error messages
        /// The message to be written. GME Console does not handle special characters and trims white-spaces.
        /// Example: GMEConsole.Error.Write("RootFolder name error: {0}.", rf.Name);
        /// If console is initialized, the message appears in GME console, if not, then in standard error.
        /// If DEBUG is defined, it also appears in VS output window.
        /// </summary>
        public static TextWriter Error
        {

            get { return error; }            
        }

        /// <summary>
        /// Prints messages.
        /// The message to be written. GME Console does not handle special characters and trims white-spaces.
        /// Example: GMEConsole.Out.Write("RootFolder name : {0}.", rf.Name);
        /// </summary>
        public static TextWriter Out
        {

            get { return normal; }
        }


        /// <summary>
        /// Prints warning messages.
        /// The message to be written. GME Console does not handle special characters and trims white-spaces.
        /// Example: GMEConsole.Warning.Write("RootFolder name is not changed : {0}.", rf.Name);
        /// </summary>
        public static TextWriter Warning
        {

            get { return warning; }
        }



        /// <summary>
        /// Proints info messages.
        /// The message to be written. GME Console does not handle special characters and trims white-spaces.
        /// Example: GMEConsole.Info.Write("RootFolder name is changed : {0}.", rf.Name);
        /// </summary>
        public static TextWriter Info
        {
            get { return info; }
        }

        /// <summary>
        /// Clear the console
        /// </summary>
        public static void Clear()
        {
            if (gme != null)
                gme.ConsoleClear();
            else
                System.Console.Clear();
        }

    }


    public class GMETextWriter : System.IO.TextWriter
    {
        private msgtype_enum type;

        public GMETextWriter(msgtype_enum type)
        {
            this.type = type;
        }

        override public Encoding Encoding
        {
            get {return Encoding.ASCII;} 
                
        }

        override public void WriteLine(string str)
        {
            Write(str + Environment.NewLine);
        }

        override public void Write(string str)
        {
            if (GMEConsole.gme == null)
            {
                switch (type)
                {
                    case msgtype_enum.MSG_NORMAL:
                        Console.Out.Write(str);
                        break;
                    case msgtype_enum.MSG_INFO:
                        Console.Out.Write("Information: " + str);
                        break;
                    case msgtype_enum.MSG_WARNING:
                        Console.Out.Write("Warning: " + str);
                        break;
                    case msgtype_enum.MSG_ERROR:
                        Console.Error.Write(str);
                        #if(DEBUG)
                            System.Diagnostics.Debug.Write(str);
                        #endif
                        break;
                }
            }
            else
            {
                GMEConsole.gme.ConsoleMessage(str, type);
            }
        }
    }
}
