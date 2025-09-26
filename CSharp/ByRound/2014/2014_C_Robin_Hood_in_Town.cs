using System.Collections.Generic;
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
    static bool check(int n, long[] a, long sum, long t)
    {
        a[n - 1] += t;
        var w = (sum + t) / (2 * n);
        var p = UpperBound(a, w);
        a[n - 1] -= t;
        if (p > 0)
        {
            if (sum + t == n * 2 * a[p - 1])
            {
                var p2 = LowerBound(a, a[p - 1]);
                return p2 > n - p2;
            }
        }
        return p > n - p;
    }
    static void getAns(int n, long[] a)
    {
        Array.Sort(a);
        var sum = a.Sum();
        var t = check(n, a, sum, 0);
        if (t) { Console.WriteLine(0); return; }
        var tt = long.MaxValue - sum - a[n - 1];
        var t2 = check(n, a, sum, tt);
        if (!t2) { Console.WriteLine(-1); return; }
        var ok = tt;
        var ng = 0L;
        while (ok - ng > 1)
        {
            var mid = ng + (ok - ng) / 2;
            if (check(n, a, sum, mid)) ok = mid;
            else ng = mid;
        }
        Console.WriteLine(ok);
    }
    static int LowerBound<T>(T[] arr, int start, int end, T value, IComparer<T> comparer)
    {
        var low = start;
        var high = end;
        while (low < high)
        {
            var mid = (high + low) / 2;
            if (comparer.Compare(arr[mid], value) < 0) low = mid + 1;
            else high = mid;
        }
        return low;
    }
    static int LowerBound<T>(T[] arr, T value) where T : IComparable
       => LowerBound(arr, 0, arr.Length, value, Comparer<T>.Default);

    static int UpperBound<T>(T[] arr, int start, int end, T value, IComparer<T> comparer)
    {
        var low = start;
        var high = end;
        while (low < high)
        {
            var mid = (high + low) / 2;
            if (comparer.Compare(arr[mid], value) <= 0) low = mid + 1;
            else high = mid;
        }
        return low;
    }
    static int UpperBound<T>(T[] arr, T value) where T : IComparable
       => UpperBound(arr, 0, arr.Length, value, Comparer<T>.Default);
}
