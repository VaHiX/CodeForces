using System;
using System.Collections.Generic;

class Program
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        while (t-- > 0)
        {
            var line = Console.ReadLine().Split();
            int n = int.Parse(line[0]);
            long m = long.Parse(line[1]);

            var arr = Array.ConvertAll(Console.ReadLine().Split(), long.Parse);
            Array.Sort(arr, (x, y) => y.CompareTo(x));  // sort descending

            long take = Math.Min(n, (int)m);
            long total = 0;

            for (int i = 0; i < take; i++)
            {
                total += arr[i] * (m - i);
            }

            Console.WriteLine(total);
        }
    }
}