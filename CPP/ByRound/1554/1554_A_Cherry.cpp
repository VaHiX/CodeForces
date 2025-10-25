// Problem: CF 1554 A - Cherry
// https://codeforces.com/contest/1554/problem/A

/*
 * Problem: Cherry
 * Description: Given an array of integers, find the maximum value of 
 *              max(a_l, ..., a_r) * min(a_l, ..., a_r) over all pairs (l, r)
 *              where 1 <= l < r <= n.
 * 
 * Algorithms/Techniques: 
 *   - Sliding window approach with tracking previous element
 *   - For each element, compute product of current and previous element,
 *     keeping track of maximum such product encountered.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll prev(0), res(0);
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      ll prod = x * prev;         // Compute product of current and previous element
      res = (res > prod) ? res : prod;  // Update maximum product
      prev = x;                   // Store current element for next iteration
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/