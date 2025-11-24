// Problem: CF 1922 F - Replace on Segment
// https://codeforces.com/contest/1922/problem/F

/*
Algorithm: Dynamic Programming with Memoization
Time Complexity: O(n^2 * x^2 * log n)
Space Complexity: O(n^2 * x)

This problem is about minimizing the number of operations to make all elements in an array equal,
where each operation replaces a subsegment with a value not present in that subsegment.
The solution uses a recursive approach with dynamic programming states:
- dp[i][v] represents the maximum end position reachable starting from index i with value v.
- g[i][v] represents the second maximum end position in similar fashion.
The algorithm builds up the solution by trying all possible numbers of operations from 1 to n,
and updates the DP states accordingly.
*/

#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

using i64 = long long;
void solve() {
  int n, x;
  std::cin >> n >> x;
  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
    a[i]--;  // Convert to 0-indexed
  }
  // dp[operation_count][index][value] = max end position
  std::vector dp(1, std::vector(n + 1, std::vector<int>(x)));
  std::vector g(1, std::vector(n + 1, std::vector<int>(x)));
  int ans = 0;
  // Initialize base case (0 operations): each position can only reach itself
  for (int i = 0; i <= n; i++) {
    dp[0][i].assign(x, i);
    g[0][i].assign(x, i);
  }
  // Precompute the initial dp values from right to left
  for (int i = n - 1; i >= 0; i--) {
    dp[0][i][a[i]] = dp[0][i + 1][a[i]];  // If we use a[i] in this segment, we can only go to the next position
    for (int j = 0; j < x; j++) {
      if (j != a[i]) {
        g[0][i][j] = g[0][i + 1][j];  // Otherwise, carry forward the value from the next position
      }
    }
  }
  // Now iterate through possible number of operations
  while (*std::max_element(dp[ans][0].begin(), dp[ans][0].end()) < n) {
    ans++;  // Increment number of operations
    dp.emplace_back(n + 1, std::vector<int>(x));  // Add new layer for this operation count
    g.emplace_back(n + 1, std::vector<int>(x));   // Add new layer for g too
    for (int i = n; i >= 0; i--) {  // For each index from right to left
      for (int v = 0; v < x; v++) {  // For each value from 0 to x-1
        // Take the maximum from previous state
        dp[ans][i][v] = std::max(dp[ans][i][v], g[ans - 1][i][v]);
        // Try all possible previous operations to find better solutions
        for (int c = 0; c <= ans; c++) {
          dp[ans][i][v] = std::max(dp[ans][i][v], dp[ans - c][dp[c][i][v]][v]);
        }
      }
      // Update g based on dp values
      for (int c = 0; c <= ans; c++) {
        std::array<int, 2> val{}; // Holds top two values
        for (int v = 0; v < x; v++) {
          int res = dp[c][i][v];
          if (res > val[0]) {
            val[1] = val[0];
            val[0] = res;
          } else if (res > val[1]) {
            val[1] = res;
          }
        }
        for (int v = 0; v < x; v++) {
          int res = val[dp[c][i][v] == val[0]];
          g[ans][i][v] = std::max(g[ans][i][v], g[ans - c][res][v]);
        }
      }
    }
  }
  std::cout << ans << "\n";
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t;
  std::cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/