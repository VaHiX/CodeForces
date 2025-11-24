// Problem: CF 1091 C - New Year and the Sphere Transmission
// https://codeforces.com/contest/1091/problem/C

#include <cstdio>
#include <set>
typedef long long ll;
int main() {
  ll n;
  scanf("%lld", &n);
  std::set<ll> s; // Set to store unique fun values
  for (ll p = 1; p * p <= n; p++) { // Iterate through all divisors up to sqrt(n)
    if (n % p == 0) { // If p is a divisor of n
      ll u = n / p;
      // Calculate fun value for divisor p
      s.insert(n * (p - 1) / 2 + p);
      // If p is not the square root of n, calculate for its complement divisor
      if (p * p != n) {
        s.insert(n * (u - 1) / 2 + u);
      }
    }
  }
  // Print all unique fun values in increasing order
  for (std::set<ll>::iterator it = s.begin(); it != s.end(); it++) {
    printf("%lld ", *it);
  }
  puts("");
  return 0;
}
/*
Flowerbox:
Problem: New Year and the Sphere Transmission
Purpose: Given n people in a circle, find all possible "fun values" (sum of IDs of people who touched the ball) for different valid choices of step size k.
Algorithm:
  - The process forms a cycle with step size k. The ball returns to person 1 after lcm(n, k)/k steps.
  - For fixed k, the set of people who touch the ball corresponds to positions: 1, (1+k)%n, (1+2k)%n, ..., until it hits 1 again.
  - The formula for fun value is derived as: n*(p-1)/2 + p where p is a divisor of n.
  - Enumerate all divisors of n and compute the corresponding fun values.
Time Complexity: O(sqrt(n))
Space Complexity: O(d(n)) where d(n) is the number of divisors of n, which is at most O(n^(1/3)) in worst case.
*/

// https://github.com/VaHiX/codeForces/