using System.Linq;
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
        var asum = a.Sum();
        if (asum % n != 0) { Console.WriteLine("NO"); return; }
        var t = asum / n;
        for (int i = 1; i < n - 1; i++)
        {
            if (a[i - 1] > t)
            {
                var d = a[i - 1] - t;
                a[i - 1] = t;
                a[i + 1] += d;
            }
            else if (a[i - 1] < t)
            {
                var d = t - a[i - 1];
                a[i - 1] = t;
                a[i + 1] -= d;
            }
        }
        Console.WriteLine(a[n - 2] == t && a[n - 1] == t ? "YES" : "NO");
    }
}
