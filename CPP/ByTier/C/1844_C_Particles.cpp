// Problem: CF 1844 C - Particles
// https://codeforces.com/contest/1844/problem/C

/*
C. Particles
Algorithm: Greedy + Dynamic Programming approach
Time Complexity: O(n) per test case
Space Complexity: O(n) for the input vector

The problem involves combining adjacent particles to maximize the final charge.
The key insight is that we want to pick elements such that their sum is maximized,
but we are constrained by alternating positions. The core idea is to split all non-negative numbers
into two groups based on their index parity (even/odd), and select the group with higher sum.

This greedy approach works because:
- All negative numbers can be removed without affecting the final result.
- We only care about maximizing the sum of selected elements in alternating positions.
*/

#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    bool allneg(true); // Flag to check if all numbers are negative
    ll mx(-1e9 - 7);   // Track maximum among negative numbers
    std::vector<ll> v(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &v[p]);
      if (v[p] > 0) {
        allneg = false; // At least one positive number exists
      }
      if (allneg) {
        mx = (mx > v[p] ? mx : v[p]); // Update max negative value
      }
    }
    if (allneg) {
      printf("%lld\n", mx); // If all numbers are negative, return maximum one
      continue;
    }
    ll z(0), a(0); // z: sum of even-indexed positive elements; a: sum of odd-indexed positive elements
    for (long p = 0; p < n; p++) {
      if (v[p] < 0) {
        continue; // Skip negative numbers
      }
      if (p % 2) { // Odd index
        a += v[p];
      } else {     // Even index
        z += v[p];
      }
    }
    printf("%lld\n", (a > z) ? a : z); // Output larger sum of the two groups
  }
}


// https://github.com/VaHiX/codeForces/