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
            getAns(n, m);
        }
    }
    static void getAns(int n, int m)
    {
        string[] line = Console.ReadLine().Trim().Split(' ');
        var a = Array.ConvertAll(line, int.Parse);
        line = Console.ReadLine().Trim().Split(' ');
        var b = Array.ConvertAll(line, int.Parse);
        var hs = new HashSet<int>();
        var pa = 0;
        foreach (var x in b)
        {
            if (x == a[pa])
            {
                hs.Add(a[pa]);
                if (pa + 1 != n) pa++;
            }
            else
            {
                if (!hs.Contains(x)) { Console.WriteLine("TIDAK"); return; }
            }
        }
        Console.WriteLine("YA");
    }
}
