using System.Linq;
using System.Collections.Generic;
using System;

public class P
{
    public int a { get; set; }
    public int b { get; set; }
}

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
        var ps = new P[n];
        for (int i = 0; i < n; i++)
        {
            string[] line = Console.ReadLine().Trim().Split(' ');
            var a = int.Parse(line[0]);
            var b = int.Parse(line[1]);
            ps[i] = new P { a = a, b = b };
        }
        var ans = new List<int>();
        foreach (var y in ps.OrderBy(x => x.a + x.b))
        {
            ans.Add(y.a);
            ans.Add(y.b);
        }
        Console.WriteLine(string.Join(" ", ans));
    }
}
