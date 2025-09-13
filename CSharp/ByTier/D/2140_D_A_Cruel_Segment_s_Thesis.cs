using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    static void Main()
    {
        int testCases;
        if (!int.TryParse(Console.ReadLine(), out testCases)) return;

        while (testCases-- > 0)
        {
            int n = int.Parse(Console.ReadLine()!);
            long[] l = new long[n];
            long[] r = new long[n];
            long[] v = new long[n];

            long sumL = 0, rangeTotal = 0;

            for (int i = 0; i < n; i++)
            {
                var parts = Console.ReadLine()!.Split();
                l[i] = long.Parse(parts[0]);
                r[i] = long.Parse(parts[1]);

                sumL += l[i];
                rangeTotal += (r[i] - l[i]);
                v[i] = l[i] + r[i];
            }

            // Build sortable list of (value, index)
            var pairs = new List<(long val, int idx)>(n);
            for (int i = 0; i < n; i++)
                pairs.Add((v[i], i));

            pairs.Sort((x, y) =>
            {
                if (x.val != y.val) return y.val.CompareTo(x.val);
                return x.idx.CompareTo(y.idx);
            });

            // Position mapping and prefix sums
            int[] pos = new int[n];
            long[] prefix = new long[n + 1];

            for (int i = 0; i < n; i++)
            {
                pos[pairs[i].idx] = i;
                prefix[i + 1] = prefix[i] + pairs[i].val;
            }

            if (n % 2 == 0)
            {
                int k = n / 2;
                long t = prefix[k];
                Console.WriteLine(rangeTotal + (t - sumL));
            }
            else
            {
                int k = (n - 1) / 2;
                long best = long.MinValue;

                for (int i = 0; i < n; i++)
                {
                    long t = (pos[i] >= k) ? prefix[k] : (prefix[k + 1] - v[i]);
                    long add = t - (sumL - l[i]);
                    best = Math.Max(best, rangeTotal + add);
                }
                Console.WriteLine(best);
            }
        }
    }
}
