// Problem: CF 1849 F - XOR Partition
// https://codeforces.com/contest/1849/problem/F

// Purpose: This code solves the XOR Partition problem by finding an optimal way to split a set of integers
//          into two subsets such that the minimum XOR value in either subset is maximized.
//          It uses dynamic programming combined with greedy selection and bit manipulation techniques.
//
// Algorithm: Dynamic Programming with greedy optimization
// Time Complexity: O(n * k^2) where n is the number of elements and k is a constant (10).
// Space Complexity: O(n * k) for the DP table and auxiliary arrays.
//
// Techniques:
// - Sorting to group similar values
// - Bit manipulation using XOR operations to compute differences
// - Dynamic Programming with state tracking of partition sizes
// - Greedy traceback to reconstruct the solution

#include <assert.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
const int c = 500005, k = 10;
const long long sok = 1e12;
long long n, dp[c][k], t[c];
vector<pair<int, int>> sz;
bool ans[c];
int main() {
  ios_base::sync_with_stdio(false);
  cin >> n;
  sz.push_back({-1, -1});
  for (int i = 1; i <= n; i++) {
    cin >> t[i];
    sz.push_back({t[i], i}); // Store elements along with their original indices
  }
  if (n == 2) {
    cout << "01\n";
    return 0;
  }
  sort(t + 1, t + n + 1); // Sort the array to simplify the DP transitions
  sort(sz.begin(), sz.end());
  for (int j = 0; j < k; j++) {
    dp[0][j] = sok; // Initialize DP table with large values
  }
  for (int j = 1; j < k; j++) {
    dp[1][j] = sok;
  }
  for (int i = 2; i <= n; i++) {
    for (int j = 1; j < k; j++) {
      int el = i - j;
      if (j > 1) {
        // If j > 1, use previous DP state to avoid local minima
        dp[i][j] = min(dp[i - 1][j - 1], t[i] ^ t[i - 1]);
      } else {
        // For j = 1, try all possible splits to maximize the result
        dp[i][j] = -1; // Initialize with a small value
        for (int s = 1; s < k; s++) {
          int el = i - 1 - s;
          long long val = (el <= 0 ? sok : t[el] ^ t[i]);
          dp[i][j] = max(dp[i][j], min(dp[i - 1][s], val));
        }
      }
      if (el >= 0) {
        // This condition seems unused; can be removed
      }
    }
  }
  int pos = 1;
  for (int j = 1; j < k; j++) {
    // Find the best DP state for final result
    if (dp[n][j] > dp[n][pos]) {
      pos = j;
    }
  }
  long long res = dp[n][pos];
  int el = n - pos, ert = 0;
  for (int i = n; i >= 1; i--) {
    ans[sz[i].second] = ert; // Assign the correct subset to each element
    if (i == el + 1) {
      ert = 1 - ert; // Switch subset
      int opt = -1;
      for (int j = 1; j < k; j++) {
        int x = i, y = i - 1 - j;
        long long val = (y < 0 ? sok : t[x] ^ t[y]);
        // Validate the split based on current best solution
        if (val >= res && dp[i - 1][j] >= res) {
          opt = j;
        }
      }
      assert(opt != -1);
      el = i - 1 - opt; // Update the split point
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << ans[i]; // Output the assignment
  }
  cout << "\n";
  return 0;
}


// https://github.com/VaHiX/CodeForces/