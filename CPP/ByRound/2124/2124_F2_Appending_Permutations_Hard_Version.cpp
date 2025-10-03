// Problem: CF 2124 F2 - Appending Permutations (Hard Version)
// https://codeforces.com/contest/2124/problem/F2

/*
F2. Appending Permutations (Hard Version)
time limit per test3 seconds
memory limit per test1024 megabytes

This problem uses dynamic programming with a segment tree-like approach and
precomputed diagonal information to count valid permutations based on allowed
operations and constraints.

The main idea is to compute how many ways we can build up the array step by step
using the given operation while respecting the restrictions. It makes use of:
- Dynamic Programming (DP) arrays: f[] tracks total valid constructions.
- Difference array techniques with segment trees for efficient range updates and
queries in a sparse way.
- Preprocessing diagonals using d[i][j] to detect valid ranges.

Time Complexity: O(n^2 + mn)
Space Complexity: O(n^2)
*/

#include <iostream>

using namespace std;
#define ll long long
const ll N = 5007, MOD = 998244353;
ll T, n, m, f[N], g[N][N];
int d[N][N];
bool ok[N][N];
void add(ll &x, ll y) {
  x += y;
  if (x >= MOD)
    x -= MOD;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> T;
  while (T--) {
    cin >> n >> m;
    f[0] = 1;
    // Initialize all positions as valid
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        ok[i][j] = 1;
    // Mark invalid positions according to restrictions
    for (int x, y, i = 1; i <= m; ++i) {
      cin >> x >> y;
      ok[x][y] = 0;
    }
    // Precompute diagonal lengths
    for (int i = n; i; --i)
      for (int j = n; j; --j)
        d[i][j] = (ok[i][j] ? d[i + 1][j + 1] + 1 : 0);
    // Dynamic programming loop over rows
    for (int i = 1; i <= n; ++i) {
      // Process valid positions in current row
      for (int j = 1; j <= n; ++j)
        if (ok[i][j]) {
          ll tmp = f[i - 1];
          // Adjust tmp based on conditions involving previous states and
          // diagonal data
          if (j > 1 && i >= j && d[i - j + 1][1] >= j - 1)
            add(tmp, MOD - f[i - j]);
          // Use segment tree difference array technique to update ranges
          // efficiently
          ll l = i, r = i + d[i][j];
          add(g[l][j - 1], tmp);
          add(g[r][j - 1], MOD - tmp);
        }
      // Propagate and accumulate values using difference arrays
      for (int j = 0; j <= n; ++j) {
        add(g[i][j], g[i - 1][j]);
        if (d[i + 1][1] >= j && i + j <= n)
          add(f[i + j], g[i][j]);
      }
    }
    // Output result for current test case
    cout << f[n] << '\n';
    // Reset arrays for next test case
    for (int i = 0; i <= n + 1; ++i) {
      f[i] = 0;
      for (int j = 0; j <= n + 1; ++j)
        g[i][j] = d[i][j] = 0;
    }
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/