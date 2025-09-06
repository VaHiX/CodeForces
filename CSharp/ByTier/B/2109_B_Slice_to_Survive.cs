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
            var h = long.Parse(line[0]);
            var w = long.Parse(line[1]);
            var a = long.Parse(line[2]);
            var b = long.Parse(line[3]);
            getAns(h, w, a, b);
        }
    }
    static int calc(long t)
    {
        var c = 0;
        while (t > 1)
        {
            if (t % 2 == 0) t /= 2;
            else t = (t + 1) / 2;
            c++;
        }
        return c;
    }
    static void getAns(long h, long w, long a, long b)
    {
        var c1 = Min(calc(b), calc(w - b + 1));
        var c2 = Min(calc(a), calc(h - a + 1));
        var ans = Min(calc(h) + c1, calc(w) + c2);
        Console.WriteLine(ans + 1);
    }
}
