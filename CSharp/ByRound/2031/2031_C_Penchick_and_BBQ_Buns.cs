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
        // Test();
    }
    static void Test()
    {
        for (var i = 1; i < 100; ++i) for (var j = i + 1; j < 100; ++j)
        {
            var k2 = i * i + j * j;
            var k = (int)Math.Sqrt(k2);
            if (k * k == k2)
            {
                WriteLine($"{i} {j} {k}: {i * i} + {j * j} = {k * k}");
            }
        }
    }
    static void Solve()
    {
        var t = NN;
        var ans = new string[t];
        for (var u = 0; u < t; ++u)
        {
            var n = NN;
            if (n % 2 == 0)
            {
                var a = new int[n];
                for (var i = 0; i < n; ++i) a[i] = i / 2 + 1;
                ans[u] = string.Join(" ", a);
            }
            else if (n > 25)
            {
                var a = new int[n];
                var f = new int[27] { 13, 1,1,2,2,3,3,4,4, 13, 5,5,6,6,7,7,8,8,9,9,10,10, 11, 12, 12, 13, 11 };
                for (var i = 0; i < f.Length; ++i) a[i] = f[i];
                for (var i = f.Length; i < n; ++i) a[i] = (i + 1) / 2;
                ans[u] = string.Join(" ", a);
            }
            else ans[u] = "-1";
        }
        WriteLine(string.Join("\n", ans));
    }
}
