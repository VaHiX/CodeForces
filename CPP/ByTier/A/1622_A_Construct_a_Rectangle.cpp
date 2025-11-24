// Problem: CF 1622 A - Construct a Rectangle
// https://codeforces.com/contest/1622/problem/A

/*
 * Problem: A. Construct a Rectangle
 * Purpose: Determine if it's possible to break exactly one stick into two pieces
 *          such that the four resulting pieces can form a rectangle.
 * 
 * Algorithm:
 * - For each testcase, we have three stick lengths a, b, c.
 * - We try breaking one of the sticks into two positive integer parts.
 * - After breaking, we check if the resulting four pieces can form a rectangle:
 *   - This means we can pair them as two pairs of equal lengths (opposite sides).
 *   - Case 1: One stick is broken into parts x and y such that:
 *     - Two of the remaining sticks are equal, and one of the newly created
 *       pieces equals the other two sticks.
 *   - Case 2: The sum of any two pieces equals another piece (this ensures
 *     one can form a valid pair for rectangle).
 * 
 * Time Complexity: O(1) per test case — constant time operations.
 * Space Complexity: O(1) — only using a fixed number of variables.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c;
    scanf("%ld %ld %ld", &a, &b, &c);
    bool res(false);
    // Check if the three sticks can form a rectangle directly
    if (a == b + c || b == a + c || c == a + b) {
      res = true;
    }
    // Special cases where one of the sticks is even and two others are equal,
    // which allows breaking such that we get equal pairs
    if ((a % 2 == 0 && b == c) || (b % 2 == 0 && a == c) ||
        (c % 2 == 0 && a == b)) {
      res = true;
    }
    puts(res ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/