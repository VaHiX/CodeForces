// Problem: CF 2122 G - Tree Parking
// https://codeforces.com/contest/2122/problem/G

/*
G. Tree Parking
Purpose: Count the number of valid pairs of sequences (l, r) for all labeled trees with n vertices and k leaves,
such that l[i] < r[i], and their concatenation is a permutation of 1...2n, and the tree is valid.
Algorithms/Techniques:
- Precomputed factorials and inverse factorials for combinatorial calculations
- Fast exponentiation for modular arithmetic
- Modular arithmetic with precomputed modular inverses
Time Complexity: O(N) per test case where N = 2 * 10^5, due to precomputation and fast operations
Space Complexity: O(N), for storing factorial and inverse arrays
*/

#include <stdio.h>
#include <iosfwd>

#define N 200005
#define mod 998244353
typedef long long ll;
using namespace std;

ll ft[N], ftv[N], inv[N]; // Precomputed factorials, inverse factorials, and modular inverses

// Computes combination C(n, m) = n! / (m! * (n - m)!)
ll C(int n, int m) { return ft[n] * ftv[m] % mod * ftv[n - m] % mod; }

// Fast exponentiation: computes a^b mod mod
ll qpow(ll a, int b) {
  ll ans = 1;
  while (b) {
    if (b & 1)
      ans = ans * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return ans;
}

int main() {
  ll ans;
  int i, k, T, n;

  // Precompute factorials and inverse factorials
  ft[0] = ftv[0] = 1;
  for (i = 1; i < N; ++i) {
    if (i == 1)
      inv[i] = 1;         // Modular inverse of 1 is 1
    else
      inv[i] = (mod - mod / i) * inv[mod % i] % mod; // Compute modular inverse using extended Euclidean
    ftv[i] = ftv[i - 1] * inv[i] % mod;       // Inverse factorial
    ft[i] = ft[i - 1] * i % mod;              // Factorial
  }

  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &k);
    ans = 0;
    --n;
    --k;

    // Compute alternating sum using inclusion-exclusion principle
    for (i = 0; i <= n - k; ++i) {
      if ((n + k + i) & 1)
        (ans -= qpow(i, n) * C(n + 1, i + k + 1)) %= mod;
      else
        (ans += qpow(i, n) * C(n + 1, i + k + 1)) %= mod;
    }

    ++n;
    ++k;

    // Multiply with factorials and inverses to finalize result
    for (i = 1; i <= n * 2 - 1; ++i)
      ans = ans * i % mod;
    for (i = 1; i <= n - 1; ++i)
      ans = ans * ((mod + 1) / 2) % mod;

    printf("%lld\n", (ans + mod) % mod);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/