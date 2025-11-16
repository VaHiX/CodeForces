// Problem: CF 1373 A - Donut Shops
// https://codeforces.com/contest/1373/problem/A

/*
Code Purpose:
This program determines the number of donuts to buy such that one donut shop is strictly cheaper than the other.
It compares two pricing models:
1. Retail: Each donut costs 'a' dollars.
2. Bulk: Boxes of 'b' donuts cost 'c' dollars each.

The solution calculates:
- The smallest number of donuts where the first shop is cheaper than the second.
- The smallest number of donuts where the second shop is cheaper than the first.

Algorithms/Techniques:
- Direct mathematical comparison to determine break-even points.
- Use of integer arithmetic to avoid floating point errors.
- Efficient computation using basic inequalities.

Time Complexity: O(t), where t is the number of test cases.
Space Complexity: O(1), constant extra space.
*/

#include <cstdio>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll a, b, c;
    scanf("%lld %lld %lld", &a, &b, &c);
    // For first shop to be cheaper: a * x < ceil(x/b) * c
    // We test x = 1 for the first case: a < c
    // If a < c, then 1 donut is cheaper in first shop.
    // Otherwise, it's not possible for any x > 0.
    printf("%lld %lld\n", (a < c ? 1LL : -1LL), (c < b * a ? b : -1LL));
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/