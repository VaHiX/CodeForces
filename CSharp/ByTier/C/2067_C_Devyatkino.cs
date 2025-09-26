using System.Linq;
using System.Collections.Generic;
using System;

public class hello
{
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            var n = long.Parse(Console.ReadLine().Trim());
            getAns(n);
        }
    }
    static int calc(long n, int t)
    {
        for (int i = 1; i <= 9; i++)
        {
            n += t;
            foreach (var x in n.ToString())
                if (x == '7') return i;
        }
        return 10;
    }
    static void getAns(long n)
    {
        foreach (var x in n.ToString())
            if (x == '7') { Console.WriteLine(0); return; }
        var a = new int[] { 9, 99, 999, 9999, 99999, 999999, 9999999, 99999999, 999999999 };
        var ans = new List<int>();
        foreach (var x in a) ans.Add(calc(n, x));
        Console.WriteLine(ans.Min());
    }
}
