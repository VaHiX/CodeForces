using System.Collections.Generic;
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
            var m = int.Parse(line[1]);
            var q = int.Parse(line[2]);
            line = Console.ReadLine().Trim().Split(' ');
            var b = Array.ConvertAll(line, int.Parse);
            line = Console.ReadLine().Trim().Split(' ');
            var a = Array.ConvertAll(line, int.Parse);
            getAns(n, m, q, b, a);
        }
    }
    static void getAns(int n, int m, int q, int[] b, int[] a)
    {
        Array.Sort(b);
        var ans = new int[q];
        for (int i = 0; i < q; i++)
        {
            var p = LowerBound(b, a[i]);
            if (p == m) ans[i] = n - b[m - 1];
            else if (p == 0) ans[i] = b[0] - 1;
            else
            {
                var L = b[p - 1];
                var r = b[p];
                var t = (r - L) / 2 + L;
                ans[i] = Min(t - L, r - t);
            }
        }
        Console.WriteLine(string.Join("\n", ans));
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
}
