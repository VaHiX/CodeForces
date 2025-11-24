// Problem: CF 659 E - New Reform
// https://codeforces.com/contest/659/problem/E

/*
 * Purpose: Find the minimum number of separate cities after converting
 *          bidirectional roads into unidirectional ones in a graph.
 *          
 * Algorithm: 
 *   - Treat the input as an undirected graph.
 *   - For each connected component, determine if it contains a cycle.
 *   - If a connected component has more edges than nodes (v > e/2),
 *     then it must contain a cycle, and we can orient edges to avoid
 *     creating separate cities.
 *   - If it's a tree (or forest of trees), then we have to leave at least one city
 *     unvisited (separate) to minimize separateness.
 *
 * Time Complexity: O(n + m) where n is number of vertices and m is number of edges.
 * Space Complexity: O(n + m) for storing the graph and visited array.
 */

#include <cstdio>
#include <vector>

// DFS function to traverse the component and count nodes and edges
// 'order' represents number of nodes in component
// 'size' represents total degree sum (2 * number of edges)
void dfs(const std::vector<std::vector<long>> &g, long node,
         std::vector<bool> &visited, long &order, long &size) {
  if (visited[node]) {
    return;
  }
  visited[node] = true;
  ++order;
  size += g[node].size();
  for (long p = 0; p < g[node].size(); p++) {
    long u = g[node][p];
    if (visited[u]) {
      continue;
    }
    dfs(g, u, visited, order, size);
  }
  return;
}

int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  std::vector<std::vector<long>> g(n + 1);
  for (long p = 0; p < m; p++) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    g[x].push_back(y);
    g[y].push_back(x);
  }
  long count(0);
  std::vector<bool> been(n + 1, 0);
  for (long p = 1; p <= n; p++) {
    if (been[p]) {
      continue;
    }
    long v(0), e(0);
    dfs(g, p, been, v, e);
    // If more edges than nodes (indicating a cycle), no separate city needed
    // Otherwise, we need 1 separate city for this tree/component
    count += (v > e / 2);
  }
  printf("%ld\n", count);
  return 0;
}


// https://github.com/VaHiX/CodeForces/