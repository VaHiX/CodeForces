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
            var k = int.Parse(line[2]);
            getAns(n, m, k);
        }
    }
    static int[,] normal(int n, int m, int k)
    {
        var a = new int[n, m];
        var t = 1;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                a[i, j] = t;
                t++;
                if (t > k) t = 1;
            }
        }
        return a;
    }
    static int[,] shift1(int n, int m, int k)
    {
        var a = new int[n, m];
        var f = true;
        for (int i = 0; i < n; i++)
        {
            if (f)
            {
                var t = 1;
                for (int j = 0; j < m; j++)
                {
                    a[i, j] = t;
                    t++;
                    if (t > k) t = 1;
                }
                f = false;
            }
            else
            {
                var t = 2;
                for (int j = 0; j < m; j++)
                {
                    a[i, j] = t;
                    t++;
                    if (t > k) t = 1;
                }
                f = true;
            }
        }
        return a;
    }
    static void print(int n, int m, int[,] ans)
    {
        var p = new int[m];
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++) p[j] = ans[i, j];
            Console.WriteLine(string.Join(" ", p));
        }
    }
    static void getAns(int n, int m, int k)
    {
        if (m % k == 0)
        {
            var ans = shift1(n, m, k);
            print(n, m, ans);
        }
        else
        {
            var ans = normal(n, m, k);
            print(n, m, ans);
        }
    }
}
