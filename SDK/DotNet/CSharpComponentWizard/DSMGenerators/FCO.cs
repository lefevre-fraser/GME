using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace DSM.Generators
{
    public class FCO : Object
    {
        new public class Template
        {
            #region Container
            public static readonly string ContainerFolderInner =
@"
                        if (this.mgaObject.ParentFolder.MetaBase.Name == ""{0}"")
                            return new {0}(this.mgaObject.ParentFolder);
";
            public static readonly string ContainerModelInner =
@"
                    if (this.mgaObject.ParentModel.MetaBase.Name == ""{0}"")
                        return new {1}(this.mgaObject.ParentModel);
";
            public static readonly string Container =
@"
        public IContainer Container
        {{
            get
            {{
                if (this.mgaObject.ParentModel != null)
                {{
                    {0}
                }}
                else if (this.mgaObject.ParentFolder != null)
                {{
                    if (this.mgaObject.ParentFolder == MgaGateway.project.RootFolder)
                    {{
                        return new RootFolder(MgaGateway.project as MGALib.IMgaFolder);
                    }}
                    else
                    {{
                        {1}
                    }}
                }}

                return null;
            }}
        }}
";
            #endregion
            #region Attribute
            public static readonly string Attribute =
@"
        public {0} {1}
        {{
            get
            {{
                return mgaObject.get_{2}AttrByName(""{1}"");
            }}

            set
            {{
                mgaObject.set_{2}AttrByName(""{1}"", value);
            }}
        }}
";

            public static readonly string AttributeInterface =
@"
        {0} {1} {{ get; set; }}
";

            public static readonly string AttributeEnum =
@"
        public {0}Enum {0}
        {{
            get
            {{
                return ({0}Enum) Enum.Parse(typeof({0}Enum), mgaObject.get_StrAttrByName(""{0}""), true); 
            }}

            set
            {{                
                mgaObject.set_StrAttrByName(""{0}"", Enum.GetName(typeof({0}Enum), value));
            }}
        }}
";

            public static readonly string Enum =
@"
        public enum {0}Enum
        {{
            {1}
        }}
";
            #endregion
            #region Relationship
            public static readonly string Relationship =
@"
        public IEnumerable<{0}> {0}{4}
        {{
            get {{ return Get{1}{3}s(); }}
        }}

        public IEnumerable<{0}> Get{1}{3}s()
        {{
            MgaConnPoints points = mgaObject.PartOfConns;
            foreach (MgaConnPoint point in points)
            {{
                //point.owner is the connection object
                if (point.Owner.MetaBase.Name == ""{1}"")
                {{
                    foreach (MgaConnPoint connPoint in point.Owner.ConnPoints)
                    {{
{2}
                    }}
                }}
            }}
        }}
";
            public static readonly string RelationshipInner =
@"
                        if (connPoint.target.ID != this.ID  && connPoint.target.MetaBase.Name == ""{0}"")
                            yield return new {1}(connPoint.target as {2});
";
            public static readonly string RelationshipInterface =
@"
        IEnumerable<{0}> {0}{3}{{get;}}
        IEnumerable<{0}> Get{1}{2}s();
";
            #endregion
            #region Connection
            public static readonly string Connection =
@"
        public IEnumerable<{0}> Get{0}s()
        {{
            MgaConnPoints points = mgaObject.PartOfConns;
            foreach (MgaConnPoint point in points)
            {{
                //point.owner is the connection object
{1}
            }}
        }}
";
            public static readonly string ConnectionInner =
@"
                if (point.Owner.MetaBase.Name == ""{0}"")
                    yield return new {1}(point.Owner as {2});
";
            public static readonly string ConnectionInterface =
@"
        IEnumerable<{0}> Get{0}s();
";
            #endregion
            #region General
            public static readonly string Interface =
@"
namespace {0}
{{
    public interface {1} : {2}
    {{
        IContainer Container{{get;}}
        #region Common
/*
{3}
{4}
*/
        #endregion

        #region Attributes
{5}
        #endregion
        
        #region Connections
{6}
        #endregion

        #region Relationships
{7}
        #endregion

        #region Other
{8}
        #endregion
    }}
}}
";
            
            public static readonly string Class =
@"
namespace {0}
{{
    public class {1} : {2}
    {{
        internal {3} mgaObject;
        internal static {9} mgaMetaObject = MgaGateway.GetMetaByName(""{10}"") as {9};
        public {1}({3} mgaObject)
        {{
            this.mgaObject = mgaObject;
        }}    

{11}

        #region Common
{4}
        #endregion

        #region Attributes
{5}
        #endregion
        
        #region Connections
{6}
        #endregion

        #region Relationships
{7}
        #endregion

        #region Other
{8}
        #endregion
    }}
}}
";
            #endregion
        }


        public FCO(MGALib.IMgaAtom mgaObject)
        {
            className = mgaObject.Name;
            baseInterfaceName = "IFCO";

            memberType = "IMgaFCO";

            namespaceName = Generator.NamespaceName;

            this.mgaObject = mgaObject;

            if (Object.ElementsByName.ContainsKey(mgaObject.Name))
            {
                //TODO
                //throw new Exception(string.Format("Element name is not unique: {0}", mgaObject.Name));
                DSM.GeneratorFacade.Errors.Add(string.Format("Element name is not unique: {0}", mgaObject.Name));
            }
            else
            {
                Object.ElementsByName.Add(mgaObject.Name, this);
            }
            if (InRootFolder)
                RootFolder.RootObject.Add(this);
        }

        internal string ProperClassName
        {
            get
            {
                if (this.HasChildren)
                    return this.className + "Impl";
                else
                    return this.className;
            }
        }



        #region Inheritance
        internal override IEnumerable<DerivedWithKind> Parents
        {
            get
            {
                foreach (MGALib.IMgaObject mgaObject in this.MgaObjects)
                {
                    MGALib.IMgaFCO fco = mgaObject as MGALib.IMgaFCO;
                    foreach (MGALib.IMgaConnPoint conn in fco.PartOfConns)
                    {
                        if (conn.Owner.Meta.Name.Contains("Derived") &&
                            conn.Owner.Meta.Name.Contains("Inheritance"))
                        {
                            foreach (MGALib.IMgaConnPoint connOther in conn.Owner.ConnPoints)
                            {
                                if (connOther.target.ID != mgaObject.ID)
                                {
                                    //we have found an inheritance: connOther.target
                                    foreach (MGALib.IMgaConnPoint conn2 in connOther.target.PartOfConns)
                                    {
                                        if (conn2.Owner.Meta.Name.Contains("Base") &&
                                            conn2.Owner.Meta.Name.Contains("Inheritance"))
                                        {
                                            foreach (MGALib.IMgaConnPoint connOther2 in conn2.Owner.ConnPoints)
                                            {
                                                if (connOther2.target.ID != conn2.target.ID)
                                                {
                                                    DerivedWithKind.InhType type = DerivedWithKind.InhType.General;
                                                    if (conn2.Owner.Meta.Name.Contains("Int"))
                                                        type = DerivedWithKind.InhType.Interface;
                                                    else if (conn2.Owner.Meta.Name.Contains("Imp"))
                                                        type = DerivedWithKind.InhType.Implementation;

                                                    if (connOther2.target.MetaBase.Name.Contains("Proxy"))
                                                    {
                                                        if (Object.ProxyCache.ContainsKey(connOther2.target.Name))
                                                            yield return new DerivedWithKind(){Rel = Object.ElementsByName[Object.ProxyCache[connOther2.target.Name]] as FCO, Type= type};
                                                        else
                                                            DSM.GeneratorFacade.Errors.Add("Proxy '" + connOther2.target.Name + "' is not found");
                                                    }
                                                    else
                                                    {
                                                        if (Object.ElementsByName.ContainsKey(connOther2.target.Name))
                                                            yield return new DerivedWithKind() { Rel = Object.ElementsByName[connOther2.target.Name] as FCO, Type = type };
                                                        else
                                                        {
                                                            //TODO
                                                            //throw new Exception(connOther2.target.Name + " is not cached");
                                                            DSM.GeneratorFacade.Errors.Add(connOther2.target.Name + " is not found");
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        internal IEnumerable<DerivedWithKind> Children
        {
            get
            {
                foreach (MGALib.IMgaObject mgaObject in this.MgaObjects)
                {
                    MGALib.IMgaFCO fco = mgaObject as MGALib.IMgaFCO;
                    foreach (MGALib.IMgaConnPoint conn in fco.PartOfConns)
                    {
                        if (conn.Owner.Meta.Name.Contains("Base") &&
                            conn.Owner.Meta.Name.Contains("Inheritance"))
                        {
                            foreach (MGALib.IMgaConnPoint connOther in conn.Owner.ConnPoints)
                            {
                                if (connOther.target.ID != mgaObject.ID)
                                {
                                    //we have found an inheritance: connOther.target
                                    foreach (MGALib.IMgaConnPoint conn2 in connOther.target.PartOfConns)
                                    {
                                        if (conn2.Owner.Meta.Name.Contains("Derived") &&
                                            conn2.Owner.Meta.Name.Contains("Inheritance"))
                                        {
                                            foreach (MGALib.IMgaConnPoint connOther2 in conn2.Owner.ConnPoints)
                                            {
                                                if (connOther2.target.ID != conn2.target.ID)
                                                {
                                                    DerivedWithKind.InhType type = DerivedWithKind.InhType.General;
                                                    if (conn2.Owner.Meta.Name.Contains("Int"))
                                                        type = DerivedWithKind.InhType.Interface;
                                                    else if (conn2.Owner.Meta.Name.Contains("Imp"))
                                                        type = DerivedWithKind.InhType.Implementation;


                                                    if (connOther2.target.MetaBase.Name.Contains("Proxy"))
                                                    {
                                                        if (Object.ProxyCache.ContainsKey(connOther2.target.Name))
                                                            yield return new DerivedWithKind() { Rel = Object.ElementsByName[Object.ProxyCache[connOther2.target.Name]] as FCO, Type = type };
                                                        else
                                                            DSM.GeneratorFacade.Errors.Add("Proxy '" + connOther2.target.Name + "' is not found");
                                                    }
                                                    else
                                                    {
                                                        if (Object.ElementsByName.ContainsKey(connOther2.target.Name))
                                                            yield return new DerivedWithKind() { Rel = Object.ElementsByName[connOther2.target.Name] as FCO, Type = type };
                                                        else
                                                        {
                                                            //todo
                                                            DSM.GeneratorFacade.Errors.Add(connOther2.target.Name + " is not found");
                                                            //throw new Exception(connOther2.target.Name + " is not cached");
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        internal IEnumerable<DerivedWithKind> ChildrenRecursive
        {
            get 
            {
                foreach (DerivedWithKind child in Children)
                {
                    yield return child;
                }
                foreach (DerivedWithKind child in Children)
                {
                    foreach (DerivedWithKind child2 in child.Rel.ChildrenRecursive)
                    {
                        yield return child2;
                    }
                }
            }
        }

        internal override bool HasChildren
        {
            get
            {
                foreach (DerivedWithKind item in Children)
                {
                    if (item.Type != DerivedWithKind.InhType.Implementation)
                        return true;
                }
                return false;
            }
        }
        #endregion

        #region Attribute
        public string GenerateAttributes(ref List<string> names, ref StringBuilder forInterface)
        {
            StringBuilder sb = new StringBuilder();

            sb.Append(generateOwnAttributes(ref names, ref forInterface));

            //genarate parents' attributes:
            foreach (DerivedWithKind parent in this.Parents)
            {
                if (parent.Type == DerivedWithKind.InhType.General ||
                    parent.Type == DerivedWithKind.InhType.Implementation)
                    sb.Append(parent.Rel.GenerateAttributes(ref names, ref forInterface));
            }            

            return sb.ToString();
        }
        private string generateOwnAttributes(ref List<string> names, ref StringBuilder forInterface)
        {
            StringBuilder sb = new StringBuilder();
            foreach (MGALib.IMgaObject mgaObject in this.MgaObjects)
            {
                MGALib.IMgaFCO fco = mgaObject as MGALib.IMgaFCO;
                foreach (MGALib.IMgaConnPoint conn in fco.PartOfConns)
                {
                    foreach (MGALib.IMgaConnPoint connOther in conn.Owner.ConnPoints)
                    {
                        if (connOther.target.ID != mgaObject.ID && connOther.target.Meta.Name.Contains("Attribute"))
                        {
                            if (connOther.target.Meta.Name == "FieldAttribute")
                            {
                                foreach (MGALib.IMgaAttribute attr in connOther.target.Attributes)
                                {
                                    if (attr.Meta.Name == "DataType")
                                    {
                                        if (!names.Contains(connOther.target.Name))
                                        {
                                            if (attr.Value.ToString() == "string")
                                            {
                                                sb.Append(generateAttribute(connOther.target.Name, "String"));
                                                if (this.HasChildren)
                                                {
                                                    forInterface.Append(generateAttributeForInterface(connOther.target.Name, "String"));
                                                }
                                            }
                                            else if (attr.Value.ToString() == "integer")
                                            {
                                                sb.Append(generateAttribute(connOther.target.Name, "Int"));
                                                if (this.HasChildren)
                                                {
                                                    forInterface.Append(generateAttributeForInterface(connOther.target.Name, "Int"));
                                                }
                                            }
                                            else if (attr.Value.ToString() == "double")
                                            {
                                                sb.Append(generateAttribute(connOther.target.Name, "Float"));
                                                if (this.HasChildren)
                                                {
                                                    forInterface.Append(generateAttributeForInterface(connOther.target.Name, "Float"));
                                                }
                                            }
                                            names.Add(connOther.target.Name);
                                        }
                                    }
                                }
                            }
                            else if (connOther.target.Meta.Name == "EnumAttribute")
                            {
                                if (!names.Contains(connOther.target.Name))
                                {
                                    //generate enum
                                    StringBuilder enum1 = new StringBuilder();

                                    StringBuilder stuff = new StringBuilder();
                                    foreach (MGALib.MgaAttribute attr in connOther.target.Attributes)
                                    {
                                        if (attr.Meta.Name == "MenuItems")
                                        {
                                            string[] items = attr.Value.ToString().Split(new char[]{'\n'}, StringSplitOptions.RemoveEmptyEntries);
                                            foreach (string s in items)
                                            {
                                                stuff.Append(s);
                                                stuff.Append(",");
                                            }
                                        }
                                    }

                                    enum1.AppendFormat(FCO.Template.Enum, connOther.target.Name, stuff);

                                    Enum.AddEnum(connOther.target.Name, enum1.ToString());

                                    sb.Append(generateAttribute(connOther.target.Name, connOther.target.Meta.Name));
                                    if (this.HasChildren)
                                    {
                                        forInterface.Append(generateAttributeForInterface(connOther.target.Name, connOther.target.Meta.Name));
                                    }
                                    names.Add(connOther.target.Name);
                                }
                            }
                            else
                            {
                                if (!names.Contains(connOther.target.Name))
                                {
                                    sb.Append(generateAttribute(connOther.target.Name, connOther.target.Meta.Name));
                                    if (this.HasChildren)
                                    {
                                        forInterface.Append(generateAttributeForInterface(connOther.target.Name, connOther.target.Meta.Name));
                                    }
                                    names.Add(connOther.target.Name);
                                }
                            }
                        }
                    }
                }
            }
            return sb.ToString();
        }

        private string generateAttribute(string name, string type)
        {
            //addCheckAttributeName(name);

            StringBuilder sb = new StringBuilder();
            switch (type)
            {                    
                case "BooleanAttribute":
                    sb.AppendFormat(FCO.Template.Attribute, "bool", name, "Bool");
                    break;
                case "Int": 
                    sb.AppendFormat(FCO.Template.Attribute, "int", name, "Int");
                    break;
                case "Float":
                    sb.AppendFormat(FCO.Template.Attribute, "double", name, "Float");
                    break;
                case "String":
                    sb.AppendFormat(FCO.Template.Attribute, "string", name, "Str");
                    break;
                case "EnumAttribute":
                    sb.AppendFormat(FCO.Template.AttributeEnum, name);
                    break;
                default:
                    sb.AppendLine("");
                    break;
            }

            return sb.ToString();
        }

        private string generateAttributeForInterface(string name, string type)
        {
            StringBuilder sb = new StringBuilder();
            switch (type)
            {
                case "BooleanAttribute":
                    sb.AppendFormat(FCO.Template.AttributeInterface, "bool", name);
                    break;
                case "Int":
                    sb.AppendFormat(FCO.Template.AttributeInterface, "int", name);
                    break;
                case "Float":
                    sb.AppendFormat(FCO.Template.AttributeInterface, "double", name);
                    break;
                case "String":
                    sb.AppendFormat(FCO.Template.AttributeInterface, "string", name);
                    break;
                case "EnumAttribute":
                    sb.AppendFormat(FCO.Template.AttributeInterface, name+"Enum",name);
                    break;
                default:
                    sb.AppendLine("");
                    break;
            }

            return sb.ToString();
        }
        #endregion

        #region Connection
        protected IEnumerable<Connection> Connections
        {
            get
            {
                foreach (MGALib.IMgaObject mgaObject in this.MgaObjects)
                {
                    MGALib.IMgaFCO fco = mgaObject as MGALib.IMgaFCO;
                    foreach (MGALib.IMgaConnPoint conn in fco.PartOfConns)
                    {
                        if (conn.Owner.Meta.Name == "ConnectorToDestination" || conn.Owner.Meta.Name == "SourceToConnector")
                        {
                            foreach (MGALib.IMgaConnPoint connOther in conn.Owner.ConnPoints)
                            {
                                if (connOther.target.ID != mgaObject.ID)
                                {
                                    //connOther.target: Connector
                                    foreach (MGALib.IMgaConnPoint conn2 in connOther.target.PartOfConns)
                                    {
                                        if (conn2.Owner.Meta.Name == "AssociationClass")
                                        {
                                            foreach (MGALib.IMgaConnPoint connOther2 in conn2.Owner.ConnPoints)
                                            {
                                                if (connOther2.target.ID != connOther.target.ID)
                                                {
                                                    //connOther2.target: Connection
                                                    if (connOther2.target.MetaBase.Name.Contains("Proxy"))
                                                    {
                                                        if (Object.ProxyCache.ContainsKey(connOther2.target.Name))
                                                            yield return Object.ElementsByName[Object.ProxyCache[connOther2.target.Name]] as Connection;
                                                        else
                                                            DSM.GeneratorFacade.Errors.Add("Proxy '" + connOther2.target.Name + "' is not found");
                                                    }
                                                    else
                                                    {
                                                        if (Object.ElementsByName.ContainsKey(connOther2.target.Name))
                                                            yield return Object.ElementsByName[connOther2.target.Name] as Connection;
                                                        else
                                                        {
                                                            //todo
                                                            DSM.GeneratorFacade.Errors.Add(connOther2.target.Name + " is not found");
                                                            //throw new Exception(connOther2.target.Name + " is not cached");
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        public string GenerateConnections(ref List<string> names, ref StringBuilder forInterface)
        {
            StringBuilder sb = new StringBuilder();
            sb.Append(generateOwnConnections(ref names, ref forInterface));

            //genarate parents' attributes:
            foreach (DerivedWithKind parent in this.Parents)
            {
                if (parent.Type == DerivedWithKind.InhType.General ||
                    parent.Type == DerivedWithKind.InhType.Interface)
                    sb.Append(parent.Rel.GenerateConnections(ref names, ref forInterface));
            }

            return sb.ToString();
        }
        private string generateOwnConnections(ref List<string> names, ref StringBuilder forInterface)
        {
            //find all connections:
            StringBuilder sb = new StringBuilder();
            foreach (Connection conn in Connections)
            {
                if (!names.Contains(conn.className))
                {
                    sb.Append(generateConnection(conn));
                    if (this.HasChildren)
                    {
                        forInterface.Append(generateConnectionForInterface(conn));
                    }
                    names.Add(conn.className);
                }
                
            }
            return sb.ToString();
        }
        private string generateConnection(FCO current)
        {
            StringBuilder inner = new StringBuilder();

            inner.AppendFormat(FCO.Template.ConnectionInner, current.className, current.ProperClassName, "IMgaConnection");
            if (current.HasChildren)
            {
                //and add all of the children
                foreach (DerivedWithKind child in current.ChildrenRecursive)
                {
                    if (child.Type == DerivedWithKind.InhType.General ||
                        child.Type == DerivedWithKind.InhType.Interface)
                        inner.AppendFormat(FCO.Template.ConnectionInner, child.Rel.className, child.Rel.ProperClassName, "IMgaConnection");
                }
            }

            StringBuilder sb = new StringBuilder();
            sb.AppendFormat(FCO.Template.Connection, current.className, inner.ToString());

            return sb.ToString();
        }
        private string generateConnectionForInterface(FCO current)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendFormat(FCO.Template.ConnectionInterface, current.className);

            return sb.ToString();
        }

        #endregion

        #region Relationship
        protected class FCOConnection
        {
            public FCOConnection(FCO Fco, Connection Conn, string DstOrSrc, string RoleName)
            {
                this.Fco = Fco;
                this.Conn = Conn;
                this.DstOrSrc = DstOrSrc;
                this.RoleName = RoleName;
            }
            public FCO Fco;
            public Connection Conn;
            public string DstOrSrc;
            public string RoleName;
        }
        protected IEnumerable<FCOConnection> Relations
        {
            get
            {
                foreach (MGALib.IMgaObject mgaObject in this.MgaObjects)
                {
                    MGALib.IMgaFCO fco = mgaObject as MGALib.IMgaFCO;
                    foreach (MGALib.IMgaConnPoint conn in fco.PartOfConns)
                    {
                        if (conn.Owner.Meta.Name == "ConnectorToDestination" || conn.Owner.Meta.Name == "SourceToConnector")
                        {
                            string dir = conn.Owner.Meta.Name;

                            string DstOrSrc = (dir == "ConnectorToDestination") ? "Src" : "Dst";

                            foreach (MGALib.IMgaConnPoint connOther in conn.Owner.ConnPoints)
                            {
                                if (connOther.target.ID != mgaObject.ID)
                                {
                                    //connOther.target: Connector
                                    Connection connection = null;

                                    //get the connection
                                    foreach (MGALib.IMgaConnPoint conn2 in connOther.target.PartOfConns)
                                    {
                                        if (conn2.Owner.Meta.Name == "AssociationClass")
                                        {
                                            foreach (MGALib.IMgaConnPoint connOther2 in conn2.Owner.ConnPoints)
                                            {
                                                if (connOther2.target.ID != connOther.target.ID)
                                                {
                                                    //connOther2.target: connection
                                                    if (connOther2.target.MetaBase.Name.Contains("Proxy"))
                                                    {
                                                        if (Object.ProxyCache.ContainsKey(connOther2.target.Name))
                                                            connection = Object.ElementsByName[Object.ProxyCache[connOther2.target.Name]] as Connection;
                                                        else
                                                            DSM.GeneratorFacade.Errors.Add("Proxy '" + connOther2.target.Name + "' is not found");
                                                    }
                                                    else
                                                    {
                                                        if (Object.ElementsByName.ContainsKey(connOther2.target.Name))
                                                            connection = Object.ElementsByName[connOther2.target.Name] as Connection;
                                                        else
                                                        {
                                                            //todo
                                                            DSM.GeneratorFacade.Errors.Add(connOther2.target.Name + " is not found");
                                                            //throw new Exception(connOther2.target.Name + " is not cached");
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }

                                    //get the other one
                                    foreach (MGALib.IMgaConnPoint conn2 in connOther.target.PartOfConns)
                                    {
                                        if (conn2.Owner.Meta.Name != "AssociationClass" && conn2.Owner.Meta.Name != dir)
                                        {
                                            foreach (MGALib.IMgaConnPoint connOther2 in conn2.Owner.ConnPoints)
                                            {
                                                if (connOther2.target.ID != connOther.target.ID)
                                                {
                                                    //connOther2.target: dst
                                                    string Role;
                                                    try
                                                    {
                                                        Role = connOther2.Owner.get_StrAttrByName(DstOrSrc.ToLower() + "Rolename");
                                                    }
                                                    catch
                                                    {
                                                        Role = DstOrSrc;
                                                    }
                                                    
                                                    if (connOther2.target.MetaBase.Name.Contains("Proxy"))
                                                    {
                                                        if (Object.ProxyCache.ContainsKey(connOther2.target.Name))
                                                            yield return new FCOConnection(
                                                                Object.ElementsByName[Object.ProxyCache[connOther2.target.Name]] as FCO,
                                                                connection, 
                                                                DstOrSrc, 
                                                                Role);
                                                        else
                                                            DSM.GeneratorFacade.Errors.Add("Proxy '" + connOther2.target.Name + "' is not found");
                                                    }
                                                    else
                                                    {
                                                        if (Object.ElementsByName.ContainsKey(connOther2.target.Name))
                                                            yield return new FCOConnection(
                                                                Object.ElementsByName[connOther2.target.Name] as FCO,
                                                                connection,
                                                                DstOrSrc,
                                                                Role);
                                                        else
                                                        {
                                                            //todo
                                                            DSM.GeneratorFacade.Errors.Add(connOther2.target.Name + " is not found");
                                                            //throw new Exception(connOther2.target.Name + " is not cached");
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        public string GenerateRelationships(ref List<string> names, ref StringBuilder forInterface)
        {
            StringBuilder sb = new StringBuilder();
            sb.Append(generateOwnRelationships(ref names, ref forInterface));

            //generate parents' relations:
            foreach (DerivedWithKind parent in this.Parents)
            {
                if (parent.Type == DerivedWithKind.InhType.General ||
                    parent.Type == DerivedWithKind.InhType.Interface)
                    sb.Append(parent.Rel.GenerateRelationships(ref names, ref forInterface));
            }

            return sb.ToString();
        }
        private string generateOwnRelationships(ref List<string> names, ref StringBuilder forInterface)
        {
            //find all connections:
            StringBuilder sb = new StringBuilder();
            foreach (FCOConnection dst in Relations)
            {
                if (!names.Contains(dst.Conn.className))
                {
                    sb.Append(generateRelationship(dst));
                    if (this.HasChildren)
                    {
                        forInterface.Append(generateRelationshipForInterface(dst));
                    }
                    names.Add(dst.Conn.className);
                }
            }
            return sb.ToString();
        }
        private string generateRelationship(FCOConnection dst)
        {
            FCO current = dst.Fco;
            string relname = dst.Conn.className;
            StringBuilder inner = new StringBuilder();

            inner.AppendFormat(FCO.Template.RelationshipInner, current.className, current.ProperClassName, current.memberType);
            if (current.HasChildren)
            {
                //and add all of the children
                foreach (DerivedWithKind child in current.ChildrenRecursive)
                {
                    if (child.Type == DerivedWithKind.InhType.General ||
                        child.Type == DerivedWithKind.InhType.Interface)
                        inner.AppendFormat(FCO.Template.RelationshipInner, child.Rel.className, child.Rel.ProperClassName, child.Rel.memberType);
                }
            }

            StringBuilder sb = new StringBuilder();
            sb.AppendFormat(FCO.Template.Relationship, current.className, relname, inner.ToString(), dst.DstOrSrc, dst.RoleName);

            return sb.ToString();
        }
        private string generateRelationshipForInterface(FCOConnection dst)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendFormat(FCO.Template.RelationshipInterface, dst.Fco.className, dst.Conn.className, dst.DstOrSrc, dst.RoleName);

            return sb.ToString();
        }
        #endregion
        
        #region Container
        public string GenerateContainer()
        {
            StringBuilder sb = new StringBuilder();

            StringBuilder model = new StringBuilder();
            StringBuilder folder = new StringBuilder();

            List<string> modelnames = new List<string>();
            List<string> foldernames = new List<string>();

            generateContainerInner(ref model, ref modelnames, ref folder, ref foldernames);

            sb.AppendFormat(FCO.Template.Container, model.ToString(), folder.ToString(), Generator.ClassName);

            return sb.ToString();
        }
        private void generateContainerInner(ref StringBuilder model, ref List<string> modelNames, ref StringBuilder folder, ref List<string> folderNames)
        {
            generateOwnContainerInnerModel(ref model, ref modelNames);
            generateOwnContainerInnerFolder(ref folder, ref folderNames);
            
            //the same to the elements parents 
            foreach (DerivedWithKind parent in this.Parents)
            {
                if (parent.Type == DerivedWithKind.InhType.General ||
                    parent.Type == DerivedWithKind.InhType.Implementation)
                {
                    parent.Rel.generateContainerInner(ref model, ref modelNames, ref folder, ref folderNames);
                }                
            }
        }
        private void generateOwnContainerInnerModel(ref StringBuilder sb, ref List<string> modelNames)
        {
            //PossibleContainers that are models
            foreach (Object container in this.PossibleContainers)
            {
                FCO model = container as FCO;
                if (model != null)
                {
                    //this container is a model
                    if (!modelNames.Contains(model.className))
                    {
                        sb.AppendFormat(FCO.Template.ContainerModelInner, model.className, model.ProperClassName);
                        modelNames.Add(model.className);
                    }

                    //its children:
                    if (model.HasChildren)
                    {
                        //and add all of the children
                        foreach (DerivedWithKind child in model.ChildrenRecursive)
                        {
                            if (child.Type == DerivedWithKind.InhType.General ||
                                child.Type == DerivedWithKind.InhType.Interface)
                            {
                                if (!modelNames.Contains(child.Rel.className))
                                {
                                    sb.AppendFormat(FCO.Template.ContainerModelInner, child.Rel.className, child.Rel.ProperClassName);
                                    modelNames.Add(child.Rel.className);
                                }
                            }
                        }
                    }
                }
            }            
        }
        private void generateOwnContainerInnerFolder(ref StringBuilder sb, ref List<string> folderNames)
        {
            //PossibleContainers that are folders
            foreach (Object container in this.PossibleContainers)
            {
                Folder folder = container as Folder;
                if (folder != null)
                {
                    if (!folderNames.Contains(folder.className))
                    {
                        //this container is a model
                        sb.AppendFormat(FCO.Template.ContainerFolderInner, folder.className, folder.className);
                        folderNames.Add(folder.className);
                    }
                }
            }    
        }

        #endregion

        public override string GenerateClass()
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine(Init());

            List<string> rels = new List<string>();
            List<string> attrs = new List<string>();
            List<string> conns = new List<string>();
            List<string> crnews = new List<string>();

            StringBuilder sbAttrib = new StringBuilder();
            StringBuilder sbConns = new StringBuilder();
            StringBuilder sbRels = new StringBuilder();

            string baseInterfaces = (this.HasChildren) ? className : baseInterfaceName;

            foreach (DerivedWithKind parent in this.Parents)
            {
                if (parent.Type != DerivedWithKind.InhType.Implementation)
                    baseInterfaces = baseInterfaces + ", " + parent.Rel.Name;
            } 

            sb.AppendFormat(
                FCO.Template.Class, 
                namespaceName, 
                (this.HasChildren)?className+"Impl":className,
                baseInterfaces, 
                memberType, 
                GenerateCommon()+GenerateContainer(),
                GenerateAttributes(ref attrs, ref sbAttrib),
                GenerateConnections(ref conns, ref sbConns),
                GenerateRelationships(ref rels, ref sbRels),
                "",
                "IMgaMeta" + memberType.Substring(4),
                className,
                GenerateCreateNews(ref crnews, this));

            baseInterfaces = baseInterfaceName;

            foreach (DerivedWithKind parent in this.Parents)
            {
                if (parent.Type != DerivedWithKind.InhType.Implementation)
                    baseInterfaces = baseInterfaces + ", " + parent.Rel.Name;
            } 

            if (this.HasChildren)
            {
                //have to generate interface as well
                if (this.HasChildren)
                {
                    //have to generate interface as well
                    sb.AppendFormat(
                        FCO.Template.Interface,
                        namespaceName,
                        className,
                        baseInterfaces,
                        memberType,
                        GenerateCommon(),
                        sbAttrib.ToString(),
                        sbConns.ToString(),
                        sbRels.ToString(),
                        "");
                }
            }

            return sb.ToString();
        }

        public override void Save()
        {
            Directory.CreateDirectory(Path.Combine(Generator.Path, Generator.ClassName));

            string pathName = Path.Combine(Generator.Path, Generator.ClassName) + @"\" + this.Name + ".cs";
            GeneratorFacade.generatedFiles.Add(pathName);

            using (TextWriter tw = new StreamWriter(pathName))
            {
                tw.WriteLine(GenerateClass());
            }
        }
    }
}
