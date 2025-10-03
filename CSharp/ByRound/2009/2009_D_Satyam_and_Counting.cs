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
            var y0 = new HashSet<int>();
            var y1 = new HashSet<int>();
            for (int i = 0; i < n; i++)
            {
                string[] line = Console.ReadLine().Trim().Split(' ');
                var t = int.Parse(line[0]);
                if (line[1] == "0") y0.Add(t);
                else y1.Add(t);
            }
            getAns(n, y0, y1);
        }
    }
    static int count(HashSet<int> a, HashSet<int> b)
    {
        var count = 0;
        foreach (var z in a)
            if (b.Contains(z - 1) && b.Contains(z + 1)) count++;
        return count;
    }
    static void getAns(int n, HashSet<int> y0, HashSet<int> y1)
    {
        var same = 0;
        foreach (var z in y0)
        {
            if (y1.Contains(z)) same++;
        }
        var ans = (long)same * (n - 2);
        ans += count(y0, y1);
        ans += count(y1, y0);
        Console.WriteLine(ans);
    }
}
