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
            getAns(n);
        }
    }
    static void getAns(int n)
    {
        var aa = new List<int>() { 1, 8, 49, 288, 1681, 9800, 57121, 332928 };
        if (aa.Contains(n)) { Console.WriteLine(-1); return; }
        var ans = Enumerable.Range(1, n).ToArray();
        for (int i = 0; i < 8; i++)
        {
            if (n > aa[i])
            {
                var w = ans[aa[i] - 1];
                ans[aa[i] - 1] = ans[aa[i]];
                ans[aa[i]] = w;
            }
        }
        Console.WriteLine(string.Join(" ", ans));
    }
}
