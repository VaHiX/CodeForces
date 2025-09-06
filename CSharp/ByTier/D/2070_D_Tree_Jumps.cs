using System;

class Program
{
    const int MOD = 998244353;

    static void Main()
    {
        // Read ALL input (including multi-line) and split into tokens
        string[] input = Console.In.ReadToEnd().Split(
            new[] { ' ', '\t', '\n', '\r' }, 
            StringSplitOptions.RemoveEmptyEntries
        );
        
        int ptr = 0;
        int t = int.Parse(input[ptr++]);
        
        for (int testCase = 0; testCase < t; testCase++)
        {
            int n = int.Parse(input[ptr++]);

            if (n == 1)
            {
                Console.WriteLine("1");
                continue;
            }

            int[] parents = new int[n - 1];
            for (int i = 0; i < n - 1; i++)
            {
                parents[i] = int.Parse(input[ptr++]);
            }

            int[] depth = new int[n + 1];
            depth[1] = 0;
            int maxDepth = 0;

            for (int i = 2; i <= n; i++)
            {
                int p = parents[i - 2];
                depth[i] = depth[p] + 1;
                if (depth[i] > maxDepth) maxDepth = depth[i];
            }

            long[] cnt = new long[maxDepth + 1];
            for (int i = 2; i <= n; i++)
            {
                cnt[depth[i]]++;
            }

            long[] S = new long[maxDepth + 2];
            if (maxDepth >= 1)
            {
                S[maxDepth] = cnt[maxDepth] % MOD;
                for (int d = maxDepth - 1; d >= 1; d--)
                {
                    long factor = (cnt[d] - 1 + MOD) % MOD; // Ensure non-negative
                    S[d] = (cnt[d] % MOD + (factor * S[d + 1]) % MOD) % MOD;
                }
            }

            long result = (1 + (maxDepth >= 1 ? S[1] : 0)) % MOD;
            Console.WriteLine(result);
        }
    }
}