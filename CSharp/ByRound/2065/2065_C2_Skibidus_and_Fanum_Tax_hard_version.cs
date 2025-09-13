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
            line = Console.ReadLine().Trim().Split(' ');
            var a = Array.ConvertAll(line, int.Parse);
            line = Console.ReadLine().Trim().Split(' ');
            var b = Array.ConvertAll(line, int.Parse);
            getAns(n, m,a, b);
        }
    }
    static void getAns(int n,int m, int[] a, int[] b)
    {
        Array.Sort(b);
        var pre = Min(a[0], b[0] - a[0]);
        for (int i = 1; i < n; i++)
        {
            var p = LowerBound(b, pre + a[i]);
            if (p == m)
            {
                if (a[i] >= pre) pre = a[i];
                else { Console.WriteLine("NO");return; }
            } 
            else
            {
                if (a[i] >= pre) pre = Min(b[p] - a[i], a[i]);
                else pre = b[p] - a[i];
            }
        }
        Console.WriteLine("YES");
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
