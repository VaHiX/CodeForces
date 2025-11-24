// Problem: CF 2151 F - Attraction Theory
// https://codeforces.com/contest/2151/problem/F

/*
F. Attraction Theory
Algorithms/Techniques: Combinatorics, Prefix Sums, Modular Arithmetic, Fast Exponentiation

Time Complexity: O(N^2) per test case due to nested loops over k and x/y combinations.
Space Complexity: O(N) for precomputed factorials, prefix sums, and auxiliary arrays.

*/

#include <stdio.h>
#include <iosfwd>

using namespace std;
const int N = 2e5, mod = 998244353;
int T, n, a[N + 5], sum[N + 5][3], f[N + 5], g[N + 5], ans;

// Fast exponentiation for modular arithmetic
int ksm(int x, int y) {
  int rt = 1;
  while (y) {
    if (y & 1)
      rt = 1ll * rt * x % mod;
    x = 1ll * x * x % mod, y >>= 1;
  }
  return rt;
}

// Calculate combination C(x,y) using precomputed factorials
int C(int x, int y) { return 1ll * f[x] * g[y] % mod * g[x - y] % mod; }

// Query sum of a[i] from index 1 to k-1 and from k+1 to n
int q(int x) {
  if (x == 0)
    return 0;
  return (0ll + sum[n][1] - sum[x - 1][1] - sum[n - x][1] + 2ll * mod) % mod;
}

void work() {
  ans = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  
  // Precompute prefix sums for efficient range queries
  for (int i = 1; i <= n; i++)
    sum[i][0] = (sum[i - 1][0] + a[i]) % mod;
  for (int i = 1; i <= n; i++)
    sum[i][1] = (sum[i - 1][1] + sum[i][0]) % mod;
  
  // Initialize suffix sum from the right side
  sum[n + 1][2] = 0;
  for (int i = n; i >= 1; i--)
    sum[i][2] = (sum[i + 1][2] + a[i]) % mod;

  // Main computation loop over k and x/y combinations
  for (int k = 2; k <= n; k++) {
    for (int x = 0; x <= 1; x++) {
      for (int y = 0; y <= 1; y++) {
        int s = n - k - x - y;
        if (s < 0 || (s & 1))
          continue;
        s >>= 1;

        // Add contribution from C(s + k - 1, k - 1) * q(k)
        ans = (0ll + ans + 1ll * C(s + k - 1, k - 1) * q(k) % mod) % mod;

        // Add contribution from C(s + k - 1, k - 1) * x * sum[n - k + 1][0]
        ans = (0ll + ans +
               1ll * C(s + k - 1, k - 1) * x * sum[n - k + 1][0] % mod) %
              mod;

        // Add contribution from C(s + k - 1, k - 1) * y * sum[k][2]
        ans =
            (0ll + ans + 1ll * C(s + k - 1, k - 1) * y * sum[k][2] % mod) % mod;

        // Add contribution from combination with additional term involving s and inverse of k
        ans = (0ll + ans +
               2ll * C(s + k - 1, k - 1) * s % mod * ksm(k, mod - 2) % mod *
                   q(k) % mod) %
              mod;
      }
    }
  }

  // Final result includes contribution of sum[a] * n
  printf("%d\n", (ans + 1ll * sum[n][0] * n % mod) % mod);
}

int main() {
  f[0] = g[0] = 1;
  for (int i = 1; i <= N; i++)
    f[i] = 1ll * f[i - 1] * i % mod, g[i] = ksm(f[i], mod - 2);
  scanf("%d", &T);
  while (T--)
    work();
}


// https://github.com/VaHiX/CodeForces/