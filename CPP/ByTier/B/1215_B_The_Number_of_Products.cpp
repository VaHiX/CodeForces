// Problem: CF 1215 B - The Number of Products
// https://codeforces.com/contest/1215/problem/B

#include <cstdio>

typedef long long ll;
int main() {
  ll n;
  scanf("%lld", &n);
  ll fpos(0), fneg(0), spos(0), sneg(0);
  // fpos: number of subsegments ending at current position with positive product
  // fneg: number of subsegments ending at current position with negative product
  // spos: cumulative count of subsegments with positive product
  // sneg: cumulative count of subsegments with negative product
  for (ll p = 0; p < n; p++) {
    ll x;
    scanf("%lld", &x);
    if (x > 0) {
      // If current element is positive:
      // - subsegments ending with positive product remain positive
      // - subsegments ending with negative product become positive (neg * pos = neg)
      ++fpos;
    } else if (x < 0) {
      // If current element is negative:
      // - subsegments ending with positive product become negative
      // - subsegments ending with negative product become positive
      ll tmp = fpos;
      fpos = fneg;
      fneg = 1 + tmp;
    }
    sneg += fneg;
    spos += fpos;
  }
  printf("%lld %lld\n", sneg, spos);
  return 0;
}

/*
Time Complexity: O(n)
Space Complexity: O(1)

Algorithm:
This solution uses a dynamic programming approach where we track:
- fpos: count of subsegments ending at current position with positive product
- fneg: count of subsegments ending at current position with negative product

For each element, we update these counts based on whether the number is positive or negative.
The key insight is that multiplying by a positive number preserves signs,
while multiplying by a negative number flips them.

The cumulative sums (spos and sneg) give us the total number of positive
and negative subsegments respectively.
*/

// https://github.com/VaHiX/codeForces/