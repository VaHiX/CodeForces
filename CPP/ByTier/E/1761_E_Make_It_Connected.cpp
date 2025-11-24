// Problem: CF 1761 E - Make It Connected
// https://codeforces.com/contest/1761/problem/E

/*
Purpose: This code determines the minimum number of operations to make a disconnected undirected graph connected.
         Each operation allows toggling all edges of a selected vertex (connect to non-adjacent, disconnect adjacent).
         The algorithm identifies connected components and uses the structure to determine minimal operations.

Algorithms/Techniques:
- DFS to find connected components
- Greedy heuristic to minimize operations based on component sizes and structure

Time Complexity: O(n^2) per test case, where n is the number of vertices
Space Complexity: O(n^2) for storing the adjacency matrix and component lists

*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long ll;
int n;
bool vis[4005];
vector<int> co[4005]; // Stores vertices in each connected component
char mp[4005][4005]; // Adjacency matrix of the graph

// DFS to find connected components
void dfs(int u, int r) {
  vis[u] = 1, co[r].push_back(u);
  for (int i = 1; i <= n; ++i)
    if (mp[u][i] == '1' && !vis[i])
      dfs(i, r); // Recursively visit all adjacent unvisited nodes
}

int main() {
  int _;
  scanf("%d", &_);
  while (_--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%s", mp[i] + 1), co[i].clear(); // Read input and reset component lists
    memset(vis, 0, sizeof(vis)); // Reset visited array
    int num = 0, res = 0, res2 = 0; // num: number of components, res: vertex for single operation, res2: vertex for 1-op case
    
    // Find connected components using DFS
    for (int i = 1; i <= n; ++i)
      if (!vis[i]) {
        dfs(i, ++num); // Start DFS for new component
        // Check for any pair of vertices in component that are not connected
        for (int x : co[num])
          for (int y : co[num])
            if (x != y && mp[x][y] == '0')
              res = x; // If there exists a missing connection, choose one vertex for operation
        if (co[num].size() == 1)
          res2 = co[num][0]; // If the component has only one vertex, remember it
      }
    
    // If graph is already connected
    if (num == 1) {
      puts("0");
      continue;
    }
    
    // If we found a vertex that can make the component connected with one operation
    if (res) {
      printf("1\n%d\n", res);
      continue;
    }
    
    // If there are more than 2 components
    if (num > 2) {
      if (res2)
        printf("1\n%d\n", res2); // Use a single vertex from a single-node component
      else
        printf("2\n%d %d\n", co[1][0], co[2][0]); // Use two vertices from first two components
      continue;
    }
    
    // If there are exactly two components, check their sizes
    if (co[1].size() > co[2].size())
      swap(co[1], co[2]); // Make sure co[1] has the smaller component
    
    printf("%d\n", (int)co[1].size()); // Number of operations needed
    for (int x : co[1])
      printf("%d ", x); // Print vertices for operations
    puts("");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/