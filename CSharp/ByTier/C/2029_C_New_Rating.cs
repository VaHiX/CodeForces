using System;

class Program
{
    static int Solve(int n, int[] arr)
    {
        int[,] dp = new int[n, 2];
        int maxVal = 0;

        int Calc(int x, int target)
        {
            if (x < target)
            {
                return x + 1;
            }
            else if (x > target)
            {
                return x - 1;
            }
            return x;
        }

        for (int i = 0; i < n; i++)
        {
            int previousVal = i > 0 ? dp[i - 1, 0] : 0;
            dp[i, 0] = Calc(previousVal, arr[i]);

            int alternateVal = i > 0 ? dp[i - 1, 1] : -n - 10;
            dp[i, 1] = Math.Max(maxVal, Calc(alternateVal, arr[i]));

            maxVal = Math.Max(maxVal, dp[i, 0]);
        }

        return dp[n - 1, 1];
    }

    static void Main(string[] args)
    {
        int testCases = int.Parse(Console.ReadLine());
        string[] results = new string[testCases];

        for (int t = 0; t < testCases; t++)
        {
            int n = int.Parse(Console.ReadLine());
            int[] arr = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);

            int result = Solve(n, arr);
            results[t] = result.ToString();
        }

        Console.WriteLine(string.Join("\n", results));
    }
}
