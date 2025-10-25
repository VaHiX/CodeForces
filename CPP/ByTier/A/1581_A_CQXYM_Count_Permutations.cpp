// Problem: CF 1581 A - CQXYM Count Permutations
// https://codeforces.com/contest/1581/problem/A

#include <cstdio>

typedef long long ll;
int main() {
  const ll MOD = 1e9 + 7; // Modulo value to prevent overflow
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll res(1); // Initialize result to 1
    for (ll p = 3; p <= 2 * n; p++) { // Loop from 3 to 2*n
      res *= p; // Multiply result by p
      res %= MOD; // Apply modulo to keep result within bounds
    }
    printf("%lld\n", res); // Print final result
  }
}
/*
 * Problem: CQXYM Count Permutations
 *
 * Purpose:
 *   Calculate the number of permutations of length 2n such that the number of
 *   indices i where p_i < p_{i+1} is at least n. The result is returned modulo 10^9 + 7.
 *
 * Algorithm:
 *   - For a fixed n, we compute (2n)! / (n! * (n-1)!) which simplifies to
 *     the product of integers from 3 to 2n modulo MOD.
 *   - This can be interpreted as computing a specific combinatorial count
 *     related to valid permutations under given constraints.
 *
 * Time Complexity: O(n) per test case, since we iterate from 3 to 2*n once.
 * Space Complexity: O(1), only using constant extra space.
 */

// https://github.com/VaHiX/codeForces/