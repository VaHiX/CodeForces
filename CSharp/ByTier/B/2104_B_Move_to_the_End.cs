using static System.Math;
using System.Collections.Generic;
using System;

public class hello
{
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            var n = int.Parse(Console.ReadLine().Trim());
            string[] line = Console.ReadLine().Trim().Split(' ');
            var a = Array.ConvertAll(line, long.Parse);
            getAns(n, a);
        }
    }
    static void getAns(int n, long[] a)
    {
        var b = new long[n];
        b[0] = a[0];
        for (int i = 1; i < n; i++) b[i] = Max(b[i - 1], a[i]);
        var c = new long[n];
        c[n - 1] = a[n - 1];
        for (int i = n - 2; i >= 0; i--) c[i] = c[i + 1] + a[i];
        var ans = new List<long>();
        for (int i = n - 1; i >= 1; i--)
        {
            if (a[i] >= b[i - 1]) ans.Add(c[i]);
            else ans.Add(c[i] - a[i] + b[i - 1]);
        }
        ans.Add(c[0]);
        Console.WriteLine(string.Join(" ", ans));
    }
}
