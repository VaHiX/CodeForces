using System;
using System.Collections.Generic;
using System.Linq;

class PerfectPermutation
{
    static int F(long m, long n, int B, int[] p)
    {
        if (m <= n) return p[(int)m];
        return (m % 2 == 1) ? B : B ^ F(m / 2, n, B, p);
    }

    static void Solve()
    {
        string[] inputs = Console.ReadLine().Split();
        int n = int.Parse(inputs[0]);
        long l = long.Parse(inputs[1]);
        long r = long.Parse(inputs[2]);

        int[] a = new int[n + 1];
        inputs = Console.ReadLine().Split();
        for (int i = 1; i <= n; i++)
        {
            a[i] = int.Parse(inputs[i - 1]);
        }

        if (l <= n)
        {
            Console.WriteLine(a[(int)l]);
            return;
        }

        int[] p = new int[n + 1];
        p[0] = 0;
        for (int i = 1; i <= n; i++)
        {
            p[i] = p[i - 1] ^ a[i];
        }

        int fn = p[n];
        int B = (n % 2 == 1) ? fn : fn ^ p[n / 2];
        long m = l / 2;

        Console.WriteLine(F(m, n, B, p));
    }

    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        while (t-- > 0) Solve();
    }
}
