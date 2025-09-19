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
        var a = new int[n];
        a[0] = 1;
        var amax = 1;
        var amin = 1;
        for (int i = 0; i < n - 1; i++)
        {
            if (s[i] == '>') { amax++; a[i + 1] = amax; }
            else { amin--; a[i + 1] = amin; }
        }
        var p = n - amax;
        for (int i = 0; i < n; i++) a[i] += p;
        Console.WriteLine(string.Join(" ", a));
    }
}
