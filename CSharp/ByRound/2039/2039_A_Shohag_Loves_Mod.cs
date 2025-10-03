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
        var ans = new List<int>();
        for (int i = 0; i < n; i++) ans.Add(i * 2 + 1);
        Console.WriteLine(string.Join(" ", ans));
    }
}
