// Problem: CF 940 A - Points on the line
// https://codeforces.com/contest/940/problem/A

/*
 * Problem: Points on the line
 * Algorithm: Sliding window technique
 * Time Complexity: O(n log n) due to sorting, O(n) for the sliding window pass => Overall O(n log n)
 * Space Complexity: O(1) if we ignore the space for input storage, otherwise O(n) for the vector
 *
 * Approach:
 * 1. Sort the points to simplify finding the maximum distance between any two points.
 * 2. Use a sliding window to find the largest subset of points where the diameter (max - min) is <= d.
 * 3. The minimum number of points to remove is the total number of points minus the size of this largest valid subset.
 */

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n, d;
  scanf("%ld %ld", &n, &d);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  sort(a.begin(), a.end()); // Sort the points to enable sliding window technique
  long left(0), rem(n); // 'left' is the left pointer of sliding window, 'rem' tracks minimum removals
  for (long p = 0; p < n; p++) {
    // Shrink the window from the left until the diameter is within the limit
    while (left <= p && a[p] - a[left] > d) {
      ++left;
    }
    // Calculate number of points to remove if we keep points from 'left' to 'p'
    long cur = n - (p - left + 1);
    rem = (rem < cur) ? rem : cur; // Update minimum removals
  }
  printf("%ld\n", rem);
  return 0;
}


// https://github.com/VaHiX/CodeForces/