// Problem: CF 1505 E - Cakewalk
// https://codeforces.com/contest/1505/problem/E

/*
E. Cakewalk
Algorithms/Techniques: Greedy approach
Time Complexity: O(H * W * (H + W))
Space Complexity: O(H * W)

The mouse starts at the top-left corner of the cake and can only move right or down.
It chooses the next berry to visit greedily, always picking the nearest unvisited berry
among those reachable from the current position. This process continues until no more
berries can be reached.

Input:
- H, W: height and width of the cake (1 <= H, W <= 5)
- H lines of W characters each:
  '.' - empty square
  '*' - square with a berry

Output:
- Number of berries eaten following the greedy strategy.
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  long h, w;
  std::cin >> h >> w;
  std::vector<std::string> b(h);
  for (long p = 0; p < h; p++) {
    std::cin >> b[p];
  }
  long row(0), col(0), cnt(b[0][0] == '*'); // Start at top-left, count berry if exists
  while (true) {
    bool found(false);
    long mindist(1000), qrow(-1), qcol(-1);
    for (long rr = row; rr < h; rr++) { // Iterate through rows from current position
      for (long cc = col; cc < w; cc++) { // Iterate through columns from current position
        if (rr == row && cc == col) {
          continue; // Skip the current position itself
        }
        if (b[rr][cc] != '*') {
          continue; // Skip non-berry squares
        }
        found = true;
        long dist = (rr - row) + (cc - col); // Manhattan distance
        if (dist < mindist) {
          mindist = dist;
          qrow = rr;
          qcol = cc;
        }
      }
    }
    if (!found) {
      break; // No more berries found
    }
    ++cnt;
    row = qrow;
    col = qcol;
  }
  std::cout << cnt << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/