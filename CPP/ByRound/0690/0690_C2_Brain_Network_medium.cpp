// Problem: CF 690 C2 - Brain Network (medium)
// https://codeforces.com/contest/690/problem/C2

/*
 * Problem: C2. Brain Network (medium)
 *
 * Purpose: Compute the brain latency of a zombie's nervous system.
 *          Brain latency is defined as the maximum distance between any two brains,
 *          where distance is the minimum number of connectors between them.
 *
 * Algorithm: The approach computes the diameter of the tree (since it's a connected graph,
 *            and based on problem constraints, it forms a tree or forest of trees).
 *            This is done using two DFS traversals:
 *            1. Start from any node (node 0) and find the furthest node.
 *            2. Start from the furthest node and find another furthest node.
 *            The maximum distance found in the second DFS is the diameter (brain latency).
 *
 * Time Complexity: O(n + m), where n is number of nodes and m is number of edges.
 * Space Complexity: O(n + m), for adjacency list and visited arrays.
 */

#include <cstdio>
#include <vector>

// DFS function to find the furthest node from a starting node
void dfs(long node, const std::vector<std::vector<long>> &g,
         std::vector<bool> &visited, long dist, long &maxDist, long &furthest) {
  if (visited[node]) {
    return;
  }
  visited[node] = true;
  if (dist > maxDist) {
    furthest = node;
    maxDist = dist;
  }
  for (long p = 0; p < g[node].size(); p++) {
    long u = g[node][p];
    if (visited[u]) {
      continue;
    }
    dfs(u, g, visited, dist + 1, maxDist, furthest);
  }
  return;
}

int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  std::vector<std::vector<long>> g(n);
  for (long p = 1; p < n; p++) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    --x;
    --y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  std::vector<bool> visitedA(n, 0);
  long maxDist(0), furthest(0);
  dfs(0, g, visitedA, 0, maxDist, furthest);
  std::vector<bool> visitedB(n, 0);
  dfs(furthest, g, visitedB, 0, maxDist, furthest);
  printf("%ld\n", maxDist);
  return 0;
}


// https://github.com/VaHiX/CodeForces/