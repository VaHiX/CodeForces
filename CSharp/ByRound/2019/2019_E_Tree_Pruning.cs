using System;
using System.Collections.Generic;

class Program
{
    static List<List<int>> e;
    static int[] dp, max_dp, ct, ct2;
    static bool[] vis;

    static void Dfs(int u)
    {
        vis[u] = true;
        max_dp[u] = dp[u];
        foreach (int v in e[u])
        {
            if (vis[v])
                continue;
            dp[v] = dp[u] + 1;
            Dfs(v);
            max_dp[u] = Math.Max(max_dp[u], max_dp[v]);
        }
    }

    static void Main()
    {
        int t = int.Parse(Console.ReadLine()); 

        while (t-- > 0)
        {
            int n = int.Parse(Console.ReadLine()); 

            e = new List<List<int>>(n + 3);
            for (int i = 0; i < n + 3; i++)
                e.Add(new List<int>());
            
            dp = new int[n + 3];
            max_dp = new int[n + 3];
            ct = new int[n + 3];
            ct2 = new int[n + 3];
            vis = new bool[n + 3];

            for (int i = 1; i < n; i++)
            {
                var edge = Console.ReadLine().Split();
                int a = int.Parse(edge[0]);
                int b = int.Parse(edge[1]);
                e[a].Add(b);
                e[b].Add(a);
            }

            Dfs(1);

            for (int i = 1; i <= n; i++)
            {
                ct[dp[i]]++;
                ct2[max_dp[i]]++;
            }

            int result = int.MaxValue; 
            int countA = 0; 
            int countB = 0; 

            for (int i = 1; i <= n; i++)
            {
                countB += ct[i];
            }

            for (int i = 1; i <= n; i++)
            {
                countB -= ct[i];
                result = Math.Min(result, countA + countB);
                countA += ct2[i];
            }

            Console.WriteLine(result);
        }
    }
}
