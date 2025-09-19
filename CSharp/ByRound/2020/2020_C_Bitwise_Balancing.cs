using System.Collections.Generic;
using System;

public class hello
{
    public static Dictionary<string, int> dic;
    static void Main()
    {
        dic = calc();
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            string[] line = Console.ReadLine().Trim().Split(' ');
            var b = long.Parse(line[0]);
            var c = long.Parse(line[1]);
            var d = long.Parse(line[2]);
            getAns(b, c, d);
        }
    }
    static Dictionary<string, int> calc()
    {
        var dic = new Dictionary<string, int>();
        for (int a = 0; a < 2; a++)
            for (int b = 0; b < 2; b++)
                for (int c = 0; c < 2; c++)
                {
                    var d = (a | b) - (a & c);
                    dic[b.ToString() + c.ToString() + d.ToString()] = a;
                }
        return dic;
    }
    static void getAns(long b, long c, long d)
    {
        var ans = 0L;
        for (int i = 0; i < 61; i++)
        {
            var bb = ((b >> i) & 1) == 1 ? "1" : "0";
            var cc = ((c >> i) & 1) == 1 ? "1" : "0";
            var dd = ((d >> i) & 1) == 1 ? "1" : "0";
            var k = bb + cc + dd;
            if (k == "100" | k == "011") { Console.WriteLine(-1); return; }
            if (dic[k] == 1) ans |= 1L << i;
        }
        Console.WriteLine(ans);
    }
}
