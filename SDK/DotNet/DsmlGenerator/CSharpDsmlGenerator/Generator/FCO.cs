using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.CodeDom;
using GME.MGA;
using ISIS.GME.Common;
using ISIS.GME.Common.Classes;
using System.Diagnostics.Contracts;

namespace CSharpDSMLGenerator.Generator
{
	public partial class FCO : Base
	{
		public FCO(
			MgaObject subject,
			CodeTypeReferenceCollection baseTypes,
			CodeTypeReferenceCollection attributes) :
			base(subject, baseTypes, attributes)
		{
		}

		public override void GenerateClassCode()
		{

			base.GenerateClassCode();

			string ClassName = Subject.Name;

			if (Subject.MetaBase.Name == "RootFolder")
			{
				ClassName = "RootFolder";
			}

			ClassCodeGetRootFolder();

			ClassCodeArcheType();

			ClassCodeRoles();

			ClassCodeSrcDstConnections();

			ClassCodeSrcDstEnd();

			ClassCodeParentContainer();

			ClassCodeAttributes();

			ClassCodeChildren();

			ClassCodeMakeConnection();

			ClassCodeCreateObject();

			ClassCodeReferred();

			ClassCodeReferencedBy();

			ClassCodeSetMembers();

			ClassCodeMemberOfSets();
		}

		public override void GenerateInterfaceCode()
		{
			base.GenerateInterfaceCode();


			if (Subject.MetaBase.Name == "RootFolder")
			{
				// rootfolder specific properties
				CodeMemberProperty libraryName = new CodeMemberProperty()
				{
					Attributes = MemberAttributes.Public,
					HasGet = true,
					Name = "LibraryName",
					Type = new CodeTypeReference(typeof(string)),
				};

				libraryName.Comments.Add(
					new CodeCommentStatement(Configuration.Comments.LibraryName, true));

				GeneratedInterface.Types[0].Members.Add(libraryName);

				CodeMemberProperty library = new CodeMemberProperty()
				{
					Attributes = MemberAttributes.Public,
					HasGet = true,
					Name = "LibraryCollection",
					Type = new CodeTypeReference(
						"IEnumerable<" + Configuration.ProjectIntefaceNamespace +
						".RootFolder" + ">"),
				};

				library.Comments.Add(
					new CodeCommentStatement(Configuration.Comments.LibraryCollection, true));

				GeneratedInterface.Types[0].Members.Add(library);
			}


			InterfaceCodeSrcDstConnections();

			IntefaceCodeSrcDstEnd();

			InterfaceCodeArcheType();

			InterfaceCodeAttributes();

			InterfaceCodeChildren();

			InterfaceCodeReferred();

			InterfaceCodeReferencedBy();

			InterfaceCodeSetMembers();

			InterfaceCodeMemberOfSets();
		}
	}
}
