// Problem: CF 1705 A - Mark the Photographer
// https://codeforces.com/contest/1705/problem/A

/*
 * Problem: A. Mark the Photographer
 * Purpose: Determine if 2n people can be arranged into two rows of n each such that
 *          each person in the back row is at least x units taller than the corresponding
 *          person in the front row.
 *
 * Algorithm:
 *   - Sort all heights in ascending order.
 *   - Try to pair the smallest n heights with the next n heights.
 *   - For each pair (front, back), check if back_height >= front_height + x.
 *   - If any pair fails this condition, it's impossible.
 *
 * Time Complexity: O(n log n) per test case due to sorting.
 * Space Complexity: O(n) for storing the heights vector.
 */

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x;
    scanf("%ld %ld", &n, &x);
    std::vector<long> h(2 * n); // Store all 2n heights
    for (long p = 0; p < 2 * n; p++) {
      scanf("%ld", &h[p]);
    }
    sort(h.begin(), h.end()); // Sort heights in ascending order
    bool possible(true);
    for (long p = 0; possible && p < n; p++) {
      // Check if the person in back row (at index p + n) is tall enough
      // compared to the person in front row (at index p)
      if (h[p + n] < h[p] + x) {
        possible = false;
      }
    }
    puts(possible ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/