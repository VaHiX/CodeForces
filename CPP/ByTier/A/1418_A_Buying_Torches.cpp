// Problem: CF 1418 A - Buying Torches
// https://codeforces.com/contest/1418/problem/A

/*
A. Buying Torches
Algorithms/Techniques: Mathematical optimization, greedy approach with binary search concept.

Time Complexity: O(t), where t is the number of test cases. Each test case is solved in constant time.
Space Complexity: O(1), only using a constant amount of extra space.

The problem involves finding the minimum number of trades to craft k torches,
where each torch requires 1 stick and 1 coal.
We can trade:
1. 1 stick for x sticks (multiplicative gain)
2. y sticks for 1 coal (coalescing gain)

Approach:
- Initially we have 1 stick and need k torches.
- To make k torches, we need k sticks and k coals.
- We start with 1 stick; we can trade to increase our stick count (for coal), or buy coal directly.
- The key idea is to compute how many trades are needed to gather enough sticks for k coals,
  which requires using the first trade option (`x`) to grow our stock of sticks.
- Let `a` be the number of times we use the "buy x sticks for 1 stick" deal to get more sticks.
  Then after `a` such deals, we have `1 + a*(x - 1)` sticks.  
  With this many sticks, we can trade to collect `k` coals (each takes `y` sticks).
  The number of times we need to trade in the second option is:
    ceil((k * y) / (1 + a*(x - 1)))
  We want to minimize total operations:  
    `a` (first trade type) + `ceil((k * y) / (1 + a*(x - 1)))` (second trade type).
- To avoid iterating through all possible values of `a`, we use the given formula:
    `a = (k * (y + 1) - 1 + (x - 2)) / (x - 1)`
    This approximates the optimal value for `a`, then add `k` to get final result (total trades).
*/

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll x, y, k;
    scanf("%lld %lld %lld", &x, &y, &k);
    // Calculate the number of trades needed for sticks and coals
    ll a = (k * (y + 1) - 1 + (x - 2)) / (x - 1); // Optimal first trade count
    printf("%lld\n", a + k); // Total trades = stick trades + coal trades
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/