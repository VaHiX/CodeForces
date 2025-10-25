// Problem: CF 2121 E - Sponsor of Your Problems
// https://codeforces.com/contest/2121/problem/E

/*
E. Sponsor of Your Problems

This problem asks to find the minimum value of f(l,x) + f(x,r) for all integers x in [l, r],
where f(a,b) is the number of matching digits at corresponding positions in the decimal representation of a and b.

The approach uses dynamic programming with digit DP (Digit Dynamic Programming) technique:
We try to construct a number x from left to right such that it is within the bounds [l, r],
and calculate how many digits match with l and r at each step.

Time Complexity: O(3 * 2 * 2 * d) = O(d), where d is the number of digits in l and r.
Space Complexity: O(d * 2 * 2) = O(d), where d is the number of digits in l and r.

Algorithms/Techniques:
- Digit DP
- Dynamic Programming with states (position, tight lower bound, tight upper bound)

*/

using System;
class Program {
  const int INF = (int)1e9;
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      string[] inputs = Console.ReadLine().Split();
      string L = inputs[0];
      string R = inputs[1];
      int n = L.Length;
      int[,,] dp = new int[20, 2, 2]; // dp[pos][lo][hi]: minimum cost at position pos with tight constraints
      for (int i = 0; i <= n; i++)
        for (int lo = 0; lo < 2; lo++)
          for (int hi = 0; hi < 2; hi++)
            dp[i, lo, hi] = INF;
      dp[0, 1, 1] = 0; // initial state: start at position 0, both bounds are tight
      for (int i = 0; i < n; i++) {
        int dL = L[i] - '0';
        int dR = R[i] - '0';
        for (int lo = 0; lo < 2; lo++) {
          for (int hi = 0; hi < 2; hi++) {
            if (dp[i, lo, hi] == INF)
              continue;
            int low = lo == 1 ? dL : 0;
            int high = hi == 1 ? dR : 9;
            for (int d = low; d <= high; d++) {
              int new_lo = (lo == 1 && d == dL) ? 1 : 0;
              int new_hi = (hi == 1 && d == dR) ? 1 : 0;
              int cost = 0;
              if (d == dL)
                cost++; // increment cost if digit matches left bound
              if (d == dR)
                cost++; // increment cost if digit matches right bound
              dp[i + 1, new_lo, new_hi] =
                  Math.Min(dp[i + 1, new_lo, new_hi], dp[i, lo, hi] + cost);
            }
          }
        }
      }
      int ans = INF;
      for (int lo = 0; lo < 2; lo++)
        for (int hi = 0; hi < 2; hi++)
          ans = Math.Min(ans, dp[n, lo, hi]);
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/CodeForces/