// Problem: CF 1194 B - Yet Another Crosses Problem
// https://codeforces.com/contest/1194/problem/B

/*
B. Yet Another Crosses Problem
Algorithms/Techniques: Greedy, Preprocessing
Time Complexity: O(n*m) per query
Space Complexity: O(n+m) per query

The problem asks to find the minimum number of white cells to paint black to form at least one cross.
A cross is defined by a row and column where all cells in that row and column are black.

Approach:
1. Precompute for each row and column how many black cells they contain.
2. For each cell (i,j), calculate how many cells need to be painted if we place a cross at (i,j).
   This is: (nr - rowcount[i]) + (nc - colcount[j]) - (v[i][j] == '*').
3. The "- (v[i][j] == '*')" ensures we don't double count if the cell itself is already black.
4. Find the minimum over all such possibilities.
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

int main() {
  long q;
  std::cin >> q;
  while (q--) {
    long nr, nc;
    std::cin >> nr >> nc;
    std::vector<std::string> v(nr);
    for (long p = 0; p < nr; p++) {
      std::cin >> v[p];
    }
    // Count black cells in each row and column
    std::vector<long> rowcount(nr), colcount(nc);
    for (long row = 0; row < nr; row++) {
      for (long col = 0; col < nc; col++) {
        if (v[row][col] == '.') {
          continue;
        }
        ++rowcount[row];
        ++colcount[col];
      }
    }
    // Initialize result to maximum possible value
    long res(2 * nr + 2 * nc);
    for (long row = 0; row < nr; row++) {
      for (long col = 0; col < nc; col++) {
        // Calculate minimum cells to paint if we place cross at (row, col)
        long tmp =
            (nr - rowcount[row]) + (nc - colcount[col]) - (v[row][col] == '.');
        res = (res < tmp) ? res : tmp;
      }
    }
    printf("%ld\n", res);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/