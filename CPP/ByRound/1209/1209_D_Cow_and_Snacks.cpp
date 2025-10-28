// Problem: CF 1209 D - Cow and Snacks
// https://codeforces.com/contest/1209/problem/D

/*
D. Cow and Snacks
Purpose: This code solves the problem of minimizing the number of sad guests at a party by optimally ordering guests to eat snacks.
The problem involves finding the minimum number of guests who will become sad because their favorite snack flavor is no longer available when they arrive.

Approach:
- Model the problem as a graph where each guest is a node and edges represent shared favorite flavors.
- Use DFS to find connected components in this graph.
- The number of sad guests = total snacks - total guests + number of connected components.

Time Complexity: O(n + k), where n is the number of snacks and k is the number of guests.
Space Complexity: O(n + k), for storing the graph and visited array.

Algorithms/Techniques:
- Graph representation using adjacency list
- Depth First Search (DFS)
- Connected component counting
*/

#include <cstdio>
#include <vector>

void dfs(const std::vector<std::vector<long>> &g, long node,
         std::vector<bool> &been) {
  if (been[node]) {           // If already visited, return
    return;
  }
  been[node] = 1;             // Mark current node as visited
  for (long p = 0; p < g[node].size(); p++) { // Iterate through neighbors
    long u = g[node][p];
    if (been[u]) {            // If neighbor already visited, skip
      continue;
    }
    dfs(g, u, been);          // Recursively visit unvisited neighbor
  }
  return;
}

int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  std::vector<std::vector<long>> g(n + 1);  // Graph representation of guests and shared flavors
  for (long p = 0; p < k; p++) {            // Read all guest favorite pairs
    long x, y;
    scanf("%ld %ld", &x, &y);
    g[x].push_back(y);      // Add edge from x to y
    g[y].push_back(x);      // Add edge from y to x (undirected graph)
  }
  long cnt(0);              // Counter for connected components
  std::vector<bool> vis(n + 1, 0);  // Visited array initialized to false
  for (long p = 1; p <= n; p++) {   // Check all nodes
    if (vis[p]) {                   // If already visited, skip
      continue;
    }
    ++cnt;                          // Found new connected component
    dfs(g, p, vis);                 // Perform DFS to mark all nodes in component
  }
  printf("%ld\n", k - n + cnt);     // Output minimum sad guests
  return 0;
}


// https://github.com/VaHiX/codeForces/