using System.Linq;
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
        var d = new Dictionary<long, int>();
        foreach (var x in a)
            if (d.ContainsKey(x)) d[x]++;
            else d[x] = 1;
        var e = d.OrderBy(x => x.Key).ToArray();
        if (e[0].Value >= 2) { Console.WriteLine("YES"); return; }
        var f = new List<long>();
        var m = e.Length;
        var emin = e[0].Key;
        for (int i = 1; i < m; i++)
        {
            if (e[i].Key % emin == 0) f.Add(e[i].Key);
        }
        var fc = f.Count;
        if (fc <= 1) { Console.WriteLine("NO"); return; }
        var g = Gcd(f[0], f[1]);
        if (g == emin) { Console.WriteLine("YES"); return; }
        if (fc == 2) { Console.WriteLine("NO"); return; }
        for (int i = 2; i < fc; i++)
        {
            g = Gcd(g, f[i]);
            if (g == emin) { Console.WriteLine("YES"); return; }
        }
        Console.WriteLine("NO");
    }
    public static long Gcd(long a, long b)
    {
        if (a < b) return Gcd(b, a);
        while (b != 0)
        {
            var w = a % b;
            a = b;
            b = w;
        }
        return a;
    }
}

