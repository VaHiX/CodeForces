// Problem: CF 1832 C - Contrast Value
// https://codeforces.com/contest/1832/problem/C

/*
C. Contrast Value

Purpose:
Given an array of integers, construct the shortest subsequence such that its contrast (sum of absolute differences between consecutive elements) equals the contrast of the original array.

Algorithm:
1. Remove consecutive duplicate elements from input array to get a simplified version.
2. Count "peaks" and "valleys" in the simplified array — these are points where local maxima or minima occur.
3. The result is the count of such extrema plus 1 (if the array has more than one element), since we must keep at least the first and last elements to maintain contrast.

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the simplified array

Techniques:
- Two-pointer approach with deduplication
- Peak/valley counting in a sequence
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a;  // Simplified array without consecutive duplicates
    long prev(-1);        // Previous element in input to detect duplicates
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x == prev) {    // Skip if current element is same as previous
        continue;
      }
      a.push_back(x);     // Add non-duplicate to simplified array
      prev = x;           // Update previous
    }
    long cnt(0);          // Count of peaks and valleys
    for (long p = 1; p + 1 < a.size(); p++) {
      // Check for peak or valley at position p
      cnt += ((a[p - 1] < a[p] && a[p] > a[p + 1]) ||
              (a[p - 1] > a[p] && a[p] < a[p + 1]));
    }
    // Add 1 for minimum element if array has more than one element
    printf("%ld\n", cnt + 1 + (a.size() > 1));
  }
}


// https://github.com/VaHiX/codeForces/