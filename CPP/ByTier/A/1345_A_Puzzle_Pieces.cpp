// Problem: CF 1345 A - Puzzle Pieces
// https://codeforces.com/contest/1345/problem/A

/*
 * Problem: A. Puzzle Pieces
 * Purpose: Determine if a jigsaw puzzle with n rows and m columns can be solved.
 *          Each piece has three tabs and one blank. Pieces must fit together such that
 *          a tab of one piece fits perfectly into a blank of another piece along shared edges.
 *
 * Algorithm:
 *   - The puzzle is solvable if and only if:
 *     1. One dimension is 1 (i.e., n = 1 or m = 1) - straight line arrangement possible
 *     2. Both dimensions are 2 (i.e., n = 2 and m = 2) - valid 2x2 grid arrangement
 *
 * Time Complexity: O(t), where t is the number of test cases.
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    // Check if puzzle is solvable based on the conditions:
    // - Either dimension is 1 (straight line)
    // - Both dimensions are 2 (valid 2x2 grid)
    bool possible = (n == 1) || (m == 1) || (n == 2 && m == 2);
    puts(possible ? "YES" : "NO");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/