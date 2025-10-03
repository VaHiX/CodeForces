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
            var k = int.Parse(line[1]);
            line = Console.ReadLine().Trim().Split(' ');
            var a = Array.ConvertAll(line, int.Parse);
            getAns(n, k, a);
        }
    }
    static void getAns(int n, int k, int[] a)
    {
        var d = new Dictionary<int, int>();
        foreach (var x in a)
            if (d.ContainsKey(x)) d[x]++;
            else d[x] = 1;
        var e = d.OrderBy(x => x.Value).ToArray();
        var c = 0;
        for (int i = 0; i < d.Count - 1; i++)
        {
            if (k - e[i].Value >= 0) { k -= e[i].Value; c++; }
            else break;
        }
        Console.WriteLine(d.Count - c);
    }
}
