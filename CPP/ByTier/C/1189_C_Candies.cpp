// Problem: CF 1189 C - Candies!
// https://codeforces.com/contest/1189/problem/C

/*
C. Candies!
Algorithm: Binary Indexed Tree / Prefix Sum with Range Query
Time Complexity: O(n + q)
Space Complexity: O(n)

This code implements a solution for computing the number of candies obtained 
from a sequence of digits using a specific operation repeatedly applied to pairs 
of adjacent elements. The key idea is to precompute prefix sums and use them to 
answer range queries quickly.

The core concept involves:
1. Preprocessing input array into prefix sums (b[])
2. For each query, compute the number of candies in a subarray [l, r]
   by calculating how many times pairs sum to at least 10 during all operations.

This allows us to efficiently process up to 10^5 queries on arrays of size up to 10^5.
*/
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll n;
  scanf("%lld", &n);
  std::vector<ll> a(n + 1), b(n + 1); // a stores input, b stores prefix sums
  for (ll p = 1; p <= n; p++) {
    scanf("%lld", &a[p]);
    b[p] = b[p - 1] + a[p]; // Build prefix sum array
  }
  ll q;
  scanf("%lld", &q);
  while (q--) {
    ll l, r;
    scanf("%lld %lld", &l, &r);
    printf("%lld\n", (b[r] - b[l - 1]) / 10); // Sum of subarray divided by 10 gives candy count
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/