// Problem: CF 1216 D - Swords
// https://codeforces.com/contest/1216/problem/D

/*
D. Swords

Purpose:
This program determines the minimum number of people (y) who broke into the theater basement and the number of swords (z) each took,
given the remaining counts of swords of each type.

Approach:
1. The difference between the maximum initial count and each remaining count is calculated.
2. The GCD of these differences gives us the minimum possible number of swords each person took (z).
3. The sum of (max - a[i]) / z gives the minimum number of people (y).

Time Complexity: O(n log(max_value))
Space Complexity: O(n)

Algorithms/Techniques:
- GCD computation using Euclidean algorithm
- Mathematical analysis of differences to find pattern

*/

#include <cstdio>
#include <vector>
typedef long long ll;

// Computes greatest common divisor using Euclidean algorithm
ll gcd(ll x, ll y) { return (x == 0) ? y : gcd(y % x, x); }

int main() {
  ll n;
  scanf("%lld", &n);
  std::vector<ll> a(n);
  ll mx(0);
  
  // Read input and find maximum initial count
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &a[p]);
    mx = (mx > a[p]) ? mx : a[p];
  }
  
  ll z(0);
  
  // Compute GCD of all differences (max - a[i]) to find minimum z
  for (ll p = 0; p < n; p++) {
    z = gcd(z, mx - a[p]);
  }
  
  ll y(0);
  
  // Sum up total people needed by dividing each difference by z
  for (ll p = 0; p < n; p++) {
    y += (mx - a[p]) / z;
  }
  
  printf("%lld %lld\n", y, z);
  return 0;
}


// https://github.com/VaHiX/codeForces/