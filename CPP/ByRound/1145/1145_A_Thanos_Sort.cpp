// Problem: CF 1145 A - Thanos Sort
// https://codeforces.com/contest/1145/problem/A

#include <cstdio>
#include <vector>
/*
 * Thanos Sort Algorithm
 *
 * Purpose: Given an array, find the maximum length of a non-decreasing subsequence
 *          that can be obtained by recursively removing either the first half or 
 *          the second half of the array until it is sorted.
 *
 * Approach:
 * - Recursively divide the array into two halves.
 * - If the current subarray is already sorted, return its length.
 * - Otherwise, compute the maximum possible sorted subsequence from each half
 *   and return the larger value.
 *
 * Time Complexity: O(n log n)
 * Space Complexity: O(log n) due to recursion stack depth (log n levels).
 */
long getThanosLength(const std::vector<long> &a, long start, long stop) {
  if (stop <= start + 1) {
    return stop - start;
  }
  bool sorted(true);
  for (long p = start + 1; p < stop; p++) {
    if (a[p - 1] > a[p]) {
      sorted = false;
      break;
    }
  }
  if (sorted) {
    return (stop - start);
  }
  long left = getThanosLength(a, start, (start + stop) / 2); // Recursively process left half
  long right = getThanosLength(a, (start + stop) / 2, stop); // Recursively process right half
  return (left > right) ? left : right;                      // Return maximum of both halves
}
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  long ans = getThanosLength(a, 0, n);
  printf("%ld\n", ans);
  return 0;
}

// https://github.com/VaHiX/codeForces/