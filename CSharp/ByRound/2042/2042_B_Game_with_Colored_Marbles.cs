using System.Collections.Generic;
using System.Linq;
using System;

public class hello
{
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            Console.ReadLine();
            string[] line = Console.ReadLine().Trim().Split(' ');
            var a = Array.ConvertAll(line, int.Parse);
            getAns(a);
        }
    }
    static void getAns(int[] a)
    {
        var d = new Dictionary<int, int>();
        foreach (var x in a)
        {
            if (d.ContainsKey(x)) d[x]++;
            else d[x] = 1;
        }
        var dc = d.Count;
        var c1 = d.Count(x => x.Value == 1);
        var ans = (c1 + 1) / 2 * 2 + dc - c1;
        Console.WriteLine(ans);
    }
}
