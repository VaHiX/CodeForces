// Problem: CF 1662 O - Circular Maze
// https://codeforces.com/contest/1662/problem/O

/*
O. Circular Maze
Time Complexity: O(n * 360) per test case, where n is the number of walls.
Space Complexity: O(40 * 360) = O(1) due to fixed dimensions.

Algorithms/Techniques:
- This problem uses a graph traversal approach (DFS) on a discretized circular maze.
- The maze is modeled as a grid where each cell represents a sector in the circular space.
- Walls are marked as blocked cells.
- Then, a DFS from the center (1,1) checks if there's a path to the outer boundary (y=720).

The maze is converted into a 2D grid by mapping radius and angle to indices.
Each circular wall is discretized into sectors. Straight walls are also converted
into sectors. Then, DFS is run from (1,1) to check if we can reach the border.
*/
#include <stdio.h>
#include <string.h>
#include <iostream>

#define use 1, n, rt
#define left l, mid, ls[p]
#define righ mid + 1, r, rs[p]
#define N 500000
#define fer(x, y, z) for (register int x = y; x <= z; x++)
using namespace std;
int t, n;
bool pd[41][361 * 2], vis[41][361 * 2]; // pd marks walls, vis marks visited
int sak_dfs(int x, int y) {
  if (x == 40) { // If reached outermost layer
    return true;
  }
  vis[x][y] = 1; // Mark current position as visited
  int flag = 0;
  if (y == 1) { // Wrap around to end
    if (!pd[x][720] && !vis[x][720])
      flag += sak_dfs(x, 720);
  } else if (!pd[x][y - 1] && !vis[x][y - 1]) // Move left (decrease angle)
    flag += sak_dfs(x, y - 1);
  if (y == 720) { // Wrap around to start
    if (!pd[x][1] && !vis[x][1])
      flag += sak_dfs(x, 1);
  } else if (!pd[x][y + 1] && !vis[x][y + 1]) // Move right (increase angle)
    flag += sak_dfs(x, y + 1);
  if (x != 1 && !pd[x - 1][y] && !vis[x - 1][y]) // Move up (decrease radius)
    flag += sak_dfs(x - 1, y);
  if (!pd[x + 1][y] && !vis[x + 1][y]) // Move down (increase radius)
    flag += sak_dfs(x + 1, y);
  return flag != 0;
}
signed main() {
  cin >> t;
  while (t--) {
    char ch;
    int x, y, z;
    cin >> n;
    memset(pd, 0, sizeof pd), memset(vis, 0, sizeof vis); // Reset for each test case
    fer(i, 1, n) {
      scanf(" %c%d%d%d", &ch, &x, &y, &z);
      x *= 2; // Scale up to improve precision
      y *= 2, z *= 2;
      if (ch == 'C') { // Circular wall
        y += 2, z += 2; // Adjust for scaling and shift angles to align with indexing
        if (y > z) { // Overlapping case
          fer(i, y, 720) pd[x][i] = 1; // Mark the portion from y to end
          fer(i, 1, z) pd[x][i] = 1;   // Then mark from start to z
        } else
          fer(i, y, z) pd[x][i] = 1; // Mark regular segment
      } else // Straight wall
        fer(i, x, y) pd[i][z + 2] = 1; // Mark vertical wall at angle z+2 (scaled)
    }
    if (sak_dfs(1, 1)) // Start DFS from center cell (1,1)
      cout << "YES\n";
    else
      cout << "NO\n";
  }
}


// https://github.com/VaHiX/codeForces/