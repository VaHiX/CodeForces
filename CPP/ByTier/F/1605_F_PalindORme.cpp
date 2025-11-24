// Problem: CF 1605 F - PalindORme
// https://codeforces.com/contest/1605/problem/F

/*
Problem: Count the number of "good" arrays of length n, consisting of integers in range [0, 2^k - 1], such that elements can be rearranged to form a PalindORme.

A PalindORme array satisfies: OR(a[1], ..., a[i]) = OR(a[n-i+1], ..., a[n]) for all 1 <= i <= n

Algorithms/Techniques: 
- Dynamic Programming with inclusion-exclusion principle
- Fast exponentiation for modular arithmetic
- Combinatorial mathematics (binomial coefficients, factorials)
- Modular inverse using Fermat's little theorem

Time Complexity: O(n^2 * m) where n, m <= 80
Space Complexity: O(n * m) for DP tables

*/

#include <iostream>

using namespace std;
#define int long long
const int N = 82;
const int M = 1e5 + 5;
int n, m, mod;
int qpow(int a, int x) {
  int sum = 1;
  while (x) {
    if (x & 1)
      sum = sum * a % mod;
    a = a * a % mod;
    x >>= 1;
  }
  return sum;
}
int f[N][N], g[N][N];
int pw[M], c[N][N], fac[M], inv[M];
inline int C(int n, int m) {
  if (n < 0 || m < 0 || n < m)
    return 0;
  int res = inv[m];
  for (int i = n; i >= n - m + 1; i--)
    res = res * i % mod;
  return res;
}
void init() {
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      for (int k = 0; k <= j; k++) {
        g[i][j] += ((j - k) & 1 ? -1 : 1) * c[j][k] * C(pw[k] - 1, i) % mod *
                   fac[i] % mod;
      }
      g[i][j] %= mod;
    }
  }
}
void solve() {
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      f[i][j] = qpow(pw[i] - 1, j);
      for (int k = 0; k < i; k++) {
        for (int l = 0; l < j; l++) {
          if (i == n && (n & 1) && i - k == 1)
            continue;
          f[i][j] -= c[i][k] * c[j][l] % mod * f[k][l] % mod * g[i - k][j - l] %
                     mod * pw[(i - k) * l] % mod;
        }
      }
      f[i][j] %= mod;
    }
  }
}
signed main() {
  cin >> n >> m >> mod;
  pw[0] = c[0][0] = fac[0] = inv[0] = 1;
  for (int i = 1; i < M; i++)
    pw[i] = pw[i - 1] * 2 % mod, fac[i] = fac[i - 1] * i % mod,
    inv[i] = qpow(fac[i], mod - 2);
  for (int i = 0; i < N; i++) {
    c[i][0] = 1;
    for (int j = 1; j <= i; j++)
      c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
  }
  init();
  solve();
  int ans = 0;
  for (int i = 0; i <= m; i++)
    ans += c[m][i] * f[n][i] % mod;
  ans = (ans % mod + mod) % mod;
  cout << ans;
  return 0;
}


// https://github.com/VaHiX/CodeForces/