using System.Collections.Generic;
using System;

public class hello
{
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            var s = Console.ReadLine().Trim();
            getAns(s);
        }
    }
    static void getAns(string s)
    {
        var n = s.Length;
        var z = new List<int>();
        var sum = 0;
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '(') sum++;
            else
            {
                sum--;
                if (sum == 0) z.Add(i);
            }
        }
        Console.WriteLine(z.Count == 1 ? "NO" : "YES");
    }
}
