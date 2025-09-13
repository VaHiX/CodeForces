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
    static int count(int n, int[] a, bool odd)
    {
        var av = odd ? 1 : 0;
        var c = -1;
        for (int i = 0; i < n; i++)
        {
            if (a[i] % 2 == av) { c = i; break; }
        }
        if (c == -1) return 1000;
        for (int i = 0; i < n; i++)
        {
            if (a[n - 1 - i] % 2 == av) { c += i; break; }
        }
        return c;
    }
    static void getAns(int n, int[] a)
    {
        Array.Sort(a);
        Console.WriteLine(Min(count(n, a, true), count(n, a, false)));
    }
}
