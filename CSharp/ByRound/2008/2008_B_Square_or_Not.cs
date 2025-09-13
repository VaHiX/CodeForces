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
            var s = Console.ReadLine().Trim();
            getAns(n, s);
        }
    }
    static void getAns(int n, string s)
    {
        var w = (int)Sqrt(n);
        if (w * w != n) { Console.WriteLine("NO"); return; }
        var t1 = new string('1', w);
        var t2 = "1" + new string('0', w - 2) + "1";
        for (int i = 1; i < w - 1; i++)
        {
            var s2 = s.Substring(i * w, w);
            if (s2 != t2) { Console.WriteLine("NO"); return; }
        }
        if (s.Substring(0, w) != t1) { Console.WriteLine("NO"); return; }
        if (s.Substring(n - w) != t1) { Console.WriteLine("NO"); return; }
        Console.WriteLine("YES");
    }
}
