using System.Numerics;
using System;

public class hello
{
    public static int MOD = 1000000007;
    static void Main()
    {
        var T = int.Parse(Console.ReadLine().Trim());
        while (T-- > 0)
        {
            var n = int.Parse(Console.ReadLine().Trim());
            string[] line = Console.ReadLine().Trim().Split(' ');
            var a = Array.ConvertAll(line, long.Parse);
            getAns(n, a);
        }
    }
    static int ModInv(int a, int m) => (int)BigInteger.ModPow(a, m - 2, m);
    static void getAns(int n, long[] a)
    {

        var b = new long[n];
        b[n - 1] = a[n - 1];
        for (int i = n - 2; i >= 0; i--)
        {
            b[i] = b[i + 1] + a[i];
            b[i] %= MOD;
        }
        var ans = 0L;
        for (int i = 0; i < n - 1; i++)
        {
            var w = a[i] * b[i + 1];
            w %= MOD;
            ans += w;
            ans %= MOD;
        }
        ans *= 2;
        ans %= MOD;
        ans *= ModInv(n, MOD);
        ans %= MOD;
        ans *= ModInv(n - 1, MOD);
        ans %= MOD;
        Console.WriteLine(ans);
    }
}
