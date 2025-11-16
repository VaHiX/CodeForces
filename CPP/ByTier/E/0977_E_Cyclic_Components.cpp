// Problem: CF 977 E - Cyclic Components
// https://codeforces.com/contest/977/problem/E

/*
 * Problem: E. Cyclic Components
 * 
 * Purpose: 
 *   This code determines the number of connected components in an undirected graph that are cycles.
 *   A cycle is defined as a connected component where every vertex has exactly two edges (degree 2),
 *   and the component forms a single closed loop.
 *
 * Algorithms/Techniques:
 *   - Graph traversal using Depth-First Search (DFS)
 *   - For each unvisited node, initiate a DFS to explore the connected component
 *   - During DFS, check if all nodes in the component have degree 2
 *   - If yes, then component is a cycle
 *
 * Time Complexity:
 *   O(n + m), where n is the number of vertices and m is the number of edges.
 *   Each node and edge is visited once during the traversal.
 *
 * Space Complexity:
 *   O(n + m), for storing the adjacency list representation of the graph and the visited array.
 */

#include <cstdio>
#include <vector>

// DFS function to traverse component and check if it's a cycle
// 'node' is the current node being processed
// 'g' is the adjacency list of the graph
// 'been' marks visited nodes
// 'circle' indicates if the current component is a cycle (modified by reference)
void dfs(long node, const std::vector<std::vector<long>> &g,
         std::vector<bool> &been, bool &circle) {
  if (been[node]) {
    return;
  }
  been[node] = true;
  // If current node doesn't have exactly 2 neighbors, it cannot be part of a cycle
  if (g[node].size() != 2) {
    circle = false;
  }
  // Traverse all neighbors
  for (long p = 0; p < g[node].size(); p++) {
    long u = g[node][p];
    if (been[u]) {
      continue;
    }
    dfs(u, g, been, circle);
  }
  return;
}

int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  // Create adjacency list for the graph, using 1-based indexing
  std::vector<std::vector<long>> g(n + 1);
  for (long p = 0; p < m; p++) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    g[x].push_back(y);
    g[y].push_back(x);
  }
  // Track visited nodes to avoid reprocessing
  std::vector<bool> visited(n + 1, 0);
  long cnt(0); // Count of cyclic components
  // Traverse all nodes
  for (long p = 1; p <= n; p++) {
    if (visited[p]) {
      continue;
    }
    bool isCycle(true);
    dfs(p, g, visited, isCycle);
    cnt += isCycle;
  }
  printf("%ld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/CodeForces/