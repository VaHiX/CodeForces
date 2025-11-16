// Problem: CF 779 C - Dishonest Sellers
// https://codeforces.com/contest/779/problem/C

/*
 * Purpose: Solve the Dishonest Sellers problem where Igor needs to buy n items,
 *          purchasing at least k items now to minimize total cost.
 *          The price of each item is a[i] now and b[i] after a week.
 *          Strategy:
 *            - Calculate the difference (a[i] - b[i]) for each item.
 *            - Sort items by this difference in ascending order.
 *            - Buy the first k items now, and the rest after the discount if beneficial.
 *            
 * Algorithm: Greedy approach with sorting
 * Time Complexity: O(n log n) due to sorting
 * Space Complexity: O(n) for storing differences and input arrays
 */

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  std::vector<long> a(n), b(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  for (long p = 0; p < n; p++) {
    scanf("%ld", &b[p]);
  }
  std::vector<std::pair<long, long>> d(n);
  for (long p = 0; p < n; p++) {
    // Store the price difference (a[i] - b[i]) and current price a[i]
    d[p] = std::pair<long, long>(a[p] - b[p], a[p]);
  }
  sort(d.begin(), d.end());
  long long total(0);
  for (long p = 0; p < n; p++) {
    // If we are buying item after discount (p >= k) and it's beneficial to wait (d[p].first > 0)
    // then subtract the price difference from the current price (d[p].second - d[p].first)
    // Otherwise, buy now at current price (d[p].second)
    total += d[p].second - ((p >= k) && (d[p].first > 0)) * d[p].first;
  }
  printf("%lld\n", total);
  return 0;
}


// https://github.com/VaHiX/CodeForces/