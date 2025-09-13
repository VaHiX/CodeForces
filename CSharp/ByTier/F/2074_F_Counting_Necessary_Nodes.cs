using System;
using System.Collections.Generic;

class Program
{
    static int LargestPowerOfTwo(int x)
    {
        int p = 1;
        while (p <= x)
        {
            p <<= 1;
        }
        return p >> 1;
    }

    static List<int> DecomposeInterval(int L, int R)
    {
        List<int> endpoints = new List<int> { L };
        int i = L;
        while (i < R)
        {
            int rem = R - i;
            int t;
            if (i == 0)
            {
                t = LargestPowerOfTwo(rem);
            }
            else
            {
                t = i & -i;
                int candidate = LargestPowerOfTwo(rem);
                if (t > candidate)
                    t = candidate;
            }
            if (t <= 0)
                t = 1;
            if (i + t > R)
                t = rem;
            endpoints.Add(i + t);
            i += t;
        }
        return endpoints;
    }

    static long ComputeScore(List<int> X, List<int> Y)
    {
        long ans = 0;
        for (int i = 0; i < X.Count - 1; i++)
        {
            int dx = X[i + 1] - X[i];
            for (int j = 0; j < Y.Count - 1; j++)
            {
                int dy = Y[j + 1] - Y[j];
                int mini = Math.Min(dx, dy);
                int maxi = Math.Max(dx, dy);
                ans += maxi / mini;
            }
        }
        return ans;
    }

    static void ProcessTestCase()
    {
        string[] tokens = Console.ReadLine().Split();
        int l1 = int.Parse(tokens[0]);
        int r1 = int.Parse(tokens[1]);
        int l2 = int.Parse(tokens[2]);
        int r2 = int.Parse(tokens[3]);

        List<int> X = DecomposeInterval(l1, r1);
        List<int> Y = DecomposeInterval(l2, r2);

        long result = ComputeScore(X, Y);
        Console.WriteLine(result);
    }

    static void Main(string[] args)
    {
        int t = int.Parse(Console.ReadLine());
        for (int tc = 0; tc < t; tc++)
        {
            ProcessTestCase();
        }
    }
}
