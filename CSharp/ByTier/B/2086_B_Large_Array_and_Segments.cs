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
            var k = int.Parse(line[1]);
            var x = long.Parse(line[2]);
            line = Console.ReadLine().Trim().Split(' ');
            var a = Array.ConvertAll(line, long.Parse);
            getAns(n, k, x, a);
        }
    }
    static void getAns(int n, int k, long x, long[] a)
    {
        var asum = a.Sum();
        var t = x / asum;
        Array.Reverse(a);
        var tsum = t * asum;
        var w = tsum;
        if (w == x)
        {
            var ww = n * (k - t) + 1;
            if (ww <= 0) Console.WriteLine(0);
            else Console.WriteLine(ww);
            return;
        }
        for (int i = 0; i < n; i++)
        {
            w += a[i];
            if (w >= x)
            {
                var www = (long)n * k - (t * n + i);
                if (www <= 0) Console.WriteLine(0);
                else Console.WriteLine(www);
                return;
            }
        }
    }
}

