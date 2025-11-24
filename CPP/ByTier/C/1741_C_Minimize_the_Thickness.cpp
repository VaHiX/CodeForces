// Problem: CF 1741 C - Minimize the Thickness
// https://codeforces.com/contest/1741/problem/C

/*
C. Minimize the Thickness
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

Task:
Given a sequence of positive integers, split it into segments such that:
- Each element belongs to exactly one segment.
- All segments have equal sums.
- Minimize the maximum length (thickness) among all segments.

Algorithm:
1. Precompute prefix sums for efficient range sum queries.
2. For each possible segment sum (divisor of total sum), check if it's valid:
   - Use a greedy approach to try forming segments with this sum.
   - Track how many elements are in the current segment and update max length.
3. Among all valid splits, return the minimum thickness.

Time Complexity: O(n^2) per test case
Space Complexity: O(n)

*/
#include <cstdio>
#include <vector>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n), b(n); // b is prefix sum array
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
      b[p] = a[p] + ((p > 0) ? b[p - 1] : 0); // Compute prefix sums
    }
    long res(n); // Initialize result with max possible thickness (whole sequence)
    for (long k = 0; k < n; k++) {
      if (b.back() % b[k]) { // If total sum is not divisible by segment sum, skip
        continue;
      }
      long s(b[k]), t(0), cnt(0), cur(0); // s: target segment sum, t: max segment length, cnt: current segment length, cur: current sum
      bool possible(true);
      for (long p = 0; possible && p < n; p++) {
        cur += a[p]; // Add next element to current segment
        ++cnt; // Increment count of elements in this segment
        if (cur == s) { // If we've reached the target sum
          t = (t > cnt) ? t : cnt; // Update max segment length
          cur = 0; // Reset for next segment
          cnt = 0;
        } else if (cur > s) { // If we exceed the target sum, impossible to split
          possible = false;
        }
      }
      if (possible) {
        res = (res < t) ? res : t; // Update minimum thickness
      }
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/