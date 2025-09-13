using System.Collections.Generic;
using System;

public class hello
{
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            var s = Console.ReadLine().Trim();
            var q = int.Parse(Console.ReadLine().Trim());
            getAns(s, q);
        }
    }
    static void check0to1(int n, int[] a, HashSet<int> hs, int p)
    {
        a[p] = 1;
        hs.Remove(p - 2);
        hs.Remove(p - 3);
        if (a[p + 1] == 1 && a[p + 2] == 0 && a[p + 3] == 0) hs.Add(p);
        if (a[p - 1] == 1 && a[p + 1] == 0 && a[p + 2] == 0) hs.Add(p - 1);
    }
    static void check1to0(int n, int[] a, HashSet<int> hs, int p)
    {
        a[p] = 0;
        hs.Remove(p);
        hs.Remove(p - 1);
        if (a[p - 3] == 1 && a[p - 2] == 1 && a[p - 1] == 0) hs.Add(p - 3);
        if (a[p - 2] == 1 && a[p - 1] == 1 && a[p + 1] == 0) hs.Add(p - 2);
    }
    static void getAns(string s, int q)
    {
        var n = s.Length;
        var a = new int[n + 6];
        for (int i = 0; i < 3; i++) { a[i] = -1; a[i + n + 3] = -1; }
        for (int i = 0; i < n; i++) a[i + 3] = s[i] - '0';
        var hs = new HashSet<int>();
        for (int i = 0; i < n; i++)
        {
            if (a[i] == 1 && a[i + 1] == 1 && a[i + 2] == 0 && a[i + 3] == 0) { hs.Add(i); }
        }
        for (int i = 0; i < q; i++)
        {
            string[] line = Console.ReadLine().Trim().Split(' ');
            var p = int.Parse(line[0]) + 2;
            var av = int.Parse(line[1]);
            if (a[p] != av)
            {
                if (av == 1) check0to1(n, a, hs, p);
                else check1to0(n, a, hs, p);
            }
            Console.WriteLine(hs.Count > 0 ? "YES" : "NO");
        }
    }
}
