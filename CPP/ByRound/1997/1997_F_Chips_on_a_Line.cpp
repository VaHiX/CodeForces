// Problem: CF 1997 F - Chips on a Line
// https://codeforces.com/contest/1997/problem/F

/*
Algorithm/Techniques:
- This solution uses dynamic programming with memoization to compute the number of ways to place chips on a line such that the minimum number of chips remaining after operations is exactly m.
- It leverages Fibonacci-like sequence to define "cost" for each point, where cost[i] = cost[i-1] + cost[i-2], with base cases cost[0]=0, cost[1]=1.
- A key insight is that the cost of a chip distribution can be computed as the minimum number of chips required after applying allowed operations.
- The DP state tracks the number of ways to distribute n chips in up to x positions with a given total cost.
- Time Complexity: O(n * x * max_fib), where max_fib is bounded by 25.
- Space Complexity: O(x * max_fib), for the DP table and auxiliary arrays.
*/

#include <string.h>
#include <algorithm>
#include <iostream>

using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int n, x, m, C = 25;
  cin >> n >> x >> m;
  int mod = 998244353;
  int fab[C];
  fab[0] = 0, fab[1] = 1;
  for (int i = 2; i < C; i++)
    fab[i] = fab[i - 1] + fab[i - 2];
  if (m >= C) {  // If m is too large, no valid combinations exist
    cout << 0 << endl;
    return 0;
  }
  int sm = fab[x] * n;  // Maximum possible total cost
  int cost[sm + 1];
  cost[0] = 0;
  for (int i = 1; i <= sm; i++) {
    cost[i] = C;  // Initialize with large value
    for (int j = 1; j < C && fab[j] <= i; j++)
      cost[i] = min(cost[i - fab[j]] + 1, cost[i]);  // Compute minimum operations for cost
  }
  int dp[2][x + 1][sm + 1];
  memset(dp, 0, sizeof(dp));
  // Initialize base case: placing zero chips in any number of points
  for (int p = 1; p <= x; p++)
    dp[0][p][0] = 1;
  // Iteratively build DP for n chips
  for (int i = 1; i <= n; i++) {
    bool b = i & 1, nb = (i - 1) & 1;
    for (int j = 1; j <= x; j++)
      for (int k = 0; k <= fab[j] * i; k++) {
        dp[b][j][k] = dp[b][j - 1][k];  // Not placing a chip at point j
        if (fab[j] <= k && i > 0)
          dp[b][j][k] = (dp[b][j][k] + dp[nb][j][k - fab[j]]) % mod;  // Placing a chip at point j
      }
  }
  int ans = 0;
  for (int i = 1; i <= sm; i++) {
    if (cost[i] == m)  // If this total cost corresponds to desired m
      ans = (ans + dp[n & 1][x][i]) % mod;  // Add valid combinations
  }
  cout << ans << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/