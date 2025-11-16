// Problem: CF 1874 F - Jellyfish and OEIS
// https://codeforces.com/contest/1874/problem/F

/*
 * Problem: Jellyfish and OEIS
 * Algorithm: Dynamic Programming with inclusion-exclusion principle
 * Time Complexity: O(n^4)
 * Space Complexity: O(n^2)
 *
 * The solution uses dynamic programming to count permutations such that
 * no subarray [l, r] forms a permutation of [l, l+1, ..., r].
 * 
 * The key idea is to use inclusion-exclusion principle over all possible
 * intervals [l, r] that could violate the condition.
 * 
 * The array `f[l][r]` stores the number of valid permutations where
 * subarray [l, r] does NOT form a permutation of [l, ..., r].
 * 
 * The variable `g[l][k]` tracks how many ways we can place k elements
 * starting from l such that they do not form a valid range.
 * 
 * The final result is computed based on inclusion-exclusion and stored
 * in f[1][n], with an additional check for the case when a[1] == n.
 */

#include <string.h>
#include <algorithm>
#include <iostream>

using namespace std;
const int N = 205, mod = 1e9 + 7;
int n, a[N];
int f[N][N], g[N][N];
int fac[N];

// Modular addition
int add(int x, int y) { return x + y < mod ? x + y : x + y - mod; }

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  fac[0] = 1;
  for (int i = 1; i <= n; i++) {
    fac[i] = 1ll * fac[i - 1] * i % mod;
    cin >> a[i];
  }
  for (int r = 1; r <= n; r++) {
    memset(g, 0, sizeof g);
    g[r + 1][0] = 1;
    for (int l = r; l; l--) {
      // Iterate over possible end points t of valid ranges
      for (int t = l; t <= min(r, a[l]); t++) {
        // For each valid placement of t, update dp accordingly
        for (int k = t - l + 1; k <= r - l + 1; k++) {
          g[l][k] =
              (g[l][k] + 1ll * g[t + 1][k - (t - l + 1)] * (mod - f[l][t])) %
              mod;
        }
      }
      // Propagate values forward
      for (int k = 0; k <= r - l + 1; k++) {
        g[l][k] = add(g[l][k], g[l + 1][k]);
      }
      // Compute total permutations for interval [l, r]
      for (int j = 0; j <= r - l + 1; j++) {
        f[l][r] = (f[l][r] + 1ll * g[l][j] * fac[r - l + 1 - j]) % mod;
      }
      // Special handling for final condition
      if (a[l] >= r) {
        g[l][r - l + 1] = (g[l][r - l + 1] + mod - f[l][r]) % mod;
      }
    }
  }
  // Output result with check for special case
  cout << f[1][n] * (a[1] != n) << endl;
}


// https://github.com/VaHiX/CodeForces/