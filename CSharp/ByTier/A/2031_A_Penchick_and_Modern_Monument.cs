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
        var ans = new int[t];
        for (var u = 0; u < t; ++u)
        {
            var n = NN;
            var a = NList;
            var count = new int[n + 1];
            foreach (var ai in a) ++count[ai];
            ans[u] = n - count.Max();
        }
        WriteLine(string.Join("\n", ans));
    }
}
