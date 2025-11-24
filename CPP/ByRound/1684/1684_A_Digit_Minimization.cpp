// Problem: CF 1684 A - Digit Minimization
// https://codeforces.com/contest/1684/problem/A

/*
 * Problem: Digit Minimization
 * Purpose: Given an integer without zeros, Alice and Bob play a game where:
 *          - Alice swaps any two digits (optimal play)
 *          - Bob removes the last digit
 *          - Game ends when only one digit remains
 *          Goal: Find the smallest possible digit Alice can end with.
 *
 * Algorithm:
 *   - For numbers < 10: Output as is
 *   - For numbers < 100: Output last digit (only one swap possible, Bob removes last)
 *   - For numbers >= 100: Find the minimum digit in the number
 *     and use it for final result (Alice can always arrange digits to put the smallest at end).
 *
 * Time Complexity: O(log n) per test case, where log n represents number of digits.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n < 10) {
      printf("%ld\n", n);
    } else if (n < 100) {
      // For two-digit numbers, Alice can only swap; Bob removes last digit.
      // So output the last digit which is n % 10
      printf("%ld\n", n % 10);
    } else {
      // For multi-digit numbers, Alice can arrange digits to put smallest at end
      int res(10); // Initialize with a value larger than any single digit (0-9)
      while (n) {
        int d = n % 10;       // Extract last digit
        res = (res < d ? res : d);  // Keep track of minimum
        n /= 10;              // Remove last digit
      }
      printf("%d\n", res);
    }
  }
}


// https://github.com/VaHiX/codeForces/