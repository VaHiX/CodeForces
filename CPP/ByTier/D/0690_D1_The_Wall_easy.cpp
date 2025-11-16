// Problem: CF 690 D1 - The Wall (easy)
// https://codeforces.com/contest/690/problem/D1

/*
 * Purpose: To count the number of disconnected wall segments in a two-dimensional wall structure made of bricks.
 *          Each brick is represented as 'B' and empty space as '.' in a grid of R rows and C columns.
 * 
 * Algorithm/Techniques: Depth-First Search (DFS)
 * 
 * Time Complexity: O(R * C) where R is the number of rows and C is the number of columns.
 *                    Each cell is visited at most once during the DFS traversal.
 * 
 * Space Complexity: O(R * C) for the visited matrix and the recursion stack in worst case (full recursion depth).
 * 
 * The code reads the wall configuration, treats each 'B' as a node in a graph,
 * and uses DFS to find connected components (wall segments).
 */

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

void dfs(int row, int col, const std::vector<std::string> &wall,
         std::vector<std::vector<bool>> &been) {
  if (been[row][col]) {
    return;
  }
  been[row][col] = 1;
  if (wall[row][col] == '.') {
    return;
  }
  // Check and recurse to adjacent bricks (up, down, left, right)
  if (row > 0 && !been[row - 1][col] && wall[row - 1][col] == 'B') {
    dfs(row - 1, col, wall, been);
  }
  if (row + 1 < wall.size() && !been[row + 1][col] &&
      wall[row + 1][col] == 'B') {
    dfs(row + 1, col, wall, been);
  }
  if (col > 0 && !been[row][col - 1] && wall[row][col - 1] == 'B') {
    dfs(row, col - 1, wall, been);
  }
  if (col + 1 < been[row].size() && !been[row][col + 1] &&
      wall[row][col + 1] == 'B') {
    dfs(row, col + 1, wall, been);
  }
  return;
}
int main() {
  std::ios_base::sync_with_stdio(false);
  int r, c;
  std::cin >> r >> c;
  std::vector<std::string> w(r);
  std::vector<std::vector<bool>> visited(r, std::vector<bool>(c, 0));
  // Read the wall from bottom to top to match the expected input format
  for (int p = r - 1; p >= 0; p--) {
    std::cin >> w[p];
  }
  int count(0);
  // Iterate through each cell to find unvisited bricks and start DFS
  for (int h = 0; h < r; h++) {
    for (int k = 0; k < c; k++) {
      if (w[h][k] == '.') {
        continue;
      }
      if (visited[h][k]) {
        continue;
      }
      ++count;
      dfs(h, k, w, visited);
    }
  }
  printf("%d\n", count);
  return 0;
}


// https://github.com/VaHiX/CodeForces/