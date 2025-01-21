using cviko05;
/*
Console.WriteLine("Hello, World!");

IntPriorityQueue1 queue1 = new IntPriorityQueue1();
queue1.InsertWithPriority(10, 8);
queue1.InsertWithPriority(5, 2);
queue1.InsertWithPriority(10, 1);
queue1.InsertWithPriority(100, 5);
queue1.InsertWithPriority(15, 1);

int i = 0;
queue1.PeekNextValue(out i);

Console.WriteLine(i);

Console.WriteLine("Hello, World!");

queue1.PrintQueue();
queue1.PopNextValue(out i);
Console.WriteLine(i);
queue1.PrintQueue();
queue1.InsertWithPriority(15, 1);
queue1.PrintQueue();

Console.WriteLine("Bagr " + queue1.ToString());
*/


var a = new MySet<double> { 1.5, 2.5, 3.5, 4.5 };
var enumerator = a.GetEnumerator();
while (enumerator.MoveNext()) { Console.WriteLine($"Enumerator for this set is {enumerator.Current}"); }
enumerator.Reset();
while (enumerator.MoveNext()) { Console.WriteLine($"Enumerator for this set is {enumerator.Current}"); }


