using System.Collections.Generic;
using System;

public class hello
{
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            string[] line = Console.ReadLine().Trim().Split(' ');
            var n = int.Parse(line[0]);
            var x = int.Parse(line[1]);
            getAns(n, x);
        }
    }
    static void getAns(int n, int x)
    {
        var mex = 0;
        for (int i = 0; i < 31; i++)
        {
            if (((x >> i) & 1) == 0) { mex = (1 << i); break; }
        }
        var ans = new List<int>();
        var ttt = 0;
        for (int i = 0; i < mex; i++)
        {
            ans.Add(i);
            ttt |= i;
            if (ans.Count == n) break;
        }
        var anscount = ans.Count;
        if (anscount == n)
        {
            if (ttt != x)
            {
                if (ans[n - 1] != x) ans[n - 1] = x;
            }
        }
        else
        {
            var cc = n - anscount;
            for (int i = 0; i < cc; i++) ans.Add(x);
        }
        Console.WriteLine(string.Join(" ", ans));
    }
}
