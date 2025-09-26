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
            var a1 = int.Parse(line[0]);
            var a2 = int.Parse(line[1]);
            var a4 = int.Parse(line[2]);
            var a5 = int.Parse(line[3]);
            getAns(a1, a2, a4, a5);
        }
    }
    static int calc(int a1, int a2, int a3, int a4, int a5)
    {
        var res = 0;
        if (a1 + a2 == a3) res++;
        if (a2 + a3 == a4) res++;
        if (a3 + a4 == a5) res++;
        return res;
    }
    static void getAns(int a1, int a2, int a4, int a5)
    {
        var ans = 0;
        var w = a1 + a2;
        ans = Max(ans, calc(a1, a2, w, a4, a5));
        w = a4 - a2;
        ans = Max(ans, calc(a1, a2, w, a4, a5));
        w = a5 - a4;
        ans = Max(ans, calc(a1, a2, w, a4, a5));
        Console.WriteLine(ans);
    }
}

