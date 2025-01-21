using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace cviko05
{
    internal class IntPriorityQueue1 : IIntPriorityQueue
    {
        private int[] queue;
        private int head = 0;

        public IntPriorityQueue1()
        {
            this.queue = Array.Empty<int>();
        }

        public bool IsEmpty()
        {
            return (head == 0);
        }

        private void ResizeDataStructureUp()
        {
            int[] nextData = new int[queue.Length + 2];
            queue.CopyTo(nextData, 0);
            queue = nextData;
        }

        public void InsertWithPriority(int value, int priority)
        {
            if (IsEmpty())
            {
                ResizeDataStructureUp();
                head += 2;
                queue[0] = value;
                queue[1] = priority;
            }
            else
            {
                int nextPos = head + 2;
                head += 2;
                if (nextPos >= queue.Length)
                {
                    ResizeDataStructureUp();
                }
                int help = 0;
                //mensi jak head
                for (int i = 1; i < head; i = i + 2)
                {
                    if (queue[i] > priority)
                    {
                        int ind = i;
                        //j = head
                        for (int j = head; j > ind + 1; j--)
                        {
                            queue[j - 1] = queue[j - 3];
                        }
                        queue[ind] = priority;
                        queue[ind - 1] = value;
                        help = 1;
                        break;
                    }
                }
                if (help == 0)
                {
                    queue[head - 1] = priority;
                    queue[head - 2] = value;
                }
            }
        }
        
        public bool PopNextValue(out int val)
        {
            PeekNextValue(out val);
            head -= 2;
            for(int i = 0; i < head; i++)
            {
                queue[i] = queue[i + 2];
            }
            //head -= 2;
            return true;
        }
       

        public bool PeekNextValue(out int val)
        {
            if (IsEmpty())
            {
                val = 0;
                return false;
            }
            else
            {
                val = queue[0];
                return true;
            }

        }

        public void PrintQueue()
        {
            for(int i = 0; i < head; i += 2)
            {
                Console.Write("val: " + queue[i] + " prior: " + queue[i + 1] + ", ");
            }
            Console.WriteLine();
        }

        public override string ToString()
        {
            /* StringBuilder sb = new StringBuilder();
             for (int i = 0; i < head; i += 2)
             {
                 sb.Append("val: " + queue[i] + " prior: " + queue[i + 1] + ", ");
             }
             string result = ToString;
            */
            string result = "";

            for (int i = 0; i < head; i += 2)
            {
                result += ("val: " + queue[i] + " prior: " + queue[i + 1] + ", ");
            }
            return result; 
        }
    }
}
