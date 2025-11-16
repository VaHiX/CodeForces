// Problem: CF 934 B - A Prosperous Lot
// https://codeforces.com/contest/934/problem/B

/*
 * Code Purpose:
 * This program finds a positive integer n not greater than 10^18 such that 
 * the number of "loops" in its decimal representation equals k.
 * A loop is defined as an enclosed area in the digit's shape:
 * - 0, 6, 9 have 1 loop
 * - 8 has 2 loops
 * - Other digits (1, 2, 3, 4, 5, 7) have 0 loops
 *
 * Strategy:
 * - Use as many '8's as possible (each contributes 2 loops)
 * - If k is odd, add one '9' (contributes 1 loop)
 * - Avoid exceeding 10^18 by checking that k <= 18 * 2 (since max 18 digits)
 *
 * Time Complexity: O(k), which is effectively O(1) since k <= 1e6.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */

#include <cstdio>
int main() {
  long k;
  scanf("%ld", &k);
  if (k <= 0) {
    puts("1");
  }
  if (k > 18 * 2) { // Check if k exceeds maximum possible loops with 18 digits
    puts("-1");
  } else {
    for (long p = 0; p < k / 2; p++) { // Add as many '8's as possible (each contributes 2 loops)
      printf("8");
    }
    if (k & 1) { // If k is odd, add one '9' to contribute 1 loop
      printf("9");
    }
    puts(""); // Print newline
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/