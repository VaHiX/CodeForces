using static System.Math;
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
    static long calc(long[] a, int start, int end)
    {
        var res = 0L;
        for (int i = start; i < end; i += 2) res = Max(res, a[i + 1] - a[i]);
        return res;
    }
    static void even(int n, long[] a)
    {
        Console.WriteLine(calc(a, 0, n));
    }
    static void odd(int n, long[] a)
    {
        var ans = calc(a, 1, n);
        ans = Min(ans, calc(a, 0, n - 1));
        if (n < 3) { Console.WriteLine(ans); return; }
        for (int i = 2; i < n - 1; i += 2)
        {
            var t = Max(calc(a, 0, i - 1), calc(a, i + 1, n));
            ans = Min(ans, t);
        }
        Console.WriteLine(ans);
    }
    static void getAns(int n, long[] a)
    {
        if (n == 1) { Console.WriteLine(1); return; }
        if (n % 2 == 1) odd(n, a);
        else even(n, a);
    }
}
