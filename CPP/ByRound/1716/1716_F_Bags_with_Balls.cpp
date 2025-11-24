// Problem: CF 1716 F - Bags with Balls
// https://codeforces.com/contest/1716/problem/F

/*
 * Problem: F. Bags with Balls
 * 
 * Purpose: Calculate the sum of F^k over all possible ways to take one ball from each of n bags,
 * where F is the number of odd-numbered balls selected. Each bag has m balls numbered from 1 to m.
 * 
 * Techniques:
 * - Stirling numbers of the second kind for computing sums of powers
 * - Modular exponentiation and inverse for modular arithmetic
 * - Preprocessing of Stirling numbers for efficiency
 * 
 * Time Complexity: O(k^2 + t * k)
 * Space Complexity: O(k^2)
 * 
 * Algorithm:
 * - Precompute Stirling numbers of the second kind up to k
 * - For each test case, compute the result using inclusion-exclusion principle
 *   combined with Stirling numbers and modular arithmetic
 */

#include <stdio.h>
#include <algorithm>

using namespace std;
#define A 2020
#define b long long
#define MOD 998244353
b t, n, m, k, s[A][A];
b qow(b x, b y) {
  // Fast exponentiation with modulo
  return y ? (y & 1 ? x * qow(x, y - 1) % MOD : qow(x * x % MOD, y / 2)) : 1;
}
int main() {
  // Precompute Stirling numbers of the second kind
  s[1][1] = 1;
  for (b i = 2; i < A; i++)
    for (b j = 1; j <= i; j++)
      s[i][j] = (s[i - 1][j - 1] + j * s[i - 1][j]) % MOD;
  
  scanf("%lld", &t);
  while (t--) {
    scanf("%lld%lld%lld", &n, &m, &k);
    b a = 0, x = m - m / 2, inv = qow(m, MOD - 2);
    // Compute sum of F^k using Stirling numbers
    for (b i = 1, K = x * qow(m, n - 1) % MOD * n % MOD; i <= min(n, k);
         i++, K = K * x % MOD * inv % MOD * (n - i + 1) % MOD)
      a = (a + s[k][i] * K) % MOD;
    printf("%lld\n", a);
  }
}


// https://github.com/VaHiX/CodeForces/