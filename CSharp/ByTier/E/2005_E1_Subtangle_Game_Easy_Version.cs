using System;
using System.Collections.Generic;
using System.IO;

class Program
{
    static void Main()
    {
        #if DEBUG
        Console.SetIn(new StreamReader("input.txt"));
        Console.SetOut(new StreamWriter("output.txt") { AutoFlush = true });
        #endif

        int tt = int.Parse(Console.ReadLine());

        while (tt-- > 0)
        {
            string[] input = Console.ReadLine().Split();
            int l = int.Parse(input[0]);
            int n = int.Parse(input[1]);
            int m = int.Parse(input[2]);

            List<int> arr = new List<int>();
            string[] arrInput = Console.ReadLine().Split();
            foreach (var s in arrInput)
            {
                arr.Add(int.Parse(s));
            }

            int[][] g = new int[n][];
            for (int i = 0; i < n; i++)
            {
                g[i] = new int[m];
                string[] gInput = Console.ReadLine().Split();
                for (int j = 0; j < m; j++)
                {
                    g[i][j] = int.Parse(gInput[j]);
                }
            }

            int[][][] dp = new int[n][][];
            for (int i = 0; i < n; i++)
            {
                dp[i] = new int[m][];
                for (int j = 0; j < m; j++)
                {
                    dp[i][j] = new int[l];
                    for (int k = 0; k < l; k++)
                    {
                        dp[i][j][k] = -1;
                    }
                }
            }

            Func<int, int, int, int> f = null;
            f = (i, j, k) =>
            {
                if (i == n || j == m || k == l)
                    return 0;

                if (dp[i][j][k] != -1)
                    return dp[i][j][k];

                int notTake = Math.Max(f(i + 1, j, k), f(i, j + 1, k));
                int take = (g[i][j] == arr[k]) && (f(i + 1, j + 1, k + 1) == 0) ? 1 : 0;

                return dp[i][j][k] = (notTake != 0 || take != 0) ? 1 : 0;
            };

            Console.WriteLine(f(0, 0, 0) != 0 ? "T" : "N");
        }
    }
}
