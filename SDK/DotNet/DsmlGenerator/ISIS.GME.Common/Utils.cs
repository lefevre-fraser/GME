using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using GME.MGA;
using System.Diagnostics.Contracts;
using GME.MGA.Meta;

namespace ISIS.GME.Common
{
	/// <summary>
	/// 
	/// </summary>
	public static class Utils
	{
		public static T CreateObject<T>(
			ISIS.GME.Common.Interfaces.Container parent,
			string roleStr = null)
			where T : ISIS.GME.Common.Classes.Base, new()
		{
			Contract.Requires(parent != null);

			T result = new T();
			string Kind = typeof(T).Name;

			if (parent.Impl is MgaModel)
			{
				MgaModel model = parent.Impl as MgaModel;
				MgaMetaRole role = null;

				if (string.IsNullOrEmpty(roleStr))
				{
					try
					{
						// try to use user defined role
						role = (model.MetaBase as MgaMetaModel).RoleByName[Kind];
					}
					catch (Exception ex)
					{
						StringBuilder sb = new StringBuilder();
						sb.AppendLine("Role was not found in the container.");
						sb.AppendLine("Paradigm violation.");
						sb.AppendFormat("Container type: {0} Requested role: {1}",
							parent.Kind,
							result.GetType().Name);
						throw new Exception(sb.ToString(), ex);
					}
				}
				else
				{
					try
					{
						// try to use user defined role
						role = (model.MetaBase as MgaMetaModel).RoleByName[roleStr];
					}
					catch (Exception ex)
					{
						StringBuilder sb = new StringBuilder();
						sb.AppendLine("Role was not found in the container.");
						sb.AppendLine("Paradigm violation.");
						sb.AppendFormat("Container type: {0} Requested role: {1}",
							parent.Kind,
							result.GetType().Name);
						throw new Exception(sb.ToString(), ex);
					}
				}
				try
				{
					MgaFCO fco = model.CreateChildObject(role);
					result.Impl = fco as MgaObject;
					return result;
				}
				catch (Exception ex)
				{
					StringBuilder sb = new StringBuilder();
					sb.AppendLine("New element could not be created.");
					sb.AppendFormat("Container type: {0} Requested role: {1}",
						parent.Kind,
						result.GetType().Name);
					throw new Exception(sb.ToString(), ex);
				}
			}
			else if (parent.Impl is MgaFolder)
			{
				if (string.IsNullOrEmpty(roleStr))
				{
					MgaFolder folder = parent.Impl as MgaFolder;

					foreach (MgaMetaFolder item in folder.MetaFolder.LegalChildFolders)
					{
						if (item.Name == Kind)
						{
							MgaFolder f = folder.CreateFolder(item);
							result.Impl = f as MgaObject;
							return result;
						}
					}
					if (result.Impl == null)
					{
						foreach (MgaMetaFCO item in folder.MetaFolder.LegalRootObjects)
						{
							if (item.Name == Kind)
							{
								MgaFCO fco = folder.CreateRootObject(item);
								result.Impl = fco as MgaObject;
								return result;
							}
						}
					}
				}
				else
				{
					MgaFolder folder = parent.Impl as MgaFolder;

					foreach (MgaMetaFolder item in folder.MetaFolder.LegalChildFolders)
					{
						if (item.Name == roleStr)
						{
							MgaFolder f = folder.CreateFolder(item);
							result.Impl = f as MgaObject;
							return result;
						}
					}
					if (result.Impl == null)
					{
						foreach (MgaMetaFCO item in folder.MetaFolder.LegalRootObjects)
						{
							if (item.Name == roleStr)
							{
								MgaFCO fco = folder.CreateRootObject(item);
								result.Impl = fco as MgaObject;
								return result;
							}
						}
					}
				}
			}

			return null;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="parent"></param>
		/// <param name="metaRef">meta ref of the new object</param>
		/// <param name="roleMetaRef">meta ref of the role (if the parent is a model)</param>
		/// <returns></returns>
		public static T CreateObject<T>(
			ISIS.GME.Common.Interfaces.Container parent,
			int metaRef,
			int roleMetaRef = 0)
			where T : ISIS.GME.Common.Classes.Base, new()
		{
			Contract.Requires(parent != null);

			T result = new T();

			if (parent.Impl is MgaModel)
			{
				MgaModel model = parent.Impl as MgaModel;
				MgaMetaRole role = null;
				try
				{
					// try to use user defined role
					role = (model.MetaBase as MgaMetaModel).
						Roles.
						Cast<MgaMetaRole>().
						FirstOrDefault(x => x.MetaRef == roleMetaRef);
				}
				catch (Exception ex)
				{
					StringBuilder sb = new StringBuilder();
					sb.AppendLine("Role was not found in the container.");
					sb.AppendLine("Paradigm violation.");
					sb.AppendFormat("Container type: {0} Requested role: {1}",
						parent.Kind,
						result.GetType().Name);
					throw new Exception(sb.ToString(), ex);
				}

				try
				{
					MgaFCO fco = model.CreateChildObject(role);
					result.Impl = fco as MgaObject;
					return result;
				}
				catch (Exception ex)
				{
					StringBuilder sb = new StringBuilder();
					sb.AppendLine("New element could not be created.");
					sb.AppendFormat("Container type: {0} Requested role: {1}",
						parent.Kind,
						result.GetType().Name);
					throw new Exception(sb.ToString(), ex);
				}
			}
			else if (parent.Impl is MgaFolder)
			{
				try
				{
					MgaFolder folder = parent.Impl as MgaFolder;

					MgaMetaFolder item = folder.MetaFolder.
						LegalChildFolders.
						Cast<MgaMetaFolder>().
						FirstOrDefault(x => x.MetaRef == metaRef);

					if (item != null)
					{
						// create new folder
						MgaFolder f = folder.CreateFolder(item);
						result.Impl = f as MgaObject;
						return result;
					}
					else
					{
						MgaMetaFCO itemFco = folder.MetaFolder.
							LegalRootObjects.
							Cast<MgaMetaFCO>().
							FirstOrDefault(x => x.MetaRef == metaRef);

						if (itemFco != null)
						{
							MgaFCO f = folder.CreateRootObject(itemFco);
							result.Impl = f as MgaObject;
							return result;
						}
					}
				}
				catch (Exception ex)
				{
					StringBuilder sb = new StringBuilder();
					sb.AppendLine("New element could not be created in folder.");
					sb.AppendFormat("Container type: {0} Requested child type: {1}",
						parent.Kind,
						result.GetType().Name);
					throw new Exception(sb.ToString(), ex);
				}
			}

			return null;
		}

		public static T MakeConnection<T>(
			Interfaces.FCO src,
			Interfaces.FCO dst,
			Interfaces.Reference srcRef = null,
			Interfaces.Reference dstRef = null,
			Interfaces.Container parent = null,
			string roleStr = null)
			where T : Interfaces.Connection, new()
		{
			Contract.Requires(src != null);
			Contract.Requires(dst != null);

			T result = new T();

			if (parent == null)
			{
				try
				{
					if (srcRef == null &&
							dstRef == null)
					{
						// set the parent if it is null
						if (src.ParentContainer.Impl == dst.ParentContainer.Impl)
						{
							parent = src.ParentContainer;
						}
						else if (src.ParentContainer.Impl == dst.ParentContainer.ParentContainer.Impl)
						{
							parent = src.ParentContainer;
						}
						else if (src.ParentContainer.ParentContainer.Impl == dst.ParentContainer.Impl)
						{
							parent = dst.ParentContainer;
						}
						else if (src.ParentContainer.ParentContainer.Impl == dst.ParentContainer.ParentContainer.Impl &&
										 src.ParentContainer.Impl != dst.ParentContainer.Impl)
						{
							parent = src.ParentContainer.ParentContainer;
						}
					}
					else if (srcRef != null &&
									 dstRef == null)
					{
						if (srcRef.ParentContainer.Impl == dst.ParentContainer.Impl)
						{
							parent = dst.ParentContainer;
						}
						else if (srcRef.ParentContainer.Impl == dst.ParentContainer.ParentContainer.Impl)
						{
							parent = srcRef.ParentContainer;
						}
					}
					else if (srcRef == null &&
									 dstRef != null)
					{
						if (src.ParentContainer.Impl == dstRef.ParentContainer.Impl)
						{
							parent = src.ParentContainer;
						}
						else if (src.ParentContainer.ParentContainer.Impl == dstRef.ParentContainer.Impl)
						{
							parent = dstRef.ParentContainer;
						}
					}
					else if (srcRef != null &&
									 dstRef != null)
					{
						if (srcRef.ParentContainer.Impl == dstRef.ParentContainer.Impl)
						{
							parent = srcRef.ParentContainer;
						}
					}
					if (parent == null)
					{
						throw new Exception("Parent could not be identified based on the given parameters.");
					}
				}
				catch (NullReferenceException ex)
				{
					// handle exception here
					throw ex;
				}
			}

			if (parent.Impl is MgaModel)
			{
				MgaModel model = parent.Impl as MgaModel;
				MgaMetaRole role = null;
				MgaFCO connection = null;

				try
				{
					if (string.IsNullOrEmpty(roleStr))
					{
						if (result.GetType().Name != typeof(Interfaces.Connection).Name)
						{
							try
							{
								role = (model.MetaBase as MgaMetaModel).RoleByName[result.GetType().Name];
							}
							catch (Exception ex)
							{
								StringBuilder sb = new StringBuilder();
								sb.AppendLine("Role was not found in the container.");
								sb.AppendLine("Paradigm violation.");
								sb.AppendFormat("Container type: {0} Requested role: {1}",
									parent.Kind,
									result.GetType().Name);
								throw new Exception(sb.ToString(), ex);
							}
						}
						else
						{
							// use default role
							string srcKind = src.Kind;
							string dstKind = dst.Kind;
							MgaMetaRoles roles = (model.MetaBase as MgaMetaModel).Roles;
							foreach (MgaMetaRole item in roles)
							{
								MgaMetaBase metaBase = item.MetaProject.FindObject[item.Kind.MetaRef];
								if (metaBase is MgaMetaConnection)
								{
									foreach (IMgaMetaConnJoint joint in (metaBase as MgaMetaConnection).Joints)
									{
										IEnumerable<MgaMetaPointerItem> srcSpecs = joint.PointerSpecByName["src"].Items.Cast<MgaMetaPointerItem>();
										IEnumerable<MgaMetaPointerItem> dstSpecs = joint.PointerSpecByName["dst"].Items.Cast<MgaMetaPointerItem>();
										if (srcSpecs.FirstOrDefault(x => x.Desc == srcKind) != null &&
											dstSpecs.FirstOrDefault(x => x.Desc == dstKind) != null)
										{
											// role found (first)
											role = item;
											break;
										}
									}
									if (role != null)
									{
										// role is ok
										break;
									}
								}
							}
						}
					}
					else
					{
						try
						{
							// try to use user defined role
							role = (model.MetaBase as MgaMetaModel).RoleByName[roleStr];
						}
						catch (Exception ex)
						{
							StringBuilder sb = new StringBuilder();
							sb.AppendLine("Role was not found in the container.");
							sb.AppendLine("Paradigm violation.");
							sb.AppendFormat("Container type: {0} Requested role: {1}",
								parent.Kind,
								result.GetType().Name);
							throw new Exception(sb.ToString(), ex);
						}
					}

					if (role == null)
					{
						throw new Exception("Role not found based on the given parameters.");
					}
					if (srcRef == null &&
								dstRef == null)
					{
						connection = model.CreateSimpleConnDisp(
							role,
							src.Impl as MgaFCO,
							dst.Impl as MgaFCO,
							null,
							null);
					}
					else if (srcRef != null &&
									 dstRef == null)
					{
						connection = model.CreateSimpleConnDisp(
							role,
							src.Impl as MgaFCO,
							dst.Impl as MgaFCO,
							srcRef.Impl as MgaFCO,
							null);
					}
					else if (srcRef == null &&
									 dstRef != null)
					{
						connection = model.CreateSimpleConnDisp(
							role,
							src.Impl as MgaFCO,
							dst.Impl as MgaFCO,
							null,
							dstRef.Impl as MgaFCO);
					}
					else if (srcRef != null &&
						dstRef != null)
					{
						connection = model.CreateSimpleConnDisp(
							role,
							src.Impl as MgaFCO,
							dst.Impl as MgaFCO,
							srcRef.Impl as MgaFCO,
							dstRef.Impl as MgaFCO);
					}
				}
				catch (Exception ex)
				{
					throw ex;
				}
			}
			else
			{
				throw new Exception("Parent could not be a folder.");
			}

			return result;
		}


		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="subject"></param>
		/// <returns></returns>
		public static T CreateObject<T>(MgaObject subject)
			where T : ISIS.GME.Common.Classes.Base, new()
		{
			// TODO: rename this function
			Contract.Requires(subject != null, "Subject cannot be null.");

			ISIS.GME.Common.Interfaces.Base newObject = null;

			//if (IsObjectCacheEnabled)
			//{
			//  if (ObjectCache.TryGetValue(subject, out newObject) == false)
			//  {
			//    // create new object and put it into the cache
			//    newObject = new T() { Impl = subject as MgaObject };
			//    ObjectCache.Add(subject, newObject);
			//  }
			//}
			//else
			{
				newObject = new T() { Impl = subject as MgaObject };
			}
			return newObject as T;
		}

		public static string ReplaceNames(this string oldName)
		{
			return oldName.
				Replace('(', '_').
				Replace(')', '_').
				Replace('/', '_').
				Replace("-", "_dash_").
				Replace(".", "_dot_").
				Replace(":", "_").
				Replace(' ', '_').
				Replace("&", "_and_");
		}

		//public static bool IsObjectCacheEnabled = true;

		//public static Dictionary<MgaObject, ISIS.GME.Common.Interfaces.Base> ObjectCache =
		//	new Dictionary<MgaObject, ISIS.GME.Common.Interfaces.Base>();

		public static IEnumerable<TResult> CastSrcConnections<TResult, TSource>(
			this TSource source, string kind = "")
			where TResult : ISIS.GME.Common.Classes.Base, new()
			where TSource : MgaFCO
		{
			Contract.Requires(source != null, "Subject cannot be null.");

			foreach (MgaConnPoint cp in source.PartOfConns)
			{
				MgaSimpleConnection simple = cp.Owner as MgaSimpleConnection;
				if (simple != null)
				{
					if (simple.Dst == source as MgaFCO)
					{
						TResult result = new TResult() { Impl = simple as MgaObject };

						if (string.IsNullOrEmpty(kind))
						{
							yield return result;
						}
						else if (simple.MetaBase.Name == kind)
						{
							yield return result;
						}
					}
				}
			}
		}

		public static IEnumerable<TResult> CastDstConnections<TResult, TSource>(
			this TSource source, string kind = "")
			where TResult : ISIS.GME.Common.Classes.Base, new()
			where TSource : MgaFCO
		{
			Contract.Requires(source != null, "Subject cannot be null.");

			foreach (MgaConnPoint cp in source.PartOfConns)
			{
				MgaSimpleConnection simple = cp.Owner as MgaSimpleConnection;
				if (simple != null)
				{
					if (simple.Src == source as MgaFCO)
					{
						TResult result = new TResult() { Impl = simple as MgaObject };

						if (string.IsNullOrEmpty(kind))
						{
							yield return result;
						}
						else if (simple.MetaBase.Name == kind)
						{
							yield return result;
						}
					}
				}
			}
		}

		public static TResult CastSrcEndRef<TResult, TSource>(
			this TSource source, string kind = "")
			where TResult : ISIS.GME.Common.Classes.Base, new()
			where TSource : MgaFCO
		{
			Contract.Requires(source != null, "Subject cannot be null.");
			Contract.Requires(source is MgaSimpleConnection, "Subject must be a MgaSimpleConnection");
			Contract.Requires((source as MgaSimpleConnection).Src != null, "Src cannot be null.");

			MgaSimpleConnection simple = source as MgaSimpleConnection;
			// TODO: use factory for valid casts
			if (kind == simple.Src.MetaBase.Name)
			{
				MgaFCO Ref = simple.SrcReferences.Cast<MgaFCO>().FirstOrDefault();
				if (Ref != null)
				{
					TResult result = new TResult() { Impl = Ref as MgaObject };
					return result;
				}
				else
				{
					return null;
				}
			}
			else if (string.IsNullOrEmpty(kind))
			{
				MgaFCO Ref = simple.SrcReferences.Cast<MgaFCO>().FirstOrDefault();
				if (Ref != null)
				{
					TResult result = new TResult() { Impl = Ref as MgaObject };
					return result;
				}
				else
				{
					return null;
				}
			}
			else
			{
				return null;
			}
		}

		public static TResult CastDstEndRef<TResult, TSource>(
			this TSource source, string kind = "")
			where TResult : ISIS.GME.Common.Classes.Base, new()
			where TSource : MgaFCO
		{
			Contract.Requires(source != null);
			Contract.Requires(source is MgaSimpleConnection);
			Contract.Requires((source as MgaSimpleConnection).Dst != null);

			MgaSimpleConnection simple = source as MgaSimpleConnection;
			// TODO: use factory for valid casts
			if (kind == simple.Dst.MetaBase.Name)
			{
				MgaFCO Ref = simple.DstReferences.Cast<MgaFCO>().FirstOrDefault();
				if (Ref != null)
				{
					TResult result = new TResult() { Impl = Ref as MgaObject };
					return result;
				}
				else
				{
					return null;
				}
			}
			else if (string.IsNullOrEmpty(kind))
			{
				MgaFCO Ref = simple.DstReferences.Cast<MgaFCO>().FirstOrDefault();
				if (Ref != null)
				{
					TResult result = new TResult() { Impl = Ref as MgaObject };
					return result;
				}
				else
				{
					return null;
				}
			}
			else
			{
				return null;
			}
		}

		public static TResult CastSrcEnd<TResult, TSource>(
			this TSource source, string kind = "")
			where TResult : ISIS.GME.Common.Classes.Base, new()
			where TSource : MgaFCO
		{
			Contract.Requires(source != null, "Subject cannot be null.");
			Contract.Requires(source is MgaSimpleConnection, "Subject must be a MgaSimpleConnection");
			Contract.Requires((source as MgaSimpleConnection).Src != null, "Src cannot be null.");

			MgaSimpleConnection simple = source as MgaSimpleConnection;
			// TODO: use factory for valid casts
			if (kind == simple.Src.MetaBase.Name)
			{
				TResult result = new TResult() { Impl = simple.Src as MgaObject };
				return result;
			}
			else if (string.IsNullOrEmpty(kind))
			{
				TResult result = new TResult() { Impl = simple.Src as MgaObject };
				return result;
			}
			else
			{
				return null;
			}
		}

		public static TResult CastDstEnd<TResult, TSource>(
			this TSource source, string kind = "")
			where TResult : ISIS.GME.Common.Classes.Base, new()
			where TSource : MgaFCO
		{
			Contract.Requires(source != null);
			Contract.Requires(source is MgaSimpleConnection);
			Contract.Requires((source as MgaSimpleConnection).Dst != null);

			MgaSimpleConnection simple = source as MgaSimpleConnection;
			// TODO: use factory for valid casts
			if (kind == simple.Dst.MetaBase.Name)
			{
				TResult result = new TResult() { Impl = simple.Dst as MgaObject };
				return result;
			}
			else if (string.IsNullOrEmpty(kind))
			{
				TResult result = new TResult() { Impl = simple.Dst as MgaObject };
				return result;
			}
			else
			{
				return null;
			}
		}

		public static IEnumerable<TResult> CastMgaChildren<TResult, TSource>(
			this TSource source, string kind = "")
			where TResult : ISIS.GME.Common.Classes.Base, new()
			where TSource : MgaObjects
		{
			Contract.Requires(source != null);

			IEnumerable<MgaObject> children = source.Cast<MgaObject>();
			ISIS.GME.Common.Interfaces.Base newObject = null;

			if (String.IsNullOrEmpty(kind))
			{
				// return all kinds
				foreach (MgaObject v in source)
				{
					newObject = new TResult() { Impl = v as MgaObject };
					yield return newObject as TResult;
				}
			}
			else
			{
				// return with the specifed kinds only
				foreach (MgaObject v in children.Where(x => x.MetaBase.Name == kind))
				{
					newObject = new TResult() { Impl = v as MgaObject };
					yield return newObject as TResult;
				}
			}
		}

		public static IEnumerable<TResult> CastMgaChildren<TResult, TSource>(
			this TSource source, int metaRef)
			where TResult : ISIS.GME.Common.Classes.Base, new()
			where TSource : MgaObjects
		{
			Contract.Requires(source != null);

			IEnumerable<MgaObject> children = source.Cast<MgaObject>();

			// return with the specifed kinds only
			foreach (MgaObject v in children.Where(x => x.MetaBase.MetaRef == metaRef))
			{
				TResult newObject = new TResult() { Impl = v as MgaObject };
				yield return newObject as TResult;
			}
		}

		public static IEnumerable<ISIS.GME.Common.Interfaces.Base> CastMgaChildren<TSource>(
			this TSource source, Dictionary<int, Type> metaRefTypes)
			where TSource : MgaObjects
		{
			Contract.Requires(source != null);

			IEnumerable<MgaObject> children = source.Cast<MgaObject>();

			// return with the specifed kinds only
			foreach (MgaObject v in children)
			{
				ISIS.GME.Common.Classes.Base newObject = null;
				newObject = Activator.CreateInstance(metaRefTypes[v.MetaBase.MetaRef]) as ISIS.GME.Common.Classes.Base;
				newObject.Impl = v as MgaObject;
				yield return newObject;
			}
		}


		public static IEnumerable<TResult> CastMgaObject<TResult, TSource>(
			this IEnumerable<TSource> source)
			where TResult : ISIS.GME.Common.Classes.Base, new()
			where TSource : MgaObject
		{
			Contract.Requires(source != null);

			foreach (var v in source)
			{
				yield return new TResult() { Impl = v as MgaObject };
			}
		}

		public static IEnumerable<TResult> CastMgaObject<TResult, TSource>(
			this TSource source)
			where TResult : ISIS.GME.Common.Classes.Base, new()
			where TSource : MgaObjects
		{
			return source.Cast<MgaObject>().CastMgaObject<TResult, MgaObject>();
		}


		/// <summary>
		/// Retrives only the specified type, which does NOT include
		/// the derived types.
		/// </summary>
		/// <typeparam name="TResult"></typeparam>
		/// <param name="source"></param>
		/// <returns></returns>
		public static IEnumerable<TResult> OfKind<TResult>(
			this IEnumerable<ISIS.GME.Common.Interfaces.Base> source)
			where TResult : ISIS.GME.Common.Interfaces.Base
		{
			string kind = typeof(TResult).Name;
			return source.Where(x => x.Kind == kind).Cast<TResult>();
		}


		public static int GetEnumItemNumber(MgaFCO mgaFCO, string attributeName)
		{
			Contract.Requires(mgaFCO != null);
			Contract.Requires(mgaFCO.MetaBase is MgaMetaFCO);
			Contract.Requires(string.IsNullOrEmpty(attributeName) == false);

			try
			{
				MgaMetaFCO meta = (mgaFCO.MetaBase as MgaMetaFCO);
				MgaMetaAttribute attr = meta.AttributeByName[attributeName];

				string selectedItemValue = mgaFCO.Attribute[attr].StringValue;
				int i = 0;
				foreach (MgaMetaEnumItem item in attr.EnumItems)
				{
					if (item.Value == selectedItemValue)
					{
						return i;
					}
					i++;
				}
				throw new Exception("Attribute / selected item was not found.");
			}
			catch (Exception)
			{

				throw;
			}

		}

		public static void SetEnumItem(MgaFCO mgaFCO, string attributeName, int index)
		{
			Contract.Requires(mgaFCO != null);
			Contract.Requires(mgaFCO.MetaBase is MgaMetaFCO);
			Contract.Requires(string.IsNullOrEmpty(attributeName) == false);

			try
			{
				MgaMetaFCO meta = (mgaFCO.MetaBase as MgaMetaFCO);
				MgaMetaAttribute attr = meta.AttributeByName[attributeName];

				mgaFCO.Attribute[attr].StringValue = attr.EnumItems[index + 1].Value;
			}
			catch (Exception ex)
			{
				throw ex;
			}
		}

		public static ISIS.GME.Common.Interfaces.FCO CastReferred(
			MgaReference mgaReference,
			Dictionary<int, Type> metaRefTypes)
		{
			Contract.Requires(mgaReference != null);

			MgaFCO referred = mgaReference.Referred;
			if (referred == null)
			{
				return null;
			}
			else
			{
				ISIS.GME.Common.Interfaces.FCO result = null;
				Type t = metaRefTypes[referred.MetaBase.MetaRef];
				result = Activator.CreateInstance(t) as ISIS.GME.Common.Interfaces.FCO;
				(result as ISIS.GME.Common.Classes.FCO).Impl = referred as MgaObject;
				return result;
			}
		}


		public static IEnumerable<T> CastSetMembers<T>(
			MgaSet mgaSet,
			string kind = null)
			where T : ISIS.GME.Common.Classes.FCO, new()
		{
			Contract.Requires(mgaSet != null);

			if (typeof(T) != typeof(ISIS.GME.Common.Classes.FCO))
			{
				kind = typeof(T).Name;
			}

			if (string.IsNullOrEmpty(kind))
			{
				// return with all kind
				foreach (MgaFCO item in mgaSet.Members)
				{
					yield return new T() { Impl = item as MgaObject };
				}
			}
			else
			{
				foreach (MgaFCO item in mgaSet.Members)
				{
					if (item.Meta.Name == kind)
					{
						yield return new T() { Impl = item as MgaObject };
					}
				}
			}
		}

		public static IEnumerable<T> MembersOfSet<T>(
			MgaFCO mgaFCO,
			string kind = null)
			where T : ISIS.GME.Common.Classes.Set, new()
		{
			Contract.Requires(mgaFCO != null);

			if (typeof(T) != typeof(ISIS.GME.Common.Classes.Set))
			{
				kind = typeof(T).Name;
			}

			if (string.IsNullOrEmpty(kind))
			{
				// return with all kind
				foreach (MgaFCO item in mgaFCO.MemberOfSets)
				{
					yield return new T() { Impl = item as MgaObject };
				}
			}
			else
			{
				foreach (MgaFCO item in mgaFCO.MemberOfSets)
				{
					if (item.Meta.Name == kind)
					{
						yield return new T() { Impl = item as MgaObject };
					}
				}
			}
		}

		public static IEnumerable<Interfaces.Reference> ReferencedBy<T>(
			MgaFCO mgaFCO,
			string kind = null)
			where T : ISIS.GME.Common.Classes.Reference, new()
		{
			Contract.Requires(mgaFCO != null);

			if (typeof(T) != typeof(ISIS.GME.Common.Classes.Reference))
			{
				kind = typeof(T).Name;
			}

			if (string.IsNullOrEmpty(kind))
			{
				// return with all kind
				foreach (MgaFCO item in mgaFCO.ReferencedBy)
				{
					yield return new T() { Impl = item as MgaObject };
				}
			}
			else
			{
				foreach (MgaFCO item in mgaFCO.ReferencedBy)
				{
					if (item.Meta.Name == kind)
					{
						yield return new T() { Impl = item as MgaObject };
					}
				}
			}
		}

		public static void SetReferred(
			MgaReference Impl,
			ISIS.GME.Common.Interfaces.FCO value)
		{
			Contract.Requires(Impl != null);
			Contract.Requires(Impl is MgaReference);

			try
			{
				if (value != null)
				{
					(Impl as MgaReference).Referred = value.Impl as MgaFCO;
				}
				else
				{
					(Impl as MgaReference).Referred = null;
				}
			}
			catch (Exception ex)
			{
				throw new Exception("Referred value could not be set.", ex);
			}
		}

		public static IEnumerable<ISIS.GME.Common.Interfaces.FCO> CastReferencedBy(
			MgaFCO mgaFCO,
			Dictionary<int, Type> dictionary)
		{
			Contract.Requires(mgaFCO != null);

			int metaRef;
			ISIS.GME.Common.Interfaces.FCO fco = null;

			foreach (MgaFCO item in mgaFCO.ReferencedBy)
			{
				try
				{
					metaRef = item.MetaBase.MetaRef;
					fco = Activator.CreateInstance(dictionary[metaRef]) as ISIS.GME.Common.Interfaces.FCO;
					(fco as ISIS.GME.Common.Classes.FCO).Impl = item as MgaObject;
				}
				catch (Exception ex)
				{
					throw ex;
				}
				yield return fco;
			}
		}

		public static IEnumerable<ISIS.GME.Common.Interfaces.FCO> CastSetMembers(
			MgaSet mgaSet,
			Dictionary<int, Type> dictionary)
		{
			Contract.Requires(mgaSet != null);


			//List<ISIS.GME.Common.Interfaces.FCO> result = new List<Interfaces.FCO>();
			int metaRef;
			ISIS.GME.Common.Interfaces.FCO fco = null;
			Type t = null;
			foreach (MgaFCO item in mgaSet.Members)
			{
				metaRef = item.MetaBase.MetaRef;
				if (dictionary.TryGetValue(metaRef, out t))
				{
					fco = Activator.CreateInstance(t) as ISIS.GME.Common.Interfaces.FCO;
					(fco as ISIS.GME.Common.Classes.FCO).Impl = item as MgaObject;
					yield return fco;
				}
			}
		}

		public static IEnumerable<Interfaces.FCO> CastMembersOfSet(MgaFCO mgaFCO,
			Dictionary<int, Type> dictionary)
		{
			Contract.Requires(mgaFCO != null);

			int metaRef;
			ISIS.GME.Common.Interfaces.FCO fco = null;
			Type t = null;
			foreach (MgaFCO item in mgaFCO.MemberOfSets)
			{
				metaRef = item.MetaBase.MetaRef;
				if (dictionary.TryGetValue(metaRef, out t))
				{
					fco = Activator.CreateInstance(t) as ISIS.GME.Common.Interfaces.FCO;
					(fco as ISIS.GME.Common.Classes.FCO).Impl = item as MgaObject;
					yield return fco;
				}
			}
		}
	}
}
