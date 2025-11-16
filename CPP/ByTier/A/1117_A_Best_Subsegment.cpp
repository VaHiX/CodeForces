// Problem: CF 1117 A - Best Subsegment
// https://codeforces.com/contest/1117/problem/A

/*
 * Problem: A. Best Subsegment
 * Purpose: Find the length of the longest subsegment with maximum arithmetic mean.
 * Algorithm: Single pass through the array to track the current maximum value and 
 *            the length of the longest sequence of this maximum value.
 * Time Complexity: O(n) - single loop over n elements.
 * Space Complexity: O(1) - only using a constant amount of extra space.
 */

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long mx(-1), len(0), cnt(0);  // mx: maximum value found so far, len: max length of subsegment with mx, cnt: current count of consecutive mx values
  for (long p = 0; p < n; p++) {
    long a;
    scanf("%ld", &a);
    if (a > mx) {             // Found a new maximum value
      mx = a;
      len = cnt = 1;          // Reset counters since we start a new potential longest sequence
    } else if (a == mx) {     // Current element equals the maximum
      ++cnt;                  // Increment current count
      len = (cnt > len) ? cnt : len;  // Update max length if needed
    } else {                  // Current element is less than maximum
      cnt = 0;                // Reset current count
    }
  }
  printf("%ld\n", len);
  return 0;
}


// https://github.com/VaHiX/codeForces/