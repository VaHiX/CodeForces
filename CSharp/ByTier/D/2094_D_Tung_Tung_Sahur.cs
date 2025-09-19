using System.Collections.Generic;
using System;

public class P
{
    public char c { get; set; }
    public int t { get; set; }
}

public class hello
{
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            var p = Console.ReadLine().Trim();
            var s = Console.ReadLine().Trim();
            getAns(p, s);
        }
    }
    static List<P> calc(string s)
    {
        var res = new List<P>();
        var n = s.Length;
        var count = 1;
        for (int i = 1; i < n; i++)
        {
            if (s[i - 1] == s[i]) count++;
            else
            {
                res.Add(new P { c = s[i - 1], t = count });
                count = 1;
            }
        }
        res.Add(new P { c = s[n - 1], t = count });
        return res;
    }
    static void getAns(string p, string s)
    {
        var psp = calc(p);
        var pss = calc(s);
        var n = psp.Count;
        if (n != pss.Count) { Console.WriteLine("NO"); return; }
        for (int i = 0; i < n; i++)
        {
            if (psp[i].c != pss[i].c) { Console.WriteLine("NO"); return; }
            if (psp[i].t * 2 < pss[i].t) { Console.WriteLine("NO"); return; }
            if (psp[i].t > pss[i].t) { Console.WriteLine("NO"); return; }
        }
        Console.WriteLine("YES");
    }
}

