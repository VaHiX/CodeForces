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
            string[] line = Console.ReadLine().Trim().Split(' ');
            var a = Array.ConvertAll(line, int.Parse);
            getAns(n, a);
        }
    }
    static void getAns(int n, int [] a)
    {
        var ans = new List<int>();
        var used = new bool[n + 1];
        foreach(var x in a)
        {
            if (!used[x])
            {
                ans.Add(x);
                used[x] = true;
            }
        }
        for (int i = 1; i <= n; i++)
        {
            if (!used[i]) ans.Add(i);
        }
        Console.WriteLine(string.Join(" ",ans));
    }
}
