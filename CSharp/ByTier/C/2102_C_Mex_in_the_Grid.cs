using System.Text;
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
    static void print(int n, int[,] map)
    {
        var sb = new StringBuilder();
        var p = new int[n];
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++) p[j] = map[i, j];
            sb.AppendLine(string.Join(" ", p));
        }
        Console.Write(sb);
    }
    static void getAns(int n)
    {
        var map = new int[n, n];
        var dx = new int[] { 0, 1, 0, -1 };
        var dy = new int[] { 1, 0, -1, 0 };
        var k = 2 * n - 1;
        var a = new int[k];
        var w = 0;
        for (int i = 0; i < k - 1; i++)
        {
            if (i % 2 == 0) w++;
            a[i] = w;
        }
        a[k - 1] = n - 1;
        var x = n % 2 == 0 ? (n - 1) / 2 : n / 2;
        var y = x;
        var p = 0;
        map[x, y] = p++;
        for (int i = 0; i < n * 2 - 1; i++)
        {
            for (int j = 0; j < a[i]; j++)
            {
                x += dx[i % 4];
                y += dy[i % 4];
                map[x, y] = p++;
            }
        }
        print(n, map);
    }
}
