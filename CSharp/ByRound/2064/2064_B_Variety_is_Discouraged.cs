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
            var n = int.Parse(Console.ReadLine().Trim());
            string[] line = Console.ReadLine().Trim().Split(' ');
            var a = Array.ConvertAll(line, int.Parse);
            getAns(n, a);
        }
    }
    static void getAns(int n, int[] a)
    {
        if (n == 1) { Console.WriteLine("1 1"); return; }
        var d = new Dictionary<int, int>();
        foreach (var x in a)
            if (d.ContainsKey(x)) d[x]++;
            else d[x] = 1;
        var b = new bool[n];
        for (int i = 0; i < n; i++)
        {
            if (d[a[i]] == 1) b[i] = true;
        }
        var tc = b.Count(x => x == true);
        if (tc == 0) { Console.WriteLine(0); return; }
        var f = false;
        var tL = 0; var ansL = 0; var ansr = 0;
        var ans = 0;
        if (b[0]) { f = true; tL = 0; }
        for (int i = 1; i < n; i++)
        {
            if (b[i])
            {
                if (!f)
                {
                    f = true;
                    tL = i;
                }
            }
            else
            {
                if (f)
                {
                    f = false;
                    var tt = i - tL;
                    if (tt > ans) { ans = tt; ansL = tL; ansr = i - 1; }
                }
            }
        }
        if (f)
        {
            var ttt = n - tL;
            if (ttt > ans) { ansL = tL; ansr = n - 1; }
        }
        Console.WriteLine("{0} {1}", ansL + 1, ansr + 1);
    }
}

