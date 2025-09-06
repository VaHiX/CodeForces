using System;
using System.Collections.Generic;
using System.IO;

public class Program
{
    const long MOD = 1000000007;

    static void Solve()
    {
        int n = int.Parse(Console.ReadLine());
        string[] pq = Console.ReadLine().Split();
        long px = long.Parse(pq[0]);
        long py = long.Parse(pq[1]);
        long qx = long.Parse(pq[2]);
        long qy = long.Parse(pq[3]);

        long[] a = new long[n];
        string[] aInput = Console.ReadLine().Split();
        long sum_a = 0;
        long max_a = 0;

        for (int i = 0; i < n; ++i)
        {
            a[i] = long.Parse(aInput[i]);
            sum_a += a[i];
            if (a[i] > max_a)
            {
                max_a = a[i];
            }
        }

        long dx = px - qx;
        long dy = py - qy;
        long D_sq = dx * dx + dy * dy;
        long R_max = sum_a;
        long R_min;

        if (n == 0)
        {
            R_min = 0;
        }
        else
        {
            long sum_other_a = sum_a - max_a;
            R_min = Math.Max(0L, max_a - sum_other_a);
        }

        long R_min_sq = R_min * R_min;
        long R_max_sq = R_max * R_max;

        if (D_sq >= R_min_sq && D_sq <= R_max_sq)
        {
            Console.WriteLine("Yes");
        }
        else
        {
            Console.WriteLine("No");
        }
    }

    public static void Main(string[] args)
    {
        if (args.Length > 0 && args[0] == "LOCAL")
        {
            Console.SetIn(new StreamReader("a2.txt"));
            Console.SetOut(new StreamWriter("a2.txt"));
        }

        int t = int.Parse(Console.ReadLine());
        for (int i = 0; i < t; i++)
        {
            Solve();
        }

        if (Console.Out is StreamWriter)
        {
            Console.Out.Flush();
            Console.Out.Close();
        }
    }
}