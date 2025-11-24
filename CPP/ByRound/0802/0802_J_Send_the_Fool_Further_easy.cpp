// Problem: CF 802 J - Send the Fool Further! (easy)
// https://codeforces.com/contest/802/problem/J

/*
 * Problem: Send the Fool Further! (easy)
 * 
 * Purpose: Find the maximum total travel cost in a path from node 0 (Jenny)
 *          to any leaf in a tree, such that no node is visited twice.
 * 
 * Algorithm: 
 *   - Build an adjacency matrix representation of the tree.
 *   - Perform DFS starting from node 0 to explore all possible paths.
 *   - Track the maximum cost of any path from root to leaf.
 *   - Since the graph is a tree, there are no cycles, so we don't need to worry
 *     about revisiting nodes beyond the initial visit.
 * 
 * Time Complexity: O(n^2) due to the adjacency matrix storage and DFS traversal
 * Space Complexity: O(n^2) for the adjacency matrix and O(n) for the visited array and recursion stack
 * 
 * Techniques:
 *   - Tree DFS traversal
 *   - Maximum path cost tracking
 */

#include <cstdio>
#include <vector>

void dfs(int node, const std::vector<std::vector<long>> &g,
         std::vector<bool> &visited, long current, long &maxCost) {
  if (visited[node]) {
    return;
  }
  visited[node] = 1;
  maxCost = (current > maxCost) ? current : maxCost;
  for (int u = 0; u < g[node].size(); u++) {
    if (g[node][u] == 0) {
      continue;
    }
    if (visited[u]) {
      continue;
    }
    dfs(u, g, visited, current + g[node][u], maxCost);
  }
  return;
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<std::vector<long>> g(n, std::vector<long>(n, 0));
  for (long p = 1; p < n; p++) {
    int x, y;
    long c;
    scanf("%d %d %ld", &x, &y, &c);
    g[x][y] = g[y][x] = c;
  }
  long maxCost(0);
  std::vector<bool> visited(n, 0);
  dfs(0, g, visited, 0, maxCost);
  printf("%ld\n", maxCost);
  return 0;
}


// https://github.com/VaHiX/CodeForces/