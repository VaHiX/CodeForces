// Problem: CF 1606 F - Tree Queries
// https://codeforces.com/contest/1606/problem/F

/*
Algorithm: Tree Dynamic Programming with Memoization
Time Complexity: O(n + q)
Space Complexity: O(n)

This solution uses a tree DP approach to precompute for each node the optimal 
number of children when deleting vertices. The key insight is to compute for 
each node a set of "delta values" representing the maximum gain in children 
when deleting a certain number of vertices from the subtree.

The dfs function computes:
1. For each vertex, the number of children (d[u])
2. A dp array where dp[u][i] represents the sum of children of all nodes in 
   subtree u minus 1 for each node, when i vertices are deleted
3. An f array for each node that stores the optimal "marginal gain" values

The main query process just looks up the precomputed data.
*/
#include <stdio.h>
#include <algorithm>
#include <string>

const int N = 200010;
int n, q, m, d[N];
std::basic_string<int> g[N];
std::basic_string<int> dp[N], f[N];

// DFS to compute dp and f arrays for each node
void dfs(int u, int fa) {
  int mx = 0;
  // Iterate through all children of node u
  for (auto &v : g[u]) {
    if (v == fa)
      continue; // Skip parent
    dfs(v, u); // Recursively process child
    ++d[u]; // Increment child count for u
    mx = std::max(mx, (int)f[v].size()); // Track maximum size of f[v]
  }
  
  // Initialize dp[u] with size mx, each element set to d[u]
  dp[u].resize(mx, d[u]);
  
  // Combine results from all children
  for (auto &v : g[u]) {
    if (v == fa)
      continue;
    // Add contribution of child v's f array to parent's dp array
    for (int k = 0; k < f[v].size(); ++k)
      dp[u][k] += f[v][k] - 1;
  }
  
  // Build the f array for node u based on the dp results
  for (int i = 0;; ++i) {
    int tmp = (i >= dp[u].size() ? d[u] : dp[u][i]);
    if (tmp - i <= 1)
      break; // Stop when marginal gain becomes too small
    f[u].push_back(tmp - i); // Add marginal gain to f[u]
  }
}

int main() {
  scanf("%d", &n);
  // Read edges and build adjacency list
  for (int i = 1; i < n; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    g[x].push_back(y);
    g[y].push_back(x);
  }
  
  // Perform DFS from root (node 1)
  dfs(1, 0);
  
  // Process queries
  scanf("%d", &q);
  while (q--) {
    int v, k;
    scanf("%d%d", &v, &k);
    // Output result: if k is within dp[v] range, use dp[v][k], otherwise use d[v]
    printf("%d\n", k < dp[v].size() ? dp[v][k] : d[v]);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/