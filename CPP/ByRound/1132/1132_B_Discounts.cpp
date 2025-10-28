// Problem: CF 1132 B - Discounts
// https://codeforces.com/contest/1132/problem/B

/*
B. Discounts
Algorithms/Techniques: Sorting, Greedy, Prefix Sum

Time Complexity: O(n * log(n) + m)
Space Complexity: O(n + m)

The problem requires finding the minimum cost of buying all chocolate bars
using one of the given coupons optimally. Each coupon allows choosing q_i
bars and paying for only the q_i - 1 most expensive ones (the cheapest is free).
We sort the prices to apply greedy strategy: to minimize total cost, we should
use the coupon on the most expensive bars possible.

The algorithm sorts the price array, then for each coupon:
- Calculates the sum of all bars (total)
- Finds the sum of q_i cheapest bars among the sorted array (to be subtracted)
- Subtracts this from total to get the cost using that coupon
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  long long total(0); // Total cost of all bars
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
    total += a[p]; // accumulate total cost
  }
  long m;
  scanf("%ld", &m);
  std::vector<long> q(m);
  for (long p = 0; p < m; p++) {
    scanf("%ld", &q[p]); // read coupon values
  }
  sort(a.begin(), a.end()); // sort prices to apply greedy strategy
  for (long p = 0; p < m; p++) {
    printf("%lld\n", total - a[n - q[p]]); // calculate min cost using coupon p
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/