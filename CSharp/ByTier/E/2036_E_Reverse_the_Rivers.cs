using static System.Math;
using System.Collections.Generic;
using System;

public class hello
{
    static void Main()
    {
        string[] line = Console.ReadLine().Trim().Split(' ');
        var h = int.Parse(line[0]);
        var w = int.Parse(line[1]);
        var q = int.Parse(line[2]);
        getAns(h, w, q);
    }
    static void getAns(int h, int w, int q)
    {
        var aa = new int[w][];
        for (int i = 0; i < w; i++) aa[i] = new int[h];
        for (int i = 0; i < h; i++)
        {
            string[] line = Console.ReadLine().Trim().Split(' ');
            for (int j = 0; j < w; j++) aa[j][i] = int.Parse(line[j]);
        }
        for (int i = 0; i < w; i++)
            for (int j = 1; j < h; j++) aa[i][j] |= aa[i][j - 1];
        for (int i = 0; i < q; i++)
        {
            var m = int.Parse(Console.ReadLine().Trim());
            var L = 0;
            var r = h-1;
            for (int j = 0; j < m; j++)
            {
                string[] line = Console.ReadLine().Trim().Split(' ');
                var a = int.Parse(line[0]) - 1;
                var b = line[1];
                var c = int.Parse(line[2]);
                if (b == ">")
                {
                    var p = UpperBound(aa[a], c);
                    L = Max(L, p);
                }
                else
                {
                    var p = LowerBound(aa[a], c);
                    r = Min(r, p - 1);
                }
            }
            if (L > r) Console.WriteLine(-1);
            else Console.WriteLine(L + 1);
        }
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
