// Problem: CF 2053 A - Tender Carpenter
// https://codeforces.com/contest/2053/problem/A

/*
 * Problem: A. Tender Carpenter
 * Task: Determine if an array can be partitioned into at least two different ways
 *       such that each partition's subsegment forms a "stable" set of integers.
 *       A stable set means any three elements can form a non-degenerate triangle.
 *
 * Algorithm:
 *   - For each test case, iterate through the array and check if any adjacent pair
 *     satisfies the condition: for elements x and prev, if prev < 2*x and x < 2*prev,
 *     then they can be in the same stable segment.
 *   - If such a condition is satisfied anywhere in the array, then there are at least two valid partitions:
 *     one where these elements are grouped together, and another where they are split apart.
 *
 * Time Complexity: O(n) per test case, where n is the length of the array.
 * Space Complexity: O(1), using only a constant amount of extra space.
 */

#include <cstdio>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long prev(-1);
    bool res(false);
    for (long p = 0; p < n; p++) {  // Iterate over all elements
      long x;
      scanf("%ld", &x);
      if (p > 0 && (x < 2 * prev) && (prev < 2 * x)) {  // Check if current and previous values satisfy stable condition
        res = true;  // If true, it's possible to partition in more than one way
      }
      prev = x;
    }
    puts(res ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/