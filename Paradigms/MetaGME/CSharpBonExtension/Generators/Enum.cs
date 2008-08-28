using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace BonExtension.Generators
{
    public class Enum
    {
        public class Template
        {
            public static readonly string Enums =
@"
namespace {0}
{{
    {1}
}}
";
        }

        private static StringBuilder enumsForAttributes = new StringBuilder();
        private static List<string> names = new List<string>();
        public static void AddEnum(string name, string enum1)
        {
            if (!names.Contains(name))
            {
                enumsForAttributes.AppendLine(enum1);
                names.Add(name);
            }
        }
        public static void Clear()
        {
            enumsForAttributes = new StringBuilder();
            names.Clear();
        }

        public static string GenerateEnums()
        {
            StringBuilder sb = new StringBuilder();

            sb.AppendFormat(
                Enum.Template.Enums,
                General.NamespaceName,
                enumsForAttributes.ToString());

            return sb.ToString();
        }

        public static void Save()
        {
            Directory.CreateDirectory(Path.Combine(General.Path, General.ClassName));
            Directory.CreateDirectory(Path.Combine(General.Path, General.ClassName) + "\\BonExtension");
            using (TextWriter tw = new StreamWriter(Path.Combine(General.Path, General.ClassName) + @"\BonExtension\Enums.cs"))
            {
                tw.WriteLine(GenerateEnums());
            }
        }
    }
}
