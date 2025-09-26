using System.Linq;
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
            var m = int.Parse(line[1]);
            getAns(n, m);
        }
    }
    static (long s, long f) calc(int m, long[] a)
    {
        var p = m;
        var res = 0L;
        var s = 0L;
        for (int i = 0; i < m; i++)
        {
            res += p-- * a[i];
            s += a[i];
        }
        return (s, res);
    }
    static void getAns(int n, int m)
    {
        var t = new (long s, int id)[n];
        var sum = 0L;
        for (int i = 0; i < n; i++)
        {
            string[] line = Console.ReadLine().Trim().Split(' ');
            var a = Array.ConvertAll(line, long.Parse);
            var w = calc(m, a);
            t[i] = (w.s, i);
            sum += w.f;
        }
        t = t.OrderBy(x => x.s).ToArray();
        for (int i = 1; i < n; i++)
        {
            sum += (m * (long)(i)) * t[i].s;
        }
        Console.WriteLine(sum);
    }
}

