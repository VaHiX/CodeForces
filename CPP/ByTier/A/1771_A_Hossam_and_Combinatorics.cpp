// Problem: CF 1771 A - Hossam and Combinatorics
// https://codeforces.com/contest/1771/problem/A

/*
Problem: A. Hossam and Combinatorics
Algorithms/Techniques: Single pass scan to find min and max values and their counts.
Time Complexity: O(n) per test case
Space Complexity: O(1)

Task: Count pairs (a_i, a_j) such that:
- i != j
- |a_i - a_j| equals the maximum absolute difference in the array.

Approach:
1. For each test case, find:
   - Maximum value 'mx' and its count 'cmx'
   - Minimum value 'mn' and its count 'cmn'
2. If min != max:
   - The maximum difference is (mx - mn)
   - All pairs of elements equal to mx and mn give the maximum difference
   - Count = 2 * cmn * cmx
3. If min == max:
   - All elements are same, so max difference is 0
   - Valid pairs are all pairs (i,j) with i != j
   - Count = n * (n-1)
*/

#include <cstdio>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll mx(0), cmx(0), mn(1e6), cmn(0);
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      if (x > mx) {           // Update maximum and reset count
        mx = x;
        cmx = 1;
      } else if (x == mx) {   // Increment count of maximum
        ++cmx;
      }
      if (x < mn) {           // Update minimum and reset count
        mn = x;
        cmn = 1;
      } else if (x == mn) {   // Increment count of minimum
        ++cmn;
      }
    }
    ll ans = (mn < mx) ? (2 * cmn * cmx) : ((n - 1) * n);  // Calculate result based on min/max comparison
    printf("%lld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/