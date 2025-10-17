// Problem: CF 2030 E - MEXimize the Score
// https://codeforces.com/contest/2030/problem/E

/*
E. MEXimize the Score
Purpose: Compute the sum of scores over all non-empty subsequences of an array,
         where the score of a partition is the sum of MEX values of multisets.
Algorithms/Techniques:
    - Dynamic Programming with inclusion-exclusion
    - Combinatorics (binomial coefficients)
    - Modular exponentiation and inverse elements
Time Complexity: O(N^2) per test case in worst case, but optimized with precomputation.
Space Complexity: O(N) for storing factorials, inverses, and DP arrays.

*/

#include <iostream>

using std::cin;
using std::cout;
constexpr int N = 200005, p = 998244353;
int t, n, a, b[N], fac[N], inv[N], g[N], f[N], s[N], k[N], ans, sum;

// Fast modular exponentiation
inline int qpow(int a, int b, int p, int t = 1) {
  for (; b; b >>= 1, a = 1ll * a * a % p)
    if (b & 1)
      t = 1ll * t * a % p;
  return t;
}

// Compute combination C(n, m) mod p using precomputed factorials and inverse
inline int C(int n, int m, int p) {
  if (n < 0 || m < 0 || n < m)
    return 0;
  return 1ll * fac[n] * inv[m] % p * inv[n - m] % p;
}

signed main() {
  std::ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  // Precompute factorials and powers of 2
  fac[0] = g[0] = 1;
  for (int i = 1; i < N; ++i) {
    fac[i] = 1ll * fac[i - 1] * i % p;
    g[i] = (g[i - 1] << 1) % p;  // g[i] = 2^i mod p
  }

  inv[N - 1] = qpow(fac[N - 1], p - 2, p);  // Modular inverse of fac[N-1]
  for (int i = N - 2; i >= 0; --i)
    inv[i] = inv[i + 1] * (i + 1ll) % p;     // Inv[i] = 1 / i! mod p

  // Process each test case
  for (cin >> t; t--; cout << ans << '\n') {
    cin >> n;
    
    // Clear count array b (b[i] = number of occurrences of value i in current array)
    for (int i = 0; i < n; ++i)
      b[i] = 0;
      
    // Populate frequency count
    for (int i = 1; i <= n; ++i) {
      cin >> a;
      ++b[a];
    }

    ans = 0;
    sum = n - b[0];   // Number of elements that are not 0
    
    // Initial computation for elements with value 0
    for (int i = b[0]; i >= 1; --i) {
      f[i] = C(b[0], i, p);     // f[i] = C(b[0], i)
      s[i] = (f[i] + s[i + 1]) % p;  // Prefix sum of f[i]
      ans = (ans + 1ll * f[i] * g[sum] % p * i % p) % p;  // Add contribution to answer
    }

    // Process values from 1 to n-1 in turn
    for (int i = 1; i < n; ++i) {
      sum -= b[i];
      if (!b[i])
        break;

      int sc = 0;
      // Compute cumulative combinations
      for (int j = b[i]; j >= 1; --j) {
        sc = (sc + 1ll * C(b[i], j, p)) % p;
        k[j] = (1ll * s[j + 1] * C(b[i], j, p) % p + 1ll * f[j] * sc % p) % p;  // Dynamic update
      }

      // Reset previous values for reuse
      for (int j = 1; j <= b[i - 1]; ++j)
        s[j] = f[j] = 0;

      // Update F and S arrays with new computations
      for (int j = b[i]; j >= 1; --j) {
        f[j] = k[j];
        ans = (ans + 1ll * f[j] * g[sum] % p * j % p) % p;
        s[j] = (s[j + 1] + f[j]) % p;
      }
    }

    // Clear arrays for next test case
    for (int i = 1; i <= n; ++i)
      s[i] = f[i] = 0;
  }

  return 0;
}


// https://github.com/VaHiX/codeForces/