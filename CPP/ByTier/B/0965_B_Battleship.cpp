// Problem: CF 965 B - Battleship
// https://codeforces.com/contest/965/problem/B

/*
Algorithm: Battleship
Approach: 
  - For each cell on the board, count how many valid ship placements (horizontal or vertical) it can be part of.
  - A ship placement is valid if all k consecutive cells in that direction are not '#'.
  - For each valid placement, increment the count for each cell in that placement.
  - Find the cell with the maximum count.

Time Complexity: O(n^2 * k)
Space Complexity: O(n^2)

The algorithm iterates through each cell (n*n), and for each cell, it checks:
  - Vertical placements (k steps) and
  - Horizontal placements (k steps).
Each check involves a loop of length k.

The final loop to find the maximum is O(n^2).
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

int main() {
  long n, k;
  std::cin >> n >> k;
  std::vector<std::string> b(n);
  for (long p = 0; p < n; p++) {
    std::cin >> b[p];
  }
  std::vector<std::vector<long>> d(n, std::vector<long>(n, 0));
  for (long row = 0; row < n; row++) {
    for (long col = 0; col < n; col++) {
      if (b[row][col] == '#') {
        continue;
      }
      // Check if vertical ship of length k can be placed starting at (row, col)
      if (row + k <= n) {
        bool vp(true);
        for (long p = row; p < row + k; p++) {
          if (b[p][col] == '#') {
            vp = false;
            break;
          }
        }
        // If valid, increment count for all cells in this vertical placement
        for (long p = row; p < row + k; p++) {
          d[p][col] += vp;
        }
      }
      // Check if horizontal ship of length k can be placed starting at (row, col)
      if (col + k <= n) {
        bool hp(true);
        for (long p = col; p < col + k; p++) {
          if (b[row][p] == '#') {
            hp = false;
            break;
          }
        }
        // If valid, increment count for all cells in this horizontal placement
        for (long p = col; p < col + k; p++) {
          d[row][p] += hp;
        }
      }
    }
  }
  long mx(0), mxr(0), mxc(0);
  // Find the cell with maximum count
  for (long row = 0; row < n; row++) {
    for (long col = 0; col < n; col++) {
      if (d[row][col] > mx) {
        mxr = row;
        mxc = col;
        mx = d[row][col];
      }
    }
  }
  printf("%ld %ld\n", mxr + 1, mxc + 1);
  return 0;
}


// https://github.com/VaHiX/CodeForces/