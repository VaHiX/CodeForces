// Problem: CF 2031 A - Penchick and Modern Monument
// https://codeforces.com/contest/2031/problem/A

/*
 * Problem: A. Penchick and Modern Monument
 * Purpose: Given a sequence of pillar heights in non-increasing order,
 *          determine the minimum number of operations to make it non-decreasing.
 *          Each operation allows changing any pillar's height to any positive integer.
 *
 * Algorithm:
 *   - For each test case, count frequency of each height value in the input array.
 *   - Find the maximum frequency of any height (this is the most common height).
 *   - The minimum operations needed = total number of pillars - max frequency.
 *
 * Time Complexity: O(n log n) per test case due to map operations.
 * Space Complexity: O(n) for storing the frequencies in the map.
 */

#include <cstdio>
#include <map>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::map<long, long> m; // Map to store frequency of each height
    long mxcnt(0);         // Maximum frequency of any height
    for (long p = 0; p < n; p++) {
      long h;
      scanf("%ld", &h);
      ++m[h];              // Increment count of this height
      mxcnt = (mxcnt > m[h] ? mxcnt : m[h]); // Update max frequency
    }
    printf("%ld\n", n - mxcnt); // Minimum operations = total - max frequency
  }
}


// https://github.com/VaHiX/codeForces/