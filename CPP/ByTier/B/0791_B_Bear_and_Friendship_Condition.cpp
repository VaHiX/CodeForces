// Problem: CF 791 B - Bear and Friendship Condition
// https://codeforces.com/contest/791/problem/B

/*
 * Purpose: Check if a social network is "reasonable" based on the condition that
 *          for any three distinct members X, Y, Z, if X-Y and Y-Z are friends,
 *          then X-Z must also be friends. This is equivalent to checking whether
 *          every connected component in the graph is a complete graph (clique).
 *
 * Algorithm/Techniques:
 * - Graph representation using adjacency list
 * - DFS traversal to explore connected components
 * - For each connected component, check if number of edges >= nodeCount * (nodeCount - 1)
 *   which is the minimum required for a clique (each node connected to every other)
 *
 * Time Complexity: O(n + m), where n is number of nodes, m is number of edges
 * Space Complexity: O(n + m), for storing the graph and visited array
 */

#include <stdint.h>
#include <cstdio>
#include <vector>

void dfs(int64_t node, const std::vector<std::vector<int64_t>> &g,
         std::vector<bool> &been, int64_t &numEdges, int64_t &numNodes) {
  if (been[node]) {
    return;
  }
  been[node] = 1;
  ++numNodes;
  std::vector<int64_t> adj = g[node];
  for (int64_t p = 0; p < adj.size(); p++) {
    ++numEdges; // Count edges in the component, but we do not divide by 2 since each edge is counted twice in an undirected graph
    dfs(adj[p], g, been, numEdges, numNodes);
  }
  return;
}

int main() {
  int64_t n, m;
  scanf("%lld %lld", &n, &m);
  std::vector<std::vector<int64_t>> g(n + 1);
  for (int64_t p = 0; p < m; p++) {
    int64_t x, y;
    scanf("%lld %lld", &x, &y);
    g[x].push_back(y);
    g[y].push_back(x);
  }
  std::vector<bool> visited(n + 1, 0);
  bool reasonable(true);
  for (int p = 1; p <= n; p++) {
    if (visited[p]) {
      continue;
    }
    int64_t edgeCount(0), nodeCount(0);
    dfs(p, g, visited, edgeCount, nodeCount);
    // For a complete graph (clique), number of edges must be at least
    // nodeCount * (nodeCount - 1) / 2. Since we count each edge twice,
    // the condition becomes edgeCount >= nodeCount * (nodeCount - 1)
    if (edgeCount < nodeCount * (nodeCount - 1)) {
      reasonable = false;
      break;
    }
  }
  puts(reasonable ? "YES" : "NO");
  return 0;
}


// https://github.com/VaHiX/CodeForces/