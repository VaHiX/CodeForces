using System;
using System.Linq;

public class Program
{
    public static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        while (t-- > 0)
        {
            int n = int.Parse(Console.ReadLine());
            int[] a = new int[n + 1];
            // Read the numbers; note that we're using 1-indexing
            string[] tokens = Console.ReadLine().Split();
            for (int i = 1; i <= n; i++)
            {
                a[i] = int.Parse(tokens[i - 1]);
            }

            // Create dp array with dimensions [n+1, n+1]. C# arrays are automatically zero-initialized.
            long[,] dp = new long[n + 1, n + 1];

            for (int len = 1; len <= n; len++)
            {
                for (int i = 1; i + len - 1 <= n; i++)
                {
                    int j = i + len - 1;
                    if (len < 3)
                    {
                        dp[i, j] = 0;
                        continue;
                    }
                    long best = Math.Max(dp[i + 1, j], dp[i, j - 1]);
                    for (int m = i + 1; m < j; m++)
                    {
                        long tmp = 0;
                        if (i + 1 <= m - 1)
                            tmp += dp[i + 1, m - 1];
                        if (m + 1 <= j - 1)
                            tmp += dp[m + 1, j - 1];
                        tmp += (long)a[i] * a[m] * a[j];
                        best = Math.Max(best, tmp);
                    }
                    for (int k = i; k < j; k++)
                    {
                        best = Math.Max(best, dp[i, k] + dp[k + 1, j]);
                    }
                    dp[i, j] = best;
                }
            }
            Console.WriteLine(dp[1, n]);
        }
    }
}
