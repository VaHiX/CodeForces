// Problem: CF 2096 H - Wonderful XOR Problem
// https://codeforces.com/contest/2096/problem/H

/*
Algorithm: This solution uses a dynamic programming approach on the bits of the numbers,
combined with the Fast Walsh-Hadamard Transform (FWHT) technique to efficiently compute XOR convolution.
The core idea is to process each bit position separately and then combine results using bit manipulation.

Time Complexity: O(n * m * 2^m)
Space Complexity: O(2^m)

Approach:
1. For each bit position p, update the counts of valid sequences that result in certain XOR values.
2. Use bit manipulation and modular arithmetic to perform convolution operations efficiently.
3. Combine the results for all bits to get final answer.

*/

#include <stdio.h>
#include <utility>

using namespace std;
const int MAXN = 262144;
const int mod = 998244353;
const int inv2 = (mod + 1) >> 1;
int f[MAXN], g[MAXN], l[MAXN], r[MAXN];
int F[MAXN];
int bc[MAXN];
int main() {
  int T;
  scanf("%d", &T);
  // Precompute the number of set bits for all numbers up to MAXN
  for (int i = 1; i < MAXN; i++)
    bc[i] = 1 - bc[i & (i - 1)];
  while (T--) {
    int n, m;
    scanf("%d%d", &n, &m);
    int M = (1 << m) - 1;
    f[0] = 1;
    for (int i = 1; i <= M; i++)
      f[i] = 1, g[i] = 1;
#define mul(a, b) 1ll * (a) * (b) % mod
    for (int i = 0; i < n; i++) {
      scanf("%d%d", l + i, r + i);
      l[i]--;
      // Multiply by the number of valid choices for current interval
      f[0] = mul(f[0], r[i] - l[i]);
    }
    // Process each bit position
    for (int p = 0; p < m; p++) {
      for (int i = 0; i < n; i++) {
        // Calculate how many valid XOR values there are for the current bit
        int a = (r[i] >> p & 1) ? (1 << p) - (r[i] & (1 << p) - 1) - 1
                                : (r[i] & (1 << p) - 1) + 1;
        int b = (l[i] >= 0)
                    ? -((l[i] >> p & 1) ? (1 << p) - (l[i] & (1 << p) - 1) - 1
                                        : (l[i] & (1 << p) - 1) + 1)
                    : 0;
        int c = r[i] >> (p + 1);
        int d = (l[i] >= 0) ? l[i] >> (p + 1) : 0;
#define _a(c) ((c) << 1 | 1) << p
        if (c == d)
          // Update f and g based on how many valid entries there are for the current bit
          f[_a(c)] = mul(f[_a(c)], a + b),
          g[_a(c)] = mul(g[_a(c)], (c != 0) ? -(a + b) : (a + b));
        else {
          // Adjust for the case when the current bit contributes in both directions
          f[_a(c ^ d)] = mul(f[_a(c ^ d)], a + b);
          g[_a(c ^ d)] = mul(g[_a(c ^ d)], a - b);
          g[_a(c)] = (mod - g[_a(c)]) % mod;
        }
      }
    }
    // Perform bit-reversal permutation
    for (int k = 0; k <= M; k++)
      if (bc[k & (k - 1)])
        swap(f[k], g[k]);
    // Perform FWHT-like transform in two stages
    for (int i = 0; i < m; i++)
      for (int k = 0; k <= M; k++)
        if ((k & (k - 1)) >> i & 1) {
          int ff = f[k], gg = g[k];
          f[k] = mul(f[k], f[k ^ (1 << i)]);
          g[k] = mul(g[k], g[k ^ (1 << i)]);
          f[k ^ (1 << i)] = mul(f[k ^ (1 << i)], gg);
          g[k ^ (1 << i)] = mul(g[k ^ (1 << i)], ff);
        }
    // Apply XOR transform to get the final f values
    for (int k = 0; k <= M; k++)
      if (bc[k])
        f[k] = (mod - f[k]) % mod;
    for (int i = 0; i < m; i++)
      for (int k = 0; k <= M; k++)
        if (k >> i & 1) {
          int ff = (mod - f[k]) % mod;
          f[k] = (f[k] + f[k ^ (1 << i)]) % mod;
          f[k ^ (1 << i)] = (f[k ^ (1 << i)] + ff) % mod;
        }
    // Compute inverse of 2^m
    int inv2m = 1;
    for (int i = 1; i <= m; i++)
      inv2m = mul(inv2m, inv2);
    int ans = 0, p2 = 1;
    // Compute the final answer using XOR convolution
    for (int x = 0; x <= M; x++)
      ans ^= mul(mul((f[x] + mod) % mod, inv2m), p2), p2 = (p2 + p2) % mod;
    printf("%d\n", ans);
  }
}


// https://github.com/VaHiX/CodeForces/