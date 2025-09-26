using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine()); 
        while (t-- > 0)
        {
            int n = int.Parse(Console.ReadLine());
            List<long> b = Console.ReadLine().Split().Select(long.Parse).ToList(); 
            b.Sort(); 

            
            long[] a = new long[2 * n + 1];

            
            for (int i = 0; i <= n; i++)
            {
                a[2 * i] = b[n + i - 1];
            }

            
            for (int i = 0; i < n - 1; i++)
            {
                a[2 * i + 1] = b[i];
            }

           
            long sumLarge = b.Skip(n - 1).Sum(); 
            long sumSmall = b.Take(n - 1).Sum(); 
            a[2 * n - 1] = sumLarge - sumSmall;

            
            Console.WriteLine(string.Join(" ", a));
        }
    }
}