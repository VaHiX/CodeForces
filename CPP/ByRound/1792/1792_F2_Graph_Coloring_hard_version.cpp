// Problem: CF 1792 F2 - Graph Coloring (hard version)
// https://codeforces.com/contest/1792/problem/F2

// This implementation computes a combinatorial sequence (arrays f,g,h)
// using factorials and inverse factorials modulo `mod`.
//
// Notes:
// - `fac` stores factorials, `nfac` stores inverse factorials (modular),
//   and `inv` stores modular inverses of integers.
// - The exact problem this code solves is the CF "hard" variant of a
//   combinatorial counting task (filename indicates 1792_F2 Graph Coloring),
//   but here we focus on documenting what each section does.
// - The program precomputes factorials, then builds sequences f,g,h up to n
//   and finally prints a derived value from f[n].

#include <bits/stdc++.h>
using namespace std;

const int maxn = 50005, mod = 998244353;
// Problem parameters and temporary flags (some may be unused in this snippet)
int n, m, T, ans, flg;

// Precomputed factorials and inverses
int fac[maxn], nfac[maxn], inv[maxn];

// Main DP / combinatorial sequences
long long f[maxn], g[maxn], h[maxn];

// Combination C(a,b) using precomputed factorials (modular arithmetic)
inline int C(int a, int b) {
  return a < b ? 0 : 1ll * fac[a] * nfac[b] % mod * nfac[a - b] % mod;
}
int main() {
  // Precompute factorials, modular inverses and inverse factorials
  fac[0] = fac[1] = nfac[0] = nfac[1] = inv[1] = 1;
  for (int i = 2; i < maxn; i++)
    // Use comma-separated expressions to fill three arrays in one for-loop
    fac[i] = 1ll * fac[i - 1] * i % mod,
    inv[i] = mod - 1ll * (mod / i) * inv[mod % i] % mod,
    nfac[i] = 1ll * nfac[i - 1] * inv[i] % mod;

  // Read input size n and initialize base values for DP arrays
  scanf("%d", &n), f[1] = g[1] = h[1] = 1;
  for (int i = 2; i <= n; i++) {
    // Compute f[i] as convolution-like sum over previous g and h
    // f[i] = sum_{j=1..i-2} g[j] * h[i-j]
    for (int j = 1; j < i - 1; j++) {
      f[i] += g[j] * h[i - j];
      // Periodically reduce modulo to avoid overflow
      if (j % 9 == 0)
        f[i] %= mod;
    }
    f[i] %= mod;

    // The next lines transform f[i] then compute g[i], h[i].
    // Note: original code uses comma operators to assign multiple values
    // in a compact (but slightly confusing) expression; preserve semantics.
    f[i] = (2ll * fac[i - 1] * f[i] + 1ll * (i - 1) * f[i - 1]) % mod,
    g[i] = 1ll * nfac[i] * f[i] % mod;
    // The following line appears to overwrite g[i] with a slightly
    // different expression and also assigns h[i]. We preserve the code
    // exactly as written to avoid changing behavior.
    g[i] = 1ll * nfac[i - 1] * f[i] % mod, h[i] = 1ll * nfac[i] * f[i] % mod;
  }
  // Print the final computed value. The expression (f[n] + f[n] - 2)
  // corresponds to some derived combinatorial formula from the DP.
  printf("%lld\n", (f[n] + f[n] - 2ll + mod) % mod);
  return 0;
}

// https://github.com/VaHiX/CodeForces/