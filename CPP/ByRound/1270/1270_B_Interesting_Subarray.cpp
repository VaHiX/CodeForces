// Problem: CF 1270 B - Interesting Subarray
// https://codeforces.com/contest/1270/problem/B

#include <cstdio>
// Problem: Find an interesting subarray in the given array.
// An array is interesting if max(a) - min(a) >= length of array.
// Algorithm: 
// - For each array, scan from left to right to find any two adjacent elements 
//   whose difference is greater than 1. If found, then we can form an interesting 
//   subarray of length 2 (since |max - min| >= 2, and length is 2).
// - Time Complexity: O(n) per test case, O(n) overall
// - Space Complexity: O(1)

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long pos(0), prev(-1);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (pos) {
        // Skip further processing if we have already found a valid subarray
        continue;
      }
      if ((prev >= 0) && ((x > prev + 1) || (x < prev - 1))) {
        // If difference between current and previous element is > 1,
        // we can create an interesting subarray of size 2
        pos = p;
      }
      prev = x;
    }
    puts(pos ? "YES" : "NO");
    if (pos) {
      // Output the indices (1-based) of the subarray
      printf("%ld %ld\n", pos, pos + 1);
    }
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/