using System;

public class hello
{
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            string[] line = Console.ReadLine().Trim().Split(' ');
            var x = int.Parse(line[0]);
            var n = int.Parse(line[1]);
            var m = int.Parse(line[2]);
            getAns(x, n, m);
        }
    }
    static int getMin(int x, int n, int m)
    {
        for (int i = 0; i < m; i++)
        {
            if (x == 0 | x == 1) break;
            x = (x + 1) / 2;
        }
        for (int i = 0; i < n; i++)
        {
            if (x == 0) return 0;
            x /= 2;
        }
        return x;
    }
    static int getMax(int x, int n, int m)
    {
        for (int i = 0; i < n; i++)
        {
            x /= 2;
            if (x == 0) return 0;
        }
        for (int i = 0; i < m; i++)
        {
            if (x == 1) return 1;
            x = (x + 1) / 2;
        }
        return x;
    }
    static void getAns(int x, int n, int m)
    {
        var min = getMin(x, n, m);
        var max = getMax(x, n, m);
        Console.WriteLine("{0} {1}", min, max);
    }
}
