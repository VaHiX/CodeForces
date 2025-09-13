using static System.Math;
using System;

public class hello
{
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            var s = Console.ReadLine().Trim();
            getAns(s);
        }
    }
    static void getAns(string s)
    {
        var c2 = 0;
        var c3 = 0;
        var sum = 0;
        foreach (var x in s)
        {
            var w = x - '0';
            sum += w;
            if (w == 2) c2++;
            else if (w == 3) c3++;
        }
        var t = sum;
        c2 = Min(c2, 8);
        c3 = Min(c3, 2);
        for (int i = 0; i <= c2; i++)
        {
            for (int j = 0; j <= c3; j++)
            {
                var ww = t + i * 2 + j * 6;
                if (ww % 9 == 0) { Console.WriteLine("YES"); return; }
            }
        }
        Console.WriteLine("NO");
    }
}
