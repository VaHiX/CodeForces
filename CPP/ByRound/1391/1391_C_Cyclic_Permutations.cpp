// Problem: CF 1391 C - Cyclic Permutations 
// https://codeforces.com/contest/1391/problem/C

// C. Cyclic Permutations
// Purpose: Calculate the number of cyclic permutations of length n modulo 10^9+7.
// Algorithm: 
//   - Total permutations = n!
//   - Non-cyclic permutations = 2^(n-1) (these are the permutations that form a forest of trees)
//   - Cyclic permutations = Total - Non-cyclic = n! - 2^(n-1)
// Time Complexity: O(n) - linear traversal for factorial and power calculations
// Space Complexity: O(1) - only using constant extra space

#include <cstdio>
typedef long long ll;

int main() {
  const ll MOD = 1e9 + 7;
  ll n;
  scanf("%lld", &n);
  
  // Compute n! mod MOD
  ll f(1);
  for (ll p = 1; p <= n; p++) {
    f *= p;
    f %= MOD;
  }
  
  // Compute 2^(n-1) mod MOD
  ll w(1);
  for (ll p = 1; p < n; p++) {
    w *= 2;
    w %= MOD;
  }
  
  // Result = (3 * MOD + f - w) % MOD to handle negative result cases properly
  ll res = (3 * MOD + f - w) % MOD;
  printf("%lld\n", res);
  return 0;
}


// https://github.com/VaHiX/codeForces/