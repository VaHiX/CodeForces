// Problem: CF 1198 A - MP3
// https://codeforces.com/contest/1198/problem/A

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n, b;
  scanf("%ld %ld", &n, &b);
  // Calculate maximum number of bits that can be used (up to 21)
  long bits = 8 * b / n;
  bits = (bits < 21) ? bits : 21;
  // Maximum range of distinct values allowed
  long range = 1 << bits;
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  // Sort array to enable sliding window technique
  sort(a.begin(), a.end());
  long idx(0), diff(0), chg(n + 1);
  for (long p = 0; p < n; p++) {
    // Count number of distinct elements in current window
    if (p == 0 || a[p] > a[p - 1]) {
      ++diff;
    }
    // Shrink window if distinct count exceeds range
    while (diff > range) {
      ++idx;
      if (a[idx] > a[idx - 1]) {
        --diff;
      }
    }
    // Calculate number of changes needed for current window
    long tmp = n - 1 - p + idx;
    chg = (chg < tmp) ? chg : tmp;
  }
  printf("%ld\n", chg);
  return 0;
}
/* 
Flowerbox:
Problem: Sound File Compression with Minimum Changes
Algorithm: Sliding window with two pointers, sorting.
Time Complexity: O(n log n) due to sorting. Sliding window is O(n).
Space Complexity: O(n) for storing the array.
Techniques: Sorting, sliding window, bit manipulation.

The problem requires finding a range [l, r] that minimizes the number of 
elements that must be changed in order to fit the file within a given disk size.
We use binary search or sliding window approach to find optimal range.
*/

// https://github.com/VaHiX/codeForces/