// Problem: CF 1150 B - Tiling Challenge
// https://codeforces.com/contest/1150/problem/B

/*
B. Tiling Challenge
Algorithm: Greedy approach to place L-shaped pieces on a grid.
Approach:
- Iterate through each cell of the board from top-left to bottom-right.
- For each free cell, attempt to place an L-shaped piece (5 tiles) such that:
  - The center tile is placed at current cell.
  - Three adjacent cells are also free: down-left, down, and down-right.
  - A fourth cell directly below the center (two positions lower) is also free.
- Mark all these cells as occupied after placing a piece.
- If any required cell is already occupied or out of bounds, return "NO".
Time Complexity: O(n^2)
Space Complexity: O(n^2)

*/
#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long n;
  std::cin >> n;
  std::vector<std::string> a(n);
  for (long p = 0; p < n; p++) {
    std::cin >> a[p];
  }
  std::string ans("YES");
  for (long row = 0; row < n; row++) {
    for (long col = 0; col < n; col++) {
      if (a[row][col] == '#') {
        continue;
      }
      a[row][col] = '#'; // Place center of the piece
      // Check and place L-shaped piece: down-left, down, down-right
      if (row + 1 < n && col > 0 && col + 1 < n && a[row + 1][col - 1] == '.' &&
          a[row + 1][col] == '.' && a[row + 1][col + 1] == '.') {
        a[row + 1][col - 1] = a[row + 1][col] = a[row + 1][col + 1] = '#';
      } else {
        ans = "NO";
        break;
      }
      // Check and place the bottom tile of the piece (two positions down)
      if (row + 2 < n && a[row + 2][col] == '.') {
        a[row + 2][col] = '#';
      } else {
        ans = "NO";
        break;
      }
    }
  }
  std::cout << ans << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/