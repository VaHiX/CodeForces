using System;
using System.Collections.Generic;

class Program
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        while (t-- > 0)
        {
            var parts = Console.ReadLine().Split();
            long k = long.Parse(parts[0]);
            ulong x = ulong.Parse(parts[1]);

            ulong total = 1UL << (int)(k + 1);
            ulong a = x, b = total - x;

            var steps = new List<int>();

            while (a != b)
            {
                if (a < b)
                {
                    steps.Add(1);
                    b -= a;
                    a += a;
                }
                else
                {
                    steps.Add(2);
                    a -= b;
                    b += b;
                }
            }

            steps.Reverse();

            Console.WriteLine(steps.Count);
            Console.WriteLine(string.Join(" ", steps));
        }
    }
}