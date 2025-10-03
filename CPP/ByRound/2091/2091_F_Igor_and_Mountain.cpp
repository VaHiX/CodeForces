// Problem: CF 2091 F - Igor and Mountain
// https://codeforces.com/contest/2091/problem/F

/*
F. Igor and Mountain
Algorithms/Techniques: Dynamic Programming with Sliding Window Optimization
Time Complexity: O(n * m)
Space Complexity: O(m)

The code computes the number of valid climbing routes from bottom to top,
where each route uses at least one hold per level (1 ≤ holds/level ≤ 2),
and movement between levels is constrained by the Euclidean distance (d).
It uses DP with prefix sums and sliding windows for efficient range queries.
*/

#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;
#define endl '\n'
int pre[2001];   // Prefix sum array for current row
int add[2001];   // Temporary array for storing computed values per row
char s[2003];    // Input characters for current row
const int mod = 998244353;

void solve() {
  int n, m, k;       // k = d (arm span)
  cin >> n >> m >> k;
  int d = sqrt(k * k - 1);  // Distance threshold for valid moves

  // Initialize prefix array
  for (int j = 1; j <= m; j++)
    pre[j] = 0;

  for (int i = 1; i <= n; i++) {
    // Read current row
    for (int j = 1; j <= m; j++)
      cin >> s[j];

    // Process all positions in current row to compute values for 'add'
    if (i > 1)  // Not the first level
      for (int j = 1; j <= m; j++)
        if ((s[j]) == 'X')
          add[j] = pre[min(m, j + d)] - pre[max(0, j - d - 1)] + mod,   // Range query over previous level with window size d
          add[j] %= mod;
        else
          add[j] = 0;

    if (i > 1)  // Clear prefix array for next computation (if not first row)
      for (int j = 1; j <= m; j++)
        pre[j] = 0;

    // Update prefix sums of 'add' for current level
    for (int j = 1; j <= m; j++)
      pre[j] = pre[j - 1] + ((i == 1) ? (s[j] == 'X') : add[j]), pre[j] %= mod;

    // Update 'add' again with another range query but now for the full span k
    for (int j = 1; j <= m; j++)
      if (s[j] == 'X')
        add[j] = pre[min(m, j + k)] - pre[max(0, j - k - 1)] + mod,     // Range query with window size k
        add[j] %= mod;
      else
        add[j] = 0;

    // Final update to prefix array
    for (int j = 1; j <= m; j++)
      pre[j] = pre[j - 1] + add[j], pre[j] %= mod;
  }

  cout << pre[m] << endl;
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/codeForces/