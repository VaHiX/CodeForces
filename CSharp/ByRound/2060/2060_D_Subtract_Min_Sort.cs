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
            var a = Array.ConvertAll(line, int.Parse);
            getAns(n, a);
        }
    }
    static void getAns(int n, int[] a)
    {
        for (int i = 0; i < n - 1; i++)
        {
            if (a[i] > a[i + 1]) { Console.WriteLine("NO"); return; }
            var w = Min(a[i], a[i + 1]);
            a[i] -= w;
            a[i + 1] -= w;
        }
        Console.WriteLine("YES");
    }
}

