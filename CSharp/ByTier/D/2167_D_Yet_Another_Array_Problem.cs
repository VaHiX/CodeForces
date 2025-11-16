// Problem: CF 2167 D - Yet Another Array Problem
// https://codeforces.com/contest/2167/problem/D

using System;
using System.Numerics;

class Program
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        while (t-- > 0)
        {
            int n = int.Parse(Console.ReadLine());
            string[] input = Console.ReadLine().Split();
            long[] a = new long[n];
            for (int i = 0; i < n; i++)
                a[i] = long.Parse(input[i]);
            long g = a[0];
            for (int i = 1; i < n; i++)
                g = GCD(g, a[i]);
            if (g == 1)
            {
                Console.WriteLine(2);
                continue;
            }
            long ans = -1;
            for (long x = 2; x <= 1000000; x++)
            {
                if (GCD(g, x) == 1)
                {
                    ans = x;
                    break;
                }
            }
            Console.WriteLine(ans);
        }
    }

    static long GCD(long a, long b)
    {
        while (b != 0)
        {
            long temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
}


// https://github.com/VaHiX/CodeForces/
