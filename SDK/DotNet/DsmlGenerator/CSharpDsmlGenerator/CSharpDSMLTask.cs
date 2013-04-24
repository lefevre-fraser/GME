﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Build.Framework;
using GME.MGA;
using System.IO;
using GME.CSharp;
using System.Threading;

namespace CSharpDSMLGenerator
{
    public class GenerateCSharpDSML : ITask
    {
        public GenerateCSharpDSML()
        {
            CompileDll = true;
        }

        public IBuildEngine BuildEngine
        {
            get;
            set;
        }

        [Required]
        public string InputFile
        {
            get;
            set;
        }

        [Required]
        public string OutputDir
        {
            get;
            set;
        }

        public bool CompileDll
        {
            get;
            set;
        }

        public string ParadigmXmpFile
        {
            get;
            set;
        }

        public string GeneratorMode
        {
            get;
            set;
        }

        public bool Execute()
        {
            Directory.CreateDirectory(OutputDir);
            CSharpDSMLGeneratorInterpreter.GeneratorMode mode;
            if (GeneratorMode == null)
            {
                mode = CSharpDSMLGeneratorInterpreter.GeneratorMode.Namespaces;
            }
            else
            {
                mode = (CSharpDSMLGeneratorInterpreter.GeneratorMode)Enum.Parse(typeof(CSharpDSMLGeneratorInterpreter.GeneratorMode), GeneratorMode);
            }

            Exception excep = null;
            bool success = false;
            Thread t = new Thread(() =>
                {
                    try
                    {
                        MgaProject project = new MgaProject();
                        bool ro;
                        project.Open("MGA=" + InputFile, out ro);
                        try
                        {
                            project.BeginTransactionInNewTerr(transactiontype_enum.TRANSACTION_NON_NESTED);
                            try
                            {
                                if (ParadigmXmpFile == null)
                                {
                                    string projectDir = Path.GetDirectoryName(InputFile);
                                    ParadigmXmpFile = Path.Combine(projectDir, project.RootFolder.Name);
                                    ParadigmXmpFile = Path.ChangeExtension(ParadigmXmpFile, "xmp");
                                }
                                var generator = new CSharpDSMLGeneratorInterpreter();
                                generator.GMEConsole = GMEConsole.CreateFromProject(project);
                                generator.MgaGateway = new MgaGateway(project);

                                var compileUnit = generator.GenerateDotNetCode(project, ParadigmXmpFile, OutputDir, mode);
                                if (CompileDll)
                                {
                                    success = generator.CompileDll(OutputDir, compileUnit);
                                }
                                else
                                {
                                    success = true;
                                }
                            }
                            finally
                            {
                                project.AbortTransaction();
                            }
                        }
                        finally
                        {
                            project.Close();
                        }

                    }
                    catch (Exception e)
                    {
                        excep = e;
                    }
                }
            );
            t.SetApartmentState(ApartmentState.STA);
            t.Start();
            t.Join();

            if (excep != null)
            {
                throw new Exception("Error generating DSML", excep);
            }
            return success;
        }

        public ITaskHost HostObject
        {
            get;
            set;
        }
    }
}
