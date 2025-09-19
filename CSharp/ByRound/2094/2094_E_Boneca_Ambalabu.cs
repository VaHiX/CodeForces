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
    static long calc(int n, int t, int[] b)
    {
        var res = 0L;
        for (int i = 0; i < 30; i++)
        {
            if (((t >> i) & 1) == 1) res += (n - b[i]) * (1L << i);
            else res += b[i] * (1L << i);
        }
        return res;
    }
    static void getAns(int n, int[] a)
    {
        var b = new int[30];
        foreach (var x in a)
        {
            for (int i = 0; i < 30; i++)
            {
                if (((x >> i) & 1) == 1) b[i]++;
            }
        }
        var ans = 0L;
        foreach (var x in a) ans = Max(ans, calc(n, x, b));
        Console.WriteLine(ans);
    }
}

