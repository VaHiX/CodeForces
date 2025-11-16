// Problem: CF 1130 C - Connect
// https://codeforces.com/contest/1130/problem/C

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

// Flowerbox: 
// Problem: Connect
// Purpose: Find minimum cost to create at most one tunnel between two land cells on a grid,
//          allowing Alice to travel from start to destination. Tunnel cost is Euclidean squared distance.
// Algorithms used:
//   - DFS to mark connected components of land cells
//   - Brute-force check all pairs of land cells in each component for minimal tunnel cost
// Time Complexity: O(n^4) due to nested loops checking all pairs of land cells from both components
// Space Complexity: O(n^2) for storing grid and visited arrays

void dfs(long row, long col, const std::vector<std::string> &m,
         std::vector<std::vector<int>> &been, int tp) {
  if (m[row][col] == '1') { // If cell is water
    return;
  }
  if (been[row][col] != 0) { // If already visited
    return;
  }
  been[row][col] = tp; // Mark with component ID
  if (row > 0) {
    dfs(row - 1, col, m, been, tp); // Up
  }
  if (row + 1 < m.size()) {
    dfs(row + 1, col, m, been, tp); // Down
  }
  if (col > 0) {
    dfs(row, col - 1, m, been, tp); // Left
  }
  if (col + 1 < m.size()) {
    dfs(row, col + 1, m, been, tp); // Right
  }
}
int main() {
  long n;
  std::cin >> n;
  long rs, cs;
  std::cin >> rs >> cs;
  long rt, ct;
  std::cin >> rt >> ct;
  --rs; // Convert to 0-based indexing
  --cs;
  --rt;
  --ct;
  std::vector<std::string> m(n);
  for (long p = 0; p < n; p++) {
    std::cin >> m[p];
  }
  std::vector<std::vector<int>> vis(n, std::vector<int>(n, 0)); // Visited array to track components
  dfs(rs, cs, m, vis, 1); // Mark start component
  dfs(rt, ct, m, vis, 2); // Mark destination component
  if (vis[rt][ct] == 1) { // If dest is in same component as start
    puts("0"); // No tunnel needed
  } else {
    long dist = 1e9; // Initialize minimum distance
    for (long xr = 0; xr < n; xr++) {
      for (long xc = 0; xc < n; xc++) {
        if (m[xr][xc] == '1') { // Skip water cells
          continue;
        }
        if (vis[xr][xc] != 1) { // Only consider land cells in start component
          continue;
        }
        for (long yr = 0; yr < n; yr++) {
          for (long yc = 0; yc < n; yc++) {
            if (m[yr][yc] == '1') { // Skip water cells
              continue;
            }
            if (vis[yr][yc] != 2) { // Only consider land cells in destination component
              continue;
            }
            long cur = (xr - yr) * (xr - yr) + (xc - yc) * (xc - yc); // Compute tunnel cost
            dist = dist < cur ? dist : cur; // Update minimum
          }
        }
      }
    }
    printf("%ld\n", dist);
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/