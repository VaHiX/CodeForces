using System;
using static System.Console;
using System.Linq;
using System.Collections.Generic;

class Program
{
    static int NN => int.Parse(ReadLine());
    static int[] NList => ReadLine().Split().Select(int.Parse).ToArray();
    static string[] SList(long n) => Enumerable.Repeat(0, (int)n).Select(_ => ReadLine()).ToArray();
    public static void Main()
    {
        Solve();
    }
    static void Solve()
    {
        var t = NN;
        var ans = new string[t];
        for (var u = 0; u < t; ++u)
        {
            var n = NN;
            var a = NList;
            ans[u] = string.Join(" ", Rabbit(n, a));
        }
        WriteLine(string.Join("\n", ans));
    }
    static int[] Rabbit(int n, int[] a)
    {
        var s = new int[n];
        for (var i = 0; i < n; ++i) s[i] = i;
        Array.Sort(s, (l, r) =>
        {
            var d = a[l].CompareTo(a[r]);
            if (d != 0) return d;
            return l.CompareTo(r);
        });
        var minlist = new int[n];
        for (var i = 0; i < n; ++i) minlist[i] = int.MaxValue;
        minlist[^1] = a[^1];
        for (var i = n - 2; i >= 0; --i) minlist[i] = Math.Min(minlist[i + 1], a[i]);
        var ans = new int[n];
        for (var i = 0; i < n; ++i) ans[i] = -1;
        var prevpos = n;
        for (var i = n - 1; i >= 0; --i)
        {
            var pos = s[i];
            if (ans[pos] >= 0) continue;
            if (prevpos == n) ans[pos] = a[pos];
            else if (a[pos] > minlist[prevpos]) ans[pos] = ans[prevpos];
            else ans[pos] = a[pos];
            for (var j = pos + 1; j < prevpos; ++j) ans[j] = ans[j - 1];
            prevpos = pos;
        }
        return ans;
    }
}
