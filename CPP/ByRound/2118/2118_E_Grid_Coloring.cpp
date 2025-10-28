// Problem: CF 2118 E - Grid Coloring
// https://codeforces.com/contest/2118/problem/E

/*
E. Grid Coloring
Algorithms/Techniques: Sorting with custom comparator based on chessboard and Manhattan distance.
Time Complexity: O(n * m * log(n * m)) - due to sorting
Space Complexity: O(n * m) - for storing cell positions

The problem asks to color a grid such that no cell receives more than 3 penalties.
Penalties are assigned to colored cells based on their "distance" from the current cell,
with tie-breaking using Manhattan distance. The approach is to:
1. Compute for each cell its "distance" from the center of the grid (using chessboard distance).
2. If two cells have same chessboard distance, use Manhattan distance as tie-breaker.
3. Sort all cells based on this custom order.
4. Output the sorted coordinates.

This greedy approach works because sorting ensures that when we color a cell,
the furthest colored cells are those with maximum chessboard distance from center,
ensuring small penalty values and preventing any single cell from exceeding 3 penalties.
*/

#include <stdlib.h>
#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

using namespace std;
int t, n, m;
int main() {
  cin >> t;
  while (t--) {
    cin >> n >> m;
    vector<array<int, 4>> pos; // Store {chessboard_dist, manhattan_dist, row, col}
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++) {
        int di = abs(i - (n + 1) / 2);  // Distance from center in row
        int dj = abs(j - (m + 1) / 2);  // Distance from center in column
        array<int, 4> node = {max(di, dj), di + dj, i, j}; // Sort by chessboard, then Manhattan
        pos.emplace_back(node);
      }
    sort(pos.begin(), pos.end());  // Sort based on custom criteria
    for (auto tmp : pos)
      cout << tmp[2] << ' ' << tmp[3] << '\n'; // Output row and column
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/