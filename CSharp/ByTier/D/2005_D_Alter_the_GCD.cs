using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    static void Solve()
    {
        int n = int.Parse(Console.ReadLine());

        int ans = 0;
        long cnt = 0;
        var a = Console.ReadLine().Split().Select(int.Parse).ToArray();
        var b = Console.ReadLine().Split().Select(int.Parse).ToArray();

        var prea = new int[n + 1];
        var preb = new int[n + 1];
        var sufa = new int[n + 1];
        var sufb = new int[n + 1];

        for (int i = 0; i < n; i++)
        {
            prea[i + 1] = Gcd(prea[i], a[i]);
            preb[i + 1] = Gcd(preb[i], b[i]);
        }

        for (int i = n - 1; i >= 0; i--)
        {
            sufa[i] = Gcd(sufa[i + 1], a[i]);
            sufb[i] = Gcd(sufb[i + 1], b[i]);
        }

        var fa = new List<int[]> { new int[] { 0, 0 } };
        var fb = new List<int[]> { new int[] { 0, 0 } };
        var pa = new List<int[]>();
        var pb = new List<int[]>();

        for (int i = 0; i <= n; i++)
        {
            if (i == n || prea[i] != prea[i + 1])
                pa.Add(new int[] { prea[i], i });
            if (i == n || preb[i] != preb[i + 1])
                pb.Add(new int[] { preb[i], i });
        }

        for (int r = 1; r <= n; r++)
        {
            int t = a[r - 1];
            for (int i = fa.Count - 1; i >= 0; i--)
            {
                t = Gcd(t, fa[i][0]);
                fa[i][0] = t;
            }

            t = b[r - 1];
            for (int i = fb.Count - 1; i >= 0; i--)
            {
                t = Gcd(t, fb[i][0]);
                fb[i][0] = t;
            }

            fa = RemoveDuplicates(fa);
            fb = RemoveDuplicates(fb);

            fa.Add(new int[] { 0, r });
            fb.Add(new int[] { 0, r });

            int ipa = 0, ipb = 0, ifa = 0, ifb = 0, lst = -1;

            while (true)
            {
                int u = Math.Min(Math.Min(pa[ipa][1], pb[ipb][1]), Math.Min(fa[ifa][1], fb[ifb][1]));
                if (u >= r) break;

                if (u > lst)
                {
                    int res = Gcd(pa[ipa][0], Gcd(fb[ifb][0], sufa[r])) + Gcd(pb[ipb][0], Gcd(fa[ifa][0], sufb[r]));
                    if (res > ans)
                    {
                        ans = res;
                        cnt = u - lst;
                    }
                    else if (res == ans)
                    {
                        cnt += u - lst;
                    }
                }

                lst = u;
                if (pa[ipa][1] == u) ipa++;
                if (pb[ipb][1] == u) ipb++;
                if (fa[ifa][1] == u) ifa++;
                if (fb[ifb][1] == u) ifb++;
            }
        }

        Console.WriteLine($"{ans} {cnt}");
    }

    static List<int[]> RemoveDuplicates(List<int[]> list)
    {
        int k = 0;
        for (int i = 0; i < list.Count; i++)
        {
            if (k > 0 && list[k - 1][0] == list[i][0])
                list[k - 1][1] = list[i][1];
            else
                list[k++] = list[i];
        }
        list.RemoveRange(k, list.Count - k);
        return list;
    }

    static int Gcd(int a, int b)
    {
        while (b != 0)
        {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        while (t-- > 0)
        {
            Solve();
        }
    }
}
