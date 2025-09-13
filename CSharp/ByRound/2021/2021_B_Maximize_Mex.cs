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
            line = Console.ReadLine().Trim().Split(' ');
            var a = Array.ConvertAll(line, int.Parse);
            getAns(n, x, a);
        }
    }
    static void getAns(int n, int x, int[] a)
    {
        var d = new Dictionary<int, int>();
        foreach (var z in a)
        {
            if (d.ContainsKey(z)) d[z]++;
            else d[z] = 1;
        }
        var r = new Dictionary<int, int>();
        for (int i = 0; i <= n+10; i++)
        {
            if (d.ContainsKey(i))
            {
                d[i]--;
                if (d[i] > 0)
                {
                    var w = i % x;
                    if (r.ContainsKey(w)) r[w] += d[i];
                    else r[w] = d[i];
                }
            }
            else
            {
                var rr = i % x;
                if (r.ContainsKey(rr))
                {
                    r[rr]--;
                    if (r[rr] == 0) r.Remove(rr);
                }
                else { Console.WriteLine(i); return; }
            }
        }
    }
}
