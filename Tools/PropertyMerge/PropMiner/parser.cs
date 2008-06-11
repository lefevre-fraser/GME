using System;
using System.Xml;
using System.Text;
using System.IO;

namespace PropMiner
{
	/// <summary>
	/// Parses a typical (IMgaDumper created) xml file and creates clipboard
	/// snippet files containing attrs and regnodes of each fco/folder.
	/// </summary>
	public class Parser
	{
		protected string            m_input;
		protected string            m_outDir;
		protected int               m_count;
		protected bool              m_1DigOption = false;
		protected bool              m_2DigOption = false;

		protected const string      m_ignoreFile  = "objs2ignore.txt";
		protected const string      m_clipClosing = "</clipboard>";
		protected const string      m_clipPreamble = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" +
			"<!DOCTYPE clipboard SYSTEM \"mga.dtd\" [\n" +
			"<!ELEMENT clipboard (regnode|attribute)*>\n" +
			"<!ATTLIST clipboard\n" +
			"	acceptingkind CDATA #IMPLIED\n" +
			"	paradigmnamehint CDATA #IMPLIED\n" +
			">\n" +
			"]>\n" +
			"<clipboard>\n\t";

		public Parser( string[] args)
		{
			m_count      = 0;
			m_input      = "";
			m_outDir     = "";
			m_1DigOption = false;
			m_2DigOption = false;

			bool   out_dir_collect_mode = false;
			bool   in_xml_file_found    = false;

			if( args.Length == 0)
			{
				Console.WriteLine("Usage: PropMiner.exe <infile.xml> [-1|-2|-f] [-d <outdir>]");
				Console.WriteLine("   -1: clipfiles created into 1 digit subdirectories [of their guid]" );
				Console.WriteLine("   -2: clipfiles created into 2 digit subdirectories [of their guid]" );
				Console.WriteLine("   -f: flat output, clipfiles created into same directory" );
				Console.WriteLine("   -d: directory root under these get created Default: infile'sdir/clip/" );
				Console.WriteLine("");
				m_input = "input.xme";
				Console.WriteLine("[No arguments given, defaulting to {0}]", m_input);
			}
			else foreach( string curr in args)
			{
				if( curr.Length == 0) continue;

				if( out_dir_collect_mode)
				{
					m_outDir = curr;
					out_dir_collect_mode = false;
				}
				else if( curr[0] == '-' || curr[0] == '/')
				{
					if( curr.Length == 1) continue;

					if( curr[1] == 'd' || curr[1] == 'D')
						out_dir_collect_mode = true;
					else if( curr[1] == '1')
						m_1DigOption = true;
					else if( curr[1] == '2')
						m_2DigOption = true;
				}
				else if( !in_xml_file_found)
				{
					m_input = curr;
					in_xml_file_found = true;
				}
			}
			
			
			// some validation
			FileInfo fi = new FileInfo( m_input);
			if( !fi.Exists)
			{
				Console.WriteLine( "Input file '{0}' not found. Exiting.", m_input);
				throw new InvalidInputException();
			}

			if( m_1DigOption && m_2DigOption) 
			{
				Console.WriteLine( "Warning: -1 and -2 can't be used in the same time.Defaulting to -1.");
				m_2DigOption = false;
			}

//			if( m_1DigOption)      Console.WriteLine( "[One digit subdirectories will be created]");
//			else if( m_2DigOption) Console.WriteLine( "[Two digit subdirectories will be created]");
//			else                   Console.WriteLine( "[Files will be dumped in one directory.]");

			// outdir empty?
			if( m_outDir.Length == 0)
			{
				m_outDir = fi.DirectoryName + "/clip/"; // default to inputfile'sdir/clip/
			}
			else if( m_outDir[m_outDir.Length - 1] != '/' && m_outDir[m_outDir.Length - 1] != '\\')
			{
				m_outDir = m_outDir + "/";
			}

			DirectoryInfo di = new DirectoryInfo( m_outDir);
			if( !di.Exists)
			{
				di.Create(); // create the directory
				Console.WriteLine( "[Output directory created: {0}]", di.FullName);
			}

			Console.WriteLine( "[Analyzing file: '{0}' ...]", m_input);
		}

		protected void createDir( string p_val)
		{
			DirectoryInfo di = new DirectoryInfo( p_val);
			if( !di.Exists)
			{
				try
				{
					di.Create();
				}
				catch( Exception e)
				{
					cons( "Could not create directory " + p_val + ". Msg: " + e.Message);
				}
			}
		}

		protected void dump( string p_guid, StringBuilder p_content)
		{
			if( p_content.Length == 0)
			{
				// 0 sized files are not created, but their name
				// is appended to an m_ignoreFile file
				appendToIgnoredFile( p_guid);

				return;
			}

			Console.WriteLine( p_guid);
			++m_count;

			// directory prefix
			StringBuilder sb_file = new StringBuilder( m_outDir);
			if( m_1DigOption || m_2DigOption)
			{
				sb_file.Append( p_guid.Substring( 1, m_1DigOption? 1 : 2));
				sb_file.Append( '/');

				// we have now a m_outDir/98/ like dirname in sb_file
				createDir( sb_file.ToString()); // 98 subdir gets created
			}

			// filenm appended
			sb_file.Append( p_guid);

			// check for filename uniqueness
			while( true)
			{
				FileInfo fi = new FileInfo( sb_file.ToString());
				if( fi.Exists)
				{
					sb_file.Append("0");
				}
				else
					break;
			}
			

			// dumping the file
			using( StreamWriter sw = new StreamWriter( sb_file.ToString()))
			{
				begClip( sw); // enclose the captured info into <clipboard>
				sw.Write( p_content.ToString());
				endClip( sw); // </clipboard>
				sw.Close();
			}
		}

		protected void begClip( TextWriter w)
		{
			w.Write( m_clipPreamble);
		}

		protected void endClip( TextWriter w)
		{
			w.Write( m_clipClosing);
		}

		protected void cons( string p_text)
		{
			Console.Write( p_text);
		}

		protected void createIgnoreFile()
		{
			// create the empty file (if existed overwrite it)
			using( StreamWriter sw = new StreamWriter( m_outDir + m_ignoreFile, false /*=not append*/))
			{
				sw.Close();
			}
		}

		protected void appendToIgnoredFile( string p_elem)
		{
			if( p_elem == null || p_elem == "") 
				return;

			using( StreamWriter sw = new StreamWriter( m_outDir + m_ignoreFile, true /*= append*/))
			{
				sw.WriteLine( p_elem);
				sw.Close();
			}
		}

		/// <summary>
		/// public method for executing the parse and dump
		/// </summary>
		public void run()
		{
			m_count = 0;
			string [] gme_main_objs = new string[] { "model", "atom", "reference", "set", "connection", "folder" };
			string [] gme_sec_objs  = new string[] { "regnode", "attribute", "constraint" };

			// create the ignore objs file
			createIgnoreFile();

			// load an xml file using xmlTextReader
			XmlTextReader reader    = new XmlTextReader( m_input);
			bool          collect   = false;
			StringBuilder collected = new StringBuilder("");
			string        owners_id = "";
			string        owners_gd = "";

			try 
			{
				while (reader.Read())
				{
					switch (reader.NodeType)
					{
						case XmlNodeType.Text:
							if( collect) 
							{
								string x = reader.ReadOuterXml();
								collected.Append( x);
							}
							break;
						case XmlNodeType.Element:
							if( reader.Name == gme_main_objs[0]
								|| reader.Name == gme_main_objs[1]
								|| reader.Name == gme_main_objs[2]
								|| reader.Name == gme_main_objs[3]
								|| reader.Name == gme_main_objs[4]
								|| reader.Name == gme_main_objs[5])
							{
								// new owner element starts, dump the old values
								if( collect)
								{
									// if was collecting for <parent>, then there was no
									// </parent> closing tag, that's why we need to dump here
									dump( owners_gd, collected);
									collected = new StringBuilder("");
								}

								// set new owners
								collect = true;
								// order does not matter when reading attrs while at an element !
								// [empirical observation]
								owners_gd = reader.GetAttribute( "guid");
								owners_id = reader.GetAttribute( "id");

								// This implementation works only with the assumption 
								// that attrs and regnodes are always the first children
								// encountered for an owner [MgaDumper conforms to this].
								// Stack-based ownership maintanence is needed in case
								// attrs and regnodes may occur even after the closing tag
								// of sub-owners
							}
							else if( reader.Name == gme_sec_objs[0]
								|| reader.Name == gme_sec_objs[1]
								|| reader.Name == gme_sec_objs[2])
							{
								string x = reader.ReadOuterXml();

								if( collect)
								{
									collected.Append( x);
								}
								else
								{
									Console.WriteLine( "Error: not been collecting {0}", x);
								}
							}
							else if( reader.Name == "name")
								reader.Skip();
							break;
						case XmlNodeType.EndElement:
							if( reader.Name == gme_main_objs[0]
								|| reader.Name == gme_main_objs[1]
								|| reader.Name == gme_main_objs[2]
								|| reader.Name == gme_main_objs[3]
								|| reader.Name == gme_main_objs[4]
								|| reader.Name == gme_main_objs[5])
							{
								if( collect)
								{
									collect = false;
									// Typical case for this: no children and the closing tag
									// indicates that collection is over, dump needed.
									// [--Note--: if it had children, when the first <child> opentag
									// was met, dump already occurent for this element]
									dump( owners_gd, collected);
									collected = new StringBuilder("");
								}
							}
							else if( reader.Name == gme_sec_objs[0]
								|| reader.Name == gme_sec_objs[1]
								|| reader.Name == gme_sec_objs[2])
							{
								collected.Append( "\n");
 								reader.Skip();
							}

							break;
					}
				}
			}
			catch( Exception e)
			{
				Console.WriteLine( "Exception: " + e.Message);//. [Tip: Check if mga.dtd is in the directory of the input file!]");
				//Console.WriteLine( e.Message);
			}
			finally
			{
				reader.Close();
			}

			Console.WriteLine();
			Console.WriteLine( "{0} files written out", m_count);
		}
	}
}
