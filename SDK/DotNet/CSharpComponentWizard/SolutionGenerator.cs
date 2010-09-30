using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using EnvDTE;
using System.IO;
using Microsoft.Win32;
using EnvDTE80;
using EnvDTE100;
using System.Text.RegularExpressions;
using System.Windows.Controls;
using System.ComponentModel;
using System.Windows.Threading;
using System.Threading;
using DSM;

namespace CSharpComponentWizard
{
    public enum CompType
    {
        Addon,
        Interpreter
    }

    public enum Registration
    {
        Systemwide,
        User,
        Both
    }

    public enum ComponentInterface
    {
        Dependent,
        Independent
    }
    
    public static class SolutionGenerator
    {
        public static Dictionary<int, string> AddonEvents;
        
        public static CompType SelectedType = CompType.Addon;
        public static ComponentInterface SelectedInterface = ComponentInterface.Dependent;
        public static Registration SelectedRegistration = Registration.Systemwide;
        public static bool[] AddonEventSelection = new bool[25];

        public static string TargetFolder;  // Without SolutionFolder
        public static string SolutionName;
        public static string ParadigmName;
        public static string ComponentName;
        public static string IconPath;
        public static string NewGuid;       // NewGuid, because Guid is a type
        public static string MgaPath;

      
        public static string GenerateSolution()
        {
            DTE2 dte;
            object obj;
            string TemplateFileName;
            string outputfolder = "";

            try
            {
                if (SolutionGenerator.SelectedType == CompType.Addon)
                {
                    TemplateFileName = "CSharpAddon.zip";
                }
                else // interpreter
                {
                    TemplateFileName = "CSharpInterpreter.zip";
                }

                System.Type type = System.Type.GetTypeFromProgID("VisualStudio.DTE.10.0");
                obj = Activator.CreateInstance(type, true);
                dte = (DTE2)obj;
                Solution4 sln = (Solution4)dte.Solution;

                outputfolder = TargetFolder + @"\" + SolutionName;
                string solutionName = SolutionName + ".sln";

                if (Directory.Exists(outputfolder))
                {
                    Directory.Delete(outputfolder, true);
                }

                // Determine the ProjectTemplateFolder of custom templates
                string ProjectTemplateLocation;
                RegistryKey masterKey = Registry.CurrentUser.OpenSubKey(MainWindow.VS2010_REGISTRY_KEYPATH);
                if (masterKey == null)
                {
                    throw new Exception("Cannot locate ProjectTemplate folder. Visual Studio 2010 is not installed!");
                }
                else
                {
                    ProjectTemplateLocation = masterKey.GetValue(MainWindow.VS2010_USERPROJECTTEMPLATEPATH_REGISTRY_KEYNAME).ToString();
                }
                masterKey.Close();


                // Unpack the sufficent template project
                Stream TemplateStream = System.Reflection.Assembly.GetExecutingAssembly().GetManifestResourceStream(
                            System.Reflection.Assembly.GetExecutingAssembly().GetName().Name + ".Templates." + TemplateFileName);
                FileStream FileWriter = new FileStream(ProjectTemplateLocation + "\\" + TemplateFileName, FileMode.Create);
                byte[] ReadFile = new byte[TemplateStream.Length];
                TemplateStream.Read(ReadFile, 0, ReadFile.Length);
                FileWriter.Write(ReadFile, 0, ReadFile.Length);
                FileWriter.Close();

                sln.Create(outputfolder, solutionName);

                string TemplatePath = sln.GetProjectTemplate(TemplateFileName, "CSharp");
                sln.AddFromTemplate(TemplatePath, outputfolder, SolutionName, false);
                sln.Close();
            }
            catch (Exception e)
            {
                Console.Write("Unexpected error occured: " + e.Message);
                throw;
            }
            finally
            {
                obj = dte = null;
            }
            return outputfolder;
        }

        public static void PostProcessComponentConfig(string outputfolder)
        {
            StreamReader ComponentConfigReadStream = new StreamReader(outputfolder + @"\ComponentConfig.cs");
            string ContentString = ComponentConfigReadStream.ReadToEnd();
            ComponentConfigReadStream.Close();

            // Fill in paradigm name
            ContentString = ContentString.Replace(@"$paradigmname$", ParadigmName);

            if (ParadigmName == "*")
            {
                if (SolutionGenerator.SelectedType == CompType.Addon)
                {
                    ContentString.Replace("COMPONENTTYPE_ADDON", "COMPONENTTYPE_ADDON | componenttype_enum.COMPONENTTYPE_PARADIGM_INDEPENDENT DELETE;");
                }
                else // Interpreter
                {
                    ContentString.Replace("COMPONENTTYPE_INTERPRETER", "COMPONENTTYPE_INTERPRETER | componenttype_enum.COMPONENTTYPE_PARADIGM_INDEPENDENT DELETE;");
                }
            }

            // Fill in ComponentName
            ContentString = ContentString.Replace(@"$componentname$", ComponentName);

            if (SelectedType == CompType.Addon)
            {
                // Set EventMask
                StringBuilder eventmask = new StringBuilder();
                bool firsttime = true;
             
                for (int i = 0; i <= 24; ++i)
                {
                    if (SolutionGenerator.AddonEventSelection[i])
                    {
                        string temp;
                        AddonEvents.TryGetValue(i, out temp);

                        if (firsttime)
                        {
                            eventmask.Append("objectevent_enum." + temp);
                        }
                        else
                        {
                            eventmask.Append(" | objectevent_enum." + temp);
                        }
                        firsttime = false;
                    }
                }

                if (firsttime == true)
                {
                    ContentString = ContentString.Replace(@"$eventmask$", "0");
                }
                else
                {
                    ContentString = ContentString.Replace(@"$eventmask$", eventmask.ToString());
                }
                ContentString = ContentString.Replace(@"$eventmask$", eventmask.ToString());

                // Set ComponentType
                ContentString = ContentString.Replace(@"$componenttype$", "ADDON");
            }
            else // interpreter
            {
                // Set IconName
                ContentString = ContentString.Replace(@"$iconname$", "Component.ico");

                if (IconPath != String.Empty && File.Exists(IconPath))
                {
                    File.Copy(IconPath, outputfolder + @"\Component.ico", true);
                }

                // Set IconPath
                ContentString = ContentString.Replace(@"$iconpath$", "null");

                // Set ComponentType
                ContentString = ContentString.Replace(@"$componenttype$", "INTERPRETER");
            }

            // Set Registration Scope
            if (SolutionGenerator.SelectedRegistration == Registration.Systemwide)
            {
                ContentString = ContentString.Replace(@"$regaccessmode$", "REGACCESS_SYSTEM");
            }
            else if (SolutionGenerator.SelectedRegistration == Registration.User)
            {
                ContentString = ContentString.Replace(@"$regaccessmode$", "REGACCESS_USER");
            }
            else if (SolutionGenerator.SelectedRegistration == Registration.Both)
            {
                ContentString = ContentString.Replace(@"$regaccessmode$", "REGACCESS_BOTH");
            }

            // Fill in progID
            ContentString = ContentString.Replace(@"$progid$", SolutionName.Replace(" ", ""));

            // Fill in guid
            ContentString = ContentString.Replace(@"$guid$", NewGuid);

            StreamWriter ComponentConfigWriteStream = new StreamWriter(outputfolder + @"\ComponentConfig.cs");
            ComponentConfigWriteStream.Write(ContentString);
            ComponentConfigWriteStream.Close();
        }

        public static void RenameProject(string outputfolder)
        {

            if (SolutionGenerator.SelectedType == CompType.Addon)
            {
                // Rename namespace, classname, and filename
                StreamReader ComponentConfigReadStream = new StreamReader(outputfolder + @"\MyAddon.cs");
                string ContentString = ComponentConfigReadStream.ReadToEnd();
                ComponentConfigReadStream.Close();

                ContentString = ContentString.Replace("MyAddon", SolutionName);

                StreamWriter ComponentConfigWriteStream = new StreamWriter(outputfolder + @"\MyAddon.cs");
                 ComponentConfigWriteStream.Write(ContentString);
                ComponentConfigWriteStream.Close();

                File.Move(outputfolder + @"\MyAddon.cs", outputfolder + @"\" + SolutionName + ".cs");


                // Rename filereference in the csproj file
                ComponentConfigReadStream = new StreamReader(outputfolder + @"\" + SolutionName + ".csproj");
                ContentString = ComponentConfigReadStream.ReadToEnd();
                ComponentConfigReadStream.Close();

                ContentString = ContentString.Replace("MyAddon", SolutionName);

                // Uncomment signature
                ContentString = ContentString.Replace("<!--DELETE", "");
                ContentString = ContentString.Replace("DELETE-->", "");

                ComponentConfigWriteStream = new StreamWriter(outputfolder + @"\" + SolutionName + ".csproj");
                ComponentConfigWriteStream.Write(ContentString);
                ComponentConfigWriteStream.Close();
            }
            else // interpreter
            {
                // Rename namespace, classname, and filename
                StreamReader FileReadStream = new StreamReader(outputfolder + @"\MyInterpreter.cs");
                string ContentString = FileReadStream.ReadToEnd();
                FileReadStream.Close();

                ContentString = ContentString.Replace("MyInterpreter", SolutionName);

                StreamWriter FileWriteStream = new StreamWriter(outputfolder + @"\MyInterpreter.cs");
                FileWriteStream.Write(ContentString);
                FileWriteStream.Close();

                File.Move(outputfolder + @"\MyInterpreter.cs", outputfolder + @"\" + SolutionName + ".cs");


                // Rename filereference in the csproj file
                FileReadStream = new StreamReader(outputfolder + @"\" + SolutionName + ".csproj");
                ContentString = FileReadStream.ReadToEnd();
                FileReadStream.Close();

                ContentString = ContentString.Replace("MyInterpreter", SolutionName);

                // Uncomment signature reference
                ContentString = ContentString.Replace("<!--DELETE", "");
                ContentString = ContentString.Replace("DELETE-->", "");

                FileWriteStream = new StreamWriter(outputfolder + @"\" + SolutionName + ".csproj");
                FileWriteStream.Write(ContentString);
                FileWriteStream.Close();
            }           
        }

        public static void GenerateSignature(string outputfolder)
        {
            // Search sn.exe
            string SNLocation;
            RegistryKey masterKey = Registry.LocalMachine.OpenSubKey(MainWindow.MSSDK_REGISTRY_KEYPATH);
            if (masterKey == null)
            {
                throw new Exception("Cannot locate sn.exe! VS2010 SDK is not installed!");
            }
            else
            {
                SNLocation = masterKey.GetValue(MainWindow.MSSDK_INSTALLFOLDER_REGISTRY_KEYNAME).ToString();
            }
            masterKey.Close();

            SNLocation += @"\bin\sn.exe";

            System.Diagnostics.ProcessStartInfo pinfo = new System.Diagnostics.ProcessStartInfo();
            pinfo.Arguments = "-k " + outputfolder + "\\AssemblySignature.snk";
            pinfo.CreateNoWindow = true;
            pinfo.UseShellExecute = true;
            pinfo.WindowStyle = System.Diagnostics.ProcessWindowStyle.Hidden;
            pinfo.FileName = SNLocation;
            System.Diagnostics.Process myProc = System.Diagnostics.Process.Start(pinfo);
        }

        public static void GenerateDomainSpecificInterface()
        {
            string ParadigmName = GeneratorFacade.Main(MgaPath, TargetFolder + @"\" + SolutionName, "GME.CSharp." + SolutionName);
            if (GeneratorFacade.Errors.Count != 0)
            {
                MessageBox.Show("Error occured during the domain specific interface generation:" + GeneratorFacade.Errors.ToString());
                throw new Exception("Error occured during the domain specific interface generation:" + GeneratorFacade.Errors.ToString());
            }
                    
            // Add files to the projectfile
            string AddString = String.Empty;
            foreach (string s in GeneratorFacade.generatedFiles)
            {
                AddString += "\t<Compile Include=\"" + ParadigmName + @"\";
                AddString += System.IO.Path.GetFileName(s);
                AddString += "\" />";
                AddString += Environment.NewLine;
            }

            try
            {
                // Rename filereference in the csproj file
                StreamReader FileReadStream = new StreamReader(TargetFolder + @"\" + SolutionName + @"\" + SolutionName + ".csproj");
                string ContentString = FileReadStream.ReadToEnd();
                FileReadStream.Close();

                ContentString = ContentString.Replace(@"<!--$ADDITIONALFILES$-->", AddString);

                StreamWriter FileWriteStream = new StreamWriter(TargetFolder + @"\" + SolutionName + @"\" + SolutionName + ".csproj");
                FileWriteStream.Write(ContentString);
                FileWriteStream.Close();
            }
            catch (Exception)
            {
                MessageBox.Show("Error occured: Cannot find the previously generated VS projectfile in the specified folder with the specified solutionname!");
                throw;
            }
            
        }
    }
}
