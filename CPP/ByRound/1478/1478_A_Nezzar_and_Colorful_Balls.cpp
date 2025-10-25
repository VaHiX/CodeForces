// Problem: CF 1478 A - Nezzar and Colorful Balls
// https://codeforces.com/contest/1478/problem/A

/*
 * Problem: A. Nezzar and Colorful Balls
 *
 * Purpose: Determine the minimum number of colors needed to color a sequence of balls
 *          such that each color forms a strictly increasing subsequence when only those
 *          colored balls are considered.
 *
 * Algorithm:
 *   - Iterate through the sequence and track the longest consecutive subsequence
 *     where elements are equal (or the length of repetition of same elements)
 *   - The minimum number of colors required equals the maximum number of times a
 *     value repeats consecutively in the input array.
 *
 * Time Complexity: O(n) per test case, where n is the number of balls.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long cnt(0), mx(0); // cnt: current consecutive count, mx: maximum count found
    long prev(0);       // stores the previous element to compare with current
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x != prev) {     // If current element is different from previous
        cnt = 0;           // Reset consecutive counter
      }
      ++cnt;               // Increment current counter
      mx = (mx > cnt) ? mx : cnt;  // Update maximum count
      prev = x;            // Store current element as previous for next iteration
    }
    printf("%ld\n", mx);
  }
}


// https://github.com/VaHiX/codeForces/