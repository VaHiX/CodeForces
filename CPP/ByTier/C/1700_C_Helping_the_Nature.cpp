// Problem: CF 1700 C - Helping the Nature
// https://codeforces.com/contest/1700/problem/C

/*
C. Helping the Nature
Algorithm: Greedy with prefix/suffix processing
Time Complexity: O(n) per test case
Space Complexity: O(1)

The problem involves making all elements of an array zero using three types of operations:
1. Decrease first i trees by 1 (prefix operation)
2. Decrease last i trees by 1 (suffix operation)
3. Increase all trees by 1 (global operation)

This is solved greedily by processing each element from left to right.
We keep track of the "excess" moisture that needs to be handled.
When we encounter a negative value, it means we need to increase the moisture for 
the current and previous elements; this is done using global increases.

The total operations is computed as:
- The sum of absolute differences between consecutive elements (to handle transitions)
- Plus the final "excess" (global operations needed)

Key insight: We process the array from left to right and compute how much excess moisture
needs to be removed with prefix/suffix operations. Global increases (operation 3) are 
used to counteract negative values during processing.
*/

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll prev;
    scanf("%lld", &prev);
    ll sp(prev), ans(0);  // sp tracks the "excess" or total moisture that must be reduced
    for (ll p = 1; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      ll diff = x - prev;         // difference between consecutive elements
      ans += (diff > 0 ? diff : -diff);  // add operations needed to balance this difference
      if (diff < 0) {             // if we go down, we need more global increases
        sp += diff;               // update the "excess" (will be negative)
      }
      prev = x;
    }
    ans += (sp > 0 ? sp : -sp);   // add remaining "excess" operations needed
    printf("%lld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/