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
            var r = long.Parse(line[2]) - 1;
            var c = long.Parse(line[3]) - 1;
            getAns(h, w, r, c);
        }
    }
    static void getAns(long h, long w, long r, long c)
    {
        var d = h - 1 - r;
        var ans = d * (w * 2L - 1) + w - c - 1;
        Console.WriteLine(ans);
    }
}
