using System;

public class hello
{
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            string[] line = Console.ReadLine().Trim().Split(' ');
            var L = long.Parse(line[0]);
            var r = long.Parse(line[1]);
            getAns(L, r);
        }
    }
    static bool check(long r, long t) => t * (t - 1) / 2 + 1 <= r;
    static void getAns(long L, long r)
    {
        r -= L - 1;
        var ok = 1L;
        var ng = 100000L;
        while (ng - ok > 1)
        {
            var mid = ok + (ng - ok) / 2;
            if (check(r, mid)) ok = mid;
            else ng = mid;
        }
        Console.WriteLine(ok);
    }
}
