using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine()!);

        while (t-- > 0)
        {
            var parts = Console.ReadLine()!.Split();
            int n = int.Parse(parts[0]);
            long k = long.Parse(parts[1]);

            int[] a = Console.ReadLine()!
                .Split()
                .Select(int.Parse)
                .ToArray();

            int[] freq = new int[n + 1];
            foreach (var val in a)
            {
                if (val <= n) freq[val]++;
            }

            // Find smallest M such that freq[M] == 0
            int M = 0;
            while (M <= n && freq[M] > 0) M++;

            // Helper for k == 1 case
            long SumAfterK1()
            {
                long sum = 0;
                int uniqueCount = 0;
                for (int y = 0; y < M; y++)
                {
                    if (freq[y] == 1)
                    {
                        uniqueCount++;
                        sum += y;
                    }
                }
                return sum + (long)(n - uniqueCount) * M;
            }

            if (k == 1)
            {
                Console.WriteLine(SumAfterK1());
                continue;
            }

            // Look for first duplicate frequency
            int p = -1;
            for (int y = 0; y < M; y++)
            {
                if (freq[y] >= 2)
                {
                    p = y;
                    break;
                }
            }

            long ans;
            if (p != -1)
            {
                long S = (long)p * (p - 1) / 2;
                long r = n - p;
                ans = (k % 2 == 0) ? S + r * p : S + r * (p + 1);
            }
            else
            {
                long S = (long)M * (M - 1) / 2;
                long r = n - M;
                if (r == 0)
                {
                    ans = S;
                }
                else if (r == 1)
                {
                    ans = S + M;
                }
                else
                {
                    ans = (k % 2 == 0) ? S + r * (M + 1) : S + r * M;
                }
            }

            Console.WriteLine(ans);
        }
    }
}