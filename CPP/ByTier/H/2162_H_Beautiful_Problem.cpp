// Problem: CF 2162 H - Beautiful Problem
// https://codeforces.com/contest/2162/problem/H

/*
 * Code Purpose: Solve the "Beautiful Problem" where we need to determine for each x from 1 to n,
 * whether there exists a rearrangement of the array such that for all given intervals [l_i, r_i],
 * the condition f(a', x, l_i, r_i) = 1 holds.
 *
 * Algorithm/Techniques:
 * - Dynamic Programming with state tracking
 * - Preprocessing intervals to compute minimum and maximum bounds for each position
 * - Optimization using prefix sums to avoid redundant calculations
 *
 * Time Complexity: O(n^3) per test case
 * Space Complexity: O(n^3) per test case
 */

#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
#define INF (int)1e9

void Solve() {
  int n, m;
  cin >> n >> m;
  vector<int> a(n + 1), f(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    f[a[i]]++; // Count frequency of each element
  }
  vector<int> b(n + 1), c(n + 1); // b[i] = min l such that i is in [l,r] for some interval, c[i] = max r
  for (int i = 1; i <= n; i++) {
    b[i] = c[i] = i;
  }
  for (int i = 1; i <= m; i++) {
    int l, r;
    cin >> l >> r;
    for (int j = l; j <= r; j++) {
      b[j] = min(b[j], l); // Update minimum left bound for position j
      c[j] = max(c[j], r); // Update maximum right bound for position j
    }
  }
  int dp[n + 1][n + 1][2];
  int pref[n + 1][n + 1][2];
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      for (int k = 0; k < 2; k++) {
        dp[i][j][k] = -INF; // Initialize dp values to negative infinity
        pref[i][j][k] = -INF; // Initialize prefix values to negative infinity
      }
    }
  }
  dp[0][0][0] = dp[0][0][1] = 0; // Base case
  pref[0][0][0] = pref[0][0][1] = 0; // Base case for prefix
  for (int i = 1; i <= n; i++) {
    for (int x = 0; x <= n; x++) {
      for (int y = 0; y < 2; y++) {
        for (int z = 0; z < 2; z++) {
          if (y == z) {
            int px = x - (y == 0); // Calculate new accumulated count
            if (px >= 0) {
              dp[i][x][y] = max(dp[i][x][y], pref[i - 1][px][z] + (y == 1)); // Update dp with previous state
            }
          } else {
            int px = x - (y == 0);
            int lim = b[i] - 1; // Limit based on the minimum required left position
            if (px >= 0) {
              dp[i][x][y] = max(dp[i][x][y], pref[lim][px][z] + (y == 1)); // Update dp based on constraint
            }
          }
        }
        pref[i][x][y] = max(pref[i - 1][x][y], dp[i][x][y]); // Update prefix maximum
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    int lower = 0;
    int upper = 0;
    for (int j = 1; j < i; j++)
      lower += f[j]; // Sum frequencies of elements smaller than current x
    for (int j = i + 1; j <= n; j++)
      upper += f[j]; // Sum frequencies of elements larger than current x
    if (pref[n][lower][0] >= upper || pref[n][lower][1] >= upper) {
      cout << "1"; // Valid arrangement exists
    } else {
      cout << "0"; // No valid arrangement
    }
  }
  cout << "\n";
}

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t = 1;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    Solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/