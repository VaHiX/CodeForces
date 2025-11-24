// Problem: CF 1749 E - Cactus Wall
// https://codeforces.com/contest/1749/problem/E

/*
Purpose: This code solves the problem of building a cactus wall on an n x m grid to block all paths from the top row to the bottom row. 
         It uses a modified BFS approach with a deque to find the minimum number of additional cacti needed to block all paths.
         The algorithm models the grid as a graph and uses BFS with a two-ended queue to efficiently manage nodes.

Algorithm: 
    - Model the grid as a graph where each cell is a node
    - Use a modified BFS with a deque (two-ended queue) to prioritize nodes based on cost
    - Start BFS from all leftmost column cells (top row to bottom row), with initial cost 0
    - For each node visited, propagate to its 4-connected neighbors
    - Track the minimum cost (number of cacti to place) to reach each node
    - If bottom row cannot be reached, return "NO"
    - If reachable, reconstruct the path and place cacti

Time Complexity: O(n * m) - Each node is visited at most once during BFS traversal
Space Complexity: O(n * m) - Space to store the grid, distance array, and BFS queue
*/

#include <stdio.h>
#include <iosfwd>

#define id(x, y) ((x) * m - m + (y))
using namespace std;
const int N = 2e5 + 5, M = 4e5 + 5, T = 2e6 + 5;
int dx[4] = {1, -1, 1, -1}, dy[4] = {1, 1, -1, -1};
int n, m;
char *s[N];
int L, R, stk[T], dis[M], from[M];

// Insert a new node into the BFS queue with updated cost
void ins(int x, int y, int k1) {
  // Check if the cell is valid and not already visited or adjacent to existing cacti
  if (x < 1 || x > n || y < 1 || y > m || (y > 1 && s[x][y - 1]) ||
      (y < m && s[x][y + 1]) || (x > 1 && s[x - 1][y]) ||
      (x < n && s[x + 1][y]) || dis[id(x, y)] != 1e9)
    return;
  // Determine if the cell was already occupied by a cactus
  int t = s[x][y] ? --L : ++R, k = id(x, y);
  dis[k] = dis[from[stk[t] = k] = k1] + (!s[x][y]);
}

// Main function to solve each test case
void xxx() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    s[i] = new char[m + 5];
    scanf("%s", s[i] + 1);
    for (int j = 1; j <= m; j++) {
      s[i][j] = s[i][j] == '#';
      int t = id(i, j);
      dis[t] = 1e9, from[t] = 0;
    }
  }
  int p = 1;
  R = 1e6;
  L = R + 1;
  // Initialize BFS from all cells in the first column
  for (int i = 1; i <= n; i++)
    ins(i, 1, 0);
  // BFS traversal using a deque
  while (L <= R) {
    int k = stk[L++], x = (k - 1) / m + 1, y = k - x * m + m;
    // Explore neighbors (4 directions)
    for (int o = 0; o < 4; o++)
      ins(x + dx[o], y + dy[o], k);
  }
  // Find the minimum cost path to reach the last column
  for (int i = 1; i <= n; i++)
    if (dis[id(p, m)] > dis[id(i, m)])
      p = i;
  // If no path exists, return NO
  if (dis[id(p, m)] == 1e9) {
    puts("NO");
    return;
  }
  // Reconstruct path and mark cells where cacti need to be placed
  for (int k = id(p, m); k;) {
    int x = (k - 1) / m + 1, y = k - x * m + m;
    s[x][y] = 1;
    k = from[k];
  }
  puts("YES");
  // Output the result grid
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++)
      s[i][j] = s[i][j] ? '#' : '.';
    printf("%s\n", s[i] + 1);
    delete s[i];
  }
}

// Main function to read input and process all test cases
int main() {
  int T;
  scanf("%d", &T);
  for (; T--;)
    xxx();
  return 0;
}


// https://github.com/VaHiX/CodeForces/