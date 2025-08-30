using System.Text;

namespace AppendingPermutationsEasy;
class Program
{
    static long Solve()
    {
        int n = Next();
        int m = Next();
        int[,] a = new int[n + 1, n + 1];
        for (int i = 0; i < m; i++) a[Next(), Next()] = 1;

        for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) a[i, j] += a[i - 1, j - 1];

        long[] dp = new long[n + 2];
        dp[1] = 1;

        long[,] dp2 = new long[n + 2, n + 2];

        for (int i = 1; i <= n; i++)
        {
            if (dp[i] == 0) continue;
            for (int s = 1; s <= n; s++)
            {
                if (s + i > n + 1) break;
                for (int r = 1; r <= s; r++)
                {
                    int j = i + s - r;
                    int k = i + s - 1;
                    if (a[j, s] - a[i - 1, r - 1] > 0) continue;
                    if (a[k, r - 1] > 0) continue;

                    dp[i + s] = (dp[i + s] + dp[i] - dp2[i, r - 1] + mod) % mod;
                    if (r == 1)
                        dp2[i + s, s] = (dp2[i + s, s] + dp[i]) % mod;
                }

            }
        }

        return dp[n + 1];
    }

    const int mod = 998244353;

    static void Main(string[] args)
    {
        long t = Next();
        for (int i = 0; i < t; i++) writer.WriteLine(Solve());
        writer.Flush();
    }

    static int Next()
    {
        int c;
        int m = 1;
        int res = 0;
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

