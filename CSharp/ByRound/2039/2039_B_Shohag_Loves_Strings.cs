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
        if (n == 1) { Console.WriteLine(-1); return; }
        for (int i = 0; i < n - 1; i++)
        {
            if (s[i] == s[i + 1]) { Console.WriteLine("{0}{1}", s[i], s[i + 1]); return; }
        }
        if (n == 2) { Console.WriteLine(-1); return; }
        for (int i = 0; i < n - 2; i++)
        {
            if (s[i] != s[i + 1] && s[i + 1] != s[i + 2] && s[i] != s[i + 2])
            {
                Console.WriteLine("{0}{1}{2}", s[i], s[i + 1], s[i + 2]);
                return;
            }
        }
        Console.WriteLine(-1);
    }
}
