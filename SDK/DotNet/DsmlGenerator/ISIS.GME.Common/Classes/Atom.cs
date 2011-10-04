using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using GME.MGA;
using System.Diagnostics.Contracts;

namespace ISIS.GME.Common.Classes
{
	public class Atom : FCO, ISIS.GME.Common.Interfaces.Atom
	{
		public static Interfaces.Atom CreateGeneric(Interfaces.Container parent, string roleStr = null)
		{
			return ISIS.GME.Common.Utils.CreateObject<Atom>(parent, roleStr);
		}

		public virtual Aspect GenericAspect
		{
			get
			{
				return new Aspect(Impl as MgaFCO);
			}
		}

		public virtual IEnumerable<Aspect> Aspects
		{
			get
			{
				return Aspect.GetAspects(Impl as MgaFCO);
			}
			set
			{
				Aspect.SetAspects(Impl as MgaFCO, value);
			}
		}

		public PreferencesAtom Preferences
		{
			get { return new PreferencesAtom(Impl as global::GME.MGA.MgaFCO); }
		}

		/// <summary>
		/// 
		/// </summary>
		public virtual IEnumerable<ISIS.GME.Common.Interfaces.Atom> GenericInstances
		{
			get
			{
				Contract.Requires(Impl != null);
				Contract.Requires(Impl is MgaFCO);

				foreach (MgaFCO item in (Impl as MgaFCO).DerivedObjects)
				{
					if (item.IsInstance)
					{
						ISIS.GME.Common.Classes.Atom result = new Atom();
						result.Impl = item as MgaObject;
						yield return result;
					}
				}
			}
		}

		/// <summary>
		/// 
		/// </summary>
		public virtual IEnumerable<ISIS.GME.Common.Interfaces.Atom> GenericSubTypes
		{
			get
			{
				Contract.Requires(Impl != null);
				Contract.Requires(Impl is MgaFCO);

				foreach (MgaFCO item in (Impl as MgaFCO).DerivedObjects)
				{
					if (item.IsInstance ? false : item.ArcheType != null)
					{
						// if subtype
						ISIS.GME.Common.Classes.Atom result = new Atom();
						result.Impl = item as MgaObject;
						yield return result;
					}
				}
			}
		}
	}
}
