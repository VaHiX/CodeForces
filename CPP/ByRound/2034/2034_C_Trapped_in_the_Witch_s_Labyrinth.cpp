// Problem: CF 2034 C - Trapped in the Witch's Labyrinth
// https://codeforces.com/contest/2034/problem/C

/*
C. Trapped in the Witch's Labyrinth

Algorithms/Techniques: Depth-First Search (DFS) with memoization to detect cycles in a directed graph.
The problem is equivalent to determining for each cell whether it leads to an exit or gets trapped in a cycle.
We use DFS from each cell to simulate movement and mark if a path leads out of bounds (free) or loops within the grid (trapped).
For '?' cells, we try both assignments (U/D or L/R) that maximize number of trapped starting positions.

Time Complexity: O(n * m) per test case, since each cell is visited at most once due to memoization.
Space Complexity: O(n * m) for the grid and auxiliary arrays.

*/

#include <stdio.h>
#include <iosfwd>

using namespace std;
int t, n, m;
char a[1001][1001];
int b[1001][1001];

// DFS to determine if a path from (x, y) leads to exit or gets trapped
bool dfs(int x, int y) {
  // Base case: if out of bounds, it means we're free -> return true
  if (!x || !y || x > n || y > m) {
    return 1;
  }
  
  // If already computed, return the stored result
  if (b[x][y] != -1) {
    return b[x][y];
  }
  
  // Mark current cell as being visited (0 = in process)
  b[x][y] = 0;
  
  // Follow the direction specified by the cell
  if (a[x][y] == 'U') {
    return b[x][y] = dfs(x - 1, y);  // Move up
  }
  if (a[x][y] == 'D') {
    return b[x][y] = dfs(x + 1, y);  // Move down
  }
  if (a[x][y] == 'L') {
    return b[x][y] = dfs(x, y - 1);  // Move left
  }
  if (a[x][y] == 'R') {
    return b[x][y] = dfs(x, y + 1);  // Move right
  }
  if (a[x][y] == '?') {
    // For unknown directions, we try both forward and backward directions
    // Return true if ALL possible paths lead to escape (i.e., not trapped)
    return b[x][y] =
               dfs(x - 1, y) && dfs(x + 1, y) && dfs(x, y - 1) && dfs(x, y + 1);
  }
}

int main() {
  t = 1;
  scanf("%d", &t);
  for (; t--;) {
    scanf("%d%d", &n, &m);
    
    // Read input and initialize memoization table
    for (int i = 1; i <= n; i++) {
      scanf("%s", a[i] + 1);
      for (int j = 1; j <= m; j++) {
        b[i][j] = -1;  // Mark as unvisited
      }
    }
    
    int ans = 0;
    // Try DFS from all cells and count how many are trapped
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        ans += !dfs(i, j);  // If trapped (return false), increment counter
      }
    }
    
    printf("%d\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/