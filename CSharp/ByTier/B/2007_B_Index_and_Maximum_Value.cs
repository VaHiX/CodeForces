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
            line = Console.ReadLine().Trim().Split(' ');
            var a = Array.ConvertAll(line, long.Parse);
            getAns(n, m, a);
        }
    }
    static void getAns(int n, int m, long[] a)
    {
        var t = a.Max();
        var ans = new long[m];
        for (int i = 0; i < m; i++)
        {
            string[] line = Console.ReadLine().Trim().Split(' ');
            var L = long.Parse(line[1]);
            var r = long.Parse(line[2]);
            if (t >= L && t <= r)
            {
                if (line[0] == "+") t++;
                else t--;
            }
            ans[i] = t;
        }
        Console.WriteLine(string.Join(" ", ans));
    }
}
