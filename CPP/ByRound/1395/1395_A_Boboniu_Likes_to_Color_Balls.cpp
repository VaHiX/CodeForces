// Problem: CF 1395 A - Boboniu Likes to Color Balls
// https://codeforces.com/contest/1395/problem/A

/*
 * Problem: Boboniu Likes to Color Balls
 * Algorithm/Technique: Simulation and parity analysis
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 *
 * Approach:
 * - For a sequence of balls to form a palindrome, at most one color can have an odd count.
 * - The allowed operation reduces red, green, and blue balls by 1 each and increases white by 1.
 * - First check if the current counts already satisfy palindrome condition (at most 1 odd count).
 * - If not, simulate one operation (if possible) and recheck.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long r, g, b, w;
    scanf("%ld %ld %ld %ld", &r, &g, &b, &w);
    // Check if already possible to make palindrome with current counts
    if (r % 2 + g % 2 + b % 2 + w % 2 <= 1) {
      puts("Yes");
    } else if (r > 0 && g > 0 && b > 0) {
      // Perform one operation: reduce r, g, b by 1 and increase w by 1
      --r;
      --g;
      --b;
      ++w;
      // Check if after operation it's possible to form palindrome
      if (r % 2 + g % 2 + b % 2 + w % 2 <= 1) {
        puts("Yes");
      } else {
        puts("No");
      }
    } else {
      // Not enough red, green, or blue balls to perform operation
      puts("No");
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/