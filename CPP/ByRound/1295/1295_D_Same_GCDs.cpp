// Problem: CF 1295 D - Same GCDs
// https://codeforces.com/contest/1295/problem/D

/*
D. Same GCDs
Algorithm: Uses Euler's totient function to count valid x values such that gcd(a, m) = gcd(a + x, m).
Time Complexity: O(sqrt(m)) per test case
Space Complexity: O(1)

The key insight is that if gcd(a, m) = gcd(a + x, m), then it must be true that 
gcd(a, m) divides x and gcd(a + x, m) = gcd(a, m). This leads to the conclusion:
The number of valid x values is phi(m / gcd(a, m)), where phi is Euler's totient function.

This approach works because we're essentially counting numbers less than m that are
relatively prime to m/gcd(a,m), which can be computed using Euler's totient function.
*/

#include <cstdio>
typedef long long ll;

// Compute greatest common divisor of a and b
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

// Compute Euler's totient function for x
ll phi(ll x) {
  ll cnt(x);  // Start with the total count of numbers from 1 to x
  for (ll p = 2; p * p <= x; p++) {
    if (x % p) {
      continue;
    }
    ll mult(0);
    while (x % p == 0) {
      x /= p;
      ++mult;
    }
    // For each prime factor p, subtract the count of multiples of p
    cnt -= (cnt / p);
  }
  if (x > 1) {
    // If x > 1 after factorization, then it is a prime factor
    cnt -= (cnt / x);
  }
  return cnt;
}

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll a, m;
    scanf("%lld %lld", &a, &m);
    ll ans = phi(m / gcd(a, m));  // Apply the formula to compute result
    printf("%lld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/