// Problem: CF 2049 A - MEX Destruction
// https://codeforces.com/contest/2049/problem/A

/* 
 * Problem: A. MEX Destruction
 * Purpose: Given an array of non-negative integers, determine the minimum number of operations
 *          to reduce all elements to zero by replacing any subarray with its MEX (minimum excluded value).
 *          
 * Algorithm:
 *   - For each test case, process the array from left to right.
 *   - Track transitions between zeros and non-zeros using a flag `prev`.
 *   - Count how many times we switch between 0 and non-0 values.
 *   - The number of operations is determined based on the count:
 *     * If count == 0: already all zeros, return 0
 *     * If count <= 2: one operation can reduce it to 0s, return 1
 *     * Otherwise: at least two operations needed, return 2
 *   
 * Time Complexity: O(n) per test case, where n is the size of the array.
 * Space Complexity: O(1), only using a few variables.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long s(0);         // Counter for number of transitions
    bool prev(0);      // Flag to track previous value (0 or 1)
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x) {         // If current element is non-zero
        s += !prev;    // Increment if we're transitioning from 0 to non-zero
        prev = 1;      // Set flag to indicate we are now in a non-zero section
      } else {
        s += prev;     // Increment if we're transitioning from non-zero to 0
        prev = 0;      // Set flag to indicate we are now in a zero section
      }
    }
    if (s == 0) {
      puts("0");
    } else if (s <= 2) {
      puts("1");
    } else {
      puts("2");
    }
  }
}


// https://github.com/VaHiX/codeForces/