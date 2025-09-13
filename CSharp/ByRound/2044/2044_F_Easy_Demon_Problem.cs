using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    static void Main()
    {
        const long M = 1000000007;
        const int N = 100010;

        // Input n, m, q
        string[] input = Console.ReadLine().Split();
        long n = long.Parse(input[0]);
        long m = long.Parse(input[1]);
        long q = long.Parse(input[2]);

        // Input arrays a and b
        long[] a = Array.ConvertAll(Console.ReadLine().Split(), long.Parse);
        long[] b = Array.ConvertAll(Console.ReadLine().Split(), long.Parse);

        // Calculate sums of a and b
        long s1 = a.Sum();
        long s2 = b.Sum();

        // Create sets for sa and sb
        HashSet<long> sa = new HashSet<long>();
        HashSet<long> sb = new HashSet<long>();

        foreach (long ai in a)
            sa.Add(s1 - ai);

        foreach (long bi in b)
            sb.Add(s2 - bi);

        // Process each query
        for (int i = 0; i < q; i++)
        {
            long x = long.Parse(Console.ReadLine());
            bool krish = false;

            for (long j = 1; j * j <= Math.Abs(x); j++)
            {
                if (Math.Abs(x) % j == 0)
                {
                    long x1 = j;
                    long x2 = x / j;

                    if ((sa.Contains(x1) && sb.Contains(x2)) ||
                        (sa.Contains(x2) && sb.Contains(x1)) ||
                        (sa.Contains(-x1) && sb.Contains(-x2)) ||
                        (sa.Contains(-x2) && sb.Contains(-x1)))
                    {
                        krish = true;
                        break;
                    }
                }
            }

            if (krish)
                Console.WriteLine("YES");
            else
                Console.WriteLine("NO");
        }
    }
}
