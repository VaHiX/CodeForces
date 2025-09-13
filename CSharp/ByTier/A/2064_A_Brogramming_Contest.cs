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
            var s = Console.ReadLine().Trim();
            getAns(n, s);
        }
    }
    static void getAns(int n, string s)
    {
        var a = new List<char>();
        if (s[0] == '1') a.Add('1');
        for (int i = 1; i < n; i++)
        {
            if (s[i] != s[i - 1]) a.Add(s[i]);
        }
        Console.WriteLine(a.Count);
    }
}
