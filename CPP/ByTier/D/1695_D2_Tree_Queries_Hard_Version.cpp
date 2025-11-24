// Problem: CF 1695 D2 - Tree Queries (Hard Version)
// https://codeforces.com/contest/1695/problem/D2

/*
 * Problem: D2. Tree Queries (Hard Version)
 * 
 * Purpose: Determine the minimum number of queries required to uniquely identify a hidden vertex x in a tree,
 *          given the distances from queried vertices to x.
 * 
 * Algorithm:
 *   - This problem is based on the concept of tree center and diameter.
 *   - The key insight is that we need to find a set of vertices such that for any two vertices in the tree,
 *     their distance to x is unique. This is essentially about determining how many queries are needed
 *     to resolve all possible locations of x.
 *   - The solution uses DFS to find the "endpoints" of paths in the tree, where each leaf node leads
 *     to a unique internal node (the "center" of a path). If multiple such paths meet at a node,
 *     that node can be part of the query set.
 *   - This approach works by identifying the endpoints of the longest paths in the tree (i.e., leaves
 *     and the internal nodes they point to), and using them to distinguish between nodes.
 * 
 * Time Complexity: O(n) per test case, since each node is visited once during DFS processing.
 * Space Complexity: O(n) for the adjacency list representation of the tree and auxiliary arrays.
 */

#include <cstdio>
#include <vector>
const int N = 2e5 + 7;
std::vector<int> to[N];
bool vis[N];

// Function to find the endpoint of a path from a leaf
// It traverses the tree starting from a leaf, going towards the center
int dfs(int i, int l) {
  // If current node has more than 2 neighbors, it's a central node in a path
  if (to[i].size() > 2)
    return i;
  // Traverse to the only neighbor that is not the previous node (l)
  for (int v : to[i])
    if (v != l)
      return dfs(v, i);
  return i;
}

int main() {
  int T, n, u, v, ans;
  scanf("%d", &T);
  while (T--) {
    ans = 0;
    scanf("%d", &n);
    // Clear adjacency list for current test case
    for (int i = 1; i <= n; ++i)
      to[i].clear();
    // Read edges and build adjacency list
    for (int i = 1; i < n; ++i)
      scanf("%d%d", &u, &v), to[u].push_back(v), to[v].push_back(u);
    // For each leaf node (degree 1), mark the node it points to (which is part of the path)
    for (int i = 1; i <= n; ++i)
      if (to[i].size() == 1)
        vis[dfs(i, 0)] = 1, ++ans;
    // Check which nodes have been marked to reduce count accordingly
    for (int i = 1; i <= n; ++i)
      if (vis[i])
        vis[i] = 0, --ans;
    // Special case: if there's only one vertex, no queries needed
    printf("%d\n", n == 1 ? 0 : (ans ? ans : 1));
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/