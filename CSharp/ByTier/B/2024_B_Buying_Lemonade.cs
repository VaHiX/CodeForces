using System;

public class hello
{
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            string[] line = Console.ReadLine().Trim().Split(' ');
            var n = int.Parse(line[0]);
            var k = int.Parse(line[1]);
            line = Console.ReadLine().Trim().Split(' ');
            var a = Array.ConvertAll(line, long.Parse);
            getAns(n, k, a);
        }
    }
    static void getAns(int n, int k, long[] a)
    {
        Array.Sort(a);
        var b = new long[n];
        b[0] = a[0] * n;
        for (int i = 1; i < n; i++) b[i] = (a[i] - a[i - 1]) * (n - i);
        var c = new long[n];
        c[0] = b[0];
        if (c[0] >= k) { Console.WriteLine(k); return; }
        for (int i = 1; i < n; i++)
        {
            c[i] = c[i - 1] + b[i];
            if (c[i] >= k) { Console.WriteLine(k + i); return; }
        }
    }
}
