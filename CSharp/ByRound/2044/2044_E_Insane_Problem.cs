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
            var k = int.Parse(line[0]);
            var L1 = int.Parse(line[1]);
            var r1 = int.Parse(line[2]);
            var L2 = int.Parse(line[3]);
            var r2 = int.Parse(line[4]);
            getAns(k, L1, r1, L2, r2);
        }
    }
    static int calc(long t, int L1, int r1, int L2, int r2)
    {
        var wL = L2 % t == 0 ? L2 / t : L2 / t + 1;
        var wr = r2 / t;
        var wwL = Max(L1, wL);
        var wwr = Min(r1, wr);
        return (int)Max(0, wwr - wwL + 1);
    }
    static void getAns(int k, int L1, int r1, int L2, int r2)
    {
        var t = 1L;
        var rmax = Max(r1, r2);
        var ans = calc(t, L1, r1, L2, r2);
        while (true)
        {
            t *= k;
            if (t > rmax) break;
            var w = calc(t, L1, r1, L2, r2);
            ans += w;
        }
        Console.WriteLine(ans);
    }
}
