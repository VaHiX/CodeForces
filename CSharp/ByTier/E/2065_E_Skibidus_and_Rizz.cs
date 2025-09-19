using System.Text;
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
            var m = int.Parse(line[1]);
            var k = int.Parse(line[2]);
            getAns(n, m, k);
        }
    }
    static void rev(string s)
    {
        var s2 = s.ToCharArray();
        var n = s.Length;
        for (int i = 0; i < n; i++) s2[i] = s2[i] == '1' ? '0' : '1';
        Console.WriteLine(new string(s2));
    }
    static void getAns(int n, int m, int k)
    {
        if (Abs(n - m) > k) { Console.WriteLine(-1); return; }
        if (Max(n, m) < k) { Console.WriteLine(-1); return; }
        var f = false;
        if (m > n)
        {
            var w = n;
            n = m;
            m = w;
            f = true;
        }
        var sb = new StringBuilder();
        sb.Append(new string('0', k));
        n -= k;
        while (n > 0)
        {
            sb.Append("10");
            n--;
            m--;
        }
        sb.Append(new string('1', m));
        var s = sb.ToString();
        if (f) rev(s);
        else Console.WriteLine(s);
    }
}
