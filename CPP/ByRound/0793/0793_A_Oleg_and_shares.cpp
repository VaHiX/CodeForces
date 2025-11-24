// Problem: CF 793 A - Oleg and shares
// https://codeforces.com/contest/793/problem/A

/*
 * Problem: Oleg and shares
 * Purpose: Determine the minimum time for all share prices to become equal
 *          by reducing exactly one price by k rubles each second.
 * 
 * Algorithm:
 * - Find the minimum initial price (mn).
 * - For each price, calculate the difference from mn.
 * - If any difference is not divisible by k, it's impossible, return -1.
 * - Otherwise, sum up all (diff / k) to get total seconds needed.
 * 
 * Time Complexity: O(n), where n is the number of prices.
 * Space Complexity: O(n), for storing the prices.
 */

#include <cstdio>
#include <vector>
int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  std::vector<long> a(n);
  long mn(1e9);  // Initialize minimum price to a large value
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
    mn = (mn < a[p]) ? mn : a[p];  // Update minimum price
  }
  long long total(0);  // Total seconds needed
  for (long p = 0; p < n; p++) {
    long diff = a[p] - mn;  // Calculate difference from minimum
    if (diff % k != 0) {  // If difference is not divisible by k, impossible
      total = -1;
      break;
    } else {
      total += (diff / k);  // Add required seconds for this price
    }
  }
  printf("%lld\n", total);
  return 0;
}


// https://github.com/VaHiX/CodeForces/