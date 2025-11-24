// Problem: CF 1991 E - Coloring Game
// https://codeforces.com/contest/1991/problem/E

/*
Purpose:
This code solves an interactive game problem where Alice and Bob play a coloring game on a graph. 
The goal is to determine which player has a winning strategy based on the structure of the graph.
The strategy is based on whether the graph is bipartite or not:
- If the graph is bipartite, Bob can always win by ensuring no two adjacent vertices have the same color.
- Otherwise, Alice wins by forcing a monochromatic edge.

Algorithms/Techniques:
- Graph traversal using DFS to check if the graph is bipartite.
- Bipartite graph detection using 2-coloring.
- Strategy implementation based on graph properties.

Time Complexity: O(n + m) for each test case due to single DFS traversal and graph construction.
Space Complexity: O(n + m) for storing the graph and auxiliary arrays.

*/
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;
int T, n, m, ok;
int col[10005];  // Color array to store color of each vertex
int a[10005];    // Array to store vertices of color 1
int b[10005];    // Array to store vertices of color 2
vector<int> g[10005];  // Adjacency list representation of the graph

// Fast input function
inline void in(int &n) {
  n = 0;
  char c = getchar();
  while (c < '0' || c > '9')
    c = getchar();
  while (c >= '0' && c <= '9')
    n = n * 10 + c - '0', c = getchar();
  return;
}

// DFS to check bipartiteness and assign colors
inline void dfs(int u, int c) {
  col[u] = c;  // Assign color to current vertex
  for (int v : g[u]) {  // For each neighbor
    if (!col[v])  // If not yet colored
      dfs(v, 3 - c);  // Recursively color with opposite color (1->2, 2->1)
    else if (3 - c != col[v]) {  // If already colored with wrong color
      ok = 0;  // Mark not bipartite
      return;
    }
    if (!ok)  // Early return if not bipartite
      return;
  }
}

int main() {
  in(T);
  while (T--) {
    in(n), in(m);
    for (int i = 1; i <= n; i++)
      g[i].clear(), col[i] = 0;  // Clear graph and color arrays
    
    // Read edges and build adjacency list
    while (m--) {
      int u, v;
      in(u), in(v);
      g[u].emplace_back(v);
      g[v].emplace_back(u);
    }
    
    ok = 1;  // Initialize bipartite flag
    dfs(1, 1);  // Start DFS from vertex 1 with color 1
    
    if (!ok) {
      // If not bipartite, Alice wins by forcing a monochromatic edge
      puts("Alice");
      fflush(stdout);
      while (n--) {
        puts("1 2");  // Alice chooses colors 1 and 2
        fflush(stdout);
        int u, v;
        in(u), in(v);  // Read Bob's move
      }
    } else {
      // If bipartite, Bob wins by maintaining bipartite coloring
      int c1 = 0, c2 = 0;
      // Separate vertices into two sets based on color
      for (int i = 1; i <= n; i++)
        if (col[i] == 1)
          a[++c1] = i;
        else
          b[++c2] = i;
      
      puts("Bob");
      fflush(stdout);
      // Simulate the game with Bob's optimal strategy
      while (n--) {
        int x, y;
        in(x), in(y);  // Read Alice's choice of colors
        // Choose vertex and color according to strategy
        if ((x == 1 || y == 1) && c1)
          printf("%d 1\n", a[c1--]);  // Use color 1
        else if ((x == 2 || y == 2) && c2)
          printf("%d 2\n", b[c2--]);  // Use color 2
        else if (c1)
          printf("%d %d\n", a[c1--], (x == 1 || y == 1) ? 1 : 3);  // Use color 3
        else
          printf("%d %d\n", b[c2--], (x == 2 || y == 2) ? 2 : 3);  // Use color 3
        fflush(stdout);
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/