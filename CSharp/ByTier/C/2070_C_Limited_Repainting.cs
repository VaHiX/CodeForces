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
            var input = Console.ReadLine().Split();
            int n = int.Parse(input[0]), k = int.Parse(input[1]);
            string s = Console.ReadLine();
            var a = Console.ReadLine().Split().Select(long.Parse).ToList();
            long maxA = a.Max();
            long lo = 0, hi = maxA, ans = hi;

            while (lo <= hi)
            {
                long mid = lo + (hi - lo) / 2;
                int ops = 0, i = 0;
                while (i < n)
                {
                    if (s[i] == 'B' && a[i] > mid)
                    {
                        ops++;
                        while (i < n && !(s[i] == 'R' && a[i] > mid))
                            i++;
                    }
                    else
                    {
                        i++;
                    }
                }

                if (ops <= k)
                {
                    ans = mid;
                    hi = mid - 1;
                }
                else
                {
                    lo = mid + 1;
                }
            }

            Console.WriteLine(ans);
        }
    }
}
