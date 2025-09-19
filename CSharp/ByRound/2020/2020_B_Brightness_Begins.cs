using static System.Math;
using System;

public class hello
{
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            var k = long.Parse(Console.ReadLine().Trim());
            getAns(k);
        }
    }
    static long calc(long t)
    {
        var w = (long)Sqrt(t);
        if (w * w > t) return t - (w - 1);
        else return t - w;
    }
    static void getAns(long k)
    {
        if (k == 1) { Console.WriteLine(2); return; }
        var ng = 1L;
        var ok = long.MaxValue;
        while (ok - ng > 1)
        {
            var mid = ng + (ok - ng) / 2;
            if (calc(mid) >= k) ok = mid;
            else ng = mid;
        }
        Console.WriteLine(ok);
    }
}
