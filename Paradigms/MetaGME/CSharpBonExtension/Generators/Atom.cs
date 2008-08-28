using System;
using System.Collections.Generic;
using System.Text;

namespace BonExtension.Generators
{
    public class Atom : FCO
    {
        public Atom(MGALib.IMgaAtom mgaObject)
            : base(mgaObject)
        {
            className = mgaObject.Name;
            baseInterfaceName = "IAtom";

            memberType = "IMgaAtom";
        }
    }
}
