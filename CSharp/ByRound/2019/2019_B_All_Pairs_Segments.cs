using System.Collections.Generic;
using System;

public class hello
{
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            string[] line = Console.ReadLine().Trim().Split(' ');
            var n = int.Parse(line[0]);
            var q = int.Parse(line[1]);
            line = Console.ReadLine().Trim().Split(' ');
            var a = Array.ConvertAll(line, int.Parse);
            line = Console.ReadLine().Trim().Split(' ');
            var b = Array.ConvertAll(line, long.Parse);
            getAns(n, q, a, b);
        }
    }
    static void getAns(int n, int q, int[] a, long[] b)
    {
        var d = new Dictionary<long, long>();
        d[n - 1] = 1;
        for (int i = 1; i < n; i++)
        {
            var w = ((long)i + 1) * ((long)n - i) - 1;
            if (d.ContainsKey(w)) d[w]++;
            else d[w] = 1;
            var w2 = i * ((long)n - i);
            if (a[i] - a[i - 1] == 1) continue;
            if (d.ContainsKey(w2)) d[w2] += a[i] - a[i - 1] - 1;
            else d[w2] = a[i] - a[i - 1] - 1;
        }
        var ans = new long[q];
        for (int i = 0; i < q; i++)
        {
            if (!d.ContainsKey(b[i])) ans[i] = 0;
            else ans[i] = d[b[i]];
        }
        Console.WriteLine(string.Join(" ", ans));
    }
}
