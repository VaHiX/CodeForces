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
            line = Console.ReadLine().Trim().Split(' ');
            var a = Array.ConvertAll(line, int.Parse);
            getAns(n, k, a);
        }
    }
    static void getAns(int n, int k, int[] a)
    {
        Array.Sort(a);
        Array.Reverse(a);
        var asum = a.Sum();
        if (asum <= k) { Console.WriteLine(k - asum); return; }
        var p = 0;
        var tsum = 0;
        while (p < n)
        {
            if (tsum + a[p] == k) { Console.WriteLine(0); return; }
            if (tsum + a[p] > k) { Console.WriteLine(k - tsum); return; }
            tsum += a[p];
            p++;
        }
    }
}
