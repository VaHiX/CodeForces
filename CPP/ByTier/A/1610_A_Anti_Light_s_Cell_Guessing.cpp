// Problem: CF 1610 A - Anti Light's Cell Guessing
// https://codeforces.com/contest/1610/problem/A

/*
 * Problem: Minimum number of queries to identify a hidden cell in an n x m grid
 * using Manhattan distances.
 *
 * Algorithm/Techniques:
 * - The key insight is that we need to determine the minimum number of queries (k)
 *   such that for any hidden cell, we can uniquely identify it based on Manhattan
 *   distances from the queried cells.
 *
 * - For a 1x1 grid, no queries needed (k=0), but since the problem requires k>=1,
 *   we output 0 for this case.
 *
 * - For a 1xN or Nx1 grid (linear), one query suffices to distinguish any two cells
 *   because Manhattan distance on a line uniquely identifies positions when only
 *   one dimension varies. So k=1.
 *
 * - For grids larger than 1x1, we can prove that 2 queries are sufficient and necessary
 *   in the worst case to uniquely identify any hidden cell in an n x m grid where both
 *   n,m > 1. This is because two distances can form a system of equations that has a
 *   unique solution for position (x, y) given two query points.
 *
 * Time Complexity: O(1) - constant time per test case.
 * Space Complexity: O(1) - only using a few variables.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    if (n == 1 && m == 1) {
      puts("0");  // Special case: single cell, no queries needed
    } else if (n == 1 || m == 1) {
      puts("1");  // One-dimensional case: one query suffices
    } else {
      puts("2");  // Two-dimensional case: two queries needed for uniqueness
    }
  }
}


// https://github.com/VaHiX/codeForces/