using System;

public class hello
{
    public static int MOD = 1000000007;
    static void Main()
    {
        var n = int.Parse(Console.ReadLine().Trim());
        string[] line = Console.ReadLine().Trim().Split(' ');
        var a = Array.ConvertAll(line, int.Parse);
        line = Console.ReadLine().Trim().Split(' ');
        var b = Array.ConvertAll(line, int.Parse);
        getAns(n, a, b);
    }
    static void getAns(int n, int[] a, int[] b)
    {
        var t = new long[100001];
        t[0] = 1;
        for (int i = 1; i < 100001; i++)
        {
            t[i] = t[i - 1] * 2;
            t[i] %= MOD;
        }
        var ans = new long[n];
        for (int i = 0; i < n; i++) ans[i] = t[b[i]];
        Console.WriteLine(string.Join("\n", ans));
    }
}
