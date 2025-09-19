using static System.Math;
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
            line = Console.ReadLine().Trim().Split(' ');
            var a = Array.ConvertAll(line, int.Parse);
            var b = int.Parse(Console.ReadLine().Trim());
            getAns(n, a, b);
        }
    }
    static void getAns(int n, int[] a, int b)
    {
        var pre = Min(a[0], b - a[0]);
        for (int i = 1; i < n; i++)
        {
            var k1 = a[i];
            var k2 = b - a[i];
            var mink = Min(k1, k2);
            if (mink >= pre) { pre = mink; continue; }
            else
            {
                var maxk = Max(k1, k2);
                if (maxk >= pre) { pre = maxk; continue; }
                else { Console.WriteLine("NO"); return; }
            }
        }
        Console.WriteLine("YES");
    }
}

