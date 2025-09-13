using System.Text;

namespace SetsOfComplementarySums;
class Program
{
    static long Solve()
    {
        long n = Next();
        long x = Next();

        long min = n * (n + 1) / 2;
        if (min > x + 1) return 0;
        if (n == 1) return x;

        // long[] dp = new long[x + 2];
        // dp[min] = 1;
        // for (long j = 2; j < n; j++)
        // {
        //     for (long i = dp.Length - 1 - j; i >= min; i--)
        //     {
        //         if (dp[i] != 0)
        //         {
        //             for (long k = i + j; k < dp.Length; k += j)
        //             {
        //                 dp[k] = (dp[k] + dp[i]) % mod;
        //             }
        //         }
        //     }
        // }

        long[] dp1 = new long[x + 2];
        dp1[min] = 1;
        for (long j = 2; j < n; j++)
        {
            for (long i = min; i + j < dp1.Length; i++)
            {
                if (dp1[i] != 0)
                    dp1[i + j] = (dp1[i + j] + dp1[i]) % mod;
            }
        }

        long ans = 0;
        for (long i = min; i < dp1.Length; i++)
        {
            ans += dp1[i] * ((x + 2 - i) * (x + 3 - i) / 2 % mod) % mod;
        }
        return ans % mod;
    }

    const int mod = 998244353;

    static void Main(string[] args)
    {
        long t = Next();
        for (int i = 0; i < t; i++) writer.WriteLine(Solve());
        writer.Flush();
    }

    static long Next()
    {
        int c;
        int m = 1;
        long res = 0;
        do
        {
            c = reader.Read();
            if (c == '-')
                m = -1;
        } while (c < '0' || c > '9');
        res = c - '0';
        while (true)
        {
            c = reader.Read();
            if (c < '0' || c > '9')
                return m * res;
            res *= 10;
            res += c - '0';
        }
    }
    static readonly StreamReader reader = new(Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
    static readonly StreamWriter writer = new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}
