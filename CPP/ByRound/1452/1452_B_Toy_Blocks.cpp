// Problem: CF 1452 B - Toy Blocks
// https://codeforces.com/contest/1452/problem/B

/*
B. Toy Blocks
Algorithm: Greedy approach with mathematical analysis
Time Complexity: O(n) per test case
Space Complexity: O(1)

The problem asks to find the minimum number of extra blocks needed so that,
regardless of which box is chosen, all remaining boxes can be made equal by moving
blocks from the selected box.

Key insight:
- Let mx = maximum number of blocks in any box.
- Let sum = total number of blocks across all boxes.
- For a target distribution where each of (n - 1) boxes contains 'target' blocks,
  and one box has all remaining blocks, we must ensure that after removing the chosen
  box's blocks from total, the rest can be evenly distributed among (n-1) boxes.
  
We compute initial value as (n-1)*mx - sum.
If this is negative, it means we already have enough to balance; otherwise,
we calculate how many more blocks are needed using modular arithmetic.

The formula res = ((n - 1) - (sum % (n - 1))) % (n - 1) handles the case when
sum is not divisible by (n-1), determining minimum extra blocks required.
*/
#include <cstdio>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll mx(0), sum(0);
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      mx = (mx > x) ? mx : x; // Keep track of maximum block count
      sum += x;              // Accumulate total blocks
    }
    ll res = (n - 1) * mx - sum; // Compute base difference
    if (res < 0) {
      // If negative, adjust to get the minimal required extras using modular math
      res = ((n - 1) - (sum % (n - 1))) % (n - 1);
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/