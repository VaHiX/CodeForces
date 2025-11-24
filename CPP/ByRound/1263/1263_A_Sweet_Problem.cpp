// Problem: CF 1263 A - Sweet Problem
// https://codeforces.com/contest/1263/problem/A

/*
 * Problem: Sweet Problem
 * Algorithm: Greedy approach with sorting and case analysis
 * Time Complexity: O(1) per test case (sorting 3 elements is constant time)
 * Space Complexity: O(1) (only using a fixed-size vector)
 *
 * Description:
 * Tanya eats exactly two candies of different colors each day.
 * We are given the count of red, green, and blue candies.
 * Goal: Find the maximum number of days she can eat candies.
 *
 * Approach:
 * 1. Sort the candy counts in ascending order.
 * 2. If the largest pile is greater than sum of other two,
 *    then the answer is the sum of smaller two piles (as we can only use
 *    each candy once, so max days = sum of smallest two).
 * 3. Otherwise, it's possible to use all candies optimally:
 *    total / 2 gives the maximum number of days.
 */

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    std::vector<long> a(3);           // Store the three candy counts
    for (long p = 0; p < 3; p++) {    // Read r, g, b
      scanf("%ld", &a[p]);
    }
    sort(a.begin(), a.end());         // Sort to get min, mid, max in a[0], a[1], a[2]
    long ans(0);
    if (a[2] > a[0] + a[1]) {         // If largest pile > sum of others
      ans = a[0] + a[1];              // Can only consume min two piles
    } else {
      ans = (a[0] + a[1] + a[2]) / 2; // Else all candies can be consumed optimally
    }
    printf("%ld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/