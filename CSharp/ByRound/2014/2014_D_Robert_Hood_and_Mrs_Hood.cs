using static System.Math;
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
            var d = int.Parse(line[1]);
            var k = int.Parse(line[2]);
            getAns(n, d, k);
        }
    }
    static void getAns(int n, int d, int k)
    {
        var a = new int[n + 2];
        for (int i = 0; i < k; i++)
        {
            string[] line = Console.ReadLine().Trim().Split(' ');
            var L = int.Parse(line[0]);
            var r = int.Parse(line[1]);
            var pL = Max(L - d + 1, 1);
            a[pL]++;
            a[r + 1]--;
        }
        var maxi = 1;
        var maxv = a[1];
        var mini = 1;
        var minv = a[1];
        for (int i = 2; i <= n - d + 1; i++)
        {
            a[i] += a[i - 1];
            if (a[i] > maxv) { maxv = a[i]; maxi = i; }
            if (a[i] < minv) { minv = a[i]; mini = i; }
        }
        Console.WriteLine("{0} {1}", maxi, mini);
    }
}
