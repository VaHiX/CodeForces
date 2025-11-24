// Problem: CF 1988 F - Heartbeat
// https://codeforces.com/contest/1988/problem/F

/*
 * Problem: F. Heartbeat
 * Algorithms: Dynamic Programming with precomputed factorials and modular inverses
 * Time Complexity: O(n^3)
 * Space Complexity: O(n^2)
 *
 * The solution computes the sum of costs over all permutations of 1..n,
 * where the cost is defined as a[pm] * b[sm] * c[as], with pm, sm, as being
 * prefix maxima, suffix maxima, and ascents respectively.
 *
 * The approach uses dynamic programming on permutations, tracking:
 * - f[q][j][k]: number of ways to form a permutation with j prefix maxima and k ascents
 * - g[i][k]: sum of a[j+1] contributions for permutations of first i elements with k ascents
 * - h[i][k]: sum of b[j+1] contributions for permutations of first i elements with k ascents
 * 
 * Final computation involves combining these counts with c array coefficients.
 */

#include <stdio.h>
#include <iosfwd>

using namespace std;
const int N = 705, P = 998244353;
int n, a[N], b[N], c[N], f[2][N][N], fac[N], inv[N], g[N][N], h[N][N], s[N][N],
    ans[N];

// Adds y to x modulo P
inline void Add(int &x, int y) {
  if ((x += y) >= P)
    x -= P;
}

int main() {
  scanf("%d", &n);
  // Precompute factorials and modular inverses
  fac[0] = inv[0] = fac[1] = inv[1] = 1;
  for (int i = 2; i <= n; ++i)
    fac[i] = 1ll * fac[i - 1] * i % P,
    inv[i] = 1ll * (P - P / i) * inv[P % i] % P;
  for (int i = 2; i <= n; ++i)
    inv[i] = 1ll * inv[i - 1] * inv[i] % P;

  // Read input arrays
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &b[i]);
  for (int i = 0; i < n; ++i)
    scanf("%d", &c[i]);

  // Initialize base case
  f[1][1][0] = 1, g[0][0] = a[1], h[0][0] = b[1];

  // Dynamic Programming transition
  for (int i = 1, q = 1, p = 0; i <= n; ++i, p ^= 1, q ^= 1)
    for (int j = 1; j <= i; ++j)
      for (int k = 0; k < i; ++k)
        if (f[q][j][k]) {
          int w = f[q][j][k];
          f[q][j][k] = 0;
          // Accumulate prefix maxima contributions
          Add(g[i][k], 1ll * w * a[j + 1] % P);
          // Accumulate suffix maxima contributions
          Add(h[i][i - 1 - k], 1ll * w * b[j + 1] % P);
          // Skip last iteration for final result
          if (i == n)
            continue;
          // Transition: increment prefix maxima and ascent count
          Add(f[p][j + 1][k + 1], w);
          // Transition: keep same prefix maxima but increase ascent
          Add(f[p][j][k + 1], 1ll * w * (i - 1 - k) % P);
          // Transition: keep same prefix maxima, same ascent count
          Add(f[p][j][k], 1ll * w * (k + 1) % P);
        }

  // Normalize g and h by dividing with factorial
  for (int i = 2; i <= n; ++i)
    for (int j = 0; j < i; ++j) {
      g[i][j] = 1ll * g[i][j] * inv[i] % P;
      h[i][j] = 1ll * h[i][j] * inv[i] % P;
    }

  // Combine g, c, and h to build final state s
  for (int i = 1; i <= n; ++i)
    for (int j = 0; !j || j < i - 1; ++j)
      for (int k = 0; !k || k < n - i; ++k)
        Add(s[i - 1][k], 1ll * g[i - 1][j] * c[j + k + (i > 1)] % P);

  // Convolve s with h to get final result in ans
  for (int i = 0; i < n; ++i)
    for (int j = 0; i + j < n; ++j)
      for (int k = 0; !k || k < j; ++k)
        Add(ans[i + j], 1ll * s[i][k] * h[j][k] % P);

  // Output results multiplied by factorial
  for (int i = 0; i < n; ++i)
    printf("%d ", 1ll * fac[i] * ans[i] % P);

  return 0;
}


// https://github.com/VaHiX/CodeForces/