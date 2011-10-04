using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using GME.MGA;
using System.Diagnostics.Contracts;
using GME.MGA.Meta;

namespace ISIS.GME.Common.Classes
{
	public class Reference : FCO, ISIS.GME.Common.Interfaces.Reference
	{
		public static Interfaces.Reference CreateGeneric(Interfaces.Container parent, string roleStr = null)
		{
			return ISIS.GME.Common.Utils.CreateObject<Reference>(parent, roleStr);
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

		public PreferencesReference Preferences
		{
			get { return new PreferencesReference(Impl as global::GME.MGA.MgaFCO); }
		}


		/// <summary>
		/// 
		/// </summary>
		public virtual IEnumerable<ISIS.GME.Common.Interfaces.Reference> GenericInstances
		{
			get
			{
				Contract.Requires(Impl != null);
				Contract.Requires(Impl is MgaFCO);

				foreach (MgaFCO item in (Impl as MgaFCO).DerivedObjects)
				{
					if (item.IsInstance)
					{
						ISIS.GME.Common.Classes.Reference result = new Reference();
						result.Impl = item as MgaObject;
						yield return result;
					}
				}
			}
		}

		/// <summary>
		/// 
		/// </summary>
		public virtual IEnumerable<ISIS.GME.Common.Interfaces.Reference> GenericSubTypes
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
						ISIS.GME.Common.Classes.Reference result = new Reference();
						result.Impl = item as MgaObject;
						yield return result;
					}
				}
			}
		}


		public virtual ISIS.GME.Common.Interfaces.FCO GenericReferred
		{
			get
			{
				MgaFCO Referred = (Impl as MgaReference).Referred;
				if (Referred != null)
				{
					return Utils.CreateObject<FCO>(Referred as MgaObject);
				}
				else
				{
					return null;
				}
			}
			set
			{
				Contract.Requires(Impl is MgaReference);
				Contract.Requires(value != null);
				Contract.Requires(value.Impl is MgaFCO);
				
				MgaFCO fco = value.Impl as MgaFCO;
				MgaReference reference = Impl as MgaReference;

				try
				{
					MgaMetaPointerItem item = null;
					
					item = (reference.MetaBase as MgaMetaReference).
						RefSpec.
						Items.
						Cast<MgaMetaPointerItem>().
						FirstOrDefault(x => x.Desc == fco.Meta.Name);

					if (item != null)
					{
						reference.Referred = fco;
					}
					else
					{
						// TODO: meaningful message types etc.
						throw new Exception("Paradigm violation.");
					}
				}
				catch (Exception ex)
				{
					throw new Exception("Referred object could not be set.", ex);
				}
			}
		}

		public override void Serialize(
			ISIS.GME.Common.IndentedStreamWriter writer,
			Serializer.Type type = Serializer.Type.OnlyThisObject)
		{
			// serialize this object
			StringBuilder sb = new StringBuilder();
			string RefName = "null";
			if (GenericReferred != null)
			{
				RefName = GenericReferred.Name;
			}

			sb.AppendFormat(
				"{0} [--> {1}]",
				Name,
				RefName);

			writer.WriteLine(sb.ToString(), true);

			if ((type == Serializer.Type.SubGraph ||
				type == Serializer.Type.Children) &&
				this is Interfaces.Container)
			{
				writer.Depth++;
				// serialize child objects
				foreach (Interfaces.Base b in (this as Interfaces.Container).AllChildren)
				{
					if (type == Serializer.Type.SubGraph)
					{
						b.Serialize(writer, type);
					}
					else if (type == Serializer.Type.Children)
					{
						b.Serialize(writer, Serializer.Type.OnlyThisObject);
					}
				}
				writer.Depth--;
			}
		}
	}
}
