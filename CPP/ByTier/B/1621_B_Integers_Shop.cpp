// Problem: CF 1621 B - Integers Shop
// https://codeforces.com/contest/1621/problem/B

/*
B. Integers Shop
Algorithms/Techniques: Greedy with prefix processing
Time Complexity: O(n log n) per test case due to sorting and linear scan
Space Complexity: O(1) extra space (excluding input)

The problem involves selecting segments from a shop to maximize the number of integers obtained,
which includes both bought segments and "gift" integers that lie between two bought segments.
We process each prefix of segments and compute the minimum cost to obtain all integers up to that point.

For each new segment added, we maintain:
- left: smallest left endpoint so far
- lc: minimum cost to cover leftmost point
- right: largest right endpoint so far  
- rc: minimum cost to cover rightmost point
- single: maximum length of a single segment
- sc: minimum cost among segments with maximum length
- res: minimum cost to cover all integers in current prefix

Key insights:
- A greedy approach works by keeping track of minimum cost to cover left and right endpoints.
- Additional coverage from the longest segment (if it spans full range) is considered as a "gift".
*/

#include <cstdio>
typedef long long ll;
int main() {
  const ll MXC = 1e10;
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll left(1e9 + 7), lc(0), right(-1e9 - 7), rc(0), single(0), sc(0), res(0);
    for (ll p = 0; p < n; p++) {
      ll x(0), y(0), z(0);
      scanf("%lld %lld %lld", &x, &y, &z);
      if (x < left) {
        left = x;
        lc = MXC; // Reset cost for new minimum left
      }
      if (x == left) {
        lc = lc < z ? lc : z; // Update min cost to cover leftmost point
      }
      if (right < y) {
        right = y, rc = MXC; // Reset cost for new maximum right
      }
      if (right == y) {
        rc = (rc < z ? rc : z); // Update min cost to cover rightmost point
      }
      if (single < y - x + 1) {
        single = y - x + 1, sc = MXC; // Reset cost for new max length segment
      }
      if (single == y - x + 1) {
        sc = (sc < z ? sc : z); // Update min cost for longest segment
      }
      ll res = lc + rc; // Base cost to cover left and right endpoints
      if (single == right - left + 1) {
        res = (res < sc ? res : sc); // Consider using a single max-length segment instead
      }
      printf("%lld\n", res);
    }
  }
}


// https://github.com/VaHiX/codeForces/