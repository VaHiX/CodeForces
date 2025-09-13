using System.Text;

namespace ChickenJockey;
class Program
{
    static long Solve()
    {
        int n = Next();
        int[] a = new int[n];
        for (int i = 0; i < n; i++) a[i] = Next();
        int[] last = new int[n];
        if (a[^1] == 1) last[^1] = last.Length - 1;
        else last[^1] = last.Length;
        for (int i = a.Length - 2; i >= 0; i--)
        {
            if (a[i] != 1) last[i] = i;
            else last[i] = last[i + 1];
        }
        long[,] dp = new long[n + 1, 3];
        dp[n - 1, 0] = a[^1];
        dp[n - 1, 1] = a[^1];
        dp[n - 1, 2] = 0;
        for (int i = a.Length - 2; i >= 0; i--)
        {
            dp[i, 0] = a[i] + dp[i + 1, 0];
            if (a[i + 1] <= i + 1)
                dp[i, 0] = Math.Min(dp[i, 0], a[i] + dp[i + 1, 2]);
            else
            {
                dp[i, 0] = Math.Min(dp[i, 0], a[i] + dp[i + 1, 1] - i - 1);
            }
            dp[i, 1] = a[i] + dp[i + 1, 0];
            if (a[i + 1] < 2)
                dp[i, 1] = Math.Min(dp[i, 1], a[i] + dp[i + 1, 2]);
            else
            {
                dp[i, 1] = Math.Min(dp[i, 1], a[i] + dp[i + 1, 1] - 1);
            }
            dp[i, 2] = dp[i + 1, 0];
            if (a[i + 1] < 2)
                dp[i, 2] = Math.Min(dp[i, 2], dp[i + 1, 2]);
            else
            {
                dp[i, 2] = Math.Min(dp[i, 2], dp[i + 1, 1] - 1);
            }
        }

        return dp[0, 0];
    }

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