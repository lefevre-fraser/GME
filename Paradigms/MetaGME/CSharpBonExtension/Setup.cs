using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using BonExtension.Generators;
using System.IO;
using System.Text.RegularExpressions;

namespace BonExtension
{
    public partial class Setup : Form
    {
        public Setup()
        {
            InitializeComponent();
            init();
        }

        private void init()
        {
            this.textBox1.Text = General.InterpreterName;
            this.textBox2.Text = General.ClassName;
            this.textBox3.Text = General.NamespaceName;
            this.textBox4.Text = Directory.GetCurrentDirectory();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            folderBrowser = new FolderBrowserDialog();
            folderBrowser.SelectedPath = this.textBox4.Text;
            folderBrowser.Description = "Choose a directory for the source code of the interpreter";

            if (DialogResult.OK == folderBrowser.ShowDialog())
            {
                this.textBox4.Text = folderBrowser.SelectedPath;
            }
        }


        private void button3_Click(object sender, EventArgs e)
        {            
            try
            {
                DirectoryInfo di = new DirectoryInfo(this.textBox4.Text);
                if (!di.Exists)
                    throw new Exception("Directory does not exist");

                //valid class name
                if (!Regex.IsMatch(this.textBox2.Text, "^[a-zA-Z][a-zA-Z0-9_]*$"))
                    throw new Exception("Classname is not valid, it should match: '[a-zA-Z][a-zA-Z0-9_]*'");

                //valid namespace name
                if (!Regex.IsMatch(this.textBox3.Text, "^([a-zA-Z][a-zA-Z0-9_]*\\.)*[a-zA-Z][a-zA-Z0-9_]*$"))
                    throw new Exception(@"Namespace is not valid, it should match: '([a-zA-Z][a-zA-Z0-9_]*\.)*[a-zA-Z][a-zA-Z0-9_]*'");

                General.Path = di.FullName;
                General.InterpreterName = this.textBox1.Text;
                General.ClassName = this.textBox2.Text;
                General.NamespaceName = this.textBox3.Text;

                this.DialogResult = DialogResult.OK;
            }
            catch (Exception exc)
            {
                MessageBox.Show(exc.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}
