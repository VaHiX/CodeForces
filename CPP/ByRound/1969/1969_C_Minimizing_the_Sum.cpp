// Problem: CF 1969 C - Minimizing the Sum
// https://codeforces.com/contest/1969/problem/C

/*
Algorithm/Technique: Dynamic Programming with Sliding Window Optimization
Time Complexity: O(n * k), where n is the length of the array and k is the maximum number of operations
Space Complexity: O(n * k), for the dp table storing intermediate results

This code solves the problem of minimizing the sum of an array after performing at most k operations,
where each operation allows replacing an element with one of its neighbors' values.
The approach uses dynamic programming with precomputed minimum values in sliding windows
to efficiently compute the minimal possible sum.
*/

#include <algorithm>
#include <iostream>

using namespace std;
using ll = long long;
const int N = 300005;
int n, k;
int a[N];
ll dp[N][11]; // dp[i][j] represents the minimum sum up to index i with exactly j operations

void solve() {
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i < n; i++) {
    if (i == 0) {
      // Base case: only one element, no operations needed
      for (int j = 0; j <= k; j++) {
        dp[i][j] = a[i];
      }
    } else {
      // Initialize dp[i][j] with the case where we don't perform any operation
      for (int j = 0; j <= k; j++) {
        dp[i][j] = dp[i - 1][j] + a[i];
      }
      // Determine the starting index for the sliding window
      int e = max(0, i - k);
      int min_val = a[i];
      // Process elements from right to left in the sliding window
      for (int j = i - 1; j >= e; j--) {
        if (a[j] < min_val)
          min_val = a[j];
        // If we are at the start of a subarray
        if (j == 0) {
          for (int p = i - j; p <= k; p++) {
            // Calculate the cost for making all elements from j to i equal to min_val
            dp[i][p] = (ll)min_val * (i - j + 1);
          }
        } else {
          // For other positions, calculate cost including previous state
          for (int p = i - j; p <= k; p++) {
            dp[i][p] =
                min(dp[i][p], (ll)min_val * (i - j + 1) + dp[j - 1][p - i + j]);
          }
        }
      }
    }
  }
  cout << dp[n - 1][k] << endl;
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  int yt = 1;
  cin >> yt;
  while (yt--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/