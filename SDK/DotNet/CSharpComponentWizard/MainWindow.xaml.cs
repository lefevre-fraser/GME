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
using System.Windows.Media;


namespace CSharpComponentWizard
{    
    public partial class MainWindow : System.Windows.Window
    {
        // DEFINES       
        public const string VS2010_REGISTRY_KEYPATH = @"SOFTWARE\Microsoft\VisualStudio\10.0";
        public const string VS2010_PROJECTFOLDER_REGISTRY_KEYNAME = "VisualStudioProjectsLocation";
        public const string VS2010_USERPROJECTTEMPLATEPATH_REGISTRY_KEYNAME = "UserProjectTemplatesLocation";
        public const string VS2010_INSTALLDIR_KEYNAME = "InstallDir";
        public const string MSSDK_REGISTRY_KEYPATH = @"SOFTWARE\Microsoft\Microsoft SDKs\Windows";      
        public const string MSSDK_INSTALLFOLDER_REGISTRY_KEYNAME = "CurrentInstallFolder";

        public const string GUIDREGEXP = @"^(\{){0,1}[0-9a-fA-F]{8}\-[0-9a-fA-F]{4}\-[0-9a-fA-F]{4}\-[0-9a-fA-F]{4}\-[0-9a-fA-F]{12}(\}){0,1}$";

        public Regex GuidExp = new Regex(GUIDREGEXP, RegexOptions.Compiled);

        public MainWindow()
        {
            InitializeComponent();

            for (int i = 0; i <= 24; ++i)
            {
                SolutionGenerator.AddonEventSelection[i] = false;
            }

            // Store AddOn events enum map for easier access later
            SolutionGenerator.AddonEvents = new Dictionary<int, string>();
            SolutionGenerator.AddonEvents.Add(0, "OBJEVENT_CREATED");
            SolutionGenerator.AddonEvents.Add(1, "OBJEVENT_ATTR");
            SolutionGenerator.AddonEvents.Add(2, "OBJEVENT_REGISTRY");
            SolutionGenerator.AddonEvents.Add(3, "OBJEVENT_NEWCHILD");
            SolutionGenerator.AddonEvents.Add(4, "OBJEVENT_RELATION");
            SolutionGenerator.AddonEvents.Add(5, "OBJEVENT_PROPERTIES");
            SolutionGenerator.AddonEvents.Add(6, "OBJEVENT_SUBT_INST");
            SolutionGenerator.AddonEvents.Add(7, "OBJEVENT_PARENT");
            SolutionGenerator.AddonEvents.Add(8, "OBJEVENT_LOSTCHILD");
            SolutionGenerator.AddonEvents.Add(9, "OBJEVENT_REFERENCED");
            SolutionGenerator.AddonEvents.Add(10, "OBJEVENT_CONNECTED");
            SolutionGenerator.AddonEvents.Add(11, "OBJEVENT_SETINCLUDED");
            SolutionGenerator.AddonEvents.Add(12, "OBJEVENT_REFRELEASED");
            SolutionGenerator.AddonEvents.Add(13, "OBJEVENT_DISCONNECTED");
            SolutionGenerator.AddonEvents.Add(14, "OBJEVENT_SETEXCLUDED");
            SolutionGenerator.AddonEvents.Add(15, "OBJEVENT_MARKEDRO");
            SolutionGenerator.AddonEvents.Add(16, "OBJEVENT_MARKEDRW");
            SolutionGenerator.AddonEvents.Add(17, "OBJEVENT_OPENMODEL");
            SolutionGenerator.AddonEvents.Add(18, "OBJEVENT_SELECT");
            SolutionGenerator.AddonEvents.Add(19, "OBJEVENT_DESELECT");
            SolutionGenerator.AddonEvents.Add(20, "OBJEVENT_MOUSEOVER");
            SolutionGenerator.AddonEvents.Add(21, "OBJEVENT_CLOSEMODEL");
            SolutionGenerator.AddonEvents.Add(22, "OBJEVENT_USERBITS");
            SolutionGenerator.AddonEvents.Add(23, "OBJEVENT_PRE_DESTROYED");
            SolutionGenerator.AddonEvents.Add(24, "OBJEVENT_DESTROYED");
            
            // Generate Guid
            this.txb_Guid.Text = Guid.NewGuid().ToString().ToUpper();

            // Get Visual Studio 2010 Project folder
            RegistryKey masterKey = Registry.CurrentUser.OpenSubKey(MainWindow.VS2010_REGISTRY_KEYPATH);
            if (masterKey == null)
            {
                this.txb_TargetFolder.Text = Environment.GetFolderPath(Environment.SpecialFolder.DesktopDirectory);
            }
            else
            {
                this.txb_TargetFolder.Text = masterKey.GetValue(MainWindow.VS2010_PROJECTFOLDER_REGISTRY_KEYNAME).ToString();
            }
            this.txb_TargetFolder.ToolTip = this.txb_TargetFolder.Text;
            masterKey.Close();
            
        }

        private void Generate()
        {
            this.lbl_pleasewait.Visibility = Visibility.Visible;

            this.pgb_generationprogress.Visibility = Visibility.Visible;
            this.pgb_generationprogress.Value = 15;

            BackgroundWorker worker = new BackgroundWorker();
            worker.WorkerReportsProgress = true;
            worker.ProgressChanged += GenerationProgressChanged;
            worker.DoWork += GenerationWork;
            worker.RunWorkerCompleted += GenerationCompleted;
            worker.RunWorkerAsync();
        }

        private void GenerationWork(object sender, DoWorkEventArgs e)
        {
            BackgroundWorker worker = sender as BackgroundWorker;

            try
            {
                string outputfolder = SolutionGenerator.GenerateSolution();

                worker.ReportProgress(40);

                if (outputfolder == String.Empty)
                {
                    throw new Exception("Something went wrong around the specified output folder...");
                }

                if (SolutionGenerator.SelectedInterface == ComponentInterface.Dependent)
                {
                    SolutionGenerator.GenerateDomainSpecificInterface();
                }                
                worker.ReportProgress(60);

                SolutionGenerator.PostProcessComponentConfig(outputfolder);
                worker.ReportProgress(70);

                SolutionGenerator.RenameProject(outputfolder);
                worker.ReportProgress(80);

                SolutionGenerator.GenerateSignature(outputfolder);
                worker.ReportProgress(100);
            }
            catch (Exception ex)
            {
                //MessageBox.Show(ex.Message, "Error occured!", MessageBoxButton.OK, MessageBoxImage.Error);
                txb_GenerationResultSummary.Text = "Generation failed";
                txb_GenerationResultDetails.Text = "Error occured while generating your Visual Studio 2010 solution. " + Environment.NewLine;
                txb_GenerationResultDetails.Text += "We recommend you to start the whole process again! " + Environment.NewLine + Environment.NewLine;
                txb_GenerationResultDetails.Text += "The specific error was: " + ex.Message;
                btn_OpenSolution.IsEnabled = false;
            }
        }
        
        /*
         *  Step validators
        */        
        private bool ValidateInputTab_1()
        {
            if(!Directory.Exists(txb_TargetFolder.Text))
            {
                return false;
            }
            if (this.txb_SolutionName.Text.Contains(" ") || txb_SolutionName.Text == String.Empty)
            {
                return false;
            }
            return true;
        }

        private bool ValidateInputTab_2()
        {
            if ((bool)ckb_GenerateDSI.IsChecked && !File.Exists(txb_MgaPath.Text))
            {
                return false;
            }
            return true;
        }
        
        private bool ValidateInputTab_3()
        {
            if (this.txb_ParadigmName.Text == String.Empty)
            {
                return false;
            }
            if (!this.GuidExp.IsMatch(this.txb_Guid.Text))
            {
                return false;
            }
            return true;
        }

        private bool ValidateInputTab_4()
        {
            bool isAtLeastOneCheckBoxChecked = false;
            if ((bool)this.rbb_Addon.IsChecked)
            {
                for (int i = 0; i <= 24; ++i)
                {
                    if ((bool)((CheckBox)this.FindName("ckb_a" + i)).IsChecked)
                    {
                        isAtLeastOneCheckBoxChecked = true;
                    }
                }
            }
            else
            {
                return true;
            }
            return isAtLeastOneCheckBoxChecked;
        }

        private bool ValidateInputTab_5()
        {
            if (txb_ComponentName.Text == String.Empty)
            {
                return false;
            }
            if (txb_IconPath.Text != String.Empty && !File.Exists(txb_IconPath.Text))
            {
                return false;
            }
            return true;
        }

        /*
         *  Event handlers
        */

        // Navigator buttons 
        private void btn_Next_Click(object sender, RoutedEventArgs e)
        {
            Button button = (Button)sender;
            if (button.Name == "btn_Next1" && this.ValidateInputTab_1())
            {
                this.tbc_WizardTab.SelectedIndex = 1;
                this.lbl_Step.Content = "Step 2 of 6";

                // Save input
                SolutionGenerator.SolutionName = txb_SolutionName.Text;
                SolutionGenerator.TargetFolder = txb_TargetFolder.Text;
            }
            else if (button.Name == "btn_Next2" && this.ValidateInputTab_2())
            {
                this.tbc_WizardTab.SelectedIndex = 2;
                this.lbl_Step.Content = "Step 3 of 6";

                // Save input (to be on the safe side)
                if((bool)ckb_GenerateDSI.IsChecked)
                {
                    SolutionGenerator.SelectedInterface = ComponentInterface.Dependent;
                }
                else
                {
                    SolutionGenerator.SelectedInterface = ComponentInterface.Independent;
                }
                SolutionGenerator.MgaPath = txb_MgaPath.Text;                
            }
            else if (button.Name == "btn_Next3" && this.ValidateInputTab_3())
            {
                this.tbc_WizardTab.SelectedIndex = 3;
                this.lbl_Step.Content = "Step 4 of 6";

                // Save input
                SolutionGenerator.ParadigmName = txb_ParadigmName.Text;
                SolutionGenerator.NewGuid = txb_Guid.Text;
            }
            else if (button.Name == "btn_Next4" && this.ValidateInputTab_4())
            {
                this.tbc_WizardTab.SelectedIndex = 4;
                this.lbl_Step.Content = "Step 5 of 6";
            }
            else if (button.Name == "btn_Next5" && this.ValidateInputTab_5())
            {
                this.tbc_WizardTab.SelectedIndex = 5;
                this.lbl_Step.Content = "Step 6 of 6";

                // Save input
                SolutionGenerator.ComponentName = txb_ComponentName.Text;
                SolutionGenerator.IconPath = txb_IconPath.Text;

                // Stepping to summary page; display summary
                if ((bool)this.rbb_Addon.IsChecked)
                {
                    this.lbl_SumComponentType.Content = "AddOn";
                }
                else // Interpreter
                {
                    this.lbl_SumComponentType.Content = "Interpreter";
                }
                this.lbl_SumComponentName.Content = this.txb_ComponentName.Text;

                if (this.txb_ParadigmName.Text == "*")
                {
                    this.lbl_SumParadigmName.Content = "All paradigms";
                }
                else
                {
                    this.lbl_SumParadigmName.Content = this.txb_ParadigmName.Text;
                }                
                this.lbl_SumSolutionName.Content = this.txb_SolutionName.Text;
                this.lbl_SumOutputFolder.Content = this.txb_TargetFolder.Text;
            }
            else if (button.Name == "btn_Generate")
            {
                Generate();
            }
        }

        private void GenerationProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            pgb_generationprogress.Value = e.ProgressPercentage;
        }

        private void GenerationCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            this.lbl_Step.Content = txb_GenerationResultSummary.Text;
            this.tbc_WizardTab.SelectedIndex = 6;
        }

        private void btn_Back_Click(object sender, RoutedEventArgs e)
        {
            Button button = (Button)sender;
            if (button.Name == "btn_Back2")
            {
                this.tbc_WizardTab.SelectedIndex = 0;
                this.lbl_Step.Content = "Step 1 of 6";
            }
            else if (button.Name == "btn_Back3")
            {
                this.tbc_WizardTab.SelectedIndex = 1;
                this.lbl_Step.Content = "Step 2 of 6";
            }
            else if (button.Name == "btn_Back4")
            {
                this.tbc_WizardTab.SelectedIndex = 2;
                this.lbl_Step.Content = "Step 3 of 6";
            }
            else if (button.Name == "btn_Back5")
            {
                this.tbc_WizardTab.SelectedIndex = 3;
                this.lbl_Step.Content = "Step 4 of 6";
            }
            else if (button.Name == "btn_Back6")
            {
                this.tbc_WizardTab.SelectedIndex = 4;
                this.lbl_Step.Content = "Step 5 of 6";
            }
        }

        // Output path selector
        private void btn_Browse_Click(object sender, RoutedEventArgs e)
        {
            var dialog = new System.Windows.Forms.FolderBrowserDialog();
            dialog.ShowNewFolderButton = true;
            dialog.Description = "Choose your target folder (the solution will be exported into a subfolder)";
            System.Windows.Forms.DialogResult result = dialog.ShowDialog();
            if (result == System.Windows.Forms.DialogResult.OK)
            {
                txb_TargetFolder.Text = dialog.SelectedPath;
            }
        }

        // SolutionName textChanged
        private void txb_SolutionName_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (ValidateInputTab_1())
            {
                btn_Next1.IsEnabled = true;
            }
            else
            {
                btn_Next1.IsEnabled = false;
            }
        }

        // Refresh path TextBox tooltip with full path
        private void txb_TargetFolder_TextChanged(object sender, TextChangedEventArgs e)
        {
            txb_TargetFolder.ToolTip = txb_TargetFolder.Text;
            if (ValidateInputTab_1())
            {
                btn_Next1.IsEnabled = true;
            }
            else
            {
                btn_Next1.IsEnabled = false;
            }
        }

        // Browse icon for interpreter
        private void btn_BrowseIcon_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "ICO files |*.ico";
            dlg.RestoreDirectory = true;

            Nullable<bool> result = dlg.ShowDialog();

            if (result == true)
            {
                this.txb_IconPath.Text = dlg.FileName;
            }
        }

        private void btn_BrowseMga_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "MGA files |*.mga";
            dlg.RestoreDirectory = true;

            Nullable<bool> result = dlg.ShowDialog();

            if (result == true)
            {
                this.txb_MgaPath.Text = dlg.FileName;
            }
        }

        // Exit either at the first step or at the end
        private void btn_Exit_Click(object sender, RoutedEventArgs e)
        {
            if(((Button)sender).Name == "btn_ExitSuccess")
            {
                this.Close();
                return;
            }
            
            string messageBoxText = "Are you sure?";
            string caption = "Exit GME component wizard...";
            MessageBoxButton button = MessageBoxButton.YesNo;
            MessageBoxImage icon = MessageBoxImage.Question;
            switch (MessageBox.Show(messageBoxText, caption, button, icon))
            {
                case MessageBoxResult.Yes:
                    this.Close();
                    break;
                case MessageBoxResult.No:
                    break;
            }
        }

        // Checkbox events for the "All paradigms" CheckBox
        private void ckb_AllParadigms_Checked(object sender, RoutedEventArgs e)
        {
            txb_ParadigmName.IsEnabled = false;
            txb_ParadigmName.Text = "*";
        }

        private void ckb_AllParadigms_Unchecked(object sender, RoutedEventArgs e)
        {
            txb_ParadigmName.IsEnabled = true;
            txb_ParadigmName.Text = String.Empty;
        }

        // RadioButton events for Component type selection
        private void rbb_Interpreter_Checked(object sender, RoutedEventArgs e)
        {
            if (this.IsLoaded == false)
            {
                return;
            }
            SolutionGenerator.SelectedType = CompType.Interpreter;
            txb_IconInfo.Visibility = Visibility.Hidden;
            txb_IconPath.IsEnabled = true;
            btn_BrowseIcon.IsEnabled = true;
            
            for (int i = 0; i <= 24; ++i)
            {
                ((CheckBox)this.FindName("ckb_a" + i)).IsEnabled = false;
            }

            if (ValidateInputTab_4())
            {
                btn_Next4.IsEnabled = true;
            }
            else
            {
                btn_Next4.IsEnabled = false;
            }
        }

        private void rbb_Interpreter_Unchecked(object sender, RoutedEventArgs e)
        {
            if (this.IsLoaded == false)
            {
                return;
            }
            
            SolutionGenerator.SelectedType = CompType.Addon;
            txb_IconInfo.Visibility = Visibility.Visible;
            txb_IconPath.IsEnabled = false;
            btn_BrowseIcon.IsEnabled = false;

            for (int i = 0; i <= 24; ++i)
            {
                ((CheckBox)this.FindName("ckb_a" + i)).IsEnabled = true;
            }

            if (ValidateInputTab_4())
            {
                btn_Next4.IsEnabled = true;
            }
            else
            {
                btn_Next4.IsEnabled = false;
            }
        }
        
        // GUID validator (to display errorlabel)
        private void Guid_Changed(object sender, TextChangedEventArgs e)
        {
            if(!GuidExp.IsMatch(txb_Guid.Text))
            {
                txb_GuidError.Visibility = Visibility.Visible;
                Color c = new Color();
                c.A = 0x00;
                c.R = 0xF2;
                c.G = 0xC3;
                c.B = 0xC3;
                txb_Guid.Background = new SolidColorBrush(c);
            }
            else
            {
                txb_GuidError.Visibility = Visibility.Hidden;
                Color c = new Color();
                c.A = 0x00;
                c.R = 0xD7;
                c.G = 0xF2;
                c.B = 0xC3;
                txb_Guid.Background = new SolidColorBrush(c);
            }

            if (ValidateInputTab_3())
            {
                btn_Next3.IsEnabled = true;
            }
            else
            {
                btn_Next3.IsEnabled = false;
            }
        }

        // ParadigmName Changed
        private void txb_ParadigmName_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (ValidateInputTab_3())
            {
                btn_Next3.IsEnabled = true;
            }
            else
            {
                btn_Next3.IsEnabled = false;
            }
        }

        // RadioButton event for Registration scope selector
        private void rbb_System_Checked(object sender, RoutedEventArgs e)
        {
            SolutionGenerator.SelectedRegistration = Registration.Systemwide;
        }

        private void rbb_User_Checked(object sender, RoutedEventArgs e)
        {
            SolutionGenerator.SelectedRegistration = Registration.User;
        }

        private void rbb_Both_Checked(object sender, RoutedEventArgs e)
        {
            SolutionGenerator.SelectedRegistration = Registration.Both;
        }

        // Checkbox event for interface selection
        private void ckb_GenerateDSI_Checked(object sender, RoutedEventArgs e)
        {
            SolutionGenerator.SelectedInterface = ComponentInterface.Dependent;
            if (this.IsLoaded)
            {
                txb_MgaPath.IsEnabled = true;
                btn_BrowseMga.IsEnabled = true;
                ckb_AllParadigms.IsEnabled = false;

                if (ValidateInputTab_2())
                {
                    btn_Next2.IsEnabled = true;
                }
                else
                {
                    btn_Next2.IsEnabled = false;
                }

            }
        }

        private void ckb_GenerateDSI_UnChecked(object sender, RoutedEventArgs e)
        {
            SolutionGenerator.SelectedInterface = ComponentInterface.Independent;
            if (this.IsLoaded)
            {
                txb_MgaPath.IsEnabled = false;
                btn_BrowseMga.IsEnabled = false;
                ckb_AllParadigms.IsEnabled = true;

                if (ValidateInputTab_2())
                {
                    btn_Next2.IsEnabled = true;
                }
                else
                {
                    btn_Next2.IsEnabled = false;
                }
            }
        }

        private void txb_MgaPath_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (ValidateInputTab_2())
            {
                btn_Next2.IsEnabled = true;
            }
            else
            {
                btn_Next2.IsEnabled = false;
            }
        }

        // Store AddOn events
        private void ckb_Checked(object sender, RoutedEventArgs e)
        {
            int i = Int32.Parse(((CheckBox)sender).Name.Substring(5));
            SolutionGenerator.AddonEventSelection[i] = true;

            if (ValidateInputTab_4())
            {
                btn_Next4.IsEnabled = true;
            }
            else
            {
                btn_Next4.IsEnabled = false;
            }
        }

        private void ckb_Unchecked(object sender, RoutedEventArgs e)
        {
            int i = Int32.Parse(((CheckBox)sender).Name.Substring(5));
            SolutionGenerator.AddonEventSelection[i] = false;

            if (ValidateInputTab_4())
            {
                btn_Next4.IsEnabled = true;
            }
            else
            {
                btn_Next4.IsEnabled = false;
            }
        }

        private void txb_IconPath_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (ValidateInputTab_5())
            {
                btn_Next5.IsEnabled = true;
            }
            else
            {
                btn_Next5.IsEnabled = false;
            }
        }

        private void txb_ComponentName_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (ValidateInputTab_5())
            {
                btn_Next5.IsEnabled = true;
            }
            else
            {
                btn_Next5.IsEnabled = false;
            }
        }

        private void btn_OpenSolution_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                string pathToOpen = "\"" + txb_TargetFolder.Text + @"\" + txb_SolutionName.Text + @"\" + txb_SolutionName.Text + ".sln\"";

                string DevenvLocation = String.Empty;
                RegistryKey masterKey = Registry.LocalMachine.OpenSubKey(MainWindow.VS2010_REGISTRY_KEYPATH);
                if (masterKey == null)
                {
                    throw new Exception("Cannot locate Visual Studio 2010");
                }
                else
                {
                    DevenvLocation = masterKey.GetValue(MainWindow.VS2010_INSTALLDIR_KEYNAME).ToString();
                }
                masterKey.Close();

                DevenvLocation += "devenv.exe";

                System.Diagnostics.ProcessStartInfo pinfo = new System.Diagnostics.ProcessStartInfo();
                pinfo.Arguments = pathToOpen;
                pinfo.FileName = DevenvLocation;
                System.Diagnostics.Process myProc = System.Diagnostics.Process.Start(pinfo);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }
}
