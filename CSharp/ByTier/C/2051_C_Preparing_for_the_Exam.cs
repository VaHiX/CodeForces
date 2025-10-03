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
            string[] line = Console.ReadLine().Trim().Split(' ');
            var n = int.Parse(line[0]);
            var m = int.Parse(line[1]);
            var k = int.Parse(line[2]);
            line = Console.ReadLine().Trim().Split(' ');
            var a = Array.ConvertAll(line, int.Parse);
            line = Console.ReadLine().Trim().Split(' ');
            var hs = Array.ConvertAll(line, int.Parse).ToHashSet();
            getAns(n, m, k, a, hs);
        }
    }
    static void getAns(int n, int m, int k, int[] a, HashSet<int> hs)
    {
        var nq = new List<int>();
        for (int i = 1; i <= n; i++)
        {
            if (!hs.Contains(i)) nq.Add(i);
        }
        var nqc = nq.Count;
        int ansv;
        if (nqc == 0) ansv = 1;
        else if (nqc > 1) ansv = 0;
        else ansv = -1;
        var ans = new int[m];
        for (int i = 0; i < m; i++)
        {
            if (ansv == 1) ans[i] = 1;
            else if (ansv == 0) ans[i] = 0;
            else
            {
                if (a[i] == nq[0]) ans[i] = 1;
                else ans[i] = 0;
            }
        }
        Console.WriteLine(string.Join("", ans));
    }
}
