using System;

namespace PropMiner
{
	/// <summary>
	/// Main class
	/// </summary>
	class AppMain
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main(string[] args)
		{
			try
			{
				Parser p = new Parser( args);
				p.run();
			}
			catch( InvalidInputException)
			{
			}
			catch( Exception e)
			{
				Console.WriteLine( e.Message);
			}
		}
	}

	class InvalidInputException : Exception
	{}
}
