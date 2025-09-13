using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    static void Solve()
    {
        int n = int.Parse(Console.ReadLine());
        var a = new int[n + 1];
        var son = new List<int>();

        for (int i = 1; i < n; ++i)
        {
            var tokens = Console.ReadLine().Split();
            int u = int.Parse(tokens[0]);
            int v = int.Parse(tokens[1]);
            son.Add(i + 1);
        }

        int Q = 0;
        Func<int, List<int>, int> ask = (op, v) =>
        {
            Q++;
            if (Q > n + 200)
            {
                throw new InvalidOperationException("Query limit exceeded.");
            }

            Console.Write("? " + op);
            if (op == 1)
            {
                Console.Write(" " + v.Count);
                foreach (var u in v)
                {
                    Console.Write(" " + u);
                }
                Console.WriteLine();
                Console.Out.Flush();
                return int.Parse(Console.ReadLine());
            }
            else
            {
                Console.WriteLine(" " + v[0]);
                Console.Out.Flush();
                return 0;
            }
        };

        int rt = 0;
        int bef = ask(1, son);
        ask(2, new List<int> { 1 });
        int af = ask(1, son);
        if (Math.Abs(bef - af) == 2 * son.Count)
        {
            rt = 1;
        }
        else
        {
            int l = 0, r = son.Count - 1;
            while (l < r)
            {
                int mid = l + (r - l) / 2;
                var query = son.GetRange(l, mid - l + 1);
                int befMid = ask(1, query);
                ask(2, new List<int> { 1 });
                int afMid = ask(1, query);
                if (Math.Abs(befMid - afMid) != 2 * (mid - l + 1))
                {
                    r = mid;
                }
                else
                {
                    l = mid + 1;
                }
            }
            rt = son[l];
        }

        for (int i = 1; i <= n; ++i)
        {
            a[i] = ask(1, new List<int> { i });
        }

        for (int i = 2; i <= n; ++i)
        {
            if (rt != i)
            {
                a[i] -= a[1];
            }
        }

        if (rt > 1)
        {
            a[1] -= a[rt];
        }

        Console.Write("!");
        for (int i = 1; i <= n; ++i)
        {
            Console.Write(" " + a[i]);
        }
        Console.WriteLine();
        Console.Out.Flush();
    }

    static void Main()
    {
        int T = int.Parse(Console.ReadLine());
        for (int t = 0; t < T; ++t)
        {
            Solve();
        }
    }
}
