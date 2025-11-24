// Problem: CF 2104 D - Array and GCD
// https://codeforces.com/contest/2104/problem/D

/*
Problem: D. Array and GCD
Purpose: Given an array of integers, find the minimum number of elements to remove such that the remaining elements can form an "ideal" array. An ideal array satisfies:
         1. All elements are at least 2.
         2. For any pair of indices i, j (i != j), GCD(a[i], a[j]) = 1.
         Operations allowed:
         - Pay 1 coin to increase an element by 1.
         - Gain 1 coin to decrease an element by 1.
         Initially have 0 coins.

Algorithms/Techniques:
- Sieve of Eratosthenes to precompute primes up to 7e6
- Prefix sums and binary search optimization on prime sums
- Sorting in descending order for greedy approach

Time Complexity: O(B log log B + n log n + n * sqrt(max(a))) where B = 7e6
Space Complexity: O(B + n)
*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  const ll B = 7e6;
  std::vector<bool> zb(B, 1); // Sieve array for prime checking
  zb[0] = zb[1] = 0;          // 0 and 1 are not primes
  
  // Sieve of Eratosthenes to find all primes up to B
  for (ll p = 2; p * p <= B; p++) {
    if (!zb[p]) { continue; }   // Skip if not prime
    for (ll q = 2 * p; q < B; q += p) {
      zb[q] = 0;                 // Mark multiples as not prime
    }
  }

  std::vector<ll> w(1, 0);     // Prefix sum of primes
  for (ll p = 0; p < B; p++) {
    if (!zb[p]) { continue; }  // Skip non-primes
    w.push_back(w.back() + p); // Cumulative sum of primes
  }

  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> v(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &v[p]);
    }

    // Sort in descending order
    std::sort(v.rbegin(), v.rend());

    // Compute prefix sums of the sorted array
    for (ll p = 1; p < n; p++) {
      v[p] += v[p - 1];
    }

    ll ans(0);
    
    // For each possible number of elements to keep (from n down to 1),
    // check if we can afford to increase elements to make GCD=1.
    for (ll p = 0; p < n; p++) {
      if (v[p] < w[p + 1]) {   // v[p] is prefix sum of array, w[p+1] is sum of first (p+1) primes
        ans = n - p;
        break;
      }
    }

    printf("%lld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/