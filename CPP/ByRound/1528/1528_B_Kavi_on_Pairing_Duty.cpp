// Problem: CF 1528 B - Kavi on Pairing Duty
// https://codeforces.com/contest/1528/problem/B

// Problem: Count "good" pairings of 2n points on a line such that for any two segments formed by pairs,
// either one lies inside the other or they have the same length.
// Algorithm: Dynamic programming with inclusion-exclusion principle and sieve-like preprocessing.
// Time Complexity: O(n log n)
// Space Complexity: O(n)

#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  const ll MOD = 998244353;
  ll n;
  scanf("%lld", &n);
  std::vector<ll> f(n + 1);
  f[0] = 1;
  // Preprocessing step: for each position p, count how many multiples of p exist up to n
  // This helps determine the structure of valid pairings
  for (ll p = 1; p <= n; p++) {
    for (ll q = 2 * p; q <= n; q += p) {
      ++f[q];
    }
  }
  ll sum(1);
  // Dynamic programming step: calculate number of good pairings
  // f[p] stores the number of good pairings for first p points
  for (ll p = 1; p <= n; p++) {
    f[p] = (f[p] + sum) % MOD;   // Add accumulated sum to current value
    sum = (sum + f[p]) % MOD;    // Update cumulative sum
  }
  printf("%lld\n", f.back());
  return 0;
}


// https://github.com/VaHiX/codeForces/