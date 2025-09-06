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
        var t = a[0];
        var c = 1;
        var ans = long.MaxValue;
        for (int i = 1; i < n; i++)
        {
            if (a[i] == a[i - 1]) c++;
            else
            {
                ans = Min(ans, (long)(n - c) * a[i - 1]);
                c = 1;
            }
        }
        ans = Min(ans, (long)(n - c) * a[n - 1]);
        Console.WriteLine(ans);
    }
}
