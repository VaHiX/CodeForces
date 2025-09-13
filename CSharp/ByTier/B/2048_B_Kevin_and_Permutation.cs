using System.Linq;
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
            getAns(n, k);
        }
    }
    static void getAns(int n, int k)
    {
        if (k == 0)
        {
            Console.WriteLine(string.Join(" ", Enumerable.Range(1, n)));
            return;
        }
        var p = k - 1;
        var av = 1;
        var ans = new int[n];
        while (p < n)
        {
            ans[p] = av++;
            p += k;
        }
        for (int i = 0; i < n; i++)
        {
            if (ans[i] == 0) ans[i] = av++;
        }
        Console.WriteLine(string.Join(" ", ans));
    }
}
