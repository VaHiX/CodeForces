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
            var m = int.Parse(line[1]);
            getAns(n, m);
        }
    }
    static bool check(int n, int m, int[] a)
    {
        for (int i = 0; i < m - 1; i++)
        {
            if (a[i + 1] - a[i] != n) return false;
        }
        return true;
    }
    static void getAns(int n, int m)
    {
        var c = new (int a0, int id)[n];
        var no = false;
        for (int i = 0; i < n; i++)
        {
            string[] line = Console.ReadLine().Trim().Split(' ');
            var a = Array.ConvertAll(line, int.Parse);
            Array.Sort(a);
            c[i] = (a[0], i + 1);
            if (!check(n, m, a)) no = true;
        }
        if (no) { Console.WriteLine(-1); return; }
        c = c.OrderBy(x => x.a0).ToArray();
        var c2 = Enumerable.Range(0, n).ToArray();
        var ans = new int[n];
        for (int i = 0; i < n; i++)
        {
            if (c[i].a0 != c2[i]) { Console.WriteLine(-1); return; }
            ans[i] = c[i].id;
        }
        Console.WriteLine(string.Join(" ", ans));
    }
}

