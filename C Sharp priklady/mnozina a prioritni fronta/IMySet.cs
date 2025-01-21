using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace cviko05
{
    public interface IMySet<Ty> : IEnumerable<Ty>
    {
        public bool Contains(Ty x);
        public void Add(Ty i);
        public void PrintSet();
        public void Remove(Ty i);
        public int Size();
        public bool IsEmpty();
    }
}
