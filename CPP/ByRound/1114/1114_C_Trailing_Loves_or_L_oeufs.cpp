// Problem: CF 1114 C - Trailing Loves (or L'oeufs?)
// https://codeforces.com/contest/1114/problem/C

/*
C. Trailing Loves (or L'oeufs?)
Algorithm: Find the number of trailing zeros in n! when represented in base b.
Approach:
- Factorize b into prime powers: b = p1^a1 * p2^a2 * ... * pk^ak
- For each prime factor pi with exponent ai, compute how many times pi divides n!
  Using Legendre's formula: count = sum(n/p^i) for i=1 to infinity
- The number of trailing zeros is determined by the minimum of (count/pi / ai) across all prime factors.
Time Complexity: O(sqrt(b) + log(n)) - factorization and Legendre's formula computation.
Space Complexity: O(log(b)) - to store the prime factorization.
*/

#include <cstdio>
#include <vector>
#include <utility>

typedef long long ll;

int main() {
  ll n, b;
  scanf("%lld %lld", &n, &b);
  std::vector<std::pair<ll, ll>> div; // Store prime factors and their exponents
  for (ll p = 2; p * p <= b; p++) { // Factorize b into primes
    if (b % p) {
      continue;
    }
    ll cnt = 0;
    while (b % p == 0) { // Count the power of prime p in b
      b /= p;
      ++cnt;
    }
    div.push_back(std::make_pair(p, cnt)); // Store prime and its count
  }
  if (b > 1) { // If b is still greater than 1, then it's a prime factor
    div.push_back(std::make_pair(b, 1));
  }
  ll res(1e18); // Initialize result to large value
  for (ll p = 0; p < div.size(); p++) {
    ll u = n;
    ll curdiv = div[p].first; // Current prime factor
    ll cnt(0);
    while (u >= curdiv) { // Apply Legendre's formula for count of primes in n!
      cnt += (u / curdiv);
      u /= curdiv;
    }
    cnt /= div[p].second; // Divide by the power of prime in b
    res = (res < cnt) ? res : cnt; // Take minimum across all prime factors
  }
  printf("%lld\n", res);
  return 0;
}


// https://github.com/VaHiX/codeForces/