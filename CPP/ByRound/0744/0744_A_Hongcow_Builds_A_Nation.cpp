// Problem: CF 744 A - Hongcow Builds A Nation
// https://codeforces.com/contest/744/problem/A

/*
 * Problem: Hongcow Builds A Nation
 * Algorithm: DFS to find connected components, then calculate maximum edges possible
 * Time Complexity: O(n + m), where n is number of nodes and m is number of edges
 * Space Complexity: O(n + m), for adjacency list and visited array
 *
 * The approach:
 * 1. For each government node, perform DFS to find all connected nodes in its component.
 * 2. For each such component, compute the maximum edges possible (complete graph minus current edges).
 * 3. Keep track of maximum number of nodes in any government-connected component.
 * 4. For all remaining unvisited nodes, connect them to the largest component to maximize edges.
 * 5. Adjust for double counting of edges in the final calculation.
 */

#include <cstdio>
#include <vector>

// Depth First Search to explore connected component
// Updates the number of nodes and total degree in the component
void dfs(const std::vector<std::vector<long>> &g, long node,
         std::vector<bool> &vis, long &order, long &dsz) {
  if (vis[node]) {
    return;
  }
  vis[node] = true;
  ++order;  // Count node
  dsz += g[node].size();  // Accumulate degree
  for (long p = 0; p < g[node].size(); p++) {
    long nn = g[node][p];
    if (vis[nn]) {
      continue;
    }
    dfs(g, nn, vis, order, dsz);
  }
  return;
}

int main() {
  long n, m, k;
  scanf("%ld %ld %ld", &n, &m, &k);
  std::vector<long> c(k);
  for (long p = 0; p < k; p++) {
    scanf("%ld", &c[p]);
  }
  std::vector<std::vector<long>> g(n + 1);  // Adjacency list
  for (long p = 0; p < m; p++) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    g[x].push_back(y);
    g[y].push_back(x);
  }
  
  long cnt(0);
  std::vector<bool> visited(n + 1, 0);  // Track visited nodes
  long maxNodes(0);  // Track max nodes in any government component

  // Process each government node's connected component
  for (long p = 0; p < k; p++) {
    long numNodes(0), edges(0);
    dfs(g, c[p], visited, numNodes, edges);
    maxNodes = (maxNodes > numNodes) ? maxNodes : numNodes;
    edges /= 2;
    // Add edges in complete graph minus existing edges in component
    cnt += (numNodes * (numNodes - 1)) / 2 - edges;
  }
  
  long rem(0);  // Degree of remaining components
  // Handle remaining unvisited nodes (non-government connected components)
  for (long p = 1; p <= n; p++) {
    if (visited[p]) {
      continue;
    }
    rem += g[p].size();
    cnt += maxNodes;  // Connect to largest component
    ++maxNodes;  // Increase size of largest component
  }
  cnt -= rem / 2;  // Correct for double counting edges
  printf("%ld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/CodeForces/