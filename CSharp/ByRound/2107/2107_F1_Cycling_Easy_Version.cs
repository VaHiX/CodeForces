using System;
using System.Linq;

class Program
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        
        while (t-- > 0)
        {
            int n = int.Parse(Console.ReadLine());
            var a = Console.ReadLine().Split().Select(int.Parse).ToArray();

            // Use 1-based indexing for a[]
            int[] agility = new int[n + 1];
            for (int i = 1; i <= n; i++)
            {
                agility[i] = a[i - 1];
            }

            long[] dp = new long[n + 1];
            for (int i = 0; i <= n; i++)
                dp[i] = long.MaxValue;

            dp[n] = 0;

            for (int i = n - 1; i >= 0; i--)
            {
                int p = i + 1;

                // Find position of the minimum element in agility[i+1 ... n]
                for (int j = i + 1; j <= n; j++)
                {
                    if (agility[j] < agility[p])
                        p = j;
                }

                for (int j = p; j <= n; j++)
                {
                    long swapCost = 2L * (j - p);
                    long overtakeCost = (long)(j - i) * agility[p];
                    long moveCost = (p - i - 1);

                    dp[i] = Math.Min(dp[i], dp[j] + swapCost + overtakeCost + moveCost);
                }
            }

            Console.WriteLine(dp[0]);
        }
    }
}
