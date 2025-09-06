using System;

public class hello
{
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            string[] line = Console.ReadLine().Trim().Split(' ');
            var x = long.Parse(line[0]);
            var y = long.Parse(line[1]);
            getAns(x, y);
        }
    }
    static void getAns(long x, long y)
    {
        if (x == y) { Console.WriteLine(-1); return; }
        if (y > x) { getAns(y, x); return; }
        Console.WriteLine((1L << 40) - x);
    }
}
