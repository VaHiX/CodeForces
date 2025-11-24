// Problem: CF 862 B - Mahmoud and Ehab and the bipartiteness
// https://codeforces.com/contest/862/problem/B

/*
Purpose: 
This code determines the maximum number of edges that can be added to a tree to keep it bipartite.
The solution uses a DFS to partition the tree into two sets (bipartition), then computes the maximum 
edges possible between these two sets minus the existing edges.

Algorithms/Techniques:
- Depth-First Search (DFS) for bipartitioning the tree
- Counting nodes in each partition to compute maximum possible edges
- Formula: (a * b - (n - 1)) where a and b are sizes of the two partitions

Time Complexity: O(n) where n is the number of nodes
Space Complexity: O(n) for storing the graph and visited/partition arrays

Note:
A bipartite graph can have edges only between nodes of different sets. 
Adding edges within the same set makes the graph non-bipartite.
*/
#include <stdint.h>
#include <cstdio>
#include <vector>

void dfs(int64_t node, const std::vector<std::vector<int64_t>> &g,
         std::vector<bool> &visited, std::vector<bool> &gv, bool grp) {
  if (visited[node]) {
    return;
  }
  visited[node] = 1;
  gv[node] = grp; // Assign group (0 or 1) to the node
  for (int64_t p = 0; p < g[node].size(); p++) {
    int64_t u = g[node][p];
    if (visited[u]) {
      continue;
    }
    dfs(u, g, visited, gv, 1 - grp); // Alternate group for neighbors
  }
  return;
}

int main() {
  int64_t n;
  scanf("%lld", &n);
  std::vector<std::vector<int64_t>> g(n);
  for (int64_t p = 1; p < n; p++) {
    int64_t x, y;
    scanf("%lld %lld", &x, &y);
    --x; // Convert to 0-based indexing
    --y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  std::vector<bool> visited(n, 0);
  std::vector<bool> gv(n, 0);
  dfs(0, g, visited, gv, 0); // Start DFS from node 0, assign group 0
  int64_t a(0);
  for (int64_t p = 0; p < n; p++) {
    a += gv[p]; // Count nodes in group 1 (true values)
  }
  int64_t b = n - a; // Nodes in group 0
  int64_t ans = a * b - (n - 1); // Maximum edges = a*b - existing edges
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/