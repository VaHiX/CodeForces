using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Text;
using static System.Console;
using ll = System.Int64;



int t = int.Parse(ReadLine());
while (t-- > 0)
{
    int n = int.Parse(ReadLine());
    var nums = ReadLine().Split().Select(int.Parse).ToArray();
    var mp = new Dictionary<int, List<int>>();
    int[] dp = new int[n + 1];
    for (int i = 1; i <= n; i++)
    {
        int v = nums[i - 1];
        if (!mp.ContainsKey(v)) mp[v] = new List<int>();
        mp[v].Add(i);
        dp[i] = dp[i - 1];
        if (mp[v].Count >= v)
        {
            if (dp[mp[v][mp[v].Count - v] - 1] + v > dp[i]) dp[i] = dp[mp[v][mp[v].Count - v] - 1] + v;
        }
    }
    WriteLine(dp[n]);
}
