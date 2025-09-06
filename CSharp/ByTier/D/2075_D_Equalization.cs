using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    const int SHIFT_MAX = 60;
    const int MAX_OP = 60;

    static void Main()
    {
        const ulong INF_COST = ulong.MaxValue;

        // Initialize DP table with INF_COST
        ulong[,] dp = new ulong[SHIFT_MAX + 1, SHIFT_MAX + 1];
        for (int i = 0; i <= SHIFT_MAX; i++)
        {
            for (int j = 0; j <= SHIFT_MAX; j++)
            {
                dp[i, j] = INF_COST;
            }
        }
        dp[0, 0] = 0;

        // DP loop
        for (int op = 1; op <= MAX_OP; op++)
        {
            ulong[,] nextDp = (ulong[,])dp.Clone();
            for (int i = 0; i <= SHIFT_MAX; i++)
            {
                for (int j = 0; j <= SHIFT_MAX; j++)
                {
                    if (dp[i, j] == INF_COST) continue;

                    if (i + op <= SHIFT_MAX)
                    {
                        nextDp[i + op, j] = Math.Min(nextDp[i + op, j], dp[i, j] + (1UL << op));
                    }
                    if (j + op <= SHIFT_MAX)
                    {
                        nextDp[i, j + op] = Math.Min(nextDp[i, j + op], dp[i, j] + (1UL << op));
                    }
                }
            }
            dp = nextDp;
        }

        // Store combinations in a list
        List<(int shiftX, int shiftY, ulong cost)> combos = new List<(int, int, ulong)>();
        for (int i = 0; i <= SHIFT_MAX; i++)
        {
            for (int j = 0; j <= SHIFT_MAX; j++)
            {
                if (dp[i, j] != INF_COST)
                {
                    combos.Add((i, j, dp[i, j]));
                }
            }
        }

        // Read number of test cases
        int T = int.Parse(Console.ReadLine());
        while (T-- > 0)
        {
            string[] inputs = Console.ReadLine().Split();
            ulong X = ulong.Parse(inputs[0]);
            ulong Y = ulong.Parse(inputs[1]);

            if (X == Y)
            {
                Console.WriteLine(0);
                continue;
            }

            ulong best = INF_COST;
            foreach (var combo in combos)
            {
                ulong newX = X >> combo.shiftX;
                ulong newY = Y >> combo.shiftY;
                if (newX == newY)
                {
                    best = Math.Min(best, combo.cost);
                }
            }
            Console.WriteLine(best);
        }
    }
}
