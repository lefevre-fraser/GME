using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;
using System.IO;

namespace BonExtension.Generators
{
    public class General
    {
        public static string Path = @"";
        public static string ParadigmName = "ParadigmName";
        public static string InterpreterName = "Paradigm Desc";
        public static string ClassName = "Paradigm";
        public static string NamespaceName = "GME.CSharp";

        public static string ProjectId = Guid.NewGuid().ToString();

        private static void util()
        {
            Assembly assembly = Assembly.GetExecutingAssembly();
            using (StreamReader textStreamReader = new StreamReader(assembly.GetManifestResourceStream("BonExtension.Templates.Util.cs")))
            {
                string content = textStreamReader.ReadToEnd();

                content = content.Replace("##1##", General.NamespaceName);
                content = content.Replace("##2##", General.ClassName);

                Directory.CreateDirectory(System.IO.Path.Combine(General.Path, General.ClassName));
                using (TextWriter tw = new StreamWriter(System.IO.Path.Combine(General.Path, General.ClassName) + "\\Util.cs"))
                {
                    tw.WriteLine(content);
                }
            }
        }

        private static void solution()
        {
            Assembly assembly = Assembly.GetExecutingAssembly();
            using (StreamReader textStreamReader = new StreamReader(assembly.GetManifestResourceStream("BonExtension.Templates.solution.sln")))
            {
                string content = textStreamReader.ReadToEnd();
                                
                //content = content.Replace("##1##", Guid.NewGuid().ToString());
                content = content.Replace("##2##", General.ClassName);
                content = content.Replace("##3##", General.ProjectId);

                using (FileStream fs = new FileStream(System.IO.Path.Combine(General.Path, General.ClassName) + ".sln", FileMode.Create))
                {
                    using (TextWriter tw = new StreamWriter(fs, Encoding.UTF8))
                    {
                        tw.WriteLine(content);
                    }
                }
            }
        }

        private static void project()
        {
            Assembly assembly = Assembly.GetExecutingAssembly();
            using (StreamReader textStreamReader = new StreamReader(assembly.GetManifestResourceStream("BonExtension.Templates.project.csproj")))
            {
                string content = textStreamReader.ReadToEnd();

                content = content.Replace("##1##", General.ProjectId);
                content = content.Replace("##2##", General.NamespaceName);
                content = content.Replace("##3##", General.ClassName);
                StringBuilder sb = new StringBuilder();
                foreach (string objectname in Object.ElementsByName.Keys)
	            {
                    sb.AppendLine(@"<Compile Include=""BonExtension\" + objectname + @".cs"" />");		
                }
                content = content.Replace("##4##", sb.ToString());

                Directory.CreateDirectory(System.IO.Path.Combine(General.Path, General.ClassName));
                using (TextWriter tw = new StreamWriter(System.IO.Path.Combine(General.Path, General.ClassName) + "\\" + General.ClassName + ".csproj"))
                {
                    tw.WriteLine(content);
                }
            }
        }

        private static void assemblyInfo()
        {
            Assembly assembly = Assembly.GetExecutingAssembly();
            using (StreamReader textStreamReader = new StreamReader(assembly.GetManifestResourceStream("BonExtension.Templates.AssemblyInfo.cs")))
            {
                string content = textStreamReader.ReadToEnd();

                content = content.Replace("##1##", General.ClassName);
                content = content.Replace("##2##", Guid.NewGuid().ToString()); //

                Directory.CreateDirectory(System.IO.Path.Combine(General.Path, General.ClassName));
                Directory.CreateDirectory(System.IO.Path.Combine(General.Path, General.ClassName) + "\\Properties");
                using (TextWriter tw = new StreamWriter(System.IO.Path.Combine(General.Path, General.ClassName) + "\\Properties\\AssemblyInfo.cs"))
                {
                    tw.WriteLine(content);
                }
            }
        }

        private static void component()
        {
            Assembly assembly = Assembly.GetExecutingAssembly();
            using (StreamReader textStreamReader = new StreamReader(assembly.GetManifestResourceStream("BonExtension.Templates.Component.cs")))
            {
                string content = textStreamReader.ReadToEnd();

                content = content.Replace("##1##", General.NamespaceName);
                content = content.Replace("##2##", General.ClassName);

                Directory.CreateDirectory(System.IO.Path.Combine(General.Path, General.ClassName));
                using (TextWriter tw = new StreamWriter(System.IO.Path.Combine(General.Path, General.ClassName) + "\\Component.cs"))
                {
                    tw.WriteLine(content);
                }
            }
        }

        private static void general()
        {
            Assembly assembly = Assembly.GetExecutingAssembly();
            using (StreamReader textStreamReader = new StreamReader(assembly.GetManifestResourceStream("BonExtension.Templates.General.cs")))
            {
                string content = textStreamReader.ReadToEnd();

                content = content.Replace("##1##", General.NamespaceName);

                Directory.CreateDirectory(System.IO.Path.Combine(General.Path, General.ClassName));
                using (TextWriter tw = new StreamWriter(System.IO.Path.Combine(General.Path, General.ClassName) + "\\General.cs"))
                {
                    tw.WriteLine(content);
                }
            }
        }

        private static void registrar()
        {
            Assembly assembly = Assembly.GetExecutingAssembly();
            using (StreamReader textStreamReader = new StreamReader(assembly.GetManifestResourceStream("BonExtension.Templates.Registrar.cs")))
            {
                string content = textStreamReader.ReadToEnd();

                content = content.Replace("##1##", General.ParadigmName);
                content = content.Replace("##2##", General.InterpreterName);
                content = content.Replace("##3##", General.NamespaceName + "." + General.ClassName);

                Directory.CreateDirectory(System.IO.Path.Combine(General.Path, General.ClassName));
                using (TextWriter tw = new StreamWriter(System.IO.Path.Combine(General.Path, General.ClassName) + "\\Registrar.cs"))
                {
                    tw.WriteLine(content);
                }
            }
        }


        public static void Save()
        {
            solution();
            project();

            component();
            general();
            registrar();
            assemblyInfo();
            util();
        }        
    }
}
