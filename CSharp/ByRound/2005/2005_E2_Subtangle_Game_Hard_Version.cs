using System;
using System.Collections.Generic;

class Program
{
    static void Main()
    {
        long t = long.Parse(Console.ReadLine());

        for (long test = 0; test < t; test++)
        {
            var input = Console.ReadLine().Split();
            long l = long.Parse(input[0]);
            long n = long.Parse(input[1]);
            long m = long.Parse(input[2]);


            long[,] field = new long[n, m];
            bool[] used = new bool[n * m + 1];
            List<long> a = new List<long>();
            long[] ind = new long[n * m + 1];
            Array.Fill(ind, -1); 
            bool isOk = false;


            input = Console.ReadLine().Split();
            for (long j = 0; j < l; j++)
            {
                long x = long.Parse(input[j]);
                if (used[x] || isOk)
                {
                    isOk = true;
                    continue;
                }
                ind[x] = j;
                a.Add(x);
                used[x] = true;
            }


            for (long j = 0; j < n; j++)
            {
                input = Console.ReadLine().Split();
                for (long g = 0; g < m; g++)
                {
                    long x = long.Parse(input[g]);
                    field[j, g] = x;
                }
            }

            long[,] dpEv = new long[n + 1, m + 1];
            long[,] dpOdd = new long[n + 1, m + 1];
            long inf = (long)1e18;

            for (long i = 0; i <= n; i++)
            {
                for (long j = 0; j <= m; j++)
                {
                    dpEv[i, j] = inf;
                    dpOdd[i, j] = inf;
                }
            }

            for (long x = n - 1; x >= 0; x--)
            {
                for (long y = m - 1; y >= 0; y--)
                {
                    long m1 = inf, m2 = inf, m3 = inf;
                    m1 = dpEv[x + 1, y];
                    m2 = dpEv[x, y + 1];
                    if (used[field[x, y]] && ind[field[x, y]] % 2 == 0 && dpOdd[x + 1, y + 1] > ind[field[x, y]] + 1)
                    {
                        m3 = ind[field[x, y]];
                    }
                    dpEv[x, y] = Math.Min(Math.Min(m1, m2), m3);

                    m1 = inf; m2 = inf; m3 = inf;
                    m1 = dpOdd[x + 1, y];
                    m2 = dpOdd[x, y + 1];
                    if (used[field[x, y]] && ind[field[x, y]] % 2 == 1 && dpEv[x + 1, y + 1] > ind[field[x, y]] + 1)
                    {
                        m3 = ind[field[x, y]];
                    }
                    dpOdd[x, y] = Math.Min(Math.Min(m1, m2), m3);
                }
            }


            if (dpEv[0, 0] == 0)
            {
                Console.WriteLine("T");
            }
            else
            {
                Console.WriteLine("N");
            }
        }
    }
}
