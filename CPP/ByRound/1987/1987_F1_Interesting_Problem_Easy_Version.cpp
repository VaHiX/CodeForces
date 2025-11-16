// Problem: CF 1987 F1 - Interesting Problem (Easy Version)
// https://codeforces.com/contest/1987/problem/F1

/**
 * Problem: F1. Interesting Problem (Easy Version)
 * 
 * Algorithm/Techniques: Dynamic Programming with Interval DP, greedy approach
 * 
 * Time Complexity: O(n^3) where n <= 100
 * Space Complexity: O(n^2) for DP table + O(n) for auxiliary arrays
 * 
 * Approach:
 * - We model the problem as a game where we greedily remove elements from array
 *   based on valid operations that satisfy condition a[i] = i.
 * - The key insight is to precompute valid intervals and use dynamic programming
 *   to determine optimal removal strategies.
 * - A recursive or interval DP-based approach is used to compute the maximum
 *   number of valid operations possible.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) "MJ >> LAMELO"
#endif

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    a[i]--; // Convert to 0-based indexing
  }
  
  // Precompute valid intervals
  vector<int> b(n);
  for (int i = 0; i < n; i++) {
    // If a[i] > i or difference is odd, this interval cannot be processed in one step
    if (a[i] > i || (i - a[i]) % 2 != 0) {
      b[i] = 1e9; // Mark as invalid
    } else {
      b[i] = i - a[i]; // Compute how many operations needed for this interval
    }
  }
  
  debug(b);
  
  // dp[i][j] stores minimum operations needed to process interval [i, j]
  vector<vector<int>> dp(n, vector<int>(n, 1e9));
  
  // Fill DP table for even-length intervals (only valid operations)
  for (int x = 2; x <= n; x += 2) {
    for (int i = 0, j = x - 1; j < n; i++, j++) {
      // Base case for adjacent elements
      if (j - i == 1 || b[i] >= dp[i + 1][j - 1]) {
        dp[i][j] = b[i];
      }
      
      // Try all possible splits and update result
      for (int m = i + 1; m < j; m += 2) {
        dp[i][j] = min(dp[i][j], max(dp[i][m], dp[m + 1][j] - (m - i + 1)));
      }
    }
  }
  
  debug(dp[0][n - 1]);
  
  // Compute final answer using greedy approach
  vector<int> f(n);
  for (int i = 1; i < n; i++) {
    f[i] = max(f[i], f[i - 1]); // Propagate previous max
    
    for (int j = 0; j < i; j++) {
      int x = (j > 0 ? f[j - 1] : 0);
      if (dp[j][i] <= 2 * x) {
        f[i] = max(f[i], x + (i - j + 1) / 2);
        if (i == 7) {
          debug(j, x + (i - j + 1) / 2);
        }
      }
    }
  }
  
  debug(dp[4][7]);
  debug(f);
  cout << f[n - 1] << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/