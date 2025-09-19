using System.Linq;
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
        var a = new int[n, n];
        for (int i = 0; i < n; i++)
        {
            string[] line = Console.ReadLine().Trim().Split(' ');
            for (int j = 0; j < n; j++) a[i, j] = int.Parse(line[j]);
        }
        var b = new int[2 * n];
        var hs = Enumerable.Range(1, 2 * n).ToHashSet();
        for (int i = 0; i < n; i++)
        {
            for (int j = i; j < n; j++)
            {
                b[i + j + 1] = a[i, j];
                hs.Remove(a[i, j]);
            }
        }
        var c = hs.ToArray();
        for (int i = 0; i < 2 * n; i++)
        {
            if (b[i] == 0) b[i] = c[0];
        }
        Console.WriteLine(string.Join(" ", b));
    }
}
