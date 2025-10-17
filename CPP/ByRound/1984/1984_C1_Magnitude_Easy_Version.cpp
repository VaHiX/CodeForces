// Problem: CF 1984 C1 - Magnitude (Easy Version)
// https://codeforces.com/contest/1984/problem/C1

/*
C1. Magnitude (Easy Version)
Algorithm: Greedy with tracking of prefix sums
Time Complexity: O(n) per test case
Space Complexity: O(1)

The problem involves choosing at each step whether to add a number directly or take the absolute value of the sum.
We maintain two values:
- mn: minimum prefix sum encountered so far
- mx: maximum prefix sum encountered so far

At each step, we update these sums and decide whether taking the absolute value helps maximize the final result.

Key insight:
If at any point the cumulative sum becomes negative, we can choose to take its absolute value to increase the potential maximum.
This greedy approach ensures we always track the maximum possible value of c.
*/

#include <cstdio>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll c(0), mn(0), mx(0);
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      mn += x;       // Update minimum prefix sum
      mx += x;       // Update maximum prefix sum
      if (mn + mx < 0) {  // If the sum of min and max is negative,
        mx = -mn;     // take absolute value to increase potential maximum
      }
    }
    printf("%lld\n", mx);
  }
}


// https://github.com/VaHiX/codeForces/