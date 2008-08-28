using System;
using System.Collections.Generic;
using System.Text;

namespace ##1##
{
    //these are not needed now
    public interface IObject
    {
        string Name { get; set; }
        string ID { get; }
        MGALib.IMgaObject MgaObject{ get; }
        void Delete();
    }

    public interface IFolder : IObject
    { }

    public interface IFCO : IObject
    { }

    public interface IModel : IFCO
    { }

    public interface IAtom : IFCO
    { }

    public interface IReference : IFCO
    { }

    public interface ISet : IFCO
    { }

    public interface IConnection : IFCO
    { }
}
