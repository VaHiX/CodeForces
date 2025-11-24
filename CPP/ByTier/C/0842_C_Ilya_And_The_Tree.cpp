// Problem: CF 842 C - Ilya And The Tree
// https://codeforces.com/contest/842/problem/C

/*
 * Problem: Ilya And The Tree
 * Algorithm: Tree DFS with GCD tracking
 * 
 * Time Complexity: O(n * sqrt(max_a) * log(max_a)) where n is number of nodes,
 *                  and max_a is the maximum value in the array. Each node's
 *                  set of GCDs can be at most log(max_a), and we process each
 *                  node once.
 * Space Complexity: O(n * sqrt(max_a)) for storing the sets of GCDs for each node.
 *
 * Approach:
 * - Build a tree from the input edges.
 * - Perform DFS traversal from root (node 0).
 * - For each node, maintain the GCD from the root to the current node.
 * - Also maintain a set of all possible GCDs from root to any ancestor of the current node.
 * - When processing a child node, compute new GCDs by combining the GCD from root to parent
 *   with the value of the child node. Update max possible GCD for this node based on all
 *   previously computed GCDs in its ancestor set.
 */

#include <cstdio>
#include <set>
#include <vector>
long gcd(long a, long b) { return (b == 0) ? a : gcd(b, a % b); }

// DFS traversal to compute max possible beauty for each node
void dfs(long node, const std::vector<std::vector<long>> &g,
         const std::vector<long> &a, std::vector<bool> &vis,
         std::vector<long> &pathgcd, std::vector<std::set<long>> &gs,
         std::vector<long> &maxgcd) {
  if (vis[node]) {
    return;
  }
  vis[node] = true;
  for (long p = 0; p < g[node].size(); p++) {
    long u = g[node][p];
    if (vis[u]) {
      continue;
    }
    // Compute GCD from root to current node u
    pathgcd[u] = gcd(pathgcd[node], a[u]);
    // Insert path GCD from root to node u
    gs[u].insert(pathgcd[node]);
    gs[u].insert(pathgcd[u]);
    // If the parent node has an empty set of GCDs, insert its own value
    if (gs[node].size() == 0) {
      gs[u].insert(a[u]);
    } else {
      // Iterate through all GCDs up to parent and compute GCD with a[u]
      for (std::set<long>::iterator it = gs[node].begin(); it != gs[node].end();
           it++) {
        gs[u].insert(gcd(*it, a[u]));
      }
    }
    // Set max possible GCD for node u as the largest value in its set
    maxgcd[u] = *(--gs[u].end());
    dfs(u, g, a, vis, pathgcd, gs, maxgcd);
  }
  return;
}

int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  std::vector<std::vector<long>> g(n);
  for (long p = 1; p < n; p++) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    --x;
    --y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  std::vector<long> maxgcd(n, 0);
  maxgcd[0] = a[0];
  std::vector<long> pathgcd(n, 0);
  pathgcd[0] = a[0];
  std::vector<bool> been(n, 0);
  std::vector<std::set<long>> gcdSets(n);
  const long root(0);
  dfs(root, g, a, been, pathgcd, gcdSets, maxgcd);
  for (long p = 0; p < n; p++) {
    printf("%ld ", maxgcd[p]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/