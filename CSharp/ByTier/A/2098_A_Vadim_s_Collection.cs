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
        var a = new int[10];
        for (int i = 0; i < 10; i++) a[i] = s[i] - '0';
        Array.Sort(a);
        var used = new bool[10];
        var b = new int[10];
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
            {
                if (!used[j] && (a[j] >= 9 - i)) { used[j] = true; b[i] = a[j]; break; }
            }
        Console.WriteLine(string.Join("", b));
    }
}

