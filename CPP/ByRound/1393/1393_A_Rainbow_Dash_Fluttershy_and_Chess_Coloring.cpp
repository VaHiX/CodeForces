// Problem: CF 1393 A - Rainbow Dash, Fluttershy and Chess Coloring
// https://codeforces.com/contest/1393/problem/A

/*
 * Problem: A. Rainbow Dash, Fluttershy and Chess Coloring
 *
 * Purpose: Find the minimum number of turns to build a chess coloring pattern
 *          on an n x n grid using alternating light blue and yellow blocks.
 *
 * Algorithm: The optimal strategy involves placing blocks in such a way that
 *            each turn places blocks of one color. Since we're building a chess 
 *            pattern, we start with a border and build inward. The total number 
 *            of turns required is (1 + n / 2) for an n x n grid.
 *
 * Time Complexity: O(T), where T is the number of test cases. Each test case
 *                  takes constant time to compute.
 *
 * Space Complexity: O(1), only using a constant amount of extra space.
 */

#include <cstdio>
int main() {
  long t;                         // Read number of test cases
  scanf("%ld", &t);
  while (t--) {
    long x;                       // Read the size of the grid
    scanf("%ld", &x);
    printf("%ld\n", 1 + x / 2);   // Output minimum turns needed
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/