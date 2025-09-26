using System;

public class hello
{
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            var x = int.Parse(Console.ReadLine().Trim());
            getAns(x);
        }
    }
    static bool check(int x, int y, int z)
    {
        if (x + y <= z) return false;
        if (y + z <= x) return false;
        if (z + x <= y) return false;
        return true;
    }
    static void getAns(int x)
    {
        var t = 0;
        for (int i = 0; i <= 30; i++)
        {
            if (((x >> i) & 1) == 1) t = i;
        }
        var y = (1 << t) - 1;
        var z = x ^ y;
        Console.WriteLine(check(x, y, z) ? y : -1);
    }
}
