// Problem: CF 741 B - Arpa's weak amphitheater and Mehrdad's valuable Hoses
// https://codeforces.com/contest/741/problem/B

/*
 * Problem: Arpa's weak amphitheater and Mehrdad's valuable Hoses
 * 
 * Algorithm/Techniques:
 * - Union-Find / Connected Components: Identify friendship groups using DFS
 * - 0/1 Knapsack on Components: For each friendship group, compute max beauty for each possible weight
 * 
 * Time Complexity: O(n * W + m), where n is number of Hoses, W is maximum weight, m is number of friendships
 * Space Complexity: O(n * W), for the DP table and auxiliary structures
 * 
 * Approach:
 * 1. Build graph from friendship pairs
 * 2. Use DFS to find connected components (friendship groups)
 * 3. For each component, calculate total weight and beauty
 * 4. Apply dynamic programming knapsack on each group
 * 5. Combine results to get maximum total beauty under weight constraint
 */

#include <cstdio>
#include <vector>
#include <algorithm>

void dfs(long node, const std::vector<std::vector<long>> &g,
         std::vector<long> &h, long root) {
  if (h[node] >= 0) {
    return;
  }
  h[node] = root;  // Mark the root of the component
  for (long p = 0; p < g[node].size(); p++) {
    dfs(g[node][p], g, h, root);  // Continue DFS for neighbors
  }
  return;
}

int main() {
  long n, m, W;
  scanf("%ld %ld %ld", &n, &m, &W);
  std::vector<long> w(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &w[p]);
  }
  std::vector<long> b(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &b[p]);
  }
  std::vector<std::vector<long>> g(n);
  for (long p = 0; p < m; p++) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    --x;
    --y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  std::vector<long> head(n, -1);
  for (long p = 0; p < n; p++) {
    dfs(p, g, head, p);  // Find root for each node
  }
  std::vector<long> sw(n, 0);
  std::vector<long> sb(n, 0);
  std::vector<std::vector<long>> sv(n);
  for (long p = 0; p < n; p++) {
    sw[head[p]] += w[p];     // Sum weights in component
    sb[head[p]] += b[p];     // Sum beauties in component
    sv[head[p]].push_back(p); // Store indices of nodes in component
  }
  std::vector<long> f(W + 1, 0);  // DP array for knapsack
  for (long p = 0; p < n; p++) {
    if (head[p] != p) {
      continue;  // Skip non-root nodes
    }
    for (long ww = W; ww >= 0; ww--) {
      if (sw[p] <= ww) {
        f[ww] = std::max(f[ww], f[ww - sw[p]] + sb[p]);  // Option 1: Take all in component
      }
      for (long t = 0; t < sv[p].size(); t++) {
        long u = sv[p][t];
        if (w[u] <= ww) {
          f[ww] = std::max(f[ww], f[ww - w[u]] + b[u]);  // Option 2: Take single node
        }
      }
    }
  }
  printf("%ld\n", f[W]);
  return 0;
}


// https://github.com/VaHiX/CodeForces/