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
        if (n <= 4) { Console.WriteLine(-1); return; }
        var t = new List<int>();
        for (int i = 1; i <= n; i += 2)
        {
            if (i != 5) t.Add(i);
        }
        t.Add(5);
        t.Add(4);
        for (int i = 2; i <= n; i += 2)
        {
            if (i != 4) t.Add(i);
        }
        Console.WriteLine(string.Join(" ", t));
    }
}
