// Problem: CF 893 C - Rumor
// https://codeforces.com/contest/893/problem/C

/*
 * Problem: C. Rumor
 * 
 * Purpose: Find the minimum cost to spread a rumor to all characters in a graph,
 *          where each character has a cost to bribe and can spread the rumor to
 *          their friends for free. The graph is undirected and each connected
 *          component needs at least one character bribed.
 * 
 * Algorithm: 
 *   - Model the problem as finding connected components in an undirected graph.
 *   - For each connected component, we must bribe the cheapest character to start
 *     the rumor spreading, as they will spread it to all others in the component.
 *   - Use DFS to traverse each connected component and track the minimum cost
 *     within that component.
 * 
 * Time Complexity: O(n + m), where n is the number of nodes and m is the number of edges.
 * Space Complexity: O(n + m), for the adjacency list and visited array.
 */

#include <cstdio>
#include <vector>
typedef long long ll;

// Depth-first search to traverse a connected component and find the minimum cost
void dfs(long node, long &minCost, std::vector<bool> &vis,
         const std::vector<long> &costVec,
         const std::vector<std::vector<long>> &g) {
  if (vis[node]) {
    return; // Already visited, skip
  }
  vis[node] = true; // Mark as visited
  // Update the minimum cost in this component
  minCost = (minCost < costVec[node]) ? minCost : costVec[node];
  // Visit all neighbors
  for (long p = 0; p < g[node].size(); p++) {
    long u = g[node][p];
    if (vis[u]) {
      continue; // Skip already visited nodes
    }
    dfs(u, minCost, vis, costVec, g);
  }
  return;
}

int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  std::vector<long> costVec(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &costVec[p]);
  }
  std::vector<std::vector<long>> g(n);
  for (long p = 0; p < m; p++) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    --x; // Convert to 0-based indexing
    --y;
    g[x].push_back(y); // Add edge
    g[y].push_back(x); // Since graph is undirected
  }
  ll totalCost(0);
  std::vector<bool> visited(n, false);
  for (long p = 0; p < n; p++) {
    if (visited[p]) {
      continue; // Skip if already part of a component
    }
    long compCost(costVec[p]); // Start with cost of current node
    dfs(p, compCost, visited, costVec, g); // Find min cost in component
    totalCost += compCost; // Add cost to total
  }
  printf("%lld\n", totalCost);
  return 0;
}


// https://github.com/VaHiX/CodeForces/