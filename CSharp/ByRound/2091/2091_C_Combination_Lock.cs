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
        if (n % 2 == 0) { Console.WriteLine(-1); return; }
        var ans = new List<int>() { 1 };
        for (int i = n; i >= 2; i--) ans.Add(i);
        Console.WriteLine(string.Join(" ", ans));
    }
}
