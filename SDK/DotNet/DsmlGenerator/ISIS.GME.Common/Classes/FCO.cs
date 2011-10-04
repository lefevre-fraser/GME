using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using GME.MGA;

namespace ISIS.GME.Common.Classes
{
	/// <summary>
	/// Represents the generic domain independent FCO.
	/// </summary>
	public class FCO : Base, ISIS.GME.Common.Interfaces.FCO
	{
		/// <summary>
		/// Note: If you write domain specific code, do NOT use this.
		/// </summary>
		public virtual ISIS.GME.Common.Interfaces.FCO ArcheType
		{
			get
			{
				if ((Impl as MgaFCO).ArcheType == null)
				{
					return null;
				}
				else
				{
					return Utils.CreateObject<FCO>(Impl);
				}
			}
		}


		/// <summary>
		/// Note: If you write domain specific code, do NOT use this.
		/// </summary>
		public virtual IEnumerable<ISIS.GME.Common.Interfaces.Connection> AllSrcConnections
		{
			get
			{
				return Utils.CastSrcConnections<Connection, MgaFCO>(Impl as MgaFCO);
			}
		}

		/// <summary>
		/// Note: If you write domain specific code, do NOT use this.
		/// </summary>
		public virtual IEnumerable<ISIS.GME.Common.Interfaces.Connection> AllDstConnections
		{
			get
			{
				return Utils.CastDstConnections<Connection, MgaFCO>(Impl as MgaFCO);
			}
		}

		public bool IsInstance
		{
			get { return (Impl as MgaFCO).IsInstance; }
		}

		public bool IsSubtype
		{
			get { return 
				(Impl as MgaFCO).IsInstance ? 
				false : 
				(Impl as MgaFCO).ArcheType != null; }
		}

		public IEnumerable<Interfaces.Set> GenericMembersOfSet
		{
			get { return Utils.MembersOfSet<Classes.Set>(Impl as MgaFCO); }
		}

		public IEnumerable<Interfaces.Reference> GenericReferencedBy
		{
			get { return Utils.ReferencedBy<Classes.Reference>(Impl as MgaFCO); }
		}

		///// <summary>
		///// This property must be implemented in the derived class.
		///// </summary>
		//public virtual IEnumerable<ISIS.GME.Common.Interfaces.FCO> InstanceCollection
		//{
		//  get
		//  {
		//    throw new NotSupportedException(
		//      "This property must be implemented in the derived class.");
		//  }
		//}

		///// <summary>
		///// This property must be implemented in the derived class.
		///// </summary>
		//public virtual IEnumerable<ISIS.GME.Common.Interfaces.FCO> DerivedCollection
		//{
		//  get
		//  {
		//    throw new NotSupportedException(
		//      "This property must be implemented in the derived class.");
		//  }
		//}

		///// <summary>
		///// This property must be implemented in the derived class.
		///// </summary>
		//public virtual IEnumerable<ISIS.GME.Common.Interfaces.FCO> SubtypeCollection
		//{
		//  get
		//  {
		//    throw new NotSupportedException(
		//      "This property must be implemented in the derived class.");
		//  }
		//}

	}
}
