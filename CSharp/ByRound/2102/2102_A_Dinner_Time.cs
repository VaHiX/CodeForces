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
            var p = int.Parse(line[2]);
            var q = int.Parse(line[3]);
            getAns(n, m, p, q);
        }
    }
    static void getAns(int n, int m, int p, int q)
    {
        var t = n / p;
        var r = n % p;
        if (r == 0) Console.WriteLine(t * q == m ? "YES" : "NO");
        else Console.WriteLine("YES");
    }
}
