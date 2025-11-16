// Problem: CF 1989 E - Distance to Different
// https://codeforces.com/contest/1989/problem/E

/*
 * Problem: E. Distance to Different
 * Purpose: Calculate the number of different arrays `b` that can be obtained
 *          by considering all possible arrays `a` of length `n` with elements from 1 to k.
 *          `b[i]` represents the minimum distance from `a[i]` to the nearest element 
 *          in `a` that is different from `a[i]`.
 *
 * Algorithm: Dynamic Programming with inclusion-exclusion principle.
 *            The key idea is to use DP over the positions, tracking how many
 *            distinct arrays `b` can be formed based on the transitions.
 *            The recurrence uses prefix sums and inclusion-exclusion to avoid overcounting.
 *
 * Time Complexity: O(n * k)
 * Space Complexity: O(n * k)
 */

#include <stdio.h>
#include <algorithm>

const int N = 2e5 + 10, M = 12;
const int mod = 998244353;
int n, k;
int dp[N][M], pre[M];

// Modular addition
int Inc(int x, int y) { return (x + y) >= mod ? x + y - mod : x + y; }

// Modular subtraction
int Dec(int x, int y) { return x < y ? x + mod - y : x - y; }

int main() {
  scanf("%d%d", &n, &k);
  
  // Base case: initial state
  dp[0][0] = 1, pre[0] = 1;
  
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= k + 1; ++j) {
      int to = std::min(j, k);
      // Add contribution from previous states
      dp[i][to] = Inc(dp[i][to], pre[j - 1]);
      
      // Apply inclusion-exclusion for positions beyond 2
      if (i > 2 && i < n)
        dp[i][to] = Dec(dp[i][to], dp[i - 2][j - 1]);
    }
    
    // Update prefix sums for next iteration
    for (int j = 0; j <= k; ++j)
      pre[j] = Inc(pre[j], dp[i][j]);
  }
  
  // Output result for the last position and full range
  printf("%d\n", dp[n][k]);
}


// https://github.com/VaHiX/CodeForces/