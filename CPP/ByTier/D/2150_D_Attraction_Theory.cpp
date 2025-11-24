// Problem: CF 2150 D - Attraction Theory
// https://codeforces.com/contest/2150/problem/D

/*
 * Problem: D. Attraction Theory
 * Algorithms/Techniques: Combinatorics, Prefix Sums, Modular Arithmetic, Fast Exponentiation
 *
 * Time Complexity: O(N^2) per test case due to nested loops and precomputation of factorials.
 * Space Complexity: O(N) for arrays storing prefix sums, factorials and inverse factorials.
 *
 * The problem models a scenario where people move towards attractions on a 1D axis.
 * We compute the sum of all possible scores over all valid configurations using combinatorics
 * and prefix sums to optimize range queries.
 */

#include <stdio.h>
#include <iostream>

using namespace std;
typedef long long LL;
const int N = 200010, mod = 998244353;
int n;
int a[N], p[N], pp[N]; // p: prefix sum of positions, pp: prefix sum of p
int fact[N], infact[N], inv[N]; // precomputed factorials and inverse factorials

// Compute combination C(a, b) = a! / (b! * (a - b)!)
int C(int a, int b) {
  return (LL)fact[a] * infact[b] % mod * infact[a - b] % mod;
}

// Fast modular exponentiation: a^k mod mod
int qmi(int a, int k) {
  int res = 1;
  while (k) {
    if (k & 1)
      res = (LL)res * a % mod;
    a = (LL)a * a % mod;
    k >>= 1;
  }
  return res;
}

int main() {
  int T;
  scanf("%d", &T);
  // Precompute factorials and inverse factorials
  fact[0] = infact[0] = fact[1] = infact[1] = inv[1] = 1;
  for (int i = 2; i < N; i++) {
    fact[i] = (LL)fact[i - 1] * i % mod;
    inv[i] = (LL)(mod - mod / i) * inv[mod % i] % mod;
    infact[i] = (LL)infact[i - 1] * inv[i] % mod;
  }
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]);
    // Compute prefix sums of a
    for (int i = 1; i <= n; i++)
      p[i] = (p[i - 1] + a[i]) % mod;
    // Compute prefix sums of p
    for (int i = 1; i <= n; i++)
      pp[i] = (pp[i - 1] + p[i]) % mod;
    int ans = 0;
    // Initialize answer with contribution from first term: a[i] * n
    for (int i = 1; i <= n; i++)
      ans = (ans + (LL)a[i] * n) % mod;
    // Iterate over all valid k and x,y combinations to compute total contribution
    for (int k = 2; k <= n; k++)
      for (int x = 1; x <= 2; x++)
        for (int y = 1; y <= 2; y++) {
          int S = n - x - y - (k - 2); // Compute S based on problem logic
          if (S < 0 || (S & 1)) // Only process valid S values
            continue;
          S /= 2;
          int E = (LL)S * qmi(k, mod - 2) % mod; // Modular inverse via Fermat's little theorem
          ans = (ans + (LL)C(k + S - 1, k - 1) * (2 * E + 1) % mod *
                           ((LL)pp[n] - pp[k - 1] - pp[n - k] + mod + mod)) %
                mod;
          // Handle special x = 2 case
          if (x == 2)
            ans = (ans + (LL)p[n - k + 1] * C(k + S - 1, k - 1)) % mod;
          // Handle special y = 2 case
          if (y == 2)
            ans =
                (ans + (LL)(p[n] - p[k - 1] + mod) * C(k + S - 1, k - 1)) % mod;
        }
    printf("%d\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/