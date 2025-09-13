using static System.Math;
using System;

public class hello
{
    public static long sum, b;
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            string[] line = Console.ReadLine().Trim().Split(' ');
            var n = long.Parse(line[0]);
            var k = long.Parse(line[1]);
            getAns(n, k);
        }
    }
    static bool calc(long k, long p)
    {
        var r = k + p;
        var sumL = r * (r + 1) / 2 - b;
        var sumr = sum - sumL;
        return sumL >= sumr;
    }
    static long calc2(long k, long p)
    {
        var r = k + p;
        var sumL = r * (r + 1) / 2 - b;
        var sumr = sum - sumL;
        return Abs(sumL - sumr);
    }
    static void getAns(long n, long k)
    {
        var r = n + k - 1;
        b = k * (k - 1) / 2;
        sum = r * (r + 1) / 2 - b;
        var ng = 0L;
        var ok = n - 1;
        while (ok - ng > 1)
        {
            var mid = ng + (ok - ng) / 2;
            if (calc(k, mid)) ok = mid;
            else ng = mid;
        }
        var ans1 = calc2(k, ok);
        var ans2 = calc2(k, ok - 1);
        Console.WriteLine(Min(ans1, ans2));
    }
}
