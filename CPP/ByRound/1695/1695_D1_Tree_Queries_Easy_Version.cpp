// Problem: CF 1695 D1 - Tree Queries (Easy Version)
// https://codeforces.com/contest/1695/problem/D1

/*
 * Problem: D1. Tree Queries (Easy Version)
 * 
 * Purpose: 
 *   Given an unrooted tree with n vertices, determine the minimum number of queries 
 *   needed to uniquely identify a hidden vertex x. Each query asks for the distance 
 *   from a vertex v to x. The solution uses the concept of centroid decomposition and 
 *   tree traversal to compute the minimum number of queries required.
 * 
 * Algorithm:
 *   - For each node in the tree, perform a DFS to calculate how many "leaves" can be 
 *     covered by a single query from that node, based on the structure of the tree.
 *   - The result is the minimum among all such computations.
 * 
 * Time Complexity:
 *   O(n^2) in the worst case due to the nested loop of checking all nodes and performing DFS.
 *   In practice, for trees with reasonable branching, it's much faster.
 * 
 * Space Complexity:
 *   O(n) for storing the tree adjacency list and auxiliary arrays.
 */

#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;
const int N = 1e5 + 5;
int t, n, x, y, f[N], ans;
vector<int> v[N];

// DFS to compute the number of required queries for a specific root node
void dfs(int x, int fa) {
  int c = 0; // Count of children that are leaves (no further children)
  for (int y : v[x])
    if (y != fa)
      dfs(y, x), f[x] += f[y], c += !f[y]; // Recursively process and count leaves
  f[x] += max(c - 1, 0); // Adjust based on number of children that are leaves
}

signed main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n), ans = 1e9;
    for (int i = 1; i <= n; i++)
      v[i].clear(); // Clear previous edges
    
    // Read edges and build adjacency list
    for (int i = 1; i < n; i++)
      scanf("%d%d", &x, &y), v[x].push_back(y), v[y].push_back(x);
    
    // Special case: only one node
    if (n == 1) {
      puts("0");
      continue;
    }
    
    // Try every node as a starting point and calculate the min queries
    for (int i = 1; i <= n; i++)
      if (v[i].size() < 2) { // Only consider nodes with less than 2 neighbors
        fill(f + 1, f + 1 + n, 0); // Reset f array
        dfs(i, 0); // Compute the number of queries needed
        ans = min(ans, f[i] + 1); // Update minimum
      }
    
    printf("%d\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/