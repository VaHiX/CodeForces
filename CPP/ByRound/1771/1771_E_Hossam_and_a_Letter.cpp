// Problem: CF 1771 E - Hossam and a Letter
// https://codeforces.com/contest/1771/problem/E

/*
 * Code Purpose: Find the maximum number of walls to form the capital letter 'H'
 *               on an n x m grid, considering quality of cells.
 * 
 * Algorithms/Techniques:
 * - Dynamic Programming (DP) with 2D arrays to track valid vertical line segments
 * - Two passes per column pair: upward and downward DP for vertical lines
 * - Iterate over all valid horizontal positions and column pairs
 * 
 * Time Complexity: O(n * m^2)
 * Space Complexity: O(n * m)
 * 
 * Note:
 * - 'H' is made of one horizontal and two vertical lines
 * - Vertical lines start and end in same row, not adjacent or same column
 * - Horizontal line connects vertical lines
 * - Costs:
 *   - Perfect ('.'): 0
 *   - Medium ('m'): 1
 *   - Bad ('#'): 2 (forbidden)
 * - At most one medium cell can be used.
 */

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
const int Maxn = 405;
int n, m;
char B[Maxn][Maxn];
int val[Maxn][Maxn];     // Convert characters to cost values
int U[Maxn][Maxn][2];    // Upward DP: U[b][i][cost] = max length ending at (i,b) with cost
int D[Maxn][Maxn][2];    // Downward DP: D[b][i][cost] = max length starting at (i,b) with cost
int res;                 // Result storing maximum wall count

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i++) {
    scanf("%s", B[i]);
    for (int j = 0; j < m; j++) {
      if (B[i][j] == '#')
        val[i][j] = 2;     // Bad cell, forbidden
      else if (B[i][j] == 'm')
        val[i][j] = 1;     // Medium cell, cost 1
    }
  }
  for (int a = 0; a < m; a++) {
    for (int b = a + 2; b < m; b++) {  // Ensure vertical lines are not adjacent or same
      for (int i = 0; i < n; i++) {
        int cost = val[i][a] + val[i][b];
        // Upward DP: cost <= 0 or 1 allowed
        U[b][i][0] = cost <= 0 ? 2 + (i > 0 ? U[b][i - 1][0] : 0) : 0;
        U[b][i][1] = cost <= 1 ? 2 + (i > 0 ? U[b][i - 1][1 - cost] : 0) : 0;
      }
      for (int i = n - 1; i >= 0; i--) {
        int cost = val[i][a] + val[i][b];
        // Downward DP: cost <= 0 or 1 allowed
        D[b][i][0] = cost <= 0 ? 2 + (i + 1 < n ? D[b][i + 1][0] : 0) : 0;
        D[b][i][1] = cost <= 1 ? 2 + (i + 1 < n ? D[b][i + 1][1 - cost] : 0) : 0;
      }
    }
    for (int i = 1; i + 1 < n; i++) {  // Horizontal line must not be top or bottom row
      int cnt = 0;   // Count medium cells in current row
      for (int b = a; b < m && cnt <= 1; b++) {  // b advances while medium count <= 1
        cnt += val[i][b]; // accumulate medium cells in this row
        if (b - a >= 2) { // Ensure horizontal line length > 2 (since columns are at least 2 apart)
          for (int z1 = 0; cnt + z1 <= 1; z1++) { // Check possible cost combinations
            int z2 = 1 - cnt - z1;
            if (U[b][i - 1][z1] >= 2 && D[b][i + 1][z2] >= 2) {
              // Check if segments are long enough
              res = max(res, b - a + 1 + U[b][i - 1][z1] + D[b][i + 1][z2]);
            }
          }
        }
      }
    }
  }
  cout << res << '\n';
}


// https://github.com/VaHiX/CodeForces/