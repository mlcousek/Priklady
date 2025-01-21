using Microsoft.Azure.Amqp.Framing;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace cviko05
{
    internal class MySet<Ty> : IMySet<Ty>
    {

        private Ty[] set;
        private int head = -1;

        public MySet()
        {
            this.set = new Ty[1];

        }

        public bool Contains(Ty x)
        {
            for (int i = 0; i <= head; i++)
            {
                Ty y = this.set[i];
                if (y != null && y.Equals(x))
                {
                    return true;
                }
            }
            return false;
        }
       
        public void Add(Ty i)
        {
            if (Contains(i))
            {
                return;
            }
            int nextPos = ++head;
            if (nextPos >= set.Length)
            {
                ResizeDataStructureUp();
            }
            set[nextPos] = i;
        }

        private void ResizeDataStructureUp()
        {
            Ty[] nextData = new Ty[set.Length + 1];
            set.CopyTo(nextData, 0);
            set = nextData;
        }

        public void PrintSet()
        {
            Console.Write("{ ");
            for (int i = 1; i <= head; i++)
            {
                Console.Write(set[i] + " ");
            }
            Console.Write("}");
            Console.Write("\n");
        }

        public void Remove(Ty i)
        {
            if (Contains(i))
            {
                int j = 1;
                Ty y = set[j];
                while (y != null && y.Equals(i))
                {
                    j++;
                }
                j++;
                for (int q = j - 1; q < set.Length - 1; q++)
                {
                    set[q] = set[q + 1];
                }
                int nextPos = head;
                if (nextPos < set.Length)
                {
                    head--;
                }
            }
        }
        public int Size()
        {
            return head + 1;
        }

        public MySet<Ty> Union(MySet<Ty> other)
        {
            MySet<Ty> result = new MySet<Ty>();
            for (int i = 0; i <= head; i++)
            {
                result.Add(set[i]);
            }
            for (int i = 0; i <= other.head; i++)
            {
                result.Add(other.set[i]);
            }
            return result;
        }

        public MySet<Ty> Intersection(MySet<Ty> other)
        {
            MySet<Ty> result = new();
            for (int i = 0; i <= head; i++)
            {
                if (other.Contains(set[i]))
                {
                    result.Add(set[i]);
                }
            }
            return result;
        }

        public MySet<Ty> Subtract(MySet<Ty> other)
        {
            MySet<Ty> result = new();
            for (int i = 0; i <= head; i++)
            {
                if (!other.Contains(set[i]))
                {
                    result.Add(set[i]);
                }
            }
            return result;
        }
        public bool AreAqual(MySet<Ty> other)
        {
            if (Size() == other.Size())
            {
                for (int i = 0; i <= head; i++)
                {
                    if (!other.Contains(set[i]))
                    {
                        return false;
                    }
                }
            }
            else
            {
                return false;
            }
            return true;
        }

        public bool IsSubsetOf(MySet<Ty> other)
        {
            for (int i = 0; i <= head; i++)
            {
                if (!other.Contains(set[i]))
                {
                    return false;
                }
            }
            return true;
        }

        public bool IsEmpty()
        {
            return Size() == 0; 
        }

        public IEnumerator<Ty> GetEnumerator()
        {
            return new SetEnumerator<Ty>(set, Size());
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        private class SetEnumerator<T> : IEnumerator<T>
        {
            private readonly T[] data;
            private int pos = -1;
            private readonly int realSize;

            public SetEnumerator(T[] data, int realSize)
            {
                this.data = data;
                this.realSize = realSize;
            }
            public T Current => data[pos];

            object? IEnumerator.Current => data[pos];

            public void Dispose()
            {
            }

            public bool MoveNext()
            {
                pos++;
                return pos < realSize;
            }

            public void Reset()
            {
                pos = -1;
            }
        }
    }
}
