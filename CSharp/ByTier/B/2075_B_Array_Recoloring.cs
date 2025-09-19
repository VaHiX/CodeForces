using static System.Math;
using System.Linq;
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
            var k = int.Parse(line[1]);
            line = Console.ReadLine().Trim().Split(' ');
            var a = Array.ConvertAll(line, long.Parse);
            getAns(n, k, a);
        }
    }
    static long k1 (int n, long[] a)
    {
        var amax = a.Max();
        if (a[0] == amax | a[n - 1] == amax)
        {
            Array.Sort(a);
            return amax + a[n - 2];
        }
        else return Max(a[0], a[n - 1]) + amax;
    }
    static void getAns(int n, int k, long[] a)
    {
        if (k == 1)
        {
            Console.WriteLine(k1(n,a));
            return;
        }
        Array.Sort(a);
        Array.Reverse(a);
        var s = a.Take(k + 1).Sum();
        Console.WriteLine(s);
    }
}
