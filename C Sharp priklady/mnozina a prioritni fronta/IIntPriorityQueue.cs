using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace cviko05
{
    internal interface IIntPriorityQueue
    {
        bool IsEmpty();
        void InsertWithPriority(int value, int priority);
        bool PopNextValue(out int val);
        bool PeekNextValue(out int val);
    }
}
