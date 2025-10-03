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
            line = Console.ReadLine().Trim().Split(' ');
            var b = Array.ConvertAll(line, int.Parse);
            getAns(n, a, b);
        }
    }
    static void getAns(int n, int[] a, int[] b)
    {
        var c = 0;
        var d1 = 0;
        var eq = 0;
        var d2 = int.MaxValue;
        for (int i = 0; i < n; i++)
        {
            if (b[i] > a[i])
            {
                c++;
                if (c > 1) { Console.WriteLine("NO"); return; }
                d1 = b[i] - a[i];
            }
            else d2 = Min(d2, a[i] - b[i]);
        }
        if (c == 0) Console.WriteLine("YES");
        else Console.WriteLine(d2 >= d1 ? "YES" : "NO");
    }
}
